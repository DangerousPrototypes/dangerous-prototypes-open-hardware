opt subtitle "HI-TECH Software Omniscient Code Generator (Lite mode) build 10920"

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
# 21 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	psect config,class=CONFIG,delta=2 ;#
# 21 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	dw 0xFFFC&0xFFE7&0xFFFF&0xFFBF&0xFFFF&0xFFFF&0xFFFF&0xFFFF&0xEFFF&0xFFFF ;#
# 22 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	psect config,class=CONFIG,delta=2 ;#
# 22 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	dw 0xFEFF&0xFFFF&0xDFFF ;#
	FNCALL	_main,_init
	FNCALL	_main,_isEE
	FNCALL	_main,_doEE
	FNCALL	_main,_I2CADCworker
	FNCALL	_main,_UARTworker
	FNCALL	_main,_nullfunc1
	FNCALL	_main,_I2CEEworker
	FNCALL	_main,_I2CDACworker
	FNCALL	_doEE,_teletype
	FNCALL	_teletype,_UARTwrite
	FNCALL	_UARTworker,_UARTread
	FNCALL	_UARTworker,_UARTwrite
	FNCALL	_I2CDACworker,_enableDAC
	FNCALL	_I2CDACworker,_setDAC
	FNCALL	_I2CDACworker,_getADC
	FNCALL	_I2CDACworker,_I2CWrite
	FNCALL	_I2CADCworker,_enableTS
	FNCALL	_I2CADCworker,_getADC
	FNCALL	_I2CADCworker,_I2CWrite
	FNCALL	_I2CEEworker,_EEPROMwrite
	FNCALL	_I2CEEworker,_EEPROMread
	FNCALL	_I2CEEworker,_I2CWrite
	FNCALL	_init,_initSPI
	FNCALL	_init,_initI2C
	FNCALL	_init,_initUART
	FNROOT	_main
	FNCALL	intlevel1,_isr
	global	intlevel1
	FNROOT	intlevel1
	global	_protos
psect	idataBANK0,class=CODE,space=0,delta=2
global __pidataBANK0
__pidataBANK0:
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	line	36

;initializer for _protos
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__UARTworker-fpbase)&0ffh
	retlw	(fp__UARTworker-fpbase)&0ffh
	retlw	(fp__UARTworker-fpbase)&0ffh
	retlw	(fp__UARTworker-fpbase)&0ffh
	retlw	(fp__I2CADCworker-fpbase)&0ffh
	retlw	(fp__I2CDACworker-fpbase)&0ffh
	retlw	(fp__I2CEEworker-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	retlw	(fp__nullfunc1-fpbase)&0ffh
	global	_ringbuff
	global	_mode_device
	global	_mode_protocol
	global	_rhead
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
	global	_CARRY
_CARRY	set	24
	global	_GIE
_GIE	set	95
	global	_RB4
_RB4	set	108
	global	_RB6
_RB6	set	110
	global	_RC0
_RC0	set	112
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
	global	_OSCCON
_OSCCON	set	153
	global	_TRISA
_TRISA	set	140
	global	_TRISB
_TRISB	set	141
	global	_TRISC
_TRISC	set	142
	global	_RCIE
_RCIE	set	1165
	global	_TRISB5
_TRISB5	set	1133
	global	_TRISC4
_TRISC4	set	1140
	global	_TXIE
_TXIE	set	1164
	global	_nWPUEN
_nWPUEN	set	1199
	global	_APFCON0
_APFCON0	set	285
	global	_APFCON1
_APFCON1	set	286
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
psect	strings,class=STRING,delta=2
global __pstrings
__pstrings:
	global    __stringtab
__stringtab:
psect	stringtext,class=STRCODE,delta=2,reloc=256
global __pstringtext
__pstringtext:
	retlw	0
psect	stringtext
	
STR_9:	
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
	
STR_3:	
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
	
STR_5:	
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
	
STR_10:	
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
	
STR_4:	
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
	
STR_2:	
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
	
STR_1:	
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
	
STR_6:	
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
	file	"BP Demoboard v5.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bssCOMMON,class=COMMON,space=1
global __pbssCOMMON
__pbssCOMMON:
_mode_protocol:
       ds      1

_rhead:
       ds      1

_rtail:
       ds      1

psect	bssBANK0,class=BANK0,space=1
global __pbssBANK0
__pbssBANK0:
_ringbuff:
       ds      16

_mode_device:
       ds      1

psect	dataBANK0,class=BANK0,space=1
global __pdataBANK0
__pdataBANK0:
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
_protos:
       ds      16

psect clrtext,class=CODE,delta=2
global clear_ram
;	Called with FSR0 containing the base address, and
;	WREG with the size to clear
clear_ram:
	clrwdt			;clear the watchdog before getting into this loop
clrloop:
	clrf	indf0		;clear RAM location pointed to by FSR
	addfsr	0,1
	decfsz wreg		;Have we reached the end of clearing yet?
	goto clrloop	;have we reached the end yet?
	retlw	0		;all done for this memory range, return
; Clear objects allocated to COMMON
psect cinit,class=CODE,delta=2
	global __pbssCOMMON
	clrf	((__pbssCOMMON)+0)&07Fh
	clrf	((__pbssCOMMON)+1)&07Fh
	clrf	((__pbssCOMMON)+2)&07Fh
; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2
	global __pbssBANK0
	movlw	low(__pbssBANK0)
	movwf	fsr0l
	movlw	high(__pbssBANK0)
	movwf	fsr0h
	movlw	011h
	fcall	clear_ram
psect inittext,class=CODE,delta=2
global init_ram,btemp
init_ram:
	movwf btemp,f
initloop:
	moviw fsr0++
	movwi fsr1++
	decfsz btemp
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
	movlw 010h
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
	global	?_UARTworker
?_UARTworker:	; 0 bytes @ 0x0
	global	?_I2CADCworker
?_I2CADCworker:	; 0 bytes @ 0x0
	global	?_I2CDACworker
?_I2CDACworker:	; 0 bytes @ 0x0
	global	?_I2CEEworker
?_I2CEEworker:	; 0 bytes @ 0x0
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
	global	?_I2CWrite
?_I2CWrite:	; 0 bytes @ 0x0
	global	?_enableTS
?_enableTS:	; 0 bytes @ 0x0
	global	?_enableDAC
?_enableDAC:	; 0 bytes @ 0x0
	global	?_setDAC
?_setDAC:	; 0 bytes @ 0x0
	global	?_UARTwrite
?_UARTwrite:	; 0 bytes @ 0x0
	global	?_isr
?_isr:	; 0 bytes @ 0x0
	global	??_isr
??_isr:	; 0 bytes @ 0x0
	global	?_isEE
?_isEE:	; 1 bytes @ 0x0
	global	?_EEPROMread
?_EEPROMread:	; 1 bytes @ 0x0
	global	?_UARTread
?_UARTread:	; 1 bytes @ 0x0
	global	?_main
?_main:	; 2 bytes @ 0x0
	ds	3
	global	??_nullfunc1
??_nullfunc1:	; 0 bytes @ 0x3
	global	??_isEE
??_isEE:	; 0 bytes @ 0x3
	global	??_initSPI
??_initSPI:	; 0 bytes @ 0x3
	global	??_initI2C
??_initI2C:	; 0 bytes @ 0x3
	global	??_initUART
??_initUART:	; 0 bytes @ 0x3
	global	?_EEPROMwrite
?_EEPROMwrite:	; 0 bytes @ 0x3
	global	??_I2CWrite
??_I2CWrite:	; 0 bytes @ 0x3
	global	??_EEPROMread
??_EEPROMread:	; 0 bytes @ 0x3
	global	??_enableTS
??_enableTS:	; 0 bytes @ 0x3
	global	??_enableDAC
??_enableDAC:	; 0 bytes @ 0x3
	global	??_setDAC
??_setDAC:	; 0 bytes @ 0x3
	global	??_UARTread
??_UARTread:	; 0 bytes @ 0x3
	global	??_UARTwrite
??_UARTwrite:	; 0 bytes @ 0x3
	global	?_getADC
?_getADC:	; 2 bytes @ 0x3
	global	I2CWrite@c
I2CWrite@c:	; 1 bytes @ 0x3
	global	UARTwrite@c
UARTwrite@c:	; 1 bytes @ 0x3
	global	EEPROMwrite@data
EEPROMwrite@data:	; 1 bytes @ 0x3
	global	EEPROMread@addr
EEPROMread@addr:	; 1 bytes @ 0x3
	global	setDAC@dac
setDAC@dac:	; 1 bytes @ 0x3
	ds	1
	global	??_EEPROMwrite
??_EEPROMwrite:	; 0 bytes @ 0x4
	global	?_teletype
?_teletype:	; 0 bytes @ 0x4
	global	initUART@i
initUART@i:	; 1 bytes @ 0x4
	global	UARTread@temp
UARTread@temp:	; 1 bytes @ 0x4
	global	EEPROMwrite@addr
EEPROMwrite@addr:	; 1 bytes @ 0x4
	global	teletype@s
teletype@s:	; 2 bytes @ 0x4
	ds	1
	global	??_UARTworker
??_UARTworker:	; 0 bytes @ 0x5
	global	??_I2CEEworker
??_I2CEEworker:	; 0 bytes @ 0x5
	global	??_init
??_init:	; 0 bytes @ 0x5
	global	getADC@adc
getADC@adc:	; 1 bytes @ 0x5
	ds	1
	global	??_teletype
??_teletype:	; 0 bytes @ 0x6
	global	UARTworker@c
UARTworker@c:	; 1 bytes @ 0x6
	global	teletype@i
teletype@i:	; 2 bytes @ 0x6
	global	getADC@i
getADC@i:	; 2 bytes @ 0x6
	ds	2
	global	??_doEE
??_doEE:	; 0 bytes @ 0x8
psect	cstackBANK0,class=BANK0,space=1
global __pcstackBANK0
__pcstackBANK0:
	global	??_getADC
??_getADC:	; 0 bytes @ 0x0
	global	I2CEEworker@temp
I2CEEworker@temp:	; 1 bytes @ 0x0
	ds	1
	global	I2CEEworker@token
I2CEEworker@token:	; 1 bytes @ 0x1
	ds	1
	global	I2CEEworker@addressed
I2CEEworker@addressed:	; 1 bytes @ 0x2
	ds	1
	global	I2CEEworker@addr
I2CEEworker@addr:	; 1 bytes @ 0x3
	ds	1
	global	??_I2CADCworker
??_I2CADCworker:	; 0 bytes @ 0x4
	global	??_I2CDACworker
??_I2CDACworker:	; 0 bytes @ 0x4
	ds	1
	global	I2CADCworker@temp
I2CADCworker@temp:	; 1 bytes @ 0x5
	global	I2CDACworker@temp
I2CDACworker@temp:	; 1 bytes @ 0x5
	ds	1
	global	I2CADCworker@token
I2CADCworker@token:	; 1 bytes @ 0x6
	global	I2CDACworker@token
I2CDACworker@token:	; 1 bytes @ 0x6
	ds	1
	global	I2CADCworker@adc
I2CADCworker@adc:	; 1 bytes @ 0x7
	global	I2CDACworker@dac
I2CDACworker@dac:	; 1 bytes @ 0x7
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0x8
	ds	1
;;Data sizes: Strings 394, constant 0, data 16, bss 20, persistent 1 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      8      11
;; BANK0           80      9      43
;; BANK1           80      0       0
;; BANK2           80      0       0
;; BANK3           80      0       0
;; BANK4           80      0       0
;; BANK5           80      0       0
;; BANK6           80      0       0
;; BANK7           80      0       0
;; BANK8           80      0       0
;; BANK9           80      0       0
;; BANK10          80      0       0
;; BANK11          80      0       0
;; BANK12          48      0       0

;;
;; Pointer list with targets:

;; ?_getADC	unsigned int  size(1) Largest target is 0
;;
;; teletype@s	PTR const unsigned char  size(2) Largest target is 75
;;		 -> STR_10(CODE[38]), STR_9(CODE[75]), STR_8(CODE[35]), STR_7(CODE[24]), 
;;		 -> STR_6(CODE[24]), STR_5(CODE[39]), STR_4(CODE[37]), STR_3(CODE[57]), 
;;		 -> STR_2(CODE[33]), STR_1(CODE[32]), 
;;
;; S2884_proto$PWMworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> UARTworker(), nullfunc1(), 
;;
;; protos.PWMworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> UARTworker(), nullfunc1(), 
;;
;; S2884_proto$EEPROMworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CEEworker(), UARTworker(), nullfunc1(), 
;;
;; protos.EEPROMworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CEEworker(), UARTworker(), nullfunc1(), 
;;
;; S2884_proto$DACworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CDACworker(), UARTworker(), nullfunc1(), 
;;
;; protos.DACworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CDACworker(), UARTworker(), nullfunc1(), 
;;
;; S2884_proto$ADCworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CADCworker(), UARTworker(), nullfunc1(), 
;;
;; protos.ADCworker	PTR FTN()void  size(1) Largest target is 0
;;		 -> I2CADCworker(), UARTworker(), nullfunc1(), 
;;


;;
;; Critical Paths under _main in COMMON
;;
;;   _doEE->_teletype
;;   _teletype->_UARTwrite
;;   _UARTworker->_UARTread
;;   _I2CDACworker->_getADC
;;   _I2CADCworker->_getADC
;;   _I2CEEworker->_EEPROMwrite
;;   _init->_initUART
;;
;; Critical Paths under _isr in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   _main->_I2CADCworker
;;   _main->_I2CDACworker
;;   _I2CDACworker->_getADC
;;   _I2CADCworker->_getADC
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
;;Main: autosize = 0, tempsize = 1, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 1     1      0    1108
;;                                              8 BANK0      1     1      0
;;                               _init
;;                               _isEE
;;                               _doEE
;;                       _I2CADCworker
;;                         _UARTworker
;;                          _nullfunc1
;;                        _I2CEEworker
;;                       _I2CDACworker
;; ---------------------------------------------------------------------------------
;; (1) _doEE                                                 0     0      0     113
;;                           _teletype
;; ---------------------------------------------------------------------------------
;; (2) _teletype                                             5     3      2     113
;;                                              4 COMMON     4     2      2
;;                          _UARTwrite
;; ---------------------------------------------------------------------------------
;; (1) _UARTworker                                           2     2      0      68
;;                                              5 COMMON     2     2      0
;;                           _UARTread
;;                          _UARTwrite
;; ---------------------------------------------------------------------------------
;; (1) _I2CDACworker                                         4     4      0     300
;;                                              4 BANK0      4     4      0
;;                          _enableDAC
;;                             _setDAC
;;                             _getADC
;;                           _I2CWrite
;; ---------------------------------------------------------------------------------
;; (1) _I2CADCworker                                         4     4      0     244
;;                                              4 BANK0      4     4      0
;;                           _enableTS
;;                             _getADC
;;                           _I2CWrite
;; ---------------------------------------------------------------------------------
;; (1) _I2CEEworker                                          5     5      0     315
;;                                              5 COMMON     1     1      0
;;                                              0 BANK0      4     4      0
;;                        _EEPROMwrite
;;                         _EEPROMread
;;                           _I2CWrite
;; ---------------------------------------------------------------------------------
;; (1) _init                                                 1     1      0      68
;;                                              5 COMMON     1     1      0
;;                            _initSPI
;;                            _initI2C
;;                           _initUART
;; ---------------------------------------------------------------------------------
;; (2) _UARTwrite                                            1     1      0      22
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _UARTread                                             2     2      0      23
;;                                              3 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; (2) _setDAC                                               1     1      0      22
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _enableDAC                                            0     0      0       0
;; ---------------------------------------------------------------------------------
;; (2) _getADC                                               9     7      2     102
;;                                              3 COMMON     5     3      2
;;                                              0 BANK0      4     4      0
;; ---------------------------------------------------------------------------------
;; (2) _enableTS                                             1     1      0       0
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _I2CWrite                                             1     1      0      31
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _EEPROMread                                           1     1      0      31
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _EEPROMwrite                                          2     1      1      62
;;                                              3 COMMON     2     1      1
;; ---------------------------------------------------------------------------------
;; (2) _initUART                                             2     2      0      68
;;                                              3 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; (2) _initI2C                                              1     1      0       0
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _initSPI                                              0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _isEE                                                 0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _nullfunc1                                            0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
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
;;   _isEE
;;   _doEE
;;     _teletype
;;       _UARTwrite
;;   _I2CADCworker
;;     _enableTS
;;     _getADC
;;     _I2CWrite
;;   _UARTworker
;;     _UARTread
;;     _UARTwrite
;;   _nullfunc1
;;   _I2CEEworker
;;     _EEPROMwrite
;;     _EEPROMread
;;     _I2CWrite
;;   _I2CDACworker
;;     _enableDAC
;;     _setDAC
;;     _getADC
;;     _I2CWrite
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
;;COMMON               E      8       B       2       78.6%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;BITSFR2              0      0       0       3        0.0%
;;SFR2                 0      0       0       3        0.0%
;;STACK                0      0       3       3        0.0%
;;BITBANK0            50      0       0       4        0.0%
;;BITSFR3              0      0       0       4        0.0%
;;SFR3                 0      0       0       4        0.0%
;;BANK0               50      9      2B       5       53.8%
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
;;ABS                  0      0      36      20        0.0%
;;BITBANK8            50      0       0      21        0.0%
;;BITSFR20             0      0       0      21        0.0%
;;SFR20                0      0       0      21        0.0%
;;BANK8               50      0       0      22        0.0%
;;BITSFR21             0      0       0      22        0.0%
;;SFR21                0      0       0      22        0.0%
;;BITBANK9            50      0       0      23        0.0%
;;BITSFR22             0      0       0      23        0.0%
;;SFR22                0      0       0      23        0.0%
;;BANK9               50      0       0      24        0.0%
;;BITSFR23             0      0       0      24        0.0%
;;SFR23                0      0       0      24        0.0%
;;BITBANK10           50      0       0      25        0.0%
;;BITSFR24             0      0       0      25        0.0%
;;SFR24                0      0       0      25        0.0%
;;BANK10              50      0       0      26        0.0%
;;BITSFR25             0      0       0      26        0.0%
;;SFR25                0      0       0      26        0.0%
;;BITBANK11           50      0       0      27        0.0%
;;BITSFR26             0      0       0      27        0.0%
;;SFR26                0      0       0      27        0.0%
;;BANK11              50      0       0      28        0.0%
;;BITSFR27             0      0       0      28        0.0%
;;SFR27                0      0       0      28        0.0%
;;BITBANK12           30      0       0      29        0.0%
;;BITSFR28             0      0       0      29        0.0%
;;SFR28                0      0       0      29        0.0%
;;BANK12              30      0       0      30        0.0%
;;BITSFR29             0      0       0      30        0.0%
;;SFR29                0      0       0      30        0.0%
;;BITSFR30             0      0       0      31        0.0%
;;SFR30                0      0       0      31        0.0%
;;DATA                 0      0      39      31        0.0%
;;BITSFR31             0      0       0      32        0.0%
;;SFR31                0      0       0      32        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 69 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  2  1593[COMMON] int 
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr1l, fsr1h, status,2, status,0, btemp+1, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       1       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_init
;;		_isEE
;;		_doEE
;;		_I2CADCworker
;;		_UARTworker
;;		_nullfunc1
;;		_I2CEEworker
;;		_I2CDACworker
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	line	69
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 12
; Regs used in _main: [allreg]
	line	70
	
l14608:	
;main.c: 70: mode=0x02;
	movlw	(02h)
	movlb 0	; select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_mode)
	line	72
	
l14610:	
;main.c: 72: init();
	fcall	_init
	goto	l14612
	line	74
;main.c: 74: while(1){
	
l1594:	
	line	76
	
l14612:	
;main.c: 76: if(isEE()) doEE();
	fcall	_isEE
	xorlw	0&0ffh
	skipnz
	goto	u2931
	goto	u2930
u2931:
	goto	l14626
u2930:
	
l14614:	
	fcall	_doEE
	goto	l14626
	
l1595:	
	line	79
;main.c: 79: switch(mode_device)
	goto	l14626
	line	80
;main.c: 80: { case 0x03: protos[mode_protocol].ADCworker();
	
l1597:	
	
l14616:	
	movf	(_mode_protocol),w
	movlb 0	; select bank0
	movwf	(??_main+0)+0
	movlw	(02h)-1
u2945:
	lslf	(??_main+0)+0,f
	addlw	-1
	skipz
	goto	u2945
	lslf	(??_main+0)+0,w
	addlw	_protos&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	fcall	fptable
	line	81
;main.c: 81: break;
	goto	l14612
	line	82
;main.c: 82: case 0x01: protos[mode_protocol].EEPROMworker();
	
l1599:	
	
l14618:	
	movf	(_mode_protocol),w
	movlb 0	; select bank0
	movwf	(??_main+0)+0
	movlw	(02h)-1
u2955:
	lslf	(??_main+0)+0,f
	addlw	-1
	skipz
	goto	u2955
	lslf	(??_main+0)+0,w
	addlw	02h
	addlw	_protos&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	fcall	fptable
	line	83
;main.c: 83: break;
	goto	l14612
	line	84
;main.c: 84: case 0x02: protos[mode_protocol].DACworker();
	
l1600:	
	
l14620:	
	movf	(_mode_protocol),w
	movlb 0	; select bank0
	movwf	(??_main+0)+0
	movlw	(02h)-1
u2965:
	lslf	(??_main+0)+0,f
	addlw	-1
	skipz
	goto	u2965
	lslf	(??_main+0)+0,w
	addlw	01h
	addlw	_protos&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	fcall	fptable
	line	85
;main.c: 85: break;
	goto	l14612
	line	86
;main.c: 86: case 0x00: protos[mode_protocol].PWMworker();
	
l1601:	
	
l14622:	
	movf	(_mode_protocol),w
	movlb 0	; select bank0
	movwf	(??_main+0)+0
	movlw	(02h)-1
u2975:
	lslf	(??_main+0)+0,f
	addlw	-1
	skipz
	goto	u2975
	lslf	(??_main+0)+0,w
	addlw	03h
	addlw	_protos&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	fcall	fptable
	goto	l14612
	line	87
;main.c: 87: default: break;
	
l1602:	
	goto	l14612
	line	88
	
l14624:	
;main.c: 88: }
	goto	l14612
	line	79
	
l1596:	
	
l14626:	
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
	goto	l14622
	xorlw	1^0	; case 1
	skipnz
	goto	l14618
	xorlw	2^1	; case 2
	skipnz
	goto	l14620
	xorlw	3^2	; case 3
	skipnz
	goto	l14616
	goto	l14612
	opt asmopt_on

	line	88
	
l1598:	
	goto	l14612
	line	89
	
l1603:	
	line	74
	goto	l14612
	
l1604:	
	line	91
	
l1605:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,90
	global	_doEE
psect	text729,local,class=CODE,delta=2
global __ptext729
__ptext729:

;; *************** function _doEE *****************
;; Defined at:
;;		line 21 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
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
psect	text729
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
	line	21
	global	__size_of_doEE
	__size_of_doEE	equ	__end_of_doEE-_doEE
	
_doEE:	
	opt	stack 12
; Regs used in _doEE: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	line	22
	
l14428:	
;easteregg.c: 22: teletype("Hello, nice of you to drop by\r\n");
	movlw	low(STR_1|8000h)
	movwf	(?_teletype)
	movlw	high(STR_1|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	23
;easteregg.c: 23: teletype("I'm happy to tell you my story\r\n");
	movlw	low(STR_2|8000h)
	movwf	(?_teletype)
	movlw	high(STR_2|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	24
;easteregg.c: 24: teletype("They put me through endless hours of regression test..\r\n");
	movlw	low(STR_3|8000h)
	movwf	(?_teletype)
	movlw	high(STR_3|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	25
;easteregg.c: 25: teletype(".. conducted several tests on me..\r\n");
	movlw	low(STR_4|8000h)
	movwf	(?_teletype)
	movlw	high(STR_4|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	26
;easteregg.c: 26: teletype(".connected me to weird prototypes...\r\n");
	movlw	low(STR_5|8000h)
	movwf	(?_teletype)
	movlw	high(STR_5|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	27
;easteregg.c: 27: teletype("abused me with 5V....\r\n");
	movlw	low(STR_6|8000h)
	movwf	(?_teletype)
	movlw	high(STR_6|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	28
;easteregg.c: 28: teletype("used HiZ on me.......\r\n");
	movlw	low(STR_7|8000h)
	movwf	(?_teletype)
	movlw	high(STR_7|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	29
;easteregg.c: 29: teletype("let me talk I2C, SPI, UART......\r\n");
	movlw	low(STR_8|8000h)
	movwf	(?_teletype)
	movlw	high(STR_8|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	30
;easteregg.c: 30: teletype("made me do weird shit like PWM, memoryemulation, convert high voltages..\r\n");
	movlw	low(STR_9|8000h)
	movwf	(?_teletype)
	movlw	high(STR_9|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	line	31
;easteregg.c: 31: teletype("COULD YOU PLEASE LEAVE ME ALONE?!?!?!");
	movlw	low(STR_10|8000h)
	movwf	(?_teletype)
	movlw	high(STR_10|8000h)
	movwf	((?_teletype))+1
	fcall	_teletype
	goto	l6406
	line	32
;easteregg.c: 32: while(1);
	
l6405:	
	
l6406:	
	goto	l6406
	
l6407:	
	line	33
	
l6408:	
	return
	opt stack 0
GLOBAL	__end_of_doEE
	__end_of_doEE:
;; =============== function _doEE ends ============

	signat	_doEE,88
	global	_teletype
psect	text730,local,class=CODE,delta=2
global __ptext730
__ptext730:

;; *************** function _teletype *****************
;; Defined at:
;;		line 36 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
;; Parameters:    Size  Location     Type
;;  s               2    4[COMMON] PTR const unsigned char 
;;		 -> STR_10(38), STR_9(75), STR_8(35), STR_7(24), 
;;		 -> STR_6(24), STR_5(39), STR_4(37), STR_3(57), 
;;		 -> STR_2(33), STR_1(32), 
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
psect	text730
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
	line	36
	global	__size_of_teletype
	__size_of_teletype	equ	__end_of_teletype-_teletype
	
_teletype:	
	opt	stack 12
; Regs used in _teletype: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	line	39
	
l14410:	
;easteregg.c: 37: char c;
;easteregg.c: 39: while(*s)
	goto	l14426
	
l6412:	
	line	41
	
l14412:	
;easteregg.c: 40: {
;easteregg.c: 41: UARTwrite(*(s++));
	movf	(teletype@s),w
	movwf	fsr0l
	movf	((teletype@s+1)),w
	movwf	fsr0h
	movf	indf0,w ;code access
	fcall	_UARTwrite
	
l14414:	
	movlw	low(01h)
	addwf	(teletype@s),f
	movlw	high(01h)
	addwfc	(teletype@s+1),f
	line	43
	
l14416:	
;easteregg.c: 43: for(i=0; i<10000; i++) asm("nop");
	clrf	(teletype@i)
	clrf	(teletype@i+1)
	
l14418:	
	movf	(teletype@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(02710h))^80h
	subwf	btemp+1,w
	skipz
	goto	u2695
	movlw	low(02710h)
	subwf	(teletype@i),w
u2695:

	skipc
	goto	u2691
	goto	u2690
u2691:
	goto	l6413
u2690:
	goto	l14426
	
l14420:	
	goto	l14426
	
l6413:	
# 43 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
nop ;#
psect	text730
	
l14422:	
	movlw	low(01h)
	addwf	(teletype@i),f
	movlw	high(01h)
	addwfc	(teletype@i+1),f
	
l14424:	
	movf	(teletype@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(02710h))^80h
	subwf	btemp+1,w
	skipz
	goto	u2705
	movlw	low(02710h)
	subwf	(teletype@i),w
u2705:

	skipc
	goto	u2701
	goto	u2700
u2701:
	goto	l6413
u2700:
	goto	l14426
	
l6414:	
	goto	l14426
	line	44
	
l6411:	
	line	39
	
l14426:	
	movf	(teletype@s),w
	movwf	fsr0l
	movf	((teletype@s+1)),w
	movwf	fsr0h
	movf	indf0,w ;code access
	iorlw	0
	skipz
	goto	u2711
	goto	u2710
u2711:
	goto	l14412
u2710:
	goto	l6416
	
l6415:	
	line	45
	
l6416:	
	return
	opt stack 0
GLOBAL	__end_of_teletype
	__end_of_teletype:
;; =============== function _teletype ends ============

	signat	_teletype,4216
	global	_UARTworker
	global	_nullfunc1
	global	_I2CADCworker
psect	text731,local,class=CODE,delta=2
global __ptext731
__ptext731:

;; *************** function _I2CADCworker *****************
;; Defined at:
;;		line 87 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  adc             1    7[BANK0 ] unsigned char 
;;  token           1    6[BANK0 ] unsigned char 
;;  temp            1    5[BANK0 ] unsigned char 
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
;;      Locals:         0       3       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       1       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       4       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_enableTS
;;		_getADC
;;		_I2CWrite
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text731
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
	line	87
	global	__size_of_I2CADCworker
	__size_of_I2CADCworker	equ	__end_of_I2CADCworker-_I2CADCworker
	
_I2CADCworker:	
	opt	stack 13
; Regs used in _I2CADCworker: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	line	89
	
l14542:	
;i2c.c: 89: adc=0x00;
	movlb 0	; select bank0
	clrf	(I2CADCworker@adc)
	line	90
	
l14544:	
;i2c.c: 90: enableTS();
	fcall	_enableTS
	line	91
	
l14546:	
;i2c.c: 91: SSP2ADD=0x10;
	movlw	(010h)
	movlb 4	; select bank4
	movwf	(538)^0200h	;volatile
	goto	l14548
	line	93
;i2c.c: 93: while(1)
	
l3217:	
	line	96
	
l14548:	
;i2c.c: 94: {
;i2c.c: 96: if(SSP2IF)
	movlb 0	; select bank0
	btfss	(160/8),(160)&7
	goto	u2871
	goto	u2870
u2871:
	goto	l14548
u2870:
	line	98
	
l14550:	
;i2c.c: 97: {
;i2c.c: 98: token=SSP2STAT&0x25;
	movlb 4	; select bank4
	movf	(540)^0200h,w
	andlw	025h
	movlb 0	; select bank0
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movwf	(I2CADCworker@token)
	line	100
	
l14552:	
;i2c.c: 100: if(SSP2STATbits.S)
	movlb 4	; select bank4
	btfss	(540)^0200h,3	;volatile
	goto	u2881
	goto	u2880
u2881:
	goto	l3219
u2880:
	line	101
	
l14554:	
;i2c.c: 101: { RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	102
;i2c.c: 102: switch(token)
	goto	l14570
	line	104
;i2c.c: 103: {
;i2c.c: 104: case 0x01:
	
l3221:	
	line	105
	
l14556:	
;i2c.c: 105: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movwf	(I2CADCworker@temp)
	line	106
;i2c.c: 106: break;
	goto	l3226
	line	107
;i2c.c: 107: case 0x21:
	
l3223:	
	line	108
	
l14558:	
;i2c.c: 108: adc=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movwf	(I2CADCworker@adc)
	line	109
;i2c.c: 109: break;
	goto	l3226
	line	110
;i2c.c: 110: case 0x05:
	
l3224:	
	line	111
	
l14560:	
;i2c.c: 111: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movwf	(I2CADCworker@temp)
	line	112
	
l14562:	
;i2c.c: 112: I2CWrite(getADC(adc));
	movf	(I2CADCworker@adc),w
	fcall	_getADC
	movf	(0+(?_getADC)),w
	fcall	_I2CWrite
	line	113
;i2c.c: 113: break;
	goto	l3226
	line	114
;i2c.c: 114: case 0x24:
	
l3225:	
	line	115
	
l14564:	
;i2c.c: 115: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CADCworker+0)+0
	movf	(??_I2CADCworker+0)+0,w
	movwf	(I2CADCworker@temp)
	line	116
	
l14566:	
;i2c.c: 116: I2CWrite(getADC(adc));
	movf	(I2CADCworker@adc),w
	fcall	_getADC
	movf	(0+(?_getADC)),w
	fcall	_I2CWrite
	line	117
;i2c.c: 117: break;
	goto	l3226
	line	118
	
l14568:	
;i2c.c: 118: }
	goto	l3226
	line	102
	
l3220:	
	
l14570:	
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
	goto	l14556
	xorlw	5^1	; case 5
	skipnz
	goto	l14560
	xorlw	33^5	; case 33
	skipnz
	goto	l14558
	xorlw	36^33	; case 36
	skipnz
	goto	l14564
	goto	l3226
	opt asmopt_on

	line	118
	
l3222:	
	line	119
;i2c.c: 119: }
	goto	l3226
	line	120
	
l3219:	
;i2c.c: 120: else if(SSP2STATbits.P)
	btfss	(540)^0200h,4	;volatile
	goto	u2891
	goto	u2890
u2891:
	goto	l3226
u2890:
	line	121
	
l14572:	
;i2c.c: 121: { RC5=0;;
	movlb 0	; select bank0
	bcf	(117/8),(117)&7
	line	122
# 122 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
NOP ;#
psect	text731
	goto	l3226
	line	123
	
l3227:	
	line	124
	
l3226:	
;i2c.c: 123: }
;i2c.c: 124: SSP2IF=0;
	movlb 0	; select bank0
	bcf	(160/8),(160)&7
	line	125
;i2c.c: 125: SSP2CON1bits.SSPEN=1;
	movlb 4	; select bank4
	bsf	(541)^0200h,5	;volatile
	line	126
;i2c.c: 126: SSP2CON1bits.CKP=1;
	bsf	(541)^0200h,4	;volatile
	goto	l14548
	line	127
	
l3218:	
	goto	l14548
	line	128
	
l3228:	
	line	93
	goto	l14548
	
l3229:	
	line	129
	
l3230:	
	return
	opt stack 0
GLOBAL	__end_of_I2CADCworker
	__end_of_I2CADCworker:
;; =============== function _I2CADCworker ends ============

	signat	_I2CADCworker,88
	global	_I2CDACworker
psect	text732,local,class=CODE,delta=2
global __ptext732
__ptext732:

;; *************** function _I2CDACworker *****************
;; Defined at:
;;		line 134 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  dac             1    7[BANK0 ] unsigned char 
;;  token           1    6[BANK0 ] unsigned char 
;;  temp            1    5[BANK0 ] unsigned char 
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
;;      Locals:         0       3       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       1       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       4       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_enableDAC
;;		_setDAC
;;		_getADC
;;		_I2CWrite
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text732
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
	line	134
	global	__size_of_I2CDACworker
	__size_of_I2CDACworker	equ	__end_of_I2CDACworker-_I2CDACworker
	
_I2CDACworker:	
	opt	stack 13
; Regs used in _I2CDACworker: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	line	136
	
l14574:	
;i2c.c: 136: dac=0x00;
	movlb 0	; select bank0
	clrf	(I2CDACworker@dac)
	line	137
	
l14576:	
;i2c.c: 137: enableDAC();
	fcall	_enableDAC
	line	138
	
l14578:	
;i2c.c: 138: SSP2ADD=0x20;
	movlw	(020h)
	movlb 4	; select bank4
	movwf	(538)^0200h	;volatile
	goto	l14580
	line	140
;i2c.c: 140: while(1)
	
l3233:	
	line	143
	
l14580:	
;i2c.c: 141: {
;i2c.c: 143: if(SSP2IF)
	movlb 0	; select bank0
	btfss	(160/8),(160)&7
	goto	u2901
	goto	u2900
u2901:
	goto	l14580
u2900:
	line	145
	
l14582:	
;i2c.c: 144: {
;i2c.c: 145: token=SSP2STAT&0x25;
	movlb 4	; select bank4
	movf	(540)^0200h,w
	andlw	025h
	movlb 0	; select bank0
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@token)
	line	147
	
l14584:	
;i2c.c: 147: if(SSP2STATbits.S)
	movlb 4	; select bank4
	btfss	(540)^0200h,3	;volatile
	goto	u2911
	goto	u2910
u2911:
	goto	l3235
u2910:
	line	148
	
l14586:	
;i2c.c: 148: { RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	149
;i2c.c: 149: switch(token)
	goto	l14604
	line	151
;i2c.c: 150: {
;i2c.c: 151: case 0x01:
	
l3237:	
	line	152
	
l14588:	
;i2c.c: 152: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@temp)
	line	153
;i2c.c: 153: break;
	goto	l3242
	line	154
;i2c.c: 154: case 0x21:
	
l3239:	
	line	155
	
l14590:	
;i2c.c: 155: dac=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@dac)
	line	156
;i2c.c: 156: dac>>=3;
	clrc
	rrf	(I2CDACworker@dac),f
	clrc
	rrf	(I2CDACworker@dac),f
	clrc
	rrf	(I2CDACworker@dac),f

	line	157
	
l14592:	
;i2c.c: 157: setDAC(dac);
	movf	(I2CDACworker@dac),w
	fcall	_setDAC
	line	158
;i2c.c: 158: break;
	goto	l3242
	line	159
;i2c.c: 159: case 0x05:
	
l3240:	
	line	160
	
l14594:	
;i2c.c: 160: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@temp)
	line	161
	
l14596:	
;i2c.c: 161: I2CWrite(getADC(dac));
	movf	(I2CDACworker@dac),w
	fcall	_getADC
	movf	(0+(?_getADC)),w
	fcall	_I2CWrite
	line	162
;i2c.c: 162: break;
	goto	l3242
	line	163
;i2c.c: 163: case 0x24:
	
l3241:	
	line	164
	
l14598:	
;i2c.c: 164: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2CDACworker+0)+0
	movf	(??_I2CDACworker+0)+0,w
	movwf	(I2CDACworker@temp)
	line	165
	
l14600:	
;i2c.c: 165: I2CWrite(getADC(dac));
	movf	(I2CDACworker@dac),w
	fcall	_getADC
	movf	(0+(?_getADC)),w
	fcall	_I2CWrite
	line	166
;i2c.c: 166: break;
	goto	l3242
	line	167
	
l14602:	
;i2c.c: 167: }
	goto	l3242
	line	149
	
l3236:	
	
l14604:	
	movlb 0	; select bank0
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
	goto	l14588
	xorlw	5^1	; case 5
	skipnz
	goto	l14594
	xorlw	33^5	; case 33
	skipnz
	goto	l14590
	xorlw	36^33	; case 36
	skipnz
	goto	l14598
	goto	l3242
	opt asmopt_on

	line	167
	
l3238:	
	line	168
;i2c.c: 168: }
	goto	l3242
	line	169
	
l3235:	
;i2c.c: 169: else if(SSP2STATbits.P)
	btfss	(540)^0200h,4	;volatile
	goto	u2921
	goto	u2920
u2921:
	goto	l3242
u2920:
	line	170
	
l14606:	
;i2c.c: 170: { RC5=0;;
	movlb 0	; select bank0
	bcf	(117/8),(117)&7
	line	171
# 171 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
NOP ;#
psect	text732
	goto	l3242
	line	172
	
l3243:	
	line	173
	
l3242:	
;i2c.c: 172: }
;i2c.c: 173: SSP2IF=0;
	movlb 0	; select bank0
	bcf	(160/8),(160)&7
	line	174
;i2c.c: 174: SSP2CON1bits.SSPEN=1;
	movlb 4	; select bank4
	bsf	(541)^0200h,5	;volatile
	line	175
;i2c.c: 175: SSP2CON1bits.CKP=1;
	bsf	(541)^0200h,4	;volatile
	goto	l14580
	line	176
	
l3234:	
	goto	l14580
	line	177
	
l3244:	
	line	140
	goto	l14580
	
l3245:	
	line	178
	
l3246:	
	return
	opt stack 0
GLOBAL	__end_of_I2CDACworker
	__end_of_I2CDACworker:
;; =============== function _I2CDACworker ends ============

	signat	_I2CDACworker,88
	global	_I2CEEworker
psect	text733,local,class=CODE,delta=2
global __ptext733
__ptext733:

;; *************** function _I2CEEworker *****************
;; Defined at:
;;		line 29 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  addr            1    3[BANK0 ] unsigned char 
;;  addressed       1    2[BANK0 ] unsigned char 
;;  token           1    1[BANK0 ] unsigned char 
;;  temp            1    0[BANK0 ] unsigned char 
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
;;      Locals:         0       4       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       4       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_EEPROMwrite
;;		_EEPROMread
;;		_I2CWrite
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text733
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
	line	29
	global	__size_of_I2CEEworker
	__size_of_I2CEEworker	equ	__end_of_I2CEEworker-_I2CEEworker
	
_I2CEEworker:	
	opt	stack 13
; Regs used in _I2CEEworker: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	31
	
l14500:	
;i2c.c: 31: addr=0x00;
	movlb 0	; select bank0
	clrf	(I2CEEworker@addr)
	line	32
;i2c.c: 32: addressed=0;
	clrf	(I2CEEworker@addressed)
	line	34
	
l14502:	
;i2c.c: 34: SSP2ADD=0xA0;
	movlw	(0A0h)
	movlb 4	; select bank4
	movwf	(538)^0200h	;volatile
	goto	l14504
	line	36
;i2c.c: 36: while(1)
	
l3199:	
	line	39
	
l14504:	
;i2c.c: 37: {
;i2c.c: 39: if(SSP2IF)
	movlb 0	; select bank0
	btfss	(160/8),(160)&7
	goto	u2831
	goto	u2830
u2831:
	goto	l14504
u2830:
	line	41
	
l14506:	
;i2c.c: 40: {
;i2c.c: 41: token=SSP2STAT&0x25;
	movlb 4	; select bank4
	movf	(540)^0200h,w
	andlw	025h
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CEEworker@token)
	line	43
	
l14508:	
;i2c.c: 43: if(SSP2STATbits.S)
	movlb 4	; select bank4
	btfss	(540)^0200h,3	;volatile
	goto	u2841
	goto	u2840
u2841:
	goto	l3201
u2840:
	line	44
	
l14510:	
;i2c.c: 44: { RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	45
;i2c.c: 45: switch(token)
	goto	l14538
	line	47
;i2c.c: 46: {
;i2c.c: 47: case 0x01:
	
l3203:	
	line	48
	
l14512:	
;i2c.c: 48: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CEEworker@temp)
	line	49
;i2c.c: 49: break;
	goto	l3210
	line	50
;i2c.c: 50: case 0x21:
	
l3205:	
	line	51
	
l14514:	
;i2c.c: 51: if(!addressed)
	movf	(I2CEEworker@addressed),f
	skipz
	goto	u2851
	goto	u2850
u2851:
	goto	l14520
u2850:
	line	52
	
l14516:	
;i2c.c: 52: { addr=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CEEworker@addr)
	line	53
	
l14518:	
;i2c.c: 53: addressed=1;
	clrf	(I2CEEworker@addressed)
	bsf	status,0
	rlf	(I2CEEworker@addressed),f
	line	54
;i2c.c: 54: }
	goto	l3210
	line	55
	
l3206:	
	line	57
	
l14520:	
;i2c.c: 55: else
;i2c.c: 56: {
;i2c.c: 57: EEPROMwrite(addr, SSP2BUF);
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movwf	(?_EEPROMwrite)
	movlb 0	; select bank0
	movf	(I2CEEworker@addr),w
	fcall	_EEPROMwrite
	line	58
	
l14522:	
;i2c.c: 58: addr++;
	movlw	(01h)
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movlb 0	; select bank0
	addwf	(I2CEEworker@addr),f
	goto	l3210
	line	59
	
l3207:	
	line	61
;i2c.c: 59: }
;i2c.c: 61: break;
	goto	l3210
	line	62
;i2c.c: 62: case 0x05:
	
l3208:	
	line	63
	
l14524:	
;i2c.c: 63: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CEEworker@temp)
	line	64
	
l14526:	
;i2c.c: 64: I2CWrite(EEPROMread(addr++));
	movf	(I2CEEworker@addr),w
	fcall	_EEPROMread
	fcall	_I2CWrite
	
l14528:	
	movlw	(01h)
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movlb 0	; select bank0
	addwf	(I2CEEworker@addr),f
	line	65
;i2c.c: 65: break;
	goto	l3210
	line	66
;i2c.c: 66: case 0x24:
	
l3209:	
	line	67
	
l14530:	
;i2c.c: 67: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movlb 0	; select bank0
	movwf	(I2CEEworker@temp)
	line	68
	
l14532:	
;i2c.c: 68: I2CWrite(EEPROMread(addr++));
	movf	(I2CEEworker@addr),w
	fcall	_EEPROMread
	fcall	_I2CWrite
	
l14534:	
	movlw	(01h)
	movwf	(??_I2CEEworker+0)+0
	movf	(??_I2CEEworker+0)+0,w
	movlb 0	; select bank0
	addwf	(I2CEEworker@addr),f
	line	69
;i2c.c: 69: break;
	goto	l3210
	line	70
	
l14536:	
;i2c.c: 70: }
	goto	l3210
	line	45
	
l3202:	
	
l14538:	
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
	goto	l14512
	xorlw	5^1	; case 5
	skipnz
	goto	l14524
	xorlw	33^5	; case 33
	skipnz
	goto	l14514
	xorlw	36^33	; case 36
	skipnz
	goto	l14530
	goto	l3210
	opt asmopt_on

	line	70
	
l3204:	
	line	71
;i2c.c: 71: }
	goto	l3210
	line	72
	
l3201:	
;i2c.c: 72: else if(SSP2STATbits.P)
	btfss	(540)^0200h,4	;volatile
	goto	u2861
	goto	u2860
u2861:
	goto	l3210
u2860:
	line	73
	
l14540:	
;i2c.c: 73: { RC5=0;;
	movlb 0	; select bank0
	bcf	(117/8),(117)&7
	line	74
;i2c.c: 74: addressed=0;
	clrf	(I2CEEworker@addressed)
	line	75
# 75 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
NOP ;#
psect	text733
	goto	l3210
	line	76
	
l3211:	
	line	77
	
l3210:	
;i2c.c: 76: }
;i2c.c: 77: SSP2IF=0;
	movlb 0	; select bank0
	bcf	(160/8),(160)&7
	line	78
;i2c.c: 78: SSP2CON1bits.SSPEN=1;
	movlb 4	; select bank4
	bsf	(541)^0200h,5	;volatile
	line	79
;i2c.c: 79: SSP2CON1bits.CKP=1;
	bsf	(541)^0200h,4	;volatile
	goto	l14504
	line	80
	
l3200:	
	goto	l14504
	line	81
	
l3212:	
	line	36
	goto	l14504
	
l3213:	
	line	82
	
l3214:	
	return
	opt stack 0
GLOBAL	__end_of_I2CEEworker
	__end_of_I2CEEworker:
;; =============== function _I2CEEworker ends ============

	signat	_I2CEEworker,88
psect	text734,local,class=CODE,delta=2
global __ptext734
__ptext734:

;; *************** function _nullfunc1 *****************
;; Defined at:
;;		line 66 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
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
psect	text734
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	line	66
	global	__size_of_nullfunc1
	__size_of_nullfunc1	equ	__end_of_nullfunc1-_nullfunc1
	
_nullfunc1:	
	opt	stack 14
; Regs used in _nullfunc1: []
	
l1591:	
	return
	opt stack 0
GLOBAL	__end_of_nullfunc1
	__end_of_nullfunc1:
;; =============== function _nullfunc1 ends ============

	signat	_nullfunc1,88
psect	text735,local,class=CODE,delta=2
global __ptext735
__ptext735:

;; *************** function _UARTworker *****************
;; Defined at:
;;		line 47 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  c               1    6[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0, pclath, cstack
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
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_UARTread
;;		_UARTwrite
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text735
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
	line	47
	global	__size_of_UARTworker
	__size_of_UARTworker	equ	__end_of_UARTworker-_UARTworker
	
_UARTworker:	
	opt	stack 13
; Regs used in _UARTworker: [wreg+fsr1l-status,0+pclath+cstack]
	line	50
	
l14406:	
;uart.c: 48: unsigned char c;
;uart.c: 50: c=UARTread();
	fcall	_UARTread
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@c)
	line	51
	
l14408:	
;uart.c: 51: UARTwrite(c);
	movf	(UARTworker@c),w
	fcall	_UARTwrite
	line	52
	
l4829:	
	return
	opt stack 0
GLOBAL	__end_of_UARTworker
	__end_of_UARTworker:
;; =============== function _UARTworker ends ============

	signat	_UARTworker,88
	global	_init
psect	text736,local,class=CODE,delta=2
global __ptext736
__ptext736:

;; *************** function _init *****************
;; Defined at:
;;		line 95 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
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
psect	text736
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	line	95
	global	__size_of_init
	__size_of_init	equ	__end_of_init-_init
	
_init:	
	opt	stack 13
; Regs used in _init: [wreg-status,0+pclath+cstack]
	line	96
	
l14252:	
;main.c: 96: OSCCON=0xEA;
	movlw	(0EAh)
	movlb 1	; select bank1
	movwf	(153)^080h	;volatile
	line	100
	
l14254:	
;main.c: 100: PORTA=0x00;
	movlb 0	; select bank0
	clrf	(12)	;volatile
	line	101
	
l14256:	
;main.c: 101: LATA=0x00;
	movlb 2	; select bank2
	clrf	(268)^0100h	;volatile
	line	102
	
l14258:	
;main.c: 102: ANSELA=0x00;
	movlb 3	; select bank3
	clrf	(396)^0180h	;volatile
	line	103
	
l14260:	
;main.c: 103: TRISA=0xFF;
	movlw	(0FFh)
	movlb 1	; select bank1
	movwf	(140)^080h	;volatile
	line	104
;main.c: 104: WPUA=0x00;
	movlb 4	; select bank4
	clrf	(524)^0200h	;volatile
	line	107
;main.c: 107: PORTB=0x00;
	movlb 0	; select bank0
	clrf	(13)	;volatile
	line	108
;main.c: 108: LATB=0x00;
	movlb 2	; select bank2
	clrf	(269)^0100h	;volatile
	line	109
;main.c: 109: ANSELB=0x00;
	movlb 3	; select bank3
	clrf	(397)^0180h	;volatile
	line	110
	
l14262:	
;main.c: 110: TRISB=0xFF;
	movlw	(0FFh)
	movlb 1	; select bank1
	movwf	(141)^080h	;volatile
	line	111
	
l14264:	
;main.c: 111: WPUB=0x50;
	movlw	(050h)
	movlb 4	; select bank4
	movwf	(525)^0200h	;volatile
	line	114
;main.c: 114: PORTC=0x00;
	movlb 0	; select bank0
	clrf	(14)	;volatile
	line	115
;main.c: 115: LATC=0x00;
	movlb 2	; select bank2
	clrf	(270)^0100h	;volatile
	line	116
;main.c: 116: ANSELC=0x00;
	movlb 3	; select bank3
	clrf	(398)^0180h	;volatile
	line	117
	
l14266:	
;main.c: 117: TRISC=0xD7;
	movlw	(0D7h)
	movlb 1	; select bank1
	movwf	(142)^080h	;volatile
	line	118
	
l14268:	
;main.c: 118: WPUC=0x05;
	movlw	(05h)
	movlb 4	; select bank4
	movwf	(526)^0200h	;volatile
	line	120
	
l14270:	
;main.c: 120: nWPUEN=0;
	movlb 1	; select bank1
	bcf	(1199/8)^080h,(1199)&7
	line	123
;main.c: 123: APFCON0=0x00;
	movlb 2	; select bank2
	clrf	(285)^0100h	;volatile
	line	124
;main.c: 124: APFCON1=0x00;
	clrf	(286)^0100h	;volatile
	line	126
	
l14272:	
;main.c: 126: RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	127
	
l14274:	
;main.c: 127: RC3=1;;
	bsf	(115/8),(115)&7
	line	133
	
l14276:	
;main.c: 133: mode_device=0x00;
	clrf	(_mode_device)
	line	134
	
l14278:	
;main.c: 134: mode_protocol=0x00;
	clrf	(_mode_protocol)
	line	135
	
l14280:	
;main.c: 135: mode_device|=(RC2<<1);
	movlw	0
	btfsc	(114/8),(114)&7
	movlw	(1 << (01h))
	movwf	(??_init+0)+0
	movf	(??_init+0)+0,w
	iorwf	(_mode_device),f
	line	136
	
l14282:	
;main.c: 136: mode_device|=(RC0);
	movlw	0
	btfsc	(112/8),(112)&7
	movlw	1
	movwf	(??_init+0)+0
	movf	(??_init+0)+0,w
	iorwf	(_mode_device),f
	line	137
	
l14284:	
;main.c: 137: mode_protocol|=(RB6<<1);
	movlw	0
	btfsc	(110/8),(110)&7
	movlw	(1 << (01h))
	movwf	(??_init+0)+0
	movf	(??_init+0)+0,w
	iorwf	(_mode_protocol),f
	line	138
	
l14286:	
;main.c: 138: mode_protocol|=(RB4);
	movlw	0
	btfsc	(108/8),(108)&7
	movlw	1
	movwf	(??_init+0)+0
	movf	(??_init+0)+0,w
	iorwf	(_mode_protocol),f
	line	142
;main.c: 142: switch(mode_protocol)
	goto	l14296
	line	143
;main.c: 143: { case 0x03: initSPI();
	
l1609:	
	
l14288:	
	fcall	_initSPI
	line	144
;main.c: 144: break;
	goto	l1610
	line	145
;main.c: 145: case 0x02: initI2C();
	
l1611:	
	
l14290:	
	fcall	_initI2C
	line	146
;main.c: 146: break;
	goto	l1610
	line	147
;main.c: 147: case 0x01: initUART();
	
l1612:	
	
l14292:	
	fcall	_initUART
	line	148
;main.c: 148: break;
	goto	l1610
	line	149
;main.c: 149: case 0x00: break;
	
l1613:	
	goto	l1610
	line	150
;main.c: 150: default: break;
	
l1614:	
	goto	l1610
	line	151
	
l14294:	
;main.c: 151: }
	goto	l1610
	line	142
	
l1608:	
	
l14296:	
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
	goto	l1610
	xorlw	1^0	; case 1
	skipnz
	goto	l14292
	xorlw	2^1	; case 2
	skipnz
	goto	l14290
	xorlw	3^2	; case 3
	skipnz
	goto	l14288
	goto	l1610
	opt asmopt_on

	line	151
	
l1610:	
	line	153
;main.c: 153: RC5=0;;
	movlb 0	; select bank0
	bcf	(117/8),(117)&7
	line	159
	
l1615:	
	return
	opt stack 0
GLOBAL	__end_of_init
	__end_of_init:
;; =============== function _init ends ============

	signat	_init,88
	global	_UARTwrite
psect	text737,local,class=CODE,delta=2
global __ptext737
__ptext737:

;; *************** function _UARTwrite *****************
;; Defined at:
;;		line 73 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
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
;;		_teletype
;; This function uses a non-reentrant model
;;
psect	text737
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
	line	73
	global	__size_of_UARTwrite
	__size_of_UARTwrite	equ	__end_of_UARTwrite-_UARTwrite
	
_UARTwrite:	
	opt	stack 13
; Regs used in _UARTwrite: [wreg]
;UARTwrite@c stored from wreg
	movwf	(UARTwrite@c)
	line	74
	
l14246:	
;uart.c: 74: RC3=1;;
	movlb 0	; select bank0
	bsf	(115/8),(115)&7
	line	76
;uart.c: 76: while(!TRMT);
	goto	l4838
	
l4839:	
	
l4838:	
	movlb 3	; select bank3
	btfss	(3313/8)^0180h,(3313)&7
	goto	u2581
	goto	u2580
u2581:
	goto	l4838
u2580:
	goto	l14248
	
l4840:	
	line	78
	
l14248:	
;uart.c: 78: TXREG=c;
	movf	(UARTwrite@c),w
	movwf	(410)^0180h	;volatile
	line	80
	
l14250:	
;uart.c: 80: RC3=0;;
	movlb 0	; select bank0
	bcf	(115/8),(115)&7
	line	81
	
l4841:	
	return
	opt stack 0
GLOBAL	__end_of_UARTwrite
	__end_of_UARTwrite:
;; =============== function _UARTwrite ends ============

	signat	_UARTwrite,4216
	global	_UARTread
psect	text738,local,class=CODE,delta=2
global __ptext738
__ptext738:

;; *************** function _UARTread *****************
;; Defined at:
;;		line 56 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
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
;; This function uses a non-reentrant model
;;
psect	text738
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
	line	56
	global	__size_of_UARTread
	__size_of_UARTread	equ	__end_of_UARTread-_UARTread
	
_UARTread:	
	opt	stack 13
; Regs used in _UARTread: [wreg+fsr1l-status,0]
	line	59
	
l14232:	
;uart.c: 57: unsigned char temp;
;uart.c: 59: while(rtail==rhead);
	goto	l14234
	
l4833:	
	goto	l14234
	
l4832:	
	
l14234:	
	movf	(_rtail),w	;volatile
	xorwf	(_rhead),w	;volatile
	skipnz
	goto	u2571
	goto	u2570
u2571:
	goto	l14234
u2570:
	
l4834:	
	line	62
;uart.c: 62: GIE=0;
	bcf	(95/8),(95)&7
	line	63
	
l14236:	
;uart.c: 63: rtail++;
	movlw	(01h)
	movwf	(??_UARTread+0)+0
	movf	(??_UARTread+0)+0,w
	addwf	(_rtail),f	;volatile
	line	64
;uart.c: 64: rtail&=(8-1);
	movlw	(07h)
	movwf	(??_UARTread+0)+0
	movf	(??_UARTread+0)+0,w
	andwf	(_rtail),f	;volatile
	line	65
	
l14238:	
;uart.c: 65: temp=ringbuff[rtail];
	movf	(_rtail),w	;volatile
	addwf	wreg,w
	addlw	_ringbuff&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	movwf	(??_UARTread+0)+0
	movf	(??_UARTread+0)+0,w
	movwf	(UARTread@temp)
	line	66
	
l14240:	
;uart.c: 66: GIE=1;
	bsf	(95/8),(95)&7
	line	68
	
l14242:	
;uart.c: 68: return temp;
	movf	(UARTread@temp),w
	goto	l4835
	
l14244:	
	line	69
	
l4835:	
	return
	opt stack 0
GLOBAL	__end_of_UARTread
	__end_of_UARTread:
;; =============== function _UARTread ends ============

	signat	_UARTread,89
	global	_setDAC
psect	text739,local,class=CODE,delta=2
global __ptext739
__ptext739:

;; *************** function _setDAC *****************
;; Defined at:
;;		line 18 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\dac.c"
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
;; This function uses a non-reentrant model
;;
psect	text739
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\dac.c"
	line	18
	global	__size_of_setDAC
	__size_of_setDAC	equ	__end_of_setDAC-_setDAC
	
_setDAC:	
	opt	stack 13
; Regs used in _setDAC: [wreg+status,2]
;setDAC@dac stored from wreg
	movwf	(setDAC@dac)
	line	19
	
l14230:	
;dac.c: 19: DACCON1=dac&0x1F;
	movf	(setDAC@dac),w
	andlw	01Fh
	movlb 2	; select bank2
	movwf	(281)^0100h	;volatile
	line	20
	
l11107:	
	return
	opt stack 0
GLOBAL	__end_of_setDAC
	__end_of_setDAC:
;; =============== function _setDAC ends ============

	signat	_setDAC,4216
	global	_enableDAC
psect	text740,local,class=CODE,delta=2
global __ptext740
__ptext740:

;; *************** function _enableDAC *****************
;; Defined at:
;;		line 8 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\dac.c"
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
;; This function uses a non-reentrant model
;;
psect	text740
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\dac.c"
	line	8
	global	__size_of_enableDAC
	__size_of_enableDAC	equ	__end_of_enableDAC-_enableDAC
	
_enableDAC:	
	opt	stack 13
; Regs used in _enableDAC: [wreg]
	line	9
	
l14228:	
;dac.c: 9: DACCON0=0b10100000;
	movlw	(0A0h)
	movlb 2	; select bank2
	movwf	(280)^0100h	;volatile
	line	10
	
l11101:	
	return
	opt stack 0
GLOBAL	__end_of_enableDAC
	__end_of_enableDAC:
;; =============== function _enableDAC ends ============

	signat	_enableDAC,88
	global	_getADC
psect	text741,local,class=CODE,delta=2
global __ptext741
__ptext741:

;; *************** function _getADC *****************
;; Defined at:
;;		line 16 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\adc.c"
;; Parameters:    Size  Location     Type
;;  adc             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  adc             1    5[COMMON] unsigned char 
;;  i               2    6[COMMON] int 
;; Return value:  Size  Location     Type
;;                  2    3[COMMON] unsigned int 
;; Registers used:
;;		wreg, status,2, status,0, btemp+1
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         5       4       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        9 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_I2CADCworker
;;		_I2CDACworker
;; This function uses a non-reentrant model
;;
psect	text741
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\adc.c"
	line	16
	global	__size_of_getADC
	__size_of_getADC	equ	__end_of_getADC-_getADC
	
_getADC:	
	opt	stack 13
; Regs used in _getADC: [wreg+status,2+status,0+btemp+1]
;getADC@adc stored from wreg
	line	20
	movwf	(getADC@adc)
	
l14478:	
;adc.c: 17: int i;
;adc.c: 20: ADCON1=0b11000000;
	movlw	(0C0h)
	movlb 1	; select bank1
	movwf	(158)^080h	;volatile
	line	21
	
l14480:	
;adc.c: 21: adc&=0x1F;
	movlw	(01Fh)
	movlb 0	; select bank0
	movwf	(??_getADC+0)+0
	movf	(??_getADC+0)+0,w
	andwf	(getADC@adc),f
	line	22
	
l14482:	
;adc.c: 22: ADCON0=0x01|(adc<<2);
	movf	(getADC@adc),w
	movwf	(??_getADC+0)+0
	movlw	(02h)-1
u2795:
	lslf	(??_getADC+0)+0,f
	addlw	-1
	skipz
	goto	u2795
	lslf	(??_getADC+0)+0,w
	iorlw	01h
	movlb 1	; select bank1
	movwf	(157)^080h	;volatile
	line	24
	
l14484:	
;adc.c: 24: for(i=0; i<4; i++) asm("nop");
	clrf	(getADC@i)
	clrf	(getADC@i+1)
	
l14486:	
	movf	(getADC@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(04h))^80h
	subwf	btemp+1,w
	skipz
	goto	u2805
	movlw	low(04h)
	subwf	(getADC@i),w
u2805:

	skipc
	goto	u2801
	goto	u2800
u2801:
	goto	l9536
u2800:
	goto	l9537
	
l14488:	
	goto	l9537
	
l9536:	
# 24 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\adc.c"
nop ;#
psect	text741
	
l14490:	
	movlw	low(01h)
	addwf	(getADC@i),f
	movlw	high(01h)
	addwfc	(getADC@i+1),f
	
l14492:	
	movf	(getADC@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(04h))^80h
	subwf	btemp+1,w
	skipz
	goto	u2815
	movlw	low(04h)
	subwf	(getADC@i),w
u2815:

	skipc
	goto	u2811
	goto	u2810
u2811:
	goto	l9536
u2810:
	
l9537:	
	line	26
;adc.c: 26: ADCON0bits.ADGO=1;
	movlb 1	; select bank1
	bsf	(157)^080h,1	;volatile
	line	27
;adc.c: 27: while(ADCON0bits.ADGO);
	goto	l9538
	
l9539:	
	
l9538:	
	btfsc	(157)^080h,1	;volatile
	goto	u2821
	goto	u2820
u2821:
	goto	l9538
u2820:
	goto	l14494
	
l9540:	
	line	29
	
l14494:	
;adc.c: 29: ADCON0&=0xFE;
	movlw	(0FEh)
	movlb 0	; select bank0
	movwf	(??_getADC+0)+0
	movf	(??_getADC+0)+0,w
	movlb 1	; select bank1
	andwf	(157)^080h,f	;volatile
	line	30
	
l14496:	
;adc.c: 30: return (ADRESH<<8)|ADRESL;
	movf	(155)^080h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_getADC+0)+0
	clrf	(??_getADC+0)+0+1
	movlb 1	; select bank1
	movf	(156)^080h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_getADC+2)+0
	clrf	(??_getADC+2)+0+1
	movf	(??_getADC+2)+0,w
	movwf	(??_getADC+2)+1
	clrf	(??_getADC+2)+0
	movf	0+(??_getADC+0)+0,w
	iorwf	0+(??_getADC+2)+0,w
	movwf	(?_getADC)
	movf	1+(??_getADC+0)+0,w
	iorwf	1+(??_getADC+2)+0,w
	movwf	1+(?_getADC)
	goto	l9541
	
l14498:	
	line	31
	
l9541:	
	return
	opt stack 0
GLOBAL	__end_of_getADC
	__end_of_getADC:
;; =============== function _getADC ends ============

	signat	_getADC,4218
	global	_enableTS
psect	text742,local,class=CODE,delta=2
global __ptext742
__ptext742:

;; *************** function _enableTS *****************
;; Defined at:
;;		line 35 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\adc.c"
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
psect	text742
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\adc.c"
	line	35
	global	__size_of_enableTS
	__size_of_enableTS	equ	__end_of_enableTS-_enableTS
	
_enableTS:	
	opt	stack 13
; Regs used in _enableTS: [wreg+status,2+status,0]
	line	36
	
l14202:	
;adc.c: 36: FVRCON|=0b00100000;
	movlb 2	; select bank2
	bsf	(279)^0100h+(5/8),(5)&7	;volatile
	line	37
	
l14204:	
;adc.c: 37: FVRCON&=0b11101111;
	movlw	(0EFh)
	movwf	(??_enableTS+0)+0
	movf	(??_enableTS+0)+0,w
	andwf	(279)^0100h,f	;volatile
	line	38
	
l9544:	
	return
	opt stack 0
GLOBAL	__end_of_enableTS
	__end_of_enableTS:
;; =============== function _enableTS ends ============

	signat	_enableTS,88
	global	_I2CWrite
psect	text743,local,class=CODE,delta=2
global __ptext743
__ptext743:

;; *************** function _I2CWrite *****************
;; Defined at:
;;		line 182 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
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
;;		_I2CEEworker
;;		_I2CADCworker
;;		_I2CDACworker
;; This function uses a non-reentrant model
;;
psect	text743
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
	line	182
	global	__size_of_I2CWrite
	__size_of_I2CWrite	equ	__end_of_I2CWrite-_I2CWrite
	
_I2CWrite:	
	opt	stack 13
; Regs used in _I2CWrite: [wreg]
;I2CWrite@c stored from wreg
	line	185
	movwf	(I2CWrite@c)
	line	183
;i2c.c: 183: do
	
l3249:	
	line	185
;i2c.c: 184: {
;i2c.c: 185: SSP2CON1bits.WCOL=0;
	movlb 4	; select bank4
	bcf	(541)^0200h,7	;volatile
	line	186
	
l14474:	
;i2c.c: 186: SSP2BUF=c;
	movf	(I2CWrite@c),w
	movwf	(537)^0200h	;volatile
	line	187
	
l14476:	
;i2c.c: 187: } while(SSP2CON1bits.WCOL);
	btfsc	(541)^0200h,7	;volatile
	goto	u2781
	goto	u2780
u2781:
	goto	l3249
u2780:
	
l3250:	
	line	188
;i2c.c: 188: SSP2CON1bits.CKP=1;
	bsf	(541)^0200h,4	;volatile
	line	189
	
l3251:	
	return
	opt stack 0
GLOBAL	__end_of_I2CWrite
	__end_of_I2CWrite:
;; =============== function _I2CWrite ends ============

	signat	_I2CWrite,4216
	global	_EEPROMread
psect	text744,local,class=CODE,delta=2
global __ptext744
__ptext744:

;; *************** function _EEPROMread *****************
;; Defined at:
;;		line 24 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\eeprom.c"
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
;;		_I2CEEworker
;; This function uses a non-reentrant model
;;
psect	text744
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\eeprom.c"
	line	24
	global	__size_of_EEPROMread
	__size_of_EEPROMread	equ	__end_of_EEPROMread-_EEPROMread
	
_EEPROMread:	
	opt	stack 13
; Regs used in _EEPROMread: [wreg]
;EEPROMread@addr stored from wreg
	movwf	(EEPROMread@addr)
	line	25
	
l14464:	
;eeprom.c: 25: EEADRL=addr;
	movf	(EEPROMread@addr),w
	movlb 3	; select bank3
	movwf	(401)^0180h	;volatile
	line	26
	
l14466:	
;eeprom.c: 26: EECON1bits.CFGS=0;
	bcf	(405)^0180h,6	;volatile
	line	27
	
l14468:	
;eeprom.c: 27: EECON1bits.EEPGD=0;
	bcf	(405)^0180h,7	;volatile
	line	28
	
l14470:	
;eeprom.c: 28: EECON1bits.RD=1;
	bsf	(405)^0180h,0	;volatile
	line	30
;eeprom.c: 30: return EEDATL;
	movf	(403)^0180h,w	;volatile
	goto	l7979
	
l14472:	
	line	31
	
l7979:	
	return
	opt stack 0
GLOBAL	__end_of_EEPROMread
	__end_of_EEPROMread:
;; =============== function _EEPROMread ends ============

	signat	_EEPROMread,4217
	global	_EEPROMwrite
psect	text745,local,class=CODE,delta=2
global __ptext745
__ptext745:

;; *************** function _EEPROMwrite *****************
;; Defined at:
;;		line 8 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\eeprom.c"
;; Parameters:    Size  Location     Type
;;  addr            1    wreg     unsigned char 
;;  data            1    3[COMMON] unsigned char 
;; Auto vars:     Size  Location     Type
;;  addr            1    4[COMMON] unsigned char 
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
;; This function uses a non-reentrant model
;;
psect	text745
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\eeprom.c"
	line	8
	global	__size_of_EEPROMwrite
	__size_of_EEPROMwrite	equ	__end_of_EEPROMwrite-_EEPROMwrite
	
_EEPROMwrite:	
	opt	stack 13
; Regs used in _EEPROMwrite: [wreg]
;EEPROMwrite@addr stored from wreg
	movwf	(EEPROMwrite@addr)
	line	9
	
l14450:	
;eeprom.c: 9: EEADRL=addr;
	movf	(EEPROMwrite@addr),w
	movlb 3	; select bank3
	movwf	(401)^0180h	;volatile
	line	10
;eeprom.c: 10: EEDATL=data;
	movf	(EEPROMwrite@data),w
	movwf	(403)^0180h	;volatile
	line	11
	
l14452:	
;eeprom.c: 11: EECON1bits.CFGS=0;
	bcf	(405)^0180h,6	;volatile
	line	12
	
l14454:	
;eeprom.c: 12: EECON1bits.EEPGD=0;
	bcf	(405)^0180h,7	;volatile
	line	13
	
l14456:	
;eeprom.c: 13: EECON1bits.WREN=1;
	bsf	(405)^0180h,2	;volatile
	line	15
	
l14458:	
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
	
l14460:	
;eeprom.c: 18: EECON1bits.WR=1;
	bsf	(405)^0180h,1	;volatile
	line	19
	
l14462:	
;eeprom.c: 19: GIE=1;
	bsf	(95/8),(95)&7
	line	20
;eeprom.c: 20: while(EECON1bits.WR);
	goto	l7973
	
l7974:	
	
l7973:	
	btfsc	(405)^0180h,1	;volatile
	goto	u2771
	goto	u2770
u2771:
	goto	l7973
u2770:
	goto	l7976
	
l7975:	
	line	21
	
l7976:	
	return
	opt stack 0
GLOBAL	__end_of_EEPROMwrite
	__end_of_EEPROMwrite:
;; =============== function _EEPROMwrite ends ============

	signat	_EEPROMwrite,8312
	global	_initUART
psect	text746,local,class=CODE,delta=2
global __ptext746
__ptext746:

;; *************** function _initUART *****************
;; Defined at:
;;		line 13 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    4[COMMON] unsigned char 
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
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_init
;; This function uses a non-reentrant model
;;
psect	text746
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
	line	13
	global	__size_of_initUART
	__size_of_initUART	equ	__end_of_initUART-_initUART
	
_initUART:	
	opt	stack 13
; Regs used in _initUART: [wreg+fsr1l-status,0]
	line	15
	
l14124:	
;uart.c: 15: APFCON0|=0x04;
	movlb 2	; select bank2
	bsf	(285)^0100h+(2/8),(2)&7	;volatile
	line	16
;uart.c: 16: TRISB5=1;
	movlb 1	; select bank1
	bsf	(1133/8)^080h,(1133)&7
	line	17
;uart.c: 17: TRISC4=0;
	bcf	(1140/8)^080h,(1140)&7
	line	21
;uart.c: 21: BRGH=1;
	movlb 3	; select bank3
	bsf	(3314/8)^0180h,(3314)&7
	line	22
	
l14126:	
;uart.c: 22: SPBRGH=0x00;
	clrf	(412)^0180h	;volatile
	line	23
	
l14128:	
;uart.c: 23: SPBRGL=25;
	movlw	(019h)
	movwf	(411)^0180h	;volatile
	line	26
	
l14130:	
;uart.c: 26: SYNC=0;
	bcf	(3316/8)^0180h,(3316)&7
	line	27
	
l14132:	
;uart.c: 27: SPEN=1;
	bsf	(3311/8)^0180h,(3311)&7
	line	28
	
l14134:	
;uart.c: 28: TXEN=1;
	bsf	(3317/8)^0180h,(3317)&7
	line	29
	
l14136:	
;uart.c: 29: CREN=1;
	bsf	(3308/8)^0180h,(3308)&7
	line	32
	
l14138:	
;uart.c: 32: RCIE=1;
	movlb 1	; select bank1
	bsf	(1165/8)^080h,(1165)&7
	line	33
	
l14140:	
;uart.c: 33: TXIE=0;
	bcf	(1164/8)^080h,(1164)&7
	line	36
	
l14142:	
;uart.c: 36: rhead=0;
	clrf	(_rhead)	;volatile
	line	37
	
l14144:	
;uart.c: 37: rtail=0;
	clrf	(_rtail)	;volatile
	line	38
	
l14146:	
;uart.c: 38: for(i=0; i<(8-1); i++)
	clrf	(initUART@i)
	
l14148:	
	movlw	(07h)
	subwf	(initUART@i),w
	skipc
	goto	u2461
	goto	u2460
u2461:
	goto	l14152
u2460:
	goto	l4825
	
l14150:	
	goto	l4825
	line	39
	
l4824:	
	line	40
	
l14152:	
;uart.c: 39: {
;uart.c: 40: ringbuff[i]=0x00;
	movf	(initUART@i),w
	addwf	wreg,w
	addlw	_ringbuff&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movlw	low(0)
	movwi	[0]fsr1
	movlw	high(0)
	movwi	[1]fsr1
	line	38
	
l14154:	
	movlw	(01h)
	movwf	(??_initUART+0)+0
	movf	(??_initUART+0)+0,w
	addwf	(initUART@i),f
	
l14156:	
	movlw	(07h)
	subwf	(initUART@i),w
	skipc
	goto	u2471
	goto	u2470
u2471:
	goto	l14152
u2470:
	
l4825:	
	line	43
;uart.c: 41: }
;uart.c: 43: RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	44
	
l4826:	
	return
	opt stack 0
GLOBAL	__end_of_initUART
	__end_of_initUART:
;; =============== function _initUART ends ============

	signat	_initUART,88
	global	_initI2C
psect	text747,local,class=CODE,delta=2
global __ptext747
__ptext747:

;; *************** function _initI2C *****************
;; Defined at:
;;		line 15 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
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
psect	text747
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
	line	15
	global	__size_of_initI2C
	__size_of_initI2C	equ	__end_of_initI2C-_initI2C
	
_initI2C:	
	opt	stack 13
; Regs used in _initI2C: [wreg+status,2+status,0]
	line	18
	
l14114:	
;i2c.c: 18: SSP2BUF=0x00;
	movlb 4	; select bank4
	clrf	(537)^0200h	;volatile
	line	19
	
l14116:	
;i2c.c: 19: SSP2STAT=0x80;
	movlw	(080h)
	movwf	(540)^0200h	;volatile
	line	20
	
l14118:	
;i2c.c: 20: SSP2MSK=0xFE;
	movlw	(0FEh)
	movwf	(539)^0200h	;volatile
	line	21
	
l14120:	
;i2c.c: 21: SSP2CON1=0x36;
	movlw	(036h)
	movwf	(541)^0200h	;volatile
	line	22
	
l14122:	
;i2c.c: 22: SSP2CON3|=0b11000000;
	movlw	(0C0h)
	movwf	(??_initI2C+0)+0
	movf	(??_initI2C+0)+0,w
	iorwf	(543)^0200h,f	;volatile
	line	23
	
l3196:	
	return
	opt stack 0
GLOBAL	__end_of_initI2C
	__end_of_initI2C:
;; =============== function _initI2C ends ============

	signat	_initI2C,88
	global	_initSPI
psect	text748,local,class=CODE,delta=2
global __ptext748
__ptext748:

;; *************** function _initSPI *****************
;; Defined at:
;;		line 6 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\spi.c"
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
;;		_init
;; This function uses a non-reentrant model
;;
psect	text748
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\spi.c"
	line	6
	global	__size_of_initSPI
	__size_of_initSPI	equ	__end_of_initSPI-_initSPI
	
_initSPI:	
	opt	stack 13
; Regs used in _initSPI: []
	line	8
	
l3254:	
	return
	opt stack 0
GLOBAL	__end_of_initSPI
	__end_of_initSPI:
;; =============== function _initSPI ends ============

	signat	_initSPI,88
	global	_isEE
psect	text749,local,class=CODE,delta=2
global __ptext749
__ptext749:

;; *************** function _isEE *****************
;; Defined at:
;;		line 16 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
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
psect	text749
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
	line	16
	global	__size_of_isEE
	__size_of_isEE	equ	__end_of_isEE-_isEE
	
_isEE:	
	opt	stack 14
; Regs used in _isEE: [wreg]
	line	17
	
l14110:	
;easteregg.c: 17: return 0;
	movlw	(0)
	goto	l6402
	
l14112:	
	line	18
	
l6402:	
	return
	opt stack 0
GLOBAL	__end_of_isEE
	__end_of_isEE:
;; =============== function _isEE ends ============

	signat	_isEE,89
	global	_isr
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:

;; *************** function _isr *****************
;; Defined at:
;;		line 164 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
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
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	line	164
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
	line	165
;main.c: 165: do { if(RCIF) { RC3=1;; if(!(RCSTA&0b00000110)) { rhead++; rhead&=(8-1); ringbuff[rhead]=RCREG; } RCIF=0; RC3=0;; } if(TXIF) { TXIF=0; } } while(0);;
	
i1l1618:	
	btfss	(141/8),(141)&7
	goto	u248_21
	goto	u248_20
u248_21:
	goto	i1l14170
u248_20:
	
i1l14158:	
	bsf	(115/8),(115)&7
	
i1l14160:	
	movlb 3	; select bank3
	movf	(413)^0180h,w
	andlw	06h
	btfss	status,2
	goto	u249_21
	goto	u249_20
u249_21:
	goto	i1l14166
u249_20:
	
i1l14162:	
	movlw	(01h)
	movwf	(??_isr+0)+0
	movf	(??_isr+0)+0,w
	addwf	(_rhead),f	;volatile
	movlw	(07h)
	movwf	(??_isr+0)+0
	movf	(??_isr+0)+0,w
	andwf	(_rhead),f	;volatile
	
i1l14164:	
	movf	(409)^0180h,w	;volatile
	movwf	(??_isr+0)+0
	clrf	(??_isr+0)+0+1
	movf	(_rhead),w	;volatile
	addwf	wreg,w
	addlw	_ringbuff&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	0+(??_isr+0)+0,w
	movwi	[0]fsr1
	movf	1+(??_isr+0)+0,w
	movwi	[1]fsr1
	goto	i1l14166
	
i1l1620:	
	
i1l14166:	
	movlb 0	; select bank0
	bcf	(141/8),(141)&7
	
i1l14168:	
	bcf	(115/8),(115)&7
	goto	i1l14170
	
i1l1619:	
	
i1l14170:	
	btfss	(140/8),(140)&7
	goto	u250_21
	goto	u250_20
u250_21:
	goto	i1l1625
u250_20:
	
i1l14172:	
	bcf	(140/8),(140)&7
	goto	i1l1625
	
i1l1621:	
	goto	i1l1625
	
i1l1622:	
	goto	i1l1625
	line	166
;main.c: 166: do { ;} while(0);;
	
i1l1623:	
	goto	i1l1625
	
i1l1624:	
	line	169
	
i1l1625:	
	movf	(??_isr+2),w
	movwf	btemp+1
	retfie
	opt stack 0
GLOBAL	__end_of_isr
	__end_of_isr:
;; =============== function _isr ends ============

	signat	_isr,88
	global	fptotal
fptotal equ 21
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
fp__I2CEEworker:
	ljmp	_I2CEEworker
	file ""
	line	#
fp__I2CDACworker:
	ljmp	_I2CDACworker
	file ""
	line	#
fp__I2CADCworker:
	ljmp	_I2CADCworker
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
