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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "queue.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct
{
  uint32_t      address;
  uint32_t      handle;
  uint32_t      psp;
}FaultInfo_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define NUMBER_OF_TASKS (2)

/* Return address offset within stack frame */
#define RETURN_ADDRESS_OFFSET (6U)

/* Mask used to identify whether instruction is 16 bits or 32 bits */
#define INSTRUCTION_32BIT_Msk (0xE000)


/* Example config */
/* Number of faults a task can cause before it gets deleted */
#define EXAMPLE_FAULT_COUNT_THRESHOLD (3)

#define EXAMPLE_SHARED_MEMORY_SIZE (512U)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* A queue to hold fault information */
static QueueHandle_t fault_queue;

/* Define an array to track fault count */
static uint8_t fault_count[NUMBER_OF_TASKS];

/* Define stack spaces for unprivileged tasks.
 * These must meet MPU alignment and size requirements. */
static StackType_t Task1Stack[ 2 * configMINIMAL_STACK_SIZE ] __attribute__( ( aligned( 32 ) ) );
static StackType_t Task2Stack[ 2 * configMINIMAL_STACK_SIZE ] __attribute__( ( aligned( 32 ) ) );

/* Define shared memory */
static uint8_t sharedMemory[ EXAMPLE_SHARED_MEMORY_SIZE ] __attribute__( ( aligned( 32 ) ) );


static void Task1(void *argument);
static void Task2(void *argument);

static TaskHandle_t MainTaskHandle;
static TaskHandle_t TaskHandles[NUMBER_OF_TASKS];

/* Task parameters for unprivileged tasks */
static const TaskParameters_t TaskParameters[NUMBER_OF_TASKS] =
{
  {
      .pvTaskCode     = Task1,
      .pcName         = "Task1",
      .usStackDepth   = 2 * configMINIMAL_STACK_SIZE,
      .pvParameters   = NULL,
      .uxPriority     = tskIDLE_PRIORITY,
      .puxStackBuffer = Task1Stack,
      .xRegions       =   {
                              { sharedMemory      , EXAMPLE_SHARED_MEMORY_SIZE,
                              tskMPU_REGION_READ_ONLY | tskMPU_REGION_EXECUTE_NEVER },
                              { LED1_GREEN_GPIO_Port, EXAMPLE_SHARED_MEMORY_SIZE,
                              tskMPU_REGION_READ_WRITE | tskMPU_REGION_EXECUTE_NEVER },

                              { 0 ,  0,  0 },
                          }
  },
  {
      .pvTaskCode     = Task2,
      .pcName         = "Task2",
      .usStackDepth   = 2 * configMINIMAL_STACK_SIZE,
      .pvParameters   = NULL,
      .uxPriority     = tskIDLE_PRIORITY,
      .puxStackBuffer = Task2Stack,
      .xRegions       =   {
                              { sharedMemory      , EXAMPLE_SHARED_MEMORY_SIZE,
                              tskMPU_REGION_READ_ONLY | tskMPU_REGION_EXECUTE_NEVER },
                              { LED2_YELLOW_GPIO_Port, EXAMPLE_SHARED_MEMORY_SIZE,
                              tskMPU_REGION_READ_WRITE | tskMPU_REGION_EXECUTE_NEVER },
                              { 0 ,  0,  0 },
                          }
  }
};

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
static void MainTask(void *argument);
/* USER CODE END FunctionPrototypes */

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  fault_queue = xQueueCreate(5U, sizeof(FaultInfo_t));
  if(fault_queue == NULL)
  {
     Error_Handler();
  }
  /* USER CODE END RTOS_QUEUES */

  /* USER CODE BEGIN RTOS_THREADS */
  if(xTaskCreate(MainTask, "MainTask", 4 * configMINIMAL_STACK_SIZE, NULL,
                 (configMAX_PRIORITIES -1) |portPRIVILEGE_BIT  ,
                 &MainTaskHandle) != pdPASS)
  {
     Error_Handler();
  }

  /* Create unprivileged threads */
  if(xTaskCreateRestricted(&TaskParameters[0], &TaskHandles[0] )!= pdPASS)
  {
     Error_Handler();
  }
  if(xTaskCreateRestricted(&TaskParameters[1], &TaskHandles[1] )!= pdPASS)
  {
     Error_Handler();
  }
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/**
* @brief Function implementing the MainTask thread.
*        It is responsible for montitoring other threads.
* @param argument: Not used
* @retval None
*/
void MainTask(void *argument)
{
  UNUSED(argument);

  FaultInfo_t fault;
  uint8_t nextInstructionOffset = 2U;
  uint32_t* returnAddress;
  uint16_t instruction;

  for(;;)
  {
    xQueueReceive(fault_queue, &fault, portMAX_DELAY);

    printf("------------------------------\n");

    /* Handle MPU exceptions */
    for(int i = 0; i < NUMBER_OF_TASKS; ++i)
    {
      if((TaskHandle_t)fault.handle == TaskHandles[i])
      {
        /* Increment fault count for task */
        ++fault_count[i];

        /* Display info about fault */
        printf("MemManage fault occurred\r\n");
        printf("\tAddress: 0x%X\n", (unsigned int) fault.address);
        printf("\tTask name: %s\n", pcTaskGetName((TaskHandle_t) fault.handle));

        returnAddress = (uint32_t*)fault.psp + RETURN_ADDRESS_OFFSET;

        /* Identify if the instruction which caused the issue
         *is 16 or 32 bit wide */
        instruction = *(uint16_t*)(*(uint32_t*)returnAddress);
        if((instruction & INSTRUCTION_32BIT_Msk) == INSTRUCTION_32BIT_Msk)
        {
            nextInstructionOffset = 4U;
        }
        else
        {
            nextInstructionOffset = 2U;
        }

        /* Move to next instruction */
        *returnAddress += nextInstructionOffset;


        /* Delete task if it has caused too many faults*/
        if(fault_count[i] == EXAMPLE_FAULT_COUNT_THRESHOLD)
        {
          vTaskDelete((TaskHandle_t)fault.handle);

          printf("Task %s has caused %d faults. It was deleted.\n",
                  pcTaskGetName(TaskHandles[i]),
                  EXAMPLE_FAULT_COUNT_THRESHOLD);
        }
        break;
      }
    }
    printf("------------------------------\n");
  }
}

/**
* @brief Function implementing the Task1 thread.
* @param argument: Not used
* @retval None
*/
void Task1(void *argument)
{
  UNUSED(argument);

  uint8_t isFirstTime = 1;

  for(;;)
  {
    HAL_GPIO_TogglePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin);
    vTaskDelay(pdMS_TO_TICKS(1000));
    if(isFirstTime)
    {
      isFirstTime = 0;

      /* Try to perform an illegal write */
      sharedMemory[EXAMPLE_SHARED_MEMORY_SIZE - 1] = 4U;
    }
  }
}

/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
void Task2(void *argument)
{
  UNUSED(argument);

  vTaskDelay(pdMS_TO_TICKS(1000));
  for(;;)
  {
    HAL_GPIO_TogglePin(LED2_YELLOW_GPIO_Port, LED2_YELLOW_Pin);
    vTaskDelay(pdMS_TO_TICKS(2000));

    /* Try to perform an illegal write */
    sharedMemory[EXAMPLE_SHARED_MEMORY_SIZE/2] = 4U;
  }
}


/* We need to use the original FreeRTOS xTaskGetCurrentTaskHandle
 * function instead of the one defined in mpu_wrapper.c */
#undef xTaskGetCurrentTaskHandle
TaskHandle_t xTaskGetCurrentTaskHandle( void );

/**
* @brief MemManage fault receovery
* @retval None
*/
void MemManage_Recover(void)
{
  FaultInfo_t current_fault;

  /* Log the offending thread */
  current_fault.address  = SCB->MMFAR;
  current_fault.handle =  (uint32_t)xTaskGetCurrentTaskHandle();
  current_fault.psp = (uint32_t)__get_PSP();

  /*
   * Clear DACCVIOL sticky bit in the MMFSR subregister.
   * If not cleared, subsequent fault addresses will not be stored in
   * the MMFAR register.*/
  SET_BIT(SCB->CFSR,SCB_CFSR_DACCVIOL_Msk);

  /* Send Fault info to Main task */
  xQueueSendToBackFromISR(fault_queue, &current_fault, NULL);

  /* Current task yields. This forces a context switch and guarantees that
   * the Main thread will be able to take action if needed before the current
   * thread continues.*/
  taskYIELD();
}

/* USER CODE END Application */

