/*
** =========================================================================
** File:
**     tspdrv_isa1200.h
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

#include <mach/msm_iomap.h>

/* Constants */
#define MODULE_NAME                         "tspdrv"
#define TSPDRV                              "/dev/"MODULE_NAME
#define TSPDRV_MAGIC_NUMBER                 0x494D4D52
#define TSPDRV_STOP_KERNEL_TIMER            _IO(TSPDRV_MAGIC_NUMBER & 0xFF, 1)
/*
 ** Obsolete IOCTL command
 ** #define TSPDRV_IDENTIFY_CALLER           _IO(TSPDRV_MAGIC_NUMBER & 0xFF, 2)
*/
#define TSPDRV_ENABLE_AMP                   _IO(TSPDRV_MAGIC_NUMBER & 0xFF, 3)
#define TSPDRV_DISABLE_AMP                  _IO(TSPDRV_MAGIC_NUMBER & 0xFF, 4)
#define TSPDRV_GET_NUM_ACTUATORS            _IO(TSPDRV_MAGIC_NUMBER & 0xFF, 5)
#define VIBE_MAX_DEVICE_NAME_LENGTH			64
#define SPI_HEADER_SIZE                     3   /* DO NOT CHANGE - SPI buffer header size */
#define VIBE_OUTPUT_SAMPLE_SIZE             50  /* DO NOT CHANGE - maximum number of samples */

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

typedef struct {
    VibeUInt8 nActuatorIndex;  /* 1st byte is actuator index */
    VibeUInt8 nBitDepth;       /* 2nd byte is bit depth */
    VibeUInt8 nBufferSize;     /* 3rd byte is data size */
    VibeUInt8 dataBuffer[VIBE_OUTPUT_SAMPLE_SIZE];
} samples_buffer;

typedef struct {
    VibeInt8 nIndexPlayingBuffer;
    VibeUInt8 nIndexOutputValue;
    samples_buffer actuatorSamples[2]; /* Use 2 buffers to receive samples from user mode */
} actuator_samples_buffer;

#endif

/* Error and Return value codes */
#define VIBE_S_SUCCESS                      0	/* Success */
#define VIBE_E_FAIL						    -4	/* Generic error */


#define VIBRATION_ON            1
#define VIBRATION_OFF           0

#define GP_CLK_M_DEFAULT			2

#if defined (CONFIG_MACH_MATISSELTE_ATT)
#define GP_CLK_N_DEFAULT			122
#define GP_CLK_D_DEFAULT			61	/* 50% duty cycle */

#else
#if defined CONFIG_MACH_MATISSE3G_OPEN || defined CONFIG_SEC_MATISSELTE_COMMON
#define GP_CLK_N_DEFAULT			99
#define GP_CLK_D_DEFAULT			44	/* 50% duty cycle */
#else
#define GP_CLK_N_DEFAULT                       93
#define GP_CLK_D_DEFAULT                       47      /* 50% duty cycle */
#endif

#endif//CONFIG_MACH_MATISSELTE_ATT

#define IMM_PWM_MULTIPLIER		    GP_CLK_N_DEFAULT	/* Must be integer */
/*
 * ** Global variables for LRA PWM M,N and D values.
 * */


 int32_t g_nforce_32 = 0;

#define MOTOR_MIN_STRENGTH                      54/*IMMERSION VALUE*/
#define MOTOR_STRENGTH                  98/*MOTOR_STRENGTH 98 %*/
int32_t g_nlra_gp_clk_m = GP_CLK_M_DEFAULT;
int32_t g_nlra_gp_clk_n = GP_CLK_N_DEFAULT;
int32_t g_nlra_gp_clk_d = GP_CLK_D_DEFAULT;
int32_t g_nlra_gp_clk_pwm_mul = IMM_PWM_MULTIPLIER;
int32_t motor_strength = MOTOR_STRENGTH;
int32_t motor_min_strength;


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


#define __inp(port) ioread8(port)

#define __inpw(port) ioread16(port)

#define __inpdw(port) ioread32(port)

#define __outp(port, val) iowrite8(val, port)

#define __outpw(port, val) iowrite16(val, port)

#define __outpdw(port, val) iowrite32(val, port)


#define in_dword(addr)              (__inpdw(addr))
#define in_dword_masked(addr, mask) (__inpdw(addr) & (mask))
#define out_dword(addr, val)        __outpdw(addr, val)
#define out_dword_masked(io, mask, val, shadow)  \
        (void) out_dword(io, \
        ((shadow & (unsigned int)(~(mask))) | ((unsigned int)((val) & (mask)))))
#define out_dword_masked_ns(io, mask, val, current_reg_content) \
        (void) out_dword(io, \
        ((current_reg_content & (unsigned int)(~(mask))) \
        | ((unsigned int)((val) & (mask)))))

#if !defined(CONFIG_MOTOR_DRV_ISA1400)
static void __iomem *virt_mmss_gp1_base;

#define HWIO_GP1_CMD_RCGR_ADDR ((void __iomem *)(virt_mmss_gp1_base + 0))       //MMSS_CC_GP1_CMD_RCGR
#define HWIO_GP1_CFG_RCGR_ADDR ((void __iomem *)(virt_mmss_gp1_base + 4))       //MMSS_CC_GP1_CFG_RCGR
#define HWIO_GP_M_REG_ADDR ((void __iomem *)(virt_mmss_gp1_base + 8))   //MMSS_CC_GP1_M
#define HWIO_GP_NS_REG_ADDR ((void __iomem *)(virt_mmss_gp1_base + 0xc))        //MMSS_CC_GP1_N
#define HWIO_GP_D_REG_ADDR ((void __iomem *)(virt_mmss_gp1_base + 0x10))        //MMSS_CC_GP1_D

#if defined(CONFIG_MACH_HLTEDCM) || defined(CONFIG_MACH_HLTEKDI) || defined(CONFIG_MACH_JS01LTEDCM)
        #define HWIO_CAMSS_GP1_CBCR_ADDR ((void __iomem *)(virt_mmss_gp1_base - 0x4))   //MMSS_CC_CAMSS_GP3_CBCR
#else
        #define HWIO_CAMSS_GP1_CBCR_ADDR ((void __iomem *)(virt_mmss_gp1_base + 0x24))  //MMSS_CC_CAMSS_GP1_CBCR
#endif
#define HWIO_GP_MD_REG_RMSK             0xffffffff
#define HWIO_GP_NS_REG_RMSK             0xffffffff

#define HWIO_GP_MD_REG_M_VAL_BMSK               0xff
#define HWIO_GP_MD_REG_M_VAL_SHFT               0
#define HWIO_GP_MD_REG_D_VAL_BMSK               0xff
#define HWIO_GP_MD_REG_D_VAL_SHFT               0
#define HWIO_GP_NS_REG_GP_N_VAL_BMSK    0xff
#define HWIO_GP_SRC_SEL_VAL_BMSK                0x700
#define HWIO_GP_SRC_SEL_VAL_SHFT                8
#define HWIO_GP_SRC_DIV_VAL_BMSK                0x1f
#define HWIO_GP_SRC_DIV_VAL_SHFT                0
#define HWIO_GP_MODE_VAL_BMSK                   0x3000
#define HWIO_GP_MODE_VAL_SHFT                   12

#define HWIO_CLK_ENABLE_VAL_BMSK        0x1
#define HWIO_CLK_ENABLE_VAL_SHFT        0
#define HWIO_UPDATE_VAL_BMSK    0x1
#define HWIO_UPDATE_VAL_SHFT    0
#define HWIO_ROOT_EN_VAL_BMSK   0x2
#define HWIO_ROOT_EN_VAL_SHFT   1


#define HWIO_GP1_CMD_RCGR_IN            \
                in_dword_masked(HWIO_GP1_CMD_RCGR_ADDR, HWIO_GP_NS_REG_RMSK)
#define HWIO_GP1_CMD_RCGR_OUTM(m, v)    \
        out_dword_masked_ns(HWIO_GP1_CMD_RCGR_ADDR, m, v, HWIO_GP1_CMD_RCGR_IN)



#define HWIO_GP1_CFG_RCGR_IN            \
                in_dword_masked(HWIO_GP1_CFG_RCGR_ADDR, HWIO_GP_NS_REG_RMSK)
#define HWIO_GP1_CFG_RCGR_OUTM(m, v)    \
        out_dword_masked_ns(HWIO_GP1_CFG_RCGR_ADDR, m, v, HWIO_GP1_CFG_RCGR_IN)



#define HWIO_CAMSS_GP1_CBCR_IN          \
                in_dword_masked(HWIO_CAMSS_GP1_CBCR_ADDR, HWIO_GP_NS_REG_RMSK)
#define HWIO_CAMSS_GP1_CBCR_OUTM(m, v)  \
       out_dword_masked_ns(HWIO_CAMSS_GP1_CBCR_ADDR, m, v, HWIO_CAMSS_GP1_CBCR_IN)

#define HWIO_GP_D_REG_IN                \
                in_dword_masked(HWIO_GP_D_REG_ADDR, HWIO_GP_MD_REG_RMSK)

#define HWIO_GP_D_REG_OUTM(m, v)\
        out_dword_masked_ns(HWIO_GP_D_REG_ADDR, m, v, HWIO_GP_D_REG_IN)


#define HWIO_GP_M_REG_IN                \
                in_dword_masked(HWIO_GP_M_REG_ADDR, HWIO_GP_MD_REG_RMSK)
#define HWIO_GP_M_REG_OUTM(m, v)\
        out_dword_masked_ns(HWIO_GP_M_REG_ADDR, m, v, HWIO_GP_M_REG_IN)


#define HWIO_GP_NS_REG_IN               \
                in_dword_masked(HWIO_GP_NS_REG_ADDR, HWIO_GP_NS_REG_RMSK)
#define HWIO_GP_NS_REG_OUTM(m, v)       \
        out_dword_masked_ns(HWIO_GP_NS_REG_ADDR, m, v, HWIO_GP_NS_REG_IN)


#define __msmhwio_outm(hwiosym, mask, val)  HWIO_##hwiosym##_OUTM(mask, val)
#define HWIO_OUTM(hwiosym, mask, val)   __msmhwio_outm(hwiosym, mask, val)

#endif

int vibrator_write_register(u8 addr, u8 w_data);

extern struct vibrator_platform_data_isa1200 vibrator_drvdata;
#endif  /* _TSPDRV_H */
