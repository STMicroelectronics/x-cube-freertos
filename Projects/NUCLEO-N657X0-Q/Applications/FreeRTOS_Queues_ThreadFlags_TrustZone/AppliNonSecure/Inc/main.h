/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"
#include "secure_nsc.h"
#include <stdio.h>
/* Exported constants --------------------------------------------------------*/
#define LED_RED_GPIO_Port   GPIOG
#define LED_RED_Pin         GPIO_PIN_10
#define LED_BLUE_GPIO_Port  GPIOG
#define LED_BLUE_Pin        GPIO_PIN_8
/* Exported macro ------------------------------------------------------------*/
#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
  #if defined ( __ICCARM__ )
  #  define CMSE_NS_CALL  __cmse_nonsecure_call
  #  define CMSE_NS_ENTRY __cmse_nonsecure_entry
  #else
  #  define CMSE_NS_CALL  __attribute((cmse_nonsecure_call))
  #  define CMSE_NS_ENTRY __attribute((cmse_nonsecure_entry))
  #endif
#endif
/* Exported types ------------------------------------------------------------*/
#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
  /* Function pointer declaration in non-secure*/
  typedef void (CMSE_NS_CALL *funcptr)(void);

  /* typedef for non-secure callback functions */
  typedef funcptr funcptr_NS;
#endif

/* Exported functions ------------------------------------------------------- */
void Error_Handler(void);
/******************************************************************************/
#ifdef __MAIN_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* Exported variables ------------------------------------------------------- */

/******************************************************************************/
#endif /* __MAIN_H */

