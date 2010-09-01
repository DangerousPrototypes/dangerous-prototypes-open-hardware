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

#ifndef __USB_STACK_H__
#define __USB_STACK_H__

#define USB_TOKEN_Mask	0b00111100
#define USB_TOKEN_OUT	0b00000100
#define USB_TOKEN_IN	0b00100100
#define USB_TOKEN_SOF	0b00010100
#define USB_TOKEN_SETUP	0b00110100
#define USB_TOKEN_DATA0	0b00001100
#define USB_TOKEN_DATA1	0b00101100
#define USB_TOKEN_DATA2	0b00011100		/* High speed isochronous endpoints only */
#define USB_TOKEN_MDATA	0b00111100		/* High speed isochronous enpoints and hub devices only */
#define USB_TOKEN_ACK	0b00001000
#define USB_TOKEN_NAK	0b00101000
#define USB_TOKEN_STALL	0b00111000
#define USB_TOKEN_NYET	0b00011000		/* High speed devices only */
#define USB_TOKEN_PRE	0b00110000
#define USB_TOKEN_ERR	0b00110000
#define USB_TOKEN_SPLIT	0b00100000		/* Hub devices only */
#define USB_TOKEN_PING	0b00010000		/* High speed devices only */

/* Descriptor Types */
#define USB_DEVICE_DESCRIPTOR_TYPE					 	1u
#define USB_CONFIGURATION_DESCRIPTOR_TYPE			 	2u
#define USB_STRING_DESCRIPTOR_TYPE					 	3u
#define USB_INTERFACE_DESCRIPTOR_TYPE				 	4u
#define USB_ENDPOINT_DESCRIPTOR_TYPE				 	5u
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE		 	6u
#define USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE	7u
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE			 	8u
#define USB_OTG_DESCRIPTOR_TYPE						 	9u
#define USB_DEBUG_DESCRIPTOR_TYPE						10u
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE		11u

//typedef void(*)(unsigned char *) usb_ep_callback;
#define USB_UEP_EPHSHK 		(0x10)
#define USB_UEP_EPCONDIS	(0x08)
#define USB_UEP_EPOUTEN 	(0x04)
#define USB_UEP_EPINEN		(0x02)

#define USB_EP_INOUT	(USB_UEP_EPHSHK | USB_UEP_EPINEN | USB_UEP_EPOUTEN | USB_UEP_EPCONDIS)
#define USB_EP_CONTROL	(USB_UEP_EPHSHK | USB_UEP_EPINEN | USB_UEP_EPOUTEN)
#define USB_EP_OUT		(USB_UEP_EPHSHK |                  USB_UEP_EPOUTEN | USB_UEP_EPCONDIS)
#define USB_EP_IN		(USB_UEP_EPHSHK | USB_UEP_EPINEN                   | USB_UEP_EPCONDIS)
#define USB_EP_NONE		(0x00)

#define USB_EP_INTERRUPT	(0)
#define USB_EP_BULK			(1)
#define	USB_EP_ISOCHRONOUS	(2)

#define HIGHB(x) ((x)>>8)
#define LOWB(x) ((x) & 0xFF)

#include "usb_lang.h"

/* Include user configuration */
#include "usb_config.h"

/* Descriptors */
#if USB_NUM_CONFIGURATIONS > 1
#error "More than 1 configuration not supported yet"
#endif

#ifndef USB_STRINGS
#warning "No usb device strings defined"
#endif

#ifndef USB_ENDPOINTS
#define USB_ENDPOINTS
#warning "No endpoints configured"
#endif

#define USB_ALL_ENDPOINTS \
  USB_EP(0, USB_EP_CONTROL, ESB_EP_INTERRUPT, USB_MAX_BUFFER_SIZE, usb_ep0_handler) \
  USB_ENDPOINTS

#define USB_EP(num, flow, typ, size, callback) +1
#define USB_NUM_EP ( 0 USB_ALL_ENDPOINTS )
#undef USB_EP

#if defined class_init
 #ifndef class_setup
  #error "No Class setup handler defined"
 #endif
#elif defined vendor_init
 #ifndef vendor_setup
  #error "No Vendor setup handler defined"
 #endif
#else
 #error "Niether Class nor Vendor initialization function defined"
#endif

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


typedef struct BDENTRY {
	unsigned char
/*	struct {
		unsigned BCH:2;
		unsigned BSTALL:1;
		unsigned DTSEN:1;
		unsigned INCDIS:1;
		unsigned KEN:1;
		unsigned DTS:1;
		unsigned UOWN:1;
	}*/
	BDSTAT;
	unsigned char BDCNT;
	unsigned char *BDADDR;
} BDentry;

/* BDSTAT Bitmasks */
#define UOWN	0x80
#define DTS		0x40
#define KEN		0x20
#define INCDIS	0x10
#define DTSEN	0x08
#define	BSTALL	0x04
#define BC98	0x03


extern BDentry usb_bdt[];

#ifndef USB_MAX_BUFFER_SIZE
#define USB_MAX_BUFFER_SIZE 8
#elif USB_MAX_BUFFER_SIZE == 8
#elif USB_MAX_BUFFER_SIZE == 16
#elif USB_MAX_BUFFER_SIZE == 32
#elif USB_MAX_BUFFER_SIZE == 64
#else
#error "USB_MAX_BUFFER_SIZE needs to be 8, 16, 32 or 64 bytes"
#endif

typedef struct USB_DEVICE_REQUEST {
	unsigned char bmRequestType;
	unsigned char bRequest;
	unsigned int wValue;
	unsigned int wIndex;
	unsigned int wLength;
} usb_device_request;

#define USB_bmRequestType		0
#define USB_bRequest			1
#define USB_wValue				2
#define USB_bDescriptorIndex	2
#define USB_wValueHigh			3
#define USB_bDescriptorType		3
#define	USB_wIndex				4
#define USB_bInterface			4
#define USB_wIndexHigh			5
#define USB_wLength				6
#define	USB_wLengthHigh			7

/*
#define USB_CLEAR_FEATURE_REQUEST		0b00000000
#define USB_GET_CONFIGURATION_REQUEST	0b10000000
#define USB_GET_DESCRIPTOR_REQUEST		0b10000000
#define USB_GET_INTERFACE_REQUEST		0b10000001
#define USB_GET_STATUS_REQUEST			0b10000000
#define USB_SET_ADDRESS_REQUEST			0b00000000
#define USB_SET_CONFIGURATION_REQUEST	0b00000000
#define USB_SET_DESCRIPTOR				0b00000000
#define USB_SET_FEATURE_REQUEST			0b00000000
#define USB_SET_INTERFACE_REQUEST		0b00000001
#define USB_SYNCH_FRAME_REQUEST			0b10000010
*/

#define USB_bmRequestType_PhaseMask		0b10000000
#define USB_bmRequestType_H2D			0b00000000
#define USB_bmRequestType_D2H			0b10000000
#define USB_bmRequestType_TypeMask		0b01100000
#define USB_bmRequestType_Standard		0b00000000
#define USB_bmRequestType_Class			0b00100000
#define USB_bmRequestType_Vendor		0b01000000
#define USB_bmRequestType_RecipientMask	0b00000011
#define USB_bmRequestType_Device		0b00000000
#define USB_bmRequestType_Interface		0b00000001
#define USB_bmRequestType_Endpoint		0b00000010
#define USB_bmRequestType_Other			0b00000011

#define USB_REQUEST_GET_STATUS			0
#define USB_REQUEST_CLEAR_FEATURE		1
#define USB_REQUEST_SET_FEATURE			3
#define USB_REQUEST_SET_ADDRESS			5
#define USB_REQUEST_GET_DESCRIPTOR		6
#define USB_REQUEST_SET_DESCRIPTOR		7
#define USB_REQUEST_GET_CONFIGURATION	8
#define USB_REQUEST_SET_CONFIGURATION	9
#define USB_REQUEST_GET_INTERFACE		10
#define USB_REQUEST_SET_INTERFACE		11
#define USB_REQUEST_SYNCH_FRAME			12

extern unsigned char trn_status;
extern BDentry *bdp, *rbdp;

typedef void(*usb_handler_t)(void);

extern void usb_init( void );
extern void usb_handler( void );
extern void usb_set_in_handler( int ep, usb_handler_t handler );
extern void usb_set_out_handler( int ep, usb_handler_t handler );
#define usb_unset_in_handler(ep) usb_set_in_handler(ep, (usb_handler_t) 0)
#define usb_unset_out_handler(ep) usb_set_in_handler(ep, (usb_handler_t) 0)
extern void usb_ack( BDentry * );
extern void usb_ack_zero( BDentry * );
extern void usb_ack_out( BDentry * );
extern void usb_RequestError( void );

extern void class_init( void );
extern void class_setup( void );
extern void vendor_init( void );
extern void vendor_setup( void );

#endif /* USB_STACK_H */