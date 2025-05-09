/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define CONSUMER_VALUE 10
#define GEN_VALUE 20
#define PRODUCER_MAX_VALUE 25

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint32_t ProducerValue = 10;
/* USER CODE END Variables */
/* Definitions for ProducerThread */
osThreadId_t ProducerThreadHandle;
const osThreadAttr_t ProducerThread_attributes = {
  .name = "ProducerThread",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for ConsumerThread */
osThreadId_t ConsumerThreadHandle;
const osThreadAttr_t ConsumerThread_attributes = {
  .name = "ConsumerThread",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for GenThread */
osThreadId_t GenThreadHandle;
const osThreadAttr_t GenThread_attributes = {
  .name = "GenThread",
  .priority = (osPriority_t) osPriorityBelowNormal,
  .stack_size = 128 * 4
};
/* Definitions for ReceiveThread */
osThreadId_t ReceiveThreadHandle;
const osThreadAttr_t ReceiveThread_attributes = {
  .name = "ReceiveThread",
  .priority = (osPriority_t) osPriorityBelowNormal,
  .stack_size = 128 * 4
};
/* Definitions for osQueue */
osMessageQueueId_t osQueueHandle;
const osMessageQueueAttr_t osQueue_attributes = {
  .name = "osQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  printf("/************ FreeRTOS_Queues_ThreadFlags_TrustZone app started: ************/\n\n");
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */
  /* creation of osQueue */
  osQueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &osQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of ProducerThread */
  ProducerThreadHandle = osThreadNew(Producer_Thread, NULL, &ProducerThread_attributes);

  /* creation of ConsumerThread */
  ConsumerThreadHandle = osThreadNew(Consumer_Thread, NULL, &ConsumerThread_attributes);

  /* creation of GenThread */
  GenThreadHandle = osThreadNew(Gen_Thread, NULL, &GenThread_attributes);

  /* creation of ReceiveThread */
  ReceiveThreadHandle = osThreadNew(Receive_Thread, NULL, &ReceiveThread_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_Producer_Thread */
/**
  * @brief Function implementing the ProducerThread thread.
  * @param argument: Not used
  * @retval None
  */
/* USER CODE END Header_Producer_Thread */
void Producer_Thread(void *argument)
{
  /* USER CODE BEGIN ProducerThread */

  for(;;)
  {
    if (ProducerValue < PRODUCER_MAX_VALUE)
    {
      /* Set the message to the queue */
      printf("ProducerThread: sending ProducerValue msg to the queue\n\n");
      if (osMessageQueuePut(osQueueHandle, &ProducerValue, 100, osWaitForever) != osOK)
      {
        Error_Handler();
      }

      ProducerValue = ProducerValue + 10;
      osDelay(2000);
    }
    else
    {
      /* Terminate ProducerThread execution */
      osThreadTerminate(ProducerThreadHandle);
    }
  }
  /* USER CODE END ProducerThread */
}

/* USER CODE BEGIN Header_Consumer_Thread */
/**
  * @brief Function implementing the ConsumerThread thread.
  * @param argument: Not used
  * @retval None
  */
/* USER CODE END Header_Consumer_Thread */
void Consumer_Thread(void *argument)
{
  /* USER CODE BEGIN ConsumerThread */
  uint32_t osQueueMsg = 0;

  for(;;)
  {
    /* Get the message from the queue */

    if (osMessageQueueGet(osQueueHandle, &osQueueMsg, NULL, osWaitForever) != osOK)
    {
      Error_Handler();
    }
    else
    {
      /* Check if it is the correct message */
      printf("ConsumerThread: getting the msg from queue & checking if it's the correct msg\n");
      if(osQueueMsg == CONSUMER_VALUE)
      {
        /* Toggle LED1 (LED_GREEN) */
        printf("ConsumerThread: correct msg verified -> Toggle LED_GREEN\n\n");
        HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
      }
    }

    /* Terminate ConsumerThread execution */
    osThreadTerminate(ConsumerThreadHandle);
  }
  /* USER CODE END ConsumerThread */
}

/* USER CODE BEGIN Header_Gen_Thread */
/**
  * @brief Function implementing the GenThread thread.
  * @param argument: Not used
  * @retval None
  */
/* USER CODE END Header_Gen_Thread */
void Gen_Thread(void *argument)
{
  /* USER CODE BEGIN GenThread */
  uint32_t osQueueMsg = 0;

  for(;;)
  {
    /* Get the message from the queue */
    if (osMessageQueueGet(osQueueHandle, &osQueueMsg, NULL, osWaitForever) != osOK)
    {
      Error_Handler();
    }
    else
    {
      /* Check if it's the correct message */
      printf("GenThread: getting the msg from queue & checking if the GEN_VALUE is reached\n");
      if(osQueueMsg == GEN_VALUE)
      {
        /* Set ReceiveThread' flag to 1 */
        printf("GenThread: GenerationValue reached -> Set ReceiveThread' flag to 1\n\n");
        osThreadFlagsSet(ReceiveThreadHandle, 0x0001U);
      }
    }

    /* Terminate GenThread execution */
    osThreadTerminate(GenThreadHandle);
   }
  /* USER CODE END GenThread */
}

/* USER CODE BEGIN Header_Receive_Thread */
/**
  * @brief Function implementing the ReceiveThread thread.
  * @param argument: Not used
  * @retval None
  */
/* USER CODE END Header_Receive_Thread */
void Receive_Thread(void *argument)
{
  /* USER CODE BEGIN ReceiveThread */
  /* Allocate secure context before calling "SECURE_LEDToggle()" secure function */
  portALLOCATE_SECURE_CONTEXT (configMINIMAL_SECURE_STACK_SIZE);
  for (;;)
  {
    /* Wait forever until thread flag 1 is set */
    printf("ReceiveThread: Wait until thread flag 1 is set\n\n");
    osThreadFlagsWait(0x0001U, osFlagsWaitAny, osWaitForever);

    /* Toggle secure LED1 (LED_BLUE) */
    printf("ReceiveThread: Flag set to 1 -> Toggle secure LED_BLUE\n\n");
    SECURE_LEDToggle();

    /* Terminate ReceiveThread execution */
    osThreadTerminate(ReceiveThreadHandle);
  }

  /* USER CODE END ReceiveThread */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

