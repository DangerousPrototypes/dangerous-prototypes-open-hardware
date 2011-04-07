;------------------------------------------------------------------------------
;
; Title:			ds30 loader for dsPIC33
;
; File description:	user settings and configuration bits
;
; Copyright: 		Copyright © 2009, Mikael Gustafsson
;
; Webpage: 			http://mrmackey.no-ip.org/elektronik/ds30loader/
;
; History:			1.0.1 -
;					1.0.0 -
;					0.9.4 -
;					0.9.3 Removed 1-way pps config
;					0.9.2 Removed PLL settings
;						  Adde config to incativate 1-way pps
;					0.9.1 Only one clock option in this file
;					0.9.0 First version of this file
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
; Device
;------------------------------------------------------------------------------
        .equ 		__33FJ128GP204, 	1		;xxx


;------------------------------------------------------------------------------
; Includes 
;------------------------------------------------------------------------------
        .include	"devices.inc"


;------------------------------------------------------------------------------
; User preferences
;------------------------------------------------------------------------------
		.equ 	FCY, 		39958561			;xxx speed of internal cycle clock[Hz], used to calculate uart brg and delay
		.equ 	BAUDRATE, 	256000				;xxx baudrate
		
		.equ	BLTIME,		3000				;xxx time in ms before bootloader loads the user application
        .equ    USE_UART1,	1					;xxx uncomment to use uart1
        ;.equ	USE_UART2,	1					;xxx uncomment to use uart2


;------------------------------------------------------------------------------
; Configuration bits, these macros can be found at the end of the inc-files located in 
; c:\Program files\Microchip\MPLAB ASM30 Suite\Support\dsPIC33F\inc
;
; These can also be set in MPLAB IDE instead, they are found in Configure->Configuration bits...
;------------------------------------------------------------------------------
		;config 	__FBS, 		RBS_NO_RAM & BSS_NO_FLASH & BWRP_WRPROTECT_OFF	;xxx boot segment
		;config 	__FSS, 		RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF	;xxx secure segment
		;config 	__FGS,		GSS_OFF & GCP_OFF & GWRP_OFF					;xxx general segment
		config 	__FOSCSEL, 	FNOSC_FRC & IESO_OFF 							;xxx oscillator mode
		config 	__FOSC, 	FCKSM_CSECMD & IOL1WAY_OFF & OSCIOFNC_ON & POSCMD_XT			;xxx clock switching/clock monitor, osc2 & oscillator selection
		;config	__FWDT,		FWDTEN_OFF & WINDIS_OFF							;xxx watchdog
		;config	__FPOR,		FPWRT_PWR1										;xxx pwm, power-on reset
		;config	__FICD,		ICS_PGD1
