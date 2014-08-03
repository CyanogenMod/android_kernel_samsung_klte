#ifndef _LINUX_FTS_I2C_H_
#define _LINUX_FTS_I2C_H_

#define FTS_SUPPORT_NOISE_PARAM
#if	defined(CONFIG_SEC_LOCALE_KOR_FRESCO)
#define FTS_SUPPORT_TA_MODE
#endif

#ifdef FTS_SUPPORT_NOISE_PARAM
#define MAX_NOISE_PARAM 5
struct fts_noise_param {
	unsigned short pAddr[MAX_NOISE_PARAM];
	unsigned short pData[MAX_NOISE_PARAM];
};
#endif

#ifdef FTS_SUPPORT_TA_MODE
struct fts_callbacks {
	void (*inform_charger) (struct fts_callbacks *, int);
};
#endif

struct fts_i2c_platform_data {
	bool factory_flatform;
	bool recovery_mode;
	bool support_hover;
	bool support_mshover;
	int max_x;
	int max_y;
	int max_width;
	unsigned char panel_revision;	/* to identify panel info */
	const char *firmware_name;
	const char *project_name;

	int (*power) (bool enable);
	void	(*register_cb)(void *);
#ifdef FTS_SUPPORT_TA_MODE
	struct fts_callbacks callbacks;
	bool charging_mode;
#endif
	void (*enable_sync)(bool on);

	unsigned gpio;
	int irq_type;
};

#define SEC_TSP_FACTORY_TEST

#ifdef SEC_TSP_FACTORY_TEST
extern struct class *sec_class;
#endif

#endif
