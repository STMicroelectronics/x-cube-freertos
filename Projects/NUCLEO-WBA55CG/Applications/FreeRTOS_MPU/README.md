
## <b>FreeRTOS_MPU Application Description</b>

This application demonstrates the use of the MPU with FreeRTOS to control memory/peripheral access for tasks.
It implements simple recovery mechanisms from prohibited memory accesses.

The application creates one Privileged mode task using xTaskCreate():

  - 'MainTask': Has higher priority than the unprivileged tasks.
                Blocks while waiting for a fault to occur.
                Displays information about the faults and takes corrective actions.

It also has User mode tasks created using the xTaskCreateRestricted() API:

  - 'Task1': Has read only access to shared memory
             Attempts an illegal write to the shared memory only once
             Toggles the green LED

  - 'Task2': Has read only access to shared memory
             Attempts an illegal write to the shared memory periodically
             Toggles the blue LED

The application will try to recover from MemManage fault exception for each task until EXAMPLE_FAULT_COUNT_THRESHOLD is reached for that task. At that point the task will be suspended to
avoid further exceptions.

#### <b>Expected success behavior</b>

Successful operation is marked by a toggling green LED light.
The blue LED will toggle `EXAMPLE_FAULT_COUNT_THRESHOLD` times.

Information about the faults will be printed to the serial port.

#### <b>Error behaviors</b>

On failure, the red LED starts toggling while the green LED and blue LED are switched OFF.

#### <b>Assumptions if any</b>

None

#### <b>Known limitations</b>

None

### <b>Notes</b>

1- When used with the MPU, FreeRTOS requires various regions to be defined in the linker file.
For more information, refer to the linker files in the example as well as the FreeRTOS Documentation/Blog:

[https://freertos.org/2020/04/using-freertos-on-armv8-m-microcontrollers.html#FREERTOS_WITH_MPU](https://freertos.org/2020/04/using-freertos-on-armv8-m-microcontrollers.html#FREERTOS_WITH_MPU)

2- MPU regions are required to have a size which is a multiple of 32 bytes and to be aligned on the 32 byte boundary.
In particular, unprivileged task stacks must comply with these requirements.

#### <b>FreeRTOS usage hints</b>

The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

### <b>Keywords</b>

FreeRTOS, RTOS, MPU, Threading

### <b>Hardware and Software environment</b>

  - This application runs on STM32WBAxx devices.
  - This application has been tested with STMicroelectronics NUCLEO-WBA55CG board MB1803 Rev. B01
    and can be easily tailored to any other supported device and development board.

  - This application uses USART1 to display logs, the hyperterminal configuration is as follows:

    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1
    - Parity = None
    - Flow control = None

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open the project in your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application
