@echo off
echo --------------------------------------------------------------------------------
echo NOTE:  -b 256 is playback buffer for finetuning in your system. default is
echo 256 when not specfied. 
echo To play single file use the full file name with extenstion .bin
echo irtoy -d COM10 -p -f test_001.bin -v -b 256
echo --------------------------------------------------------------------------------
echo This utility requires v15 or higher and expected to fail with older firmwares 
echo This is  for forum members who wanted to test the new firmware using the new 
echo transmit command 0x07 and use 64byte buffer when replaying regardless of 
echo buffer setting.
echo please update to the latest firmware before running this app.
echo -

irtoy -d COM6 -p -f test -v -b 256 -r
pause

