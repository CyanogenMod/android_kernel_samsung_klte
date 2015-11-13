/*
** =============================================================================
**
** File:Immvibespi_drv2604.c
**
** Description:
**     Device-dependent functions called by Immersion TSP API
**     to control PWM duty cycle, amp enable/disable, save IVT file, etc...
**
**
** Copyright (c) 2012-2013 Immersion Corporation. All Rights Reserved.
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
**
** =============================================================================
*/
//#warning ********* Compiling SPI for DRV2604 using LRA actuator ************

#ifdef IMMVIBESPIAPI
#undef IMMVIBESPIAPI
#endif
#define IMMVIBESPIAPI static

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/slab.h>
#include <linux/types.h>

#include <linux/fs.h>
#include <linux/cdev.h>

#include <linux/i2c.h>
#include <linux/semaphore.h>
#include <linux/device.h>

#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

#include <linux/gpio.h>
#include <mach/gpiomux.h>


#include <linux/workqueue.h>
//#include "tspdrv.h"
#include "tspdrv_drv2604.h"

#ifdef CONFIG_REG_DRV2604L
struct dentry *drv_debugfs_dir;
#endif

static int g_nDeviceID = -1;
static bool g_bAmpEnabled = false;

static const unsigned char init_sequence[] = {
#include "init.seq"
};

#if SKIP_AUTOCAL == 0
static const unsigned char autocal_sequence[] = {
#include <autocal.seq>
};
#endif

#ifndef ACTUATOR_NAME
#define ACTUATOR_NAME "haptic_motor"
#endif

static void drv2604_write_reg_val(const unsigned char* data, unsigned int size)
{

    int i = 0,ret;
    if (size % 2 != 0)
        return;

    while (i < size)
    {
        ret = i2c_smbus_write_byte_data(vibrator_drvdata.client, data[i], data[i+1]);
        i+=2;
    }
}

static unsigned char drv2604_read_reg(unsigned char reg)
{
    return i2c_smbus_read_byte_data(vibrator_drvdata.client, reg);
}

#if SKIP_AUTOCAL == 0
static void drv2604_poll_go_bit(void)
{
    while (drv2604_read_reg(GO_REG) == GO)
      schedule_timeout_interruptible(msecs_to_jiffies(GO_BIT_POLL_INTERVAL));
}
#endif

static void drv2604_set_rtp_val(char value)
{
    char rtp_val[] =
    {
        REAL_TIME_PLAYBACK_REG, value
    };
    drv2604_write_reg_val(rtp_val, sizeof(rtp_val));
}

static void drv2604_change_mode(char mode)
{
    unsigned char tmp[] =
    {
        MODE_REG, mode
    };
    drv2604_write_reg_val(tmp, sizeof(tmp));
}

#if USE_DRV2604_EN_PIN
static void drv2604_set_en(bool enabled)
{
    gpio_direction_output(vibrator_drvdata.motor_en, enabled ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW);

    if(enabled == true)
	gpio_set_value(vibrator_drvdata.motor_en,VIBRATION_ON);
    else
	gpio_set_value(vibrator_drvdata.motor_en,VIBRATION_OFF);
}
#endif

#ifdef CONFIG_REG_DRV2604L
static int drv_debug_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

static ssize_t drv_debug_read(struct file *filp,
	char __user *buffer, size_t count, loff_t *ppos)
{
	char *buf;
	size_t len = 0;
	ssize_t ret;
	int i;

	if (*ppos != 0)
		return 0;

	if (count < sizeof(buf))
		return -ENOSPC;

	buf = kzalloc(TSPDRV_BUF_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	for(i = 0x00; i <= 0xFF; i += 0x01){
		if(( 0x00 <= i && i <= 0x10) || (0x16 <= i && i <= 0x22) || (0xFD <= i && i<=0xFF)){
			len += snprintf(buf + len, TSPDRV_BUF_SIZE - len,
			"drv2604 reg addr = %x , value =%x\n", i, drv2604_read_reg(i));
		}
	}
	ret = simple_read_from_buffer(buffer, len, ppos, buf, TSPDRV_BUF_SIZE);
	kfree(buf);

	return ret;
}

static const struct file_operations drv_debugfs_fops = {
	.owner = THIS_MODULE,
	.open =  drv_debug_open,
	.read = drv_debug_read,
};
#endif

static int32_t ImmVibeSPI_ForceOut_AmpDisable(u_int8_t nActuatorIndex);

#if GUARANTEE_AUTOTUNE_BRAKE_TIME

#define AUTOTUNE_BRAKE_TIME 25

static VibeInt8 g_lastForce = 0;
static bool g_brake = false;

static void autotune_brake_complete(struct work_struct *work)
{
    /* new nForce value came in before workqueue terminated */
    if (g_lastForce > 0)
        return;

#if USE_DRV2604_STANDBY
    /* Put hardware in standby */
    drv2604_change_mode(MODE_STANDBY);
#endif

#if USE_DRV2604_EN_PIN
    drv2604_set_en(false);
#endif
}

DECLARE_DELAYED_WORK(g_brake_complete, autotune_brake_complete);

static struct workqueue_struct *g_workqueue;

#endif

/*
** Called to disable amp (disable output force)
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_AmpDisable(VibeUInt8 nActuatorIndex)
{
    if (g_bAmpEnabled)
    {
        /* Set the force to 0 */
        drv2604_set_rtp_val(0);

#if GUARANTEE_AUTOTUNE_BRAKE_TIME
        /* if a brake signal arrived from daemon, let the chip stay on
         * extra time to allow it to brake */
        if (g_brake && g_workqueue)
        {
            queue_delayed_work(g_workqueue,
                               &g_brake_complete,
                               msecs_to_jiffies(AUTOTUNE_BRAKE_TIME));
        }
        else /* disable immediately (smooth effect style) */
#endif
        {
#if USE_DRV2604_STANDBY
            /* Put hardware in standby via i2c */
            drv2604_change_mode(MODE_STANDBY);
#endif

#if USE_DRV2604_EN_PIN
            /* Disable hardware via pin */
            drv2604_set_en(false);
#endif
        }

        g_bAmpEnabled = false;
    }
    return VIBE_S_SUCCESS;
}

/*
** Called to enable amp (enable output force)
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_AmpEnable(VibeUInt8 nActuatorIndex)
{
    if (!g_bAmpEnabled)
    {
#if GUARANTEE_AUTOTUNE_BRAKE_TIME
        cancel_delayed_work_sync(&g_brake_complete);
#endif

#if USE_DRV2604_EN_PIN
        drv2604_set_en(true);
#endif

#if USE_DRV2604_STANDBY
        drv2604_change_mode(MODE_DEVICE_READY);
#endif
        // Chip requires minimum 250us power-up delay before RTP value can be set
        // If the chip is powered on <10ms after powering off, it needs 1000us
        // for the internal LDO voltage to stabilize
        usleep_range(1000, 1000);

        /* Workaround for power issue in the DRV2604 */
        /* Restore the register settings if they have reset to the defaults */

        if(drv2604_read_reg(RATED_VOLTAGE_REG) != init_sequence[3])
        {
            drv2604_write_reg_val(init_sequence, sizeof(init_sequence));
        }

        drv2604_change_mode(MODE_REAL_TIME_PLAYBACK);
        g_bAmpEnabled = true;
    }
    return VIBE_S_SUCCESS;
}

/*
** Called at initialization time.
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_Initialize(void)
{

	int retVal=0;
	if (retVal) {
	    return VIBE_E_FAIL;
	}

#if GUARANTEE_AUTOTUNE_BRAKE_TIME
    g_workqueue = create_workqueue("tspdrv_workqueue");
#endif

    return VIBE_S_SUCCESS;
}

/*
** Called at termination time to disable amp, etc...
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_Terminate(void)
{

#if GUARANTEE_AUTOTUNE_BRAKE_TIME
    if (g_workqueue)
    {
        destroy_workqueue(g_workqueue);
        g_workqueue = 0;
    }
#endif

    ImmVibeSPI_ForceOut_AmpDisable(0);
    return VIBE_S_SUCCESS;
}

/*
** Called by the real-time loop to set the force
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_SetSamples(VibeUInt8 nActuatorIndex, VibeUInt16 nOutputSignalBitDepth, VibeUInt16 nBufferSizeInBytes, VibeInt8* pForceOutputBuffer)
{

#if GUARANTEE_AUTOTUNE_BRAKE_TIME
    VibeInt8 force = pForceOutputBuffer[0];
    if (force > 0 && g_lastForce <= 0)
    {
        g_brake = false;

        ImmVibeSPI_ForceOut_AmpEnable(nActuatorIndex);
    }
    else if (force <= 0 && g_lastForce > 0)
    {
        g_brake = force < 0;

        ImmVibeSPI_ForceOut_AmpDisable(nActuatorIndex);
    }

    if (g_lastForce != force)
    {
        /* AmpDisable sets force to zero, so need to here */
        if (force > 0)
            drv2604_set_rtp_val(pForceOutputBuffer[0]);

        g_lastForce = force;
    }
#else
    drv2604_set_rtp_val(pForceOutputBuffer[0]);
#endif

    return VIBE_S_SUCCESS;
}

/*
** Called to set force output frequency parameters
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_SetFrequency(VibeUInt8 nActuatorIndex, VibeUInt16 nFrequencyParameterID, VibeUInt32 nFrequencyParameterValue)
{
    if (nActuatorIndex != 0) return VIBE_S_SUCCESS;

    switch (nFrequencyParameterID)
    {
        case VIBE_KP_CFG_FREQUENCY_PARAM1:
            break;

        case VIBE_KP_CFG_FREQUENCY_PARAM2:
            break;

        case VIBE_KP_CFG_FREQUENCY_PARAM3:
            break;

        case VIBE_KP_CFG_FREQUENCY_PARAM4:
            break;

        case VIBE_KP_CFG_FREQUENCY_PARAM5:
            break;

        case VIBE_KP_CFG_FREQUENCY_PARAM6:
            break;
    }
    return VIBE_S_SUCCESS;
}

/*
** Called to get the device name (device name must be returned as ANSI char)
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_Device_GetName(VibeUInt8 nActuatorIndex, char *szDevName, int nSize)
{
    char szRevision[MAX_REVISION_STRING_SIZE];

    if ((!szDevName) || (nSize < 1)) return VIBE_E_FAIL;

    switch (g_nDeviceID)
    {
        case DRV2605:
            strncpy(szDevName, "DRV2605", nSize-1);
            break;
        case DRV2604:
            strncpy(szDevName, "DRV2604", nSize-1);
	 case DRV2604L:
            strncpy(szDevName, "DRV2604L", nSize-1);
            break;
	 case DRV2605L:
            strncpy(szDevName, "DRV2605L", nSize-1);
        default:
            strncpy(szDevName, "Unknown", nSize-1);
            break;
    }

    /* Append revision number to the device name */
    sprintf(szRevision, "r%d %s", (drv2604_read_reg(SILICON_REVISION_REG) & SILICON_REVISION_MASK), ACTUATOR_NAME);
    if ((strlen(szRevision) + strlen(szDevName)) < nSize-1)
        strcat(szDevName, szRevision);

    szDevName[nSize - 1] = '\0'; /* make sure the string is NULL terminated */

    return VIBE_S_SUCCESS;
}






