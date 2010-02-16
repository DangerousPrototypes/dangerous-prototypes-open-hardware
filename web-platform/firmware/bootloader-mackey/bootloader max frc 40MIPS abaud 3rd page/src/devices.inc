;------------------------------------------------------------------------------
;
; Title:			ds30 loader for dsPIC33
;
; File description:	Device specific constants
;
; Copyright: 		Copyright © 09-10, Mikael Gustafsson
;
; Webpage: 			http://mrmackey.no-ip.org/elektronik/ds30loader/
;
; History:			1.0.3 -
;					1.0.2 -
;					1.0.1 -
;					1.0.0 -
;					0.9.4 -
;					0.9.3 -
;					0.9.2 -
;					0.9.1 Added pps equ
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
;    along with ds30 Loader. If not, see <http:;www.gnu.org/licenses/>.
;------------------------------------------------------------------------------ 


;------------------------------------------------------------------------------
; Devices dsPIC33F - 6kB
;------------------------------------------------------------------------------ 
.ifdef __33FJ06GS101 
	.include	"p33FJ06GS101.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x1000
	.equ		DEVICEID,	100
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ06GS102 
	.include	"p33FJ06GS102.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x1000
	.equ		DEVICEID,	101
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ06GS202 
	.include	"p33FJ06GS202.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x1000
	.equ		DEVICEID,	102
	.equ		HAS_PPS,	1
.endif


;------------------------------------------------------------------------------
; Devices dsPIC33F - 12kB
;------------------------------------------------------------------------------ 
.ifdef __33FJ12GP201 
	.include	"p33FJ12GP201.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2000
	.equ		DEVICEID,	110
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ12GP202 
	.include	"p33FJ12GP202.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2000
	.equ		DEVICEID,	111
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ12MC201 
	.include	"p33FJ12MC201.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2000
	.equ		DEVICEID,	112
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ12MC202 
	.include	"p33FJ12MC202.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2000
	.equ		DEVICEID,	113
	.equ		HAS_PPS,	1
.endif


;------------------------------------------------------------------------------
; Devices dsPIC33F - 16kB
;------------------------------------------------------------------------------ 
.ifdef __33FJ16GP304 
	.include	"p33FJ16GP304.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2C00
	.equ		DEVICEID,	120
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ16GS402 
	.include	"p33FJ16GS402.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2C00
	.equ		DEVICEID,	121
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ16GS404 
	.include	"p33FJ16GS404.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2C00
	.equ		DEVICEID,	122
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ16GS502 
	.include	"p33FJ16GS502.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2C00
	.equ		DEVICEID,	123
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ16GS504 
	.include	"p33FJ16GS504.inc"
	.equ		VALID_DEV, 1	
	.equ		FLASHSIZE,	0x2C00
	.equ		DEVICEID,	124
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ16MC304 
	.include	"p33FJ16MC304.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2C00
	.equ		DEVICEID,	125
	.equ		HAS_PPS,	1
.endif


;------------------------------------------------------------------------------
; Devices dsPIC33F - 32kB
;------------------------------------------------------------------------------ 
.ifdef __33FJ32GP202 
	.include	"p33FJ32GP202.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x5800
	.equ		DEVICEID,	130
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ32GP204 
	.include	"p33FJ32GP204.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x5800
	.equ		DEVICEID,	131
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ32GP302 
	.include	"p33FJ32GP302.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x5800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	132
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ32GP304 
	.include	"p33FJ32GP304.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x5800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	133
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ32MC202 
	.include	"p33FJ32MC202.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x5800
	.equ		DEVICEID,	134
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ32MC204 
	.include	"p33FJ32MC204.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x5800
	.equ		DEVICEID,	135
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ32MC302 
	.include	"p33FJ32MC302.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x5800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	136
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ32MC304 
	.include	"p33FJ32MC304.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x5800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	137
	.equ		HAS_PPS,	1
.endif


;------------------------------------------------------------------------------
; Devices dsPIC33F - 64kB
;------------------------------------------------------------------------------ 
.ifdef __33FJ64GP202 
	.include	"p33FJ64GP202.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	140
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ64GP204 
	.include	"p33FJ64GP204.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	141
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ64GP206 
	.include	"p33FJ64GP206.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	142
.endif
.ifdef __33FJ64GP306 
	.include	"p33FJ64GP306.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	143
.endif
.ifdef __33FJ64GP310 
	.include	"p33FJ64GP310.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	144
.endif
.ifdef __33FJ64GP706 
	.include	"p33FJ64GP706.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	145
.endif
.ifdef __33FJ64GP706A 
	.include	"p33FJ64GP706A.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	146
.endif
.ifdef __33FJ64GP708 
	.include	"p33FJ64GP708.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	147
.endif
.ifdef __33FJ64GP710 
	.include	"p33FJ64GP710.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	148
.endif
.ifdef __33FJ64GP802 
	.include	"p33FJ64GP802.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	149
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ64GP804 
	.include	"p33FJ64GP804.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	150
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ64MC202 
	.include	"p33FJ64MC202.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	151
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ64MC204 
	.include	"p33FJ64MC204.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	152
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ64MC506 
	.include	"p33FJ64MC506.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	153
.endif
.ifdef __33FJ64MC508 
	.include	"p33FJ64MC508.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	154
.endif
.ifdef __33FJ64MC510 
	.include	"p33FJ64MC510.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	155
.endif
.ifdef __33FJ64MC510A 
	.include	"p33FJ64MC510A.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	156
.endif
.ifdef __33FJ64MC706 
	.include	"p33FJ64MC706.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	157
.endif
.ifdef __33FJ64MC710 
	.include	"p33FJ64MC710.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	158
.endif
.ifdef __33FJ64MC802 
	.include	"p33FJ64MC802.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	159
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ64MC804 
	.include	"p33FJ64MC804.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0xAC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	160
	.equ		HAS_PPS,	1
.endif


;------------------------------------------------------------------------------
; Devices dsPIC33F - 128kB
;------------------------------------------------------------------------------ 
.ifdef __33FJ128GP202 
	.include	"p33FJ128GP202.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	170
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ128GP204 
	.include	"p33FJ128GP204.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	171
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ128GP206 
	.include	"p33FJ128GP206.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	172
.endif
.ifdef __33FJ128GP206A 
	.include	"p33FJ128GP206A.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	173
.endif
.ifdef __33FJ128GP306 
	.include	"p33FJ128GP306.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	174
.endif
.ifdef __33FJ128GP306A 
	.include	"p33FJ128GP306A.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	175
.endif
.ifdef __33FJ128GP310 
	.include	"p33FJ128GP310.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	176
.endif
.ifdef __33FJ128GP706 
	.include	"p33FJ128GP706.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	177
.endif
.ifdef __33FJ128GP708 
	.include	"p33FJ128GP708.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	178
.endif
.ifdef __33FJ128GP710 
	.include	"p33FJ128GP710.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	179
.endif
.ifdef __33FJ128GP802 
	.include	"p33FJ128GP802.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	180
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ128GP804 
	.include	"p33FJ128GP804.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	181
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ128MC202 
	.include	"p33FJ128MC202.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	182
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ128MC204 
	.include	"p33FJ128MC204.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	183
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ128MC506 
	.include	"p33FJ128MC506.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	184
.endif
.ifdef __33FJ128MC510 
	.include	"p33FJ128MC510.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	185
.endif
.ifdef __33FJ128MC706 
	.include	"p33FJ128MC706.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	186
.endif
.ifdef __33FJ128MC708 
	.include	"p33FJ128MC708.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	187
.endif
.ifdef __33FJ128MC710 
	.include	"p33FJ128MC710.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	188
.endif
.ifdef __33FJ128MC802 
	.include	"p33FJ128MC802.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	189
	.equ		HAS_PPS,	1
.endif
.ifdef __33FJ128MC804 
	.include	"p33FJ128MC804.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x15800
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	190
	.equ		HAS_PPS,	1
.endif


;------------------------------------------------------------------------------
; Devices dsPIC33F - 256kB
;------------------------------------------------------------------------------ 
.ifdef __33FJ256GP506 
	.include	"p33FJ256GP506.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2AC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	195
.endif
.ifdef __33FJ256GP510 
	.include	"p33FJ256GP510.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2AC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	196
.endif
.ifdef __33FJ256GP710 
	.include	"p33FJ256GP710.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2AC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	197
.endif
.ifdef __33FJ256MC510 
	.include	"p33FJ256MC510.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2AC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	198
.endif
.ifdef __33FJ256MC710 
	.include	"p33FJ256MC710.inc"
	.equ		VALID_DEV, 1
	.equ		FLASHSIZE,	0x2AC00
	.equ		HAS_UART2,	1
	.equ		DEVICEID,	199
.endif


;------------------------------------------------------------------------------
; 
;------------------------------------------------------------------------------ 
.ifndef VALID_DEV
	.error "Unknown device specified"
.endif
