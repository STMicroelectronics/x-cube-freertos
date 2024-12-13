## <b>FreeRTOS_Semaphore_LowPower Application Description</b>

This application demonstrates the use of FreeRTOS tickless low power mode and semaphores.

The system relies on EXTI to wake up from its low power state.

The thread blocks on a semaphore which causes the system to enter STOP mode.

Once the USER Button is pressed, an interrupt is triggered and the CPU returns to RUN mode.
The semaphore is released in the EXTI's interrupt handler. The thread resumes execution and
toggles the green LED.

#### <b>Expected success behavior</b>
LED_GREEN toggles every 1s for 5 seconds each time user presses the user button.

#### <b>Error behaviors</b>
On failure, the green LED is turned off and an error message is printed to the serial port.

#### <b>Assumptions if any</b>
None

#### <b>Known limitations</b>
None

### <b>Notes</b>
To measure the current consumption remove JP5 jumper and connect an ammeter to JP5 to measure IDD current.

This example can not be used in DEBUG mode due to the fact that the Cortex-M0+ core is no longer clocked during low power mode so debugging features are disabled.

It is possible to reduce power consumption even further by configuring all pins as analog pins and disabling their clocks.

#### <b>FreeRTOS usage hints</b>
The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

### <b>Keywords</b>

FreeRTOS, RTOS, LowPower, EXTI, Semaphore, Threading

### <b>Hardware and Software environment</b>

  - This application runs on STM32U083RCTx devices.
  - This application has been tested with STMicroelectronics NUCLEO-U083RC board MB1932 Rev. B01
    and can be easily tailored to any other supported device and development board.

  - This application uses USART2 to display output, the hyperterminal configuration is as follows:

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
