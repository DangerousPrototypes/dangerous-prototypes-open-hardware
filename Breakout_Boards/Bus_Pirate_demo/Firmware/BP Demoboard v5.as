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
	dw 0xFFFE&0xFEFF&0xFFFF&0xDFFF ;#
	FNCALL	_main,_init
	FNCALL	_main,_isEE
	FNCALL	_main,_doEE
	FNCALL	_main,_SPIworker
	FNCALL	_main,_I2Cworker
	FNCALL	_main,_UARTworker
	FNCALL	_doEE,_teletype
	FNCALL	_teletype,_UARTwrite
	FNCALL	_UARTworker,_UARTread
	FNCALL	_UARTworker,_UARTwrite
	FNCALL	_I2Cworker,_enableTS
	FNCALL	_I2Cworker,_getADC
	FNCALL	_I2Cworker,_I2CWrite
	FNCALL	_init,_initSPI
	FNCALL	_init,_initI2C
	FNCALL	_init,_initUART
	FNROOT	_main
	FNCALL	intlevel1,_isr
	global	intlevel1
	FNROOT	intlevel1
	global	_ringbuff
	global	_rhead
	global	_rtail
	global	_mode
psect	nvCOMMON,class=COMMON,space=1
global __pnvCOMMON
__pnvCOMMON:
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
_rhead:
       ds      1

_rtail:
       ds      1

psect	bssBANK0,class=BANK0,space=1
global __pbssBANK0
__pbssBANK0:
_ringbuff:
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
; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2
	global __pbssBANK0
	movlw	low(__pbssBANK0)
	movwf	fsr0l
	movlw	high(__pbssBANK0)
	movwf	fsr0h
	movlw	010h
	fcall	clear_ram
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
movlb 0
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_init
?_init:	; 0 bytes @ 0x0
	global	?_doEE
?_doEE:	; 0 bytes @ 0x0
	global	?_SPIworker
?_SPIworker:	; 0 bytes @ 0x0
	global	?_I2Cworker
?_I2Cworker:	; 0 bytes @ 0x0
	global	?_UARTworker
?_UARTworker:	; 0 bytes @ 0x0
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
	global	?_UARTwrite
?_UARTwrite:	; 0 bytes @ 0x0
	global	?_isr
?_isr:	; 0 bytes @ 0x0
	global	??_isr
??_isr:	; 0 bytes @ 0x0
	global	?_isEE
?_isEE:	; 1 bytes @ 0x0
	global	?_UARTread
?_UARTread:	; 1 bytes @ 0x0
	global	?_main
?_main:	; 2 bytes @ 0x0
	ds	3
	global	??_isEE
??_isEE:	; 0 bytes @ 0x3
	global	??_SPIworker
??_SPIworker:	; 0 bytes @ 0x3
	global	??_initSPI
??_initSPI:	; 0 bytes @ 0x3
	global	??_initI2C
??_initI2C:	; 0 bytes @ 0x3
	global	??_initUART
??_initUART:	; 0 bytes @ 0x3
	global	??_I2CWrite
??_I2CWrite:	; 0 bytes @ 0x3
	global	??_enableTS
??_enableTS:	; 0 bytes @ 0x3
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
	ds	1
	global	?_teletype
?_teletype:	; 0 bytes @ 0x4
	global	initUART@i
initUART@i:	; 1 bytes @ 0x4
	global	UARTread@temp
UARTread@temp:	; 1 bytes @ 0x4
	global	teletype@s
teletype@s:	; 2 bytes @ 0x4
	ds	1
	global	??_init
??_init:	; 0 bytes @ 0x5
	global	??_UARTworker
??_UARTworker:	; 0 bytes @ 0x5
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
	ds	4
	global	??_I2Cworker
??_I2Cworker:	; 0 bytes @ 0x4
	ds	1
	global	I2Cworker@temp
I2Cworker@temp:	; 1 bytes @ 0x5
	ds	1
	global	I2Cworker@token
I2Cworker@token:	; 1 bytes @ 0x6
	ds	1
	global	I2Cworker@adc
I2Cworker@adc:	; 1 bytes @ 0x7
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0x8
	ds	2
;;Data sizes: Strings 394, constant 0, data 0, bss 18, persistent 1 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      8      11
;; BANK0           80     10      26
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


;;
;; Critical Paths under _main in COMMON
;;
;;   _doEE->_teletype
;;   _teletype->_UARTwrite
;;   _UARTworker->_UARTread
;;   _I2Cworker->_getADC
;;   _init->_initUART
;;
;; Critical Paths under _isr in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   _main->_I2Cworker
;;   _I2Cworker->_getADC
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
;;Main: autosize = 0, tempsize = 2, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 2     2      0     439
;;                                              8 BANK0      2     2      0
;;                               _init
;;                               _isEE
;;                               _doEE
;;                          _SPIworker
;;                          _I2Cworker
;;                         _UARTworker
;; ---------------------------------------------------------------------------------
;; (1) _doEE                                                 0     0      0      75
;;                           _teletype
;; ---------------------------------------------------------------------------------
;; (2) _teletype                                             5     3      2      75
;;                                              4 COMMON     4     2      2
;;                          _UARTwrite
;; ---------------------------------------------------------------------------------
;; (1) _UARTworker                                           2     2      0      61
;;                                              5 COMMON     2     2      0
;;                           _UARTread
;;                          _UARTwrite
;; ---------------------------------------------------------------------------------
;; (1) _I2Cworker                                            4     4      0     235
;;                                              4 BANK0      4     4      0
;;                           _enableTS
;;                             _getADC
;;                           _I2CWrite
;; ---------------------------------------------------------------------------------
;; (1) _init                                                 2     2      0      68
;;                                              5 COMMON     2     2      0
;;                            _initSPI
;;                            _initI2C
;;                           _initUART
;; ---------------------------------------------------------------------------------
;; (2) _UARTwrite                                            1     1      0      15
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _UARTread                                             2     2      0      23
;;                                              3 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; (2) _getADC                                               9     7      2     102
;;                                              3 COMMON     5     3      2
;;                                              0 BANK0      4     4      0
;; ---------------------------------------------------------------------------------
;; (2) _enableTS                                             1     1      0       0
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _I2CWrite                                             1     1      0      22
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _initUART                                             2     2      0      68
;;                                              3 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; (2) _initI2C                                              1     1      0       0
;;                                              3 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (2) _initSPI                                              0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _SPIworker                                            0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _isEE                                                 0     0      0       0
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
;;   _SPIworker
;;   _I2Cworker
;;     _enableTS
;;     _getADC
;;     _I2CWrite
;;   _UARTworker
;;     _UARTread
;;     _UARTwrite
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
;;BANK0               50      A      1A       5       32.5%
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
;;ABS                  0      0      25      20        0.0%
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
;;DATA                 0      0      28      31        0.0%
;;BITSFR31             0      0       0      32        0.0%
;;SFR31                0      0       0      32        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 32 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  2  1580[COMMON] int 
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr1l, fsr1h, status,2, status,0, btemp+1, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_init
;;		_isEE
;;		_doEE
;;		_SPIworker
;;		_I2Cworker
;;		_UARTworker
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	line	32
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 12
; Regs used in _main: [allreg]
	line	33
	
l14502:	
;main.c: 33: mode=0x02;
	movlw	(02h)
	movlb 0	; select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(_mode)
	line	35
	
l14504:	
;main.c: 35: init();
	fcall	_init
	line	37
	
l14506:	
;main.c: 37: if(isEE()) doEE();
	fcall	_isEE
	xorlw	0&0ffh
	skipnz
	goto	u2741
	goto	u2740
u2741:
	goto	l14518
u2740:
	
l14508:	
	fcall	_doEE
	goto	l14518
	
l1581:	
	line	40
;main.c: 40: switch(mode&0x03)
	goto	l14518
	line	41
;main.c: 41: { case 0x00: SPIworker();
	
l1583:	
	
l14510:	
	fcall	_SPIworker
	line	42
;main.c: 42: break;
	goto	l1589
	line	43
;main.c: 43: case 0x02: I2Cworker();
	
l1585:	
	
l14512:	
	fcall	_I2Cworker
	line	44
;main.c: 44: break;
	goto	l1589
	line	45
;main.c: 45: case 0x01: UARTworker();
	
l1586:	
	
l14514:	
	fcall	_UARTworker
	line	46
;main.c: 46: break;
	goto	l1589
	line	47
;main.c: 47: case 0x03: break;
	
l1587:	
	goto	l1589
	line	48
;main.c: 48: default: break;
	
l1588:	
	goto	l1589
	line	49
	
l14516:	
;main.c: 49: }
	goto	l1589
	line	40
	
l1582:	
	
l14518:	
	movf	(_mode),w
	andlw	03h
	movlb 0	; select bank0
	movwf	(??_main+0)+0
	clrf	(??_main+0)+0+1
	; Switch on 2 bytes has been partitioned into a top level switch of size 1, and 1 sub-switches
; Switch size 1, requested type "space"
; Number of cases is 1, Range of values is 0 to 0
; switch strategies available:
; Name         Instructions Cycles
; simple_byte            4     3 (average)
; direct_byte            8     6 (fixed)
; jumptable            260     6 (fixed)
; rangetable             5     4 (fixed)
; spacedrange            7     6 (fixed)
; locatedrange           1     3 (fixed)
;	Chosen strategy is simple_byte

	movf 1+(??_main+0)+0,w
	opt asmopt_off
	xorlw	0^0	; case 0
	skipnz
	goto	l14564
	goto	l1589
	opt asmopt_on
	
l14564:	
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

	movf 0+(??_main+0)+0,w
	opt asmopt_off
	xorlw	0^0	; case 0
	skipnz
	goto	l14510
	xorlw	1^0	; case 1
	skipnz
	goto	l14514
	xorlw	2^1	; case 2
	skipnz
	goto	l14512
	xorlw	3^2	; case 3
	skipnz
	goto	l1589
	goto	l1589
	opt asmopt_on

	line	49
	
l1584:	
	line	50
	
l1589:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,90
	global	_doEE
psect	text523,local,class=CODE,delta=2
global __ptext523
__ptext523:

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
psect	text523
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
	line	21
	global	__size_of_doEE
	__size_of_doEE	equ	__end_of_doEE-_doEE
	
_doEE:	
	opt	stack 12
; Regs used in _doEE: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	line	22
	
l14060:	
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
	goto	l6390
	line	32
;easteregg.c: 32: while(1);
	
l6389:	
	
l6390:	
	goto	l6390
	
l6391:	
	line	33
	
l6392:	
	return
	opt stack 0
GLOBAL	__end_of_doEE
	__end_of_doEE:
;; =============== function _doEE ends ============

	signat	_doEE,88
	global	_teletype
psect	text524,local,class=CODE,delta=2
global __ptext524
__ptext524:

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
psect	text524
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
	line	36
	global	__size_of_teletype
	__size_of_teletype	equ	__end_of_teletype-_teletype
	
_teletype:	
	opt	stack 12
; Regs used in _teletype: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	line	39
	
l14042:	
;easteregg.c: 37: char c;
;easteregg.c: 39: while(*s)
	goto	l14058
	
l6396:	
	line	41
	
l14044:	
;easteregg.c: 40: {
;easteregg.c: 41: UARTwrite(*(s++));
	movf	(teletype@s),w
	movwf	fsr0l
	movf	((teletype@s+1)),w
	movwf	fsr0h
	movf	indf0,w ;code access
	fcall	_UARTwrite
	
l14046:	
	movlw	low(01h)
	addwf	(teletype@s),f
	movlw	high(01h)
	addwfc	(teletype@s+1),f
	line	43
	
l14048:	
;easteregg.c: 43: for(i=0; i<10000; i++) asm("nop");
	clrf	(teletype@i)
	clrf	(teletype@i+1)
	
l14050:	
	movf	(teletype@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(02710h))^80h
	subwf	btemp+1,w
	skipz
	goto	u2385
	movlw	low(02710h)
	subwf	(teletype@i),w
u2385:

	skipc
	goto	u2381
	goto	u2380
u2381:
	goto	l6397
u2380:
	goto	l14058
	
l14052:	
	goto	l14058
	
l6397:	
# 43 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
nop ;#
psect	text524
	
l14054:	
	movlw	low(01h)
	addwf	(teletype@i),f
	movlw	high(01h)
	addwfc	(teletype@i+1),f
	
l14056:	
	movf	(teletype@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(02710h))^80h
	subwf	btemp+1,w
	skipz
	goto	u2395
	movlw	low(02710h)
	subwf	(teletype@i),w
u2395:

	skipc
	goto	u2391
	goto	u2390
u2391:
	goto	l6397
u2390:
	goto	l14058
	
l6398:	
	goto	l14058
	line	44
	
l6395:	
	line	39
	
l14058:	
	movf	(teletype@s),w
	movwf	fsr0l
	movf	((teletype@s+1)),w
	movwf	fsr0h
	movf	indf0,w ;code access
	iorlw	0
	skipz
	goto	u2401
	goto	u2400
u2401:
	goto	l14044
u2400:
	goto	l6400
	
l6399:	
	line	45
	
l6400:	
	return
	opt stack 0
GLOBAL	__end_of_teletype
	__end_of_teletype:
;; =============== function _teletype ends ============

	signat	_teletype,4216
	global	_UARTworker
psect	text525,local,class=CODE,delta=2
global __ptext525
__ptext525:

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
psect	text525
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
	line	47
	global	__size_of_UARTworker
	__size_of_UARTworker	equ	__end_of_UARTworker-_UARTworker
	
_UARTworker:	
	opt	stack 13
; Regs used in _UARTworker: [wreg+fsr1l-status,0+pclath+cstack]
	line	50
	
l14348:	
;uart.c: 48: unsigned char c;
;uart.c: 50: c=UARTread();
	fcall	_UARTread
	movwf	(??_UARTworker+0)+0
	movf	(??_UARTworker+0)+0,w
	movwf	(UARTworker@c)
	line	51
	
l14350:	
;uart.c: 51: UARTwrite(c);
	movf	(UARTworker@c),w
	fcall	_UARTwrite
	line	52
	
l4813:	
	return
	opt stack 0
GLOBAL	__end_of_UARTworker
	__end_of_UARTworker:
;; =============== function _UARTworker ends ============

	signat	_UARTworker,88
	global	_I2Cworker
psect	text526,local,class=CODE,delta=2
global __ptext526
__ptext526:

;; *************** function _I2Cworker *****************
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
psect	text526
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
	line	87
	global	__size_of_I2Cworker
	__size_of_I2Cworker	equ	__end_of_I2Cworker-_I2Cworker
	
_I2Cworker:	
	opt	stack 13
; Regs used in _I2Cworker: [wreg-fsr0h+status,2+status,0+btemp+1+pclath+cstack]
	line	89
	
l14470:	
;i2c.c: 89: adc=0x00;
	movlb 0	; select bank0
	clrf	(I2Cworker@adc)
	line	90
	
l14472:	
;i2c.c: 90: enableTS();
	fcall	_enableTS
	line	91
	
l14474:	
;i2c.c: 91: SSP2ADD=0x10;
	movlw	(010h)
	movlb 4	; select bank4
	movwf	(538)^0200h	;volatile
	goto	l14476
	line	93
;i2c.c: 93: while(1)
	
l3201:	
	line	96
	
l14476:	
;i2c.c: 94: {
;i2c.c: 96: if(SSP2IF)
	movlb 0	; select bank0
	btfss	(160/8),(160)&7
	goto	u2711
	goto	u2710
u2711:
	goto	l14476
u2710:
	line	98
	
l14478:	
;i2c.c: 97: {
;i2c.c: 98: token=SSP2STAT&0x25;
	movlb 4	; select bank4
	movf	(540)^0200h,w
	andlw	025h
	movlb 0	; select bank0
	movwf	(??_I2Cworker+0)+0
	movf	(??_I2Cworker+0)+0,w
	movwf	(I2Cworker@token)
	line	100
	
l14480:	
;i2c.c: 100: if(SSP2STATbits.S)
	movlb 4	; select bank4
	btfss	(540)^0200h,3	;volatile
	goto	u2721
	goto	u2720
u2721:
	goto	l3203
u2720:
	line	101
	
l14482:	
;i2c.c: 101: { RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	102
;i2c.c: 102: switch(token)
	goto	l14498
	line	104
;i2c.c: 103: {
;i2c.c: 104: case 0x01:
	
l3205:	
	line	105
	
l14484:	
;i2c.c: 105: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2Cworker+0)+0
	movf	(??_I2Cworker+0)+0,w
	movwf	(I2Cworker@temp)
	line	106
;i2c.c: 106: break;
	goto	l3210
	line	107
;i2c.c: 107: case 0x21:
	
l3207:	
	line	108
	
l14486:	
;i2c.c: 108: adc=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2Cworker+0)+0
	movf	(??_I2Cworker+0)+0,w
	movwf	(I2Cworker@adc)
	line	109
;i2c.c: 109: break;
	goto	l3210
	line	110
;i2c.c: 110: case 0x05:
	
l3208:	
	line	111
	
l14488:	
;i2c.c: 111: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2Cworker+0)+0
	movf	(??_I2Cworker+0)+0,w
	movwf	(I2Cworker@temp)
	line	112
	
l14490:	
;i2c.c: 112: I2CWrite(getADC(adc));
	movf	(I2Cworker@adc),w
	fcall	_getADC
	movf	(0+(?_getADC)),w
	fcall	_I2CWrite
	line	113
;i2c.c: 113: break;
	goto	l3210
	line	114
;i2c.c: 114: case 0x24:
	
l3209:	
	line	115
	
l14492:	
;i2c.c: 115: temp=SSP2BUF;
	movlb 4	; select bank4
	movf	(537)^0200h,w	;volatile
	movlb 0	; select bank0
	movwf	(??_I2Cworker+0)+0
	movf	(??_I2Cworker+0)+0,w
	movwf	(I2Cworker@temp)
	line	116
	
l14494:	
;i2c.c: 116: I2CWrite(getADC(adc));
	movf	(I2Cworker@adc),w
	fcall	_getADC
	movf	(0+(?_getADC)),w
	fcall	_I2CWrite
	line	117
;i2c.c: 117: break;
	goto	l3210
	line	118
	
l14496:	
;i2c.c: 118: }
	goto	l3210
	line	102
	
l3204:	
	
l14498:	
	movlb 0	; select bank0
	movf	(I2Cworker@token),w
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
	goto	l14484
	xorlw	5^1	; case 5
	skipnz
	goto	l14488
	xorlw	33^5	; case 33
	skipnz
	goto	l14486
	xorlw	36^33	; case 36
	skipnz
	goto	l14492
	goto	l3210
	opt asmopt_on

	line	118
	
l3206:	
	line	119
;i2c.c: 119: }
	goto	l3210
	line	120
	
l3203:	
;i2c.c: 120: else if(SSP2STATbits.P)
	btfss	(540)^0200h,4	;volatile
	goto	u2731
	goto	u2730
u2731:
	goto	l3210
u2730:
	line	121
	
l14500:	
;i2c.c: 121: { RC5=0;;
	movlb 0	; select bank0
	bcf	(117/8),(117)&7
	line	122
# 122 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
NOP ;#
psect	text526
	goto	l3210
	line	123
	
l3211:	
	line	124
	
l3210:	
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
	goto	l14476
	line	127
	
l3202:	
	goto	l14476
	line	128
	
l3212:	
	line	93
	goto	l14476
	
l3213:	
	line	129
	
l3214:	
	return
	opt stack 0
GLOBAL	__end_of_I2Cworker
	__end_of_I2Cworker:
;; =============== function _I2Cworker ends ============

	signat	_I2Cworker,88
	global	_init
psect	text527,local,class=CODE,delta=2
global __ptext527
__ptext527:

;; *************** function _init *****************
;; Defined at:
;;		line 54 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
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
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
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
psect	text527
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
	line	54
	global	__size_of_init
	__size_of_init	equ	__end_of_init-_init
	
_init:	
	opt	stack 13
; Regs used in _init: [wreg-status,0+pclath+cstack]
	line	55
	
l14282:	
;main.c: 55: OSCCON=0xEA;
	movlw	(0EAh)
	movlb 1	; select bank1
	movwf	(153)^080h	;volatile
	line	59
	
l14284:	
;main.c: 59: PORTA=0x00;
	movlb 0	; select bank0
	clrf	(12)	;volatile
	line	60
	
l14286:	
;main.c: 60: LATA=0x00;
	movlb 2	; select bank2
	clrf	(268)^0100h	;volatile
	line	61
	
l14288:	
;main.c: 61: ANSELA=0x00;
	movlb 3	; select bank3
	clrf	(396)^0180h	;volatile
	line	62
	
l14290:	
;main.c: 62: TRISA=0xFF;
	movlw	(0FFh)
	movlb 1	; select bank1
	movwf	(140)^080h	;volatile
	line	63
;main.c: 63: WPUA=0x00;
	movlb 4	; select bank4
	clrf	(524)^0200h	;volatile
	line	66
;main.c: 66: PORTB=0x00;
	movlb 0	; select bank0
	clrf	(13)	;volatile
	line	67
;main.c: 67: LATB=0x00;
	movlb 2	; select bank2
	clrf	(269)^0100h	;volatile
	line	68
;main.c: 68: ANSELB=0x00;
	movlb 3	; select bank3
	clrf	(397)^0180h	;volatile
	line	69
	
l14292:	
;main.c: 69: TRISB=0xFF;
	movlw	(0FFh)
	movlb 1	; select bank1
	movwf	(141)^080h	;volatile
	line	70
	
l14294:	
;main.c: 70: WPUB=0x50;
	movlw	(050h)
	movlb 4	; select bank4
	movwf	(525)^0200h	;volatile
	line	73
;main.c: 73: PORTC=0x00;
	movlb 0	; select bank0
	clrf	(14)	;volatile
	line	74
;main.c: 74: LATC=0x00;
	movlb 2	; select bank2
	clrf	(270)^0100h	;volatile
	line	75
;main.c: 75: ANSELC=0x00;
	movlb 3	; select bank3
	clrf	(398)^0180h	;volatile
	line	76
	
l14296:	
;main.c: 76: TRISC=0xD7;
	movlw	(0D7h)
	movlb 1	; select bank1
	movwf	(142)^080h	;volatile
	line	77
	
l14298:	
;main.c: 77: WPUC=0x05;
	movlw	(05h)
	movlb 4	; select bank4
	movwf	(526)^0200h	;volatile
	line	79
	
l14300:	
;main.c: 79: nWPUEN=0;
	movlb 1	; select bank1
	bcf	(1199/8)^080h,(1199)&7
	line	82
;main.c: 82: APFCON0=0x00;
	movlb 2	; select bank2
	clrf	(285)^0100h	;volatile
	line	83
;main.c: 83: APFCON1=0x00;
	clrf	(286)^0100h	;volatile
	line	94
;main.c: 94: switch(mode&0x03)
	goto	l14310
	line	95
;main.c: 95: { case 0x00: initSPI();
	
l1593:	
	
l14302:	
	fcall	_initSPI
	line	96
;main.c: 96: break;
	goto	l1599
	line	97
;main.c: 97: case 0x02: initI2C();
	
l1595:	
	
l14304:	
	fcall	_initI2C
	line	98
;main.c: 98: break;
	goto	l1599
	line	99
;main.c: 99: case 0x01: initUART();
	
l1596:	
	
l14306:	
	fcall	_initUART
	line	100
;main.c: 100: break;
	goto	l1599
	line	101
;main.c: 101: case 0x03: break;
	
l1597:	
	goto	l1599
	line	102
;main.c: 102: default: break;
	
l1598:	
	goto	l1599
	line	103
	
l14308:	
;main.c: 103: }
	goto	l1599
	line	94
	
l1592:	
	
l14310:	
	movf	(_mode),w
	andlw	03h
	movwf	(??_init+0)+0
	clrf	(??_init+0)+0+1
	; Switch on 2 bytes has been partitioned into a top level switch of size 1, and 1 sub-switches
; Switch size 1, requested type "space"
; Number of cases is 1, Range of values is 0 to 0
; switch strategies available:
; Name         Instructions Cycles
; simple_byte            4     3 (average)
; direct_byte            8     6 (fixed)
; jumptable            260     6 (fixed)
; rangetable             5     4 (fixed)
; spacedrange            7     6 (fixed)
; locatedrange           1     3 (fixed)
;	Chosen strategy is simple_byte

	movf 1+(??_init+0)+0,w
	opt asmopt_off
	xorlw	0^0	; case 0
	skipnz
	goto	l14566
	goto	l1599
	opt asmopt_on
	
l14566:	
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

	movf 0+(??_init+0)+0,w
	opt asmopt_off
	xorlw	0^0	; case 0
	skipnz
	goto	l14302
	xorlw	1^0	; case 1
	skipnz
	goto	l14306
	xorlw	2^1	; case 2
	skipnz
	goto	l14304
	xorlw	3^2	; case 3
	skipnz
	goto	l1599
	goto	l1599
	opt asmopt_on

	line	103
	
l1594:	
	line	109
	
l1599:	
	return
	opt stack 0
GLOBAL	__end_of_init
	__end_of_init:
;; =============== function _init ends ============

	signat	_init,88
	global	_UARTwrite
psect	text528,local,class=CODE,delta=2
global __ptext528
__ptext528:

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
psect	text528
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
	
l13094:	
;uart.c: 74: RC3=1;;
	movlb 0	; select bank0
	bsf	(115/8),(115)&7
	line	76
;uart.c: 76: while(!TRMT);
	goto	l4822
	
l4823:	
	
l4822:	
	movlb 3	; select bank3
	btfss	(3313/8)^0180h,(3313)&7
	goto	u201
	goto	u200
u201:
	goto	l4822
u200:
	goto	l13096
	
l4824:	
	line	78
	
l13096:	
;uart.c: 78: TXREG=c;
	movf	(UARTwrite@c),w
	movwf	(410)^0180h	;volatile
	line	80
	
l13098:	
;uart.c: 80: RC3=0;;
	movlb 0	; select bank0
	bcf	(115/8),(115)&7
	line	81
	
l4825:	
	return
	opt stack 0
GLOBAL	__end_of_UARTwrite
	__end_of_UARTwrite:
;; =============== function _UARTwrite ends ============

	signat	_UARTwrite,4216
	global	_UARTread
psect	text529,local,class=CODE,delta=2
global __ptext529
__ptext529:

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
psect	text529
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
	line	56
	global	__size_of_UARTread
	__size_of_UARTread	equ	__end_of_UARTread-_UARTread
	
_UARTread:	
	opt	stack 13
; Regs used in _UARTread: [wreg+fsr1l-status,0]
	line	59
	
l14268:	
;uart.c: 57: unsigned char temp;
;uart.c: 59: while(rtail==rhead);
	goto	l14270
	
l4817:	
	goto	l14270
	
l4816:	
	
l14270:	
	movf	(_rtail),w	;volatile
	xorwf	(_rhead),w	;volatile
	skipnz
	goto	u2591
	goto	u2590
u2591:
	goto	l14270
u2590:
	
l4818:	
	line	62
;uart.c: 62: GIE=0;
	bcf	(95/8),(95)&7
	line	63
	
l14272:	
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
	
l14274:	
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
	
l14276:	
;uart.c: 66: GIE=1;
	bsf	(95/8),(95)&7
	line	68
	
l14278:	
;uart.c: 68: return temp;
	movf	(UARTread@temp),w
	goto	l4819
	
l14280:	
	line	69
	
l4819:	
	return
	opt stack 0
GLOBAL	__end_of_UARTread
	__end_of_UARTread:
;; =============== function _UARTread ends ============

	signat	_UARTread,89
	global	_getADC
psect	text530,local,class=CODE,delta=2
global __ptext530
__ptext530:

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
;;		_I2Cworker
;;		_I2CDACworker
;; This function uses a non-reentrant model
;;
psect	text530
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
	
l14414:	
;adc.c: 17: int i;
;adc.c: 20: ADCON1=0b11000000;
	movlw	(0C0h)
	movlb 1	; select bank1
	movwf	(158)^080h	;volatile
	line	21
	
l14416:	
;adc.c: 21: adc&=0x1F;
	movlw	(01Fh)
	movlb 0	; select bank0
	movwf	(??_getADC+0)+0
	movf	(??_getADC+0)+0,w
	andwf	(getADC@adc),f
	line	22
	
l14418:	
;adc.c: 22: ADCON0=0x01|(adc<<2);
	movf	(getADC@adc),w
	movwf	(??_getADC+0)+0
	movlw	(02h)-1
u2645:
	lslf	(??_getADC+0)+0,f
	addlw	-1
	skipz
	goto	u2645
	lslf	(??_getADC+0)+0,w
	iorlw	01h
	movlb 1	; select bank1
	movwf	(157)^080h	;volatile
	line	24
	
l14420:	
;adc.c: 24: for(i=0; i<4; i++) asm("nop");
	clrf	(getADC@i)
	clrf	(getADC@i+1)
	
l14422:	
	movf	(getADC@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(04h))^80h
	subwf	btemp+1,w
	skipz
	goto	u2655
	movlw	low(04h)
	subwf	(getADC@i),w
u2655:

	skipc
	goto	u2651
	goto	u2650
u2651:
	goto	l9520
u2650:
	goto	l9521
	
l14424:	
	goto	l9521
	
l9520:	
# 24 "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\adc.c"
nop ;#
psect	text530
	
l14426:	
	movlw	low(01h)
	addwf	(getADC@i),f
	movlw	high(01h)
	addwfc	(getADC@i+1),f
	
l14428:	
	movf	(getADC@i+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(04h))^80h
	subwf	btemp+1,w
	skipz
	goto	u2665
	movlw	low(04h)
	subwf	(getADC@i),w
u2665:

	skipc
	goto	u2661
	goto	u2660
u2661:
	goto	l9520
u2660:
	
l9521:	
	line	26
;adc.c: 26: ADCON0bits.ADGO=1;
	movlb 1	; select bank1
	bsf	(157)^080h,1	;volatile
	line	27
;adc.c: 27: while(ADCON0bits.ADGO);
	goto	l9522
	
l9523:	
	
l9522:	
	btfsc	(157)^080h,1	;volatile
	goto	u2671
	goto	u2670
u2671:
	goto	l9522
u2670:
	goto	l14430
	
l9524:	
	line	29
	
l14430:	
;adc.c: 29: ADCON0&=0xFE;
	movlw	(0FEh)
	movlb 0	; select bank0
	movwf	(??_getADC+0)+0
	movf	(??_getADC+0)+0,w
	movlb 1	; select bank1
	andwf	(157)^080h,f	;volatile
	line	30
	
l14432:	
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
	goto	l9525
	
l14434:	
	line	31
	
l9525:	
	return
	opt stack 0
GLOBAL	__end_of_getADC
	__end_of_getADC:
;; =============== function _getADC ends ============

	signat	_getADC,4218
	global	_enableTS
psect	text531,local,class=CODE,delta=2
global __ptext531
__ptext531:

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
;;		_I2Cworker
;; This function uses a non-reentrant model
;;
psect	text531
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\adc.c"
	line	35
	global	__size_of_enableTS
	__size_of_enableTS	equ	__end_of_enableTS-_enableTS
	
_enableTS:	
	opt	stack 13
; Regs used in _enableTS: [wreg+status,2+status,0]
	line	36
	
l14208:	
;adc.c: 36: FVRCON|=0b00100000;
	movlb 2	; select bank2
	bsf	(279)^0100h+(5/8),(5)&7	;volatile
	line	37
	
l14210:	
;adc.c: 37: FVRCON&=0b11101111;
	movlw	(0EFh)
	movwf	(??_enableTS+0)+0
	movf	(??_enableTS+0)+0,w
	andwf	(279)^0100h,f	;volatile
	line	38
	
l9528:	
	return
	opt stack 0
GLOBAL	__end_of_enableTS
	__end_of_enableTS:
;; =============== function _enableTS ends ============

	signat	_enableTS,88
	global	_I2CWrite
psect	text532,local,class=CODE,delta=2
global __ptext532
__ptext532:

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
;;		_I2Cworker
;;		_I2CEEworker
;;		_I2CDACworker
;; This function uses a non-reentrant model
;;
psect	text532
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
	
l3233:	
	line	185
;i2c.c: 184: {
;i2c.c: 185: SSP2CON1bits.WCOL=0;
	movlb 4	; select bank4
	bcf	(541)^0200h,7	;volatile
	line	186
	
l14204:	
;i2c.c: 186: SSP2BUF=c;
	movf	(I2CWrite@c),w
	movwf	(537)^0200h	;volatile
	line	187
	
l14206:	
;i2c.c: 187: } while(SSP2CON1bits.WCOL);
	btfsc	(541)^0200h,7	;volatile
	goto	u2511
	goto	u2510
u2511:
	goto	l3233
u2510:
	
l3234:	
	line	188
;i2c.c: 188: SSP2CON1bits.CKP=1;
	bsf	(541)^0200h,4	;volatile
	line	189
	
l3235:	
	return
	opt stack 0
GLOBAL	__end_of_I2CWrite
	__end_of_I2CWrite:
;; =============== function _I2CWrite ends ============

	signat	_I2CWrite,4216
	global	_initUART
psect	text533,local,class=CODE,delta=2
global __ptext533
__ptext533:

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
psect	text533
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\uart.c"
	line	13
	global	__size_of_initUART
	__size_of_initUART	equ	__end_of_initUART-_initUART
	
_initUART:	
	opt	stack 13
; Regs used in _initUART: [wreg+fsr1l-status,0]
	line	15
	
l14112:	
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
	
l14114:	
;uart.c: 22: SPBRGH=0x00;
	clrf	(412)^0180h	;volatile
	line	23
	
l14116:	
;uart.c: 23: SPBRGL=25;
	movlw	(019h)
	movwf	(411)^0180h	;volatile
	line	26
	
l14118:	
;uart.c: 26: SYNC=0;
	bcf	(3316/8)^0180h,(3316)&7
	line	27
	
l14120:	
;uart.c: 27: SPEN=1;
	bsf	(3311/8)^0180h,(3311)&7
	line	28
	
l14122:	
;uart.c: 28: TXEN=1;
	bsf	(3317/8)^0180h,(3317)&7
	line	29
	
l14124:	
;uart.c: 29: CREN=1;
	bsf	(3308/8)^0180h,(3308)&7
	line	32
	
l14126:	
;uart.c: 32: RCIE=1;
	movlb 1	; select bank1
	bsf	(1165/8)^080h,(1165)&7
	line	33
	
l14128:	
;uart.c: 33: TXIE=0;
	bcf	(1164/8)^080h,(1164)&7
	line	36
	
l14130:	
;uart.c: 36: rhead=0;
	clrf	(_rhead)	;volatile
	line	37
	
l14132:	
;uart.c: 37: rtail=0;
	clrf	(_rtail)	;volatile
	line	38
	
l14134:	
;uart.c: 38: for(i=0; i<(8-1); i++)
	clrf	(initUART@i)
	
l14136:	
	movlw	(07h)
	subwf	(initUART@i),w
	skipc
	goto	u2421
	goto	u2420
u2421:
	goto	l14140
u2420:
	goto	l4809
	
l14138:	
	goto	l4809
	line	39
	
l4808:	
	line	40
	
l14140:	
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
	
l14142:	
	movlw	(01h)
	movwf	(??_initUART+0)+0
	movf	(??_initUART+0)+0,w
	addwf	(initUART@i),f
	
l14144:	
	movlw	(07h)
	subwf	(initUART@i),w
	skipc
	goto	u2431
	goto	u2430
u2431:
	goto	l14140
u2430:
	
l4809:	
	line	43
;uart.c: 41: }
;uart.c: 43: RC5=1;;
	movlb 0	; select bank0
	bsf	(117/8),(117)&7
	line	44
	
l4810:	
	return
	opt stack 0
GLOBAL	__end_of_initUART
	__end_of_initUART:
;; =============== function _initUART ends ============

	signat	_initUART,88
	global	_initI2C
psect	text534,local,class=CODE,delta=2
global __ptext534
__ptext534:

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
psect	text534
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\i2c.c"
	line	15
	global	__size_of_initI2C
	__size_of_initI2C	equ	__end_of_initI2C-_initI2C
	
_initI2C:	
	opt	stack 13
; Regs used in _initI2C: [wreg+status,2+status,0]
	line	18
	
l12886:	
;i2c.c: 18: SSP2BUF=0x00;
	movlb 4	; select bank4
	clrf	(537)^0200h	;volatile
	line	19
	
l12888:	
;i2c.c: 19: SSP2STAT=0x80;
	movlw	(080h)
	movwf	(540)^0200h	;volatile
	line	20
	
l12890:	
;i2c.c: 20: SSP2MSK=0xFE;
	movlw	(0FEh)
	movwf	(539)^0200h	;volatile
	line	21
	
l12892:	
;i2c.c: 21: SSP2CON1=0x36;
	movlw	(036h)
	movwf	(541)^0200h	;volatile
	line	22
	
l12894:	
;i2c.c: 22: SSP2CON3|=0b11000000;
	movlw	(0C0h)
	movwf	(??_initI2C+0)+0
	movf	(??_initI2C+0)+0,w
	iorwf	(543)^0200h,f	;volatile
	line	23
	
l3180:	
	return
	opt stack 0
GLOBAL	__end_of_initI2C
	__end_of_initI2C:
;; =============== function _initI2C ends ============

	signat	_initI2C,88
	global	_initSPI
psect	text535,local,class=CODE,delta=2
global __ptext535
__ptext535:

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
psect	text535
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\spi.c"
	line	6
	global	__size_of_initSPI
	__size_of_initSPI	equ	__end_of_initSPI-_initSPI
	
_initSPI:	
	opt	stack 13
; Regs used in _initSPI: []
	line	8
	
l3238:	
	return
	opt stack 0
GLOBAL	__end_of_initSPI
	__end_of_initSPI:
;; =============== function _initSPI ends ============

	signat	_initSPI,88
	global	_SPIworker
psect	text536,local,class=CODE,delta=2
global __ptext536
__ptext536:

;; *************** function _SPIworker *****************
;; Defined at:
;;		line 11 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\spi.c"
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
psect	text536
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\spi.c"
	line	11
	global	__size_of_SPIworker
	__size_of_SPIworker	equ	__end_of_SPIworker-_SPIworker
	
_SPIworker:	
	opt	stack 14
; Regs used in _SPIworker: []
	line	13
	
l3241:	
	return
	opt stack 0
GLOBAL	__end_of_SPIworker
	__end_of_SPIworker:
;; =============== function _SPIworker ends ============

	signat	_SPIworker,88
	global	_isEE
psect	text537,local,class=CODE,delta=2
global __ptext537
__ptext537:

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
psect	text537
	file	"E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\easteregg.c"
	line	16
	global	__size_of_isEE
	__size_of_isEE	equ	__end_of_isEE-_isEE
	
_isEE:	
	opt	stack 14
; Regs used in _isEE: [wreg]
	line	17
	
l12882:	
;easteregg.c: 17: return 0;
	movlw	(0)
	goto	l6386
	
l12884:	
	line	18
	
l6386:	
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
;;		line 114 in file "E:\Work\dp\Breakout_Boards\Bus_Pirate_demo\Firmware\main.c"
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
	line	114
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
	line	115
;main.c: 115: do { if(RCIF) { RC3=1;; if(!(RCSTA&0b00000110)) { rhead++; rhead&=(8-1); ringbuff[rhead]=RCREG; } RCIF=0; RC3=0;; } if(TXIF) { TXIF=0; } } while(0);;
	
i1l1602:	
	btfss	(141/8),(141)&7
	goto	u244_21
	goto	u244_20
u244_21:
	goto	i1l14158
u244_20:
	
i1l14146:	
	bsf	(115/8),(115)&7
	
i1l14148:	
	movlb 3	; select bank3
	movf	(413)^0180h,w
	andlw	06h
	btfss	status,2
	goto	u245_21
	goto	u245_20
u245_21:
	goto	i1l14154
u245_20:
	
i1l14150:	
	movlw	(01h)
	movwf	(??_isr+0)+0
	movf	(??_isr+0)+0,w
	addwf	(_rhead),f	;volatile
	movlw	(07h)
	movwf	(??_isr+0)+0
	movf	(??_isr+0)+0,w
	andwf	(_rhead),f	;volatile
	
i1l14152:	
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
	goto	i1l14154
	
i1l1604:	
	
i1l14154:	
	movlb 0	; select bank0
	bcf	(141/8),(141)&7
	
i1l14156:	
	bcf	(115/8),(115)&7
	goto	i1l14158
	
i1l1603:	
	
i1l14158:	
	btfss	(140/8),(140)&7
	goto	u246_21
	goto	u246_20
u246_21:
	goto	i1l1609
u246_20:
	
i1l14160:	
	bcf	(140/8),(140)&7
	goto	i1l1609
	
i1l1605:	
	goto	i1l1609
	
i1l1606:	
	goto	i1l1609
	line	116
;main.c: 116: do { ;} while(0);;
	
i1l1607:	
	goto	i1l1609
	
i1l1608:	
	line	119
	
i1l1609:	
	movf	(??_isr+2),w
	movwf	btemp+1
	retfie
	opt stack 0
GLOBAL	__end_of_isr
	__end_of_isr:
;; =============== function _isr ends ============

	signat	_isr,88
psect	intentry
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
