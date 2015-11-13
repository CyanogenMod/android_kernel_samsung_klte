/*
 * cyttsp5_core.h
 * Cypress TrueTouch(TM) Standard Product V5 Core Module.
 * For use with Cypress Txx5xx parts.
 * Supported parts include:
 * TMA5XX
 *
 * Copyright (C) 2012-2013 Cypress Semiconductor
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2, and only version 2, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Contact Cypress Semiconductor at www.cypress.com <ttdrivers@cypress.com>
 *
 */

#ifndef _LINUX_CYTTSP5_CORE_H
#define _LINUX_CYTTSP5_CORE_H

#include <linux/stringify.h>

#define CYTTSP5_I2C_NAME "cyttsp5_i2c_adapter"
#define CYTTSP5_SPI_NAME "cyttsp5_spi_adapter"

#define CYTTSP5_CORE_NAME "cyttsp5_core"
#define CYTTSP5_MT_NAME "cyttsp5_mt"
#define CYTTSP5_BTN_NAME "cyttsp5_btn"
#define CYTTSP5_PROXIMITY_NAME "cyttsp5_proximity"

#define CY_DRIVER_NAME TTDA
#define CY_DRIVER_MAJOR 03
#define CY_DRIVER_MINOR 02

#define CY_DRIVER_REVCTRL 000005

#define CY_DRIVER_VERSION		    \
__stringify(CY_DRIVER_NAME)		    \
"." __stringify(CY_DRIVER_MAJOR)	    \
"." __stringify(CY_DRIVER_MINOR)	    \
"." __stringify(CY_DRIVER_REVCTRL)

#define CY_DRIVER_DATE "20131202"	/* YYYYMMDD */

/* abs settings */
#define CY_IGNORE_VALUE             0xFFFF

/* FW VERSION */
#define CY_HW_VERSION 0x02
#define CY_FW_VERSION 0x1900

enum cyttsp5_core_platform_flags {
	CY_CORE_FLAG_NONE,
	CY_CORE_FLAG_WAKE_ON_GESTURE,
};

enum cyttsp5_loader_platform_flags {
	CY_LOADER_FLAG_NONE,
	CY_LOADER_FLAG_CALIBRATE_AFTER_FW_UPGRADE,
};

struct touch_settings {
	const uint8_t   *data;
	uint32_t         size;
	const uint8_t   *ver;
	uint32_t         vsize;
	uint8_t         tag;
};

struct cyttsp5_touch_firmware {
	const uint8_t *img;
	uint32_t size;
	const uint8_t *ver;
	uint8_t vsize;
	uint8_t hw_version;
	uint16_t fw_version;
};

struct cyttsp5_touch_config {
	struct touch_settings *param_regs;
	struct touch_settings *param_size;
	const uint8_t *fw_ver;
	uint8_t fw_vsize;
};

struct cyttsp5_loader_platform_data {
	struct cyttsp5_touch_firmware *fw;
	struct cyttsp5_touch_config *ttconfig;
	u32 flags;
};

#define CY_TOUCH_SETTINGS_MAX 32

struct cyttsp5_core_platform_data {
	int irq_gpio;
	int rst_gpio;
	int pwr_1p8;
	int pwr_3p3;
	int level_irq_udelay;
	u16 hid_desc_register;
	u16 vendor_id;
	u16 product_id;
	int (*xres)(struct cyttsp5_core_platform_data *pdata,
		struct device *dev);
	int (*init)(struct cyttsp5_core_platform_data *pdata,
		int on, struct device *dev);
	int (*power)(struct cyttsp5_core_platform_data *pdata,
		int on, struct device *dev, atomic_t *ignore_irq);
	int (*irq_stat)(struct cyttsp5_core_platform_data *pdata,
		struct device *dev);
	struct touch_settings *sett[CY_TOUCH_SETTINGS_MAX];
	u32 flags;
};

struct touch_framework {
	const uint16_t  *abs;
	uint8_t         size;
	uint8_t         enable_vkeys;
} __packed;

enum cyttsp5_mt_platform_flags {
	CY_MT_FLAG_NONE,
	CY_MT_FLAG_HOVER = 0x04,
	CY_MT_FLAG_FLIP = 0x08,
	CY_MT_FLAG_INV_X = 0x10,
	CY_MT_FLAG_INV_Y = 0x20,
	CY_MT_FLAG_VKEYS = 0x40,
	CY_MT_FLAG_NO_TOUCH_ON_LO = 0x80,
};

struct cyttsp5_mt_platform_data {
	struct touch_framework *frmwrk;
	unsigned short flags;
	char const *inp_dev_name;
	int vkeys_x;
	int vkeys_y;
};

struct cyttsp5_btn_platform_data {
	char const *inp_dev_name;
};

struct cyttsp5_proximity_platform_data {
	struct touch_framework *frmwrk;
	char const *inp_dev_name;
};

struct cyttsp5_platform_data {
	struct cyttsp5_core_platform_data *core_pdata;
	struct cyttsp5_loader_platform_data *loader_pdata;
	struct cyttsp5_mt_platform_data *mt_pdata;
	struct cyttsp5_btn_platform_data *btn_pdata;
	struct cyttsp5_proximity_platform_data *prox_pdata;
};

#endif /* _LINUX_CYTTSP5_CORE_H */
