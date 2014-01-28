/* Copyright (c) 2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of_platform.h>
#include <mach/rpm-smd.h>
#include "ext-buck-support.h"

static bool msm_ext_buck;

#define RPM_REQUEST_TYPE_GPIO  0x6F697067
#define RPM_GPIO_NUMB_KEY      0x626d756e
#define RPM_GPIO_STAT_KEY      0x74617473
#define RPM_GPIO_SETT_KEY      0x74746573
#define RPM_GPIO_RESOURCE_ID   3
#define GPIO_SET               1
#define GPIO_RESET             0

static void msm_send_ext_buck_votes(int gpio_num, int settling_time)
{
	int rc;
	int gpio_status_sleep = GPIO_RESET;
	int gpio_status_active = GPIO_SET;

	struct msm_rpm_kvp kvp_sleep[] = {
		{
		.key = RPM_GPIO_NUMB_KEY,
		.data = (void *)&gpio_num,
		.length = sizeof(gpio_num),
		},
		{
		.key = RPM_GPIO_STAT_KEY,
		.data = (void *)&gpio_status_sleep,
		.length = sizeof(gpio_status_sleep),
		},
		{
		.key = RPM_GPIO_SETT_KEY,
		.data = (void *)&settling_time,
		.length = sizeof(settling_time),
		},
	};

	struct msm_rpm_kvp kvp_active[] = {
		{
		.key = RPM_GPIO_NUMB_KEY,
		.data = (void *)&gpio_num,
		.length = sizeof(gpio_num),
		},
		{
		.key = RPM_GPIO_STAT_KEY,
		.data = (void *)&gpio_status_active,
		.length = sizeof(gpio_status_active),
		},
		{
		.key = RPM_GPIO_SETT_KEY,
		.data = (void *)&settling_time,
		.length = sizeof(settling_time),
		},
	};

	rc = msm_rpm_send_message(MSM_RPM_CTX_SLEEP_SET,
		RPM_REQUEST_TYPE_GPIO, RPM_GPIO_RESOURCE_ID, kvp_sleep, 3);
	WARN(rc < 0, "RPM GPIO toggling (sleep set) did not enable!\n");

	rc = msm_rpm_send_message(MSM_RPM_CTX_ACTIVE_SET,
		RPM_REQUEST_TYPE_GPIO, RPM_GPIO_RESOURCE_ID, kvp_active, 3);
	WARN(rc < 0, "RPM GPIO toggling (active set) did not enable!\n");
}

int msm_get_ext_buck_presence(void)
{
	return msm_ext_buck;
}
EXPORT_SYMBOL(msm_get_ext_buck_presence);

static int msm_ext_buck_probe(struct platform_device *pdev)
{
	char *key = NULL;

	key = "qcom,ext-buck";
	msm_ext_buck = of_property_read_bool(pdev->dev.of_node, key);
	if (msm_ext_buck) {
		int gpio_num;
		int settling_time;

		key = "qcom,gpio-num";
		of_property_read_u32(pdev->dev.of_node, key,
							&gpio_num);

		key = "qcom,sett-time";
		of_property_read_u32(pdev->dev.of_node, key,
						&settling_time);

		msm_send_ext_buck_votes(gpio_num, settling_time);
	}

	return 0;
}

static struct of_device_id msm_ext_buck_table[] = {
	{.compatible = "qcom,ext-buck-support"},
	{},
};

static struct platform_driver msm_ext_buck_driver = {
	.probe = msm_ext_buck_probe,
	.driver = {
		.name = "ext-buck-support",
		.owner = THIS_MODULE,
		.of_match_table = msm_ext_buck_table,
	},
};

static int __init msm_ext_buck_init(void)
{
	return platform_driver_register(&msm_ext_buck_driver);
}
device_initcall(msm_ext_buck_init);
