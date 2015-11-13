/*
** =========================================================================
** File:
**     ImmVibeSPI.c
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
#include <linux/delay.h>
#include <linux/gpio.h>
#include "tspdrv.h"

/*
** This SPI supports only one actuator.
*/
#define NUM_ACTUATORS 1
#define PWM_DUTY_MAX    213 /* 13MHz / (579 + 1) = 22.4kHz */
#define PWM_DEVICE	1

static bool g_bampenabled;

struct pm_gpio vib_pwm = {
				.direction = PM_GPIO_DIR_OUT,
				.output_buffer = 0,
				.output_value = 0,
				.pull = PM_GPIO_PULL_NO,
				.vin_sel = 0,
				.out_strength = PM_GPIO_STRENGTH_HIGH,
				.function = PM_GPIO_FUNC_1,
				.inv_int_pol = 0,
			};

int32_t vibe_set_pwm_freq(int nForce)
{
	/* Put the MND counter in reset mode for programming */
	HWIO_OUTM(GP1_CFG_RCGR, HWIO_GP_SRC_SEL_VAL_BMSK, 
				0 << HWIO_GP_SRC_SEL_VAL_SHFT); //SRC_SEL = 000(cxo)
#if defined(CONFIG_SEC_BERLUTI_PROJECT) || defined(CONFIG_MACH_S3VE3G_EUR)
	HWIO_OUTM(GP1_CFG_RCGR, HWIO_GP_SRC_DIV_VAL_BMSK,
				23 << HWIO_GP_SRC_DIV_VAL_SHFT); //SRC_DIV = 10111 (Div 12)
#else
	HWIO_OUTM(GP1_CFG_RCGR, HWIO_GP_SRC_DIV_VAL_BMSK,
				31 << HWIO_GP_SRC_DIV_VAL_SHFT); //SRC_DIV = 11111 (Div 16)
#endif
	HWIO_OUTM(GP1_CFG_RCGR, HWIO_GP_MODE_VAL_BMSK, 
				2 << HWIO_GP_MODE_VAL_SHFT); //Mode Select 10
	//M value
	HWIO_OUTM(GP_M_REG, HWIO_GP_MD_REG_M_VAL_BMSK,
		g_nlra_gp_clk_m << HWIO_GP_MD_REG_M_VAL_SHFT);

#if defined(CONFIG_MACH_LT03EUR) || defined(CONFIG_MACH_LT03SKT)\
	|| defined(CONFIG_MACH_LT03KTT)	|| defined(CONFIG_MACH_LT03LGT) || defined(CONFIG_MACH_PICASSO_LTE)

	if (nForce > 0){
		g_nforce_32 = g_nlra_gp_clk_n - (((nForce * g_nlra_gp_clk_pwm_mul) >> 8));
		if(g_nforce_32 < motor_min_strength)
			g_nforce_32 = motor_min_strength;
		else
			g_nforce_32 = (g_nforce_32 - motor_min_strength) \
				* (g_nlra_gp_clk_n * motor_strength / 100 - motor_min_strength) \
				/ (g_nlra_gp_clk_n - motor_min_strength) + motor_min_strength;
	}
	else{
		g_nforce_32 = ((nForce * g_nlra_gp_clk_pwm_mul) >> 8) + g_nlra_gp_clk_d;
		if(g_nlra_gp_clk_n - g_nforce_32 > g_nlra_gp_clk_n * motor_strength /100)
			g_nforce_32 = g_nlra_gp_clk_n - g_nlra_gp_clk_n * motor_strength /100;
	}
#else
	if (nForce > 0){
		g_nforce_32 = g_nlra_gp_clk_n - (((nForce * g_nlra_gp_clk_pwm_mul) >> 8));
		g_nforce_32 = g_nforce_32 * motor_strength /100;
		if(g_nforce_32 < motor_min_strength)
			g_nforce_32 = motor_min_strength;
	}
	else{
		g_nforce_32 = ((nForce * g_nlra_gp_clk_pwm_mul) >> 8) + g_nlra_gp_clk_d;
		if(g_nlra_gp_clk_n - g_nforce_32 > g_nlra_gp_clk_n * motor_strength /100)
			g_nforce_32 = g_nlra_gp_clk_n - g_nlra_gp_clk_n * motor_strength /100;
	}
#endif
	// D value
	HWIO_OUTM(GP_D_REG, HWIO_GP_MD_REG_D_VAL_BMSK,
	 (~((int16_t)g_nforce_32 << 1)) << HWIO_GP_MD_REG_D_VAL_SHFT);
	
	//N value	
	HWIO_OUTM(GP_NS_REG, HWIO_GP_NS_REG_GP_N_VAL_BMSK,
	 ~(g_nlra_gp_clk_n - g_nlra_gp_clk_m) << 0);
	
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


/*
** Called to disable amp (disable output force)
*/
static int32_t ImmVibeSPI_ForceOut_AmpDisable(u_int8_t nActuatorIndex)
{

	if (g_bampenabled) {
		g_bampenabled = false;
		if (vibrator_drvdata.power_onoff)
			vibrator_drvdata.power_onoff(0);
		if (vibrator_drvdata.vib_model == HAPTIC_PWM) {
			if(vibrator_drvdata.is_pmic_vib_pwm){  //PMIC PWM 
				gpio_set_value(vibrator_drvdata.vib_pwm_gpio, \
				VIBRATION_OFF);
				if(vibrator_drvdata.pwm_dev != NULL) //Disable the PWM device.
					pwm_disable(vibrator_drvdata.pwm_dev);
			} else{	//AP PWM
#if defined(CONFIG_MACH_S3VE3G_EUR) || defined(CONFIG_MACH_VICTOR3GDSDTV_LTN)
				gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_pwm_gpio,\
				0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, \
				GPIO_CFG_2MA),GPIO_CFG_ENABLE);
				gpio_set_value(vibrator_drvdata.vib_pwm_gpio, \
				    VIBRATION_OFF);
#else
				gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_pwm_gpio,\
				0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, \
				GPIO_CFG_2MA),GPIO_CFG_ENABLE);
				gpio_set_value(vibrator_drvdata.vib_pwm_gpio, \
				    VIBRATION_OFF);
#endif
			}
		}
		printk(KERN_DEBUG "tspdrv: %s\n", __func__);
#if defined(CONFIG_MOTOR_DRV_MAX77803)
		max77803_vibtonz_en(0);
#elif defined(CONFIG_MOTOR_DRV_MAX77804K)
		max77804k_vibtonz_en(0);
#elif defined(CONFIG_MOTOR_DRV_MAX77828)
		max77828_vibtonz_en(0);
#elif defined(CONFIG_MOTOR_DRV_MAX77888)
		max77888_gpio_en(0);
		max77888_vibtonz_en(0);
#elif defined(CONFIG_MOTOR_DRV_DRV2603)
		drv2603_gpio_en(0);
#elif defined(CONFIG_MOTOR_ISA1000)
		gpio_direction_output(vibrator_drvdata.vib_en_gpio,VIBRATION_OFF);
		gpio_set_value(vibrator_drvdata.vib_en_gpio,VIBRATION_OFF);
#endif
	}

	return VIBE_S_SUCCESS;
}

/*
** Called to enable amp (enable output force)
*/
static int32_t ImmVibeSPI_ForceOut_AmpEnable(u_int8_t nActuatorIndex)
{
	if (!g_bampenabled) {
		g_bampenabled = true;
		if (vibrator_drvdata.power_onoff)
			vibrator_drvdata.power_onoff(1);
		if (vibrator_drvdata.vib_model == HAPTIC_PWM) {
			if(vibrator_drvdata.is_pmic_vib_pwm){ //PMIC PWM
				gpio_set_value(vibrator_drvdata.vib_pwm_gpio, \
					VIBRATION_ON);
			} else {	//AP PWM
#if defined(CONFIG_MACH_HLTEDCM) || defined(CONFIG_MACH_HLTEKDI) || \
	defined(CONFIG_MACH_JS01LTEDCM) || defined(CONFIG_MACH_JS01LTESBM)
				gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_pwm_gpio,\
					2, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, \
					GPIO_CFG_2MA), GPIO_CFG_ENABLE);
					gpio_set_value(vibrator_drvdata.vib_pwm_gpio, \
						VIBRATION_ON);
#elif defined(CONFIG_SEC_BERLUTI_PROJECT) || defined(CONFIG_MACH_S3VE3G_EUR) || defined(CONFIG_MACH_VICTOR3GDSDTV_LTN) || defined(CONFIG_SEC_HESTIA_PROJECT)
				gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_pwm_gpio,\
					3, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, \
					GPIO_CFG_2MA), GPIO_CFG_ENABLE);
					gpio_set_value(vibrator_drvdata.vib_pwm_gpio, \
						VIBRATION_ON);
#else
				gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_pwm_gpio,\
					6, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, \
					GPIO_CFG_2MA), GPIO_CFG_ENABLE);
					gpio_set_value(vibrator_drvdata.vib_pwm_gpio, \
						VIBRATION_ON);
#endif
			}
		}
		printk(KERN_DEBUG "tspdrv: %s\n", __func__);
#if defined(CONFIG_MOTOR_DRV_MAX77803)
		max77803_vibtonz_en(1);
#elif defined(CONFIG_MOTOR_DRV_MAX77804K)
		max77804k_vibtonz_en(1);
#elif defined(CONFIG_MOTOR_DRV_MAX77828)
                max77828_vibtonz_en(1);
#elif defined(CONFIG_MOTOR_DRV_MAX77888)
		max77888_gpio_en(1);
		max77888_vibtonz_en(1);
#elif defined(CONFIG_MOTOR_DRV_DRV2603)
		drv2603_gpio_en(1);
#elif defined(CONFIG_MOTOR_ISA1000)
	gpio_direction_output(vibrator_drvdata.vib_en_gpio,VIBRATION_ON);
	gpio_set_value(vibrator_drvdata.vib_en_gpio,VIBRATION_ON);
#endif
	}

	return VIBE_S_SUCCESS;
}

/*
** Called at initialization time to set PWM freq,
** disable amp, etc...
*/
static int32_t ImmVibeSPI_ForceOut_Initialize(void)
{
	int ret;
	DbgOut((KERN_DEBUG "ImmVibeSPI_ForceOut_Initialize.\n"));
	/* to force ImmVibeSPI_ForceOut_AmpDisable disabling the amp */
	g_bampenabled = true;

	/*
	** Disable amp.
	** If multiple actuators are supported, please make sure to call
	** ImmVibeSPI_ForceOut_AmpDisable for each actuator
	** (provide the actuator index as input argument).
	*/

	/* set gpio config	*/
	if (vibrator_drvdata.vib_model == HAPTIC_PWM) {
		if (vibrator_drvdata.is_pmic_vib_pwm) { //PMIC PWM
			ret = gpio_request(vibrator_drvdata.vib_pwm_gpio, \
				"vib pwm");
			if (ret < 0) {
				printk(KERN_ERR"vib pwm gpio_request is failed\n");
				goto err2;
			}

			ret = pm8xxx_gpio_config(vibrator_drvdata.vib_pwm_gpio,\
					&vib_pwm);
			if (ret < 0) {
				printk(KERN_ERR "failed to configure vib pwm pmic gpio\n");
				goto err2;
			}
		} else { //AP PWM
#if defined(CONFIG_MACH_S3VE3G_EUR)
			gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_pwm_gpio,
			0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
			GPIO_CFG_ENABLE);
#else
			gpio_tlmm_config(GPIO_CFG(vibrator_drvdata.vib_pwm_gpio,
			0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
			GPIO_CFG_ENABLE);
#endif
		}
#if defined(CONFIG_MOTOR_ISA1000)
	if (!vibrator_drvdata.is_pmic_vib_en) {
		ret = gpio_request(vibrator_drvdata.vib_en_gpio,"vib enable");
		if (ret < 0) {
			printk(KERN_ERR "vib enable gpio_request is failed\n");
			goto err2;
		}
	}
#endif

#if defined(CONFIG_MOTOR_DRV_DRV2603)
		if (drv2603_gpio_init())
			goto err2;
#elif defined(CONFIG_MOTOR_DRV_MAX77888)
		if(max77888_gpio_init())
			goto err2;
#endif
	}
	ImmVibeSPI_ForceOut_AmpDisable(0);
	return VIBE_S_SUCCESS;

err2:
	return VIBE_E_FAIL;
}

/*
** Called at termination time to set PWM freq, disable amp, etc...
*/
static int32_t ImmVibeSPI_ForceOut_Terminate(void)
{
	DbgOut((KERN_DEBUG "ImmVibeSPI_ForceOut_Terminate.\n"));

	/*
	** Disable amp.
	** If multiple actuators are supported, please make sure to call
	** ImmVibeSPI_ForceOut_AmpDisable for each actuator
	** (provide the actuator index as input argument).
	*/
	ImmVibeSPI_ForceOut_AmpDisable(0);
	return VIBE_S_SUCCESS;
}


int vib_config_pwm_device(void)
{
	int ret = 0;
	if(vibrator_drvdata.pwm_dev == NULL){
	//u32	pwm_period_us, duty_us;
#if defined(CONFIG_MACH_HLTEDCM) || defined(CONFIG_MACH_HLTEKDI) || \
	defined(CONFIG_MACH_JS01LTEDCM) || defined(CONFIG_MACH_JS01LTESBM)
	vibrator_drvdata.pwm_dev = pwm_request(0,"lpg_3"); // 0 index for LPG3 channel. 
#else
	vibrator_drvdata.pwm_dev = pwm_request(0,"lpg_1"); // 0 index for LPG1 channel. 
#endif

	if (IS_ERR_OR_NULL(vibrator_drvdata.pwm_dev)) {
		pr_err("could not acquire PWM Channel 0, "
						"error %ld\n",PTR_ERR(vibrator_drvdata.pwm_dev));
		vibrator_drvdata.pwm_dev = NULL;
		return -ENODEV;
	}
	//pwm_period_us = 19; // 2000000; 
	//duty_us = 18; //1000000; (90% Duty Cycle)
	
	ret = pwm_config(vibrator_drvdata.pwm_dev,
					 vibrator_drvdata.duty_us,
					 vibrator_drvdata.pwm_period_us); 
	if (ret) {
		pr_err("pwm_config in vibrator enable failed %d\n", ret);
		return ret;
	}
	ret = pwm_enable(vibrator_drvdata.pwm_dev);	
	if (ret < 0) {
		pr_err("pwm_enable in vibrator  failed %d\n", ret);
		return ret;
	}
	} else {
		ret = pwm_enable(vibrator_drvdata.pwm_dev); 
		if (ret < 0) {
			pr_err("pwm_enable in vibrator  failed %d\n", ret);
			return ret;
		}
	}
	return ret;
}

/*
** Called by the real-time loop to set PWM duty cycle
*/
#ifdef CONFIG_TACTILE_ASSIST
static bool g_bOutputDataBufferEmpty = 1;
#endif
static int32_t ImmVibeSPI_ForceOut_SetSamples(u_int8_t nActuatorIndex,
						u_int16_t nOutputSignalBitDepth,
						u_int16_t nBufferSizeInBytes,
						int8_t *pForceOutputBuffer)
{
	int8_t nforce;
	static int8_t pre_nforce;
	int ret;

#ifdef CONFIG_TACTILE_ASSIST
	if (g_bOutputDataBufferEmpty) {
		nActuatorIndex = 0;
		nOutputSignalBitDepth = 8;
		nBufferSizeInBytes = 1;
		pForceOutputBuffer[0] = 0;
	}
#endif

	switch (nOutputSignalBitDepth) {
	case 8:
		/* pForceOutputBuffer is expected to contain 1 byte */
		if (nBufferSizeInBytes != 1) {
			DbgOut(KERN_ERR
			"[ImmVibeSPI] ImmVibeSPI_ForceOut_SetSamples nBufferSizeInBytes =  %d\n",
			nBufferSizeInBytes);
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
		if (!vibrator_drvdata.is_pmic_vib_pwm){
			//AP PWM
			vibe_pwm_onoff(0);
		}
		nforce = 0;
		pre_nforce = 0;
	} else {
		if (nforce > 0)
			nforce = 127 - nforce;
		/* Map force from [-127, 127] to [0, PWM_DUTY_MAX] */
		/* printk(KERN_DEBUG "[tspdrv]nForce===%d\n", nforce); */
		if (pre_nforce != nforce) {
			if (vibrator_drvdata.is_pmic_vib_pwm){ 
				//PMIC  PWM
				ret = vib_config_pwm_device();
				if(ret < 0)
					return ret;				
			}else {
				//AP PWM
				vibe_set_pwm_freq(nforce);
				vibe_pwm_onoff(1);
			}
			ImmVibeSPI_ForceOut_AmpEnable(0);
			pre_nforce = nforce;
		}
	}
	return VIBE_S_SUCCESS;
}

/*
** Called to get the device name (device name must be returned as ANSI char)
*/
static int32_t ImmVibeSPI_Device_GetName(
		u_int8_t nActuatorIndex, char *szDevName, int nSize)
{
	return VIBE_S_SUCCESS;
}
