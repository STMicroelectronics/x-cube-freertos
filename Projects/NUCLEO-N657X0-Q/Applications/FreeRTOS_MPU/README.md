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
             Toggles the blue LED
  - 'Task2': Has read only access to shared memory
             Attempts an illegal write to the shared memory periodically
             Toggles the green LED
The application will try to recover from MemManage fault exception for each task until EXAMPLE_FAULT_COUNT_THRESHOLD is reached for that task. At that point the task will be suspended to
avoid further exceptions.

####  <b>Expected success behavior</b>
Successful operation is marked by a toggling blue led light.
The green LED will toggle `EXAMPLE_FAULT_COUNT_THRESHOLD` times.
Information about the faults will be printed to the serial port.

#### <b>Error behaviors</b>
On failure, the red led is ON.

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

TrustZone is enabled by default in STM32N6 devices. When FreeRTOS is to be run in the secure world,
the `configENABLE_TRUSTZONE` must be set to 0, and `configRUN_FREERTOS_SECURE_ONLY` must be set to 1. in FreeRTOSConfig.h


### <b>Keywords</b>
FreeRTOS, RTOS, MPU, Threading

### <b>Hardware and Software environment</b>

  - This application runs on STM32N657X0H3QU devices.
  - This application has been tested with STMicroelectronics NUCLEO-N657X0 boards revision MB1940-N657X0-C01 and can be easily tailored to any other supported device and development board.
  - This application uses USART1 to display output, the hyperterminal configuration is as follows:

      - BaudRate = 115200 baud
      - Word Length = 8 Bits
      - Stop Bit = 1
      - Parity = none
      - Flow control = None

###  <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 2-3, BOOT0 switch position doesn't matter).
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.

Next, this program can be run in boot from flash mode. This can be done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary FreeRTOS_MPU.bin with the following command
      - *STM32MP_SigningTool_CLI.exe -bin FreeRTOS_MPU.bin -nk -of 0x80000000 -t fsbl -o FreeRTOS_MPU-trusted.bin -hv 2.3 -dump FreeRTOS_MPU-trusted.bin*
   - The resulting binary is FreeRTOS_MPU-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (FreeRTOS_MPU_trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Unplug the board then plug it again. The code then executes in boot from external Flash mode.