gcc piratePICprog.c buspirateio.c serial.c -o piratePICprog.exe
piratePICprog --dev=COM3 --hex=pump.hex --verbose
pause