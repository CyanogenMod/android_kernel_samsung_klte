/*
** =========================================================================
** File:
**     tspdrv_drv2604.c
**
** Description: 
**     TouchSense Kernel Module main entry-point.
**
** Portions Copyright (c) 2008-2014 Immersion Corporation. All Rights Reserved.
**
** This file contains Original Code and/or Modifications of Original Code 
** as defined in and that are subject to the GNU Public License v2 - 
** (the 'License'). You may not use this file except in compliance with the 
** License. You should have received a copy of the GNU General Public License 
** along with this program; if not, write to the Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA or contact 
** TouchSenseSales@immersion.com.
**
** The Original Code and all software distributed under the License are 
** distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER 
** EXPRESS OR IMPLIED, AND IMMERSION HEREBY DISCLAIMS ALL SUCH WARRANTIES, 
** INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS 
** FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. Please see 
** the License for the specific language governing rights and limitations 
** under the License.
** =========================================================================
*/

#ifndef __KERNEL__
#define __KERNEL__
#endif

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <tspdrv_drv2604.h>
#include <linux/vibrator.h>
#include "../staging/android/timed_output.h"
#include <linux/of_gpio.h>
#include <linux/delay.h>
#include <linux/wakelock.h>

static int g_nTimerPeriodMs = 5; /* 5ms timer by default. This variable could be used by the SPI.*/

#ifdef VIBE_RUNTIME_RECORD
/* Flag indicating whether runtime recorder on or off */
static atomic_t g_bRuntimeRecord;
#endif

#include <Immvibespi_drv2604.c>
#if (defined(VIBE_DEBUG) && defined(VIBE_RECORD)) || defined(VIBE_RUNTIME_RECORD)
#include <tspdrvRecorder.c>
#endif

/* Device name and version information */
#define VERSION_STR " v3.7.45.1\n"                  /* DO NOT CHANGE - this is auto-generated */
#define VERSION_STR_LEN 16                          /* account extra space for future extra digits in version number */
static char g_szDeviceName[  (VIBE_MAX_DEVICE_NAME_LENGTH 
                            + VERSION_STR_LEN)
                            * NUM_ACTUATORS];       /* initialized in init_module */
static size_t g_cchDeviceName;                      /* initialized in init_module */

/* Flag indicating whether the driver is in use */
static char g_bIsPlaying = false;

/* Flag indicating the debug level*/
static atomic_t g_nDebugLevel;


/* Buffer to store data sent to SPI */
#define MAX_SPI_BUFFER_SIZE (NUM_ACTUATORS * (VIBE_OUTPUT_SAMPLE_SIZE + SPI_HEADER_SIZE))

static char g_cWriteBuffer[MAX_SPI_BUFFER_SIZE];


#if ((LINUX_VERSION_CODE & 0xFFFF00) < KERNEL_VERSION(2,6,0))
#error Unsupported Kernel version
#endif

#ifndef HAVE_UNLOCKED_IOCTL
#define HAVE_UNLOCKED_IOCTL 0
#endif

#ifdef IMPLEMENT_AS_CHAR_DRIVER
static int g_nMajor = 0;
#endif



/* Needs to be included after the global variables because they use them */
#include <tspdrvOutputDataHandler_drv2604.c>
#ifdef CONFIG_HIGH_RES_TIMERS
    #include <VibeOSKernelLinuxHRTime_drv2604.c>
#else
    #include <VibeOSKernelLinuxTime_drv2604.c>
#endif

static struct hrtimer timer;
static int max_timeout = 10000;
static int vibrator_value = 0;
static int vibrator_work;
static int drv2604_enabled;

static void _set_vibetonz_work(struct work_struct *unused);

static DECLARE_WORK(vibetonz_work, _set_vibetonz_work);
struct vibrator_platform_data_drv2604 vibrator_drvdata;

static int set_vibetonz(int timeout)
{
        int8_t strength;
        if(!timeout) {
                strength = 0;
                ImmVibeSPI_ForceOut_SetSamples(0,8,1,&strength);
        }
        else {
                DbgOut((KERN_INFO "tspdrv: ENABLE\n"));
                strength = 126;
                ImmVibeSPI_ForceOut_SetSamples(0,8,1,&strength);
        }

        vibrator_value = timeout;
        return 0;
}

static void _set_vibetonz_work(struct work_struct *unused)
{
        set_vibetonz(vibrator_work);

        return;
}


static enum hrtimer_restart vibetonz_timer_func(struct hrtimer *timer)
{
        vibrator_work = 0;
        schedule_work(&vibetonz_work);
        return HRTIMER_NORESTART;
}

static int get_time_for_vibetonz(struct timed_output_dev *dev)
{
        int remaining;

        if (hrtimer_active(&timer)) {
                ktime_t r = hrtimer_get_remaining(&timer);
                remaining = (int)ktime_to_ms(r);
        } else
                remaining = 0;

        if (vibrator_value ==-1)
                remaining = -1;

        return remaining;

}

static void enable_vibetonz_from_user(struct timed_output_dev *dev,int value)
{
        printk("[VIBETONZ] %s : time = %d msec \n",__func__,value);
        hrtimer_cancel(&timer);
        /* set_vibetonz(value); */
        vibrator_work = value;
        schedule_work(&vibetonz_work);


        if (value > 0)
        {
                if (value > max_timeout)
                        value = max_timeout;

                hrtimer_start(&timer,ktime_set(value / 1000, (value % 1000) * 1000000),
                                                HRTIMER_MODE_REL);
                vibrator_value = 0;
        }
}

static struct timed_output_dev timed_output_vt = {
        .name     = "vibrator",
        .get_time = get_time_for_vibetonz,
        .enable   = enable_vibetonz_from_user,
};

static void vibetonz_start(void)
{
        int ret = 0;

        hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
        timer.function = vibetonz_timer_func;

        ret = timed_output_dev_register(&timed_output_vt);
        if(ret)
                DbgOut((KERN_ERR "[VIBETONZ] timed_output_dev_register is fail \n"));
}


/* File IO */
static int open(struct inode *inode, struct file *file);
static int release(struct inode *inode, struct file *file);
static ssize_t read(struct file *file, char *buf, size_t count, loff_t *ppos);
static ssize_t write(struct file *file, const char *buf, size_t count, loff_t *ppos);
#if HAVE_UNLOCKED_IOCTL
static long unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
#else
static int ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);
#endif
static struct file_operations fops = 
{
    .owner =            THIS_MODULE,
    .read =             read,
    .write =            write,
#if HAVE_UNLOCKED_IOCTL
    .unlocked_ioctl =   unlocked_ioctl,
#else
    .ioctl =            ioctl,
#endif
    .open =             open,
    .release =          release,
    .llseek =           default_llseek    /* using default implementation as declared in linux/fs.h */
};

#ifndef IMPLEMENT_AS_CHAR_DRIVER
static struct miscdevice miscdev = 
{
	.minor =    MISC_DYNAMIC_MINOR,
	.name =     MODULE_NAME,
	.fops =     &fops
};
#endif

static int drv2604_parse_dt(struct device *dev)
{
        struct device_node *np = dev->of_node;
        vibrator_drvdata.motor_en = of_get_named_gpio(np, "drv2604,motor_en",0);
        return 0;
}


static int __devinit drv2604_vibrator_i2c_probe(struct i2c_client *client,
                        const struct i2c_device_id *id)
{

	int nRet, i,error;   /* initialized below */
	char status;
#if SKIP_AUTOCAL == 0
	int nCalibrationCount = 0;
#endif
        DbgOut((KERN_INFO "tspdrv: Probe called.\n"));

        vibrator_drvdata.client = client;
        if(!(client->dev.of_node)){
                        DbgOut(KERN_ERR "tspdrv: tspdrv probe failed, DT is NULL");
                        return -ENODEV;
        }
        error = drv2604_parse_dt(&client->dev);
        if (error)
                return error;

        if( gpio_request(vibrator_drvdata.motor_en, "MOTOR_EN") < 0)
        {
                return -EINVAL;
        }

        gpio_direction_output(vibrator_drvdata.motor_en, 0);
        gpio_export(vibrator_drvdata.motor_en, 0);


        nRet = misc_register(&miscdev);
        if (nRet)
        {
        DbgOut((KERN_ERR "tspdrv: misc_register failed.\n"));
                return nRet;
        }

#if USE_DRV2604_EN_PIN
    drv2604_set_en(true);
#endif
#if USE_DRV2604_STANDBY
    /* Wait 1000 us for chip power to stabilize */
    usleep_range(100000, 100000);
    drv2604_change_mode(MODE_DEVICE_READY);
#endif
    /* Wait 1000 us for chip power to stabilize */
    usleep_range(1000, 1000);

#if SKIP_AUTOCAL
    usleep_range(100000, 100000);
    drv2604_write_reg_val(init_sequence, sizeof(init_sequence));
    status = drv2604_read_reg(STATUS_REG);
#else
    /* Run auto-calibration */
    do{
        drv2604_write_reg_val(autocal_sequence, sizeof(autocal_sequence));

        /* Wait until the procedure is done */
        drv2604_poll_go_bit();

        /* Read status */
        status = drv2604_read_reg(STATUS_REG);
        nCalibrationCount++;

    } while (((status & DIAG_RESULT_MASK) == AUTO_CAL_FAILED) && (nCalibrationCount < MAX_AUTOCALIBRATION_ATTEMPT));

    /* Check result */
    if ((status & DIAG_RESULT_MASK) == AUTO_CAL_FAILED)
    {
      DbgOut((DBL_ERROR, "drv2604 auto-calibration failed after %d attempts.\n", nCalibrationCount));
    }
    else
    {
        /* Read calibration results */
        drv2604_read_reg(AUTO_CALI_RESULT_REG);
        drv2604_read_reg(AUTO_CALI_BACK_EMF_RESULT_REG);
        drv2604_read_reg(FEEDBACK_CONTROL_REG);
    }
#endif

    /* Read device ID */
    g_nDeviceID = (status & DEV_ID_MASK);

    switch (g_nDeviceID)
    {
        case DRV2605:
            DbgOut((DBL_INFO, "drv2604 driver found: drv2605.\n"));
            break;
        case DRV2604:
            DbgOut((DBL_INFO, "drv2604 driver found: drv2604.\n"));
            break;
        case DRV2604L:
            DbgOut((DBL_INFO, "drv2604 driver found: drv2604L.\n"));
            break;
        case DRV2605L:
            DbgOut((DBL_INFO, "drv2604 driver found: drv2605L.\n"));
            break;
        default:
            DbgOut((DBL_INFO, "drv2604 driver found: unknown.\n"));
            break;
    }

#if USE_DRV2604_STANDBY
    /* Put hardware in standby */
    drv2604_change_mode(MODE_STANDBY);
#elif USE_DRV2604_EN_PIN
    /* enable RTP mode that will be toggled on/off with EN pin */
#endif

#if USE_DRV2604_EN_PIN
    /* turn off chip */
    drv2604_set_en(false);
#endif

    DbgRecorderInit(());

    ImmVibeSPI_ForceOut_Initialize();
    VibeOSKernelLinuxInitTimer();
    ResetOutputData();

    /* Get and concatenate device name and initialize data buffer */
    g_cchDeviceName = 0;
    for (i=0; i<NUM_ACTUATORS; i++)
    {
        char *szName = g_szDeviceName + g_cchDeviceName;
        ImmVibeSPI_Device_GetName(i, szName, VIBE_MAX_DEVICE_NAME_LENGTH);

        /* Append version information and get buffer length */
        strcat(szName, VERSION_STR);
        g_cchDeviceName += strlen(szName);

    }
    vibetonz_start();
    return 0;
}

static int open(struct inode *inode, struct file *file) 
{
    DbgOut((DBL_INFO, "tspdrv: open.\n"));

    if (!try_module_get(THIS_MODULE)) return -ENODEV;

    return 0; 
}

static int release(struct inode *inode, struct file *file) 
{
    DbgOut((DBL_INFO, "tspdrv: release.\n"));

    /* 
    ** Reset force and stop timer when the driver is closed, to make sure
    ** no dangling semaphore remains in the system, especially when the
    ** driver is run outside of immvibed for testing purposes.
    */
    VibeOSKernelLinuxStopTimer();

    /* 
    ** Clear the variable used to store the magic number to prevent 
    ** unauthorized caller to write data. TouchSense service is the only 
    ** valid caller.
    */
    file->private_data = (void*)NULL;

    module_put(THIS_MODULE);

    return 0; 
}

static ssize_t read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
    const size_t nBufSize = (g_cchDeviceName > (size_t)(*ppos)) ? min(count, g_cchDeviceName - (size_t)(*ppos)) : 0;

    /* End of buffer, exit */
    if (0 == nBufSize) return 0;

    if (0 != copy_to_user(buf, g_szDeviceName + (*ppos), nBufSize)) 
    {
        /* Failed to copy all the data, exit */
        DbgOut((DBL_ERROR, "tspdrv: copy_to_user failed.\n"));
        return 0;
    }

    /* Update file position and return copied buffer size */
    *ppos += nBufSize;
    return nBufSize;
}

static ssize_t write(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
    *ppos = 0;  /* file position not used, always set to 0 */

    /* 
    ** Prevent unauthorized caller to write data. 
    ** TouchSense service is the only valid caller.
    */
    if (file->private_data != (void*)TSPDRV_MAGIC_NUMBER) 
    {
        DbgOut((DBL_ERROR, "tspdrv: unauthorized write.\n"));
        return 0;
    }

    /* 
    ** Ignore packets that have size smaller than SPI_HEADER_SIZE or bigger than MAX_SPI_BUFFER_SIZE.
    ** Please note that the daemon may send an empty buffer (count == SPI_HEADER_SIZE)
    ** during quiet time between effects while playing a Timeline effect in order to maintain
    ** correct timing: if "count" is equal to SPI_HEADER_SIZE, the call to VibeOSKernelLinuxStartTimer()
    ** will just wait for the next timer tick.
    */
    if ((count < SPI_HEADER_SIZE) || (count > MAX_SPI_BUFFER_SIZE))
    {
        DbgOut((DBL_ERROR, "tspdrv: invalid buffer size.\n"));
        return 0;
    }

    /* Copy immediately the input buffer */
    if (0 != copy_from_user(g_cWriteBuffer, buf, count))
    {
        /* Failed to copy all the data, exit */
        DbgOut((DBL_ERROR, "tspdrv: copy_from_user failed.\n"));
        return 0;
    }

    /* Extract force output samples and save them in an internal buffer */
    if (!SaveOutputData(g_cWriteBuffer, count))
    {
        DbgOut((DBL_ERROR, "tspdrv: SaveOutputData failed.\n"));
        return 0;
    }

    /* Start the timer after receiving new output force */
    g_bIsPlaying = true;

    VibeOSKernelLinuxStartTimer();

    return count;
}

#if HAVE_UNLOCKED_IOCTL
static long unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
#else
static int ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
#endif
{
    switch (cmd)
    {
        case TSPDRV_SET_MAGIC_NUMBER:
            file->private_data = (void*)TSPDRV_MAGIC_NUMBER;
            break;

        case TSPDRV_ENABLE_AMP:
            ImmVibeSPI_ForceOut_AmpEnable(arg);
#ifdef VIBE_RUNTIME_RECORD
            if (atomic_read(&g_bRuntimeRecord)) {
                DbgRecord((arg,";------- TSPDRV_ENABLE_AMP ---------\n"));
            }
#else
            DbgRecorderReset((arg));
            DbgRecord((arg,";------- TSPDRV_ENABLE_AMP ---------\n"));
#endif
            break;

        case TSPDRV_DISABLE_AMP:
            ImmVibeSPI_ForceOut_AmpDisable(arg);
#ifdef VIBE_RUNTIME_RECORD
            if (atomic_read(&g_bRuntimeRecord)) {
                DbgRecord((arg,";------- TSPDRV_DISABLE_AMP ---------\n"));
            }
#endif
            break;

        case TSPDRV_GET_NUM_ACTUATORS:
            return NUM_ACTUATORS;

#ifdef IMMVIBESPI_MULTIPARAM_SUPPORT
        case TSPDRV_GET_PARAM_FILE_ID:
            return ImmVibeSPI_Device_GetParamFileId();
#endif

        case TSPDRV_SET_DBG_LEVEL:
            {
                long nDbgLevel;
                if (0 != copy_from_user((void *)&nDbgLevel, (const void __user *)arg, sizeof(long))) {
                    /* Error copying the data */
                    DbgOut((DBL_ERROR, "copy_from_user failed to copy debug level data.\n"));
                    return -1;
                }

                if (DBL_TEMP <= nDbgLevel &&  nDbgLevel <= DBL_OVERKILL) {
                    atomic_set(&g_nDebugLevel, nDbgLevel);
                } else {
                    DbgOut((DBL_ERROR, "Invalid debug level requested, ignored."));
                }

                break;
            }

        case TSPDRV_GET_DBG_LEVEL:
            return atomic_read(&g_nDebugLevel);

#ifdef VIBE_RUNTIME_RECORD
        case TSPDRV_SET_RUNTIME_RECORD_FLAG:
            {
                long nRecordFlag;
                if (0 != copy_from_user((void *)&nRecordFlag, (const void __user *)arg, sizeof(long))) {
                    /* Error copying the data */
                    DbgOut((DBL_ERROR, "copy_from_user failed to copy runtime record flag.\n"));
                    return -1;
                }

                atomic_set(&g_bRuntimeRecord, nRecordFlag);
                if (nRecordFlag) {
                    int i;
                    for (i=0; i<NUM_ACTUATORS; i++) { 
                        DbgRecorderReset((i));
                    }
                }
                break;
            }
        case TSPDRV_GET_RUNTIME_RECORD_FLAG:
            return atomic_read(&g_bRuntimeRecord);
        case TSPDRV_SET_RUNTIME_RECORD_BUF_SIZE:
            {
                long nRecorderBufSize;
                if (0 != copy_from_user((void *)&nRecorderBufSize, (const void __user *)arg, sizeof(long))) {
                    /* Error copying the data */
                    DbgOut((DBL_ERROR, "copy_from_user failed to copy recorder buffer size.\n"));
                    return -1;
                }

                if (0 == DbgSetRecordBufferSize(nRecorderBufSize)) {
                    DbgOut((DBL_ERROR, "DbgSetRecordBufferSize failed.\n"));
                    return -1;
                }
                break;
            }
        case TSPDRV_GET_RUNTIME_RECORD_BUF_SIZE:
            return DbgGetRecordBufferSize();
#endif

        case TSPDRV_SET_DEVICE_PARAMETER:
            {
                device_parameter deviceParam;

                if (0 != copy_from_user((void *)&deviceParam, (const void __user *)arg, sizeof(deviceParam)))
                {
                    /* Error copying the data */
                    DbgOut((DBL_ERROR, "tspdrv: copy_from_user failed to copy kernel parameter data.\n"));
                    return -1;
                }

                switch (deviceParam.nDeviceParamID)
                {
                    case VIBE_KP_CFG_UPDATE_RATE_MS:
                        /* Update the timer period */
                        g_nTimerPeriodMs = deviceParam.nDeviceParamValue;



#ifdef CONFIG_HIGH_RES_TIMERS
                        /* For devices using high resolution timer we need to update the ktime period value */
                        g_ktTimerPeriod = ktime_set(0, g_nTimerPeriodMs * 1000000);
#endif
                        break;

                    case VIBE_KP_CFG_FREQUENCY_PARAM1:
                    case VIBE_KP_CFG_FREQUENCY_PARAM2:
                    case VIBE_KP_CFG_FREQUENCY_PARAM3:
                    case VIBE_KP_CFG_FREQUENCY_PARAM4:
                    case VIBE_KP_CFG_FREQUENCY_PARAM5:
                    case VIBE_KP_CFG_FREQUENCY_PARAM6:
                        if (0 > ImmVibeSPI_ForceOut_SetFrequency(deviceParam.nDeviceIndex, deviceParam.nDeviceParamID, deviceParam.nDeviceParamValue))
                        {
                            DbgOut((DBL_ERROR, "tspdrv: cannot set device frequency parameter.\n"));
                            return -1;
                        }
                        break;
                }
            }
        }
    return 0;
}

static int __devexit drv2604_remove(struct i2c_client *client)
{
	DbgOut((KERN_INFO "tspdrv: drv2604_remove_module.\n"));
	DbgRecorderTerminate(());
	VibeOSKernelLinuxTerminateTimer();
	ImmVibeSPI_ForceOut_Terminate();
	misc_deregister(&miscdev);
	gpio_free(vibrator_drvdata.motor_en);
	return 0;
}



static int drv2604_vibrator_suspend(struct i2c_client *client,pm_message_t mesg)
{

	int ret = 0;
        if (g_bIsPlaying){
        ret = -EBUSY;
        }
        else{
		DbgOut((KERN_INFO "tspdrv: suspend.\n"));
                if(drv2604_enabled){
                        gpio_set_value(vibrator_drvdata.motor_en, VIBRATION_OFF);
                        drv2604_enabled = 0;
                }
        DbgOut((KERN_ERR "[VIBTONZ] drv2604_early_suspend \n"));
        }
        return ret;

}

static int drv2604_vibrator_resume(struct i2c_client *client)
{

        DbgOut(KERN_DEBUG "[VIBTONZ] drv2604_vibrator_resume \n");
        return 0;
}

static const struct i2c_device_id drv2604_vibrator_device_id[] = {
        {"drv2604_vibrator", 0},
        {}
};
MODULE_DEVICE_TABLE(i2c, drv2604_vibrator_device_id);
static struct of_device_id drv2604_vibrator_table[] = {

        { .compatible = "drv2604_vibrator,vibrator",},
        { },
};


static struct i2c_driver drv2604_vibrator_i2c_driver = {
        .driver = {
                .name = "drv2604_vibrator",
                .owner = THIS_MODULE,
                .of_match_table = drv2604_vibrator_table,
        },
        .probe     = drv2604_vibrator_i2c_probe,
        .id_table  = drv2604_vibrator_device_id,
        .suspend = drv2604_vibrator_suspend,
        .resume = drv2604_vibrator_resume,
        .remove = __devexit_p(drv2604_remove),
};

static int __init drv2604_vibrator_init(void)
{
        return(i2c_add_driver(&drv2604_vibrator_i2c_driver));
}

static void __exit drv2604_vibrator_exit(void)
{
        i2c_del_driver(&drv2604_vibrator_i2c_driver);
}

module_init(drv2604_vibrator_init);
module_exit(drv2604_vibrator_exit);

MODULE_AUTHOR("Immersion Corporation");
MODULE_DESCRIPTION("TouchSense Kernel Module");
MODULE_LICENSE("GPL v2");

