/*******************************************************************************
* File Name: ADC_1_INT.c
* Version 2.0
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2015-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_1.h"
#include "cyapicallbacks.h"

/******************************************************************************
* Custom Declarations and Variables
* - add user include files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_1_SYS_VAR`  */

/* `#END`  */

/******************************************************************************
* Function Name: ADC_1_ISR
*******************************************************************************
*
* \brief Handle Interrupt Service Routine.
*
* \param None
*
* \return None
*
* \sideeffect None
*
******************************************************************************/
CY_ISR( ADC_1_ISR )
{
    uint32 intr_status;

    /* Read interrupt status register */
    intr_status = ADC_1_SAR_INTR_REG;
    
    /* ISR Macro Callback */
    #ifdef ADC_1_ISR_CALLBACK
		ADC_1_ISR_Callback();
	#endif

    /************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    *************************************************************************/
    /* `#START MAIN_ADC_1_ISR`  */

    /* `#END`  */

    /* Clear handled interrupt */
    ADC_1_SAR_INTR_REG = intr_status;
}

/* [] END OF FILE */
