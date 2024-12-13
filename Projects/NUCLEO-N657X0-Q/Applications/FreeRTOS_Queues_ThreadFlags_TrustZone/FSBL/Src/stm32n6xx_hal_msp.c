/**
  ******************************************************************************
  * @file    stm32n6xx_hal_msp.c
  * @author  GPM Application Team
  * @brief   HAL MSP module.
  *          This file should be copied to the application folder and renamed
  *          to stm32n6xx_hal_msp.c
  *
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32N6xx_HAL_Driver
  * @{
  */

/** @defgroup HAL_MSP HAL MSP module driver
  * @brief HAL MSP module.
  * @{
  */

/* Private typedefs ----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define HSLV_OTP 124
#define VDDIO3_HSLV_MASK (1<<15)
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the Global MSP.
  * @retval None
  */
void HAL_MspInit(void)
{
}

/**
  * @brief  DeInitialize the Global MSP.
  * @retval None
  */
void HAL_MspDeInit(void)
{
}

/**
  * @brief XSPI MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hxspi: XSPI handle pointer
  * @retval None
  */
void HAL_XSPI_MspInit(XSPI_HandleTypeDef *hxspi)
{

  if (hxspi->Instance == XSPI2)
  {
    BSEC_HandleTypeDef hbsec;
    uint32_t fuse_data = 0;

    /* Enable BSEC & SYSCFG clocks to ensure BSEC data accesses */
    __HAL_RCC_BSEC_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    hbsec.Instance = BSEC;
    if (HAL_BSEC_OTP_Read(&hbsec, HSLV_OTP, &fuse_data) != HAL_OK)
    {
      Error_Handler();
    }

    if (fuse_data & VDDIO3_HSLV_MASK)
    {
      /* High speed IO optimization is enabled */
      RCC_PeriphCLKInitTypeDef PeriphClkInit;

      /*  Select IC3 clock from PLL1 at 200MHz (1200/6) as XSPI2 source */
      PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_XSPI2;
      PeriphClkInit.Xspi2ClockSelection = RCC_XSPI2CLKSOURCE_IC3;
      PeriphClkInit.ICSelection[RCC_IC3].ClockSelection = RCC_ICCLKSOURCE_PLL1;
      PeriphClkInit.ICSelection[RCC_IC3].ClockDivider = 6;
      if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
      {
        Error_Handler();
      }
    }
    else
    {
      /* High speed IO optimization is disabled, lower XSPI clock speed */
      RCC_PeriphCLKInitTypeDef PeriphClkInit;

      /*  Select IC3 clock from PLL1 at 50MHz (1200/24) as XSPI2 source */
      PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_XSPI2;
      PeriphClkInit.Xspi2ClockSelection = RCC_XSPI2CLKSOURCE_IC3;
      PeriphClkInit.ICSelection[RCC_IC3].ClockSelection = RCC_ICCLKSOURCE_PLL1;
      PeriphClkInit.ICSelection[RCC_IC3].ClockDivider = 24;
      if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
      {
        Error_Handler();
      }
    }

    /* Set PWR configuration for IO speed optimization */
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWREx_EnableVddIO3();
    HAL_PWREx_ConfigVddIORange(PWR_VDDIO3, PWR_VDDIO_RANGE_1V8);
    /* Set SYSCFG configuration for IO speed optimization (clock already enabled) */
    HAL_SYSCFG_EnableVDDIO3CompensationCell();

    /* Enable the XSPI memory interface clock */
    __HAL_RCC_XSPI2_CLK_ENABLE();

    /* Set GPIO pin configuration for XSPI operation */
    {
      __HAL_RCC_GPION_CLK_ENABLE();
      GPIO_InitTypeDef GPIO_InitStruct = {0};
      GPIO_InitStruct.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
                                  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_8 | \
                                  GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
      GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
      GPIO_InitStruct.Pull      = GPIO_NOPULL;
      GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P2;
      HAL_GPIO_Init(GPION, &GPIO_InitStruct);
    }
  }
}

/**
  * @brief XSPI MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @retval None
  */
void HAL_XSPI_MspDeInit(XSPI_HandleTypeDef *hxspi)
{
  if(hxspi->Instance==XSPI2)
  {
    /* Peripheral clock disable */
    __HAL_RCC_XSPI2_CLK_DISABLE();

    /* De-Configure pins */
    HAL_GPIO_DeInit(GPION, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
                           GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_8 | \
                           GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);
  }
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
