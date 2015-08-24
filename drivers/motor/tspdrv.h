/*
** =========================================================================
** File:
**     tspdrv.h
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
** FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. Please see
** the License for the specific language governing rights and limitations
** under the License.
** =========================================================================
*/

#ifndef _TSPDRV_H
#define _TSPDRV_H
#define VIBE_DEBUG
#include <mach/msm_iomap.h>

#include <linux/mfd/pm8xxx/pm8921.h>

#define PM8921_GPIO_BASE  NR_GPIO_IRQS
#define PM8921_GPIO_PM_TO_SYS(pm_gpio) (pm_gpio - 1 + PM8921_GPIO_BASE)

extern struct vibrator_platform_data vibrator_drvdata;

/* Constants */
#define MODULE_NAME                         "tspdrv"
#define TSPDRV                              "/dev/"MODULE_NAME
#define TSPDRV_MAGIC_NUMBER                 0x494D4D52

#ifdef CONFIG_TACTILE_ASSIST
#define TSPDRV_IOCTL_GROUP                  0x52
#define TSPDRV_SET_MAGIC_NUMBER             _IO(TSPDRV_IOCTL_GROUP, 2)
#endif

#define TSPDRV_STOP_KERNEL_TIMER            _IO(TSPDRV_MAGIC_NUMBER & 0xFF, 1)

/*
** Obsolete IOCTL command
** #define TSPDRV_IDENTIFY_CALLER           _IO(TSPDRV_MAGIC_NUMBER & 0xFF, 2)
*/
#define TSPDRV_ENABLE_AMP		_IO(TSPDRV_MAGIC_NUMBER & 0xFF, 3)
#define TSPDRV_DISABLE_AMP		_IO(TSPDRV_MAGIC_NUMBER & 0xFF, 4)
#define TSPDRV_GET_NUM_ACTUATORS	_IO(TSPDRV_MAGIC_NUMBER & 0xFF, 5)
#define VIBE_MAX_DEVICE_NAME_LENGTH	64
#define SPI_HEADER_SIZE	3   /* DO NOT CHANGE - SPI buffer header size */
 /* DO NOT CHANGE - maximum number of samples */
#define VIBE_OUTPUT_SAMPLE_SIZE	50

/* Type definitions */
#ifdef __KERNEL__
typedef struct {
	u_int8_t nactuator_index;  /* 1st byte is actuator index */
	u_int8_t nbit_depth;       /* 2nd byte is bit depth */
	u_int8_t nbuffer_size;     /* 3rd byte is data size */
	u_int8_t data_buffer[VIBE_OUTPUT_SAMPLE_SIZE];
} samples_buffer;

typedef struct {
	int8_t nindex_playing_buffer;
	u_int8_t nindex_output_value;
	/* Use 2 buffers to receive samples from user mode */
	samples_buffer actuator_samples[2];
} actuator_samples_buffer;

#endif

/* Error and Return value codes */
#define VIBE_S_SUCCESS		0	/* Success */
#define VIBE_E_FAIL		 -4	/* Generic error */

#if defined(VIBE_RECORD) && defined(VIBE_DEBUG)
	void _RecorderInit(void);
	void _RecorderTerminate(void);
	void _RecorderReset(int nActuator);
	void _Record(int actuatorIndex, const char *format, ...);
#endif
#define VIBRATION_ON            1
#define VIBRATION_OFF           0

int32_t g_nforce_32;


#if defined(CONFIG_MACH_KS01SKT) \
	   || defined(CONFIG_MACH_KS01KTT) || defined(CONFIG_MACH_KS01LGT) \
	   || defined(CONFIG_MACH_JACTIVESKT) || defined(CONFIG_MACH_HLTEDCM)
#define MOTOR_STRENGTH			94/*MOTOR_STRENGTH 94 %*/
#elif defined(CONFIG_MACH_LT03EUR) || defined(CONFIG_MACH_LT03SKT)\
	|| defined(CONFIG_MACH_LT03KTT)	|| defined(CONFIG_MACH_LT03LGT)
#define MOTOR_STRENGTH			98/*MOTOR_STRENGTH 98 %*/
#elif defined(CONFIG_MACH_PICASSO_LTE)
#define MOTOR_STRENGTH			91
#elif defined(CONFIG_MACH_JS01LTEDCM)
#define MOTOR_STRENGTH			93/*MOTOR_STRENGTH 93 %*/
#elif defined(CONFIG_MACH_HLTEUSC) || defined(CONFIG_MACH_HLTEVZW)
#define MOTOR_STRENGTH			99/*MOTOR_STRENGTH 99 %*/
#elif defined(CONFIG_SEC_K_PROJECT) || defined(CONFIG_SEC_KACTIVE_PROJECT) || defined(CONFIG_SEC_KSPORTS_PROJECT)
#define MOTOR_STRENGTH			98/*MOTOR_STRENGTH 98 %*/
#else
#define MOTOR_STRENGTH			98/*MOTOR_STRENGTH 98 %*/
#endif


#if defined (CONFIG_MACH_HLTESPR) || defined (CONFIG_MACH_HLTEEUR) || defined(CONFIG_SEC_LOCALE_KOR_H) || defined (CONFIG_MACH_HLTETMO) || defined(CONFIG_MACH_H3GDUOS) || defined(CONFIG_MACH_HLTEATT)
	#define GP_CLK_M_DEFAULT                        3
	#define GP_CLK_N_DEFAULT                        138
	#define GP_CLK_D_DEFAULT                        69  /* 50% duty cycle	*/
	#define IMM_PWM_MULTIPLIER			137
#elif defined (CONFIG_MACH_JS01LTEDCM) || defined (CONFIG_MACH_JS01LTESBM)
	#define GP_CLK_M_DEFAULT			2
	#define GP_CLK_N_DEFAULT			92
	#define GP_CLK_D_DEFAULT			46  /* 50% duty cycle */
	#define IMM_PWM_MULTIPLIER		92
#elif defined (CONFIG_MACH_HLTEUSC) || defined(CONFIG_MACH_HLTEVZW)
	#define GP_CLK_M_DEFAULT			1
	#define GP_CLK_N_DEFAULT			46
	#define GP_CLK_D_DEFAULT			23  /* 50% duty cycle */
	#define IMM_PWM_MULTIPLIER		46
#elif defined(CONFIG_MACH_FLTESKT)
	#define GP_CLK_M_DEFAULT			2
	#define GP_CLK_N_DEFAULT                        92
	#define GP_CLK_D_DEFAULT			46  /* 50% duty cycle */
	#define IMM_PWM_MULTIPLIER			92
#elif defined(CONFIG_SEC_K_PROJECT) || defined(CONFIG_SEC_KACTIVE_PROJECT)
#if defined(CONFIG_MACH_KLTE_JPN)
#if defined(CONFIG_MACH_KLTE_MAX77828_JPN)
	#define GP_CLK_M_DEFAULT			1
	#define GP_CLK_N_DEFAULT                        20
	#define GP_CLK_D_DEFAULT			10  /* 50% duty cycle */
	#define IMM_PWM_MULTIPLIER			20
#else
	#define GP_CLK_M_DEFAULT			4
	#define GP_CLK_N_DEFAULT                        161
	#define GP_CLK_D_DEFAULT			81  /* 50% duty cycle */
	#define IMM_PWM_MULTIPLIER			161
#endif
#else
	#define GP_CLK_M_DEFAULT			3
	#define GP_CLK_N_DEFAULT                        121
	#define GP_CLK_D_DEFAULT			61  /* 50% duty cycle */
	#define IMM_PWM_MULTIPLIER			121
#endif
#elif defined(CONFIG_SEC_LOCALE_KOR_FRESCO)
	#define GP_CLK_M_DEFAULT			3
	#define GP_CLK_N_DEFAULT                        120
	#define GP_CLK_D_DEFAULT			60  /* 50% duty cycle */
	#define IMM_PWM_MULTIPLIER			120
#elif defined(CONFIG_SEC_BERLUTI_PROJECT) || defined(CONFIG_MACH_S3VE3G_EUR)
	#define GP_CLK_M_DEFAULT			1
	#define GP_CLK_N_DEFAULT			61
	#define GP_CLK_D_DEFAULT			31  /* 50% duty cycle */
	#define IMM_PWM_MULTIPLIER			61
#else
	#define GP_CLK_M_DEFAULT			2
	#define GP_CLK_N_DEFAULT                        91
	#define GP_CLK_D_DEFAULT			46  /* 50% duty cycle */
	#define IMM_PWM_MULTIPLIER			91
#endif


#define MOTOR_MIN_STRENGTH			54/*IMMERSION VALUE*/
/*
 * ** Global variables for LRA PWM M,N and D values.
 * */
int32_t g_nlra_gp_clk_m = GP_CLK_M_DEFAULT;
int32_t g_nlra_gp_clk_n = GP_CLK_N_DEFAULT;
int32_t g_nlra_gp_clk_d = GP_CLK_D_DEFAULT;
int32_t g_nlra_gp_clk_pwm_mul = IMM_PWM_MULTIPLIER;
int32_t motor_strength = MOTOR_STRENGTH;
int32_t motor_min_strength;

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

#define HWIO_GP1_CMD_RCGR_ADDR ((void __iomem *)(virt_mmss_gp1_base + 0))	//MMSS_CC_GP1_CMD_RCGR
#define HWIO_GP1_CFG_RCGR_ADDR ((void __iomem *)(virt_mmss_gp1_base + 4))	//MMSS_CC_GP1_CFG_RCGR
#define HWIO_GP_M_REG_ADDR ((void __iomem *)(virt_mmss_gp1_base + 8))	//MMSS_CC_GP1_M
#define HWIO_GP_NS_REG_ADDR ((void __iomem *)(virt_mmss_gp1_base + 0xc))	//MMSS_CC_GP1_N
#define HWIO_GP_D_REG_ADDR ((void __iomem *)(virt_mmss_gp1_base + 0x10))	//MMSS_CC_GP1_D

#if defined(CONFIG_MACH_HLTEDCM) || defined(CONFIG_MACH_HLTEKDI) || \
	defined(CONFIG_MACH_JS01LTEDCM) || defined(CONFIG_MACH_JS01LTESBM)
	#define HWIO_CAMSS_GP1_CBCR_ADDR ((void __iomem *)(virt_mmss_gp1_base - 0x4))	//MMSS_CC_CAMSS_GP3_CBCR
#else
	#define HWIO_CAMSS_GP1_CBCR_ADDR ((void __iomem *)(virt_mmss_gp1_base + 0x24))	//MMSS_CC_CAMSS_GP1_CBCR
#endif

#define HWIO_GP_MD_REG_RMSK		0xffffffff
#define HWIO_GP_NS_REG_RMSK		0xffffffff

#define HWIO_GP_MD_REG_M_VAL_BMSK		0xff
#define HWIO_GP_MD_REG_M_VAL_SHFT		0
#define HWIO_GP_MD_REG_D_VAL_BMSK		0xff
#define HWIO_GP_MD_REG_D_VAL_SHFT		0
#define HWIO_GP_NS_REG_GP_N_VAL_BMSK	0xff
#define HWIO_GP_SRC_SEL_VAL_BMSK		0x700
#define HWIO_GP_SRC_SEL_VAL_SHFT		8
#define HWIO_GP_SRC_DIV_VAL_BMSK		0x1f
#define HWIO_GP_SRC_DIV_VAL_SHFT		0
#define HWIO_GP_MODE_VAL_BMSK			0x3000
#define HWIO_GP_MODE_VAL_SHFT			12

#define HWIO_CLK_ENABLE_VAL_BMSK	0x1
#define HWIO_CLK_ENABLE_VAL_SHFT	0
#define HWIO_UPDATE_VAL_BMSK	0x1
#define HWIO_UPDATE_VAL_SHFT	0
#define HWIO_ROOT_EN_VAL_BMSK	0x2
#define HWIO_ROOT_EN_VAL_SHFT	1


#define HWIO_GP1_CMD_RCGR_IN		\
		in_dword_masked(HWIO_GP1_CMD_RCGR_ADDR, HWIO_GP_NS_REG_RMSK)
#define HWIO_GP1_CMD_RCGR_OUTM(m, v)	\
	out_dword_masked_ns(HWIO_GP1_CMD_RCGR_ADDR, m, v, HWIO_GP1_CMD_RCGR_IN)



#define HWIO_GP1_CFG_RCGR_IN		\
		in_dword_masked(HWIO_GP1_CFG_RCGR_ADDR, HWIO_GP_NS_REG_RMSK)
#define HWIO_GP1_CFG_RCGR_OUTM(m, v)	\
	out_dword_masked_ns(HWIO_GP1_CFG_RCGR_ADDR, m, v, HWIO_GP1_CFG_RCGR_IN)



#define HWIO_CAMSS_GP1_CBCR_IN		\
		in_dword_masked(HWIO_CAMSS_GP1_CBCR_ADDR, HWIO_GP_NS_REG_RMSK)
#define HWIO_CAMSS_GP1_CBCR_OUTM(m, v)	\
	out_dword_masked_ns(HWIO_CAMSS_GP1_CBCR_ADDR, m, v, HWIO_CAMSS_GP1_CBCR_IN)

#define HWIO_GP_D_REG_IN		\
		in_dword_masked(HWIO_GP_D_REG_ADDR, HWIO_GP_MD_REG_RMSK)

#define HWIO_GP_D_REG_OUTM(m, v)\
	out_dword_masked_ns(HWIO_GP_D_REG_ADDR, m, v, HWIO_GP_D_REG_IN)


#define HWIO_GP_M_REG_IN		\
		in_dword_masked(HWIO_GP_M_REG_ADDR, HWIO_GP_MD_REG_RMSK)
#define HWIO_GP_M_REG_OUTM(m, v)\
	out_dword_masked_ns(HWIO_GP_M_REG_ADDR, m, v, HWIO_GP_M_REG_IN)


#define HWIO_GP_NS_REG_IN		\
		in_dword_masked(HWIO_GP_NS_REG_ADDR, HWIO_GP_NS_REG_RMSK)
#define HWIO_GP_NS_REG_OUTM(m, v)	\
	out_dword_masked_ns(HWIO_GP_NS_REG_ADDR, m, v, HWIO_GP_NS_REG_IN)


#define __msmhwio_outm(hwiosym, mask, val)  HWIO_##hwiosym##_OUTM(mask, val)
#define HWIO_OUTM(hwiosym, mask, val)	__msmhwio_outm(hwiosym, mask, val)
int32_t vibe_pwm_onoff(u8 onoff);
int32_t vibe_set_pwm_freq(int nForce);
#endif
/* Kernel Debug Macros */
#ifdef __KERNEL__
	#ifdef VIBE_DEBUG
		#define DbgOut(_x_, ...) printk(_x_, ##__VA_ARGS__)
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

#if defined(CONFIG_MOTOR_DRV_MAX77803)
extern void max77803_vibtonz_en(bool en);
#elif defined(CONFIG_MOTOR_DRV_MAX77804K)
extern void max77804k_vibtonz_en(bool en);
#elif defined(CONFIG_MOTOR_DRV_MAX77828)
extern void max77828_vibtonz_en(bool en);
#elif defined(CONFIG_MOTOR_DRV_DRV2603)
void drv2603_gpio_en(bool);
static int32_t drv2603_gpio_init(void);
#endif

#endif  /* _TSPDRV_H */
