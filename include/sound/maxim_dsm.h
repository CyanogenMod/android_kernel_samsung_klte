/*
 * Platform data for MAX98504
 *
 * Copyright 2011-2012 Maxim Integrated Products
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 */

#ifndef __SOUND_MAXIM_DSM_H__
#define __SOUND_MAXIM_DSM_H__

#define DSM_RX_PORT_ID	0x4000

#define AFE_PARAM_ID_ENABLE_DSM_RX    0x0F010203
#define AFE_PARAM_ID_ENABLE_DSM_TX    0x0FF10203

#define DSM_ID_FILTER_GET_AFE_PARAMS 0x00000000
#define DSM_ID_FILTER_SET_AFE_CNTRLS 0x00000001

enum	{
	MODE_DSM_COPP,
	MODE_DSM_AFE,	
	MODE_DSM_MAX,
};

enum	{
	PARAM_VOICE_COIL_TEMP,
	PARAM_VOICE_COIL_TEMP_SZ,
	PARAM_EXCURSION,
	PARAM_EXCURSION_SZ,
	PARAM_RDC,
	PARAM_RDC_SZ,
	PARAM_Q,
	PARAM_Q_SZ,
	PARAM_FRES,
	PARAM_FRES_SZ,
	PARAM_EXCUR_LIMIT,
	PARAM_EXCUR_LIMIT_SZ,
	PARAM_VOICE_COIL,
	PARAM_VOICE_COIL_SZ,
	PARAM_THERMAL_LIMIT,
	PARAM_THERMAL_LIMIT_SZ,
	PARAM_RELEASE_TIME,
	PARAM_RELEASE_TIME_SZ,
	PARAM_ONOFF,
	PARAM_ONOFF_SZ,
	PARAM_STATIC_GAIN,
	PARAM_STATIC_GAIN_SZ,
	PARAM_LFX_GAIN,
	PARAM_LFX_GAIN_SZ,
	PARAM_PILOT_GAIN,
	PARAM_PILOT_GAIN_SZ,
	PARAM_WRITE_FLAG,
	PARAM_WRITE_FLAG_SZ,
	PARAM_FEATURE_SET,
	PARAM_FEATURE_SET_SZ,
	PARAM_SMOOTH_VOLT,
	PARAM_SMOOTH_VOLT_SZ,
	PARAM_HPF_CUTOFF,
	PARAM_HPF_CUTOFF_SZ,
	PARAM_LEAD_R,
	PARAM_LEAD_R_SZ,
	PARAM_RMS_SMOO_FAC,
	PARAM_RMS_SMOO_FAC_SZ,
	PARAM_CLIP_LIMIT,
	PARAM_CLIP_LIMIT_SZ,
	PARAM_THERMAL_COEF,
	PARAM_THERMAL_COEF_SZ,
	PARAM_QSPK,
	PARAM_QSPK_SZ,
	PARAM_EXCUR_LOG_THRESH,
	PARAM_EXCUR_LOG_THRESH_SZ,
	PARAM_TEMP_LOG_THRESH,
	PARAM_TEMP_LOG_THRESH_SZ,
	PARAM_RES_FREQ,
	PARAM_RES_FREQ_SZ,
	PARAM_RES_FREQ_GUARD_BAND,
	PARAM_RES_FREQ_GUARD_BAND_SZ,
	PARAM_DSM_MAX,
};

#define FLAG_WRITE_ALL 0xabefcdab
#define FLAG_WRITE_ONOFF_ONLY	0xcdababef

int maxdsm_init(void);
int maxdsm_deinit(void);

#define DEBUG_DSM

#define USE_DSM_LOG

#ifdef USE_DSM_LOG
#define LOG_BUFFER_ARRAY_SIZE 10

/* BUFSIZE must be 4 bytes allignment*/
#define BEFORE_BUFSIZE (4+(LOG_BUFFER_ARRAY_SIZE*2))
#define AFTER_BUFSIZE (LOG_BUFFER_ARRAY_SIZE*4)

extern int maxdsm_get_dump_status(void);
extern ssize_t maxdsm_log_prepare(char *buf);
extern void maxdsm_update_param(void);
extern void maxdsm_log_update(const void *byteLogArray,
	       const void *intLogArray, const void *afterProbByteLogArray, 
	       const void *afterProbIntLogArray);
#endif

#endif
