;------------------------------------------------------------------------------
; Title:			ds30 loader for dsPIC33F
;
; File description:	Main firmwarefile
;
; Copyright: 		Copyright © 2009, Mikael Gustafsson
;
; Version			1.0.2 november 2009
;
; Webpage: 			http://mrmackey.no-ip.org/elektronik/ds30loader/
;
; History:			1.0.2 Erase is now made just before write to increase reliability
;					1.0.1 Fixed baudrate error check
;					1.0.0 Added flash verification
;						  Corrected buffer variable location to .bss
;						  Buffer is now correctly sized
;					0.9.4 Fixed config write, byte instead of word
;					0.9.3 Added code to restore pps settings
;						  Removed initialization of stack limit register
;						  BRG is rounded instead of truncated
;					0.9.2 Removed PLL and clockswitching code
;					0.9.1 Added pps code
;						  Added baudrate error check
;						  Added clockswitching for frc+ppl
;					0.9.0 First version released, based on the dsPIC30F version
;                                          
;------------------------------------------------------------------------------

;-----------------------------------------------------------------------------
;    This file is part of ds30 Loader.
;
;    ds30 Loader is free software: you can redistribute it and/or modify
;    it under the terms of the GNU General Public License as published by
;    the Free Software Foundation.
;
;    ds30 Loader is distributed in the hope that it will be useful,
;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;    GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License
;    along with ds30 Loader. If not, see <http://www.gnu.org/licenses/>.
;------------------------------------------------------------------------------ 

;------------------------------------------------------------------------------
;
; USAGE  USAGE  USAGE  USAGE  USAGE  USAGE  USAGE  USAGE  USAGE  USAGE  USAGE
;
;------------------------------------------------------------------------------
;
; This MPLAB-project comes preconfigured for the dsPIC33FJ256GP710 device using
; internal FRC and uart2
;
; To use other chip and/or configuration you need to do:
; * Select correct device in MPLAB IDE, menu Configure->Select Device
; * Include correct linker script
; * Search for xxx in settings.inc and check/alter those lines
; * If your device has the PPS(peripheral pin select) feature you need to configure that, template below, search for xxx
; * Put your own code in this file at designated areas, like i/o initialization etc. (optional)
; * No device specific errata workarounds are implemented in the code below
;
; Tabsize used is 4
;
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
; Register usage
;------------------------------------------------------------------------------
		;.equ	MIXED,		W0		;immediate
		.equ	DOERASE,	W1		;flag indicated erase should be done before next write
		.equ	WBUFPTR,	W2		;buffer pointer
		.equ	WCNT,		W3		;loop counter
		.equ	WADDR2,		W4		;memory pointer
		.equ	WADDR,		W5		;memory pointer
		.equ	PPSTEMP1,	W6		;used to restore pps register
		.equ	PPSTEMP2,	W7		;used to restore pps register
		;.equ	UNUSED,		W8		;
		;.equ	UNUSED,		W9		;
		.equ	WDEL1,		W10		;delay outer
		.equ	WDEL2,		W11		;delay inner
		;.equ	UNUSED,		W12		;
		.equ	WCMD,		W13		;command
		.equ 	WCRC, 		W14		;checksum
		.equ	WSTPTR,		W15		;stack pointer


;------------------------------------------------------------------------------
; Includes
;------------------------------------------------------------------------------
		.include "settings.inc"	


;-----------------------------------------------------------------------------
; UART stuff
;------------------------------------------------------------------------------ 
		.ifndef USE_UART1
			.ifndef USE_UART2
				.error "No uart is specified"
			.endif
		.endif
		
		.ifdef USE_UART1
			.ifdef USE_UART2
				.error "Both uarts are specified"
			.endif

		   	.equ    UMODE,	    U1MODE					;uart mode
		   	.equ    USTA,  		U1STA					;uart status
		   	.equ    UBRG,		U1BRG					;uart baudrate
		   	.equ    UTXREG,		U1TXREG					;uart transmit
		   	.equ	URXREG,		U1RXREG					;uart receive
			.equ	UIFS,		IFS0					;uart interupt flag sfr
			.equ	URXIF,		U1RXIF					;uart received interupt flag
			.equ	UTXIF,		U1TXIF					;uart transmit interupt flag		   	
		.endif
		
		.ifdef USE_UART2
			.ifndef HAS_UART2
				.error "UART2 specified for a device that only has uart1"
			.endif		
		
		   	.equ    UMODE,	    U2MODE					;uart mode
		   	.equ    USTA,  		U2STA					;uart status
		   	.equ    UBRG,		U2BRG					;uart baudrate
		   	.equ    UTXREG,		U2TXREG					;uart transmit
		   	.equ	URXREG,		U2RXREG					;uart receive
			.equ	UIFS,		IFS1					;uart interupt flag sfr
			.equ	URXIF,		U2RXIF					;uart received interupt flag
			.equ	UTXIF,		U2TXIF					;uart transmit interupt flag		   	
		.endif


;------------------------------------------------------------------------------
; Constants
;------------------------------------------------------------------------------
		.equ	VERMAJ,		1										/*firmware version major*/
		.equ	VERMIN,		0										/*fimrware version minor*/
		.equ	VERREV,		2										/*firmware version revision*/

		.equ 	HELLO, 		0xC1		
		.equ 	OK, 		'K'										/*erase/write ok*/
		.equ 	CHECKSUMERR,'N'										/*checksum error*/
		.equ	VERFAIL,	'V'										/*verification failed*/
		

		.equ	BLDELAY,	( BLTIME * (FCY / 1000) / (65536 * 7) )	/*delay before user application is loaded*/
		.equ	UARTBR,		( ((FCY / (BAUDRATE * 8)) - 1) / 2 )	/*brg calculation with rounding*/

		.equ	PAGESIZE,	512										/*words*/
		.equ	ROWSIZE,	64										/*words*/		
		.equ	STARTADDR,	( FLASHSIZE - PAGESIZE * 2 ) 			/*place bootloader in last program page*/


;------------------------------------------------------------------------------
; Validate user settings
;------------------------------------------------------------------------------
		; Internal cycle clock
		.if FCY > 40000000
			.error "Fcy specified is out of range"
		.endif

		; Baudrate error
		.equ REALBR,	( FCY / (16 * (UARTBR+1)) )
		.equ BAUDERR,	( (1000 * ( BAUDRATE - REALBR)) / BAUDRATE )
		.if ( BAUDERR > 25) || (BAUDERR < -25 )
			.error "Baudrate error is more than 2.5%. Remove this check or try another baudrate and/or clockspeed."
		.endif 
		

;------------------------------------------------------------------------------
; Global declarations
;------------------------------------------------------------------------------
        .global __reset          	;the label for the first line of code, needed by the linker script


;------------------------------------------------------------------------------
; Uninitialized variables in data memory
;------------------------------------------------------------------------------
		.bss
buffer:	.space ( ROWSIZE * 3 + 1/*checksum*/ ) 


;------------------------------------------------------------------------------
; Send macro
;------------------------------------------------------------------------------
		.macro SendL char
			mov #\char, W0
			mov W0, UTXREG
		.endm


;------------------------------------------------------------------------------
; Start of code section in program memory
;------------------------------------------------------------------------------
		.section *, code, address(STARTADDR-4)
usrapp:	nopr						;these two instructions will be replaced
		nopr						;with a goto to the user application by the pc program
		

;------------------------------------------------------------------------------
; Reset vector
;------------------------------------------------------------------------------
		.section *, code, address(STARTADDR)
__reset:mov		#__SP_init, WSTPTR	;initalize the Stack Pointer
		
		
;------------------------------------------------------------------------------
; User specific entry code go here, see also user exit code section at end of file
;------------------------------------------------------------------------------
		;setup the PLLFBD to 50 (/52) = 23952500Hz
		bclr	PLLFBD, #PLLDIV0
		bset	PLLFBD, #PLLDIV1
		bclr	PLLFBD, #PLLDIV2
		bclr	PLLFBD, #PLLDIV3
		bset	PLLFBD, #PLLDIV4
		bset	PLLFBD, #PLLDIV5
		bclr	PLLFBD, #PLLDIV6
		bclr	PLLFBD, #PLLDIV7
		bclr	PLLFBD, #PLLDIV8
		;wait for lock
waitforPLLlock: btss 	OSCCON, #LOCK		
				bra 	waitforPLLlock
		;----------------------------------------------------------------------
		; UART pps config
		;----------------------------------------------------------------------
		.ifdef HAS_PPS
			;.error "UART pps is not configured. Read datasheet and configure pps."			;xxx remove this line			
			
			; ** IMPORTANT **
			;
			; THIS CODE IS JUST A TEMPLATE AND WILL MOST LIKELY NOT WORK FOR YOU, 
			; READ THE DATASHEET AND ALTER LINES MARKED WITH XXX
			;
			; ** IMPORTANT **
			; 	//uart
			;	//RX PR14 (input)
			;	U1RXR_I = 14;
			;	//TX RP15 (output)
			;	RP15_O=U1TX_O;
			
			; Backup, these are restored in exit code at end of file
			; Changes needs to be done in exit, search for xxx
			mov		RPINR18, PPSTEMP1		;xxx
			mov		RPOR7, PPSTEMP2			;xxx

			;analog pins to digital
			bset	AD1PCFGL, #PCFG9
			bset	AD1PCFGL, #PCFG10

			; Receive, map pin (14 = 1110) to uart
			bset	TRISB, #TRISB14 		;make input (datasheet pg 157)
			bclr	RPINR18, #U1RXR0		;xxx
			bset	RPINR18, #U1RXR1		;xxx
			bset	RPINR18, #U1RXR2		;xxx
			bset	RPINR18, #U1RXR3		;xxx
			bclr	RPINR18, #U1RXR4		;xxx
					
			; Transmit, map uart to pin
			bset	RPOR7, #RP15R0			;xxx
			bset	RPOR7, #RP15R1			;xxx
			bclr	RPOR7, #RP15R2			;xxx
			bclr	RPOR7, #RP15R3			;xxx
			bclr	RPOR7, #RP15R4			;xxx		

			;LD1 on during bootload time
			bset LATA, #LATA8
			bclr TRISA, #TRISA8
		.endif	

      			
;------------------------------------------------------------------------------
; Init 
;------------------------------------------------------------------------------
		clr		DOERASE
		
		;UART
		mov		#UARTBR, W0 		;set	
		mov 	W0, UBRG			; baudrate
		bset 	UMODE, #UARTEN		;enable UART

;------------------------------------------------------------------------------
;	Echo test for debugging UART settings
;------------------------------------------------------------------------------

;echo test
;SendL 	DEVICEID
;echotest:	btss USTA, #URXDA		
;			bra echotest	
;echouart:	mov URXREG, W0
;			mov W0, UTXREG
;			bra echotest


;------------------------------------------------------------------------------
; Receive hello
; Added different delay method to deal with phantom byte
;------------------------------------------------------------------------------
		; Init delay
		mov 	#BLDELAY, WDEL1
		; Check for received byte
srpt1:	clr		WDEL2
srptc:	clrwdt						;clear watchdog
		btss 	USTA, #URXDA		
		bra 	snotrcv
		mov 	URXREG, W0			
		add 	WCRC, W0, WCRC		;add to checksum
		sub 	#HELLO, W0			;check
		bra 	z, gothello		;if(W0-#HELLO==0) goto gothello
 		; Delay
snotrcv:dec 	WDEL2, WDEL2
		bra 	nz, srptc
		dec 	WDEL1, WDEL1
		bra 	nz, srpt1
		; If we get here, uart receive timed out
		mov 	#__SP_init, WSTPTR	;reinitialize the Stack Pointer    
		bra		exit		;branch to the exit routine

;------------------------------------------------------------------------------
; Send device id and firmware version
;------------------------------------------------------------------------------
gothello:	bset 	USTA, #UTXEN		;enable TX after RX, to avoid backpowering FTDI chip	
			NOP
			SendL 	DEVICEID
			SendL	VERMAJ
			SendL	(VERMIN*16 + VERREV)
		

;------------------------------------------------------------------------------
; Main
;------------------------------------------------------------------------------
		; Send ok
Main:	SendL 	OK

		; Init checksum
main1:	clr 	WCRC

	
		;----------------------------------------------------------------------
		; Receive address
		;----------------------------------------------------------------------
		; Upper byte
		rcall 	Receive
		mov 	W0, TBLPAG
		; High byte, use PR1 as temporary sfr
		rcall 	Receive		
		mov.b	WREG, PR1+1
		; Low byte, use PR1 as temporary sfr
		rcall 	Receive
		mov.b	WREG, PR1
		;
		mov		PR1, WREG
		mov		W0,	WADDR
		mov		W0, WADDR2
		
		
		;----------------------------------------------------------------------
		; Receive command
		;----------------------------------------------------------------------
		rcall 	Receive
		mov		W0, WCMD
		

		;----------------------------------------------------------------------
		; Receive nr of data bytes that will follow
		;----------------------------------------------------------------------
		rcall 	Receive				
		mov 	W0, WCNT
	

		;----------------------------------------------------------------------
		; Receive data		
		;----------------------------------------------------------------------
		mov 	#buffer, WBUFPTR
rcvdata:
		rcall 	Receive				
		mov.b 	W0, [WBUFPTR++]
		dec		WCNT, WCNT
		bra 	nz, rcvdata			;last byte received is checksum		
		
				
		;----------------------------------------------------------------------
		; Check checksum
		;----------------------------------------------------------------------
		cp0.b 	WCRC
		bra 	z, ptrinit
		SendL 	CHECKSUMERR
		bra 	main1			
		
	
		;----------------------------------------------------------------------
		; Init pointer
		;----------------------------------------------------------------------			
ptrinit:mov 	#buffer, WBUFPTR
		
		
		;----------------------------------------------------------------------
		; Check command
		;----------------------------------------------------------------------			
		; Write row				0x00 02 00 - 0x02 AC 00 
		btsc	WCMD,	#1		
		bra		erase
		; Write config byte		0xF8 00 00 - 0xF8 00 0E
		btsc	WCMD, #3
		bra		config
		; Else erase page
		mov		#0xffff, DOERASE
		bra		Main
		
			
		;----------------------------------------------------------------------		
		; Erase page
		;----------------------------------------------------------------------		
erase:	btss	DOERASE, #0
		bra		program
		tblwtl	WADDR, [WADDR]		;"Set base address of erase block", equivalent to setting nvmadr/u in dsPIC30F?
		; Erase
		mov 	#0x4042, W0
		rcall 	Write	
		; Erase finished
		clr		DOERASE
		
		
		;----------------------------------------------------------------------		
		; Write row
		;----------------------------------------------------------------------		
program:mov 	#ROWSIZE, WCNT
		; Load latches
latlo:	tblwth.b 	[WBUFPTR++], [WADDR] 	;upper byte
		tblwtl.b	[WBUFPTR++], [WADDR++] 	;low byte
		tblwtl.b	[WBUFPTR++], [WADDR++] 	;high byte	
		dec 	WCNT, WCNT
		bra 	nz, latlo
		; Write flash row
		mov 	#0x4001, W0		
		rcall 	Write
		
		
		;----------------------------------------------------------------------		
		; Verify row
		;----------------------------------------------------------------------	
		mov 	#ROWSIZE, WCNT
		mov 	#buffer, WBUFPTR	
		; Verify upper byte
verrow:	tblrdh.b [WADDR2], W0
		cp.b	W0, [WBUFPTR++]
		bra		NZ, vfail	
		; Verify low byte
		tblrdl.b [WADDR2++], W0
		cp.b	W0, [WBUFPTR++]
		bra		NZ, vfail
		; Verify high byte
		tblrdl.b [WADDR2++], W0
		cp.b	W0, [WBUFPTR++]
		bra		NZ, vfail
		;
		dec		WCNT, WCNT
		bra 	nz, verrow
		bra		Main
		
		
		;----------------------------------------------------------------------
		; Verify fail
		;----------------------------------------------------------------------
vfail:	SendL	VERFAIL
		bra		main1
		
				
		;----------------------------------------------------------------------
		; Write config byte
		;----------------------------------------------------------------------
		; Load latch
config:	tblwtl.b [WBUFPTR], [WADDR]			
		; Write config byte
		mov 	#0x4000, W0
		rcall 	Write
		; Write finished
		bra 	Main
			
		
;------------------------------------------------------------------------------
; Write
;------------------------------------------------------------------------------
Write:	mov 	W0, NVMCON
		mov 	#0x55, W0
		mov 	W0, NVMKEY
		mov 	#0xAA, W0
		mov 	W0, NVMKEY
		bset 	NVMCON, #WR
		nop
		nop	
		; Wait for erase/write to finish	
compl:	btsc	NVMCON, #WR		
		bra 	compl				
		return


;------------------------------------------------------------------------------
; Receive
;------------------------------------------------------------------------------
		; Init delay
Receive:mov 	#BLDELAY, WDEL1
		; Check for received byte
rpt1:	clr		WDEL2
rptc:	clrwdt						;clear watchdog
		btss 	USTA, #URXDA		
		bra 	notrcv
		mov 	URXREG, W0			
		add 	WCRC, W0, WCRC		;add to checksum
		return
 		; Delay
notrcv:	dec 	WDEL2, WDEL2
		bra 	nz, rptc
		dec 	WDEL1, WDEL1
		bra 	nz, rpt1
		; If we get here, uart receive timed out
		mov 	#__SP_init, WSTPTR	;reinitialize the Stack Pointer    

;------------------------------------------------------------------------------
; Exit point, clean up and load user application
;------------------------------------------------------------------------------		
exit:	bclr	UIFS, #URXIF		;clear uart received interupt flag
		bclr	UIFS, #UTXIF		;clear uart transmit interupt flag
		bclr	USTA, #UTXEN		;disable uart transmit
		bclr 	UMODE, #UARTEN		;disable uart
		clr		PR1					;clear PR1, was used as temporary sfr
		bclr 	LATA, #LATA8		;turn off LD1, done with bootloader

;------------------------------------------------------------------------------
; User specific exit code go here
;------------------------------------------------------------------------------
		.ifdef HAS_PPS
			;.error "PPS restoration is not configured."			;xxx remove this line
			mov		PPSTEMP1, RPINR18	;xxx restore 
			mov		PPSTEMP2, RPOR7		;xxx  pps settings
		.endif

;	never ending loop for debugging
;		bra  lp1
;lp1: 	bra lp2
;lp2: 	bra lp1   

;------------------------------------------------------------------------------
; Load user application
;------------------------------------------------------------------------------
        bra 	usrapp

	
;------------------------------------------------------------------------------
; End of code
;------------------------------------------------------------------------------
		.end

 
