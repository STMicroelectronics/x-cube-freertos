## <b>FreeRTOS_Queues_ThreadFlags_TrustZone Application Description</b>

This application demonstrates the use of message queues, thread flags with CMSIS_RTOS2 API along with the use of FreeRTOS when the TrustZone feature is enabled (TZEN=1).

The application creates 4 Tasks and 1 Queue:

  - 'ProducerThread': Sends message (incrementing value "ProducerValue") to the queue.

  - 'ConsumerThread': Gets message from the queue.
                      Checks if it's the correct message (ProducerValue == ConsumerValue).

  - 'GenThread': Waits for the message on the queue to reach a specific "GenerationValue".
                 Sets ReceiveThread flag to 1.

  - 'ReceiveThread': Waits for the thread flag settings.
                     Toggles SECURE LED_GREEN.

    It is to note that 'ReceiveThread' is a non-secure FreeRTOS task that toggles a secure IO with HAL GPIO via a non-secure callable API provided by the secure application.
    The secure IO is PA.05 which corresponds to LED_GREEN.

#### <b>Description</b>

This project is composed of two sub-projects:

  - One for the secure application part (FreeRTOS_Queues_ThreadFlags_TrustZone_S)
  - One for the non-secure application part (FreeRTOS_Queues_ThreadFlags_TrustZone_NS)

Please remember that on system with security enabled, the system always boots in secure and
the secure application is responsible for launching the non-secure application.

This project mainly shows how to switch from secure application to non-secure application
thanks to the system isolation performed to split the internal Flash and internal SRAM memories
into two halves:

  - The first half for the secure application
  - The second half for the non-secure application

User Option Bytes configuration:

Please note the internal Flash is fully secure by default in TZEN=1 and User Option Bytes
Security Watermarks should be set according to the application configuration.
Here the proper User Option Bytes setup in line with the project linker/scatter
file is as follows:

    - TZEN=1
      NSBOOTADD0 = 0x08080000
    - SECWM1_PSTRT=0x0  SECWM1_PEND=0x7F  meaning all 128 pages of Bank1 set as secure
    - SECWM2_PSTRT=0x7F SECWM2_PEND=0x0   meaning no page of Bank2 set as secure, hence Bank2 non-secure

Any attempt by the non-secure application to access unauthorized code, memory or
peripheral generates a fault.

#### <b>Expected success behavior</b>

Successful operation is marked by turning on GREEN LED.

Information about the application will be printed to the serial port.

#### <b>Error behaviors</b>

On failure, an error message is printed to the serial port.

#### <b>Notes</b>

 1. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
 2. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.
 3. When deleting MDK-ARM project folder and regenerating this application with STM32CubeMx tool, be sure to place the Veneer$$CMSE section into IROM2 “ROM_NSC_region”.
 4. When deleting the MDK-ARM project folder and regenerating the application with the STM32CubeMX tool, be sure to keep the Debug.ini file.
 5. The instruction cache (ICACHE) must be enabled by software to get a 0 wait-state execution
    from Flash memory and external memories, and reach the maximum performance.

#### <b>FreeRTOS usage hints</b>
The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

### <b>Keywords</b>

Security, RTOS, FreeRTOS, TrustZone, Threading, GPIO, Message, Queues, ThreadFlags

### <b>Hardware and Software environment</b>

  - This application runs on STM32U385CG devices with security enabled (TZEN=1).
  - This application has been tested with STMicroelectronics NUCLEO-U385RG-Q (MB1841 Rev D01)
    board and can be easily tailored to any other supported device
    and development board.

  - This application uses USART1 to display logs, the hyperterminal configuration is as follows:

    - BaudRate = 115200 Baud
    - Word Length = 8 Bits
    - Stop Bit = 1
    - Parity = None
    - Flow control = None

  - User Option Bytes requirement (with STM32CubeProgrammer tool)
    - TZEN = 1                            System with TrustZone-M enabled
    - SBOOT0 address : SBOOT0R = 0x0C000000
    - BOOT0 address for non-secure automatic VTOR update : NSBOOT0R = 0x08080000
    - Bank 1 watermark : SECWM1R1 : STRT=0x00  END=0x7F  meaning all pages of Flash bank 1 set as secured
    - Bank 2 watermark : SECWM2R1 : STRT=0x7F  END=0x00  meaning all pages of Flash bank 2 set as non-secured

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Make sure that the system is configured with the security enable (TZEN=1) (option byte)

<b>IAR</b>

 - Open your toolchain
 - Open Multi-projects workspace file Project.eww
 - Rebuild xxxxx_S project
 - Rebuild xxxxx_NS project
 - Set the "xxxxx_S" as active application (Set as Active)
 - Flash the non-seure and secure binaries with Project->Download->Download active application
   (this shall download the \Secure_nsclib\xxxxx_S.out and \EWARM\xxxxx_NS\Exe\xxxxx_NS.out to flash memory)
 - Run the application

<b>MDK-ARM</b>

 - Open your toolchain
 - Open Multi-projects workspace file Project.uvmpw
 - Select the xxxxx_S project as Active Project (Set as Active Project)
 - Build xxxxx_S project
 - Select the xxxxx_NS project as Active Project (Set as Active Project)
 - Build xxxxx_NS project
 - Select the xxxxx_S project as Active Project (Set as Active Project)
 - Load the secure binary (F8) (this shall download the \MDK-ARM\xxxxx_s\Exe\FreeRTOS_Queues_ThreadFlags_TrustZone_S.axf and \MDK-ARM\xxxxx_ns\Exe\FreeRTOS_Queues_ThreadFlags_TrustZone_NS.axf to flash memory)
 - Run the application

<b>STM32CubeIDE</b>

 - Open STM32CubeIDE
 - File > Import. Point to the STM32CubeIDE folder of the application project. Click Finish.
 - Select and build the xxxxx_NS project, this will automatically trigger build of xxxxx_S project
 - Select the xxxxx_S project and select “Debug configuration”
   - Double click on “STM32 Cortex-M C/C++ Application”
   - Select  “Startup” >  “Add” >
 - Select the xxxxx_NS project
 - Build configuration : Select Release/Debug
 - Click Debug to debug the application
