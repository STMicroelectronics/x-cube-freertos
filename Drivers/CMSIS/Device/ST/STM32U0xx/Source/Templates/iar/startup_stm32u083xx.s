;********************************************************************************
;* File Name          : startup_stm32u083xx.s
;* Author             : MCD Application Team
;* Description        : STM32U083xx Ultra Low Power Devices vector
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == _iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR
;*                        address.
;*                      - Branches to main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M0+ processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;********************************************************************************
;* @attention
;*
;* Copyright (c) 2023 STMicroelectronics.
;* All rights reserved.
;*
;* This software is licensed under terms that can be found in the LICENSE file
;* in the root directory of this software component.
;* If no LICENSE file comes with this software, it is provided AS-IS.
;*
;*******************************************************************************
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler                  ; Reset Handler

        DCD     NMI_Handler                    ; NMI Handler
        DCD     HardFault_Handler              ; Hard Fault Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     SVC_Handler                    ; SVCall Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     PendSV_Handler                 ; PendSV Handler
        DCD     SysTick_Handler                ; SysTick Handler

         ; External Interrupts
        DCD     WWDG_IWDG_IRQHandler              ; Window WatchDog / Independent Watchdog Interrupt
        DCD     PVD_PVM_IRQHandler                ; PVD through EXTI line detection
        DCD     RTC_TAMP_IRQHandler               ; RTC/TAMP through the EXTI line
        DCD     FLASH_ECC_IRQHandler              ; FLASH / ECC
        DCD     RCC_CRS_IRQHandler                ; RCC / CRS
        DCD     EXTI0_1_IRQHandler                ; EXTI Line[0:1]
        DCD     EXTI2_3_IRQHandler                ; EXTI Line[2:3]
        DCD     EXTI4_15_IRQHandler               ; EXTI Line[4:15]
        DCD     USB_DRD_FS_IRQHandler             ; USB global interrupt through EXTI line detection
        DCD     DMA1_Channel1_IRQHandler          ; DMA1 Channel1 interrupt
        DCD     DMA1_Channel2_3_IRQHandler        ; DMA1 Channel2/Channel3 interrupt
        DCD     DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX_OVR_IRQHandler ; DMA1 Channel 4 to Channel 7, DMA2 Channel 1 to Channel 5, DMAMUX overrun
        DCD     ADC_COMP1_2_IRQHandler            ; ADC and COMP1/COMP2 interrupts
        DCD     TIM1_BRK_UP_TRG_COM_IRQHandler    ; TIM1 break, update, trigger, commutation, error, direction change  and index interrupts
        DCD     TIM1_CC_IRQHandler                ; TIM1 Capture Compare interrupt
        DCD     TIM2_IRQHandler                   ; TIM2
        DCD     TIM3_IRQHandler                   ; TIM3
        DCD     TIM6_DAC_LPTIM1_IRQHandler        ; TIM6 / DAC1&3 / LPTIM1 global interrupt
        DCD     TIM7_LPTIM2_IRQHandler            ; TIM7 / LPTIM2 global interrupt
        DCD     TIM15_LPTIM3_IRQHandler           ; TIM15 / LPTIM3 global interrupt
        DCD     TIM16_IRQHandler                  ; TIM16
        DCD     TSC_IRQHandler                    ; TSC global interrupt
        DCD     LCD_IRQHandler                    ; LCD global interrupt
        DCD     I2C1_IRQHandler                   ; I2C1 global interrupt
        DCD     I2C2_3_4_IRQHandler               ; I2C2 / I2C3 / I2C4 global interrupt
        DCD     SPI1_IRQHandler                   ; SPI1 global interrupt
        DCD     SPI2_3_IRQHandler                 ; SPI2 /SPI3 global interrupt
        DCD     USART1_IRQHandler                 ; USART1 global interrupt
        DCD     USART2_LPUART2_IRQHandler         ; USART2, LPUART 2 global interrupt
        DCD     USART3_LPUART1_IRQHandler         ; USART3, LPUART 1 global interrupt
        DCD     USART4_LPUART3_IRQHandler         ; USART4, LPUART 3 global interrupt
        DCD     RNG_CRYP_IRQHandler               ; RNG, CRYPTO global interrupt

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDG_IWDG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG_IWDG_IRQHandler
        B WWDG_IWDG_IRQHandler

        PUBWEAK PVD_PVM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PVD_PVM_IRQHandler
        B PVD_PVM_IRQHandler

        PUBWEAK RTC_TAMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_TAMP_IRQHandler
        B RTC_TAMP_IRQHandler

        PUBWEAK FLASH_ECC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_ECC_IRQHandler
        B FLASH_ECC_IRQHandler

        PUBWEAK RCC_CRS_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCC_CRS_IRQHandler
        B RCC_CRS_IRQHandler

        PUBWEAK EXTI0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_1_IRQHandler
        B EXTI0_1_IRQHandler

        PUBWEAK EXTI2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_3_IRQHandler
        B EXTI2_3_IRQHandler

        PUBWEAK EXTI4_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_15_IRQHandler
        B EXTI4_15_IRQHandler

        PUBWEAK USB_DRD_FS_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_DRD_FS_IRQHandler
        B USB_DRD_FS_IRQHandler

        PUBWEAK DMA1_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel1_IRQHandler
        B DMA1_Channel1_IRQHandler

        PUBWEAK DMA1_Channel2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel2_3_IRQHandler
        B DMA1_Channel2_3_IRQHandler

        PUBWEAK DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX_OVR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX_OVR_IRQHandler
        B DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX_OVR_IRQHandler

        PUBWEAK ADC_COMP1_2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_COMP1_2_IRQHandler
        B ADC_COMP1_2_IRQHandler

        PUBWEAK TIM1_BRK_UP_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_BRK_UP_TRG_COM_IRQHandler
        B TIM1_BRK_UP_TRG_COM_IRQHandler

        PUBWEAK TIM1_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_CC_IRQHandler
        B TIM1_CC_IRQHandler

        PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_IRQHandler
        B TIM2_IRQHandler

        PUBWEAK TIM3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM3_IRQHandler
        B TIM3_IRQHandler

        PUBWEAK TIM6_DAC_LPTIM1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM6_DAC_LPTIM1_IRQHandler
        B TIM6_DAC_LPTIM1_IRQHandler

        PUBWEAK TIM7_LPTIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM7_LPTIM2_IRQHandler
        B TIM7_LPTIM2_IRQHandler

        PUBWEAK TIM15_LPTIM3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM15_LPTIM3_IRQHandler
        B TIM15_LPTIM3_IRQHandler

        PUBWEAK TIM16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM16_IRQHandler
        B TIM16_IRQHandler

        PUBWEAK TSC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TSC_IRQHandler
        B TSC_IRQHandler

        PUBWEAK LCD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LCD_IRQHandler
        B LCD_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK I2C2_3_4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_3_4_IRQHandler
        B I2C2_3_4_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_3_IRQHandler
        B SPI2_3_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_LPUART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_LPUART2_IRQHandler
        B USART2_LPUART2_IRQHandler

        PUBWEAK USART3_LPUART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART3_LPUART1_IRQHandler
        B USART3_LPUART1_IRQHandler

        PUBWEAK USART4_LPUART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART4_LPUART3_IRQHandler
        B USART4_LPUART3_IRQHandler

        PUBWEAK RNG_CRYP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RNG_CRYP_IRQHandler
        B RNG_CRYP_IRQHandler

        END
