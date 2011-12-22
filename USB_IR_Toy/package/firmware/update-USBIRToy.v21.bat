@ECHO OFF
set /P INPUT=Enter Com Port Number %=%

BootLoader.exe %INPUT%

ECHO Once the device has entered boot loader mode
pause

fw_update -e -w -v -m flash -vid 0x04D8 -pid 0xFD0B -ix USBIRToy.v21.hex
pause