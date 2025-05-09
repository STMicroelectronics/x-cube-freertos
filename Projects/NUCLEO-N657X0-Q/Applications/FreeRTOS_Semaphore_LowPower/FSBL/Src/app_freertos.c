/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
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
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DEFAULT_TIMEOUT (1000)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern LPTIM_HandleTypeDef hlptim2;
/* USER CODE END Variables */
/* Definitions for MainThread */
osThreadId_t MainThreadHandle;
const osThreadAttr_t MainThread_attributes = {
  .name = "MainThread",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for BinarySemaphore */
osSemaphoreId_t BinarySemaphoreHandle;
const osSemaphoreAttr_t BinarySemaphore_attributes = {
  .name = "BinarySemaphore"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void SystemClock_Config(void);
/* USER CODE END FunctionPrototypes */

/* USER CODE BEGIN PREPOSTSLEEP */
void PreSleepProcessing(uint32_t ulExpectedIdleTime)
{
  /* This is needed to prevent TIM6 from triggering an interrupt,
   * which could prevent the CPU from entering STOP mode */
  HAL_SuspendTick();

  /* Start low power timer */
  HAL_LPTIM_TimeOut_Start_IT(&hlptim2, DEFAULT_TIMEOUT);

  /* Enter STOP mode */
  HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);
}
void PostSleepProcessing(uint32_t ulExpectedIdleTime)
{
  /* Resume HAL timebase */
  HAL_ResumeTick();
}
/* USER CODE END PREPOSTSLEEP */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */
  /* creation of BinarySemaphore */
  BinarySemaphoreHandle = osSemaphoreNew(1, 1, &BinarySemaphore_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of MainThread */
  MainThreadHandle = osThreadNew(MainThread_Entry, NULL, &MainThread_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_MainThread_Entry */
/**
  * @brief Function implementing the MainThread thread.
  * @param argument: Not used
  * @retval None
  */
/* USER CODE END Header_MainThread_Entry */
void MainThread_Entry(void *argument)
{
  /* USER CODE BEGIN MainThread */
  /* Infinite loop */
  for(;;osSemaphoreAcquire(BinarySemaphoreHandle, osWaitForever))
  {
    HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
  }
  /* USER CODE END MainThread */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_LPTIM_CompareMatchCallback(LPTIM_HandleTypeDef *hlptim)
{
  if(hlptim->Instance == LPTIM2)
  {
    osSemaphoreRelease(BinarySemaphoreHandle);
    HAL_LPTIM_TimeOut_Stop_IT(&hlptim2);
  }
}

/* USER CODE END Application */

