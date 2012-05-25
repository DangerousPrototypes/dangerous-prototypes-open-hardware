# MPLAB IDE generated this makefile for use with GNU make.
# Project: PartNinja.mcp
# Date: Fri May 25 17:03:00 2012

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

output/PartNinja.cof : work/main.o work/HD44780.o work/test.o
	$(LD) /p18F4550 /l"C:\mcc18\lib" "rm18f2550 - HID Bootload.lkr" "work\main.o" "work\HD44780.o" "work\test.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"output\PartNinja.cof" /M"output\PartNinja.map" /W

work/main.o : main.c HD44780.h test.h main.c globals.h HardwareProfile.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/GenericTypeDefs.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stddef.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18cxxx.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18f4550.h config.h
	$(CC) -p=18F4550 /i"." -I"c:\mcc18\h" -I"..\microchip\include" "main.c" -fo="work\main.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

work/HD44780.o : HD44780.c test.h HD44780.h HD44780.c globals.h HardwareProfile.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/GenericTypeDefs.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stddef.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18cxxx.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18f4550.h
	$(CC) -p=18F4550 /i"." -I"c:\mcc18\h" -I"..\microchip\include" "HD44780.c" -fo="work\HD44780.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

work/test.o : test.c test.h HD44780.h test.c globals.h HardwareProfile.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/GenericTypeDefs.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stddef.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18cxxx.h ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18f4550.h
	$(CC) -p=18F4550 /i"." -I"c:\mcc18\h" -I"..\microchip\include" "test.c" -fo="work\test.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "work\main.o" "work\HD44780.o" "work\test.o" "output\PartNinja.cof" "output\PartNinja.hex"

