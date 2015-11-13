/* drivers/motor/isa1400_vibrator.c
 *
 * Copyright (C) 2011 Samsung Electronics Co. Ltd. All Rights Reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/hrtimer.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/wakelock.h>
#include <linux/mutex.h>
#include <linux/pwm.h>
#include <linux/workqueue.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include "../staging/android/timed_output.h"
#include <linux/isa1400_vibrator.h>
#include <linux/fs.h>
#include "tspdrv.h"
#include <asm/uaccess.h>
#include <linux/miscdevice.h>

#define MOTOR_DEBUG	0

#ifdef CONFIG_MOTOR_DRV_ISA1400
#include "ImmVibeSPI_isa1400.c"
#endif
#define VERSION_STR " v3.4.55.7\n"
/* account extra space for future extra digits in version number */
#define VERSION_STR_LEN 16

static char g_szdevice_name[(VIBE_MAX_DEVICE_NAME_LENGTH
							+ VERSION_STR_LEN)
							* NUM_ACTUATORS];
static size_t g_cchdevice_name;

static struct wake_lock vib_wake_lock;

/* Flag indicating whether the driver is in use */
static char g_bisplaying;

/* Buffer to store data sent to SPI */
#define SPI_BUFFER_SIZE \
		(NUM_ACTUATORS * (VIBE_OUTPUT_SAMPLE_SIZE + SPI_HEADER_SIZE))
static int g_bstoprequested;
static actuator_samples_buffer g_samples_buffer[NUM_ACTUATORS] = {{0} };
static char g_cwrite_buffer[SPI_BUFFER_SIZE];
/* For QA purposes */
#ifdef QA_TEST
#define FORCE_LOG_BUFFER_SIZE   128
#define TIME_INCREMENT          5
static int g_ntime;
static int g_nforcelog_index;
static int8_t g_nforcelog[FORCE_LOG_BUFFER_SIZE];
#endif

#ifdef IMPLEMENT_AS_CHAR_DRIVER
static int g_nmajor;
#endif

/* Needs to be included after the global variables because it uses them */
#ifdef CONFIG_HIGH_RES_TIMERS
    #include "VibeOSKernelLinuxHRTime.c"
#else
    #include "VibeOSKernelLinuxTime.c"
#endif

struct isa1400_vibrator_drvdata {
	struct timed_output_dev dev;
	struct hrtimer timer;
	struct work_struct work;
	struct pwm_device	*pwm;
	struct i2c_client *client;
	struct isa1400_vibrator_platform_data *pdata;
	struct mutex		mutex_lock;
	bool running;
	bool power_en;
	int timeout;
};

static int isa1400_vibrator_i2c_write(struct i2c_client *client,
					u8 addr, u8 val)
{
	int error = 0;
	error = i2c_smbus_write_byte_data(client, addr, val);
	if (error)
		printk(KERN_ERR "[VIB] Failed to write addr=[0x%x], val=[0x%x]\n",
				addr, val);

#if MOTOR_DEBUG
	printk(KERN_DEBUG "[VIB] %s : 0x%x, 0x%x\n",
		__func__, addr, val);
#endif

	return error;
}

static void isa1400_reg_write(struct isa1400_vibrator_drvdata *data,
	u8 type)
{
	int i = 0, j = 0;

	for (i  = 0; i < ISA1400_REG_MAX; i++) {
		if (data->pdata->reg_data[i][0] == type){
			for (j = 2; j < data->pdata->reg_data[i][1]; j += 2){
				/*printk("[VIB] inside loop %d %d %d\n", j,
					data->pdata->reg_data[i][j],
					data->pdata->reg_data[i][j + 1]);*/
				isa1400_vibrator_i2c_write(data->client,
					data->pdata->reg_data[i][j],
					data->pdata->reg_data[i][j + 1]);

			}
		}
	}
}

static void isa1400_vibrator_hw_init(struct isa1400_vibrator_drvdata *data)
{
	data->pdata->gpio_en(true);
	data->pdata->clk_en(true);
	isa1400_reg_write(data, ISA1400_REG_INIT);
}

int vib_ioctl_lock = 0;
EXPORT_SYMBOL(vib_ioctl_lock);
static void isa1400_vibrator_on(struct isa1400_vibrator_drvdata *data)
{
	isa1400_vibrator_hw_init(data);
	isa1400_reg_write(data, ISA1400_REG_START);
}

static void isa1400_vibrator_off(struct isa1400_vibrator_drvdata *data)
{
#if 0
	isa1400_reg_write(data, ISA1400_REG_STOP);
#endif
	if(vib_ioctl_lock)
		return;

	isa1400_reg_write(data, ISA1400_REG_STOP);
	data->pdata->clk_en(false);
	data->pdata->gpio_en(false);
}


static struct isa1400_vibrator_drvdata	*g_drvdata;
int isa1400_i2c_write(u8 addr, int length, u8 *data)
{
	if (NULL == g_drvdata) {
		printk(KERN_ERR "[VIB] driver is not ready\n");
		return -EFAULT;
	}

	if (2 != length)
		printk(KERN_ERR "[VIB] length should be 2(len:%d)\n",
			length);

#if MOTOR_DEBUG
	printk(KERN_DEBUG "[VIB] data : %x, %x\n",
		data[0], data[1]);
#endif

	return isa1400_vibrator_i2c_write(g_drvdata->client,
		data[0], data[1]);
}

void isa1400_clk_config(u8 index, int duty)
{
	if (NULL == g_drvdata) {
		printk(KERN_ERR "[VIB] driver is not ready\n");
		return ;
	}

#if MOTOR_DEBUG
	printk(KERN_DEBUG "[VIB] %s %d, %d\n", __func__, index, duty);
#endif

	if (index >= g_drvdata->pdata->actuactor_num) {
		printk(KERN_ERR "[VIB] index is wrong : %d\n", index);
		return ;
	}

	duty = (duty > 0) ? duty : (abs(duty) |0x80);

	isa1400_vibrator_i2c_write(g_drvdata->client,
		ISA1400_REG_GAIN + g_drvdata->pdata->actuator[index],
		duty);
	isa1400_vibrator_i2c_write(g_drvdata->client,
		ISA1400_REG_HPTEN,
		(0x01 << g_drvdata->pdata->actuator[index]));
}

void isa1400_chip_enable(bool en)
{
	if (NULL == g_drvdata) {
		printk(KERN_ERR "[VIB] driver is not ready\n");
		return ;
	}

	if (en) {
		if (g_drvdata->power_en)
			return ;
		g_drvdata->power_en = true;
		isa1400_vibrator_hw_init(g_drvdata);
	} else {
		if (!g_drvdata->power_en)
			return ;
		g_drvdata->power_en = false;
		isa1400_vibrator_off(g_drvdata);
	}
}

static enum hrtimer_restart isa1400_vibrator_timer_func(struct hrtimer *_timer)
{
	struct isa1400_vibrator_drvdata *data =
		container_of(_timer, struct isa1400_vibrator_drvdata, timer);

	data->timeout = 0;

	schedule_work(&data->work);
	return HRTIMER_NORESTART;
}

static void isa1400_vibrator_work(struct work_struct *_work)
{
	struct isa1400_vibrator_drvdata *data =
		container_of(_work, struct isa1400_vibrator_drvdata, work);
	if (0 == data->timeout) {
		if (!data->running)
			return ;

		data->running = false;
		isa1400_vibrator_off(data);
	} else {
		if (data->running)
			return ;

		data->running = true;
		isa1400_vibrator_on(data);
	}
}

static int isa1400_vibrator_get_time(struct timed_output_dev *_dev)
{
	struct isa1400_vibrator_drvdata	*data =
		container_of(_dev, struct isa1400_vibrator_drvdata, dev);

	if (hrtimer_active(&data->timer)) {
		ktime_t r = hrtimer_get_remaining(&data->timer);
		struct timeval t = ktime_to_timeval(r);
		return t.tv_sec * 1000 + t.tv_usec / 1000;
	} else
		return 0;
}

static void isa1400_vibrator_enable(struct timed_output_dev *_dev, int value)
{
	struct isa1400_vibrator_drvdata	*data =
		container_of(_dev, struct isa1400_vibrator_drvdata, dev);

	printk(KERN_DEBUG "[VIB] time = %dms\n", value);
	mutex_lock(&data->mutex_lock);
	cancel_work_sync(&data->work);
	hrtimer_cancel(&data->timer);
	data->timeout = value;
	if (value > 0) {
		if (value > data->pdata->max_timeout)
			value = data->pdata->max_timeout;

		hrtimer_start(&data->timer,
			ns_to_ktime((u64)value * NSEC_PER_MSEC),
			HRTIMER_MODE_REL);
	}
	mutex_unlock(&data->mutex_lock);
	schedule_work(&data->work);
}

/* File IO */
static int open(struct inode *inode, struct file *file);
static int release(struct inode *inode, struct file *file);
static ssize_t read(struct file *file, char *buf, size_t count, loff_t *ppos);
static ssize_t write(struct file *file, const char *buf, size_t count,
					 loff_t *ppos);
#if HAVE_UNLOCKED_IOCTL
static long ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
#endif
static const struct file_operations fops = {
	.owner =    THIS_MODULE,
	.read =     read,
	.write =    write,
	.unlocked_ioctl =    ioctl,
	.open =     open,
	.release =  release ,
	.llseek =   default_llseek
};

#ifndef IMPLEMENT_AS_CHAR_DRIVER
static struct miscdevice miscdev = {
	.minor =    MISC_DYNAMIC_MINOR,
	.name =     MODULE_NAME,
	.fops =     &fops
};
#endif

static int open(struct inode *inode, struct file *file)
{
	/*DbgOut((KERN_INFO "tspdrv: open.\n"));*/

	if (!try_module_get(THIS_MODULE))
		return -ENODEV;

	return 0;
}

static int release(struct inode *inode, struct file *file)
{
	DbgOut((KERN_INFO "tspdrv: release.\n"));

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
	file->private_data = (void *)NULL;

	module_put(THIS_MODULE);

	return 0;
}

static ssize_t read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
	const size_t nbufsize =
			(g_cchdevice_name > (size_t)(*ppos)) ?
			min(count, g_cchdevice_name - (size_t)(*ppos)) : 0;
	/*DbgOut((KERN_INFO "tspdrv: read function called\n"));*/
	/* End of buffer, exit */
	if (0 == nbufsize)
		return 0;

	if (0 != copy_to_user(buf, g_szdevice_name + (*ppos), nbufsize)) {
		/* Failed to copy all the data, exit */
		DbgOut((KERN_ERR "tspdrv: copy_to_user failed.\n"));
		return 0;
	}

	/* Update file position and return copied buffer size */
	*ppos += nbufsize;
	return nbufsize;
}

static ssize_t write(struct file *file, const char *buf, size_t count,
					 loff_t *ppos)
{
	int i = 0;

	*ppos = 0;  /* file position not used, always set to 0 */
	/*DbgOut((KERN_ERR "tspdrv: write....\n")); */

	/*
	** Prevent unauthorized caller to write data.
	** TouchSense service is the only valid caller.
	*/
	if (file->private_data != (void *)TSPDRV_MAGIC_NUMBER) {
		DbgOut((KERN_ERR "tspdrv: unauthorized write.\n"));
		return 0;
	}

	/* Check buffer size */
	if ((count <= SPI_HEADER_SIZE) || (count > SPI_BUFFER_SIZE)) {
		DbgOut((KERN_ERR "tspdrv: invalid write buffer size.\n"));
		return 0;
	}

	/* Copy immediately the input buffer */
	if (0 != copy_from_user(g_cwrite_buffer, buf, count)) {
		/* Failed to copy all the data, exit */
		DbgOut((KERN_ERR "tspdrv: copy_from_user failed.\n"));
		return 0;
	}

	while (i < count) {
		int nindex_free_buffer;   /* initialized below */

		samples_buffer *pinput_buffer =
			(samples_buffer *)(&g_cwrite_buffer[i]);

		if ((i + SPI_HEADER_SIZE) >= count) {
			/*
			** Index is about to go beyond the buffer size.
			** (Should never happen).
			*/
			DbgOut((KERN_EMERG "tspdrv: invalid buffer index.\n"));
			return 0;
		}

		/* Check bit depth */
		if (8 != pinput_buffer->nbit_depth)
			DbgOut((KERN_WARNING
			"tspdrv: invalid bit depth.Use default value(8).\n"));

		/* The above code not valid if SPI header size is not 3 */
#if (SPI_HEADER_SIZE != 3)
#error "SPI_HEADER_SIZE expected to be 3"
#endif

		/* Check buffer size */
		if ((i + SPI_HEADER_SIZE + pinput_buffer->nbuffer_size)
			> count) {
			/*
			** Index is about to go beyond the buffer size.
			** (Should never happen).
			*/
			DbgOut((KERN_EMERG "tspdrv: invalid data size.\n"));
			return 0;
		}

		/* Check actuator index */
		if (NUM_ACTUATORS <= pinput_buffer->nactuator_index) {
			DbgOut((KERN_ERR "tspdrv: invalid actuator index.\n"));
			i += (SPI_HEADER_SIZE + pinput_buffer->nbuffer_size);
			continue;
		}

		if (0 == g_samples_buffer[pinput_buffer->nactuator_index]
			.actuator_samples[0].nbuffer_size) {
			nindex_free_buffer = 0;
		} else if (0 == g_samples_buffer[pinput_buffer->nactuator_index]
			.actuator_samples[1].nbuffer_size) {
			nindex_free_buffer = 1;
		} else {
			/* No room to store new samples  */
			DbgOut((KERN_ERR
			 "tspdrv: no room to store new samples.\n"));
			return 0;
		}

		/* Store the data in the free buffer of the given actuator */
		memcpy(
			   &(g_samples_buffer[pinput_buffer->nactuator_index]
			   .actuator_samples[nindex_free_buffer]),
			   &g_cwrite_buffer[i],
			   (SPI_HEADER_SIZE + pinput_buffer->nbuffer_size));

		/*  If the no buffer is playing, prepare to play
		 ** g_samples_buffer[pinput_buffer->nactuator_index].
		 ** actuator_samples[nindex_free_buffer]
		 */
		if (-1 == g_samples_buffer[pinput_buffer->nactuator_index]
			.nindex_playing_buffer) {
			g_samples_buffer[pinput_buffer->nactuator_index]
				.nindex_playing_buffer = nindex_free_buffer;
			g_samples_buffer[pinput_buffer->nactuator_index]
				.nindex_output_value = 0;
		}

		/* Increment buffer index */
		i += (SPI_HEADER_SIZE + pinput_buffer->nbuffer_size);
	}

#ifdef QA_TEST
	g_nforcelog[g_nforcelog_index++] = g_cSPIBuffer[0];
	if (g_nforcelog_index >= FORCE_LOG_BUFFER_SIZE) {
		for (i = 0; i < FORCE_LOG_BUFFER_SIZE; i++) {
			printk(KERN_INFO "%d\t%d\n", g_ntime, g_nforcelog[i]);
			g_ntime += TIME_INCREMENT;
		}
		g_nforcelog_index = 0;
	}
#endif

	/* Start the timer after receiving new output force */
	g_bisplaying = true;
	VibeOSKernelLinuxStartTimer();

	return count;
}
static long ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
#ifdef QA_TEST
	int i;
#endif

	 /*DbgOut(KERN_INFO "tspdrv: ioctl cmd[0x%x].\n", cmd); */
	switch (cmd) {
	case TSPDRV_STOP_KERNEL_TIMER:
		/*
		** As we send one sample ahead of time, we need to finish
		** playing the last sample before stopping the timer.
		** So we just set a flag here.
		*/
		if (g_bisplaying)
			g_bstoprequested = true;

#ifdef VIBEOSKERNELPROCESSDATA
		/* Last data processing to disable amp and stop timer */
		VibeOSKernelProcessData(NULL);
#endif

#ifdef QA_TEST
		if (g_nforcelog_index) {
			for (i = 0; i < g_nforcelog_index; i++) {
				printk(KERN_INFO "%d\t%d\n"
					   , g_ntime, g_nforcelog[i]);
				g_ntime += TIME_INCREMENT;
			}
		}
		g_ntime = 0;
		g_nforcelog_index = 0;
#endif
		break;

	case TSPDRV_MAGIC_NUMBER:
		filp->private_data = (void *)TSPDRV_MAGIC_NUMBER;
		break;

	case TSPDRV_ENABLE_AMP:
		wake_lock(&vib_wake_lock);
		ImmVibeSPI_ForceOut_AmpEnable(arg);
		DbgRecorderReset((arg));
		DbgRecord((arg, ";------- TSPDRV_ENABLE_AMP ---------\n"));
		break;

	case TSPDRV_DISABLE_AMP:
		/*
		** Small fix for now to handle proper combination of
		** TSPDRV_STOP_KERNEL_TIMER and TSPDRV_DISABLE_AMP together
		** If a stop was requested, ignore the request as the amp
		** will be disabled by the timer proc when it's ready
		*/
		if (!g_bstoprequested)
			ImmVibeSPI_ForceOut_AmpDisable(arg);
		wake_unlock(&vib_wake_lock);
		break;

	case TSPDRV_GET_NUM_ACTUATORS:
		return NUM_ACTUATORS;
	}

	return 0;
}
static int __devinit isa1400_vibrator_i2c_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct isa1400_vibrator_platform_data *pdata =
		client->dev.platform_data;
	struct isa1400_vibrator_drvdata *ddata;
	int ret = 0;
	int i;

	ddata = kzalloc(sizeof(struct isa1400_vibrator_drvdata), GFP_KERNEL);
	if (NULL == ddata) {
		printk(KERN_ERR "[VIB] Failed to alloc memory.\n");
		ret = -ENOMEM;
		goto err_free_mem;
	}

	ddata->client = client;
	if (NULL == pdata) {
		printk(KERN_ERR "[VIB] the platform data is empty.\n");
		goto err_platform_data;
	} else
		ddata->pdata = pdata;

 #ifdef IMPLEMENT_AS_CHAR_DRIVER
	g_nmajor = register_chrdev(0, MODULE_NAME, &fops);
	if (g_nmajor < 0) {
		DbgOut((KERN_ERR "tspdrv: can't get major number.\n"));
		ret = g_nmajor;
		goto err_platform_data;
	}
#else
	ret = misc_register(&miscdev);
	if (ret) {
		DbgOut((KERN_ERR "tspdrv: misc_register failed.\n"));
		goto err_platform_data;
	}
#endif
	ddata->dev.name = "vibrator";
	ddata->dev.get_time = isa1400_vibrator_get_time;
	ddata->dev.enable = isa1400_vibrator_enable;

	hrtimer_init(&ddata->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	ddata->timer.function = isa1400_vibrator_timer_func;
	INIT_WORK(&ddata->work, isa1400_vibrator_work);
	mutex_init(&ddata->mutex_lock);

	i2c_set_clientdata(client, ddata);
	/*ddata->pdata->gpio_en(true);
	isa1400_vibrator_hw_init(ddata);*/
	VibeOSKernelLinuxInitTimer();
	/* Get and concatenate device name and initialize data buffer */
	g_cchdevice_name = 0;
	for (i = 0; i < NUM_ACTUATORS; i++) {
		char *szName = g_szdevice_name + g_cchdevice_name;
		ImmVibeSPI_Device_GetName(i,
				szName, VIBE_MAX_DEVICE_NAME_LENGTH);

		/* Append version information and get buffer length */
		strlcat(szName, VERSION_STR, sizeof(VERSION_STR));
		g_cchdevice_name += strnlen(szName, sizeof(szName));

		g_samples_buffer[i].nindex_playing_buffer = -1;/* Not playing */
		g_samples_buffer[i].actuator_samples[0].nbuffer_size = 0;
		g_samples_buffer[i].actuator_samples[1].nbuffer_size = 0;
	}
	wake_lock_init(&vib_wake_lock, WAKE_LOCK_SUSPEND, "vib_present");
	ret = timed_output_dev_register(&ddata->dev);
	if (ret < 0) {
		printk(KERN_ERR "[VIB] Failed to register timed_output : -%d\n", ret);
		goto err_to_dev_reg;
	}
	g_drvdata = ddata;
	return 0;

err_to_dev_reg:
err_platform_data:
	kfree(ddata);
err_free_mem:
	return ret;

}

static int isa1400_vibrator_suspend(struct i2c_client *client, pm_message_t mesg)
{
	struct isa1400_vibrator_drvdata *ddata  = i2c_get_clientdata(client);
	printk(KERN_INFO "[VIB] isa1400_vibrator_suspend called ");

	if(vib_ioctl_lock){
		vib_ioctl_lock = 0;
		ddata->pdata->gpio_en(false);
		ddata->pdata->clk_en(false);
	}

	return 0;
}

static int isa1400_vibrator_resume(struct i2c_client *client)
{
	return 0;
}

static const struct i2c_device_id isa1400_vibrator_device_id[] = {
	{"isa1400_vibrator", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, isa1400_vibrator_device_id);

static struct i2c_driver isa1400_vibrator_i2c_driver = {
	.driver = {
		.name = "isa1400_vibrator",
		.owner = THIS_MODULE,
	},
	.probe     = isa1400_vibrator_i2c_probe,
	.id_table  = isa1400_vibrator_device_id,
	.suspend	= isa1400_vibrator_suspend,
	.resume	= isa1400_vibrator_resume,
};

static int __init isa1400_vibrator_init(void)
{
	printk("[VIB] init called for 1400\n");
	return i2c_add_driver(&isa1400_vibrator_i2c_driver);
}

static void __exit isa1400_vibrator_exit(void)
{
	VibeOSKernelLinuxTerminateTimer();
	wake_lock_destroy(&vib_wake_lock);
       mutex_destroy(&g_drvdata->mutex_lock);
       timed_output_dev_unregister(&g_drvdata->dev);
	i2c_del_driver(&isa1400_vibrator_i2c_driver);
}

module_init(isa1400_vibrator_init);
module_exit(isa1400_vibrator_exit);

MODULE_AUTHOR("Junki Min <Junki671.min@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("haptic driver for the isa1400 ic");

