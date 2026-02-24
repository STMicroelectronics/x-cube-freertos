/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_timebase_tim.c
  * @brief   HAL time base based on the hardware TIM.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32wbaxx_hal.h"
#include "stm32wbaxx_hal_tim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TIM_CNT_FREQ 1000000U /* Timer frequency counter : 1 MHz */
#define TIM_FREQ     1000U    /* Timer frequency : 1 kHz => to have 1 ms interrupt */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef        htim17;
/* Private function prototypes -----------------------------------------------*/
void TIM17_IRQHandler(void);
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1U)
void TimeBase_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the TIM17 as a time base source.
  *         The time source is configured  to have 1ms time base with a dedicated
  *         Tick interrupt priority.
  * @note   This function is called  automatically at the beginning of program after
  *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig().
  * @param  TickPriority: Tick interrupt priority.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  RCC_ClkInitTypeDef    clkconfig;
  uint32_t              uwTimclock;
  uint32_t              uwAPB2Prescaler;
  uint32_t              uwPrescalerValue;
  uint32_t              pFLatency;

  HAL_StatusTypeDef     Status;

  /* Enable TIM17 clock */
  __HAL_RCC_TIM17_CLK_ENABLE();

  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

  /* Get APB2 prescaler */
  uwAPB2Prescaler = clkconfig.APB2CLKDivider;
  /* Compute TIM17 clock */
  if (uwAPB2Prescaler == RCC_HCLK_DIV1)
  {
    uwTimclock = HAL_RCC_GetPCLK2Freq();
  }
  else
  {
    uwTimclock = 2UL * HAL_RCC_GetPCLK2Freq();
  }

  /* Compute the prescaler value to have TIM17 counter clock equal to TIM_CNT_FREQ */
  uwPrescalerValue = (uint32_t) ((uwTimclock / TIM_CNT_FREQ) - 1U);

  /* Initialize TIM17 */
  htim17.Instance = TIM17;

  /* Initialize TIMx peripheral as follow:
   * Period = [(TIM_CNT_FREQ/TIM_FREQ) - 1]. to have a (1/TIM_FREQ) s time base.
   * Prescaler = (uwTimclock/TIM_CNT_FREQ - 1) to have a TIM_CNT_FREQ counter clock.
   * ClockDivision = 0
   * Counter direction = Up
   */
  htim17.Init.Period = (TIM_CNT_FREQ / TIM_FREQ) - 1U;
  htim17.Init.Prescaler = uwPrescalerValue;
  htim17.Init.ClockDivision = 0;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;

  Status = HAL_TIM_Base_Init(&htim17);
  if (Status == HAL_OK)
  {
    /* Start the TIM time Base generation in interrupt mode */
    Status = HAL_TIM_Base_Start_IT(&htim17);
    if (Status == HAL_OK)
    {
      if (TickPriority < (1UL << __NVIC_PRIO_BITS))
      {
        /* Enable the TIM17 global Interrupt */
        HAL_NVIC_SetPriority(TIM17_IRQn, TickPriority, 0U);
        uwTickPrio = TickPriority;
      }
      else
      {
        Status = HAL_ERROR;
      }
    }
  }
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1U)
  HAL_TIM_RegisterCallback(&htim17, HAL_TIM_PERIOD_ELAPSED_CB_ID, TimeBase_TIM_PeriodElapsedCallback);
#endif
  /* Enable the TIM17 global Interrupt */
  HAL_NVIC_EnableIRQ(TIM17_IRQn);

  /* Return function Status */
  return Status;

}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling TIM17 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_SuspendTick(void)
{
  /* Disable TIM17 update Interrupt */
  __HAL_TIM_DISABLE_IT(&htim17, TIM_IT_UPDATE);
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling TIM17 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_ResumeTick(void)
{
  /* Enable TIM17 Update interrupt */
  __HAL_TIM_ENABLE_IT(&htim17, TIM_IT_UPDATE);
}

