;******************************************************************************
;* File Name          : startup_stm32u073xx.s
;* Author             : MCD Application Team
;* Description        : STM32U073xx devices vector table for MDK-ARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM0 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;* <<< Use Configuration Wizard in Context Menu >>>
;******************************************************************************
;* @attention
;*
;* Copyright (c) 2023 STMicroelectronics.
;* All rights reserved.
;*
;* This software is licensed under terms that can be found in the LICENSE file
;* in the root directory of this software component.
;* If no LICENSE file comes with this software, it is provided AS-IS.
;*
;******************************************************************************
; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
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

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler    PROC
                 EXPORT  Reset_Handler                 [WEAK]
        IMPORT  __main
        IMPORT  SystemInit  
                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IWDG_IRQHandler           [WEAK]
				EXPORT  PVD_PVM_IRQHandler             [WEAK]
                EXPORT  RTC_TAMP_IRQHandler            [WEAK]
                EXPORT  FLASH_ECC_IRQHandler           [WEAK]
                EXPORT  RCC_CRS_IRQHandler             [WEAK]
                EXPORT  EXTI0_1_IRQHandler             [WEAK]
                EXPORT  EXTI2_3_IRQHandler             [WEAK]
                EXPORT  EXTI4_15_IRQHandler            [WEAK]
                EXPORT  USB_DRD_FS_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler       [WEAK]
                EXPORT  DMA1_Channel2_3_IRQHandler     [WEAK]
                EXPORT  DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX_OVR_IRQHandler [WEAK]
                EXPORT  ADC_COMP1_2_IRQHandler         [WEAK]
                EXPORT  TIM1_BRK_UP_TRG_COM_IRQHandler [WEAK]
                EXPORT  TIM1_CC_IRQHandler             [WEAK]
                EXPORT  TIM2_IRQHandler                [WEAK]
                EXPORT  TIM3_IRQHandler                [WEAK]
                EXPORT  TIM6_DAC_LPTIM1_IRQHandler     [WEAK]
                EXPORT  TIM7_LPTIM2_IRQHandler         [WEAK]
                EXPORT  TIM15_LPTIM3_IRQHandler        [WEAK]
                EXPORT  TIM16_IRQHandler               [WEAK]
                EXPORT  TSC_IRQHandler                 [WEAK]
				EXPORT  LCD_IRQHandler                 [WEAK]
                EXPORT  I2C1_IRQHandler                [WEAK]
                EXPORT  I2C2_3_4_IRQHandler            [WEAK]
                EXPORT  SPI1_IRQHandler                [WEAK]
                EXPORT  SPI2_3_IRQHandler              [WEAK]
                EXPORT  USART1_IRQHandler              [WEAK]
                EXPORT  USART2_LPUART2_IRQHandler      [WEAK]
                EXPORT  USART3_LPUART1_IRQHandler      [WEAK]
				EXPORT  USART4_LPUART3_IRQHandler      [WEAK]
			    EXPORT  RNG_CRYP_IRQHandler            [WEAK]


WWDG_IWDG_IRQHandler
PVD_PVM_IRQHandler
RTC_TAMP_IRQHandler
FLASH_ECC_IRQHandler
RCC_CRS_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
USB_DRD_FS_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_3_IRQHandler
DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX_OVR_IRQHandler
ADC_COMP1_2_IRQHandler
TIM1_BRK_UP_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM6_DAC_LPTIM1_IRQHandler
TIM7_LPTIM2_IRQHandler
TIM15_LPTIM3_IRQHandler
TIM16_IRQHandler
TSC_IRQHandler
LCD_IRQHandler
I2C1_IRQHandler
I2C2_3_4_IRQHandler
SPI1_IRQHandler
SPI2_3_IRQHandler
USART1_IRQHandler
USART2_LPUART2_IRQHandler
USART3_LPUART1_IRQHandler
USART4_LPUART3_IRQHandler
RNG_CRYP_IRQHandler

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB

                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit

                 ELSE

                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap

__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END
