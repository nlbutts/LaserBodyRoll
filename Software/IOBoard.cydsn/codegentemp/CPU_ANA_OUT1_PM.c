/*******************************************************************************
* File Name: CPU_ANA_OUT1.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "CPU_ANA_OUT1.h"

static CPU_ANA_OUT1_BACKUP_STRUCT  CPU_ANA_OUT1_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CPU_ANA_OUT1_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet CPU_ANA_OUT1_SUT.c usage_CPU_ANA_OUT1_Sleep_Wakeup
*******************************************************************************/
void CPU_ANA_OUT1_Sleep(void)
{
    #if defined(CPU_ANA_OUT1__PC)
        CPU_ANA_OUT1_backup.pcState = CPU_ANA_OUT1_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CPU_ANA_OUT1_backup.usbState = CPU_ANA_OUT1_CR1_REG;
            CPU_ANA_OUT1_USB_POWER_REG |= CPU_ANA_OUT1_USBIO_ENTER_SLEEP;
            CPU_ANA_OUT1_CR1_REG &= CPU_ANA_OUT1_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CPU_ANA_OUT1__SIO)
        CPU_ANA_OUT1_backup.sioState = CPU_ANA_OUT1_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CPU_ANA_OUT1_SIO_REG &= (uint32)(~CPU_ANA_OUT1_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CPU_ANA_OUT1_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to CPU_ANA_OUT1_Sleep() for an example usage.
*******************************************************************************/
void CPU_ANA_OUT1_Wakeup(void)
{
    #if defined(CPU_ANA_OUT1__PC)
        CPU_ANA_OUT1_PC = CPU_ANA_OUT1_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CPU_ANA_OUT1_USB_POWER_REG &= CPU_ANA_OUT1_USBIO_EXIT_SLEEP_PH1;
            CPU_ANA_OUT1_CR1_REG = CPU_ANA_OUT1_backup.usbState;
            CPU_ANA_OUT1_USB_POWER_REG &= CPU_ANA_OUT1_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CPU_ANA_OUT1__SIO)
        CPU_ANA_OUT1_SIO_REG = CPU_ANA_OUT1_backup.sioState;
    #endif
}


/* [] END OF FILE */
