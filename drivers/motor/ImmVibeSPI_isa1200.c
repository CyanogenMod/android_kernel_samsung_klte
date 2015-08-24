/*
** =========================================================================
** File:
**     ImmVibeSPI_isa1200.c
**
** Description:
**     Device-dependent functions called by Immersion TSP API
**     to control PWM duty cycle, amp enable/disable, save IVT file, etc...
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
#include <linux/pwm.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/clk.h>

#include "tspdrv_isa1200.h"

#include <linux/module.h>
#include <linux/mfd/pmic8058.h>
#include <linux/slab.h>
#include <linux/regulator/consumer.h>
#include <linux/delay.h>


#ifdef IMMVIBESPIAPI
#undef IMMVIBESPIAPI
#endif
#define IMMVIBESPIAPI static

/*
** This SPI supports only one actuator.
*/
#define NUM_ACTUATORS 1

#define HCTRL0     (0x30)     /* 0x09 */ /* Haptic Motor Driver Control Register Group 0*/
#define HCTRL1     (0x31)     /* 0x4B */ /* Haptic Motor Driver Control Register Group 1*/

static bool g_bAmpEnabled = false;

int32_t vibe_set_pwm_freq(int nForce)
{
	/* Put the MND counter in reset mode for programming */
	HWIO_OUTM(GP1_CFG_RCGR, HWIO_GP_SRC_SEL_VAL_BMSK,0 << HWIO_GP_SRC_SEL_VAL_SHFT); //SRC_SEL = 000(cxo)
#if defined (CONFIG_MACH_MATISSELTE_ATT)
	HWIO_OUTM(GP1_CFG_RCGR, HWIO_GP_SRC_DIV_VAL_BMSK,23 << HWIO_GP_SRC_DIV_VAL_SHFT); //SRC_DIV = 11111 (Div 12)
#else
#if defined CONFIG_MACH_MATISSE3G_OPEN || defined CONFIG_SEC_MATISSELTE_COMMON
	HWIO_OUTM(GP1_CFG_RCGR, HWIO_GP_SRC_DIV_VAL_BMSK,29 << HWIO_GP_SRC_DIV_VAL_SHFT); //SRC_DIV = 11111 (Div 16)
#else
	HWIO_OUTM(GP1_CFG_RCGR, HWIO_GP_SRC_DIV_VAL_BMSK,31 << HWIO_GP_SRC_DIV_VAL_SHFT); //SRC_DIV = 11111 (Div 16)
#endif
#endif//CONFIG_MACH_MATISSELTE_ATT
	HWIO_OUTM(GP1_CFG_RCGR, HWIO_GP_MODE_VAL_BMSK,2 << HWIO_GP_MODE_VAL_SHFT); //Mode Select 10
	//M value
	HWIO_OUTM(GP_M_REG, HWIO_GP_MD_REG_M_VAL_BMSK,g_nlra_gp_clk_m << HWIO_GP_MD_REG_M_VAL_SHFT);
	if (nForce > 0){
		g_nforce_32 = g_nlra_gp_clk_n - (((nForce * g_nlra_gp_clk_pwm_mul) >> 8));
		g_nforce_32 = g_nforce_32 * motor_strength /100;
		if(g_nforce_32 < motor_min_strength)
			g_nforce_32 = motor_min_strength;
	}
	else {
		g_nforce_32 = ((nForce * g_nlra_gp_clk_pwm_mul) >> 8) + g_nlra_gp_clk_d;
		if(g_nlra_gp_clk_n - g_nforce_32 > g_nlra_gp_clk_n * motor_strength /100)
			g_nforce_32 = g_nlra_gp_clk_n - g_nlra_gp_clk_n * motor_strength /100;
	}
        // D value
		HWIO_OUTM(GP_D_REG, HWIO_GP_MD_REG_D_VAL_BMSK,(~((int16_t)g_nforce_32 << 1)) << HWIO_GP_MD_REG_D_VAL_SHFT);
	//N value
	HWIO_OUTM(GP_NS_REG, HWIO_GP_NS_REG_GP_N_VAL_BMSK,~(g_nlra_gp_clk_n - g_nlra_gp_clk_m) << 0);

	return VIBE_S_SUCCESS;
}


int32_t vibe_pwm_onoff(u8 onoff)
{
	if (onoff) {
                HWIO_OUTM(GP1_CMD_RCGR,HWIO_UPDATE_VAL_BMSK,
                                        1 << HWIO_UPDATE_VAL_SHFT);//UPDATE ACTIVE
                HWIO_OUTM(GP1_CMD_RCGR,HWIO_ROOT_EN_VAL_BMSK,
                                        1 << HWIO_ROOT_EN_VAL_SHFT);//ROOT_EN
                HWIO_OUTM(CAMSS_GP1_CBCR, HWIO_CLK_ENABLE_VAL_BMSK,
                                        1 << HWIO_CLK_ENABLE_VAL_SHFT); //CLK_ENABLE
        } else {
		HWIO_OUTM(GP1_CMD_RCGR,HWIO_UPDATE_VAL_BMSK,
                                        0 << HWIO_UPDATE_VAL_SHFT);
                HWIO_OUTM(GP1_CMD_RCGR,HWIO_ROOT_EN_VAL_BMSK,
                                        0 << HWIO_ROOT_EN_VAL_SHFT);
                HWIO_OUTM(CAMSS_GP1_CBCR, HWIO_CLK_ENABLE_VAL_BMSK,
                                        0 << HWIO_CLK_ENABLE_VAL_SHFT);
        }
	return VIBE_S_SUCCESS;
}

int vib_isa1200_onoff(u8 onoff)
{

	if(onoff) {
		vibrator_write_register(HCTRL0, 0x88);	//HCTRL0
                vibrator_write_register(HCTRL1, 0x4B);
	} else {
		vibrator_write_register(HCTRL0, 0x08);
	}
	return 0;
}

/*
** Called to disable amp (disable output force)
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_AmpDisable(VibeUInt8 nActuatorIndex)
{
    if (g_bAmpEnabled)
    {
	printk("[VIBETONZ] %s \n",__func__);
	g_bAmpEnabled = false;
	vib_isa1200_onoff(0);
#if defined CONFIG_MACH_MATISSE3G_OPEN || defined CONFIG_SEC_MATISSELTE_COMMON
	vibrator_drvdata.power_onoff(0);
#endif
	gpio_set_value(vibrator_drvdata.motor_en, VIBRATION_OFF);
	gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_clk,  0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),GPIO_CFG_ENABLE);
	gpio_set_value(vibrator_drvdata.vib_clk, VIBRATION_OFF);
    }

	return VIBE_S_SUCCESS;
}

/*
** Called to enable amp (enable output force)
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_AmpEnable(VibeUInt8 nActuatorIndex)
{


    if (!g_bAmpEnabled)
    {
	printk("[VIBETONZ] %s \n",__func__);
	g_bAmpEnabled = true;

#if defined CONFIG_MACH_MATISSE3G_OPEN || defined CONFIG_SEC_MATISSELTE_COMMON
	vibrator_drvdata.power_onoff(1);
	gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_clk,  3, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),GPIO_CFG_ENABLE);
#else
	gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_clk,  6, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),GPIO_CFG_ENABLE);
#endif
	gpio_set_value(vibrator_drvdata.vib_clk, VIBRATION_ON);
	gpio_set_value(vibrator_drvdata.motor_en, VIBRATION_ON);
#if defined CONFIG_MACH_MATISSE3G_OPEN || defined CONFIG_SEC_MATISSELTE_COMMON
	msleep(1);
#endif
	vib_isa1200_onoff(1);
    }

    return VIBE_S_SUCCESS;
}

/*
** Called at initialization time to set PWM freq, disable amp, etc...
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_Initialize(void)
{
	g_bAmpEnabled = true;
	DbgOut((KERN_DEBUG "ImmVibeSPI_ForceOut_Initialize.\n"));
	gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_clk,0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),GPIO_CFG_ENABLE);
	msleep(1);
	vibrator_write_register(HCTRL0, 0x08);
	vibrator_write_register(HCTRL1, 0x4B);
	ImmVibeSPI_ForceOut_AmpDisable(0);

    return VIBE_S_SUCCESS;
}

/*
** Called at termination time to set PWM freq, disable amp, etc...
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_Terminate(void)
{
	DbgOut((KERN_DEBUG "ImmVibeSPI_ForceOut_Terminate.\n"));

    /*** Disable amp.
	** If multiple actuators are supported, please make sure to call
	** ImmVibeSPI_ForceOut_AmpDisable for each actuator (provide the actuator index as
	** input argument).
    */
    ImmVibeSPI_ForceOut_AmpDisable(0);

    return VIBE_S_SUCCESS;
}

IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_SetSamples(u_int8_t nActuatorIndex,u_int16_t nOutputSignalBitDepth,u_int16_t nBufferSizeInBytes,int8_t *pForceOutputBuffer)
{
	int8_t nforce;
	static int8_t pre_nforce;
	switch (nOutputSignalBitDepth) {
		case 8:
			/* pForceOutputBuffer is expected to contain 1 byte */
			if (nBufferSizeInBytes != 1) {
				DbgOut((KERN_ERR"[ImmVibeSPI] ImmVibeSPI_ForceOut_SetSamples nBufferSizeInBytes =  %d\n",nBufferSizeInBytes));
				return VIBE_E_FAIL;
			}
			nforce = pForceOutputBuffer[0];
			break;
		case 16:
			/* pForceOutputBuffer is expected to contain 2 byte */
			if (nBufferSizeInBytes != 2)
				return VIBE_E_FAIL;

			 /* Map 16-bit value to 8-bit */
			nforce = ((int16_t *)pForceOutputBuffer)[0] >> 8;
			break;
		default:
			/* Unexpected bit depth */
			return VIBE_E_FAIL;
		}
	if (nforce == 0) {
		/* Set 50% duty cycle or disable amp */
		ImmVibeSPI_ForceOut_AmpDisable(0);
		vibe_pwm_onoff(0);
		nforce = 0;
		pre_nforce = 0;
	} else {
		if (nforce > 0)
			 nforce = 127 - nforce;
		/* Map force from [-127, 127] to [0, PWM_DUTY_MAX] */
		/* printk(KERN_DEBUG "[tspdrv]nForce===%d\n", nforce); */
		if (pre_nforce != nforce) {
			vibe_set_pwm_freq(nforce);
			vibe_pwm_onoff(1);
			ImmVibeSPI_ForceOut_AmpEnable(0);
			pre_nforce = nforce;
			}
		}
	        return VIBE_S_SUCCESS;
}


/*
** Called to get the device name (device name must be returned as ANSI char)
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_Device_GetName(VibeUInt8 nActuatorIndex, char *szDevName, int nSize)
{
    return VIBE_S_SUCCESS;
}

