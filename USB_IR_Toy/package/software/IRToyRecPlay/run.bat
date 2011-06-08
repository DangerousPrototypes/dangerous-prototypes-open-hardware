@echo off
echo NOTE:  -b 256 is playback buffer for finetuning in your system. default is
echo 256 when not specfied. 
echo To play single file use the full file name with extenstion .bin
echo irtoy -d COM10 -p -f test_001.bin -v -b 256
echo -----------------------------------------------------------------------------------------
echo This utility does not check for the version of firmware and expected to fail 
echo with other firmwares (v15 below)  other than USBIRTOY-newtransmit.hex.
echo This is a for forum members who wanted to test the new firmware using the new 
echo transmit command 0x07 and use 64byte buffer when replaying regardless of 
echo buffer setting.
echo please update to USBIRTOY-newtransmit.hex before running this app.
echo -----------------------------------------------------------------------------------------
pause

irtoy -d COM6 -p -f test -v -b 256 -r
pause

