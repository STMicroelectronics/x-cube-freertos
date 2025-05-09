@color 0B
@echo off

REM Generate all CMSIS files 
REM Active perl must be installed

set scriptPATH=%CD%\..\..\..\..\..\..\..\__INTERNAL__tools\tools\_CmsisDeviceGenerator\

echo %scriptPATH%

if not exist "%scriptPATH%"  (
	echo Input directory does not exist!
	pause
	exit
)

cd %scriptPATH%

perl DeviceGeneration.pl  --target STM32U3xx -replace

pause

