/*
* Copyright (C) 2012 Invensense, Inc.
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/sysfs.h>
#include <linux/jiffies.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/kfifo.h>
#include <linux/poll.h>
#include <linux/miscdevice.h>

#include "iio.h"
#include "kfifo_buf.h"
#include "trigger_consumer.h"
#include "sysfs.h"

#include "inv_mpu_iio.h"

#define MAX_GYRO	32767
#define MIN_GYRO	-32768

static u8 fifo_data[HARDWARE_FIFO_SIZE + HEADERED_Q_BYTES];
static int inv_process_batchmode(struct inv_mpu_state *st);

static int inv_push_marker_to_buffer(struct inv_mpu_state *st, u16 hdr)
{
	struct iio_dev *indio_dev = iio_priv_to_dev(st);
	u8 buf[IIO_BUFFER_BYTES];

	memcpy(buf, &hdr, sizeof(hdr));
	iio_push_to_buffer(indio_dev->buffer, buf, 0);

	return 0;
}

static int inv_push_8bytes_buffer(struct inv_mpu_state *st, u16 hdr,
							u64 t, s16 *d)
{
	struct iio_dev *indio_dev = iio_priv_to_dev(st);
	u8 buf[IIO_BUFFER_BYTES];
	int i;

	memcpy(buf, &hdr, sizeof(hdr));
	for (i = 0; i < 3; i++)
		memcpy(&buf[2 + i * 2], &d[i], sizeof(d[i]));
	iio_push_to_buffer(indio_dev->buffer, buf, 0);
	memcpy(buf, &t, sizeof(t));
	iio_push_to_buffer(indio_dev->buffer, buf, 0);

	return 0;
}

static int inv_push_16bytes_buffer(struct inv_mpu_state *st, u16 hdr, u64 t,
									int *q)
{
	struct iio_dev *indio_dev = iio_priv_to_dev(st);
	u8 buf[IIO_BUFFER_BYTES];
	int i;

	memcpy(buf, &hdr, sizeof(hdr));
	memcpy(buf + 4, &q[0], sizeof(q[0]));
	iio_push_to_buffer(indio_dev->buffer, buf, 0);
	for (i = 0; i < 2; i++)
		memcpy(buf + 4 * i, &q[i + 1], sizeof(q[i]));
	iio_push_to_buffer(indio_dev->buffer, buf, 0);
	memcpy(buf, &t, sizeof(t));
	iio_push_to_buffer(indio_dev->buffer, buf, 0);

	return 0;
}

static int inv_send_pressure_data(struct inv_mpu_state *st)
{
	short sen[3];
	struct inv_chip_config_s *conf;
	struct inv_mpu_slave *slave;
	u64 curr_ts;
	int result;

	conf = &st->chip_config;
	slave = st->slave_pressure;
	if (!st->sensor[SENSOR_PRESSURE].on)
		return 0;
	if (conf->dmp_on && conf->dmp_event_int_on)
		return 0;
	if (!conf->normal_pressure_measure) {
		conf->normal_pressure_measure = 1;
		return 0;
	}
	curr_ts = get_time_ns();
	if (curr_ts - slave->prev_ts > slave->min_read_time) {
		result = slave->read_data(st, sen);
		if (!result)
			inv_push_8bytes_buffer(st, PRESSURE_HDR,
						st->last_ts, sen);
		slave->prev_ts = curr_ts;
	}

	return 0;
}

static int inv_send_compass_data(struct inv_mpu_state *st)
{
	short sen[3];
	struct inv_chip_config_s *conf;
	struct inv_mpu_slave *slave;
	u64 curr_ts;
	int result;

	conf = &st->chip_config;
	slave = st->slave_compass;
	if (!st->sensor[SENSOR_COMPASS].on)
		return 0;
	if (conf->dmp_on && conf->dmp_event_int_on)
		return 0;
	if (!conf->normal_compass_measure) {
		conf->normal_compass_measure = 1;
		return 0;
	}
	curr_ts = get_time_ns();
	if (curr_ts - slave->prev_ts > slave->min_read_time) {
		result = slave->read_data(st, sen);
		if (!result)
			inv_push_8bytes_buffer(st, COMPASS_HDR,
						st->last_ts, sen);
		slave->prev_ts = curr_ts;
	}

	return 0;
}

static int inv_batchmode_calc(struct inv_mpu_state *st)
{
	int b, timeout;
	int rate_dur;

	rate_dur = MSEC_PER_SEC / st->batch.min_rate;
	if (st->batch.timeout < rate_dur)
		st->batch.timeout = rate_dur;
	b = st->batch.timeout * st->bytes_per_sec;
	if ((b > (FIFO_SIZE * ONE_K_HZ)) && (!st->batch.overflow_on))
		timeout = FIFO_SIZE * ONE_K_HZ / st->bytes_per_sec;
	else
		timeout = st->batch.timeout;

	st->batch.counter = timeout / 5;
	if (timeout)
		st->batch.on = true;

	return 0;
}

int inv_batchmode_setup(struct inv_mpu_state *st)
{
	int r;

	r = inv_write_2bytes(st, KEY_BM_NUMWORD_TOFILL, 0);
	if (r)
		return r;
	r = write_be32_key_to_mem(st, 0, KEY_BM_BATCH_CNTR);
	if (r)
		return r;

	if (st->chip_config.dmp_on && (st->batch.timeout > 0) &&
			(st->chip_config.dmp_event_int_on == 0)) {
		r = inv_batchmode_calc(st);
		if (r)
			return r;
	}

	if (st->batch.on) {
		r = write_be32_key_to_mem(st, st->batch.counter,
						KEY_BM_BATCH_THLD);
		if (r)
			return r;
	}
	r = inv_write_2bytes(st, KEY_BM_ENABLE, st->batch.on);

	return r;
}

/**
 *  reset_fifo_mpu3050() - Reset FIFO related registers
 *  @indio_dev:	Device driver instance.
 */
static int reset_fifo_mpu3050(struct iio_dev *indio_dev)
{
	struct inv_reg_map_s *reg;
	int result;
	u8 val, user_ctrl;
	struct inv_mpu_state  *st = iio_priv(indio_dev);
	reg = &st->reg;

	/* disable interrupt */
	result = inv_i2c_single_write(st, reg->int_enable,
				st->plat_data.int_config);
	if (result)
		return result;
	/* disable the sensor output to FIFO */
	result = inv_i2c_single_write(st, reg->fifo_en, 0);
	if (result)
		goto reset_fifo_fail;
	result = inv_i2c_read(st, reg->user_ctrl, 1, &user_ctrl);
	if (result)
		goto reset_fifo_fail;
	/* disable fifo reading */
	user_ctrl &= ~BIT_FIFO_EN;
	st->chip_config.has_footer = 0;
	/* reset fifo */
	val = (BIT_3050_FIFO_RST | user_ctrl);
	result = inv_i2c_single_write(st, reg->user_ctrl, val);
	if (result)
		goto reset_fifo_fail;
	if (st->chip_config.dmp_on) {
		/* enable interrupt when DMP is done */
		result = inv_i2c_single_write(st, reg->int_enable,
				st->plat_data.int_config | BIT_DMP_INT_EN);
		if (result)
			return result;

		result = inv_i2c_single_write(st, reg->user_ctrl,
			BIT_FIFO_EN|user_ctrl);
		if (result)
			return result;
	} else {
		/* enable interrupt */
		if (st->sensor[SENSOR_ACCEL].on ||
		    st->sensor[SENSOR_GYRO].on) {
			result = inv_i2c_single_write(st, reg->int_enable,
				st->plat_data.int_config | BIT_DATA_RDY_EN);
			if (result)
				return result;
		}
		/* enable FIFO reading and I2C master interface*/
		result = inv_i2c_single_write(st, reg->user_ctrl,
			BIT_FIFO_EN | user_ctrl);
		if (result)
			return result;
		/* enable sensor output to FIFO and FIFO footer*/
		val = 1;
		if (st->sensor[SENSOR_ACCEL].on)
			val |= BITS_3050_ACCEL_OUT;
		if (st->sensor[SENSOR_GYRO].on)
			val |= BITS_GYRO_OUT;
		result = inv_i2c_single_write(st, reg->fifo_en, val);
		if (result)
			return result;
	}

	return 0;
reset_fifo_fail:
	if (st->chip_config.dmp_on)
		val = BIT_DMP_INT_EN;
	else
		val = BIT_DATA_RDY_EN;
	inv_i2c_single_write(st, reg->int_enable,
			     st->plat_data.int_config | val);
	pr_err("reset fifo failed\n");

	return result;
}

/*
 *  inv_set_lpf() - set low pass filer based on fifo rate.
 */
static int inv_set_lpf(struct inv_mpu_state *st, int rate)
{
	const short hz[] = {188, 98, 42, 20, 10, 5};
	const int   d[] = {INV_FILTER_188HZ, INV_FILTER_98HZ,
			INV_FILTER_42HZ, INV_FILTER_20HZ,
			INV_FILTER_10HZ, INV_FILTER_5HZ};
	int i, h, data, result;
	struct inv_reg_map_s *reg;

	reg = &st->reg;
	h = (rate >> 1);
	i = 0;
	while ((h < hz[i]) && (i < ARRAY_SIZE(d) - 1))
		i++;
	data = d[i];
	if (INV_MPU3050 == st->chip_type) {
		if (st->slave_accel != NULL) {
			result = st->slave_accel->set_lpf(st, rate);
			if (result)
				return result;
		}
		result = inv_i2c_single_write(st, reg->lpf, data |
			(st->chip_config.fsr << GYRO_CONFIG_FSR_SHIFT));
	} else {
		result = inv_i2c_single_write(st, reg->lpf, data);
	}
	if (result)
		return result;
	st->chip_config.lpf = data;

	return 0;
}

/*
 *  set_fifo_rate_reg() - Set fifo rate in hardware register
 */
static int set_fifo_rate_reg(struct inv_mpu_state *st)
{
	u8 data;
	u16 fifo_rate;
	int result;
	struct inv_reg_map_s *reg;

	reg = &st->reg;
	fifo_rate = st->chip_config.fifo_rate;
	data = ONE_K_HZ / fifo_rate - 1;
	result = inv_i2c_single_write(st, reg->sample_rate_div, data);
	if (result)
		return result;
	result = inv_set_lpf(st, fifo_rate);
	if (result)
		return result;

	return 0;
}

/*
 *  inv_lpa_mode() - store current low power mode settings
 */
static int inv_lpa_mode(struct inv_mpu_state *st, int lpa_mode)
{
	unsigned long result;
	u8 d;
	struct inv_reg_map_s *reg;

	reg = &st->reg;
	result = inv_i2c_read(st, reg->pwr_mgmt_1, 1, &d);
	if (result)
		return result;
	if (lpa_mode)
		d |= BIT_CYCLE;
	else
		d &= ~BIT_CYCLE;

	result = inv_i2c_single_write(st, reg->pwr_mgmt_1, d);
	if (result)
		return result;
	if (INV_MPU6500 == st->chip_type) {
		/* set to 512 bytes for FIFO size and LPF 42HZ */
		d = INV_FILTER_42HZ;

		if (lpa_mode)
			d |= BIT_ACCEL_FCHOCIE_B;
		result = inv_i2c_single_write(st, st->reg.accel_config2, d);
		if (result)
			return result;
	}

	return 0;
}

static int inv_saturate_secondary_counter(struct inv_mpu_state *st)
{
	int result;
	struct inv_reg_map_s *reg;

#define COUNT_SATURATE_TIME_MS 32
	reg = &st->reg;
	/* set sampling to 1KHz */
	result = inv_i2c_single_write(st, reg->sample_rate_div, 0);
	if (result)
		return result;
	result = inv_i2c_single_write(st, REG_I2C_MST_DELAY_CTRL,
							BIT_SLV0_DLY_EN);
	if (result)
		return result;
	result = inv_i2c_single_write(st, REG_I2C_SLV4_CTRL, 0);
	if (result)
		return result;
	result = inv_i2c_single_write(st, reg->user_ctrl, BIT_I2C_MST_EN);
	if (result)
		return result;
	msleep(COUNT_SATURATE_TIME_MS);

	return 0;
}
static int inv_set_master_delay(struct inv_mpu_state *st)
{
	int d, result, rate;
	u8 delay;

	if ((!st->sensor[SENSOR_COMPASS].on) &&
		(!st->sensor[SENSOR_PRESSURE].on))
		return 0;

	delay = 0;
	d = 0;
	if (st->sensor[SENSOR_COMPASS].on) {
		switch (st->plat_data.sec_slave_id) {
		case COMPASS_ID_AK8975:
		case COMPASS_ID_AK8972:
		case COMPASS_ID_AK8963:
		case COMPASS_ID_AK09911:
			delay = (BIT_SLV0_DLY_EN | BIT_SLV1_DLY_EN);
			break;
		case COMPASS_ID_MLX90399:
			delay = (BIT_SLV0_DLY_EN |
				BIT_SLV1_DLY_EN |
				BIT_SLV2_DLY_EN |
				BIT_SLV3_DLY_EN);
			break;
		default:
			return -EINVAL;
		}
		d = max(d, st->slave_compass->rate_scale);
	}
	if (st->sensor[SENSOR_PRESSURE].on) {
		/* read fake data when compass is disabled for DMP read */
		if ((!st->sensor[SENSOR_COMPASS].on) && st->chip_config.dmp_on)
			delay |= BIT_SLV0_DLY_EN;
		switch (st->plat_data.aux_slave_id) {
		case PRESSURE_ID_BMP280:
			delay |= (BIT_SLV2_DLY_EN | BIT_SLV3_DLY_EN);
			break;
		default:
			return -EINVAL;
		}
		d = max(d, st->slave_pressure->rate_scale);
	}

	d = d * st->chip_config.fifo_rate / ONE_K_HZ;
	if (st->chip_config.dmp_on) {
		rate = 0;
		if (st->sensor[SENSOR_PRESSURE].on)
			rate = max(rate, st->sensor[SENSOR_PRESSURE].rate);
		if (st->sensor[SENSOR_COMPASS].on)
			rate = max(rate, st->sensor[SENSOR_COMPASS].rate);
		if (rate == 0)
			return -EINVAL;
		d = max(d, st->chip_config.fifo_rate / rate);
	}

	if (d > 0)
		d -= 1;
	if (d > 0x1F)
		d = 0x1F;

	/* I2C_MST_DLY is set to slow down secondary I2C */
	if (0 == d)
		delay = 0;
	if (delay) {
		result = inv_saturate_secondary_counter(st);
		if (result)
			return result;
	}
	result = inv_i2c_single_write(st, REG_I2C_MST_DELAY_CTRL, delay);
	if (result)
		return result;

	return inv_i2c_single_write(st, REG_I2C_SLV4_CTRL, d);
}

/*
 *  reset_fifo_itg() - Reset FIFO related registers.
 */
static int reset_fifo_itg(struct iio_dev *indio_dev)
{
	struct inv_reg_map_s *reg;
	int result, i;
	u8 val, int_word;
	struct inv_mpu_state  *st = iio_priv(indio_dev);

	reg = &st->reg;
	if (st->chip_config.lpa_mode) {
		result = inv_lpa_mode(st, 0);
		if (result) {
			pr_err("reset lpa mode failed\n");
			return result;
		}
	}
	/* disable interrupt */
	result = inv_i2c_single_write(st, reg->int_enable, 0);
	if (result) {
		pr_err("int_enable write failed\n");
		return result;
	}
	/* disable the sensor output to FIFO */
	result = inv_i2c_single_write(st, reg->fifo_en, 0);
	if (result)
		goto reset_fifo_fail;
	/* disable fifo reading */
	result = inv_i2c_single_write(st, reg->user_ctrl, 0);
	if (result)
		goto reset_fifo_fail;
	int_word = 0;

	/* MPU6500's BIT_6500_WOM_EN is the same as BIT_MOT_EN */
	if (st->mot_int.mot_on)
		int_word |= BIT_MOT_EN;

	if (st->chip_config.dmp_on) {
		val = (BIT_FIFO_RST | BIT_DMP_RST);
		result = inv_i2c_single_write(st, reg->user_ctrl, val);
		if (result)
			goto reset_fifo_fail;
		if (st->chip_config.dmp_int_on) {
			int_word |= BIT_DMP_INT_EN;
			result = inv_i2c_single_write(st, reg->int_enable,
							int_word);
			if (result)
				return result;
		}
		val = (BIT_DMP_EN | BIT_FIFO_EN);
		if ((st->sensor[SENSOR_COMPASS].on ||
			st->sensor[SENSOR_PRESSURE].on) &&
			(!st->chip_config.dmp_event_int_on))
			val |= BIT_I2C_MST_EN;
		result = inv_i2c_single_write(st, reg->user_ctrl, val);
		if (result)
			goto reset_fifo_fail;
	} else {
		/* reset FIFO and possibly reset I2C*/
		val = BIT_FIFO_RST;
		result = inv_i2c_single_write(st, reg->user_ctrl, val);
		if (result)
			goto reset_fifo_fail;
		/* enable interrupt */
		if (st->sensor[SENSOR_ACCEL].on ||
				    st->sensor[SENSOR_GYRO].on ||
				    st->sensor[SENSOR_COMPASS].on ||
				    st->sensor[SENSOR_PRESSURE].on)
			int_word |= BIT_DATA_RDY_EN;

		result = inv_i2c_single_write(st, reg->int_enable, int_word);
		if (result)
			return result;
		/* enable FIFO reading and I2C master interface*/
		val = BIT_FIFO_EN;
		if (st->sensor[SENSOR_COMPASS].on ||
		    st->sensor[SENSOR_PRESSURE].on)
			val |= BIT_I2C_MST_EN;
		result = inv_i2c_single_write(st, reg->user_ctrl, val);
		if (result)
			goto reset_fifo_fail;
		/* enable sensor output to FIFO */
		val = 0;
		if (st->sensor[SENSOR_GYRO].on)
			val |= BITS_GYRO_OUT;
		if (st->sensor[SENSOR_ACCEL].on)
			val |= BIT_ACCEL_OUT;
		result = inv_i2c_single_write(st, reg->fifo_en, val);
		if (result)
			goto reset_fifo_fail;
	}
	st->last_ts = get_time_ns();
	st->prev_ts = st->last_ts;
	st->last_run_time = st->last_ts;
	if (st->sensor[SENSOR_COMPASS].on)
		st->slave_compass->prev_ts = st->last_ts;
	if (st->sensor[SENSOR_PRESSURE].on)
		st->slave_pressure->prev_ts = st->last_ts;

	st->dmp_interval = DMP_INTERVAL_INIT;
	st->ts_counter = 0;
	st->diff_accumulater = 0;
	st->dmp_interval_accum = 0;
	st->step_detector_base_ts = st->last_ts;
	st->chip_config.normal_compass_measure = 0;
	st->chip_config.normal_pressure_measure = 0;
	st->left_over_size = 0;
	for (i = 0; i < SENSOR_NUM_MAX; i++)
		st->sensor[i].ts = st->last_ts;

	result = inv_lpa_mode(st, st->chip_config.lpa_mode);
	if (result)
		goto reset_fifo_fail;

	return 0;

reset_fifo_fail:
	if (st->chip_config.dmp_on)
		val = BIT_DMP_INT_EN;
	else
		val = BIT_DATA_RDY_EN;
	inv_i2c_single_write(st, reg->int_enable, val);
	pr_err("reset fifo failed\n");

	return result;
}

/**
 *  inv_clear_kfifo() - clear time stamp fifo
 *  @st:	Device driver instance.
 */
static void inv_clear_kfifo(struct inv_mpu_state *st)
{
	unsigned long flags;

	spin_lock_irqsave(&st->time_stamp_lock, flags);
	kfifo_reset(&st->timestamps);
	spin_unlock_irqrestore(&st->time_stamp_lock, flags);
}

/*
 *  inv_reset_fifo() - Reset FIFO related registers.
 */
int inv_reset_fifo(struct iio_dev *indio_dev)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);

	inv_clear_kfifo(st);
	if (INV_MPU3050 == st->chip_type)
		return reset_fifo_mpu3050(indio_dev);
	else
		return reset_fifo_itg(indio_dev);
}

static int inv_send_gyro_data(struct inv_mpu_state *st, bool on)
{
	u8 rn[] = {0xa3, 0xa3};
	u8 rf[] = {0xf4, 0x12};
	int result;
	u8 *r;

	if (on)
		r = rn;
	else
		r = rf;
	result = mem_w_key(KEY_CFG_OUT_GYRO, ARRAY_SIZE(rf), r);

	return result;
}

static int inv_send_accel_data(struct inv_mpu_state *st, bool on)
{
	u8 rn[] = {0xa3, 0xa3};
	u8 rf[] = {0xf4, 0x12};
	int result;
	u8 *r;

	if (on)
		r = rn;
	else
		r = rf;
	result = mem_w_key(KEY_CFG_OUT_ACCL, ARRAY_SIZE(rf), r);

	return result;
}

static int inv_send_three_q_data(struct inv_mpu_state *st, bool on)
{
	u8 rn[] = {0xa3, 0xa3};
	u8 rf[] = {0xf4, 0x13};
	int result;
	u8 *r;

	if (on)
		r = rn;
	else
		r = rf;
	result = mem_w_key(KEY_CFG_OUT_3QUAT, ARRAY_SIZE(rf), r);

	return result;
}

static int inv_send_six_q_data(struct inv_mpu_state *st, bool on)
{
	u8 rn[] = {0xa3, 0xa3};
	u8 rf[] = {0xf4, 0x13};
	int result;
	u8 *r;

	if (on)
		r = rn;
	else
		r = rf;
	result = mem_w_key(KEY_CFG_OUT_6QUAT, ARRAY_SIZE(rf), r);

	return result;
}

static int inv_send_ped_q_data(struct inv_mpu_state *st, bool on)
{
	u8 rn[] = {0xa3, 0xa3};
	u8 rf[] = {0xf4, 0x12};
	u8 *r;
	int result;

	if (on)
		r = rn;
	else
		r = rf;
	result = mem_w_key(KEY_CFG_OUT_PQUAT, ARRAY_SIZE(rn), r);

	return result;
}

static int inv_add_step_indicator(struct inv_mpu_state *st, bool on)
{
	u8 rn[] = {0xf3, 0xf3};
	u8 rf[] = {0xf4, 0x03};
	int result;
	u8 *r;

	if (on)
		r = rn;
	else
		r = rf;
	result = mem_w_key(KEY_CFG_PEDSTEP_DET, ARRAY_SIZE(rn), r);

	return result;
}

static int inv_send_compass_dmp_data(struct inv_mpu_state *st, bool on)
{
	u8 rn[] = {0xa3, 0xa3};
	u8 rf[] = {0xf4, 0x12};
	u8 *r;
	int result;

	if (on)
		r = rn;
	else
		r = rf;
	result = mem_w_key(KEY_CFG_OUT_CPASS, ARRAY_SIZE(rf), r);

	return result;
}

static int inv_send_pressure_dmp_data(struct inv_mpu_state *st, bool on)
{
	u8 rn[] = {0xa3, 0xa3};
	u8 rf[] = {0xf4, 0x12};
	u8 *r;
	int result;

	if (on)
		r = rn;
	else
		r = rf;
	result = mem_w_key(KEY_CFG_OUT_PRESS, ARRAY_SIZE(rf), r);

	return result;
}

static int inv_send_step_detector(struct inv_mpu_state *st, bool on)
{
	u8 rn[] = {0xa3, 0xa3};
	u8 rf[] = {0xf4, 0x0e};
	u8 *r;
	int result;

	if (on)
		r = rn;
	else
		r = rf;
	result = mem_w_key(KEY_CFG_OUT_STEPDET, ARRAY_SIZE(rf), r);

	return result;
}

static int inv_set_rate(struct inv_mpu_state *st, int k, int k_ct, int rate)
{
	int v, result;

	v = MPU_DEFAULT_DMP_FREQ / rate - 1;
	result = inv_write_2bytes(st, k, v);
	if (result)
		return result;
	result = inv_write_2bytes(st, k_ct, 0);

	return result;
}

static int inv_set_gyro_rate(struct inv_mpu_state *st)
{
	int result;

	result = inv_set_rate(st, KEY_CFG_GYRO_ODR, KEY_ODR_CNTR_GYRO,
					st->sensor[SENSOR_GYRO].rate);

	return result;
}

static int inv_set_accel_rate(struct inv_mpu_state *st)
{
	int result;

	result = inv_set_rate(st, KEY_CFG_ACCL_ODR, KEY_ODR_CNTR_ACCL,
					st->sensor[SENSOR_ACCEL].rate);

	return result;
}

static int inv_set_compass_rate(struct inv_mpu_state *st)
{
	int result;

	result = inv_set_rate(st, KEY_CFG_CPASS_ODR, KEY_ODR_CNTR_CPASS,
					st->sensor[SENSOR_COMPASS].rate);

	return result;
}

static int inv_set_pressure_rate(struct inv_mpu_state *st)
{
	int result;

	result = inv_set_rate(st, KEY_CFG_PRESS_ODR, KEY_ODR_CNTR_PRESS,
					st->sensor[SENSOR_PRESSURE].rate);

	return result;
}

static int inv_set_step_detector(struct inv_mpu_state *st)
{
	return 0;
}


static int inv_set_lpq_rate(struct inv_mpu_state *st)
{
	int result;

	result = inv_set_rate(st, KEY_CFG_3QUAT_ODR, KEY_ODR_CNTR_3QUAT,
					st->sensor[SENSOR_LPQ].rate);

	return result;
}

static int inv_set_sixq_rate(struct inv_mpu_state *st)
{
	int result;

	result = inv_set_rate(st, KEY_CFG_6QUAT_ODR, KEY_ODR_CNTR_6QUAT,
					st->sensor[SENSOR_SIXQ].rate);

	return result;
}

static int inv_set_pedq_rate(struct inv_mpu_state *st)
{
	int result;

	result = inv_set_rate(st, KEY_CFG_PQUAT6_ODR, KEY_ODR_CNTR_PQUAT,
					st->sensor[SENSOR_PEDQ].rate);

	return result;
}

static int inv_set_accel_feedback_gain_klp(struct inv_mpu_state *st, bool on)
{
	int result;
	u8 reg;

	if (on)
		reg = 0xc0;
	else
		reg = 0xf1;

	result = mem_w_key(KEY_CFG_FB_GAIN_GYRO_ON, 1, &reg);

	return result;
}

static int inv_set_dmp_sysfs(struct inv_mpu_state *st)
{
	int result, i, s;
	u8 d[] = {0, 0, 0, 0};

	result = inv_set_interrupt_on_gesture_event(st,
				st->chip_config.dmp_event_int_on);
	if (result)
		return result;

	if (st->chip_config.dmp_event_int_on) {
		for (i = 0; i < SENSOR_NUM_MAX; i++) {
			result = st->sensor[i].send_data(st, false);
			if (result)
				return result;
		}
	} else {
		s = 0;
		st->batch.min_rate = MAX_DMP_OUTPUT_RATE;
		for (i = 0; i < SENSOR_NUM_MAX; i++) {
			result = st->sensor[i].send_data(st, st->sensor[i].on);
			if (result)
				return result;
			if (st->sensor[i].on) {
				if (0 == st->sensor[i].rate)
					return -EINVAL;
				if (st->sensor[i].rate < st->batch.min_rate)
					st->batch.min_rate = st->sensor[i].rate;
				s += st->sensor[i].rate *
						st->sensor[i].sample_size;

				result = st->sensor[i].set_rate(st);
				if (result)
					return result;
				st->sensor[i].counter = MPU_DEFAULT_DMP_FREQ /
							st->sensor[i].rate;
			}
		}
		st->bytes_per_sec = s;
		if (st->sensor[SENSOR_STEP].on)
			result = inv_add_step_indicator(st, true);
		else
			result = inv_add_step_indicator(st,
					st->chip_config.step_indicator_on);
		if (result)
			return result;
	}
	result = inv_batchmode_setup(st);
	if (result)
		return result;

	result = inv_set_accel_feedback_gain_klp(st,
					st->chip_config.gyro_enable);
	if (result)
		return result;
	st->dmp_counter = 0;
	result = mem_w_key(KEY_DMP_RUN_CNTR, ARRAY_SIZE(d), d);
	if (result)
		return result;
	result = mem_w_key(KEY_D_STPDET_TIMESTAMP, ARRAY_SIZE(d), d);

	return result;
}

static void inv_get_data_count(struct inv_mpu_state *st)
{
	struct inv_chip_config_s *c;
	int b, i;

	c = &st->chip_config;
	b = 0;
	if (st->chip_config.dmp_on) {
		for (i = 0; i < SENSOR_NUM_MAX; i++) {
			if (st->sensor[i].on)
				b += st->sensor[i].sample_size;
		}
	} else {
		if (st->sensor[SENSOR_ACCEL].on)
			b += BYTES_PER_SENSOR;
		if (st->sensor[SENSOR_GYRO].on)
			b += BYTES_PER_SENSOR;
	}
	c->bytes_per_datum = b;

	return;
}
/*
 *  set_inv_enable() - main enable/disable function.
 */
int set_inv_enable(struct iio_dev *indio_dev, bool enable)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);
	struct inv_reg_map_s *reg;
	u8 data[2];
	int result;
#if defined(CONFIG_SENSORS)
	u8 d;
#endif

	pr_info("[SENSOR] %s, enable = %x : %x%x%x%x", __func__, enable,
		st->chip_config.dmp_on,
		st->chip_config.gyro_enable,
		st->chip_config.accel_enable,
		st->sensor[SENSOR_COMPASS].on);

	reg = &st->reg;
	if (enable) {
		if (st->chip_config.dmp_on &&
				(!st->chip_config.firmware_loaded))
			return -EINVAL;
		st->batch.on = false;

		inv_get_data_count(st);
		result = inv_set_master_delay(st);
		if (result)
			return result;

		result = set_fifo_rate_reg(st);
		if (result)
			return result;
		if (st->chip_config.dmp_on) {
			result = inv_set_dmp_sysfs(st);
			if (result)
				return result;
		}

		if (st->chip_config.gyro_enable) {
			result = st->switch_gyro_engine(st, true);
			if (result)
				return result;
		}
		if (st->chip_config.accel_enable) {
			result = st->switch_accel_engine(st, true);
			if (result)
				return result;
		}
		if (st->sensor[SENSOR_COMPASS].on) {
			result = st->slave_compass->resume(st);
			if (result)
				return result;
		}
		if (st->sensor[SENSOR_PRESSURE].on) {
			result = st->slave_pressure->resume(st);
			if (result)
				return result;
		}
		result = inv_reset_fifo(indio_dev);
		if (result)
			return result;
	} else {
		if ((INV_MPU3050 != st->chip_type)
			&& st->chip_config.lpa_mode) {
			/* if the chip is in low power mode,
				register write/read could fail */
			result = inv_lpa_mode(st, 0);
			if (result)
				return result;
		}
		result = inv_i2c_single_write(st, reg->fifo_en, 0);
		if (result)
			return result;
		if (st->chip_config.dmp_on) {
			result = inv_read_time_and_ticks(st, false);
			if (result)
				return result;
			result = inv_i2c_read(st, reg->fifo_count_h,
						FIFO_COUNT_BYTE, data);
			if (result)
				return result;
			st->fifo_count = be16_to_cpup((__be16 *)(data));
			if (st->fifo_count) {
				result = inv_process_batchmode(st);
				if (result)
					return result;
			}
		}
		inv_push_marker_to_buffer(st, END_MARKER);
		/* disable fifo reading */
		if (INV_MPU3050 != st->chip_type) {
			result = inv_i2c_single_write(st, reg->int_enable, 0);
			if (result)
				return result;
			result = inv_i2c_single_write(st, reg->user_ctrl, 0);
		} else {
			result = inv_i2c_single_write(st, reg->int_enable,
				st->plat_data.int_config);
		}
		if (result)
			return result;
		/* turn off the gyro/accel engine during disable phase */
		result = st->switch_gyro_engine(st, false);
		if (result)
			return result;
		result = st->switch_accel_engine(st, false);
		if (result)
			return result;
		if (st->sensor[SENSOR_COMPASS].on) {
			result = st->slave_compass->suspend(st);
			if (result)
				return result;
		}
		if (st->sensor[SENSOR_PRESSURE].on) {
			result = st->slave_pressure->suspend(st);
			if (result)
				return result;
		}
	}
	st->chip_config.enable = enable;

#if defined(CONFIG_SENSORS)

	if (st->reactive_enable) {
		result = inv_i2c_read(st, REG_PWR_MGMT_1, 1, &d);
		if (result)
			return result;

		if (d & BIT_SLEEP) {
			/* Power up the chip and clear the cycle bit. Full power */
			inv_i2c_single_write(st, REG_PWR_MGMT_1, 0x01);
			mdelay(50);
			inv_i2c_single_write(st, REG_PWR_MGMT_2, 0x00);
		}

		if (!(st->chip_config.enable || st->chip_config.dmp_on))
			inv_i2c_single_write(st, REG_CONFIG, 0x00);

		result = inv_i2c_read(st, REG_INT_ENABLE, 1, &d);
		if (result)
			return result;

		/* Set motion thr & dur */
		if (st->factory_mode)
			d |= BIT_MOT_INT | 0x01;	/* Make the motion & drdy enable */
		else
			d |= BIT_MOT_INT;		/* Make the motion interrupt enable */
		inv_i2c_single_write(st, REG_INT_ENABLE, d);

		 /* Motion Duration =1 ms */
		inv_i2c_single_write(st, REG_6500_ACCEL_INTEL_CTRL, 0xC0);

		/* Motion Threshold =1mg, based on the data sheet. */
		if (st->factory_mode)
			d = 0x00;
		else
			d = 0x0C + 0x5;
		inv_i2c_single_write(st, REG_6500_ACCEL_WOM_THR, d);

		d = 0x04;	/* 3.91 Hz (low power accel odr) */
		inv_i2c_single_write(st, REG_6500_LP_ACCEL_ODR, d);

		/* put gyro in standby. */
		if (!(st->chip_config.gyro_enable))
			inv_i2c_single_write(st, REG_PWR_MGMT_2, BIT_PWR_GYRO_STBY);
		else
			inv_i2c_single_write(st, REG_PWR_MGMT_2, 0x00);

		/* Set the cycle bit to be 1. LP MODE */
		if (!(st->chip_config.enable || st->chip_config.dmp_on))
			inv_i2c_single_write(st, REG_PWR_MGMT_1, 0x21);
		else
			inv_i2c_single_write(st, REG_PWR_MGMT_1, 0x01);

		pr_info("[SENSOR] %s, setting reactive config\n", __func__);
		st->mot_st_time = jiffies;
	}
#endif
	return 0;
}

/*
 *  inv_irq_handler() - Cache a timestamp at each data ready interrupt.
 */
static irqreturn_t inv_irq_handler(int irq, void *dev_id)
{
	struct inv_mpu_state *st = (struct inv_mpu_state *)dev_id;
	u64 ts;

	if (!st->chip_config.dmp_on) {
		ts = get_time_ns();
		kfifo_in_spinlocked(&st->timestamps, &ts, 1,
						&st->time_stamp_lock);
	}

	return IRQ_WAKE_THREAD;	//inv_read_fifo_mpu3050
}

static void inv_report_data_3050(struct iio_dev *indio_dev, s64 t,
			int has_footer, u8 *data)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);
	int ind, i;
	short s[THREE_AXIS];

	ind = 0;
	if (has_footer)
		ind += 2;

	if (st->sensor[SENSOR_GYRO].on) {
		for (i = 0; i < 3; i++)
			s[i] = be16_to_cpup((__be16 *)(&data[ind + i * 2]));

		inv_push_8bytes_buffer(st, GYRO_HDR, t, s);
		ind += BYTES_PER_SENSOR;
	}
	if (st->sensor[SENSOR_ACCEL].on) {
		st->slave_accel->combine_data(&data[ind], s);
		inv_push_8bytes_buffer(st, ACCEL_HDR, t, s);
	}
}

/*
 *  inv_read_fifo_mpu3050() - Transfer data from FIFO to ring buffer for
 *                            mpu3050.
 */
irqreturn_t inv_read_fifo_mpu3050(int irq, void *dev_id)
{

	struct inv_mpu_state *st = (struct inv_mpu_state *)dev_id;
	struct iio_dev *indio_dev = iio_priv_to_dev(st);
	int bytes_per_datum;
	u8 data[64];
	int result;
	short fifo_count, byte_read;
	s64 timestamp;
	struct inv_reg_map_s *reg;

	reg = &st->reg;
	mutex_lock(&st->suspend_resume_lock);
	mutex_lock(&indio_dev->mlock);
	if (st->chip_config.dmp_on)
		bytes_per_datum = HEADERED_NORMAL_BYTES;
	else
		bytes_per_datum = (st->sensor[SENSOR_ACCEL].on +
			st->sensor[SENSOR_GYRO].on) * BYTES_PER_SENSOR;
	if (st->chip_config.has_footer)
		byte_read = bytes_per_datum + MPU3050_FOOTER_SIZE;
	else
		byte_read = bytes_per_datum;

	fifo_count = 0;
	if (byte_read != 0) {
		result = inv_i2c_read(st, reg->fifo_count_h,
				FIFO_COUNT_BYTE, data);
		if (result)
			goto end_session;
		fifo_count = be16_to_cpup((__be16 *)(&data[0]));
		if (fifo_count < byte_read)
			goto end_session;
		if (fifo_count & 1)
			goto flush_fifo;
		if (fifo_count > FIFO_THRESHOLD)
			goto flush_fifo;
		/* Timestamp mismatch. */
		if (kfifo_len(&st->timestamps) <
			fifo_count / byte_read)
			goto flush_fifo;
		if (kfifo_len(&st->timestamps) >
			fifo_count / byte_read + TIME_STAMP_TOR) {
			if (st->chip_config.dmp_on) {
				result = kfifo_out(&st->timestamps,
				&timestamp, 1);
				if (result != 1)
					goto flush_fifo;
			} else {
				goto flush_fifo;
			}
		}
	}
	while ((bytes_per_datum != 0) && (fifo_count >= byte_read)) {
		result = inv_i2c_read(st, reg->fifo_r_w, byte_read, data);
		if (result)
			goto flush_fifo;

		result = kfifo_out(&st->timestamps, &timestamp, 1);
		if (result != 1)
			goto flush_fifo;
		inv_report_data_3050(indio_dev, timestamp,
				     st->chip_config.has_footer, data);
		fifo_count -= byte_read;
		if (st->chip_config.has_footer == 0) {
			st->chip_config.has_footer = 1;
			byte_read = bytes_per_datum + MPU3050_FOOTER_SIZE;
		}
	}

end_session:
	mutex_unlock(&indio_dev->mlock);
	mutex_unlock(&st->suspend_resume_lock);

	return IRQ_HANDLED;

flush_fifo:
	/* Flush HW and SW FIFOs. */
	inv_reset_fifo(indio_dev);
	inv_clear_kfifo(st);
	mutex_unlock(&indio_dev->mlock);
	mutex_unlock(&st->suspend_resume_lock);

	return IRQ_HANDLED;
}

static int inv_report_gyro_accel(struct iio_dev *indio_dev,
					u8 *data, s64 t)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);
	short s[THREE_AXIS];
	int ind;
	int i;

	ind = 0;
	if (st->sensor[SENSOR_ACCEL].on) {
		for (i = 0; i < 3; i++) {
			s[i] = be16_to_cpup((__be16 *)(&data[ind + i * 2]));
			st->accel_data[i] = s[i];
			s[i] = s[i] + st->cal_data[i];
		}
		inv_push_8bytes_buffer(st, ACCEL_HDR, t, s);
		ind += BYTES_PER_SENSOR;
	}

	if (st->sensor[SENSOR_GYRO].on) {
		for (i = 0; i < 3; i++)
			s[i] = be16_to_cpup((__be16 *)(&data[ind + i * 2]));
		inv_push_8bytes_buffer(st, GYRO_HDR, t, s);
		ind += BYTES_PER_SENSOR;
	}

	return 0;
}

static void inv_process_motion(struct inv_mpu_state *st)
{
	struct iio_dev *indio_dev = iio_priv_to_dev(st);
	int result;
	u8 data;
#if defined(CONFIG_SENSORS)
	unsigned long timediff = 0;
#endif

	/* motion interrupt */
	result = inv_i2c_read(st, REG_INT_STATUS, 1, &data);
	if (result)
		return;

	if (data & BIT_MOT_INT || st->factory_mode) {
		sysfs_notify(&indio_dev->dev.kobj, NULL, "event_accel_motion");

#if defined(CONFIG_SENSORS)
		timediff = jiffies_to_msecs(jiffies - st->mot_st_time);
		/* ignore motion interrupt happened in 100ms to skip intial erronous interrupt */
		if (timediff < 1000 && !(st->factory_mode)) {
			pr_err("[SENSOR] %s: timediff = %ld msec\n", __func__, timediff);
			return;
		}

		st->reactive_state = 1;
		pr_info("[SENSOR] Reactive alert happened ##############\n");

		result = inv_i2c_read(st, REG_INT_ENABLE, 1, &data);
		if (result)
			return;
		data &= ~BIT_MOT_INT;
		if (st->factory_mode) {
			data &= ~0x01;
			st->factory_mode = false;
		}

		inv_i2c_single_write(st, REG_INT_ENABLE, data);
		wake_lock_timeout(&st->reactive_wake_lock, msecs_to_jiffies(2000));

		pr_info("[SENSOR] %s: disable interrupt\n", __func__);
#endif
	}
}

static int inv_get_timestamp(struct inv_mpu_state *st, int count)
{
	u32 *dur;
	u32 thresh;
	s32 diff, result, counter;
	u64 ts;

	/* goal of algorithm is to estimate the true frequency of the chip */
	if (st->chip_config.dmp_on && st->chip_config.dmp_event_int_on)
		return 0;
	dur = &st->irq_dur_ns;
	counter = 1;
	thresh = min((u32)((*dur) >> 2), (u32)(10 * NSEC_PER_MSEC));
	while (kfifo_len(&st->timestamps) >= count) {
		result = kfifo_out(&st->timestamps, &ts, 1);
		if (result != 1)
			return -EINVAL;
		/* first time since reset fifo, just take it */
		if (!st->ts_counter) {
			st->last_ts = ts;
			st->prev_ts = ts;
			st->ts_counter++;
			return 0;
		}
		diff = (s32)(ts - st->prev_ts);
		st->prev_ts = ts;
		if (abs(diff - (*dur)) < thresh) {
			st->diff_accumulater >>= 1;
			if (*dur > diff)
				st->diff_accumulater -= (((*dur) - diff) >> 7);
			else
				st->diff_accumulater += ((diff - (*dur)) >> 7);
			*dur += st->diff_accumulater;
		}
	}
	ts = *dur;
	ts *= counter;
	st->last_ts += ts;

	return 0;
}

static int inv_process_dmp_interrupt(struct inv_mpu_state *st)
{
	int r;
	u8 d[2];
	struct iio_dev *indio_dev = iio_priv_to_dev(st);

#define DMP_INT_SHEALT      0x02	// Disabled by HQ
#define DMP_INT_SMD             0x04
#define DMP_INT_PED             0x08
#define DMP_INT_QSHOT_START     0x10
#define DMP_INT_QSHOT_FINISH    0x20

	if ((!st->chip_config.smd_enable) &&
		(!st->ped.int_on) &&
		(!st->qshot.start_int_enable) &&
		(!st->qshot.finish_int_enable) &&
		(!st->shealth.enabled))
		return 0;

	r = inv_i2c_read(st, REG_DMP_INT_STATUS, 1, d);
	if (r)
		return r;

	if (d[0] & DMP_INT_SHEALT) {
		pr_info("[shealth]%d minute interrupt!!!!\n", st->shealth.interrupt_duration);

		/*wake AP for 1 sec*/
		wake_lock_timeout(&st->shealth.wake_lock,msecs_to_jiffies(1000));
		st->shealth.interrupt_counter ++;
		st->shealth.interrupt_timestamp = inv_get_shealth_timestamp(st, false);
		st->shealth.interrupt_time_timeofday = get_time_timeofday();

		st->shealth.interrupt_mask |= SHEALTH_INT_CADENCE;
		inv_get_shealth_cadence(st, 1, 21, st->shealth.cadence);
		st->shealth.valid_count = st->shealth.interrupt_duration;
		/*adjust interrupt time period*/
		{
			u16 tick_count = 0;

			s32 kerneltime_diff = (st->shealth.interrupt_time_timeofday
						- st->shealth.start_time_timeofday) >> 30;
			s32 timestamp_diff = (st->shealth.interrupt_timestamp
						- st->shealth.start_timestamp) >> 30;
			tick_count =  timestamp_diff * (st->shealth.tick_count + 1)
					/ kerneltime_diff - 1;
			pr_info("[SHEALTH] %s Tick[Before After] = [%d %d]\n", __func__,
				st->shealth.tick_count, tick_count);

			/*change the value of update timer for adjusting interrupt timing*/
			inv_set_shealth_update_timer(st, tick_count);
			st->shealth.tick_count = tick_count;
		}
		complete(&st->shealth.wait);
	}

	if (d[0] & DMP_INT_SMD) {
		sysfs_notify(&indio_dev->dev.kobj, NULL, "event_smd");
		st->chip_config.smd_enable = false;
		st->chip_config.smd_triggered = true;
	}
	if (d[0] & DMP_INT_PED)
		sysfs_notify(&indio_dev->dev.kobj, NULL, "event_pedometer");
	if (d[0] & DMP_INT_QSHOT_START)
		sysfs_notify(&indio_dev->dev.kobj, NULL, "event_qshot_start");
	if (d[0] & DMP_INT_QSHOT_FINISH)
		sysfs_notify(&indio_dev->dev.kobj, NULL, "event_qshot_finish");

	return 0;
}

static int inv_get_shift2(int count)
{
	int i;

	if (1 == count)
		return 13;
	if (count > 2000)
		return 2;
	i = 13;
	while (count > 0) {
		count >>= 1;
		i--;
	}

	return i;
}

static void inv_adjust_sensor_ts(struct inv_mpu_state *st, int sensor_ind)
{
	s64 diff;
	int i, rate_adj, s3, delta, total_count;

	if (!st->chip_config.adjust_time)
		return;
#define MAX_DIFF 0x7fffffff
	total_count = st->dmp_ticks;
	if (0 == total_count)
		total_count = 1;

	diff = (st->last_ts - st->prev_ts) - (u64)(st->dmp_interval) *
								total_count;
	if (diff > MAX_DIFF)
		diff = MAX_DIFF;
	if (diff < -MAX_DIFF)
		diff = -MAX_DIFF;
	s3 = 4;
	rate_adj = (int)diff;
	rate_adj /= total_count;
	delta = min(abs(rate_adj) >> inv_get_shift2(total_count),
						DMP_INTERVAL_MIN_ADJ);
	if (rate_adj < 0)
		delta = -delta;
	st->dmp_interval_accum >>= 1;
	st->dmp_interval_accum += delta;
	st->dmp_interval += st->dmp_interval_accum;
	for (i = 0; i < SENSOR_NUM_MAX; i++)
		if (st->sensor[i].on)
			st->sensor[i].dur = st->dmp_interval *
						st->sensor[i].counter;

	st->prev_ts = st->last_ts;
}

static void inv_reset_ts(struct inv_mpu_state *st, u64 curr_ts)
{
	u32 dur, i;

	dur = USEC_PER_SEC / st->bytes_per_sec;
	dur *= HARDWARE_FIFO_SIZE;
	curr_ts -= ((u64)dur * NSEC_PER_USEC);
	for (i = 0; i < SENSOR_NUM_MAX; i++)
		st->sensor[i].ts = curr_ts;
}

static void inv_push_step_indicator(struct inv_mpu_state *st, int sensor_ind,
							int steps)
{
	int dur, i;
	s16 sen[3];
	u64 base;
#define STEP_INDICATOR_HEADER 0x0001

	dur = st->sensor[sensor_ind].dur / steps;
	base = st->sensor[sensor_ind].ts;

	for (i = 1; i < steps; i++)
		inv_push_8bytes_buffer(st, STEP_INDICATOR_HEADER,
						base + i * dur, sen);
}

static int inv_parse_header(u16 hdr)
{
	switch (hdr) {
	case ACCEL_HDR:
		return SENSOR_ACCEL;
	case GYRO_HDR:
		return SENSOR_GYRO;
	case PEDQUAT_HDR:
		return SENSOR_PEDQ;
	case LPQUAT_HDR:
		return SENSOR_LPQ;
	case SIXQUAT_HDR:
		return SENSOR_SIXQ;
	case COMPASS_HDR:
	case COMPASS_HDR_2:
		return SENSOR_COMPASS;
	case PRESSURE_HDR:
		return SENSOR_PRESSURE;
	case STEP_DETECTOR_HDR:
		return SENSOR_STEP;
	default:
		return SENSOR_INVALID;
	}
}
#define FEATURE_IKR_PANIC 1

static int inv_process_batchmode(struct inv_mpu_state *st)
{
	int i, target_bytes, tmp, res, counter;
	int sensor_ind, q[3];
	u8 *dptr, *d;
	u16 hdr, steps;
	s16 sen[3];
	u64 t;
	bool done_flag;

#if FEATURE_IKR_PANIC
	if (HARDWARE_FIFO_SIZE <= st->fifo_count) {
		if (HARDWARE_FIFO_SIZE < st->fifo_count) {
			pr_err("fifo_count over spec\n");
			return 0;
		}
		inv_reset_ts(st, st->last_ts);
		st->left_over_size = 0;
	}
#else
	if (HARDWARE_FIFO_SIZE == st->fifo_count) {
		inv_reset_ts(st, st->last_ts);
		st->left_over_size = 0;
	}
#endif

	d = fifo_data;
	if (st->left_over_size > 0) {
#if FEATURE_IKR_PANIC
		if (st->left_over_size > HEADERED_Q_BYTES) {
			pr_err("left_over_size overflow 1\n");
			st->left_over_size = HEADERED_Q_BYTES;
		}
#endif
		dptr = d + st->left_over_size;
		memcpy(d, st->left_over, st->left_over_size);
	} else {
		dptr = d;
	}
	target_bytes = st->fifo_count;
	while (target_bytes > 0) {
		if (target_bytes < MAX_READ_SIZE)
			tmp = target_bytes;
		else
			tmp = MAX_READ_SIZE;
		res = inv_i2c_read(st, st->reg.fifo_r_w, tmp, dptr);
		if (res < 0)
			return res;
		dptr += tmp;
		target_bytes -= tmp;
	}
	dptr = d;
	done_flag = false;
	target_bytes = st->fifo_count + st->left_over_size;
	counter = 0;
	while (((dptr - d) <= (target_bytes - HEADERED_NORMAL_BYTES)) &&
							(!done_flag)) {
		hdr = (u16)be16_to_cpup((__be16 *)(dptr));
		steps = (hdr & STEP_INDICATOR_MASK);
		hdr &= (~STEP_INDICATOR_MASK);
		sensor_ind = inv_parse_header(hdr);
		/* error packet */
		if ((sensor_ind == SENSOR_INVALID) ||
				(!st->sensor[sensor_ind].on)) {
			dptr += (HEADERED_NORMAL_BYTES / 4);
			continue;
		}
		/* incomplete packet */
		if ((target_bytes - (dptr - d)) <
					st->sensor[sensor_ind].sample_size) {
			done_flag = true;
			continue;
		}
		if (sensor_ind == SENSOR_STEP) {
			tmp = (int)be32_to_cpup((__be32 *)(dptr + 4));
			t = st->step_detector_base_ts +
					(u64)tmp * 5 * NSEC_PER_MSEC;
			inv_push_8bytes_buffer(st, hdr, t, sen);
			dptr += HEADERED_NORMAL_BYTES;
			continue;
		}
		if (steps > 1)
			inv_push_step_indicator(st, sensor_ind, steps);
		st->sensor[sensor_ind].ts += (u64)st->sensor[sensor_ind].dur;
		t = st->sensor[sensor_ind].ts;
		if (sensor_ind == SENSOR_COMPASS) {
			if (!st->chip_config.normal_compass_measure) {
				st->chip_config.normal_compass_measure = 1;
			} else if (COMPASS_HDR == hdr) {
				for (i = 0; i < 6; i++)
					st->fifo_data[i] = dptr[i + 2];
				res = st->slave_compass->read_data(st, sen);
				if (!res)
					inv_push_8bytes_buffer(st, hdr |
							(!!steps), t, sen);
			} else if (COMPASS_HDR_2 == hdr) {
				inv_push_marker_to_buffer(st, hdr);
			}
			dptr += HEADERED_NORMAL_BYTES;
			continue;
		}
		if (sensor_ind == SENSOR_PRESSURE) {
			if (!st->chip_config.normal_pressure_measure) {
				st->chip_config.normal_pressure_measure = 1;
			} else {
				for (i = 0; i < 6; i++)
					st->fifo_data[i] = dptr[i + 2];
				res = st->slave_pressure->read_data(st, sen);
				if (!res)
					inv_push_8bytes_buffer(st, hdr |
							(!!steps), t, sen);
			}
			dptr += HEADERED_NORMAL_BYTES;
			continue;
		}
		if (st->sensor[sensor_ind].sample_size == HEADERED_Q_BYTES) {
			for (i = 0; i < 3; i++)
				q[i] = (int)be32_to_cpup((__be32 *)(dptr + 4
							+ i * 4));
			inv_push_16bytes_buffer(st, hdr | (!!steps), t, q);
		} else {
			for (i = 0; i < 3; i++) {
				sen[i] = (short)be16_to_cpup((__be16 *)(dptr +
							2 + i * 2));
				if (sensor_ind == SENSOR_ACCEL) {
					st->accel_data[i] = sen[i];
					sen[i] = sen[i] + st->cal_data[i];
				}
			}

			inv_push_8bytes_buffer(st, hdr | (!!steps), t, sen);
		}
		dptr += st->sensor[sensor_ind].sample_size;
	}
	inv_adjust_sensor_ts(st, sensor_ind);
	st->left_over_size = target_bytes - (dptr - d);

	if (st->left_over_size) {
#if FEATURE_IKR_PANIC
		if (st->left_over_size > HEADERED_Q_BYTES) {
			pr_err("left_over_size overflow 2\n");
			st->left_over_size = HEADERED_Q_BYTES;
		}
#endif
		memcpy(st->left_over, dptr, st->left_over_size);
	}

	return 0;
}

int inv_read_time_and_ticks(struct inv_mpu_state *st, bool resume)
{
	int result;
	u32 counter;
	u8 data[4];

#define MIN_TICK_READING_TIME NSEC_PER_SEC
	st->last_ts = get_time_ns();
	if ((st->last_ts - st->prev_ts < MIN_TICK_READING_TIME) &&
							(!resume)) {
		st->chip_config.adjust_time = false;
		return 0;
	}
	result = mpu_memory_read(st, st->i2c_addr,
			inv_dmp_get_address(KEY_DMP_RUN_CNTR), 4, data);
	if (result)
		return result;

	counter = be32_to_cpup((__be32 *)(data));
	if (resume) {
		st->dmp_counter = counter;
		st->prev_ts = st->last_ts;

		return 0;
	}
	if (counter > st->dmp_counter)
		st->dmp_ticks = counter - st->dmp_counter;
	else
		st->dmp_ticks = 0xffffffff - st->dmp_counter + counter + 1;
	st->dmp_counter = counter;
	st->chip_config.adjust_time = true;

	return 0;
}

/*
 *  inv_read_fifo() - Transfer data from FIFO to ring buffer.
 */
irqreturn_t inv_read_fifo(int irq, void *dev_id)
{

	struct inv_mpu_state *st = (struct inv_mpu_state *)dev_id;
	struct iio_dev *indio_dev = iio_priv_to_dev(st);
	int result, bpm;
	u8 data[MAX_HW_FIFO_BYTES];
	u16 fifo_count;
	struct inv_reg_map_s *reg;
	u64 pts1;

	if(st->reactive_enable) {
		result = inv_i2c_read(st, REG_INT_ENABLE, 1, data);
		if (result)
			goto end_session;

		if (data[0] & BIT_MOT_INT)
			inv_process_motion(st);

		if ((data[0] & ~BIT_MOT_INT) == 0x00)
			goto end_session;
	}

#define DMP_MIN_RUN_TIME (37 * NSEC_PER_MSEC)
	if (st->suspend_state)
		return IRQ_HANDLED;
	if (st->chip_config.dmp_on) {
		pts1 = get_time_ns();
		result = inv_process_dmp_interrupt(st);
		if (result || st->chip_config.dmp_event_int_on)
			goto end_session;
		if (!st->chip_config.smd_triggered) {
			if (pts1 - st->last_run_time < DMP_MIN_RUN_TIME)
				goto end_session;
			else
				st->last_run_time = pts1;
		} else {
			st->chip_config.smd_triggered = false;
		}
	}

	if (!(iio_buffer_enabled(indio_dev)) || (!st->chip_config.enable))
		goto end_session;

	reg = &st->reg;
	if (!(st->sensor[SENSOR_ACCEL].on |
		st->sensor[SENSOR_GYRO].on |
		st->sensor[SENSOR_COMPASS].on |
		st->sensor[SENSOR_PRESSURE].on |
		st->chip_config.dmp_on |
		st->mot_int.mot_on))
		goto end_session;
	if (st->chip_config.lpa_mode) {
		result = inv_i2c_read(st, reg->raw_accel,
						BYTES_PER_SENSOR, data);
		if (result)
			goto end_session;
		inv_report_gyro_accel(indio_dev, data, get_time_ns());
		if (st->mot_int.mot_on)
			inv_process_motion(st);

		goto end_session;
	}

	if (st->chip_config.dmp_on) {
		result = inv_read_time_and_ticks(st, false);
		if (result)
			goto end_session;
	}
	bpm = st->chip_config.bytes_per_datum;
	fifo_count = 0;
	if (bpm) {
		result = inv_i2c_read(st, reg->fifo_count_h, FIFO_COUNT_BYTE,
									data);
		if (result)
			goto end_session;
		fifo_count = be16_to_cpup((__be16 *)(data));
		/* fifo count can't be odd number */
		if (fifo_count & 1)
			goto flush_fifo;
		if (fifo_count == 0)
			goto end_session;
		st->fifo_count = fifo_count;
	}

	if (st->chip_config.dmp_on) {
		result = inv_process_batchmode(st);
	} else {
		if (fifo_count >  FIFO_THRESHOLD)
			goto flush_fifo;
		if (bpm) {
			while (fifo_count >= bpm) {
				result = inv_i2c_read(st, reg->fifo_r_w, bpm,
									data);
				if (result)
					goto flush_fifo;
				result = inv_get_timestamp(st,
							fifo_count / bpm);
				if (result)
					goto flush_fifo;
				inv_report_gyro_accel(indio_dev, data,
								st->last_ts);
				fifo_count -= bpm;
			}
		} else {
			result = inv_get_timestamp(st, 1);
			if (result)
				goto flush_fifo;
		}
		inv_send_compass_data(st);
		inv_send_pressure_data(st);
	}
end_session:

	return IRQ_HANDLED;
flush_fifo:
	/* Flush HW and SW FIFOs. */
	inv_reset_fifo(indio_dev);
	inv_clear_kfifo(st);

	return IRQ_HANDLED;
}

void inv_mpu_unconfigure_ring(struct iio_dev *indio_dev)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);
	free_irq(st->client->irq, st);
	iio_kfifo_free(indio_dev->buffer);
};

static int inv_predisable(struct iio_dev *indio_dev)
{
	struct inv_mpu_state  *st = iio_priv(indio_dev);
	int result;

	if (st->chip_config.enable) {
		result = set_inv_enable(indio_dev, false);
		if (result)
			return result;
		result = st->set_power_state(st, false);
		if (result)
			return result;
	}

	return 0;
}

static int inv_check_conflict_sysfs(struct iio_dev *indio_dev)
{
	struct inv_mpu_state  *st = iio_priv(indio_dev);

	if (st->chip_config.lpa_mode) {
		/* dmp cannot run with low power mode on */
		st->chip_config.dmp_on = 0;
		st->chip_config.gyro_enable = false;
		st->sensor[SENSOR_GYRO].on = false;
		st->sensor[SENSOR_COMPASS].on = false;
	}
	if (st->sensor[SENSOR_GYRO].on &&
		(!st->chip_config.gyro_enable)) {
		st->chip_config.gyro_enable = true;
	}
	if (st->sensor[SENSOR_ACCEL].on &&
		(!st->chip_config.accel_enable)) {
		st->chip_config.accel_enable = true;
	}

	return 0;
}

static int inv_preenable(struct iio_dev *indio_dev)
{
	int result;

	result = inv_check_conflict_sysfs(indio_dev);
	if (result)
		return result;
	result = iio_sw_buffer_preenable(indio_dev);

	return result;
}

void inv_init_sensor_struct(struct inv_mpu_state *st)
{
	int i;

	for (i = 0; i < SENSOR_NUM_MAX; i++) {
		if (i < SENSOR_SIXQ)
			st->sensor[i].sample_size =
					HEADERED_NORMAL_BYTES;
		else
			st->sensor[i].sample_size = HEADERED_Q_BYTES;
		if (i == SENSOR_STEP) {
			st->sensor[i].rate = 1;
			st->sensor[i].dur = NSEC_PER_SEC;
		} else {
			st->sensor[i].rate = INIT_DMP_OUTPUT_RATE;
			st->sensor[i].dur  = NSEC_PER_SEC /
						INIT_DMP_OUTPUT_RATE;
		}
	}

	st->sensor[SENSOR_ACCEL].send_data     = inv_send_accel_data;
	st->sensor[SENSOR_GYRO].send_data      = inv_send_gyro_data;
	st->sensor[SENSOR_COMPASS].send_data   = inv_send_compass_dmp_data;
	st->sensor[SENSOR_PRESSURE].send_data  = inv_send_pressure_dmp_data;
	st->sensor[SENSOR_STEP].send_data      = inv_send_step_detector;
	st->sensor[SENSOR_PEDQ].send_data      = inv_send_ped_q_data;
	st->sensor[SENSOR_SIXQ].send_data      = inv_send_six_q_data;
	st->sensor[SENSOR_LPQ].send_data       = inv_send_three_q_data;

	st->sensor[SENSOR_ACCEL].set_rate     = inv_set_accel_rate;
	st->sensor[SENSOR_GYRO].set_rate      = inv_set_gyro_rate;
	st->sensor[SENSOR_COMPASS].set_rate   = inv_set_compass_rate;
	st->sensor[SENSOR_PRESSURE].set_rate  = inv_set_pressure_rate;
	st->sensor[SENSOR_STEP].set_rate      = inv_set_step_detector;
	st->sensor[SENSOR_PEDQ].set_rate      = inv_set_pedq_rate;
	st->sensor[SENSOR_SIXQ].set_rate      = inv_set_sixq_rate;
	st->sensor[SENSOR_LPQ].set_rate       = inv_set_lpq_rate;
}

int inv_flush_batch_data(struct iio_dev *indio_dev, bool *has_data)
{
	struct inv_mpu_state *st = iio_priv(indio_dev);
	struct inv_reg_map_s *reg;
	u8 data[FIFO_COUNT_BYTE];
	int result;

	reg = &st->reg;
	if (!(iio_buffer_enabled(indio_dev)) || (!st->chip_config.enable))
		return -EINVAL;

	if (st->batch.on) {
		result = inv_read_time_and_ticks(st, false);
		if (result)
			return result;
		result = inv_i2c_read(st, reg->fifo_count_h,
					FIFO_COUNT_BYTE, data);
		if (result)
			return result;
		st->fifo_count = be16_to_cpup((__be16 *)(data));
		if (st->fifo_count) {
			result = inv_process_batchmode(st);
			if (result)
				return result;
			*has_data = !!st->fifo_count;
			inv_push_marker_to_buffer(st, END_MARKER);
			result = write_be32_key_to_mem(st, 0,
						KEY_BM_BATCH_CNTR);
			return result;
		}
	}
	inv_push_marker_to_buffer(st, EMPTY_MARKER);

	return 0;
}

static const struct iio_buffer_setup_ops inv_mpu_ring_setup_ops = {
	.preenable = &inv_preenable,
	.predisable = &inv_predisable,
};

int inv_mpu_configure_ring(struct iio_dev *indio_dev)
{
	int ret;
	struct inv_mpu_state *st = iio_priv(indio_dev);
	struct iio_buffer *ring;

	ring = iio_kfifo_allocate(indio_dev);
	if (!ring)
		return -ENOMEM;
	indio_dev->buffer = ring;
	/* setup ring buffer */
	ring->scan_timestamp = true;
	indio_dev->setup_ops = &inv_mpu_ring_setup_ops;
	/*scan count double count timestamp. should subtract 1. but
	number of channels still includes timestamp*/
	if (INV_MPU3050 == st->chip_type)
		ret = request_threaded_irq(st->client->irq, inv_irq_handler,
			inv_read_fifo_mpu3050,
			IRQF_TRIGGER_RISING | IRQF_SHARED, "inv_irq", st);
	else
		ret = request_threaded_irq(st->client->irq, inv_irq_handler,
			inv_read_fifo,
			IRQF_TRIGGER_RISING | IRQF_SHARED, "inv_irq", st);
	if (ret)
		goto error_iio_sw_rb_free;

	indio_dev->modes |= INDIO_BUFFER_TRIGGERED;

	return 0;
error_iio_sw_rb_free:
	iio_kfifo_free(indio_dev->buffer);

	return ret;
}

