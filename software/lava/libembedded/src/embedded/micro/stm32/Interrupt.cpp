#include <embedded/micro/stm32/Interrupt.h>
#include <stdio.h>

/*lint -e527 */
/*lint -e716 */
/*lint -e528 */

using Embedded::Micro::STM32::Interrupt;

Interrupt * Interrupt::_ISRVectorTable[];

// Interrupt::Interrupt(INT_PORT port, INT_PIN pin, EXTIMode_TypeDef mode, EXTITrigger_TypeDef trigger, PREEMPTION_PRIORITY prem, SUB_PRIORITY sub)
// {
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

//     // Map PG6 to one of the external interrupt lines
//     SYSCFG_EXTILineConfig((uint8_t)port, (uint8_t)pin);

//     EXTI_InitTypeDef exti;
//     exti.EXTI_Line      = (uint32_t)1 << ((uint32_t)pin);
//     exti.EXTI_Mode      = mode;
//     exti.EXTI_Trigger   = trigger;
//     exti.EXTI_LineCmd   = ENABLE;
//     EXTI_Init(&exti);

//     // Enable this interrupt in the NVIC
//     NVIC_InitTypeDef ih;
//     ih.NVIC_IRQChannelCmd                   = ENABLE;
//     ih.NVIC_IRQChannelPreemptionPriority    = (uint8_t)prem;
//     ih.NVIC_IRQChannelSubPriority           = (uint8_t)sub;
//     switch (pin)
//     {
//         case INT_PIN_0:
//             ih.NVIC_IRQChannel  = static_cast<uint8_t>(EXTI0_IRQn);
//             break;
//         case INT_PIN_1:
//             ih.NVIC_IRQChannel  = static_cast<uint8_t>(EXTI1_IRQn);
//             break;
//         case INT_PIN_2:
//             ih.NVIC_IRQChannel  = static_cast<uint8_t>(EXTI2_IRQn);
//             break;
//         case INT_PIN_3:
//             ih.NVIC_IRQChannel  = static_cast<uint8_t>(EXTI3_IRQn);
//             break;
//         case INT_PIN_4:
//             ih.NVIC_IRQChannel  = static_cast<uint8_t>(EXTI4_IRQn);
//             break;
//         case INT_PIN_5:
//         case INT_PIN_6:
//         case INT_PIN_7:
//         case INT_PIN_8:
//         case INT_PIN_9:
//             ih.NVIC_IRQChannel  = static_cast<uint8_t>(EXTI9_5_IRQn);
//             break;
//         case INT_PIN_10:
//         case INT_PIN_11:
//         case INT_PIN_12:
//         case INT_PIN_13:
//         case INT_PIN_14:
//         case INT_PIN_15:
//             ih.NVIC_IRQChannel  = static_cast<uint8_t>(EXTI15_10_IRQn);
//             break;
//         default:
//             break;
//     }

//     NVIC_Init(&ih);
// }

Interrupt::Interrupt(IRQn_Type irq, PREEMPTION_PRIORITY prem, SUB_PRIORITY sub)
{
    // NVIC_InitTypeDef ih;
    // ih.NVIC_IRQChannel                      = static_cast<uint8_t>(irq);
    // ih.NVIC_IRQChannelCmd                   = ENABLE;
    // ih.NVIC_IRQChannelPreemptionPriority    = (uint8_t)prem;
    // ih.NVIC_IRQChannelSubPriority           = (uint8_t)sub;
    // NVIC_Init(&ih);
    HAL_NVIC_SetPriority(irq, prem, sub);
    HAL_NVIC_EnableIRQ(irq);
}


Interrupt::~Interrupt()
{

}

void Interrupt::Register(ISR_ROUTINE intNumber, Interrupt *isr)
{
    _ISRVectorTable[intNumber] = isr;
}

void Interrupt::Unregister(ISR_ROUTINE intNumber)
{
    _ISRVectorTable[intNumber] = NULL;
}

/*
 * Interrupt handlers, no brief comments, these functions are named after the
 * interrupt vectors. Refer to the Reference Manual for details
 */
#if 1
#ifdef __cplusplus
 extern "C" {
#endif

void NMI_Handler(void)
{
    if (Interrupt::_ISRVectorTable[Interrupt::ISR_NMI_HANDLER] != NULL)
    {
        Interrupt::_ISRVectorTable[Interrupt::ISR_NMI_HANDLER]->ISR();
    }
    else
    {
        while(1){};
    }
}

__attribute__ ((externally_visible))
void prvGetRegistersFromStack( uint32_t *pulFaultStackAddress )
{
/* These are volatile to try and prevent the compiler/linker optimising them
away as the variables never actually get used.  If the debugger won't show the
values of the variables, make them global my moving their declaration outside
of this function. */
volatile uint32_t r0;
volatile uint32_t r1;
volatile uint32_t r2;
volatile uint32_t r3;
volatile uint32_t r12;
volatile uint32_t lr; /* Link register. */
volatile uint32_t pc; /* Program counter. */
volatile uint32_t psr;/* Program status register. */

// Add (void) cast to silence gcc warning
    (void)(r0  = pulFaultStackAddress[ 0 ]);
    (void)(r1  = pulFaultStackAddress[ 1 ]);
    (void)(r2  = pulFaultStackAddress[ 2 ]);
    (void)(r3  = pulFaultStackAddress[ 3 ]);

    (void)(r12 = pulFaultStackAddress[ 4 ]);
    (void)(lr  = pulFaultStackAddress[ 5 ]);
    (void)(pc  = pulFaultStackAddress[ 6 ]);
    (void)(psr = pulFaultStackAddress[ 7 ]);

    /* When the following line is hit, the variables contain the register values. */
    for( ;; );  //lint !e722 ; is ok
}   //lint !e550 !e818 : lots of unreferenced variables, don't worry about const * parameter


void HardFault_Handler(void)
{
    __asm volatile
      (
          " tst lr, #4                                                \n"
          " ite eq                                                    \n"
          " mrseq r0, msp                                             \n"
          " mrsne r0, psp                                             \n"
          " ldr r1, [r0, #24]                                         \n"
          " ldr r2, handler2_address_const                            \n"
          " bx r2                                                     \n"
          " handler2_address_const: .word prvGetRegistersFromStack    \n"
      );
  /* Go to infinite loop when Hard Fault exception occurs */
  for(;;)
  {
  }
}

void MemManage_Handler(void)
{
    for(;;)
    {
    }
}
void BusFault_Handler(void)
{
    for(;;)
    {
    }
}
void UsageFault_Handler(void)
{
    for(;;)
    {
    }
}
void SysTick_Handler(void)
{
    uint16_t index = static_cast<uint16_t>(Interrupt::ISR_SysTick_Handler);
    if (Interrupt::_ISRVectorTable[index] != NULL)
    {
        Interrupt::_ISRVectorTable[index]->ISR();
    }
}

// void MemManage_Handler(void)
// {
//   /* Go to infinite loop when Memory Manage exception occurs */
//   for(;;)
//   {
//   }
// }

// void BusFault_Handler(void)
// {
//   /* Go to infinite loop when Bus Fault exception occurs */
//   for(;;)
//   {
//   }
// }

// void UsageFault_Handler(void)
// {
//   /* Go to infinite loop when Usage Fault exception occurs */
//   for(;;)
//   {
//   }
// }

// void SVC_Handler(void)
// {
// }

// void DebugMon_Handler(void)
// {
// }

// void PendSV_Handler(void)
// {
// }

// void SysTick_Handler(void)
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_SYSTICK_HANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }


// void WWDG_IRQHandler()
// {
//     for(;;){};
// }
// void PVD_IRQHandler()
// {
//     for(;;){};
// }
// void TAMP_STAMP_IRQHandler()
// {
//     for(;;){};
// }
// void RTC_WKUP_IRQHandler()
// {
//     for(;;){};
// }
// void FLASH_IRQHandler()
// {
//     for(;;){};
// }
// void RCC_IRQHandler()
// {
//     for(;;){};
// }
// void EXTI0_IRQHandler()
// {
//     EXTI_ClearITPendingBit(EXTI_Line0);
//     Interrupt::_ISRVectorTable[Interrupt::ISR_EXTI0_IRQHANDLER]->ISR();
// }
// void EXTI1_IRQHandler()
// {
//     EXTI_ClearITPendingBit(EXTI_Line1);
//     Interrupt::_ISRVectorTable[Interrupt::ISR_EXTI1_IRQHANDLER]->ISR();
// }
// void EXTI2_IRQHandler()
// {
//     EXTI_ClearITPendingBit(EXTI_Line2);
//     Interrupt::_ISRVectorTable[Interrupt::ISR_EXTI2_IRQHANDLER]->ISR();
// }
// void EXTI3_IRQHandler()
// {
//     EXTI_ClearITPendingBit(EXTI_Line3);
//     Interrupt::_ISRVectorTable[Interrupt::ISR_EXTI3_IRQHANDLER]->ISR();
// }
// void EXTI4_IRQHandler()
// {
//     EXTI_ClearITPendingBit(EXTI_Line4);
//     Interrupt::_ISRVectorTable[Interrupt::ISR_EXTI4_IRQHANDLER]->ISR();
// }
// void DMA1_Stream0_IRQHandler()
// {

//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA1_STREAM0_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA1_Stream1_IRQHandler()
// {

//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA1_STREAM1_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA1_Stream2_IRQHandler()
// {

//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA1_STREAM2_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA1_Stream3_IRQHandler()
// {

//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA1_STREAM3_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA1_Stream4_IRQHandler()
// {

//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA1_STREAM4_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA1_Stream5_IRQHandler()
// {

//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA1_STREAM5_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA1_Stream6_IRQHandler()
// {

//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA1_STREAM6_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void ADC_IRQHandler()
// {
//     for(;;){};
// }
// void CAN1_TX_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_CAN1_TX_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void CAN1_RX0_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_CAN1_RX0_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void CAN1_RX1_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_CAN1_RX1_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void CAN1_SCE_IRQHandler()
// {
//     for(;;){};
// }
// void EXTI9_5_IRQHandler()
// {
//     uint32_t extLine;
//     uint32_t routine = (uint32_t)Interrupt::ISR_EXTI5_IRQHANDLER;
//     for (extLine = EXTI_Line5; extLine <= EXTI_Line9; extLine <<= 1, routine++)
//     {
//         if (EXTI_GetITStatus(extLine) == SET)
//         {
//             EXTI_ClearITPendingBit(extLine);
//             Interrupt::_ISRVectorTable[routine]->ISR();
//         }
//     }
// }
// void TIM1_BRK_TIM9_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_TIM1_BRK_TIM9_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void TIM1_UP_TIM10_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_TIM1_UP_TIM10_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void TIM1_TRG_COM_TIM11_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_TIM1_TRG_COM_TIM11_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void TIM1_CC_IRQHandler()
// {
//     for(;;){};
// }
// void TIM2_IRQHandler()
// {
//     for(;;){};
// }
// void TIM3_IRQHandler()
// {
//     for(;;){};
// }
// void TIM4_IRQHandler()
// {
//     for(;;){};
// }
// void I2C1_EV_IRQHandler()
// {
//     for(;;){};
// }
// void I2C1_ER_IRQHandler()
// {
//     for(;;){};
// }
// void I2C2_EV_IRQHandler()
// {
//     for(;;){};
// }
// void I2C2_ER_IRQHandler()
// {
//     for(;;){};
// }
// void SPI1_IRQHandlerv()
// {
//     for(;;){};
// }
// void SPI2_IRQHandler()
// {
//     for(;;){};
// }
// void USART1_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_USART1_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void USART2_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_USART2_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void USART3_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_USART3_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void EXTI15_10_IRQHandler()
// {
//     uint32_t extLine;
//     uint32_t routine = (uint32_t)Interrupt::ISR_EXTI10_IRQHANDLER;
//     for (extLine = EXTI_Line10; extLine <= EXTI_Line15; extLine <<= 1, routine++)
//     {
//         if (EXTI_GetITStatus(extLine) == SET)
//         {
//             EXTI_ClearITPendingBit(extLine);
//             Interrupt::_ISRVectorTable[routine]->ISR();
//         }
//     }
// }
// void RTC_Alarm_IRQHandler()
// {
//     for(;;){};
// }
// void OTG_FS_WKUP_IRQHandler()
// {
//     for(;;){};
// }
// void TIM8_BRK_TIM12_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_TIM8_BRK_TIM12_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void TIM8_UP_TIM13_IRQHandler()
// {
//     for(;;){};
// }
// void TIM8_TRG_COM_TIM14_IRQHandler()
// {
//     for(;;){};
// }
// void TIM8_CC_IRQHandler()
// {
//     for(;;){};
// }
// void DMA1_Stream7_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA1_STREAM7_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void FSMC_IRQHandler()
// {
//     for(;;){};
// }
// void SDIO_IRQHandler()
// {
//     for(;;){};
// }
// void TIM5_IRQHandler()
// {
//     for(;;){};
// }
// void SPI3_IRQHandler()
// {
//     for(;;){};
// }
// void UART4_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_UART4_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void UART5_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_UART5_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void TIM6_DAC_IRQHandler()
// {
//     for(;;){};
// }
// void TIM7_IRQHandler()
// {
//     for(;;){};
// }
// void DMA2_Stream0_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA2_STREAM0_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA2_Stream1_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA2_STREAM1_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA2_Stream2_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA2_STREAM2_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA2_Stream3_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA2_STREAM3_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA2_Stream4_IRQHandler()
// {

//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA2_STREAM4_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void ETH_IRQHandler()
// {
//     for(;;){};
// }
// void ETH_WKUP_IRQHandler()
// {
//     for(;;){};
// }
// void CAN2_TX_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_CAN2_TX_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void CAN2_RX0_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_CAN2_RX0_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void CAN2_RX1_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_CAN2_RX1_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void CAN2_SCE_IRQHandler()
// {
//     for(;;){};
// }
// void OTG_FS_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_OTG_FS_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA2_Stream5_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA2_STREAM5_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA2_Stream6_IRQHandler()
// {

//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA2_STREAM6_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void DMA2_Stream7_IRQHandler()
// {

//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_DMA2_STREAM7_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void USART6_IRQHandler()
// {
//     uint16_t index = static_cast<uint16_t>(Interrupt::ISR_USART6_IRQHANDLER);
//     if (Interrupt::_ISRVectorTable[index] != NULL)
//     {
//         Interrupt::_ISRVectorTable[index]->ISR();
//     }
// }
// void I2C3_EV_IRQHandler()
// {
//     for(;;){};
// }
// void I2C3_ER_IRQHandler()
// {
//     for(;;){};
// }
// void OTG_HS_EP1_OUT_IRQHandler()
// {
//     for(;;){};
// }
// void OTG_HS_EP1_IN_IRQHandler()
// {
//     for(;;){};
// }
// void OTG_HS_WKUP_IRQHandler()
// {
//     for(;;){};
// }
// void OTG_HS_IRQHandler()
// {
//     for(;;){};
// }
// void DCMI_IRQHandler()
// {
//     for(;;){};
// }
// void CRYP_IRQHandler()
// {
//     for(;;){};
// }
// void HASH_RNG_IRQHandler()
// {
//     for(;;){};
// }
// void FPU_IRQHandler()
// {
//     for(;;){};
// }

#ifdef __cplusplus
 }
#endif
#endif

