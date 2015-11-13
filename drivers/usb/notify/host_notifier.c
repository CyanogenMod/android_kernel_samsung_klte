/*
 * Copyright (C) 2011-2013 Samsung Electronics Co. Ltd.
 *  Hyuk Kang <hyuk78.kang@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/usb/otg.h>
#include <linux/host_notify.h>
#if defined(CONFIG_MFD_MAX77803)
#include <linux/mfd/max77803.h>
#elif defined(CONFIG_MFD_MAX77804K)
#include <linux/mfd/max77804k.h>
#endif
#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "notifier %s %d: " fmt, __func__, __LINE__

struct  hnotifier_info {
	struct usb_phy *phy;
	struct host_notify_dev ndev;
	struct work_struct noti_work;
	struct booster_data *booster;

	int event;
	int prev_event;
};

static struct hnotifier_info ninfo = {
	.ndev.name = "usb_otg",
};

extern int sec_handle_event(int enable);
static int safe_boost(struct hnotifier_info *pinfo, int enable)
{
	if (pinfo && pinfo->booster) {
		pinfo->booster->boost(enable);
		return 0;
	} else {
		pr_err("Error! No booster.\n");
		return -1;
	}
}

static int host_notifier_booster(int enable, struct host_notify_dev *ndev)
{
	struct hnotifier_info *pinfo;
	int ret = 0;
	pr_info("booster %s\n", enable ? "ON" : "OFF");

	pinfo = container_of(ndev, struct hnotifier_info, ndev);
	safe_boost(pinfo, enable);

	return ret;
}

static void hnotifier_work(struct work_struct *w)
{
	struct hnotifier_info *pinfo;
	int event;

	pinfo = container_of(w, struct hnotifier_info, noti_work);
	event = pinfo->event;
	pr_info("hnotifier_work : event %d\n", pinfo->event);

	switch (event) {
	case HNOTIFY_NONE:
	case HNOTIFY_VBUS: break;
	case HNOTIFY_ID:
		pr_info("!ID\n");
		host_state_notify(&pinfo->ndev,	NOTIFY_HOST_ADD);
#if defined(CONFIG_MUIC_MAX77804K_SUPPORT_LANHUB)
		safe_boost(pinfo, 2);
#else
		safe_boost(pinfo, 1);
#endif
		sec_handle_event(1);
		break;
	case HNOTIFY_ENUMERATED:
	case HNOTIFY_CHARGER: break;
	case HNOTIFY_ID_PULL:
		pr_info("ID\n");
		host_state_notify(&pinfo->ndev,	NOTIFY_HOST_REMOVE);
		sec_handle_event(0);
		safe_boost(pinfo, 0);
		break;
	case HNOTIFY_OVERCURRENT:
		pr_info("OVP\n");
		host_state_notify(&pinfo->ndev,	NOTIFY_HOST_OVERCURRENT);
		break;
	case HNOTIFY_OTG_POWER_ON:
		pinfo->ndev.booster = NOTIFY_POWER_ON;
		break;
	case HNOTIFY_OTG_POWER_OFF:
		pinfo->ndev.booster = NOTIFY_POWER_OFF;
		break;
	case HNOTIFY_SMARTDOCK_ON:
		sec_handle_event(1);
		break;
	case HNOTIFY_SMARTDOCK_OFF:
		sec_handle_event(0);
		break;
	case HNOTIFY_AUDIODOCK_ON:
		sec_handle_event(1);
		break;
	case HNOTIFY_AUDIODOCK_OFF:
		sec_handle_event(0);
		break;
	case HNOTIFY_LANHUB_ON:
		host_state_notify(&pinfo->ndev,	NOTIFY_HOST_ADD);
		sec_handle_event(1);
		break;
	case HNOTIFY_LANHUB_OFF:
		host_state_notify(&pinfo->ndev,	NOTIFY_HOST_REMOVE);
		sec_handle_event(0);
		break;
	case HNOTIFY_LANHUBTA_ON:
		safe_boost(pinfo, 2);
		break;
	case HNOTIFY_LANHUBTA_OFF:
		safe_boost(pinfo, 1);
		break;
	default:
		break;
	}

#if 0
	atomic_notifier_call_chain(&pinfo->phy->notifier,
		event, pinfo);
#endif
}

int sec_otg_notify(int event)
{
	pr_info("sec_otg_notify : %d\n", event);
	ninfo.prev_event = ninfo.event;
	ninfo.event = event;

	if (ninfo.phy)
		schedule_work(&ninfo.noti_work);
	return 0;
}
EXPORT_SYMBOL(sec_otg_notify);

int sec_otg_register_booster(struct booster_data *booster)
{
	int ret = 0;
	if (ninfo.booster) {
		pr_err("booster %s is already registered.\n", ninfo.booster->name);
		return -EBUSY;
	}

	if (booster && booster->name && booster->boost) {
		pr_info("register %s\n", booster->name);
		ninfo.booster = booster;
	} else {
		pr_err("register failed\n");
		ret = -ENODATA;
	}
	return ret;
}
EXPORT_SYMBOL(sec_otg_register_booster);

int sec_get_notification(int ndata)
{
	int ret = 0;

	switch (ndata) {
	case HNOTIFY_EVENT:		ret = ninfo.event; break;
	case HNOTIFY_MODE:		ret = ninfo.ndev.mode; break;
	case HNOTIFY_BOOSTER:	ret = ninfo.ndev.booster; break;
	default:
		break;
	}

	pr_info("ndata %d : %d\n", ndata, ret);
	return ret;
}
EXPORT_SYMBOL(sec_get_notification);

static int host_notifier_probe(struct platform_device *pdev)
{
	int ret = 0;

	dev_info(&pdev->dev, "notifier_probe\n");

	INIT_WORK(&ninfo.noti_work, hnotifier_work);

	ninfo.ndev.set_booster = host_notifier_booster;
	ninfo.phy = usb_get_transceiver();

	if(!ninfo.phy){
		return -ENODEV;
	}
	ATOMIC_INIT_NOTIFIER_HEAD(&ninfo.phy->notifier);

	ret = host_notify_dev_register(&ninfo.ndev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to host_notify_dev_register\n");
		return ret;
	}
	return 0;
}

static int host_notifier_remove(struct platform_device *pdev)
{
	cancel_work_sync(&ninfo.noti_work);
	host_notify_dev_unregister(&ninfo.ndev);
	return 0;
}

static struct of_device_id host_notifier_of_match[] = {
	{	.compatible = "sec,host-notifier", },
	{}
};

static struct platform_driver host_notifier_driver = {
	.probe		= host_notifier_probe,
	.remove		= host_notifier_remove,
	.driver		= {
		.name	= "host_notifier",
		.owner	= THIS_MODULE,
		.of_match_table = host_notifier_of_match,
	},
};
module_platform_driver(host_notifier_driver);

MODULE_AUTHOR("Hyuk Kang <hyuk78.kang@samsung.com>");
MODULE_DESCRIPTION("USB Host notifier");
MODULE_LICENSE("GPL");
