opt subtitle "HI-TECH Software Omniscient Code Generator (Lite mode) build 9453"

opt pagewidth 120

	opt lm

	processor	16F1829
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
indf1	equ	1
pc	equ	2
pcl	equ	2
status	equ	3
fsr0l	equ	4
fsr0h	equ	5
fsr1l	equ	6
fsr1h	equ	7
bsr	equ	8
wreg	equ	9
intcon	equ	11
c	equ	1
z	equ	0
pclath	equ	10
# 21 "C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
	psect config,class=CONFIG,delta=2 ;#
# 21 "C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
	dw 0xFFFC&0xFFE7&0xFFFF&0xFFBF&0xFFFF&0xFFFF&0xFFFF&0xFFFF&0xEFFF&0xFFFF ;#
# 22 "C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
	psect config,class=CONFIG,delta=2 ;#
# 22 "C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
	dw 0xFEFF&0xFFFF&0xDFFF ;#
DABS 1,1568,48	;_eeBuf
DABS 1,1440,80	;_eeBuf
DABS 1,1312,80	;_eeBuf
DABS 1,1216,48	;_eeBuf
	FNCALL	_main,_init
	FNCALL	_main,_EEPROMread
	FNCALL	_main,_isEE
	FNCALL	_main,_doEE
	FNCALL	_main,_I2CADCworker
	FNCALL	_main,_UARTworker
	FNCALL	_main,_SPIADCworker
	FNCALL	_main,_nullfunc1
	FNCALL	_main,_I2CEEworker
	FNCALL	_main,_SPIEEworker
	FNCALL	_main,_I2CDACworker
	FNCALL	_main,_SPIDACworker
	FNCALL	_main,_I2CPWMworker
	FNCALL	_main,_SPIPWMworker
	FNCALL	_UARTworker,_initUART
	FNCALL	_UARTworker,_UARTwriteString
	FNCALL	_UARTworker,_UARTwrite
	FNCALL	_UARTworker,_UARTread
	FNCALL	_UARTworker,_enablePWM
	FNCALL	_UARTworker,_enableDAC
	FNCALL	_UARTworker,_getADC
	FNCALL	_UARTworker,_UARTwriteDecimal
	FNCALL	_UARTworker,_UARTcharFromString
	FNCALL	_UARTworker,_setPeriod
	FNCALL	_UARTworker,_setDuty
	FNCALL	_UARTworker,_disablePWM
	FNCALL	_UARTworker,_setDAC
	FNCALL	_UARTworker,_disableDAC
	FNCALL	_UARTworker,_EEPROMwrite
	FNCALL	_UARTworker,_EEPROMread
	FNCALL	_SPIPWMworker,_initSPI
	FNCALL	_SPIPWMworker,_enablePWM
	FNCALL	_SPIPWMworker,_setPeriod
	FNCALL	_SPIPWMworker,_setDuty
	FNCALL	_I2CPWMworker,_enablePWM
	FNCALL	_I2CPWMworker,_setPeriod
	FNCALL	_I2CPWMworker,_setDuty
	FNCALL	_doEE,_teletype
	FNCALL	_teletype,_UARTwrite
	FNCALL	_UARTcharFromString,_UARTread
	FNCALL	_UARTcharFromString,_UARTwrite
	FNCALL	_UARTcharFromString,___bmul
	FNCALL	_UARTwriteDecimal,___lbdiv
	FNCALL	_UARTwriteDecimal,_UARTwrite
	FNCALL	_UARTwriteDecimal,___bmul
	FNCALL	_UARTwriteString,_UARTwrite
	FNCALL	_SPIADCworker,_initSPI
	FNCALL	_SPIADCworker,_getADC
	FNCALL	_SPIDACworker,_initSPI
	FNCALL	_SPIDACworker,_enableDAC
	FNCALL	_SPIDACworker,_setDAC
	FNCALL	_SPIEEworker,_initSPI
	FNCALL	_SPIEEworker,_EEPROMwrite
	FNCALL	_setDuty,___wmul
	FNCALL	_setDuty,___lwdiv
	FNCALL	_setPeriod,___wmul
	FNCALL	_setPeriod,___lwdiv
	FNCALL	_enablePWM,___wmul
	FNCALL	_enablePWM,___lwdiv
	FNCALL	_I2CDACworker,_enableDAC
	FNCALL	_I2CDACworker,_setDAC
	FNCALL	_I2CDACworker,_I2CWrite
	FNCALL	_I2CADCworker,_enableTS
	FNCALL	_I2CADCworker,_I2CWrite
	FNCALL	_I2CADCworker,_startADC16
	FNCALL	_I2CEEworker,_EEPROMwrite
	FNCALL	_init,_initSPI
	FNCALL	_init,_initI2C
	FNCALL	_init,_initUART
	FNROOT	_main
	FNCALL	intlevel1,_isr
	global	intlevel1
	FNROOT	intlevel1
	global	_protos
	global	_msgMenu
psect	idataBANK0,class=CODE,space=0,delta=2
global __pidataBANK0
__pidataBANK0:
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
	line	36

;initializer for _protos
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__SPIADCworker-fpbase)&0ffh
	retlw	(fp__SPIDACworker-fpbase)&0ffh
	retlw	(fp__SPIEEworker-fpbase)&0ffh
	retlw	(fp__SPIPWMworker-fpbase)&0ffh
	retlw	(fp__UARTworker-fpbase)&0ffh
	retlw	(fp__UARTworker-fpbase)&0ffh
	retlw	(fp__UARTworker-fpbase)&0ffh
	retlw	(fp__UARTworker-fpbase)&0ffh
	retlw	(fp__I2CADCworker-fpbase)&0ffh
	retlw	(fp__I2CDACworker-fpbase)&0ffh
	retlw	(fp__I2CEEworker-fpbase)&0ffh
	retlw	(fp__I2CPWMworker-fpbase)&0ffh
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\./uart.h"
	line	49

;initializer for _msgMenu
	retlw	low(_msgMenu0|8000h)
	retlw	high(_msgMenu0|8000h)

	retlw	low(_msgMenu1|8000h)
	retlw	high(_msgMenu1|8000h)

	retlw	low(_msgMenu2|8000h)
	retlw	high(_msgMenu2|8000h)

	retlw	low(_msgMenu3|8000h)
	retlw	high(_msgMenu3|8000h)

	retlw	low(_msgMenu4|8000h)
	retlw	high(_msgMenu4|8000h)

	global	_msgMenu1
psect	stringtext,class=STRCODE,delta=2,reloc=256
global __pstringtext
__pstringtext:
	global    __stringtab
__stringtab:
	retlw	0
psect	stringtext
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\./uart.h"
	line	39
_msgMenu1:
	retlw	0Ah
	retlw	0Ah
	retlw	041h
	retlw	044h
	retlw	043h
	retlw	020h
	retlw	04Dh
	retlw	065h
	retlw	06Eh
	retlw	075h
	retlw	0Ah
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	0Ah
	retlw	0Ah
	retlw	072h
	retlw	029h
	retlw	052h
	retlw	065h
	retlw	061h
	retlw	064h
	retlw	020h
	retlw	041h
	retlw	044h
	retlw	043h
	retlw	0Ah
	retlw	031h
	retlw	029h
	retlw	043h
	retlw	068h
	retlw	061h
	retlw	06Eh
	retlw	06Eh
	retlw	065h
	retlw	06Ch
	retlw	020h
	retlw	06Ch
	retlw	0Ah
	retlw	032h
	retlw	029h
	retlw	043h
	retlw	068h
	retlw	061h
	retlw	06Eh
	retlw	06Eh
	retlw	065h
	retlw	06Ch
	retlw	020h
	retlw	032h
	retlw	0Ah
	retlw	033h
	retlw	029h
	retlw	043h
	retlw	068h
	retlw	061h
	retlw	06Eh
	retlw	06Eh
	retlw	065h
	retlw	06Ch
	retlw	020h
	retlw	033h
	retlw	0Ah
	retlw	074h
	retlw	029h
	retlw	054h
	retlw	065h
	retlw	06Dh
	retlw	070h
	retlw	065h
	retlw	072h
	retlw	061h
	retlw	074h
	retlw	075h
	retlw	072h
	retlw	065h
	retlw	020h
	retlw	073h
	retlw	065h
	retlw	06Eh
	retlw	073h
	retlw	06Fh
	retlw	072h
	retlw	0Ah
	retlw	06Dh
	retlw	029h
	retlw	042h
	retlw	061h
	retlw	063h
	retlw	06Bh
	retlw	020h
	retlw	074h
	retlw	06Fh
	retlw	020h
	retlw	06Dh
	retlw	061h
	retlw	069h
	retlw	06Eh
	retlw	020h
	retlw	06Dh
	retlw	065h
	retlw	06Eh
	retlw	075h
	retlw	0Ah
	retlw	0Ah
	retlw	043h
	retlw	068h
	retlw	06Fh
	retlw	06Fh
	retlw	073h
	retlw	065h
	retlw	03Ah
	retlw	020h
	retlw	0
	retlw	0
	global	_msgMenu4
psect	stringtext
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\./uart.h"
	line	42
_msgMenu4:
	retlw	0Ah
	retlw	0Ah
	retlw	045h
	retlw	045h
	retlw	050h
	retlw	052h
	retlw	04Fh
	retlw	04Dh
	retlw	020h
	retlw	04Dh
	retlw	065h
	retlw	06Eh
	retlw	075h
	retlw	0Ah
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	0Ah
	retlw	0Ah
	retlw	077h
	retlw	029h
	retlw	057h
	retlw	072h
	retlw	069h
	retlw	074h
	retlw	065h
	retlw	020h
	retlw	061h
	retlw	020h
	retlw	063h
	retlw	068h
	retlw	061h
	retlw	072h
	retlw	061h
	retlw	063h
	retlw	074h
	retlw	065h
	retlw	072h
	retlw	020h
	retlw	074h
	retlw	06Fh
	retlw	020h
	retlw	045h
	retlw	045h
	retlw	050h
	retlw	052h
	retlw	04Fh
	retlw	04Dh
	retlw	0Ah
	retlw	072h
	retlw	029h
	retlw	052h
	retlw	065h
	retlw	061h
	retlw	064h
	retlw	020h
	retlw	061h
	retlw	020h
	retlw	063h
	retlw	068h
	retlw	061h
	retlw	072h
	retlw	061h
	retlw	063h
	retlw	074h
	retlw	065h
	retlw	072h
	retlw	020h
	retlw	066h
	retlw	072h
	retlw	06Fh
	retlw	06Dh
	retlw	020h
	retlw	045h
	retlw	045h
	retlw	050h
	retlw	052h
	retlw	04Fh
	retlw	04Dh
	retlw	0Ah
	retlw	06Dh
	retlw	029h
	retlw	042h
	retlw	061h
	retlw	063h
	retlw	06Bh
	retlw	020h
	retlw	074h
	retlw	06Fh
	retlw	020h
	retlw	06Dh
	retlw	061h
	retlw	069h
	retlw	06Eh
	retlw	020h
	retlw	06Dh
	retlw	065h
	retlw	06Eh
	retlw	075h
	retlw	0Ah
	retlw	0Ah
	retlw	043h
	retlw	068h
	retlw	06Fh
	retlw	06Fh
	retlw	073h
	retlw	065h
	retlw	03Ah
	retlw	020h
	retlw	0
	retlw	0
	global	_msgMenu0
psect	stringtext
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\./uart.h"
	line	38
_msgMenu0:
	retlw	0Ah
	retlw	0Ah
	retlw	042h
	retlw	075h
	retlw	073h
	retlw	020h
	retlw	050h
	retlw	069h
	retlw	072h
	retlw	061h
	retlw	074h
	retlw	065h
	retlw	020h
	retlw	044h
	retlw	065h
	retlw	06Dh
	retlw	06Fh
	retlw	020h
	retlw	042h
	retlw	06Fh
	retlw	061h
	retlw	072h
	retlw	064h
	retlw	020h
	retlw	076h
	retlw	035h
	retlw	0Ah
	retlw	046h
	retlw	057h
	retlw	020h
	retlw	076h
	retlw	065h
	retlw	072h
	retlw	069h
	retlw	073h
	retlw	06Fh
	retlw	06Eh
	retlw	020h
	retlw	076h
	retlw	030h
	retlw	02Eh
	retlw	039h
	retlw	035h
	retlw	0Ah
	retlw	0Ah
	retlw	020h
	retlw	020h
	retlw	04Dh
	retlw	061h
	retlw	069h
	retlw	06Eh
	retlw	020h
	retlw	04Dh
	retlw	065h
	retlw	06Eh
	retlw	075h
	retlw	0Ah
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	0Ah
	retlw	0Ah
	retlw	031h
	retlw	029h
	retlw	041h
	retlw	044h
	retlw	043h
	retlw	0Ah
	retlw	032h
	retlw	029h
	retlw	050h
	retlw	057h
	retlw	04Dh
	retlw	0Ah
	retlw	033h
	retlw	029h
	retlw	044h
	retlw	041h
	retlw	043h
	retlw	0Ah
	retlw	034h
	retlw	029h
	retlw	045h
	retlw	045h
	retlw	050h
	retlw	052h
	retlw	04Fh
	retlw	04Dh
	retlw	0Ah
	retlw	0Ah
	retlw	043h
	retlw	068h
	retlw	06Fh
	retlw	06Fh
	retlw	073h
	retlw	065h
	retlw	028h
	retlw	031h
	retlw	02Dh
	retlw	034h
	retlw	029h
	retlw	03Ah
	retlw	0
	retlw	0
	global	_msgMenu2
psect	stringtext
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\./uart.h"
	line	40
_msgMenu2:
	retlw	0Ah
	retlw	0Ah
	retlw	050h
	retlw	057h
	retlw	04Dh
	retlw	020h
	retlw	04Dh
	retlw	065h
	retlw	06Eh
	retlw	075h
	retlw	0Ah
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	0Ah
	retlw	0Ah
	retlw	070h
	retlw	029h
	retlw	053h
	retlw	065h
	retlw	074h
	retlw	020h
	retlw	050h
	retlw	057h
	retlw	04Dh
	retlw	020h
	retlw	050h
	retlw	065h
	retlw	072h
	retlw	069h
	retlw	06Fh
	retlw	064h
	retlw	0Ah
	retlw	064h
	retlw	029h
	retlw	053h
	retlw	065h
	retlw	074h
	retlw	020h
	retlw	050h
	retlw	057h
	retlw	04Dh
	retlw	020h
	retlw	044h
	retlw	075h
	retlw	074h
	retlw	079h
	retlw	020h
	retlw	043h
	retlw	079h
	retlw	063h
	retlw	06Ch
	retlw	065h
	retlw	0Ah
	retlw	06Dh
	retlw	029h
	retlw	042h
	retlw	061h
	retlw	063h
	retlw	06Bh
	retlw	020h
	retlw	074h
	retlw	06Fh
	retlw	020h
	retlw	06Dh
	retlw	061h
	retlw	069h
	retlw	06Eh
	retlw	020h
	retlw	06Dh
	retlw	065h
	retlw	06Eh
	retlw	075h
	retlw	0Ah
	retlw	0Ah
	retlw	043h
	retlw	068h
	retlw	06Fh
	retlw	06Fh
	retlw	073h
	retlw	065h
	retlw	03Ah
	retlw	020h
	retlw	0
	retlw	0
	global	_msgMenu3
psect	stringtext
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\./uart.h"
	line	41
_msgMenu3:
	retlw	0Ah
	retlw	0Ah
	retlw	044h
	retlw	041h
	retlw	043h
	retlw	020h
	retlw	04Dh
	retlw	065h
	retlw	06Eh
	retlw	075h
	retlw	0Ah
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	02Dh
	retlw	0Ah
	retlw	0Ah
	retlw	076h
	retlw	029h
	retlw	053h
	retlw	065h
	retlw	074h
	retlw	020h
	retlw	044h
	retlw	041h
	retlw	043h
	retlw	020h
	retlw	06Ch
	retlw	065h
	retlw	076h
	retlw	065h
	retlw	06Ch
	retlw	020h
	retlw	030h
	retlw	02Dh
	retlw	033h
	retlw	031h
	retlw	0Ah
	retlw	06Dh
	retlw	029h
	retlw	042h
	retlw	061h
	retlw	063h
	retlw	06Bh
	retlw	020h
	retlw	074h
	retlw	06Fh
	retlw	020h
	retlw	06Dh
	retlw	061h
	retlw	069h
	retlw	06Eh
	retlw	020h
	retlw	06Dh
	retlw	065h
	retlw	06Eh
	retlw	075h
	retlw	0Ah
	retlw	0Ah
	retlw	043h
	retlw	068h
	retlw	06Fh
	retlw	06Fh
	retlw	073h
	retlw	065h
	retlw	03Ah
	retlw	020h
	retlw	0
	retlw	0
	global	_msgEEw
psect	stringtext
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\./uart.h"
	line	46
_msgEEw:
	retlw	0Ah
	retlw	0Ah
	retlw	045h
	retlw	06Eh
	retlw	074h
	retlw	065h
	retlw	072h
	retlw	020h
	retlw	074h
	retlw	068h
	retlw	065h
	retlw	020h
	retlw	076h
	retlw	061h
	retlw	072h
	retlw	069h
	retlw	061h
	retlw	062h
	retlw	06Ch
	retlw	065h
	retlw	020h
	retlw	028h
	retlw	030h
	retlw	02Dh
	retlw	032h
	retlw	035h
	retlw	035h
	retlw	029h
	retlw	020h
	retlw	074h
	retlw	06Fh
	retlw	020h
	retlw	062h
	retlw	065h
	retlw	020h
	retlw	065h
	retlw	06Eh
	retlw	074h
	retlw	065h
	retlw	072h
	retlw	065h
	retlw	064h
	retlw	020h
	retlw	069h
	retlw	06Eh
	retlw	074h
	retlw	06Fh
	retlw	020h
	retlw	045h
	retlw	045h
	retlw	050h
	retlw	052h
	retlw	04Fh
	retlw	04Dh
	retlw	03Ah
	retlw	020h
	retlw	0
	global	_msgDACsetV
psect	stringtext
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\./uart.h"
	line	44
_msgDACsetV:
	retlw	0Ah
	retlw	0Ah
	retlw	045h
	retlw	06Eh
	retlw	074h
	retlw	065h
	retlw	072h
	retlw	020h
	retlw	064h
	retlw	065h
	retlw	073h
	retlw	069h
	retlw	072h
	retlw	065h
	retlw	064h
	retlw	020h
	retlw	044h
	retlw	041h
	retlw	043h
	retlw	020h
	retlw	06Ch
	retlw	065h
	retlw	076h
	retlw	065h
	retlw	06Ch
	retlw	020h
	retlw	066h
	retlw	072h
	retlw	06Fh
	retlw	06Dh
	retlw	020h
	retlw	030h
	retlw	020h
	retlw	074h
	retlw	06Fh
	retlw	020h
	retlw	033h
	retlw	031h
	retlw	03Ah
	retlw	020h
	retlw	0
	global	_msgEEaddr
psect	stringtext
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\./uart.h"
	line	47
_msgEEaddr:
	retlw	0Ah
	retlw	0Ah
	retlw	045h
	retlw	06Eh
	retlw	074h
	retlw	065h
	retlw	072h
	retlw	020h
	retlw	074h
	retlw	068h
	retlw	065h
	retlw	020h
	retlw	061h
	retlw	064h
	retlw	064h
	retlw	072h
	retlw	065h
	retlw	073h
	retlw	073h
	retlw	020h
	retlw	030h
	retlw	02Dh
	retlw	032h
	retlw	035h
	retlw	035h
	retlw	03Ah
	retlw	020h
	retlw	0
	global	_msgMenu1
	global	_msgMenu4
	global	_msgMenu0
	global	_msgMenu2
	global	_msgMenu3
	global	_msgEEw
	global	_msgDACsetV
	global	_msgEEaddr
	global	_ringbuff
	global	_PWMduty
	global	_PWMperiod
	global	_mode_device
	global	_mode_protocol
	global	_rhead
	global	_eeBuf
	global	_rtail
	global	_mode
psect	nvBANK0,class=BANK0,space=1
global __pnvBANK0
__pnvBANK0:
_mode:
       ds      1

	global	_PORTA
_PORTA	set	12
	global	_PORTB
_PORTB	set	13
	global	_PORTC
_PORTC	set	14
	global	_PORTCbits
_PORTCbits	set	14
	global	_PR2
_PR2	set	27
	global	_T2CON
_T2CON	set	28
	global	_T2CONbits
_T2CONbits	set	28
	global	_CARRY
_CARRY	set	24
	global	_GIE
_GIE	set	95
	global	_RA2
_RA2	set	98
	global	_RB4
_RB4	set	108
	global	_RB6
_RB6	set	110
	global	_RC2
_RC2	set	114
	global	_RC3
_RC3	set	115
	global	_RC5
_RC5	set	117
	global	_RCIF
_RCIF	set	141
	global	_SSP2IF
_SSP2IF	set	160
	global	_TMR2IF
_TMR2IF	set	137
	global	_TXIF
_TXIF	set	140
	global	_ADCON0
_ADCON0	set	157
	global	_ADCON0bits
_ADCON0bits	set	157
	global	_ADCON1
_ADCON1	set	158
	global	_ADRESH
_ADRESH	set	156
	global	_ADRESL
_ADRESL	set	155
	global	_OSCCONbits
_OSCCONbits	set	153
	global	_TRISA
_TRISA	set	140
	global	_TRISAbits
_TRISAbits	set	140
	global	_TRISB
_TRISB	set	141
	global	_TRISC
_TRISC	set	142
	global	_TRISCbits
_TRISCbits	set	142
	global	_TRISB5
_TRISB5	set	1133
	global	_TRISC4
_TRISC4	set	1140
	global	_nWPUEN
_nWPUEN	set	1199
	global	_APFCON0
_APFCON0	set	285
	global	_APFCON1
_APFCON1	set	286
	global	_APFCON1bits
_APFCON1bits	set	286
	global	_DACCON0
_DACCON0	set	280
	global	_DACCON1
_DACCON1	set	281
	global	_FVRCON
_FVRCON	set	279
	global	_LATA
_LATA	set	268
	global	_LATB
_LATB	set	269
	global	_LATC
_LATC	set	270
	global	_DACOE
_DACOE	set	2245
	global	_EEADR
_EEADR	set	401
	global	_ANSELA
_ANSELA	set	396
	global	_ANSELB
_ANSELB	set	397
	global	_ANSELC
_ANSELC	set	398
	global	_EEADRL
_EEADRL	set	401
	global	_EECON1
_EECON1	set	405
	global	_EECON1bits
_EECON1bits	set	405
	global	_EECON2
_EECON2	set	406
	global	_EEDATA
_EEDATA	set	403
	global	_EEDATL
_EEDATL	set	403
	global	_RCREG
_RCREG	set	409
	global	_RCSTA
_RCSTA	set	413
	global	_SPBRGH
_SPBRGH	set	412
	global	_SPBRGL
_SPBRGL	set	411
	global	_TXREG
_TXREG	set	410
	global	_BRGH
_BRGH	set	3314
	global	_CREN
_CREN	set	3308
	global	_RD
_RD	set	3240
	global	_SPEN
_SPEN	set	3311
	global	_SYNC
_SYNC	set	3316
	global	_TRMT
_TRMT	set	3313
	global	_TXEN
_TXEN	set	3317
	global	_WR
_WR	set	3241
	global	_WREN
_WREN	set	3242
	global	_SSP2ADD
_SSP2ADD	set	538
	global	_SSP2BUF
_SSP2BUF	set	537
	global	_SSP2CON1
_SSP2CON1	set	541
	global	_SSP2CON1bits
_SSP2CON1bits	set	541
	global	_SSP2CON2bits
_SSP2CON2bits	set	542
	global	_SSP2CON3
_SSP2CON3	set	543
	global	_SSP2MSK
_SSP2MSK	set	539
	global	_SSP2STAT
_SSP2STAT	set	540
	global	_SSP2STATbits
_SSP2STATbits	set	540
	global	_WPUA
_WPUA	set	524
	global	_WPUB
_WPUB	set	525
	global	_WPUC
_WPUC	set	526
	global	_CCP2CON
_CCP2CON	set	666
	global	_CCPR2L
_CCPR2L	set	664
	global	_CCPTMRS
_CCPTMRS	set	670
psect	stringtext
	
STR_17:	
	retlw	109	;'m'
	retlw	97	;'a'
	retlw	100	;'d'
	retlw	101	;'e'
	retlw	32	;' '
	retlw	109	;'m'
	retlw	101	;'e'
	retlw	32	;' '
	retlw	100	;'d'
	retlw	111	;'o'
	retlw	32	;' '
	retlw	119	;'w'
	retlw	101	;'e'
	retlw	105	;'i'
	retlw	114	;'r'
	retlw	100	;'d'
	retlw	32	;' '
	retlw	115	;'s'
	retlw	104	;'h'
	retlw	105	;'i'
	retlw	116	;'t'
	retlw	32	;' '
	retlw	108	;'l'
	retlw	105	;'i'
	retlw	107	;'k'
	retlw	101	;'e'
	retlw	32	;' '
	retlw	80	;'P'
	retlw	87	;'W'
	retlw	77	;'M'
	retlw	44	;','
	retlw	32	;' '
	retlw	109	;'m'
	retlw	101	;'e'
	retlw	109	;'m'
	retlw	111	;'o'
	retlw	114	;'r'
	retlw	121	;'y'
	retlw	101	;'e'
	retlw	109	;'m'
	retlw	117	;'u'
	retlw	108	;'l'
	retlw	97	;'a'
	retlw	116	;'t'
	retlw	105	;'i'
	retlw	111	;'o'
	retlw	110	;'n'
	retlw	44	;','
	retlw	32	;' '
	retlw	99	;'c'
	retlw	111	;'o'
	retlw	110	;'n'
	retlw	118	;'v'
	retlw	101	;'e'
	retlw	114	;'r'
	retlw	116	;'t'
	retlw	32	;' '
	retlw	104	;'h'
	retlw	105	;'i'
	retlw	103	;'g'
	retlw	104	;'h'
	retlw	32	;' '
	retlw	118	;'v'
	retlw	111	;'o'
	retlw	108	;'l'
	retlw	116	;'t'
	retlw	97	;'a'
	retlw	103	;'g'
	retlw	101	;'e'
	retlw	115	;'s'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	13
	retlw	10
	retlw	0
psect	stringtext
	
STR_11:	
	retlw	84	;'T'
	retlw	104	;'h'
	retlw	101	;'e'
	retlw	121	;'y'
	retlw	32	;' '
	retlw	112	;'p'
	retlw	117	;'u'
	retlw	116	;'t'
	retlw	32	;' '
	retlw	109	;'m'
	retlw	101	;'e'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	104	;'h'
	retlw	114	;'r'
	retlw	111	;'o'
	retlw	117	;'u'
	retlw	103	;'g'
	retlw	104	;'h'
	retlw	32	;' '
	retlw	101	;'e'
	retlw	110	;'n'
	retlw	100	;'d'
	retlw	108	;'l'
	retlw	101	;'e'
	retlw	115	;'s'
	retlw	115	;'s'
	retlw	32	;' '
	retlw	104	;'h'
	retlw	111	;'o'
	retlw	117	;'u'
	retlw	114	;'r'
	retlw	115	;'s'
	retlw	32	;' '
	retlw	111	;'o'
	retlw	102	;'f'
	retlw	32	;' '
	retlw	114	;'r'
	retlw	101	;'e'
	retlw	103	;'g'
	retlw	114	;'r'
	retlw	101	;'e'
	retlw	115	;'s'
	retlw	115	;'s'
	retlw	105	;'i'
	retlw	111	;'o'
	retlw	110	;'n'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	115	;'s'
	retlw	116	;'t'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	13
	retlw	10
	retlw	0
psect	stringtext
	
STR_13:	
	retlw	46	;'.'
	retlw	99	;'c'
	retlw	111	;'o'
	retlw	110	;'n'
	retlw	110	;'n'
	retlw	101	;'e'
	retlw	99	;'c'
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	100	;'d'
	retlw	32	;' '
	retlw	109	;'m'
	retlw	101	;'e'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	111	;'o'
	retlw	32	;' '
	retlw	119	;'w'
	retlw	101	;'e'
	retlw	105	;'i'
	retlw	114	;'r'
	retlw	100	;'d'
	retlw	32	;' '
	retlw	112	;'p'
	retlw	114	;'r'
	retlw	111	;'o'
	retlw	116	;'t'
	retlw	111	;'o'
	retlw	116	;'t'
	retlw	121	;'y'
	retlw	112	;'p'
	retlw	101	;'e'
	retlw	115	;'s'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	13
	retlw	10
	retlw	0
psect	stringtext
	
STR_18:	
	retlw	67	;'C'
	retlw	79	;'O'
	retlw	85	;'U'
	retlw	76	;'L'
	retlw	68	;'D'
	retlw	32	;' '
	retlw	89	;'Y'
	retlw	79	;'O'
	retlw	85	;'U'
	retlw	32	;' '
	retlw	80	;'P'
	retlw	76	;'L'
	retlw	69	;'E'
	retlw	65	;'A'
	retlw	83	;'S'
	retlw	69	;'E'
	retlw	32	;' '
	retlw	76	;'L'
	retlw	69	;'E'
	retlw	65	;'A'
	retlw	86	;'V'
	retlw	69	;'E'
	retlw	32	;' '
	retlw	77	;'M'
	retlw	69	;'E'
	retlw	32	;' '
	retlw	65	;'A'
	retlw	76	;'L'
	retlw	79	;'O'
	retlw	78	;'N'
	retlw	69	;'E'
	retlw	63	;'?'
	retlw	33	;'!'
	retlw	63	;'?'
	retlw	33	;'!'
	retlw	63	;'?'
	retlw	33	;'!'
	retlw	0
psect	stringtext
	
STR_12:	
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	32	;' '
	retlw	99	;'c'
	retlw	111	;'o'
	retlw	110	;'n'
	retlw	100	;'d'
	retlw	117	;'u'
	retlw	99	;'c'
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	100	;'d'
	retlw	32	;' '
	retlw	115	;'s'
	retlw	101	;'e'
	retlw	118	;'v'
	retlw	101	;'e'
	retlw	114	;'r'
	retlw	97	;'a'
	retlw	108	;'l'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	115	;'s'
	retlw	116	;'t'
	retlw	115	;'s'
	retlw	32	;' '
	retlw	111	;'o'
	retlw	110	;'n'
	retlw	32	;' '
	retlw	109	;'m'
	retlw	101	;'e'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	13
	retlw	10
	retlw	0
psect	stringtext
	
STR_8:	
	retlw	10
	retlw	10
	retlw	72	;'H'
	retlw	105	;'i'
	retlw	116	;'t'
	retlw	32	;' '
	retlw	97	;'a'
	retlw	110	;'n'
	retlw	121	;'y'
	retlw	32	;' '
	retlw	107	;'k'
	retlw	101	;'e'
	retlw	121	;'y'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	111	;'o'
	retlw	32	;' '
	retlw	114	;'r'
	retlw	101	;'e'
	retlw	97	;'a'
	retlw	100	;'d'
	retlw	32	;' '
	retlw	102	;'f'
	retlw	114	;'r'
	retlw	111	;'o'
	retlw	109	;'m'
	retlw	32	;' '
	retlw	69	;'E'
	retlw	69	;'E'
	retlw	80	;'P'
	retlw	82	;'R'
	retlw	79	;'O'
	retlw	77	;'M'
	retlw	46	;'.'
	retlw	10
	retlw	10
	retlw	0
psect	stringtext
	
STR_16:	
	retlw	108	;'l'
	retlw	101	;'e'
	retlw	116	;'t'
	retlw	32	;' '
	retlw	109	;'m'
	retlw	101	;'e'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	97	;'a'
	retlw	108	;'l'
	retlw	107	;'k'
	retlw	32	;' '
	retlw	73	;'I'
	retlw	50	;'2'
	retlw	67	;'C'
	retlw	44	;','
	retlw	32	;' '
	retlw	83	;'S'
	retlw	80	;'P'
	retlw	73	;'I'
	retlw	44	;','
	retlw	32	;' '
	retlw	85	;'U'
	retlw	65	;'A'
	retlw	82	;'R'
	retlw	84	;'T'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	13
	retlw	10
	retlw	0
psect	stringtext
	
STR_10:	
	retlw	73	;'I'
	retlw	39	;'''
	retlw	109	;'m'
	retlw	32	;' '
	retlw	104	;'h'
	retlw	97	;'a'
	retlw	112	;'p'
	retlw	112	;'p'
	retlw	121	;'y'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	111	;'o'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	108	;'l'
	retlw	32	;' '
	retlw	121	;'y'
	retlw	111	;'o'
	retlw	117	;'u'
	retlw	32	;' '
	retlw	109	;'m'
	retlw	121	;'y'
	retlw	32	;' '
	retlw	115	;'s'
	retlw	116	;'t'
	retlw	111	;'o'
	retlw	114	;'r'
	retlw	121	;'y'
	retlw	13
	retlw	10
	retlw	0
psect	stringtext
	
STR_9:	
	retlw	72	;'H'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	108	;'l'
	retlw	111	;'o'
	retlw	44	;','
	retlw	32	;' '
	retlw	110	;'n'
	retlw	105	;'i'
	retlw	99	;'c'
	retlw	101	;'e'
	retlw	32	;' '
	retlw	111	;'o'
	retlw	102	;'f'
	retlw	32	;' '
	retlw	121	;'y'
	retlw	111	;'o'
	retlw	117	;'u'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	111	;'o'
	retlw	32	;' '
	retlw	100	;'d'
	retlw	114	;'r'
	retlw	111	;'o'
	retlw	112	;'p'
	retlw	32	;' '
	retlw	98	;'b'
	retlw	121	;'y'
	retlw	13
	retlw	10
	retlw	0
psect	stringtext
	
STR_7:	
	retlw	10
	retlw	10
	retlw	69	;'E'
	retlw	110	;'n'
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	114	;'r'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	104	;'h'
	retlw	101	;'e'
	retlw	32	;' '
	retlw	80	;'P'
	retlw	87	;'W'
	retlw	77	;'M'
	retlw	32	;' '
	retlw	68	;'D'
	retlw	117	;'u'
	retlw	116	;'t'
	retlw	121	;'y'
	retlw	32	;' '
	retlw	67	;'C'
	retlw	121	;'y'
	retlw	99	;'c'
	retlw	108	;'l'
	retlw	101	;'e'
	retlw	58	;':'
	retlw	32	;' '
	retlw	0
psect	stringtext
	
STR_6:	
	retlw	10
	retlw	10
	retlw	69	;'E'
	retlw	110	;'n'
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	114	;'r'
	retlw	32	;' '
	retlw	116	;'t'
	retlw	104	;'h'
	retlw	101	;'e'
	retlw	32	;' '
	retlw	80	;'P'
	retlw	87	;'W'
	retlw	77	;'M'
	retlw	32	;' '
	retlw	80	;'P'
	retlw	101	;'e'
	retlw	114	;'r'
	retlw	105	;'i'
	retlw	111	;'o'
	retlw	100	;'d'
	retlw	58	;':'
	retlw	32	;' '
	retlw	0
psect	stringtext
	
STR_15:	
	retlw	117	;'u'
	retlw	115	;'s'
	retlw	101	;'e'
	retlw	100	;'d'
	retlw	32	;' '
	retlw	72	;'H'
	retlw	105	;'i'
	retlw	90	;'Z'
	retlw	32	;' '
	retlw	111	;'o'
	retlw	110	;'n'
	retlw	32	;' '
	retlw	109	;'m'
	retlw	101	;'e'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	13
	retlw	10
	retlw	0
psect	stringtext
	
STR_14:	
	retlw	97	;'a'
	retlw	98	;'b'
	retlw	117	;'u'
	retlw	115	;'s'
	retlw	101	;'e'
	retlw	100	;'d'
	retlw	32	;' '
	retlw	109	;'m'
	retlw	101	;'e'
	retlw	32	;' '
	retlw	119	;'w'
	retlw	105	;'i'
	retlw	116	;'t'
	retlw	104	;'h'
	retlw	32	;' '
	retlw	53	;'5'
	retlw	86	;'V'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	46	;'.'
	retlw	13
	retlw	10
	retlw	0
psect	stringtext
	
STR_5:	
	retlw	10
	retlw	10
	retlw	84	;'T'
	retlw	101	;'e'
	retlw	109	;'m'
	retlw	112	;'p'
	retlw	32	;' '
	retlw	115	;'s'
	retlw	101	;'e'
	retlw	110	;'n'
	retlw	115	;'s'
	retlw	111	;'o'
	retlw	114	;'r'
	retlw	32	;' '
	retlw	115	;'s'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	101	;'e'
	retlw	99	;'c'
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	100	;'d'
	retlw	0
psect	stringtext
	
STR_2:	
	retlw	10
	retlw	10
	retlw	99	;'c'
	retlw	104	;'h'
	retlw	97	;'a'
	retlw	110	;'n'
	retlw	110	;'n'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	32	;' '
	retlw	49	;'1'
	retlw	32	;' '
	retlw	115	;'s'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	101	;'e'
	retlw	99	;'c'
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	100	;'d'
	retlw	0
psect	stringtext
	
STR_3:	
	retlw	10
	retlw	10
	retlw	99	;'c'
	retlw	104	;'h'
	retlw	97	;'a'
	retlw	110	;'n'
	retlw	110	;'n'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	32	;' '
	retlw	50	;'2'
	retlw	32	;' '
	retlw	115	;'s'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	101	;'e'
	retlw	99	;'c'
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	100	;'d'
	retlw	0
psect	stringtext
	
STR_4:	
	retlw	10
	retlw	10
	retlw	99	;'c'
	retlw	104	;'h'
	retlw	97	;'a'
	retlw	110	;'n'
	retlw	110	;'n'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	32	;' '
	retlw	51	;'3'
	retlw	32	;' '
	retlw	115	;'s'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	101	;'e'
	retlw	99	;'c'
	retlw	116	;'t'
	retlw	101	;'e'
	retlw	100	;'d'
	retlw	0
psect	stringtext
	
STR_1:	
	retlw	10
	retlw	10
	retlw	65	;'A'
	retlw	68	;'D'
	retlw	67	;'C'
	retlw	32	;' '
	retlw	118	;'v'
	retlw	97	;'a'
	retlw	108	;'l'
	retlw	117	;'u'
	retlw	101	;'e'
	retlw	58	;':'
	retlw	32	;' '
	retlw	0
psect	stringtext
	file	"BP Demoboard v5.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

_eeBuf  equ     8944	;BIGRAM
psect	bssCOMMON,class=COMMON,space=1
global __pbssCOMMON
__pbssCOMMON:
_rtail:
       ds      1

psect	bssBANK0,class=BANK0,space=1
global __pbssBANK0
__pbssBANK0:
_ringbuff:
       ds      16

_PWMduty:
       ds      1

_PWMperiod:
       ds      1

_mode_device:
       ds      1

_mode_protocol:
       ds      1

_rhead:
       ds      1

psect	dataBANK0,class=BANK0,space=1
global __pdataBANK0
__pdataBANK0:
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
	line	36
_protos:
       ds      16

psect	dataBANK0
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\./uart.h"
	line	49
_msgMenu:
       ds      10

psect clrtext,class=CODE,delta=2
global clear_ram
;	Called with FSR0 containing the base address, and
;	btemp/btemp+1 has the size to clear
clear_ram:
	clrwdt			;clear the watchdog before getting into this loop
clrloop:
	clrf	indf0		;clear RAM location pointed to by FSR
	addfsr	0,1
	movlw	1
	subwf	btemp,f
	movlw	0
	subwfb btemp+1,f
	movf btemp+1,w
	iorwf btemp,w
	skipz
	goto clrloop	;have we reached the end yet?
	retlw	0		;all done for this memory range, return
; Clear objects allocated to BIGRAM
psect cinit,class=CODE,delta=2
	global __pbssBIGRAM
	movlw	low(__pbssBIGRAM)
	movwf	fsr0l
	movlw	high(__pbssBIGRAM)
	movwf	fsr0h
	movlw	low(0100h)
	movwf	btemp
	movlw	high(0100h)
	movwf	btemp+1
	fcall	clear_ram
; Clear objects allocated to COMMON
psect cinit,class=CODE,delta=2
	global __pbssCOMMON
	clrf	((__pbssCOMMON)+0)&07Fh
; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2
	global __pbssBANK0
	movlw	low(__pbssBANK0)
	movwf	fsr0l
	movlw	high(__pbssBANK0)
	movwf	fsr0h
	movlw	low(015h)
	movwf	btemp
	movlw	high(015h)
	movwf	btemp+1
	fcall	clear_ram
psect inittext,class=CODE,delta=2
global init_ram,btemp
init_ram:
	movwf btemp,f
initloop:
	moviw fsr0++
	movwi fsr1++
	movlw 1
subwf btemp,f
movlw 0
subwfb btemp+1,f
	movf btemp+1,w
	iorwf btemp,w
	skipz
	goto initloop
	retlw 0
; Initialize objects allocated to BANK0
	global __pidataBANK0,__pdataBANK0
psect cinit,class=CODE,delta=2
	movlw low(__pidataBANK0)
	movwf fsr0l
	movlw high(__pidataBANK0)|80h
	movwf fsr0h
	movlw low(__pdataBANK0)
	movwf fsr1l
	movlw high(__pdataBANK0)
	movwf fsr1h
	movlw high(01Ah)
	movwf btemp+1
	movlw low(01Ah)
	fcall init_ram
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
movlb 0
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_nullfunc1
?_nullfunc1:	; 0 bytes @ 0x0
	global	?_SPIADCworker
?_SPIADCworker:	; 0 bytes @ 0x0
	global	?_SPIDACworker
?_SPIDACworker:	; 0 bytes @ 0x0
	global	?_SPIEEworker
?_SPIEEworker:	; 0 bytes @ 0x0
	global	?_SPIPWMworker
?_SPIPWMworker:	; 0 bytes @ 0x0
	global	?_UARTworker
?_UARTworker:	; 0 bytes @ 0x0
	global	?_I2CADCworker
?_I2CADCworker:	; 0 bytes @ 0x0
	global	?_I2CDACworker
?_I2CDACworker:	; 0 bytes @ 0x0
	global	?_I2CEEworker
?_I2CEEworker:	; 0 bytes @ 0x0
	global	?_I2CPWMworker
?_I2CPWMworker:	; 0 bytes @ 0x0
	global	?_init
?_init:	; 0 bytes @ 0x0
	global	?_doEE
?_doEE:	; 0 bytes @ 0x0
	global	?_initSPI
?_initSPI:	; 0 bytes @ 0x0
	global	?_initI2C
?_initI2C:	; 0 bytes @ 0x0
	global	?_initUART
?_initUART:	; 0 bytes @ 0x0
	global	?_enableTS
?_enableTS:	; 0 bytes @ 0x0
	global	?_I2CWrite
?_I2CWrite:	; 0 bytes @ 0x0
	global	?_enableDAC
?_enableDAC:	; 0 bytes @ 0x0
	global	?_setDAC
?_setDAC:	; 0 bytes @ 0x0
	global	?_enablePWM
?_enablePWM:	; 0 bytes @ 0x0
	global	?_setPeriod
?_setPeriod:	; 0 bytes @ 0x0
	global	?_setDuty
?_setDuty:	; 0 bytes @ 0x0
	global	?_UARTwrite
?_UARTwrite:	; 0 bytes @ 0x0
	global	?_UARTwriteDecimal
?_UARTwriteDecimal:	; 0 bytes @ 0x0
	global	?_disablePWM
?_disablePWM:	; 0 bytes @ 0x0
	global	?_disableDAC
?_disableDAC:	; 0 bytes @ 0x0
	global	?_isr
?_isr:	; 0 bytes @ 0x0
	global	??_isr
??_isr:	; 0 bytes @ 0x0
	global	?_EEPROMread
?_EEPROMread:	; 1 bytes @ 0x0
	global	?_isEE
?_isEE:	; 1 bytes @ 0x0
	global	?_UARTread
?_UARTread:	; 1 bytes @ 0x0
	global	?_UARTcharFromString
?_UARTcharFromString:	; 1 bytes @ 0x0
	global	?_startADC16
?_startADC16:	; 2 bytes @ 0x0
	global	?_main
?_main:	; 2 bytes @ 0x0
	ds	3
	global	??_nullfunc1
??_nullfunc1:	; 0 bytes @ 0x3
	global	??_EEPROMread
??_EEPROMread:	; 0 bytes @ 0x3
	global	??_isEE
??_isEE:	; 0 bytes @ 0x3
	global	??_initSPI
??_initSPI:	; 0 bytes @ 0x3
	global	??_initI2C
??_initI2C:	; 0 bytes @ 0x3
	global	??_initUART
??_initUART:	; 0 bytes @ 0x3
	global	??_enableTS
??_enableTS:	; 0 bytes @ 0x3
	global	??_I2CWrite
??_I2CWrite:	; 0 bytes @ 0x3
	global	??_startADC16
??_startADC16:	; 0 bytes @ 0x3
	global	??_enableDAC
??_enableDAC:	; 0 bytes @ 0x3
	global	??_setDAC
??_setDAC:	; 0 bytes @ 0x3
	global	??_UARTwrite
??_UARTwrite:	; 0 bytes @ 0x3
	global	??_UARTread
??_UARTread:	; 0 bytes @ 0x3
	global	??_disablePWM
??_disablePWM:	; 0 bytes @ 0x3
	global	??_disableDAC
??_disableDAC:	; 0 bytes @ 0x3
	global	?___bmul
?___bmul:	; 1 bytes @ 0x3
	global	?___lbdiv
?___lbdiv:	; 1 bytes @ 0x3
	global	?_getADC
?_getADC:	; 2 bytes @ 0x3
	global	?___wmul
?___wmul:	; 2 bytes @ 0x3
	global	?___lwdiv
?___lwdiv:	; 2 bytes @ 0x3
	global	I2CWrite@c
I2CWrite@c:	; 1 bytes @ 0x3
	global	UARTwrite@c
UARTwrite@c:	; 1 bytes @ 0x3
	global	EEPROMread@addr
EEPROMread@addr:	; 1 bytes @ 0x3
	global	setDAC@dac
setDAC@dac:	; 1 bytes @ 0x3
	global	___bmul@multiplicand
___bmul@multiplicand:	; 1 bytes @ 0x3
	global	___lbdiv@divisor
___lbdiv@divisor:	; 1 bytes @ 0x3
	global	___wmul@multiplier
___wmul@multiplier:	; 2 bytes @ 0x3
	global	___lwdiv@divisor
___lwdiv@divisor:	; 2 bytes @ 0x3
	ds	1
	global	??_SPIDACworker
??_SPIDACworker:	; 0 bytes @ 0x4
	global	??_I2CDACworker
??_I2CDACworker:	; 0 bytes @ 0x4
	global	??_init
??_init:	; 0 bytes @ 0x4
	global	?_UARTwriteString
?_UARTwriteString:	; 0 bytes @ 0x4
	global	?_teletype
?_teletype:	; 0 bytes @ 0x4
	global	??___bmul
??___bmul:	; 0 bytes @ 0x4
	global	??___lbdiv
??___lbdiv:	; 0 bytes @ 0x4
	global	SPIDACworker@fInst
SPIDACworker@fInst:	; 1 bytes @ 0x4
	global	UARTread@temp
UARTread@temp:	; 1 bytes @ 0x4
	global	UARTwriteString@str
UARTwriteString@str:	; 2 bytes @ 0x4
	global	teletype@s
teletype@s:	; 2 bytes @ 0x4
	global	startADC16@i
startADC16@i:	; 2 bytes @ 0x4
	ds	1
	global	??_getADC
??_getADC:	; 0 bytes @ 0x5
	global	I2CDACworker@temp
I2CDACworker@temp:	; 1 bytes @ 0x5
	global	SPIDACworker@fb
SPIDACworker@fb:	; 1 bytes @ 0x5
	global	___bmul@product
___bmul@product:	; 1 bytes @ 0x5
	global	___lbdiv@dividend
___lbdiv@dividend:	; 1 bytes @ 0x5
	global	___wmul@multiplicand
___wmul@multiplicand:	; 2 bytes @ 0x5
	global	___lwdiv@dividend
___lwdiv@dividend:	; 2 bytes @ 0x5
	ds	1
	global	??_UARTwriteString
??_UARTwriteString:	; 0 bytes @ 0x6
	global	??_teletype
??_teletype:	; 0 bytes @ 0x6
	global	I2CDACworker@fb
I2CDACworker@fb:	; 1 bytes @ 0x6
	global	SPIDACworker@bf
SPIDACworker@bf:	; 1 bytes @ 0x6
	global	startADC16@adc
startADC16@adc:	; 1 bytes @ 0x6
	global	___bmul@multiplier
___bmul@multiplier:	; 1 bytes @ 0x6
	global	___lbdiv@counter
___lbdiv@counter:	; 1 bytes @ 0x6
	global	teletype@i
teletype@i:	; 2 bytes @ 0x6
	ds	1
	global	??_I2CADCworker
??_I2CADCworker:	; 0 bytes @ 0x7
	global	?_EEPROMwrite
?_EEPROMwrite:	; 0 bytes @ 0x7
	global	??___wmul
??___wmul:	; 0 bytes @ 0x7
	global	??___lwdiv
??___lwdiv:	; 0 bytes @ 0x7
	global	I2CDACworker@token
I2CDACworker@token:	; 1 bytes @ 0x7
	global	EEPROMwrite@data
EEPROMwrite@data:	; 1 bytes @ 0x7
	global	___lbdiv@quotient
___lbdiv@quotient:	; 1 bytes @ 0x7
	global	___wmul@product
___wmul@product:	; 2 bytes @ 0x7
	ds	1
	global	??_SPIADCworker
??_SPIADCworker:	; 0 bytes @ 0x8
	global	??_doEE
??_doEE:	; 0 bytes @ 0x8
	global	??_EEPROMwrite
??_EEPROMwrite:	; 0 bytes @ 0x8
	global	??_UARTwriteDecimal
??_UARTwriteDecimal:	; 0 bytes @ 0x8
	global	I2CDACworker@command
I2CDACworker@command:	; 1 bytes @ 0x8
	global	UARTwriteString@i
UARTwriteString@i:	; 1 bytes @ 0x8
	global	EEPROMwrite@addr
EEPROMwrite@addr:	; 1 bytes @ 0x8
	ds	1
	global	??_SPIPWMworker
??_SPIPWMworker:	; 0 bytes @ 0x9
	global	??_I2CPWMworker
??_I2CPWMworker:	; 0 bytes @ 0x9
	global	I2CDACworker@dac
I2CDACworker@dac:	; 1 bytes @ 0x9
	ds	1
psect	cstackBANK0,class=BANK0,space=1
global __pcstackBANK0
__pcstackBANK0:
	global	??_SPIEEworker
??_SPIEEworker:	; 0 bytes @ 0x0
	global	??_I2CEEworker
??_I2CEEworker:	; 0 bytes @ 0x0
	global	??_UARTcharFromString
??_UARTcharFromString:	; 0 bytes @ 0x0
	global	I2CADCworker@adcON
I2CADCworker@adcON:	; 1 bytes @ 0x0
	global	UARTwriteDecimal@c
UARTwriteDecimal@c:	; 1 bytes @ 0x0
	global	getADC@temp
getADC@temp:	; 1 bytes @ 0x0
	global	___lwdiv@counter
___lwdiv@counter:	; 1 bytes @ 0x0
	ds	1
	global	I2CADCworker@temp
I2CADCworker@temp:	; 1 bytes @ 0x1
	global	UARTwriteDecimal@hC
UARTwriteDecimal@hC:	; 1 bytes @ 0x1
	global	getADC@i
getADC@i:	; 2 bytes @ 0x1
	global	___lwdiv@quotient
___lwdiv@quotient:	; 2 bytes @ 0x1
	ds	1
	global	I2CADCworker@token
I2CADCworker@token:	; 1 bytes @ 0x2
	global	UARTcharFromString@c
UARTcharFromString@c:	; 1 bytes @ 0x2
	global	UARTwriteDecimal@d
UARTwriteDecimal@d:	; 1 bytes @ 0x2
	ds	1
	global	??_enablePWM
??_enablePWM:	; 0 bytes @ 0x3
	global	??_setPeriod
??_setPeriod:	; 0 bytes @ 0x3
	global	??_setDuty
??_setDuty:	; 0 bytes @ 0x3
	global	I2CEEworker@temp
I2CEEworker@temp:	; 1 bytes @ 0x3
	global	I2CADCworker@adc
I2CADCworker@adc:	; 1 bytes @ 0x3
	global	SPIEEworker@fb2
SPIEEworker@fb2:	; 1 bytes @ 0x3
	global	UARTcharFromString@outF
UARTcharFromString@outF:	; 1 bytes @ 0x3
	global	getADC@adc
getADC@adc:	; 1 bytes @ 0x3
	ds	1
	global	I2CEEworker@token
I2CEEworker@token:	; 1 bytes @ 0x4
	global	I2CADCworker@fb
I2CADCworker@fb:	; 1 bytes @ 0x4
	global	SPIEEworker@pageIndex
SPIEEworker@pageIndex:	; 1 bytes @ 0x4
	global	SPIADCworker@fInst
SPIADCworker@fInst:	; 1 bytes @ 0x4
	global	UARTcharFromString@c1
UARTcharFromString@c1:	; 1 bytes @ 0x4
	ds	1
	global	I2CEEworker@addressed
I2CEEworker@addressed:	; 1 bytes @ 0x5
	global	I2CADCworker@config
I2CADCworker@config:	; 1 bytes @ 0x5
	global	SPIEEworker@WIP
SPIEEworker@WIP:	; 1 bytes @ 0x5
	global	SPIADCworker@bf
SPIADCworker@bf:	; 1 bytes @ 0x5
	global	UARTcharFromString@rC
UARTcharFromString@rC:	; 1 bytes @ 0x5
	ds	1
	global	I2CEEworker@w
I2CEEworker@w:	; 1 bytes @ 0x6
	global	SPIEEworker@instruction
SPIEEworker@instruction:	; 1 bytes @ 0x6
	global	SPIADCworker@chanel
SPIADCworker@chanel:	; 1 bytes @ 0x6
	global	enablePWM@tempP
enablePWM@tempP:	; 2 bytes @ 0x6
	ds	1
	global	I2CEEworker@i
I2CEEworker@i:	; 1 bytes @ 0x7
	global	SPIEEworker@fb
SPIEEworker@fb:	; 1 bytes @ 0x7
	global	SPIADCworker@fb
SPIADCworker@fb:	; 1 bytes @ 0x7
	global	setDuty@D
setDuty@D:	; 1 bytes @ 0x7
	global	setPeriod@temp
setPeriod@temp:	; 2 bytes @ 0x7
	ds	1
	global	I2CEEworker@addr
I2CEEworker@addr:	; 1 bytes @ 0x8
	global	SPIEEworker@bf
SPIEEworker@bf:	; 1 bytes @ 0x8
	global	setDuty@temp
setDuty@temp:	; 2 bytes @ 0x8
	ds	1
	global	SPIEEworker@WREN
SPIEEworker@WREN:	; 1 bytes @ 0x9
	global	setPeriod@P
setPeriod@P:	; 1 bytes @ 0x9
	ds	1
	global	??_UARTworker
??_UARTworker:	; 0 bytes @ 0xA
	global	I2CPWMworker@temp
I2CPWMworker@temp:	; 1 bytes @ 0xA
	global	SPIEEworker@token
SPIEEworker@token:	; 1 bytes @ 0xA
	global	SPIPWMworker@token
SPIPWMworker@token:	; 1 bytes @ 0xA
	ds	1
	global	I2CPWMworker@token
I2CPWMworker@token:	; 1 bytes @ 0xB
	global	SPIEEworker@addressed
SPIEEworker@addressed:	; 1 bytes @ 0xB
	global	SPIPWMworker@instruction
SPIPWMworker@instruction:	; 1 bytes @ 0xB
	ds	1
	global	I2CPWMworker@tempP
I2CPWMworker@tempP:	; 1 bytes @ 0xC
	global	SPIEEworker@w
SPIEEworker@w:	; 1 bytes @ 0xC
	global	SPIPWMworker@fb
SPIPWMworker@fb:	; 1 bytes @ 0xC
	global	UARTworker@addr
UARTworker@addr:	; 1 bytes @ 0xC
	ds	1
	global	I2CPWMworker@tempD
I2CPWMworker@tempD:	; 1 bytes @ 0xD
	global	SPIEEworker@i
SPIEEworker@i:	; 1 bytes @ 0xD
	global	SPIPWMworker@bf
SPIPWMworker@bf:	; 1 bytes @ 0xD
	global	UARTworker@helpC
UARTworker@helpC:	; 1 bytes @ 0xD
	ds	1
	global	I2CPWMworker@fD
I2CPWMworker@fD:	; 1 bytes @ 0xE
	global	SPIEEworker@fInst
SPIEEworker@fInst:	; 1 bytes @ 0xE
	global	SPIPWMworker@fInst
SPIPWMworker@fInst:	; 1 bytes @ 0xE
	global	UARTworker@EEaddrF
UARTworker@EEaddrF:	; 1 bytes @ 0xE
	ds	1
	global	I2CPWMworker@fP
I2CPWMworker@fP:	; 1 bytes @ 0xF
	global	SPIEEworker@STATUS
SPIEEworker@STATUS:	; 1 bytes @ 0xF
	global	UARTworker@adcc
UARTworker@adcc:	; 1 bytes @ 0xF
	ds	1
	global	I2CPWMworker@addressed
I2CPWMworker@addressed:	; 1 bytes @ 0x10
	global	SPIEEworker@addr
SPIEEworker@addr:	; 1 bytes @ 0x10
	global	UARTworker@EEaddr
UARTworker@EEaddr:	; 1 bytes @ 0x10
	ds	1
	global	I2CPWMworker@addr
I2CPWMworker@addr:	; 1 bytes @ 0x11
	global	UARTworker@mode
UARTworker@mode:	; 1 bytes @ 0x11
	ds	1
	global	UARTworker@c
UARTworker@c:	; 1 bytes @ 0x12
	ds	1
	global	UARTworker@instruction
UARTworker@instruction:	; 1 bytes @ 0x13
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0x14
	ds	3
	global	main@i
main@i:	; 2 bytes @ 0x17
	ds	2
;;Data sizes: Strings 585, constant 654, data 26, bss 22, persistent 1 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14     10      11
;; BANK0           80     25      73
;; BANK1           80      0       0
;; BANK2           80      0       0
;; BANK3           80      0       0
;; BANK4           80      0       0
;; BANK5           80      0       0
;; BANK6           80      0       0
;; BANK7           80      0       0
;; BANK8           80      0       0
;; BANK9           32      0       0
;; BANK10           0      0       0
;; BANK11           0      0       0
;; BANK12           0      0       0

;;
;; Pointer list with targets:

;; ?___lwdiv	unsigned int  size(1) Largest target is 0
;;
;; ?___wmul	unsigned int  size(1) Largest target is 0
;;
;; ?_getADC	unsigned int  size(1) Largest target is 0
;;
;; teletype@s	PTR const unsigned char  size(2) Largest target is 75
;;		 -> STR_18(CODE[38]), STR_17(CODE[75]), STR_16(CODE[35]), STR_15(CODE[24]), 
;;		 -> STR_14(CODE[24]), STR_13(CODE[39]), STR_12(CODE[37]), STR_11(CODE[57]), 
;;		 -> STR_10(CODE[33]), STR_9(CODE[32]), 
;;
;; UARTwriteString@str	PTR unsigned char  size(2) Largest target is 123
;;		 -> msgEEaddr(CODE[28]), STR_8(CODE[37]), msgEEw(CODE[57]), msgDACsetV(CODE[41]), 
;;		 -> STR_7(CODE[29]), STR_6(CODE[25]), STR_5(CODE[23]), STR_4(CODE[21]), 
;;		 -> STR_3(CODE[21]), STR_2(CODE[21]), STR_1(CODE[14]), msgMenu4(CODE[122]), 
;;		 -> msgMenu3(CODE[76]), msgMenu2(CODE[93]), msgMenu1(CODE[123]), msgMenu0(CODE[114]), 
;;
;; S2893_proto$PWMworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CPWMworker(), UARTworker(), SPIPWMworker(), nullfunc1(), 
;;
;; protos.PWMworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CPWMworker(), UARTworker(), SPIPWMworker(), nullfunc1(), 
;;
;; S2893_proto$EEPROMworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CEEworker(), UARTworker(), SPIEEworker(), nullfunc1(), 
;;
;; protos.EEPROMworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CEEworker(), UARTworker(), SPIEEworker(), nullfunc1(), 
;;
;; S2893_proto$DACworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CDACworker(), UARTworker(), SPIDACworker(), nullfunc1(), 
;;
;; protos.DACworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CDACworker(), UARTworker(), SPIDACworker(), nullfunc1(), 
;;
;; S2893_proto$ADCworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CADCworker(), UARTworker(), SPIADCworker(), nullfunc1(), 
;;
;; protos.ADCworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CADCworker(), UARTworker(), SPIADCworker(), nullfunc1(), 
;;
;; msgMenu	PTR const unsigned char [5] size(2) Largest target is 123
;;		 -> msgMenu4(CODE[122]), msgMenu3(CODE[76]), msgMenu2(CODE[93]), msgMenu1(CODE[123]), 
;;		 -> msgMenu0(CODE[114]), 
;;


;;
;; Critical Paths under _main in COMMON
;;
;;   _main->_SPIADCworker
;;   _main->_I2CDACworker
;;   _main->_I2CPWMworker
;;   _main->_SPIPWMworker
;;   _UARTworker->_UARTwriteDecimal
;;   _doEE->_teletype
;;   _teletype->_UARTwrite
;;   _UARTcharFromString->_EEPROMwrite
;;   _UARTwriteDecimal->___lbdiv
;;   _UARTwriteString->_UARTwrite
;;   _SPIADCworker->_getADC
;;   _SPIDACworker->_setDAC
;;   _SPIEEworker->_EEPROMwrite
;;   _setDuty->___wmul
;;   _setPeriod->___wmul
;;   _enablePWM->___wmul
;;   _I2CDACworker->_setDAC
;;   _I2CDACworker->_I2CWrite
;;   _I2CADCworker->_startADC16
;;   _I2CEEworker->_EEPROMwrite
;;   _init->_initI2C
;;   _EEPROMwrite->___bmul
;;
;; Critical Paths under _isr in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   _main->_UARTworker
;;   _UARTworker->_setPeriod
;;   _UARTworker->_setDuty
;;   _SPIPWMworker->_setPeriod
;;   _SPIPWMworker->_setDuty
;;   _I2CPWMworker->_setPeriod
;;   _I2CPWMworker->_setDuty
;;   _SPIADCworker->_getADC
;;   _setDuty->___lwdiv
;;   _setPeriod->___lwdiv
;;   _enablePWM->___lwdiv
;;
;; Critical Paths under _isr in BANK0
;;
;;   None.
;;
;; Critical Paths under _main in BANK1
;;
;;   None.
;;
;; Critical Paths under _isr in BANK1
;;
;;   None.
;;
;; Critical Paths under _main in BANK2
;;
;;   None.
;;
;; Critical Paths under _isr in BANK2
;;
;;   None.
;;
;; Critical Paths under _main in BANK3
;;
;;   None.
;;
;; Critical Paths under _isr in BANK3
;;
;;   None.
;;
;; Critical Paths under _main in BANK4
;;
;;   None.
;;
;; Critical Paths under _isr in BANK4
;;
;;   None.
;;
;; Critical Paths under _main in BANK5
;;
;;   None.
;;
;; Critical Paths under _isr in BANK5
;;
;;   None.
;;
;; Critical Paths under _main in BANK6
;;
;;   None.
;;
;; Critical Paths under _isr in BANK6
;;
;;   None.
;;
;; Critical Paths under _main in BANK7
;;
;;   None.
;;
;; Critical Paths under _isr in BANK7
;;
;;   None.
;;
;; Critical Paths under _main in BANK8
;;
;;   None.
;;
;; Critical Paths under _isr in BANK8
;;
;;   None.
;;
;; Critical Paths under _main in BANK9
;;
;;   None.
;;
;; Critical Paths under _isr in BANK9
;;
;;   None.
;;
;; Critical Paths under _main in BANK10
;;
;;   None.
;;
;; Critical Paths under _isr in BANK10
;;
;;   None.
;;
;; Critical Paths under _main in BANK11
;;
;;   None.
;;
;; Critical Paths under _isr in BANK11
;;
;;   None.
;;
;; Critical Paths under _main in BANK12
;;
;;   None.
;;
;; Critical Paths under _isr in BANK12
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 3, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 5     5      0    9427
;;                                             20 BANK0      5     5      0
;;                               _init
;;                         _EEPROMread
;;                               _isEE
;;                               _doEE
;;                       _I2CADCworker
;;                         _UARTworker
;;                       _SPIADCworker
;;                          _nullfunc1
;;                        _I2CEEworker
;;                        _SPIEEworker
;;                       _I2CDACworker
;;                       _SPIDACworker
;;                       _I2CPWMworker
;;                       _SPIPWMworker
;; ---------------------------------------------------------------------------------
;; (1) _UARTworker                                          10    10      0    3869
;;                                             10 BANK0     10    10      0
;;                           _initUART
;;                    _UARTwriteString
;;                          _UARTwrite
;;                           _UARTread
;;                          _enablePWM
;;                          _enableDAC
;;                             _getADC
;;                   _UARTwriteDecimal
;;                 _UARTcharFromString
;;                          _setPeriod
;;                            _setDuty
;;                         _disablePWM
;;                             _setDAC
;;                         _disableDAC
;;                        _EEPROMwrite
;;                         _EEPROMread
;; ---------------------------------------------------------------------------------
;; (1) _SPIPWMworker                                         6     6      0    1713
;;                                              9 COMMON     1     1      0
;;                                             10 BANK0      5     5      0
;;                            _initSPI
;;                          _enablePWM
;;                          _setPeriod
;;                            _setDuty
;; ---------------------------------------------------------------------------------
;; (1) _I2CPWMworker                                        11    11      0    1697
;;                                              9 COMMON     1     1      0
;;                                             10 BANK0      8     8      0
;;                          _enablePWM
;;                          _setPeriod
;;                            _setDuty
;; ---------------------------------------------------------------------------------
;; (1) _doEE                                                 0     0      0     113
;;                           _teletype
;; ---------------------------------------------------------------------------------
;; (2) _teletype                                             5     3      2     113
;;                                              4 COMMON     4     2      2
;;                          _UARTwrite
;; ---------------------------------------------------------------------------------
;; (2) _UARTcharFromString                                   6     6      0     372
;;                                              0 BANK0      6     6      0
;;                           _UARTread
;;                          _UARTwrite
;;                             ___bmul
;;                        _EEPROMwrite (ARG)
;; ---------------------------------------------------------------------------------
;; (2) _UARTwriteDecimal                                     5     5      0     434
;;                                              8 COMMON     2     2      0
;;                                              0 BANK0      3     3      0
;;                            ___lbdiv
;;                          _UARTwrite
;;                             ___bmul
;; ---------------------------------------------------------------------------------
;; (2) _UARTwriteString                                      5     3      2     112
;;                                              4 COMMON     5     3      2
;;                          _UARTwrite
;; ---------------------------------------------------------------------------------
;; (1) _SPIADCworker                                         8     8      0     237
;;                                              8 COMMON     2     2      0
;;                                              4 BANK0      4     4      0
;;                            _initSPI
;;                             _getADC
;; ---------------------------------------------------------------------------------
;; (1) _SPIDACworker                                         5     5      0      73
;;                                              4 COMMON     3     3      0
;;                            _initSPI
;;                          _enableDAC
;;                             _setDAC
;; ---------------------------------------------------------------------------------
;; (1) _SPIEEworker                                         17    17      0     795
;;                                              0 BANK0     17    17      0
;;                            _initSPI
;;                        _EEPROMwrite
;; ---------------------------------------------------------------------------------
;; (2) _setDuty                                              7     7      0     531
;;                                              3 BANK0      7     7      0
;;                             ___wmul
;;                            ___lwdiv
;; ---------------------------------------------------------------------------------
;; (2) _setPeriod                                            7     7      0     525
;;                                              3 BANK0      7     7      0
;;                             ___wmul
;;                            ___lwdiv
;; ---------------------------------------------------------------------------------
;; (2) _enablePWM                                            5     5      0     367
;;                                              3 BANK0      5     5      0
;;                             ___wmul
;;                            ___lwdiv
;; ---------------------------------------------------------------------------------
;; (1) _I2CDACworker                                         6     6      0     212
;;                                              4 COMMON     6     6      0
;;                          _enableDAC
;;                             _setDAC
;;                           _I2CWrite
;; ---------------------------------------------------------------------------------
;; (1) _I2CADCworker                                         7     7      0     240
;;                                              7 COMMON     1     1      0
;;                                              0 BANK0      6     6      0
;;                           _enableTS
;;                           _I2CWrite
;;                         _startADC16
;; ---------------------------------------------------------------------------------
;; (1) _I2CEEworker                                          9     9      0     326
;;                                              0 BANK0      9     9      0
;;                        _EEPROMwrite
;; ---------------------------------------------------------------------------------
;; (1) _init                                                 1     1      0       0
;;                                              4 COMMON     1     1      0
;;                            _initSPI
;;                            _initI2C
;;                           _initUART
;; ---------------------------------------------------------------------------------
;; (3) ___lbdiv                                              5     4      1     162
;;                                              3 COMMON     5     4      1
;; ---------------------------------------------------------------------------------
;; (3) ___lwdiv                                              8     4      4     241
;;                                              3 COMMON     5     1      4
;;                                              0 BANK0      3     3      0
;; ---------------------------------------------------------------------------------
;; (3) ___wmul                                               6     2      4      92
;;                                              3 COMMON     6     2      4
;; ---------------------------------------------------------------------------------
;; (3) ___bmul                                               4     3      1      92
;;                                              3 COMMON     4     3      1
;; ---------------------------------------------------------------------------------
;; (2) _disableDAC                                           0     0      0       0
;; ---------------------------------------------------------------------------------
;; (2) _disablePWM                                           0     0      0       0
;; ---------------------------------------------------------------------------------
;; (3) _UARTread                                             2     2      0      23
;;                                              3 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; (3) _UARTwrite                                            1     1      0      22
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _getADC                                               9     7      2     118
;;                                              3 COMMON     5     3      2
;;                                              0 BANK0      4     4      0
;; ---------------------------------------------------------------------------------
;; (2) _setDAC                                               1     1      0      22
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _enableDAC                                            0     0      0       0
;; ---------------------------------------------------------------------------------
;; (2) _startADC16                                           5     5      0      95
;;                                              3 COMMON     4     4      0
;; ---------------------------------------------------------------------------------
;; (2) _I2CWrite                                             1     1      0      22
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _enableTS                                             1     1      0       0
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _EEPROMwrite                                          2     1      1      44
;;                                              7 COMMON     2     1      1
;;                           _UARTread (ARG)
;;                          _UARTwrite (ARG)
;;                             ___bmul (ARG)
;; ---------------------------------------------------------------------------------
;; (2) _initUART                                             1     1      0       0
;; ---------------------------------------------------------------------------------
;; (2) _initI2C                                              1     1      0       0
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _initSPI                                              0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _isEE                                                 0     0      0       0
;; ---------------------------------------------------------------------------------
;; (2) _EEPROMread                                           1     1      0      22
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (1) _nullfunc1                                            0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 3
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (4) _isr                                                  3     3      0       0
;;                                              0 COMMON     3     3      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 4
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _init
;;     _initSPI
;;     _initI2C
;;     _initUART
;;   _EEPROMread
;;   _isEE
;;   _doEE
;;     _teletype
;;       _UARTwrite
;;   _I2CADCworker
;;     _enableTS
;;     _I2CWrite
;;     _startADC16
;;   _UARTworker
;;     _initUART
;;     _UARTwriteString
;;       _UARTwrite
;;     _UARTwrite
;;     _UARTread
;;     _enablePWM
;;       ___wmul
;;       ___lwdiv
;;     _enableDAC
;;     _getADC
;;     _UARTwriteDecimal
;;       ___lbdiv
;;       _UARTwrite
;;       ___bmul
;;     _UARTcharFromString
;;       _UARTread
;;       _UARTwrite
;;       ___bmul
;;       _EEPROMwrite (ARG)
;;         _UARTread (ARG)
;;         _UARTwrite (ARG)
;;         ___bmul (ARG)
;;     _setPeriod
;;       ___wmul
;;       ___lwdiv
;;     _setDuty
;;       ___wmul
;;       ___lwdiv
;;     _disablePWM
;;     _setDAC
;;     _disableDAC
;;     _EEPROMwrite
;;       _UARTread (ARG)
;;       _UARTwrite (ARG)
;;       ___bmul (ARG)
;;     _EEPROMread
;;   _SPIADCworker
;;     _initSPI
;;     _getADC
;;   _nullfunc1
;;   _I2CEEworker
;;     _EEPROMwrite
;;       _UARTread (ARG)
;;       _UARTwrite (ARG)
;;       ___bmul (ARG)
;;   _SPIEEworker
;;     _initSPI
;;     _EEPROMwrite
;;       _UARTread (ARG)
;;       _UARTwrite (ARG)
;;       ___bmul (ARG)
;;   _I2CDACworker
;;     _enableDAC
;;     _setDAC
;;     _I2CWrite
;;   _SPIDACworker
;;     _initSPI
;;     _enableDAC
;;     _setDAC
;;   _I2CPWMworker
;;     _enablePWM
;;       ___wmul
;;       ___lwdiv
;;     _setPeriod
;;       ___wmul
;;       ___lwdiv
;;     _setDuty
;;       ___wmul
;;       ___lwdiv
;;   _SPIPWMworker
;;     _initSPI
;;     _enablePWM
;;       ___wmul
;;       ___lwdiv
;;     _setPeriod
;;       ___wmul
;;       ___lwdiv
;;     _setDuty
;;       ___wmul
;;       ___lwdiv
;;
;; _isr (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BIGRAM             3F0      0       0       0        0.0%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;BITCOMMON            E      0       0       1        0.0%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;COMMON               E      A       B       2       78.6%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;BITSFR2              0      0       0       3        0.0%
;;SFR2                 0      0       0       3        0.0%
;;STACK                0      0       3       3        0.0%
;;BITBANK0            50      0       0       4        0.0%
;;BITSFR3              0      0       0       4        0.0%
;;SFR3                 0      0       0       4        0.0%
;;BANK0               50     19      49       5       91.3%
;;BITSFR4              0      0       0       5        0.0%
;;SFR4                 0      0       0       5        0.0%
;;BITBANK1            50      0       0       6        0.0%
;;BITSFR5              0      0       0       6        0.0%
;;SFR5                 0      0       0       6        0.0%
;;BANK1               50      0       0       7        0.0%
;;BITSFR6              0      0       0       7        0.0%
;;SFR6                 0      0       0       7        0.0%
;;BITBANK2            50      0       0       8        0.0%
;;BITSFR7              0      0       0       8        0.0%
;;SFR7                 0      0       0       8        0.0%
;;BANK2               50      0       0       9        0.0%
;;BITSFR8              0      0       0       9        0.0%
;;SFR8                 0      0       0       9        0.0%
;;BITBANK3            50      0       0      10        0.0%
;;BITSFR9              0      0       0      10        0.0%
;;SFR9                 0      0       0      10        0.0%
;;BANK3               50      0       0      11        0.0%
;;BITSFR10             0      0       0      11        0.0%
;;SFR10                0      0       0      11        0.0%
;;BITBANK4            50      0       0      12        0.0%
;;BITSFR11             0      0       0      12        0.0%
;;SFR11                0      0       0      12        0.0%
;;BANK4               50      0       0      13        0.0%
;;BITSFR12             0      0       0      13        0.0%
;;SFR12                0      0       0      13        0.0%
;;BITBANK5            50      0       0      14        0.0%
;;BITSFR13             0      0       0      14        0.0%
;;SFR13                0      0       0      14        0.0%
;;BANK5               50      0       0      15        0.0%
;;BITSFR14             0      0       0      15        0.0%
;;SFR14                0      0       0      15        0.0%
;;BITBANK6            50      0       0      16        0.0%
;;BITSFR15             0      0       0      16        0.0%
;;SFR15                0      0       0      16        0.0%
;;BANK6               50      0       0      17        0.0%
;;BITSFR16             0      0       0      17        0.0%
;;SFR16                0      0       0      17        0.0%
;;BITBANK7            50      0       0      18        0.0%
;;BITSFR17             0      0       0      18        0.0%
;;SFR17                0      0       0      18        0.0%
;;BANK7               50      0       0      19        0.0%
;;BITSFR18             0      0       0      19        0.0%
;;SFR18                0      0       0      19        0.0%
;;BITSFR19             0      0       0      20        0.0%
;;SFR19                0      0       0      20        0.0%
;;ABS                  0      0      54      20        0.0%
;;BITBANK8            50      0       0      21        0.0%
;;BITSFR20             0      0       0      21        0.0%
;;SFR20                0      0       0      21        0.0%
;;BANK8               50      0       0      22        0.0%
;;BITSFR21             0      0       0      22        0.0%
;;SFR21                0      0       0      22        0.0%
;;BITBANK9            50      0       0      23        0.0%
;;BITSFR22             0      0       0      23        0.0%
;;SFR22                0      0       0      23        0.0%
;;BANK9               20      0       0      24        0.0%
;;BITSFR23             0      0       0      24        0.0%
;;SFR23                0      0       0      24        0.0%
;;BITBANK10           50      0       0      25        0.0%
;;BITSFR24             0      0       0      25        0.0%
;;SFR24                0      0       0      25        0.0%
;;BITSFR25             0      0       0      26        0.0%
;;SFR25                0      0       0      26        0.0%
;;BANK10               0      0       0      26        0.0%
;;BITBANK11           50      0       0      27        0.0%
;;BITSFR26             0      0       0      27        0.0%
;;SFR26                0      0       0      27        0.0%
;;BITSFR27             0      0       0      28        0.0%
;;SFR27                0      0       0      28        0.0%
;;BANK11               0      0       0      28        0.0%
;;BITBANK12           30      0       0      29        0.0%
;;BITSFR28             0      0       0      29        0.0%
;;SFR28                0      0       0      29        0.0%
;;BITSFR29             0      0       0      30        0.0%
;;SFR29                0      0       0      30        0.0%
;;BANK12               0      0       0      30        0.0%
;;BITSFR30             0      0       0      31        0.0%
;;SFR30                0      0       0      31        0.0%
;;DATA                 0      0      57      31        0.0%
;;BITSFR31             0      0       0      32        0.0%
;;SFR31                0      0       0      32        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 75 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               2   23[BANK0 ] int 
;; Return value:  Size  Location     Type
;;                  2  1625[COMMON] int 
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr1l, fsr1h, status,2, status,0, btemp+1, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       3       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       5       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_init
;;		_EEPROMread
;;		_isEE
;;		_doEE
;;		_I2CADCworker
;;		_UARTworker
;;		_SPIADCworker
;;		_nullfunc1
;;		_I2CEEworker
;;		_SPIEEworker
;;		_I2CDACworker
;;		_SPIDACworker
;;		_I2CPWMworker
;;		_SPIPWMworker
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
	line	75
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 12
; Regs used in _main: [allreg]
	line	76
	
l20084:	
;main.c: 76: mode=0x03;
	movlw	(03h)
	movlb 0	; select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_mode)
	line	78
	
l20086:	
;main.c: 78: init();
	fcall	_init
	line	81
	
l20088:	
;main.c: 80: int i;
;main.c: 81: for (i=0;i<256;i++)
	movlb 0	; select bank0
	clrf	(main@i)
	clrf	(main@i+1)
	
l20090:	
	movf	(main@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(0100h))^80h
	subwf	btemp+1,w
	skipz
	goto	u5175
	movlw	low(0100h)
	subwf	(main@i),w
u5175:

	skipc
	goto	u5171
	goto	u5170
u5171:
	goto	l20094
u5170:
	goto	l20100
	
l20092:	
	goto	l20100
	line	82
	
l1626:	
	line	83
	
l20094:	
;main.c: 82: {
;main.c: 83: eeBuf[i]= EEPROMread(i);
	movlb 0	; select bank0
	movf	(main@i),w
	fcall	_EEPROMread
	movlb 0	; select bank0
	movwf	(??_main+0)+0
	movf	(main@i),w
	addlw	low 8944
	movwf	(??_main+1)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_main+1)+0)+1
	movf	0+(??_main+1)+0,w
	movwf	fsr1l
	movf	1+(??_main+1)+0,w
	movwf	fsr1h

	movf	(??_main+0)+0,w
	movwf	indf1
	line	81
	
l20096:	
	movlw	low(01h)
	addwf	(main@i),f
	movlw	high(01h)
	addwfc	(main@i+1),f
	
l20098:	
	movf	(main@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(0100h))^80h
	subwf	btemp+1,w
	skipz
	goto	u5185
	movlw	low(0100h)
	subwf	(main@i),w
u5185:

	skipc
	goto	u5181
	goto	u5180
u5181:
	goto	l20094
u5180:
	goto	l20100
	
l1627:	
	goto	l20100
	line	87
;main.c: 84: }
;main.c: 87: while(1){
	
l1628:	
	line	89
	
l20100:	
;main.c: 89: if(isEE()) doEE();
	fcall	_isEE
	xorlw	0&0ffh
	skipnz
	goto	u5191
	goto	u5190
u5191:
	goto	l20114
u5190:
	
l20102:	
	fcall	_doEE
	goto	l20114
	
l1629:	
	line	92
;main.c: 92: switch(mode_device)
	goto	l20114
	line	94
;main.c: 93: {
;main.c: 94: case 0x03: protos[mode_protocol].ADCworker();
	
l1631:	
	
l20104:	
	movlb 0	; select bank0
	movf	(_mode_protocol),w
	movwf	(??_main+0)+0
	movlw	(02h)-1
u5205:
	lslf	(??_main+0)+0,f
	addlw	-1
	skipz
	goto	u5205
	lslf	(??_main+0)+0,w
	addlw	_protos&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	fcall	fptable
	line	95
;main.c: 95: break;
	goto	l20100
	line	96
;main.c: 96: case 0x02: protos[mode_protocol].EEPROMworker();
	
l1633:	
	
l20106:	
	movlb 0	; select bank0
	movf	(_mode_protocol),w
	movwf	(??_main+0)+0
	movlw	(02h)-1
u5215:
	lslf	(??_main+0)+0,f
	addlw	-1
	skipz
	goto	u5215
	lslf	(??_main+0)+0,w
	addlw	02h
	addlw	_protos&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	fcall	fptable
	line	97
;main.c: 97: break;
	goto	l20100
	line	98
;main.c: 98: case 0x01: protos[mode_protocol].DACworker();
	
l1634:	
	
l20108:	
	movlb 0	; select bank0
	movf	(_mode_protocol),w
	movwf	(??_main+0)+0
	movlw	(02h)-1
u5225:
	lslf	(??_main+0)+0,f
	addlw	-1
	skipz
	goto	u5225
	lslf	(??_main+0)+0,w
	addlw	01h
	addlw	_protos&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	fcall	fptable
	line	99
;main.c: 99: break;
	goto	l20100
	line	100
;main.c: 100: case 0x00: protos[mode_protocol].PWMworker();
	
l1635:	
	
l20110:	
	movlb 0	; select bank0
	movf	(_mode_protocol),w
	movwf	(??_main+0)+0
	movlw	(02h)-1
u5235:
	lslf	(??_main+0)+0,f
	addlw	-1
	skipz
	goto	u5235
	lslf	(??_main+0)+0,w
	addlw	03h
	addlw	_protos&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	fcall	fptable
	goto	l20100
	line	101
;main.c: 101: default: break;
	
l1636:	
	goto	l20100
	line	102
	
l20112:	
;main.c: 102: }
	goto	l20100
	line	92
	
l1630:	
	
l20114:	
	movlb 0	; select bank0
	movf	(_mode_device),w
	; Switch size 1, requested type "space"
; Number of cases is 4, Range of values is 0 to 3
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           13     7 (average)
; direct_byte           14     6 (fixed)
; jumptable            260     6 (fixed)
; rangetable             8     4 (fixed)
; spacedrange           13     6 (fixed)
; locatedrange           4     3 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	0^0	; case 0
	skipnz
	goto	l20110
	xorlw	1^0	; case 1
	skipnz
	goto	l20108
	xorlw	2^1	; case 2
	skipnz
	goto	l20106
	xorlw	3^2	; case 3
	skipnz
	goto	l20104
	goto	l20100
	opt asmopt_on

	line	102
	
l1632:	
	goto	l20100
	line	103
	
l1637:	
	line	87
	goto	l20100
	
l1638:	
	line	105
	
l1639:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,90
	global	_UARTworker
	global	_nullfunc1
	global	_SPIADCworker
	global	_I2CADCworker
psect	text1300,local,class=CODE,delta=2
global __ptext1300
__ptext1300:

;; *************** function _I2CADCworker *****************
;; Defined at:
;;		line 98 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  config          1    5[BANK0 ] unsigned char 
;;  fb              1    4[BANK0 ] unsigned char 
;;  adc             1    3[BANK0 ] unsigned char 
;;  token           1    2[BANK0 ] unsigned char 
;;  temp            1    1[BANK0 ] unsigned char 
;;  adcON           1    0[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, btemp+1, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       6       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       6       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        7 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_enableTS
;;		_I2CWrite
;;		_startADC16
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1300
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
	line	98
	global	__size_of_I2CADCworker
	__size_of_I2CADCworker	equ	__end_of_I2CADCworker-_I2CADCworker
	
_I2CADCworker:	
	opt	stack 13
; Regs used in _I2CADCworker: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	
l18918:	
	movlb 0	; select bank0
	clrf	(I2CADCworker@config)
	clrf	(I2CADCworker@adcON)
	clrf	(I2CADCworker@fb)
	line	100
;i2c.c: 100: adc=0x00;
	clrf	(I2CADCworker@adc)
	line	101
	
l18920:	
;i2c.c: 101: enableTS();
	fcall	_enableTS
	line	102
	
l18922:	
;i2c.c: 102: SSP2ADD=0x68;
	movlw	(068h)
	movlb 4	; select bank4
	movwf	(538)^0200h	;volatile
	goto	l18924
	line	104
;i2c.c: 104: while(1)
	
l3266:	
	line	107
	
l18924:	
;i2c.c: 105: {
;i2c.c: 107: if(SSP2IF)
	movlb 0	; select bank0
	btfss	(160/8),(160)&7
	goto	u3731
	goto	u3730
u3731:
	goto	l18924
u3730:
	line	109
	
l18926:	
;i2c.c: 108: {
;i2c.c: 109: token=SSP2STAT&0x25;
	movlb 4	; select bank4
	movf	(540)^0200h,w
	andlw	025h
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CADCworker@token)
	line	111
	
l18928:	
;i2c.c: 111: if(SSP2STATbits.S)
	movlb 4	; select bank4
	btfss	(540)^0200h,3	;volatile
	goto	u3741
	goto	u3740
u3741:
	goto	l3268
u3740:
	line	112
	
l18930:	
;i2c.c: 112: { RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	113
;i2c.c: 113: switch(token)
	goto	l18952
	line	115
;i2c.c: 114: {
;i2c.c: 115: case 0x01:
	
l3270:	
	line	116
	
l18932:	
;i2c.c: 116: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CADCworker@temp)
	line	117
;i2c.c: 117: break;
	goto	l18964
	line	118
;i2c.c: 118: case 0x21:
	
l3272:	
	line	119
	
l18934:	
;i2c.c: 119: config=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CADCworker@config)
	line	120
;i2c.c: 120: break;
	goto	l18964
	line	121
;i2c.c: 121: case 0x05:
	
l3273:	
	line	122
	
l18936:	
;i2c.c: 122: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CADCworker@temp)
	line	123
	
l18938:	
;i2c.c: 123: I2CWrite(ADRESH);
	movlb 1	; select bank1
	movf	(156)^080h,w	;volatile
	fcall	_I2CWrite
	line	124
;i2c.c: 124: break;
	goto	l18964
	line	125
;i2c.c: 125: case 0x24:
	
l3274:	
	line	126
	
l18940:	
;i2c.c: 126: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CADCworker@temp)
	line	127
	
l18942:	
;i2c.c: 127: if(fb==0)
	movf	(I2CADCworker@fb),f
	skipz
	goto	u3751
	goto	u3750
u3751:
	goto	l18948
u3750:
	line	129
	
l18944:	
;i2c.c: 128: {
;i2c.c: 129: fb=1;
	clrf	(I2CADCworker@fb)
	bsf	status,0
	rlf	(I2CADCworker@fb),f
	line	130
	
l18946:	
;i2c.c: 130: I2CWrite(ADRESL);
	movlb 1	; select bank1
	movf	(155)^080h,w	;volatile
	fcall	_I2CWrite
	line	131
;i2c.c: 131: }
	goto	l18964
	line	132
	
l3275:	
	line	134
	
l18948:	
;i2c.c: 132: else
;i2c.c: 133: {
;i2c.c: 134: I2CWrite(config&(ADCON0bits.ADGO<<7));
	movlb 1	; select bank1
	rrf	(157)^080h,w	;volatile
	andlw	(1<<1)-1
	movwf	(??_I2CADCworker+0)+0
	movlw	(07h)-1
u3765:
	lslf	(??_I2CADCworker+0)+0,f
	addlw	-1
	skipz
	goto	u3765
	lslf	(??_I2CADCworker+0)+0,w
	movlb 0	; select bank0
	andwf	(I2CADCworker@config),w
	fcall	_I2CWrite
	goto	l18964
	line	135
	
l3276:	
	line	136
;i2c.c: 135: }
;i2c.c: 136: break;
	goto	l18964
	line	137
	
l18950:	
;i2c.c: 137: }
	goto	l18964
	line	113
	
l3269:	
	
l18952:	
	movlb 0	; select bank0
	movf	(I2CADCworker@token),w
	; Switch size 1, requested type "space"
; Number of cases is 4, Range of values is 1 to 36
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           13     7 (average)
; direct_byte           81     9 (fixed)
; jumptable            263     9 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	1^0	; case 1
	skipnz
	goto	l18932
	xorlw	5^1	; case 5
	skipnz
	goto	l18936
	xorlw	33^5	; case 33
	skipnz
	goto	l18934
	xorlw	36^33	; case 36
	skipnz
	goto	l18940
	goto	l18964
	opt asmopt_on

	line	137
	
l3271:	
	line	138
;i2c.c: 138: }
	goto	l18964
	line	139
	
l3268:	
;i2c.c: 139: else if(SSP2STATbits.P)
	btfss	(540)^0200h,4	;volatile
	goto	u3771
	goto	u3770
u3771:
	goto	l18964
u3770:
	line	141
	
l18954:	
;i2c.c: 140: {
;i2c.c: 141: fb=0;
	movlb 0	; select bank0
	clrf	(I2CADCworker@fb)
	line	142
;i2c.c: 142: RC5=0;;
	bcf	(117/8),(117)&7
	line	143
	
l18956:	
;i2c.c: 143: adc=config&0b01100000;
	movf	(I2CADCworker@config),w
	andlw	060h
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movwf	(I2CADCworker@adc)
	line	144
	
l18958:	
;i2c.c: 144: adc>>=5;
	swapf (I2CADCworker@adc),f
	rrf	(I2CADCworker@adc),f
	movlw	7
	andwf	(I2CADCworker@adc),f

	line	145
	
l18960:	
;i2c.c: 145: startADC16(adc);
	movf	(I2CADCworker@adc),w
	fcall	_startADC16
	line	146
	
l18962:	
# 146 "C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
NOP ;#
psect	text1300
	goto	l18964
	line	148
	
l3278:	
	goto	l18964
	line	150
	
l3277:	
	
l18964:	
;i2c.c: 148: }
;i2c.c: 150: SSP2IF=0;
	movlb 0	; select bank0
	bcf	(160/8),(160)&7
	line	151
	
l18966:	
;i2c.c: 151: ADCON0bits.ADGO=1;
	movlb 1	; select bank1
	bsf	(157)^080h,1	;volatile
	line	152
	
l18968:	
;i2c.c: 152: SSP2CON1bits.SSPEN=1;
	movlb 4	; select bank4
	bsf	(541)^0200h,5	;volatile
	line	153
	
l18970:	
;i2c.c: 153: SSP2CON1bits.CKP=1;
	bsf	(541)^0200h,4	;volatile
	goto	l18924
	line	155
	
l3267:	
	goto	l18924
	line	156
	
l3279:	
	line	104
	goto	l18924
	
l3280:	
	line	157
	
l3281:	
	return
	opt stack 0
GLOBAL	__end_of_I2CADCworker
	__end_of_I2CADCworker:
;; =============== function _I2CADCworker ends ============

	signat	_I2CADCworker,88
psect	text1301,local,class=CODE,delta=2
global __ptext1301
__ptext1301:

;; *************** function _SPIADCworker *****************
;; Defined at:
;;		line 261 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\spi.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  fb              1    7[BANK0 ] unsigned char 
;;  chanel          1    6[BANK0 ] unsigned char 
;;  bf              1    5[BANK0 ] unsigned char 
;;  fInst           1    4[BANK0 ] unsigned char 
;;  instruction     1    0        unsigned char 
;;  token           1    0        unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, btemp+1, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       4       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       4       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_initSPI
;;		_getADC
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1301
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\spi.c"
	line	261
	global	__size_of_SPIADCworker
	__size_of_SPIADCworker	equ	__end_of_SPIADCworker-_SPIADCworker
	
_SPIADCworker:	
	opt	stack 13
; Regs used in _SPIADCworker: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	line	262
	
l19218:	
;spi.c: 262: unsigned char token, instruction, chanel, fInst=0,fb=0,bf=0;
	movlb 0	; select bank0
	clrf	(SPIADCworker@fInst)
	clrf	(SPIADCworker@fb)
	clrf	(SPIADCworker@bf)
	line	263
	
l19220:	
;spi.c: 263: initSPI();
	fcall	_initSPI
	line	264
	
l19222:	
;spi.c: 264: SSP2BUF = 0xFD;
	movlw	(0FDh)
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	goto	l19242
	line	266
;spi.c: 266: while (1)
	
l5001:	
	line	268
;spi.c: 267: {
;spi.c: 268: while(PORTCbits.RC0 ==0)
	goto	l19242
	
l5003:	
	line	270
;spi.c: 269: {
;spi.c: 270: if(SSP2STATbits.BF)
	movlb 4	; select bank4
	btfss	(540)^0200h,0	;volatile
	goto	u4091
	goto	u4090
u4091:
	goto	l19242
u4090:
	line	272
	
l19224:	
;spi.c: 271: {
;spi.c: 272: SSP2STATbits.BF=0;
	bcf	(540)^0200h,0	;volatile
	line	273
	
l19226:	
;spi.c: 273: bf=1;
	movlb 0	; select bank0
	clrf	(SPIADCworker@bf)
	bsf	status,0
	rlf	(SPIADCworker@bf),f
	line	274
;spi.c: 274: if(fb==0)
	movf	(SPIADCworker@fb),f
	skipz
	goto	u4101
	goto	u4100
u4101:
	goto	l19234
u4100:
	line	276
	
l19228:	
;spi.c: 275: {
;spi.c: 276: if(SSP2BUF==1)fb=1;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	xorlw	01h&0ffh
	skipz
	goto	u4111
	goto	u4110
u4111:
	goto	l19232
u4110:
	
l19230:	
	movlb 0	; select bank0
	clrf	(SPIADCworker@fb)
	bsf	status,0
	rlf	(SPIADCworker@fb),f
	goto	l19232
	
l5006:	
	line	277
	
l19232:	
;spi.c: 277: SSP2BUF=0;
	movlb 4	; select bank4
	clrf	(537)^0200h	;volatile
	line	278
;spi.c: 278: }
	goto	l19242
	line	279
	
l5005:	
	
l19234:	
;spi.c: 279: else if(fb==1)
	movlb 0	; select bank0
	movf	(SPIADCworker@fb),w
	xorlw	01h&0ffh
	skipz
	goto	u4121
	goto	u4120
u4121:
	goto	l19242
u4120:
	line	281
	
l19236:	
;spi.c: 280: {
;spi.c: 281: chanel = SSP2BUF &0b00110000;
	movlb 4	; select bank4
	movf	(537)^0200h,w
	andlw	030h
	movwf	(??_SPIADCworker+0)+0
	movf	(??_SPIADCworker+0)+0,w
	movlb 0	; select bank0
	movwf	(SPIADCworker@chanel)
	line	282
	
l19238:	
;spi.c: 282: chanel = chanel>>4;
	movf	(SPIADCworker@chanel),w
	movwf	(??_SPIADCworker+0)+0
	movlw	04h
u4135:
	lsrf	(??_SPIADCworker+0)+0,f
	decfsz	wreg,f
	goto	u4135
	movf	0+(??_SPIADCworker+0)+0,w
	movwf	(??_SPIADCworker+1)+0
	movf	(??_SPIADCworker+1)+0,w
	movwf	(SPIADCworker@chanel)
	line	283
	
l19240:	
;spi.c: 283: SSP2BUF = getADC(chanel);
	movf	(SPIADCworker@chanel),w
	fcall	_getADC
	movf	(0+(?_getADC)),w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	goto	l19242
	line	284
	
l5008:	
	goto	l19242
	line	286
	
l5007:	
	goto	l19242
	
l5004:	
	goto	l19242
	line	287
	
l5002:	
	line	268
	
l19242:	
	movlb 0	; select bank0
	btfss	(14),0	;volatile
	goto	u4141
	goto	u4140
u4141:
	goto	l5003
u4140:
	goto	l19244
	
l5009:	
	line	288
	
l19244:	
;spi.c: 284: }
;spi.c: 286: }
;spi.c: 287: }
;spi.c: 288: if(bf)
	movf	(SPIADCworker@bf),w
	skipz
	goto	u4150
	goto	l19242
u4150:
	line	290
	
l19246:	
;spi.c: 289: {
;spi.c: 290: fb=0;
	clrf	(SPIADCworker@fb)
	line	291
;spi.c: 291: bf=0;
	clrf	(SPIADCworker@bf)
	goto	l19242
	line	292
	
l5010:	
	goto	l19242
	line	293
	
l5011:	
	line	266
	goto	l19242
	
l5012:	
	line	294
	
l5013:	
	return
	opt stack 0
GLOBAL	__end_of_SPIADCworker
	__end_of_SPIADCworker:
;; =============== function _SPIADCworker ends ============

	signat	_SPIADCworker,88
	global	_SPIDACworker
	global	_I2CDACworker
psect	text1302,local,class=CODE,delta=2
global __ptext1302
__ptext1302:

;; *************** function _I2CDACworker *****************
;; Defined at:
;;		line 164 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  dac             1    9[COMMON] unsigned char 
;;  command         1    8[COMMON] unsigned char 
;;  token           1    7[COMMON] unsigned char 
;;  fb              1    6[COMMON] unsigned char 
;;  temp            1    5[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         5       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         6       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_enableDAC
;;		_setDAC
;;		_I2CWrite
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1302
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
	line	164
	global	__size_of_I2CDACworker
	__size_of_I2CDACworker	equ	__end_of_I2CDACworker-_I2CDACworker
	
_I2CDACworker:	
	opt	stack 13
; Regs used in _I2CDACworker: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	
l18972:	
	clrf	(I2CDACworker@command)
	clrf	(I2CDACworker@fb)
	line	166
;i2c.c: 166: dac=0x00;
	clrf	(I2CDACworker@dac)
	line	167
	
l18974:	
;i2c.c: 167: enableDAC();
	fcall	_enableDAC
	line	170
	
l18976:	
;i2c.c: 170: SSP2ADD=0x5C;
	movlw	(05Ch)
	movlb 4	; select bank4
	movwf	(538)^0200h	;volatile
	goto	l18978
	line	172
;i2c.c: 172: while(1)
	
l3284:	
	line	175
	
l18978:	
;i2c.c: 173: {
;i2c.c: 175: if(SSP2IF)
	movlb 0	; select bank0
	btfss	(160/8),(160)&7
	goto	u3781
	goto	u3780
u3781:
	goto	l18978
u3780:
	line	177
	
l18980:	
;i2c.c: 176: {
;i2c.c: 177: token=SSP2STAT&0x25;
	movlb 4	; select bank4
	movf	(540)^0200h,w
	andlw	025h
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@token)
	line	179
	
l18982:	
;i2c.c: 179: if(SSP2STATbits.S)
	btfss	(540)^0200h,3	;volatile
	goto	u3791
	goto	u3790
u3791:
	goto	l3286
u3790:
	line	180
	
l18984:	
;i2c.c: 180: { RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	181
;i2c.c: 181: switch(token)
	goto	l19018
	line	183
;i2c.c: 182: {
;i2c.c: 183: case 0x01:
	
l3288:	
	line	184
	
l18986:	
;i2c.c: 184: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@temp)
	line	185
;i2c.c: 185: break;
	goto	l3301
	line	186
;i2c.c: 186: case 0x21:
	
l3290:	
	line	187
;i2c.c: 187: if(fb=0)
	clrf	(I2CDACworker@fb)
	goto	l18992
	line	189
	
l18988:	
;i2c.c: 188: {
;i2c.c: 189: command = SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@command)
	line	190
	
l18990:	
;i2c.c: 190: fb=1;
	clrf	(I2CDACworker@fb)
	bsf	status,0
	rlf	(I2CDACworker@fb),f
	line	191
;i2c.c: 191: }
	goto	l3301
	line	192
	
l3291:	
	line	194
	
l18992:	
;i2c.c: 192: else
;i2c.c: 193: {
;i2c.c: 194: if(command ==0)
	movf	(I2CDACworker@command),f
	skipz
	goto	u3801
	goto	u3800
u3801:
	goto	l18998
u3800:
	line	196
	
l18994:	
;i2c.c: 195: {
;i2c.c: 196: dac=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@dac)
	line	197
;i2c.c: 197: dac>>=1;
	clrc
	rrf	(I2CDACworker@dac),f

	line	198
	
l18996:	
;i2c.c: 198: setDAC(dac);
	movf	(I2CDACworker@dac),w
	fcall	_setDAC
	line	199
;i2c.c: 199: }
	goto	l3301
	line	200
	
l3293:	
	
l18998:	
;i2c.c: 200: else temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@temp)
	goto	l3301
	
l3294:	
	goto	l3301
	line	201
	
l3292:	
	line	202
;i2c.c: 201: }
;i2c.c: 202: break;
	goto	l3301
	line	203
;i2c.c: 203: case 0x05:
	
l3295:	
	line	204
	
l19000:	
;i2c.c: 204: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@temp)
	line	205
	
l19002:	
;i2c.c: 205: if(command==0)I2CWrite(dac<<1);
	movf	(I2CDACworker@command),f
	skipz
	goto	u3811
	goto	u3810
u3811:
	goto	l19006
u3810:
	
l19004:	
	movf	(I2CDACworker@dac),w
	addwf	wreg,w
	fcall	_I2CWrite
	goto	l3301
	line	206
	
l3296:	
	
l19006:	
;i2c.c: 206: else I2CWrite(0);
	movlw	(0)
	fcall	_I2CWrite
	goto	l3301
	
l3297:	
	line	207
;i2c.c: 207: break;
	goto	l3301
	line	208
;i2c.c: 208: case 0x24:
	
l3298:	
	line	209
	
l19008:	
;i2c.c: 209: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@temp)
	line	210
	
l19010:	
;i2c.c: 210: if(command==0)I2CWrite(dac<<1);
	movf	(I2CDACworker@command),f
	skipz
	goto	u3821
	goto	u3820
u3821:
	goto	l19014
u3820:
	
l19012:	
	movf	(I2CDACworker@dac),w
	addwf	wreg,w
	fcall	_I2CWrite
	goto	l3301
	line	211
	
l3299:	
	
l19014:	
;i2c.c: 211: else I2CWrite(0);
	movlw	(0)
	fcall	_I2CWrite
	goto	l3301
	
l3300:	
	line	212
;i2c.c: 212: break;
	goto	l3301
	line	213
	
l19016:	
;i2c.c: 213: }
	goto	l3301
	line	181
	
l3287:	
	
l19018:	
	movf	(I2CDACworker@token),w
	; Switch size 1, requested type "space"
; Number of cases is 4, Range of values is 1 to 36
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           13     7 (average)
; direct_byte           81     9 (fixed)
; jumptable            263     9 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	1^0	; case 1
	skipnz
	goto	l18986
	xorlw	5^1	; case 5
	skipnz
	goto	l19000
	xorlw	33^5	; case 33
	skipnz
	goto	l3290
	xorlw	36^33	; case 36
	skipnz
	goto	l19008
	goto	l3301
	opt asmopt_on

	line	213
	
l3289:	
	line	214
;i2c.c: 214: }
	goto	l3301
	line	215
	
l3286:	
;i2c.c: 215: else if(SSP2STATbits.P)
	btfss	(540)^0200h,4	;volatile
	goto	u3831
	goto	u3830
u3831:
	goto	l3301
u3830:
	line	217
	
l19020:	
;i2c.c: 216: {
;i2c.c: 217: fb=0;
	clrf	(I2CDACworker@fb)
	line	218
;i2c.c: 218: RC5=0;;
	movlb 0	; select bank0
	bcf	(117/8),(117)&7
	line	219
# 219 "C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
NOP ;#
psect	text1302
	goto	l3301
	line	220
	
l3302:	
	line	221
	
l3301:	
;i2c.c: 220: }
;i2c.c: 221: SSP2IF=0;
	movlb 0	; select bank0
	bcf	(160/8),(160)&7
	line	222
;i2c.c: 222: SSP2CON1bits.SSPEN=1;
	movlb 4	; select bank4
	bsf	(541)^0200h,5	;volatile
	line	223
;i2c.c: 223: SSP2CON1bits.CKP=1;
	bsf	(541)^0200h,4	;volatile
	goto	l18978
	line	224
	
l3285:	
	goto	l18978
	line	225
	
l3303:	
	line	172
	goto	l18978
	
l3304:	
	line	226
	
l3305:	
	return
	opt stack 0
GLOBAL	__end_of_I2CDACworker
	__end_of_I2CDACworker:
;; =============== function _I2CDACworker ends ============

	signat	_I2CDACworker,88
psect	text1303,local,class=CODE,delta=2
global __ptext1303
__ptext1303:

;; *************** function _SPIDACworker *****************
;; Defined at:
;;		line 224 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\spi.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  bf              1    6[COMMON] unsigned char 
;;  fb              1    5[COMMON] unsigned char 
;;  fInst           1    4[COMMON] unsigned char 
;;  instruction     1    0        unsigned char 
;;  token           1    0        unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_initSPI
;;		_enableDAC
;;		_setDAC
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1303
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\spi.c"
	line	224
	global	__size_of_SPIDACworker
	__size_of_SPIDACworker	equ	__end_of_SPIDACworker-_SPIDACworker
	
_SPIDACworker:	
	opt	stack 13
; Regs used in _SPIDACworker: [wreg+status,2+status,0+pclath+cstack]
	line	225
	
l19190:	
;spi.c: 225: unsigned char token, instruction, fInst=0,fb=0,bf=0;
	clrf	(SPIDACworker@fInst)
	clrf	(SPIDACworker@fb)
	clrf	(SPIDACworker@bf)
	line	226
	
l19192:	
;spi.c: 226: initSPI();
	fcall	_initSPI
	line	227
	
l19194:	
;spi.c: 227: SSP2BUF = 0xFD;
	movlw	(0FDh)
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	line	228
	
l19196:	
;spi.c: 228: enableDAC();
	fcall	_enableDAC
	goto	l19212
	line	230
;spi.c: 230: while (1)
	
l4986:	
	line	232
;spi.c: 231: {
;spi.c: 232: while(PORTCbits.RC0 ==0)
	goto	l19212
	
l4988:	
	line	234
;spi.c: 233: {
;spi.c: 234: if(SSP2STATbits.BF)
	movlb 4	; select bank4
	btfss	(540)^0200h,0	;volatile
	goto	u4041
	goto	u4040
u4041:
	goto	l19212
u4040:
	line	236
	
l19198:	
;spi.c: 235: {
;spi.c: 236: bf=1;
	clrf	(SPIDACworker@bf)
	bsf	status,0
	rlf	(SPIDACworker@bf),f
	line	237
	
l19200:	
;spi.c: 237: if(fb)
	movf	(SPIDACworker@fb),w
	skipz
	goto	u4050
	goto	l19204
u4050:
	line	239
	
l19202:	
;spi.c: 238: {
;spi.c: 239: setDAC(SSP2BUF);
	movf	(537)^0200h,w	;volatile
	fcall	_setDAC
	line	240
;spi.c: 240: }
	goto	l19210
	line	241
	
l4990:	
	line	243
	
l19204:	
;spi.c: 241: else
;spi.c: 242: {
;spi.c: 243: fb=1;
	clrf	(SPIDACworker@fb)
	bsf	status,0
	rlf	(SPIDACworker@fb),f
	line	244
	
l19206:	
;spi.c: 244: if(SSP2BUF&0b00010000)DACOE =1;
	movlb 4	; select bank4
	btfss	(537)^0200h,(4)&7
	goto	u4061
	goto	u4060
u4061:
	goto	l4992
u4060:
	
l19208:	
	movlb 2	; select bank2
	bsf	(2245/8)^0100h,(2245)&7
	goto	l19210
	line	245
	
l4992:	
;spi.c: 245: else DACOE =0;
	movlb 2	; select bank2
	bcf	(2245/8)^0100h,(2245)&7
	goto	l19210
	
l4993:	
	goto	l19210
	line	246
	
l4991:	
	line	247
	
l19210:	
;spi.c: 246: }
;spi.c: 247: SSP2BUF = DACCON1&0x1F;
	movlb 2	; select bank2
	movf	(281)^0100h,w
	andlw	01Fh
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	goto	l19212
	line	248
	
l4989:	
	goto	l19212
	line	249
	
l4987:	
	line	232
	
l19212:	
	movlb 0	; select bank0
	btfss	(14),0	;volatile
	goto	u4071
	goto	u4070
u4071:
	goto	l4988
u4070:
	goto	l19214
	
l4994:	
	line	250
	
l19214:	
;spi.c: 248: }
;spi.c: 249: }
;spi.c: 250: if(bf)
	movf	(SPIDACworker@bf),w
	skipz
	goto	u4080
	goto	l19212
u4080:
	line	252
	
l19216:	
;spi.c: 251: {
;spi.c: 252: fb=0;
	clrf	(SPIDACworker@fb)
	line	253
;spi.c: 253: bf=0;
	clrf	(SPIDACworker@bf)
	goto	l19212
	line	254
	
l4995:	
	goto	l19212
	line	255
	
l4996:	
	line	230
	goto	l19212
	
l4997:	
	line	257
	
l4998:	
	return
	opt stack 0
GLOBAL	__end_of_SPIDACworker
	__end_of_SPIDACworker:
;; =============== function _SPIDACworker ends ============

	signat	_SPIDACworker,88
	global	_SPIEEworker
	global	_I2CEEworker
psect	text1304,local,class=CODE,delta=2
global __ptext1304
__ptext1304:

;; *************** function _I2CEEworker *****************
;; Defined at:
;;		line 29 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  addr            1    8[BANK0 ] unsigned char 
;;  i               1    7[BANK0 ] unsigned char 
;;  w               1    6[BANK0 ] unsigned char 
;;  addressed       1    5[BANK0 ] unsigned char 
;;  token           1    4[BANK0 ] unsigned char 
;;  temp            1    3[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr1l, fsr1h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       6       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       3       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       9       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        9 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_EEPROMwrite
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1304
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
	line	29
	global	__size_of_I2CEEworker
	__size_of_I2CEEworker	equ	__end_of_I2CEEworker-_I2CEEworker
	
_I2CEEworker:	
	opt	stack 13
; Regs used in _I2CEEworker: [wreg-status,0+pclath+cstack]
	line	30
	
l18858:	
;i2c.c: 30: unsigned char token,i, addr=0, temp=0, addressed=0,w=0;
	movlb 0	; select bank0
	clrf	(I2CEEworker@addr)
	clrf	(I2CEEworker@temp)
	clrf	(I2CEEworker@addressed)
	clrf	(I2CEEworker@w)
	line	33
	
l18860:	
;i2c.c: 33: SSP2ADD=0xA0;
	movlw	(0A0h)
	movlb 4	; select bank4
	movwf	(538)^0200h	;volatile
	line	34
	
l18862:	
;i2c.c: 34: SSP2CON1bits.SSPEN=1;
	bsf	(541)^0200h,5	;volatile
	goto	l18864
	line	35
;i2c.c: 35: while(1)
	
l3243:	
	line	38
	
l18864:	
;i2c.c: 36: {
;i2c.c: 38: if(SSP2IF)
	movlb 0	; select bank0
	btfss	(160/8),(160)&7
	goto	u3661
	goto	u3660
u3661:
	goto	l18864
u3660:
	line	40
	
l18866:	
;i2c.c: 39: {
;i2c.c: 40: SSP2IF=0;
	bcf	(160/8),(160)&7
	line	41
	
l18868:	
;i2c.c: 41: token=SSP2STAT&0x25;
	movlb 4	; select bank4
	movf	(540)^0200h,w
	andlw	025h
	movlb 0	; select bank0
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movwf	(I2CEEworker@token)
	line	42
	
l18870:	
;i2c.c: 42: if(SSP2STATbits.S)
	movlb 4	; select bank4
	btfss	(540)^0200h,3	;volatile
	goto	u3671
	goto	u3670
u3671:
	goto	l3245
u3670:
	line	44
	
l18872:	
;i2c.c: 43: {
;i2c.c: 44: RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	45
;i2c.c: 45: switch(token)
	goto	l18904
	line	47
;i2c.c: 46: {
;i2c.c: 47: case 0x01:
	
l3247:	
	line	48
	
l18874:	
;i2c.c: 48: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movwf	(I2CEEworker@temp)
	line	49
;i2c.c: 49: break;
	goto	l3255
	line	50
;i2c.c: 50: case 0x21:
	
l3249:	
	line	51
	
l18876:	
;i2c.c: 51: if(!addressed)
	movf	(I2CEEworker@addressed),f
	skipz
	goto	u3681
	goto	u3680
u3681:
	goto	l18882
u3680:
	line	53
	
l18878:	
;i2c.c: 52: {
;i2c.c: 53: addr=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movwf	(I2CEEworker@addr)
	line	54
	
l18880:	
;i2c.c: 54: addressed=1;
	clrf	(I2CEEworker@addressed)
	bsf	status,0
	rlf	(I2CEEworker@addressed),f
	line	55
;i2c.c: 55: }
	goto	l3255
	line	56
	
l3250:	
	line	58
	
l18882:	
;i2c.c: 56: else
;i2c.c: 57: {
;i2c.c: 58: eeBuf[addr++]=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CEEworker+0)+0
	movf	(I2CEEworker@addr),w
	addlw	low 8944
	movwf	(??_I2CEEworker+1)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_I2CEEworker+1)+0)+1
	movf	0+(??_I2CEEworker+1)+0,w
	movwf	fsr1l
	movf	1+(??_I2CEEworker+1)+0,w
	movwf	fsr1h

	movf	(??_I2CEEworker+0)+0,w
	movwf	indf1
	
l18884:	
	movlw	(01h)
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	addwf	(I2CEEworker@addr),f
	line	59
	
l18886:	
;i2c.c: 59: w++;
	movlw	(01h)
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	addwf	(I2CEEworker@w),f
	goto	l3255
	line	60
	
l3251:	
	line	61
;i2c.c: 60: }
;i2c.c: 61: break;
	goto	l3255
	line	62
;i2c.c: 62: case 0x05:
	
l3252:	
	line	63
	
l18888:	
;i2c.c: 63: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movwf	(I2CEEworker@temp)
	line	64
	
l18890:	
;i2c.c: 64: SSP2BUF = eeBuf[addr++];
	movf	(I2CEEworker@addr),w
	addlw	low 8944
	movwf	(??_I2CEEworker+0)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_I2CEEworker+0)+0)+1
	movf	0+(??_I2CEEworker+0)+0,w
	movwf	fsr1l
	movf	1+(??_I2CEEworker+0)+0,w
	movwf	fsr1h

	movf	indf1,w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	
l18892:	
	movlw	(01h)
	movlb 0	; select bank0
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	addwf	(I2CEEworker@addr),f
	line	65
;i2c.c: 65: break;
	goto	l3255
	line	66
;i2c.c: 66: case 0x24:
	
l3253:	
	line	67
	
l18894:	
;i2c.c: 67: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movwf	(I2CEEworker@temp)
	line	69
	
l18896:	
;i2c.c: 69: if(SSP2CON2bits.ACKSTAT==0)SSP2BUF=eeBuf[addr++];
	movlb 4	; select bank4
	btfsc	(542)^0200h,6	;volatile
	goto	u3691
	goto	u3690
u3691:
	goto	l3255
u3690:
	
l18898:	
	movlb 0	; select bank0
	movf	(I2CEEworker@addr),w
	addlw	low 8944
	movwf	(??_I2CEEworker+0)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_I2CEEworker+0)+0)+1
	movf	0+(??_I2CEEworker+0)+0,w
	movwf	fsr1l
	movf	1+(??_I2CEEworker+0)+0,w
	movwf	fsr1h

	movf	indf1,w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	
l18900:	
	movlw	(01h)
	movlb 0	; select bank0
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	addwf	(I2CEEworker@addr),f
	goto	l3255
	
l3254:	
	line	70
;i2c.c: 70: break;
	goto	l3255
	line	71
	
l18902:	
;i2c.c: 71: }
	goto	l3255
	line	45
	
l3246:	
	
l18904:	
	movf	(I2CEEworker@token),w
	; Switch size 1, requested type "space"
; Number of cases is 4, Range of values is 1 to 36
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           13     7 (average)
; direct_byte           81     9 (fixed)
; jumptable            263     9 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	1^0	; case 1
	skipnz
	goto	l18874
	xorlw	5^1	; case 5
	skipnz
	goto	l18888
	xorlw	33^5	; case 33
	skipnz
	goto	l18876
	xorlw	36^33	; case 36
	skipnz
	goto	l18894
	goto	l3255
	opt asmopt_on

	line	71
	
l3248:	
	line	72
;i2c.c: 72: }
	goto	l3255
	line	73
	
l3245:	
;i2c.c: 73: else if(SSP2STATbits.P)
	btfss	(540)^0200h,4	;volatile
	goto	u3701
	goto	u3700
u3701:
	goto	l3255
u3700:
	line	75
	
l18906:	
;i2c.c: 74: {
;i2c.c: 75: RC5=0;;
	movlb 0	; select bank0
	bcf	(117/8),(117)&7
	line	76
;i2c.c: 76: addressed=0;
	clrf	(I2CEEworker@addressed)
	line	77
	
l18908:	
;i2c.c: 77: if(w>0)
	movf	(I2CEEworker@w),w
	skipz
	goto	u3710
	goto	l3257
u3710:
	line	79
	
l18910:	
;i2c.c: 78: {
;i2c.c: 79: for(i=addr-w;i<addr-1;i++)
	decf	(I2CEEworker@w),w
	xorlw	0ffh
	addwf	(I2CEEworker@addr),w
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movwf	(I2CEEworker@i)
	goto	l18916
	line	80
	
l3259:	
	line	81
	
l18912:	
;i2c.c: 80: {
;i2c.c: 81: EEPROMwrite(i,eeBuf[i]);
	movlb 0	; select bank0
	movf	(I2CEEworker@i),w
	addlw	low 8944
	movwf	(??_I2CEEworker+0)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_I2CEEworker+0)+0)+1
	movf	0+(??_I2CEEworker+0)+0,w
	movwf	fsr1l
	movf	1+(??_I2CEEworker+0)+0,w
	movwf	fsr1h

	movf	indf1,w
	movwf	(??_I2CEEworker+2)+0
	movf	(??_I2CEEworker+2)+0,w
	movwf	(?_EEPROMwrite)
	movf	(I2CEEworker@i),w
	fcall	_EEPROMwrite
	line	79
	
l18914:	
	movlw	(01h)
	movlb 0	; select bank0
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	addwf	(I2CEEworker@i),f
	goto	l18916
	
l3258:	
	
l18916:	
	movf	(I2CEEworker@addr),w
	addlw	low(-1)
	movwf	(??_I2CEEworker+0)+0
	movlw	high(-1)
	skipnc
	movlw	(high(-1)+1)&0ffh
	movwf	((??_I2CEEworker+0)+0)+1
	movf	1+(??_I2CEEworker+0)+0,w
	xorlw	80h
	sublw	080h
	skipz
	goto	u3725
	movf	0+(??_I2CEEworker+0)+0,w
	subwf	(I2CEEworker@i),w
u3725:

	skipc
	goto	u3721
	goto	u3720
u3721:
	goto	l18912
u3720:
	goto	l3257
	
l3260:	
	line	83
	
l3257:	
	line	84
;i2c.c: 82: }
;i2c.c: 83: }
;i2c.c: 84: w=0;
	movlb 0	; select bank0
	clrf	(I2CEEworker@w)
	line	85
# 85 "C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
NOP ;#
psect	text1304
	goto	l3255
	line	86
	
l3256:	
	line	87
	
l3255:	
;i2c.c: 86: }
;i2c.c: 87: SSP2CON1bits.CKP=1;
	movlb 4	; select bank4
	bsf	(541)^0200h,4	;volatile
	goto	l18864
	line	88
	
l3244:	
	goto	l18864
	line	89
	
l3261:	
	line	35
	goto	l18864
	
l3262:	
	line	90
	
l3263:	
	return
	opt stack 0
GLOBAL	__end_of_I2CEEworker
	__end_of_I2CEEworker:
;; =============== function _I2CEEworker ends ============

	signat	_I2CEEworker,88
psect	text1305,local,class=CODE,delta=2
global __ptext1305
__ptext1305:

;; *************** function _SPIEEworker *****************
;; Defined at:
;;		line 38 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\spi.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  addr            1   16[BANK0 ] unsigned char 
;;  STATUS          1   15[BANK0 ] unsigned char 
;;  fInst           1   14[BANK0 ] unsigned char 
;;  i               1   13[BANK0 ] unsigned char 
;;  w               1   12[BANK0 ] unsigned char 
;;  addressed       1   11[BANK0 ] unsigned char 
;;  token           1   10[BANK0 ] unsigned char 
;;  WREN            1    9[BANK0 ] unsigned char 
;;  bf              1    8[BANK0 ] unsigned char 
;;  fb              1    7[BANK0 ] unsigned char 
;;  instruction     1    6[BANK0 ] unsigned char 
;;  WIP             1    5[BANK0 ] unsigned char 
;;  pageIndex       1    4[BANK0 ] unsigned char 
;;  fb2             1    3[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr1l, fsr1h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0      14       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       3       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      17       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       17 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_initSPI
;;		_EEPROMwrite
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1305
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\spi.c"
	line	38
	global	__size_of_SPIEEworker
	__size_of_SPIEEworker	equ	__end_of_SPIEEworker-_SPIEEworker
	
_SPIEEworker:	
	opt	stack 13
; Regs used in _SPIEEworker: [wreg-status,0+pclath+cstack]
	line	39
	
l19066:	
;spi.c: 39: unsigned char token, instruction, fInst=0,addr=0,addressed =0,STATUS=0,fb=0,fb2=0,bf=0;
	movlb 0	; select bank0
	clrf	(SPIEEworker@fInst)
	clrf	(SPIEEworker@addr)
	clrf	(SPIEEworker@addressed)
	clrf	(SPIEEworker@STATUS)
	clrf	(SPIEEworker@fb)
	clrf	(SPIEEworker@fb2)
	clrf	(SPIEEworker@bf)
	line	40
;spi.c: 40: unsigned char i,pageIndex=0,WREN=0,WIP=0,w=0;
	clrf	(SPIEEworker@pageIndex)
	clrf	(SPIEEworker@WREN)
	clrf	(SPIEEworker@WIP)
	clrf	(SPIEEworker@w)
	line	41
	
l19068:	
;spi.c: 41: initSPI();
	fcall	_initSPI
	line	42
	
l19070:	
;spi.c: 42: SSP2BUF = 0xFD;
	movlw	(0FDh)
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	goto	l4922
	line	43
;spi.c: 43: while (1)
	
l4921:	
	line	45
;spi.c: 44: {
;spi.c: 45: while(PORTCbits.RC0 ==0)
	goto	l4922
	
l4923:	
	line	47
;spi.c: 46: {
;spi.c: 47: if(SSP2STATbits.BF)
	movlb 4	; select bank4
	btfss	(540)^0200h,0	;volatile
	goto	u3861
	goto	u3860
u3861:
	goto	l4922
u3860:
	line	49
	
l19072:	
;spi.c: 48: {
;spi.c: 49: bf=1;
	movlb 0	; select bank0
	clrf	(SPIEEworker@bf)
	bsf	status,0
	rlf	(SPIEEworker@bf),f
	line	50
;spi.c: 50: if(fb==0)
	movf	(SPIEEworker@fb),f
	skipz
	goto	u3871
	goto	u3870
u3871:
	goto	l19078
u3870:
	line	52
	
l19074:	
;spi.c: 51: {
;spi.c: 52: token = SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	movwf	(SPIEEworker@token)
	line	53
	
l19076:	
;spi.c: 53: instruction = token & 0xF7;
	movf	(SPIEEworker@token),w
	andlw	0F7h
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	movwf	(SPIEEworker@instruction)
	goto	l19078
	line	54
	
l4925:	
	line	55
	
l19078:	
;spi.c: 54: }
;spi.c: 55: fb=1;
	clrf	(SPIEEworker@fb)
	bsf	status,0
	rlf	(SPIEEworker@fb),f
	line	56
;spi.c: 56: switch(instruction)
	goto	l19168
	line	58
;spi.c: 57: {
;spi.c: 58: case 0x03:
	
l4927:	
	line	59
	
l19080:	
;spi.c: 59: if(fInst)
	movf	(SPIEEworker@fInst),w
	skipz
	goto	u3880
	goto	l19096
u3880:
	line	61
	
l19082:	
;spi.c: 60: {
;spi.c: 61: if(addressed==0)
	movf	(SPIEEworker@addressed),f
	skipz
	goto	u3891
	goto	u3890
u3891:
	goto	l19092
u3890:
	line	63
	
l19084:	
;spi.c: 62: {
;spi.c: 63: addr = SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	movwf	(SPIEEworker@addr)
	line	64
	
l19086:	
;spi.c: 64: addressed =1;
	clrf	(SPIEEworker@addressed)
	bsf	status,0
	rlf	(SPIEEworker@addressed),f
	line	65
	
l19088:	
;spi.c: 65: SSP2BUF = eeBuf[addr++];
	movf	(SPIEEworker@addr),w
	addlw	low 8944
	movwf	(??_SPIEEworker+0)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_SPIEEworker+0)+0)+1
	movf	0+(??_SPIEEworker+0)+0,w
	movwf	fsr1l
	movf	1+(??_SPIEEworker+0)+0,w
	movwf	fsr1h

	movf	indf1,w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	
l19090:	
	movlw	(01h)
	movlb 0	; select bank0
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	addwf	(SPIEEworker@addr),f
	line	66
;spi.c: 66: }
	goto	l4922
	line	67
	
l4929:	
	line	69
	
l19092:	
;spi.c: 67: else
;spi.c: 68: {
;spi.c: 69: SSP2BUF = eeBuf[addr++];
	movf	(SPIEEworker@addr),w
	addlw	low 8944
	movwf	(??_SPIEEworker+0)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_SPIEEworker+0)+0)+1
	movf	0+(??_SPIEEworker+0)+0,w
	movwf	fsr1l
	movf	1+(??_SPIEEworker+0)+0,w
	movwf	fsr1h

	movf	indf1,w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	
l19094:	
	movlw	(01h)
	movlb 0	; select bank0
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	addwf	(SPIEEworker@addr),f
	goto	l4922
	line	70
	
l4930:	
	line	71
;spi.c: 70: }
;spi.c: 71: }
	goto	l4922
	line	72
	
l4928:	
	line	74
	
l19096:	
;spi.c: 72: else
;spi.c: 73: {
;spi.c: 74: fInst=1;
	clrf	(SPIEEworker@fInst)
	bsf	status,0
	rlf	(SPIEEworker@fInst),f
	line	75
	
l19098:	
;spi.c: 75: SSP2BUF = STATUS;
	movf	(SPIEEworker@STATUS),w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	goto	l4922
	line	76
	
l4931:	
	line	77
;spi.c: 76: }
;spi.c: 77: break;
	goto	l4922
	line	78
;spi.c: 78: case 0x02:
	
l4933:	
	line	79
	
l19100:	
;spi.c: 79: if(WREN)
	movlb 0	; select bank0
	movf	(SPIEEworker@WREN),w
	skipz
	goto	u3900
	goto	l19148
u3900:
	line	81
	
l19102:	
;spi.c: 80: {
;spi.c: 81: if(fInst)
	movf	(SPIEEworker@fInst),w
	skipz
	goto	u3910
	goto	l19146
u3910:
	line	83
	
l19104:	
;spi.c: 82: {
;spi.c: 83: if(addressed)
	movf	(SPIEEworker@addressed),w
	skipz
	goto	u3920
	goto	l19142
u3920:
	line	85
	
l19106:	
;spi.c: 84: {
;spi.c: 85: if(STATUS > 11);
	movlw	(0Ch)
	subwf	(SPIEEworker@STATUS),w
	skipc
	goto	u3931
	goto	u3930
u3931:
	goto	l19110
u3930:
	goto	l19148
	
l19108:	
	goto	l19148
	line	86
	
l4937:	
	
l19110:	
;spi.c: 86: else if(STATUS >7)
	movlw	(08h)
	subwf	(SPIEEworker@STATUS),w
	skipc
	goto	u3941
	goto	u3940
u3941:
	goto	l19122
u3940:
	line	88
	
l19112:	
;spi.c: 87: {
;spi.c: 88: if(addr<0x80)
	movlw	(080h)
	subwf	(SPIEEworker@addr),w
	skipnc
	goto	u3951
	goto	u3950
u3951:
	goto	l19148
u3950:
	line	90
	
l19114:	
;spi.c: 89: {
;spi.c: 90: eeBuf[addr++]=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_SPIEEworker+0)+0
	movf	(SPIEEworker@addr),w
	addlw	low 8944
	movwf	(??_SPIEEworker+1)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_SPIEEworker+1)+0)+1
	movf	0+(??_SPIEEworker+1)+0,w
	movwf	fsr1l
	movf	1+(??_SPIEEworker+1)+0,w
	movwf	fsr1h

	movf	(??_SPIEEworker+0)+0,w
	movwf	indf1
	
l19116:	
	movlw	(01h)
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	addwf	(SPIEEworker@addr),f
	line	91
	
l19118:	
;spi.c: 91: STATUS|=1;
	bsf	(SPIEEworker@STATUS)+(0/8),(0)&7
	line	92
	
l19120:	
;spi.c: 92: w++;
	movlw	(01h)
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	addwf	(SPIEEworker@w),f
	goto	l19148
	line	93
	
l4940:	
	line	94
;spi.c: 93: }
;spi.c: 94: }
	goto	l19148
	line	95
	
l4939:	
	
l19122:	
;spi.c: 95: else if(STATUS > 3)
	movlw	(04h)
	subwf	(SPIEEworker@STATUS),w
	skipc
	goto	u3961
	goto	u3960
u3961:
	goto	l19134
u3960:
	line	97
	
l19124:	
;spi.c: 96: {
;spi.c: 97: if(addr<0xC0)
	movlw	(0C0h)
	subwf	(SPIEEworker@addr),w
	skipnc
	goto	u3971
	goto	u3970
u3971:
	goto	l19148
u3970:
	line	99
	
l19126:	
;spi.c: 98: {
;spi.c: 99: eeBuf[addr++]=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_SPIEEworker+0)+0
	movf	(SPIEEworker@addr),w
	addlw	low 8944
	movwf	(??_SPIEEworker+1)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_SPIEEworker+1)+0)+1
	movf	0+(??_SPIEEworker+1)+0,w
	movwf	fsr1l
	movf	1+(??_SPIEEworker+1)+0,w
	movwf	fsr1h

	movf	(??_SPIEEworker+0)+0,w
	movwf	indf1
	
l19128:	
	movlw	(01h)
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	addwf	(SPIEEworker@addr),f
	line	100
	
l19130:	
;spi.c: 100: STATUS|=1;
	bsf	(SPIEEworker@STATUS)+(0/8),(0)&7
	line	101
	
l19132:	
;spi.c: 101: w++;
	movlw	(01h)
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	addwf	(SPIEEworker@w),f
	goto	l19148
	line	102
	
l4943:	
	line	103
;spi.c: 102: }
;spi.c: 103: }
	goto	l19148
	line	104
	
l4942:	
	line	106
	
l19134:	
;spi.c: 104: else
;spi.c: 105: {
;spi.c: 106: eeBuf[addr++]=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_SPIEEworker+0)+0
	movf	(SPIEEworker@addr),w
	addlw	low 8944
	movwf	(??_SPIEEworker+1)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_SPIEEworker+1)+0)+1
	movf	0+(??_SPIEEworker+1)+0,w
	movwf	fsr1l
	movf	1+(??_SPIEEworker+1)+0,w
	movwf	fsr1h

	movf	(??_SPIEEworker+0)+0,w
	movwf	indf1
	
l19136:	
	movlw	(01h)
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	addwf	(SPIEEworker@addr),f
	line	107
	
l19138:	
;spi.c: 107: w++;
	movlw	(01h)
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	addwf	(SPIEEworker@w),f
	line	108
	
l19140:	
;spi.c: 108: STATUS|=1;
	bsf	(SPIEEworker@STATUS)+(0/8),(0)&7
	goto	l19148
	line	109
	
l4944:	
	goto	l19148
	
l4941:	
	goto	l19148
	
l4938:	
	line	110
;spi.c: 109: }
;spi.c: 110: }
	goto	l19148
	line	111
	
l4936:	
	line	113
	
l19142:	
;spi.c: 111: else
;spi.c: 112: {
;spi.c: 113: addr = SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	movwf	(SPIEEworker@addr)
	line	114
	
l19144:	
;spi.c: 114: addressed =1;
	clrf	(SPIEEworker@addressed)
	bsf	status,0
	rlf	(SPIEEworker@addressed),f
	goto	l19148
	line	115
	
l4945:	
	line	116
;spi.c: 115: }
;spi.c: 116: }
	goto	l19148
	line	117
	
l4935:	
	line	119
	
l19146:	
;spi.c: 117: else
;spi.c: 118: {
;spi.c: 119: fInst=1;
	clrf	(SPIEEworker@fInst)
	bsf	status,0
	rlf	(SPIEEworker@fInst),f
	goto	l19148
	line	120
	
l4946:	
	goto	l19148
	line	121
	
l4934:	
	line	122
	
l19148:	
;spi.c: 120: }
;spi.c: 121: }
;spi.c: 122: SSP2BUF = STATUS;
	movf	(SPIEEworker@STATUS),w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	line	123
;spi.c: 123: break;
	goto	l4922
	line	124
;spi.c: 124: case 0x04:
	
l4947:	
	line	125
;spi.c: 125: WREN=0;
	clrf	(SPIEEworker@WREN)
	line	126
	
l19150:	
;spi.c: 126: STATUS&=~(1<<1);
	movlw	(0FDh)
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	andwf	(SPIEEworker@STATUS),f
	line	127
;spi.c: 127: break;
	goto	l4922
	line	128
;spi.c: 128: case 0x06:
	
l4948:	
	line	129
	
l19152:	
;spi.c: 129: WREN =1;
	clrf	(SPIEEworker@WREN)
	bsf	status,0
	rlf	(SPIEEworker@WREN),f
	line	130
	
l19154:	
;spi.c: 130: STATUS|=1<<1;
	bsf	(SPIEEworker@STATUS)+(1/8),(1)&7
	line	131
	
l19156:	
;spi.c: 131: SSP2BUF = STATUS;
	movf	(SPIEEworker@STATUS),w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	line	132
;spi.c: 132: break;
	goto	l4922
	line	133
;spi.c: 133: case 0x05:
	
l4949:	
	line	134
	
l19158:	
;spi.c: 134: SSP2BUF = STATUS;
	movlb 0	; select bank0
	movf	(SPIEEworker@STATUS),w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	line	135
;spi.c: 135: break;
	goto	l4922
	line	136
;spi.c: 136: case 0x01:
	
l4950:	
	line	137
	
l19160:	
;spi.c: 137: if(fInst)STATUS = SSP2BUF;
	movlb 0	; select bank0
	movf	(SPIEEworker@fInst),w
	skipz
	goto	u3980
	goto	l19164
u3980:
	
l19162:	
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	movwf	(SPIEEworker@STATUS)
	goto	l19164
	
l4951:	
	line	138
	
l19164:	
;spi.c: 138: fInst=1;
	clrf	(SPIEEworker@fInst)
	bsf	status,0
	rlf	(SPIEEworker@fInst),f
	line	139
;spi.c: 139: break;
	goto	l4922
	line	140
	
l19166:	
;spi.c: 140: }
	goto	l4922
	line	56
	
l4926:	
	
l19168:	
	movf	(SPIEEworker@instruction),w
	; Switch size 1, requested type "space"
; Number of cases is 6, Range of values is 1 to 6
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           19    10 (average)
; direct_byte           21     9 (fixed)
; jumptable            263     9 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	1^0	; case 1
	skipnz
	goto	l19160
	xorlw	2^1	; case 2
	skipnz
	goto	l19100
	xorlw	3^2	; case 3
	skipnz
	goto	l19080
	xorlw	4^3	; case 4
	skipnz
	goto	l4947
	xorlw	5^4	; case 5
	skipnz
	goto	l19158
	xorlw	6^5	; case 6
	skipnz
	goto	l19152
	goto	l4922
	opt asmopt_on

	line	140
	
l4932:	
	goto	l4922
	line	141
	
l4924:	
	line	142
	
l4922:	
	line	45
	movlb 0	; select bank0
	btfss	(14),0	;volatile
	goto	u3991
	goto	u3990
u3991:
	goto	l4923
u3990:
	goto	l19170
	
l4952:	
	line	143
	
l19170:	
;spi.c: 141: }
;spi.c: 142: }
;spi.c: 143: if(bf)
	movf	(SPIEEworker@bf),w
	skipz
	goto	u4000
	goto	l4922
u4000:
	line	145
	
l19172:	
;spi.c: 144: {
;spi.c: 145: addressed=0;
	clrf	(SPIEEworker@addressed)
	line	146
	
l19174:	
;spi.c: 146: if (token == 0x02)
	movf	(SPIEEworker@token),w
	xorlw	02h&0ffh
	skipz
	goto	u4011
	goto	u4010
u4011:
	goto	l19180
u4010:
	line	148
	
l19176:	
;spi.c: 147: {
;spi.c: 148: WREN =0;
	clrf	(SPIEEworker@WREN)
	line	149
	
l19178:	
;spi.c: 149: STATUS&=0b11111100;
	movlw	(0FCh)
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	andwf	(SPIEEworker@STATUS),f
	goto	l19180
	line	150
	
l4954:	
	line	151
	
l19180:	
;spi.c: 150: }
;spi.c: 151: if(w>0)
	movf	(SPIEEworker@w),w
	skipz
	goto	u4020
	goto	l4955
u4020:
	line	153
	
l19182:	
;spi.c: 152: {
;spi.c: 153: for(i=addr-w;i<addr;i++)EEPROMwrite(i,eeBuf[i]);
	decf	(SPIEEworker@w),w
	xorlw	0ffh
	addwf	(SPIEEworker@addr),w
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	movwf	(SPIEEworker@i)
	goto	l19188
	
l4957:	
	
l19184:	
	movf	(SPIEEworker@i),w
	addlw	low 8944
	movwf	(??_SPIEEworker+0)+0
	movlw	high 8944
	skipnc
	movlw	high (8944)+1
	movwf	((??_SPIEEworker+0)+0)+1
	movf	0+(??_SPIEEworker+0)+0,w
	movwf	fsr1l
	movf	1+(??_SPIEEworker+0)+0,w
	movwf	fsr1h

	movf	indf1,w
	movwf	(??_SPIEEworker+2)+0
	movf	(??_SPIEEworker+2)+0,w
	movwf	(?_EEPROMwrite)
	movf	(SPIEEworker@i),w
	fcall	_EEPROMwrite
	
l19186:	
	movlw	(01h)
	movlb 0	; select bank0
	movwf	(??_SPIEEworker+0)+0
	movf	(??_SPIEEworker+0)+0,w
	addwf	(SPIEEworker@i),f
	goto	l19188
	
l4956:	
	
l19188:	
	movf	(SPIEEworker@addr),w
	subwf	(SPIEEworker@i),w
	skipc
	goto	u4031
	goto	u4030
u4031:
	goto	l19184
u4030:
	goto	l4955
	
l4958:	
	line	154
	
l4955:	
	line	155
;spi.c: 154: }
;spi.c: 155: w=0;
	clrf	(SPIEEworker@w)
	line	156
;spi.c: 156: fb=0;
	clrf	(SPIEEworker@fb)
	line	157
;spi.c: 157: fInst=0;
	clrf	(SPIEEworker@fInst)
	line	158
;spi.c: 158: bf=0;
	clrf	(SPIEEworker@bf)
	goto	l4922
	line	159
	
l4953:	
	goto	l4922
	line	160
	
l4959:	
	line	43
	goto	l4922
	
l4960:	
	line	161
	
l4961:	
	return
	opt stack 0
GLOBAL	__end_of_SPIEEworker
	__end_of_SPIEEworker:
;; =============== function _SPIEEworker ends ============

	signat	_SPIEEworker,88
	global	_SPIPWMworker
	global	_I2CPWMworker
psect	text1306,local,class=CODE,delta=2
global __ptext1306
__ptext1306:

;; *************** function _I2CPWMworker *****************
;; Defined at:
;;		line 231 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  addr            1   17[BANK0 ] unsigned char 
;;  addressed       1   16[BANK0 ] unsigned char 
;;  fP              1   15[BANK0 ] unsigned char 
;;  fD              1   14[BANK0 ] unsigned char 
;;  tempD           1   13[BANK0 ] unsigned char 
;;  tempP           1   12[BANK0 ] unsigned char 
;;  token           1   11[BANK0 ] unsigned char 
;;  temp            1   10[BANK0 ] unsigned char 
;;  rFreq           1    0        unsigned char 
;;  rDuty           1    0        unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       8       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       8       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        9 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_enablePWM
;;		_setPeriod
;;		_setDuty
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1306
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
	line	231
	global	__size_of_I2CPWMworker
	__size_of_I2CPWMworker	equ	__end_of_I2CPWMworker-_I2CPWMworker
	
_I2CPWMworker:	
	opt	stack 12
; Regs used in _I2CPWMworker: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	232
	
l19784:	
;i2c.c: 232: unsigned char token, tempP,tempD,temp, rDuty,rFreq,fD=0,fP=0,addr=0,addressed=0;
	movlb 0	; select bank0
	clrf	(I2CPWMworker@fD)
	clrf	(I2CPWMworker@fP)
	clrf	(I2CPWMworker@addr)
	clrf	(I2CPWMworker@addressed)
	line	233
	
l19786:	
;i2c.c: 233: enablePWM();
	fcall	_enablePWM
	line	234
	
l19788:	
;i2c.c: 234: SSP2ADD=0x30;
	movlw	(030h)
	movlb 4	; select bank4
	movwf	(538)^0200h	;volatile
	line	235
	
l19790:	
;i2c.c: 235: SSP2CON1bits.SSPEN=1;
	bsf	(541)^0200h,5	;volatile
	goto	l19792
	line	236
;i2c.c: 236: while(1)
	
l3308:	
	line	239
	
l19792:	
;i2c.c: 237: {
;i2c.c: 239: if(SSP2IF)
	movlb 0	; select bank0
	btfss	(160/8),(160)&7
	goto	u4811
	goto	u4810
u4811:
	goto	l19792
u4810:
	line	241
	
l19794:	
;i2c.c: 240: {
;i2c.c: 241: SSP2IF=0;
	bcf	(160/8),(160)&7
	line	242
	
l19796:	
;i2c.c: 242: token=SSP2STAT&0x25;
	movlb 4	; select bank4
	movf	(540)^0200h,w
	andlw	025h
	movwf	(??_I2CPWMworker+0)+0
	movf	(??_I2CPWMworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CPWMworker@token)
	line	243
	
l19798:	
;i2c.c: 243: if(SSP2STATbits.S)
	movlb 4	; select bank4
	btfss	(540)^0200h,3	;volatile
	goto	u4821
	goto	u4820
u4821:
	goto	l3310
u4820:
	line	245
	
l19800:	
;i2c.c: 244: {
;i2c.c: 245: RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	246
;i2c.c: 246: switch(token)
	goto	l19830
	line	248
;i2c.c: 247: {
;i2c.c: 248: case 0x01:
	
l3312:	
	line	249
	
l19802:	
;i2c.c: 249: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CPWMworker+0)+0
	movf	(??_I2CPWMworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CPWMworker@temp)
	line	250
;i2c.c: 250: break;
	goto	l19844
	line	251
;i2c.c: 251: case 0x21:
	
l3314:	
	line	252
	
l19804:	
;i2c.c: 252: if(!addressed)
	movf	(I2CPWMworker@addressed),f
	skipz
	goto	u4831
	goto	u4830
u4831:
	goto	l19810
u4830:
	line	254
	
l19806:	
;i2c.c: 253: {
;i2c.c: 254: addr=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CPWMworker+0)+0
	movf	(??_I2CPWMworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CPWMworker@addr)
	line	255
	
l19808:	
;i2c.c: 255: addressed=1;
	clrf	(I2CPWMworker@addressed)
	bsf	status,0
	rlf	(I2CPWMworker@addressed),f
	line	256
;i2c.c: 256: }
	goto	l19844
	line	257
	
l3315:	
	line	259
	
l19810:	
;i2c.c: 257: else
;i2c.c: 258: {
;i2c.c: 259: if(addr==0)
	movf	(I2CPWMworker@addr),f
	skipz
	goto	u4841
	goto	u4840
u4841:
	goto	l19818
u4840:
	line	261
	
l19812:	
;i2c.c: 260: {
;i2c.c: 261: tempP=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CPWMworker+0)+0
	movf	(??_I2CPWMworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CPWMworker@tempP)
	line	262
	
l19814:	
;i2c.c: 262: addr=1;
	clrf	(I2CPWMworker@addr)
	bsf	status,0
	rlf	(I2CPWMworker@addr),f
	line	263
	
l19816:	
;i2c.c: 263: fP=1;
	clrf	(I2CPWMworker@fP)
	bsf	status,0
	rlf	(I2CPWMworker@fP),f
	line	264
;i2c.c: 264: }
	goto	l19844
	line	265
	
l3317:	
	line	267
	
l19818:	
;i2c.c: 265: else
;i2c.c: 266: {
;i2c.c: 267: tempD=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CPWMworker+0)+0
	movf	(??_I2CPWMworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CPWMworker@tempD)
	line	268
	
l19820:	
;i2c.c: 268: addr=0;
	clrf	(I2CPWMworker@addr)
	line	269
	
l19822:	
;i2c.c: 269: fD=1;
	clrf	(I2CPWMworker@fD)
	bsf	status,0
	rlf	(I2CPWMworker@fD),f
	goto	l19844
	line	270
	
l3318:	
	goto	l19844
	line	271
	
l3316:	
	line	272
;i2c.c: 270: }
;i2c.c: 271: }
;i2c.c: 272: break;
	goto	l19844
	line	273
;i2c.c: 273: case 0x05:
	
l3319:	
	line	274
	
l19824:	
;i2c.c: 274: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CPWMworker+0)+0
	movf	(??_I2CPWMworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CPWMworker@temp)
	line	275
;i2c.c: 275: SSP2BUF = PWMperiod;
	movf	(_PWMperiod),w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	line	276
;i2c.c: 276: break;
	goto	l19844
	line	277
;i2c.c: 277: case 0x24:
	
l3320:	
	line	278
	
l19826:	
;i2c.c: 278: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CPWMworker+0)+0
	movf	(??_I2CPWMworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CPWMworker@temp)
	line	280
;i2c.c: 280: SSP2BUF = PWMduty;
	movf	(_PWMduty),w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	line	281
;i2c.c: 281: break;
	goto	l19844
	line	282
	
l19828:	
;i2c.c: 282: }
	goto	l19844
	line	246
	
l3311:	
	
l19830:	
	movlb 0	; select bank0
	movf	(I2CPWMworker@token),w
	; Switch size 1, requested type "space"
; Number of cases is 4, Range of values is 1 to 36
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           13     7 (average)
; direct_byte           81     9 (fixed)
; jumptable            263     9 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	1^0	; case 1
	skipnz
	goto	l19802
	xorlw	5^1	; case 5
	skipnz
	goto	l19824
	xorlw	33^5	; case 33
	skipnz
	goto	l19804
	xorlw	36^33	; case 36
	skipnz
	goto	l19826
	goto	l19844
	opt asmopt_on

	line	282
	
l3313:	
	line	283
;i2c.c: 283: }
	goto	l19844
	line	284
	
l3310:	
;i2c.c: 284: else if(SSP2STATbits.P)
	btfss	(540)^0200h,4	;volatile
	goto	u4851
	goto	u4850
u4851:
	goto	l19844
u4850:
	line	286
	
l19832:	
;i2c.c: 285: {
;i2c.c: 286: RC5=0;;
	movlb 0	; select bank0
	bcf	(117/8),(117)&7
	line	287
;i2c.c: 287: addressed=0;
	clrf	(I2CPWMworker@addressed)
	line	288
# 288 "C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
NOP ;#
psect	text1306
	line	289
	
l19834:	
;i2c.c: 289: if(fP)setPeriod(tempP);
	movlb 0	; select bank0
	movf	(I2CPWMworker@fP),w
	skipz
	goto	u4860
	goto	l19838
u4860:
	
l19836:	
	movf	(I2CPWMworker@tempP),w
	fcall	_setPeriod
	goto	l19838
	
l3323:	
	line	290
	
l19838:	
;i2c.c: 290: if(fD)setDuty(tempD);
	movlb 0	; select bank0
	movf	(I2CPWMworker@fD),w
	skipz
	goto	u4870
	goto	l19842
u4870:
	
l19840:	
	movf	(I2CPWMworker@tempD),w
	fcall	_setDuty
	goto	l19842
	
l3324:	
	line	291
	
l19842:	
;i2c.c: 291: fD=fP=0;
	movlw	(0)
	movlb 0	; select bank0
	movwf	(I2CPWMworker@fP)
	movwf	(??_I2CPWMworker+0)+0
	movf	(??_I2CPWMworker+0)+0,w
	movwf	(I2CPWMworker@fD)
	goto	l19844
	line	293
	
l3322:	
	goto	l19844
	line	294
	
l3321:	
	
l19844:	
;i2c.c: 293: }
;i2c.c: 294: SSP2CON1bits.CKP=1;
	movlb 4	; select bank4
	bsf	(541)^0200h,4	;volatile
	goto	l19792
	line	295
	
l3309:	
	goto	l19792
	line	296
	
l3325:	
	line	236
	goto	l19792
	
l3326:	
	line	297
	
l3327:	
	return
	opt stack 0
GLOBAL	__end_of_I2CPWMworker
	__end_of_I2CPWMworker:
;; =============== function _I2CPWMworker ends ============

	signat	_I2CPWMworker,88
psect	text1307,local,class=CODE,delta=2
global __ptext1307
__ptext1307:

;; *************** function _SPIPWMworker *****************
;; Defined at:
;;		line 165 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\spi.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  fInst           1   14[BANK0 ] unsigned char 
;;  bf              1   13[BANK0 ] unsigned char 
;;  fb              1   12[BANK0 ] unsigned char 
;;  instruction     1   11[BANK0 ] unsigned char 
;;  token           1   10[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       5       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       5       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_initSPI
;;		_enablePWM
;;		_setPeriod
;;		_setDuty
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1307
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\spi.c"
	line	165
	global	__size_of_SPIPWMworker
	__size_of_SPIPWMworker	equ	__end_of_SPIPWMworker-_SPIPWMworker
	
_SPIPWMworker:	
	opt	stack 12
; Regs used in _SPIPWMworker: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	166
	
l19846:	
;spi.c: 166: unsigned char token, instruction, fInst=0,fb=0,bf=0;
	movlb 0	; select bank0
	clrf	(SPIPWMworker@fInst)
	clrf	(SPIPWMworker@fb)
	clrf	(SPIPWMworker@bf)
	line	167
	
l19848:	
;spi.c: 167: initSPI();
	fcall	_initSPI
	line	168
	
l19850:	
;spi.c: 168: SSP2BUF = 0xFD;
	movlw	(0FDh)
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	line	169
	
l19852:	
;spi.c: 169: enablePWM();
	fcall	_enablePWM
	goto	l4965
	line	170
;spi.c: 170: while (1)
	
l4964:	
	line	172
;spi.c: 171: {
;spi.c: 172: while(PORTCbits.RC0 ==0)
	goto	l4965
	
l4966:	
	line	174
;spi.c: 173: {
;spi.c: 174: if(SSP2STATbits.BF)
	movlb 4	; select bank4
	btfss	(540)^0200h,0	;volatile
	goto	u4881
	goto	u4880
u4881:
	goto	l4965
u4880:
	line	176
	
l19854:	
;spi.c: 175: {
;spi.c: 176: bf=1;
	movlb 0	; select bank0
	clrf	(SPIPWMworker@bf)
	bsf	status,0
	rlf	(SPIPWMworker@bf),f
	line	177
;spi.c: 177: if(fb==0)
	movf	(SPIPWMworker@fb),f
	skipz
	goto	u4891
	goto	u4890
u4891:
	goto	l19860
u4890:
	line	179
	
l19856:	
;spi.c: 178: {
;spi.c: 179: token = SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_SPIPWMworker+0)+0
	movf	(??_SPIPWMworker+0)+0,w
	movlb 0	; select bank0
	movwf	(SPIPWMworker@token)
	line	180
	
l19858:	
;spi.c: 180: instruction = token & 0xF7;
	movf	(SPIPWMworker@token),w
	andlw	0F7h
	movwf	(??_SPIPWMworker+0)+0
	movf	(??_SPIPWMworker+0)+0,w
	movwf	(SPIPWMworker@instruction)
	goto	l19860
	line	181
	
l4968:	
	line	182
	
l19860:	
;spi.c: 181: }
;spi.c: 182: fb=1;
	clrf	(SPIPWMworker@fb)
	bsf	status,0
	rlf	(SPIPWMworker@fb),f
	line	183
;spi.c: 183: switch (instruction)
	goto	l19888
	line	185
;spi.c: 184: {
;spi.c: 185: case 0:
	
l4970:	
	line	186
	
l19862:	
;spi.c: 186: if(fInst)
	movf	(SPIPWMworker@fInst),w
	skipz
	goto	u4900
	goto	l19870
u4900:
	line	188
	
l19864:	
;spi.c: 187: {
;spi.c: 188: if(fInst==1)setPeriod(SSP2BUF);
	movf	(SPIPWMworker@fInst),w
	xorlw	01h&0ffh
	skipz
	goto	u4911
	goto	u4910
u4911:
	goto	l19868
u4910:
	
l19866:	
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	fcall	_setPeriod
	goto	l19868
	
l4972:	
	line	189
	
l19868:	
;spi.c: 189: fInst++;
	movlw	(01h)
	movwf	(??_SPIPWMworker+0)+0
	movf	(??_SPIPWMworker+0)+0,w
	movlb 0	; select bank0
	addwf	(SPIPWMworker@fInst),f
	line	190
;spi.c: 190: }
	goto	l19872
	line	191
	
l4971:	
	line	193
	
l19870:	
;spi.c: 191: else
;spi.c: 192: {
;spi.c: 193: fInst=1;
	clrf	(SPIPWMworker@fInst)
	bsf	status,0
	rlf	(SPIPWMworker@fInst),f
	goto	l19872
	line	194
	
l4973:	
	line	195
	
l19872:	
;spi.c: 194: }
;spi.c: 195: SSP2BUF = PWMperiod;
	movf	(_PWMperiod),w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	line	196
;spi.c: 196: break;
	goto	l4965
	line	197
;spi.c: 197: case 1:
	
l4975:	
	line	198
	
l19874:	
;spi.c: 198: if(fInst)
	movlb 0	; select bank0
	movf	(SPIPWMworker@fInst),w
	skipz
	goto	u4920
	goto	l19882
u4920:
	line	200
	
l19876:	
;spi.c: 199: {
;spi.c: 200: if(fInst==1)setDuty(SSP2BUF);
	movf	(SPIPWMworker@fInst),w
	xorlw	01h&0ffh
	skipz
	goto	u4931
	goto	u4930
u4931:
	goto	l19880
u4930:
	
l19878:	
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	fcall	_setDuty
	goto	l19880
	
l4977:	
	line	201
	
l19880:	
;spi.c: 201: fInst++;
	movlw	(01h)
	movwf	(??_SPIPWMworker+0)+0
	movf	(??_SPIPWMworker+0)+0,w
	movlb 0	; select bank0
	addwf	(SPIPWMworker@fInst),f
	line	202
;spi.c: 202: }
	goto	l19884
	line	203
	
l4976:	
	line	205
	
l19882:	
;spi.c: 203: else
;spi.c: 204: {
;spi.c: 205: fInst=1;
	clrf	(SPIPWMworker@fInst)
	bsf	status,0
	rlf	(SPIPWMworker@fInst),f
	goto	l19884
	line	206
	
l4978:	
	line	207
	
l19884:	
;spi.c: 206: }
;spi.c: 207: SSP2BUF = PWMduty;
	movf	(_PWMduty),w
	movlb 4	; select bank4
	movwf	(537)^0200h	;volatile
	line	208
;spi.c: 208: break;
	goto	l4965
	line	209
	
l19886:	
;spi.c: 209: }
	goto	l4965
	line	183
	
l4969:	
	
l19888:	
	movlb 0	; select bank0
	movf	(SPIPWMworker@instruction),w
	; Switch size 1, requested type "space"
; Number of cases is 2, Range of values is 0 to 1
; switch strategies available:
; Name         Instructions Cycles
; simple_byte            7     4 (average)
; direct_byte           10     6 (fixed)
; jumptable            260     6 (fixed)
; rangetable             6     4 (fixed)
; spacedrange            9     6 (fixed)
; locatedrange           2     3 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	0^0	; case 0
	skipnz
	goto	l19862
	xorlw	1^0	; case 1
	skipnz
	goto	l19874
	goto	l4965
	opt asmopt_on

	line	209
	
l4974:	
	goto	l4965
	line	210
	
l4967:	
	line	211
	
l4965:	
	line	172
	movlb 0	; select bank0
	btfss	(14),0	;volatile
	goto	u4941
	goto	u4940
u4941:
	goto	l4966
u4940:
	goto	l19890
	
l4979:	
	line	212
	
l19890:	
;spi.c: 210: }
;spi.c: 211: }
;spi.c: 212: if(bf)
	movf	(SPIPWMworker@bf),w
	skipz
	goto	u4950
	goto	l4965
u4950:
	line	214
	
l19892:	
;spi.c: 213: {
;spi.c: 214: fb=0;
	clrf	(SPIPWMworker@fb)
	line	215
;spi.c: 215: bf=0;
	clrf	(SPIPWMworker@bf)
	line	216
;spi.c: 216: fInst = 0;
	clrf	(SPIPWMworker@fInst)
	goto	l4965
	line	217
	
l4980:	
	goto	l4965
	line	218
	
l4981:	
	line	170
	goto	l4965
	
l4982:	
	line	220
	
l4983:	
	return
	opt stack 0
GLOBAL	__end_of_SPIPWMworker
	__end_of_SPIPWMworker:
;; =============== function _SPIPWMworker ends ============

	signat	_SPIPWMworker,88
psect	text1308,local,class=CODE,delta=2
global __ptext1308
__ptext1308:

;; *************** function _nullfunc1 *****************
;; Defined at:
;;		line 70 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1308
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
	line	70
	global	__size_of_nullfunc1
	__size_of_nullfunc1	equ	__end_of_nullfunc1-_nullfunc1
	
_nullfunc1:	
	opt	stack 14
; Regs used in _nullfunc1: []
	
l1623:	
	return
	opt stack 0
GLOBAL	__end_of_nullfunc1
	__end_of_nullfunc1:
;; =============== function _nullfunc1 ends ============

	signat	_nullfunc1,88
psect	text1309,local,class=CODE,delta=2
global __ptext1309
__ptext1309:

;; *************** function _UARTworker *****************
;; Defined at:
;;		line 52 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  instruction     1   19[BANK0 ] unsigned char 
;;  c               1   18[BANK0 ] unsigned char 
;;  mode            1   17[BANK0 ] unsigned char 
;;  EEaddr          1   16[BANK0 ] unsigned char 
;;  adcc            1   15[BANK0 ] unsigned char 
;;  EEaddrF         1   14[BANK0 ] unsigned char 
;;  helpC           1   13[BANK0 ] unsigned char 
;;  addr            1   12[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr1l, fsr1h, status,2, status,0, btemp+1, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       8       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      10       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       10 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_initUART
;;		_UARTwriteString
;;		_UARTwrite
;;		_UARTread
;;		_enablePWM
;;		_enableDAC
;;		_getADC
;;		_UARTwriteDecimal
;;		_UARTcharFromString
;;		_setPeriod
;;		_setDuty
;;		_disablePWM
;;		_setDAC
;;		_disableDAC
;;		_EEPROMwrite
;;		_EEPROMread
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1309
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
	line	52
	global	__size_of_UARTworker
	__size_of_UARTworker	equ	__end_of_UARTworker-_UARTworker
	
_UARTworker:	
	opt	stack 12
; Regs used in _UARTworker: [allreg]
	line	53
	
l19894:	
;uart.c: 53: unsigned char c,mode=0,addr=0,instruction=0,EEaddrF=0,EEaddr=0,adcc=0,helpC;
	movlb 0	; select bank0
	clrf	(UARTworker@mode)
	clrf	(UARTworker@addr)
	clrf	(UARTworker@instruction)
	clrf	(UARTworker@EEaddrF)
	clrf	(UARTworker@EEaddr)
	clrf	(UARTworker@adcc)
	line	54
	
l19896:	
;uart.c: 54: initUART();
	fcall	_initUART
	line	56
	
l19898:	
;uart.c: 56: UARTwriteString(msgMenu[0]);
	movlb 0	; select bank0
	movf	(_msgMenu+1),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(_msgMenu),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	57
	
l19900:	
;uart.c: 57: UARTwrite('\n');
	movlw	(0Ah)
	fcall	_UARTwrite
	goto	l19902
	line	58
;uart.c: 58: while(1)
	
l6627:	
	line	61
	
l19902:	
;uart.c: 59: {
;uart.c: 61: if(RCIF)
	movlb 0	; select bank0
	btfss	(141/8),(141)&7
	goto	u4961
	goto	u4960
u4961:
	goto	l19902
u4960:
	line	63
	
l19904:	
;uart.c: 62: {
;uart.c: 63: RCIF=0;
	bcf	(141/8),(141)&7
	line	64
;uart.c: 64: RC3=1;;
	bsf	(115/8),(115)&7
	line	65
	
l19906:	
;uart.c: 65: if(!(RCSTA&0b00000110))
	movlb 3	; select bank3
	movf	(413)^0180h,w
	andlw	06h
	btfss	status,2
	goto	u4971
	goto	u4970
u4971:
	goto	l19912
u4970:
	line	66
	
l19908:	
;uart.c: 66: { rhead++;
	movlw	(01h)
	movlb 0	; select bank0
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	addwf	(_rhead),f	;volatile
	line	67
;uart.c: 67: rhead&=(8-1);
	movlw	(07h)
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	andwf	(_rhead),f	;volatile
	line	68
	
l19910:	
;uart.c: 68: ringbuff[rhead]=RCREG;
	movlb 3	; select bank3
	movf	(409)^0180h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_UARTworker+0)+0
	clrf	(??_UARTworker+0)+0+1
	movf	(_rhead),w	;volatile
	addwf	wreg,w
	addlw	_ringbuff&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	0+(??_UARTworker+0)+0,w
	movwi	[0]fsr1
	movf	1+(??_UARTworker+0)+0,w
	movwi	[1]fsr1
	goto	l19912
	line	69
	
l6629:	
	line	70
	
l19912:	
;uart.c: 69: }
;uart.c: 70: RC3=0;;
	movlb 0	; select bank0
	bcf	(115/8),(115)&7
	line	71
	
l19914:	
;uart.c: 71: c=UARTread();
	fcall	_UARTread
	movlb 0	; select bank0
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@c)
	line	72
;uart.c: 72: UARTwrite(c);
	movf	(UARTworker@c),w
	fcall	_UARTwrite
	line	74
;uart.c: 74: switch (mode)
	goto	l20078
	line	76
;uart.c: 75: {
;uart.c: 76: case 0:
	
l6631:	
	line	77
	
l19916:	
;uart.c: 77: mode=c-48;
	movlb 0	; select bank0
	movf	(UARTworker@c),w
	addlw	0D0h
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@mode)
	line	78
	
l19918:	
;uart.c: 78: UARTwriteString(msgMenu[c-48]);
	movf	(UARTworker@c),w
	addwf	wreg,w
	addlw	0A0h
	addlw	_msgMenu&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	moviw	[0]fsr1
	movwf	(?_UARTwriteString)
	moviw	[1]fsr1
	movwf	(?_UARTwriteString+1)
	fcall	_UARTwriteString
	line	79
	
l19920:	
;uart.c: 79: if(mode==2)enablePWM();
	movlb 0	; select bank0
	movf	(UARTworker@mode),w
	xorlw	02h&0ffh
	skipz
	goto	u4981
	goto	u4980
u4981:
	goto	l19924
u4980:
	
l19922:	
	fcall	_enablePWM
	goto	l19902
	line	80
	
l6632:	
	
l19924:	
;uart.c: 80: else if(mode==3)enableDAC();
	movlb 0	; select bank0
	movf	(UARTworker@mode),w
	xorlw	03h&0ffh
	skipz
	goto	u4991
	goto	u4990
u4991:
	goto	l19902
u4990:
	
l19926:	
	fcall	_enableDAC
	goto	l19902
	
l6634:	
	goto	l19902
	line	81
	
l6633:	
;uart.c: 81: break;
	goto	l19902
	line	82
;uart.c: 82: case 1:
	
l6636:	
	line	83
;uart.c: 83: switch(c)
	goto	l19962
	line	85
;uart.c: 84: {
;uart.c: 85: case 'r':
	
l6638:	
	line	86
	
l19928:	
;uart.c: 86: UARTwriteString("\n\nADC value: ");
	movlw	low(STR_1|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(STR_1|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	line	87
	
l19930:	
;uart.c: 87: helpC=getADC(adcc);
	movlb 0	; select bank0
	movf	(UARTworker@adcc),w
	fcall	_getADC
	movf	(0+(?_getADC)),w
	movlb 0	; select bank0
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@helpC)
	line	88
	
l19932:	
;uart.c: 88: UARTwriteDecimal(helpC);
	movf	(UARTworker@helpC),w
	fcall	_UARTwriteDecimal
	line	89
	
l19934:	
;uart.c: 89: UARTwriteString(msgMenu[1]);
	movlb 0	; select bank0
	movf	(1+_msgMenu+02h),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(0+_msgMenu+02h),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	90
;uart.c: 90: break;
	goto	l19902
	line	91
;uart.c: 91: case '1':
	
l6640:	
	line	92
	
l19936:	
;uart.c: 92: UARTwriteString("\n\nchannel 1 selected");
	movlw	low(STR_2|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(STR_2|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	line	93
	
l19938:	
;uart.c: 93: adcc=0;
	movlb 0	; select bank0
	clrf	(UARTworker@adcc)
	line	94
;uart.c: 94: UARTwriteString(msgMenu[1]);
	movf	(1+_msgMenu+02h),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(0+_msgMenu+02h),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	95
;uart.c: 95: break;
	goto	l19902
	line	96
;uart.c: 96: case '2':
	
l6641:	
	line	97
	
l19940:	
;uart.c: 97: UARTwriteString("\n\nchannel 2 selected");
	movlw	low(STR_3|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(STR_3|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	line	98
	
l19942:	
;uart.c: 98: adcc=1;
	movlb 0	; select bank0
	clrf	(UARTworker@adcc)
	bsf	status,0
	rlf	(UARTworker@adcc),f
	line	99
	
l19944:	
;uart.c: 99: UARTwriteString(msgMenu[1]);
	movf	(1+_msgMenu+02h),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(0+_msgMenu+02h),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	100
;uart.c: 100: break;
	goto	l19902
	line	101
;uart.c: 101: case '3':
	
l6642:	
	line	102
	
l19946:	
;uart.c: 102: UARTwriteString("\n\nchannel 3 selected");
	movlw	low(STR_4|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(STR_4|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	line	103
	
l19948:	
;uart.c: 103: adcc=2;
	movlw	(02h)
	movlb 0	; select bank0
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@adcc)
	line	104
	
l19950:	
;uart.c: 104: UARTwriteString(msgMenu[1]);
	movf	(1+_msgMenu+02h),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(0+_msgMenu+02h),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	105
;uart.c: 105: break;
	goto	l19902
	line	106
;uart.c: 106: case 't':
	
l6643:	
	line	107
	
l19952:	
;uart.c: 107: UARTwriteString("\n\nTemp sensor selected");
	movlw	low(STR_5|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(STR_5|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	line	108
	
l19954:	
;uart.c: 108: adcc=3;
	movlw	(03h)
	movlb 0	; select bank0
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@adcc)
	line	109
	
l19956:	
;uart.c: 109: UARTwriteString(msgMenu[1]);
	movf	(1+_msgMenu+02h),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(0+_msgMenu+02h),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	110
;uart.c: 110: break;
	goto	l19902
	line	111
;uart.c: 111: case 'm':
	
l6644:	
	line	112
;uart.c: 112: mode = 0;
	clrf	(UARTworker@mode)
	line	113
	
l19958:	
;uart.c: 113: UARTwriteString(msgMenu[0]);
	movf	(_msgMenu+1),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(_msgMenu),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	114
;uart.c: 114: break;
	goto	l19902
	line	115
;uart.c: 115: default:
	
l6645:	
	line	116
;uart.c: 116: break;
	goto	l19902
	line	117
	
l19960:	
;uart.c: 117: }
	goto	l19902
	line	83
	
l6637:	
	
l19962:	
	movlb 0	; select bank0
	movf	(UARTworker@c),w
	; Switch size 1, requested type "space"
; Number of cases is 6, Range of values is 49 to 116
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           19    10 (average)
; direct_byte          145     9 (fixed)
; jumptable            263     9 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	49^0	; case 49
	skipnz
	goto	l19936
	xorlw	50^49	; case 50
	skipnz
	goto	l19940
	xorlw	51^50	; case 51
	skipnz
	goto	l19946
	xorlw	109^51	; case 109
	skipnz
	goto	l6644
	xorlw	114^109	; case 114
	skipnz
	goto	l19928
	xorlw	116^114	; case 116
	skipnz
	goto	l19952
	goto	l19902
	opt asmopt_on

	line	117
	
l6639:	
	line	118
;uart.c: 118: break;
	goto	l19902
	line	119
;uart.c: 119: case 2:
	
l6646:	
	line	120
	
l19964:	
;uart.c: 120: if(instruction)
	movf	(UARTworker@instruction),w
	skipz
	goto	u5000
	goto	l19982
u5000:
	goto	l19980
	line	122
	
l19966:	
;uart.c: 121: {
;uart.c: 122: switch(instruction)
	goto	l19980
	line	124
;uart.c: 123: {
;uart.c: 124: case 'p':
	
l6649:	
	line	126
	
l19968:	
;uart.c: 126: setPeriod(UARTcharFromString(c));
	movf	(UARTworker@c),w
	fcall	_UARTcharFromString
	fcall	_setPeriod
	line	127
	
l19970:	
;uart.c: 127: UARTwriteString(msgMenu[2]);
	movlb 0	; select bank0
	movf	(1+_msgMenu+04h),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(0+_msgMenu+04h),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	128
;uart.c: 128: break;
	goto	l6650
	line	129
;uart.c: 129: case 'd':
	
l6651:	
	line	130
	
l19972:	
;uart.c: 130: setDuty(UARTcharFromString(c));
	movlb 0	; select bank0
	movf	(UARTworker@c),w
	fcall	_UARTcharFromString
	fcall	_setDuty
	line	131
	
l19974:	
;uart.c: 131: UARTwriteString(msgMenu[2]);
	movlb 0	; select bank0
	movf	(1+_msgMenu+04h),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(0+_msgMenu+04h),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	133
;uart.c: 133: break;
	goto	l6650
	line	134
;uart.c: 134: case 'm':
	
l6652:	
	line	135
;uart.c: 135: mode =0;
	clrf	(UARTworker@mode)
	line	137
	
l19976:	
;uart.c: 137: UARTwriteString(msgMenu[0]);
	movf	(_msgMenu+1),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(_msgMenu),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	138
;uart.c: 138: break;
	goto	l6650
	line	139
;uart.c: 139: default:
	
l6653:	
	line	140
;uart.c: 140: break;
	goto	l6650
	line	141
	
l19978:	
;uart.c: 141: }
	goto	l6650
	line	122
	
l6648:	
	
l19980:	
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	; Switch size 1, requested type "space"
; Number of cases is 3, Range of values is 100 to 112
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           10     6 (average)
; direct_byte           35     9 (fixed)
; jumptable            263     9 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	100^0	; case 100
	skipnz
	goto	l19972
	xorlw	109^100	; case 109
	skipnz
	goto	l6652
	xorlw	112^109	; case 112
	skipnz
	goto	l19968
	goto	l6650
	opt asmopt_on

	line	141
	
l6650:	
	line	142
;uart.c: 142: instruction = 0;
	movlb 0	; select bank0
	clrf	(UARTworker@instruction)
	line	143
;uart.c: 143: }
	goto	l19902
	line	144
	
l6647:	
	line	146
	
l19982:	
;uart.c: 144: else
;uart.c: 145: {
;uart.c: 146: instruction = c;
	movf	(UARTworker@c),w
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@instruction)
	line	147
;uart.c: 147: if(instruction == 'p')
	movf	(UARTworker@instruction),w
	xorlw	070h&0ffh
	skipz
	goto	u5011
	goto	u5010
u5011:
	goto	l19986
u5010:
	line	149
	
l19984:	
;uart.c: 148: {
;uart.c: 149: UARTwriteString("\n\nEnter the PWM Period: ");
	movlw	low(STR_6|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(STR_6|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	line	151
;uart.c: 151: }
	goto	l19902
	line	152
	
l6655:	
	
l19986:	
;uart.c: 152: else if(instruction == 'd')
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	xorlw	064h&0ffh
	skipz
	goto	u5021
	goto	u5020
u5021:
	goto	l19990
u5020:
	line	154
	
l19988:	
;uart.c: 153: {
;uart.c: 154: UARTwriteString("\n\nEnter the PWM Duty Cycle: ");
	movlw	low(STR_7|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(STR_7|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	line	155
;uart.c: 155: }
	goto	l19902
	line	156
	
l6657:	
	
l19990:	
;uart.c: 156: else if(instruction == 'm')
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	xorlw	06Dh&0ffh
	skipz
	goto	u5031
	goto	u5030
u5031:
	goto	l19902
u5030:
	line	158
	
l19992:	
;uart.c: 157: {
;uart.c: 158: mode =0;
	clrf	(UARTworker@mode)
	line	159
;uart.c: 159: instruction =0;
	clrf	(UARTworker@instruction)
	line	160
	
l19994:	
;uart.c: 160: disablePWM();
	fcall	_disablePWM
	line	161
	
l19996:	
;uart.c: 161: UARTwriteString(msgMenu[0]);
	movlb 0	; select bank0
	movf	(_msgMenu+1),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(_msgMenu),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	goto	l19902
	line	162
	
l6659:	
	goto	l19902
	line	163
	
l6658:	
	goto	l19902
	
l6656:	
	goto	l19902
	
l6654:	
	line	164
;uart.c: 162: }
;uart.c: 163: }
;uart.c: 164: break;
	goto	l19902
	line	165
;uart.c: 165: case 3:
	
l6660:	
	line	166
	
l19998:	
;uart.c: 166: if(instruction)
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	skipz
	goto	u5040
	goto	l20012
u5040:
	goto	l20010
	line	168
	
l20000:	
;uart.c: 167: {
;uart.c: 168: switch(instruction)
	goto	l20010
	line	170
;uart.c: 169: {
;uart.c: 170: case 'v':
	
l6663:	
	line	171
	
l20002:	
;uart.c: 171: setDAC(UARTcharFromString(c));
	movf	(UARTworker@c),w
	fcall	_UARTcharFromString
	fcall	_setDAC
	line	172
	
l20004:	
;uart.c: 172: UARTwriteString(msgMenu[3]);
	movlb 0	; select bank0
	movf	(1+_msgMenu+06h),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(0+_msgMenu+06h),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	173
;uart.c: 173: break;
	goto	l6664
	line	174
;uart.c: 174: case 'm':
	
l6665:	
	line	175
;uart.c: 175: mode = 0;
	clrf	(UARTworker@mode)
	line	176
	
l20006:	
;uart.c: 176: UARTwriteString(msgMenu[0]);
	movf	(_msgMenu+1),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(_msgMenu),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	177
;uart.c: 177: break;
	goto	l6664
	line	178
;uart.c: 178: default:
	
l6666:	
	line	179
;uart.c: 179: break;
	goto	l6664
	line	180
	
l20008:	
;uart.c: 180: }
	goto	l6664
	line	168
	
l6662:	
	
l20010:	
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	; Switch size 1, requested type "space"
; Number of cases is 2, Range of values is 109 to 118
; switch strategies available:
; Name         Instructions Cycles
; simple_byte            7     4 (average)
; direct_byte           29     9 (fixed)
; jumptable            263     9 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	109^0	; case 109
	skipnz
	goto	l6665
	xorlw	118^109	; case 118
	skipnz
	goto	l20002
	goto	l6664
	opt asmopt_on

	line	180
	
l6664:	
	line	181
;uart.c: 181: instruction =0;
	movlb 0	; select bank0
	clrf	(UARTworker@instruction)
	line	182
;uart.c: 182: }
	goto	l19902
	line	183
	
l6661:	
	line	185
	
l20012:	
;uart.c: 183: else
;uart.c: 184: {
;uart.c: 185: instruction = c;
	movf	(UARTworker@c),w
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@instruction)
	line	186
;uart.c: 186: if(instruction == 'v')
	movf	(UARTworker@instruction),w
	xorlw	076h&0ffh
	skipz
	goto	u5051
	goto	u5050
u5051:
	goto	l20016
u5050:
	line	188
	
l20014:	
;uart.c: 187: {
;uart.c: 188: UARTwriteString(msgDACsetV);
	movlw	low(_msgDACsetV|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(_msgDACsetV|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	line	189
;uart.c: 189: }
	goto	l19902
	line	190
	
l6668:	
	
l20016:	
;uart.c: 190: else if(instruction == 'm')
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	xorlw	06Dh&0ffh
	skipz
	goto	u5061
	goto	u5060
u5061:
	goto	l19902
u5060:
	line	192
	
l20018:	
;uart.c: 191: {
;uart.c: 192: mode =0;
	clrf	(UARTworker@mode)
	line	193
;uart.c: 193: instruction =0;
	clrf	(UARTworker@instruction)
	line	194
	
l20020:	
;uart.c: 194: disableDAC();
	fcall	_disableDAC
	line	195
	
l20022:	
;uart.c: 195: UARTwriteString(msgMenu[0]);
	movlb 0	; select bank0
	movf	(_msgMenu+1),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(_msgMenu),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	goto	l19902
	line	196
	
l6670:	
	goto	l19902
	line	197
	
l6669:	
	goto	l19902
	
l6667:	
	line	198
;uart.c: 196: }
;uart.c: 197: }
;uart.c: 198: break;
	goto	l19902
	line	199
;uart.c: 199: case 4:
	
l6671:	
	line	200
	
l20024:	
;uart.c: 200: if(instruction)
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	skipz
	goto	u5070
	goto	l20062
u5070:
	line	202
	
l20026:	
;uart.c: 201: {
;uart.c: 202: if(EEaddrF)
	movf	(UARTworker@EEaddrF),w
	skipz
	goto	u5080
	goto	l20050
u5080:
	line	204
	
l20028:	
;uart.c: 203: {
;uart.c: 204: if(instruction == 'w')
	movf	(UARTworker@instruction),w
	xorlw	077h&0ffh
	skipz
	goto	u5091
	goto	u5090
u5091:
	goto	l20034
u5090:
	line	206
	
l20030:	
;uart.c: 205: {
;uart.c: 206: EEPROMwrite(EEaddr,UARTcharFromString(c));
	movf	(UARTworker@c),w
	fcall	_UARTcharFromString
	movlb 0	; select bank0
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(?_EEPROMwrite)
	movf	(UARTworker@EEaddr),w
	fcall	_EEPROMwrite
	line	207
	
l20032:	
;uart.c: 207: UARTwriteString(msgMenu[4]);
	movlb 0	; select bank0
	movf	(1+_msgMenu+08h),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(0+_msgMenu+08h),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	209
;uart.c: 209: }
	goto	l20046
	line	210
	
l6674:	
	
l20034:	
;uart.c: 210: else if (instruction == 'r')
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	xorlw	072h&0ffh
	skipz
	goto	u5101
	goto	u5100
u5101:
	goto	l20040
u5100:
	line	212
	
l20036:	
;uart.c: 211: {
;uart.c: 212: UARTwriteDecimal(EEPROMread(EEaddr));
	movf	(UARTworker@EEaddr),w
	fcall	_EEPROMread
	fcall	_UARTwriteDecimal
	line	213
	
l20038:	
;uart.c: 213: UARTwriteString(msgMenu[4]);
	movlb 0	; select bank0
	movf	(1+_msgMenu+08h),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(0+_msgMenu+08h),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	214
;uart.c: 214: }
	goto	l20046
	line	215
	
l6676:	
	
l20040:	
;uart.c: 215: else if (instruction == 'm')
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	xorlw	06Dh&0ffh
	skipz
	goto	u5111
	goto	u5110
u5111:
	goto	l20046
u5110:
	line	217
	
l20042:	
;uart.c: 216: {
;uart.c: 217: mode = 0;
	clrf	(UARTworker@mode)
	line	218
	
l20044:	
;uart.c: 218: UARTwriteString(msgMenu[0]);
	movf	(_msgMenu+1),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(_msgMenu),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	goto	l20046
	line	219
	
l6678:	
	goto	l20046
	line	220
	
l6677:	
	goto	l20046
	
l6675:	
	
l20046:	
;uart.c: 219: }
;uart.c: 220: EEaddrF=0;
	movlb 0	; select bank0
	clrf	(UARTworker@EEaddrF)
	line	221
	
l20048:	
;uart.c: 221: instruction =0;
	clrf	(UARTworker@instruction)
	line	222
;uart.c: 222: }
	goto	l19902
	line	223
	
l6673:	
	line	225
	
l20050:	
;uart.c: 223: else
;uart.c: 224: {
;uart.c: 225: EEaddrF=1;
	clrf	(UARTworker@EEaddrF)
	bsf	status,0
	rlf	(UARTworker@EEaddrF),f
	line	226
	
l20052:	
;uart.c: 226: EEaddr=UARTcharFromString(c);
	movf	(UARTworker@c),w
	fcall	_UARTcharFromString
	movlb 0	; select bank0
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@EEaddr)
	line	228
	
l20054:	
;uart.c: 228: if(instruction=='w')UARTwriteString(msgEEw);
	movf	(UARTworker@instruction),w
	xorlw	077h&0ffh
	skipz
	goto	u5121
	goto	u5120
u5121:
	goto	l20058
u5120:
	
l20056:	
	movlw	low(_msgEEw|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(_msgEEw|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	goto	l19902
	line	229
	
l6680:	
	
l20058:	
;uart.c: 229: else if(instruction == 'r')UARTwriteString("\n\nHit any key to read from EEPROM.\n\n");
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	xorlw	072h&0ffh
	skipz
	goto	u5131
	goto	u5130
u5131:
	goto	l19902
u5130:
	
l20060:	
	movlw	low(STR_8|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(STR_8|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	goto	l19902
	
l6682:	
	goto	l19902
	line	230
	
l6681:	
	goto	l19902
	
l6679:	
	line	231
;uart.c: 230: }
;uart.c: 231: }
	goto	l19902
	line	232
	
l6672:	
	line	234
	
l20062:	
;uart.c: 232: else
;uart.c: 233: {
;uart.c: 234: instruction = c;
	movlb 0	; select bank0
	movf	(UARTworker@c),w
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@instruction)
	line	235
;uart.c: 235: if((instruction == 'w')||(instruction == 'r'))
	movf	(UARTworker@instruction),w
	xorlw	077h&0ffh
	skipnz
	goto	u5141
	goto	u5140
u5141:
	goto	l20066
u5140:
	
l20064:	
	movf	(UARTworker@instruction),w
	xorlw	072h&0ffh
	skipz
	goto	u5151
	goto	u5150
u5151:
	goto	l20068
u5150:
	goto	l20066
	
l6686:	
	line	237
	
l20066:	
;uart.c: 236: {
;uart.c: 237: UARTwriteString(msgEEaddr);
	movlw	low(_msgEEaddr|8000h)
	movwf	(?_UARTwriteString)
	movlw	high(_msgEEaddr|8000h)
	movwf	((?_UARTwriteString))+1
	fcall	_UARTwriteString
	line	238
;uart.c: 238: }
	goto	l19902
	line	239
	
l6684:	
	
l20068:	
;uart.c: 239: else if(instruction == 'm')
	movlb 0	; select bank0
	movf	(UARTworker@instruction),w
	xorlw	06Dh&0ffh
	skipz
	goto	u5161
	goto	u5160
u5161:
	goto	l19902
u5160:
	line	241
	
l20070:	
;uart.c: 240: {
;uart.c: 241: mode =0;
	clrf	(UARTworker@mode)
	line	242
;uart.c: 242: instruction =0;
	clrf	(UARTworker@instruction)
	line	243
	
l20072:	
;uart.c: 243: UARTwriteString(msgMenu[0]);
	movf	(_msgMenu+1),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(_msgMenu),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	goto	l19902
	line	244
	
l6688:	
	goto	l19902
	line	245
	
l6687:	
	goto	l19902
	
l6683:	
	line	246
;uart.c: 244: }
;uart.c: 245: }
;uart.c: 246: break;
	goto	l19902
	line	247
;uart.c: 247: default:
	
l6689:	
	line	248
;uart.c: 248: mode=0;
	clrf	(UARTworker@mode)
	line	249
	
l20074:	
;uart.c: 249: UARTwriteString(msgMenu[0]);
	movf	(_msgMenu+1),w
	clrf	(?_UARTwriteString+1)
	addwf	(?_UARTwriteString+1)
	movf	(_msgMenu),w
	clrf	(?_UARTwriteString)
	addwf	(?_UARTwriteString)

	fcall	_UARTwriteString
	line	250
;uart.c: 250: break;
	goto	l19902
	line	251
	
l20076:	
;uart.c: 251: }
	goto	l19902
	line	74
	
l6630:	
	
l20078:	
	movlb 0	; select bank0
	movf	(UARTworker@mode),w
	; Switch size 1, requested type "space"
; Number of cases is 5, Range of values is 0 to 4
; switch strategies available:
; Name         Instructions Cycles
; direct_byte           16     6 (fixed)
; simple_byte           16     9 (average)
; jumptable            260     6 (fixed)
; rangetable             9     4 (fixed)
; spacedrange           15     6 (fixed)
; locatedrange           5     3 (fixed)
;	Chosen strategy is direct_byte

	movwf fsr0l
	movlw	5
	subwf	fsr0l,w
skipnc
goto l6689
movlp high(S20136)
	lslf fsr0l,w
	addlw low(S20136)
	movwf pc
psect	swtext1,local,class=CONST,delta=2
global __pswtext1
__pswtext1:
S20136:
	ljmp	l19916
	ljmp	l19962
	ljmp	l19964
	ljmp	l19998
	ljmp	l20024
psect	text1309

	line	251
	
l6635:	
	goto	l19902
	line	252
	
l6628:	
	goto	l19902
	line	253
	
l6690:	
	line	58
	goto	l19902
	
l6691:	
	line	254
	
l6692:	
	return
	opt stack 0
GLOBAL	__end_of_UARTworker
	__end_of_UARTworker:
;; =============== function _UARTworker ends ============

	signat	_UARTworker,88
	global	_doEE
psect	text1310,local,class=CODE,delta=2
global __ptext1310
__ptext1310:

;; *************** function _doEE *****************
;; Defined at:
;;		line 21 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\easteregg.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, btemp+1, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_teletype
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1310
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\easteregg.c"
	line	21
	global	__size_of_doEE
	__size_of_doEE	equ	__end_of_doEE-_doEE
	
_doEE:	
	opt	stack 12
; Regs used in _doEE: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	line	22
	
l19314:	
;easteregg.c: 22: teletype("Hello, nice of you to drop by\r\n");
	movlw	low(STR_9|8000h)
	movwf	(?_teletype)
	movlw	high(STR_9|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	23
;easteregg.c: 23: teletype("I'm happy to tell you my story\r\n");
	movlw	low(STR_10|8000h)
	movwf	(?_teletype)
	movlw	high(STR_10|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	24
;easteregg.c: 24: teletype("They put me through endless hours of regression test..\r\n");
	movlw	low(STR_11|8000h)
	movwf	(?_teletype)
	movlw	high(STR_11|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	25
;easteregg.c: 25: teletype(".. conducted several tests on me..\r\n");
	movlw	low(STR_12|8000h)
	movwf	(?_teletype)
	movlw	high(STR_12|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	26
;easteregg.c: 26: teletype(".connected me to weird prototypes...\r\n");
	movlw	low(STR_13|8000h)
	movwf	(?_teletype)
	movlw	high(STR_13|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	27
;easteregg.c: 27: teletype("abused me with 5V....\r\n");
	movlw	low(STR_14|8000h)
	movwf	(?_teletype)
	movlw	high(STR_14|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	28
;easteregg.c: 28: teletype("used HiZ on me.......\r\n");
	movlw	low(STR_15|8000h)
	movwf	(?_teletype)
	movlw	high(STR_15|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	29
;easteregg.c: 29: teletype("let me talk I2C, SPI, UART......\r\n");
	movlw	low(STR_16|8000h)
	movwf	(?_teletype)
	movlw	high(STR_16|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	30
;easteregg.c: 30: teletype("made me do weird shit like PWM, memoryemulation, convert high voltages..\r\n");
	movlw	low(STR_17|8000h)
	movwf	(?_teletype)
	movlw	high(STR_17|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	31
;easteregg.c: 31: teletype("COULD YOU PLEASE LEAVE ME ALONE?!?!?!");
	movlw	low(STR_18|8000h)
	movwf	(?_teletype)
	movlw	high(STR_18|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	goto	l8307
	line	32
;easteregg.c: 32: while(1);
	
l8306:	
	
l8307:	
	goto	l8307
	
l8308:	
	line	33
	
l8309:	
	return
	opt stack 0
GLOBAL	__end_of_doEE
	__end_of_doEE:
;; =============== function _doEE ends ============

	signat	_doEE,88
	global	_teletype
psect	text1311,local,class=CODE,delta=2
global __ptext1311
__ptext1311:

;; *************** function _teletype *****************
;; Defined at:
;;		line 36 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\easteregg.c"
;; Parameters:    Size  Location     Type
;;  s               2    4[COMMON] PTR const unsigned char 
;;		 -> STR_18(38), STR_17(75), STR_16(35), STR_15(24), 
;;		 -> STR_14(24), STR_13(39), STR_12(37), STR_11(57), 
;;		 -> STR_10(33), STR_9(32), 
;; Auto vars:     Size  Location     Type
;;  i               2    6[COMMON] int 
;;  c               1    0        unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, btemp+1, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_UARTwrite
;; This function is called by:
;;		_doEE
;; This function uses a non-reentrant model
;;
psect	text1311
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\easteregg.c"
	line	36
	global	__size_of_teletype
	__size_of_teletype	equ	__end_of_teletype-_teletype
	
_teletype:	
	opt	stack 12
; Regs used in _teletype: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	line	39
	
l19296:	
;easteregg.c: 37: char c;
;easteregg.c: 39: while(*s)
	goto	l19312
	
l8313:	
	line	41
	
l19298:	
;easteregg.c: 40: {
;easteregg.c: 41: UARTwrite(*(s++));
	movf	(teletype@s),w
	movwf	fsr0l
	movf	((teletype@s+1)),w
	movwf	fsr0h
	movf	indf0,w ;code access
	fcall	_UARTwrite
	
l19300:	
	movlw	low(01h)
	addwf	(teletype@s),f
	movlw	high(01h)
	addwfc	(teletype@s+1),f
	line	43
	
l19302:	
;easteregg.c: 43: for(i=0; i<10000; i++) asm("nop");
	clrf	(teletype@i)
	clrf	(teletype@i+1)
	
l19304:	
	movf	(teletype@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(02710h))^80h
	subwf	btemp+1,w
	skipz
	goto	u4225
	movlw	low(02710h)
	subwf	(teletype@i),w
u4225:

	skipc
	goto	u4221
	goto	u4220
u4221:
	goto	l8314
u4220:
	goto	l19312
	
l19306:	
	goto	l19312
	
l8314:	
# 43 "C:\Users\Filip\Documents\MPLAB\Demo Board\easteregg.c"
nop ;#
psect	text1311
	
l19308:	
	movlw	low(01h)
	addwf	(teletype@i),f
	movlw	high(01h)
	addwfc	(teletype@i+1),f
	
l19310:	
	movf	(teletype@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(02710h))^80h
	subwf	btemp+1,w
	skipz
	goto	u4235
	movlw	low(02710h)
	subwf	(teletype@i),w
u4235:

	skipc
	goto	u4231
	goto	u4230
u4231:
	goto	l8314
u4230:
	goto	l19312
	
l8315:	
	goto	l19312
	line	44
	
l8312:	
	line	39
	
l19312:	
	movf	(teletype@s),w
	movwf	fsr0l
	movf	((teletype@s+1)),w
	movwf	fsr0h
	movf	indf0,w ;code access
	iorlw	0
	skipz
	goto	u4241
	goto	u4240
u4241:
	goto	l19298
u4240:
	goto	l8317
	
l8316:	
	line	45
	
l8317:	
	return
	opt stack 0
GLOBAL	__end_of_teletype
	__end_of_teletype:
;; =============== function _teletype ends ============

	signat	_teletype,4216
	global	_UARTcharFromString
psect	text1312,local,class=CODE,delta=2
global __ptext1312
__ptext1312:

;; *************** function _UARTcharFromString *****************
;; Defined at:
;;		line 295 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
;; Parameters:    Size  Location     Type
;;  c               1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  c               1    2[BANK0 ] unsigned char 
;;  rC              1    5[BANK0 ] unsigned char 
;;  c1              1    4[BANK0 ] unsigned char 
;;  outF            1    3[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       4       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       6       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_UARTread
;;		_UARTwrite
;;		___bmul
;; This function is called by:
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1312
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
	line	295
	global	__size_of_UARTcharFromString
	__size_of_UARTcharFromString	equ	__end_of_UARTcharFromString-_UARTcharFromString
	
_UARTcharFromString:	
	opt	stack 12
; Regs used in _UARTcharFromString: [wreg+fsr1l-status,0+pclath+cstack]
;UARTcharFromString@c stored from wreg
	movlb 0	; select bank0
	movwf	(UARTcharFromString@c)
	line	296
	
l19756:	
;uart.c: 296: unsigned char rC,outF=0,c1=c-48;
	clrf	(UARTcharFromString@outF)
	
l19758:	
	movf	(UARTcharFromString@c),w
	addlw	0D0h
	movwf	(??_UARTcharFromString+0)+0
	movf	(??_UARTcharFromString+0)+0,w
	movwf	(UARTcharFromString@c1)
	line	297
;uart.c: 297: while(outF==0)
	goto	l19778
	
l6711:	
	line	299
;uart.c: 298: {
;uart.c: 299: while(RCIF==0);
	goto	l6712
	
l6713:	
	
l6712:	
	btfss	(141/8),(141)&7
	goto	u4771
	goto	u4770
u4771:
	goto	l6712
u4770:
	goto	l19760
	
l6714:	
	line	300
	
l19760:	
;uart.c: 300: if(!(RCSTA&0b00000110))
	movlb 3	; select bank3
	movf	(413)^0180h,w
	andlw	06h
	btfss	status,2
	goto	u4781
	goto	u4780
u4781:
	goto	l19766
u4780:
	line	301
	
l19762:	
;uart.c: 301: { rhead++;
	movlw	(01h)
	movlb 0	; select bank0
	movwf	(??_UARTcharFromString+0)+0
	movf	(??_UARTcharFromString+0)+0,w
	addwf	(_rhead),f	;volatile
	line	302
;uart.c: 302: rhead&=(8-1);
	movlw	(07h)
	movwf	(??_UARTcharFromString+0)+0
	movf	(??_UARTcharFromString+0)+0,w
	andwf	(_rhead),f	;volatile
	line	303
	
l19764:	
;uart.c: 303: ringbuff[rhead]=RCREG;
	movlb 3	; select bank3
	movf	(409)^0180h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_UARTcharFromString+0)+0
	clrf	(??_UARTcharFromString+0)+0+1
	movf	(_rhead),w	;volatile
	addwf	wreg,w
	addlw	_ringbuff&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	0+(??_UARTcharFromString+0)+0,w
	movwi	[0]fsr1
	movf	1+(??_UARTcharFromString+0)+0,w
	movwi	[1]fsr1
	goto	l19766
	line	304
	
l6715:	
	line	305
	
l19766:	
;uart.c: 304: }
;uart.c: 305: RCIF=0;
	movlb 0	; select bank0
	bcf	(141/8),(141)&7
	line	306
	
l19768:	
;uart.c: 306: rC=UARTread();
	fcall	_UARTread
	movlb 0	; select bank0
	movwf	(??_UARTcharFromString+0)+0
	movf	(??_UARTcharFromString+0)+0,w
	movwf	(UARTcharFromString@rC)
	line	307
;uart.c: 307: UARTwrite(rC);
	movf	(UARTcharFromString@rC),w
	fcall	_UARTwrite
	line	308
	
l19770:	
;uart.c: 308: if(rC==13)outF=1;
	movlb 0	; select bank0
	movf	(UARTcharFromString@rC),w
	xorlw	0Dh&0ffh
	skipz
	goto	u4791
	goto	u4790
u4791:
	goto	l19774
u4790:
	
l19772:	
	clrf	(UARTcharFromString@outF)
	bsf	status,0
	rlf	(UARTcharFromString@outF),f
	goto	l19778
	line	309
	
l6716:	
	line	311
	
l19774:	
;uart.c: 309: else
;uart.c: 310: {
;uart.c: 311: c1*=10;
	movf	(UARTcharFromString@c1),w
	movwf	(??_UARTcharFromString+0)+0
	movf	(??_UARTcharFromString+0)+0,w
	movwf	(?___bmul)
	movlw	(0Ah)
	fcall	___bmul
	movlb 0	; select bank0
	movwf	(??_UARTcharFromString+1)+0
	movf	(??_UARTcharFromString+1)+0,w
	movwf	(UARTcharFromString@c1)
	line	312
	
l19776:	
;uart.c: 312: c1+=(rC-48);
	movf	(UARTcharFromString@rC),w
	addlw	0D0h
	movwf	(??_UARTcharFromString+0)+0
	movf	(??_UARTcharFromString+0)+0,w
	addwf	(UARTcharFromString@c1),f
	goto	l19778
	line	313
	
l6717:	
	goto	l19778
	line	314
	
l6710:	
	line	297
	
l19778:	
	movf	(UARTcharFromString@outF),w
	skipz
	goto	u4800
	goto	l6712
u4800:
	goto	l19780
	
l6718:	
	line	315
	
l19780:	
;uart.c: 313: }
;uart.c: 314: }
;uart.c: 315: return c1;
	movf	(UARTcharFromString@c1),w
	goto	l6719
	
l19782:	
	line	316
	
l6719:	
	return
	opt stack 0
GLOBAL	__end_of_UARTcharFromString
	__end_of_UARTcharFromString:
;; =============== function _UARTcharFromString ends ============

	signat	_UARTcharFromString,4217
	global	_UARTwriteDecimal
psect	text1313,local,class=CODE,delta=2
global __ptext1313
__ptext1313:

;; *************** function _UARTwriteDecimal *****************
;; Defined at:
;;		line 319 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
;; Parameters:    Size  Location     Type
;;  c               1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  c               1    0[BANK0 ] unsigned char 
;;  d               1    2[BANK0 ] unsigned char 
;;  hC              1    1[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       3       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       3       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		___lbdiv
;;		_UARTwrite
;;		___bmul
;; This function is called by:
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1313
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
	line	319
	global	__size_of_UARTwriteDecimal
	__size_of_UARTwriteDecimal	equ	__end_of_UARTwriteDecimal-_UARTwriteDecimal
	
_UARTwriteDecimal:	
	opt	stack 12
; Regs used in _UARTwriteDecimal: [wreg+status,2+status,0+pclath+cstack]
;UARTwriteDecimal@c stored from wreg
	movlb 0	; select bank0
	movwf	(UARTwriteDecimal@c)
	line	320
	
l19256:	
;uart.c: 320: unsigned char hC,d=100;
	movlw	(064h)
	movwf	(??_UARTwriteDecimal+0)+0
	movf	(??_UARTwriteDecimal+0)+0,w
	movwf	(UARTwriteDecimal@d)
	goto	l19258
	line	321
;uart.c: 321: do
	
l6722:	
	line	323
	
l19258:	
;uart.c: 322: {
;uart.c: 323: hC=c/d;
	movf	(UARTwriteDecimal@d),w
	movwf	(??_UARTwriteDecimal+0)+0
	movf	(??_UARTwriteDecimal+0)+0,w
	movwf	(?___lbdiv)
	movf	(UARTwriteDecimal@c),w
	fcall	___lbdiv
	movwf	(??_UARTwriteDecimal+1)+0
	movf	(??_UARTwriteDecimal+1)+0,w
	movlb 0	; select bank0
	movwf	(UARTwriteDecimal@hC)
	line	324
	
l19260:	
;uart.c: 324: UARTwrite(hC+48);
	movf	(UARTwriteDecimal@hC),w
	addlw	030h
	fcall	_UARTwrite
	line	325
	
l19262:	
;uart.c: 325: c-=hC*d;
	movlb 0	; select bank0
	movf	(UARTwriteDecimal@d),w
	movwf	(??_UARTwriteDecimal+0)+0
	movf	(??_UARTwriteDecimal+0)+0,w
	movwf	(?___bmul)
	movf	(UARTwriteDecimal@hC),w
	fcall	___bmul
	movwf	(??_UARTwriteDecimal+1)+0
	movf	0+(??_UARTwriteDecimal+1)+0,w
	movlb 0	; select bank0
	subwf	(UARTwriteDecimal@c),f
	line	326
	
l19264:	
;uart.c: 326: d/=10;
	movlw	(0Ah)
	movwf	(??_UARTwriteDecimal+0)+0
	movf	(??_UARTwriteDecimal+0)+0,w
	movwf	(?___lbdiv)
	movf	(UARTwriteDecimal@d),w
	fcall	___lbdiv
	movwf	(??_UARTwriteDecimal+1)+0
	movf	(??_UARTwriteDecimal+1)+0,w
	movlb 0	; select bank0
	movwf	(UARTwriteDecimal@d)
	line	327
	
l19266:	
;uart.c: 327: }while(d);
	movf	(UARTwriteDecimal@d),f
	skipz
	goto	u4171
	goto	u4170
u4171:
	goto	l19258
u4170:
	goto	l6724
	
l6723:	
	line	328
	
l6724:	
	return
	opt stack 0
GLOBAL	__end_of_UARTwriteDecimal
	__end_of_UARTwriteDecimal:
;; =============== function _UARTwriteDecimal ends ============

	signat	_UARTwriteDecimal,4216
	global	_UARTwriteString
psect	text1314,local,class=CODE,delta=2
global __ptext1314
__ptext1314:

;; *************** function _UARTwriteString *****************
;; Defined at:
;;		line 286 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
;; Parameters:    Size  Location     Type
;;  str             2    4[COMMON] PTR unsigned char 
;;		 -> msgEEaddr(28), STR_8(37), msgEEw(57), msgDACsetV(41), 
;;		 -> STR_7(29), STR_6(25), STR_5(23), STR_4(21), 
;;		 -> STR_3(21), STR_2(21), STR_1(14), msgMenu4(122), 
;;		 -> msgMenu3(76), msgMenu2(93), msgMenu1(123), msgMenu0(114), 
;; Auto vars:     Size  Location     Type
;;  i               1    8[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         5       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_UARTwrite
;; This function is called by:
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1314
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
	line	286
	global	__size_of_UARTwriteString
	__size_of_UARTwriteString	equ	__end_of_UARTwriteString-_UARTwriteString
	
_UARTwriteString:	
	opt	stack 12
; Regs used in _UARTwriteString: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	287
	
l19248:	
;uart.c: 287: unsigned char i=0;
	clrf	(UARTwriteString@i)
	line	288
;uart.c: 288: while(str[i])
	goto	l19254
	
l6705:	
	line	290
	
l19250:	
;uart.c: 289: {
;uart.c: 290: UARTwrite(str[i++]);
	movf	(UARTwriteString@str+1),w
	movwf	(??_UARTwriteString+0)+0+1
	movf	(UARTwriteString@str),w
	movwf	(??_UARTwriteString+0)+0
	movf	(UARTwriteString@i),w
	addwf	(??_UARTwriteString+0)+0,w
	movwf	fsr0l
	movf	(??_UARTwriteString+0)+1,w
	skipnc
	incf	(??_UARTwriteString+0)+1,w
	movwf	fsr0h

	movf	indf0,w ;code access
	fcall	_UARTwrite
	
l19252:	
	movlw	(01h)
	movwf	(??_UARTwriteString+0)+0
	movf	(??_UARTwriteString+0)+0,w
	addwf	(UARTwriteString@i),f
	goto	l19254
	line	291
	
l6704:	
	line	288
	
l19254:	
	movf	(UARTwriteString@str+1),w
	movwf	(??_UARTwriteString+0)+0+1
	movf	(UARTwriteString@str),w
	movwf	(??_UARTwriteString+0)+0
	movf	(UARTwriteString@i),w
	addwf	(??_UARTwriteString+0)+0,w
	movwf	fsr0l
	movf	(??_UARTwriteString+0)+1,w
	skipnc
	incf	(??_UARTwriteString+0)+1,w
	movwf	fsr0h

	movf	indf0,w ;code access
	iorlw	0
	skipz
	goto	u4161
	goto	u4160
u4161:
	goto	l19250
u4160:
	goto	l6707
	
l6706:	
	line	292
	
l6707:	
	return
	opt stack 0
GLOBAL	__end_of_UARTwriteString
	__end_of_UARTwriteString:
;; =============== function _UARTwriteString ends ============

	signat	_UARTwriteString,4216
	global	_setDuty
psect	text1315,local,class=CODE,delta=2
global __ptext1315
__ptext1315:

;; *************** function _setDuty *****************
;; Defined at:
;;		line 55 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\pwm.c"
;; Parameters:    Size  Location     Type
;;  D               1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  D               1    7[BANK0 ] unsigned char 
;;  temp            2    8[BANK0 ] unsigned int 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       3       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       7       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        7 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		___wmul
;;		___lwdiv
;; This function is called by:
;;		_I2CPWMworker
;;		_SPIPWMworker
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1315
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\pwm.c"
	line	55
	global	__size_of_setDuty
	__size_of_setDuty	equ	__end_of_setDuty-_setDuty
	
_setDuty:	
	opt	stack 12
; Regs used in _setDuty: [wreg+status,2+status,0+pclath+cstack]
;setDuty@D stored from wreg
	line	58
	movlb 0	; select bank0
	movwf	(setDuty@D)
	
l19742:	
;pwm.c: 56: unsigned int temp;
;pwm.c: 58: if(D<100)
	movlw	(064h)
	subwf	(setDuty@D),w
	skipnc
	goto	u4761
	goto	u4760
u4761:
	goto	l19750
u4760:
	line	60
	
l19744:	
;pwm.c: 59: {
;pwm.c: 60: PWMduty = D;
	movf	(setDuty@D),w
	movwf	(??_setDuty+0)+0
	movf	(??_setDuty+0)+0,w
	movwf	(_PWMduty)
	line	61
	
l19746:	
;pwm.c: 61: temp = PWMduty*PWMperiod;
	movf	(_PWMduty),w
	movwf	(??_setDuty+0)+0
	clrf	(??_setDuty+0)+0+1
	movf	0+(??_setDuty+0)+0,w
	movwf	(?___wmul)
	movf	1+(??_setDuty+0)+0,w
	movwf	(?___wmul+1)
	movf	(_PWMperiod),w
	movwf	(??_setDuty+2)+0
	clrf	(??_setDuty+2)+0+1
	movf	0+(??_setDuty+2)+0,w
	movwf	0+(?___wmul)+02h
	movf	1+(??_setDuty+2)+0,w
	movwf	1+(?___wmul)+02h
	fcall	___wmul
	movf	(1+(?___wmul)),w
	movlb 0	; select bank0
	clrf	(setDuty@temp+1)
	addwf	(setDuty@temp+1)
	movf	(0+(?___wmul)),w
	clrf	(setDuty@temp)
	addwf	(setDuty@temp)

	line	62
	
l19748:	
;pwm.c: 62: temp = temp/100;
	movlw	low(064h)
	movwf	(?___lwdiv)
	movlw	high(064h)
	movwf	((?___lwdiv))+1
	movf	(setDuty@temp+1),w
	clrf	1+(?___lwdiv)+02h
	addwf	1+(?___lwdiv)+02h
	movf	(setDuty@temp),w
	clrf	0+(?___lwdiv)+02h
	addwf	0+(?___lwdiv)+02h

	fcall	___lwdiv
	movf	(1+(?___lwdiv)),w
	movlb 0	; select bank0
	clrf	(setDuty@temp+1)
	addwf	(setDuty@temp+1)
	movf	(0+(?___lwdiv)),w
	clrf	(setDuty@temp)
	addwf	(setDuty@temp)

	line	63
;pwm.c: 63: CCPR2L = temp;
	movf	(setDuty@temp),w
	movlb 5	; select bank5
	movwf	(664)^0280h	;volatile
	line	64
;pwm.c: 64: }
	goto	l14598
	line	65
	
l14596:	
	line	67
	
l19750:	
;pwm.c: 65: else
;pwm.c: 66: {
;pwm.c: 67: PWMduty = 99;
	movlw	(063h)
	movlb 0	; select bank0
	movwf	(??_setDuty+0)+0
	movf	(??_setDuty+0)+0,w
	movwf	(_PWMduty)
	line	68
	
l19752:	
;pwm.c: 68: temp = PWMduty*PWMperiod;
	movf	(_PWMduty),w
	movwf	(??_setDuty+0)+0
	clrf	(??_setDuty+0)+0+1
	movf	0+(??_setDuty+0)+0,w
	movwf	(?___wmul)
	movf	1+(??_setDuty+0)+0,w
	movwf	(?___wmul+1)
	movf	(_PWMperiod),w
	movwf	(??_setDuty+2)+0
	clrf	(??_setDuty+2)+0+1
	movf	0+(??_setDuty+2)+0,w
	movwf	0+(?___wmul)+02h
	movf	1+(??_setDuty+2)+0,w
	movwf	1+(?___wmul)+02h
	fcall	___wmul
	movf	(1+(?___wmul)),w
	movlb 0	; select bank0
	clrf	(setDuty@temp+1)
	addwf	(setDuty@temp+1)
	movf	(0+(?___wmul)),w
	clrf	(setDuty@temp)
	addwf	(setDuty@temp)

	line	69
	
l19754:	
;pwm.c: 69: temp = temp/100;
	movlw	low(064h)
	movwf	(?___lwdiv)
	movlw	high(064h)
	movwf	((?___lwdiv))+1
	movf	(setDuty@temp+1),w
	clrf	1+(?___lwdiv)+02h
	addwf	1+(?___lwdiv)+02h
	movf	(setDuty@temp),w
	clrf	0+(?___lwdiv)+02h
	addwf	0+(?___lwdiv)+02h

	fcall	___lwdiv
	movf	(1+(?___lwdiv)),w
	movlb 0	; select bank0
	clrf	(setDuty@temp+1)
	addwf	(setDuty@temp+1)
	movf	(0+(?___lwdiv)),w
	clrf	(setDuty@temp)
	addwf	(setDuty@temp)

	line	70
;pwm.c: 70: CCPR2L = temp;
	movf	(setDuty@temp),w
	movlb 5	; select bank5
	movwf	(664)^0280h	;volatile
	goto	l14598
	line	71
	
l14597:	
	line	72
	
l14598:	
	return
	opt stack 0
GLOBAL	__end_of_setDuty
	__end_of_setDuty:
;; =============== function _setDuty ends ============

	signat	_setDuty,4216
	global	_setPeriod
psect	text1316,local,class=CODE,delta=2
global __ptext1316
__ptext1316:

;; *************** function _setPeriod *****************
;; Defined at:
;;		line 35 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\pwm.c"
;; Parameters:    Size  Location     Type
;;  P               1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  P               1    9[BANK0 ] unsigned char 
;;  temp            2    7[BANK0 ] unsigned int 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       3       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       7       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        7 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		___wmul
;;		___lwdiv
;; This function is called by:
;;		_I2CPWMworker
;;		_SPIPWMworker
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1316
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\pwm.c"
	line	35
	global	__size_of_setPeriod
	__size_of_setPeriod	equ	__end_of_setPeriod-_setPeriod
	
_setPeriod:	
	opt	stack 12
; Regs used in _setPeriod: [wreg+status,2+status,0+pclath+cstack]
;setPeriod@P stored from wreg
	line	37
	movlb 0	; select bank0
	movwf	(setPeriod@P)
	
l19730:	
;pwm.c: 36: unsigned int temp;
;pwm.c: 37: if(P>1)
	movlw	(02h)
	subwf	(setPeriod@P),w
	skipc
	goto	u4751
	goto	u4750
u4751:
	goto	l19740
u4750:
	line	39
	
l19732:	
;pwm.c: 38: {
;pwm.c: 39: temp=P*PWMduty;
	movf	(setPeriod@P),w
	movwf	(??_setPeriod+0)+0
	clrf	(??_setPeriod+0)+0+1
	movf	0+(??_setPeriod+0)+0,w
	movwf	(?___wmul)
	movf	1+(??_setPeriod+0)+0,w
	movwf	(?___wmul+1)
	movf	(_PWMduty),w
	movwf	(??_setPeriod+2)+0
	clrf	(??_setPeriod+2)+0+1
	movf	0+(??_setPeriod+2)+0,w
	movwf	0+(?___wmul)+02h
	movf	1+(??_setPeriod+2)+0,w
	movwf	1+(?___wmul)+02h
	fcall	___wmul
	movf	(1+(?___wmul)),w
	movlb 0	; select bank0
	clrf	(setPeriod@temp+1)
	addwf	(setPeriod@temp+1)
	movf	(0+(?___wmul)),w
	clrf	(setPeriod@temp)
	addwf	(setPeriod@temp)

	line	40
;pwm.c: 40: temp = temp/100;
	movlw	low(064h)
	movwf	(?___lwdiv)
	movlw	high(064h)
	movwf	((?___lwdiv))+1
	movf	(setPeriod@temp+1),w
	clrf	1+(?___lwdiv)+02h
	addwf	1+(?___lwdiv)+02h
	movf	(setPeriod@temp),w
	clrf	0+(?___lwdiv)+02h
	addwf	0+(?___lwdiv)+02h

	fcall	___lwdiv
	movf	(1+(?___lwdiv)),w
	movlb 0	; select bank0
	clrf	(setPeriod@temp+1)
	addwf	(setPeriod@temp+1)
	movf	(0+(?___lwdiv)),w
	clrf	(setPeriod@temp)
	addwf	(setPeriod@temp)

	line	41
	
l19734:	
;pwm.c: 41: CCPR2L = temp;
	movf	(setPeriod@temp),w
	movlb 5	; select bank5
	movwf	(664)^0280h	;volatile
	line	42
	
l19736:	
;pwm.c: 42: PWMperiod = P;
	movlb 0	; select bank0
	movf	(setPeriod@P),w
	movwf	(??_setPeriod+0)+0
	movf	(??_setPeriod+0)+0,w
	movwf	(_PWMperiod)
	line	43
	
l19738:	
;pwm.c: 43: PR2=P;
	movf	(setPeriod@P),w
	movwf	(27)	;volatile
	line	44
;pwm.c: 44: }
	goto	l14593
	line	45
	
l14591:	
	line	47
	
l19740:	
;pwm.c: 45: else
;pwm.c: 46: {
;pwm.c: 47: PWMperiod = 2;
	movlw	(02h)
	movwf	(??_setPeriod+0)+0
	movf	(??_setPeriod+0)+0,w
	movwf	(_PWMperiod)
	line	48
;pwm.c: 48: PR2 = 2;
	movlw	(02h)
	movwf	(27)	;volatile
	line	49
;pwm.c: 49: CCPR2L = 1;
	movlw	(01h)
	movlb 5	; select bank5
	movwf	(664)^0280h	;volatile
	goto	l14593
	line	50
	
l14592:	
	line	52
	
l14593:	
	return
	opt stack 0
GLOBAL	__end_of_setPeriod
	__end_of_setPeriod:
;; =============== function _setPeriod ends ============

	signat	_setPeriod,4216
	global	_enablePWM
psect	text1317,local,class=CODE,delta=2
global __ptext1317
__ptext1317:

;; *************** function _enablePWM *****************
;; Defined at:
;;		line 9 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\pwm.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  tempP           2    6[BANK0 ] unsigned int 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       3       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       5       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		___wmul
;;		___lwdiv
;; This function is called by:
;;		_I2CPWMworker
;;		_SPIPWMworker
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1317
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\pwm.c"
	line	9
	global	__size_of_enablePWM
	__size_of_enablePWM	equ	__end_of_enablePWM-_enablePWM
	
_enablePWM:	
	opt	stack 12
; Regs used in _enablePWM: [wreg+status,2+status,0+pclath+cstack]
	line	11
	
l19712:	
;pwm.c: 10: unsigned int tempP;
;pwm.c: 11: TRISAbits.TRISA5 =1;
	movlb 1	; select bank1
	bsf	(140)^080h,5	;volatile
	line	12
;pwm.c: 12: APFCON1bits.CCP2SEL=1;
	movlb 2	; select bank2
	bsf	(286)^0100h,0	;volatile
	line	13
	
l19714:	
;pwm.c: 13: PR2 = 0x02;
	movlw	(02h)
	movlb 0	; select bank0
	movwf	(27)	;volatile
	line	15
;pwm.c: 15: PWMperiod = PR2;
	movf	(27),w	;volatile
	movwf	(??_enablePWM+0)+0
	movf	(??_enablePWM+0)+0,w
	movwf	(_PWMperiod)
	line	17
;pwm.c: 17: CCP2CON =0b00001100;
	movlw	(0Ch)
	movlb 5	; select bank5
	movwf	(666)^0280h	;volatile
	line	20
;pwm.c: 20: CCPR2L =0x01;
	movlw	(01h)
	movwf	(664)^0280h	;volatile
	line	22
	
l19716:	
;pwm.c: 22: tempP=(unsigned int)CCPR2L*100;
	movf	(664)^0280h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_enablePWM+0)+0
	clrf	(??_enablePWM+0)+0+1
	movf	0+(??_enablePWM+0)+0,w
	movwf	(?___wmul)
	movf	1+(??_enablePWM+0)+0,w
	movwf	(?___wmul+1)
	movlw	low(064h)
	movwf	0+(?___wmul)+02h
	movlw	high(064h)
	movwf	(0+(?___wmul)+02h)+1
	fcall	___wmul
	movf	(1+(?___wmul)),w
	movlb 0	; select bank0
	clrf	(enablePWM@tempP+1)
	addwf	(enablePWM@tempP+1)
	movf	(0+(?___wmul)),w
	clrf	(enablePWM@tempP)
	addwf	(enablePWM@tempP)

	line	23
	
l19718:	
;pwm.c: 23: PWMduty = tempP/PWMperiod;
	movf	(_PWMperiod),w
	movwf	(??_enablePWM+0)+0
	clrf	(??_enablePWM+0)+0+1
	movf	0+(??_enablePWM+0)+0,w
	movwf	(?___lwdiv)
	movf	1+(??_enablePWM+0)+0,w
	movwf	(?___lwdiv+1)
	movf	(enablePWM@tempP+1),w
	clrf	1+(?___lwdiv)+02h
	addwf	1+(?___lwdiv)+02h
	movf	(enablePWM@tempP),w
	clrf	0+(?___lwdiv)+02h
	addwf	0+(?___lwdiv)+02h

	fcall	___lwdiv
	movf	(0+(?___lwdiv)),w
	movlb 0	; select bank0
	movwf	(??_enablePWM+2)+0
	movf	(??_enablePWM+2)+0,w
	movwf	(_PWMduty)
	line	26
	
l19720:	
;pwm.c: 26: CCPTMRS=0;
	movlb 5	; select bank5
	clrf	(670)^0280h	;volatile
	line	27
	
l19722:	
;pwm.c: 27: TMR2IF=0;
	movlb 0	; select bank0
	bcf	(137/8),(137)&7
	line	29
	
l19724:	
;pwm.c: 29: T2CON = 0;
	clrf	(28)	;volatile
	line	30
	
l19726:	
;pwm.c: 30: T2CONbits.TMR2ON =1;
	bsf	(28),2	;volatile
	line	31
	
l19728:	
;pwm.c: 31: TRISAbits.TRISA5 =0;
	movlb 1	; select bank1
	bcf	(140)^080h,5	;volatile
	line	32
	
l14588:	
	return
	opt stack 0
GLOBAL	__end_of_enablePWM
	__end_of_enablePWM:
;; =============== function _enablePWM ends ============

	signat	_enablePWM,88
	global	_init
psect	text1318,local,class=CODE,delta=2
global __ptext1318
__ptext1318:

;; *************** function _init *****************
;; Defined at:
;;		line 109 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_initSPI
;;		_initI2C
;;		_initUART
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1318
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
	line	109
	global	__size_of_init
	__size_of_init	equ	__end_of_init-_init
	
_init:	
	opt	stack 13
; Regs used in _init: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	111
	
l18792:	
;main.c: 111: OSCCONbits.SPLLEN=1;
	movlb 1	; select bank1
	bsf	(153)^080h,7	;volatile
	line	112
	
l18794:	
;main.c: 112: OSCCONbits.IRCF = 14;
	movf	(153)^080h,w	;volatile
	andlw	not (((1<<4)-1)<<3)
	iorlw	(0Eh & ((1<<4)-1))<<3
	movwf	(153)^080h	;volatile
	line	113
;main.c: 113: OSCCONbits.SCS =0;
	movlw	((0 & ((1<<2)-1))<<0)|not (((1<<2)-1)<<0)
	andwf	(153)^080h,f	;volatile
	line	116
	
l18796:	
;main.c: 116: PORTA=0x00;
	movlb 0	; select bank0
	clrf	(12)	;volatile
	line	117
	
l18798:	
;main.c: 117: LATA=0x00;
	movlb 2	; select bank2
	clrf	(268)^0100h	;volatile
	line	118
	
l18800:	
;main.c: 118: ANSELA=0x00;
	movlb 3	; select bank3
	clrf	(396)^0180h	;volatile
	line	119
	
l18802:	
;main.c: 119: TRISA=0xFF;
	movlw	(0FFh)
	movlb 1	; select bank1
	movwf	(140)^080h	;volatile
	line	120
	
l18804:	
;main.c: 120: WPUA=0x00;
	movlb 4	; select bank4
	clrf	(524)^0200h	;volatile
	line	123
	
l18806:	
;main.c: 123: PORTB=0x00;
	movlb 0	; select bank0
	clrf	(13)	;volatile
	line	124
	
l18808:	
;main.c: 124: LATB=0x00;
	movlb 2	; select bank2
	clrf	(269)^0100h	;volatile
	line	125
	
l18810:	
;main.c: 125: ANSELB=0x00;
	movlb 3	; select bank3
	clrf	(397)^0180h	;volatile
	line	126
	
l18812:	
;main.c: 126: TRISB=0xFF;
	movlw	(0FFh)
	movlb 1	; select bank1
	movwf	(141)^080h	;volatile
	line	127
	
l18814:	
;main.c: 127: WPUB=0x50;
	movlw	(050h)
	movlb 4	; select bank4
	movwf	(525)^0200h	;volatile
	line	130
	
l18816:	
;main.c: 130: PORTC=0x00;
	movlb 0	; select bank0
	clrf	(14)	;volatile
	line	131
	
l18818:	
;main.c: 131: LATC=0x00;
	movlb 2	; select bank2
	clrf	(270)^0100h	;volatile
	line	132
	
l18820:	
;main.c: 132: ANSELC=0x00;
	movlb 3	; select bank3
	clrf	(398)^0180h	;volatile
	line	133
	
l18822:	
;main.c: 133: TRISC=0xD7;
	movlw	(0D7h)
	movlb 1	; select bank1
	movwf	(142)^080h	;volatile
	line	134
	
l18824:	
;main.c: 134: WPUC=0x05;
	movlw	(05h)
	movlb 4	; select bank4
	movwf	(526)^0200h	;volatile
	line	136
	
l18826:	
;main.c: 136: nWPUEN=0;
	movlb 1	; select bank1
	bcf	(1199/8)^080h,(1199)&7
	line	139
	
l18828:	
;main.c: 139: APFCON0=0x00;
	movlb 2	; select bank2
	clrf	(285)^0100h	;volatile
	line	140
	
l18830:	
;main.c: 140: APFCON1=0x00;
	clrf	(286)^0100h	;volatile
	line	142
	
l18832:	
;main.c: 142: RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	143
	
l18834:	
;main.c: 143: RC3=1;;
	bsf	(115/8),(115)&7
	line	149
	
l18836:	
;main.c: 149: mode_device=0x00;
	clrf	(_mode_device)
	line	150
	
l18838:	
;main.c: 150: mode_protocol=0x00;
	clrf	(_mode_protocol)
	line	151
	
l18840:	
;main.c: 151: mode_device|=(RC2<<1);
	movlw	0
	btfsc	(114/8),(114)&7
	movlw	(1 << (01h))
	movwf	(??_init+0)+0
	movf	(??_init+0)+0,w
	iorwf	(_mode_device),f
	line	152
	
l18842:	
;main.c: 152: mode_device|=(RA2);
	movlw	0
	btfsc	(98/8),(98)&7
	movlw	1
	movwf	(??_init+0)+0
	movf	(??_init+0)+0,w
	iorwf	(_mode_device),f
	line	153
	
l18844:	
;main.c: 153: mode_protocol|=(RB6<<1);
	movlw	0
	btfsc	(110/8),(110)&7
	movlw	(1 << (01h))
	movwf	(??_init+0)+0
	movf	(??_init+0)+0,w
	iorwf	(_mode_protocol),f
	line	154
	
l18846:	
;main.c: 154: mode_protocol|=(RB4);
	movlw	0
	btfsc	(108/8),(108)&7
	movlw	1
	movwf	(??_init+0)+0
	movf	(??_init+0)+0,w
	iorwf	(_mode_protocol),f
	line	158
;main.c: 158: switch(mode_protocol)
	goto	l18856
	line	159
;main.c: 159: { case 0x01: initSPI();
	
l1643:	
	
l18848:	
	fcall	_initSPI
	line	160
;main.c: 160: break;
	goto	l1644
	line	161
;main.c: 161: case 0x03: initI2C();
	
l1645:	
	
l18850:	
	fcall	_initI2C
	line	162
;main.c: 162: break;
	goto	l1644
	line	163
;main.c: 163: case 0x02: initUART();
	
l1646:	
	
l18852:	
	fcall	_initUART
	line	164
;main.c: 164: break;
	goto	l1644
	line	165
;main.c: 165: case 0x00: break;
	
l1647:	
	goto	l1644
	line	166
;main.c: 166: default: break;
	
l1648:	
	goto	l1644
	line	167
	
l18854:	
;main.c: 167: }
	goto	l1644
	line	158
	
l1642:	
	
l18856:	
	movlb 0	; select bank0
	movf	(_mode_protocol),w
	; Switch size 1, requested type "space"
; Number of cases is 4, Range of values is 0 to 3
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           13     7 (average)
; direct_byte           14     6 (fixed)
; jumptable            260     6 (fixed)
; rangetable             8     4 (fixed)
; spacedrange           13     6 (fixed)
; locatedrange           4     3 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	0^0	; case 0
	skipnz
	goto	l1644
	xorlw	1^0	; case 1
	skipnz
	goto	l18848
	xorlw	2^1	; case 2
	skipnz
	goto	l18852
	xorlw	3^2	; case 3
	skipnz
	goto	l18850
	goto	l1644
	opt asmopt_on

	line	167
	
l1644:	
	line	169
;main.c: 169: RC5=0;;
	movlb 0	; select bank0
	bcf	(117/8),(117)&7
	line	176
	
l1649:	
	return
	opt stack 0
GLOBAL	__end_of_init
	__end_of_init:
;; =============== function _init ends ============

	signat	_init,88
	global	___lbdiv
psect	text1319,local,class=CODE,delta=2
global __ptext1319
__ptext1319:

;; *************** function ___lbdiv *****************
;; Defined at:
;;		line 5 in file "C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\lbdiv.c"
;; Parameters:    Size  Location     Type
;;  dividend        1    wreg     unsigned char 
;;  divisor         1    3[COMMON] unsigned char 
;; Auto vars:     Size  Location     Type
;;  dividend        1    5[COMMON] unsigned char 
;;  quotient        1    7[COMMON] unsigned char 
;;  counter         1    6[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         5       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_UARTwriteDecimal
;; This function uses a non-reentrant model
;;
psect	text1319
	file	"C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\lbdiv.c"
	line	5
	global	__size_of___lbdiv
	__size_of___lbdiv	equ	__end_of___lbdiv-___lbdiv
	
___lbdiv:	
	opt	stack 12
; Regs used in ___lbdiv: [wreg+status,2+status,0]
;___lbdiv@dividend stored from wreg
	line	9
	movwf	(___lbdiv@dividend)
	
l18768:	
	clrf	(___lbdiv@quotient)
	line	10
	movf	(___lbdiv@divisor),w
	skipz
	goto	u3620
	goto	l18788
u3620:
	line	11
	
l18770:	
	clrf	(___lbdiv@counter)
	bsf	status,0
	rlf	(___lbdiv@counter),f
	line	12
	goto	l18776
	
l16056:	
	line	13
	
l18772:	
	clrc
	rlf	(___lbdiv@divisor),f

	line	14
	
l18774:	
	movlw	(01h)
	movwf	(??___lbdiv+0)+0
	movf	(??___lbdiv+0)+0,w
	addwf	(___lbdiv@counter),f
	goto	l18776
	line	15
	
l16055:	
	line	12
	
l18776:	
	btfss	(___lbdiv@divisor),(7)&7
	goto	u3631
	goto	u3630
u3631:
	goto	l18772
u3630:
	goto	l18778
	
l16057:	
	goto	l18778
	line	16
	
l16058:	
	line	17
	
l18778:	
	clrc
	rlf	(___lbdiv@quotient),f

	line	18
	movf	(___lbdiv@divisor),w
	subwf	(___lbdiv@dividend),w
	skipc
	goto	u3641
	goto	u3640
u3641:
	goto	l18784
u3640:
	line	19
	
l18780:	
	movf	(___lbdiv@divisor),w
	subwf	(___lbdiv@dividend),f
	line	20
	
l18782:	
	bsf	(___lbdiv@quotient)+(0/8),(0)&7
	goto	l18784
	line	21
	
l16059:	
	line	22
	
l18784:	
	clrc
	rrf	(___lbdiv@divisor),f

	line	23
	
l18786:	
	movlw	low(01h)
	subwf	(___lbdiv@counter),f
	btfss	status,2
	goto	u3651
	goto	u3650
u3651:
	goto	l18778
u3650:
	goto	l18788
	
l16060:	
	goto	l18788
	line	24
	
l16054:	
	line	25
	
l18788:	
	movf	(___lbdiv@quotient),w
	goto	l16061
	
l18790:	
	line	26
	
l16061:	
	return
	opt stack 0
GLOBAL	__end_of___lbdiv
	__end_of___lbdiv:
;; =============== function ___lbdiv ends ============

	signat	___lbdiv,8313
	global	___lwdiv
psect	text1320,local,class=CODE,delta=2
global __ptext1320
__ptext1320:

;; *************** function ___lwdiv *****************
;; Defined at:
;;		line 5 in file "C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\lwdiv.c"
;; Parameters:    Size  Location     Type
;;  divisor         2    3[COMMON] unsigned int 
;;  dividend        2    5[COMMON] unsigned int 
;; Auto vars:     Size  Location     Type
;;  quotient        2    1[BANK0 ] unsigned int 
;;  counter         1    0[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    3[COMMON] unsigned int 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       3       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         5       3       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_enablePWM
;;		_setPeriod
;;		_setDuty
;; This function uses a non-reentrant model
;;
psect	text1320
	file	"C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\lwdiv.c"
	line	5
	global	__size_of___lwdiv
	__size_of___lwdiv	equ	__end_of___lwdiv-___lwdiv
	
___lwdiv:	
	opt	stack 12
; Regs used in ___lwdiv: [wreg+status,2+status,0]
	line	9
	
l19686:	
	movlb 0	; select bank0
	clrf	(___lwdiv@quotient)
	clrf	(___lwdiv@quotient+1)
	line	10
	
l19688:	
	movf	(___lwdiv@divisor+1),w
	iorwf	(___lwdiv@divisor),w
	skipnz
	goto	u4681
	goto	u4680
u4681:
	goto	l19708
u4680:
	line	11
	
l19690:	
	clrf	(___lwdiv@counter)
	bsf	status,0
	rlf	(___lwdiv@counter),f
	line	12
	goto	l19696
	
l16036:	
	line	13
	
l19692:	
	movlw	01h
	
u4695:
	lslf	(___lwdiv@divisor),f
	rlf	(___lwdiv@divisor+1),f
	decfsz	wreg,f
	goto	u4695
	line	14
	
l19694:	
	movlw	(01h)
	movwf	(??___lwdiv+0)+0
	movf	(??___lwdiv+0)+0,w
	addwf	(___lwdiv@counter),f
	goto	l19696
	line	15
	
l16035:	
	line	12
	
l19696:	
	btfss	(___lwdiv@divisor+1),(15)&7
	goto	u4701
	goto	u4700
u4701:
	goto	l19692
u4700:
	goto	l19698
	
l16037:	
	goto	l19698
	line	16
	
l16038:	
	line	17
	
l19698:	
	movlw	01h
	
u4715:
	lslf	(___lwdiv@quotient),f
	rlf	(___lwdiv@quotient+1),f
	decfsz	wreg,f
	goto	u4715
	line	18
	movf	(___lwdiv@divisor+1),w
	subwf	(___lwdiv@dividend+1),w
	skipz
	goto	u4725
	movf	(___lwdiv@divisor),w
	subwf	(___lwdiv@dividend),w
u4725:
	skipc
	goto	u4721
	goto	u4720
u4721:
	goto	l19704
u4720:
	line	19
	
l19700:	
	movf	(___lwdiv@divisor),w
	subwf	(___lwdiv@dividend),f
	movf	(___lwdiv@divisor+1),w
	subwfb	(___lwdiv@dividend+1),f
	line	20
	
l19702:	
	bsf	(___lwdiv@quotient)+(0/8),(0)&7
	goto	l19704
	line	21
	
l16039:	
	line	22
	
l19704:	
	movlw	01h
	
u4735:
	lsrf	(___lwdiv@divisor+1),f
	rrf	(___lwdiv@divisor),f
	decfsz	wreg,f
	goto	u4735
	line	23
	
l19706:	
	movlw	low(01h)
	subwf	(___lwdiv@counter),f
	btfss	status,2
	goto	u4741
	goto	u4740
u4741:
	goto	l19698
u4740:
	goto	l19708
	
l16040:	
	goto	l19708
	line	24
	
l16034:	
	line	25
	
l19708:	
	movf	(___lwdiv@quotient+1),w
	clrf	(?___lwdiv+1)
	addwf	(?___lwdiv+1)
	movf	(___lwdiv@quotient),w
	clrf	(?___lwdiv)
	addwf	(?___lwdiv)

	goto	l16041
	
l19710:	
	line	26
	
l16041:	
	return
	opt stack 0
GLOBAL	__end_of___lwdiv
	__end_of___lwdiv:
;; =============== function ___lwdiv ends ============

	signat	___lwdiv,8314
	global	___wmul
psect	text1321,local,class=CODE,delta=2
global __ptext1321
__ptext1321:

;; *************** function ___wmul *****************
;; Defined at:
;;		line 3 in file "C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\wmul.c"
;; Parameters:    Size  Location     Type
;;  multiplier      2    3[COMMON] unsigned int 
;;  multiplicand    2    5[COMMON] unsigned int 
;; Auto vars:     Size  Location     Type
;;  product         2    7[COMMON] unsigned int 
;; Return value:  Size  Location     Type
;;                  2    3[COMMON] unsigned int 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         6       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_enablePWM
;;		_setPeriod
;;		_setDuty
;; This function uses a non-reentrant model
;;
psect	text1321
	file	"C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\wmul.c"
	line	3
	global	__size_of___wmul
	__size_of___wmul	equ	__end_of___wmul-___wmul
	
___wmul:	
	opt	stack 12
; Regs used in ___wmul: [wreg+status,2+status,0]
	line	4
	
l18730:	
	clrf	(___wmul@product)
	clrf	(___wmul@product+1)
	goto	l18732
	line	6
	
l16028:	
	line	7
	
l18732:	
	btfss	(___wmul@multiplier),(0)&7
	goto	u3511
	goto	u3510
u3511:
	goto	l16029
u3510:
	line	8
	
l18734:	
	movf	(___wmul@multiplicand),w
	addwf	(___wmul@product),f
	movf	(___wmul@multiplicand+1),w
	addwfc	(___wmul@product+1),f
	
l16029:	
	line	9
	movlw	01h
	
u3525:
	lslf	(___wmul@multiplicand),f
	rlf	(___wmul@multiplicand+1),f
	decfsz	wreg,f
	goto	u3525
	line	10
	
l18736:	
	movlw	01h
	
u3535:
	lsrf	(___wmul@multiplier+1),f
	rrf	(___wmul@multiplier),f
	decfsz	wreg,f
	goto	u3535
	line	11
	movf	((___wmul@multiplier+1)),w
	iorwf	((___wmul@multiplier)),w
	skipz
	goto	u3541
	goto	u3540
u3541:
	goto	l18732
u3540:
	goto	l18738
	
l16030:	
	line	12
	
l18738:	
	movf	(___wmul@product+1),w
	clrf	(?___wmul+1)
	addwf	(?___wmul+1)
	movf	(___wmul@product),w
	clrf	(?___wmul)
	addwf	(?___wmul)

	goto	l16031
	
l18740:	
	line	13
	
l16031:	
	return
	opt stack 0
GLOBAL	__end_of___wmul
	__end_of___wmul:
;; =============== function ___wmul ends ============

	signat	___wmul,8314
	global	___bmul
psect	text1322,local,class=CODE,delta=2
global __ptext1322
__ptext1322:

;; *************** function ___bmul *****************
;; Defined at:
;;		line 3 in file "C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\bmul.c"
;; Parameters:    Size  Location     Type
;;  multiplier      1    wreg     unsigned char 
;;  multiplicand    1    3[COMMON] unsigned char 
;; Auto vars:     Size  Location     Type
;;  multiplier      1    6[COMMON] unsigned char 
;;  product         1    5[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_UARTcharFromString
;;		_UARTwriteDecimal
;; This function uses a non-reentrant model
;;
psect	text1322
	file	"C:\Program Files (x86)\HI-TECH Software\PICC\9.82\sources\bmul.c"
	line	3
	global	__size_of___bmul
	__size_of___bmul	equ	__end_of___bmul-___bmul
	
___bmul:	
	opt	stack 12
; Regs used in ___bmul: [wreg+status,2+status,0]
;___bmul@multiplier stored from wreg
	movwf	(___bmul@multiplier)
	line	4
	
l18714:	
	clrf	(___bmul@product)
	goto	l18716
	line	6
	
l16022:	
	line	7
	
l18716:	
	btfss	(___bmul@multiplier),(0)&7
	goto	u3491
	goto	u3490
u3491:
	goto	l18720
u3490:
	line	8
	
l18718:	
	movf	(___bmul@multiplicand),w
	movwf	(??___bmul+0)+0
	movf	(??___bmul+0)+0,w
	addwf	(___bmul@product),f
	goto	l18720
	
l16023:	
	line	9
	
l18720:	
	clrc
	rlf	(___bmul@multiplicand),f

	line	10
	
l18722:	
	clrc
	rrf	(___bmul@multiplier),f

	line	11
	
l18724:	
	movf	(___bmul@multiplier),f
	skipz
	goto	u3501
	goto	u3500
u3501:
	goto	l18716
u3500:
	goto	l18726
	
l16024:	
	line	12
	
l18726:	
	movf	(___bmul@product),w
	goto	l16025
	
l18728:	
	line	13
	
l16025:	
	return
	opt stack 0
GLOBAL	__end_of___bmul
	__end_of___bmul:
;; =============== function ___bmul ends ============

	signat	___bmul,8313
	global	_disableDAC
psect	text1323,local,class=CODE,delta=2
global __ptext1323
__ptext1323:

;; *************** function _disableDAC *****************
;; Defined at:
;;		line 16 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\dac.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1323
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\dac.c"
	line	16
	global	__size_of_disableDAC
	__size_of_disableDAC	equ	__end_of_disableDAC-_disableDAC
	
_disableDAC:	
	opt	stack 13
; Regs used in _disableDAC: [status,2]
	line	17
	
l18712:	
;dac.c: 17: DACCON1=0x00;
	movlb 2	; select bank2
	clrf	(281)^0100h	;volatile
	line	18
	
l13024:	
	return
	opt stack 0
GLOBAL	__end_of_disableDAC
	__end_of_disableDAC:
;; =============== function _disableDAC ends ============

	signat	_disableDAC,88
	global	_disablePWM
psect	text1324,local,class=CODE,delta=2
global __ptext1324
__ptext1324:

;; *************** function _disablePWM *****************
;; Defined at:
;;		line 75 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\pwm.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1324
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\pwm.c"
	line	75
	global	__size_of_disablePWM
	__size_of_disablePWM	equ	__end_of_disablePWM-_disablePWM
	
_disablePWM:	
	opt	stack 13
; Regs used in _disablePWM: []
	line	76
	
l18710:	
;pwm.c: 76: TRISAbits.TRISA5=1;
	movlb 1	; select bank1
	bsf	(140)^080h,5	;volatile
	line	77
;pwm.c: 77: T2CONbits.TMR2ON =0;
	movlb 0	; select bank0
	bcf	(28),2	;volatile
	line	78
	
l14601:	
	return
	opt stack 0
GLOBAL	__end_of_disablePWM
	__end_of_disablePWM:
;; =============== function _disablePWM ends ============

	signat	_disablePWM,88
	global	_UARTread
psect	text1325,local,class=CODE,delta=2
global __ptext1325
__ptext1325:

;; *************** function _UARTread *****************
;; Defined at:
;;		line 258 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  temp            1    4[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_UARTworker
;;		_UARTcharFromString
;; This function uses a non-reentrant model
;;
psect	text1325
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
	line	258
	global	__size_of_UARTread
	__size_of_UARTread	equ	__end_of_UARTread-_UARTread
	
_UARTread:	
	opt	stack 12
; Regs used in _UARTread: [wreg+fsr1l-status,0]
	line	265
	
l18702:	
;uart.c: 259: unsigned char temp;
;uart.c: 265: rtail++;
	movlw	(01h)
	movwf	(??_UARTread+0)+0
	movf	(??_UARTread+0)+0,w
	addwf	(_rtail),f	;volatile
	line	266
;uart.c: 266: rtail&=(8-1);
	movlw	(07h)
	movwf	(??_UARTread+0)+0
	movf	(??_UARTread+0)+0,w
	andwf	(_rtail),f	;volatile
	line	267
	
l18704:	
;uart.c: 267: temp=ringbuff[rtail];
	movf	(_rtail),w	;volatile
	addwf	wreg,w
	addlw	_ringbuff&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	movwf	(??_UARTread+0)+0
	movf	(??_UARTread+0)+0,w
	movwf	(UARTread@temp)
	line	270
	
l18706:	
;uart.c: 270: return temp;
	movf	(UARTread@temp),w
	goto	l6695
	
l18708:	
	line	271
	
l6695:	
	return
	opt stack 0
GLOBAL	__end_of_UARTread
	__end_of_UARTread:
;; =============== function _UARTread ends ============

	signat	_UARTread,89
	global	_UARTwrite
psect	text1326,local,class=CODE,delta=2
global __ptext1326
__ptext1326:

;; *************** function _UARTwrite *****************
;; Defined at:
;;		line 275 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
;; Parameters:    Size  Location     Type
;;  c               1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  c               1    3[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_UARTworker
;;		_UARTwriteString
;;		_UARTcharFromString
;;		_UARTwriteDecimal
;;		_teletype
;; This function uses a non-reentrant model
;;
psect	text1326
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
	line	275
	global	__size_of_UARTwrite
	__size_of_UARTwrite	equ	__end_of_UARTwrite-_UARTwrite
	
_UARTwrite:	
	opt	stack 12
; Regs used in _UARTwrite: [wreg]
;UARTwrite@c stored from wreg
	movwf	(UARTwrite@c)
	line	276
	
l18696:	
;uart.c: 276: RC3=1;;
	movlb 0	; select bank0
	bsf	(115/8),(115)&7
	line	278
;uart.c: 278: while(!TRMT);
	goto	l6698
	
l6699:	
	
l6698:	
	movlb 3	; select bank3
	btfss	(3313/8)^0180h,(3313)&7
	goto	u3481
	goto	u3480
u3481:
	goto	l6698
u3480:
	goto	l18698
	
l6700:	
	line	280
	
l18698:	
;uart.c: 280: TXREG=c;
	movf	(UARTwrite@c),w
	movwf	(410)^0180h	;volatile
	line	282
	
l18700:	
;uart.c: 282: RC3=0;;
	movlb 0	; select bank0
	bcf	(115/8),(115)&7
	line	283
	
l6701:	
	return
	opt stack 0
GLOBAL	__end_of_UARTwrite
	__end_of_UARTwrite:
;; =============== function _UARTwrite ends ============

	signat	_UARTwrite,4216
	global	_getADC
psect	text1327,local,class=CODE,delta=2
global __ptext1327
__ptext1327:

;; *************** function _getADC *****************
;; Defined at:
;;		line 16 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\adc.c"
;; Parameters:    Size  Location     Type
;;  adc             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  adc             1    3[BANK0 ] unsigned char 
;;  i               2    1[BANK0 ] int 
;;  temp            1    0[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    3[COMMON] unsigned int 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, btemp+1
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       4       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         5       4       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        9 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_SPIADCworker
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1327
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\adc.c"
	line	16
	global	__size_of_getADC
	__size_of_getADC	equ	__end_of_getADC-_getADC
	
_getADC:	
	opt	stack 13
; Regs used in _getADC: [wreg-fsr0h+status,2+status,0+btemp+1]
;getADC@adc stored from wreg
	movlb 0	; select bank0
	movwf	(getADC@adc)
	line	19
	
l18656:	
;adc.c: 17: unsigned char temp;
;adc.c: 18: int i;
;adc.c: 19: switch (adc)
	goto	l18672
	line	21
;adc.c: 20: {
;adc.c: 21: case 0:
	
l11438:	
	line	22
	
l18658:	
;adc.c: 22: adc=3;
	movlw	(03h)
	movwf	(??_getADC+0)+0
	movf	(??_getADC+0)+0,w
	movwf	(getADC@adc)
	line	23
;adc.c: 23: break;
	goto	l18674
	line	24
;adc.c: 24: case 1:
	
l11440:	
	line	25
	
l18660:	
;adc.c: 25: adc=8;
	movlw	(08h)
	movwf	(??_getADC+0)+0
	movf	(??_getADC+0)+0,w
	movwf	(getADC@adc)
	line	26
;adc.c: 26: break;
	goto	l18674
	line	27
;adc.c: 27: case 2:
	
l11441:	
	line	28
	
l18662:	
;adc.c: 28: adc =9;
	movlw	(09h)
	movwf	(??_getADC+0)+0
	movf	(??_getADC+0)+0,w
	movwf	(getADC@adc)
	line	29
;adc.c: 29: break;
	goto	l18674
	line	30
;adc.c: 30: case 3:
	
l11442:	
	line	31
	
l18664:	
;adc.c: 31: adc=0b11101;
	movlw	(01Dh)
	movwf	(??_getADC+0)+0
	movf	(??_getADC+0)+0,w
	movwf	(getADC@adc)
	line	32
;adc.c: 32: break;
	goto	l18674
	line	33
;adc.c: 33: default:
	
l11443:	
	line	34
	
l18666:	
;adc.c: 34: return 0;
	clrf	(?_getADC)
	clrf	(?_getADC+1)
	goto	l11444
	
l18668:	
	goto	l11444
	line	35
	
l18670:	
;adc.c: 35: }
	goto	l18674
	line	19
	
l11437:	
	
l18672:	
	movf	(getADC@adc),w
	; Switch size 1, requested type "space"
; Number of cases is 4, Range of values is 0 to 3
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           13     7 (average)
; direct_byte           14     6 (fixed)
; jumptable            260     6 (fixed)
; rangetable             8     4 (fixed)
; spacedrange           13     6 (fixed)
; locatedrange           4     3 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	0^0	; case 0
	skipnz
	goto	l18658
	xorlw	1^0	; case 1
	skipnz
	goto	l18660
	xorlw	2^1	; case 2
	skipnz
	goto	l18662
	xorlw	3^2	; case 3
	skipnz
	goto	l18664
	goto	l18666
	opt asmopt_on

	line	35
	
l11439:	
	line	38
	
l18674:	
;adc.c: 38: ADCON1=0b11000000;
	movlw	(0C0h)
	movlb 1	; select bank1
	movwf	(158)^080h	;volatile
	line	39
	
l18676:	
;adc.c: 39: adc&=0x1F;
	movlw	(01Fh)
	movwf	(??_getADC+0)+0
	movf	(??_getADC+0)+0,w
	movlb 0	; select bank0
	andwf	(getADC@adc),f
	line	40
	
l18678:	
;adc.c: 40: ADCON0=0x01|(adc<<2);
	movf	(getADC@adc),w
	movwf	(??_getADC+0)+0
	movlw	(02h)-1
u3425:
	lslf	(??_getADC+0)+0,f
	addlw	-1
	skipz
	goto	u3425
	lslf	(??_getADC+0)+0,w
	iorlw	01h
	movlb 1	; select bank1
	movwf	(157)^080h	;volatile
	line	42
	
l18680:	
;adc.c: 42: for(i=0; i<4; i++) asm("nop");
	movlb 0	; select bank0
	clrf	(getADC@i)
	clrf	(getADC@i+1)
	
l18682:	
	movf	(getADC@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(04h))^80h
	subwf	btemp+1,w
	skipz
	goto	u3435
	movlw	low(04h)
	subwf	(getADC@i),w
u3435:

	skipc
	goto	u3431
	goto	u3430
u3431:
	goto	l11445
u3430:
	goto	l11446
	
l18684:	
	goto	l11446
	
l11445:	
# 42 "C:\Users\Filip\Documents\MPLAB\Demo Board\adc.c"
nop ;#
psect	text1327
	
l18686:	
	movlw	low(01h)
	movlb 0	; select bank0
	addwf	(getADC@i),f
	movlw	high(01h)
	addwfc	(getADC@i+1),f
	
l18688:	
	movf	(getADC@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(04h))^80h
	subwf	btemp+1,w
	skipz
	goto	u3445
	movlw	low(04h)
	subwf	(getADC@i),w
u3445:

	skipc
	goto	u3441
	goto	u3440
u3441:
	goto	l11445
u3440:
	
l11446:	
	line	44
;adc.c: 44: ADCON0bits.ADGO=1;
	movlb 1	; select bank1
	bsf	(157)^080h,1	;volatile
	line	45
;adc.c: 45: while(ADCON0bits.ADGO);
	goto	l11447
	
l11448:	
	
l11447:	
	btfsc	(157)^080h,1	;volatile
	goto	u3451
	goto	u3450
u3451:
	goto	l11447
u3450:
	goto	l18690
	
l11449:	
	line	47
	
l18690:	
;adc.c: 47: ADCON0&=0xFE;
	movlw	(0FEh)
	movwf	(??_getADC+0)+0
	movf	(??_getADC+0)+0,w
	andwf	(157)^080h,f	;volatile
	line	48
;adc.c: 48: temp = (ADRESH<<6)|(ADRESL>>2);
	movf	(155)^080h,w	;volatile
	movwf	(??_getADC+0)+0
	movlw	02h
u3465:
	lsrf	(??_getADC+0)+0,f
	decfsz	wreg,f
	goto	u3465
	movf	(156)^080h,w	;volatile
	movwf	(??_getADC+1)+0
	movlw	(06h)-1
u3475:
	lslf	(??_getADC+1)+0,f
	addlw	-1
	skipz
	goto	u3475
	lslf	(??_getADC+1)+0,w
	iorwf	0+(??_getADC+0)+0,w
	movwf	(??_getADC+2)+0
	movf	(??_getADC+2)+0,w
	movlb 0	; select bank0
	movwf	(getADC@temp)
	line	49
	
l18692:	
;adc.c: 49: return temp;
	movf	(getADC@temp),w
	movwf	(??_getADC+0)+0
	clrf	(??_getADC+0)+0+1
	movf	0+(??_getADC+0)+0,w
	movwf	(?_getADC)
	movf	1+(??_getADC+0)+0,w
	movwf	(?_getADC+1)
	goto	l11444
	
l18694:	
	line	50
	
l11444:	
	return
	opt stack 0
GLOBAL	__end_of_getADC
	__end_of_getADC:
;; =============== function _getADC ends ============

	signat	_getADC,4218
	global	_setDAC
psect	text1328,local,class=CODE,delta=2
global __ptext1328
__ptext1328:

;; *************** function _setDAC *****************
;; Defined at:
;;		line 21 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\dac.c"
;; Parameters:    Size  Location     Type
;;  dac             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  dac             1    3[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_I2CDACworker
;;		_SPIDACworker
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1328
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\dac.c"
	line	21
	global	__size_of_setDAC
	__size_of_setDAC	equ	__end_of_setDAC-_setDAC
	
_setDAC:	
	opt	stack 13
; Regs used in _setDAC: [wreg+status,2]
;setDAC@dac stored from wreg
	movwf	(setDAC@dac)
	line	22
	
l18648:	
;dac.c: 22: DACCON1=dac&0x1F;
	movf	(setDAC@dac),w
	andlw	01Fh
	movlb 2	; select bank2
	movwf	(281)^0100h	;volatile
	line	23
	
l13027:	
	return
	opt stack 0
GLOBAL	__end_of_setDAC
	__end_of_setDAC:
;; =============== function _setDAC ends ============

	signat	_setDAC,4216
	global	_enableDAC
psect	text1329,local,class=CODE,delta=2
global __ptext1329
__ptext1329:

;; *************** function _enableDAC *****************
;; Defined at:
;;		line 8 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\dac.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_I2CDACworker
;;		_SPIDACworker
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1329
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\dac.c"
	line	8
	global	__size_of_enableDAC
	__size_of_enableDAC	equ	__end_of_enableDAC-_enableDAC
	
_enableDAC:	
	opt	stack 13
; Regs used in _enableDAC: [wreg]
	line	9
	
l18646:	
;dac.c: 9: DACCON0=0b11100000;
	movlw	(0E0h)
	movlb 2	; select bank2
	movwf	(280)^0100h	;volatile
	line	13
	
l13021:	
	return
	opt stack 0
GLOBAL	__end_of_enableDAC
	__end_of_enableDAC:
;; =============== function _enableDAC ends ============

	signat	_enableDAC,88
	global	_startADC16
psect	text1330,local,class=CODE,delta=2
global __ptext1330
__ptext1330:

;; *************** function _startADC16 *****************
;; Defined at:
;;		line 60 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\adc.c"
;; Parameters:    Size  Location     Type
;;  adc             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  adc             1    6[COMMON] unsigned char 
;;  i               2    4[COMMON] int 
;;  temp            1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  2  3223[COMMON] unsigned int 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, btemp+1
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_I2CADCworker
;; This function uses a non-reentrant model
;;
psect	text1330
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\adc.c"
	line	60
	global	__size_of_startADC16
	__size_of_startADC16	equ	__end_of_startADC16-_startADC16
	
_startADC16:	
	opt	stack 13
; Regs used in _startADC16: [wreg-fsr0h+status,2+status,0+btemp+1]
;startADC16@adc stored from wreg
	movwf	(startADC16@adc)
	line	63
	
l18616:	
;adc.c: 61: unsigned char temp;
;adc.c: 62: int i;
;adc.c: 63: switch (adc)
	goto	l18628
	line	65
;adc.c: 64: {
;adc.c: 65: case 0:
	
l11456:	
	line	66
	
l18618:	
;adc.c: 66: adc=3;
	movlw	(03h)
	movwf	(??_startADC16+0)+0
	movf	(??_startADC16+0)+0,w
	movwf	(startADC16@adc)
	line	67
;adc.c: 67: break;
	goto	l18630
	line	68
;adc.c: 68: case 1:
	
l11458:	
	line	69
	
l18620:	
;adc.c: 69: adc=8;
	movlw	(08h)
	movwf	(??_startADC16+0)+0
	movf	(??_startADC16+0)+0,w
	movwf	(startADC16@adc)
	line	70
;adc.c: 70: break;
	goto	l18630
	line	71
;adc.c: 71: case 2:
	
l11459:	
	line	72
	
l18622:	
;adc.c: 72: adc =9;
	movlw	(09h)
	movwf	(??_startADC16+0)+0
	movf	(??_startADC16+0)+0,w
	movwf	(startADC16@adc)
	line	73
;adc.c: 73: break;
	goto	l18630
	line	74
;adc.c: 74: case 3:
	
l11460:	
	line	75
	
l18624:	
;adc.c: 75: adc=0b11101;
	movlw	(01Dh)
	movwf	(??_startADC16+0)+0
	movf	(??_startADC16+0)+0,w
	movwf	(startADC16@adc)
	line	76
;adc.c: 76: break;
	goto	l18630
	line	77
;adc.c: 77: default:
	
l11461:	
	line	78
;adc.c: 78: return 0;
;	Return value of _startADC16 is never used
	goto	l11462
	line	79
	
l18626:	
;adc.c: 79: }
	goto	l18630
	line	63
	
l11455:	
	
l18628:	
	movf	(startADC16@adc),w
	; Switch size 1, requested type "space"
; Number of cases is 4, Range of values is 0 to 3
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           13     7 (average)
; direct_byte           14     6 (fixed)
; jumptable            260     6 (fixed)
; rangetable             8     4 (fixed)
; spacedrange           13     6 (fixed)
; locatedrange           4     3 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	0^0	; case 0
	skipnz
	goto	l18618
	xorlw	1^0	; case 1
	skipnz
	goto	l18620
	xorlw	2^1	; case 2
	skipnz
	goto	l18622
	xorlw	3^2	; case 3
	skipnz
	goto	l18624
	goto	l11462
	opt asmopt_on

	line	79
	
l11457:	
	line	82
	
l18630:	
;adc.c: 82: ADCON1=0b11000000;
	movlw	(0C0h)
	movlb 1	; select bank1
	movwf	(158)^080h	;volatile
	line	83
	
l18632:	
;adc.c: 83: adc&=0x1F;
	movlw	(01Fh)
	movwf	(??_startADC16+0)+0
	movf	(??_startADC16+0)+0,w
	andwf	(startADC16@adc),f
	line	84
	
l18634:	
;adc.c: 84: ADCON0=0x01|(adc<<2);
	movf	(startADC16@adc),w
	movwf	(??_startADC16+0)+0
	movlw	(02h)-1
u3385:
	lslf	(??_startADC16+0)+0,f
	addlw	-1
	skipz
	goto	u3385
	lslf	(??_startADC16+0)+0,w
	iorlw	01h
	movwf	(157)^080h	;volatile
	line	86
	
l18636:	
;adc.c: 86: for(i=0; i<4; i++) asm("nop");
	clrf	(startADC16@i)
	clrf	(startADC16@i+1)
	
l18638:	
	movf	(startADC16@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(04h))^80h
	subwf	btemp+1,w
	skipz
	goto	u3395
	movlw	low(04h)
	subwf	(startADC16@i),w
u3395:

	skipc
	goto	u3391
	goto	u3390
u3391:
	goto	l11463
u3390:
	goto	l11462
	
l18640:	
	goto	l11462
	
l11463:	
# 86 "C:\Users\Filip\Documents\MPLAB\Demo Board\adc.c"
nop ;#
psect	text1330
	
l18642:	
	movlw	low(01h)
	addwf	(startADC16@i),f
	movlw	high(01h)
	addwfc	(startADC16@i+1),f
	
l18644:	
	movf	(startADC16@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(04h))^80h
	subwf	btemp+1,w
	skipz
	goto	u3405
	movlw	low(04h)
	subwf	(startADC16@i),w
u3405:

	skipc
	goto	u3401
	goto	u3400
u3401:
	goto	l11463
u3400:
	goto	l11462
	
l11464:	
	line	87
	
l11462:	
	return
	opt stack 0
GLOBAL	__end_of_startADC16
	__end_of_startADC16:
;; =============== function _startADC16 ends ============

	signat	_startADC16,4218
	global	_I2CWrite
psect	text1331,local,class=CODE,delta=2
global __ptext1331
__ptext1331:

;; *************** function _I2CWrite *****************
;; Defined at:
;;		line 303 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
;; Parameters:    Size  Location     Type
;;  c               1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  c               1    3[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_I2CADCworker
;;		_I2CDACworker
;; This function uses a non-reentrant model
;;
psect	text1331
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
	line	303
	global	__size_of_I2CWrite
	__size_of_I2CWrite	equ	__end_of_I2CWrite-_I2CWrite
	
_I2CWrite:	
	opt	stack 13
; Regs used in _I2CWrite: [wreg]
;I2CWrite@c stored from wreg
	line	306
	movwf	(I2CWrite@c)
	line	304
;i2c.c: 304: do
	
l3330:	
	line	306
;i2c.c: 305: {
;i2c.c: 306: SSP2CON1bits.WCOL=0;
	movlb 4	; select bank4
	bcf	(541)^0200h,7	;volatile
	line	307
	
l18612:	
;i2c.c: 307: SSP2BUF=c;
	movf	(I2CWrite@c),w
	movwf	(537)^0200h	;volatile
	line	308
	
l18614:	
;i2c.c: 308: } while(SSP2CON1bits.WCOL);
	btfsc	(541)^0200h,7	;volatile
	goto	u3371
	goto	u3370
u3371:
	goto	l3330
u3370:
	
l3331:	
	line	309
;i2c.c: 309: SSP2CON1bits.CKP=1;
	bsf	(541)^0200h,4	;volatile
	line	310
	
l3332:	
	return
	opt stack 0
GLOBAL	__end_of_I2CWrite
	__end_of_I2CWrite:
;; =============== function _I2CWrite ends ============

	signat	_I2CWrite,4216
	global	_enableTS
psect	text1332,local,class=CODE,delta=2
global __ptext1332
__ptext1332:

;; *************** function _enableTS *****************
;; Defined at:
;;		line 54 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\adc.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_I2CADCworker
;; This function uses a non-reentrant model
;;
psect	text1332
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\adc.c"
	line	54
	global	__size_of_enableTS
	__size_of_enableTS	equ	__end_of_enableTS-_enableTS
	
_enableTS:	
	opt	stack 13
; Regs used in _enableTS: [wreg+status,2+status,0]
	line	55
	
l18608:	
;adc.c: 55: FVRCON|=0b00100000;
	movlb 2	; select bank2
	bsf	(279)^0100h+(5/8),(5)&7	;volatile
	line	56
	
l18610:	
;adc.c: 56: FVRCON&=0b11101111;
	movlw	(0EFh)
	movwf	(??_enableTS+0)+0
	movf	(??_enableTS+0)+0,w
	andwf	(279)^0100h,f	;volatile
	line	57
	
l11452:	
	return
	opt stack 0
GLOBAL	__end_of_enableTS
	__end_of_enableTS:
;; =============== function _enableTS ends ============

	signat	_enableTS,88
	global	_EEPROMwrite
psect	text1333,local,class=CODE,delta=2
global __ptext1333
__ptext1333:

;; *************** function _EEPROMwrite *****************
;; Defined at:
;;		line 8 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\eeprom.c"
;; Parameters:    Size  Location     Type
;;  addr            1    wreg     unsigned char 
;;  data            1    7[COMMON] unsigned char 
;; Auto vars:     Size  Location     Type
;;  addr            1    8[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_I2CEEworker
;;		_SPIEEworker
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1333
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\eeprom.c"
	line	8
	global	__size_of_EEPROMwrite
	__size_of_EEPROMwrite	equ	__end_of_EEPROMwrite-_EEPROMwrite
	
_EEPROMwrite:	
	opt	stack 13
; Regs used in _EEPROMwrite: [wreg]
;EEPROMwrite@addr stored from wreg
	movwf	(EEPROMwrite@addr)
	line	9
	
l18594:	
;eeprom.c: 9: EEADRL=addr;
	movf	(EEPROMwrite@addr),w
	movlb 3	; select bank3
	movwf	(401)^0180h	;volatile
	line	10
;eeprom.c: 10: EEDATL=data;
	movf	(EEPROMwrite@data),w
	movwf	(403)^0180h	;volatile
	line	11
	
l18596:	
;eeprom.c: 11: EECON1bits.CFGS=0;
	bcf	(405)^0180h,6	;volatile
	line	12
	
l18598:	
;eeprom.c: 12: EECON1bits.EEPGD=0;
	bcf	(405)^0180h,7	;volatile
	line	13
	
l18600:	
;eeprom.c: 13: EECON1bits.WREN=1;
	bsf	(405)^0180h,2	;volatile
	line	15
	
l18602:	
;eeprom.c: 15: GIE=0;
	bcf	(95/8),(95)&7
	line	16
;eeprom.c: 16: EECON2=0x55;
	movlw	(055h)
	movwf	(406)^0180h	;volatile
	line	17
;eeprom.c: 17: EECON2=0xAA;
	movlw	(0AAh)
	movwf	(406)^0180h	;volatile
	line	18
	
l18604:	
;eeprom.c: 18: EECON1bits.WR=1;
	bsf	(405)^0180h,1	;volatile
	line	19
	
l18606:	
;eeprom.c: 19: GIE=1;
	bsf	(95/8),(95)&7
	line	20
;eeprom.c: 20: while(EECON1bits.WR);
	goto	l9874
	
l9875:	
	
l9874:	
	btfsc	(405)^0180h,1	;volatile
	goto	u3361
	goto	u3360
u3361:
	goto	l9874
u3360:
	goto	l9877
	
l9876:	
	line	21
	
l9877:	
	return
	opt stack 0
GLOBAL	__end_of_EEPROMwrite
	__end_of_EEPROMwrite:
;; =============== function _EEPROMwrite ends ============

	signat	_EEPROMwrite,8312
	global	_initUART
psect	text1334,local,class=CODE,delta=2
global __ptext1334
__ptext1334:

;; *************** function _initUART *****************
;; Defined at:
;;		line 17 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    0        unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_init
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1334
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\uart.c"
	line	17
	global	__size_of_initUART
	__size_of_initUART	equ	__end_of_initUART-_initUART
	
_initUART:	
	opt	stack 13
; Regs used in _initUART: [wreg+status,2]
	line	19
	
l18562:	
;uart.c: 19: APFCON0|=0x04;
	movlb 2	; select bank2
	bsf	(285)^0100h+(2/8),(2)&7	;volatile
	line	20
;uart.c: 20: TRISB5=1;
	movlb 1	; select bank1
	bsf	(1133/8)^080h,(1133)&7
	line	21
;uart.c: 21: TRISC4=0;
	bcf	(1140/8)^080h,(1140)&7
	line	25
;uart.c: 25: BRGH=1;
	movlb 3	; select bank3
	bsf	(3314/8)^0180h,(3314)&7
	line	26
	
l18564:	
;uart.c: 26: SPBRGH=0x00;
	clrf	(412)^0180h	;volatile
	line	27
	
l18566:	
;uart.c: 27: SPBRGL=207;
	movlw	(0CFh)
	movwf	(411)^0180h	;volatile
	line	30
	
l18568:	
;uart.c: 30: SYNC=0;
	bcf	(3316/8)^0180h,(3316)&7
	line	31
	
l18570:	
;uart.c: 31: SPEN=1;
	bsf	(3311/8)^0180h,(3311)&7
	line	32
	
l18572:	
;uart.c: 32: TXEN=1;
	bsf	(3317/8)^0180h,(3317)&7
	line	33
	
l18574:	
;uart.c: 33: CREN=1;
	bsf	(3308/8)^0180h,(3308)&7
	line	48
	
l18576:	
;uart.c: 48: RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	49
	
l6624:	
	return
	opt stack 0
GLOBAL	__end_of_initUART
	__end_of_initUART:
;; =============== function _initUART ends ============

	signat	_initUART,88
	global	_initI2C
psect	text1335,local,class=CODE,delta=2
global __ptext1335
__ptext1335:

;; *************** function _initI2C *****************
;; Defined at:
;;		line 15 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_init
;; This function uses a non-reentrant model
;;
psect	text1335
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\i2c.c"
	line	15
	global	__size_of_initI2C
	__size_of_initI2C	equ	__end_of_initI2C-_initI2C
	
_initI2C:	
	opt	stack 13
; Regs used in _initI2C: [wreg+status,2+status,0]
	line	18
	
l18552:	
;i2c.c: 18: SSP2BUF=0x00;
	movlb 4	; select bank4
	clrf	(537)^0200h	;volatile
	line	19
	
l18554:	
;i2c.c: 19: SSP2STAT=0x80;
	movlw	(080h)
	movwf	(540)^0200h	;volatile
	line	20
	
l18556:	
;i2c.c: 20: SSP2MSK=0xFE;
	movlw	(0FEh)
	movwf	(539)^0200h	;volatile
	line	21
	
l18558:	
;i2c.c: 21: SSP2CON1=0x36;
	movlw	(036h)
	movwf	(541)^0200h	;volatile
	line	22
	
l18560:	
;i2c.c: 22: SSP2CON3|=0b11000000;
	movlw	(0C0h)
	movwf	(??_initI2C+0)+0
	movf	(??_initI2C+0)+0,w
	iorwf	(543)^0200h,f	;volatile
	line	23
	
l3240:	
	return
	opt stack 0
GLOBAL	__end_of_initI2C
	__end_of_initI2C:
;; =============== function _initI2C ends ============

	signat	_initI2C,88
	global	_initSPI
psect	text1336,local,class=CODE,delta=2
global __ptext1336
__ptext1336:

;; *************** function _initSPI *****************
;; Defined at:
;;		line 11 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\spi.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_init
;;		_SPIEEworker
;;		_SPIPWMworker
;;		_SPIDACworker
;;		_SPIADCworker
;;		_SPIworker
;; This function uses a non-reentrant model
;;
psect	text1336
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\spi.c"
	line	11
	global	__size_of_initSPI
	__size_of_initSPI	equ	__end_of_initSPI-_initSPI
	
_initSPI:	
	opt	stack 13
; Regs used in _initSPI: [wreg+status,2]
	line	13
	
l18544:	
;spi.c: 13: TRISCbits.TRISC1 = 0;
	movlb 1	; select bank1
	bcf	(142)^080h,1	;volatile
	line	14
	
l18546:	
;spi.c: 14: SSP2STAT=0x40;
	movlw	(040h)
	movlb 4	; select bank4
	movwf	(540)^0200h	;volatile
	line	15
;spi.c: 15: SSP2CON1=0x24;
	movlw	(024h)
	movwf	(541)^0200h	;volatile
	line	16
	
l18548:	
;spi.c: 16: SSP2CON3=0x00;
	clrf	(543)^0200h	;volatile
	line	18
	
l18550:	
;spi.c: 18: SSP2BUF=0xAA;
	movlw	(0AAh)
	movwf	(537)^0200h	;volatile
	line	20
	
l4911:	
	return
	opt stack 0
GLOBAL	__end_of_initSPI
	__end_of_initSPI:
;; =============== function _initSPI ends ============

	signat	_initSPI,88
	global	_isEE
psect	text1337,local,class=CODE,delta=2
global __ptext1337
__ptext1337:

;; *************** function _isEE *****************
;; Defined at:
;;		line 16 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\easteregg.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1337
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\easteregg.c"
	line	16
	global	__size_of_isEE
	__size_of_isEE	equ	__end_of_isEE-_isEE
	
_isEE:	
	opt	stack 14
; Regs used in _isEE: [wreg]
	line	17
	
l18540:	
;easteregg.c: 17: return 0;
	movlw	(0)
	goto	l8303
	
l18542:	
	line	18
	
l8303:	
	return
	opt stack 0
GLOBAL	__end_of_isEE
	__end_of_isEE:
;; =============== function _isEE ends ============

	signat	_isEE,89
	global	_EEPROMread
psect	text1338,local,class=CODE,delta=2
global __ptext1338
__ptext1338:

;; *************** function _EEPROMread *****************
;; Defined at:
;;		line 24 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\eeprom.c"
;; Parameters:    Size  Location     Type
;;  addr            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  addr            1    3[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;;		_UARTworker
;; This function uses a non-reentrant model
;;
psect	text1338
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\eeprom.c"
	line	24
	global	__size_of_EEPROMread
	__size_of_EEPROMread	equ	__end_of_EEPROMread-_EEPROMread
	
_EEPROMread:	
	opt	stack 13
; Regs used in _EEPROMread: [wreg]
;EEPROMread@addr stored from wreg
	movwf	(EEPROMread@addr)
	line	25
	
l18530:	
;eeprom.c: 25: EEADRL=addr;
	movf	(EEPROMread@addr),w
	movlb 3	; select bank3
	movwf	(401)^0180h	;volatile
	line	26
	
l18532:	
;eeprom.c: 26: EECON1bits.CFGS=0;
	bcf	(405)^0180h,6	;volatile
	line	27
	
l18534:	
;eeprom.c: 27: EECON1bits.EEPGD=0;
	bcf	(405)^0180h,7	;volatile
	line	28
	
l18536:	
;eeprom.c: 28: EECON1bits.RD=1;
	bsf	(405)^0180h,0	;volatile
	line	30
;eeprom.c: 30: return EEDATL;
	movf	(403)^0180h,w	;volatile
	goto	l9880
	
l18538:	
	line	31
	
l9880:	
	return
	opt stack 0
GLOBAL	__end_of_EEPROMread
	__end_of_EEPROMread:
;; =============== function _EEPROMread ends ============

	signat	_EEPROMread,4217
	global	_isr
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:

;; *************** function _isr *****************
;; Defined at:
;;		line 181 in file "C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	intentry
	file	"C:\Users\Filip\Documents\MPLAB\Demo Board\main.c"
	line	181
	global	__size_of_isr
	__size_of_isr	equ	__end_of_isr-_isr
	
_isr:	
	opt	stack 12
; Regs used in _isr: [wreg+fsr1l-status,0]
psect	intentry
	pagesel	$
	movlb 0	; select bank0
	movf	btemp+1,w
	movwf	(??_isr+2)
	line	182
;main.c: 182: do { if(RCIF) { RC3=1;; if(!(RCSTA&0b00000110)) { rhead++; rhead&=(8-1); ringbuff[rhead]=RCREG; } RCIF=0; RC3=0;; } if(TXIF) { TXIF=0; } } while(0);;
	
i1l1652:	
	btfss	(141/8),(141)&7
	goto	u333_21
	goto	u333_20
u333_21:
	goto	i1l18590
u333_20:
	
i1l18578:	
	bsf	(115/8),(115)&7
	
i1l18580:	
	movlb 3	; select bank3
	movf	(413)^0180h,w
	andlw	06h
	btfss	status,2
	goto	u334_21
	goto	u334_20
u334_21:
	goto	i1l18586
u334_20:
	
i1l18582:	
	movlw	(01h)
	movwf	(??_isr+0)+0
	movf	(??_isr+0)+0,w
	movlb 0	; select bank0
	addwf	(_rhead),f	;volatile
	movlw	(07h)
	movwf	(??_isr+0)+0
	movf	(??_isr+0)+0,w
	andwf	(_rhead),f	;volatile
	
i1l18584:	
	movlb 3	; select bank3
	movf	(409)^0180h,w	;volatile
	movwf	(??_isr+0)+0
	clrf	(??_isr+0)+0+1
	movlb 0	; select bank0
	movf	(_rhead),w	;volatile
	addwf	wreg,w
	addlw	_ringbuff&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	0+(??_isr+0)+0,w
	movwi	[0]fsr1
	movf	1+(??_isr+0)+0,w
	movwi	[1]fsr1
	goto	i1l18586
	
i1l1654:	
	
i1l18586:	
	movlb 0	; select bank0
	bcf	(141/8),(141)&7
	
i1l18588:	
	bcf	(115/8),(115)&7
	goto	i1l18590
	
i1l1653:	
	
i1l18590:	
	btfss	(140/8),(140)&7
	goto	u335_21
	goto	u335_20
u335_21:
	goto	i1l1659
u335_20:
	
i1l18592:	
	bcf	(140/8),(140)&7
	goto	i1l1659
	
i1l1655:	
	goto	i1l1659
	
i1l1656:	
	goto	i1l1659
	line	183
;main.c: 183: do { ;} while(0);;
	
i1l1657:	
	goto	i1l1659
	
i1l1658:	
	line	186
	
i1l1659:	
	movf	(??_isr+2),w
	movwf	btemp+1
	retfie
	opt stack 0
GLOBAL	__end_of_isr
	__end_of_isr:
;; =============== function _isr ends ============

	signat	_isr,88
	global	fptotal
fptotal equ 26
	file ""
	line	#
psect	functab,class=CODE,delta=2,reloc=256
global __pfunctab
__pfunctab:
	global	fptable
fptable:
	movlp high(fptable)
	addwf pc
	global	fpbase
fpbase:
	goto fpbase	; Call via a null pointer and you will get stuck here.
	file ""
	line	#
fp__UARTworker:
	ljmp	_UARTworker
	file ""
	line	#
fp__nullfunc1:
	ljmp	_nullfunc1
	file ""
	line	#
fp__SPIPWMworker:
	ljmp	_SPIPWMworker
	file ""
	line	#
fp__I2CPWMworker:
	ljmp	_I2CPWMworker
	file ""
	line	#
fp__SPIEEworker:
	ljmp	_SPIEEworker
	file ""
	line	#
fp__I2CEEworker:
	ljmp	_I2CEEworker
	file ""
	line	#
fp__SPIDACworker:
	ljmp	_SPIDACworker
	file ""
	line	#
fp__I2CDACworker:
	ljmp	_I2CDACworker
	file ""
	line	#
fp__SPIADCworker:
	ljmp	_SPIADCworker
	file ""
	line	#
fp__I2CADCworker:
	ljmp	_I2CADCworker
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
global __pbssBIGRAM
__pbssBIGRAM	equ	8944
	end
