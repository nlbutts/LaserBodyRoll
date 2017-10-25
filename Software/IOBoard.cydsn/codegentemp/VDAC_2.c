/***************************************************************************//**
* \file     VDAC_2.c
* \version  1.10
*
* \brief
* Provides the source code to the API for the VDAC_2 Component.
*
********************************************************************************
* \copyright
* (c) 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/
#include "VDAC_2.h"
#include "VDAC_2_UAB.h"
#include "VDAC_2_OUTBUFFER.h"

uint8 VDAC_2_initVar = 0u; /**< 0 if component is uninitialized. 1 otherwise. */
/*******************************************************************************
* Function Name: VDAC_2_Start
****************************************************************************//**
*
* \brief Starts the component.  Must be called before using the UAB_VDAC.
*
*  Invokes VDAC_2_Init() (the first time it is called only) and
* VDAC_2_Enable().  After this function call the component is enabled
* and ready for operation.  This is the preferred method to begin component
* operation.
*
* \globalvars
*  \ref VDAC_2_initVar (RW)
*
* \sideeffect
*  None.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_Start
*
*******************************************************************************/
void VDAC_2_Start(void)
{
    if (1u != VDAC_2_initVar)
    {
        VDAC_2_Init();
        VDAC_2_initVar = 1u;
    }
    VDAC_2_Enable();
    
    return;
}

/*******************************************************************************
* Function Name: VDAC_2_Stop
****************************************************************************//**
*
* \brief Stops the component.
*
* Disables the component.  Output becomes high-Z, and UAB and CTB are disabled.
* The UAB and CTB are only half of their blocks, and disabling them is not the same
* as stopping the blocks.  This function does not stop the block power.
*
* \sideeffect
*  UAB and CTB are not fully powered-down.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_Stop
*
*******************************************************************************/
void VDAC_2_Stop(void)
{
    
    /* Stopping the CTB first prevents output glitches. */
    VDAC_2_OUTBUFFER_Stop();
    
    /* Stop the UAB */
    VDAC_2_UAB_Stop();
    
    VDAC_2_initVar = 0u;
    return;
}

/*******************************************************************************
* Function Name: VDAC_2_SetValue
****************************************************************************//**
*
* \brief This sets the next value for the DAC to output.
*
* The value is assumed to be correctly formatted according to the DAC mode 
* (ie 13bit 2's complement, 13bit sign magnitude, or 12bit unsigned).
* 
*
* \param value
*  The value with which to update the DAC. Saturates if out of range.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_SetValue
*
*******************************************************************************/
void VDAC_2_SetValue(int32 value)
{
    VDAC_2_UAB_SetDacNext((int16)value);
    return;
}

/*******************************************************************************
* Function Name: VDAC_2_SaturateTwosComp
****************************************************************************//**
*
* \brief Saturates input to the 13-bit 2's complement range.
*
* The maximum value that the DAC supports is 4095.  The minimum is -4096.
*
* \param value
*  The value to saturate.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_SaturateTwosComp
*
*******************************************************************************/
int32 VDAC_2_SaturateTwosComp(int32 value)
{
    /* If larger than max, or smaller than min, saturate. Otherwise, do nothing. */
    value = (value > VDAC_2_MAX_13b2SCOMP) ? VDAC_2_MAX_13b2SCOMP :
            ((value < VDAC_2_MIN_13b2SCOMP) ? VDAC_2_MIN_13b2SCOMP : value);
    return value;
}

/*******************************************************************************
* Function Name: VDAC_2_SaturateSignMagnitude
****************************************************************************//**
*
* \brief Saturates input to the 13-bit sign magnitude range.
*
* The maximum value that the DAC supports is 4095.  The minimum is -4095.
*
* \param sign
*  The sign of the value to saturate.  See \ref sign for values.
*
* \param magnitude
*  The magnitude of the value to saturate.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_SaturateSignMagnitude
*
*******************************************************************************/
int32 VDAC_2_SaturateSignMagnitude(VDAC_2_sign_enum sign, uint32 magnitude)
{
    uint32 tmpSign = 0u;
    magnitude = (magnitude > VDAC_2_MAX_13bSGNMAG_12bUNSIGN) ? VDAC_2_MAX_13bSGNMAG_12bUNSIGN : magnitude;
    if (VDAC_2_SIGN_POSITIVE != sign)
    {
        tmpSign = 0x00001000UL;
    }
    magnitude = tmpSign | magnitude;
    return (int32) magnitude;
}

/*******************************************************************************
* Function Name: VDAC_2_ConvertUnsigned2TwosComp
****************************************************************************//**
*
* \brief Saturates input to the 13-bit unsigned, and reformats to two's-complement.
*
* The maximum value that the DAC supports is 8191.  The minimum is 0.
*
* \param value
*  The value to saturate and convert.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_ConvertUnsigned2TwosComp
*
*******************************************************************************/
int32 VDAC_2_ConvertUnsigned2TwosComp(uint32 value)
{
    uint32 retVal = 0U;
    /* Saturate value */
    value = ((value > VDAC_2_MAX_13bUNSIGNED) ? VDAC_2_MAX_13bUNSIGNED :value);
    /* Convert from binary offset to 2's complement */
    retVal = value ^ 0x00001000UL;
    return (int32) retVal;
}
/*******************************************************************************
* Function Name: VDAC_2_SetFormat
****************************************************************************//**
*
* \brief This sets the format of the DAC.
*
* The DAC can decode numbers in the formats: 13bit 2's complement, 13bit sign magnitude,
* and 12bit unsigned.
*
* \param dacFormat
*  Which format the DAC should use. See the \ref dacFormat constants for
*  the valid values.
* 
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_SetFormat
*
*******************************************************************************/
void VDAC_2_SetFormat(VDAC_2_format_enum dacFormat)
{
    switch (dacFormat) 
    {
    case VDAC_2_FORMAT_13SIGNMAG:
        VDAC_2_UAB_SetDacMode(CyUAB_DAC_MODE_UNSIGNED12); /* Hardware does no conversions. */
        break;
    case VDAC_2_FORMAT_13TWOSCOMP:
    default: /* Other format requires UAB to be set in DACMode 2 */
        VDAC_2_UAB_SetDacMode(CyUAB_DAC_MODE_SIGNED13); /* Hardware converts negative numbers to sign-mag. */
        break;
    }
    return;
}

/*******************************************************************************
* Function Name: VDAC_2_SetStrobeMode
****************************************************************************//**
* \brief Set whether a hardware strobe is required to update DAC value.
*
* Invalid input results in no change.
*
* \param isHWStrobed
*  Whether to continuously update or require HW strobe. 
*  See the \ref isHWStrobed constants for the valid values.
*
* \sideeffect
*  This is a side effect section.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_SetStrobeMode
*
*******************************************************************************/
void VDAC_2_SetStrobeMode(VDAC_2_strobe_mode_enum isHWStrobed)
{
    switch(isHWStrobed)
    {
    case VDAC_2_STROBE_CONTINUOUSLY:
        /* Strobe clock treats strobe signal as "modbit", so to not use HW strobe
           set the strobe clock to a regular clock. */
        VDAC_2_UAB_SetStrobeClock(CyUAB_CLK_PHI1);
        break;
    case VDAC_2_STROBE_FROM_TERMINAL:
        /* Strobe clock treats strobe signal as "modbit", so to use HW strobe
           set the strobe clock to a mod clock. Use PHI11, since we need a waveform
           that is PHI1 when strobe is high, and 0 when strobe is low.*/
        VDAC_2_UAB_SetStrobeClock(CyUAB_CLK_PHI11);
        break;
    default:
        break;
    }
    return;
}

/*******************************************************************************
* Function Name: VDAC_2_SetHiZ
****************************************************************************//**
*
* \brief This sets the output state of the DAC.
*
* The output state can be tristated, or restored from tristate.  Invalid input
* results in no change.
*
* \param isHiZ
*  The target setting. See the \ref isHiZ constants for the valid values.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_SetHiZ
*
*******************************************************************************/
void VDAC_2_SetHiZ(VDAC_2_output_state_enum isHiZ)
{
    switch(isHiZ)
    {
    case VDAC_2_OUTSTATE_HIZ:
        VDAC_2_OUTBUFFER_Stop();
        break;
    case VDAC_2_OUTSTATE_DRIVEN:
        VDAC_2_OUTBUFFER_Start();
        break;
    default:
        break;
    }
    
    return;
}

/*******************************************************************************
* Function Name: VDAC_2_SetRange
****************************************************************************//**
*
* \brief Set the range.
*
* \param gainFactor
*  The range to be applied to input codes. See the \ref rangeFactor constants for
*  the valid values.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_SetGain
*
*******************************************************************************/
void VDAC_2_SetRange(VDAC_2_range_enum rangeFactor)
{   
    /* DAC Range is inversely proportional to feedback capacitors, so
       set the feedback capacitors to maximum amount, divided by desired gain.
       This division is built-in to the range_enum definitions, so they may
       simply be set as the feedback capacitance. */
    VDAC_2_UAB_SetCapF((CyUAB_f_cap_enum)rangeFactor);
}


/*******************************************************************************
* Function Name: VDAC_2_Init
****************************************************************************//**
*
* \brief Configures hardware, after reset, according to parameters defined in 
* the customizer.
*
* It is not necessary to call Init() because the Start() API 
* calls this function and is the preferred method to begin the component operation.  
* Init will not necessarily restore a default state if the block is not in a reset state.
* VDAC_2_Init only writes registers when the resulting register will be
* nonzero, and it only writes to registers that the VDAC utilizes.
*
* \sideeffect
*  Component output will be in a high impedance state until 
*  VDAC_2_Enable() is called.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_Init
*
*******************************************************************************/
void VDAC_2_Init(void)
{
    /* Call the default UAB init*/
    VDAC_2_UAB_Init(&VDAC_2_UAB_config);
    /* Set several of the UAB switches or buffers based on what source is used as Vagnd/Vref. */
    #if VDAC_2_UAB_halfuab__VAGND_SRC != VDAC_2_UAB_halfuab__SRC_AGNDBUF
        VDAC_2_UAB_SetStaticSwitch(VDAC_2_SW_EXTAGND, CyUAB_SW_CLOSED);
    #else
        VDAC_2_UAB_SetAgndPower(CyUAB_PWR_HIGH);
    #endif
    
    #if VDAC_2_UAB_halfuab__VREF_SRC != VDAC_2_UAB_halfuab__SRC_REFBUF
        VDAC_2_UAB_SetSwitch(VDAC_2_SW_EXTREFA, CyUAB_CLK_PHI9);
        VDAC_2_UAB_SetSwitch(VDAC_2_SW_EXTREFB, CyUAB_CLK_PHI9);
    #else
        VDAC_2_UAB_SetSwitch(CyUAB_SW_AR_MODBIT, CyUAB_CLK_PHI9);
        VDAC_2_UAB_SetSwitch(CyUAB_SW_BR_MODBIT, CyUAB_CLK_PHI9);
        VDAC_2_UAB_SetRefPower(CyUAB_PWR_HIGH);
    #endif
    
    /* Highest power, Bypass, Enable OA Pump*/
    VDAC_2_OUTBUFFER_Init();
    return;
}

/*******************************************************************************
* Function Name: VDAC_2_Enable
****************************************************************************//**
*
* \brief Enables the component.
*
* It is not necessary to call Enable() because the Start() API 
* calls this function and is the preferred method to begin the component operation.
* Activates the UAB and CTB.  Requires that the blocks have been configured, such
* as by calling VDAC_2_Init().
*
* \sideeffect
*  Causes output state to be driven until set to analog high impedance by, for
*  example, VDAC_2_Stop().
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_2_Enable
*
*******************************************************************************/
void VDAC_2_Enable(void) 
{
    /* Enable the UAB */
    VDAC_2_UAB_Run(1u);
    /* Enable the CTB */
    VDAC_2_OUTBUFFER_Enable();
    return;
}
/* [] END OF FILE */
