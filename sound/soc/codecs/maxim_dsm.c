#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/tlv.h>
#include <sound/maxim_dsm.h>
#include <sound/q6afe.h>

static int param[PARAM_DSM_MAX];

static DEFINE_MUTEX(dsm_lock);

#ifdef USE_DSM_LOG
static DEFINE_MUTEX(maxdsm_log_lock);

static uint32_t exSeqCountTemp;
static uint32_t exSeqCountExcur;
static uint32_t newLogAvail;

int maxdsm_get_dump_status(void)
{
	int ret = (newLogAvail&0x3);
	newLogAvail &= 0x1;
	return ret;
}

void maxdsm_update_param(void)
{
	uint32_t filter_set = DSM_ID_FILTER_GET_AFE_PARAMS;

	mutex_lock(&dsm_lock);
	dsm_open(DSM_RX_PORT_ID, &filter_set, (u8 *) param);
	if (param[PARAM_EXCUR_LIMIT] != 0 && param[PARAM_THERMAL_LIMIT] != 0)
		newLogAvail |= 0x1;
	mutex_unlock(&dsm_lock);
}

static bool maxdsm_log_present;
static struct tm maxdsm_log_timestamp;
static uint8_t maxdsm_byteLogArray[BEFORE_BUFSIZE];
static uint32_t maxdsm_intLogArray[BEFORE_BUFSIZE];
static uint8_t maxdsm_afterProbByteLogArray[AFTER_BUFSIZE];
static uint32_t maxdsm_afterProbIntLogArray[AFTER_BUFSIZE];

void maxdsm_log_update(const void *byteLogArray, const void *intLogArray, \
	const void *afterProbByteLogArray, const void *afterProbIntLogArray)
{
	struct timeval tv;
	mutex_lock(&maxdsm_log_lock);

	memcpy(maxdsm_byteLogArray, byteLogArray, sizeof(maxdsm_byteLogArray));
	memcpy(maxdsm_intLogArray, intLogArray, sizeof(maxdsm_intLogArray));

	memcpy(maxdsm_afterProbByteLogArray, afterProbByteLogArray, \
		sizeof(maxdsm_afterProbByteLogArray));
	memcpy(maxdsm_afterProbIntLogArray, afterProbIntLogArray, \
		sizeof(maxdsm_afterProbIntLogArray));

	do_gettimeofday(&tv);
	time_to_tm(tv.tv_sec, 0, &maxdsm_log_timestamp);

	maxdsm_log_present = true;

	mutex_unlock(&maxdsm_log_lock);
}

static void maxdsm_log_free(void **byteLogArray, void **intLogArray, \
	void **afterbyteLogArray, void **afterintLogArray)
{
	if (likely(*byteLogArray)) {
		kfree(*byteLogArray);
		*byteLogArray = NULL;
	}

	if (likely(*intLogArray)) {
		kfree(*intLogArray);
		*intLogArray = NULL;
	}

	if (likely(*afterbyteLogArray)) {
		kfree(*afterbyteLogArray);
		*afterbyteLogArray = NULL;
	}

	if (likely(*afterintLogArray)) {
		kfree(*afterintLogArray);
		*afterintLogArray = NULL;
	}
}

static int maxdsm_log_duplicate(void **byteLogArray, void **intLogArray, \
	void **afterbyteLogArray, void **afterintLogArray)
{
	void *blog_buf = NULL, *ilog_buf = NULL;
	void *after_blog_buf = NULL, *after_ilog_buf = NULL;
	int rc = 0;

	mutex_lock(&maxdsm_log_lock);

	if (unlikely(!maxdsm_log_present)) {
		rc = -ENODATA;
		goto abort;
	}

	blog_buf = kzalloc(sizeof(maxdsm_byteLogArray), GFP_KERNEL);
	ilog_buf = kzalloc(sizeof(maxdsm_intLogArray), GFP_KERNEL);
	after_blog_buf
		= kzalloc(sizeof(maxdsm_afterProbByteLogArray), GFP_KERNEL);
	after_ilog_buf
		= kzalloc(sizeof(maxdsm_afterProbIntLogArray), GFP_KERNEL);

	if (unlikely(!blog_buf || !ilog_buf \
		|| !after_blog_buf || !after_ilog_buf)) {
		rc = -ENOMEM;
		goto abort;
	}

	memcpy(blog_buf, maxdsm_byteLogArray, sizeof(maxdsm_byteLogArray));
	memcpy(ilog_buf, maxdsm_intLogArray, sizeof(maxdsm_intLogArray));
	memcpy(after_blog_buf, maxdsm_afterProbByteLogArray,
		sizeof(maxdsm_afterProbByteLogArray));
	memcpy(after_ilog_buf, maxdsm_afterProbIntLogArray,
		sizeof(maxdsm_afterProbIntLogArray));

	goto out;

abort:
	maxdsm_log_free(&blog_buf, &ilog_buf, &after_blog_buf, &after_ilog_buf);
out:
	*byteLogArray = blog_buf;
	*intLogArray  = ilog_buf;
	*afterbyteLogArray = after_blog_buf;
	*afterintLogArray  = after_ilog_buf;
	mutex_unlock(&maxdsm_log_lock);

	return rc;
}

ssize_t maxdsm_log_prepare(char *buf)
{
	uint8_t *byteLogArray = NULL;
	uint32_t *intLogArray = NULL;
	uint8_t *afterbyteLogArray = NULL;
	uint32_t *afterintLogArray = NULL;
	int rc = 0;

	uint8_t logAvailable;
	uint8_t versionID;
	uint8_t *coilTempLogArray;
	uint8_t *exCurLogArray;
	uint8_t *AftercoilTempLogArray;
	uint8_t *AfterexCurLogArray;
	uint8_t *ExcurAftercoilTempLogArray;
	uint8_t *ExcurAfterexCurLogArray;

	uint32_t seqCountTemp;
	uint32_t seqCountExcur;
	uint32_t *rdcLogArray;
	uint32_t *freqLogArray;
	uint32_t *AfterrdcLogArray;
	uint32_t *AfterfreqLogArray;
	uint32_t *ExcurAfterrdcLogArray;
	uint32_t *ExcurAfterfreqLogArray;

	rc = maxdsm_log_duplicate((void **)&byteLogArray, \
		(void **)&intLogArray, (void **)&afterbyteLogArray, \
		(void **)&afterintLogArray);

	if (unlikely(rc)) {
		rc = snprintf(buf, PAGE_SIZE, "no log\n");
		if (param[PARAM_EXCUR_LIMIT] != 0 &&\
			param[PARAM_THERMAL_LIMIT] != 0)	{
			rc += snprintf(buf+rc, PAGE_SIZE,  \
				"[Parameter Set] excursionlimit:0x%x, "\
				"rdcroomtemp:0x%x, coilthermallimit:0x%x, "
				"releasetime:0x%x\n"\
				, param[PARAM_EXCUR_LIMIT],
				param[PARAM_VOICE_COIL],
				param[PARAM_THERMAL_LIMIT],
				param[PARAM_RELEASE_TIME]);
			rc += snprintf(buf+rc, PAGE_SIZE,  "[Parameter Set] "\
				"staticgain:0x%x, lfxgain:0x%x, "\
				"pilotgain:0x%x\n",
				param[PARAM_STATIC_GAIN],
				param[PARAM_LFX_GAIN],
				param[PARAM_PILOT_GAIN]);
		}
		goto out;
	}

	logAvailable     = byteLogArray[0];
	versionID        = byteLogArray[1];
	coilTempLogArray = &byteLogArray[2];
	exCurLogArray    = &byteLogArray[2+LOG_BUFFER_ARRAY_SIZE];

	seqCountTemp       = intLogArray[0];
	seqCountExcur   = intLogArray[1];
	rdcLogArray  = &intLogArray[2];
	freqLogArray = &intLogArray[2+LOG_BUFFER_ARRAY_SIZE];

	AftercoilTempLogArray = &afterbyteLogArray[0];
	AfterexCurLogArray = &afterbyteLogArray[LOG_BUFFER_ARRAY_SIZE];
	AfterrdcLogArray = &afterintLogArray[0];
	AfterfreqLogArray = &afterintLogArray[LOG_BUFFER_ARRAY_SIZE];

	ExcurAftercoilTempLogArray
		= &afterbyteLogArray[LOG_BUFFER_ARRAY_SIZE*2];
	ExcurAfterexCurLogArray = &afterbyteLogArray[LOG_BUFFER_ARRAY_SIZE*3];
	ExcurAfterrdcLogArray = &afterintLogArray[LOG_BUFFER_ARRAY_SIZE*2];
	ExcurAfterfreqLogArray = &afterintLogArray[LOG_BUFFER_ARRAY_SIZE*3];

	if (logAvailable > 0 && \
		(exSeqCountTemp != seqCountTemp \
		|| exSeqCountExcur != seqCountExcur))	{
		exSeqCountTemp = seqCountTemp;
		exSeqCountExcur = seqCountExcur;
		newLogAvail |= 0x2;
	}

	rc += snprintf(buf+rc, PAGE_SIZE, "DSM LogData saved at "\
		"%4d-%02d-%02d %02d:%02d:%02d (UTC)\n",
		(int)(maxdsm_log_timestamp.tm_year + 1900),
		(int)(maxdsm_log_timestamp.tm_mon + 1),
		(int)(maxdsm_log_timestamp.tm_mday),
		(int)(maxdsm_log_timestamp.tm_hour),
		(int)(maxdsm_log_timestamp.tm_min),
		(int)(maxdsm_log_timestamp.tm_sec));

	if ((logAvailable & 0x1) == 0x1) {
		rc += snprintf(buf+rc, PAGE_SIZE, \
			"*** Excursion Limit was exceeded.\n");
		rc += snprintf(buf+rc, PAGE_SIZE, \
			"Seq:%d, logAvailable=%d, versionID:3.1.%d\n", \
			seqCountExcur, logAvailable, versionID);
		rc += snprintf(buf+rc, PAGE_SIZE, "Temperature="\
			"{ %d, %d, %d, %d, %d, %d, %d, %d, %d, %d }\n",
			ExcurAftercoilTempLogArray[0],
			ExcurAftercoilTempLogArray[1],
			ExcurAftercoilTempLogArray[2],
			ExcurAftercoilTempLogArray[3],
			ExcurAftercoilTempLogArray[4],
			ExcurAftercoilTempLogArray[5],
			ExcurAftercoilTempLogArray[6],
			ExcurAftercoilTempLogArray[7],
			ExcurAftercoilTempLogArray[8],
			ExcurAftercoilTempLogArray[9]);
		rc += snprintf(buf+rc, PAGE_SIZE,  \
			"Excursion="\
			"{ %d, %d, %d, %d, %d, %d, %d, %d, %d, %d }\n",
			ExcurAfterexCurLogArray[0],
			ExcurAfterexCurLogArray[1],
			ExcurAfterexCurLogArray[2],
			ExcurAfterexCurLogArray[3],
			ExcurAfterexCurLogArray[4],
			ExcurAfterexCurLogArray[5],
			ExcurAfterexCurLogArray[6],
			ExcurAfterexCurLogArray[7],
			ExcurAfterexCurLogArray[8],
			ExcurAfterexCurLogArray[9]);
		rc += snprintf(buf+rc, PAGE_SIZE,  "Rdc="\
			"{ %d, %d, %d, %d, %d, %d, %d, %d, %d, %d }\n",
			ExcurAfterrdcLogArray[0],
			ExcurAfterrdcLogArray[1],
			ExcurAfterrdcLogArray[2],
			ExcurAfterrdcLogArray[3],
			ExcurAfterrdcLogArray[4],
			ExcurAfterrdcLogArray[5],
			ExcurAfterrdcLogArray[6],
			ExcurAfterrdcLogArray[7],
			ExcurAfterrdcLogArray[8],
			ExcurAfterrdcLogArray[9]);
		rc += snprintf(buf+rc, PAGE_SIZE,  "Frequency="\
			"{ %d, %d, %d, %d, %d, %d, %d, %d, %d, %d }\n",
			ExcurAfterfreqLogArray[0],
			ExcurAfterfreqLogArray[1],
			ExcurAfterfreqLogArray[2],
			ExcurAfterfreqLogArray[3],
			ExcurAfterfreqLogArray[4],
			ExcurAfterfreqLogArray[5],
			ExcurAfterfreqLogArray[6],
			ExcurAfterfreqLogArray[7],
			ExcurAfterfreqLogArray[8],
			ExcurAfterfreqLogArray[9]);
	}

	if ((logAvailable & 0x2) == 0x2) {
		rc += snprintf(buf+rc, PAGE_SIZE, \
			"*** Temperature Limit was exceeded.\n");
		rc += snprintf(buf+rc, PAGE_SIZE, \
			"Seq:%d, logAvailable=%d, versionID:3.1.%d\n", \
			seqCountTemp, logAvailable, versionID);
		rc += snprintf(buf+rc, PAGE_SIZE, "Temperature="\
			"{ %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",
			coilTempLogArray[0],
			coilTempLogArray[1],
			coilTempLogArray[2],
			coilTempLogArray[3],
			coilTempLogArray[4],
			coilTempLogArray[5],
			coilTempLogArray[6],
			coilTempLogArray[7],
			coilTempLogArray[8],
			coilTempLogArray[9]);
		rc += snprintf(buf+rc, PAGE_SIZE, "              "\
			"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d }\n",
			AftercoilTempLogArray[0],
			AftercoilTempLogArray[1],
			AftercoilTempLogArray[2],
			AftercoilTempLogArray[3],
			AftercoilTempLogArray[4],
			AftercoilTempLogArray[5],
			AftercoilTempLogArray[6],
			AftercoilTempLogArray[7],
			AftercoilTempLogArray[8],
			AftercoilTempLogArray[9]);
		rc += snprintf(buf+rc, PAGE_SIZE, \
			"Excursion={ %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",
			exCurLogArray[0],
			exCurLogArray[1],
			exCurLogArray[2],
			exCurLogArray[3],
			exCurLogArray[4],
			exCurLogArray[5],
			exCurLogArray[6],
			exCurLogArray[7],
			exCurLogArray[8],
			exCurLogArray[9]);
		rc += snprintf(buf+rc, PAGE_SIZE, "            "\
			"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d }\n",
			AfterexCurLogArray[0],
			AfterexCurLogArray[1],
			AfterexCurLogArray[2],
			AfterexCurLogArray[3],
			AfterexCurLogArray[4],
			AfterexCurLogArray[5],
			AfterexCurLogArray[6],
			AfterexCurLogArray[7],
			AfterexCurLogArray[8],
			AfterexCurLogArray[9]);
		rc += snprintf(buf+rc, PAGE_SIZE,\
			"Rdc={ %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",
			rdcLogArray[0],
			rdcLogArray[1],
			rdcLogArray[2],
			rdcLogArray[3],
			rdcLogArray[4],
			rdcLogArray[5],
			rdcLogArray[6],
			rdcLogArray[7],
			rdcLogArray[8],
			rdcLogArray[9]);
		rc += snprintf(buf+rc, PAGE_SIZE,
			"      %d, %d, %d, %d, %d, %d, %d, %d, %d, %d }\n",
			AfterrdcLogArray[0],
			AfterrdcLogArray[1],
			AfterrdcLogArray[2],
			AfterrdcLogArray[3],
			AfterrdcLogArray[4],
			AfterrdcLogArray[5],
			AfterrdcLogArray[6],
			AfterrdcLogArray[7],
			AfterrdcLogArray[8],
			AfterrdcLogArray[9]);
		rc += snprintf(buf+rc, PAGE_SIZE, \
			"Frequency={ %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",
			freqLogArray[0],
			freqLogArray[1],
			freqLogArray[2],
			freqLogArray[3],
			freqLogArray[4],
			freqLogArray[5],
			freqLogArray[6],
			freqLogArray[7],
			freqLogArray[8],
			freqLogArray[9]);
		rc += snprintf(buf+rc, PAGE_SIZE, "            "\
			"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d }\n",
			AfterfreqLogArray[0],
			AfterfreqLogArray[1],
			AfterfreqLogArray[2],
			AfterfreqLogArray[3],
			AfterfreqLogArray[4],
			AfterfreqLogArray[5],
			AfterfreqLogArray[6],
			AfterfreqLogArray[7],
			AfterfreqLogArray[8],
			AfterfreqLogArray[9]);
	}

	if (param[PARAM_EXCUR_LIMIT] != 0 &&\
		param[PARAM_THERMAL_LIMIT] != 0)	{
		rc += snprintf(buf+rc, PAGE_SIZE, \
			"[Parameter Set] excursionlimit:0x%x, "\
			"rdcroomtemp:0x%x, coilthermallimit:0x%x, "\
			"releasetime:0x%x\n",
			param[PARAM_EXCUR_LIMIT],
			param[PARAM_VOICE_COIL],
			param[PARAM_THERMAL_LIMIT],
			param[PARAM_RELEASE_TIME]);
		rc += snprintf(buf+rc, PAGE_SIZE,  "[Parameter Set] "\
			"staticgain:0x%x, lfxgain:0x%x, pilotgain:0x%x\n",
			param[PARAM_STATIC_GAIN],
			param[PARAM_LFX_GAIN],
			param[PARAM_PILOT_GAIN]);
	}

out:
	maxdsm_log_free((void **)&byteLogArray, (void **)&intLogArray, \
		(void **)&afterbyteLogArray, (void **)&afterintLogArray);

	return (ssize_t)rc;
}
#endif

int get_dsm_onoff_status(void){
	return param[PARAM_ONOFF];
}

static int maxdsm_open(struct inode *inode, struct file *filep)
{
	return 0;
}

static ssize_t maxdsm_read(struct file *filep, char __user *buf,
			size_t count, loff_t *ppos)
{
	int rc;
	uint32_t filter_set;

	mutex_lock(&dsm_lock);

	filter_set = DSM_ID_FILTER_GET_AFE_PARAMS;

	dsm_open(DSM_RX_PORT_ID, &filter_set, (u8 *) param);

	rc = copy_to_user(buf, param, count);
	if (rc != 0) {
		pr_err("%s: copy_to_user failed - %d\n", __func__, rc);
		mutex_unlock(&dsm_lock);
		return 0;
	}

	mutex_unlock(&dsm_lock);

	return rc;
}

static ssize_t maxdsm_write(struct file *filep, const char __user *buf,
			size_t count, loff_t *ppos)
{
	int x, rc;
	uint32_t filter_set;

	mutex_lock(&dsm_lock);

	rc = copy_from_user(param, buf, count);
	if (rc != 0) {
		pr_err("%s: copy_from_user failed - %d\n", __func__, rc);
		mutex_unlock(&dsm_lock);
		return rc;
	}

	if (param[PARAM_WRITE_FLAG] == 0)	{
		/* validation check */
		for (x = PARAM_THERMAL_LIMIT;
			x < PARAM_DSM_MAX; x += 2)	{
			if ((x != PARAM_ONOFF) && (param[x] != 0)) {
				param[PARAM_WRITE_FLAG] = FLAG_WRITE_ALL;
				break;
			}
		}
	}

	if (param[PARAM_WRITE_FLAG] == FLAG_WRITE_ONOFF_ONLY \
		|| param[PARAM_WRITE_FLAG] == FLAG_WRITE_ALL) {
		/* set params from the algorithm to application */
		filter_set = DSM_ID_FILTER_SET_AFE_CNTRLS;
		dsm_open(DSM_RX_PORT_ID, &filter_set, (u8 *) param);
	}
	mutex_unlock(&dsm_lock);

	return rc;
}

static const struct file_operations dsm_ctrl_fops = {
	.owner		= THIS_MODULE,
	.open		= maxdsm_open,
	.release	= NULL,
	.read		= maxdsm_read,
	.write		= maxdsm_write,
	.mmap		= NULL,
	.poll		= NULL,
	.fasync		= NULL,
	.llseek		= NULL,
};

static struct miscdevice dsm_ctrl_miscdev = {
	.minor =    MISC_DYNAMIC_MINOR,
	.name =     "dsm_ctrl_dev",
	.fops =     &dsm_ctrl_fops
};

int maxdsm_init(void)
{
	memset(param, 0, sizeof(param));
	return misc_register(&dsm_ctrl_miscdev);
}

int maxdsm_deinit(void)
{
	return misc_deregister(&dsm_ctrl_miscdev);
}