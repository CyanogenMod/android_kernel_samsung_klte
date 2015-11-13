/*
 * haptic motor driver for max77888 - max77673_haptic.c
 *
 * Copyright (C) 2011 ByungChang Cha <bc.cha@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hrtimer.h>
#include <linux/pwm.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/clk.h>
#include <linux/i2c.h>
#include <linux/regulator/consumer.h>
#include <linux/mfd/max77888.h>
#include <linux/mfd/max77888-private.h>

struct max77888_haptic_data {
	struct max77888_dev *max77888;
	struct i2c_client *i2c;
	struct i2c_client *pmic_i2c;
	struct max77888_haptic_platform_data *pdata;

	spinlock_t lock;
	bool running;
};

struct max77888_haptic_data *g_hap_data;

static void max77888_haptic_i2c(struct max77888_haptic_data *hap_data, bool en)
{
	int ret;
	u8 value = hap_data->pdata->reg2;
	u8 lscnfg_val = 0x00;

	pr_debug("[VIB] %s %d\n", __func__, en);

	if (en) {
		value |= MOTOR_EN;
		lscnfg_val = 0x80;
	}

	ret = max77888_update_reg(hap_data->pmic_i2c, MAX77888_PMIC_REG_LSCNFG,
				lscnfg_val, 0x80);
	if (ret)
		pr_err("[VIB] i2c update error %d\n", ret);

	ret = max77888_write_reg(hap_data->i2c,
				 MAX77888_HAPTIC_REG_CONFIG2, value);
	if (ret)
		pr_err("[VIB] i2c write error %d\n", ret);
}

#ifdef CONFIG_VIBETONZ
void max77888_vibtonz_en(bool en)
{
	if (g_hap_data == NULL) {
		printk(KERN_ERR "[VIB] the motor is not ready!!!");
		return ;
	}

	if (en) {
		if (g_hap_data->running)
			return;

		max77888_haptic_i2c(g_hap_data, true);

		g_hap_data->running = true;
	} else {
		if (!g_hap_data->running)
			return;

		max77888_haptic_i2c(g_hap_data, false);

		g_hap_data->running = false;
	}
}
EXPORT_SYMBOL(max77888_vibtonz_en);
#endif

static int __devinit max77888_haptic_probe(struct platform_device *pdev)
{
	int error = 0;
	struct max77888_dev *max77888 = dev_get_drvdata(pdev->dev.parent);
	struct max77888_platform_data *max77888_pdata
		= dev_get_platdata(max77888->dev);

#ifdef CONFIG_VIBETONZ
	struct max77888_haptic_platform_data *pdata
		= max77888_pdata->haptic_data;
#endif
	struct max77888_haptic_data *hap_data;

	pr_err("[VIB] ++ %s\n", __func__);
	 if (pdata == NULL) {
		pr_err("%s: no pdata\n", __func__);
		return -ENODEV;
	}

	hap_data = kzalloc(sizeof(struct max77888_haptic_data), GFP_KERNEL);
	if (!hap_data)
		return -ENOMEM;

	platform_set_drvdata(pdev, hap_data);
	g_hap_data = hap_data;
	hap_data->max77888 = max77888;
	hap_data->i2c = max77888->haptic;
	hap_data->pmic_i2c = max77888->i2c;
	pdata->reg2 = MOTOR_LRA | EXT_PWM | DIVIDER_128;
	hap_data->pdata = pdata;

	spin_lock_init(&(hap_data->lock));

	pr_err("[VIB] -- %s\n", __func__);

	return error;
}

static int __devexit max77888_haptic_remove(struct platform_device *pdev)
{
	struct max77888_haptic_data *data = platform_get_drvdata(pdev);
	kfree(data);
	g_hap_data = NULL;

	return 0;
}

static int max77888_haptic_suspend(struct platform_device *pdev,
			pm_message_t state)
{
	return 0;
}
static int max77888_haptic_resume(struct platform_device *pdev)
{
	return 0;
}

static struct platform_driver max77888_haptic_driver = {
	.probe		= max77888_haptic_probe,
	.remove		= max77888_haptic_remove,
	.suspend	= max77888_haptic_suspend,
	.resume		= max77888_haptic_resume,
	.driver = {
		.name	= "max77888-haptic",
		.owner	= THIS_MODULE,
	},
};

static int __init max77888_haptic_init(void)
{
	pr_debug("[VIB] %s\n", __func__);
	return platform_driver_register(&max77888_haptic_driver);
}
module_init(max77888_haptic_init);

static void __exit max77888_haptic_exit(void)
{
	platform_driver_unregister(&max77888_haptic_driver);
}
module_exit(max77888_haptic_exit);

MODULE_AUTHOR("ByungChang Cha <bc.cha@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MAX77888 haptic driver");
