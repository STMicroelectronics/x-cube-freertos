/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"
#include <stdio.h>

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported types ------------------------------------------------------------*/

/* Exported constants ------------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions ------------------------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines ------------------------------------------------------------*/
#define LED1_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOG
#define LED2_Pin GPIO_PIN_10
#define LED3_GPIO_Port GPIOG
#define LED3_Pin GPIO_PIN_0

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MAIN_H */

