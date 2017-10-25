/***************************************************************************//**
* \file VDAC_1_PM.c  
* \version 1.10
*
* \brief
*  This file provides the power manager source code to the API for PGA 
*  Component.
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

#include "VDAC_1.h" /* Need VDAC's .h */
#include "VDAC_1_UAB.h" /* Need sub-component's functions */
#include "VDAC_1_OUTBUFFER.h" 
/**
* \addtogroup group_globals
* @{
*/
/** Contains configuration of VDAC_1 before sleep. Enable state is the
*   only data required to be preserved. */
static VDAC_1_BACKUP_STRUCT  VDAC_1_backup;
/** @} globals */


/*******************************************************************************   
* Function Name: VDAC_1_Sleep
****************************************************************************//**
*
* \brief
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* \globalvars
*  \ref VDAC_1_backup (W)
*
* \sideeffect
*  None.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_1_Sleep
*
*
* \globalvars
*  \ref VDAC_1_backup
*
*******************************************************************************/
void VDAC_1_Sleep(void) 
{
    /* Save UAB_VDAC enable state */
    if( 0UL != (VDAC_1_UAB_SRAM_CTRL_REG & VDAC_1_UAB_RUN_MASK)  )
    {
        /* Component is enabled */
        VDAC_1_backup.enableState = VDAC_1_BACKUP_BLOCKENABLED;
        if (VDAC_1_OUTBUFFER_CHECK_PWR_MODE_OFF)
        {
            /* Output is not HiZ */
            VDAC_1_backup.enableState |= VDAC_1_BACKUP_OUTPUTDRIVEN;
        }
        /* Stop the configuration */
        VDAC_1_Stop();
    }
    else
    {
        /* Component is disabled */
        VDAC_1_backup.enableState = 0u;
    }
}


/*******************************************************************************
* Function Name: VDAC_1_Wakeup
****************************************************************************//**
*
* \brief
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* \globalvars
*  \ref VDAC_1_backup (R)
*
* \sideeffect
*  None.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_1_Wakeup
*
*
* \globalvars
*  \ref VDAC_1_backup
* 
*******************************************************************************/
void VDAC_1_Wakeup(void)
{
     /* Enables the component operation */
    if((VDAC_1_backup.enableState & VDAC_1_BACKUP_BLOCKENABLED)
        == VDAC_1_BACKUP_BLOCKENABLED) /* If block was enabled... */
    {
        /* Then enable rest of block */
        VDAC_1_Enable();
        /* Set up output buffer first */
        if ((VDAC_1_backup.enableState & VDAC_1_BACKUP_OUTPUTDRIVEN) 
             == VDAC_1_BACKUP_OUTPUTDRIVEN) /* If output was not HiZ */
        {
            VDAC_1_SetHiZ(VDAC_1_OUTSTATE_DRIVEN);
        }
        else
        {
            VDAC_1_SetHiZ(VDAC_1_OUTSTATE_HIZ);
        }
    } /* Do nothing if component was disable before */
}

/* [] END OF FILE */
