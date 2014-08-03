#ifndef _MMS100_ISP_H
#define _MMS100_ISP_H

#include <linux/platform_data/mms_ts.h>

int mms_flash_fw(struct i2c_client *client, struct mms_ts_platform_data *pdata);

#endif

