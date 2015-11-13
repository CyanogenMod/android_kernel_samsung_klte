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

#ifdef IMMVIBESPIAPI
#undef IMMVIBESPIAPI
#endif
#define IMMVIBESPIAPI static

#include <linux/isa1400_vibrator.h>

/*
** This SPI supports only one actuator.
*/
#define NUM_ACTUATORS 1

#define ISA1400_I2C_ADDRESS	0x90

static bool g_bAmpEnabled[NUM_ACTUATORS];

/* Variable defined to allow for tuning of the handset. */
/* For temporary section for Tuning Work */
#if 0
#define VIBETONZ_TUNING
#define ISA1400_GEN_MODE
#endif
#define MOTOR_TYPE_LRA

#ifdef VIBETONZ_TUNING
extern VibeStatus ImmVibeGetDeviceKernelParameter(VibeInt32 nDeviceIndex, VibeInt32 nDeviceKernelParamID, VibeInt32 *pnDeviceKernelParamValue);
#endif /* VIBETONZ_TUNING */

/* PWM mode selection */
#ifndef ISA1400_GEN_MODE
#define ISA1400_PWM_MODE
#if 0
#define ISA1400_PWM_256DIV_MODE
#else
#define ISA1400_PWM_128DIV_MODE
#endif
#endif

/* Actuator selection */
#ifndef MOTOR_TYPE_LRA
#define MOTOR_TYPE_ERM
#endif

#define ISA1400_HEN_ENABLE
#define RETRY_CNT 10

#define SYS_API_LEN_HIGH	isa1400_chip_enable(true)
#define SYS_API_LEN_LOW	isa1400_chip_enable(false)
#define SYS_API_HEN_HIGH
#define SYS_API_HEN_LOW
#define SYS_API_VDDP_ON
#define SYS_API_VDDP_OFF
#define SYS_API__I2C__Write( _addr, _dataLength, _data)	\
	isa1400_i2c_write(_addr, _dataLength, _data)
#define SLEEP(_us_time)

#define PWM_CLK_ENABLE
#define PWM_CLK_DISABLE

#define DEBUG_MSG(fmt, ...) \
	printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)

#define SYS_API_SET_PWM_FREQ(freq)
#define SYS_API_SET_PWM_DUTY(index, ratio)	isa1400_clk_config(index, ratio)

#define DEVICE_NAME "Generic"

/*
** Called to disable amp (disable output force)
*/
extern int vib_ioctl_lock;

IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_AmpDisable(VibeUInt8 nActuatorIndex)
{

	vib_ioctl_lock = 0;
    if (g_bAmpEnabled[nActuatorIndex])
    {
        DbgOut((KERN_DEBUG "ImmVibeSPI_ForceOut_AmpDisable.\n"));

        g_bAmpEnabled[nActuatorIndex] = false;

    }

	if((!g_bAmpEnabled[0]))
		SYS_API_LEN_LOW;

    return VIBE_S_SUCCESS;
}

/*
** Called to enable amp (enable output force)
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_AmpEnable(VibeUInt8 nActuatorIndex)
{
	vib_ioctl_lock = 1;
    if (!g_bAmpEnabled[nActuatorIndex])
    {
        DbgOut((KERN_DEBUG "ImmVibeSPI_ForceOut_AmpEnable.\n"));
        g_bAmpEnabled[nActuatorIndex] = true;

	/* mz_ops.bstat |= HN_BATTERY_MOTOR; */

    }

	if(g_bAmpEnabled[0] )
		SYS_API_LEN_HIGH;

    return VIBE_S_SUCCESS;
}
#if 0
/*
** Called at initialization time to set PWM frequencies, disable amp, etc...
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_Initialize(void)
{
    return VIBE_S_SUCCESS;
}

/*
** Called at termination time to set PWM freq, disable amp, etc...
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_Terminate(void)
{

    VibeStatus nActuatorIndex;  /* Initialized below. */

    DbgOut((KERN_DEBUG "ImmVibeSPI_ForceOut_Terminate.\n"));

    /* For each actuator... */
    for (nActuatorIndex = 0; NUM_ACTUATORS > nActuatorIndex; ++nActuatorIndex)
    {
        /* Disable amp */
        ImmVibeSPI_ForceOut_AmpDisable(nActuatorIndex);
    }

    return VIBE_S_SUCCESS;
}
#endif
/*
** Called by the real-time loop to set PWM_MAG duty cycle
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_SetSamples(VibeUInt8 nActuatorIndex, VibeUInt16 nOutputSignalBitDepth, VibeUInt16 nBufferSizeInBytes, VibeInt8* pForceOutputBuffer)
{
    VibeInt8 nForce = 0;
    VibeBool bSingleValueOutput = false;
    //int cnt = 0;
    //unsigned char I2C_data[2];
    //int ret = VIBE_S_SUCCESS;

    switch (nOutputSignalBitDepth)
    {
        case 8:
            /* For ERM/LRA, pForceOutputBuffer is expected to contain 1 byte */
            if (nBufferSizeInBytes == 1)
            {
                bSingleValueOutput = true;
                nForce = pForceOutputBuffer[0];
            }
            break;
        case 16:
            /* For ERM/LRA, pForceOutputBuffer is expected to contain 2 byte */
            if (nBufferSizeInBytes == 2)
            {
                bSingleValueOutput = true;
                /* Map 16-bit value to 8-bit */
                nForce = ((VibeInt16*)pForceOutputBuffer)[0] >> 8;
            }
            break;
        default:
            /* Unexpected bit depth */
            return VIBE_E_FAIL;
    }

	 SYS_API_SET_PWM_DUTY(nActuatorIndex, nForce);

    return VIBE_S_SUCCESS;
}
#if 0
/*
** Called to set force output frequency parameters
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_ForceOut_SetFrequency(VibeUInt8 nActuatorIndex, VibeUInt16 nFrequencyParameterID, VibeUInt32 nFrequencyParameterValue)
{
    return VIBE_S_SUCCESS;
}
#endif

/*
** Called to get the device name (device name must be returned as ANSI char)
*/
IMMVIBESPIAPI VibeStatus ImmVibeSPI_Device_GetName(VibeUInt8 nActuatorIndex, char *szDevName, int nSize)
{
    return VIBE_S_SUCCESS;
}

