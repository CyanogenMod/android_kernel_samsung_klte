#ifndef __IST30XX_TRACKING_H__
#define __IST30XX_TRACKING_H__


#define IST30XX_RINGBUF_NO_ERR      (0)
#define IST30XX_RINGBUF_NOT_ENOUGH  (1)
#define IST30XX_RINGBUF_EMPTY       (2)
#define IST30XX_RINGBUF_FULL        (3)
#define IST30XX_RINGBUF_TIMEOUT     (4)
#define IST30XX_MAX_LOG_SIZE        (4 * 100 * 1024)    // 4bytes * 100Kbytes, Single touch: about 12minutes

#define TRACK_PWR_OFF           (0x0)
#define TRACK_PWR_ON            (0x1)
#define TRACK_PWR_RESET         (0x3)
#define TRACK_INTR_ENABLE       (0x4)
#define TRACK_INTR_DISABLE      (0x5)
#define TRACK_CMD_RUN_DEVICE    (0x10)
#define TRACK_CMD_SCAN          (0x11)
#define TRACK_CMD_TACON         (0x12)
#define TRACK_CMD_TADISCON      (0x13)
#define TRACK_CMD_FWUPDATE      (0x14)
#define TRACK_CMD_PRUPDATE      (0x15)
#define TRACK_CMD_CALIB         (0x16)
#define TRACK_CMD_CHECK_CALIB   (0x17)
#define TRACK_CMD_CHKSUM        (0x18)
#define TRACK_CMD_CHKSUM_ALL    (0x19)
#define TRACK_CMD_ENTER_REG     (0x1A)
#define TRACK_CMD_EXIT_REG      (0x1B)
#define TRACK_POS_FINGER        (0x20)
#define TRACK_POS_KEY           (0x30)
#define TRACK_POS_UNKNOWN       (0x3F)

#define IST30XX_TRACKING_MAGIC  (0x7750 << 16)


typedef struct _IST30XX_RINGBUF {
	u32	RingBufCtr; // Number of characters in the ring buffer
	u32	RingBufInIdx;
	u32	RingBufOutIdx;
	u8	LogBuf[IST30XX_MAX_LOG_SIZE];        // Ring buffer for status
} IST30XX_RING_BUF;


void ist30xx_tracking_init(void);
void ist30xx_tracking_deinit(void);

int ist30xx_get_track(u32 *track, int cnt);
int ist30xx_put_track(u32 *track, int cnt);
int ist30xx_put_track_ms(u32 ms);

u32 ist30xx_get_track_cnt(void);

int ist30xx_tracking(u32 status);

int ist30xx_init_tracking_sysfs(void);

#endif  // __IST30XX_TRACKING_H__
