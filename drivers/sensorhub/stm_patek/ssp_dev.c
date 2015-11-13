/*
 *  Copyright (C) 2012, Samsung Electronics Co. Ltd. All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */
#include "ssp.h"
#ifdef CONFIG_OF
#include <linux/of_gpio.h>
#endif
#if SSP_SEC_DEBUG
#include <mach/sec_debug.h>
#endif

#ifdef CONFIG_HAS_EARLYSUSPEND
static void ssp_early_suspend(struct early_suspend *handler);
static void ssp_late_resume(struct early_suspend *handler);
#endif

#define NORMAL_SENSOR_STATE_K	0x3FEFF

#define GES_LDO_ON  1
#define GES_LDO_OFF 0

#ifdef CONFIG_DUAL_LCD
int flip_status;
static struct ssp_data *ssp_data_check = NULL;

void magnetic_set_ssp_info(struct ssp_data *data)
{
	if (data != NULL)
		ssp_data_check = data;
	else
		pr_info("%s : ssp info is null\n", __func__);
}

static struct ssp_data *magnetic_get_ssp_info(void)
{
	return ssp_data_check;
}

void samsung_switching_ssp(int flip)
{
	struct ssp_data *data;

	data = magnetic_get_ssp_info();

	if (data == NULL){
		pr_err("[SSP] %s: ssp info is null\n", __func__);
		return;
	}

	flip_status = flip;

	if ((atomic_read(&data->aSensorEnable) & (1 << GEOMAGNETIC_SENSOR))
		|| (atomic_read(&data->aSensorEnable) & (1 << ORIENTATION_SENSOR))
		|| (atomic_read(&data->aSensorEnable) & (1 << ROTATION_VECTOR))){
	/*flip_status 0:open, 1:close*/
		set_magnetic_cal_with_folder_state(data, flip_status);
	pr_info("[SSP] %s : Folder is %sed now.\n", __func__,
			flip_status ? "clos":"open");
}
}
EXPORT_SYMBOL(samsung_switching_ssp);

int ssp_get_flip_status(void)
{
	return flip_status;
}
#endif

void ssp_enable(struct ssp_data *data, bool enable)
{
	pr_info("[SSP] %s, enable = %d, old enable = %d\n",
		__func__, enable, data->bSspShutdown);

	if (enable && data->bSspShutdown) {
		data->bSspShutdown = false;
		enable_irq(data->iIrq);
		enable_irq_wake(data->iIrq);
	} else if (!enable && !data->bSspShutdown) {
		data->bSspShutdown = true;
		disable_irq(data->iIrq);
		disable_irq_wake(data->iIrq);
	} else
		pr_err("[SSP] %s, enable error\n", __func__);
}
/************************************************************************/
/* interrupt happened due to transition/change of SSP MCU		*/
/************************************************************************/

static irqreturn_t sensordata_irq_thread_fn(int iIrq, void *dev_id)
{
	struct ssp_data *data = dev_id;
	if(gpio_get_value(data->mcu_int1)) {
		pr_info("[SSP] MCU int HIGH");
		return IRQ_HANDLED;
	}

	select_irq_msg(data);
	data->uIrqCnt++;

	return IRQ_HANDLED;
}

/*************************************************************************/
/* initialize sensor hub						 */
/*************************************************************************/

static void initialize_variable(struct ssp_data *data)
{
	int iSensorIndex;

	for (iSensorIndex = 0; iSensorIndex < SENSOR_MAX; iSensorIndex++) {
		data->adDelayBuf[iSensorIndex] = DEFUALT_POLLING_DELAY;
		data->batchLatencyBuf[iSensorIndex] = 0;
		data->batchOptBuf[iSensorIndex] = 0;
		data->aiCheckStatus[iSensorIndex] = INITIALIZATION_STATE;
	}

	atomic_set(&data->aSensorEnable, 0);
	data->iLibraryLength = 0;
	data->uSensorState = NORMAL_SENSOR_STATE_K;
	data->uFactoryProxAvg[0] = 0;
	data->uMagCntlRegData = 1;

	data->uResetCnt = 0;
	data->uTimeOutCnt = 0;
	data->uComFailCnt = 0;
	data->uIrqCnt = 0;

	data->bSspShutdown = true;
	data->bProximityRawEnabled = false;
	data->bGeomagneticRawEnabled = false;
	data->bBarcodeEnabled = false;
	data->bAccelAlert = false;
	data->bTimeSyncing = true;

	data->accelcal.x = 0;
	data->accelcal.y = 0;
	data->accelcal.z = 0;

	data->gyrocal.x = 0;
	data->gyrocal.y = 0;
	data->gyrocal.z = 0;

	data->magoffset.x = 0;
	data->magoffset.y = 0;
	data->magoffset.z = 0;

	data->iPressureCal = 0;
	data->uProxCanc = 0;
	data->uProxHiThresh = 0;
	data->uProxLoThresh = 0;
	data->uGyroDps = GYROSCOPE_DPS500;
	data->uIr_Current = 0;

	data->mcu_device = NULL;
	data->acc_device = NULL;
	data->gyro_device = NULL;
	data->mag_device = NULL;
	data->prs_device = NULL;
	data->prox_device = NULL;
	data->light_device = NULL;
	data->ges_device = NULL;

	data->voice_device = NULL;
#if SSP_SEC_DEBUG
	data->bMcuDumpMode = sec_debug_is_enabled();
#endif
	INIT_LIST_HEAD(&data->pending_list);

	data->step_count_total = 0;
	data->sealevelpressure = 0;
	initialize_function_pointer(data);
}

int initialize_mcu(struct ssp_data *data)
{
	int iRet = 0;

	clean_pending_list(data);

	iRet = get_chipid(data);
	pr_info("[SSP] MCU device ID = %d, reading ID = %d\n", DEVICE_ID, iRet);
	if (iRet != DEVICE_ID) {
		if (iRet < 0) {
			pr_err("[SSP]: %s - MCU is not working : 0x%x\n",
				__func__, iRet);
		} else {
			pr_err("[SSP]: %s - MCU identification failed\n",
				__func__);
			iRet = -ENODEV;
		}
		goto out;
	}

	iRet = set_sensor_position(data);
	if (iRet < 0) {
		pr_err("[SSP]: %s - set_sensor_position failed\n", __func__);
		goto out;
	}

	iRet = get_fuserom_data(data);
	if (iRet < 0)
		pr_err("[SSP]: %s - get_fuserom_data failed\n", __func__);

	data->uSensorState = get_sensor_scanning_info(data);
	if (data->uSensorState == 0) {
		pr_err("[SSP]: %s - get_sensor_scanning_info failed\n",
			__func__);
		iRet = ERROR;
		goto out;
	}

	data->uCurFirmRev = get_firmware_rev(data);
	pr_info("[SSP] MCU Firm Rev : New = %8u\n",
		data->uCurFirmRev);

	iRet = ssp_send_cmd(data, MSG2SSP_AP_MCU_DUMP_CHECK, 0);
out:
	return iRet;
}

static int initialize_irq(struct ssp_data *data)
{
	int iRet, iIrq;
	iIrq = gpio_to_irq(data->mcu_int1);

	pr_info("[SSP]: requesting IRQ %d\n", iIrq);
	iRet = request_threaded_irq(iIrq, NULL, sensordata_irq_thread_fn,
				    IRQF_TRIGGER_FALLING|IRQF_ONESHOT, "SSP_Int", data);
	if (iRet < 0) {
		pr_err("[SSP]: %s - request_irq(%d) failed for gpio %d (%d)\n",
		       __func__, iIrq, iIrq, iRet);
		goto err_request_irq;
	}

	/* start with interrupts disabled */
	data->iIrq = iIrq;
	disable_irq(data->iIrq);
	return 0;

err_request_irq:
	gpio_free(data->mcu_int1);
	return iRet;
}

static void work_function_firmware_update(struct work_struct *work)
{
	struct ssp_data *data = container_of((struct delayed_work *)work,
	struct ssp_data, work_firmware);
	int iRet = 0;

	pr_info("[SSP] : %s\n", __func__);

	iRet = forced_to_download_binary(data, KERNEL_BINARY);
	if (iRet < 0) {
		ssp_dbg("[SSP]: %s - forced_to_download_binary failed!\n",
			__func__);
		data->uSensorState = 0;
		return;
	}

	queue_refresh_task(data, SSP_SW_RESET_TIME);
}

static int ssp_parse_dt(struct device *dev,
	struct  ssp_data *data)
{
	struct device_node *np = dev->of_node;
	enum of_gpio_flags flags;
	int errorno = 0;

	data->mcu_int1 = of_get_named_gpio_flags(np, "ssp,mcu_int1-gpio",
		0, &flags);
	if (data->mcu_int1 < 0) {
		errorno = data->mcu_int1;
		goto dt_exit;
	}

	data->mcu_int2 = of_get_named_gpio_flags(np, "ssp,mcu_int2-gpio",
		0, &flags);
	if (data->mcu_int2 < 0) {
		errorno = data->mcu_int2;
		goto dt_exit;
	}

	data->ap_int = of_get_named_gpio_flags(np, "ssp,ap_int-gpio",
		0, &flags);
	if (data->ap_int < 0) {
		errorno = data->ap_int;
		goto dt_exit;
	}
#if defined(CONFIG_SEC_PATEK_PROJECT)
	if (of_property_read_string(np, "ssp,ges_vdd_1p8",
		&data->ges_vdd) < 0)
		 pr_err("%s - get ges_vdd error\n", __func__);

	if (of_property_read_string(np, "ssp,ges_led_3p3",
		&data->ges_led) < 0)
		pr_err("%s - get ges_led error\n", __func__);

	pr_err("%s - get ges_vcc pass\n", __func__);

#endif

#if defined(CONFIG_MACH_KLTE_JPN) || defined(CONFIG_MACH_KACTIVELTE_DCM)
#if defined(CONFIG_MACH_KLTE_MAX77828_JPN)
	data->rst = of_get_named_gpio_flags(np, "ssp,rst-gpio",
		0, &flags);
#else
	of_property_read_u32(np, "ssp,rst-gpio", &data->rst);
#endif
#else
	data->rst = of_get_named_gpio_flags(np, "ssp,rst-gpio",
		0, &flags);
#endif
	if (data->rst < 0) {
		errorno = data->rst ;
		goto dt_exit;
	}

	if (of_property_read_u32(np, "ssp,acc-position", &data->accel_position))
		data->accel_position = 0;

	if (of_property_read_u32(np, "ssp,mag-position", &data->mag_position))
		data->mag_position = 0;

	if (of_property_read_u32(np, "ssp,ap-rev", &data->ap_rev))
		data->ap_rev = 0;

	errorno = gpio_request(data->mcu_int1, "mpu_ap_int1");
	if (errorno) {
		pr_err("[SSP] failed to request MCU_INT2 for SSP\n");
		goto dt_exit;
	}

	errorno = gpio_direction_input(data->mcu_int1);
	if (errorno) {
		pr_err("[SSP] failed to set mcu_int1 as input\n");
		goto dt_exit;
	}

	errorno = gpio_request(data->mcu_int2, "MCU_INT2");
	if (errorno) {
		pr_err("[SSP] failed to request MCU_INT2 for SSP\n");
		goto dt_exit;
	}
	gpio_direction_input(data->mcu_int2);

	errorno = gpio_request(data->ap_int, "AP_MCU_INT");
	if (errorno) {
		pr_err("[SSP] failed to request AP_INT for SSP\n");
		goto dt_exit;
	}
	gpio_direction_output(data->ap_int, 1);

	errorno = gpio_request(data->rst, "MCU_RST");
	if (errorno) {
		pr_err("[SSP] failed to request MCU_RST for SSP\n");
		goto dt_exit;
	}
	gpio_direction_output(data->rst, 1);

	data->reg_hub = devm_regulator_get(dev, "hub_vreg");
	if (IS_ERR(data->reg_hub)) {
		pr_err("[SSP] could not get hub_vreg, %ld\n",
			PTR_ERR(data->reg_hub));
	} else {
		regulator_enable(data->reg_hub);
	}

	data->reg_sns= devm_regulator_get(dev, "psns_vreg");
	if (IS_ERR(data->reg_hub)) {
		pr_err("[SSP] could not get psns_vreg, %ld\n",
			PTR_ERR(data->reg_sns));
	} else {
		regulator_enable(data->reg_sns);
	}

dt_exit:
	return errorno;
}
#if defined(CONFIG_SEC_PATEK_PROJECT)
 static int ssp_gesture_regulator_onoff(struct ssp_data *data, int onoff)
 {
	int rc = 0;
	struct regulator *regulator_led_3p3;
	struct regulator *regulator_vdd_1p8;

	pr_info("[SSP] %s - start = %d\n", __func__, onoff);

	regulator_vdd_1p8 = regulator_get(NULL, data->ges_vdd);
	if (IS_ERR(regulator_vdd_1p8)) {
	pr_err("[SSP] %s - vdd_1p8 regulator_get fail\n", __func__);
		return -ENODEV;
	}

	regulator_led_3p3 = regulator_get(NULL, data->ges_led);
	if (IS_ERR(regulator_led_3p3)) {
		pr_err("[SSP] %s - vdd_3p3 regulator_get fail\n", __func__);
		regulator_put(regulator_vdd_1p8);
		return -ENODEV;
	}
	pr_info("[SSP] %s - onoff = %d\n", __func__, onoff);

	if (onoff == GES_LDO_ON) {
		regulator_set_voltage(regulator_vdd_1p8, 1800000, 1800000);
		rc = regulator_enable(regulator_vdd_1p8);
		if (rc) {
			pr_err("[SSP] %s - enable vdd_1p8 failed, rc=%d\n",
			__func__, rc);
			goto done;
		}
		regulator_set_voltage(regulator_led_3p3, 3300000, 3300000);
		rc = regulator_enable(regulator_led_3p3);
		if (rc) {
			pr_err("[SSP] %s - enable led_3p3 failed, rc=%d\n",
				__func__, rc);
			goto done;
		}
	}else {
		rc = regulator_disable(regulator_vdd_1p8);
		if (rc) {
			pr_err("[SSP] %s - disable vdd_1p8 failed, rc=%d\n",
				__func__, rc);
			goto done;
		}
		rc = regulator_disable(regulator_led_3p3);
		if (rc) {
			pr_err("[SSP] %s - disable led_3p3 failed, rc=%d\n",
				__func__, rc);
			goto done;
		}
	}

	data->regulator_is_enable = (u8)onoff;

done:
	regulator_put(regulator_led_3p3);
	regulator_put(regulator_vdd_1p8);

	return rc;
}
#endif
static int ssp_probe(struct spi_device *spi_dev)
{
	int iRet = 0;
	struct ssp_data *data;
	struct ssp_platform_data *pdata;
#if defined(CONFIG_SEC_PATEK_PROJECT)
	int err =-1;
#endif

	pr_info("[SSP] %s\n", __func__);

	if (poweroff_charging == 1 || boot_mode_recovery == 1) {
		pr_err("[SSP] probe exit : lpm %d, recovery %d\n",
			poweroff_charging, boot_mode_recovery);
		return -ENODEV;
	}

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (data == NULL) {
		pr_err("[SSP]: %s - failed to allocate memory for data\n",
			__func__);
		iRet = -ENOMEM;
		goto exit;
	}

	if (spi_dev->dev.of_node) {
		iRet = ssp_parse_dt(&spi_dev->dev, data);
		if (iRet) {
			pr_err("[SSP]: %s - Failed to parse DT\n", __func__);
			goto err_setup;
		}
		data->ssp_changes = SSP_MCU_L5; /* K330, MPU L5*/
	} else {
		pdata = spi_dev->dev.platform_data;
		if (pdata == NULL) {
			pr_err("[SSP]: %s - platform_data is null\n", __func__);
			iRet = -ENOMEM;
			goto err_setup;
		}
		data->wakeup_mcu = pdata->wakeup_mcu;
		data->check_mcu_ready = pdata->check_mcu_ready;
		data->check_mcu_busy = pdata->check_mcu_busy;
		data->set_mcu_reset = pdata->set_mcu_reset;
		data->read_chg = pdata->read_chg;

		/* AP system_rev */
		if (pdata->check_ap_rev)
			data->ap_rev = pdata->check_ap_rev();
		else
			data->ap_rev = 0;
		/* For changed devices */
		if (pdata->check_changes)
			data->ssp_changes = pdata->check_changes();
		else
			data->ssp_changes = SSP_MCU_L5; /* K330, MPU L5*/

		/* Get sensor positions */
		if (pdata->get_positions)
			pdata->get_positions(&data->accel_position,
				&data->mag_position);
		else if (spi_dev->dev.of_node == NULL) {
			data->accel_position = 0;
			data->mag_position = 0;
		}

	}
#if defined(CONFIG_SEC_PATEK_PROJECT)
       err = ssp_gesture_regulator_onoff(data, GES_LDO_ON);
       if (err < 0) {
		pr_err("[SSP] %s max88922_regulator_on fail err = %d\n",
			__func__, err);
		//goto err_setup;
	}
       usleep_range(1000, 1100);
#endif

	spi_dev->mode = SPI_MODE_1;
	if (spi_setup(spi_dev)) {
		pr_err("failed to setup spi for ssp_spi\n");
		goto err_setup;
	}

	data->bProbeIsDone = false;
	data->fw_dl_state = FW_DL_STATE_NONE;
	data->spi = spi_dev;
	spi_set_drvdata(spi_dev, data);

#ifdef CONFIG_DUAL_LCD
	magnetic_set_ssp_info(data);
#endif

#ifdef CONFIG_SENSORS_SSP_SHTC1
	mutex_init(&data->cp_temp_adc_lock);
	mutex_init(&data->bulk_temp_read_lock);
#endif
#ifdef CONFIG_SENSORS_SSP_STM
	mutex_init(&data->comm_mutex);
	mutex_init(&data->pending_mutex);
#endif

	if (((data->wakeup_mcu == NULL)
		|| (data->check_mcu_ready == NULL)
		|| (data->check_mcu_busy == NULL)
		|| (data->set_mcu_reset == NULL)
		|| (data->read_chg == NULL))
		&& (spi_dev->dev.of_node == NULL)) {
		pr_err("[SSP]: %s - function callback is null\n", __func__);
		iRet = -EIO;
		goto err_reset_null;
	}

	pr_info("\n#####################################################\n");

	INIT_DELAYED_WORK(&data->work_firmware, work_function_firmware_update);

	wake_lock_init(&data->ssp_wake_lock,
		WAKE_LOCK_SUSPEND, "ssp_wake_lock");

	iRet = initialize_input_dev(data);
	if (iRet < 0) {
		pr_err("[SSP]: %s - could not create input device\n", __func__);
		goto err_input_register_device;
	}

	iRet = initialize_debug_timer(data);
	if (iRet < 0) {
		pr_err("[SSP]: %s - could not create workqueue\n", __func__);
		goto err_create_workqueue;
	}

	iRet = initialize_irq(data);
	if (iRet < 0) {
		pr_err("[SSP]: %s - could not create irq\n", __func__);
		goto err_setup_irq;
	}

	iRet = initialize_sysfs(data);
	if (iRet < 0) {
		pr_err("[SSP]: %s - could not create sysfs\n", __func__);
		goto err_sysfs_create;
	}

	iRet = initialize_event_symlink(data);
	if (iRet < 0) {
		pr_err("[SSP]: %s - could not create symlink\n", __func__);
		goto err_symlink_create;
	}

	initialize_variable(data);

#ifdef CONFIG_SENSORS_SSP_SENSORHUB
	/* init sensorhub device */
	iRet = ssp_sensorhub_initialize(data);
	if (iRet < 0) {
		pr_err("%s: ssp_sensorhub_initialize err(%d)", __func__, iRet);
		ssp_sensorhub_remove(data);
	}
#endif

	ssp_enable(data, true);
	/* check boot loader binary */
	data->fw_dl_state = check_fwbl(data);

	if (data->fw_dl_state == FW_DL_STATE_NONE) {
		iRet = initialize_mcu(data);
		if (iRet == ERROR) {
			toggle_mcu_reset(data);
		} else if (iRet < ERROR) {
			pr_err("[SSP]: %s - initialize_mcu failed\n", __func__);
			goto err_read_reg;
		}
	}

#ifdef CONFIG_HAS_EARLYSUSPEND
	data->early_suspend.suspend = ssp_early_suspend;
	data->early_suspend.resume = ssp_late_resume;
	register_early_suspend(&data->early_suspend);
#endif
#ifdef CONFIG_DUAL_LCD
	/* if read gpio , 0: close, 1:open so flip_status 0:open, 1:close*/
	flip_status = !(gpio_get_value(HALL_SENSOR_INT_GPIO));
	pr_info("[SSP] %s : Folder is %sed now.\n", __func__,flip_status ? "clos":"open");
#endif

	pr_info("[SSP]: %s - probe success!\n", __func__);

	enable_debug_timer(data);

	iRet = 0;
	if (data->fw_dl_state == FW_DL_STATE_NEED_TO_SCHEDULE) {
		pr_info("[SSP]: Firmware update is scheduled\n");
		schedule_delayed_work(&data->work_firmware,
				msecs_to_jiffies(1000));
		data->fw_dl_state = FW_DL_STATE_SCHEDULED;
	} else if (data->fw_dl_state == FW_DL_STATE_FAIL)
		data->bSspShutdown = true;
	data->bProbeIsDone = true;

	goto exit;

err_read_reg:
err_symlink_create:
	remove_sysfs(data);
err_sysfs_create:
	free_irq(data->iIrq, data);
	gpio_free(data->mcu_int1);
err_setup_irq:
	destroy_workqueue(data->debug_wq);
err_create_workqueue:
	remove_input_dev(data);
err_input_register_device:
	wake_lock_destroy(&data->ssp_wake_lock);
err_reset_null:
#ifdef CONFIG_SENSORS_SSP_SHTC1
	mutex_destroy(&data->cp_temp_adc_lock);
	mutex_destroy(&data->bulk_temp_read_lock);
#endif
#ifdef CONFIG_SENSORS_SSP_STM
	mutex_destroy(&data->comm_mutex);
	mutex_destroy(&data->pending_mutex);
#endif

err_setup:
	kfree(data);
	pr_err("[SSP]: %s - probe failed!\n", __func__);
exit:
	pr_info("#####################################################\n\n");
	return iRet;
}

static void ssp_shutdown(struct spi_device *spi_dev)
{
	struct ssp_data *data = spi_get_drvdata(spi_dev);

	func_dbg();
	if (data->bProbeIsDone == false)
		goto exit;

	if (data->fw_dl_state >= FW_DL_STATE_SCHEDULED &&
		data->fw_dl_state < FW_DL_STATE_DONE) {
		pr_err("%s, cancel_delayed_work_sync state = %d\n",
			__func__, data->fw_dl_state);
		cancel_delayed_work_sync(&data->work_firmware);
	}

	disable_debug_timer(data);

	if (SUCCESS != ssp_send_cmd(data, MSG2SSP_AP_STATUS_SHUTDOWN, 0))
		pr_err("[SSP]: %s MSG2SSP_AP_STATUS_SHUTDOWN failed\n",
			__func__);

	ssp_enable(data, false);
	clean_pending_list(data);

#ifdef CONFIG_HAS_EARLYSUSPEND
	unregister_early_suspend(&data->early_suspend);
#endif

	free_irq(data->iIrq, data);
	gpio_free(data->mcu_int1);

	remove_event_symlink(data);
	remove_sysfs(data);
	remove_input_dev(data);

#ifdef CONFIG_SENSORS_SSP_SENSORHUB
	ssp_sensorhub_remove(data);
#endif

	cancel_delayed_work_sync(&data->work_refresh);
	destroy_workqueue(data->debug_wq);
	wake_lock_destroy(&data->ssp_wake_lock);
#ifdef CONFIG_SENSORS_SSP_SHTC1
	mutex_destroy(&data->cp_temp_adc_lock);
	mutex_destroy(&data->bulk_temp_read_lock);
#endif
#ifdef CONFIG_SENSORS_SSP_STM
	mutex_destroy(&data->comm_mutex);
	mutex_destroy(&data->pending_mutex);
#endif
	toggle_mcu_reset(data);
/*	gpio_set_value_cansleep(data->rst, 0); */
	pr_info("[SSP]: %s done\n", __func__);
exit:
	kfree(data);
}

#ifdef CONFIG_HAS_EARLYSUSPEND
static void ssp_early_suspend(struct early_suspend *handler)
{
	struct ssp_data *data;
	data = container_of(handler, struct ssp_data, early_suspend);

	func_dbg();
	disable_debug_timer(data);

#ifdef CONFIG_SENSORS_SSP_SENSORHUB
	/* give notice to user that AP goes to sleep */
	ssp_sensorhub_report_notice(data, MSG2SSP_AP_STATUS_SLEEP);
	ssp_sleep_mode(data);
	data->uLastAPState = MSG2SSP_AP_STATUS_SLEEP;
#else
	if (atomic_read(&data->aSensorEnable) > 0)
		ssp_sleep_mode(data);
#endif
}

static void ssp_late_resume(struct early_suspend *handler)
{
	struct ssp_data *data;
	data = container_of(handler, struct ssp_data, early_suspend);

	func_dbg();
	enable_debug_timer(data);

#ifdef CONFIG_SENSORS_SSP_SENSORHUB
	/* give notice to user that AP goes to sleep */
	ssp_sensorhub_report_notice(data, MSG2SSP_AP_STATUS_WAKEUP);
	ssp_resume_mode(data);
	data->uLastAPState = MSG2SSP_AP_STATUS_WAKEUP;
#else
	if (atomic_read(&data->aSensorEnable) > 0)
		ssp_resume_mode(data);
#endif
}

#else /* CONFIG_HAS_EARLYSUSPEND */

static int ssp_suspend(struct device *dev)
{
	struct spi_device *spi_dev = to_spi_device(dev);
	struct ssp_data *data = spi_get_drvdata(spi_dev);

	func_dbg();
	data->uLastResumeState = MSG2SSP_AP_STATUS_SUSPEND;
	disable_debug_timer(data);

	if (SUCCESS != ssp_send_cmd(data, MSG2SSP_AP_STATUS_SUSPEND, 0))
		pr_err("[SSP]: %s MSG2SSP_AP_STATUS_SUSPEND failed\n",
			__func__);
	data->bTimeSyncing = false;
	disable_irq(data->iIrq);
	return 0;
}

static int ssp_resume(struct device *dev)
{
	struct spi_device *spi_dev = to_spi_device(dev);
	struct ssp_data *data = spi_get_drvdata(spi_dev);
	enable_irq(data->iIrq);
	func_dbg();
	enable_debug_timer(data);

	if (SUCCESS != ssp_send_cmd(data, MSG2SSP_AP_STATUS_RESUME, 0))
		pr_err("[SSP]: %s MSG2SSP_AP_STATUS_RESUME failed\n",
			__func__);
	data->uLastResumeState = MSG2SSP_AP_STATUS_RESUME;

	return 0;
}

static const struct dev_pm_ops ssp_pm_ops = {
	.suspend = ssp_suspend,
	.resume = ssp_resume
};
#endif /* CONFIG_HAS_EARLYSUSPEND */

static const struct spi_device_id ssp_id[] = {
	{"ssp", 0},
	{}
};

MODULE_DEVICE_TABLE(spi, ssp_id);
#ifdef CONFIG_OF
static struct of_device_id ssp_match_table[] = {
	{ .compatible = "ssp,STM32F",},
	{},
};
#else
#define mpu6500_match_table NULL
#endif

static struct spi_driver ssp_driver = {
	.probe = ssp_probe,
	.shutdown = ssp_shutdown,
	.id_table = ssp_id,
	.driver = {
#ifndef CONFIG_HAS_EARLYSUSPEND
		   .pm = &ssp_pm_ops,
#endif
		   .owner = THIS_MODULE,
		   .name = "ssp",
		   .of_match_table = ssp_match_table
		},
};

module_spi_driver(ssp_driver);
MODULE_DESCRIPTION("ssp driver");
MODULE_AUTHOR("Samsung Electronics");
MODULE_LICENSE("GPL");
