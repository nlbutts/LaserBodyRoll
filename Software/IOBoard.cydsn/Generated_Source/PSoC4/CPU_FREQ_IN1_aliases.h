/*******************************************************************************
* File Name: CPU_FREQ_IN1.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CPU_FREQ_IN1_ALIASES_H) /* Pins CPU_FREQ_IN1_ALIASES_H */
#define CY_PINS_CPU_FREQ_IN1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CPU_FREQ_IN1_0			(CPU_FREQ_IN1__0__PC)
#define CPU_FREQ_IN1_0_PS		(CPU_FREQ_IN1__0__PS)
#define CPU_FREQ_IN1_0_PC		(CPU_FREQ_IN1__0__PC)
#define CPU_FREQ_IN1_0_DR		(CPU_FREQ_IN1__0__DR)
#define CPU_FREQ_IN1_0_SHIFT	(CPU_FREQ_IN1__0__SHIFT)
#define CPU_FREQ_IN1_0_INTR	((uint16)((uint16)0x0003u << (CPU_FREQ_IN1__0__SHIFT*2u)))

#define CPU_FREQ_IN1_INTR_ALL	 ((uint16)(CPU_FREQ_IN1_0_INTR))


#endif /* End Pins CPU_FREQ_IN1_ALIASES_H */


/* [] END OF FILE */
