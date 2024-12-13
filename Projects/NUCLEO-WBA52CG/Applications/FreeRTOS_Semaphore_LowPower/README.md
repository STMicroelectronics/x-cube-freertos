## <b>FreeRTOS_Semaphore_LowPower Application Description</b>

This application demonstrates the use of FreeRTOS tickless low power mode and semaphores.

The system relies on a low power timer to wake up from its low power state.

The thread blocks on a semaphore.
This causes the system to start the low power timer and enter STOP mode.

Before entring to LowPower mode the application :

- Disable SRAM1, SRAM2 & ICACHE content retention
- Configure Flash memory low power read
- Disable Flash memory fast wake up
- Enable ultra low power mode

Once the timer expires, an interrupt is triggered and the CPU returns to RUN mode.
The semaphore is released in the timer's interrupt handler. The thread resumes execution and
toggles the green LED.

#### <b>Expected success behavior</b>

Successful operation is marked by the green LED toggling every second.

#### <b>Error behaviors</b>

On failure, the red LED starts toggling while the green LED is switched OFF.

#### <b>Assumptions if any</b>

None

#### <b>Known limitations</b>

None

### <b>Notes</b>

To measure the current consumption remove JP2 jumper and connect an amperemeter to JP2 to measure IDD current.

This example can not be used in DEBUG mode due to the fact that the Cortex-M33 core is no longer clocked during low power mode so debugging features are disabled.

#### <b>FreeRTOS usage hints</b>

The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.
For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

### <b>Keywords</b>

FreeRTOS, RTOS, Semaphore, LowPower, LPTIM

### <b>Hardware and Software environment</b>

  - This application runs on STM32WBAxx devices.
  - This application has been tested with STMicroelectronics NUCLEO-WBA52CG board MB1845 Rev. A02
    and can be easily tailored to any other supported device and development board.

### <b>How to use it ?</b>
In order to make the program work, you must do the following :

 - Open the project in your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application
