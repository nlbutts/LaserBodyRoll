#ifndef EMBEDDED_MICRO_STM32_INTERRUPT_H_
#define EMBEDDED_MICRO_STM32_INTERRUPT_H_

#include <libst_config.h>

namespace Embedded {
namespace Micro {
namespace STM32 {

class Interrupt
{
    public:
        typedef enum
        {
            INT_PORT_A,
            INT_PORT_B,
            INT_PORT_C,
            INT_PORT_D,
            INT_PORT_E,
            INT_PORT_F,
            INT_PORT_G,
            INT_PORT_H,
            INT_PORT_I,
        } INT_PORT;

        typedef enum
        {
            INT_PIN_0,
            INT_PIN_1,
            INT_PIN_2,
            INT_PIN_3,
            INT_PIN_4,
            INT_PIN_5,
            INT_PIN_6,
            INT_PIN_7,
            INT_PIN_8,
            INT_PIN_9,
            INT_PIN_10,
            INT_PIN_11,
            INT_PIN_12,
            INT_PIN_13,
            INT_PIN_14,
            INT_PIN_15,
        } INT_PIN;

        /*
         * These are enums for registerable interrupt calls. Note this doesn't map 1 to 1 with
         * actual ISR. For example in the case of external interrupts there is a one interrupt
         * request to the processor for many external interrupts. The interrupt class splits
         * that up into seperate calls for easier use by the class that wants to register
         */
        typedef enum
        {
            ISR_NMI_HANDLER,
            ISR_HARDFAULT_HANDLER,
            ISR_MEMMANAGE_HANDLER,
            ISR_BUSFAULT_HANDLER,
            ISR_USAGEFAULT_HANDLER,
            ISR_RESERVED1,
            ISR_RESERVED2,
            ISR_RESERVED3,
            ISR_RESERVED4,
            ISR_SVC_Handler,
            ISR_DebugMon_Handler,
            ISR_RESERVED5,
            ISR_PendSV_Handler,
            ISR_SysTick_Handler,
            ISR_WWDG_IRQHandler,
            ISR_PVD_IRQHandler,
            ISR_TAMP_STAMP_IRQHandler,
            ISR_RTC_WKUP_IRQHandler,
            ISR_FLASH_IRQHandler,
            ISR_RCC_IRQHandler,
            ISR_EXTI0_IRQHandler,
            ISR_EXTI1_IRQHandler,
            ISR_EXTI2_TSC_IRQHandler,
            ISR_EXTI3_IRQHandler,
            ISR_EXTI4_IRQHandler,
            ISR_DMA1_Channel1_IRQHandler,
            ISR_DMA1_Channel2_IRQHandler,
            ISR_DMA1_Channel3_IRQHandler,
            ISR_DMA1_Channel4_IRQHandler,
            ISR_DMA1_Channel5_IRQHandler,
            ISR_DMA1_Channel6_IRQHandler,
            ISR_DMA1_Channel7_IRQHandler,
            ISR_ADC1_2_IRQHandler,
            ISR_USB_HP_CAN_TX_IRQHandler,
            ISR_USB_LP_CAN_RX0_IRQHandler,
            ISR_CAN_RX1_IRQHandler,
            ISR_CAN_SCE_IRQHandler,
            ISR_EXTI9_5_IRQHandler,
            ISR_TIM1_BRK_TIM15_IRQHandler,
            ISR_TIM1_UP_TIM16_IRQHandler,
            ISR_TIM1_TRG_COM_TIM17_IRQHandler,
            ISR_TIM1_CC_IRQHandler,
            ISR_TIM2_IRQHandler,
            ISR_TIM3_IRQHandler,
            ISR_TIM4_IRQHandler,
            ISR_I2C1_EV_IRQHandler,
            ISR_I2C1_ER_IRQHandler,
            ISR_I2C2_EV_IRQHandler,
            ISR_I2C2_ER_IRQHandler,
            ISR_SPI1_IRQHandler,
            ISR_SPI2_IRQHandler,
            ISR_USART1_IRQHandler,
            ISR_USART2_IRQHandler,
            ISR_USART3_IRQHandler,
            ISR_EXTI15_10_IRQHandler,
            ISR_RTC_Alarm_IRQHandler,
            ISR_USBWakeUp_IRQHandler,
            ISR_TIM8_BRK_IRQHandler,
            ISR_TIM8_UP_IRQHandler,
            ISR_TIM8_TRG_COM_IRQHandler,
            ISR_TIM8_CC_IRQHandler,
            ISR_ADC3_IRQHandler,
            ISR_FMC_IRQHandler,
            ISR_RESERVED6,
            ISR_RESERVED7,
            ISR_SPI3_IRQHandler,
            ISR_UART4_IRQHandler,
            ISR_UART5_IRQHandler,
            ISR_TIM6_DAC_IRQHandler,
            ISR_TIM7_IRQHandler,
            ISR_DMA2_Channel1_IRQHandler,
            ISR_DMA2_Channel2_IRQHandler,
            ISR_DMA2_Channel3_IRQHandler,
            ISR_DMA2_Channel4_IRQHandler,
            ISR_DMA2_Channel5_IRQHandler,
            ISR_ADC4_IRQHandler,
            ISR_RESERVED8,
            ISR_RESERVED9,
            ISR_COMP1_2_3_IRQHandler,
            ISR_COMP4_5_6_IRQHandler,
            ISR_COMP7_IRQHandler,
            ISR_RESERVED10,
            ISR_RESERVED11,
            ISR_RESERVED12,
            ISR_RESERVED13,
            ISR_RESERVED14,
            ISR_I2C3_EV_IRQHandler,
            ISR_I2C3_ER_IRQHandler,
            ISR_USB_HP_IRQHandler,
            ISR_USB_LP_IRQHandler,
            ISR_USBWakeUp_RMP_IRQHandler,
            ISR_TIM20_BRK_IRQHandler,
            ISR_TIM20_UP_IRQHandler,
            ISR_TIM20_TRG_COM_IRQHandler,
            ISR_TIM20_CC_IRQHandler,
            ISR_FPU_IRQHandler,
            ISR_RESERVED15,
            ISR_RESERVED16,
            ISR_SPI4_IRQHandler,
            ISR_MAX_HANDLERS
        } ISR_ROUTINE;

        typedef enum
        {
            PREEMPT_PRIO_0,
            PREEMPT_PRIO_1,
            PREEMPT_PRIO_2,
            PREEMPT_PRIO_3,
            PREEMPT_PRIO_4,
            PREEMPT_PRIO_5,
            PREEMPT_PRIO_6,
            PREEMPT_PRIO_7,
            PREEMPT_PRIO_8,
            PREEMPT_PRIO_9,
            PREEMPT_PRIO_10,
            PREEMPT_PRIO_11,
            PREEMPT_PRIO_12,
            PREEMPT_PRIO_13,
            PREEMPT_PRIO_14,
            PREEMPT_PRIO_15,
        } PREEMPTION_PRIORITY;

        typedef enum
        {
            SUB_PRIO_0,
            SUB_PRIO_1,
            SUB_PRIO_2,
            SUB_PRIO_3,
            SUB_PRIO_4,
            SUB_PRIO_5,
            SUB_PRIO_6,
            SUB_PRIO_7,
            SUB_PRIO_8,
            SUB_PRIO_9,
            SUB_PRIO_10,
            SUB_PRIO_11,
            SUB_PRIO_12,
            SUB_PRIO_13,
            SUB_PRIO_14,
            SUB_PRIO_15,
        } SUB_PRIORITY;

        /**
         * Setup an interrupt for an external pin. The external interrupts are a bit weird. There are 16
         * external interrupt channels. These channels map from pin numbers to EXTI channels
         * It would be best to group ALL external interrupts into the same port, otherwise
         * conflicts might occur.
         *
         * @param port the port the GPIO is on
         * @param pin the pin number of the GPIO
         * @param mode either generate an interrupt or an event (events appear to be one shots)
         * @param trigger rising, falling or both trigger
         * @param prem preemtion priority as defined in RM
         * @param sub sub channel priority as defined in RM
         */
        //Interrupt(INT_PORT port, INT_PIN pin, EXTIMode_TypeDef mode, EXTITrigger_TypeDef trigger, PREEMPTION_PRIORITY prem = PREEMPT_PRIO_1, SUB_PRIORITY sub = SUB_PRIO_1);

        /**
         * Setup an interrupt for other sources
         *
         * @param irq enum of irq channel
         * @param prem preemtion priority as defined in RM
         * @param sub sub channel priority as defined in RM
         */
        Interrupt(IRQn_Type irq, PREEMPTION_PRIORITY prem = PREEMPT_PRIO_1, SUB_PRIORITY sub = SUB_PRIO_1);

        virtual ~Interrupt();

        /**
         * This function allows you to inherit this class and create your own ISR function
         *
         */
        virtual void ISR() = 0;

        /**
         * This function is used to register an Interrupt class with the ISR number
         *
         * @param intNumber the ISR routine to register
         * @param isr the Interrupt class to register with the interrupt number
         */
        static void Register(ISR_ROUTINE intNumber, Interrupt *isr);

        /**
         * Remove an ISR from the ISR table
         *
         * @param intNumber the ISR routine to register
         */
        static void Unregister(ISR_ROUTINE intNumber);

        static Interrupt* _ISRVectorTable[ISR_MAX_HANDLERS];
    private:
};

} // namespace STM32
} // namespace Micro
} // namespace Embedded

#endif /* EMBEDDED_MICRO_STM32_INTERRUPT_H_ */
