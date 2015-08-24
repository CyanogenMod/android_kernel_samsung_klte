/*
 *  sec_board-msm8226.c
 *  Samsung Mobile Battery Driver
 *
 *  Copyright (C) 2013 Samsung Electronics
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/battery/sec_battery.h>
#include <linux/battery/sec_fuelgauge.h>
#include <linux/battery/sec_charging_common.h>

#include <linux/qpnp/pin.h>
#include <linux/qpnp/qpnp-adc.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/krait-regulator.h>

#define SHORT_BATTERY_STANDARD      100



#if defined(CONFIG_EXTCON)
int current_cable_type = POWER_SUPPLY_TYPE_BATTERY;
#else
extern int current_cable_type;
#endif
extern unsigned int system_rev;

extern int check_jig_state(void);
extern int check_sm5502_jig_state(void);

#if defined(CONFIG_FUELGAUGE_MAX17048)
static struct battery_data_t samsung_battery_data[] = {
  /* SDI battery data (High voltage 4.35V) */
  {
#if defined(CONFIG_MACH_AFYONLTE_TMO)
    .RCOMP0 = 0x4A,
    .RCOMP_charging = 0x4A,
    .temp_cohot = -75,
    .temp_cocold = -4700,
#else
    .RCOMP0 = 0x74,
    .RCOMP_charging = 0x8D,
    .temp_cohot = -1000,
    .temp_cocold = -4350,
#endif
    .is_using_model_data = true,
    .type_str = "SDI",
  }
};
#elif defined(CONFIG_FUELGAUGE_MAX17050)
static struct battery_data_t samsung_battery_data[] = {
  /* SDI battery data (High voltage 4.35V) */
  {
#if defined(CONFIG_SEC_MILLET_PROJECT)
    .Capacity = 0x2198, /* Millet : 4300mAh */
#elif defined(CONFIG_SEC_MATISSE_PROJECT)
    .Capacity = 0x32CD, /* Matisse: 6502mAh */
#else
    .Capacity = 0x4A38, /* V1/V2: 9500mAh */
#endif
    .low_battery_comp_voltage = 3500,
    .low_battery_table = {
      /* range, slope, offset */
      {-5000, 0,  0}, /* dummy for top limit */
      {-1250, 0,  3320},
      {-750, 97,  3451},
      {-100, 96,  3461},
      {0, 0,  3456},
    },
    .temp_adjust_table = {
      /* range, slope, offset */
      {47000, 122,  8950},
      {60000, 200,  51000},
      {100000, 0, 0}, /* dummy for top limit */
    },
    .type_str = "SDI",
  }
};
#else
static void * samsung_battery_data;
#endif

#define CAPACITY_MAX      1000
#define CAPACITY_MAX_MARGIN 50
#define CAPACITY_MIN      0

//static struct qpnp_vadc_chip *adc_client;
static enum qpnp_vadc_channels temp_channel;
static struct sec_fuelgauge_info *sec_fuelgauge =  NULL;

#if defined(CONFIG_MACH_AFYONLTE_TMO)
#define TEMP_HIGH_THRESHOLD_EVENT  620
#define TEMP_HIGH_RECOVERY_EVENT   480
#define TEMP_LOW_THRESHOLD_EVENT   (-33)
#define TEMP_LOW_RECOVERY_EVENT    10
#define TEMP_HIGH_THRESHOLD_NORMAL 520
#define TEMP_HIGH_RECOVERY_NORMAL  470
#define TEMP_LOW_THRESHOLD_NORMAL  (-33)
#define TEMP_LOW_RECOVERY_NORMAL   10
#define TEMP_HIGH_THRESHOLD_LPM    520
#define TEMP_HIGH_RECOVERY_LPM     480
#define TEMP_LOW_THRESHOLD_LPM     (-5)
#define TEMP_LOW_RECOVERY_LPM      30
#elif defined(CONFIG_MACH_MATISSELTE_ATT)|| defined(CONFIG_MACH_MATISSELTE_VZW)
#define TEMP_HIGH_THRESHOLD_EVENT  590
#define TEMP_HIGH_RECOVERY_EVENT   500
#define TEMP_LOW_THRESHOLD_EVENT   (-50)
#define TEMP_LOW_RECOVERY_EVENT    0
#define TEMP_HIGH_THRESHOLD_NORMAL 545
#define TEMP_HIGH_RECOVERY_NORMAL  475
#define TEMP_LOW_THRESHOLD_NORMAL  (-15)
#define TEMP_LOW_RECOVERY_NORMAL   0
#define TEMP_HIGH_THRESHOLD_LPM    520
#define TEMP_HIGH_RECOVERY_LPM     500
#define TEMP_LOW_THRESHOLD_LPM     (-10)
#define TEMP_LOW_RECOVERY_LPM      0
#elif defined(CONFIG_MACH_MATISSEWIFIUS_OPEN)
#define TEMP_HIGH_THRESHOLD_EVENT  530
#define TEMP_HIGH_RECOVERY_EVENT   460
#define TEMP_LOW_THRESHOLD_EVENT   (-50)
#define TEMP_LOW_RECOVERY_EVENT    0
#define TEMP_HIGH_THRESHOLD_NORMAL 530
#define TEMP_HIGH_RECOVERY_NORMAL  460
#define TEMP_LOW_THRESHOLD_NORMAL  (-20)
#define TEMP_LOW_RECOVERY_NORMAL   0
#define TEMP_HIGH_THRESHOLD_LPM    510
#define TEMP_HIGH_RECOVERY_LPM     490
#define TEMP_LOW_THRESHOLD_LPM     0
#define TEMP_LOW_RECOVERY_LPM      5
#elif defined(CONFIG_MACH_MILLETLTE_VZW)  || defined(CONFIG_MACH_MILLETWIFIUS_OPEN)
#define TEMP_HIGH_THRESHOLD_EVENT  645
#define TEMP_HIGH_RECOVERY_EVENT   505
#define TEMP_LOW_THRESHOLD_EVENT   (-50)
#define TEMP_LOW_RECOVERY_EVENT    0
#define TEMP_HIGH_THRESHOLD_NORMAL 555
#define TEMP_HIGH_RECOVERY_NORMAL  505
#define TEMP_LOW_THRESHOLD_NORMAL  (-50)
#define TEMP_LOW_RECOVERY_NORMAL   0
#define TEMP_HIGH_THRESHOLD_LPM    510
#define TEMP_HIGH_RECOVERY_LPM     460
#define TEMP_LOW_THRESHOLD_LPM     (-40)
#define TEMP_LOW_RECOVERY_LPM      0
#elif defined(CONFIG_SEC_MATISSE_PROJECT)
#define TEMP_HIGH_THRESHOLD_EVENT  600
#define TEMP_HIGH_RECOVERY_EVENT   450
#define TEMP_LOW_THRESHOLD_EVENT   (-50)
#define TEMP_LOW_RECOVERY_EVENT    0
#define TEMP_HIGH_THRESHOLD_NORMAL 600
#define TEMP_HIGH_RECOVERY_NORMAL  460
#define TEMP_LOW_THRESHOLD_NORMAL  (-50)
#define TEMP_LOW_RECOVERY_NORMAL   0
#define TEMP_HIGH_THRESHOLD_LPM    600
#define TEMP_HIGH_RECOVERY_LPM     460
#define TEMP_LOW_THRESHOLD_LPM     (-50)
#define TEMP_LOW_RECOVERY_LPM      0
#else
#define TEMP_HIGH_THRESHOLD_EVENT  520
#define TEMP_HIGH_RECOVERY_EVENT   460
#define TEMP_LOW_THRESHOLD_EVENT   (-50)
#define TEMP_LOW_RECOVERY_EVENT    0
#define TEMP_HIGH_THRESHOLD_NORMAL 520
#define TEMP_HIGH_RECOVERY_NORMAL  460
#define TEMP_LOW_THRESHOLD_NORMAL  (-50)
#define TEMP_LOW_RECOVERY_NORMAL   0
#define TEMP_HIGH_THRESHOLD_LPM    520
#define TEMP_HIGH_RECOVERY_LPM     460
#define TEMP_LOW_THRESHOLD_LPM     (-50)
#define TEMP_LOW_RECOVERY_LPM      0
#endif

#if defined(CONFIG_MACH_AFYONLTE_TMO)
static sec_bat_adc_table_data_t temp_table[] = {
  {27604, 650},
  {28080, 600},
  {28628, 550},
  {28858, 530},
  {29182, 510},
  {29306, 500},
  {29438, 490},
  {29627, 480},
  {30032, 450},
  {30879, 400},
  {31325, 380},
  {31772, 350},
  {32132, 330},
  {32825, 300},
  {33127, 280},
  {33825, 250},
  {34132, 230},
  {34843, 200},
  {35228, 180},
  {35911, 150},
  {36313, 130},
  {37021, 100},
  {37356, 80},
  {38034, 50},
  {38433, 30},
  {38716, 10},
  {38912, 0},
  {39120, -10},
  {39442, -30},
  {39855, -50},
  {40043, -70},
  {40580, -100},
  {41173, -150},
  {41667, -200},
};
#elif defined(CONFIG_MACH_MILLETLTE_VZW)
static sec_bat_adc_table_data_t temp_table[] = {
  {25950, 900},
  {26183, 850},
  {26397, 800},
  {26700, 750},
  {27061, 700},
  {27424, 650},
  {27873, 600},
  {28422, 550},
  {29065, 500},
  {29761, 450},
  {30819, 400},
  {31731, 350},
  {32633, 300},
  {33665, 250},
  {34711, 200},
  {35572, 150},
  {36680, 100},
  {37628, 50},
  {38706, 0},
  {39569, -50},
  {40286, -100},
  {40894, -150},
  {41448, -200},
};
#elif defined(CONFIG_SEC_MILLET_PROJECT)
static sec_bat_adc_table_data_t temp_table[] = {
  {26437, 900},
  {27225, 800},
  {28019, 700},
  {28378, 650},
  {28738, 620},
  {28917, 600},
  {29126, 580},
  {29576, 550},
  {30027, 500},
  {30420, 470}, 
  {30675, 450},
  {30953, 430},
  {31375, 400},
  {32149, 350},
  {32924, 300},
  {33849, 250},
  {34775, 200},
  {35694, 150},
  {36613, 100},
  {37216, 50},
  {37820, 20},
  {38170, 0},
  {38727, -30},
  {38878, -50},
  {39589, -100},
  {40303, -150},
  {40584, -200},
};

#elif defined(CONFIG_MACH_MATISSELTE_ATT)
static sec_bat_adc_table_data_t temp_table[] = {
  {32938, 700},
  {32888, 650},
  {32938, 600},
  {32991, 550},
  {33122, 500},
  {33095, 470},
  {33131, 450},
  {33218, 400},
  {33332, 350},
  {33474, 300},
  {33606, 250},
  {33797, 200},
  {33983, 150},
  {34281, 100},
  {34581, 50},
  {34857, 10},
  {34937, 0},
  {35131, -30},
  {35326, -50},
  {35795, -100},
  {36419, -150},
  {37016, -200},
  {37687, -250},
  {38387, -300},
};
#elif defined(CONFIG_MACH_MATISSELTE_VZW)
static sec_bat_adc_table_data_t temp_table[] = {
  {32810, 750},
  {32848, 700},
  {32888, 650},
  {32938, 600},
  {32991, 550},
  {33055, 500},
  {33131, 450},
  {33218, 400},
  {33332, 350},
  {33474, 300},
  {33606, 250},
  {33797, 200},
  {33983, 150},
  {34281, 100},
  {34581, 50},
  {34937, 0},
  {35326, -50},
  {35795, -100},
  {36419, -150},
  {37016, -200},
  {37687, -250},
  {38387, -300},
};
#elif defined(CONFIG_SEC_MATISSE_PROJECT)
static sec_bat_adc_table_data_t temp_table[] = {
  {24384, 900},
  {25129, 850},
  {25875, 800},
  {27567, 750},
  {27935, 700},
  {28388, 650},
  {28827, 600},
  {29363, 550},
  {29973, 500},
  {30585, 450},
  {31306, 400},
  {32056, 350},
  {32856, 300},
  {33728, 250},
  {34597, 200},
  {35633, 150},
  {36390, 100},
  {37252, 50},
  {38087, 0},
  {38867, -50},
  {39626, -100},
  {40212, -150},
  {40795, -200},
};
#else
static sec_bat_adc_table_data_t temp_table[] = {
  {25950, 900},
  {26173, 850},
  {26424, 800},
  {26727, 750},
  {26884, 700},
  {27346, 650},
  {27750, 600},
  {28213, 550},
  {28760, 500},
  {29384, 450},
  {30180, 400},
  {31095, 350},
  {32085, 300},
  {33132, 250},
  {34242, 200},
  {35340, 150},
  {36430, 100},
  {37471, 50},
  {38406, 0},
  {39388, -50},
  {40184, -100},
  {40852, -150},
  {41420, -200},
};
#endif

static void sec_bat_adc_ap_init(struct platform_device *pdev,
        struct sec_battery_info *battery)
{
  temp_channel = LR_MUX1_BATT_THERM;
  pr_info("%s :  temp_channel = %d\n", __func__,temp_channel);
}

static int sec_bat_adc_ap_read(struct sec_battery_info *battery, int channel)
{
  struct qpnp_vadc_result results;
  int rc = -1;
  int data = -1;

  switch (channel)
  {
  case SEC_BAT_ADC_CHANNEL_TEMP :
    rc = qpnp_vadc_read(NULL, temp_channel, &results);
    if (rc) {
      pr_err("%s: Unable to read batt temperature rc=%d\n",
        __func__, rc);
      return 0;
    }
    data = results.adc_code;
    break;
  case SEC_BAT_ADC_CHANNEL_TEMP_AMBIENT:
    data = 33000;
    break;
  case SEC_BAT_ADC_CHANNEL_BAT_CHECK:
    rc = qpnp_vadc_read(NULL, LR_MUX2_BAT_ID, &results);
    if (rc) {
      pr_err("%s: Unable to read BATT_ID ADC rc=%d\n",
        __func__, rc);
      return 0;
    }
    pr_debug("BAT_ID physical= %lld, raw = 0x%x\n", results.physical, results.adc_code);
    data = results.physical;
    break;
  default :
    break;
  }

  return data;
}

static void sec_bat_adc_ap_exit(void)
{
}

static void sec_bat_adc_none_init(struct platform_device *pdev,
        struct sec_battery_info *battery)
{
}

static int sec_bat_adc_none_read(struct sec_battery_info *battery, int channel)
{
  return 0;
}

static void sec_bat_adc_none_exit(void)
{
}

static void sec_bat_adc_ic_init(struct platform_device *pdev,
        struct sec_battery_info *battery)
{
}

static int sec_bat_adc_ic_read(struct sec_battery_info *battery, int channel)
{
  return 0;
}

static void sec_bat_adc_ic_exit(void)
{
}
static int adc_read_type(struct sec_battery_info *battery, int channel)
{
  int adc = 0;

  switch (battery->pdata->temp_adc_type)
  {
  case SEC_BATTERY_ADC_TYPE_NONE :
    adc = sec_bat_adc_none_read(battery, channel);
    break;
  case SEC_BATTERY_ADC_TYPE_AP :
    adc = sec_bat_adc_ap_read(battery, channel);
    break;
  case SEC_BATTERY_ADC_TYPE_IC :
    adc = sec_bat_adc_ic_read(battery, channel);
    break;
  case SEC_BATTERY_ADC_TYPE_NUM :
    break;
  default :
    break;
  }
  pr_debug("[%s] ADC = %d\n", __func__, adc);
  return adc;
}

static void adc_init_type(struct platform_device *pdev,
        struct sec_battery_info *battery)
{
  switch (battery->pdata->temp_adc_type)
  {
  case SEC_BATTERY_ADC_TYPE_NONE :
    sec_bat_adc_none_init(pdev, battery);
    break;
  case SEC_BATTERY_ADC_TYPE_AP :
    sec_bat_adc_ap_init(pdev, battery);
    break;
  case SEC_BATTERY_ADC_TYPE_IC :
    sec_bat_adc_ic_init(pdev, battery);
    break;
  case SEC_BATTERY_ADC_TYPE_NUM :
    break;
  default :
    break;
  }
}

static void adc_exit_type(struct sec_battery_info *battery)
{
  switch (battery->pdata->temp_adc_type)
  {
  case SEC_BATTERY_ADC_TYPE_NONE :
    sec_bat_adc_none_exit();
    break;
  case SEC_BATTERY_ADC_TYPE_AP :
    sec_bat_adc_ap_exit();
    break;
  case SEC_BATTERY_ADC_TYPE_IC :
    sec_bat_adc_ic_exit();
    break;
  case SEC_BATTERY_ADC_TYPE_NUM :
    break;
  default :
    break;
  }
}

int adc_read(struct sec_battery_info *battery, int channel)
{
  int adc = 0;

  adc = adc_read_type(battery, channel);

  pr_info("[%s]adc = %d\n", __func__, adc);

  return adc;
}

void adc_exit(struct sec_battery_info *battery)
{
  adc_exit_type(battery);
}

bool sec_bat_check_jig_status(void)
{
#if defined(CONFIG_MACH_AFYONLTE_TMO)
	return check_jig_state();
#elif defined(CONFIG_SEC_MATISSE_PROJECT) || defined(CONFIG_SEC_MILLET_PROJECT)
	return check_sm5502_jig_state();
#else
	return false;
#endif
}
/* callback for battery check
 * return : bool
 * true - battery detected, false battery NOT detected
 */
bool sec_bat_check_callback(struct sec_battery_info *battery)
{
  return true;
}

bool sec_bat_check_cable_result_callback(
    int cable_type)
{
  return true;
}

int sec_bat_check_cable_callback(struct sec_battery_info *battery)
{
  union power_supply_propval value;

  if (battery->pdata->ta_irq_gpio == 0) {
    pr_err("%s: ta_int_gpio is 0 or not assigned yet(cable_type(%d))\n",
      __func__, current_cable_type);
  } else {
    if (battery->wire_status == POWER_SUPPLY_TYPE_BATTERY &&
      !gpio_get_value_cansleep(battery->pdata->ta_irq_gpio)) {
      pr_info("%s : VBUS IN\n", __func__);

      value.intval = POWER_SUPPLY_TYPE_UARTOFF;
      psy_do_property("battery", set, POWER_SUPPLY_PROP_ONLINE, value);
      current_cable_type = POWER_SUPPLY_TYPE_UARTOFF;

      return POWER_SUPPLY_TYPE_UARTOFF;
    }

    if ((battery->wire_status == POWER_SUPPLY_TYPE_UARTOFF ||
      battery->wire_status == POWER_SUPPLY_TYPE_CARDOCK) &&
      gpio_get_value_cansleep(battery->pdata->ta_irq_gpio)) {
      pr_info("%s : VBUS OUT\n", __func__);

      value.intval = POWER_SUPPLY_TYPE_BATTERY;
      psy_do_property("battery", set, POWER_SUPPLY_PROP_ONLINE, value);
      current_cable_type = POWER_SUPPLY_TYPE_BATTERY;

      return POWER_SUPPLY_TYPE_BATTERY;
    }
  }

  return current_cable_type;
}

void board_battery_init(struct platform_device *pdev, struct sec_battery_info *battery)
{
  if ((!battery->pdata->temp_adc_table) &&
    (battery->pdata->thermal_source == SEC_BATTERY_THERMAL_SOURCE_ADC)) {
     pr_info("%s : assign temp adc table\n", __func__);
	 
     battery->pdata->temp_adc_table = temp_table;
     battery->pdata->temp_amb_adc_table = temp_table;

      battery->pdata->temp_adc_table_size = sizeof(temp_table)/sizeof(sec_bat_adc_table_data_t);
      battery->pdata->temp_amb_adc_table_size = sizeof(temp_table)/sizeof(sec_bat_adc_table_data_t);
  }
	
	  
  battery->pdata->event_check = true;
  battery->pdata->temp_high_threshold_event = TEMP_HIGH_THRESHOLD_EVENT;
  battery->pdata->temp_high_recovery_event = TEMP_HIGH_RECOVERY_EVENT;
  battery->pdata->temp_low_threshold_event = TEMP_LOW_THRESHOLD_EVENT;
  battery->pdata->temp_low_recovery_event = TEMP_LOW_RECOVERY_EVENT;
  battery->pdata->temp_high_threshold_normal = TEMP_HIGH_THRESHOLD_NORMAL;
  battery->pdata->temp_high_recovery_normal = TEMP_HIGH_RECOVERY_NORMAL;
  battery->pdata->temp_low_threshold_normal = TEMP_LOW_THRESHOLD_NORMAL;
  battery->pdata->temp_low_recovery_normal = TEMP_LOW_RECOVERY_NORMAL;
  battery->pdata->temp_high_threshold_lpm = TEMP_HIGH_THRESHOLD_LPM;
  battery->pdata->temp_high_recovery_lpm = TEMP_HIGH_RECOVERY_LPM;
  battery->pdata->temp_low_threshold_lpm = TEMP_LOW_THRESHOLD_LPM;
  battery->pdata->temp_low_recovery_lpm = TEMP_LOW_RECOVERY_LPM;

#if defined(CONFIG_MACH_MATISSELTE_ATT) || defined(CONFIG_MACH_MATISSELTE_VZW) || defined(CONFIG_MACH_MILLETLTE_VZW)
  battery->pdata->fuelgauge_name = "sec-fuelgauge";
#endif
#if defined(CONFIG_MACH_MATISSELTE_ATT) || defined(CONFIG_MACH_MATISSELTE_VZW)
battery->pdata->thermal_source = SEC_BATTERY_THERMAL_SOURCE_FG;
#endif
#if defined(CONFIG_MACH_MATISSELTE_ATT)
if(system_rev<=1)
  battery->pdata->temp_check_type = SEC_BATTERY_TEMP_CHECK_NONE;
#endif
  adc_init_type(pdev, battery);
}

void board_fuelgauge_init(struct sec_fuelgauge_info *fuelgauge)
{
  sec_fuelgauge = fuelgauge;

  if (!fuelgauge->pdata->battery_data) {
    pr_info("%s : assign battery data\n", __func__);
      fuelgauge->pdata->battery_data = (void *)samsung_battery_data;
  }

  fuelgauge->pdata->capacity_max = CAPACITY_MAX;
  fuelgauge->pdata->capacity_max_margin = CAPACITY_MAX_MARGIN;
  fuelgauge->pdata->capacity_min = CAPACITY_MIN;

#if defined(CONFIG_FUELGAUGE_MAX17048)
  pr_info("%s: RCOMP0: 0x%x, RCOMP_charging: 0x%x, "
    "temp_cohot: %d, temp_cocold: %d, "
    "is_using_model_data: %d, type_str: %s, "
    "capacity_max: %d, capacity_max_margin: %d, "
    "capacity_min: %d, \n", __func__ ,
    get_battery_data(fuelgauge).RCOMP0,
    get_battery_data(fuelgauge).RCOMP_charging,
    get_battery_data(fuelgauge).temp_cohot,
    get_battery_data(fuelgauge).temp_cocold,
    get_battery_data(fuelgauge).is_using_model_data,
    get_battery_data(fuelgauge).type_str,
    fuelgauge->pdata->capacity_max,
    fuelgauge->pdata->capacity_max_margin,
    fuelgauge->pdata->capacity_min
    );
#endif
}

void cable_initial_check(struct sec_battery_info *battery)
{
  union power_supply_propval value;

  pr_info("%s : current_cable_type : (%d)\n", __func__, current_cable_type);
  if (POWER_SUPPLY_TYPE_BATTERY != current_cable_type) {
    value.intval = current_cable_type;
    psy_do_property("battery", set,
        POWER_SUPPLY_PROP_ONLINE, value);
  } else {
    psy_do_property(battery->pdata->charger_name, get,
        POWER_SUPPLY_PROP_ONLINE, value);
    if (value.intval == POWER_SUPPLY_TYPE_WIRELESS) {
      value.intval = 1;
      psy_do_property("wireless", set,
          POWER_SUPPLY_PROP_ONLINE, value);
    }
  }
}
