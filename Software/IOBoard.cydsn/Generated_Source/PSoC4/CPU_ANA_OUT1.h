/*******************************************************************************
* File Name: CPU_ANA_OUT1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CPU_ANA_OUT1_H) /* Pins CPU_ANA_OUT1_H */
#define CY_PINS_CPU_ANA_OUT1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CPU_ANA_OUT1_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} CPU_ANA_OUT1_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CPU_ANA_OUT1_Read(void);
void    CPU_ANA_OUT1_Write(uint8 value);
uint8   CPU_ANA_OUT1_ReadDataReg(void);
#if defined(CPU_ANA_OUT1__PC) || (CY_PSOC4_4200L) 
    void    CPU_ANA_OUT1_SetDriveMode(uint8 mode);
#endif
void    CPU_ANA_OUT1_SetInterruptMode(uint16 position, uint16 mode);
uint8   CPU_ANA_OUT1_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CPU_ANA_OUT1_Sleep(void); 
void CPU_ANA_OUT1_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CPU_ANA_OUT1__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CPU_ANA_OUT1_DRIVE_MODE_BITS        (3)
    #define CPU_ANA_OUT1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CPU_ANA_OUT1_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CPU_ANA_OUT1_SetDriveMode() function.
         *  @{
         */
        #define CPU_ANA_OUT1_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CPU_ANA_OUT1_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CPU_ANA_OUT1_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CPU_ANA_OUT1_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CPU_ANA_OUT1_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CPU_ANA_OUT1_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CPU_ANA_OUT1_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CPU_ANA_OUT1_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CPU_ANA_OUT1_MASK               CPU_ANA_OUT1__MASK
#define CPU_ANA_OUT1_SHIFT              CPU_ANA_OUT1__SHIFT
#define CPU_ANA_OUT1_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CPU_ANA_OUT1_SetInterruptMode() function.
     *  @{
     */
        #define CPU_ANA_OUT1_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CPU_ANA_OUT1_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CPU_ANA_OUT1_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CPU_ANA_OUT1_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CPU_ANA_OUT1__SIO)
    #define CPU_ANA_OUT1_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CPU_ANA_OUT1__PC) && (CY_PSOC4_4200L)
    #define CPU_ANA_OUT1_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CPU_ANA_OUT1_USBIO_DISABLE              ((uint32)(~CPU_ANA_OUT1_USBIO_ENABLE))
    #define CPU_ANA_OUT1_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CPU_ANA_OUT1_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CPU_ANA_OUT1_USBIO_ENTER_SLEEP          ((uint32)((1u << CPU_ANA_OUT1_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CPU_ANA_OUT1_USBIO_SUSPEND_DEL_SHIFT)))
    #define CPU_ANA_OUT1_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CPU_ANA_OUT1_USBIO_SUSPEND_SHIFT)))
    #define CPU_ANA_OUT1_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CPU_ANA_OUT1_USBIO_SUSPEND_DEL_SHIFT)))
    #define CPU_ANA_OUT1_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CPU_ANA_OUT1__PC)
    /* Port Configuration */
    #define CPU_ANA_OUT1_PC                 (* (reg32 *) CPU_ANA_OUT1__PC)
#endif
/* Pin State */
#define CPU_ANA_OUT1_PS                     (* (reg32 *) CPU_ANA_OUT1__PS)
/* Data Register */
#define CPU_ANA_OUT1_DR                     (* (reg32 *) CPU_ANA_OUT1__DR)
/* Input Buffer Disable Override */
#define CPU_ANA_OUT1_INP_DIS                (* (reg32 *) CPU_ANA_OUT1__PC2)

/* Interrupt configuration Registers */
#define CPU_ANA_OUT1_INTCFG                 (* (reg32 *) CPU_ANA_OUT1__INTCFG)
#define CPU_ANA_OUT1_INTSTAT                (* (reg32 *) CPU_ANA_OUT1__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CPU_ANA_OUT1_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CPU_ANA_OUT1__SIO)
    #define CPU_ANA_OUT1_SIO_REG            (* (reg32 *) CPU_ANA_OUT1__SIO)
#endif /* (CPU_ANA_OUT1__SIO_CFG) */

/* USBIO registers */
#if !defined(CPU_ANA_OUT1__PC) && (CY_PSOC4_4200L)
    #define CPU_ANA_OUT1_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CPU_ANA_OUT1_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CPU_ANA_OUT1_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CPU_ANA_OUT1_DRIVE_MODE_SHIFT       (0x00u)
#define CPU_ANA_OUT1_DRIVE_MODE_MASK        (0x07u << CPU_ANA_OUT1_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CPU_ANA_OUT1_H */


/* [] END OF FILE */
