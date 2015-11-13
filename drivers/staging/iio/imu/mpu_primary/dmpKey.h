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
#ifndef DMPKEY_H__
#define DMPKEY_H__

#define KEY_CFG_25                  (0)
#define KEY_CFG_24                  (KEY_CFG_25 + 1)
#define KEY_CFG_26                  (KEY_CFG_24 + 1)
#define KEY_CFG_27                  (KEY_CFG_26 + 1)
#define KEY_CFG_21                  (KEY_CFG_27 + 1)
#define KEY_CFG_20                  (KEY_CFG_21 + 1)
#define KEY_CFG_TAP4                (KEY_CFG_20 + 1)
#define KEY_CFG_TAP5                (KEY_CFG_TAP4 + 1)
#define KEY_CFG_TAP6                (KEY_CFG_TAP5 + 1)
#define KEY_CFG_TAP7                (KEY_CFG_TAP6 + 1)
#define KEY_CFG_TAP0                (KEY_CFG_TAP7 + 1)
#define KEY_CFG_TAP1                (KEY_CFG_TAP0 + 1)
#define KEY_CFG_TAP2                (KEY_CFG_TAP1 + 1)
#define KEY_CFG_TAP3                (KEY_CFG_TAP2 + 1)
#define KEY_CFG_TAP_QUANTIZE        (KEY_CFG_TAP3 + 1)
#define KEY_CFG_TAP_JERK            (KEY_CFG_TAP_QUANTIZE + 1)
#define KEY_CFG_DR_INT              (KEY_CFG_TAP_JERK + 1)
#define KEY_CFG_AUTH                (KEY_CFG_DR_INT + 1)
#define KEY_CFG_TAP_SAVE_ACCB       (KEY_CFG_AUTH + 1)
#define KEY_CFG_TAP_CLEAR_STICKY    (KEY_CFG_TAP_SAVE_ACCB + 1)
#define KEY_CFG_FIFO_ON_EVENT       (KEY_CFG_TAP_CLEAR_STICKY + 1)
#define KEY_FCFG_ACCEL_INPUT        (KEY_CFG_FIFO_ON_EVENT + 1)
#define KEY_FCFG_ACCEL_INIT         (KEY_FCFG_ACCEL_INPUT + 1)
#define KEY_CFG_23                  (KEY_FCFG_ACCEL_INIT + 1)
#define KEY_FCFG_1                  (KEY_CFG_23 + 1)
#define KEY_FCFG_3                  (KEY_FCFG_1 + 1)
#define KEY_FCFG_2                  (KEY_FCFG_3 + 1)
#define KEY_CFG_3D                  (KEY_FCFG_2 + 1)
#define KEY_CFG_3B                  (KEY_CFG_3D + 1)
#define KEY_CFG_3C                  (KEY_CFG_3B + 1)
#define KEY_FCFG_5                  (KEY_CFG_3C + 1)
#define KEY_FCFG_4                  (KEY_FCFG_5 + 1)
#define KEY_FCFG_7                  (KEY_FCFG_4 + 1)
#define KEY_FCFG_FSCALE             (KEY_FCFG_7 + 1)
#define KEY_FCFG_AZ                 (KEY_FCFG_FSCALE + 1)
#define KEY_FCFG_6                  (KEY_FCFG_AZ + 1)
#define KEY_FCFG_LSB4               (KEY_FCFG_6 + 1)
#define KEY_CFG_12                  (KEY_FCFG_LSB4 + 1)
#define KEY_CFG_14                  (KEY_CFG_12 + 1)
#define KEY_CFG_15                  (KEY_CFG_14 + 1)
#define KEY_CFG_16                  (KEY_CFG_15 + 1)
#define KEY_CFG_18                  (KEY_CFG_16 + 1)
#define KEY_CFG_6                   (KEY_CFG_18 + 1)
#define KEY_CFG_7                   (KEY_CFG_6 + 1)
#define KEY_CFG_4                   (KEY_CFG_7 + 1)
#define KEY_CFG_5                   (KEY_CFG_4 + 1)
#define KEY_CFG_2                   (KEY_CFG_5 + 1)
#define KEY_CFG_3                   (KEY_CFG_2 + 1)
#define KEY_CFG_1                   (KEY_CFG_3 + 1)
#define KEY_CFG_EXTERNAL            (KEY_CFG_1 + 1)
#define KEY_CFG_8                   (KEY_CFG_EXTERNAL + 1)
#define KEY_CFG_9                   (KEY_CFG_8 + 1)
#define KEY_CFG_ORIENT_3            (KEY_CFG_9 + 1)
#define KEY_CFG_ORIENT_2            (KEY_CFG_ORIENT_3 + 1)
#define KEY_CFG_ORIENT_1            (KEY_CFG_ORIENT_2 + 1)
#define KEY_CFG_GYRO_SOURCE         (KEY_CFG_ORIENT_1 + 1)
#define KEY_CFG_ORIENT_IRQ_1        (KEY_CFG_GYRO_SOURCE + 1)
#define KEY_CFG_ORIENT_IRQ_2        (KEY_CFG_ORIENT_IRQ_1 + 1)
#define KEY_CFG_ORIENT_IRQ_3        (KEY_CFG_ORIENT_IRQ_2 + 1)
#define KEY_FCFG_MAG_VAL            (KEY_CFG_ORIENT_IRQ_3 + 1)
#define KEY_FCFG_MAG_MOV            (KEY_FCFG_MAG_VAL + 1)
#define KEY_CFG_LP_QUAT             (KEY_FCFG_MAG_MOV + 1)
#define KEY_CFG_GYRO_RAW_DATA       (KEY_CFG_LP_QUAT + 1)
#define KEY_CFG_EXT_GYRO_BIAS       (KEY_CFG_GYRO_RAW_DATA + 1)
#define KEY_CFG_EXT_GYRO_BIAS_X     (KEY_CFG_EXT_GYRO_BIAS + 1)
#define KEY_CFG_EXT_GYRO_BIAS_Y     (KEY_CFG_EXT_GYRO_BIAS_X + 1)
#define KEY_CFG_EXT_GYRO_BIAS_Z     (KEY_CFG_EXT_GYRO_BIAS_Y + 1)
#define KEY_bad_compass				(KEY_CFG_EXT_GYRO_BIAS_Z + 1)
#define KEY_COMPASS_CHG_SENSITIVITY (KEY_bad_compass + 1)
#define KEY_CCS_HEADING_THLD        (KEY_COMPASS_CHG_SENSITIVITY + 1)
#define KEY_CCS_TIME_THLD           (KEY_CCS_HEADING_THLD + 1)
#define KEY_CCS_DOTP_THLD           (KEY_CCS_TIME_THLD + 1)
#define KEY_CCS_COMP_CNTR           (KEY_CCS_DOTP_THLD + 1)
#define KEY_CFG_NM_DET              (KEY_CCS_COMP_CNTR + 1)
#define KEY_SMD_ENABLE              (KEY_CFG_NM_DET + 1)
#define KEY_SMD_ACCEL_THLD          (KEY_SMD_ENABLE + 1)
#define KEY_SMD_DELAY_THLD          (KEY_SMD_ACCEL_THLD + 1)
#define KEY_SMD_DELAY2_THLD         (KEY_SMD_DELAY_THLD + 1)
#define KEY_SMD_ENABLE_TESTPT1      (KEY_SMD_DELAY2_THLD + 1)
#define KEY_SMD_ENABLE_TESTPT2      (KEY_SMD_ENABLE_TESTPT1 + 1)
#define KEY_SMD_EXE_STATE           (KEY_SMD_ENABLE_TESTPT2 + 1)
#define KEY_SMD_DELAY_CNTR          (KEY_SMD_EXE_STATE + 1)

#define KEY_INV_BREAK (81)
#if KEY_SMD_DELAY_CNTR != KEY_INV_BREAK
#error
#endif

/* MPU6050 keys */
#define KEY_CFG_ACCEL_FILTER        (KEY_INV_BREAK + 1)
#define KEY_CFG_MOTION_BIAS         (KEY_CFG_ACCEL_FILTER + 1)
#define KEY_TEMPLABEL               (KEY_CFG_MOTION_BIAS + 1)

#define KEY_D_0_22                  (KEY_TEMPLABEL + 1)
#define KEY_D_0_104                 (KEY_D_0_22 + 1)

#define KEY_DMP_PREVPTAT            (KEY_D_0_104 + 1)
#define KEY_D_1_74                  (KEY_DMP_PREVPTAT + 1)
#define KEY_D_1_232                 (KEY_D_1_74 + 1)
#define KEY_D_1_250                 (KEY_D_1_232 + 1)
#define KEY_D_2_12                  (KEY_D_1_250 + 1)
#define KEY_FLICK_MSG               (KEY_D_2_12 + 1)
#define KEY_FLICK_COUNTER           (KEY_FLICK_MSG + 1)
#define KEY_FLICK_LOWER             (KEY_FLICK_COUNTER + 1)
#define KEY_FLICK_UPPER             (KEY_FLICK_LOWER + 1)
#define KEY_CGNOTICE_INTR           (KEY_FLICK_UPPER + 1)

#define KEY_D_GYRO_BIAS_X               (KEY_CGNOTICE_INTR + 1)
#define KEY_D_GYRO_BIAS_Y               (KEY_D_GYRO_BIAS_X + 1)
#define KEY_D_GYRO_BIAS_Z               (KEY_D_GYRO_BIAS_Y + 1)
#define KEY_D_ACC_BIAS_X                (KEY_D_GYRO_BIAS_Z + 1)
#define KEY_D_ACC_BIAS_Y                (KEY_D_ACC_BIAS_X + 1)
#define KEY_D_ACC_BIAS_Z                (KEY_D_ACC_BIAS_Y + 1)
#define KEY_D_OUTPUT_ENABLE             (KEY_D_ACC_BIAS_Z + 1)
#define KEY_D_ACCEL_CNTR                (KEY_D_OUTPUT_ENABLE + 1)
#define KEY_D_GYRO_CNTR                 (KEY_D_ACCEL_CNTR + 1)
#define KEY_D_QUAT0_CNTR                (KEY_D_GYRO_CNTR + 1)
#define KEY_D_QUAT1_CNTR                (KEY_D_QUAT0_CNTR + 1)
#define KEY_D_QUAT2_CNTR                (KEY_D_QUAT1_CNTR + 1)
#define KEY_D_CR_TIME_G                 (KEY_D_QUAT2_CNTR + 1)
#define KEY_D_CR_TIME_A                 (KEY_D_CR_TIME_G + 1)
#define KEY_D_CR_TIME_Q                 (KEY_D_CR_TIME_A + 1)
#define KEY_D_CS_TAX                    (KEY_D_CR_TIME_Q + 1)
#define KEY_D_CS_TAY                    (KEY_D_CS_TAX + 1)
#define KEY_D_CS_TAZ                    (KEY_D_CS_TAY + 1)
#define KEY_D_CS_TGX                    (KEY_D_CS_TAZ + 1)
#define KEY_D_CS_TGY                    (KEY_D_CS_TGX + 1)
#define KEY_D_CS_TGZ                    (KEY_D_CS_TGY + 1)
#define KEY_D_CS_TQ0                    (KEY_D_CS_TGZ + 1)
#define KEY_D_CS_TQ1                    (KEY_D_CS_TQ0 + 1)
#define KEY_D_CS_TQ2                    (KEY_D_CS_TQ1 + 1)
#define KEY_D_CS_TQ3                    (KEY_D_CS_TQ2 + 1)

/* Compass keys */
#define KEY_CPASS_GAIN              (KEY_D_CS_TQ3 + 1)
#define KEY_CPASS_BIAS_X            (KEY_CPASS_GAIN + 1)
#define KEY_CPASS_BIAS_Y            (KEY_CPASS_BIAS_X + 1)
#define KEY_CPASS_BIAS_Z            (KEY_CPASS_BIAS_Y + 1)
#define KEY_CPASS_MTX_00            (KEY_CPASS_BIAS_Z + 1)
#define KEY_CPASS_MTX_01            (KEY_CPASS_MTX_00 + 1)
#define KEY_CPASS_MTX_02            (KEY_CPASS_MTX_01 + 1)
#define KEY_CPASS_MTX_10            (KEY_CPASS_MTX_02 + 1)
#define KEY_CPASS_MTX_11            (KEY_CPASS_MTX_10 + 1)
#define KEY_CPASS_MTX_12            (KEY_CPASS_MTX_11 + 1)
#define KEY_CPASS_MTX_20            (KEY_CPASS_MTX_12 + 1)
#define KEY_CPASS_MTX_21            (KEY_CPASS_MTX_20 + 1)
#define KEY_CPASS_MTX_22            (KEY_CPASS_MTX_21 + 1)
#define KEY_CPASS_STATUS_CHK		(KEY_CPASS_MTX_22 + 1)
/* LCD Position Detection Keys */
#define KEY_CFG_LCD_UP_DOWN_INT			(KEY_CPASS_STATUS_CHK + 1)
#define KEY_LCD_UP_DOWN_ENABLE			(KEY_CFG_LCD_UP_DOWN_INT + 1)
#define KEY_LCD_TIME_THRESH			(KEY_LCD_UP_DOWN_ENABLE + 1)
#define KEY_LCD_UP_X_THRESH			(KEY_LCD_TIME_THRESH + 1)
#define KEY_LCD_UP_Y_THRESH			(KEY_LCD_UP_X_THRESH + 1)
#define KEY_LCD_UP_Z_THRESH			(KEY_LCD_UP_Y_THRESH + 1)
#define KEY_LCD_DOWN_X_THRESH			(KEY_LCD_UP_Z_THRESH + 1)
#define KEY_LCD_DOWN_Y_THRESH			(KEY_LCD_DOWN_X_THRESH + 1)
#define KEY_LCD_DOWN_Z_THRESH			(KEY_LCD_DOWN_Y_THRESH + 1)
#define KEY_LCD_STATUS				(KEY_LCD_DOWN_Z_THRESH + 1)

/* QShot Keys */
#define KEY_CFG_QSHOT_START_INT		(KEY_LCD_STATUS + 1)
#define KEY_CFG_QSHOT_FINISH_INT	(KEY_CFG_QSHOT_START_INT + 1)
#define KEY_D_QSHOT_START_ANGLE		(KEY_CFG_QSHOT_FINISH_INT + 1)
#define KEY_D_QSHOT_FINISH_ANGLE	(KEY_D_QSHOT_START_ANGLE + 1)


#define KEY_CFG_DISPLAY_ORIENT_INT  (KEY_D_QSHOT_FINISH_ANGLE + 1)
#define KEY_NO_ORIENT_INTERRUPT     (KEY_CFG_DISPLAY_ORIENT_INT + 1)
#define KEY_X_GRT_Y_TMP2            (KEY_NO_ORIENT_INTERRUPT + 1)

/*Shake Keys */
#define KEY_D_0_64                  (KEY_X_GRT_Y_TMP2 + 1)
#define KEY_D_2_4                   (KEY_D_0_64 + 1)
#define KEY_D_2_8                   (KEY_D_2_4 + 1)
#define KEY_D_2_48                  (KEY_D_2_8 + 1)
#define KEY_D_2_92                  (KEY_D_2_48 + 1)
#define KEY_D_2_94                  (KEY_D_2_92 + 1)
#define KEY_D_2_160                 (KEY_D_2_94 + 1)
#define KEY_D_3_180                 (KEY_D_2_160 + 1)
#define KEY_D_3_184                 (KEY_D_3_180 + 1)
#define KEY_D_3_188                 (KEY_D_3_184 + 1)
#define KEY_D_3_208                 (KEY_D_3_188 + 1)
#define KEY_D_3_240                 (KEY_D_3_208 + 1)
#define KEY_RETRACTION_1            (KEY_D_3_240 + 1)
#define KEY_RETRACTION_2            (KEY_RETRACTION_1 + 1)
#define KEY_RETRACTION_3            (KEY_RETRACTION_2 + 1)
#define KEY_RETRACTION_4            (KEY_RETRACTION_3 + 1)
#define KEY_CFG_SHAKE_INT           (KEY_RETRACTION_4 + 1)

/* Authenticate Keys */
#define KEY_D_AUTH_OUT              (KEY_CFG_SHAKE_INT + 1)
#define KEY_D_AUTH_IN               (KEY_D_AUTH_OUT + 1)
#define KEY_D_AUTH_A                (KEY_D_AUTH_IN + 1)
#define KEY_D_AUTH_B                (KEY_D_AUTH_A + 1)

/* Pedometer standalone only keys */
#define KEY_D_PEDSTD_BP_B           (KEY_D_AUTH_B + 1)
#define KEY_D_PEDSTD_HP_A           (KEY_D_PEDSTD_BP_B + 1)
#define KEY_D_PEDSTD_HP_B           (KEY_D_PEDSTD_HP_A + 1)
#define KEY_D_PEDSTD_BP_A4          (KEY_D_PEDSTD_HP_B + 1)
#define KEY_D_PEDSTD_BP_A3          (KEY_D_PEDSTD_BP_A4 + 1)
#define KEY_D_PEDSTD_BP_A2          (KEY_D_PEDSTD_BP_A3 + 1)
#define KEY_D_PEDSTD_BP_A1          (KEY_D_PEDSTD_BP_A2 + 1)
#define KEY_D_PEDSTD_INT_THRSH      (KEY_D_PEDSTD_BP_A1 + 1)
#define KEY_D_PEDSTD_CLIP           (KEY_D_PEDSTD_INT_THRSH + 1)
#define KEY_D_PEDSTD_SB             (KEY_D_PEDSTD_CLIP + 1)
#define KEY_D_PEDSTD_SB_TIME        (KEY_D_PEDSTD_SB + 1)
#define KEY_D_PEDSTD_PEAKTHRSH      (KEY_D_PEDSTD_SB_TIME + 1)
#define KEY_D_PEDSTD_TIML           (KEY_D_PEDSTD_PEAKTHRSH + 1)
#define KEY_D_PEDSTD_TIMH           (KEY_D_PEDSTD_TIML + 1)
#define KEY_D_PEDSTD_PEAK           (KEY_D_PEDSTD_TIMH + 1)
#define KEY_D_PEDSTD_TIMECTR        (KEY_D_PEDSTD_PEAK + 1)
#define KEY_D_PEDSTD_STEPCTR        (KEY_D_PEDSTD_TIMECTR + 1)
#define KEY_D_PEDSTD_STEPCTR2		(KEY_D_PEDSTD_STEPCTR + 1)
#define KEY_D_PEDSTD_WALKTIME       (KEY_D_PEDSTD_STEPCTR2 + 1)
#define KEY_D_PEDSTD_DECI           (KEY_D_PEDSTD_WALKTIME + 1)
#define KEY_D_PEDSTD_SB2			(KEY_D_PEDSTD_DECI + 1)
#define KEY_D_PEDSTD_DRIVE_STATE    (KEY_D_PEDSTD_SB2 + 1)
#define KEY_CFG_PED_INT             (KEY_D_PEDSTD_DRIVE_STATE + 1)
#define KEY_CFG_PED_ENABLE          (KEY_CFG_PED_INT + 1)
#define KEY_D_STPDET_TIMESTAMP      (KEY_CFG_PED_ENABLE + 1)

#define KEY_D_S_HEALTH_WALK_RUN_1   (KEY_D_STPDET_TIMESTAMP + 1)
#define KEY_D_S_HEALTH_WALK_RUN_2   (KEY_D_S_HEALTH_WALK_RUN_1 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_3   (KEY_D_S_HEALTH_WALK_RUN_2 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_4   (KEY_D_S_HEALTH_WALK_RUN_3 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_5   (KEY_D_S_HEALTH_WALK_RUN_4 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_6   (KEY_D_S_HEALTH_WALK_RUN_5 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_7   (KEY_D_S_HEALTH_WALK_RUN_6 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_8   (KEY_D_S_HEALTH_WALK_RUN_7 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_9   (KEY_D_S_HEALTH_WALK_RUN_8 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_10  (KEY_D_S_HEALTH_WALK_RUN_9 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_11  (KEY_D_S_HEALTH_WALK_RUN_10 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_12  (KEY_D_S_HEALTH_WALK_RUN_11 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_13  (KEY_D_S_HEALTH_WALK_RUN_12 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_14  (KEY_D_S_HEALTH_WALK_RUN_13 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_15  (KEY_D_S_HEALTH_WALK_RUN_14 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_16  (KEY_D_S_HEALTH_WALK_RUN_15 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_17  (KEY_D_S_HEALTH_WALK_RUN_16 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_18  (KEY_D_S_HEALTH_WALK_RUN_17 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_19  (KEY_D_S_HEALTH_WALK_RUN_18 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_20  (KEY_D_S_HEALTH_WALK_RUN_19 + 1)
#define KEY_D_S_HEALTH_WALK_RUN_21   (KEY_D_S_HEALTH_WALK_RUN_20 + 1)
#define KEY_D_S_HEALTH_CADENCE1     (KEY_D_S_HEALTH_WALK_RUN_21 + 1)
#define KEY_D_S_HEALTH_CADENCE2     (KEY_D_S_HEALTH_CADENCE1 + 1)
#define KEY_D_S_HEALTH_CADENCE3     (KEY_D_S_HEALTH_CADENCE2 + 1)
#define KEY_D_S_HEALTH_CADENCE4     (KEY_D_S_HEALTH_CADENCE3 + 1)
#define KEY_D_S_HEALTH_CADENCE5     (KEY_D_S_HEALTH_CADENCE4 + 1)
#define KEY_D_S_HEALTH_CADENCE6     (KEY_D_S_HEALTH_CADENCE5 + 1)
#define KEY_D_S_HEALTH_CADENCE7     (KEY_D_S_HEALTH_CADENCE6 + 1)
#define KEY_D_S_HEALTH_CADENCE8     (KEY_D_S_HEALTH_CADENCE7 + 1)
#define KEY_D_S_HEALTH_CADENCE9     (KEY_D_S_HEALTH_CADENCE8 + 1)
#define KEY_D_S_HEALTH_CADENCE10    (KEY_D_S_HEALTH_CADENCE9 + 1)
#define KEY_D_S_HEALTH_CADENCE11    (KEY_D_S_HEALTH_CADENCE10 + 1)
#define KEY_D_S_HEALTH_CADENCE12    (KEY_D_S_HEALTH_CADENCE11 + 1)
#define KEY_D_S_HEALTH_CADENCE13    (KEY_D_S_HEALTH_CADENCE12 + 1)
#define KEY_D_S_HEALTH_CADENCE14    (KEY_D_S_HEALTH_CADENCE13 + 1)
#define KEY_D_S_HEALTH_CADENCE15    (KEY_D_S_HEALTH_CADENCE14 + 1)
#define KEY_D_S_HEALTH_CADENCE16    (KEY_D_S_HEALTH_CADENCE15 + 1)
#define KEY_D_S_HEALTH_CADENCE17    (KEY_D_S_HEALTH_CADENCE16 + 1)
#define KEY_D_S_HEALTH_CADENCE18    (KEY_D_S_HEALTH_CADENCE17 + 1)
#define KEY_D_S_HEALTH_CADENCE19    (KEY_D_S_HEALTH_CADENCE18 + 1)
#define KEY_D_S_HEALTH_CADENCE20    (KEY_D_S_HEALTH_CADENCE19 + 1)
#define KEY_D_S_HEALTH_CADENCE21     (KEY_D_S_HEALTH_CADENCE20 + 1)

#define KEY_CFG_S_HEALTH_INT        (KEY_D_S_HEALTH_CADENCE21 + 1)
#define KEY_S_HEALTH_INT_PERIOD     (KEY_CFG_S_HEALTH_INT + 1)
#define KEY_S_HEALTH_INT_PERIOD2    (KEY_S_HEALTH_INT_PERIOD + 1)
#define KEY_S_HEALTH_MIN_CNTR	(KEY_S_HEALTH_INT_PERIOD2 + 1)
#define KEY_S_HEALTH_MIN_CONST	(KEY_S_HEALTH_MIN_CNTR + 1)
#define KEY_S_HEALTH_STEP_CNT	(KEY_S_HEALTH_MIN_CONST + 1)
#define KEY_S_HEALTH_STEP_CNT_P	(KEY_S_HEALTH_STEP_CNT + 1)
#define KEY_S_HEALTH_FREQ_TH        (KEY_S_HEALTH_STEP_CNT_P + 1)
#define KEY_S_HEALTH_ALPHA1         (KEY_S_HEALTH_FREQ_TH + 1)
#define KEY_S_HEALTH_ALPHA2         (KEY_S_HEALTH_ALPHA1 + 1)

/*Host Based No Motion*/
#define KEY_D_HOST_NO_MOT           (KEY_S_HEALTH_FREQ_TH + 1)

/*Host Based Accel Bias*/
#define KEY_D_ACCEL_BIAS            (KEY_D_HOST_NO_MOT + 1)

/*Screen/Display Orientation Keys*/
#define KEY_D_ORIENT_GAP            (KEY_D_ACCEL_BIAS + 1)
#define KEY_D_TILT0_H               (KEY_D_ORIENT_GAP + 1)
#define KEY_D_TILT0_L               (KEY_D_TILT0_H + 1)
#define KEY_D_TILT1_H               (KEY_D_TILT0_L + 1)
#define KEY_D_TILT1_L               (KEY_D_TILT1_H + 1)
#define KEY_D_TILT2_H               (KEY_D_TILT1_L + 1)
#define KEY_D_TILT2_L               (KEY_D_TILT2_H  + 1)
#define KEY_D_TILT3_H               (KEY_D_TILT2_L + 1)
#define KEY_D_TILT3_L               (KEY_D_TILT3_H + 1)

#define KEY_STREAM_P_ACCEL_Z        (KEY_D_TILT3_L + 1)

/* Batch mode */
#define KEY_BM_ENABLE               (KEY_STREAM_P_ACCEL_Z + 1)
#define KEY_BM_BATCH_THLD           (KEY_BM_ENABLE + 1)
#define KEY_BM_BATCH_CNTR           (KEY_BM_BATCH_THLD + 1)
#define KEY_BM_NUMWORD_TOFILL       (KEY_BM_BATCH_CNTR + 1)

/* Watermark */
#define KEY_CFG_WATERMARK_H         (KEY_BM_NUMWORD_TOFILL + 1)
#define KEY_CFG_WATERMARK_L         (KEY_CFG_WATERMARK_H + 1)

/* FIFO output control */
#define KEY_CFG_OUT_ACCL            (KEY_CFG_WATERMARK_L + 1)
#define KEY_CFG_OUT_GYRO            (KEY_CFG_OUT_ACCL + 1)
#define KEY_CFG_OUT_3QUAT           (KEY_CFG_OUT_GYRO + 1)
#define KEY_CFG_OUT_6QUAT           (KEY_CFG_OUT_3QUAT + 1)
#define KEY_CFG_OUT_9QUAT           (KEY_CFG_OUT_6QUAT + 1)
#define KEY_CFG_OUT_PQUAT           (KEY_CFG_OUT_9QUAT + 1)
#define KEY_CFG_OUT_PQUAT9          (KEY_CFG_OUT_PQUAT + 1)
#define KEY_CFG_OUT_CPASS           (KEY_CFG_OUT_PQUAT9 + 1)
#define KEY_CFG_OUT_PRESS           (KEY_CFG_OUT_CPASS + 1)
#define KEY_CFG_OUT_STEPDET         (KEY_CFG_OUT_PRESS + 1)
#define KEY_CFG_FIFO_INT            (KEY_CFG_OUT_STEPDET + 1)

/* Ped Step detection */
#define KEY_CFG_PEDSTEP_DET         (KEY_CFG_FIFO_INT + 1)

/* Screen Orientation data */
#define KEY_SO_DATA                 (KEY_CFG_PEDSTEP_DET + 1)

/* MPU for DMP Android K */
#define KEY_P_INIT                  (KEY_SO_DATA + 1)
#define KEY_P_HW_ID                 (KEY_P_INIT + 1)

/* DMP running counter */
#define KEY_DMP_RUN_CNTR            (KEY_P_HW_ID + 1)

/* Sensor's ODR */
#define KEY_CFG_3QUAT_ODR           (KEY_DMP_RUN_CNTR + 1)
#define KEY_CFG_6QUAT_ODR           (KEY_CFG_3QUAT_ODR + 1)
#define KEY_CFG_9QUAT_ODR           (KEY_CFG_6QUAT_ODR + 1)
#define KEY_CFG_PQUAT6_ODR          (KEY_CFG_9QUAT_ODR + 1)
#define KEY_CFG_PQUAT9_ODR          (KEY_CFG_PQUAT6_ODR + 1)
#define KEY_CFG_ACCL_ODR            (KEY_CFG_PQUAT9_ODR + 1)
#define KEY_CFG_GYRO_ODR            (KEY_CFG_ACCL_ODR + 1)
#define KEY_CFG_CPASS_ODR           (KEY_CFG_GYRO_ODR + 1)
#define KEY_CFG_PRESS_ODR           (KEY_CFG_CPASS_ODR + 1)

#define KEY_ODR_CNTR_3QUAT          (KEY_CFG_PRESS_ODR + 1)
#define KEY_ODR_CNTR_6QUAT          (KEY_ODR_CNTR_3QUAT + 1)
#define KEY_ODR_CNTR_9QUAT          (KEY_ODR_CNTR_6QUAT + 1)
#define KEY_ODR_CNTR_PQUAT          (KEY_ODR_CNTR_9QUAT + 1)
#define KEY_ODR_CNTR_PQUAT9         (KEY_ODR_CNTR_PQUAT + 1)
#define KEY_ODR_CNTR_ACCL           (KEY_ODR_CNTR_PQUAT9 + 1)
#define KEY_ODR_CNTR_GYRO           (KEY_ODR_CNTR_ACCL + 1)
#define KEY_ODR_CNTR_CPASS          (KEY_ODR_CNTR_GYRO + 1)
#define KEY_ODR_CNTR_PRESS          (KEY_ODR_CNTR_CPASS + 1)

/* DMP fusion LP-Quat */
#define KEY_DMP_LPQ0                (KEY_ODR_CNTR_PRESS + 1)
#define KEY_DMP_LPQ1                (KEY_DMP_LPQ0 + 1)
#define KEY_DMP_LPQ2                (KEY_DMP_LPQ1 + 1)
#define KEY_DMP_LPQ3                (KEY_DMP_LPQ2 + 1)

/* DMP fusion 6-axis Quat */
#define KEY_CFG_FB_GAIN_GYRO_ON		(KEY_DMP_LPQ3 + 1)
#define KEY_DMP_Q0                  (KEY_CFG_FB_GAIN_GYRO_ON + 1)
#define KEY_DMP_Q1                  (KEY_DMP_Q0 + 1)
#define KEY_DMP_Q2                  (KEY_DMP_Q1 + 1)
#define KEY_DMP_Q3                  (KEY_DMP_Q2 + 1)

/* 9-axis fusion */
#define KEY_CPASS_VALID             (KEY_DMP_Q3 + 1)
#define KEY_9AXIS_ACCURACY          (KEY_CPASS_VALID + 1)
#define KEY_DMP_9Q0                 (KEY_9AXIS_ACCURACY + 1)
#define KEY_DMP_9Q1                 (KEY_DMP_9Q0 + 1)
#define KEY_DMP_9Q2                 (KEY_DMP_9Q1 + 1)
#define KEY_DMP_9Q3                 (KEY_DMP_9Q2 + 1)

#define NUM_KEYS                    (KEY_DMP_9Q3 + 1)

struct tKeyLabel  {
	unsigned short key;
	unsigned short addr;
};

#define DINA0A 0x0a
#define DINA22 0x22
#define DINA42 0x42
#define DINA5A 0x5a

#define DINA06 0x06
#define DINA0E 0x0e
#define DINA16 0x16
#define DINA1E 0x1e
#define DINA26 0x26
#define DINA2E 0x2e
#define DINA36 0x36
#define DINA3E 0x3e
#define DINA46 0x46
#define DINA4E 0x4e
#define DINA56 0x56
#define DINA5E 0x5e
#define DINA66 0x66
#define DINA6E 0x6e
#define DINA76 0x76
#define DINA7E 0x7e

#define DINA00 0x00
#define DINA08 0x08
#define DINA10 0x10
#define DINA18 0x18
#define DINA20 0x20
#define DINA28 0x28
#define DINA30 0x30
#define DINA38 0x38
#define DINA40 0x40
#define DINA48 0x48
#define DINA50 0x50
#define DINA58 0x58
#define DINA60 0x60
#define DINA68 0x68
#define DINA70 0x70
#define DINA78 0x78

#define DINA04 0x04
#define DINA0C 0x0c
#define DINA14 0x14
#define DINA1C 0x1C
#define DINA24 0x24
#define DINA2C 0x2c
#define DINA34 0x34
#define DINA3C 0x3c
#define DINA44 0x44
#define DINA4C 0x4c
#define DINA54 0x54
#define DINA5C 0x5c
#define DINA64 0x64
#define DINA6C 0x6c
#define DINA74 0x74
#define DINA7C 0x7c

#define DINA01 0x01
#define DINA09 0x09
#define DINA11 0x11
#define DINA19 0x19
#define DINA21 0x21
#define DINA29 0x29
#define DINA31 0x31
#define DINA39 0x39
#define DINA41 0x41
#define DINA49 0x49
#define DINA51 0x51
#define DINA59 0x59
#define DINA61 0x61
#define DINA69 0x69
#define DINA71 0x71
#define DINA79 0x79

#define DINA25 0x25
#define DINA2D 0x2d
#define DINA35 0x35
#define DINA3D 0x3d
#define DINA4D 0x4d
#define DINA55 0x55
#define DINA5D 0x5D
#define DINA6D 0x6d
#define DINA75 0x75
#define DINA7D 0x7d

#define DINADC 0xdc
#define DINAF2 0xf2
#define DINAAB 0xab
#define DINAAA 0xaa
#define DINAF1 0xf1
#define DINADF 0xdf
#define DINADA 0xda
#define DINAB1 0xb1
#define DINAB9 0xb9
#define DINAF3 0xf3
#define DINA8B 0x8b
#define DINAA3 0xa3
#define DINA91 0x91
#define DINAB6 0xb6
#define DINAB4 0xb4

#define DINC00 0x00
#define DINC01 0x01
#define DINC02 0x02
#define DINC03 0x03
#define DINC08 0x08
#define DINC09 0x09
#define DINC0A 0x0a
#define DINC0B 0x0b
#define DINC10 0x10
#define DINC11 0x11
#define DINC12 0x12
#define DINC13 0x13
#define DINC18 0x18
#define DINC19 0x19
#define DINC1A 0x1a
#define DINC1B 0x1b

#define DINC20 0x20
#define DINC21 0x21
#define DINC22 0x22
#define DINC23 0x23
#define DINC28 0x28
#define DINC29 0x29
#define DINC2A 0x2a
#define DINC2B 0x2b
#define DINC30 0x30
#define DINC31 0x31
#define DINC32 0x32
#define DINC33 0x33
#define DINC38 0x38
#define DINC39 0x39
#define DINC3A 0x3a
#define DINC3B 0x3b

#define DINC40 0x40
#define DINC41 0x41
#define DINC42 0x42
#define DINC43 0x43
#define DINC48 0x48
#define DINC49 0x49
#define DINC4A 0x4a
#define DINC4B 0x4b
#define DINC50 0x50
#define DINC51 0x51
#define DINC52 0x52
#define DINC53 0x53
#define DINC58 0x58
#define DINC59 0x59
#define DINC5A 0x5a
#define DINC5B 0x5b

#define DINC60 0x60
#define DINC61 0x61
#define DINC62 0x62
#define DINC63 0x63
#define DINC68 0x68
#define DINC69 0x69
#define DINC6A 0x6a
#define DINC6B 0x6b
#define DINC70 0x70
#define DINC71 0x71
#define DINC72 0x72
#define DINC73 0x73
#define DINC78 0x78
#define DINC79 0x79
#define DINC7A 0x7a
#define DINC7B 0x7b
#define DIND40 0x40
#define DINA80 0x80
#define DINA90 0x90
#define DINAA0 0xa0
#define DINAC9 0xc9
#define DINACB 0xcb
#define DINACD 0xcd
#define DINACF 0xcf
#define DINAC8 0xc8
#define DINACA 0xca
#define DINACC 0xcc
#define DINACE 0xce
#define DINAD8 0xd8
#define DINADD 0xdd
#define DINAF8 0xf0
#define DINAFE 0xfe

#define DINBF8 0xf8
#define DINAC0 0xb0
#define DINAC1 0xb1
#define DINAC2 0xb4
#define DINAC3 0xb5
#define DINAC4 0xb8
#define DINAC5 0xb9
#define DINBC0 0xc0
#define DINBC2 0xc2
#define DINBC4 0xc4
#define DINBC6 0xc6

#endif
