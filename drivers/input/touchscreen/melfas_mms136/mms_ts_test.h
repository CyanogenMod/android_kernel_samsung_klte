#define __MMS_TEST_MODE__
#ifdef __MMS_TEST_MODE__

#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/platform_data/mms_ts.h>

#define MMS_EVENT_PKT_SZ		0x0F
#define MMS_INPUT_EVENT			0x10
#define MMS_UNIVERSAL_CMD		0xA0
#define MMS_UNIVERSAL_RESULT		0xAF
#define MMS_UNIVERSAL_RESULT_LENGTH	0xAE
#define MMS_UNIV_ENTER_TEST		0x40
#define MMS_UNIV_TEST_CM		0x41
#define MMS_UNIV_GET_CM			0x42
#define MMS_UNIV_EXIT_TEST		0x4F
#define MMS_UNIV_INTENSITY		0x70

struct mms_ts_test {
	struct i2c_client 		*client;

	u8				tx_num;
	u8				rx_num;
	u8				key_num;

	int 				irq;

	char				*get_data;

	struct mms_ts_platform_data 	*pdata;

};


int get_cm_test_init(struct mms_ts_test *test);
int get_cm_test_exit(struct mms_ts_test *test);
int get_cm_test_delta(struct mms_ts_test *test);
int get_cm_test_abs(struct mms_ts_test *test);
int get_cm_test_jitter(struct mms_ts_test *test);
int get_test_intensity(struct mms_ts_test *test);
#endif
