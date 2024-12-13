## <b>FreeRTOS_Mutex Application Description</b>

This application demonstrates the use of mutexes to serialize access to a shared resource.

The application has two threads:

    -Thread1 : Prints messages counting from 1 to 10 ("Thread1 : This is message number x")
               Blinks the blue LED every second

    -Thread2 : Prints messages counting from 1 to 10 ("Thread2 : This is message number x")
               Blinks the green LED every second

The mutex is created before the threads using it are scheduled. Each thread will try to acquire it
before outputting characters to the serial port. Once the mutex is acquired, the thread will proceed
to printing its message, and then immediately releases it.

If the mutex is not used, the two threads will try to use "printf" at almost the same time. This will
result in either thread winning over the other or both threads interrupting each other.

The user can observe the effect of not using a mutex to protect printf by setting the
`EXAMPLE_USES_MUTEX` define in Src/app_freertos.c to 0.

####  <b>Expected success behavior</b>

If the `EXAMPLE_USES_MUTEX` is set to 0, some messages will not be printed, or may be corrupted.

If the `EXAMPLE_USES_MUTEX` is set to 1, each thread will display 10 messages identified by the thread name
and the message number , for a total of 20 messages. Additional messages will be printed to displayed when
the mutex is acquired or released.

The blue LED and yellow LED will toggle every second.

#### <b>Error behaviors</b>

On failure, the red LED toggles every second while the blue LED and yellow LED are turned OFF.
An Error message is printed on the hyperterminal.

#### <b>Assumptions if any</b>

None

#### <b>Known limitations</b>

None

### <b>Notes</b>

None

### <b>FreeRTOS usage hints</b>
The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

TrustZone is enabled by default in STM32N6 devices. When FreeRTOS is to be run in the secure world, 
the `configENABLE_TRUSTZONE` must be set to 0, and `configRUN_FREERTOS_SECURE_ONLY` must be set to 1. in FreeRTOSConfig.h

### <b>Keywords</b>

FreeRTOS, Tasks, Multithreading, Mutex

### <b>Hardware and Software environment</b>

  - This application runs on STM32N657X0H3QU devices.
  - This application has been tested with STMicroelectronics NUCLEO-N657X0 boards revision MB1940-N657X0-C01 and can be easily tailored to any other supported device and development board.

  - This application uses USART1 to display output, the hyperterminal configuration is as follows:

    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1
    - Parity = None
    - Flow control = None

###  <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Set the boot mode in development mode (BOOT1 switch position is 2-3, BOOT0 switch position doesn't matter).
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory. Code can be executed in this mode for debugging purposes.

Next, this program can be run in boot from flash mode. This can be done by following the instructions below:

 - Resort to CubeProgrammer to add a header to the generated binary FreeRTOS_Mutex.bin with the following command
      - *STM32MP_SigningTool_CLI.exe -bin FreeRTOS_Mutex.bin -nk -of 0x80000000 -t fsbl -o FreeRTOS_Mutex-trusted.bin -hv 2.3 -dump FreeRTOS_Mutex-trusted.bin*
   - The resulting binary is FreeRTOS_Mutex-trusted.bin.
 - Next, in resorting again to CubeProgrammer, load the binary and its header (FreeRTOS_Mutex_trusted.bin) in Nucleo board external Flash at address 0x7000'0000.
 - Set the boot mode in boot from external Flash (BOOT0 switch position is 1-2 and BOOT1 switch position is 1-2).
 - Unplug the board then plug it again. The code then executes in boot from external Flash mode.