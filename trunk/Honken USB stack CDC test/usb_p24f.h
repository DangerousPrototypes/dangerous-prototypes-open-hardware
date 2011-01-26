/*
This work is licensed under the Creative Commons Attribution 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
or send a letter to
	Creative Commons,
	171 Second Street,
	Suite 300,
	San Francisco,
	California,
	94105,
	USA.
*/

#ifndef __USB_P24F_H__
#define __USB_P24F_H__

#include <p24fxxxx.h>

/* Bitmasks */
#define USB_UEP_EPHSHK 		(0x01)
#define USB_UEP_EPSTALL		(0x02)
#define USB_UEP_EPINEN		(0x04)
#define USB_UEP_EPOUTEN 	(0x08)
#define USB_UEP_EPCONDIS	(0x10)

#define USB_EP_INOUT		(USB_UEP_EPHSHK | USB_UEP_EPINEN | USB_UEP_EPOUTEN | USB_UEP_EPCONDIS)
#define USB_EP_CONTROL		(USB_UEP_EPHSHK | USB_UEP_EPINEN | USB_UEP_EPOUTEN)
#define USB_EP_OUT			(USB_UEP_EPHSHK |                  USB_UEP_EPOUTEN | USB_UEP_EPCONDIS)
#define USB_EP_IN			(USB_UEP_EPHSHK | USB_UEP_EPINEN                   | USB_UEP_EPCONDIS)
#define USB_EP_NONE			(0x00)

#define USB_EP_INTERRUPT	(0)
#define USB_EP_BULK			(1)
#define	USB_EP_ISOCHRONOUS	(2)

typedef unsigned char usb_uep_t;
#define USB_UEP				((usb_uep_t*) (&U1EP0))
#define USB_UEP0			U1EP0
#define USB_UEP1			U1EP1
#define USB_UEP2			U1EP2
#define USB_UEP3			U1EP3
#define USB_UEP4			U1EP4
#define USB_UEP5			U1EP5
#define USB_UEP6			U1EP6
#define USB_UEP7			U1EP7
#define USB_UEP8			U1EP8
#define USB_UEP9			U1EP9
#define USB_UEP10			U1EP10
#define USB_UEP11			U1EP11
#define USB_UEP12			U1EP12
#define USB_UEP13			U1EP13
#define USB_UEP14			U1EP14
#define USB_UEP15			U1EP15

/* Interrupt */
#define USB_STALL				0x0080
#define USB_ACTIV				0x0020
#define USB_IDLE				0x0010
#define USB_TRN					0x0008
#define USB_SOF					0x0004
#define USB_UERR				0x0002
#define USB_URST				0x0001

/* Interrupt 18F*/
#if 0
#define USB_SOF				0x40
#define USB_STALL			0x20
#define USB_IDLE			0x10
#define USB_TRN				0x08
#define USB_ACTIV			0x04
#define USB_UERR			0x02
#define USB_URST			0x01
#endif

#define USB_RESET_FLAG						U1IRbits.URSTIF
#define USB_ERROR_FLAG						U1IRbits.UERRIF
#define USB_ACTIVITY_FLAG					U1IRbits.RESUMEIF
#define USB_IDLE_FLAG						U1IRbits.IDLEIF
#define USB_STALL_FLAG						U1IRbits.STALLIF
#define USB_SOF_FLAG						U1IRbits.SOFIF
#define USB_TRANSACTION_FLAG				U1IRbits.TRNIF

#define UsbInterruptFlags()					(U1IR)
#define UsbErrorInterruptFlags()			(U1EIR)

#define ClearUsbInterruptFlag(x)			U1IR &= ~(x)
#define ClearAllUsbInterruptFlags()			U1IR = 0
#define ClearUsbErrorInterruptFlag(x)		U1EIR &= ~(x)
#define ClearAllUsbErrorInterruptFlags()	U1EIR = 0
#define DisableUsbInterrupts()				IEC5bits.USB1IE=0 //PIE2bits.USBIE = 0 /*FIX*/
#define DisableUsbInterrupt(x)				U1IE &= ~(x)
#define DisableAllUsbInterrupts()			U1IE = 0
#define DisableUsbErrorInterrupt(x)			U1EIE &= ~(x)
#define DisableAllUsbErrorInterrupts()		U1EIE = 0	
#define EnableUsbInterrupts()				IEC5bits.USB1IE=1 //PIE2bits.USBIE = 1 /*FIX*/
#define EnableUsbInterrupt(x)				U1IE |= (x)
#define EnableAllUsbInterrupts()			U1IE = 0x00FF
#define EnableUsbErrorInterrupt(x)			U1EIE |= (x)
#define EnableAllUsbErrorInterrupts()		U1EIE = 0x00FF

/* UCON */
#define ResetPPbuffers()					do {U1CONbits.PPBRST = 1; U1CONbits.PPBRST=0;} while(0)
#define SingleEndedZeroIsSet()				(U1CONbits.SE0)
#define EnablePacketTransfer()				U1CONbits.PKTDIS = 0
#define EnableUsb()							U1CONbits.USBEN = 1
#define SignalResume()						do {U1CONbits.RESUME = 1; delay_ms(10); U1CONbits.RESUME = 0;} while(0)
#define SuspendUsb()						U1PWRCbits.USUSPND = 1
#define WakeupUsb()							do {U1PWRCbits.USUSPND = 0; while(USB_ACTIVITY_FLAG){USB_ACTIVITY_FLAG = 0;}} while(0)

/* UADDR */
#define SetUsbAddress(x)					(U1ADDR = (x))
#define GetUsbAddress()						(U1ADDR)

/* USTAT */
typedef unsigned char usb_status_t;
#define GetUsbTransaction()					(U1STAT)
#define USB_STAT2EP(x)						((x>>3)&0x0F)
#define USB_STAT2DIR(x)						((x>>2)&0x01)
#define USB_STAT2ADDR(x)					((x>>2)&0x1F)
#define USB_STAT2PPI(x)						((x>>1)&0x01)

/* Hardware implementations */

#if defined USB_INTERNAL_PULLUPS
#elif defined USB_EXTERNAL_PULLUPS
#define USB_U1OTGCON_UPUEN_VALUE (0)
#else
#error "Neither internal nor external pullups defined"
#endif

#if defined USB_INTERNAL_TRANSCIEVER
#define USB_U1CNFG2_UTRDIS_VALUE (0)
#elif defined USB_EXTERNAL_TRANSCIEVER
#define USB_U1CNFG2_UTRDIS_VALUE (1)
#else
#error "Neither internal nor external transciever defined"
#endif

#if defined USB_FULL_SPEED_DEVICE
#if defined USB_INTERNAL_PULLUPS
#define USB_U1OTGCON_DPPULUP_VALUE (1<<7)
#define USB_U1OTGCON_DMPULUP_VALUE (0)
#else
#define USB_U1OTGCON_DPPULUP_VALUE (0)
#define USB_U1OTGCON_DMPULUP_VALUE (0)
#endif
#elif defined USB_LOW_SPEED_DEVICE
#if defined USB_INTERNAL_PULLUPS
#define USB_U1OTGCON_DPPULUP_VALUE (0)
#define USB_U1OTGCON_DMPULUP_VALUE (1<<6)
#else
#define USB_U1OTGCON_DPPULUP_VALUE (0)
#define USB_U1OTGCON_DMPULUP_VALUE (0)
#endif
#else
#error "Neither internal nor external pullups defined"
#endif

#if defined USB_BUS_POWERED
#ifndef usb_low_power_request
/* Default low power mode is DUD */
#define usb_low_power_request() Nop()
#endif
#ifndef usb_low_power_resume
#define usb_low_power_resume() Nop()
#endif
#elif defined USB_SELF_POWERED
#define usb_low_power_request() Nop()
#define usb_low_power_resume() Nop()
#else
#error "No source of device power defined"
#endif

#ifndef USB_INTERNAL_VREG
#warning "Use of internal voltage regulator not implemented. User must supply 3.3V on Vusb pin."
#endif

#define USB_DIR_OUT	0
#define USB_DIR_IN	1
#define USB_PP_EVEN	0
#define USB_PP_ODD	1

/* PingPong buffer descriptor table index calculations */
#if USB_PP_BUF_MODE == 0
#define USB_USTAT2BD(X)				( (X)/4 )
#define USB_CALC_BD(ep, dir, sync)	( 2*(ep)+(dir) )
#elif USB_PP_BUF_MODE == 1
#define USB_USTAT2BD(X)				( ((X)>2)? (X)/4+1 : (X)/2 )
#define USB_CALC_BD(ep, dir, sync)	( ((ep)==0 && (dir)==0)? (sync) : 2*(ep)+(dir) )
#elif USB_PP_BUF_MODE == 2
#define USB_USTAT2BD(X)				( (X)/2 )
#define USB_CALC_BD(ep, dir, sync)	( 4*(ep)+2*(dir)+(sync) )
#elif USB_PP_BUF_MODE == 3
#define USB_USTAT2BD(X)				( ((X)>4)? (X)/2-2 : (X)/4 )
#define USB_CALC_BD(ep, dir, sync)	( ((ep)==0)? (dir) : 4*(ep)+2*(dir)+(sync)-2 )
#else
#error "USB_PP_BUF_MODE outside scope."
#endif

#define ConfigureUsbHardware()		do { \
										U1CNFG1 = 0x0040 | USB_PP_BUF_MODE; \
										U1CNFG2 = USB_U1CNFG2_UTRDIS_VALUE; \
										U1BDTP1 = (unsigned int) usb_bdt/256; \										
										U1PWRCbits.USBPWR = 1; \
										U1OTGCON = USB_U1OTGCON_DPPULUP_VALUE | \
												   USB_U1OTGCON_DMPULUP_VALUE; \
									} while(0)
//TODO: Remove magic OEMON = 0x0040

#define ROM __attribute__((space(auto_psv)))
#define ROMPTR
#define ARCH_memcpy memcpy

#ifdef __DEBUG
#include <stdio.h>
#define DINIT()			/* TODO: Implement */
#define DPRINTF(...)	
#else
#define DINIT()
#define DPRINTF(...)
#endif

#endif//__USB_P24F_H__
