## <b>FreeRTOS_Queues_ThreadFlags Application Description</b>

This application demonstrates the use of message queues, thread flags with CMSIS_RTOS2 API.

The application creates 4 Tasks and 1 Queue:

  - 'ProducerThread': Sends message (incrementing value "ProducerValue") to the queue.

  - 'ConsumerThread': Gets message from the queue
                      Checks if it's the correct message (ProducerValue == ConsumerValue)
                      Prints message to the serial port

  - 'GenThread': Waits for the message on the queue to reach a specific "GenerationValue"
                 Sets ReceiveThread' flag to 1

  - 'ReceiveThread': Waits for the thread flag settings
                     Toggles LED_GREEN

#### <b>Expected success behavior</b>

Successful operation is marked by turning on Green LED.

Information about the application will be printed to the serial port.

#### <b>Error behaviors</b>

On failure, the green LED is turned off and an error message is printed to the serial port.

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

### <b>Keywords</b>

FreeRTOS, Threading, GPIO, Message, Queues, ThreadFlags

### <b>Hardware and Software environment</b>

  - This application runs on STM32C031C6Tx devices.
  - This application has been tested with STMicroelectronics NUCLEO-C031C6 board MB1717 Rev. B01
    and can be easily tailored to any other supported device and development board.

  - This application uses USART2 to display output, the hyperterminal configuration is as follows:

      - BaudRate = 115200 baud
      - Word Length = 8 Bits
      - Stop Bit = 1
      - Parity = none
      - Flow control = None


### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open the project in your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application
