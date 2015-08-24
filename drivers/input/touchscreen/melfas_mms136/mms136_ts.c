
#define DEBUG
#define SEC_TSP_DEBUG

#define SEC_TSP_FACTORY_TEST
#define SEC_TSP_FW_UPDATE
#define TSP_BUF_SIZE 1024
#define FAIL -1

#include <linux/module.h>
#include <linux/firmware.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/earlysuspend.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/platform_data/mms_ts.h>
#include <linux/completion.h>
#include <linux/init.h>
#include <asm/uaccess.h>

#include <linux/mutex.h>
#include <mach/gpio.h>
#include <linux/cpufreq.h>
#include <asm/unaligned.h>

#include <linux/regulator/consumer.h>
#include <linux/of_gpio.h>

#include "mms100_cfg_update.h"
#include "mms100_isp.h"

/* Melfas TSP test mode */
#include "mms_ts_test.h"

#define SEC_TSP_FACTORY_TEST

/* Flag to enable touch key */
#define MMS_HAS_TOUCH_KEY		1

#define ESD_DETECT_COUNT		10

#define MAX_SECTION_NUM			3
#define MAX_FINGER_NUM			10
#define MAX_WIDTH			30
#define MAX_PRESSURE			255
#define MAX_LOG_LENGTH			128

#define FINGER_EVENT_SZ			6

/* Registers */
#define MMS_MODE_CONTROL		0x01
#define MMS_TX_NUM			0x0B
#define MMS_RX_NUM			0x0C
#define MMS_KEY_NUM			0x0D

#define MMS_EVENT_PKT_SZ		0x0F
#define MMS_INPUT_EVENT			0x10

#define MMS_UNIVERSAL_CMD		0xA0
#define MMS_UNIVERSAL_RESULT_LENGTH	0xAE
#define MMS_UNIVERSAL_RESULT		0xAF
//#define MMS_FW_VERSION			0xE1

/* Universal commands */
#define MMS_CMD_SET_LOG_MODE		0x20

/* Event types */
#define MMS_LOG_EVENT			0xD
#define MMS_NOTIFY_EVENT		0xE
#define MMS_ERROR_EVENT			0xF
#define MMS_TOUCH_KEY_EVENT		0x40

#define MMS_COORDS_ARR_SIZE	4

#define MMS_I2C_VTG_MIN_UV	1800000
#define MMS_I2C_VTG_MAX_UV	1800000
#define MMS_I2C_LOAD_UA	10000


struct device *sec_touchscreen;

int touch_is_pressed;

#define MAX_FINGERS		10
#define MAX_WIDTH		30
#define MAX_PRESSURE		255
#define MAX_ANGLE		90
#define MIN_ANGLE		-90

#define MMS_CORE_VERSION	0xE1
#define MMS_TSP_REVISION	0xF0
#define MMS_HW_REVISION		0xF1
#define MMS_COMPAT_GROUP	0xF2
#define MMS_FW_VERSION		0xE1 //0xF4
#define MMS_MODULE_REVISION 0xC2

enum {
	ISP_MODE_FLASH_ERASE = 0x59F3,
	ISP_MODE_FLASH_WRITE = 0x62CD,
	ISP_MODE_FLASH_READ = 0x6AC9,
};

/* each address addresses 4-byte words */
#define ISP_MAX_FW_SIZE		(0x1F00 * 4)
#define ISP_IC_INFO_ADDR	0x1F00
#define ISP_CAL_DATA_SIZE	256



#ifdef SEC_TSP_FACTORY_TEST
#define TX_NUM		21 //25
#define RX_NUM		14 //18
#define NODE_NUM	294 //450	/* 25x18 */

/* self diagnostic */
#define ADDR_CH_NUM		0x0B
#define ADDR_UNIV_CMD	0xA0
#define CMD_ENTER_TEST	0x40
#define CMD_EXIT_TEST	0x4F
#define CMD_CM_DELTA	0x41
#define CMD_GET_DELTA	0x42
#define CMD_CM_ABS		0X43
#define CMD_GET_ABS		0X44
#define CMD_CM_JITTER	0X45
#define CMD_GET_JITTER	0X46
#define CMD_GET_INTEN	0x70
#define CMD_RESULT_SZ	0XAE
#define CMD_RESULT		0XAF

/* VSC(Vender Specific Command)  */
#define MMS_VSC_CMD			0xB0	/* vendor specific command */
#define MMS_VSC_MODE			0x1A	/* mode of vendor */

#define MMS_VSC_CMD_ENTER		0X01
#define MMS_VSC_CMD_CM_DELTA		0X02
#define MMS_VSC_CMD_CM_ABS		0X03
#define MMS_VSC_CMD_EXIT		0X05
#define MMS_VSC_CMD_INTENSITY		0X04
#define MMS_VSC_CMD_RAW			0X06
#define MMS_VSC_CMD_REFER		0X07

#define TSP_CMD_STR_LEN 32
#define TSP_CMD_RESULT_STR_LEN 512
#define TSP_CMD_PARAM_NUM 8
#endif /* SEC_TSP_FACTORY_TEST */

#define FLIP_COVER_TEST 0

#define FW_VERSION 0x05 /*Config Version*/
#define BOOT_VERSION 0x06
#define CORE_VERSION 0x58
#define MODU_VERSION 0x02
#define MAX_FW_PATH 255
#define TSP_FW_FILENAME "melfas.fw"

#define TOUCH_BOOSTER			0

enum{
	SYS_TXNUM = 3,
	SYS_RXNUM,
	SYS_CLEAR,
	SYS_ENABLE,
	SYS_DISABLE,
	SYS_INTERRUPT,
	SYS_RESET,
};

enum {
	GET_RX_NUM = 1,
	GET_TX_NUM,
	GET_EVENT_DATA,
};

enum {
	LOG_TYPE_U08 = 2,
	LOG_TYPE_S08,
	LOG_TYPE_U16,
	LOG_TYPE_S16,
	LOG_TYPE_U32 = 8,
	LOG_TYPE_S32,
};

enum {
	SEC_NONE = -1,
	SEC_BOOTLOADER = 0,
	SEC_CORE,
	SEC_CONFIG,
	SEC_MODULE,
	SEC_LIMIT
};

enum {
	BUILT_IN = 0,
	UMS,
	REQ_FW,
};

struct mms_log_data {
	__u8				*data;
	int				cmd;
};

struct mms_ts_info {
	struct i2c_client 		*client;
	struct input_dev 		*input_dev;
	char 				phys[32];

	int 				max_x;
	int 				max_y;

	u8				tx_num;
	u8				rx_num;
	u8				key_num;

	int 				irq;
	int				data_cmd;
	struct regulator *vcc_i2c;	
	struct mms_ts_platform_data 	*pdata;

	char 				*fw_name;
	//struct completion 		init_done;
	struct early_suspend		early_suspend;
	
#if TOUCH_BOOSTER
		struct delayed_work work_dvfs_off;
		struct delayed_work work_dvfs_chg;
		bool dvfs_lock_status;
		int cpufreq_level;
		struct mutex dvfs_lock;
#endif

	struct mutex 			lock;
	bool				enabled;

	struct class			*class;
	dev_t				mms_dev;
	struct cdev			cdev;

	struct mms_log_data		*log;

#if defined(SEC_TSP_DEBUG)
	unsigned char finger_state[MAX_FINGERS];
#endif

#if defined(SEC_TSP_FW_UPDATE)
	u8 fw_update_state;
#endif

#if 1
	bool ta_status;
	//bool noise_mode;
	//bool sleep_wakeup_ta_check;
	u8 fw_ic_ver;
	//u8 panel;
	u8 fw_core_ver;
	u8 fw_module_ver;
#endif

#if defined(SEC_TSP_FACTORY_TEST)
	struct list_head cmd_list_head;
	u8 cmd_state;
	char cmd[TSP_CMD_STR_LEN];
	int cmd_param[TSP_CMD_PARAM_NUM];
	char cmd_result[TSP_CMD_RESULT_STR_LEN];
	struct mutex cmd_lock;
	bool cmd_is_running;

	unsigned int reference[NODE_NUM];
	unsigned int raw[NODE_NUM]; /* CM_ABS */
	unsigned int inspection[NODE_NUM];/* CM_DELTA */
	unsigned int intensity[NODE_NUM];
	bool ft_flag;
#endif				/* SEC_TSP_FACTORY_TEST */

};

static bool mms_isp_flash = false;
module_param(mms_isp_flash, bool, S_IWUSR | S_IRUGO);
static int esd_cnt;

#define USE_OPEN_CLOSE

#ifdef CONFIG_HAS_EARLYSUSPEND
static void mms_ts_early_suspend(struct early_suspend *h);
static void mms_ts_late_resume(struct early_suspend *h);
#endif


static void mms_reboot(struct mms_ts_info *info);
static void mms_report_input_data(struct mms_ts_info *info, u8 sz, u8 *buf);


extern struct class *sec_class;
//EXPORT_SYMBOL(sec_class);

#if defined(SEC_TSP_FACTORY_TEST)
#define TSP_CMD(name, func) .cmd_name = name, .cmd_func = func

struct tsp_cmd {
	struct list_head	list;
	const char	*cmd_name;
	void	(*cmd_func)(void *device_data);
};

static void fw_update(void *device_data);
static void get_fw_ver_bin(void *device_data);
static void get_fw_ver_ic(void *device_data);
static void get_config_ver(void *device_data);
static void get_threshold(void *device_data);
static void module_off_master(void *device_data);
static void module_on_master(void *device_data);
/*static void module_off_slave(void *device_data);
static void module_on_slave(void *device_data);*/
static void get_chip_vendor(void *device_data);
static void get_chip_name(void *device_data);
static void get_reference(void *device_data);
static void get_cm_abs(void *device_data);
static void get_cm_delta(void *device_data);
static void get_intensity(void *device_data);
static void get_x_num(void *device_data);
static void get_y_num(void *device_data);
static void run_reference_read(void *device_data);
static void run_cm_abs_read(void *device_data);
static void run_cm_delta_read(void *device_data);
static void run_intensity_read(void *device_data);
static void not_support_cmd(void *device_data);
static int get_data(struct mms_ts_info *info, u8 addr, u8 size, u8 *array);


struct tsp_cmd tsp_cmds[] = {
	{TSP_CMD("fw_update", fw_update),},
	{TSP_CMD("get_fw_ver_bin", get_fw_ver_bin),},
	{TSP_CMD("get_fw_ver_ic", get_fw_ver_ic),},
	{TSP_CMD("get_config_ver", get_config_ver),},
	{TSP_CMD("get_threshold", get_threshold),},
	{TSP_CMD("module_off_master", module_off_master),},
	{TSP_CMD("module_on_master", module_on_master),},
	{TSP_CMD("module_off_slave", not_support_cmd),},
	{TSP_CMD("module_on_slave", not_support_cmd),},
	{TSP_CMD("get_chip_vendor", get_chip_vendor),},
	{TSP_CMD("get_chip_name", get_chip_name),},
	{TSP_CMD("get_x_num", get_x_num),},
	{TSP_CMD("get_y_num", get_y_num),},
	{TSP_CMD("get_reference", get_reference),},
	{TSP_CMD("get_cm_abs", get_cm_abs),},
	{TSP_CMD("get_cm_delta", get_cm_delta),},
	{TSP_CMD("get_intensity", get_intensity),},
	{TSP_CMD("run_reference_read", run_reference_read),},
	{TSP_CMD("run_cm_abs_read", run_cm_abs_read),},
	{TSP_CMD("run_cm_delta_read", run_cm_delta_read),},
	{TSP_CMD("run_intensity_read", run_intensity_read),},
#if FLIP_COVER_TEST
	{TSP_CMD("flip_cover_enable", flip_cover_enable),},
#endif	
	{TSP_CMD("not_support_cmd", not_support_cmd),},
};
#endif

#if FLIP_COVER_TEST
static int set_conifg_flip_cover(struct mms_ts_info *info,int enables);
static int note_flip_open(struct mms_ts_info *info);//void);
static int note_flip_close(struct mms_ts_info *info);//(void);
#endif
#define SEC_TSP_INFO_SHOW


/*
 * mms_clear_input_data - all finger point release
 */
static void mms_clear_input_data(struct mms_ts_info *info)
{
	int i;

	for (i = 0; i< MAX_FINGER_NUM; i++) {
		input_mt_slot(info->input_dev, i);
		input_mt_report_slot_state(info->input_dev, MT_TOOL_FINGER, false);
	}
	input_sync(info->input_dev);

	return;
}

/*
 * mms_fs_open, mms_fs_release, mms_event_handler, mms_fs_read, mms_fs_write
 * melfas debugging function
 */
static int mms_fs_open(struct inode *node, struct file *fp)
{
	struct mms_ts_info *info;
	struct i2c_client *client;
	struct i2c_msg msg;
	u8 buf[3] = { 
		MMS_UNIVERSAL_CMD, 
		MMS_CMD_SET_LOG_MODE, 
		true, 
	};

	info = container_of(node->i_cdev, struct mms_ts_info, cdev);
	client = info->client;

	disable_irq(info->irq);

	fp->private_data = info;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = sizeof(buf);

	i2c_transfer(client->adapter, &msg, 1);

	info->log->data = kzalloc(MAX_LOG_LENGTH * 20 + 5, GFP_KERNEL);

	mms_clear_input_data(info);

	return 0;
}

static int mms_fs_release(struct inode *node, struct file *fp)
{
	struct mms_ts_info *info = fp->private_data;

	mms_clear_input_data(info);
	mms_reboot(info);

	kfree(info->log->data);
	enable_irq(info->irq);

	return 0;
}

static void mms_event_handler(struct mms_ts_info *info)
{
	struct i2c_client *client = info->client;
	int sz;
	int ret;
	int row_num;
	u8 reg = MMS_INPUT_EVENT;
	struct i2c_msg msg[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.buf = &reg,
			.len = 1,
		},
		{
			.addr = client->addr,
			.flags = 1,
			.buf = info->log->data,
		},
	};
	struct mms_log_pkt {
		u8 marker;
		u8 log_info;
		u8 code;
		u8 element_sz;
		u8 row_sz;
	} __attribute__((packed)) *pkt = (struct mms_log_pkt *)info->log->data;;

	memset(pkt, 0, sizeof(struct mms_log_pkt));

	if (gpio_get_value(info->pdata->gpio_resetb)) {
		return;
	}

	sz = i2c_smbus_read_byte_data(client, MMS_EVENT_PKT_SZ);
	msg[1].len = sz;
	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	if (ret != ARRAY_SIZE(msg)) {
		dev_err(&client->dev,
			"failed to read %d bytes of touch data (%d)\n",
			sz, ret);
		return;
	}

	if ((pkt->marker & 0xf) == MMS_LOG_EVENT) {
		if ((pkt->log_info & 0x7) == 0x1) {
			pkt->element_sz = 0;
			pkt->row_sz = 0;

			return;
		}

		switch (pkt->log_info >> 4) {
		case LOG_TYPE_U08:
		case LOG_TYPE_S08:
			msg[1].len = pkt->element_sz;
			break;
		case LOG_TYPE_U16:
		case LOG_TYPE_S16:
			msg[1].len = pkt->element_sz * 2;
			break;
		case LOG_TYPE_U32:
		case LOG_TYPE_S32:
			msg[1].len = pkt->element_sz * 4;
			break;
		default:
			dev_err(&client->dev, "invalid log type\n");
			break;
		}

		msg[1].buf = info->log->data + sizeof(struct mms_log_pkt);
		reg = MMS_UNIVERSAL_RESULT;
		row_num = pkt->row_sz ? pkt->row_sz : 1;

		while (row_num--) {
			while (gpio_get_value(info->pdata->gpio_resetb))
				;

			ret = i2c_transfer(client->adapter, msg, 2);
			msg[1].buf += msg[1].len;
		}; 

	} else {
		mms_report_input_data(info, sz, info->log->data);
		memset(pkt, 0, sizeof(struct mms_log_pkt));
	}


	return;

}

static ssize_t mms_fs_read(struct file *fp, char *rbuf, size_t cnt, loff_t *fpos)
{
	struct mms_ts_info *info = fp->private_data;
	struct i2c_client *client = info->client;
	int ret = 0;

	switch (info->log->cmd) {
	case GET_RX_NUM:
		ret = copy_to_user(rbuf, &info->rx_num, 1);
		break;

	case GET_TX_NUM:
		ret = copy_to_user(rbuf, &info->tx_num, 1);
		break;

	case GET_EVENT_DATA:
		mms_event_handler(info);
		/* send event without log marker */
		ret = copy_to_user(rbuf, info->log->data + 1, cnt);
		break;

	default:
		dev_err(&client->dev, "unknown command\n");
		ret = -EFAULT;
		goto out;
	}

out:
	return ret; 
}

static ssize_t mms_fs_write(struct file *fp, const char *wbuf, size_t cnt, loff_t *fpos)
{
	struct mms_ts_info *info = fp->private_data;
	struct i2c_client *client = info->client;
	struct i2c_msg msg;
	int ret = 0;
	u8 *buf;

	mutex_lock(&info->lock);

	buf = kzalloc(cnt + 1, GFP_KERNEL); 

	if ((buf == NULL) || copy_from_user(buf, wbuf, cnt)) {
		dev_err(&client->dev, "failed to read data from user\n");
		ret = -EIO;
		goto out;
	}

	if (cnt == 1) {
		info->log->cmd = *buf;
	} else {
		msg.addr = client->addr;
		msg.flags = 0;
		msg.buf = buf;
		msg.len = cnt;

		if (i2c_transfer(client->adapter, &msg, 1) != 1) {
			dev_err(&client->dev, "failt to transfer command\n");
			ret = -EIO;
			goto out;
		}
	}

	ret = 0;

out:
	kfree(buf);
	mutex_unlock(&info->lock);

	return ret;
}

static struct file_operations mms_fops = {
	.owner 				= THIS_MODULE,
	.open 				= mms_fs_open,
	.release 			= mms_fs_release,
	.read 				= mms_fs_read,
	.write 				= mms_fs_write,
};

static int reg_set_optimum_mode_check(struct regulator *reg, int load_uA)
{
	return (regulator_count_voltages(reg) > 0) ?
		regulator_set_optimum_mode(reg, load_uA) : 0;
}

void  melfas_vdd_on(struct mms_ts_info *info, bool onoff)
{
	int ret = 0, rc = 0;
	pr_info("[TSP] power %s\n", onoff ? "on" : "off");

	if (!info->vcc_i2c) {
		if (info->pdata->i2c_pull_up) {
			info->vcc_i2c = regulator_get(&info->client->dev,
				"vcc_i2c");
			if (IS_ERR(info->vcc_i2c)) {
				rc = PTR_ERR(info->vcc_i2c);
				dev_err(&info->client->dev,
					"Regulator get failed rc=%d\n", rc);
				goto error_get_vtg_i2c;
			}
			if (regulator_count_voltages(info->vcc_i2c) > 0) {
				rc = regulator_set_voltage(info->vcc_i2c,
				MMS_I2C_VTG_MIN_UV, MMS_I2C_VTG_MAX_UV);
				if (rc) {
					dev_err(&info->client->dev,
					"regulator set_vtg failed rc=%d\n",
					rc);
					goto error_set_vtg_i2c;
				}
			}
		}
	}

	if (onoff) {
		if (info->pdata->i2c_pull_up) {
			rc = reg_set_optimum_mode_check(info->vcc_i2c,
						MMS_I2C_LOAD_UA);
			if (rc < 0) {
				dev_err(&info->client->dev,
				"Regulator vcc_i2c set_opt failed rc=%d\n",
				rc);
				goto error_reg_opt_i2c;
			}

			rc = regulator_enable(info->vcc_i2c);
			if (rc) {
				dev_err(&info->client->dev,
				"Regulator vcc_i2c enable failed rc=%d\n",
				rc);
				goto error_reg_en_vcc_i2c;
			}
		}
	} else {
		if (info->pdata->i2c_pull_up) {
			reg_set_optimum_mode_check(info->vcc_i2c, 0);
			regulator_disable(info->vcc_i2c);
		}
	}
	//msleep(50);

	ret = gpio_direction_output(info->pdata->vdd_en, onoff);
	if (ret) {
		pr_err("[TSP]%s: unable to set_direction for mms_vdd_en [%d]\n",
				__func__, info->pdata->vdd_en);
	}
	//msleep(30);
	return;

error_reg_en_vcc_i2c:
	if (info->pdata->i2c_pull_up)
		reg_set_optimum_mode_check(info->vcc_i2c, 0);
error_reg_opt_i2c:
error_set_vtg_i2c:
	regulator_put(info->vcc_i2c);
error_get_vtg_i2c:
	return;

}

int melfas_power(struct i2c_client *client,bool onoff)
{
	struct mms_ts_info *info = i2c_get_clientdata(client);	
	melfas_vdd_on(info,onoff);
	return 0;
}

EXPORT_SYMBOL(melfas_power);

/* mms_reboot - IC reset */ 
static void mms_reboot(struct mms_ts_info *info)
{
	struct i2c_adapter *adapter = to_i2c_adapter(info->client->dev.parent);

	i2c_lock_adapter(adapter);
//	info->pdata->mux_fw_flash(true);

//	gpio_direction_output(info->pdata->gpio_vdd_en, 0);
//	gpio_direction_output(info->pdata->gpio_scl, 1);
//	gpio_direction_output(info->pdata->gpio_sda, 1);
//	gpio_direction_output(info->pdata->gpio_resetb, 1);
	melfas_vdd_on(info, 0);
	msleep(50);
//	gpio_direction_output(info->pdata->gpio_vdd_en, 1);
	melfas_vdd_on(info, 1);
	msleep(50);

//	info->pdata->mux_fw_flash(false);
	i2c_unlock_adapter(adapter);

	msleep(250);
}

/* mms_report_input_data - The position of a touch send to platfrom  */
static void mms_report_input_data(struct mms_ts_info *info, u8 sz, u8 *buf)
{
	int i;
	struct i2c_client *client = info->client;
	int id;
	int x;
	int y;
	int touch_major;
	int pressure;
	int key_code;
	int key_state;
	u8 *tmp;

	if (buf[0] == MMS_NOTIFY_EVENT) {
		dev_info(&client->dev, "TSP mode changed (%d)\n", buf[1]);
		goto out;
	} else if (buf[0] == MMS_ERROR_EVENT) {
		dev_info(&client->dev, "Error detected, restarting TSP\n");
		mms_clear_input_data(info);
		mms_reboot(info);
		esd_cnt++;
		if (esd_cnt>= ESD_DETECT_COUNT)
		{
			i2c_smbus_write_byte_data(info->client, MMS_MODE_CONTROL, 0x04);
			esd_cnt =0;
		}
		goto out;
	}

	for (i = 0; i < sz; i += FINGER_EVENT_SZ) {
		tmp = buf + i;
		esd_cnt =0;
		if (tmp[0] & MMS_TOUCH_KEY_EVENT) {
			switch (tmp[0] & 0xf) {
			case 1:
				key_code = KEY_MENU;
				break;
			case 2:
				key_code = KEY_BACK;
				break;
			default:
				dev_err(&client->dev, "unknown key type\n");
				goto out;
				break;
			}

			key_state = (tmp[0] & 0x80) ? 1 : 0;
			input_report_key(info->input_dev, key_code, key_state);
			printk("[KEY] key_code=%d key_state=%d\n",key_code, key_state);

		} else {
			id = (tmp[0] & 0xf) -1;
			x = tmp[2] | ((tmp[1] & 0xf) << 8);
			y = tmp[3] | (((tmp[1] >> 4 ) & 0xf) << 8);
			touch_major = tmp[4];
			pressure = tmp[5];

			input_mt_slot(info->input_dev, id);
			
			if (!(tmp[0] & 0x80)) {
				dev_info(&client->dev,"finger id[%d]: x=%d y=%d\n", id, x, y);
				input_mt_report_slot_state(info->input_dev, MT_TOOL_FINGER, false);
				continue;
			}

			input_mt_report_slot_state(info->input_dev, MT_TOOL_FINGER, true);
			input_report_abs(info->input_dev, ABS_MT_POSITION_X, x);
			input_report_abs(info->input_dev, ABS_MT_POSITION_Y, y);
			input_report_abs(info->input_dev, ABS_MT_TOUCH_MAJOR, touch_major);
			input_report_abs(info->input_dev, ABS_MT_PRESSURE, pressure);
		}
	}

	input_sync(info->input_dev);
 out:
	return;
}

/* mms_ts_interrupt - interrupt thread */
static irqreturn_t mms_ts_interrupt(int irq, void *dev_id)
{
	struct mms_ts_info *info = dev_id;
	struct i2c_client *client = info->client;
	u8 buf[MAX_FINGER_NUM * FINGER_EVENT_SZ] = { 0 };
	int ret;
	int sz;
	u8 reg = MMS_INPUT_EVENT;
	struct i2c_msg msg[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.buf = &reg,
			.len = 1,
		},
		{
			.addr = client->addr,
			.flags = 1,
			.buf = buf,
		},
	};

	sz = i2c_smbus_read_byte_data(client, MMS_EVENT_PKT_SZ);
	msg[1].len = sz;
	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	if (ret != ARRAY_SIZE(msg)) {
		dev_err(&client->dev,
			"failed to read %d bytes of touch data (%d)\n",
			sz, ret);
	}

	mms_report_input_data(info, sz, buf);

	return IRQ_HANDLED;
}

#if 1 // firmup

int get_tsp_status(void)
{
	return touch_is_pressed;
}
EXPORT_SYMBOL(get_tsp_status);

static void hw_reboot(struct mms_ts_info *info, bool bootloader)
{
	melfas_vdd_on(info, 0);
	gpio_direction_output(info->pdata->gpio_sda, bootloader ? 0 : 1);
	gpio_direction_output(info->pdata->gpio_scl, bootloader ? 0 : 1);
	gpio_direction_output(info->pdata->gpio_int, 0);
	msleep(30);
	melfas_vdd_on(info, 1);
	msleep(30);

	if (bootloader) {
		gpio_set_value(info->pdata->gpio_scl, 0);
		gpio_set_value(info->pdata->gpio_sda, 1);
	} else {
		gpio_set_value(info->pdata->gpio_int, 1);
		gpio_direction_input(info->pdata->gpio_int);
		gpio_direction_input(info->pdata->gpio_scl);
		gpio_direction_input(info->pdata->gpio_sda);
	}
	msleep(40);
}

static inline void hw_reboot_bootloader(struct mms_ts_info *info)
{
	hw_reboot(info, true);
}

static inline void hw_reboot_normal(struct mms_ts_info *info)
{
	hw_reboot(info, false);
}

static void isp_toggle_clk(struct mms_ts_info *info, int start_lvl, int end_lvl,
			   int hold_us)
{
	gpio_set_value(info->pdata->gpio_scl, start_lvl);
	udelay(hold_us);
	gpio_set_value(info->pdata->gpio_scl, end_lvl);
	udelay(hold_us);
}

/* 1 <= cnt <= 32 bits to write */
static void isp_send_bits(struct mms_ts_info *info, u32 data, int cnt)
{
	gpio_direction_output(info->pdata->gpio_int, 0);
	gpio_direction_output(info->pdata->gpio_scl, 0);
	gpio_direction_output(info->pdata->gpio_sda, 0);

	/* clock out the bits, msb first */
	while (cnt--) {
		gpio_set_value(info->pdata->gpio_sda, (data >> cnt) & 1);
		udelay(3);
		isp_toggle_clk(info, 1, 0, 3);
	}
}

/* 1 <= cnt <= 32 bits to read */
static u32 isp_recv_bits(struct mms_ts_info *info, int cnt)
{
	u32 data = 0;

	gpio_direction_output(info->pdata->gpio_int, 0);
	gpio_direction_output(info->pdata->gpio_scl, 0);
	gpio_set_value(info->pdata->gpio_sda, 0);
	gpio_direction_input(info->pdata->gpio_sda);

	/* clock in the bits, msb first */
	while (cnt--) {
		isp_toggle_clk(info, 0, 1, 1);
		data = (data << 1) | (!!gpio_get_value(info->pdata->gpio_sda));
	}

	gpio_direction_output(info->pdata->gpio_sda, 0);
	return data;
}

static void isp_enter_mode(struct mms_ts_info *info, u32 mode)
{
	int cnt;
	unsigned long flags;

	local_irq_save(flags);
	gpio_direction_output(info->pdata->gpio_int, 0);
	gpio_direction_output(info->pdata->gpio_scl, 0);
	gpio_direction_output(info->pdata->gpio_sda, 1);

	mode &= 0xffff;
	for (cnt = 15; cnt >= 0; cnt--) {
		gpio_set_value(info->pdata->gpio_int, (mode >> cnt) & 1);
		udelay(3);
		isp_toggle_clk(info, 1, 0, 3);
	}

	gpio_set_value(info->pdata->gpio_int, 0);
	local_irq_restore(flags);
}

static void isp_exit_mode(struct mms_ts_info *info)
{
	int i;
	unsigned long flags;

	local_irq_save(flags);
	gpio_direction_output(info->pdata->gpio_int, 0);
	udelay(3);

	for (i = 0; i < 10; i++)
		isp_toggle_clk(info, 1, 0, 3);
	local_irq_restore(flags);
}

static void flash_set_address(struct mms_ts_info *info, u16 addr)
{
	/* Only 13 bits of addr are valid.
	 * The addr is in bits 13:1 of cmd */
	isp_send_bits(info, (u32) (addr & 0x1fff) << 1, 18);
}

static void flash_erase(struct mms_ts_info *info)
{
	isp_enter_mode(info, ISP_MODE_FLASH_ERASE);

	gpio_direction_output(info->pdata->gpio_int, 0);
	gpio_direction_output(info->pdata->gpio_scl, 0);
	gpio_direction_output(info->pdata->gpio_sda, 1);

	/* 4 clock cycles with different timings for the erase to
	 * get processed, clk is already 0 from above */
	udelay(7);
	isp_toggle_clk(info, 1, 0, 3);
	udelay(7);
	isp_toggle_clk(info, 1, 0, 3);
	usleep_range(25000, 35000);
	isp_toggle_clk(info, 1, 0, 3);
	usleep_range(150, 200);
	isp_toggle_clk(info, 1, 0, 3);

	gpio_set_value(info->pdata->gpio_sda, 0);

	isp_exit_mode(info);
}

static u32 flash_readl(struct mms_ts_info *info, u16 addr)
{
	int i;
	u32 val;
	unsigned long flags;

	local_irq_save(flags);
	isp_enter_mode(info, ISP_MODE_FLASH_READ);
	flash_set_address(info, addr);

	gpio_direction_output(info->pdata->gpio_scl, 0);
	gpio_direction_output(info->pdata->gpio_sda, 0);
	udelay(40);

	/* data load cycle */
	for (i = 0; i < 6; i++)
		isp_toggle_clk(info, 1, 0, 10);

	val = isp_recv_bits(info, 32);
	isp_exit_mode(info);
	local_irq_restore(flags);

	return val;
}

static void flash_writel(struct mms_ts_info *info, u16 addr, u32 val)
{
	unsigned long flags;

	local_irq_save(flags);
	isp_enter_mode(info, ISP_MODE_FLASH_WRITE);
	flash_set_address(info, addr);
	isp_send_bits(info, val, 32);

	gpio_direction_output(info->pdata->gpio_sda, 1);
	/* 6 clock cycles with different timings for the data to get written
	 * into flash */
	isp_toggle_clk(info, 0, 1, 3);
	isp_toggle_clk(info, 0, 1, 3);
	isp_toggle_clk(info, 0, 1, 6);
	isp_toggle_clk(info, 0, 1, 12);
	isp_toggle_clk(info, 0, 1, 3);
	isp_toggle_clk(info, 0, 1, 3);

	isp_toggle_clk(info, 1, 0, 1);

	gpio_direction_output(info->pdata->gpio_sda, 0);
	isp_exit_mode(info);
	local_irq_restore(flags);
	usleep_range(300, 400);
}

static bool flash_is_erased(struct mms_ts_info *info)
{
	struct i2c_client *client = info->client;
	u32 val;
	u16 addr;

	for (addr = 0; addr < (ISP_MAX_FW_SIZE / 4); addr++) {
		udelay(40);
		val = flash_readl(info, addr);

		if (val != 0xffffffff) {
			dev_dbg(&client->dev,
				"addr 0x%x not erased: 0x%08x != 0xffffffff\n",
				addr, val);
			return false;
		}
	}
	return true;
}

static int fw_write_image(struct mms_ts_info *info, const u8 * data, size_t len)
{
	struct i2c_client *client = info->client;
	u16 addr = 0;

	for (addr = 0; addr < (len / 4); addr++, data += 4) {
		u32 val = get_unaligned_le32(data);
		u32 verify_val;
		int retries = 3;

		while (retries--) {
			flash_writel(info, addr, val);
			verify_val = flash_readl(info, addr);
			if (val == verify_val)
				break;
			dev_err(&client->dev,
				"mismatch @ addr 0x%x: 0x%x != 0x%x\n",
				addr, verify_val, val);
			continue;
		}
		if (retries < 0)
			return -ENXIO;
	}

	return 0;
}

static int fw_download(struct mms_ts_info *info, const u8 * data, size_t len)
{
	struct i2c_client *client = info->client;
	u32 val;
	int ret = 0;
	int i;
	u32 *buf = kzalloc(ISP_CAL_DATA_SIZE * 4, GFP_KERNEL);
	if (!buf) {
		dev_err(&info->client->dev, "%s: failed to allocate memory\n",
			__func__);
		return -ENOMEM;
	}

	if (len % 4) {
		dev_err(&client->dev,
			"fw image size (%d) must be a multiple of 4 bytes\n",
			len);
		kfree(buf);
		return -EINVAL;
	} else if (len > ISP_MAX_FW_SIZE) {
		dev_err(&client->dev,
			"fw image is too big, %d > %d\n", len, ISP_MAX_FW_SIZE);
		kfree(buf);
		return -EINVAL;
	}

	dev_info(&client->dev, "fw download start\n");

	melfas_vdd_on(info, 0);
	gpio_direction_output(info->pdata->gpio_sda, 0);
	gpio_direction_output(info->pdata->gpio_scl, 0);
	gpio_direction_output(info->pdata->gpio_int, 0);

	hw_reboot_bootloader(info);

	dev_info(&client->dev, "calibration data backup\n");
	for (i = 0; i < ISP_CAL_DATA_SIZE; i++)
		buf[i] = flash_readl(info, ISP_IC_INFO_ADDR+i);

	val = flash_readl(info, ISP_IC_INFO_ADDR);
	dev_info(&client->dev, "IC info: 0x%02x (%x)\n", val & 0xff, val);

	dev_info(&client->dev, "fw erase...\n");
	flash_erase(info);
	if (!flash_is_erased(info)) {
		ret = -ENXIO;
		goto err;
	}

	dev_info(&client->dev, "fw write...\n");
	/* XXX: what does this do?! */
	flash_writel(info, ISP_IC_INFO_ADDR, 0xffffff00 | (val & 0xff));
	usleep_range(1000, 1500);
	ret = fw_write_image(info, data, len);
	if (ret)
		goto err;
	usleep_range(1000, 1500);

	dev_info(&client->dev, "restoring data\n");
	for (i = 0; i < ISP_CAL_DATA_SIZE; i++)
		flash_writel(info, ISP_IC_INFO_ADDR+i, buf[i]);
	kfree(buf);

	dev_info(&client->dev, "fw download done...\n");
	hw_reboot_normal(info);
	msleep(200);
	return 0;

err:
	dev_err(&client->dev, "fw download failed...\n");
	kfree(buf);
	hw_reboot_normal(info);
	return ret;
}

#if 0 // unused
static int mms_flash_boot(struct mms_ts_info *info)
{
	struct i2c_client *client = info->client;
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	int ret = 0;
	int retries = 3;
	const u8 *buff = 0;
	long fsize = 0;
	const struct firmware *tsp_fw = NULL;

	dev_info(&client->dev, "%s\n", __func__);

	ret = request_firmware(&tsp_fw,
		"tsp_melfas/note/mms_boot.fw", &(client->dev));
	if (ret) {
		dev_err(&client->dev, "request firmware error!!\n");
		return 1;
	}

	fsize = tsp_fw->size;
	buff = kzalloc((size_t)fsize, GFP_KERNEL);
	if (!buff) {
		dev_err(&client->dev, "fail to alloc buffer for fw\n");
		info->cmd_state = 3;
		release_firmware(tsp_fw);
		return 1;
	}

	memcpy((void *)buff, tsp_fw->data, fsize);
	release_firmware(tsp_fw);

	while (retries--) {
		i2c_lock_adapter(adapter);
		info->pdata->mux_fw_flash(true);

		ret = fw_download(info, (const u8 *)buff,
				(const size_t)fsize);

		info->pdata->mux_fw_flash(false);
		i2c_unlock_adapter(adapter);

		if (ret < 0)
			dev_err(&client->dev, "retry flashing\n");
		else
			break;
	}
	kfree(buff);
	return ret;
}

#endif

#endif


/* mms_ts_enable - wake-up func (VDD on)  */
static int mms_ts_enable(struct mms_ts_info *info)
{
//        mutex_lock(&info->lock);
	if (info->enabled)
		goto out;

	/*
	gpio_direction_output(info->pdata->gpio_resetb, 0);
	udelay(5);
	gpio_direction_input(info->pdata->gpio_resetb);
*/

	gpio_direction_output(info->pdata->vdd_en, 1);

	info->enabled = true;
	enable_irq(info->irq);
out:
//	mutex_unlock(&info->lock);
	return 0;
}

/* mms_ts_disable - sleep func (VDD off) */
static int mms_ts_disable(struct mms_ts_info *info)
{
//        mutex_lock(&info->lock);

	if (!info->enabled)
		goto out;

	
	disable_irq(info->irq);

/*
	i2c_smbus_write_byte_data(info->client, MMS_MODE_CONTROL, 0);
	usleep_range(10000, 12000);

*/
	gpio_direction_output(info->pdata->vdd_en, 0);


	info->enabled = false;

out:
//	mutex_unlock(&info->lock);
	return 0;
}
/*
 * mms_ts_input_open - Register input device after call this function 
 * this function is wait firmware flash wait
 */ 
static int mms_ts_input_open(struct input_dev *dev)
{
	struct mms_ts_info *info = input_get_drvdata(dev);
//	int ret;
	printk("%s %d\n",__func__,__LINE__);
	mms_ts_enable(info);
/*
	ret = wait_for_completion_interruptible_timeout(&info->init_done,
			msecs_to_jiffies(90 * MSEC_PER_SEC));

	if (ret > 0) {
		if (info->irq != -1)
			ret = mms_ts_enable(info);
		else
			ret = -ENXIO;
	} else if (ret < 0) {
		dev_err(&dev->dev,
			"error while waiting for device to init (%d)\n", ret);
		ret = -ENXIO;
	} else if (ret == 0) {
		dev_err(&dev->dev,
			"timeout while waiting for device to init");
		ret = -ENXIO;
	}
	return ret;
*/
	return 0;
}

/*
 * mms_ts_input_close -If device power off state call this function
 */
static void mms_ts_input_close(struct input_dev *dev)
{
	struct mms_ts_info *info = input_get_drvdata(dev);
	printk("%s %d\n",__func__,__LINE__);	
	mms_ts_disable(info);
	return;
}

/*
 * get_fw_version - get firmware vertion
 */

static unsigned char get_fw_version(struct mms_ts_info *info, u8 area)
{
	struct i2c_client *client = info->client;
	struct i2c_adapter *adapter = client->adapter;
	struct i2c_msg msg;
	u8 reg = MMS_CORE_VERSION;
	u8 reg2 = MMS_MODULE_REVISION;
	int ret;
	unsigned char buf[4];

	msg.addr = client->addr;
	msg.flags = 0x00;
	msg.len = 1;
	if(area == SEC_MODULE)
		msg.buf = &reg2;
	else 
		msg.buf = &reg;

	ret = i2c_transfer(adapter, &msg, 1);

	if (ret >= 0) {
		msg.addr = client->addr;
		msg.flags = I2C_M_RD;
		
		if(area == SEC_MODULE)
			msg.len = 2;
		else
			msg.len = 4;
		msg.buf = buf;

		ret = i2c_transfer(adapter, &msg, 1);
	}
	if (ret < 0) {
		pr_err("[TSP] : read error : [%d]", ret);
		return ret;
	}

	if ((area == SEC_BOOTLOADER)||(area == SEC_MODULE))
		return buf[0];
	else if (area == SEC_CORE)
		return buf[1];
	else if (area == SEC_CONFIG)
		return buf[2];
	else
		return 0;
}


static int get_fw_version2(struct i2c_client *client, u8 *buf)
{
	u8 cmd = MMS_FW_VERSION;
	struct i2c_msg msg[2] = {
		{
			.addr = client->addr,
			.flags = 0,
			.buf = &cmd,
			.len = 1,
		}, {
			.addr = client->addr,
			.flags = I2C_M_RD,
			.buf = buf,
			.len = MAX_SECTION_NUM,
		},
	};

	return (i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg)) != ARRAY_SIZE(msg));
}

/*
 * mms_ts_config - f/w check download & irq thread register
 */
static int mms_ts_config(struct mms_ts_info *info)
{
	struct i2c_client *client = info->client;
	int ret;
	bool flag = false;
	int retries = 3;
	u8 ver[MAX_SECTION_NUM];
	mms_reboot(info);

	if (/* check_fw_status(info) ||*/ mms_isp_flash) {
		mms_flash_fw(client, info->pdata);
	} else {
		while (retries--){
			if (!get_fw_version2(client, ver)){
				print_hex_dump(KERN_INFO, "mms_ts fw ver : ", DUMP_PREFIX_NONE, 16, 1,
						ver, MAX_SECTION_NUM, false);
				if((ver[0]==0x4)&&(ver[1])==0x53){	//Delos TSP 04 53 25,  Victor TSP 06 58 05
					printk("%s TSP firmware update skip !!(%d)\n",__func__, __LINE__);
					break;
				}

				if(get_fw_version(info, SEC_MODULE)== 0x1){
					printk("%s TSP moduleis old, update skip !!(%d)\n",__func__, __LINE__);
					break;
				}
				
				mms100_ISC_download_mbinary(client, flag);
				mms_reboot(info);
				if(ISC_NO_NEED_UPDATE_ERROR || ISC_SUCCESS)
					break;
			}else{
				mms_reboot(info);
			}
		} 
	}

	if (retries < 0) {
		dev_err(&client->dev, "failed to update firmware\n");
	}

	client->irq = gpio_to_irq(info->pdata->gpio_int);
	printk("%s: tsp : gpio_to_irq : %d\n", __func__, client->irq);
	
	ret = request_threaded_irq(client->irq, NULL, mms_ts_interrupt,
				   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				   "mms_ts", info);
	disable_irq(client->irq);
	info->irq = client->irq;
	barrier();

	info->tx_num = i2c_smbus_read_byte_data(client, MMS_TX_NUM);
	info->rx_num = i2c_smbus_read_byte_data(client, MMS_RX_NUM);
	info->key_num = i2c_smbus_read_byte_data(client, MMS_KEY_NUM);
	dev_info(&client->dev,
		"Melfas MMS-series touch controller initialized\n");

//	complete_all(&info->init_done);

	return 0;
}

/*
 * bin_report_read, bin_report_write, bin_sysfs_read, bin_sysfs_write
 * melfas debugging function
 */
static ssize_t bin_report_read(struct file *fp, struct kobject *kobj, struct bin_attribute *attr,
                                char *buf, loff_t off, size_t count)
{
        struct device *dev = container_of(kobj, struct device, kobj);
        struct i2c_client *client = to_i2c_client(dev);
        struct mms_ts_info *info = i2c_get_clientdata(client);
	count = 0;
	switch(info->data_cmd){
	case SYS_TXNUM:
		dev_info(&info->client->dev, "tx send %d \n",info->tx_num);
		buf[0]=info->tx_num;
		count =1;
		info->data_cmd = 0;
		break;
	case SYS_RXNUM:
		dev_info(&info->client->dev, "rx send%d\n", info->rx_num);
		buf[0]=info->rx_num;
		count =1;
		info->data_cmd = 0;
		break;
	case SYS_CLEAR:
		dev_info(&info->client->dev, "Input clear\n");
		mms_clear_input_data(info);
		count = 1;
		info->data_cmd = 0;
		break;
	case SYS_ENABLE:
		dev_info(&info->client->dev, "enable_irq  \n");
		enable_irq(info->irq);
		count = 1;
		info->data_cmd = 0;
		break;
	case SYS_DISABLE:
		dev_info(&info->client->dev, "disable_irq  \n");
		disable_irq(info->irq);
		count = 1;
		info->data_cmd = 0;
		break;
	case SYS_INTERRUPT:
		count = gpio_get_value(info->pdata->gpio_resetb);
		info->data_cmd = 0;
		break;
	case SYS_RESET:
		mms_reboot(info);
		dev_info(&info->client->dev, "read mms_reboot\n");
		count = 1;
		info->data_cmd = 0;
		break;
	}
	return count;
}

static ssize_t bin_report_write(struct file *fp, struct kobject *kobj, struct bin_attribute *attr,
                                char *buf, loff_t off, size_t count)
{
        struct device *dev = container_of(kobj, struct device, kobj);
        struct i2c_client *client = to_i2c_client(dev);
        struct mms_ts_info *info = i2c_get_clientdata(client);
	if(buf[0]==100){
		mms_report_input_data(info, buf[1], &buf[2]);
	}else{
		info->data_cmd=(int)buf[0];
	}
	return count;
        
}
static struct bin_attribute bin_attr_data = {
        .attr = {
                .name = "report_data",
                .mode = S_IRWXUGO,
        },
        .size = PAGE_SIZE,
        .read = bin_report_read,
        .write = bin_report_write,
};

static ssize_t bin_sysfs_read(struct file *fp, struct kobject *kobj , struct bin_attribute *attr,
                          char *buf, loff_t off,size_t count)
{
        struct device *dev = container_of(kobj, struct device, kobj);
        struct i2c_client *client = to_i2c_client(dev);
        struct mms_ts_info *info = i2c_get_clientdata(client);
        struct i2c_msg msg;
        info->client = client;

        msg.addr = client->addr;
        msg.flags = I2C_M_RD ;
        msg.buf = (u8 *)buf;
        msg.len = count;

	switch (count)
	{
		case 65535:
			mms_reboot(info);
			dev_info(&client->dev, "read mms_reboot\n");
			return 0;

		default :
			if(i2c_transfer(client->adapter, &msg, 1) != 1){
	                	dev_err(&client->dev, "failed to transfer data\n");
        	        	mms_reboot(info);
        	        	return 0;
        		}
			break;

	}

        return count;
}

static ssize_t bin_sysfs_write(struct file *fp, struct kobject *kobj, struct bin_attribute *attr,
                                char *buf, loff_t off, size_t count)
{
        struct device *dev = container_of(kobj, struct device, kobj);
        struct i2c_client *client = to_i2c_client(dev);
        struct mms_ts_info *info = i2c_get_clientdata(client);
        struct i2c_msg msg;

        msg.addr =client->addr;
        msg.flags = 0;
        msg.buf = (u8 *)buf;
        msg.len = count;


        if(i2c_transfer(client->adapter, &msg, 1) != 1){
                dev_err(&client->dev, "failed to transfer data\n");
                mms_reboot(info);
                return 0;
        }

        return count;
}

static struct bin_attribute bin_attr = {
        .attr = {
                .name = "mms_bin",
                .mode = S_IRWXUGO,
        },
        .size = PAGE_SIZE,
        .read = bin_sysfs_read,
        .write = bin_sysfs_write,
};

#ifdef __MMS_TEST_MODE__
struct mms_ts_test test;
static ssize_t mms_intensity(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct mms_ts_info *info = dev_get_drvdata(dev);
	int ret;
	dev_info(&info->client->dev, "Intensity Test\n");
	if(get_test_intensity(&test)!=0){
		dev_err(&info->client->dev, "Intensity Test failed\n");
		return -1;
	}
	ret = snprintf(buf,PAGE_SIZE,"%s\n",test.get_data);
	return ret;
}

static DEVICE_ATTR(intensity, 0666, mms_intensity, NULL);

static ssize_t mms_cmdelta(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct mms_ts_info *info = dev_get_drvdata(dev);
	int ret;
	dev_info(&info->client->dev, "cm delta Test\n");
	get_cm_test_init(&test);
	get_cm_test_delta(&test);
	get_cm_test_exit(&test);
	
	ret = snprintf(buf,PAGE_SIZE,"%s\n",test.get_data);
	memset(test.get_data,0,4096);
	return ret;
}
static DEVICE_ATTR(cmdelta, 0666, mms_cmdelta, NULL);

static ssize_t mms_cmabs(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct mms_ts_info *info = dev_get_drvdata(dev);
	int ret;
	dev_info(&info->client->dev, "cm delta Test\n");
	get_cm_test_init(&test);
	get_cm_test_abs(&test);
	get_cm_test_exit(&test);
	
	
	ret = snprintf(buf,PAGE_SIZE,"%s\n",test.get_data);
	memset(test.get_data,0,4096);
	return ret;
}
static DEVICE_ATTR(cmabs, 0666, mms_cmabs, NULL);

static ssize_t mms_cmjitter(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct mms_ts_info *info = dev_get_drvdata(dev);
	int ret;
	dev_info(&info->client->dev, "cm delta Test\n");
	get_cm_test_init(&test);
	get_cm_test_jitter(&test);
	get_cm_test_exit(&test);
	
	ret = snprintf(buf,PAGE_SIZE,"%s\n",test.get_data);
	memset(test.get_data,0,4096);
	return ret;
}
static DEVICE_ATTR(cmjitter, 0666, mms_cmjitter, NULL);

static struct attribute *mms_attrs[] = {
	&dev_attr_intensity.attr,
	&dev_attr_cmdelta.attr,
	&dev_attr_cmabs.attr,
	&dev_attr_cmjitter.attr,
	NULL,
};

static const struct attribute_group mms_attr_group = {
	.attrs = mms_attrs,
};
#endif



static inline void mms_pwr_on_reset(struct mms_ts_info *info)
{
	struct i2c_adapter *adapter = to_i2c_adapter(info->client->dev.parent);

	/*if (!info->pdata->mux_fw_flash) {
		dev_info(&info->client->dev,
			 "missing platform data, can't do power-on-reset\n");
		return;
	}*/

	i2c_lock_adapter(adapter);
//	info->pdata->mux_fw_flash(true);

	//info->pdata->power(0);
	melfas_vdd_on(info, 0);

//	gpio_direction_output(info->pdata->gpio_sda, 0);
//	gpio_direction_output(info->pdata->gpio_scl, 0);
//	gpio_direction_output(info->pdata->gpio_int, 0);
	msleep(50);
	//info->pdata->power(1);
	melfas_vdd_on(info, 1);

	msleep(200);

	//info->pdata->mux_fw_flash(false);
	i2c_unlock_adapter(adapter);

	/* TODO: Seems long enough for the firmware to boot.
	 * Find the right value */
	msleep(250);
}
static void release_all_fingers(struct mms_ts_info *info)
{
	struct i2c_client *client = info->client;
	int i;

	dev_dbg(&client->dev, "[TSP] %s\n", __func__);

	for (i = 0; i < MAX_FINGERS; i++) {
#ifdef SEC_TSP_DEBUG
		if (info->finger_state[i] == 1)
			printk("finger %d up(force)\n", i);
#endif
		info->finger_state[i] = 0;
		input_mt_slot(info->input_dev, i);
		input_mt_report_slot_state(info->input_dev, MT_TOOL_FINGER,
					   false);
	}
	input_sync(info->input_dev);
#if TOUCH_BOOSTER
	set_dvfs_lock(info, 2);
	pr_info("[TSP] dvfs_lock free.\n ");
#endif
}
#if 0
static void mms_set_noise_mode(struct mms_ts_info *info)
{
	struct i2c_client *client = info->client;

      //return ; /* 20130913 TEMP */

	if (!(info->noise_mode && info->enabled))
		return;
	dev_notice(&client->dev, "%s\n", __func__);

	if (info->ta_status) {
		dev_notice(&client->dev, "noise_mode & TA connect!!!\n");
		i2c_smbus_write_byte_data(info->client, 0x30, 0x1);
	} else {
		dev_notice(&client->dev, "noise_mode & TA disconnect!!!\n");
		i2c_smbus_write_byte_data(info->client, 0x30, 0x2);
		info->noise_mode = 0;
	}
}
#endif


#ifdef SEC_TSP_INFO_SHOW


struct device *sec_touchkey;

//static u16 menu_sensitivity=0;
//static u16 home_sensitivity=0;
//static u16 back_sensitivity=0;


static ssize_t set_firm_update_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	return 0;
}


static ssize_t set_firm_status_show(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	return 0;

}

#define THRESHOLD_SHOW

#ifdef THRESHOLD_SHOW
static ssize_t threshold_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	return 0;

}

static ssize_t threshold_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t size)
{
	return 0;

}
#endif

static ssize_t set_phone_firm_version_show(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
//  	struct i2c_client *client = to_i2c_client(dev);
//	struct mms_ts_info *info = i2c_get_clientdata(client);

      /* for phone */
//return sprintf(buf, "ME%02X%02X%02X", BOOT_VERSION, CORE_VERSION, FW_VERSION); 
return sprintf(buf, "ME%02X%02X%02X", MODU_VERSION, CORE_VERSION, FW_VERSION); 
}

static ssize_t set_panel_firm_version_show(struct device *dev,
					      struct device_attribute *attr,
					      char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct mms_ts_info *info = i2c_get_clientdata(client);

      /* for panel */

//	  return sprintf(buf, "ME%02X%02X%02X", get_fw_version(info, SEC_BOOTLOADER)
//				  ,get_fw_version(info, SEC_CORE), get_fw_version(info, SEC_CONFIG)); 
	  return sprintf(buf, "ME%02X%02X%02X", get_fw_version(info,SEC_MODULE),get_fw_version(info, SEC_CORE), get_fw_version(info, SEC_CONFIG)); 
}

static ssize_t set_config_version_read_show(struct device *dev,
						struct device_attribute *attr,
						char *buf)
{

      return sprintf(buf, "%s", "NA\n");
}

static ssize_t tsp_touchtype_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{

	char temp[15];
	
      sprintf(temp, "TSP : MMS136\n");
	strcat(buf, temp);

	return strlen(buf);
}

#define RMI_ADDR_UNIV_CMD						0xA0
#define UNIVCMD_GET_INTENSITY_KEY				0x71
#define RMI_ADDR_UNIV_CMD_RESULT_LENGTH			0xAE
#define RMI_ADDR_UNIV_CMD_RESULT				0xAF
#define RMI_ADDR_KEY_NUM						0x0D

#define WRITEARRAY_LEN		10
#define READARRAY_LEN       10

u8 master_write_buf[WRITEARRAY_LEN];
u8 master_read_buf_array[READARRAY_LEN];

static ssize_t menu_sensitivity_show(struct device *dev, struct device_attribute *attr, char *buf)
{

   	struct i2c_client *client = to_i2c_client(dev);
	struct mms_ts_info *info = i2c_get_clientdata(client);

	s16 local_menu_sensitivity = 0;

	int ret;

	master_write_buf[0] = RMI_ADDR_UNIV_CMD;
	master_write_buf[1] = UNIVCMD_GET_INTENSITY_KEY;
	master_write_buf[2] = 0xFF; //Exciting CH.
	master_write_buf[3] = 0; //Sensing CH.


	ret = i2c_smbus_write_i2c_block_data(info->client,master_write_buf[0], 4, &master_write_buf[1]);
	if(ret < 0)
	{
		printk( "menu_sensitivity_show 1 error\n");
		goto ERROR_HANDLE;
	}

	master_write_buf[0] = RMI_ADDR_UNIV_CMD_RESULT_LENGTH;
	
	ret = i2c_smbus_write_i2c_block_data(info->client,master_write_buf[0], 4, &master_write_buf[1]);
	
	if(ret < 0)
	{
		printk( "menu_sensitivity_show 2 error\n");
		goto ERROR_HANDLE;
	}

	ret = i2c_smbus_read_i2c_block_data(info->client,master_write_buf[0], 1, &master_read_buf_array[0]);

	if(ret < 0)
	{
		printk( "menu_sensitivity_show 3 error\n");
		goto ERROR_HANDLE;
	}

	master_write_buf[0] = RMI_ADDR_UNIV_CMD_RESULT;
	ret = i2c_smbus_write_i2c_block_data(info->client,master_write_buf[0], 4, &master_write_buf[1]);

	if(ret < 0)
	{
		printk( "menu_sensitivity_show 4 error\n");
		goto ERROR_HANDLE;
	}

	ret = i2c_smbus_read_i2c_block_data(info->client,master_write_buf[0], 4, &master_read_buf_array[0]);

	if(ret < 0)
	{
		printk( "menu_sensitivity_show 5 error\n");
		goto ERROR_HANDLE;
	}

	local_menu_sensitivity = master_read_buf_array[0] | (master_read_buf_array[1] << 8);


	printk( "%5d\n", local_menu_sensitivity);

	return sprintf(buf, "%d\n",  local_menu_sensitivity);


ERROR_HANDLE:
	printk( "menu sensitivity read Error!!\n");
	return 0;

}

#if 0
static ssize_t home_sensitivity_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int ret = 0;
    	u16 local_home_sensitivity = 200;

	if (ret<0)
		return sprintf(buf, "%s\n",  "fail to read home_sensitivity.");	
	else
	      return sprintf(buf, "%d\n",  local_home_sensitivity);
}
#endif

static ssize_t back_sensitivity_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
   	struct i2c_client *client = to_i2c_client(dev);
	struct mms_ts_info *info = i2c_get_clientdata(client);

	s16 local_back_sensitivity = 0;

	int ret;

	master_write_buf[0] = RMI_ADDR_UNIV_CMD;
	master_write_buf[1] = UNIVCMD_GET_INTENSITY_KEY;
	master_write_buf[2] = 0xFF; //Exciting CH.
	master_write_buf[3] = 0; //Sensing CH.


	ret = i2c_smbus_write_i2c_block_data(info->client,master_write_buf[0], 4, &master_write_buf[1]);
	if(ret < 0)
	{
		printk( "menu_sensitivity_show 1 error\n");
		goto ERROR_HANDLE;
	}

	master_write_buf[0] = RMI_ADDR_UNIV_CMD_RESULT_LENGTH;
	
	ret = i2c_smbus_write_i2c_block_data(info->client,master_write_buf[0], 4, &master_write_buf[1]);
	
	if(ret < 0)
	{
		printk( "menu_sensitivity_show 2 error\n");
		goto ERROR_HANDLE;
	}

	ret = i2c_smbus_read_i2c_block_data(info->client,master_write_buf[0], 1, &master_read_buf_array[0]);

	if(ret < 0)
	{
		printk( "menu_sensitivity_show 3 error\n");
		goto ERROR_HANDLE;
	}

	master_write_buf[0] = RMI_ADDR_UNIV_CMD_RESULT;
	ret = i2c_smbus_write_i2c_block_data(info->client,master_write_buf[0], 4, &master_write_buf[1]);

	if(ret < 0)
	{
		printk( "menu_sensitivity_show 4 error\n");
		goto ERROR_HANDLE;
	}

	ret = i2c_smbus_read_i2c_block_data(info->client,master_write_buf[0], 4, &master_read_buf_array[0]);

	if(ret < 0)
	{
		printk( "menu_sensitivity_show 5 error\n");
		goto ERROR_HANDLE;
	}

	local_back_sensitivity = master_read_buf_array[2] | (master_read_buf_array[3] << 8);


	printk( "%5d\n", local_back_sensitivity);

	return sprintf(buf, "%d\n",  local_back_sensitivity);


ERROR_HANDLE:
	printk( "back sensitivity read Error!!\n");
	return 0;

}

static ssize_t touchkey_threshold_show(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
   //	struct i2c_client *client = to_i2c_client(dev);
	int ret;
	
	ret = sprintf(buf, "%d\n", 35);

	return ret;
}


static DEVICE_ATTR(tsp_firm_update, S_IRUGO | S_IWUSR | S_IWGRP,
	set_firm_update_show, NULL);/* firmware update */
static DEVICE_ATTR(tsp_firm_update_status, S_IRUGO | S_IWUSR | S_IWGRP,
	set_firm_status_show, NULL);/* firmware update status return */
static DEVICE_ATTR(tsp_threshold, S_IRUGO | S_IWUSR | S_IWGRP,
	threshold_show, threshold_store);/* threshold return, store */
static DEVICE_ATTR(tsp_firm_version_phone, S_IRUGO | S_IWUSR | S_IWGRP,
	set_phone_firm_version_show, NULL);	/* PHONE */
static DEVICE_ATTR(tsp_firm_version_panel, S_IRUGO | S_IWUSR | S_IWGRP,
		   set_panel_firm_version_show, NULL);/*PART*/
static DEVICE_ATTR(tsp_config_version, S_IRUGO | S_IWUSR | S_IWGRP,
		   set_config_version_read_show, NULL);
 /*PART*/			/* TSP config last modifying date */
static DEVICE_ATTR(tsp_touchtype, S_IRUGO | S_IWUSR | S_IWGRP,
		   tsp_touchtype_show, NULL);

static DEVICE_ATTR(touchkey_menu, S_IRUGO, menu_sensitivity_show, NULL);
//static DEVICE_ATTR(touchkey_home, S_IRUGO, home_sensitivity_show, NULL);
static DEVICE_ATTR(touchkey_back, S_IRUGO, back_sensitivity_show, NULL);
static DEVICE_ATTR(touchkey_threshold, S_IRUGO, touchkey_threshold_show, NULL);
#endif				


#ifdef SEC_TSP_FACTORY_TEST
static void set_cmd_result(struct mms_ts_info *info, char *buff, int len)
{
	strncat(info->cmd_result, buff, len);
}

static int get_data(struct mms_ts_info *info, u8 addr, u8 size, u8 *array)
{
	struct i2c_client *client = info->client;
	struct i2c_adapter *adapter = client->adapter;
	struct i2c_msg msg;
	u8 reg = addr;
	unsigned char buf[size];
	int ret;

	msg.addr = client->addr;
	msg.flags = 0x00;
	msg.len = 1;
	msg.buf = &reg;

	ret = i2c_transfer(adapter, &msg, 1);

	if (ret >= 0) {
		msg.addr = client->addr;
		msg.flags = I2C_M_RD;
		msg.len = size;
		msg.buf = buf;

		ret = i2c_transfer(adapter, &msg, 1);
	}
	if (ret < 0) {
		pr_err("[TSP] : read error : [%d]", ret);
		return ret;
	}

	memcpy(array, &buf, size);
	return size;
}

static void get_intensity_data(struct mms_ts_info *info)
{
	u8 w_buf[4];
	u8 r_buf;
	u8 read_buffer[60] = {0};
	int i, j;
	int ret;
	u16 max_value = 0, min_value = 0;
	u16 raw_data;
	char buff[TSP_CMD_STR_LEN] = {0};

	disable_irq(info->irq);

	w_buf[0] = ADDR_UNIV_CMD;
	w_buf[1] = CMD_GET_INTEN;
	w_buf[2] = 0xFF;
	for (i = 0; i < RX_NUM; i++) {
		w_buf[3] = i;

		ret = i2c_smbus_write_i2c_block_data(info->client,
			w_buf[0], 3, &w_buf[1]);
		if (ret < 0)
			goto err_i2c;
		usleep_range(1, 5);

		ret = i2c_smbus_read_i2c_block_data(info->client,
			CMD_RESULT_SZ, 1, &r_buf);
		if (ret < 0)
			goto err_i2c;

		ret = get_data(info, CMD_RESULT, r_buf, read_buffer);
		if (ret < 0)
			goto err_i2c;

		for (j = 0; j < r_buf/2; j++) {
			raw_data = read_buffer[2*j] | (read_buffer[2*j+1] << 8);
			if (raw_data > 32767)
				raw_data = 0;
			if (i == 0 && j == 0) {
				max_value = min_value = raw_data;
			} else {
				max_value = max(max_value, raw_data);
				min_value = min(min_value, raw_data);
			}
			info->intensity[i * TX_NUM + j] = raw_data;
			dev_dbg(&info->client->dev,
				"[TSP] intensity[%d][%d] = %d\n", j, i,
				info->intensity[i * TX_NUM + j]);
		}
	}

	snprintf(buff, sizeof(buff), "%d,%d", min_value, max_value);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));

	enable_irq(info->irq);

	return;

err_i2c:
	dev_err(&info->client->dev, "%s: fail to i2c (cmd=%d)\n",
		__func__, MMS_VSC_CMD_INTENSITY);
}

static void get_raw_data(struct mms_ts_info *info, u8 cmd)
{
	u8 w_buf[4];
	u8 r_buf = 0;
	u8 read_buffer[60] = {0};
	int ret;
	int i, j;
	int max_value = 0, min_value = 0;
	int raw_data;
	int retry;
	char buff[TSP_CMD_STR_LEN] = {0};
	int gpio = info->pdata->gpio_int;

	disable_irq(info->irq);

	ret = i2c_smbus_write_byte_data(info->client,
		ADDR_UNIV_CMD, CMD_ENTER_TEST);
	if (ret < 0)
		goto err_i2c;

	/* event type check */
	retry = 1;
	while (retry) {
		while (gpio_get_value(gpio))
			udelay(100);

		ret = i2c_smbus_read_i2c_block_data(info->client,
			0x0F, 1, &r_buf);
		if (ret < 0)
			goto err_i2c;

		ret = i2c_smbus_read_i2c_block_data(info->client,
			0x10, 1, &r_buf);
		if (ret < 0)
			goto err_i2c;

		dev_info(&info->client->dev, "event type = 0x%x\n", r_buf);
		if (r_buf == 0x0C)
			retry = 0;
	}

	w_buf[0] = ADDR_UNIV_CMD;
	if (cmd == MMS_VSC_CMD_CM_DELTA)
		w_buf[1] = CMD_CM_DELTA;
	else
		w_buf[1] = CMD_CM_ABS;
	ret = i2c_smbus_write_i2c_block_data(info->client,
		 w_buf[0], 1, &w_buf[1]);
	if (ret < 0)
		goto err_i2c;
	while (gpio_get_value(gpio))
		udelay(100);

	ret = i2c_smbus_read_i2c_block_data(info->client,
		CMD_RESULT_SZ, 1, &r_buf);
	if (ret < 0)
		goto err_i2c;
	ret = i2c_smbus_read_i2c_block_data(info->client,
		CMD_RESULT, 1, &r_buf);
	if (ret < 0)
		goto err_i2c;

	if (r_buf == 1)
		dev_info(&info->client->dev, "PASS\n");
	else
		dev_info(&info->client->dev, "FAIL\n");

	if (cmd == MMS_VSC_CMD_CM_DELTA)
		w_buf[1] = CMD_GET_DELTA;
	else
		w_buf[1] = CMD_GET_ABS;
	w_buf[2] = 0xFF;

	for (i = 0; i < RX_NUM; i++) {
		w_buf[3] = i;

		ret = i2c_smbus_write_i2c_block_data(info->client,
			w_buf[0], 3, &w_buf[1]);
		if (ret < 0)
			goto err_i2c;

		while (gpio_get_value(gpio))
			udelay(100);

		ret = i2c_smbus_read_i2c_block_data(info->client,
			CMD_RESULT_SZ, 1, &r_buf);
		if (ret < 0)
			goto err_i2c;

		ret = get_data(info, CMD_RESULT, r_buf, read_buffer);
		if (ret < 0)
			goto err_i2c;

		for (j = 0; j < TX_NUM; j++) {
			raw_data = read_buffer[2*j] | (read_buffer[2*j+1] << 8);
			if (i == 0 && j == 0) {
				max_value = min_value = raw_data;
			} else {
				max_value = max(max_value, raw_data);
				min_value = min(min_value, raw_data);
			}

			if (cmd == MMS_VSC_CMD_CM_DELTA) {
				info->inspection[i * TX_NUM + j] =
					raw_data;
				dev_dbg(&info->client->dev,
					"[TSP] delta[%d][%d] = %d\n", j, i,
					info->inspection[i * TX_NUM + j]);
			} else if (cmd == MMS_VSC_CMD_CM_ABS) {
				info->raw[i * TX_NUM + j] =
					raw_data;
				dev_dbg(&info->client->dev,
					"[TSP] raw[%d][%d] = %d\n", j, i,
					info->raw[i * TX_NUM + j]);
			} else if (cmd == MMS_VSC_CMD_REFER) {
				info->reference[i * TX_NUM + j] =
					raw_data;
				dev_dbg(&info->client->dev,
					"[TSP] reference[%d][%d] = %d\n", j, i,
					info->reference[i * TX_NUM + j]);
			}
		}
	}

	ret = i2c_smbus_write_byte_data(info->client,
		ADDR_UNIV_CMD, CMD_EXIT_TEST);

	snprintf(buff, sizeof(buff), "%d,%d", min_value, max_value);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));

	touch_is_pressed = 0;
	release_all_fingers(info);

	mms_pwr_on_reset(info);
	info->enabled = true;


      printk("%s  ,   %d \n",__func__, __LINE__);
	if (info->ta_status) {
		dev_notice(&info->client->dev, "TA connect!!!\n");
		i2c_smbus_write_byte_data(info->client, 0x30, 0x1);
	} else {
		dev_notice(&info->client->dev, "TA disconnect!!!\n");
		i2c_smbus_write_byte_data(info->client, 0x30, 0x2);
	}
	// mms_set_noise_mode(info);

	enable_irq(info->irq);

	return;

err_i2c:
	dev_err(&info->client->dev, "%s: fail to i2c (cmd=%d)\n",
		__func__, cmd);
}

static void get_raw_data_all(struct mms_ts_info *info, u8 cmd)
{
	u8 w_buf[6];
	u8 read_buffer[2];	/* 52 */
	int ret;
	int i, j;
	u32 max_value = 0, min_value = 0;
	u32 raw_data;
	char buff[TSP_CMD_STR_LEN] = {0};
	int gpio = info->pdata->gpio_int;

/*      gpio = msm_irq_to_gpio(info->irq); */
	disable_irq(info->irq);

	w_buf[0] = MMS_VSC_CMD;	/* vendor specific command id */
	w_buf[1] = MMS_VSC_MODE;	/* mode of vendor */
	w_buf[2] = 0;		/* tx line */
	w_buf[3] = 0;		/* rx line */
	w_buf[4] = 0;		/* reserved */
	w_buf[5] = 0;		/* sub command */

	if (cmd == MMS_VSC_CMD_EXIT) {
		w_buf[5] = MMS_VSC_CMD_EXIT;	/* exit test mode */

		ret = i2c_smbus_write_i2c_block_data(info->client,
						     w_buf[0], 5, &w_buf[1]);
		if (ret < 0)
			goto err_i2c;
		enable_irq(info->irq);
		msleep(200);
		return;
	}

	/* MMS_VSC_CMD_CM_DELTA or MMS_VSC_CMD_CM_ABS
	 * this two mode need to enter the test mode
	 * exit command must be followed by testing.
	 */
	if (cmd == MMS_VSC_CMD_CM_DELTA || cmd == MMS_VSC_CMD_CM_ABS) {
		/* enter the debug mode */
		w_buf[2] = 0x0;	/* tx */
		w_buf[3] = 0x0;	/* rx */
		w_buf[5] = MMS_VSC_CMD_ENTER;

		ret = i2c_smbus_write_i2c_block_data(info->client,
						     w_buf[0], 5, &w_buf[1]);
		if (ret < 0)
			goto err_i2c;

		/* wating for the interrupt */
		while (gpio_get_value(gpio))
			udelay(100);
	}

	for (i = 0; i < RX_NUM; i++) {
		for (j = 0; j < TX_NUM; j++) {

			w_buf[2] = j;	/* tx */
			w_buf[3] = i;	/* rx */
			w_buf[5] = cmd;

			ret = i2c_smbus_write_i2c_block_data(info->client,
					w_buf[0], 5, &w_buf[1]);
			if (ret < 0)
				goto err_i2c;

			usleep_range(1, 5);

			ret = i2c_smbus_read_i2c_block_data(info->client, 0xBF,
							    2, read_buffer);
			if (ret < 0)
				goto err_i2c;

			raw_data = ((u16) read_buffer[1] << 8) | read_buffer[0];
			if (i == 0 && j == 0) {
				max_value = min_value = raw_data;
			} else {
				max_value = max(max_value, raw_data);
				min_value = min(min_value, raw_data);
			}

			if (cmd == MMS_VSC_CMD_INTENSITY) {
				info->intensity[i * TX_NUM + j] =
					raw_data;
				dev_dbg(&info->client->dev,
					"[TSP] intensity[%d][%d] = %d\n", j, i,
					info->intensity[i * TX_NUM + j]);
			} else if (cmd == MMS_VSC_CMD_CM_DELTA) {
				info->inspection[i * TX_NUM + j] =
					raw_data;
				dev_dbg(&info->client->dev,
					"[TSP] delta[%d][%d] = %d\n", j, i,
					info->inspection[i * TX_NUM + j]);
			} else if (cmd == MMS_VSC_CMD_CM_ABS) {
				info->raw[i * TX_NUM + j] =
					raw_data;
				dev_dbg(&info->client->dev,
					"[TSP] raw[%d][%d] = %d\n", j, i,
					info->raw[i * TX_NUM + j]);
			} else if (cmd == MMS_VSC_CMD_REFER) {
				info->reference[i * TX_NUM + j] =
					raw_data;
				dev_dbg(&info->client->dev,
					"[TSP] reference[%d][%d] = %d\n", j, i,
					info->reference[i * TX_NUM + j]);
			}
		}

	}

	snprintf(buff, sizeof(buff), "%d,%d", min_value, max_value);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));

	enable_irq(info->irq);

	return;

err_i2c:
	dev_err(&info->client->dev, "%s: fail to i2c (cmd=%d)\n",
		__func__, cmd);
}

static ssize_t show_close_tsp_test(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct mms_ts_info *info = dev_get_drvdata(dev);

	get_raw_data_all(info, MMS_VSC_CMD_EXIT);
	info->ft_flag = 0;

	return snprintf(buf, TSP_BUF_SIZE, "%u\n", 0);
}

static void set_default_result(struct mms_ts_info *info)
{
	char delim = ':';

	memset(info->cmd_result, 0x00, ARRAY_SIZE(info->cmd_result));
	memcpy(info->cmd_result, info->cmd, strlen(info->cmd));
	strncat(info->cmd_result, &delim, 1);
}

static int check_rx_tx_num(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[TSP_CMD_STR_LEN] = {0};
	int node;

	if (info->cmd_param[0] < 0 ||
			info->cmd_param[0] >= TX_NUM  ||
			info->cmd_param[1] < 0 ||
			info->cmd_param[1] >= RX_NUM) {
		snprintf(buff, sizeof(buff) , "%s", "NG");
		set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
		info->cmd_state = 3;

		dev_info(&info->client->dev, "%s: parameter error: %u,%u\n",
				__func__, info->cmd_param[0],
				info->cmd_param[1]);
		node = -1;
		return node;
}
	node = info->cmd_param[1] * TX_NUM + info->cmd_param[0];
	dev_info(&info->client->dev, "%s: node = %d\n", __func__,
			node);
	return node;

}

static void not_support_cmd(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;
	char buff[16] = {0};

	set_default_result(info);
	sprintf(buff, "%s", "NA");
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 4;
	dev_info(&info->client->dev, "%s: \"%s(%d)\"\n", __func__,
				buff, strnlen(buff, sizeof(buff)));
	return;
}

static int mms_ts_core_fw_load(struct mms_ts_info *info)
{
	struct i2c_client *client = info->client;
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	int ret;
	u8 fw_bin_ver = FW_VERSION;
	int retries = 3;
	const u8 *buff = 0;
	long fsize = 0;
	const struct firmware *tsp_fw = NULL;
	bool error = false;
	u8 ver;

	dev_info(&client->dev, "Entered REQ_FW\n");
	ret = request_firmware(&tsp_fw,
		"tsp_melfas/gd2/melfas.fw", &(client->dev));
	if (ret) {
		dev_err(&client->dev, "request firmware error!!\n");
		return 1;
	}
	dev_info(&client->dev,
		"fw_bin_ver = 0x%02x\n", fw_bin_ver);

	fsize = tsp_fw->size;
	buff = kzalloc((size_t)fsize, GFP_KERNEL);
	if (!buff) {
		dev_err(&client->dev, "fail to alloc buffer for fw\n");
		info->cmd_state = 3;
		release_firmware(tsp_fw);
		return 1;
	}

	memcpy((void *)buff, tsp_fw->data, fsize);
	release_firmware(tsp_fw);

	while (retries--) {
		if (error) {
			dev_err(&client->dev, "retry flashing\n");
			error = false;
		}
		i2c_lock_adapter(adapter);
		info->pdata->mux_fw_flash(true);

		ret = fw_download(info, (const u8 *)buff,
				(const size_t)fsize);

		info->pdata->mux_fw_flash(false);
		i2c_unlock_adapter(adapter);

		if (ret < 0) {
			dev_err(&client->dev, "fw_download fail\n");
			error = true;
			continue;
		}

		ver = get_fw_version(info, SEC_BOOTLOADER);
		if (ver != BOOT_VERSION) {
			dev_err(&client->dev, "boot version read fail\n");
			error = true;
			continue;
		}
		ver = get_fw_version(info, SEC_CORE);
		if (ver != CORE_VERSION) {
			dev_err(&client->dev, "core version read fail\n");
			error = true;
			continue;
		}
		info->fw_ic_ver = get_fw_version(info, SEC_CONFIG);
		if (info->fw_ic_ver != fw_bin_ver) {
			dev_err(&client->dev, "config version read fail\n");
			error = true;
			continue;
		}

		dev_info(&client->dev,
		  "ISP fw update done. ver = 0x%02x\n", info->fw_ic_ver);
		break;
	}
	if (error) {
		dev_err(&client->dev, "ERROR : fw update fail\n");
		kfree(buff);
		return 1;
	} else {
		dev_info(&client->dev, "fw update success\n");
		kfree(buff);
		return 0;
	}
}

static void fw_update(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;
	struct i2c_client *client = info->client;
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	int ret = 0;
	int ver = 0, fw_bin_ver=FW_VERSION, fw_core_ver=CORE_VERSION;
	int retries = 5;
	const u8 *buff = 0;
	mm_segment_t old_fs = {0};
	struct file *fp = NULL;
	long fsize = 0, nread = 0;
	const struct firmware *tsp_fw = NULL;
	char fw_path[MAX_FW_PATH+1];
	char result[16] = {0};

	set_default_result(info);
	dev_info(&client->dev,
		"fw_ic_ver = 0x%02x, fw_bin_ver = 0x%02x\n",info->fw_ic_ver, fw_bin_ver);
	dev_info(&client->dev,
		"core_ic_ver = 0x%02x, core_bin_ver = 0x%02x\n",info->fw_core_ver, fw_core_ver);
		

	if (info->cmd_param[0] == 0) {
		if (info->fw_core_ver > CORE_VERSION) {
			dev_info(&client->dev,
				"fw update does not need\n");
			info->cmd_state = 2;
			goto do_not_need_update;
		} else if (info->fw_core_ver == CORE_VERSION) {
			if (info->fw_ic_ver >= fw_bin_ver) {
				dev_info(&client->dev,
					"fw update does not need\n");
				info->cmd_state = 2;
				goto do_not_need_update;
			}
		} else { /* core < CORE_VERSION */
			dev_info(&client->dev,
				"fw update excute(core:0x%x)\n",
				info->fw_core_ver);
		}
	}

	switch (info->cmd_param[0]) {
	case BUILT_IN:
		dev_info(&client->dev, "built in fw is loaded!!\n");
		disable_irq(info->irq);

		ret = mms_ts_core_fw_load(info);

		ver = get_fw_version(info, SEC_CONFIG);
		info->fw_ic_ver = ver;
		if (ret == 0) {
			pr_err("[TSP] fw update success");
			info->cmd_state = 2;
		} else {
			pr_err("[TSP] fw update fail[%d]",
						ret);
			info->cmd_state = 3;
		}
		enable_irq(info->irq);
		return;
		break;

	case UMS:
		old_fs = get_fs();
		set_fs(get_ds());

		snprintf(fw_path, MAX_FW_PATH, "/sdcard/%s", TSP_FW_FILENAME);
		fp = filp_open(fw_path, O_RDONLY, 0);
		if (IS_ERR(fp)) {
			dev_err(&client->dev,
				"file %s open error:%d\n", fw_path, (s32)fp);
			info->cmd_state = 3;
			goto err_open;
		}

		fsize = fp->f_path.dentry->d_inode->i_size;

		buff = kzalloc((size_t)fsize, GFP_KERNEL);
		if (!buff) {
			dev_err(&client->dev, "fail to alloc buffer for fw\n");
			info->cmd_state = 3;
			goto err_alloc;
		}

		nread = vfs_read(fp, (char __user *)buff, fsize, &fp->f_pos);
		if (nread != fsize) {
			/*dev_err("fail to read file %s (nread = %d)\n",
					fw_path, nread);*/
			info->cmd_state = 3;
			goto err_fw_size;
		}

		filp_close(fp, current->files);
		set_fs(old_fs);
		dev_info(&client->dev, "ums fw is loaded!!\n");
		break;

	case REQ_FW:
		dev_info(&client->dev, "Entered REQ_FW case\n");
		ret = request_firmware(&tsp_fw, TSP_FW_FILENAME,
					&(client->dev));
		if (ret) {
			dev_err(&client->dev, "request firmware error!!\n");
			goto not_support;
		}

		fsize = tsp_fw->size;
		buff = kzalloc((size_t)fsize, GFP_KERNEL);
		if (!buff) {
			dev_err(&client->dev, "fail to alloc buffer for fw\n");
			info->cmd_state = 3;
			release_firmware(tsp_fw);
			goto not_support;
		}

		memcpy((void *)buff, tsp_fw->data, fsize);
		release_firmware(tsp_fw);
		break;

	default:
		dev_err(&client->dev, "invalid fw file type!!\n");
		goto not_support;
	}

	disable_irq(info->irq);
	while (retries--) {
		i2c_lock_adapter(adapter);
		info->pdata->mux_fw_flash(true);

		ret = fw_download(info, (const u8 *)buff,
				(const size_t)fsize);

		info->pdata->mux_fw_flash(false);
		i2c_unlock_adapter(adapter);

		if (ret < 0) {
			dev_err(&client->dev, "retry flashing\n");
			continue;
		}

		ver = get_fw_version(info, SEC_CONFIG);
		info->fw_ic_ver = ver;

		if (info->cmd_param[0] == 1 || info->cmd_param[0] == 2) {
			dev_info(&client->dev,
			  "fw update done. ver = 0x%02x\n", ver);
			info->cmd_state = 2;
			snprintf(result, sizeof(result) , "%s", "OK");
			set_cmd_result(info, result,
					strnlen(result, sizeof(result)));
			enable_irq(info->irq);
			kfree(buff);
			return;
		} else if (ver == fw_bin_ver) {
			dev_info(&client->dev,
			  "fw update done. ver = 0x%02x\n", ver);
			info->cmd_state = 2;
			snprintf(result, sizeof(result) , "%s", "OK");
			set_cmd_result(info, result,
					strnlen(result, sizeof(result)));
			enable_irq(info->irq);
			return;
		} else {
			dev_err(&client->dev,
					"ERROR : fw version is still wrong (0x%x != 0x%x)\n",
					ver, fw_bin_ver);
		}
		dev_err(&client->dev, "retry flashing\n");
	}

if (fp != NULL) {
err_fw_size:
	kfree(buff);
err_alloc:
	filp_close(fp, NULL);
err_open:
	set_fs(old_fs);
}
not_support:
do_not_need_update:
	snprintf(result, sizeof(result) , "%s", "NG");
	set_cmd_result(info, result, strnlen(result, sizeof(result)));
	return;
}


#if FLIP_COVER_TEST
static void flip_cover_enable(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	int status = 0;
	char buff[16] = {0};

	set_default_result(info);

	status = set_conifg_flip_cover(info, info->cmd_param[0]);

	dev_info(&info->client->dev, "%s: flip_cover %s %s.\n",
			__func__, info->cmd_param ? "enable" : "disable", status == 0 ? "successed" : "failed");

	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));

	info->cmd_state = 2;

	dev_info(&info->client->dev, "%s\n", __func__);
}

static int set_conifg_flip_cover(struct mms_ts_info *info,int enables)
{
    int retval = 0;

	if (enables) {

        retval = note_flip_open(info);

	} else {

        retval = note_flip_close(info);
	}

	return retval;
}
#define UNIVCMD_SET_CUSTOM_VALUE 0x80 //Use Custom value for flip cover defence
static int note_flip_open(struct mms_ts_info *info )
{
    int retval = 0;

	master_write_buf[0] = RMI_ADDR_UNIV_CMD;
	master_write_buf[1] = UNIVCMD_SET_CUSTOM_VALUE;
	master_write_buf[2] = 0; //Exciting CH.
	master_write_buf[3] = 0; //Sensing CH.

	
	printk("%s Enter\n", __func__);
	retval = i2c_smbus_write_i2c_block_data(info->client,master_write_buf[0], 4, &master_write_buf[1]);
	if(retval < 0)
	{
		printk( "open error\n", __func__);
		return -1;
	}
	return retval;
}

static int note_flip_close(struct mms_ts_info *info )
{
    int retval = 0;
	
	master_write_buf[0] = RMI_ADDR_UNIV_CMD;
	master_write_buf[1] = UNIVCMD_SET_CUSTOM_VALUE;
	master_write_buf[2] = 0; //Exciting CH.
	master_write_buf[3] = 1; //Sensing CH.

	
	printk("%s Enter\n", __func__);
	retval = i2c_smbus_write_i2c_block_data(info->client,master_write_buf[0], 4, &master_write_buf[1]);
	if(retval < 0)
	{
		printk( "close error\n", __func__);
		return -1;
	}
	return retval;
}
#endif


static void get_fw_ver_bin(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};

	//u8 bootloader_fw_ver = BOOT_VERSION;
	//u8 fw_core_ver = CORE_VERSION;
	//u8 fw_ic_ver = FW_VERSION;

	set_default_result(info);
	//snprintf(buff, sizeof(buff), "ME%02x%02x%02x", BOOT_VERSION, CORE_VERSION, FW_VERSION);
	snprintf(buff, sizeof(buff), "ME%02x%02x%02x", MODU_VERSION, CORE_VERSION, FW_VERSION);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;
	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__,
			buff, strnlen(buff, sizeof(buff)));
}

static void get_fw_ver_ic(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};
	//u8 bootloader_fw_ver=0;

	set_default_result(info);

	if (info->enabled) {
		info->fw_core_ver = get_fw_version(info, SEC_CORE);
		info->fw_ic_ver = get_fw_version(info, SEC_CONFIG);
		info->fw_module_ver = get_fw_version(info, SEC_MODULE);
	}
	
	//bootloader_fw_ver= get_fw_version(info, SEC_BOOTLOADER);
	
	//snprintf(buff, sizeof(buff), "ME%02x%02x%02x",
	//	bootloader_fw_ver, info->fw_core_ver, info->fw_ic_ver);
	snprintf(buff, sizeof(buff), "ME%02x%02x%02x", info->fw_module_ver, info->fw_core_ver, info->fw_ic_ver);

	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;
	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__,
			buff, strnlen(buff, sizeof(buff)));
}

static void get_config_ver(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[20] = {0};

	set_default_result(info);

	snprintf(buff, sizeof(buff), "G3588_ME_0124");

	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;
	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__,
			buff, strnlen(buff, sizeof(buff)));
}

static void get_threshold(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};
	int threshold;

	set_default_result(info);

	threshold = i2c_smbus_read_byte_data(info->client, 0x05);
	if (threshold < 0) {
		snprintf(buff, sizeof(buff), "%s", "NG");
		set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
		info->cmd_state = 3;
		return;
}
	snprintf(buff, sizeof(buff), "%d", threshold);

	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;
	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__,
			buff, strnlen(buff, sizeof(buff)));
}

static void module_off_master(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[3] = {0};

	//mms_ts_suspend(&info->client->dev);
	mms_ts_disable(info);

//	if (info->pdata->is_vdd_on() == 0)
		snprintf(buff, sizeof(buff), "%s", "OK");
//	else
//		snprintf(buff, sizeof(buff), "%s", "NG");

	set_default_result(info);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));

	if (strncmp(buff, "OK", 2) == 0)
		info->cmd_state = 2;
	else
		info->cmd_state = 3;

	info->cmd_is_running = false;

	dev_info(&info->client->dev, "%s: %s\n", __func__, buff);
}

static void module_on_master(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[3] = {0};

	//mms_ts_resume(&info->client->dev);
	mms_ts_enable(info);

//	if (info->pdata->is_vdd_on() == 1)
		snprintf(buff, sizeof(buff), "%s", "OK");
//	else
//		snprintf(buff, sizeof(buff), "%s", "NG");

	set_default_result(info);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));

	if (strncmp(buff, "OK", 2) == 0)
		info->cmd_state = 2;
	else
		info->cmd_state = 3;

	info->cmd_is_running = false;

	dev_info(&info->client->dev, "%s: %s\n", __func__, buff);

}
/*
static void module_off_slave(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	not_support_cmd(info);
}

static void module_on_slave(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	not_support_cmd(info);
}
*/
static void get_chip_vendor(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};

	set_default_result(info);

	snprintf(buff, sizeof(buff), "%s", "MELFAS");
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;
	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__,
			buff, strnlen(buff, sizeof(buff)));
}

static void get_chip_name(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};

	set_default_result(info);

	snprintf(buff, sizeof(buff), "%s", "MMS244");
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;
	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__,
			buff, strnlen(buff, sizeof(buff)));
}

static void get_reference(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};
	unsigned int val;
	int node;

	set_default_result(info);
	node = check_rx_tx_num(info);

	if (node < 0)
		return;

	val = info->reference[node];
	snprintf(buff, sizeof(buff), "%u", val);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));

	info->cmd_state = 2;

	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__,
			buff, strnlen(buff, sizeof(buff)));

}

static void get_cm_abs(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};
	unsigned int val;
	int node;

	set_default_result(info);
	node = check_rx_tx_num(info);

	if (node < 0)
		return;

	val = info->raw[node];
	snprintf(buff, sizeof(buff), "%u", val);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;

	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__, buff,
			strnlen(buff, sizeof(buff)));
}

static void get_cm_delta(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};
	unsigned int val;
	int node;

	set_default_result(info);
	node = check_rx_tx_num(info);

	if (node < 0)
		return;

	val = info->inspection[node];
	snprintf(buff, sizeof(buff), "%u", val);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;

	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__, buff,
			strnlen(buff, sizeof(buff)));
}

static void get_intensity(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};
	unsigned int val;
	int node;

	set_default_result(info);
	node = check_rx_tx_num(info);

	if (node < 0)
		return;

	val = info->intensity[node];

	snprintf(buff, sizeof(buff), "%u", val);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;

	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__, buff,
			strnlen(buff, sizeof(buff)));
}

static void get_x_num(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};
	int val;
	u8 r_buf[2];
	int ret;

	set_default_result(info);

	ret = i2c_smbus_read_i2c_block_data(info->client,
		ADDR_CH_NUM, 2, r_buf);
	val = r_buf[0];
	if (ret < 0) {
		snprintf(buff, sizeof(buff), "%s", "NG");
		set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
		info->cmd_state = 3;

			dev_info(&info->client->dev,
			"%s: fail to read num of x (%d).\n",
			__func__, val);
		return;
	}

	snprintf(buff, sizeof(buff), "%u", val);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;

	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__, buff,
			strnlen(buff, sizeof(buff)));
}

static void get_y_num(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	char buff[16] = {0};
	int val;
	u8 r_buf[2];
	int ret;

	set_default_result(info);

	ret = i2c_smbus_read_i2c_block_data(info->client,
		ADDR_CH_NUM, 2, r_buf);
	val = r_buf[1];
	if (ret < 0) {
		snprintf(buff, sizeof(buff), "%s", "NG");
		set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
		info->cmd_state = 3;
			
		dev_info(&info->client->dev,
			"%s: fail to read num of x (%d).\n",
			__func__, val);
		return;
	}

	snprintf(buff, sizeof(buff), "%u", val);
	set_cmd_result(info, buff, strnlen(buff, sizeof(buff)));
	info->cmd_state = 2;

	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__, buff,
			strnlen(buff, sizeof(buff)));
}

static void run_reference_read(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	set_default_result(info);
	get_raw_data(info, MMS_VSC_CMD_REFER);
	info->cmd_state = 2;

/*	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__); */
}

static void run_cm_abs_read(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	set_default_result(info);
	get_raw_data(info, MMS_VSC_CMD_CM_ABS);
	info->cmd_state = 2;

/*	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__); */
}

static void run_cm_delta_read(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	set_default_result(info);
	get_raw_data(info, MMS_VSC_CMD_CM_DELTA);
	info->cmd_state = 2;

/*	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__); */
}

static void run_intensity_read(void *device_data)
{
	struct mms_ts_info *info = (struct mms_ts_info *)device_data;

	set_default_result(info);
	get_intensity_data(info);
	info->cmd_state = 2;

/*	dev_info(&info->client->dev, "%s: %s(%d)\n", __func__); */
}

static ssize_t store_cmd(struct device *dev, struct device_attribute
				  *devattr, const char *buf, size_t count)
{
	struct mms_ts_info *info = dev_get_drvdata(dev);
	struct i2c_client *client = info->client;

	char *cur, *start, *end;
	char buff[TSP_CMD_STR_LEN] = {0};
	int len, i;
	struct tsp_cmd *tsp_cmd_ptr = NULL;
	char delim = ',';
	bool cmd_found = false;
	int param_cnt = 0;
	int ret;

	if (info->cmd_is_running == true) {
		dev_err(&info->client->dev, "tsp_cmd: other cmd is running.\n");
		goto err_out;
	}


	/* check lock  */
	mutex_lock(&info->cmd_lock);
	info->cmd_is_running = true;
	mutex_unlock(&info->cmd_lock);

	info->cmd_state = 1;

	for (i = 0; i < ARRAY_SIZE(info->cmd_param); i++)
		info->cmd_param[i] = 0;

	len = (int)count;
	if (*(buf + len - 1) == '\n')
		len--;
	memset(info->cmd, 0x00, ARRAY_SIZE(info->cmd));
	memcpy(info->cmd, buf, len);

	cur = strchr(buf, (int)delim);
	if (cur)
		memcpy(buff, buf, cur - buf);
	else
		memcpy(buff, buf, len);

	/* find command */
	list_for_each_entry(tsp_cmd_ptr, &info->cmd_list_head, list) {
		if (!strcmp(buff, tsp_cmd_ptr->cmd_name)) {
			cmd_found = true;
			break;
		}
	}

	/* set not_support_cmd */
	if (!cmd_found) {
		list_for_each_entry(tsp_cmd_ptr, &info->cmd_list_head, list) {
			if (!strcmp("not_support_cmd", tsp_cmd_ptr->cmd_name))
				break;
		}
	}

	/* parsing parameters */
	if (cur && cmd_found) {
		cur++;
		start = cur;
		memset(buff, 0x00, ARRAY_SIZE(buff));
		do {
			if (*cur == delim || cur - buf == len) {
				end = cur;
				memcpy(buff, start, end - start);
				*(buff + strlen(buff)) = '\0';
				ret = kstrtoint(buff, 10,\
						info->cmd_param + param_cnt);
				start = cur + 1;
				memset(buff, 0x00, ARRAY_SIZE(buff));
				param_cnt++;
			}
			cur++;
		} while (cur - buf <= len);
	}

	dev_info(&client->dev, "cmd = %s\n", tsp_cmd_ptr->cmd_name);
	for (i = 0; i < param_cnt; i++)
		dev_info(&client->dev, "cmd param %d= %d\n", i,
							info->cmd_param[i]);

	tsp_cmd_ptr->cmd_func(info);


err_out:
	return count;
}

static ssize_t show_cmd_status(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	struct mms_ts_info *info = dev_get_drvdata(dev);
	char buff[16] = {0};

	dev_info(&info->client->dev, "tsp cmd: status:%d\n",
			info->cmd_state);

	if (info->cmd_state == 0)
		snprintf(buff, sizeof(buff), "WAITING");

	else if (info->cmd_state == 1)
		snprintf(buff, sizeof(buff), "RUNNING");

	else if (info->cmd_state == 2)
		snprintf(buff, sizeof(buff), "OK");

	else if (info->cmd_state == 3)
		snprintf(buff, sizeof(buff), "FAIL");

	else if (info->cmd_state == 4)
		snprintf(buff, sizeof(buff), "NOT_APPLICABLE");

	return snprintf(buf, TSP_BUF_SIZE, "%s\n", buff);
}

static ssize_t show_cmd_result(struct device *dev, struct device_attribute
				    *devattr, char *buf)
{
	struct mms_ts_info *info = dev_get_drvdata(dev);

	dev_info(&info->client->dev, "tsp cmd: result: %s\n", info->cmd_result);

	mutex_lock(&info->cmd_lock);
	info->cmd_is_running = false;
	mutex_unlock(&info->cmd_lock);

	info->cmd_state = 0;

	return snprintf(buf, TSP_BUF_SIZE, "%s\n", info->cmd_result);
}

#ifdef ESD_DEBUG

static bool intensity_log_flag;

static u32 get_raw_data_one(struct mms_ts_info *info, u16 rx_idx, u16 tx_idx,
			    u8 cmd)
{
	u8 w_buf[6];
	u8 read_buffer[2];
	int ret;
	u32 raw_data;

	w_buf[0] = MMS_VSC_CMD;	/* vendor specific command id */
	w_buf[1] = MMS_VSC_MODE;	/* mode of vendor */
	w_buf[2] = 0;		/* tx line */
	w_buf[3] = 0;		/* rx line */
	w_buf[4] = 0;		/* reserved */
	w_buf[5] = 0;		/* sub command */

	if (cmd != MMS_VSC_CMD_INTENSITY && cmd != MMS_VSC_CMD_RAW &&
	    cmd != MMS_VSC_CMD_REFER) {
		dev_err(&info->client->dev, "%s: not profer command(cmd=%d)\n",
			__func__, cmd);
		return FAIL;
	}

	w_buf[2] = tx_idx;	/* tx */
	w_buf[3] = rx_idx;	/* rx */
	w_buf[5] = cmd;		/* sub command */

	ret = i2c_smbus_write_i2c_block_data(info->client, w_buf[0], 5,
					     &w_buf[1]);
	if (ret < 0)
		goto err_i2c;

	ret = i2c_smbus_read_i2c_block_data(info->client, 0xBF, 2, read_buffer);
	if (ret < 0)
		goto err_i2c;

	raw_data = ((u16) read_buffer[1] << 8) | read_buffer[0];
	if (cmd == MMS_VSC_CMD_REFER)
		raw_data = raw_data >> 4;

	return raw_data;

err_i2c:
	dev_err(&info->client->dev, "%s: fail to i2c (cmd=%d)\n",
		__func__, cmd);
	return FAIL;
}

static ssize_t show_intensity_logging_on(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	struct mms_ts_info *info = dev_get_drvdata(dev);
	struct i2c_client *client = info->client;
	struct file *fp;
	char log_data[160] = { 0, };
	char buff[16] = { 0, };
	mm_segment_t old_fs;
	long nwrite;
	u32 val;
	int i, y, c;

	old_fs = get_fs();
	set_fs(KERNEL_DS);

#define MELFAS_DEBUG_LOG_PATH "/sdcard/melfas_log"

	dev_info(&client->dev, "%s: start.\n", __func__);
	fp = filp_open(MELFAS_DEBUG_LOG_PATH, O_RDWR | O_CREAT,
		       S_IRWXU | S_IRWXG | S_IRWXO);
	if (IS_ERR(fp)) {
		dev_err(&client->dev, "%s: fail to open log file\n", __func__);
		goto open_err;
	}

	intensity_log_flag = 1;
	do {
		for (y = 0; y < 3; y++) {
			/* for tx chanel 0~2 */
			memset(log_data, 0x00, 160);

			snprintf(buff, 16, "%1u: ", y);
			strncat(log_data, buff, strnlen(buff, 16));

			for (i = 0; i < RX_NUM; i++) {
				val = get_raw_data_one(info, i, y,
						       MMS_VSC_CMD_INTENSITY);
				snprintf(buff, 16, "%5u, ", val);
				strncat(log_data, buff, strnlen(buff, 16));
			}
			memset(buff, '\n', 2);
			c = (y == 2) ? 2 : 1;
			strncat(log_data, buff, c);
			nwrite = vfs_write(fp, (const char __user *)log_data,
					   strnlen(log_data, 160), &fp->f_pos);
		}
		usleep_range(3000, 5000);
	} while (intensity_log_flag);

	filp_close(fp, current->files);
	set_fs(old_fs);

	return 0;

open_err:
	set_fs(old_fs);
	return FAIL;
}

static ssize_t show_intensity_logging_off(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	struct mms_ts_info *info = dev_get_drvdata(dev);
	intensity_log_flag = 0;
	usleep_range(10000, 12000);
	get_raw_data_all(info, MMS_VSC_CMD_EXIT);
	return 0;
}

#endif

static DEVICE_ATTR(close_tsp_test, S_IRUGO, show_close_tsp_test, NULL);
static DEVICE_ATTR(cmd, S_IWUSR | S_IWGRP, NULL, store_cmd);
static DEVICE_ATTR(cmd_status, S_IRUGO, show_cmd_status, NULL);
static DEVICE_ATTR(cmd_result, S_IRUGO, show_cmd_result, NULL);
#ifdef ESD_DEBUG
static DEVICE_ATTR(intensity_logging_on, S_IRUGO, show_intensity_logging_on,
		   NULL);
static DEVICE_ATTR(intensity_logging_off, S_IRUGO, show_intensity_logging_off,
		   NULL);
#endif

static struct attribute *sec_touch_facotry_attributes[] = {
	&dev_attr_close_tsp_test.attr,
	&dev_attr_cmd.attr,
	&dev_attr_cmd_status.attr,
	&dev_attr_cmd_result.attr,
#ifdef ESD_DEBUG
	&dev_attr_intensity_logging_on.attr,
	&dev_attr_intensity_logging_off.attr,
#endif
	NULL,
};

static struct attribute_group sec_touch_factory_attr_group = {
	.attrs = sec_touch_facotry_attributes,
};
#endif /* SEC_TSP_FACTORY_TEST */


#ifdef CONFIG_OF
static void melfas_request_gpio(struct mms_ts_platform_data *pdata)
{
	int ret;
	pr_info("[TSP] request gpio\n");

	ret = gpio_request(pdata->gpio_scl, "melfas_tsp_scl");
	if (ret) {
		pr_err("[TSP]%s: unable to request melfas_tsp_scl [%d]\n",
				__func__, pdata->gpio_scl);
		return;
	}

	ret = gpio_request(pdata->gpio_sda, "melfas_tsp_sda");
	if (ret) {
		pr_err("[TSP]%s: unable to request melfas_tsp_sda [%d]\n",
				__func__, pdata->gpio_sda);
		return;
	}

	ret = gpio_request(pdata->gpio_int, "melfas_tsp_irq");
	if (ret) {
		pr_err("[TSP]%s: unable to request melfas_tsp_irq [%d]\n",
				__func__, pdata->gpio_int);
		return;
	}
	ret = gpio_request(pdata->vdd_en, "melfas_vdd_en");
	if (ret) {
		pr_err("[TSP]%s: unable to request melfas_vdd_en [%d]\n",
				__func__, pdata->vdd_en);
		return;
	}
}



static int mms_get_dt_coords(struct device *dev, char *name,
				struct mms_ts_platform_data *pdata)
{
	u32 coords[MMS_COORDS_ARR_SIZE];
	struct property *prop;
	struct device_node *np = dev->of_node;
	int coords_size, rc;

	prop = of_find_property(np, name, NULL);
	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;

	coords_size = prop->length / sizeof(u32);
	if (coords_size != MMS_COORDS_ARR_SIZE) {
		dev_err(dev, "invalid %s\n", name);
		return -EINVAL;
	}

	rc = of_property_read_u32_array(np, name, coords, coords_size);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read %s\n", name);
		return rc;
	}

	if (strncmp(name, "melfas,panel-coords",
			sizeof("melfas,panel-coords")) == 0) {
		pdata->invert_x = coords[0];
		pdata->invert_y = coords[1];
		pdata->max_x = coords[2];
		pdata->max_y = coords[3];
	} else {
		dev_err(dev, "unsupported property %s\n", name);
		return -EINVAL;
	}

	return 0;
}

static int mms_parse_dt(struct device *dev,
			struct mms_ts_platform_data *pdata)
{
	int rc;
	struct device_node *np = dev->of_node;

	rc = mms_get_dt_coords(dev, "melfas,panel-coords", pdata);
	if (rc)
		return rc;

	/* regulator info */
	pdata->i2c_pull_up = of_property_read_bool(np, "melfas,i2c-pull-up");
	pdata->vdd_en = of_get_named_gpio(np, "vdd_en-gpio", 0);

	/* reset, irq gpio info */
	pdata->gpio_scl = of_get_named_gpio_flags(np, "melfas,scl-gpio",
				0, &pdata->scl_gpio_flags);
	pdata->gpio_sda = of_get_named_gpio_flags(np, "melfas,sda-gpio",
				0, &pdata->sda_gpio_flags);
	pdata->gpio_int = of_get_named_gpio_flags(np, "melfas,irq-gpio",
				0, &pdata->irq_gpio_flags);
//data->config_fw_version = of_get_property(np,
//		"melfas,config_fw_version", NULL);
	return 0;
}
#else
static int mms_parse_dt(struct device *dev,
			struct mms_ts_platform_data *pdata)
{
	return -ENODEV;
}
#endif


int __devinit mms_ts_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct mms_ts_platform_data *pdata;
	struct mms_ts_info *info;
	struct input_dev *input_dev;
	int ret = 0;
	int error;

	#ifdef SEC_TSP_FACTORY_TEST
	int i;
	struct device *fac_dev_ts;
	#endif

	printk("%s +++ %d\n",__func__,__LINE__);
	if (!i2c_check_functionality(adapter, I2C_FUNC_I2C))
		return -EIO;
#ifdef CONFIG_OF
	if (client->dev.of_node) {
		pdata = devm_kzalloc(&client->dev,
			sizeof(struct mms_ts_platform_data), GFP_KERNEL);
		if (!pdata) {
			dev_err(&client->dev, "Failed to allocate memory\n");
			return -ENOMEM;
		}

		error = mms_parse_dt(&client->dev, pdata);
		if (error)
			return error;
	} else
		pdata = client->dev.platform_data;

	if (!pdata)
		return -EINVAL;

	melfas_request_gpio(pdata);
#endif
	info = kzalloc(sizeof(struct mms_ts_info), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!info || !input_dev) {
		dev_err(&client->dev, " Failed to allocate memory\n");
		return -ENOMEM;
	}

	info->client = client;
	info->input_dev = input_dev;
	//info->pdata = client->dev.platform_data;
	//init_completion(&info->init_done);
	info->irq = -1;
	//mutex_init(&info->lock);
	info->pdata = pdata;

	info->max_x = info->pdata->max_x;
	info->max_y = info->pdata->max_y;

	melfas_vdd_on(info, 1);
	msleep(100);

	input_mt_init_slots(input_dev, MAX_FINGER_NUM);

//	snprintf(info->phys, sizeof(info->phys),
//		"%s/input0", dev_name(&client->dev));
	
	input_dev->name = "sec_touchscreen";//"Melfas MMSxxx Touchscreen";
	input_dev->phys = info->phys;
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;
	input_dev->open = mms_ts_input_open;
	input_dev->close = mms_ts_input_close;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(INPUT_PROP_DIRECT, input_dev->propbit);

	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, MAX_WIDTH, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_PRESSURE, 0, MAX_PRESSURE, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0, info->max_x, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0, info->max_y, 0, 0);

	input_set_drvdata(input_dev, info);

#if MMS_HAS_TOUCH_KEY
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(KEY_MENU, input_dev->keybit);
	__set_bit(KEY_BACK, input_dev->keybit);
#endif

	ret = input_register_device(input_dev);
	if (ret) {
		dev_err(&client->dev, "failed to register input dev\n");
		return -EIO;
	}

	i2c_set_clientdata(client, info);

	mms_ts_config(info);

	mms_reboot(info);
	esd_cnt = 0;

	enable_irq(info->irq);

#ifdef CONFIG_HAS_EARLYSUSPEND
	info->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN +1;
	info->early_suspend.suspend = mms_ts_early_suspend;
	info->early_suspend.resume = mms_ts_late_resume;
	register_early_suspend(&info->early_suspend);
#endif

	if (alloc_chrdev_region(&info->mms_dev, 0, 1, "mms_ts")) {
		dev_err(&client->dev, "failed to allocated device region\n");
		return -ENOMEM;
	}

	info->class = class_create(THIS_MODULE, "mms_ts");

	cdev_init(&info->cdev, &mms_fops);
	info->cdev.owner = THIS_MODULE;

	if (cdev_add(&info->cdev, info->mms_dev, 1)) {
		dev_err(&client->dev, "failed to add ch dev\n");
		return -EIO;
	}

	sec_touchscreen = device_create(sec_class,
					NULL, 0, info, "sec_touchscreen");
	if (IS_ERR(sec_touchscreen)) {
		dev_err(&client->dev,
			"Failed to create device for the sysfs1\n");
		ret = -ENODEV;
	}
	

#ifdef SEC_TSP_INFO_SHOW
	
	sec_touchkey =
	device_create(sec_class, NULL, 0, info, "sec_touchkey");

	if (device_create_file(sec_touchscreen, &dev_attr_tsp_firm_update) < 0)
		pr_err("[TSP] Failed to create device file(%s)!\n",dev_attr_tsp_firm_update.attr.name);

	if (device_create_file
		(sec_touchscreen, &dev_attr_tsp_firm_update_status) < 0)
		pr_err("Failed to create device file(%s)!\n",
			   dev_attr_tsp_firm_update_status.attr.name);

	if (device_create_file(sec_touchscreen, &dev_attr_tsp_threshold) < 0)
		pr_err("Failed to create device file(%s)!\n",
			   dev_attr_tsp_threshold.attr.name);

	if (device_create_file
		(sec_touchscreen, &dev_attr_tsp_firm_version_phone) < 0)
		pr_err("Failed to create device file(%s)!\n",
			   dev_attr_tsp_firm_version_phone.attr.name);

	if (device_create_file
		(sec_touchscreen, &dev_attr_tsp_firm_version_panel) < 0)
		pr_err("Failed to create device file(%s)!\n",
			   dev_attr_tsp_firm_version_panel.attr.name);

	if (device_create_file(sec_touchscreen, &dev_attr_tsp_config_version) <
		0)
		pr_err("Failed to create device file(%s)!\n",
			   dev_attr_tsp_config_version.attr.name);

	if (device_create_file(sec_touchscreen, &dev_attr_tsp_touchtype) < 0)
		pr_err("Failed to create device file(%s)!\n",
			   dev_attr_tsp_touchtype.attr.name);

	  if (device_create_file(sec_touchkey, &dev_attr_touchkey_menu) < 0)
		pr_err("Failed to create device file(%s)!\n", dev_attr_touchkey_menu.attr.name);
	if (device_create_file(sec_touchkey, &dev_attr_touchkey_back) < 0)
		pr_err("Failed to create device file(%s)!\n", dev_attr_touchkey_back.attr.name);
//	if (device_create_file(sec_touchkey, &dev_attr_touchkey_home) < 0)
//		pr_err("Failed to create device file(%s)!\n", dev_attr_touchkey_home.attr.name);
	  if (device_create_file(sec_touchkey, &dev_attr_touchkey_threshold) < 0)
		pr_err("Failed to create device file(%s)!\n", dev_attr_touchkey_threshold.attr.name);
	
#endif

	device_create(info->class, NULL, info->mms_dev, NULL, "mms_ts");

	if(sysfs_create_bin_file(&client->dev.kobj ,&bin_attr)){
		dev_err(&client->dev, "failed to create sysfs symlink\n");
		return -EAGAIN;
	}

	if(sysfs_create_bin_file(&client->dev.kobj ,&bin_attr_data)){
		dev_err(&client->dev, "failed to create sysfs symlink\n");
		return -EAGAIN;
	}

	if (sysfs_create_link(NULL, &client->dev.kobj, "mms_ts")) {
		dev_err(&client->dev, "failed to create sysfs symlink\n");
		return -EAGAIN;
	}

#ifdef __MMS_TEST_MODE__
	if (sysfs_create_group(&client->dev.kobj, &mms_attr_group)) {
		dev_err(&client->dev, "failed to create sysfs group\n");
		return -EAGAIN;
	}
	test.get_data = kzalloc(4096, GFP_KERNEL);
	test.client = client;
	test.pdata = info->pdata;
	test.tx_num = info->tx_num;
	test.rx_num = info->rx_num;
	test.key_num = info->key_num;
	test.irq = info->irq;
#endif

#ifdef SEC_TSP_FACTORY_TEST
			INIT_LIST_HEAD(&info->cmd_list_head);
			for (i = 0; i < ARRAY_SIZE(tsp_cmds); i++)
				list_add_tail(&tsp_cmds[i].list, &info->cmd_list_head);
	
			mutex_init(&info->cmd_lock);
			info->cmd_is_running = false;
	
		fac_dev_ts = device_create(sec_class,
				NULL, 0, info, "tsp");
		if (IS_ERR(fac_dev_ts))
			dev_err(&client->dev, "Failed to create device for the sysfs\n");
	
		ret = sysfs_create_group(&fac_dev_ts->kobj,
					 &sec_touch_factory_attr_group);
		if (ret)
			dev_err(&client->dev, "Failed to create sysfs group\n");
#endif

	info->log = kzalloc(sizeof(struct mms_log_data), GFP_KERNEL);
	info->fw_name = kstrdup("mms_fw", GFP_KERNEL);

	dev_notice(&client->dev, "mms dev initialized\n");
	printk("%s --- %d\n",__func__,__LINE__);
	return 0;
}

static int __devexit mms_ts_remove(struct i2c_client *client)
{
	struct mms_ts_info *info = i2c_get_clientdata(client);

	if (info->irq >= 0)
		free_irq(info->irq, info);

#ifdef __MMS_TEST_MODE__
	sysfs_remove_group(&info->client->dev.kobj, &mms_attr_group);
	kfree(test.get_data);
#endif		
	sysfs_remove_link(NULL, "mms_ts");
	sysfs_remove_bin_file(&client->dev.kobj, &bin_attr);
	sysfs_remove_bin_file(&client->dev.kobj, &bin_attr_data);
	input_unregister_device(info->input_dev);
	unregister_early_suspend(&info->early_suspend);
	class_destroy(info->class);
	device_destroy(info->class, info->mms_dev);
	
	kfree(info->log);
	kfree(info->fw_name);
	kfree(info);

	return 0;
}

#if (defined(CONFIG_PM) || defined(CONFIG_HAS_EARLYSUSPEND)) && !defined(USE_OPEN_CLOSE)
static int mms_ts_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct mms_ts_info *info = i2c_get_clientdata(client);

	mutex_lock(&info->input_dev->mutex);
	if (!info->input_dev->users)
		goto out;

	mms_ts_disable(info);
	mms_clear_input_data(info);

out:
	mutex_unlock(&info->input_dev->mutex);
	return 0;

}

static int mms_ts_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct mms_ts_info *info = i2c_get_clientdata(client);
	int ret = 0;

	mutex_lock(&info->input_dev->mutex);
	if (info->input_dev->users)
		ret = mms_ts_enable(info);
	mutex_unlock(&info->input_dev->mutex);

	return ret;
}
#endif

#if defined(CONFIG_HAS_EARLYSUSPEND)  && !defined(USE_OPEN_CLOSE)
static void mms_ts_early_suspend(struct early_suspend *h)
{
	struct mms_ts_info *info;
	info = container_of(h, struct mms_ts_info, early_suspend);
	mms_ts_suspend(&info->client->dev);
}

static void mms_ts_late_resume(struct early_suspend *h)
{
	struct mms_ts_info *info;
	info = container_of(h, struct mms_ts_info, early_suspend);
	mms_ts_resume(&info->client->dev);
}
#endif

#if defined(CONFIG_PM) && !defined(CONFIG_HAS_EARLYSUSPEND) && !defined(USE_OPEN_CLOSE)
static const struct dev_pm_ops mms_ts_pm_ops = {
	.suspend	= mms_ts_suspend,
	.resume		= mms_ts_resume,
};
#endif

static const struct i2c_device_id mms_ts_id[] = {
	{MELFAS_TS_NAME, 0},
	{ }
};
MODULE_DEVICE_TABLE(i2c, mms_ts_id);

#ifdef CONFIG_OF
static struct of_device_id mms_match_table[] = {
	{ .compatible = "melfas,mms-ts",},
	{ },
};
#else
#define mms_match_table NULL
#endif

static struct i2c_driver mms_ts_driver = {
	.probe		= mms_ts_probe,
	.remove		= __devexit_p(mms_ts_remove),
	.driver		= {
				.name 	= MELFAS_TS_NAME,
#ifdef CONFIG_OF
		   .of_match_table = mms_match_table,
#endif
#if defined(CONFIG_PM) && !defined(CONFIG_HAS_EARLYSUSPEND) && !defined(USE_OPEN_CLOSE)
				.pm	= &mms_ts_pm_ops,
#endif
	},
	.id_table	= mms_ts_id,
};

static int __init mms_ts_init(void)
{
	return i2c_add_driver(&mms_ts_driver);
}

static void __exit mms_ts_exit(void)
{
	i2c_del_driver(&mms_ts_driver);
}

module_init(mms_ts_init);
module_exit(mms_ts_exit);

MODULE_VERSION("1.1.1");
MODULE_DESCRIPTION("Touchscreen driver for MELFAS MMS-series");
MODULE_LICENSE("GPL");

