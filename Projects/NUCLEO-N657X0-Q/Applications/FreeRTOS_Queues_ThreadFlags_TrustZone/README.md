## <b>FreeRTOS_Queues_ThreadFlags_TrustZone Application Description</b>

This application demonstrates the use of message queues, thread flags with CMSIS_RTOS2 API.

The application creates 4 Tasks and 1 Queue:

  - 'ProducerThread': Sends message (incrementing value "ProducerValue") to the queue.

  - 'ConsumerThread': Gets message from the queue
                      Checks if it's the correct message (ProducerValue == ConsumerValue)
                      Prints message to the serial port
                      Toggles LED_BLUE

  - 'GenThread': Waits for the message on the queue to reach a specific "GenerationValue"
                 Sets ReceiveThread flag to 1

  - 'ReceiveThread': Waits for the thread flag settings
                     Toggles SECURE LED_GREEN

#### <b>Expected success behavior</b>

Successful operation is marked by turning on Blue LED then the Green LED.

Information about the application will be printed to the serial port.

#### <b>Error behaviors</b>

On failure, the Red Led is ON.

#### <b>Assumptions if any</b>
None

#### <b>Known limitations</b>
None

### <b>Notes</b>
None

#### <b>FreeRTOS usage hints</b>
The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

TrustZone is enabled by default in STM32N6 devices. When FreeRTOS is to be run in the secure world,
the `configENABLE_TRUSTZONE` must be set to 0, and `configRUN_FREERTOS_SECURE_ONLY` must be set to 1. in FreeRTOSConfig.h


### <b>Keywords</b>

FreeRTOS, Threading, GPIO, Message, Queues, ThreadFlags, TrustZone, TZEN

### <b>Hardware and Software environment</b>

  - This application runs on STM32N657xx devices.
  - This application has been tested with STMicroelectronics NUCLEO-N657X0-Q board MB1940 Rev. C01
    and can be easily tailored to any other supported device and development board.

  - This application uses USART1 to display output, the hyperterminal configuration is as follows:

      - BaudRate = 115200 baud
      - Word Length = 8 Bits
      - Stop Bit = 1
      - Parity = none
      - Flow control = None


### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 2-3, BOOT0 switch position doesn't matter).
 - Open your preferred toolchain
 - Select first the FSBL workspace
 - Rebuild all files from sub-project FreeRTOS_Queues_ThreadFlags_TrustZone_FSBL (if no modification is done on FreeRTOS_Queues_ThreadFlags_TrustZone_FSBL project, this step can be done only once)
 - Select the FreeRTOS_Queues_ThreadFlags_TrustZone_S workspace
 - Rebuild all files from sub-project FreeRTOS_Queues_ThreadFlags_TrustZone_S
 - Select the FreeRTOS_Queues_ThreadFlags_TrustZone_NS workspace
 - Rebuild all files from sub-project FreeRTOS_Queues_ThreadFlags_TrustZone_NS
 - Resort to CubeProgrammer to add a header to the generated App_Secure binary FreeRTOS_Queues_ThreadFlags_TrustZone_S.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin FreeRTOS_Queues_ThreadFlags_TrustZone_S.bin -nk -of 0x80000000 -t fsbl -o FreeRTOS_Queues_ThreadFlags_TrustZone_S-trusted.bin -hv 2.3 -dump FreeRTOS_Queues_ThreadFlags_TrustZone_S-trusted.bin*
   - The resulting binary is FreeRTOS_Queues_ThreadFlags_TrustZone_S-trusted.bin.
 - Do the same with App_NonSecure
   - *STM32_SigningTool_CLI.exe -bin FreeRTOS_Queues_ThreadFlags_TrustZone_NS.bin -nk -of 0x80000000 -t fsbl -o FreeRTOS_Queues_ThreadFlags_TrustZone_NS-trusted.bin -hv 2.3 -dump FreeRTOS_Queues_ThreadFlags_TrustZone_NS-trusted.bin*
   - The resulting binary is FreeRTOS_Queues_ThreadFlags_TrustZone_NS-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the secure application binary and its header (FreeRTOS_Queues_ThreadFlags_TrustZone_S-trusted.bin) in Nucleo board external Flash at address 0x7010'0000
   and the non-secure application binary and its header (FreeRTOS_Queues_ThreadFlags_TrustZone_NS-trusted.bin) at address 0x7018'0000.


 To run the template with boot in development mode,

 - Load the FreeRTOS_Queues_ThreadFlags_TrustZone_FSBL binary in internal RAM using the IDE
 - Run the example


To run the template in boot from flash mode,

 - Resort to CubeProgrammer to add a header to the generated binary FreeRTOS_Queues_ThreadFlags_TrustZone_FSBL.bin with the following command
   - *STM32_SigningTool_CLI.exe -bin FreeRTOS_Queues_ThreadFlags_TrustZone_FSBL.bin -nk -of 0x80000000 -t fsbl -o FreeRTOS_Queues_ThreadFlags_TrustZone_FSBL-trusted.bin -hv 2.3 -dump FreeRTOS_Queues_ThreadFlags_TrustZone_FSBL-trusted.bin*
   - The resulting binary is FreeRTOS_Queues_ThreadFlags_TrustZone_FSBL-trusted.bin.
 - With CubeProgrammer, load the FreeRTOS_Queues_ThreadFlags_TrustZone_FSBL binary and its header (FreeRTOS_Queues_ThreadFlags_TrustZone_FSBL-trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Press the reset button. The code then executes in boot from Flash mode.
