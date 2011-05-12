rem  -b 256 is playback buffer for finetuning in your system. default is 246 when not specfied.
rem  to play single file use the full file name with extenstion .bin
rem irtoy -d COM10 -p -f test_001.bin -v -b 256


irtoy -d COM10 -p -f test -v -r -b 256
pause

