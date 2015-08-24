/*
 * max77804k-muic.c - MUIC driver for the Maxim 77804k
 *
 *  Copyright (C) 2012 Samsung Electronics.
 *  <sukdong.kim@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/workqueue.h>
#include <linux/input.h>
#include <linux/mfd/max77804k.h>
#include <linux/mfd/max77804k-private.h>
#ifdef CONFIG_USB_HOST_NOTIFY
#include <linux/host_notify.h>
#endif
#include <linux/wakelock.h>
#include <linux/switch.h>
#ifdef CONFIG_USBHUB_USB3804k
#include <linux/usb3804k.h>
#endif
#include <linux/delay.h>
#include <linux/extcon.h>
#if defined(CONFIG_SWITCH_DUAL_MODEM)
#include <linux/sec_param.h>
#endif

#define DEV_NAME	"max77804k-muic"

#if defined(CONFIG_CHARGER_SMB1357)
extern int smb1357_otg_control(int enable);
#endif

/* for providing API */
static struct max77804k_muic_info *gInfo;

/* For restore charger interrupt states */
static u8 chg_int_state;

/* MAX77804K MUIC CHG_TYP setting values */
enum {
	/* No Valid voltage at VB (Vvb < Vvbdet) */
	CHGTYP_NO_VOLTAGE	= 0x00,
	/* Unknown (D+/D- does not present a valid USB charger signature) */
	CHGTYP_USB		= 0x01,
	/* Charging Downstream Port */
	CHGTYP_DOWNSTREAM_PORT	= 0x02,
	/* Dedicated Charger (D+/D- shorted) */
	CHGTYP_DEDICATED_CHGR	= 0x03,
	/* Special 500mA charger, max current 500mA */
	CHGTYP_500MA		= 0x04,
	/* Special 1A charger, max current 1A */
	CHGTYP_1A		= 0x05,
	/* Reserved for Future Use */
	CHGTYP_RFU		= 0x06,
	/* Dead Battery Charging, max current 100mA */
	CHGTYP_DB_100MA		= 0x07,
	CHGTYP_MAX,

	CHGTYP_INIT,
	CHGTYP_MIN = CHGTYP_NO_VOLTAGE
};

#define CHGTYP (CHGTYP_USB | CHGTYP_DOWNSTREAM_PORT |\
CHGTYP_DEDICATED_CHGR | CHGTYP_500MA | CHGTYP_1A)

enum {
	ADC_GND			= 0x00,
	ADC_MHL			= 0x01,
	ADC_INCOMPATIBLE1_CHG	= 0x08, /* 0x01000 10.0K ohm*/
	ADC_VZW_USB_DOCK	= 0x0e, /* 0x01110 28.7K ohm VZW Dock */
	ADC_SMARTDOCK		= 0x10, /* 0x10000 40.2K ohm */
#if defined(CONFIG_MUIC_MAX77804K_SUPPORT_HMT_DETECTION)
	ADC_HMT			= 0x11, /* 0x10001 49.9K ohm */
#else
	ADC_INCOMPATIBLE2_CHG	= 0x11, /* 0x10001 49.9K ohm */
#endif
	ADC_AUDIODOCK		= 0x12, /* 0x10010 64.9K ohm */
	ADC_CHARGING_CABLE		= 0x14, /* 0x10100 102K ohm */
	ADC_CEA936ATYPE1_CHG	= 0x17,	/* 0x10111 200K ohm */
	ADC_JIG_USB_OFF		= 0x18, /* 0x11000 255K ohm */
	ADC_JIG_USB_ON		= 0x19, /* 0x11001 301K ohm */
	ADC_DESKDOCK		= 0x1a, /* 0x11010 365K ohm */
	ADC_CEA936ATYPE2_CHG	= 0x1b, /* 0x11011 442K ohm */
	ADC_JIG_UART_OFF	= 0x1c, /* 0x11100 523K ohm */
	ADC_JIG_UART_ON		= 0x1d, /* 0x11101 619K ohm */
	ADC_CARDOCK		= 0x1d, /* 0x11101 619K ohm */
	ADC_OPEN		= 0x1f
};

struct max77804k_muic_info {
	struct device		*dev;
	struct max77804k_dev	*max77804k;
	struct i2c_client	*muic;
	struct max77804k_muic_data *muic_data;
	struct extcon_dev		*edev;
	int			irq_adc;
	int			irq_vbvolt;
	int			irq_chgtype;
	int			mansw;
	int			path;
	int			otg_test;
	u8			adc_mode;

	struct wake_lock muic_wake_lock;

	enum cable_type_muic	cable_type;
	enum extcon_cable_name	cable_name;
	struct delayed_work	init_work;
	struct mutex		mutex;
#if !defined(CONFIG_MUIC_MAX77804K_SUPPORT_CAR_DOCK)
	bool			is_factory_start;
#endif /* !CONFIG_MUIC_MAX77804K_SUPORT_CAR_DOCK */

	u8		adc;
	u8		chgtyp;
	u8		vbvolt;
	bool			is_adc_open_prev;
};

static const char const *max77804k_path_name[] = {
	[PATH_OPEN]	= "OPEN",
	[PATH_USB_AP]	= "USB-AP",
	[PATH_AUDIO]	= "AUDIO",
	[PATH_UART_AP]	= "UART-AP",
	[PATH_USB_CP]	= "USB-CP",
	[PATH_UART_CP]	= "UART-CP",
	NULL,
};

static struct switch_dev switch_uart3 = {
	.name = "uart3",	/* /sys/class/switch/uart3/state */
};

static int if_muic_info;
static int switch_sel;
static int if_pmic_rev;

int is_cardock;
static bool is_lpm_mode;
EXPORT_SYMBOL(is_cardock);

void max77804k_update_jig_state(struct max77804k_muic_info *info);

/* func : get_if_pmic_inifo
 * switch_sel value get from bootloader comand line
 * switch_sel data consist 8 bits (xxxxzzzz)
 * first 4bits(zzzz) mean path infomation.
 * next 4bits(xxxx) mean if pmic version info
 */
static int get_if_pmic_inifo(char *str)
{
	get_option(&str, &if_muic_info);
	switch_sel = if_muic_info & 0x0f;
	if_pmic_rev = (if_muic_info & 0xf0) >> 4;
	pr_info("%s %s: switch_sel: %x if_pmic_rev:%x\n",
		__FILE__, __func__, switch_sel, if_pmic_rev);
	return if_muic_info;
}
__setup("pmic_info=", get_if_pmic_inifo);

int get_switch_sel(void)
{
	return switch_sel;
}

static int max77804k_muic_set_comp2_comn1_pass2
	(struct max77804k_muic_info *info, int type, int path)
{
	/* type 0 == usb, type 1 == uart */
	u8 cntl1_val, cntl1_msk;
	int ret = 0;
	int val;

	dev_info(info->dev, "func: %s type: %d path: %d\n",
		__func__, type, path);
	if (type == 0) {
		if (path == PATH_USB_AP) {
			info->muic_data->usb_sel = PATH_USB_AP;
			val = MAX77804K_MUIC_CTRL1_BIN_1_001;
		} else if (path == PATH_USB_CP) {
			info->muic_data->usb_sel = PATH_USB_CP;
			val = MAX77804K_MUIC_CTRL1_BIN_4_100;
		} else {
			dev_err(info->dev, "func: %s invalid usb path\n"
				, __func__);
			return -EINVAL;
		}
	} else if (type == 1) {
		if (path == PATH_UART_AP) {
			info->muic_data->uart_sel = PATH_UART_AP;
			val = MAX77804K_MUIC_CTRL1_BIN_3_011;
		} else if (path == PATH_UART_CP) {
			info->muic_data->uart_sel = PATH_UART_CP;
			val = MAX77804K_MUIC_CTRL1_BIN_5_101;
		} else {
			dev_err(info->dev, "func: %s invalid uart path\n"
				, __func__);
			return -EINVAL;
		}
	}
	else {
		dev_err(info->dev, "func: %s invalid path type(%d)\n"
			, __func__, type);
		return -EINVAL;
	}

	cntl1_val = (val << COMN1SW_SHIFT) | (val << COMP2SW_SHIFT);
	cntl1_msk = COMN1SW_MASK | COMP2SW_MASK;

	max77804k_update_reg(info->muic, MAX77804K_MUIC_REG_CTRL1, cntl1_val,
			    cntl1_msk);

	return ret;
}

static int max77804k_muic_set_uart_sel_pass2
	(struct max77804k_muic_info *info, int path)
{
	int ret = 0;
	ret = max77804k_muic_set_comp2_comn1_pass2(info, 1/*uart*/, path);
	return ret;

}

static ssize_t max77804k_muic_show_usb_state(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	dev_info(info->dev, "func:%s info->cable_name:%d\n",
		 __func__, info->cable_name);
	switch (info->cable_name) {
	case EXTCON_USB:
	case EXTCON_JIG_USBOFF:
	case EXTCON_JIG_USBON:
		return sprintf(buf, "USB_STATE_CONFIGURED\n");
	default:
		break;
	}

	return sprintf(buf, "USB_STATE_NOTCONFIGURED\n");
}

static ssize_t max77804k_muic_show_device(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	dev_info(info->dev, "func:%s info->cable_type:%d\n",
		 __func__, info->cable_type);

	switch (info->cable_type) {
	case CABLE_TYPE_NONE_MUIC:
		return sprintf(buf, "No cable\n");
	case CABLE_TYPE_USB_MUIC:
		return sprintf(buf, "USB\n");
	case CABLE_TYPE_OTG_MUIC:
		return sprintf(buf, "OTG\n");
	case CABLE_TYPE_TA_MUIC:
		return sprintf(buf, "TA\n");
	case CABLE_TYPE_DESKDOCK_MUIC:
		return sprintf(buf, "Desk Dock\n");
	case CABLE_TYPE_SMARTDOCK_MUIC:
		return sprintf(buf, "Smart Dock\n");
	case CABLE_TYPE_SMARTDOCK_TA_MUIC:
		return sprintf(buf, "Smart Dock with TA\n");
	case CABLE_TYPE_SMARTDOCK_USB_MUIC:
		return sprintf(buf, "Smart Dock with USB\n");
	case CABLE_TYPE_AUDIODOCK_MUIC:
		return sprintf(buf, "Audio Dock\n");
	case CABLE_TYPE_CARDOCK_MUIC:
		return sprintf(buf, "Car Dock\n");
	case CABLE_TYPE_JIG_UART_OFF_MUIC:
		return sprintf(buf, "JIG UART OFF\n");
	case CABLE_TYPE_JIG_UART_OFF_VB_MUIC:
		return sprintf(buf, "JIG UART OFF/VB\n");
	case CABLE_TYPE_JIG_UART_ON_MUIC:
		return sprintf(buf, "JIG UART ON\n");
	case CABLE_TYPE_JIG_USB_OFF_MUIC:
		return sprintf(buf, "JIG USB OFF\n");
	case CABLE_TYPE_JIG_USB_ON_MUIC:
		return sprintf(buf, "JIG USB ON\n");
	case CABLE_TYPE_MHL_MUIC:
		return sprintf(buf, "mHL\n");
	case CABLE_TYPE_MHL_VB_MUIC:
		return sprintf(buf, "mHL charging\n");
	case CABLE_TYPE_INCOMPATIBLE_MUIC:
		return sprintf(buf, "Incompatible TA\n");
	default:
		break;
	}

	return sprintf(buf, "UNKNOWN\n");
}

static ssize_t max77804k_muic_show_manualsw(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);

	dev_info(info->dev, "func:%s ap(0),cp(1),vps(2)usb_sel:%d\n",
		 __func__, info->muic_data->usb_sel);/*For debuging*/

	switch (info->muic_data->usb_sel) {
	case PATH_USB_AP:
		return sprintf(buf, "PDA\n");
	case PATH_USB_CP:
		return sprintf(buf, "MODEM\n");
	case PATH_AUDIO:
		return sprintf(buf, "Audio\n");
	default:
		break;
	}

	return sprintf(buf, "UNKNOWN\n");
}

static int max77804k_muic_set_usb_path(struct max77804k_muic_info *info,
					int path);
static ssize_t max77804k_muic_set_manualsw(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf, size_t count)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);

	dev_info(info->dev, "func:%s buf:%s,count:%d\n", __func__, buf, count);

	if (!strncasecmp(buf, "PDA", 3)) {
		info->muic_data->usb_sel = PATH_USB_AP;
		dev_info(info->dev, "%s: PATH_USB_AP\n", __func__);
	} else if (!strncasecmp(buf, "MODEM", 5)) {
		info->muic_data->usb_sel = PATH_USB_CP;
		dev_info(info->dev, "%s: PATH_USB_CP\n", __func__);
		max77804k_muic_set_usb_path(info, PATH_USB_CP);
	} else
		dev_warn(info->dev, "%s: Wrong command\n", __func__);

	return count;
}

static ssize_t max77804k_muic_show_adc(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	int ret;
	u8 val;

	ret = max77804k_read_reg(info->muic, MAX77804K_MUIC_REG_STATUS1, &val);
	dev_info(info->dev, "func:%s ret:%d val:%x\n", __func__, ret, val);

	if (ret) {
		dev_err(info->dev, "%s: fail to read muic reg\n", __func__);
		return sprintf(buf, "UNKNOWN\n");
	}

	return sprintf(buf, "%x\n", (val & STATUS1_ADC_MASK));
}

static ssize_t max77804k_muic_show_audio_path(struct device *dev,
					     struct device_attribute *attr,
					     char *buf)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	int ret;
	u8 val;

	ret = max77804k_read_reg(info->muic, MAX77804K_MUIC_REG_CTRL1, &val);
	dev_info(info->dev, "func:%s ret:%d val:%x\n", __func__, ret, val);
	if (ret) {
		dev_err(info->dev, "%s: fail to read muic reg\n", __func__);
		return sprintf(buf, "UNKNOWN\n");
	}

	return sprintf(buf, "%x\n", val);
}

static ssize_t max77804k_muic_set_audio_path(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	struct i2c_client *client = info->muic;
	u8 cntl1_val, cntl1_msk;
	u8 val;
	dev_info(info->dev, "func:%s buf:%s\n", __func__, buf);
	if (!strncmp(buf, "0", 1))
		val = MAX77804K_MUIC_CTRL1_BIN_0_000;
	else if (!strncmp(buf, "1", 1))
		val = MAX77804K_MUIC_CTRL1_BIN_2_010;
	else {
		dev_warn(info->dev, "%s: Wrong command\n", __func__);
		return count;
	}

	cntl1_val = (val << COMN1SW_SHIFT) | (val << COMP2SW_SHIFT) |
	    (0 << MICEN_SHIFT);
	cntl1_msk = COMN1SW_MASK | COMP2SW_MASK | MICEN_MASK;

	max77804k_update_reg(client, MAX77804K_MUIC_REG_CTRL1, cntl1_val,
			    cntl1_msk);
	dev_info(info->dev, "MUIC cntl1_val:%x, cntl1_msk:%x\n", cntl1_val,
		 cntl1_msk);

	cntl1_val = MAX77804K_MUIC_CTRL1_BIN_0_000;
	max77804k_read_reg(client, MAX77804K_MUIC_REG_CTRL1, &cntl1_val);
	dev_info(info->dev, "%s: CNTL1(0x%02x)\n", __func__, cntl1_val);

	return count;
}

static ssize_t max77804k_muic_show_otg_test(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	int ret;
	u8 val;

	ret = max77804k_read_reg(info->muic, MAX77804K_MUIC_REG_CDETCTRL1, &val);
	dev_info(info->dev, "func:%s ret:%d val:%x buf%s\n",
		 __func__, ret, val, buf);
	if (ret) {
		dev_err(info->dev, "%s: fail to read muic reg\n", __func__);
		return sprintf(buf, "UNKNOWN\n");
	}
	val &= CHGDETEN_MASK;

	return sprintf(buf, "%x\n", val);
}

static ssize_t max77804k_muic_set_otg_test(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf, size_t count)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	struct i2c_client *client = info->muic;
	u8 val;

	dev_info(info->dev, "func:%s buf:%s\n", __func__, buf);
	if (!strncmp(buf, "0", 1))
		val = 0;
	else if (!strncmp(buf, "1", 1))
		val = 1;
	else {
		dev_warn(info->dev, "%s: Wrong command\n", __func__);
		return count;
	}

	max77804k_update_reg(client, MAX77804K_MUIC_REG_CDETCTRL1,
			    val << CHGDETEN_SHIFT, CHGDETEN_MASK);

	val = 0;
	max77804k_read_reg(client, MAX77804K_MUIC_REG_CDETCTRL1, &val);
	dev_info(info->dev, "%s: CDETCTRL(0x%02x)\n", __func__, val);

	return count;
}

#if defined(CONFIG_ADC_ONESHOT)
static int max77804k_muic_set_adcmode(struct max77804k_muic_info *info,
				       int value)
{
	int ret;
	u8 val;

	if (info->adc_mode == value) {
		pr_info("%s: same value:%02x\n", __func__, value);
		return 1;
	}
	dev_info(info->dev,"value:%02x\n", value);
	if (!info->muic) {
		dev_err(info->dev, "%s: no muic i2c client\n", __func__);
		return -EINVAL;
	}

	val = value << CTRL4_ADCMODE_SHIFT;
	dev_info(info->dev, "ADC MODE(0x%02x)\n", val);
	ret = max77804k_update_reg(info->muic, MAX77804K_MUIC_REG_CTRL4, val,
				  CTRL4_ADCMODE_MASK);
	if (ret < 0) {
		dev_err(info->dev, "%s: fail to update reg\n", __func__);
		return -EINVAL;
	}
	info->adc_mode = value;
	return 0;
}
#endif

static void max77804k_muic_set_adcdbset(struct max77804k_muic_info *info,
				       int value)
{
	int ret;
	u8 val;
	dev_info(info->dev, "func:%s value:%x\n", __func__, value);
	if (value > 3) {
		dev_err(info->dev, "%s: invalid value(%x)\n", __func__, value);
		return;
	}

	if (!info->muic) {
		dev_err(info->dev, "%s: no muic i2c client\n", __func__);
		return;
	}

	val = value << CTRL4_ADCDBSET_SHIFT;
	dev_info(info->dev, "%s: ADCDBSET(0x%02x)\n", __func__, val);
	ret = max77804k_update_reg(info->muic, MAX77804K_MUIC_REG_CTRL4, val,
				  CTRL4_ADCDBSET_MASK);
	if (ret < 0)
		dev_err(info->dev, "%s: fail to update reg\n", __func__);
}

static ssize_t max77804k_muic_show_adc_debounce_time(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	int ret;
	u8 val;
	dev_info(info->dev, "func:%s buf:%s\n", __func__, buf);

	if (!info->muic)
		return sprintf(buf, "No I2C client\n");

	ret = max77804k_read_reg(info->muic, MAX77804K_MUIC_REG_CTRL4, &val);
	if (ret) {
		dev_err(info->dev, "%s: fail to read muic reg\n", __func__);
		return sprintf(buf, "UNKNOWN\n");
	}
	val &= CTRL4_ADCDBSET_MASK;
	val = val >> CTRL4_ADCDBSET_SHIFT;
	dev_info(info->dev, "func:%s val:%x\n", __func__, val);
	return sprintf(buf, "%x\n", val);
}

static ssize_t max77804k_muic_set_uart_sel(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf, size_t count)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);

	dev_info(info->dev, "%s, buf : %s\n",__func__,buf);

	if (!strncasecmp(buf, "AP", 2)) {
		int ret = max77804k_muic_set_uart_sel_pass2
			(info, PATH_UART_AP);
		if (ret >= 0){
			info->muic_data->uart_sel = PATH_UART_AP;
			dev_info(info->dev, "UART PATH(CP:0, AP:1):%d\n",
				info->muic_data->uart_sel);

		}else
			dev_err(info->dev, "%s: Change(AP) fail!!", __func__);
#if defined(CONFIG_SWITCH_DUAL_MODEM)
	} else if (!strncasecmp(buf, "CP2", 3)) {
		int ret = max77804k_muic_set_uart_sel_pass2
			(info, PATH_UART_CP);
		if (ret >= 0){
			info->muic_data->uart_sel = PATH_UART_CP;
			dev_info(info->dev, "UART PATH(CP:0, AP:1):%d\n",
				info->muic_data->uart_sel);
		}else
			dev_err(info->dev, "%s: Change(CP) fail!!", __func__);
#endif
	} else if (!strncasecmp(buf, "CP", 2)) {
		int ret = max77804k_muic_set_uart_sel_pass2
			(info, PATH_UART_CP);
		if (ret >= 0){
			info->muic_data->uart_sel = PATH_UART_CP;
			dev_info(info->dev, "UART PATH(CP:0, AP:1):%d\n",
				info->muic_data->uart_sel);
		}else
			dev_err(info->dev, "%s: Change(CP) fail!!", __func__);
	} else {
		dev_warn(info->dev, "%s: Wrong command\n", __func__);
	}
	return count;
}

static ssize_t max77804k_muic_show_uart_sel(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);

	dev_info(info->dev, "func:%s cp(0),ap(1)usb_sel:%d\n",
	 __func__, info->muic_data->uart_sel);/*For debuging*/

	switch (info->muic_data->uart_sel) {
	case PATH_UART_AP:
		return sprintf(buf, "AP\n");
		break;
	case PATH_UART_CP:
#if defined(CONFIG_SWITCH_DUAL_MODEM)
		return sprintf(buf, "CP2\n");
#else
		return sprintf(buf, "CP\n");
#endif
		break;
	default:
		break;
	}
	return sprintf(buf, "UNKNOWN\n");
}

static ssize_t max77804k_muic_show_charger_type(struct device *dev,
					       struct device_attribute *attr,
					       char *buf)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	u8 adc, status;
	int ret;

	ret = max77804k_read_reg(info->muic, MAX77804K_MUIC_REG_STATUS1, &status);

	adc = status & STATUS1_ADC_MASK;

	/* SYSFS Node : chg_type
	*  SYSFS State
	*  0 : Dedicated Charger
	*  1 : Non-Dedicated Charger
	*  2 : Cigar Jack
	*/
	switch (adc){
	case ADC_MHL:
	case ADC_VZW_USB_DOCK:
	case ADC_SMARTDOCK:
	case ADC_AUDIODOCK:
	case ADC_DESKDOCK:
	case ADC_CARDOCK:
	case ADC_OPEN:
		dev_info(info->dev, "%s: Dedicated Charger State\n", __func__);
		return snprintf(buf, 4, "%d\n", 0);
		break;
	case ADC_CEA936ATYPE1_CHG:
	case ADC_INCOMPATIBLE1_CHG:
#if !defined(CONFIG_MUIC_MAX77804K_SUPPORT_HMT_DETECTION)
	case ADC_INCOMPATIBLE2_CHG:
#endif
		dev_info(info->dev, "%s: Undedicated Charger State\n", __func__);
		return snprintf(buf, 4, "%d\n", 1);
		break;
	case ADC_CEA936ATYPE2_CHG:
		dev_info(info->dev, "%s: Dedicated Charger State\n", __func__);
		return snprintf(buf, 4, "%d\n", 2);
		break;
	default:
		dev_info(info->dev, "%s: Undeclared State\n", __func__);
		break;
	}
	return snprintf(buf, 9, "%s\n", "UNKNOWN");
}

#if !defined(CONFIG_MUIC_MAX77804K_SUPPORT_CAR_DOCK)
static ssize_t max77804k_muic_show_apo_factory(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	const char *mode;

	/* true: Factory mode, false: not Factory mode */
	if (info->is_factory_start)
		mode = "FACTORY_MODE";
	else
		mode = "NOT_FACTORY_MODE";

	pr_info("%s:%s apo factory=%s\n", DEV_NAME, __func__, mode);

	return sprintf(buf, "%s\n", mode);
}

static ssize_t max77804k_muic_set_apo_factory(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf, size_t count)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	const char *mode;

	pr_info("%s:%s buf:%s\n", DEV_NAME, __func__, buf);

	/* "FACTORY_START": factory mode */
	if (!strncmp(buf, "FACTORY_START", 13)) {
		info->is_factory_start = true;
		mode = "FACTORY_MODE";
	} else {
		pr_warn("%s:%s Wrong command\n", DEV_NAME, __func__);
		return count;
	}

	pr_info("%s:%s apo factory=%s\n", DEV_NAME, __func__, mode);

	return count;
}
#endif /* !CONFIG_MUIC_MAX77804K_SUPPORT_CAR_DOCK */

#if !defined(CONFIG_MUIC_MAX77804K_SUPPORT_CAR_DOCK)
static DEVICE_ATTR(apo_factory, 0664,
		max77804k_muic_show_apo_factory,
		max77804k_muic_set_apo_factory);
#endif /* !CONFIG_MUIC_MAX77804K_SUPPORT_CAR_DOCK */
static DEVICE_ATTR(chg_type, 0664, max77804k_muic_show_charger_type, NULL);
static DEVICE_ATTR(uart_sel, 0664, max77804k_muic_show_uart_sel,
		max77804k_muic_set_uart_sel);
static DEVICE_ATTR(usb_state, S_IRUGO, max77804k_muic_show_usb_state, NULL);
static DEVICE_ATTR(device, S_IRUGO, max77804k_muic_show_device, NULL);
static DEVICE_ATTR(usb_sel, 0664,
		max77804k_muic_show_manualsw, max77804k_muic_set_manualsw);
static DEVICE_ATTR(adc, S_IRUGO, max77804k_muic_show_adc, NULL);
static DEVICE_ATTR(audio_path, 0664,
		max77804k_muic_show_audio_path, max77804k_muic_set_audio_path);
static DEVICE_ATTR(otg_test, 0664,
		max77804k_muic_show_otg_test, max77804k_muic_set_otg_test);
static DEVICE_ATTR(adc_debounce_time, 0664,
		max77804k_muic_show_adc_debounce_time,
		NULL);

static struct attribute *max77804k_muic_attributes[] = {
	&dev_attr_uart_sel.attr,
	&dev_attr_usb_state.attr,
	&dev_attr_device.attr,
	&dev_attr_usb_sel.attr,
	&dev_attr_adc.attr,
	&dev_attr_audio_path.attr,
	&dev_attr_otg_test.attr,
	&dev_attr_adc_debounce_time.attr,
	&dev_attr_chg_type.attr,
#if !defined(CONFIG_MUIC_MAX77804K_SUPPORT_CAR_DOCK)
	&dev_attr_apo_factory.attr,
#endif /* !CONFIG_MUIC_MAX77804K_SUPPORT_CAR_DOCK */
	NULL
};

static void max77804k_muic_uart_uevent(int state)
{
	if (switch_uart3.dev != NULL) {
		switch_set_state(&switch_uart3, state);
		dev_info(gInfo->dev, "%s: state:%d\n", __func__, state);
	}
}

static const struct attribute_group max77804k_muic_group = {
	.attrs = max77804k_muic_attributes,
};

static int max77804k_muic_set_usb_path(struct max77804k_muic_info *info, int path)
{
	struct i2c_client *client = info->muic;
	int ret;
	u8 cntl1_val, cntl1_msk;
	int val;
	dev_info(info->dev, "func:%s path:%d, cable_name:%d\n", __func__, path, info->cable_name);
	ret = max77804k_muic_set_safeout(path);
	if (ret) {
		dev_err(info->dev, "%s: fail to set safout!\n",
			__func__);
		return ret;
	}
	switch (path) {
	case PATH_USB_AP:
		dev_info(info->dev, "%s: PATH_USB_AP\n", __func__);
		val = MAX77804K_MUIC_CTRL1_BIN_1_001;
		cntl1_val = (val << COMN1SW_SHIFT) | (val << COMP2SW_SHIFT);
		cntl1_msk = COMN1SW_MASK | COMP2SW_MASK;
		break;
	case PATH_AUDIO:
		dev_info(info->dev, "%s: PATH_AUDIO\n", __func__);
		/* SL1, SR2 */
		cntl1_val = (MAX77804K_MUIC_CTRL1_BIN_2_010 << COMN1SW_SHIFT)
			| (MAX77804K_MUIC_CTRL1_BIN_2_010 << COMP2SW_SHIFT) |
			(0 << MICEN_SHIFT);
		cntl1_msk = COMN1SW_MASK | COMP2SW_MASK | MICEN_MASK;
		break;
	case PATH_USB_CP:
		dev_info(info->dev, "%s: PATH_USB_CP\n", __func__);
		val = MAX77804K_MUIC_CTRL1_BIN_4_100;
		cntl1_val = (val << COMN1SW_SHIFT) | (val << COMP2SW_SHIFT);
		cntl1_msk = COMN1SW_MASK | COMP2SW_MASK;
		break;
	case PATH_OPEN:
		dev_info(info->dev, "%s: PATH_OPEN\n", __func__);
		val = MAX77804K_MUIC_CTRL1_BIN_0_000;
		cntl1_val = (val << COMN1SW_SHIFT) | (val << COMP2SW_SHIFT);
		cntl1_msk = COMN1SW_MASK | COMP2SW_MASK;
		break;
	default:
		dev_warn(info->dev, "%s: invalid path(%d)\n", __func__, path);
		return -EINVAL;
	}
	dev_info(info->dev, "%s: Set manual path\n", __func__);
	if (info->cable_name != EXTCON_CARDOCK)
		max77804k_update_reg(client, MAX77804K_MUIC_REG_CTRL1, cntl1_val,
			    cntl1_msk);
	max77804k_update_reg(client, MAX77804K_MUIC_REG_CTRL2,
				CTRL2_CPEn1_LOWPWD0,
				CTRL2_CPEn_MASK | CTRL2_LOWPWD_MASK);

	cntl1_val = MAX77804K_MUIC_CTRL1_BIN_0_000;
	max77804k_read_reg(client, MAX77804K_MUIC_REG_CTRL1, &cntl1_val);
	dev_info(info->dev, "%s: CNTL1(0x%02x)\n", __func__, cntl1_val);

	cntl1_val = MAX77804K_MUIC_CTRL1_BIN_0_000;
	max77804k_read_reg(client, MAX77804K_MUIC_REG_CTRL2, &cntl1_val);
	dev_info(info->dev, "%s: CNTL2(0x%02x)\n", __func__, cntl1_val);

	sysfs_notify(&switch_dev->kobj, NULL, "usb_sel");
	return 0;
}

void max77804k_muic_send_event(int val)
{
	char *envp[2];

	if (val == 0)
		envp[0] = "USB_CONNECTION=READY";
	else
		envp[0] = "USB_CONNECTION=DISCONNECTED";
	envp[1] = NULL;
	dev_info(gInfo->dev, "%s\n", __func__);
	kobject_uevent_env(&gInfo->dev->kobj, KOBJ_CHANGE, envp);
}

extern int system_rev;

void max77804k_otg_control(struct max77804k_muic_info *info, int enable)
{
	u8 int_mask, cdetctrl1, chg_cnfg_00;
	pr_info("%s: enable(%d)\n", __func__, enable);

	if (enable) {
		/* disable charger interrupt */
		max77804k_read_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_INT_MASK, &int_mask);
		chg_int_state = int_mask;
		int_mask |= (1 << 4);	/* disable chgin intr */
		int_mask |= (1 << 6);	/* disable chg */
		int_mask &= ~(1 << 0);	/* enable byp intr */
		max77804k_write_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_INT_MASK, int_mask);

		/* disable charger detection */
		max77804k_read_reg(info->max77804k->muic,
			MAX77804K_MUIC_REG_CDETCTRL1, &cdetctrl1);
		cdetctrl1 &= ~(1 << 0);
		max77804k_write_reg(info->max77804k->muic,
			MAX77804K_MUIC_REG_CDETCTRL1, cdetctrl1);

		/* OTG on, boost on, DIS_MUIC_CTRL=1 */
		max77804k_update_reg(info->max77804k->i2c, MAX77804K_CHG_REG_CHG_CNFG_00,
			CHG_CNFG_00_OTG_CTRL, CHG_CNFG_00_OTG_CTRL);
		max77804k_read_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_CNFG_00, &chg_cnfg_00);

		/* Update CHG_CNFG_11 to 0x50(5V) */
		max77804k_write_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_CNFG_11, 0x50);
	} else {
		/* OTG off, boost off, (buck on),
		   DIS_MUIC_CTRL = 0 unless CHG_ENA = 1 */
		max77804k_update_reg(info->max77804k->i2c, MAX77804K_CHG_REG_CHG_CNFG_00,
			0x00, CHG_CNFG_00_OTG_CTRL);
		max77804k_read_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_CNFG_00, &chg_cnfg_00);

		/* Update CHG_CNFG_11 to 0x00(3V) */
		max77804k_write_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_CNFG_11, 0x00);
		mdelay(50);

		/* [MAX77804] Workaround to get rid of reading dummy(0x00) */
		/* disable charger detection again */
		max77804k_read_reg(info->max77804k->muic,
			MAX77804K_MUIC_REG_CDETCTRL1, &cdetctrl1);
		cdetctrl1 &= ~(1 << 0);
		max77804k_write_reg(info->max77804k->muic,
			MAX77804K_MUIC_REG_CDETCTRL1, cdetctrl1);

		mdelay(10);
		/* enable charger detection */
		max77804k_read_reg(info->max77804k->muic,
			MAX77804K_MUIC_REG_CDETCTRL1, &cdetctrl1);
		cdetctrl1 |= (1 << 0);
		max77804k_write_reg(info->max77804k->muic,
			MAX77804K_MUIC_REG_CDETCTRL1, cdetctrl1);

		/* enable charger interrupt */
		max77804k_write_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_INT_MASK, chg_int_state);
		max77804k_read_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_INT_MASK, &int_mask);
	}

	pr_info("%s: INT_MASK(0x%x), CDETCTRL1(0x%x), CHG_CNFG_00(0x%x)\n",
				__func__, int_mask, cdetctrl1, chg_cnfg_00);
}

void max77804k_powered_otg_control(struct max77804k_muic_info *info, int enable)
{
	pr_info("%s: enable(%d)\n", __func__, enable);

	if (enable) {
		/* OTG on, boost on */
		max77804k_write_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_CNFG_00, 0x05);

		max77804k_write_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_CNFG_02, 0x0E);

		/* Update CHG_CNFG_11 to 0x50(5V) */
		max77804k_write_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_CNFG_11, 0x50);
	} else {
		/* OTG off, boost off, (buck on) */
		max77804k_write_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_CNFG_00, 0x04);

		/* Update CHG_CNFG_11 to 0x00(3V) */
		max77804k_write_reg(info->max77804k->i2c,
			MAX77804K_CHG_REG_CHG_CNFG_11, 0x00);
	}
}
/* use in mach for otg */
int muic_otg_control(int enable)
{
	pr_debug("%s: enable(%d)\n", __func__, enable);

	gInfo->otg_test = enable;

#if defined(CONFIG_CHARGER_SMB1357)
	if(enable) {
		u8 cdetctrl1;
		/* disable charger detection */
		max77804k_read_reg(gInfo->max77804k->muic,
			MAX77804K_MUIC_REG_CDETCTRL1, &cdetctrl1);
		cdetctrl1 &= ~(1 << 0);
		max77804k_write_reg(gInfo->max77804k->muic,
			MAX77804K_MUIC_REG_CDETCTRL1, cdetctrl1);
	} else {
		u8 cdetctrl1;
		/* enable charger detection */
		max77804k_read_reg(gInfo->max77804k->muic,
			MAX77804K_MUIC_REG_CDETCTRL1, &cdetctrl1);
		cdetctrl1 |= (1 << 0);
		max77804k_write_reg(gInfo->max77804k->muic,
			MAX77804K_MUIC_REG_CDETCTRL1, cdetctrl1);
	}
	smb1357_otg_control(enable);
#else
	max77804k_otg_control(gInfo, enable);
#endif
	return 0;
}

/* use in mach for powered-otg */
void powered_otg_control(int enable)
{
	pr_debug("%s: enable(%d)\n", __func__, enable);

	max77804k_powered_otg_control(gInfo, enable);
}
#if 0
static void max77804k_muic_set_cddelay(struct max77804k_muic_info *info)
{
	u8 cdetctrl1;
	int ret;

	ret = max77804k_read_reg(info->max77804k->muic,
		MAX77804K_MUIC_REG_CDETCTRL1, &cdetctrl1);

	pr_info("%s:%s read CDETCTRL1=0x%x, ret=%d\n", DEV_NAME, __func__,
			cdetctrl1, ret);

	if ((cdetctrl1 & 0x10) == 0x10) {
		pr_info("%s:%s CDDelay already setted, return\n", DEV_NAME,
				__func__);
		return;
	}

	cdetctrl1 |= 0x10;

	ret = max77804k_write_reg(info->max77804k->muic,
		MAX77804K_MUIC_REG_CDETCTRL1, cdetctrl1);

	pr_info("%s:%s write CDETCTRL1=0x%x, ret=%d\n", DEV_NAME,
			__func__, cdetctrl1, ret);
}

static void max77804k_muic_clear_cddelay(struct max77804k_muic_info *info)
{
	u8 cdetctrl1;
	int ret;

	ret = max77804k_read_reg(info->max77804k->muic,
		MAX77804K_MUIC_REG_CDETCTRL1, &cdetctrl1);

	pr_info("%s:%s read CDETCTRL1=0x%x, ret=%d\n", DEV_NAME, __func__,
			cdetctrl1, ret);

	if ((cdetctrl1 & 0x10) == 0x0) {
		pr_info("%s:%s CDDelay already cleared, return\n", DEV_NAME,
				__func__);
		return;
	}

	cdetctrl1 &= ~(0x10);

	ret = max77804k_write_reg(info->max77804k->muic,
		MAX77804K_MUIC_REG_CDETCTRL1, cdetctrl1);

	pr_info("%s:%s write CDETCTRL1=0x%x, ret=%d\n", DEV_NAME,
			__func__, cdetctrl1, ret);
}
#endif
static int max77804k_muic_set_path(struct max77804k_muic_info *info, int path)
{
	int ret;
	u8 ctrl1_val, ctrl1_msk;
	u8 ctrl2_val, ctrl2_msk;
	int val;

	dev_info(info->dev, "set path to (%d)\n", path);
	ret = max77804k_muic_set_safeout(path);
	if (ret) {
		dev_err(info->dev, "fail to set safout!(%d)\n", ret);
		return ret;
	}
	if ((info->max77804k->pmic_rev == MAX77804K_REV_PASS1) &&
			((path == PATH_USB_CP) || (path == PATH_UART_CP))) {
		dev_info(info->dev,
				"PASS1 doesn't support manual path to CP.\n");
		if (path == PATH_USB_CP)
			path = PATH_USB_AP;
		else if (path == PATH_UART_CP)
			path = PATH_UART_AP;
	}

	switch (path) {
	case PATH_USB_AP:
		val = MAX77804K_MUIC_CTRL1_BIN_1_001;
		break;
	case PATH_AUDIO:
		val = MAX77804K_MUIC_CTRL1_BIN_2_010;
		break;
	case PATH_UART_AP:
		val = MAX77804K_MUIC_CTRL1_BIN_3_011;
		break;
	case PATH_USB_CP:
		val = MAX77804K_MUIC_CTRL1_BIN_4_100;
		break;
	case PATH_UART_CP:
		val = MAX77804K_MUIC_CTRL1_BIN_5_101;
		break;
	default:
		dev_warn(info->dev, "invalid path(%d)\n", path);
		return -EINVAL;
	}

	ctrl1_val = (val << COMN1SW_SHIFT) | (val << COMP2SW_SHIFT);
	ctrl1_msk = COMN1SW_MASK | COMP2SW_MASK;

	if (path == PATH_AUDIO) {
		ctrl1_val |= 0 << MICEN_SHIFT;
		ctrl1_msk |= MICEN_MASK;
	}

	max77804k_update_reg(info->muic,
				MAX77804K_MUIC_REG_CTRL1, ctrl1_val, ctrl1_msk);

	ctrl2_val = CTRL2_CPEn1_LOWPWD0;
	ctrl2_msk = CTRL2_CPEn_MASK | CTRL2_LOWPWD_MASK;

	max77804k_update_reg(info->muic,
			MAX77804K_MUIC_REG_CTRL2, ctrl2_val, ctrl2_msk);

	return 0;
}

#if defined(CONFIG_MUIC_MAX77804K_SUPPORT_HMT_DETECTION)
#define MAX77804K_PATH_FIX_USB_MASK \
	(BIT(EXTCON_USB_HOST) | BIT(EXTCON_SMARTDOCK) \
	 | BIT(EXTCON_AUDIODOCK) | BIT(EXTCON_HMT))
#else
#define MAX77804K_PATH_FIX_USB_MASK \
	(BIT(EXTCON_USB_HOST) | BIT(EXTCON_SMARTDOCK) | BIT(EXTCON_AUDIODOCK))
#endif

#define MAX77804K_PATH_USB_MASK \
	(BIT(EXTCON_USB) | BIT(EXTCON_JIG_USBOFF) | BIT(EXTCON_JIG_USBON))
#define MAX77804K_PATH_AUDIO_MASK \
	(BIT(EXTCON_DESKDOCK) | BIT(EXTCON_CARDOCK))
#define MAX77804K_PATH_UART_MASK	\
	(BIT(EXTCON_JIG_UARTOFF) | BIT(EXTCON_JIG_UARTON) | BIT(EXTCON_USB_HOST_5V))

#if defined(CONFIG_CHARGER_SMB1357)
#define MAX77804K_PATH_TA_MASK	\
	(BIT(EXTCON_SMARTDOCK_TA) | BIT(EXTCON_TA))
#endif

static int set_muic_path(struct max77804k_muic_info *info)
{
	u32 state = info->edev->state;
	int path;
	int ret = 0;

	dev_info(info->dev, "%s: current state=0x%x, path=%s\n",
			__func__, state, max77804k_path_name[info->path]);

	if (state & MAX77804K_PATH_FIX_USB_MASK)
		path = PATH_USB_AP;
	else if (state & MAX77804K_PATH_USB_MASK) {
		/* set path to usb following usb_sel */
		if (info->muic_data->usb_sel == PATH_USB_CP)
			path = PATH_USB_CP;
		else
			path = PATH_USB_AP;
	} else if (state & MAX77804K_PATH_UART_MASK) {
		/* set path to uart following uart_sel */
		if (info->muic_data->uart_sel == PATH_UART_CP)
			path = PATH_UART_CP;
		else
			path = PATH_UART_AP;
	} else if (state & MAX77804K_PATH_AUDIO_MASK)
		path = PATH_AUDIO;
#if defined(CONFIG_CHARGER_SMB1357)
	else if (state & MAX77804K_PATH_TA_MASK) {
		/* set path to TA */
		path = PATH_USB_CP;
	}
#endif
	else {
		dev_info(info->dev, "%s: don't have to set path\n", __func__);
		return 0;
	}

	ret = max77804k_muic_set_path(info, path);
	if (ret < 0) {
		dev_err(info->dev, "fail to set path(%s->%s),stat=%x,ret=%d\n",
				max77804k_path_name[info->path],
				max77804k_path_name[path], state, ret);
		return ret;
	}

	dev_info(info->dev, "%s: path: %s -> %s\n", __func__,
			max77804k_path_name[info->path],
			max77804k_path_name[path]);
	info->path = path;

	return 0;
}

static void _detected(struct max77804k_muic_info *info, u32 new_state)
{
	u32 current_state;
	u32 changed_state;
	int index;
	int attach;
	int ret;

	current_state = info->edev->state;
	changed_state = current_state ^ new_state;

	dev_info(info->dev, "state: cur=0x%x, new=0x%x, changed=0x%x\n",
			current_state, new_state, changed_state);
	for (index = 0; index < SUPPORTED_CABLE_MAX; index++) {
		if (!(changed_state & BIT(index)))
			continue;

		if (new_state & BIT(index))
			attach = 1;
		else
			attach = 0;

		ret = extcon_set_cable_state(info->edev,
				extcon_cable_name[index], attach);
		if (unlikely(ret < 0))
			dev_err(info->dev, "fail to notify %s(%d), %d, ret=%d\n",
				extcon_cable_name[index], index, attach, ret);
	}
#if defined(CONFIG_ADC_ONESHOT)
		/* Set ADC Mode to oneshot */
	if (!new_state) {
		max77804k_muic_set_adcmode(info, ADC_ONESHOT);
	}
#endif
	set_muic_path(info);
}

static int max77804k_muic_handle_attach(struct max77804k_muic_info *info,
				       u8 status1, u8 status2)
{
	u8 adc;
	u8 vbvolt;
	u8 chgtyp;
	u8 chgdetrun;
	u8 adc1k;
	u32 pre_state;
	u32 new_state;

	new_state = 0;
	pre_state = info->edev->state;

	adc = status1 & STATUS1_ADC_MASK;
	adc1k = status1 & STATUS1_ADC1K_MASK;
	chgtyp = status2 & STATUS2_CHGTYP_MASK;
	vbvolt = status2 & STATUS2_VBVOLT_MASK;
	chgdetrun = status2 & STATUS2_CHGDETRUN_MASK;

	dev_info(info->dev, "st1:0x%x st2:0x%x\n", status1, status2);
	dev_info(info->dev,
		"adc:0x%x, adc1k:0x%x, chgtyp:0x%x, vbvolt:%d\n",
				adc, adc1k, chgtyp, vbvolt);
	dev_info(info->dev, "chgdetrun:0x%x, prev state:0x%x\n",
				chgdetrun, pre_state);

	/* Workaround for Factory mode in MUIC PASS2.
	 * Abandon adc interrupt of approximately +-100K range
	 * if previous cable status was JIG UART BOOT OFF.
	 * In uart path cp, adc is unstable state
	 * MUIC PASS2 turn to AP_UART mode automatically
	 * So, in this state set correct path manually.
	 */
#if 0
	if (info->max77804k->pmic_rev > MAX77804K_REV_PASS1) {
		if ((pre_state & BIT(EXTCON_JIG_UARTOFF)) &&
			((adc == ADC_JIG_UART_OFF + 1 ||
			(adc == ADC_JIG_UART_OFF - 1))) &&
			(info->muic_data->uart_sel == PATH_UART_CP)) {
			dev_warn(info->dev, "abandon ADC\n");
			new_state = BIT(EXTCON_JIG_UARTOFF);
			goto __found_cable;
		}
	}
#endif
	/* 1Kohm ID regiter detection (mHL)
	 * Old MUIC : ADC value:0x00 or 0x01, ADCLow:1
	 * New MUIC : ADC value is not set(Open), ADCLow:1, ADCError:1
	 */
	if (adc1k) {
		new_state = BIT(EXTCON_MHL);
		/* If is_otg_boost is true,
		 * it means that vbolt is from the device to accessory.
		 */
		if (vbvolt)
			new_state |= BIT(EXTCON_MHL_VB);
		goto __found_cable;
	}

	switch (adc) {
	case ADC_GND:
		new_state = BIT(EXTCON_USB_HOST);
		break;
#if defined(CONFIG_MUIC_SUPPORT_SMART_DOCK)
	case ADC_SMARTDOCK:
#if defined(CONFIG_ADC_ONESHOT)
		/* Set ADC Mode to Always */
		if (!max77804k_muic_set_adcmode(info, ADC_ALWAYS))
			msleep(50);
#endif
		new_state = BIT(EXTCON_SMARTDOCK);
		if (chgtyp == CHGTYP_DEDICATED_CHGR) {
			new_state |= BIT(EXTCON_SMARTDOCK_TA);
		} else if (chgtyp == CHGTYP_USB) {
			new_state |= BIT(EXTCON_SMARTDOCK_USB);
		}

		break;
#endif
#if defined(CONFIG_MUIC_MAX77804K_SUPPORT_HMT_DETECTION)
	case ADC_HMT:
#if defined(CONFIG_ADC_ONESHOT)
		/* Set ADC Mode to Always */
		if (!max77804k_muic_set_adcmode(info, ADC_ALWAYS))
			msleep(50);
#endif
		new_state = BIT(EXTCON_HMT);
		new_state |= BIT(EXTCON_USB_HOST);
		break;
#endif
	case ADC_JIG_UART_OFF:
		new_state = BIT(EXTCON_JIG_UARTOFF);
		if (vbvolt) {
			if (gInfo->otg_test) /*	add for DFMS */
				new_state |= BIT(EXTCON_USB_HOST_5V);
			else
				new_state |= BIT(EXTCON_JIG_UARTOFF_VB);
		}
		break;
	case ADC_CARDOCK:	/* ADC_CARDOCK == ADC_JIG_UART_ON */
#if defined(CONFIG_SEC_FACTORY)
		new_state = BIT(EXTCON_CARDOCK);
#else
		new_state = BIT(EXTCON_JIG_UARTON);
#endif
		if (vbvolt)
			new_state |= BIT(EXTCON_CARDOCK_VB);
		break;
	case ADC_JIG_USB_OFF:
		if (vbvolt) {
			new_state = BIT(EXTCON_JIG_USBOFF);
			info->cable_name = EXTCON_JIG_USBOFF;
		}
		break;
	case ADC_JIG_USB_ON:
		if (vbvolt) {
			new_state = BIT(EXTCON_JIG_USBON);
			info->cable_name = EXTCON_JIG_USBON;
		}
		break;
#if defined(CONFIG_MUIC_SUPPORT_DESK_DOCK)
	case ADC_DESKDOCK:
		new_state = BIT(EXTCON_DESKDOCK);
		if (vbvolt)
			new_state |= BIT(EXTCON_DESKDOCK_VB);
		break;
#endif
#if defined(CONFIG_MUIC_SUPPORT_AUDIO_DOCK)
	case ADC_AUDIODOCK:
			new_state = BIT(EXTCON_AUDIODOCK);
		break;
#endif
	case ADC_CHARGING_CABLE:
		new_state = BIT(EXTCON_CHARGING_CABLE);
		break;
	case ADC_CEA936ATYPE1_CHG:
	case ADC_CEA936ATYPE2_CHG:
	case ADC_OPEN:
		switch (chgtyp) {
		case CHGTYP_USB:
		case CHGTYP_DOWNSTREAM_PORT:
			if (adc == ADC_CEA936ATYPE2_CHG) {
				new_state = BIT(EXTCON_CEA936_CHG);
			} else {
				new_state = BIT(EXTCON_USB);
				info->cable_name = EXTCON_USB;
			}
			break;
		case CHGTYP_DEDICATED_CHGR:
		case CHGTYP_500MA:
		case CHGTYP_1A:
			new_state = BIT(EXTCON_TA);
			break;
		default:
			break;
		}
		break;
	default:
#if defined(CONFIG_MUIC_SUPPORT_INCOMPATIBLE_CHARGER)
		if (vbvolt) {
			dev_warn(info->dev, "Incompatible adc=0x%x\n", adc);
			new_state = BIT(EXTCON_INCOMPATIBLE);
		} else
#endif
		{
			if (is_lpm_mode && vbvolt) {
				dev_warn(info->dev, "Incompatible adc=0x%x\n", adc);
				new_state = BIT(EXTCON_INCOMPATIBLE);
			} else {
				dev_warn(info->dev, "unsupported adc=0x%x\n", adc);
			}
		}
		break;
	}

	if (!new_state) {
		dev_warn(info->dev, "Fail to get cable type (adc=0x%x)\n", adc);
		_detected(info, 0);
		return -1;
	}

__found_cable:
	_detected(info, new_state);
	max77804k_update_jig_state(info);
	return 0;
}

static int max77804k_muic_handle_detach(struct max77804k_muic_info *info)
{
	u8 ctrl2_val;

	info->cable_name = EXTCON_NONE;
	/* Workaround: irq doesn't occur after detaching mHL cable */
	max77804k_write_reg(info->muic, MAX77804K_MUIC_REG_CTRL1,
					MAX77804K_MUIC_CTRL1_BIN_0_000);

	/* Enable Factory Accessory Detection State Machine */

	max77804k_update_reg(info->muic,
				MAX77804K_MUIC_REG_CTRL2, CTRL2_CPEn0_LOWPWD1,
				CTRL2_CPEn_MASK | CTRL2_LOWPWD_MASK);

	max77804k_read_reg(info->muic, MAX77804K_MUIC_REG_CTRL2,
				&ctrl2_val);
	dev_info(info->dev, "%s: CNTL2(0x%02x)\n", __func__, ctrl2_val);

	_detected(info, 0);

	return 0;
}

static void max77804k_muic_detect_dev(struct max77804k_muic_info *info, int irq)
{
	struct i2c_client *client = info->muic;
	u8 status[2];
	int intr = INT_ATTACH;
	int ret;
	u8 cntl1_val;

	ret = max77804k_read_reg(client, MAX77804K_MUIC_REG_CTRL1, &cntl1_val);
	dev_info(info->dev, "func:%s CONTROL1:%x\n", __func__, cntl1_val);

	ret = max77804k_bulk_read(client, MAX77804K_MUIC_REG_STATUS1, 2, status);
	dev_info(info->dev, "func:%s irq:%d ret:%d\n", __func__, irq, ret);
	if (ret) {
		dev_err(info->dev, "%s: fail to read muic reg(%d)\n", __func__,
			ret);
		return;
	}

	dev_info(info->dev, "%s: STATUS1:0x%x, 2:0x%x\n", __func__,
		 status[0], status[1]);

	wake_lock_timeout(&info->muic_wake_lock, HZ * 2);

	info->adc = status[0] & STATUS1_ADC_MASK;
	info->chgtyp = status[1] & STATUS2_CHGTYP_MASK;
	info->vbvolt = status[1] & STATUS2_VBVOLT_MASK;

	if ((info->adc == ADC_OPEN) && (info->chgtyp == CHGTYP_NO_VOLTAGE))
		intr = INT_DETACH;
	if (intr == INT_ATTACH) {
		dev_info(info->dev, "%s: ATTACHED/CHANGED\n", __func__);
		max77804k_muic_handle_attach(info, status[0], status[1]);
	} else if (intr == INT_DETACH) {
		dev_info(info->dev, "%s: DETACHED\n", __func__);
		max77804k_muic_handle_detach(info);
	} else {
		pr_info("%s:%s device filtered, nothing affect.\n", DEV_NAME,
				__func__);
	}
	return;
}

static irqreturn_t max77804k_muic_irq(int irq, void *data)
{
	struct max77804k_muic_info *info = data;
	dev_info(info->dev, "%s: irq:%d\n", __func__, irq);

	mutex_lock(&info->mutex);
	max77804k_muic_detect_dev(info, irq);
	mutex_unlock(&info->mutex);

	return IRQ_HANDLED;
}

#define REQUEST_IRQ(_irq, _name)					\
do {									\
	ret = request_threaded_irq(_irq, NULL, max77804k_muic_irq,	\
				    0, _name, info);			\
	if (ret < 0)							\
		dev_err(info->dev, "Failed to request IRQ #%d: %d\n",	\
			_irq, ret);					\
} while (0)

static int max77804k_muic_irq_init(struct max77804k_muic_info *info)
{
	int ret, count;
	u8 val;

	dev_info(info->dev, "func:%s\n", __func__);
	/* dev_info(info->dev, "%s: system_rev=%x\n", __func__, system_rev); */

	/* INTMASK1  3:ADC1K 2:ADCErr 1:ADCLow 0:ADC */
	/* INTMASK2  0:Chgtype */
	max77804k_write_reg(info->muic, MAX77804K_MUIC_REG_INTMASK1, 0x09);
	max77804k_write_reg(info->muic, MAX77804K_MUIC_REG_INTMASK2, 0x11);
	max77804k_write_reg(info->muic, MAX77804K_MUIC_REG_INTMASK3, 0x00);

	REQUEST_IRQ(info->irq_adc, "muic-adc");
	REQUEST_IRQ(info->irq_chgtype, "muic-chgtype");
	REQUEST_IRQ(info->irq_vbvolt, "muic-vbvolt");

	dev_info(info->dev, "adc:%d chgtype:%d vbvolt:%d",
		info->irq_adc, info->irq_chgtype, info->irq_vbvolt);

	for (count = 1; count < 9 ; count ++) {
		max77804k_read_reg(info->muic, count, &val);
		dev_info(info->dev, "%s: reg=%x, val=%x\n", __func__,
				count, val);
	}

	return 0;
}

static void max77804k_muic_init_detect(struct work_struct *work)
{
	struct max77804k_muic_info *info =
	    container_of(work, struct max77804k_muic_info, init_work.work);
	dev_info(info->dev, "func:%s\n", __func__);

	mutex_lock(&info->mutex);

	info->edev->state = 0;
	max77804k_muic_detect_dev(info, -1);

	mutex_unlock(&info->mutex);
}

void max77804k_update_jig_state(struct max77804k_muic_info *info)
{
	struct i2c_client *client = info->muic;
	//struct max77804k_muic_data *mdata = info->muic_data;
	u8 reg_data, adc;
	int ret, jig_state;

	ret = max77804k_read_reg(client, MAX77804K_MUIC_REG_STATUS1, &reg_data);
	if (ret) {
		dev_err(info->dev, "%s: fail to read muic reg(%d)\n",
					__func__, ret);
		return;
	}
	adc = reg_data & STATUS1_ADC_MASK;

	switch (adc) {
	case ADC_JIG_UART_OFF:
	case ADC_JIG_USB_OFF:
	case ADC_JIG_USB_ON:
		jig_state = true;
		break;
	default:
		jig_state = false;
		break;
	}

//	mdata->jig_state(jig_state);
	max77804k_muic_uart_uevent(jig_state);
}

#ifdef CONFIG_USB_HOST_NOTIFY
struct booster_data sec_booster = {
	.name = "max77804k",
	.boost = muic_otg_control,
};
#endif

static int __init get_lpm_mode(char *str)
{
	if (!strncasecmp(str, "lpm", 3)) {
		pr_info("%s:lpm mode\n", __func__);
		is_lpm_mode = true;
	} else {
		pr_info("%s:not lpm mode\n", __func__);
		is_lpm_mode = false;
	}
	return 0;
}
__setup("androidboot.baseband=", get_lpm_mode);

static int __devinit max77804k_muic_probe(struct platform_device *pdev)
{
	struct max77804k_dev *max77804k = dev_get_drvdata(pdev->dev.parent);
	struct max77804k_platform_data *pdata = dev_get_platdata(max77804k->dev);
	struct max77804k_muic_info *info;
	int ret;
	u8 cdetctrl1;

	pr_info("func:%s\n", __func__);

	info = kzalloc(sizeof(struct max77804k_muic_info), GFP_KERNEL);
	if (!info) {
		dev_err(&pdev->dev, "%s: failed to allocate info\n", __func__);
		ret = -ENOMEM;
		goto err_return;
	}

	info->dev = &pdev->dev;
	info->max77804k = max77804k;
	info->muic = max77804k->muic;
	info->irq_adc = max77804k->irq_base + MAX77804K_MUIC_IRQ_INT1_ADC;
	info->irq_vbvolt = max77804k->irq_base + MAX77804K_MUIC_IRQ_INT2_VBVOLT;
	info->irq_chgtype = max77804k->irq_base + MAX77804K_MUIC_IRQ_INT2_CHGTYP;
	info->muic_data = pdata->muic_data;
	info->muic_data->uart_sel = PATH_UART_AP;
	info->is_adc_open_prev = true;
#if !defined(CONFIG_MUIC_MAX77804K_SUPPORT_CAR_DOCK)
	info->is_factory_start = false;
#endif /* !CONFIG_MUIC_MZX77804k_SUPPORT_CAR_DOCK */
	info->edev = devm_kzalloc(&pdev->dev, sizeof(struct extcon_dev),
			GFP_KERNEL);
	if (!info->edev) {
		dev_err(&pdev->dev, "failed to allocate memory for extcon\n");
		ret = -ENOMEM;
		goto err_input;
	}

	info->edev->name=EXTCON_DEV_NAME;
	info->edev->supported_cable = extcon_cable_name;

	ret = extcon_dev_register(info->edev, NULL);
	if (ret) {
		dev_err(&pdev->dev, "failed to register extcon device\n");
		goto err_input;
	}

	wake_lock_init(&info->muic_wake_lock, WAKE_LOCK_SUSPEND,
		"muic wake lock");

	info->cable_name = EXTCON_NONE;
	info->muic_data->usb_sel = PATH_USB_AP;
	gInfo = info;

	platform_set_drvdata(pdev, info);
	dev_info(info->dev, "adc:%d chgtype:%d\n",
		 info->irq_adc, info->irq_chgtype);

#if defined(CONFIG_SWITCH_DUAL_MODEM)
	switch_sel &= 0xf;
	if ((switch_sel & MAX77804K_SWITCH_SEL_1st_BIT_USB) == 0x1)
		info->muic_data->usb_sel = PATH_USB_AP;
	else
		info->muic_data->usb_sel = PATH_USB_CP;

	if ((switch_sel & MAX77804K_SWITCH_SEL_2nd_BIT_UART) == 0x1 << 1)
		info->muic_data->uart_sel = PATH_UART_AP;
	else
		info->muic_data->uart_sel = PATH_UART_CP;

	pr_err("%s: switch_sel: %x\n", __func__, switch_sel);
#endif

	/* create sysfs group */
	ret = sysfs_create_group(&switch_dev->kobj, &max77804k_muic_group);
	pr_info("dev_set_drvdata:%s\n", __func__);
	dev_set_drvdata(switch_dev, info);
	if (ret) {
		dev_err(&pdev->dev,
			"failed to create max77804k muic attribute group\n");
		goto err_input;
	}
	mutex_init(&info->mutex);

	/* Set ADC debounce time: 25ms */
	max77804k_muic_set_adcdbset(info, 2);
	/* Set DCDTmr to 2sec */
	max77804k_read_reg(info->max77804k->muic,
		MAX77804K_MUIC_REG_CDETCTRL1, &cdetctrl1);
	/* Get adcmode value */
	max77804k_read_reg(info->max77804k->muic,
		MAX77804K_MUIC_REG_CTRL4, &info->adc_mode);
	info->adc_mode = info->adc_mode >> CTRL4_ADCMODE_SHIFT;
	pr_info("%s: ADCMODE(0x%x)\n", __func__, info->adc_mode);
	cdetctrl1 &= ~(1 << 5);
	max77804k_write_reg(info->max77804k->muic,
		MAX77804K_MUIC_REG_CDETCTRL1, cdetctrl1);
	pr_info("%s: CDETCTRL1(0x%02x)\n", __func__, cdetctrl1);

	ret = switch_dev_register(&switch_uart3);
	if (ret < 0) {
		pr_err("%s : Failed to register switch_uart3 device\n", __func__);
		goto err_switch_uart3_dev_register;
	}

	ret = max77804k_muic_irq_init(info);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to initialize MUIC irq:%d\n", ret);
		goto fail;
	}

	/* initial cable detection */
	INIT_DELAYED_WORK(&info->init_work, max77804k_muic_init_detect);
	schedule_delayed_work(&info->init_work, msecs_to_jiffies(3000));

	/* init jig state */
	max77804k_update_jig_state(info);
#ifdef CONFIG_USB_HOST_NOTIFY
	sec_otg_register_booster(&sec_booster);
#endif

	return 0;

 fail:
	if (info->irq_adc)
		free_irq(info->irq_adc, NULL);
	if (info->irq_chgtype)
		free_irq(info->irq_chgtype, NULL);
	if (info->irq_vbvolt)
		free_irq(info->irq_vbvolt, NULL);
	mutex_destroy(&info->mutex);
 err_input:
	platform_set_drvdata(pdev, NULL);
	wake_lock_destroy(&info->muic_wake_lock);
 err_switch_uart3_dev_register:
	kfree(info);
	switch_dev_unregister(&switch_uart3);
 err_return:
	return ret;
}

static int __devexit max77804k_muic_remove(struct platform_device *pdev)
{
	struct max77804k_muic_info *info = platform_get_drvdata(pdev);
	sysfs_remove_group(&switch_dev->kobj, &max77804k_muic_group);

	if (info) {
		dev_info(info->dev, "func:%s\n", __func__);
		cancel_delayed_work(&info->init_work);
		free_irq(info->irq_adc, info);
		free_irq(info->irq_chgtype, info);
		free_irq(info->irq_vbvolt, info);
		wake_lock_destroy(&info->muic_wake_lock);
		mutex_destroy(&info->mutex);
		kfree(info);
	}
	return 0;
}

void max77804k_muic_shutdown(struct device *dev)
{
	struct max77804k_muic_info *info = dev_get_drvdata(dev);
	int ret;
	u8 val;
	dev_info(info->dev, "func:%s\n", __func__);
	if (!info->muic) {
		dev_err(info->dev, "%s: no muic i2c client\n", __func__);
		return;
	}

	dev_info(info->dev, "%s: JIGSet: auto detection\n", __func__);
	val = (0 << CTRL3_JIGSET_SHIFT) | (0 << CTRL3_BOOTSET_SHIFT);

	ret = max77804k_update_reg(info->muic, MAX77804K_MUIC_REG_CTRL3, val,
			CTRL3_JIGSET_MASK | CTRL3_BOOTSET_MASK);
	if (ret < 0) {
		dev_err(info->dev, "%s: fail to update reg\n", __func__);
		return;
	}
}

static struct platform_driver max77804k_muic_driver = {
	.driver		= {
		.name	= DEV_NAME,
		.owner	= THIS_MODULE,
		.shutdown = max77804k_muic_shutdown,
	},
	.probe		= max77804k_muic_probe,
	.remove		= __devexit_p(max77804k_muic_remove),
};

static int __init max77804k_muic_init(void)
{
	pr_info("func:%s\n", __func__);
	return platform_driver_register(&max77804k_muic_driver);
}
module_init(max77804k_muic_init);

static void __exit max77804k_muic_exit(void)
{
	pr_info("func:%s\n", __func__);
	platform_driver_unregister(&max77804k_muic_driver);
}
module_exit(max77804k_muic_exit);


MODULE_DESCRIPTION("Maxim MAX77804K MUIC driver");
MODULE_AUTHOR("<sukdong.kim@samsung.com>");
MODULE_LICENSE("GPL");
