## <b>FreeRTOS_Semaphore_LowPower Application Description</b>

This application demonstrates the use of FreeRTOS tickless low power mode and semaphores.

The system relies on a low power timer to wake up from its low power state.

The thread blocks on a semaphore.
This causes the system to start the low power timer and enter STOP mode.

Once the timer expires, an interrupt is triggered and the CPU returns to RUN mode.
The semaphore is released in the timer's interrupt handler. The thread resumes execution and
toggles the green LED.

#### <b>Expected success behavior</b>

Successful operation is marked by the green LED toggling every second.

#### <b>Error behaviors</b>

On failure, the red LED is ON while the green LED is turned OFF.

#### <b>Assumptions if any</b>

None

#### <b>Known limitations</b>

None

### <b>Notes</b>

To measure the current consumption in stop mode,  refer to NUCLEO-N657X0-Q board User Manual.

This example can not be used in DEBUG mode due to the fact that the Cortex-M55 core is no longer clocked during low power mode so debugging features are disabled.

It is possible to reduce power consumption even further by configuring all pins as analog pins and disabling their clocks.

#### <b>FreeRTOS usage hints</b>

The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.
For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

TrustZone is enabled by default in STM32N6 devices. When FreeRTOS is to be run in the secure world, the `configENABLE_TRUSTZONE`
must be set to 0, and `configRUN_FREERTOS_SECURE_ONLY` must be set to 1. in FreeRTOSConfig.h

### <b>Keywords</b>

FreeRTOS, RTOS, Semaphore, LowPower, LPTIM

### <b>Hardware and Software environment</b>

  - This application runs on STM32N657X0H3QU devices.
  - This application has been tested with STMicroelectronics NUCLEO-N657X0 boards revision MB1940-N657X0-C01
    and can be easily tailored to any other supported device
    and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 2-3, BOOT0 switch position doesn't matter).
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.

Next, this program can be run in boot from flash mode. This can be done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary FreeRTOS_Semaphore_LowPower_FSBL.bin with the following command
   - STM32_SigningTool_CLI.exe -bin FreeRTOS_Semaphore_LowPower_FSBL.bin -nk -of 0x80000000 -t fsbl -o FreeRTOS_Semaphore_LowPower_FSBL-trusted.bin -hv 2.3 -dump FreeRTOS_Semaphore_LowPower_FSBL-trusted.bin
   - The resulting binary is FreeRTOS_Semaphore_LowPower_FSBL-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (FreeRTOS_Semaphore_LowPower_FSBL-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Unplug the board then plug it again. The code then executes in boot from external Flash mode.
