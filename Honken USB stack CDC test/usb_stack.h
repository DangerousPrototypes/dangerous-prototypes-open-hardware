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

#include "usb_lang.h"

/* Include user configuration */
#include "usb_config.h"

#ifndef USB_VID
#error "Must supply own Vendor ID (USB_VID) in usb_config.h"
#endif
#ifndef USB_PID
#error "Must supply Product ID (USB_PID) in usb_config.h"
#endif

#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550) || defined(__18F14K50)
#include "usb_p18f.h"
#elif defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
#include "usb_p24f.h"
#endif

/* Structs for defining endpoints */
//typedef void(*)(unsigned char *) usb_ep_callback;
typedef void(*usb_handler_t)(void);

typedef struct USB_EP_TYPE {
	usb_uep_t		type;
	unsigned int 	buffer_size;
	unsigned char	*in_buffer, *out_buffer;
	usb_handler_t	in_handler, out_handler;
} usb_ep_t;

/* Misc */
#define HIGHB(x) ((x)>>8)
#define LOWB(x) ((x) & 0xFF)

#define XCAT(x,y) x ## y
#define CAT(x,y) XCAT(x,y)

/* Descriptors */
#if USB_NUM_CONFIGURATIONS > 1
#error "More than 1 configuration not supported yet"
#endif
/*
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
*/
typedef struct BDENTRY {
	volatile unsigned char
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
	volatile unsigned char BDCNT;
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

#ifndef USB_EP0_BUFFER_SIZE
#define USB_EP0_BUFFER_SIZE 8u
#endif

#ifndef USB_MAX_BUFFER_SIZE
#define USB_MAX_BUFFER_SIZE 8u
#elif USB_MAX_BUFFER_SIZE == 8u
#elif USB_MAX_BUFFER_SIZE == 16u
#elif USB_MAX_BUFFER_SIZE == 32u
#elif USB_MAX_BUFFER_SIZE == 64u
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

extern usb_status_t trn_status;
extern BDentry *bdp, *rbdp;

extern void usb_init(	ROM const unsigned char *dev_descriptor, 
						ROM const unsigned char *config_descriptor, 
						ROM const unsigned char *string_descriptor, int num_string_descriptors );
extern void usb_start( void );
extern void usb_register_sof_handler( usb_handler_t handler );
extern void usb_register_class_setup_handler( usb_handler_t handler );
extern void usb_register_vendor_setup_handler( usb_handler_t handler );
extern void usb_register_endpoint(	unsigned int endpoint, usb_uep_t type,
									unsigned int buffer_size, unsigned char *out_buffer, unsigned char *in_buffer, 
									usb_handler_t out_handler, usb_handler_t in_handler );
extern void usb_set_in_handler( int ep, usb_handler_t handler );
extern void usb_set_out_handler( int ep, usb_handler_t handler );
#define usb_unset_in_handler(ep) usb_set_in_handler(ep, (usb_handler_t) 0)
#define usb_unset_out_handler(ep) usb_set_in_handler(ep, (usb_handler_t) 0)

extern void usb_handler( void );

extern void usb_ack( BDentry * );
extern void usb_ack_zero( BDentry * );
extern void usb_ack_out( BDentry * );
extern void usb_RequestError( void );

#endif /* USB_STACK_H */
