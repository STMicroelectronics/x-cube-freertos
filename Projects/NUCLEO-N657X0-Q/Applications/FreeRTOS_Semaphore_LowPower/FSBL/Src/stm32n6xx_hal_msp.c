/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32n6xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{

  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
  * @brief LPTIM MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hlptim: LPTIM handle pointer
  * @retval None
  */
void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef* hlptim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hlptim->Instance==LPTIM2)
  {
    /* USER CODE BEGIN LPTIM2_MspInit 0 */

    /* USER CODE END LPTIM2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LPTIM2;
    PeriphClkInitStruct.Lptim2ClockSelection = RCC_LPTIM2CLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_LPTIM2_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**LPTIM2 GPIO Configuration
    PE0     ------> LPTIM2_ETR
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_LPTIM2;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* LPTIM2 interrupt Init */
    HAL_NVIC_SetPriority(LPTIM2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(LPTIM2_IRQn);
    /* USER CODE BEGIN LPTIM2_MspInit 1 */
    /* Enable LPTIM clock during Low Power mode */    
    __HAL_RCC_LPTIM2_CLK_SLEEP_ENABLE();

    /* USER CODE END LPTIM2_MspInit 1 */

  }

}

/**
  * @brief LPTIM MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hlptim: LPTIM handle pointer
  * @retval None
  */
void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef* hlptim)
{
  if(hlptim->Instance==LPTIM2)
  {
    /* USER CODE BEGIN LPTIM2_MspDeInit 0 */

    /* Force the LPTIM2 Periheral Clock Reset */
    __HAL_RCC_LPTIM2_FORCE_RESET();

    /* Release the LPTIM2 Periheral Clock Reset */
    __HAL_RCC_LPTIM2_RELEASE_RESET();

    /* USER CODE END LPTIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPTIM2_CLK_DISABLE();

    /**LPTIM2 GPIO Configuration
    PE0     ------> LPTIM2_ETR
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0);

    /* LPTIM2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(LPTIM2_IRQn);
    /* USER CODE BEGIN LPTIM2_MspDeInit 1 */

    /* USER CODE END LPTIM2_MspDeInit 1 */
  }

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
