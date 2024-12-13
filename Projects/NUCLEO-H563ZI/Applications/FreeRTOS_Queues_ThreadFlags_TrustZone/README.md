
## <b>FreeRTOS_Queues_ThreadFlags_TrustZone Application Description</b>

This application demonstrates the use of message queues, thread flags with CMSIS_RTOS2 API along with the use of FreeRTOS when the TrustZone feature is enabled (TZEN=1).

The application creates 4 Tasks and 1 Queue:

  - 'ProducerThread': Sends message (incrementing value "ProducerValue") to the queue.

  - 'ConsumerThread': Gets message from the queue.
                      Checks if it's the correct message (ProducerValue == ConsumerValue).
                      Toggles LED_GREEN.

  - 'GenThread': Waits for the message on the queue to reach a specific "GenerationValue".
                 Sets ReceiveThread' flag to 1.

  - 'ReceiveThread': Waits for the thread flag settings.
                     Toggles SECURE LED_YELLOW.

    It is to note that 'ReceiveThread' is a non-secure FreeRTOS task that toggles a secure IO with HAL GPIO via a non-secure callable API provided by the secure application.
    The secure IO is PB.07 which corresponds to LED2 (LED_YELLOW).

This project is composed of two sub-projects:

- One for the secure application part (FreeRTOS_Queues_ThreadFlags_TrustZone_S).
- One for the non-secure application part (FreeRTOS_Queues_ThreadFlags_TrustZone_NS).

Please remember that on system with security enabled:

- The system always boots in secure and the secure application is responsible for launching the non-secure application.
- The SystemInit() function in secure application sets up the SAU/IDAU, FPU and secure/non-secure interrupts allocations defined in partition_stm32u575xx.h file.

This project shows how to switch between secure and non-secure applications thanks to the system isolation performed to split the internal Flash and internal SRAM memories into two halves:

 - The first half for the secure application
 - The second half for the non-secure application

User Option Bytes configuration:

Please note that the internal Flash is fully secure by default in TZEN=1 and User Option Bytes SECWM1_PSTRT/SECWM1_PEND and SECWM2_PSTRT/SECWM2_PEND should be set according to the application configuration.

#### <b>Expected success behavior</b>

Successful operation is marked by turning ON green LED then the yellow LED.

Information about the application will be printed to the serial port.

#### <b>Error behaviors</b>

On failure, the red LED starts toggling.

#### <b>Assumptions if any</b>

None

#### <b>Known limitations</b>

None

### <b>Notes</b>

The following sequence is needed to disable TrustZone:

  - Boot from user Flash memory:
  
    1. Make sure that secure and non-secure applications are well loaded and executed (jump done on non-secure application).
    2. If not yet done, set RDP to level 1 through STM32CubeProgrammer. Then only Hotplug connection is possible during non-secure application execution.
    3. Use a power supply different from ST-LINK in order to be able to connect to the target.
    4. Uncheck the TZEN box and set RDP to level 0 (option byte value 0xAA), then click on Apply.

  - Boot from RSS:
  
    1. Make sure to apply a high level on BOOT0 pin (make sure that nSWBOOT0 Option Byte is checked).
    2. If not yet done, set RDP to level 1 through STM32CubeProgrammer. Then only Hotplug connection is possible during non-secure application execution.
    3. Use a power supply different from ST-LINK in order to be able to connect to the target.
    4. Uncheck the TZEN box and set RDP to level 0 (option byte value 0xAA), then click on Apply.

Please refer to AN5347 for more details.

#### <b>FreeRTOS usage hints</b>

The FreeRTOS heap size configTOTAL_HEAP_SIZE defined in FreeRTOSConfig.h is set accordingly to the
OS resources memory requirements of the application with +10% margin and rounded to the upper Kbyte boundary.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications
on STM32Cube with RTOS".

### <b>Keywords</b>

Security, RTOS, FreeRTOS, TrustZone, Threading, GPIO, Message, Queues, ThreadFlags

### <b>Hardware and Software environment</b>

  - This application runs on STM32H563xx devices with security enabled (TZEN=B4).
  - This application has been tested with STMicroelectronics NUCLEO-H563ZI boards revision: MB1404-H563ZI-C01
    and can be easily tailored to any other supported device and development board.

  - This application uses USART3 to display logs, the hyperterminal configuration is as follows:

    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1
    - Parity = None
    - Flow control = None

  - User Option Bytes requirement (with STM32CubeProgrammer tool)

      - TZEN = B4                           System with TrustZone-M enabled
      - SECWM1_PSTRT=0x0  SECWM1_PEND=0x7F  All 128 pages of internal Flash Bank1 set as secure
      - SECWM2_PSTRT=0x1  SECWM2_PEND=0x0   No page of internal Flash Bank2 set as secure, hence Bank2 non-secure

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Make sure that the system is configured with the security enable (TZEN=1) (option byte)

IAR

 - Open your toolchain
 - Open Multi-projects workspace file Project.eww
 - Rebuild FreeRTOS_Queues_ThreadFlags_TrustZone_S project
 - Rebuild FreeRTOS_Queues_ThreadFlags_TrustZone_NS project
 - Set the "FreeRTOS_Queues_ThreadFlags_TrustZone_NS" as active application (Set as Active)
 - Flash the non-secure binary with Project->Download->Download active application
   (this shall download the \EWARM\FreeRTOS_Queues_ThreadFlags_TrustZone_NS\Exe\FreeRTOS_Queues_ThreadFlags_TrustZone_NS.out to flash memory)
 - Set the "FreeRTOS_Queues_ThreadFlags_TrustZone_S" as active application (Set as Active)
 - Flash the secure binary with Project->Download->Download active application
   (this shall download the \Secure_nsclib\FreeRTOS_Queues_ThreadFlags_TrustZone_S.out to flash memory)
 - Run the application

MDK-ARM

 - Open your toolchain
 - Open Multi-projects workspace file Project.uvmpw
 - Select the FreeRTOS_Queues_ThreadFlags_TrustZone_S project as Active Project (Set as Active Project)
 - Build FreeRTOS_Queues_ThreadFlags_TrustZone_S project
 - Select the FreeRTOS_Queues_ThreadFlags_TrustZone_NS project as Active Project (Set as Active Project)
 - Build FreeRTOS_Queues_ThreadFlags_TrustZone_NS project
 - Load the non-secure binary (F8)
   (this shall download the \MDK-ARM\FreeRTOS_Queues_ThreadFlags_TrustZone_ns\Exe\Project_ns.axf to flash memory)
 - Select the FreeRTOS_Queues_ThreadFlags_TrustZone_S project as Active Project (Set as Active Project)
 - Load the secure binary (F8)
   (this shall download the \MDK-ARM\FreeRTOS_Queues_ThreadFlags_TrustZone_s\Exe\Project_s.axf to flash memory)
 - Run the application

STM32CubeIDE

 - Open STM32CubeIDE
 - File > Import. Point to the STM32CubeIDE folder of the example project. Click Finish.
 - Build configuration: Set the same active build configuration: Debug (default) or Release for both projects FreeRTOS_Queues_ThreadFlags_TrustZone_S & FreeRTOS_Queues_ThreadFlags_TrustZone_NS
 - Select and build the FreeRTOS_Queues_ThreadFlags_TrustZone_NS project, this will automatically trigger the build of FreeRTOS_Queues_ThreadFlags_TrustZone_S project
 - Select the FreeRTOS_Queues_ThreadFlags_TrustZone_S project and select "Debug configuration" or "Run configuration" in function of the active build configuration
   - Double click on "STM32 Cortex-M C/C++ Application"
   - Select  "Startup" >  "Add" >
     - Select the FreeRTOS_Queues_ThreadFlags_TrustZone_NS project
 - Click Debug/Run to debug/run the application
