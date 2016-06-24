/*
** =========================================================================
** File:
**     tspdrv_drv2604.h
**
** Description:
**     Constants and type definitions for the TouchSense Kernel Module.
**
** Portions Copyright (c) 2008-2010 Immersion Corporation. All Rights Reserved.
**
** This file contains Original Code and/or Modifications of Original Code
** as defined in and that are subject to the GNU Public License v2 -
** (the 'License'). You may not use this file except in compliance with the
** License. You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA or contact
** TouchSenseSales@immersion.com.
**
** The Original Code and all software distributed under the License are
** distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
** EXPRESS OR IMPLIED, AND IMMERSION HEREBY DISCLAIMS ALL SUCH WARRANTIES,
** INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS
** FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. Please see** the License for the specific language governing rights and limitations
** under the License.
** =========================================================================
*/

#ifndef _TSPDRV_H
#define _TSPDRV_H

/* Constants */
#define MODULE_NAME                         "tspdrv"
#define TSPDRV                              "/dev/"MODULE_NAME
#define TSPDRV_MAGIC_NUMBER                 0x494D4D52

#define TSPDRV_IOCTL_GROUP                  0x52
#define TSPDRV_STOP_KERNEL_TIMER            _IO(TSPDRV_IOCTL_GROUP, 1) /* obsolete, may be removed in future */
#define TSPDRV_SET_MAGIC_NUMBER             _IO(TSPDRV_IOCTL_GROUP, 2)
#define TSPDRV_ENABLE_AMP                   _IO(TSPDRV_IOCTL_GROUP, 3)
#define TSPDRV_DISABLE_AMP                  _IO(TSPDRV_IOCTL_GROUP, 4)
#define TSPDRV_GET_NUM_ACTUATORS            _IO(TSPDRV_IOCTL_GROUP, 5)
#define TSPDRV_SET_DEVICE_PARAMETER         _IO(TSPDRV_IOCTL_GROUP, 6)
#define TSPDRV_SET_DBG_LEVEL                _IO(TSPDRV_IOCTL_GROUP, 7)
#define TSPDRV_GET_DBG_LEVEL                _IO(TSPDRV_IOCTL_GROUP, 8)
#define TSPDRV_SET_RUNTIME_RECORD_FLAG      _IO(TSPDRV_IOCTL_GROUP, 9)
#define TSPDRV_GET_RUNTIME_RECORD_FLAG      _IO(TSPDRV_IOCTL_GROUP, 10)
#define TSPDRV_SET_RUNTIME_RECORD_BUF_SIZE  _IO(TSPDRV_IOCTL_GROUP, 11)
#define TSPDRV_GET_RUNTIME_RECORD_BUF_SIZE  _IO(TSPDRV_IOCTL_GROUP, 12)
#define TSPDRV_GET_PARAM_FILE_ID            _IO(TSPDRV_IOCTL_GROUP, 13)
/*
** Frequency constant parameters to control force output values and signals.
*/
#define VIBE_KP_CFG_FREQUENCY_PARAM1        85
#define VIBE_KP_CFG_FREQUENCY_PARAM2        86
#define VIBE_KP_CFG_FREQUENCY_PARAM3        87
#define VIBE_KP_CFG_FREQUENCY_PARAM4        88
#define VIBE_KP_CFG_FREQUENCY_PARAM5        89
#define VIBE_KP_CFG_FREQUENCY_PARAM6        90

/*
** Force update rate in milliseconds.
*/
#define VIBE_KP_CFG_UPDATE_RATE_MS          95

#define VIBE_MAX_DEVICE_NAME_LENGTH         64
#define SPI_HEADER_SIZE                     3   /* DO NOT CHANGE - SPI buffer header size */
#define VIBE_OUTPUT_SAMPLE_SIZE             50  /* DO NOT CHANGE - maximum number of samples */
#define MAX_DEBUG_BUFFER_LENGTH             1024



/* Type definitions */
#ifdef __KERNEL__
typedef int8_t		VibeInt8;
typedef u_int8_t	VibeUInt8;
typedef int16_t		VibeInt16;
typedef u_int16_t	VibeUInt16;
typedef int32_t		VibeInt32;
typedef u_int32_t	VibeUInt32;
typedef u_int8_t	VibeBool;
typedef VibeInt32	VibeStatus;
/* Debug Levels */
#define DBL_TEMP                        0
#define DBL_FATAL                       0
#define DBL_ERROR                       1
#define DBL_WARNING                     2
#define DBL_INFO                        3
#define DBL_VERBOSE                     4
#define DBL_OVERKILL                    5

/* Device parameters sent to the kernel module, tspdrv.ko */
typedef struct
{
    VibeInt32 nDeviceIndex;
    VibeInt32 nDeviceParamID;
    VibeInt32 nDeviceParamValue;
} device_parameter;

#endif

/* Error and Return value codes */
#define VIBE_S_SUCCESS                      0	/* Success */
#define VIBE_E_FAIL						    -4	/* Generic error */


#define VIBRATION_ON            1
#define VIBRATION_OFF           0


#if defined(VIBE_RECORD) && defined(VIBE_DEBUG)
    void _RecorderInit(void);
    void _RecorderTerminate(void);
    void _RecorderReset(int nActuator);
    void _Record(int actuatorIndex, const char *format,...);
#endif

/* Kernel Debug Macros */
#ifdef __KERNEL__
    #ifdef VIBE_DEBUG
        #define DbgOut(_x_) printk _x_
    #else   /* VIBE_DEBUG */
        #define DbgOut(_x_)
    #endif  /* VIBE_DEBUG */

    #if defined(VIBE_RECORD) && defined(VIBE_DEBUG)
        #define DbgRecorderInit(_x_) _RecorderInit _x_
        #define DbgRecorderTerminate(_x_) _RecorderTerminate _x_
        #define DbgRecorderReset(_x_) _RecorderReset _x_
        #define DbgRecord(_x_) _Record _x_
    #else /* defined(VIBE_RECORD) && defined(VIBE_DEBUG) */
        #define DbgRecorderInit(_x_)
        #define DbgRecorderTerminate(_x_)
        #define DbgRecorderReset(_x_)
        #define DbgRecord(_x_)
    #endif /* defined(VIBE_RECORD) && defined(VIBE_DEBUG) */
#endif  /* __KERNEL__ */

/////////////////////////////////////////////////////////////////////////

#define GUARANTEE_AUTOTUNE_BRAKE_TIME  1

/*
** Enable to use DRV2604 EN pin to enter standby mode
*/
#define USE_DRV2604_EN_PIN  1

/*
** Enable to use DRV2604 i2c command to enter standby mode
*/
#define USE_DRV2604_STANDBY 1

/*
** This SPI supports only one actuator.
*/
#define NUM_ACTUATORS 1

/*
** Name of the DRV2604 board
*/
#define DRV2604_BOARD_NAME   "DRV2604L"
#define HAPTIC_I2C_ID				15
/*
** Go
*/
#define GO_REG 0x0C
#define GO     0x01
#define STOP   0x00

/*
** Status
*/
#define STATUS_REG          0x00
#define STATUS_DEFAULT      0x00

#define DIAG_RESULT_MASK    (1 << 3)
#define AUTO_CAL_PASSED     (0 << 3)
#define AUTO_CAL_FAILED     (1 << 3)
#define DIAG_GOOD           (0 << 3)
#define DIAG_BAD            (1 << 3)

#define DEV_ID_MASK (7 << 5)
#define DRV2605 (3 << 5) /* per DRV2604 datasheet */
#define DRV2604 (4 << 5)
#define DRV2605L (7<<5)
#define DRV2604L (6<<5)
/*
** Mode
*/
#define MODE_REG            0x01
#define MODE_STANDBY        0x40
#define MODE_DEVICE_READY   0x00

#define DRV2604_MODE_MASK           0x07
#define MODE_INTERNAL_TRIGGER       0
#define MODE_REAL_TIME_PLAYBACK     5
#define MODE_DIAGNOSTICS            6
#define AUTO_CALIBRATION            7

#define MODE_RESET                  0x80

/*
** Real Time Playback
*/
#define REAL_TIME_PLAYBACK_REG      0x02

/*
** Library Selection
*/
#define LIBRARY_SELECTION_REG       0x03
#define LIBRARY_SELECTION_DEFAULT   0x00

/*
** Waveform Sequencer
*/
#define WAVEFORM_SEQUENCER_REG      0x04
#define WAVEFORM_SEQUENCER_REG2     0x05
#define WAVEFORM_SEQUENCER_REG3     0x06
#define WAVEFORM_SEQUENCER_REG4     0x07
#define WAVEFORM_SEQUENCER_REG5     0x08
#define WAVEFORM_SEQUENCER_REG6     0x09
#define WAVEFORM_SEQUENCER_REG7     0x0A
#define WAVEFORM_SEQUENCER_REG8     0x0B
#define WAVEFORM_SEQUENCER_MAX      8
#define WAVEFORM_SEQUENCER_DEFAULT  0x00

/*
** OverDrive Time Offset
*/
#define OVERDRIVE_TIME_OFFSET_REG  0x0D

/*
** Sustain Time Offset, postive
*/
#define SUSTAIN_TIME_OFFSET_POS_REG 0x0E

/*
** Sustain Time Offset, negative
*/
#define SUSTAIN_TIME_OFFSET_NEG_REG 0x0F

/*
** Brake Time Offset
*/
#define BRAKE_TIME_OFFSET_REG       0x10

/*
** Rated Voltage
*/
#define RATED_VOLTAGE_REG           0x16

/*
** Overdrive Clamp Voltage
*/
#define OVERDRIVE_CLAMP_VOLTAGE_REG 0x17

/*
** Auto Calibrationi Compensation Result
*/
#define AUTO_CALI_RESULT_REG        0x18

/*
** Auto Calibration Back-EMF Result
*/
#define AUTO_CALI_BACK_EMF_RESULT_REG 0x19

/*
** Feedback Control
*/
#define FEEDBACK_CONTROL_REG        0x1A

#define FEEDBACK_CONTROL_BEMF_LRA_GAIN0 0 /* 5x */
#define FEEDBACK_CONTROL_BEMF_LRA_GAIN1 1 /* 10x */
#define FEEDBACK_CONTROL_BEMF_LRA_GAIN2 2 /* 20x */
#define FEEDBACK_CONTROL_BEMF_LRA_GAIN3 3 /* 30x */

#define LOOP_RESPONSE_SLOW      (0 << 2)
#define LOOP_RESPONSE_MEDIUM    (1 << 2) /* default */
#define LOOP_RESPONSE_FAST      (2 << 2)
#define LOOP_RESPONSE_VERY_FAST (3 << 2)

#define FB_BRAKE_FACTOR_1X   (0 << 4) /* 1x */
#define FB_BRAKE_FACTOR_2X   (1 << 4) /* 2x */
#define FB_BRAKE_FACTOR_3X   (2 << 4) /* 3x (default) */
#define FB_BRAKE_FACTOR_4X   (3 << 4) /* 4x */
#define FB_BRAKE_FACTOR_6X   (4 << 4) /* 6x */
#define FB_BRAKE_FACTOR_8X   (5 << 4) /* 8x */
#define FB_BRAKE_FACTOR_16X  (6 << 4) /* 16x */
#define FB_BRAKE_DISABLED    (7 << 4)

#define FEEDBACK_CONTROL_MODE_ERM 0 /* default */
#define FEEDBACK_CONTROL_MODE_LRA (1 << 7)

/*
** Control1
*/
#define Control1_REG            0x1B
#define STARTUP_BOOST_ENABLED   (1 << 7)
#define STARTUP_BOOST_DISABLED  (0 << 7) /* default */

/*
** Control2
*/
#define Control2_REG            0x1C

#define IDISS_TIME_MASK         0x03
#define IDISS_TIME_VERY_SHORT   0
#define IDISS_TIME_SHORT        1
#define IDISS_TIME_MEDIUM       2 /* default */
#define IDISS_TIME_LONG         3

#define BLANKING_TIME_MASK          0x0C
#define BLANKING_TIME_VERY_SHORT    (0 << 2)
#define BLANKING_TIME_SHORT         (1 << 2)
#define BLANKING_TIME_MEDIUM        (2 << 2) /* default */
#define BLANKING_TIME_VERY_LONG     (3 << 2)

#define AUTO_RES_GAIN_MASK         0x30
#define AUTO_RES_GAIN_VERY_LOW     (0 << 4)
#define AUTO_RES_GAIN_LOW          (1 << 4)
#define AUTO_RES_GAIN_MEDIUM       (2 << 4) /* default */
#define AUTO_RES_GAIN_HIGH         (3 << 4)

#define SOFT_BRAKE_MASK            0x40
#define SOFT_BRAKE                 (1 << 6)

#define BIDIR_INPUT_MASK           0x80
#define UNIDIRECT_INPUT            (0 << 7)
#define BIDIRECT_INPUT             (1 << 7) /* default */

/*
** Control3
*/
#define Control3_REG 0x1D

#define ERM_OpenLoop_Enabled (1 << 5)
#define NG_Thresh_1 (1 << 6)
#define NG_Thresh_2 (2 << 6)
#define NG_Thresh_3 (3 << 6)

/*
** Auto Calibration Memory Interface
*/
#define AUTOCAL_MEM_INTERFACE_REG   0x1E

#define AUTOCAL_TIME_150MS          (0 << 4)
#define AUTOCAL_TIME_250MS          (1 << 4)
#define AUTOCAL_TIME_500MS          (2 << 4)
#define AUTOCAL_TIME_1000MS         (3 << 4)

#define SILICON_REVISION_REG        0x3B
#define SILICON_REVISION_MASK       0x07

#define DEFAULT_DRIVE_TIME      0x17

#define MAX_AUTOCALIBRATION_ATTEMPT 2
#define SKIP_AUTOCAL        1
#define GO_BIT_POLL_INTERVAL    15

#define MAX_REVISION_STRING_SIZE 20

#ifndef GPIO_LEVEL_HIGH
#define GPIO_LEVEL_HIGH 1
#endif
#ifndef GPIO_LEVEL_LOW
#define GPIO_LEVEL_LOW 0
#endif

//////////////////////////////////////////

#define DEVICE_NAME "DRV2604L"
#define DRIVER_VERSION "162"

#define EFFECT_LIBRARY LIBRARY_A

/* Commands */
#define HAPTIC_CMDID_PLAY_SINGLE_EFFECT     0x01
#define HAPTIC_CMDID_PLAY_EFFECT_SEQUENCE   0x02
#define HAPTIC_CMDID_PLAY_TIMED_EFFECT      0x03
#define HAPTIC_CMDID_GET_DEV_ID             0x04
#define HAPTIC_CMDID_RUN_DIAG               0x05
#define HAPTIC_CMDID_AUDIOHAPTIC_ENABLE     0x06
#define HAPTIC_CMDID_AUDIOHAPTIC_DISABLE    0x07
#define HAPTIC_CMDID_AUDIOHAPTIC_GETSTATUS  0x08
#define HAPTIC_CMDID_STOP                   0xFF

/* Command size */
#define HAPTIC_CMDSZ_SINGLE_EFFECT     2
#define HAPTIC_CMDSZ_EFFECT_SEQUENCE   9
#define HAPTIC_CMDSZ_TIMED_EFFECT      3
#define HAPTIC_CMDSZ_STOP              1

/*
** Go
*/
#define GO_REG 0x0C
#define GO     0x01
#define STOP   0x00

/*
** Status
*/
#define STATUS_REG          0x00
#define STATUS_DEFAULT      0x00

#define DIAG_RESULT_MASK    (1 << 3)
#define AUTO_CAL_PASSED     (0 << 3)
#define AUTO_CAL_FAILED     (1 << 3)
#define DIAG_GOOD           (0 << 3)
#define DIAG_BAD            (1 << 3)

#define DEV_ID_MASK (7 << 5)
//#define DRV2605 (5 << 5)
#define DRV2604 (4 << 5)

/*
** Mode
*/
#define MODE_REG            0x01
#define MODE_STANDBY        0x40

#define DRV260X_MODE_MASK           0x07
#define MODE_INTERNAL_TRIGGER       0
#define MODE_EXTERNAL_TRIGGER_EDGE  1
#define MODE_EXTERNAL_TRIGGER_LEVEL 2
#define MODE_PWM_OR_ANALOG_INPUT    3
#define MODE_AUDIOHAPTIC            4
#define MODE_REAL_TIME_PLAYBACK     5
#define MODE_DIAGNOSTICS            6
#define AUTO_CALIBRATION            7

#define MODE_STANDBY_MASK           0x40
#define MODE_READY                  1 // default
#define MODE_SOFT_STANDBY           0

#define MODE_RESET                  0x80

/*
** Real Time Playback
*/
#define REAL_TIME_PLAYBACK_REG      0x02

/*
** Library Selection
*/
#define LIBRARY_SELECTION_REG       0x03
#define LIBRARY_SELECTION_DEFAULT   0x00

#define LIBRARY_A 0x01
#define LIBRARY_B 0x02
#define LIBRARY_C 0x03
#define LIBRARY_D 0x04
#define LIBRARY_E 0x05
#define LIBRARY_F 0x06

#define LIBRARY_SELECTION_MASK              0x07
#define LIBRARY_SELECTION_LIBRARY_RAM       0 // default
#define LIBRARY_SELECTION_LIBRARY_OVERDRIVE 1
#define LIBRARY_SELECTION_LIBRARY_40_60     2
#define LIBRARY_SELECTION_LIBRARY_60_80     3
#define LIBRARY_SELECTION_LIBRARY_100_140   4
#define LIBRARY_SELECTION_LIBRARY_140_PLUS  5

#define LIBRARY_SELECTION_HIZ_MASK          0x10
#define LIBRARY_SELECTION_HIZ_EN            1
#define LIBRARY_SELECTION_HIZ_DIS           0

/*
** Waveform Sequencer
*/
#define WAVEFORM_SEQUENCER_REG      0x04
#define WAVEFORM_SEQUENCER_REG2     0x05
#define WAVEFORM_SEQUENCER_REG3     0x06
#define WAVEFORM_SEQUENCER_REG4     0x07
#define WAVEFORM_SEQUENCER_REG5     0x08
#define WAVEFORM_SEQUENCER_REG6     0x09
#define WAVEFORM_SEQUENCER_REG7     0x0A
#define WAVEFORM_SEQUENCER_REG8     0x0B
#define WAVEFORM_SEQUENCER_MAX      8
#define WAVEFORM_SEQUENCER_DEFAULT  0x00

/*
** OverDrive Time Offset
*/
#define OVERDRIVE_TIME_OFFSET_REG  0x0D

/*
** Sustain Time Offset, postive
*/
#define SUSTAIN_TIME_OFFSET_POS_REG 0x0E

/*
** Sustain Time Offset, negative
*/
#define SUSTAIN_TIME_OFFSET_NEG_REG 0x0F

/*
** Brake Time Offset
*/
#define BRAKE_TIME_OFFSET_REG       0x10

/*
** Audio to Haptics Control
*/
#define AUDIO_HAPTICS_CONTROL_REG   0x11

#define AUDIO_HAPTICS_RECT_10MS     (0 << 2)
#define AUDIO_HAPTICS_RECT_20MS     (1 << 2)
#define AUDIO_HAPTICS_RECT_30MS     (2 << 2)
#define AUDIO_HAPTICS_RECT_40MS     (3 << 2)

#define AUDIO_HAPTICS_FILTER_100HZ  0
#define AUDIO_HAPTICS_FILTER_125HZ  1
#define AUDIO_HAPTICS_FILTER_150HZ  2
#define AUDIO_HAPTICS_FILTER_200HZ  3

/*
** Audio to Haptics Minimum Input Level
*/
#define AUDIO_HAPTICS_MIN_INPUT_REG 0x12

/*
** Audio to Haptics Maximum Input Level
*/
#define AUDIO_HAPTICS_MAX_INPUT_REG 0x13

/*
** Audio to Haptics Minimum Output Drive
*/
#define AUDIO_HAPTICS_MIN_OUTPUT_REG 0x14

/*
** Audio to Haptics Maximum Output Drive
*/
#define AUDIO_HAPTICS_MAX_OUTPUT_REG 0x15

/*
** Rated Voltage
*/
#define RATED_VOLTAGE_REG           0x16

/*
** Overdrive Clamp Voltage
*/
#define OVERDRIVE_CLAMP_VOLTAGE_REG 0x17

/*
** Auto Calibrationi Compensation Result
*/
#define AUTO_CALI_RESULT_REG        0x18

/*
** Auto Calibration Back-EMF Result
*/
#define AUTO_CALI_BACK_EMF_RESULT_REG 0x19

/*
** Feedback Control
*/


#if EFFECT_LIBRARY == LIBRARY_A
#define REAL_TIME_PLAYBACK_STRENGTH 0x38 // ~44% of overdrive voltage (open loop)
#elif EFFECT_LIBRARY == LIBRARY_F
#define REAL_TIME_PLAYBACK_STRENGTH LRA_RTP_STRENGTH
#else
#define REAL_TIME_PLAYBACK_STRENGTH 0x7F // 100% of overdrive voltage (open loop)
#endif

#define FEEDBACK_CONTROL_REG        0x1A

#define FEEDBACK_CONTROL_BEMF_ERM_GAIN0 0 // 0.33x
#define FEEDBACK_CONTROL_BEMF_ERM_GAIN1 1 // 1.0x
#define FEEDBACK_CONTROL_BEMF_ERM_GAIN2 2 // 1.8x
#define FEEDBACK_CONTROL_BEMF_ERM_GAIN3 3 // 4.0x

#define FEEDBACK_CONTROL_BEMF_LRA_GAIN0 0 // 5x
#define FEEDBACK_CONTROL_BEMF_LRA_GAIN1 1 // 10x
#define FEEDBACK_CONTROL_BEMF_LRA_GAIN2 2 // 20x
#define FEEDBACK_CONTROL_BEMF_LRA_GAIN3 3 // 30x

#define LOOP_RESPONSE_SLOW      (0 << 2)
#define LOOP_RESPONSE_MEDIUM    (1 << 2) // default
#define LOOP_RESPONSE_FAST      (2 << 2)
#define LOOP_RESPONSE_VERY_FAST (3 << 2)

#define FB_BRAKE_FACTOR_1X   (0 << 4) // 1x
#define FB_BRAKE_FACTOR_2X   (1 << 4) // 2x
#define FB_BRAKE_FACTOR_3X   (2 << 4) // 3x (default)
#define FB_BRAKE_FACTOR_4X   (3 << 4) // 4x
#define FB_BRAKE_FACTOR_6X   (4 << 4) // 6x
#define FB_BRAKE_FACTOR_8X   (5 << 4) // 8x
#define FB_BRAKE_FACTOR_16X  (6 << 4) // 16x
#define FB_BRAKE_DISABLED    (7 << 4)

#define FEEDBACK_CONTROL_MODE_ERM 0 // default
#define FEEDBACK_CONTROL_MODE_LRA (1 << 7)

#define LRA_DRIVE_TIME			0x13
#define LRA_SEMCO1036                   0
#define LRA_SEMCO0934                   1
#define LRA_SELECTION                   LRA_SEMCO1036
#if (LRA_SELECTION == LRA_SEMCO1036)
#define LRA_RATED_VOLTAGE               0x56
#define LRA_OVERDRIVE_CLAMP_VOLTAGE     0x90
#define LRA_RTP_STRENGTH                0x7F // 100% of rated voltage (closed loop)

#elif (LRA_SELECTION == LRA_SEMCO0934)
#define LRA_RATED_VOLTAGE               0x51
#define LRA_OVERDRIVE_CLAMP_VOLTAGE     0x72
#define LRA_RTP_STRENGTH                0x7F // 100% of rated voltage (closed loop)
#endif

/*
** Control1
*/
#define Control1_REG            0x1B

#define STARTUP_BOOST_ENABLED   (1 << 7)
#define STARTUP_BOOST_DISABLED  (0 << 7) // default
#define AC_COUPLE_ENABLED       (1 << 5)
#define AC_COUPLE_DISABLED      (0 << 5) // default

#define DEFAULT_DRIVE_TIME      0x17
#define AUDIOHAPTIC_DRIVE_TIME  0x13

/*
** Control2
*/
#define Control2_REG            0x1C

#define IDISS_TIME_MASK         0x03
#define IDISS_TIME_VERY_SHORT   0
#define IDISS_TIME_SHORT        1
#define IDISS_TIME_MEDIUM       2 // default
#define IDISS_TIME_LONG         3

#define BLANKING_TIME_MASK          0x0C
#define BLANKING_TIME_VERY_SHORT    (0 << 2)
#define BLANKING_TIME_SHORT         (1 << 2)
#define BLANKING_TIME_MEDIUM        (2 << 2) // default
#define BLANKING_TIME_VERY_LONG     (3 << 2)

#define AUTO_RES_GAIN_MASK         0x30
#define AUTO_RES_GAIN_VERY_LOW     (0 << 4)
#define AUTO_RES_GAIN_LOW          (1 << 4)
#define AUTO_RES_GAIN_MEDIUM       (2 << 4) // default
#define AUTO_RES_GAIN_HIGH         (3 << 4)

#define SOFT_BRAKE_MASK            0x40

#define BIDIR_INPUT_MASK           0x80
#define UNIDIRECT_INPUT            (0 << 7)
#define BIDIRECT_INPUT             (1 << 7) // default

/*
** Control3
*/
#define Control3_REG 0x1D

#define INPUT_PWM               (0 << 1) // default
#define INPUT_ANALOG            (1 << 1)
#define ERM_OpenLoop_Enabled    (1 << 5)
#define NG_Thresh_DISABLED      (0 << 6)
#define NG_Thresh_1             (1 << 6)
#define NG_Thresh_2             (2 << 6)
#define NG_Thresh_3             (3 << 6)

/*
** Auto Calibration Memory Interface
*/
#define AUTOCAL_MEM_INTERFACE_REG   0x1E

#define AUTOCAL_TIME_150MS          (0 << 4)
#define AUTOCAL_TIME_250MS          (1 << 4)
#define AUTOCAL_TIME_500MS          (2 << 4)
#define AUTOCAL_TIME_1000MS         (3 << 4)

#define SILICON_REVISION_REG        0x3B
#define SILICON_REVISION_MASK       0x07

#define AUDIO_HAPTICS_MIN_INPUT_VOLTAGE     0x19
#define AUDIO_HAPTICS_MAX_INPUT_VOLTAGE     0x64
#define AUDIO_HAPTICS_MIN_OUTPUT_VOLTAGE    0x19
#define AUDIO_HAPTICS_MAX_OUTPUT_VOLTAGE    0xFF

#define DEFAULT_ERM_AUTOCAL_COMPENSATION    0x14
#define DEFAULT_ERM_AUTOCAL_BACKEMF         0x72

#define DEFAULT_LRA_AUTOCAL_COMPENSATION    0x06
#define DEFAULT_LRA_AUTOCAL_BACKEMF         0xDE

int vibrator_write_register(u8 addr, u8 w_data);

extern struct vibrator_platform_data_drv2604 vibrator_drvdata;
#endif  /* _TSPDRV_H */
