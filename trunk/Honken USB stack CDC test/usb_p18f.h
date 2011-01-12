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

#ifndef __USB_P18F_H__
#define __USB_P18F_H__

#include <p18cxxx.h>

/* Bitmasks */
#define USB_UEP_EPHSHK 		(0x10)
#define USB_UEP_EPCONDIS	(0x08)
#define USB_UEP_EPOUTEN 	(0x04)
#define USB_UEP_EPINEN		(0x02)
#define USB_UEP_EPSTALL		(0x01)

#define USB_EP_INOUT		(USB_UEP_EPHSHK | USB_UEP_EPINEN | USB_UEP_EPOUTEN | USB_UEP_EPCONDIS)
#define USB_EP_CONTROL		(USB_UEP_EPHSHK | USB_UEP_EPINEN | USB_UEP_EPOUTEN)
#define USB_EP_OUT			(USB_UEP_EPHSHK |                  USB_UEP_EPOUTEN | USB_UEP_EPCONDIS)
#define USB_EP_IN			(USB_UEP_EPHSHK | USB_UEP_EPINEN                   | USB_UEP_EPCONDIS)
#define USB_EP_NONE			(0x00)

#define USB_EP_INTERRUPT	(0)
#define USB_EP_BULK			(1)
#define	USB_EP_ISOCHRONOUS	(2)

typedef unsigned char usb_uep_t;
#define USB_UEP				((usb_uep_t*) (&UEP0))
#define USB_UEP0			UEP0
#define USB_UEP1			UEP1
#define USB_UEP2			UEP2
#define USB_UEP3			UEP3
#define USB_UEP4			UEP4
#define USB_UEP5			UEP5
#define USB_UEP6			UEP6
#define USB_UEP7			UEP7
#define USB_UEP8			UEP8
#define USB_UEP9			UEP9
#define USB_UEP10			UEP10
#define USB_UEP11			UEP11
#define USB_UEP12			UEP12
#define USB_UEP13			UEP13
#define USB_UEP14			UEP14
#define USB_UEP15			UEP15

/* Interrupt */
#define USB_SOF				0x40
#define USB_STALL			0x20
#define USB_IDLE			0x10
#define USB_TRN				0x08
#define USB_ACTIV			0x04
#define USB_UERR			0x02
#define USB_URST			0x01

#define USB_RESET_FLAG						UIRbits.URSTIF
#define USB_ERROR_FLAG						UIRbits.UERRIF
#define USB_ACTIVITY_FLAG					UIRbits.ACTVIF
#define USB_IDLE_FLAG						UIRbits.IDLEIF
#define USB_STALL_FLAG						UIRbits.STALLIF
#define USB_SOF_FLAG						UIRbits.SOFIF
#define USB_TRANSACTION_FLAG				UIRbits.TRNIF

#define UsbInterruptFlags()					(UIR)
#define UsbErrorInterruptFlags()			(UEIR)

#define ClearUsbInterruptFlag(x)			UIR &= ~(x)
#define ClearAllUsbInterruptFlags()			UIR = 0
#define ClearUsbErrorInterruptFlag(x)		UEIR &= ~(x)
#define ClearAllUsbErrorInterruptFlags()	UEIR = 0
#define DisableUsbInterrupts()				PIE2bits.USBIE = 0
#define DisableUsbInterrupt(x)				UIE &= ~(x)
#define DisableAllUsbInterrupts()			UIE = 0
#define DisableUsbErrorInterrupt(x)			UEIE &= ~(x)
#define DisableAllUsbErrorInterrupts()		UEIE = 0
#define EnableUsbInterrupts()				PIE2bits.USBIE = 1
#define EnableUsbInterrupt(x)				UIE |= (x)
#define EnableAllUsbInterrupts()			UIE = 0xFF
#define EnableUsbErrorInterrupt(x)			UEIE |= (x)
#define EnableAllUsbErrorInterrupts()		UEIE = 0xFF

/* UCON */
#define ResetPPbuffers()					do {UCONbits.PPBRST = 1; UCONbits.PPBRST=0;} while(0)
#define SingleEndedZeroIsSet()				(UCONbits.SE0)
#define EnablePacketTransfer()				UCONbits.PKTDIS = 0
#define EnableUsb()							UCONbits.USBEN = 1
#define SignalResume()						do {UCONbits.RESUME = 1; delay_ms(10); UCONbits.RESUME = 0;} while(0)
#define SuspendUsb()						UCONbits.SUSPND = 1
#define WakeupUsb()							do {UCONbits.SUSPND = 0; while(USB_ACTIVITY_FLAG){USB_ACTIVITY_FLAG = 0;}} while(0)

/* UADDR */
#define SetUsbAddress(x)					(UADDR = (x))
#define GetUsbAddress()						(UADDR)

/* USTAT */
typedef unsigned char usb_status_t;
#define GetUsbTransaction()					(USTAT)
#define USB_STAT2EP(x)						((x>>3)&0x0F)
#define USB_STAT2DIR(x)						((x>>2)&0x01)
#define USB_STAT2ADDR(x)					((x>>2)&0x1F)
#define USB_STAT2PPI(x)						((x>>1)&0x01)

/* Hardware implementations */

#if defined USB_INTERNAL_PULLUPS
#define USB_UCFG_UPUEN_VALUE (1<<4)
#elif defined USB_EXTERNAL_PULLUPS
#define USB_UCFG_UPUEN_VALUE (0)
#else
#error "Neither internal nor external pullups defined"
#endif

#if defined USB_INTERNAL_TRANSCIEVER
#define USB_UCFG_UTRDIS_VALUE (0)
#elif defined USB_EXTERNAL_TRANSCIEVER
#define USB_UCFG_UTRDIS_VALUE (1<<3)
#else
#error "Neither internal nor external transciever defined"
#endif

#if defined USB_FULL_SPEED_DEVICE
#define USB_UCFG_FSEN_VALUE (1<<2)
#elif defined USB_LOW_SPEED_DEVICE
#define USB_UCFG_FSEN_VALUE (0)
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
#warning "Use of internal voltage regulator not defined. User must supply 3.3V on Vusb pin."
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

#define USB_UCFG_REGISTER_VALUE	((USB_UCFG_UPUEN_VALUE) | \
								 (USB_UCFG_UTRDIS_VALUE) | \
								 (USB_UCFG_FSEN_VALUE) | \
								 (USB_PP_BUF_MODE))

#define ConfigureUsbHardware()				do {UCFG = USB_UCFG_REGISTER_VALUE;} while(0)

#define ROM far rom
#define ARCH_memcpy memcpypgm2ram

#ifdef __DEBUG
#include <stdio.h>
#include <usart.h>
#define DINIT()			do {	OpenUSART(	USART_TX_INT_OFF & \
											USART_RX_INT_OFF & \
											USART_ASYNCH_MODE & \
											USART_EIGHT_BIT & \
											USART_CONT_RX & \
											USART_BRGH_HIGH, \
											25); /* 25 <==> 115200:8-n-1 @ 20MHz XTAL */\
								stderr = _H_USART; } while(0)
#define DPRINTF(...)	fprintf(stderr, (const ROM char *) __VA_ARGS__)
#else
#define DINIT()
#define DPRINTF(...)
#endif

#endif//__USB_P18F_H__
