/*
 * max98504.c -- MAX98504 ALSA SoC Audio driver
 *
 * Copyright 2011-2012 Maxim Integrated Products
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/tlv.h>
#include <sound/max98504.h>
#include "max98504.h"
#include <linux/version.h>

#define SUPPORT_DEVICE_TREE
//#define USE_MISC_FOR_DEMO
#define DEBUG_MAX98504

#ifdef SUPPORT_DEVICE_TREE
#include <linux/regulator/consumer.h>
#endif

#ifdef DEBUG_MAX98504
#define msg_maxim(format, args...)	\
	printk(KERN_INFO "[MAX98504_DEBUG] %s " format, __func__, ## args)
#else
#define msg_maxim(format, args...)
#endif

static struct regulator *max98504_vcc_i2c;

static DEFINE_MUTEX(rx_lock);
static DEFINE_MUTEX(tx_lock);

static const u8 max98504_reg_def[MAX98504_REG_CNT] = {
	[MAX98504_REG_01_INTERRUPT_STATUS] = 0,
	[MAX98504_REG_02_INTERRUPT_FLAGS] = 0,
	[MAX98504_REG_03_INTERRUPT_ENABLES] = 0,
	[MAX98504_REG_04_INTERRUPT_FLAG_CLEARS] = 0,
	[MAX98504_REG_10_GPIO_ENABLE] = 0,
	[MAX98504_REG_11_GPIO_CONFIG] = 0,
	[MAX98504_REG_12_WATCHDOG_ENABLE] = 0,
	[MAX98504_REG_13_WATCHDOG_CONFIG] = 0,
	[MAX98504_REG_14_WATCHDOG_CLEAR] = 0,
	[MAX98504_REG_15_CLOCK_MONITOR_ENABLE] = 0,
	[MAX98504_REG_16_PVDD_BROWNOUT_ENABLE] = 0,
	[MAX98504_REG_17_PVDD_BROWNOUT_CONFIG_1] = 0,
	[MAX98504_REG_18_PVDD_BROWNOUT_CONFIG_2] = 0,
	[MAX98504_REG_19_PVDD_BROWNOUT_CONFIG_3] = 0,
	[MAX98504_REG_1A_PVDD_BROWNOUT_CONFIG_4] = 0,
	[MAX98504_REG_20_PCM_RX_ENABLES] = 0,
	[MAX98504_REG_21_PCM_TX_ENABLES] = 0,
	[MAX98504_REG_22_PCM_TX_HIZ_CONTROL] = 0,
	[MAX98504_REG_23_PCM_TX_CHANNEL_SOURCES] = 0,
	[MAX98504_REG_24_PCM_MODE_CONFIG] = 0,
	[MAX98504_REG_25_PCM_DSP_CONFIG] = 0,
	[MAX98504_REG_26_PCM_CLOCK_SETUP] = 0,
	[MAX98504_REG_27_PCM_SAMPLE_RATE_SETUP] = 0,
	[MAX98504_REG_28_PCM_TO_SPEAKER_MONOMIX] = 0,
	[MAX98504_REG_30_PDM_TX_ENABLES] = 0,
	[MAX98504_REG_31_PDM_TX_HIZ_CONTROL] = 0,
	[MAX98504_REG_32_PDM_TX_CONTROL] = 0,
	[MAX98504_REG_33_PDM_RX_ENABLE] = 0,
	[MAX98504_REG_34_SPEAKER_ENABLE] = 0,
	[MAX98504_REG_35_SPEAKER_SOURCE_SELECT] = 0,
	[MAX98504_REG_36_MEASUREMENT_ENABLES] = 0,
	[MAX98504_REG_37_ANALOGUE_INPUT_GAIN] = 0,
	[MAX98504_REG_38_TEMPERATURE_LIMIT_CONFIG] = 0,
	[MAX98504_REG_39_ANALOGUE_SPARE] = 0,
	[MAX98504_REG_40_GLOBAL_ENABLE] = 0,
	[MAX98504_REG_41_SOFTWARE_RESET] = 0,
};

static struct {
	u8 read;
	u8 write;
	u8 vol;
} max98504_reg_access[MAX98504_REG_CNT] = {
	[MAX98504_REG_01_INTERRUPT_STATUS] = { 0xFF, 0x00, 0xFF },
	[MAX98504_REG_02_INTERRUPT_FLAGS] = { 0xFF, 0x00, 0xFF },
	[MAX98504_REG_03_INTERRUPT_ENABLES] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_04_INTERRUPT_FLAG_CLEARS] = { 0x00, 0xFF, 0xFF },
	[MAX98504_REG_10_GPIO_ENABLE] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_11_GPIO_CONFIG] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_12_WATCHDOG_ENABLE] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_13_WATCHDOG_CONFIG] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_14_WATCHDOG_CLEAR] = { 0x00, 0xFF, 0xFF },
	[MAX98504_REG_15_CLOCK_MONITOR_ENABLE] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_16_PVDD_BROWNOUT_ENABLE] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_17_PVDD_BROWNOUT_CONFIG_1] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_18_PVDD_BROWNOUT_CONFIG_2] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_19_PVDD_BROWNOUT_CONFIG_3] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_1A_PVDD_BROWNOUT_CONFIG_4] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_20_PCM_RX_ENABLES] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_21_PCM_TX_ENABLES] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_22_PCM_TX_HIZ_CONTROL] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_23_PCM_TX_CHANNEL_SOURCES] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_24_PCM_MODE_CONFIG] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_25_PCM_DSP_CONFIG] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_26_PCM_CLOCK_SETUP] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_27_PCM_SAMPLE_RATE_SETUP] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_28_PCM_TO_SPEAKER_MONOMIX] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_30_PDM_TX_ENABLES] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_31_PDM_TX_HIZ_CONTROL] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_32_PDM_TX_CONTROL] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_33_PDM_RX_ENABLE] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_34_SPEAKER_ENABLE] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_35_SPEAKER_SOURCE_SELECT] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_36_MEASUREMENT_ENABLES] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_37_ANALOGUE_INPUT_GAIN] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_38_TEMPERATURE_LIMIT_CONFIG] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_39_ANALOGUE_SPARE] = { 0xFF, 0xFF, 0x00 },
	[MAX98504_REG_40_GLOBAL_ENABLE] = { 0xFF, 0xFF, 0xFF },
	[MAX98504_REG_41_SOFTWARE_RESET] = { 0x00, 0xFF, 0xFF },
};

static int max98504_volatile_register(struct snd_soc_codec *codec, unsigned int reg)
{
	if (max98504_reg_access[reg].vol)
		return 1;
	else
/* Mark all volatile for 2nd Ev Kit i2c master */
	return 0;
}

static int max98504_readable(struct snd_soc_codec *codec, unsigned int reg)
{
	if (reg >= MAX98504_REG_CNT)
		return 0;
	return max98504_reg_access[reg].read != 0;
}

static int max98504_reset(struct snd_soc_codec *codec)
{
	int ret;
	msg_maxim("\n");

	/* Reset the codec by writing to this write-only reset register */
	ret = snd_soc_write(codec, MAX98504_REG_41_SOFTWARE_RESET, M98504_SOFTWARE_RESET_MASK);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to reset codec: %d\n", ret);
		return ret;
	}

	msleep(10);

	return ret;
}

static int max98504_rxpcm_gain_set(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	unsigned int sel = ucontrol->value.integer.value[0];

	msg_maxim("val=%d\n",sel);

	snd_soc_update_bits(codec, MAX98504_REG_25_PCM_DSP_CONFIG,
	    M98504_PCM_DSP_CFG_RX_GAIN_MASK,
		sel << M98504_PCM_DSP_CFG_RX_GAIN_SHIFT);

	return 0;

}

static int max98504_rxpcm_gain_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	unsigned int val = snd_soc_read(codec, MAX98504_REG_25_PCM_DSP_CONFIG);

	val = (val & M98504_PCM_DSP_CFG_RX_GAIN_MASK) >> M98504_PCM_DSP_CFG_RX_GAIN_SHIFT;

	ucontrol->value.integer.value[0] = val;
	msg_maxim("val=%d\n",val);

	return 0;

}

static int max98504_ain_gain_set(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	unsigned int sel = ucontrol->value.integer.value[0];

	msg_maxim("val=%d\n",sel);

	snd_soc_update_bits(codec, MAX98504_REG_37_ANALOGUE_INPUT_GAIN,
	    M98504_ANALOG_INPUT_GAIN_MASK,
		sel << M98504_ANALOG_INPUT_GAIN_SHIFT);

	return 0;

}

static int max98504_ain_gain_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	unsigned int val = snd_soc_read(codec, MAX98504_REG_37_ANALOGUE_INPUT_GAIN);

	val = (val & M98504_ANALOG_INPUT_GAIN_MASK) >> M98504_ANALOG_INPUT_GAIN_SHIFT;

	ucontrol->value.integer.value[0] = val;
	msg_maxim("val=%d\n",val);

	return 0;

}
static const unsigned int max98504_rxpcm_gain_tlv[] = {
	TLV_DB_RANGE_HEAD(1),
	0, 12, TLV_DB_SCALE_ITEM(0, 100, 0),
};

static const unsigned int max98504_ain_gain_tlv[] = {
	TLV_DB_RANGE_HEAD(1),
	0, 1, TLV_DB_SCALE_ITEM(1200, 600, 0),
};

static const char * max98504_enableddisabled_text[] = {"Disabled", "Enabled"};

static const struct soc_enum max98504_ispken_enum =
	SOC_ENUM_SINGLE(MAX98504_REG_36_MEASUREMENT_ENABLES, M98504_MEAS_I_EN_MASK,
		ARRAY_SIZE(max98504_enableddisabled_text), max98504_enableddisabled_text);

static const struct soc_enum max98504_vspken_enum =
	SOC_ENUM_SINGLE(MAX98504_REG_36_MEASUREMENT_ENABLES, M98504_MEAS_V_EN_MASK,
		ARRAY_SIZE(max98504_enableddisabled_text), max98504_enableddisabled_text);

static const char * max98504_vbatbrown_code_text[] = { "2.6V", "2.65V","Reserved", "Reserved","Reserved","Reserved","Reserved","Reserved",\
														"Reserved","Reserved","Reserved","Reserved","Reserved","Reserved","Reserved","Reserved",\
														"Reserved","Reserved","Reserved","Reserved","Reserved","Reserved","Reserved","Reserved",\
														"Reserved","Reserved","Reserved","Reserved","Reserved","Reserved","Reserved","3.7V"};

static const struct soc_enum max98504_brownout_code_enum =
	SOC_ENUM_SINGLE(MAX98504_REG_17_PVDD_BROWNOUT_CONFIG_1, M98504_PVDD_BROWNOUT_CFG1_CODE_SHIFT, 31, max98504_vbatbrown_code_text);

static const char * max98504_vbatbrown_max_atten_text[] = {"0dB","1dB","2dB","3dB","4dB","5dB","6dB"};

static const struct soc_enum max98504_brownout_max_atten_enum =
	SOC_ENUM_SINGLE(MAX98504_REG_17_PVDD_BROWNOUT_CONFIG_1, M98504_PVDD_BROWNOUT_CFG1_MAX_ATTEN_SHIFT, 6, max98504_vbatbrown_max_atten_text);

static const char * max98504_flt_mode_text[] = {"Voice", "Music"};

static const struct soc_enum max98504_pcm_rx_flt_mode_enum =
	SOC_ENUM_SINGLE(MAX98504_REG_25_PCM_DSP_CONFIG, M98504_PCM_DSP_CFG_RX_FLT_MODE_SHIFT, 1, max98504_flt_mode_text);

static const char * max98504_pcm_bsel_text[] = {"Reserved","Reserved","32","48", "64", "Reserved", "128", "Reserved", "256"};

static const struct soc_enum max98504_pcm_bsel_enum =
	SOC_ENUM_SINGLE(MAX98504_REG_26_PCM_CLOCK_SETUP, M98504_PCM_CLK_SETUP_BSEL_SHIFT, 8, max98504_pcm_bsel_text);

static const struct snd_kcontrol_new max98504_snd_controls[] = {
	SOC_SINGLE("GPIO Pin Switch", MAX98504_REG_10_GPIO_ENABLE, M98504_GPIO_ENALBE_SHIFT, 1, 0),
	SOC_SINGLE("Watchdog Enable Switch", MAX98504_REG_12_WATCHDOG_ENABLE, M98504_WDOG_ENABLE_SHIFT, 1, 0),
	SOC_SINGLE("Watchdog Config Switch", MAX98504_REG_13_WATCHDOG_CONFIG, M98504_WDOG_CONFIG_SHIFT, 3, 0),
	SOC_SINGLE("Watchdog Clear Switch", MAX98504_REG_14_WATCHDOG_CLEAR, M98504_WDOG_CLEAR_SHIFT, 0xe9, 0),
	SOC_SINGLE("Clock Monitor Switch", MAX98504_REG_15_CLOCK_MONITOR_ENABLE, M98504_CMON_ENA_SHIFT, 1, 0),
	SOC_SINGLE("Brownout Protection Switch", MAX98504_REG_16_PVDD_BROWNOUT_ENABLE, M98504_CMON_ENA_SHIFT, 1, 0),
	SOC_ENUM("Brownout Threshold", max98504_brownout_code_enum),
	SOC_ENUM("Brownout Attenuation Value", max98504_brownout_max_atten_enum),
	SOC_SINGLE("Brownout Attack Hold Time", MAX98504_REG_18_PVDD_BROWNOUT_CONFIG_2, M98504_PVDD_BROWNOUT_CFG2_ATTK_HOLD_SHIFT, 255, 0),
	SOC_SINGLE("Brownout Timed Hold", MAX98504_REG_19_PVDD_BROWNOUT_CONFIG_3, M98504_PVDD_BROWNOUT_CFG3_TIMED_HOLD_SHIFT, 255, 0),
	SOC_SINGLE("Brownout Release", MAX98504_REG_1A_PVDD_BROWNOUT_CONFIG_4, M98504_PVDD_BROWNOUT_CFG4_RELEASE_SHIFT, 255, 0),

	SOC_SINGLE("PCM BCLK Edge", MAX98504_REG_24_PCM_MODE_CONFIG, M98504_PCM_MODE_CFG_BCLKEDGE_SHIFT, 1, 0),
	SOC_SINGLE("PCM Channel Select", MAX98504_REG_24_PCM_MODE_CONFIG, M98504_PCM_MODE_CFG_CHSEL_SHIFT, 1, 0),
	SOC_SINGLE("PCM Transmit Extra HiZ Switch", MAX98504_REG_24_PCM_MODE_CONFIG, M98504_PCM_MODE_CFG_TX_EXTRA_HIZ_SHIFT, 1, 0),
	SOC_SINGLE("PCM Output Dither Switch", MAX98504_REG_25_PCM_DSP_CONFIG, M98504_PCM_DSP_CFG_TX_DITH_EN_SHIFT, 1, 0),
	SOC_SINGLE("PCM Measurement DC Blocking Filter Switch", MAX98504_REG_25_PCM_DSP_CONFIG, M98504_PCM_DSP_CFG_MEAS_DCBLK_EN_SHIFT, 1, 0),
	SOC_SINGLE("PCM Input Dither Switch", MAX98504_REG_25_PCM_DSP_CONFIG, M98504_PCM_DSP_CFG_RX_DITH_EN_SHIFT, 1, 0),
	SOC_ENUM("PCM Output Filter Mode", max98504_pcm_rx_flt_mode_enum),
	SOC_SINGLE_EXT_TLV("PCM Rx Gain",
		MAX98504_REG_25_PCM_DSP_CONFIG, M98504_PCM_DSP_CFG_RX_GAIN_SHIFT,
		M98504_PCM_DSP_CFG_RX_GAIN_WIDTH - 1, 1, max98504_rxpcm_gain_get, max98504_rxpcm_gain_set, 
		max98504_rxpcm_gain_tlv),

	SOC_SINGLE("DAC MONOMIX", MAX98504_REG_28_PCM_TO_SPEAKER_MONOMIX,
		M98504_PCM_TO_SPK_MONOMIX_CFG_SHIFT, 3, 0),

	SOC_ENUM("PCM BCLK rate", max98504_pcm_bsel_enum),
	
	SOC_ENUM("Speaker Current Sense Enable", max98504_ispken_enum),
	SOC_ENUM("Speaker Voltage Sense Enable", max98504_vspken_enum),

	SOC_SINGLE_EXT_TLV("AIN Gain",
		MAX98504_REG_37_ANALOGUE_INPUT_GAIN, M98504_ANALOG_INPUT_GAIN_SHIFT,
		M98504_ANALOG_INPUT_GAIN_WIDTH - 1, 1, max98504_ain_gain_get, max98504_ain_gain_set, 
		max98504_ain_gain_tlv),

	SOC_SINGLE("AUTH_STATUS", MAX98504_REG_01_INTERRUPT_STATUS, 0, M98504_INT_INTERRUPT_STATUS_MASK, 0),
};

static const char *spk_src_mux_text[] = { "PCM", "AIN", "PDM_CH0", "PDM_CH1" };

#if 0 // TEMP TEST FACTORY
static const struct soc_enum spk_src_mux_enum =
	SOC_ENUM_SINGLE(MAX98504_REG_35_SPEAKER_SOURCE_SELECT, 7,
		ARRAY_SIZE(spk_src_mux_text), spk_src_mux_text);
#else
static const struct soc_enum spk_src_mux_enum =
	SOC_ENUM_SINGLE(MAX98504_REG_35_SPEAKER_SOURCE_SELECT, M98504_SPK_SRC_SEL_SHIFT,
		ARRAY_SIZE(spk_src_mux_text), spk_src_mux_text);
#endif
static const struct snd_kcontrol_new max98504_spk_src_mux =
	SOC_DAPM_ENUM("SPK_SRC Mux", spk_src_mux_enum);

static const struct snd_kcontrol_new max98504_digital_mono_mixer_controls[] = {
	SOC_DAPM_SINGLE("CH0 DAC Switch", MAX98504_REG_28_PCM_TO_SPEAKER_MONOMIX,
		M98504_PCM_TO_SPK_MONOMIX_CH0_SRC_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("CH1 DAC Switch", MAX98504_REG_28_PCM_TO_SPEAKER_MONOMIX,
		M98504_PCM_TO_SPK_MONOMIX_CH1_SRC_SHIFT, 1, 0),
};

static const struct snd_soc_dapm_widget max98504_dapm_widgets[] = {
	//SND_SOC_DAPM_SUPPLY("SHDN", MAX98504_REG_40_GLOBAL_ENABLE, M98504_GLOBAL_EN_SHIFT, 0, NULL, 0),

	SND_SOC_DAPM_INPUT("Voltage Data"),
	SND_SOC_DAPM_INPUT("Current Data"),
	SND_SOC_DAPM_INPUT("Analog Input"),

	SND_SOC_DAPM_ADC("ADCL", NULL, MAX98504_REG_36_MEASUREMENT_ENABLES,
		M98504_MEAS_V_EN_SHIFT, 0),
	SND_SOC_DAPM_ADC("ADCR", NULL, MAX98504_REG_36_MEASUREMENT_ENABLES,
		M98504_MEAS_I_EN_SHIFT, 0),

	SND_SOC_DAPM_AIF_OUT("AIFOUTL", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIFOUTR", "AIF1 Capture", 1, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("AIFINL", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFINR", "AIF1 Playback", 1, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DACL", NULL, MAX98504_REG_20_PCM_RX_ENABLES,
		M98504_PCM_RX_EN_CH0_SHIFT, 0),
	SND_SOC_DAPM_DAC("DACR", NULL, MAX98504_REG_20_PCM_RX_ENABLES,
		M98504_PCM_RX_EN_CH1_SHIFT, 0),

	SND_SOC_DAPM_MIXER("Digital Mono Mixer", SND_SOC_NOPM, 0, 0,
		&max98504_digital_mono_mixer_controls[0],
		ARRAY_SIZE(max98504_digital_mono_mixer_controls)),

	SND_SOC_DAPM_MUX("SPK_SRC Mux", SND_SOC_NOPM,
		0, 0, &max98504_spk_src_mux),

	SND_SOC_DAPM_PGA("SHDN_TEMP", MAX98504_REG_40_GLOBAL_ENABLE, M98504_GLOBAL_EN_SHIFT, 0, NULL, 0),
#if 0 // TEMP TEST FACTORY
	SND_SOC_DAPM_PGA("SPK Mono Out", MAX98504_REG_34_SPEAKER_ENABLE, 7, 0, NULL, 0),
#else
	SND_SOC_DAPM_PGA("SPK Mono Out", MAX98504_REG_34_SPEAKER_ENABLE, M98504_SPK_EN_SHIFT, 0, NULL, 0),
#endif
	SND_SOC_DAPM_OUTPUT("SPKOUT"),
};

static const struct snd_soc_dapm_route max98504_audio_map[] = {
	{"ADCL", NULL, "Voltage Data"},
	{"ADCR", NULL, "Current Data"},

	{"AIFOUTL", NULL, "ADCL"},
	{"AIFOUTR", NULL, "ADCR"},
	//{"AIFOUTL", NULL, "SHDN"},
	//{"AIFOUTR", NULL, "SHDN"},

	//{"AIFINL", NULL, "SHDN"},
	//{"AIFINR", NULL, "SHDN"},

	{"Digital Mono Mixer", "CH0 DAC Switch", "DACL"}, 
	{"Digital Mono Mixer", "CH1 DAC Switch", "DACR"},

	{"SPK_SRC Mux", "PCM", "Digital Mono Mixer"}, 
	{"SPK_SRC Mux", "AIN", "Analog Input"}, 
	{"SHDN_TEMP", NULL, "SPK_SRC Mux"},

	{"SPK Mono Out", NULL, "SHDN_TEMP"}, 
	{"SPKOUT", NULL, "SPK Mono Out"}, 
};

static int max98504_add_widgets(struct snd_soc_codec *codec)
{
	//struct max98504_priv *max98504 = snd_soc_codec_get_drvdata(codec);

	msg_maxim("\n");

	snd_soc_add_codec_controls(codec, max98504_snd_controls,
		ARRAY_SIZE(max98504_snd_controls));

	return 0;
}

/* codec sample rate config parameter table */
static const struct { 
	u32 rate;
	u8  sr;
} rate_table[] = {
	{8000,  (0)},
	{11025,	(1)},
	{12000, (2)},
	{16000, (3)},
	{22050, (4)},
	{24000, (5)},
    {32000, (6)},
	{44100, (7)},
	{48000, (8)},
};
static inline int rate_value(int rate, u8 *value)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rate_table); i++) {
	       if (rate_table[i].rate >= rate) {
	               *value = rate_table[i].sr;
	               return 0;
	       }
	}
	*value = rate_table[0].sr;
	return -EINVAL;
}


/* #define TDM */
static int max98504_set_tdm_slot(struct snd_soc_dai *codec_dai, unsigned int tx_mask,
				      unsigned int rx_mask, int slots, int slot_width)
{
	return 0;
}

static int max98504_dai_set_fmt(struct snd_soc_dai *codec_dai,
				 unsigned int fmt)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct max98504_priv *max98504 = snd_soc_codec_get_drvdata(codec);
	struct max98504_cdata *cdata;
	u8 regval;

	msg_maxim("\n");

	cdata = &max98504->dai[0];

	if (fmt != cdata->fmt) {
		cdata->fmt = fmt;

		regval = 0;

		switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
		case SND_SOC_DAIFMT_CBS_CFS:
		case SND_SOC_DAIFMT_CBM_CFM:
			break;
		case SND_SOC_DAIFMT_CBS_CFM:
		case SND_SOC_DAIFMT_CBM_CFS:
		default:
			dev_err(codec->dev, "DAI clock mode unsupported");
			return -EINVAL;
		}

		switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
		case SND_SOC_DAIFMT_I2S:
			snd_soc_update_bits(codec, MAX98504_REG_24_PCM_MODE_CONFIG,
				M98504_PCM_MODE_CFG_FORMAT_MASK, M98504_PCM_MODE_CFG_FORMAT_I2S_MASK);
			break;
		case SND_SOC_DAIFMT_LEFT_J:
			snd_soc_update_bits(codec, MAX98504_REG_24_PCM_MODE_CONFIG,
				M98504_PCM_MODE_CFG_FORMAT_MASK, M98504_PCM_MODE_CFG_FORMAT_LJ_MASK);
			break;
		case SND_SOC_DAIFMT_RIGHT_J:
			snd_soc_update_bits(codec, MAX98504_REG_24_PCM_MODE_CONFIG,
				M98504_PCM_MODE_CFG_FORMAT_MASK, M98504_PCM_MODE_CFG_FORMAT_RJ_MASK);
			break;
		case SND_SOC_DAIFMT_DSP_A:
			/* Not supported mode */
		default:
			dev_err(codec->dev, "DAI format unsupported, fmt:0x%x", fmt);
			return -EINVAL;
		}

		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
		case SND_SOC_DAIFMT_NB_IF:
			break;
		case SND_SOC_DAIFMT_IB_NF:
		case SND_SOC_DAIFMT_IB_IF:
			break;
		default:
			dev_err(codec->dev, "DAI invert mode unsupported");
			return -EINVAL;
		}

		snd_soc_write(codec, MAX98504_REG_26_PCM_CLOCK_SETUP, 0);

	}

	return 0;
}

static int max98504_set_bias_level(struct snd_soc_codec *codec,
				   enum snd_soc_bias_level level)
{

	int ret;

	msg_maxim("level=%d \n", level);

	switch (level) {
	case SND_SOC_BIAS_ON:

	if (codec->dapm.bias_level == SND_SOC_BIAS_OFF) {
		ret = snd_soc_cache_sync(codec);

		if (ret != 0) {
			dev_err(codec->dev, "Failed to sync cache: %d\n", ret);
			return ret;
		}
	}

//	snd_soc_update_bits(codec, MAX98504_REG_40_GLOBAL_ENABLE,
	//	M98504_GLOBAL_EN_MASK, M98504_GLOBAL_EN_MASK);

	break;

	case SND_SOC_BIAS_PREPARE:
		break;


	case SND_SOC_BIAS_STANDBY:
	case SND_SOC_BIAS_OFF:
		//snd_soc_update_bits(codec, MAX98504_REG_40_GLOBAL_ENABLE,
			//M98504_GLOBAL_EN_MASK, 0x00);

		codec->cache_sync = 1;
		break;
	}

	codec->dapm.bias_level = level;
	return 0;
}

static int max98504_dai_hw_params(struct snd_pcm_substream *substream,
				   struct snd_pcm_hw_params *params,
				   struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct max98504_priv *max98504 = snd_soc_codec_get_drvdata(codec);
	struct max98504_cdata *cdata;

	unsigned int rate;
	u8 regval;

	msg_maxim("\n");

	cdata = &max98504->dai[0];

	rate = params_rate(params);

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S8:
		snd_soc_update_bits(codec, MAX98504_REG_24_PCM_MODE_CONFIG,
			M98504_PCM_MODE_CFG_CH_SIZE_MASK, M98504_PCM_MODE_CFG_CH_SIZE_8_MASK);
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		snd_soc_update_bits(codec, MAX98504_REG_24_PCM_MODE_CONFIG,
			M98504_PCM_MODE_CFG_CH_SIZE_MASK, M98504_PCM_MODE_CFG_CH_SIZE_16_MASK);
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		snd_soc_update_bits(codec, MAX98504_REG_24_PCM_MODE_CONFIG,
			M98504_PCM_MODE_CFG_CH_SIZE_MASK, M98504_PCM_MODE_CFG_CH_SIZE_24_MASK);
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		snd_soc_update_bits(codec, MAX98504_REG_24_PCM_MODE_CONFIG,
			M98504_PCM_MODE_CFG_CH_SIZE_MASK, M98504_PCM_MODE_CFG_CH_SIZE_32_MASK);
		break;
	default:
		return -EINVAL;
	}

	if (rate_value(rate, &regval))
		return -EINVAL;

	/* Update sample rate mode */
	snd_soc_update_bits(codec, MAX98504_REG_27_PCM_SAMPLE_RATE_SETUP,
		M98504_PCM_SR_SETUP_SPK_SR_MASK, regval<<M98504_PCM_SR_SETUP_SPK_SR_SHIFT);	

	snd_soc_update_bits(codec, MAX98504_REG_27_PCM_SAMPLE_RATE_SETUP,
		M98504_PCM_SR_SETUP_MEAS_SR_MASK, regval<<M98504_PCM_SR_SETUP_MEAS_SR_SHIFT);

	return 0;
}

/*
 * PLL / Sysclk
 */
static int max98504_dai_set_sysclk(struct snd_soc_dai *dai,
				   int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = dai->codec;
	struct max98504_priv *max98504 = snd_soc_codec_get_drvdata(codec);

	msg_maxim("clk_id;%d, freq:%d, dir:%d\n", clk_id, freq, dir);

	/* Requested clock frequency is already setup */
	if (freq == max98504->sysclk)
		return 0;

	max98504->sysclk = freq;

	return 0;
}

static int max98504_dai_digital_mute(struct snd_soc_dai *codec_dai, int mute)
{
	//struct snd_soc_codec *codec = codec_dai->codec;

	msg_maxim("- mute:%d\n", mute);

	if(mute)	{
		#ifdef MAX98504_WATCHDOG_ENABLE
		snd_soc_write(codec, MAX98504_REG_12_WATCHDOG_ENABLE, 0);
		#endif
		//snd_soc_update_bits(codec, MAX98504_REG_34_SPEAKER_ENABLE, M98504_SPK_EN_MASK, 0);
	}
	else	{
		#ifdef MAX98504_WATCHDOG_ENABLE
		snd_soc_write(codec, MAX98504_REG_12_WATCHDOG_ENABLE, M98504_WDOG_ENABLE_MASK);
		#endif
		//snd_soc_update_bits(codec, MAX98504_REG_34_SPEAKER_ENABLE, M98504_SPK_EN_MASK, M98504_SPK_EN_MASK);
	}
	return 0;
}

#define MAX98504_RATES SNDRV_PCM_RATE_8000_48000
#define MAX98504_FORMATS (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

static struct snd_soc_dai_ops max98504_dai_ops = {
	.set_sysclk = max98504_dai_set_sysclk,
	.set_fmt = max98504_dai_set_fmt,
	.set_tdm_slot = max98504_set_tdm_slot,
	.hw_params = max98504_dai_hw_params,
	.digital_mute = max98504_dai_digital_mute,
};

static struct snd_soc_dai_driver max98504_dai[] = {
{
	.name = "max98504-aif1",
	.playback = {
		.stream_name = "AIF1 Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = MAX98504_RATES,
		.formats = MAX98504_FORMATS,
	},
	.capture = {
		.stream_name = "AIF1 Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = MAX98504_RATES,
		.formats = MAX98504_FORMATS,
	},
	 .ops = &max98504_dai_ops,
}
};

#if 1	// TEST
static struct max98504_dsp_cfg dsp_cfg[] = {
	{
		.name = "FILTER",
		.tx_dither_en = 1,
		.rx_dither_en = 1,
		.meas_dc_block_en = 1,	
		.rx_flt_mode = 1,
	},
};

static struct max98504_pdata max98504_config = {
	.dsp_cfg = dsp_cfg,
	.clk_monitor_en = 0,
	.rx_ch_en = 0x00,
	.tx_ch_en = 0x03,
	.tx_hiz_ch_en = 0x00,
	.tx_ch_src = 0x2,
	.auth_en = 0,
	.wdog_time_out = 3,
};
#endif
static void max98504_handle_pdata(struct snd_soc_codec *codec)
{
	struct max98504_priv *max98504 = snd_soc_codec_get_drvdata(codec);
	struct max98504_pdata *pdata = max98504->pdata;

	struct max98504_dsp_cfg *dsp_cfg;
	u8 cmon_en, rx_en, tx_en, tx_hiz_en, tx_ch_src, auth_en, wdog_time_out;
	u8 regval = 0;

#if 1	// TEST
	pdata = &max98504_config;
#endif
	msg_maxim("\n");

	if (!pdata) {
		dev_dbg(codec->dev, "No platform data\n");
		return;
	}
	dsp_cfg = pdata->dsp_cfg;
	cmon_en = pdata->clk_monitor_en;
	rx_en = pdata->rx_ch_en;
	tx_en = pdata->tx_ch_en;
	tx_hiz_en = pdata->tx_hiz_ch_en;
	tx_ch_src = pdata->tx_ch_src;
	auth_en = pdata->auth_en;
	wdog_time_out = pdata->wdog_time_out;

	/* filter */
	if(dsp_cfg->tx_dither_en)	regval = M98504_PCM_DSP_CFG_TX_DITH_EN_MASK;
	if(dsp_cfg->meas_dc_block_en)	regval |= M98504_PCM_DSP_CFG_MEAS_DCBLK_EN_MASK;
	if(dsp_cfg->rx_dither_en)	regval |= M98504_PCM_DSP_CFG_RX_DITH_EN_MASK;
	if(dsp_cfg->rx_flt_mode)	regval |= M98504_PCM_DSP_CFG_RX_FLT_MODE_MASK;

	snd_soc_update_bits(codec, MAX98504_REG_25_PCM_DSP_CONFIG,
		M98504_PCM_DSP_CFG_FLT_MASK, regval);

	snd_soc_write(codec, MAX98504_REG_15_CLOCK_MONITOR_ENABLE, cmon_en & M98504_CMON_ENA_MASK);

	snd_soc_write(codec, MAX98504_REG_20_PCM_RX_ENABLES, rx_en);
	snd_soc_write(codec, MAX98504_REG_21_PCM_TX_ENABLES, tx_en);
	snd_soc_write(codec, MAX98504_REG_22_PCM_TX_HIZ_CONTROL, tx_hiz_en);
	snd_soc_write(codec, MAX98504_REG_23_PCM_TX_CHANNEL_SOURCES, tx_ch_src);

	snd_soc_write(codec, MAX98504_REG_13_WATCHDOG_CONFIG, wdog_time_out);

#if 0	// TEST
	snd_soc_write(codec, MAX98504_REG_35_SPEAKER_SOURCE_SELECT, 1);
#endif

	msg_maxim("RX_EN:0x%x, TX_EN:0x%x, TX_SRC:0x%x, wdog_time_out:%d\n", rx_en, tx_en, tx_ch_src, wdog_time_out);
}

static int max98504_suspend(struct snd_soc_codec *codec)
{
	msg_maxim("\n");
	if (max98504_vcc_i2c)
	{
		int rc;
		rc= regulator_disable(max98504_vcc_i2c);
		if(rc) {
				pr_err("Regulator vcc_i2c enable failed rc=%d\n", rc);
				return rc;
			}
	}

	return 0;
}

static int max98504_resume(struct snd_soc_codec *codec)
{
	msg_maxim("\n");
	if(max98504_vcc_i2c)
	{
		int rc;
		rc = regulator_enable(max98504_vcc_i2c);
		if (rc) {
			pr_err("Regulator vcc_i2c enable failed rc=%d\n", rc);
			return rc;
		}
	}
	return 0;
}

#ifdef MAX98504_WATCHDOG_ENABLE
static irqreturn_t max98504_interrupt(int irq, void *data)
{
	struct snd_soc_codec *codec = (struct snd_soc_codec *) data;
	struct max98504_priv *max98504 = snd_soc_codec_get_drvdata(codec);

	unsigned int mask;
	unsigned int flag;

	mask = snd_soc_read(codec, MAX98504_REG_03_INTERRUPT_ENABLES);
	flag = snd_soc_read(codec, MAX98504_REG_02_INTERRUPT_FLAGS);

	msg_maxim("flag=0x%02x mask=0x%02x -> flag=0x%02x\n",
		flag, mask, flag & mask);

	flag &= mask;

	if (!flag)
		return IRQ_NONE;
	
	/* Send work to be scheduled */
	if (flag & M98504_INT_GENFAIL_EN_MASK) {
		msg_maxim("M98504_INT_GENFAIL_EN_MASK active!");
	}

	if (flag & M98504_INT_AUTHDONE_EN_MASK) {
		msg_maxim("M98504_INT_AUTHDONE_EN_MASK active!");
	}

	if (flag & M98504_INT_VBATBROWN_EN_MASK) {
		msg_maxim("M98504_INT_VBATBROWN_EN_MASK active!");
	}

	if (flag & M98504_INT_WATCHFAIL_EN_MASK) {
		msg_maxim("M98504_INT_WATCHFAIL_EN_MASK active!");
		schedule_delayed_work(&max98504->work, msecs_to_jiffies(2000));
	}

	if (flag & M98504_INT_THERMWARN_END_EN_MASK) {
		msg_maxim("M98504_INT_THERMWARN_END_EN_MASK active!");
	}

	if (flag & M98504_INT_THERMWARN_BGN_EN_MASK) {
		msg_maxim("M98504_INT_THERMWARN_BGN_EN_MASK active!\n");
	}
	if (flag & M98504_INT_THERMSHDN_END_EN_MASK) {
		msg_maxim("M98504_INT_THERMSHDN_END_EN_MASK active!\n");
	}
	if (flag & M98504_INT_THERMSHDN_BGN_FLAG_MASK) {
		msg_maxim("M98504_INT_THERMSHDN_BGN_FLAG_MASK active!\n");
	}
	snd_soc_write(codec, MAX98504_REG_04_INTERRUPT_FLAG_CLEARS, flag&0xff);

	return IRQ_HANDLED;
}
#endif

#ifdef MAX98504_WATCHDOG_ENABLE
static void max98504_work(struct work_struct *work)
{
	struct max98504_priv *max98504 = container_of(work, struct max98504_priv, work.work);
	struct snd_soc_codec *codec= max98504->codec;

	if(codec->dapm.bias_level==SND_SOC_BIAS_ON)	{
		snd_soc_write(codec, MAX98504_REG_14_WATCHDOG_CLEAR, 0xE9);
		snd_soc_write(codec, MAX98504_REG_40_GLOBAL_ENABLE, M98504_GLOBAL_EN_MASK);
		msg_maxim("Watchdog Recovery\n");
	}
	else	msg_maxim("No Watchdog Recovery.\n");
}
#endif

static int max98504_probe(struct snd_soc_codec *codec)
{
	struct max98504_priv *max98504 = snd_soc_codec_get_drvdata(codec);
	struct max98504_cdata *cdata;
	int ret = 0;

	msg_maxim("\n");

	max98504->codec = codec;

	codec->cache_sync = 1;

	ret = snd_soc_codec_set_cache_io(codec, 16, 8, SND_SOC_I2C);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to set cache I/O: %d\n", ret);
		return ret;
	}

	/* reset the codec, the DSP core, and disable all interrupts */
	ret = max98504_reset(codec);
	if (ret < 0) {
		goto err_access;
	}

	/* initialize private data */

	max98504->sysclk = (unsigned)-1;

	cdata = &max98504->dai[0];
	cdata->rate = (unsigned)-1;
	cdata->fmt  = (unsigned)-1;

	ret = snd_soc_read(codec, MAX98504_REG_7FFF_REV_ID);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to read device revision: %d\n",
			ret);
		goto err_access;
	}
	msg_maxim("REV ID=0x%x\n", ret);

	// Do this command for SSM, DEM enable.
	snd_soc_write(codec, MAX98504_REG_7FFF_REV_ID, 0x54);
	snd_soc_write(codec, MAX98504_REG_7FFF_REV_ID, 0x4d);

	#if 0 // // TEMP TEST FACTORY
	snd_soc_write(codec, MAX98504_REG_34_SPEAKER_ENABLE, 0x1);	// Temporary
	snd_soc_write(codec, MAX98504_REG_36_MEASUREMENT_ENABLES, 0x3);	// Temporary
	#endif
	

#ifdef MAX98504_WATCHDOG_ENABLE
	snd_soc_write(codec, MAX98504_REG_03_INTERRUPT_ENABLES, M98504_INT_WATCHFAIL_EN_MASK);
	snd_soc_write(codec, MAX98504_REG_10_GPIO_ENABLE, M98504_GPIO_ENABLE_MASK);
	snd_soc_write(codec, MAX98504_REG_04_INTERRUPT_FLAG_CLEARS, 0xFF);

	if ( (request_threaded_irq(pdata->irq, NULL,
		max98504_interrupt, IRQF_TRIGGER_FALLING,
		"max98504_interrupt", codec)) < 0) {
		msg_maxim("request_irq failed\n");
	}
#endif

	max98504_handle_pdata(codec);
	max98504_add_widgets(codec);

#ifdef MAX98504_WATCHDOG_ENABLE
	INIT_DELAYED_WORK_DEFERRABLE(&max98504->work, max98504_work);
#endif

	msg_maxim("done.");

err_access:
	return ret;
}

static int max98504_remove(struct snd_soc_codec *codec)
{

	msg_maxim("\n");

	return 0;
}

static struct snd_soc_codec_driver soc_codec_dev_max98504 = {
	.probe   = max98504_probe,
	.remove  = max98504_remove,
	.suspend = max98504_suspend,
	.resume  = max98504_resume,
	.set_bias_level = max98504_set_bias_level,
	.reg_cache_size = ARRAY_SIZE(max98504_reg_def),
	.reg_word_size = sizeof(u8),
	.reg_cache_default = max98504_reg_def,
	.readable_register = max98504_readable,
	.volatile_register = max98504_volatile_register,
	.dapm_widgets	  = max98504_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(max98504_dapm_widgets),
	.dapm_routes     = max98504_audio_map,
	.num_dapm_routes = ARRAY_SIZE(max98504_audio_map),
};

#ifdef SUPPORT_DEVICE_TREE
static int reg_set_optimum_mode_check(struct regulator *reg, int load_uA)
{
	return (regulator_count_voltages(reg) > 0) ?
		regulator_set_optimum_mode(reg, load_uA) : 0;
}

static int max98504_regulator_config(struct i2c_client *i2c, bool pullup, bool on)
{
	int rc;
    #define VCC_I2C_MIN_UV	1800000
    #define VCC_I2C_MAX_UV	1800000
	#define I2C_LOAD_UA		300000

	//pr_info("[RYAN] %s\n", __func__);

	if (pullup) {
		//pr_info("[RYAN] %s I2C PULL UP.\n", __func__);

		max98504_vcc_i2c = regulator_get(&i2c->dev, "vcc_i2c");
		if (IS_ERR(max98504_vcc_i2c)) {
			rc = PTR_ERR(max98504_vcc_i2c);
			pr_info("Regulator get failed rc=%d\n",	rc);
			goto error_get_vtg_i2c;
		}
		if (regulator_count_voltages(max98504_vcc_i2c) > 0) {
			rc = regulator_set_voltage(max98504_vcc_i2c,
				VCC_I2C_MIN_UV, VCC_I2C_MAX_UV);
			if (rc) {
				pr_info("regulator set_vtg failed rc=%d\n", rc);
				goto error_set_vtg_i2c;
			}
		}

		rc = reg_set_optimum_mode_check(max98504_vcc_i2c, I2C_LOAD_UA);
		if (rc < 0) {
			pr_info("Regulator vcc_i2c set_opt failed rc=%d\n", rc);
			goto error_reg_opt_i2c;
		}
		
		rc = regulator_enable(max98504_vcc_i2c);
		if (rc) {
			pr_info("Regulator vcc_i2c enable failed rc=%d\n", rc);
			goto error_reg_en_vcc_i2c;
		}

	}
	//pr_info("[RYAN] %s OUT\n", __func__);

	return 0;

error_reg_en_vcc_i2c:
	if(pullup) reg_set_optimum_mode_check(max98504_vcc_i2c, 0);
error_reg_opt_i2c:
	regulator_disable(max98504_vcc_i2c);
error_set_vtg_i2c:
	if (regulator_count_voltages(max98504_vcc_i2c) > 0)
		regulator_set_voltage(max98504_vcc_i2c, 0,
			VCC_I2C_MAX_UV);
error_get_vtg_i2c:
	regulator_put(max98504_vcc_i2c);

	//pr_info("[RYAN] %s OUT WITH ERROR.\n", __func__);


	return rc;
}
#endif

static int max98504_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct max98504_priv *max98504;
	int ret;

	msg_maxim("\n");
#ifdef SUPPORT_DEVICE_TREE
	max98504_regulator_config(i2c, of_property_read_bool(i2c->dev.of_node, "max98504,i2c-pull-up"), 1);
#endif

	max98504 = kzalloc(sizeof(struct max98504_priv), GFP_KERNEL);
	if (max98504 == NULL)
		return -ENOMEM;

	max98504->devtype = id->driver_data;
	i2c_set_clientdata(i2c, max98504);
	max98504->control_data = i2c;
	max98504->pdata = i2c->dev.platform_data;

	ret = snd_soc_register_codec(&i2c->dev,
			&soc_codec_dev_max98504, max98504_dai, ARRAY_SIZE(max98504_dai));
	msg_maxim("ret=%d\n", ret);

	if (ret < 0)
		kfree(max98504);
	return ret;
}

static int __devexit max98504_i2c_remove(struct i2c_client *client)
{
	snd_soc_unregister_codec(&client->dev);
	kfree(i2c_get_clientdata(client));

	msg_maxim("\n");

	return 0;
}

static const struct i2c_device_id max98504_i2c_id[] = {
	{ "max98504", MAX98504 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, max98504_i2c_id);

static struct i2c_driver max98504_i2c_driver = {
	.driver = {
		.name = "max98504",
		.owner = THIS_MODULE,
	},
	.probe  = max98504_i2c_probe,
	.remove = __devexit_p(max98504_i2c_remove),
	.id_table = max98504_i2c_id,
};

#ifdef USE_MISC_FOR_DEMO
static int param_voice_coil_temp=0;	//0
static int param_voice_coil_temp_sz=0;	// 1
static int param_excursion=0;	// 2
static int param_excursion_sz=0;	// 3
static int param_rdc=0; // 4
static int param_rdc_sz=0; // 5
static int param_q=0; // 6
static int param_q_sz=0; // 7
static int param_fres=0;// 8
static int param_fres_sz=0;// 9
static int param_excur_limit=0;// 10
static int param_excur_limit_sz=0;// 11
static int param_voice_coil=0; // 12
static int param_voice_coil_sz=0; // 13
static int param_thermal_limit=0;// 14
static int param_thermal_limit_sz=0;// 15
static int param_release_time=0; // 16
static int param_release_time_sz=0; // 17
static int param_onoff=0; // 18
static int param_onoff_sz=0; // 19

#define DSM_PARAM_SZIE	4*10*2

#if 1 // Vinay
extern int32_t dsm_open(int32_t port_id,uint32_t*  dsm_params, u8* param);
#endif

static void write_param(u8 *param)
{
	uint32_t filter_set;
    int32_t port_id =0x4000; //hardcoded to slimbus
	int x=0;

	x=10;

	memcpy(&param_excur_limit, &param[x*4], 4);	x+=2;
	memcpy(&param_voice_coil, &param[x*4], 4);	x+=2;
	memcpy(&param_thermal_limit, &param[x*4], 4);	x+=2;
	memcpy(&param_release_time, &param[x*4], 4);	x+=2;
	memcpy(&param_onoff, &param[x*4], 4);

	/* set params from the algorithm to application */
	filter_set = 3;
	dsm_open(port_id, &filter_set, param);
	
	//pr_info("[RYAN] write_param excur_limit:%d, voice_coil:%d\n", param_excur_limit, param_voice_coil);
	//pr_info("[RYAN] thermal_limit:%d, param_release_time:%d, param_onoff:%d\n", param_thermal_limit, param_release_time, param_onoff);

}
static void read_param(u8 *param)
{
	int x=0;
	uint32_t filter_set;
    int32_t port_id =0x4000; //hardcoded to slimbus

	filter_set = 2;
	dsm_open(port_id, &filter_set, param);

	memcpy(&param_voice_coil_temp, &param[x*4], 4); x++;
	memcpy(&param_voice_coil_temp_sz, &param[x*4], 4); x++;
	
	memcpy(&param_excursion, &param[x*4], 4); x++;
	memcpy(&param_excursion_sz, &param[x*4], 4); x++;
	
	memcpy(&param_rdc, &param[x*4], 4); x++;
	memcpy(&param_rdc_sz, &param[x*4], 4); x++;
	
	memcpy(&param_q, &param[x*4], 4); x++;
	memcpy(&param_q_sz, &param[x*4], 4); x++;
	
	memcpy(&param_fres, &param[x*4], 4); x++;
	memcpy(&param_fres_sz, &param[x*4], 4); x++;
	
	memcpy(&param_excur_limit, &param[x*4], 4); x++;
	memcpy(&param_excur_limit_sz, &param[x*4], 4); x++;
	
	memcpy(&param_voice_coil, &param[x*4], 4); x++;
	memcpy(&param_voice_coil_sz, &param[x*4], 4); x++;
	
	memcpy(&param_thermal_limit, &param[x*4], 4); x++;
	memcpy(&param_thermal_limit_sz, &param[x*4], 4); x++;
	
	memcpy(&param_release_time, &param[x*4], 4); x++;
	memcpy(&param_release_time_sz, &param[x*4], 4); x++;
	
	memcpy(&param_onoff, &param[x*4], 4); x++;
	memcpy(&param_onoff_sz, &param[x*4], 4);
	
	/* get params from the algorithm to application */

	//pr_info("[RYAN] read_param(1) param_rdc:%d, param_q:%d, param_fres:%d\n", param_rdc, param_q, param_fres);
	//pr_info("[RYAN] read_param(2) param_excur_limit:%d, param_voice_coil:%d, param_thermal_limit:%d\n", param_excur_limit, param_voice_coil, param_thermal_limit);
	//pr_info("[RYAN] read_param(3) param_release_time:%d, param_onoff:%d\n", param_release_time, param_onoff);
}

static int __devexit dsm_ctrl_remove(struct i2c_client *client)
{
	return 0;
}

static int dsm_ctrl_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int dsm_ctrl_release(struct inode *inode, struct file *file)
{
	return 0;	
}

static ssize_t dsm_ctrl_read(struct file *fp, char __user *buf,
			 size_t count, loff_t *pos)
{
	int rc;

	static u8 param[DSM_PARAM_SZIE];
	mutex_lock(&tx_lock);

	//pr_info("%s enter. (count:%d)\n", __func__, count);
	read_param(param);

	rc = copy_to_user(buf, param, count);
	if (rc != 0) {
		pr_err("copy_to_user failed. (rc=%d)\n", rc);
		mutex_unlock(&tx_lock);
		return 0;
	}
	//pr_info("%s out.\n", __func__);
	mutex_unlock(&tx_lock);

	return rc;
}

static ssize_t dsm_ctrl_write(struct file *file,
				const char __user *buf,
				size_t count,
				loff_t *ppos)
{
	int rc=0;
	static u8 param[DSM_PARAM_SZIE];
	int x;
	mutex_lock(&rx_lock);		
	//pr_info("%s enter. (count:%d)\n", __func__, count);

	rc = copy_from_user(param, buf, count);
	if (rc != 0) {
		//pr_info("copy_from_user failed. (rc=%d)", rc);
		mutex_unlock(&rx_lock);
		return rc;
	}
	//pr_info("----------------------------------------------------\n");
	for(x=0;x<80;x+=4)	{
		//pr_info("[RYAN] dsm_ctrl_write[%d] %d %d %d %d\n", x, param[x], param[x+1], param[x+2], param[x+3]);
	}
	write_param(param);
	mutex_unlock(&rx_lock);

	//pr_info("%s out.(count=%d, rc=%d)\n", __func__, count, rc);
	return rc;
}

static struct file_operations dsm_ctrl_fops = {
	.owner		= THIS_MODULE,
	.open		= dsm_ctrl_open,
	.release	= dsm_ctrl_release,
	.read = dsm_ctrl_read,
	.write = dsm_ctrl_write,
};
static struct miscdevice dsm_ctrl_miscdev = {
	.minor =    MISC_DYNAMIC_MINOR,
	.name =     "dsm_ctrl_dev",
	.fops =     &dsm_ctrl_fops
};

static int dsm_misc_device_init(void)
{
    int result=0;
    result = misc_register(&dsm_ctrl_miscdev);
    return result;
}
static int dsm_misc_device_deinit(void)
{
    int result=0;
    result = misc_deregister(&dsm_ctrl_miscdev);
    return result;
}
#endif

static int __init max98504_init(void)
{
	int ret;

	msg_maxim("%s\n", __func__);

	ret = i2c_add_driver(&max98504_i2c_driver);
	if (ret)
		pr_err("Failed to register MAX98504 I2C driver: %d\n", ret);
	else
		pr_info("MAX98504 driver built on %s at %s\n",
			__DATE__,
			__TIME__);

#ifdef USE_MISC_FOR_DEMO
	dsm_misc_device_init();
#endif
	return ret;
}

module_init(max98504_init);

static void __exit max98504_exit(void)
{
	i2c_del_driver(&max98504_i2c_driver);
#ifdef USE_MISC_FOR_DEMO
	dsm_misc_device_deinit();
#endif
}
module_exit(max98504_exit);

MODULE_DESCRIPTION("ALSA SoC MAX98504 driver");
MODULE_AUTHOR("Ryan Lee");
MODULE_LICENSE("GPL");

