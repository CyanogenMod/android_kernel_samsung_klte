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
#include "../../staging/iio/iio.h"
#include "../../staging/iio/events.h"
#include "../../staging/iio/sysfs.h"
#include "../../staging/iio/buffer.h"
#include "../../staging/iio/types.h"

/*************************************************************************/
/* SSP Kernel -> HAL input evnet function                                */
/*************************************************************************/

#define IIO_BUFFER_12_BYTES         20 /* 12 + timestamp 8*/
#define IIO_BUFFER_6_BYTES         14
#define IIO_BUFFER_1_BYTES			9
#define IIO_BUFFER_17_BYTES			25

/* data header defines */

static int ssp_push_17bytes_buffer(struct iio_dev *indio_dev,
							u64 t, int *q)
{
	u8 buf[IIO_BUFFER_17_BYTES];
	
	int i;

	for (i = 0; i < 4; i++)
		memcpy(buf + 4 * i, &q[i], sizeof(q[i]));
	buf[16] = (u8)q[5];
	memcpy(buf + 17, &t, sizeof(t));
	mutex_lock(&indio_dev->mlock);
	iio_push_to_buffer(indio_dev->buffer, buf, 0);
	mutex_unlock(&indio_dev->mlock);

	return 0;
}

static int ssp_push_12bytes_buffer(struct iio_dev *indio_dev, u64 t,
									int *q)
{
	u8 buf[IIO_BUFFER_12_BYTES];
	int i;

	for (i = 0; i < 3; i++)
		memcpy(buf + 4 * i, &q[i], sizeof(q[i]));
	memcpy(buf + 12, &t, sizeof(t));
	mutex_lock(&indio_dev->mlock);
	iio_push_to_buffer(indio_dev->buffer, buf, 0);
	mutex_unlock(&indio_dev->mlock);

	return 0;
}

static int ssp_push_6bytes_buffer(struct iio_dev *indio_dev,
							u64 t, s16 *d)
{
	u8 buf[IIO_BUFFER_6_BYTES];
	int i;

	for (i = 0; i < 3; i++)
		memcpy(buf + i * 2, &d[i], sizeof(d[i]));

	memcpy(buf + 6, &t, sizeof(t));
	mutex_lock(&indio_dev->mlock);
	iio_push_to_buffer(indio_dev->buffer, buf, 0);
	mutex_unlock(&indio_dev->mlock);

	return 0;
}

static int ssp_push_1bytes_buffer(struct iio_dev *indio_dev,
							u64 t, u8 *d)
{
	u8 buf[IIO_BUFFER_1_BYTES];

	memcpy(buf, d, sizeof(u8));
	memcpy(buf + 1, &t, sizeof(t));
	mutex_lock(&indio_dev->mlock);
	iio_push_to_buffer(indio_dev->buffer, buf, 0);
	mutex_unlock(&indio_dev->mlock);

	return 0;
}

void convert_acc_data(s16 *iValue)
{
	if (*iValue > MAX_ACCEL_2G)
		*iValue = ((MAX_ACCEL_4G - *iValue)) * (-1);
}

void report_acc_data(struct ssp_data *data, struct sensor_value *accdata)
{
	s16 accel_buf[3];
	data->buf[ACCELEROMETER_SENSOR].x = accdata->x;
	data->buf[ACCELEROMETER_SENSOR].y = accdata->y;
	data->buf[ACCELEROMETER_SENSOR].z = accdata->z;

	accel_buf[0] = data->buf[ACCELEROMETER_SENSOR].x;
	accel_buf[1] = data->buf[ACCELEROMETER_SENSOR].y;
	accel_buf[2] = data->buf[ACCELEROMETER_SENSOR].z;
	ssp_push_6bytes_buffer(data->accel_indio_dev, accdata->timestamp,
		accel_buf);
}

void report_meta_data(struct ssp_data *data, struct sensor_value *s)
{
	input_report_rel(data->meta_input_dev, REL_DIAL, s->meta_data.what);
	input_report_rel(data->meta_input_dev, REL_HWHEEL, s->meta_data.sensor + 1);
	input_sync(data->meta_input_dev);
}

void report_gyro_data(struct ssp_data *data, struct sensor_value *gyrodata)
{
	int lTemp[3] = {0,};
	data->buf[GYROSCOPE_SENSOR].x = gyrodata->x;
	data->buf[GYROSCOPE_SENSOR].y = gyrodata->y;
	data->buf[GYROSCOPE_SENSOR].z = gyrodata->z;

	if (data->uGyroDps == GYROSCOPE_DPS500) {
		lTemp[0] = (int)data->buf[GYROSCOPE_SENSOR].x;
		lTemp[1] = (int)data->buf[GYROSCOPE_SENSOR].y;
		lTemp[2] = (int)data->buf[GYROSCOPE_SENSOR].z;
	} else if (data->uGyroDps == GYROSCOPE_DPS250)	{
		lTemp[0] = (int)data->buf[GYROSCOPE_SENSOR].x >> 1;
		lTemp[1] = (int)data->buf[GYROSCOPE_SENSOR].y >> 1;
		lTemp[2] = (int)data->buf[GYROSCOPE_SENSOR].z >> 1;
	} else if (data->uGyroDps == GYROSCOPE_DPS2000)	{
		lTemp[0] = (int)data->buf[GYROSCOPE_SENSOR].x << 2;
		lTemp[1] = (int)data->buf[GYROSCOPE_SENSOR].y << 2;
		lTemp[2] = (int)data->buf[GYROSCOPE_SENSOR].z << 2;
	} else {
		lTemp[0] = (int)data->buf[GYROSCOPE_SENSOR].x;
		lTemp[1] = (int)data->buf[GYROSCOPE_SENSOR].y;
		lTemp[2] = (int)data->buf[GYROSCOPE_SENSOR].z;
	}

	ssp_push_12bytes_buffer(data->gyro_indio_dev, gyrodata->timestamp,
		lTemp);
}

void report_geomagnetic_raw_data(struct ssp_data *data,
	struct sensor_value *magrawdata)
{
	data->buf[GEOMAGNETIC_RAW].x = magrawdata->x;
	data->buf[GEOMAGNETIC_RAW].y = magrawdata->y;
	data->buf[GEOMAGNETIC_RAW].z = magrawdata->z;
}
void report_mag_data(struct ssp_data *data, struct sensor_value *magdata)
{
#ifdef SAVE_MAG_LOG
	s16 arrTemp[9] = {0, };

	arrTemp[0] = magdata->log_data[0];	// ST1 Reg
	arrTemp[1] = (short)((magdata->log_data[3] << 8) +\
				magdata->log_data[2]);
	arrTemp[2] = (short)((magdata->log_data[5] << 8) +\
				magdata->log_data[4]);
	arrTemp[3] = (short)((magdata->log_data[7] << 8) +\
				magdata->log_data[6]);
	arrTemp[4] = magdata->log_data[1];	// ST2 Reg
	arrTemp[5] = (short)((magdata->log_data[9] << 8) +\
				magdata->log_data[8]);
	arrTemp[6] = (short)((magdata->log_data[11] << 8) +\
				magdata->log_data[10]);
	arrTemp[7] = (short)((magdata->log_data[13] << 8) +\
				magdata->log_data[12]);

	/* We report data & register to HAL only when ST1 register sets to 1 */
	if (arrTemp[0] == 1) {
		input_report_rel(data->mag_input_dev, REL_X, arrTemp[0] + 1);
		input_report_rel(data->mag_input_dev, REL_Y, arrTemp[1]);
		input_report_rel(data->mag_input_dev, REL_Z, arrTemp[2]);
		input_report_rel(data->mag_input_dev, REL_RX, arrTemp[3]);
		input_report_rel(data->mag_input_dev, REL_RY, arrTemp[4] + 1);
		input_report_rel(data->mag_input_dev, REL_RZ, arrTemp[5]);
		input_report_rel(data->mag_input_dev, REL_HWHEEL, arrTemp[6]);
		input_report_rel(data->mag_input_dev, REL_DIAL, arrTemp[7]);
		mdelay(5);
		input_sync(data->mag_input_dev);
	} else {
		pr_info("[SSP] %s, not initialised, val = %d", __func__, arrTemp[0]);
	}
#else
	data->buf[GEOMAGNETIC_SENSOR].cal_x = magdata->cal_x;
	data->buf[GEOMAGNETIC_SENSOR].cal_y = magdata->cal_y;
	data->buf[GEOMAGNETIC_SENSOR].cal_z = magdata->cal_z;
	data->buf[GEOMAGNETIC_SENSOR].accuracy = magdata->accuracy;

	input_report_rel(data->mag_input_dev, REL_RX,
		data->buf[GEOMAGNETIC_SENSOR].cal_x);
	input_report_rel(data->mag_input_dev, REL_RY,
		data->buf[GEOMAGNETIC_SENSOR].cal_y);
	input_report_rel(data->mag_input_dev, REL_RZ,
		data->buf[GEOMAGNETIC_SENSOR].cal_z);
	input_report_rel(data->mag_input_dev, REL_HWHEEL,
		data->buf[GEOMAGNETIC_SENSOR].accuracy + 1);

	input_sync(data->mag_input_dev);
#endif
}

void report_mag_uncaldata(struct ssp_data *data, struct sensor_value *magdata)
{
	data->buf[GEOMAGNETIC_UNCALIB_SENSOR].uncal_x = magdata->uncal_x;
	data->buf[GEOMAGNETIC_UNCALIB_SENSOR].uncal_y = magdata->uncal_y;
	data->buf[GEOMAGNETIC_UNCALIB_SENSOR].uncal_z = magdata->uncal_z;
	data->buf[GEOMAGNETIC_UNCALIB_SENSOR].offset_x= magdata->offset_x;
	data->buf[GEOMAGNETIC_UNCALIB_SENSOR].offset_y= magdata->offset_y;
	data->buf[GEOMAGNETIC_UNCALIB_SENSOR].offset_z= magdata->offset_z;

	input_report_rel(data->uncal_mag_input_dev, REL_RX,
		data->buf[GEOMAGNETIC_UNCALIB_SENSOR].uncal_x);
	input_report_rel(data->uncal_mag_input_dev, REL_RY,
		data->buf[GEOMAGNETIC_UNCALIB_SENSOR].uncal_y);
	input_report_rel(data->uncal_mag_input_dev, REL_RZ,
		data->buf[GEOMAGNETIC_UNCALIB_SENSOR].uncal_z);
	input_report_rel(data->uncal_mag_input_dev, REL_HWHEEL,
		data->buf[GEOMAGNETIC_UNCALIB_SENSOR].offset_x);
	input_report_rel(data->uncal_mag_input_dev, REL_DIAL,
		data->buf[GEOMAGNETIC_UNCALIB_SENSOR].offset_y);
	input_report_rel(data->uncal_mag_input_dev, REL_WHEEL,
		data->buf[GEOMAGNETIC_UNCALIB_SENSOR].offset_z);
	input_sync(data->uncal_mag_input_dev);
}

void report_uncalib_gyro_data(struct ssp_data *data, struct sensor_value *gyrodata)
{
	data->buf[GYRO_UNCALIB_SENSOR].uncal_x = gyrodata->uncal_x;
	data->buf[GYRO_UNCALIB_SENSOR].uncal_y = gyrodata->uncal_y;
	data->buf[GYRO_UNCALIB_SENSOR].uncal_z = gyrodata->uncal_z;
	data->buf[GYRO_UNCALIB_SENSOR].offset_x = gyrodata->offset_x;
	data->buf[GYRO_UNCALIB_SENSOR].offset_y = gyrodata->offset_y;
	data->buf[GYRO_UNCALIB_SENSOR].offset_z = gyrodata->offset_z;

	input_report_rel(data->uncalib_gyro_input_dev, REL_X,
		data->buf[GYRO_UNCALIB_SENSOR].uncal_x);
	input_report_rel(data->uncalib_gyro_input_dev, REL_Y,
		data->buf[GYRO_UNCALIB_SENSOR].uncal_y);
	input_report_rel(data->uncalib_gyro_input_dev, REL_Z,
		data->buf[GYRO_UNCALIB_SENSOR].uncal_z);
	input_report_rel(data->uncalib_gyro_input_dev, REL_RX,
		data->buf[GYRO_UNCALIB_SENSOR].offset_x);
	input_report_rel(data->uncalib_gyro_input_dev, REL_RY,
		data->buf[GYRO_UNCALIB_SENSOR].offset_y);
	input_report_rel(data->uncalib_gyro_input_dev, REL_RZ,
		data->buf[GYRO_UNCALIB_SENSOR].offset_z);
	input_sync(data->uncalib_gyro_input_dev);
}

void report_sig_motion_data(struct ssp_data *data,
	struct sensor_value *sig_motion_data)
{
	data->buf[SIG_MOTION_SENSOR].sig_motion = sig_motion_data->sig_motion;

	input_report_rel(data->sig_motion_input_dev, REL_MISC,
		data->buf[SIG_MOTION_SENSOR].sig_motion);
	input_sync(data->sig_motion_input_dev);
}

void report_rot_data(struct ssp_data *data, struct sensor_value *rotdata)
{
	int rot_buf[5];
	data->buf[ROTATION_VECTOR].quat_a = rotdata->quat_a;
	data->buf[ROTATION_VECTOR].quat_b = rotdata->quat_b;
	data->buf[ROTATION_VECTOR].quat_c = rotdata->quat_c;
	data->buf[ROTATION_VECTOR].quat_d = rotdata->quat_d;
	data->buf[ROTATION_VECTOR].acc_rot = rotdata->acc_rot;
	rot_buf[0] = rotdata->quat_a;
	rot_buf[1] = rotdata->quat_b;
	rot_buf[2] = rotdata->quat_c;
	rot_buf[3] = rotdata->quat_d;
	rot_buf[4] = rotdata->acc_rot;
	ssp_push_17bytes_buffer(data->rot_indio_dev, rotdata->timestamp, rot_buf);
}

void report_game_rot_data(struct ssp_data *data, struct sensor_value *grotdata)
{
	int rot_buf[5];
	data->buf[GAME_ROTATION_VECTOR].quat_a = grotdata->quat_a;
	data->buf[GAME_ROTATION_VECTOR].quat_b = grotdata->quat_b;
	data->buf[GAME_ROTATION_VECTOR].quat_c = grotdata->quat_c;
	data->buf[GAME_ROTATION_VECTOR].quat_d = grotdata->quat_d;
	data->buf[GAME_ROTATION_VECTOR].acc_rot = grotdata->acc_rot;

	rot_buf[0] = grotdata->quat_a;
	rot_buf[1] = grotdata->quat_b;
	rot_buf[2] = grotdata->quat_c;
	rot_buf[3] = grotdata->quat_d;
	rot_buf[4] = grotdata->acc_rot;
	ssp_push_17bytes_buffer(data->game_rot_indio_dev, grotdata->timestamp,
		rot_buf);
}

void report_gesture_data(struct ssp_data *data, struct sensor_value *gesdata)
{
	int i = 0;
#if defined (CONFIG_SENSORS_SSP_MAX88921)
	int ges_max = 19;
#else
	int ges_max = 20;
#endif
	for (i=0; i<ges_max; i++) {
		data->buf[GESTURE_SENSOR].data[i] = gesdata->data[i];
	}

	input_report_abs(data->gesture_input_dev,
		ABS_X, data->buf[GESTURE_SENSOR].data[0]);
	input_report_abs(data->gesture_input_dev,
		ABS_Y, data->buf[GESTURE_SENSOR].data[1]);
	input_report_abs(data->gesture_input_dev,
		ABS_Z, data->buf[GESTURE_SENSOR].data[2]);
	input_report_abs(data->gesture_input_dev,
		ABS_RX, data->buf[GESTURE_SENSOR].data[3]);
	input_report_abs(data->gesture_input_dev,
		ABS_RY, data->buf[GESTURE_SENSOR].data[4]);
	input_report_abs(data->gesture_input_dev,
		ABS_RZ, data->buf[GESTURE_SENSOR].data[5]);
	input_report_abs(data->gesture_input_dev,
		ABS_THROTTLE, data->buf[GESTURE_SENSOR].data[6]);
	input_report_abs(data->gesture_input_dev,
		ABS_RUDDER, data->buf[GESTURE_SENSOR].data[7]);
	input_report_abs(data->gesture_input_dev,
		ABS_WHEEL, data->buf[GESTURE_SENSOR].data[8]);
	input_report_abs(data->gesture_input_dev,
		ABS_GAS, data->buf[GESTURE_SENSOR].data[9]);
	input_report_abs(data->gesture_input_dev,
		ABS_BRAKE, data->buf[GESTURE_SENSOR].data[10]);
	input_report_abs(data->gesture_input_dev,
		ABS_HAT0X, data->buf[GESTURE_SENSOR].data[11]);
	input_report_abs(data->gesture_input_dev,
		ABS_HAT0Y, data->buf[GESTURE_SENSOR].data[12]);
	input_report_abs(data->gesture_input_dev,
		ABS_HAT1X, data->buf[GESTURE_SENSOR].data[13]);
	input_report_abs(data->gesture_input_dev,
		ABS_HAT1Y, data->buf[GESTURE_SENSOR].data[14]);
	input_report_abs(data->gesture_input_dev,
		ABS_HAT2X, data->buf[GESTURE_SENSOR].data[15]);
	input_report_abs(data->gesture_input_dev,
		ABS_HAT2Y, data->buf[GESTURE_SENSOR].data[16]);
	input_report_abs(data->gesture_input_dev,
		ABS_HAT3X, data->buf[GESTURE_SENSOR].data[17]);
	input_report_abs(data->gesture_input_dev,
		ABS_HAT3Y, data->buf[GESTURE_SENSOR].data[18]);
#if !defined (CONFIG_SENSORS_SSP_MAX88921)
	input_report_abs(data->gesture_input_dev,
		ABS_PRESSURE, data->buf[GESTURE_SENSOR].data[19]);
#endif
	input_sync(data->gesture_input_dev);
}

void report_pressure_data(struct ssp_data *data, struct sensor_value *predata)
{
	int temp[3] = {0, };
	data->buf[PRESSURE_SENSOR].pressure[0] =
		predata->pressure[0] - data->iPressureCal;
	data->buf[PRESSURE_SENSOR].pressure[1] = predata->pressure[1];

	temp[0] = data->buf[PRESSURE_SENSOR].pressure[0];
	temp[1] = data->buf[PRESSURE_SENSOR].pressure[1];
	temp[2] = data->sealevelpressure;

	ssp_push_12bytes_buffer(data->pressure_indio_dev, predata->timestamp,
		temp);
}

void report_light_data(struct ssp_data *data, struct sensor_value *lightdata)
{
	data->buf[LIGHT_SENSOR].r = lightdata->r;
	data->buf[LIGHT_SENSOR].g = lightdata->g;
	data->buf[LIGHT_SENSOR].b = lightdata->b;
	data->buf[LIGHT_SENSOR].w = lightdata->w;
#if defined (CONFIG_SENSORS_SSP_TMG399X)
	data->buf[LIGHT_SENSOR].a_time = lightdata->a_time;
	data->buf[LIGHT_SENSOR].a_gain = (0x03) & (lightdata->a_gain);
#elif defined (CONFIG_SENSORS_SSP_MAX88921)
	data->buf[LIGHT_SENSOR].ir_cmp = lightdata->ir_cmp;
	data->buf[LIGHT_SENSOR].amb_pga = lightdata->amb_pga;
#endif

	input_report_rel(data->light_input_dev, REL_HWHEEL,
		data->buf[LIGHT_SENSOR].r + 1);
	input_report_rel(data->light_input_dev, REL_DIAL,
		data->buf[LIGHT_SENSOR].g + 1);
	input_report_rel(data->light_input_dev, REL_WHEEL,
		data->buf[LIGHT_SENSOR].b + 1);
	input_report_rel(data->light_input_dev, REL_MISC,
		data->buf[LIGHT_SENSOR].w + 1);
#if defined (CONFIG_SENSORS_SSP_TMG399X)
	input_report_rel(data->light_input_dev, REL_RY,
		data->buf[LIGHT_SENSOR].a_time + 1);
	input_report_rel(data->light_input_dev, REL_RZ,
		data->buf[LIGHT_SENSOR].a_gain + 1);
#elif defined (CONFIG_SENSORS_SSP_MAX88921)
	input_report_rel(data->light_input_dev, REL_RY,
		data->buf[LIGHT_SENSOR].ir_cmp + 1);
	input_report_rel(data->light_input_dev, REL_RZ,
		data->buf[LIGHT_SENSOR].amb_pga + 1);
#endif
	input_sync(data->light_input_dev);
}

void report_prox_data(struct ssp_data *data, struct sensor_value *proxdata)
{
	ssp_dbg("[SSP] Proximity Sensor Detect : %u, raw : %u, thd(%u, %u)\n",
		proxdata->prox[0], proxdata->prox[1],
		data->uProxHiThresh, data->uProxLoThresh);

	data->buf[PROXIMITY_SENSOR].prox[0] = proxdata->prox[0];
	data->buf[PROXIMITY_SENSOR].prox[1] = proxdata->prox[1];

	input_report_abs(data->prox_input_dev, ABS_DISTANCE,
		(!proxdata->prox[0]));
	input_sync(data->prox_input_dev);

	wake_lock_timeout(&data->ssp_wake_lock, 3 * HZ);
}

void report_prox_raw_data(struct ssp_data *data,
	struct sensor_value *proxrawdata)
{
	if (data->uFactoryProxAvg[0]++ >= PROX_AVG_READ_NUM) {
		data->uFactoryProxAvg[2] /= PROX_AVG_READ_NUM;
		data->buf[PROXIMITY_RAW].prox[1] = (u16)data->uFactoryProxAvg[1];
		data->buf[PROXIMITY_RAW].prox[2] = (u16)data->uFactoryProxAvg[2];
		data->buf[PROXIMITY_RAW].prox[3] = (u16)data->uFactoryProxAvg[3];

		data->uFactoryProxAvg[0] = 0;
		data->uFactoryProxAvg[1] = 0;
		data->uFactoryProxAvg[2] = 0;
		data->uFactoryProxAvg[3] = 0;
	} else {
		data->uFactoryProxAvg[2] += proxrawdata->prox[0];

		if (data->uFactoryProxAvg[0] == 1)
			data->uFactoryProxAvg[1] = proxrawdata->prox[0];
		else if (proxrawdata->prox[0] < data->uFactoryProxAvg[1])
			data->uFactoryProxAvg[1] = proxrawdata->prox[0];

		if (proxrawdata->prox[0] > data->uFactoryProxAvg[3])
			data->uFactoryProxAvg[3] = proxrawdata->prox[0];
	}

	data->buf[PROXIMITY_RAW].prox[0] = proxrawdata->prox[0];
}

void report_step_det_data(struct ssp_data *data,
	struct sensor_value *sig_motion_data)
{
	data->buf[STEP_DETECTOR].step_det = sig_motion_data->step_det;
	ssp_push_1bytes_buffer(data->step_det_indio_dev, sig_motion_data->timestamp,
			&sig_motion_data->step_det);
}

void report_step_cnt_data(struct ssp_data *data,
	struct sensor_value *sig_motion_data)
{
	data->buf[STEP_COUNTER].step_diff = sig_motion_data->step_diff;

	data->step_count_total += data->buf[STEP_COUNTER].step_diff;

	input_report_rel(data->step_cnt_input_dev, REL_MISC,
		data->step_count_total + 1);
	input_sync(data->step_cnt_input_dev);
}

void report_temp_humidity_data(struct ssp_data *data,
	struct sensor_value *temp_humi_data)
{
	data->buf[TEMPERATURE_HUMIDITY_SENSOR].x = temp_humi_data->x;
	data->buf[TEMPERATURE_HUMIDITY_SENSOR].y = temp_humi_data->y;
	data->buf[TEMPERATURE_HUMIDITY_SENSOR].z = temp_humi_data->z;

	/* Temperature */
	input_report_rel(data->temp_humi_input_dev, REL_HWHEEL,
		data->buf[TEMPERATURE_HUMIDITY_SENSOR].x);
	/* Humidity */
	input_report_rel(data->temp_humi_input_dev, REL_DIAL,
		data->buf[TEMPERATURE_HUMIDITY_SENSOR].y);
	input_sync(data->temp_humi_input_dev);
	if (data->buf[TEMPERATURE_HUMIDITY_SENSOR].z)
		wake_lock_timeout(&data->ssp_wake_lock, 2 * HZ);
}

#ifdef CONFIG_SENSORS_SSP_SHTC1
void report_bulk_comp_data(struct ssp_data *data)
{
	input_report_rel(data->temp_humi_input_dev, REL_WHEEL,
		data->bulk_buffer->len);
	input_sync(data->temp_humi_input_dev);
}
#endif

int initialize_event_symlink(struct ssp_data *data)
{
	int iRet = 0;

	data->sen_dev = device_create(sensors_event_class, NULL, 0, NULL,
		"%s", "symlink");

	iRet = sysfs_create_link(&data->sen_dev->kobj,
		&data->gesture_input_dev->dev.kobj,
		data->gesture_input_dev->name);
	if (iRet < 0)
		goto iRet_gesture_sysfs_create_link;

	iRet = sysfs_create_link(&data->sen_dev->kobj,
		&data->light_input_dev->dev.kobj,
		data->light_input_dev->name);
	if (iRet < 0)
		goto iRet_light_sysfs_create_link;

	iRet = sysfs_create_link(&data->sen_dev->kobj,
		&data->prox_input_dev->dev.kobj,
		data->prox_input_dev->name);
	if (iRet < 0)
		goto iRet_prox_sysfs_create_link;

	iRet = sysfs_create_link(&data->sen_dev->kobj,
		&data->temp_humi_input_dev->dev.kobj,
		data->temp_humi_input_dev->name);
	if (iRet < 0)
		goto iRet_temp_humi_sysfs_create_link;

	iRet = sysfs_create_link(&data->sen_dev->kobj,
		&data->mag_input_dev->dev.kobj,
		data->mag_input_dev->name);
	if (iRet < 0)
		goto iRet_mag_sysfs_create_link;

	iRet = sysfs_create_link(&data->sen_dev->kobj,
		&data->uncal_mag_input_dev->dev.kobj,
		data->uncal_mag_input_dev->name);
	if (iRet < 0)
		goto iRet_uncal_mag_sysfs_create_link;

	iRet = sysfs_create_link(&data->sen_dev->kobj,
		&data->sig_motion_input_dev->dev.kobj,
		data->sig_motion_input_dev->name);
	if (iRet < 0)
		goto iRet_sig_motion_sysfs_create_link;

	iRet = sysfs_create_link(&data->sen_dev->kobj,
		&data->uncalib_gyro_input_dev->dev.kobj,
		data->uncalib_gyro_input_dev->name);
	if (iRet < 0)
		goto iRet_uncalib_gyro_sysfs_create_link;

	iRet = sysfs_create_link(&data->sen_dev->kobj,
		&data->step_cnt_input_dev->dev.kobj,
		data->step_cnt_input_dev->name);
	if (iRet < 0)
		goto iRet_step_cnt_sysfs_create_link;

	iRet = sysfs_create_link(&data->sen_dev->kobj,
		&data->meta_input_dev->dev.kobj,
		data->meta_input_dev->name);
	if (iRet < 0)
		goto iRet_meta_sysfs_create_link;

	return SUCCESS;
iRet_meta_sysfs_create_link:
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->step_cnt_input_dev->dev.kobj,
		data->step_cnt_input_dev->name);
iRet_step_cnt_sysfs_create_link:
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->uncalib_gyro_input_dev->dev.kobj,
		data->uncalib_gyro_input_dev->name);
iRet_uncalib_gyro_sysfs_create_link:
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->sig_motion_input_dev->dev.kobj,
		data->sig_motion_input_dev->name);
iRet_sig_motion_sysfs_create_link:
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->uncal_mag_input_dev->dev.kobj,
		data->uncal_mag_input_dev->name);
iRet_uncal_mag_sysfs_create_link:
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->mag_input_dev->dev.kobj,
		data->mag_input_dev->name);
iRet_mag_sysfs_create_link:
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->temp_humi_input_dev->dev.kobj,
		data->temp_humi_input_dev->name);
iRet_temp_humi_sysfs_create_link:
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->prox_input_dev->dev.kobj,
		data->prox_input_dev->name);
iRet_prox_sysfs_create_link:
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->light_input_dev->dev.kobj,
		data->light_input_dev->name);
iRet_light_sysfs_create_link:
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->gesture_input_dev->dev.kobj,
		data->gesture_input_dev->name);
iRet_gesture_sysfs_create_link:
	pr_err("[SSP]: %s - could not create event symlink\n", __func__);

	return FAIL;
}

void remove_event_symlink(struct ssp_data *data)
{
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->gesture_input_dev->dev.kobj,
		data->gesture_input_dev->name);
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->light_input_dev->dev.kobj,
		data->light_input_dev->name);
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->prox_input_dev->dev.kobj,
		data->prox_input_dev->name);
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->temp_humi_input_dev->dev.kobj,
		data->temp_humi_input_dev->name);
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->mag_input_dev->dev.kobj,
		data->mag_input_dev->name);
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->uncal_mag_input_dev->dev.kobj,
		data->uncal_mag_input_dev->name);
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->sig_motion_input_dev->dev.kobj,
		data->sig_motion_input_dev->name);
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->uncalib_gyro_input_dev->dev.kobj,
		data->uncalib_gyro_input_dev->name);
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->step_cnt_input_dev->dev.kobj,
		data->step_cnt_input_dev->name);
	sysfs_delete_link(&data->sen_dev->kobj,
		&data->meta_input_dev->dev.kobj,
		data->meta_input_dev->name);
}

static const struct iio_info accel_info = {
	.driver_module = THIS_MODULE,
};

static const struct iio_chan_spec accel_channels[] = {
	{
		.type = IIO_TIMESTAMP,
		.channel = -1,
		.scan_index = 3,
		.scan_type = IIO_ST('s', IIO_BUFFER_6_BYTES * 8,
			IIO_BUFFER_6_BYTES * 8, 0)
	}
};

static const struct iio_info gyro_info = {
	.driver_module = THIS_MODULE,
};

static const struct iio_chan_spec gyro_channels[] = {
	{
		.type = IIO_TIMESTAMP,
		.channel = -1,
		.scan_index = 3,
		.scan_type = IIO_ST('s', IIO_BUFFER_12_BYTES * 8,
			IIO_BUFFER_12_BYTES * 8, 0)
	}
};

static const struct iio_info game_rot_info = {
	.driver_module = THIS_MODULE,
};

static const struct iio_chan_spec game_rot_channels[] = {
	{
		.type = IIO_TIMESTAMP,
		.channel = -1,
		.scan_index = 3,
		.scan_type = IIO_ST('s', IIO_BUFFER_17_BYTES * 8,
			IIO_BUFFER_17_BYTES * 8, 0)
	}
};

static const struct iio_info rot_info = {
	.driver_module = THIS_MODULE,
};

static const struct iio_chan_spec rot_channels[] = {
	{
		.type = IIO_TIMESTAMP,
		.channel = -1,
		.scan_index = 3,
		.scan_type = IIO_ST('s', IIO_BUFFER_17_BYTES * 8,
			IIO_BUFFER_17_BYTES * 8, 0)
	}
};


static const struct iio_info step_det_info = {
	.driver_module = THIS_MODULE,
};

static const struct iio_chan_spec step_det_channels[] = {
	{
		.type = IIO_TIMESTAMP,
		.channel = -1,
		.scan_index = 3,
		.scan_type = IIO_ST('s', IIO_BUFFER_1_BYTES * 8,
			IIO_BUFFER_1_BYTES * 8, 0)
	}
};

static const struct iio_info pressure_info = {
	.driver_module = THIS_MODULE,
};

static const struct iio_chan_spec pressure_channels[] = {
	{
		.type = IIO_TIMESTAMP,
		.channel = -1,
		.scan_index = 3,
		.scan_type = IIO_ST('s', IIO_BUFFER_12_BYTES * 8,
			IIO_BUFFER_12_BYTES * 8, 0)
	}
};

int initialize_input_dev(struct ssp_data *data)
{
	int iRet = 0;
	struct input_dev *light_input_dev, *prox_input_dev, *temp_humi_input_dev,
		*mag_input_dev, *gesture_input_dev, *uncal_mag_input_dev,
		*sig_motion_input_dev, *uncalib_gyro_input_dev, *step_cnt_input_dev,
		*meta_input_dev;

	data->accel_indio_dev = iio_allocate_device(0);
	if (!data->accel_indio_dev) {
		pr_err("[SSP]: %s failed to allocate memory for iio accel device\n", __func__);
		return -ENOMEM;
	}

	data->accel_indio_dev->name = "accelerometer_sensor";
	data->accel_indio_dev->dev.parent = &data->spi->dev;
	data->accel_indio_dev->info = &accel_info;
	data->accel_indio_dev->channels = accel_channels;
	data->accel_indio_dev->num_channels = ARRAY_SIZE(accel_channels);
	data->accel_indio_dev->modes = INDIO_DIRECT_MODE;
	data->accel_indio_dev->currentmode = INDIO_DIRECT_MODE;

	iRet = ssp_iio_configure_ring(data->accel_indio_dev);
	if (iRet) {
		pr_err("[SSP]: %s configure ring buffer fail\n", __func__);
		goto out_free_accel;
	}

	iRet = iio_buffer_register(data->accel_indio_dev, data->accel_indio_dev->channels,
					data->accel_indio_dev->num_channels);
	if (iRet)
		goto out_unreg_ring_accel;

	iRet = iio_device_register(data->accel_indio_dev);
	if (iRet)
		goto out_remove_trigger_accel;

	data->gyro_indio_dev = iio_allocate_device(0);
	if (!data->gyro_indio_dev) {
		pr_err("[SSP]: %s failed to allocate memory for iio gyro device\n", __func__);
		goto out_alloc_fail_gyro;
	}

	data->gyro_indio_dev->name = "gyro_sensor";
	data->gyro_indio_dev->dev.parent = &data->spi->dev;
	data->gyro_indio_dev->info = &gyro_info;
	data->gyro_indio_dev->channels = gyro_channels;
	data->gyro_indio_dev->num_channels = ARRAY_SIZE(gyro_channels);
	data->gyro_indio_dev->modes = INDIO_DIRECT_MODE;
	data->gyro_indio_dev->currentmode = INDIO_DIRECT_MODE;

	iRet = ssp_iio_configure_ring(data->gyro_indio_dev);
	if (iRet) {
		pr_err("[SSP]: %s configure ring buffer fail\n", __func__);
		goto out_free_gyro;
	}

	iRet = iio_buffer_register(data->gyro_indio_dev, data->gyro_indio_dev->channels,
					data->gyro_indio_dev->num_channels);
	if (iRet)
		goto out_unreg_ring_gyro;

	iRet = iio_device_register(data->gyro_indio_dev);
	if (iRet)
		goto out_remove_trigger_gyro;

	data->game_rot_indio_dev = iio_allocate_device(0);
	if (!data->game_rot_indio_dev) {
		pr_err("[SSP]: %s failed to allocate memory for iio gyro device\n", __func__);
		goto out_alloc_fail_game_rot;
	}

	data->game_rot_indio_dev->name = "game_rotation_vector_sensor";
	data->game_rot_indio_dev->dev.parent = &data->spi->dev;
	data->game_rot_indio_dev->info = &game_rot_info;
	data->game_rot_indio_dev->channels = game_rot_channels;
	data->game_rot_indio_dev->num_channels = ARRAY_SIZE(game_rot_channels);
	data->game_rot_indio_dev->modes = INDIO_DIRECT_MODE;
	data->game_rot_indio_dev->currentmode = INDIO_DIRECT_MODE;

	iRet = ssp_iio_configure_ring(data->game_rot_indio_dev);
	if (iRet) {
		pr_err("[SSP]: %s configure ring buffer fail\n", __func__);
		goto out_free_game_rot;
	}

	iRet = iio_buffer_register(data->game_rot_indio_dev, data->game_rot_indio_dev->channels,
					data->game_rot_indio_dev->num_channels);
	if (iRet)
		goto out_unreg_ring_game_rot;

	iRet = iio_device_register(data->game_rot_indio_dev);
	if (iRet)
		goto out_remove_trigger_game_rot;

	data->rot_indio_dev = iio_allocate_device(0);
	if (!data->rot_indio_dev) {
		pr_err("[SSP]: %s failed to allocate memory for iio gyro device\n", __func__);
		goto out_alloc_fail_rot;
	}

	data->rot_indio_dev->name = "rotation_vector_sensor";
	data->rot_indio_dev->dev.parent = &data->spi->dev;
	data->rot_indio_dev->info = &rot_info;
	data->rot_indio_dev->channels = rot_channels;
	data->rot_indio_dev->num_channels = ARRAY_SIZE(rot_channels);
	data->rot_indio_dev->modes = INDIO_DIRECT_MODE;
	data->rot_indio_dev->currentmode = INDIO_DIRECT_MODE;

	iRet = ssp_iio_configure_ring(data->rot_indio_dev);
	if (iRet) {
		pr_err("[SSP]: %s configure ring buffer fail\n", __func__);
		goto out_free_rot;
	}

	iRet = iio_buffer_register(data->rot_indio_dev, data->rot_indio_dev->channels,
					data->rot_indio_dev->num_channels);
	if (iRet)
		goto out_unreg_ring_rot;

	iRet = iio_device_register(data->rot_indio_dev);
	if (iRet)
		goto out_remove_trigger_rot;

	data->step_det_indio_dev = iio_allocate_device(0);
	if (!data->step_det_indio_dev) {
		pr_err("[SSP]: %s failed to allocate memory for iio gyro device\n", __func__);
		goto out_alloc_fail_step_det;
	}

	data->step_det_indio_dev->name = "step_det_sensor";
	data->step_det_indio_dev->dev.parent = &data->spi->dev;
	data->step_det_indio_dev->info = &step_det_info;
	data->step_det_indio_dev->channels = step_det_channels;
	data->step_det_indio_dev->num_channels = ARRAY_SIZE(step_det_channels);
	data->step_det_indio_dev->modes = INDIO_DIRECT_MODE;
	data->step_det_indio_dev->currentmode = INDIO_DIRECT_MODE;

	iRet = ssp_iio_configure_ring(data->step_det_indio_dev);
	if (iRet) {
		pr_err("[SSP]: %s configure ring buffer fail\n", __func__);
		goto out_free_step_det;
	}

	iRet = iio_buffer_register(data->step_det_indio_dev, data->step_det_indio_dev->channels,
					data->step_det_indio_dev->num_channels);
	if (iRet)
		goto out_unreg_ring_step_det;

	iRet = iio_device_register(data->step_det_indio_dev);
	if (iRet)
		goto out_remove_trigger_step_det;

	data->pressure_indio_dev = iio_allocate_device(0);
	if (!data->pressure_indio_dev) {
		pr_err("[SSP]: %s failed to allocate memory for iio gyro device\n", __func__);
		goto out_alloc_fail_pressure;
	}

	data->pressure_indio_dev->name = "pressure_sensor";
	data->pressure_indio_dev->dev.parent = &data->spi->dev;
	data->pressure_indio_dev->info = &pressure_info;
	data->pressure_indio_dev->channels = pressure_channels;
	data->pressure_indio_dev->num_channels = ARRAY_SIZE(pressure_channels);
	data->pressure_indio_dev->modes = INDIO_DIRECT_MODE;
	data->pressure_indio_dev->currentmode = INDIO_DIRECT_MODE;

	iRet = ssp_iio_configure_ring(data->pressure_indio_dev);
	if (iRet) {
		pr_err("[SSP]: %s configure ring buffer fail\n", __func__);
		goto out_free_pressure;
	}

	iRet = iio_buffer_register(data->pressure_indio_dev, data->pressure_indio_dev->channels,
					data->pressure_indio_dev->num_channels);
	if (iRet)
		goto out_unreg_ring_pressure;

	iRet = iio_device_register(data->pressure_indio_dev);
	if (iRet)
		goto out_remove_trigger_pressure;

	/* allocate input_device */
	gesture_input_dev = input_allocate_device();
	if (gesture_input_dev == NULL)
		goto iRet_gesture_input_free_device;

	light_input_dev = input_allocate_device();
	if (light_input_dev == NULL)
		goto iRet_light_input_free_device;

	prox_input_dev = input_allocate_device();
	if (prox_input_dev == NULL)
		goto iRet_proximity_input_free_device;

	temp_humi_input_dev = input_allocate_device();
	if (temp_humi_input_dev == NULL)
		goto iRet_temp_humidity_input_free_device;

	mag_input_dev = input_allocate_device();
	if (mag_input_dev == NULL)
		goto iRet_mag_input_free_device;

	uncal_mag_input_dev = input_allocate_device();
	if (uncal_mag_input_dev == NULL)
		goto iRet_uncal_mag_input_free_device;

	sig_motion_input_dev = input_allocate_device();
	if (sig_motion_input_dev == NULL)
		goto iRet_sig_motion_input_free_device;

	uncalib_gyro_input_dev = input_allocate_device();
	if (uncalib_gyro_input_dev == NULL)
		goto iRet_uncalib_gyro_input_free_device;

	step_cnt_input_dev = input_allocate_device();
	if (step_cnt_input_dev == NULL)
		goto iRet_step_cnt_input_free_device;

	meta_input_dev = input_allocate_device();
	if (meta_input_dev == NULL)
		goto iRet_meta_input_free_device;

	input_set_drvdata(gesture_input_dev, data);
	input_set_drvdata(light_input_dev, data);
	input_set_drvdata(prox_input_dev, data);
	input_set_drvdata(temp_humi_input_dev, data);
	input_set_drvdata(mag_input_dev, data);
	input_set_drvdata(uncal_mag_input_dev, data);
	input_set_drvdata(sig_motion_input_dev, data);
	input_set_drvdata(uncalib_gyro_input_dev, data);
	input_set_drvdata(step_cnt_input_dev, data);
	input_set_drvdata(meta_input_dev, data);

	gesture_input_dev->name = "gesture_sensor";
	light_input_dev->name = "light_sensor";
	prox_input_dev->name = "proximity_sensor";
	temp_humi_input_dev->name = "temp_humidity_sensor";
	mag_input_dev->name = "geomagnetic_sensor";
	uncal_mag_input_dev->name = "uncal_geomagnetic_sensor";
	sig_motion_input_dev->name = "sig_motion_sensor";
	uncalib_gyro_input_dev->name = "uncalibrated_gyro_sensor";
	step_cnt_input_dev->name = "step_cnt_sensor";
	meta_input_dev->name = "meta_event";

	input_set_capability(gesture_input_dev, EV_ABS, ABS_X);
	input_set_abs_params(gesture_input_dev, ABS_X, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_Y);
	input_set_abs_params(gesture_input_dev, ABS_Y, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_Z);
	input_set_abs_params(gesture_input_dev, ABS_Z, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_RX);
	input_set_abs_params(gesture_input_dev, ABS_RX, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_RY);
	input_set_abs_params(gesture_input_dev, ABS_RY, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_RZ);
	input_set_abs_params(gesture_input_dev, ABS_RZ, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_THROTTLE);
	input_set_abs_params(gesture_input_dev, ABS_THROTTLE, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_RUDDER);
	input_set_abs_params(gesture_input_dev, ABS_RUDDER, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_WHEEL);
	input_set_abs_params(gesture_input_dev, ABS_WHEEL, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_GAS);
	input_set_abs_params(gesture_input_dev, ABS_GAS, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_BRAKE);
	input_set_abs_params(gesture_input_dev, ABS_BRAKE, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_HAT0X);
	input_set_abs_params(gesture_input_dev, ABS_HAT0X, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_HAT0Y);
	input_set_abs_params(gesture_input_dev, ABS_HAT0Y, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_HAT1X);
	input_set_abs_params(gesture_input_dev, ABS_HAT1X, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_HAT1Y);
	input_set_abs_params(gesture_input_dev, ABS_HAT1Y, 0, 1024, 0, 0);

	input_set_capability(gesture_input_dev, EV_ABS, ABS_HAT2X);
	input_set_abs_params(gesture_input_dev, ABS_HAT2X, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_HAT2Y);
	input_set_abs_params(gesture_input_dev, ABS_HAT2Y, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_HAT3X);
	input_set_abs_params(gesture_input_dev, ABS_HAT3X, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_HAT3Y);
	input_set_abs_params(gesture_input_dev, ABS_HAT3Y, 0, 1024, 0, 0);
	input_set_capability(gesture_input_dev, EV_ABS, ABS_PRESSURE);
	input_set_abs_params(gesture_input_dev, ABS_PRESSURE, 0, 1024, 0, 0);

	input_set_capability(light_input_dev, EV_REL, REL_HWHEEL);
	input_set_capability(light_input_dev, EV_REL, REL_DIAL);
	input_set_capability(light_input_dev, EV_REL, REL_WHEEL);
	input_set_capability(light_input_dev, EV_REL, REL_MISC);
	input_set_capability(light_input_dev, EV_REL, REL_RY);
	input_set_capability(light_input_dev, EV_REL, REL_RZ);

	input_set_capability(prox_input_dev, EV_ABS, ABS_DISTANCE);
	input_set_abs_params(prox_input_dev, ABS_DISTANCE, 0, 1, 0, 0);

	input_set_capability(temp_humi_input_dev, EV_REL, REL_HWHEEL);
	input_set_capability(temp_humi_input_dev, EV_REL, REL_DIAL);
	input_set_capability(temp_humi_input_dev, EV_REL, REL_WHEEL);

#ifdef SAVE_MAG_LOG
	input_set_capability(mag_input_dev, EV_REL, REL_X);
	input_set_capability(mag_input_dev, EV_REL, REL_Y);
	input_set_capability(mag_input_dev, EV_REL, REL_Z);
	input_set_capability(mag_input_dev, EV_REL, REL_RX);
	input_set_capability(mag_input_dev, EV_REL, REL_RY);
	input_set_capability(mag_input_dev, EV_REL, REL_RZ);
	input_set_capability(mag_input_dev, EV_REL, REL_HWHEEL);
	input_set_capability(mag_input_dev, EV_REL, REL_DIAL);
	input_set_capability(mag_input_dev, EV_REL, REL_WHEEL);
#else
	input_set_capability(mag_input_dev, EV_REL, REL_RX);
	input_set_capability(mag_input_dev, EV_REL, REL_RY);
	input_set_capability(mag_input_dev, EV_REL, REL_RZ);
	input_set_capability(mag_input_dev, EV_REL, REL_HWHEEL);
#endif

	input_set_capability(uncal_mag_input_dev, EV_REL, REL_RX);
	input_set_capability(uncal_mag_input_dev, EV_REL, REL_RY);
	input_set_capability(uncal_mag_input_dev, EV_REL, REL_RZ);
	input_set_capability(uncal_mag_input_dev, EV_REL, REL_HWHEEL);
	input_set_capability(uncal_mag_input_dev, EV_REL, REL_DIAL);
	input_set_capability(uncal_mag_input_dev, EV_REL, REL_WHEEL);

	input_set_capability(sig_motion_input_dev, EV_REL, REL_MISC);

	input_set_capability(uncalib_gyro_input_dev, EV_REL, REL_X);
	input_set_capability(uncalib_gyro_input_dev, EV_REL, REL_Y);
	input_set_capability(uncalib_gyro_input_dev, EV_REL, REL_Z);
	input_set_capability(uncalib_gyro_input_dev, EV_REL, REL_RX);
	input_set_capability(uncalib_gyro_input_dev, EV_REL, REL_RY);
	input_set_capability(uncalib_gyro_input_dev, EV_REL, REL_RZ);
	input_set_capability(step_cnt_input_dev, EV_REL, REL_MISC);

	input_set_capability(meta_input_dev, EV_REL, REL_HWHEEL);
	input_set_capability(meta_input_dev, EV_REL, REL_DIAL);

	/* register input_device */
	iRet = input_register_device(gesture_input_dev);
	if (iRet < 0)
		goto iRet_gesture_input_unreg_device;

	iRet = input_register_device(light_input_dev);
	if (iRet < 0) {
		input_free_device(light_input_dev);
		input_free_device(prox_input_dev);
		input_free_device(temp_humi_input_dev);
		input_free_device(mag_input_dev);
		input_free_device(uncal_mag_input_dev);
		input_free_device(sig_motion_input_dev);
		input_free_device(uncalib_gyro_input_dev);
		input_free_device(step_cnt_input_dev);
		input_free_device(meta_input_dev);
		goto iRet_light_input_unreg_device;
	}

	iRet = input_register_device(prox_input_dev);
	if (iRet < 0) {
		input_free_device(prox_input_dev);
		input_free_device(temp_humi_input_dev);
		input_free_device(mag_input_dev);
		input_free_device(uncal_mag_input_dev);
		input_free_device(sig_motion_input_dev);
		input_free_device(uncalib_gyro_input_dev);
		input_free_device(step_cnt_input_dev);
		input_free_device(meta_input_dev);
		goto iRet_proximity_input_unreg_device;
	}

	iRet = input_register_device(temp_humi_input_dev);
	if (iRet < 0) {
		input_free_device(temp_humi_input_dev);
		input_free_device(mag_input_dev);
		input_free_device(uncal_mag_input_dev);
		input_free_device(sig_motion_input_dev);
		input_free_device(uncalib_gyro_input_dev);
		input_free_device(step_cnt_input_dev);
		input_free_device(meta_input_dev);
		goto iRet_tmep_humi_input_unreg_device;
	}

	iRet = input_register_device(mag_input_dev);
	if (iRet < 0) {
		input_free_device(mag_input_dev);
		input_free_device(uncal_mag_input_dev);
		input_free_device(sig_motion_input_dev);
		input_free_device(uncalib_gyro_input_dev);
		input_free_device(step_cnt_input_dev);
		input_free_device(meta_input_dev);
		goto iRet_mag_input_unreg_device;
	}

	iRet = input_register_device(uncal_mag_input_dev);
	if (iRet < 0) {
		input_free_device(uncal_mag_input_dev);
		input_free_device(sig_motion_input_dev);
		input_free_device(uncalib_gyro_input_dev);
		input_free_device(step_cnt_input_dev);
		input_free_device(meta_input_dev);
		goto iRet_uncal_mag_input_unreg_device;
	}

	iRet = input_register_device(sig_motion_input_dev);
	if (iRet < 0) {
		input_free_device(sig_motion_input_dev);
		input_free_device(uncalib_gyro_input_dev);
		input_free_device(step_cnt_input_dev);
		input_free_device(meta_input_dev);
		goto iRet_sig_motion_input_unreg_device;
	}

	iRet = input_register_device(uncalib_gyro_input_dev);
	if (iRet < 0) {
		input_free_device(uncalib_gyro_input_dev);
		input_free_device(step_cnt_input_dev);
		input_free_device(meta_input_dev);
		goto iRet_uncalib_gyro_input_unreg_device;
	}

	iRet = input_register_device(step_cnt_input_dev);
	if (iRet < 0) {
		input_free_device(step_cnt_input_dev);
		input_free_device(meta_input_dev);
		goto iRet_step_cnt_input_unreg_device;
	}

	iRet = input_register_device(meta_input_dev);
	if (iRet < 0) {
		input_free_device(meta_input_dev);
		goto iRet_meta_input_unreg_device;
	}

	data->gesture_input_dev = gesture_input_dev;
	data->light_input_dev = light_input_dev;
	data->prox_input_dev = prox_input_dev;
	data->temp_humi_input_dev = temp_humi_input_dev;
	data->mag_input_dev = mag_input_dev;
	data->uncal_mag_input_dev = uncal_mag_input_dev;
	data->sig_motion_input_dev = sig_motion_input_dev;
	data->uncalib_gyro_input_dev = uncalib_gyro_input_dev;
	data->step_cnt_input_dev = step_cnt_input_dev;
	data->meta_input_dev = meta_input_dev;

	return SUCCESS;
iRet_meta_input_unreg_device:
	input_unregister_device(step_cnt_input_dev);
iRet_step_cnt_input_unreg_device:
	input_unregister_device(uncalib_gyro_input_dev);
iRet_uncalib_gyro_input_unreg_device:
	input_unregister_device(sig_motion_input_dev);
iRet_sig_motion_input_unreg_device:
	input_unregister_device(uncal_mag_input_dev);
iRet_uncal_mag_input_unreg_device:
	input_unregister_device(mag_input_dev);
iRet_mag_input_unreg_device:
	input_unregister_device(temp_humi_input_dev);
iRet_tmep_humi_input_unreg_device:
	input_unregister_device(prox_input_dev);
iRet_proximity_input_unreg_device:
	input_unregister_device(light_input_dev);
iRet_light_input_unreg_device:
	input_unregister_device(gesture_input_dev);
	return ERROR;
iRet_gesture_input_unreg_device:
	input_free_device(meta_input_dev);
iRet_meta_input_free_device:
	input_free_device(step_cnt_input_dev);
iRet_step_cnt_input_free_device:
	input_free_device(uncalib_gyro_input_dev);
iRet_uncalib_gyro_input_free_device:
	input_free_device(sig_motion_input_dev);
iRet_sig_motion_input_free_device:
	input_free_device(uncal_mag_input_dev);
iRet_uncal_mag_input_free_device:
	input_free_device(mag_input_dev);
iRet_mag_input_free_device:
	input_free_device(temp_humi_input_dev);
iRet_temp_humidity_input_free_device:
	input_free_device(prox_input_dev);
iRet_proximity_input_free_device:
	input_free_device(light_input_dev);
iRet_light_input_free_device:
	input_free_device(gesture_input_dev);
iRet_gesture_input_free_device:
	iio_device_unregister(data->pressure_indio_dev);
out_remove_trigger_pressure:
	iio_buffer_unregister(data->pressure_indio_dev);
out_unreg_ring_pressure:
	ssp_iio_unconfigure_ring(data->pressure_indio_dev);
out_free_pressure:
	iio_free_device(data->pressure_indio_dev);
out_alloc_fail_pressure:
	iio_device_unregister(data->step_det_indio_dev);
out_remove_trigger_step_det:
	iio_buffer_unregister(data->step_det_indio_dev);
out_unreg_ring_step_det:
	ssp_iio_unconfigure_ring(data->step_det_indio_dev);
out_free_step_det:
	iio_free_device(data->step_det_indio_dev);
out_alloc_fail_step_det:
	iio_device_unregister(data->rot_indio_dev);
out_remove_trigger_rot:
	iio_buffer_unregister(data->rot_indio_dev);
out_unreg_ring_rot:
	ssp_iio_unconfigure_ring(data->rot_indio_dev);
out_free_rot:
	iio_free_device(data->rot_indio_dev);
out_alloc_fail_rot:
	iio_device_unregister(data->game_rot_indio_dev);
out_remove_trigger_game_rot:
	iio_buffer_unregister(data->game_rot_indio_dev);
out_unreg_ring_game_rot:
	ssp_iio_unconfigure_ring(data->game_rot_indio_dev);
out_free_game_rot:
	iio_free_device(data->game_rot_indio_dev);
out_alloc_fail_game_rot:
	iio_device_unregister(data->gyro_indio_dev);
out_remove_trigger_gyro:
	iio_buffer_unregister(data->gyro_indio_dev);
out_unreg_ring_gyro:
	ssp_iio_unconfigure_ring(data->gyro_indio_dev);
out_free_gyro:
	iio_free_device(data->gyro_indio_dev);
out_alloc_fail_gyro:
	iio_device_unregister(data->accel_indio_dev);
out_remove_trigger_accel:
	iio_buffer_unregister(data->accel_indio_dev);
out_unreg_ring_accel:
	ssp_iio_unconfigure_ring(data->accel_indio_dev);
out_free_accel:
	iio_free_device(data->accel_indio_dev);
	pr_err("[SSP]: %s - could not allocate input device\n", __func__);
	return ERROR;
}

void remove_input_dev(struct ssp_data *data)
{
	input_unregister_device(data->gesture_input_dev);
	input_unregister_device(data->light_input_dev);
	input_unregister_device(data->prox_input_dev);
	input_unregister_device(data->temp_humi_input_dev);
	input_unregister_device(data->mag_input_dev);
	input_unregister_device(data->uncal_mag_input_dev);
	input_unregister_device(data->sig_motion_input_dev);
	input_unregister_device(data->uncalib_gyro_input_dev);
	input_unregister_device(data->step_cnt_input_dev);
	input_unregister_device(data->meta_input_dev);
}
