/*****************************************************************************
	Copyright(c) 2013 FCI Inc. All Rights Reserved

	File name : fc8300_spi.c

	Description : source of SPI interface

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

	History :
	----------------------------------------------------------------------
*******************************************************************************/
#include <linux/spi/spi.h>
#include <linux/slab.h>
#include <linux/module.h>

#include "fci_types.h"
#include "fc8300_regs.h"
#include "fci_oal.h"

#define SPI_LEN             0x00 /* or 0x10 */
#define SPI_REG             0x20
#define SPI_THR             0x30
#define SPI_READ            0x40
#define SPI_WRITE           0x00
#define SPI_AINC            0x80

#define DRIVER_NAME "fc8300_spi"

struct spi_device *fc8300_spi;

static u8 tx_data[10];

static u8 wdata_buf[32] __cacheline_aligned;
static u8 rdata_buf[65536] __cacheline_aligned;

static DEFINE_MUTEX(fci_spi_lock);

static int fc8300_spi_probe(struct spi_device *spi)
{
	s32 ret;

	print_log(0, "fc8300_spi_probe\n");

	spi->max_speed_hz = 52000000;
	spi->bits_per_word = 8;
	spi->mode =  SPI_MODE_0;

	ret = spi_setup(spi);

	if (ret < 0)
		return ret;

	fc8300_spi = spi;

	return ret;
}

static int fc8300_spi_remove(struct spi_device *spi)
{

	return 0;
}

static struct spi_driver fc8300_spi_driver = {
	.driver = {
		.name		= DRIVER_NAME,
		.owner		= THIS_MODULE,
	},
	.probe		= fc8300_spi_probe,
	.remove		= fc8300_spi_remove,
};

static int fc8300_spi_write_then_read(struct spi_device *spi
	, u8 *txbuf, u16 tx_length, u8 *rxbuf, u16 rx_length)
{
	int res = 0;

	struct spi_message	message;
	struct spi_transfer	x;

	if (spi == NULL) {
		print_log(0, "[ERROR] FC8300_SPI Handle Fail...........\n");
		return BBM_NOK;
	}

	spi_message_init(&message);
	memset(&x, 0, sizeof x);

	spi_message_add_tail(&x, &message);

	memcpy(&wdata_buf[0], txbuf, tx_length);

	x.tx_buf = &wdata_buf[0];
	x.rx_buf = &rdata_buf[0];
	x.len = tx_length + rx_length;
	x.cs_change = 0;
	x.bits_per_word = 8;
	res = spi_sync(spi, &message);

	memcpy(rxbuf, x.rx_buf + tx_length, rx_length);

	return res;
}

static s32 spi_bulkread(HANDLE handle, u8 devid,
		u16 addr, u8 command, u8 *data, u16 length)
{
	int res;

	tx_data[0] = addr & 0xff;
	tx_data[1] = (addr >> 8) & 0xff;
	tx_data[2] = command | devid;
	tx_data[3] = length & 0xff;

	res = fc8300_spi_write_then_read(fc8300_spi
		, &tx_data[0], 4, data, length);

	if (res) {
		print_log(0, "fc8300_spi_bulkread fail : %d\n", res);
		return BBM_NOK;
	}

	return res;
}

static s32 spi_bulkwrite(HANDLE handle, u8 devid,
		u16 addr, u8 command, u8 *data, u16 length)
{
	int i;
	int res;

	tx_data[0] = addr & 0xff;
	tx_data[1] = (addr >> 8) & 0xff;
	tx_data[2] = command | devid;
	tx_data[3] = length & 0xff;

	for (i = 0 ; i < length ; i++)
		tx_data[4+i] = data[i];

	res = fc8300_spi_write_then_read(fc8300_spi
		, &tx_data[0], length+4, NULL, 0);

	if (res) {
		print_log(0, "fc8300_spi_bulkwrite fail : %d\n", res);
		return BBM_NOK;
	}

	return res;
}

static s32 spi_dataread(HANDLE handle, u8 devid,
		u16 addr, u8 command, u8 *data, u32 length)
{
	int res;

	tx_data[0] = addr & 0xff;
	tx_data[1] = (addr >> 8) & 0xff;
	tx_data[2] = command | devid;
	tx_data[3] = length & 0xff;

	res = fc8300_spi_write_then_read(fc8300_spi
		, &tx_data[0], 4, data, length);

	if (res) {
		print_log(0, "fc8300_spi_dataread fail : %d\n", res);
		return BBM_NOK;
	}

	return res;
}

s32 fc8300_spi_init(HANDLE handle, u16 param1, u16 param2)
{
	int res = 0;

	print_log(0, "fc8300_spi_init : %d\n", res);

	res = spi_register_driver(&fc8300_spi_driver);

	if (res) {
		print_log(0, "fc8300_spi register fail : %d\n", res);
		return BBM_NOK;
	}

	return res;
}

s32 fc8300_spi_byteread(HANDLE handle, DEVICEID devid, u16 addr, u8 *data)
{
	s32 res;
	u8 command = SPI_READ;

	mutex_lock(&fci_spi_lock);
	res = spi_bulkread(handle, (u8) (devid & 0x000f), addr, command,
				data, 1);
	mutex_unlock(&fci_spi_lock);

	return res;
}

s32 fc8300_spi_wordread(HANDLE handle, DEVICEID devid, u16 addr, u16 *data)
{
	s32 res;
	u8 command = SPI_READ | SPI_AINC;

	mutex_lock(&fci_spi_lock);
	res = spi_bulkread(handle, (u8) (devid & 0x000f), addr, command,
				(u8 *)data, 2);
	mutex_unlock(&fci_spi_lock);

	return res;
}

s32 fc8300_spi_longread(HANDLE handle, DEVICEID devid, u16 addr, u32 *data)
{
	s32 res;
	u8 command = SPI_READ | SPI_AINC;

	mutex_lock(&fci_spi_lock);
	res = spi_bulkread(handle, (u8) (devid & 0x000f), addr, command,
				(u8 *)data, 4);
	mutex_unlock(&fci_spi_lock);

	return res;
}

s32 fc8300_spi_bulkread(HANDLE handle, DEVICEID devid,
		u16 addr, u8 *data, u16 length)
{
	s32 res;
	u8 command = SPI_READ | SPI_AINC;

	mutex_lock(&fci_spi_lock);
	res = spi_bulkread(handle, (u8) (devid & 0x000f), addr, command,
				data, length);
	mutex_unlock(&fci_spi_lock);

	return res;
}

s32 fc8300_spi_bytewrite(HANDLE handle, DEVICEID devid, u16 addr, u8 data)
{
	s32 res;
	u8 command = SPI_WRITE;

	mutex_lock(&fci_spi_lock);
	res = spi_bulkwrite(handle, (u8) (devid & 0x000f), addr, command,
				(u8 *)&data, 1);
	mutex_unlock(&fci_spi_lock);

	return res;
}

s32 fc8300_spi_wordwrite(HANDLE handle, DEVICEID devid, u16 addr, u16 data)
{
	s32 res;
#ifdef BBM_ES
	u8 command = SPI_WRITE;

	if ((addr & 0xff00) != 0x0f00)
		command |= SPI_AINC;
#else
	u8 command = SPI_WRITE | SPI_AINC;
#endif

	mutex_lock(&fci_spi_lock);
	res = spi_bulkwrite(handle, (u8) (devid & 0x000f), addr, command,
				(u8 *)&data, 2);
	mutex_unlock(&fci_spi_lock);

	return res;
}

s32 fc8300_spi_longwrite(HANDLE handle, DEVICEID devid, u16 addr, u32 data)
{
	s32 res;
	u8 command = SPI_WRITE | SPI_AINC;

	mutex_lock(&fci_spi_lock);
	res = spi_bulkwrite(handle, (u8) (devid & 0x000f), addr, command,
				(u8 *) &data, 4);
	mutex_unlock(&fci_spi_lock);

	return res;
}

s32 fc8300_spi_bulkwrite(HANDLE handle, DEVICEID devid,
		u16 addr, u8 *data, u16 length)
{
	s32 res;
	u8 command = SPI_WRITE | SPI_AINC;

	mutex_lock(&fci_spi_lock);
	res = spi_bulkwrite(handle, (u8) (devid & 0x000f), addr, command,
				data, length);
	mutex_unlock(&fci_spi_lock);

	return res;
}

s32 fc8300_spi_dataread(HANDLE handle, DEVICEID devid,
		u16 addr, u8 *data, u32 length)
{
	s32 res = 0;
#ifdef SPI_DATAREAD_REGMODE
	u8 command = SPI_READ | SPI_REG;
	u32 read_len = 0;
	u32 i, m, r;

	mutex_lock(&fci_spi_lock);

	if (length > SPI_DMA_MAX_SIZE) {
		m = length / SPI_DMA_MAX_SIZE;
		r = length % SPI_DMA_MAX_SIZE;
		for (i = 0; i < m ; i++) {
			res |= spi_dataread(handle, (u8) (devid & 0x000f), addr
				, command, &data[read_len], SPI_DMA_MAX_SIZE);
			read_len += SPI_DMA_MAX_SIZE;
		}
	} else {
		res = spi_dataread(handle, (u8) (devid & 0x000f), addr, command,
				data, length);
	}

	mutex_unlock(&fci_spi_lock);

#else
	u8 command = SPI_READ | SPI_THR;
	mutex_lock(&fci_spi_lock);
	res = spi_dataread(handle, (u8) (devid & 0x000f), addr, command,
				data, length);
	mutex_unlock(&fci_spi_lock);

	return res;
#endif

}

s32 fc8300_spi_deinit(HANDLE handle)
{

	return BBM_OK;
}

