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

Influence and inspiration taken from http://pe.ece.olin.edu/ece/projects.html
*/


#include <p18cxxx.h>
#include <string.h>

#include "usb_stack.h"
#include "descriptors.h"

#ifdef __DEBUG
#include <stdio.h>
#define DPRINTF(...) printf((const far rom char *) __VA_ARGS__)
#else
#define DPRINTF(...)
#endif

#define XCAT(x,y) x ## y
#define CAT(x,y) XCAT(x,y)

#pragma udata usb_bdt=0x400
BDentry usb_bdt[2*4];

#if USB_PP_BUF_MODE == 0

#define USB_EP(num, flow, typ, size, callback) \
	unsigned char usb_ep ## num ## _out_buf[size]; \
	unsigned char usb_ep ## num ## _in_buf[size];
USB_ALL_ENDPOINTS
#undef USB_EP

#elif USB_PP_BUF_MODE == 1

#define USB_EP(num, flow, typ, size, callback) \
	unsigned char usb_ep ## num ## _out_buf[size]; \
	unsigned char usb_ep ## num ## _in_buf[size];
unsigned char usb_ep0_out_even_buf[USB_MAX_BUFFER_SIZE];
unsigned char usb_ep0_out_odd_buf[USB_MAX_BUFFER_SIZE];
unsigned char usb_ep0_in_buf[USB_MAX_BUFFER_SIZE];
USB_ENDPOINTS
#undef USB_EP

#elif USB_PP_BUF_MODE == 2

#define USB_EP(num, flow, typ, size, callback) \
	unsigned char usb_ep ## num ## _out_even_buf[size]; \
	unsigned char usb_ep ## num ## _out_odd_buf[size]; \
	unsigned char usb_ep ## num ## _in_even_buf[size]; \
	unsigned char usb_ep ## num ## _in_odd_buf[size];
USB_ALL_ENDPOINTS
#undef USB_EP

#elif USB_PP_BUF_MODE == 3

#define USB_EP(num, flow, typ, size, callback) \
	unsigned char usb_ep ## num ## _out_even_buf[size]; \
	unsigned char usb_ep ## num ## _out_odd_buf[size]; \
	unsigned char usb_ep ## num ## _in_even_buf[size]; \
	unsigned char usb_ep ## num ## _in_odd_buf[size];
unsigned char usb_ep0_out_buf[USB_MAX_BUFFER_SIZE];
unsigned char usb_ep0_in_buf[USB_MAX_BUFFER_SIZE];
USB_ENDPOINTS
#undef USB_EP

#endif

#pragma udata

unsigned int usb_device_status;
unsigned int usb_configured;
unsigned char usb_addr_pending;

unsigned char trn_status;					// Global since it is needed everywere
BDentry *bdp, *rbdp;						// Dito

usb_handler_t in_handlers[16];
usb_handler_t out_handlers[16];

const unsigned char rom *usb_desc_ptr;
unsigned int usb_desc_len;

#define USB_STRING(num, size, ...) rom const unsigned char CAT(usb_str_desc,num) [] = {2*(size+1), USB_STRING_DESCRIPTOR_TYPE, __VA_ARGS__};
USB_STRINGS
#undef USB_STRING

/* Forward Reference Prototypes */
#define usb_handle_error() UEIR = 0		/* No errorhandler for now, just clear offending flag*/
void usb_handle_reset( void );
void usb_handle_transaction( void );
void usb_handle_setup( void );
void usb_handle_out( void );
void usb_handle_in( void );
void usb_handle_StandardDeviceRequest( BDentry* );
void usb_handle_StandardInterfaceRequest( BDentry* );
void usb_handle_StandardEndpointRequest( BDentry* );
void usb_handle_ClassRequest( void );
void usb_handle_VendorRequest( void );
void usb_RequestError( void );

void usb_set_address( void );
void usb_send_descriptor( void );

void usb_init( void ) {
	unsigned char i;

	DPRINTF(((const rom char *) "USB init "));
	UIE = 0x00;					// Disable all USB-related interrupts
	UEIE = 0xFF;				// Enable all errors to set flag in UIR
	UIR = UEIR = 0x00;			// Clear all USB-related interrupt flags
	
	UCFG = USB_UCFG_REGISTER_VALUE;	// Configure USB-hardware

/* Configure endpoint buffer descriptors */
#if USB_PP_BUF_MODE == 0
#define USB_EP(num, flow, typ, size, callback) \
	bdp = &usb_bdt[USB_CALC_BD(num, USB_DIR_OUT, 0)]; \
	bdp->BDCNT = size; \
	bdp->BDADDR = usb_ep ## num ## _out_buf; \
	bdp->BDSTAT = UOWN + DTSEN; \
	bdp = &usb_bdt[USB_CALC_BD(num, USB_DIR_IN, 0)]; \
	bdp->BDCNT = size; \
	bdp->BDADDR = usb_ep ## num ## _in_buf; \
	bdp->BDSTAT = DTSEN;

	USB_ALL_ENDPOINTS
#undef USB_EP
#else
	#error "PP Mode not implemented yet"
#endif

/* Configure endpoints (UEPn - registers) */
#define USB_EP(num, flow, typ, size, callback) CAT(UEP,num) = flow;
USB_ALL_ENDPOINTS
#undef USB_EP

#ifdef USB_SELF_POWERED
	usb_device_status = 0x0001;
#else
	usb_device_status = 0x0000;
#endif
	usb_configured = 0x00;
	usb_addr_pending = 0x00;

	class_init();

	UCON = 0x08;				// Enable USB-hardware, TODO: Remove magic
	while(UCONbits.SE0);		// Busywait for initial power-up
	UIE = 0x3F;					// Enable all but Start-Of-Frame, TODO: Remove magic (STALLIE + IDLEIE + TRNIE + ACTVIE + UERRIE + URSTIE)
	DPRINTF("sucessful\n");
}

void usb_handler( void ) {
	if (UIRbits.UERRIF) {
		DPRINTF("USB ERROR 0x%02X\n", UEIR);
		usb_handle_error();
	} else if (UIRbits.URSTIF) {
		usb_handle_reset();
		DPRINTF("Reset\n");
	} else if (UIRbits.ACTVIF) {
		/* Activity - unsuspend */
		UCONbits.SUSPND = 0;
		while(UIRbits.ACTVIF) UIRbits.ACTVIF = 0;	// Busy wait, the USB SIE is a slow starter
		DPRINTF("Active\n");
	} else if (UIRbits.IDLEIF) {
		/* Idle - suspend */
		UIRbits.IDLEIF = 0;
		UCONbits.SUSPND = 1;
		usb_low_power_request();
		DPRINTF("Idle\n");
	} else if (UIRbits.STALLIF) {
		/* Stall detected
		 * Not sure when this interrupt fires
		 * as the host never should send out a stall.
		 * Perhaps as a respons to our own stalls? 
		 * For now just ignore it. */
		UIRbits.STALLIF = 0;
		DPRINTF("Stall int fired");
	} else if (UIRbits.SOFIF) {
		/* Start-of-frame - ignore */
		UIRbits.SOFIF = 0;
	} else if (UIRbits.TRNIF) {
		usb_handle_transaction();
	}
}

void usb_handle_reset( void ) {

#ifdef USB_SELF_POWERED
	usb_device_status = 0x0001;
#else
	usb_device_status = 0x0000;
#endif
	usb_configured = 0x00;
	usb_addr_pending = 0x00;

	UIRbits.TRNIF = 0;		// Advance USTAT FIFO four times to clear
	UIRbits.TRNIF = 0;
	UIRbits.TRNIF = 0;
	UIRbits.TRNIF = 0;
	UEP0 = 0;				// Disable all endpoints
	UEP1 = 0;
	UEP2 = 0;
	UEP3 = 0;
	UEP4 = 0;
	UEP5 = 0;
	UEP6 = 0;
	UEP7 = 0;
	UEP8 = 0;
	UEP9 = 0;
	UEP10 = 0;
	UEP11 = 0;
	UEP12 = 0;
	UEP13 = 0;
	UEP14 = 0;
	UEP15 = 0;

	UADDR = 0;				// After reset we don't have an address
	UIR = UEIR = 0;			// Clear all interrupts

/* Configure endpoints (UEPn - registers) */
#define USB_EP(num, flow, typ, size, callback)\
	CAT(UEP,num) = flow;
USB_ALL_ENDPOINTS
#undef USB_EP

/* Configure buffer descriptors */
#if USB_PP_BUF_MODE == 0
#define USB_EP(num, flow, typ, size, callback) \
	usb_bdt[USB_CALC_BD(num, USB_DIR_OUT, USB_PP_EVEN)].BDCNT  = size; \
	usb_bdt[USB_CALC_BD(num, USB_DIR_OUT, USB_PP_EVEN)].BDADDR = usb_ep ## num ##_out_buf; \
	usb_bdt[USB_CALC_BD(num, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN + DTSEN; \
	usb_bdt[USB_CALC_BD(num, USB_DIR_IN, USB_PP_EVEN)].BDCNT  = 0; \
	usb_bdt[USB_CALC_BD(num, USB_DIR_IN, USB_PP_EVEN)].BDADDR = usb_ep ## num ##_in_buf; \
	usb_bdt[USB_CALC_BD(num, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = DTSEN;
	USB_ALL_ENDPOINTS
#undef USB_EP
#else
	// TODO: Implement Ping-Pong buffering setup.
	#error "PP Mode not implemented yet"
#endif

	UEIE = 0xFF;			// Enable all error interrupts
}

void usb_handle_transaction( void ) {

	trn_status = USTAT;	// Save USTAT
	UIRbits.TRNIF = 0;										// Clear interrupt and advance USTAT FIFO
	bdp  = &usb_bdt[USB_USTAT2BD(trn_status)];
	rbdp = &usb_bdt[USB_USTAT2BD(trn_status | 0x04)];		// All replies in IN direction

	DPRINTF("USTAT: 0x%02X PID 0x%02X DATA%c ", trn_status, bdp->BDSTAT % USB_TOKEN_Mask, (bdp->BDSTAT & 0x40)?'1':'0');
	switch (bdp->BDSTAT & USB_TOKEN_Mask) {
	case USB_TOKEN_SETUP:
		usb_handle_setup();
		break;
	case USB_TOKEN_OUT:
		usb_handle_out();
		break;
	case USB_TOKEN_IN:
		usb_handle_in();
		break;
	default:
		/* Default case of unknown TOKEN - silently discard */
		DPRINTF("Unknown token\n");
	}
}

void usb_handle_setup( void ) {
	DPRINTF("bmReqType 0x%02X ", bdp->BDADDR[USB_bmRequestType]);
	rbdp->BDSTAT = DTSEN;									// Reclaim reply buffer
	switch (bdp->BDADDR[USB_bmRequestType] & USB_bmRequestType_TypeMask) {
	case USB_bmRequestType_Standard:
		switch (bdp->BDADDR[USB_bmRequestType] & USB_bmRequestType_RecipientMask) {
		case USB_bmRequestType_Device:
			usb_handle_StandardDeviceRequest( bdp );
			break;
		case USB_bmRequestType_Interface:
			usb_handle_StandardInterfaceRequest( bdp );
			break;
		case USB_bmRequestType_Endpoint:
			usb_handle_StandardEndpointRequest( bdp );
			break;
		default:
			usb_RequestError();
		}
		break;
	case USB_bmRequestType_Class:
		usb_handle_ClassRequest();
		break;
	case USB_bmRequestType_Vendor:
		usb_handle_VendorRequest();
		break;
	default:
		usb_RequestError();
	}
	/* Prepare endpoint for new reception */
	bdp->BDCNT = USB_MAX_BUFFER_SIZE;
	bdp->BDSTAT = (!(bdp->BDADDR[USB_bmRequestType] & USB_bmRequestType_PhaseMask) &&
					(bdp->BDADDR[USB_wLength] || bdp->BDADDR[USB_wLengthHigh]))? UOWN + DTS + DTSEN : UOWN + DTSEN;
	UCONbits.PKTDIS = 0;		// Reenable packet reception
}

void usb_handle_StandardDeviceRequest( BDentry *bdp ) {
	unsigned char *packet = bdp->BDADDR;

	switch(packet[USB_bRequest]) {
	case USB_REQUEST_GET_STATUS:
		rbdp->BDADDR[0] = usb_device_status & 0xFF;
		rbdp->BDADDR[1] = usb_device_status >> 8;
		rbdp->BDCNT = 2;
		rbdp->BDSTAT = UOWN + DTS + DTSEN;
		DPRINTF("DEV Get_Status\n");
		break;
	case USB_REQUEST_CLEAR_FEATURE:
		if (0x01u == packet[USB_wValue])	{	// TODO: Remove magic (REMOTE_WAKEUP_FEATURE)
			usb_device_status &= ~0x0002;
			rbdp->BDCNT = 0;
			rbdp->BDSTAT = 0xC8;
			DPRINTF("DEV Clear_Feature 0x%02X\n", packet[USB_wValue]);
		} else
			usb_RequestError();
		break;
	case USB_REQUEST_SET_FEATURE:
		if (0x01u == packet[USB_wValue])	{	// TODO: Remove magic (REMOTE_WAKEUP_FEATURE)
			usb_device_status |= 0x0002;
			rbdp->BDCNT = 0;
			rbdp->BDSTAT = 0xC8;
			DPRINTF("DEV Set_Feature 0x%02X\n", packet[USB_wValue]);
		} else
			usb_RequestError();
		break;
	case USB_REQUEST_SET_ADDRESS:
		if (0x00u == packet[USB_wValueHigh] && 0x7Fu >= packet[USB_wValue]) {
			usb_addr_pending = packet[USB_wValue];
			rbdp->BDCNT = 0;
			rbdp->BDSTAT = 0xC8;
			usb_set_in_handler(0, usb_set_address);
			DPRINTF("DEV Set address 0x%02X\n", usb_addr_pending);
		} else
			usb_RequestError();
		break;
	case USB_REQUEST_GET_DESCRIPTOR:
		switch (packet[USB_bDescriptorType]) {
		case USB_DEVICE_DESCRIPTOR_TYPE:
			usb_desc_ptr = usb_device_descriptor;
			usb_desc_len = usb_device_descriptor[0];
			if (0u==packet[USB_wLengthHigh] && 
				   packet[USB_wLength] < usb_desc_len)
				usb_desc_len = packet[USB_wLength];
			DPRINTF("DEV Dev_desc_req ");
			break;
		case USB_CONFIGURATION_DESCRIPTOR_TYPE:
			if (USB_NUM_CONFIGURATIONS <= packet[USB_bDescriptorIndex])
				usb_RequestError();
			usb_desc_ptr = usb_config_descriptor;
			usb_desc_len = usb_desc_ptr[2] + usb_desc_ptr[3] * 256;
			if (packet[USB_wLengthHigh] <  usb_desc_ptr[3] || 
				packet[USB_wLengthHigh] == usb_desc_ptr[3] && packet[USB_wLength] < usb_desc_ptr[2])
				usb_desc_len = packet[USB_wLength] + packet[USB_wLengthHigh] * 256;
			DPRINTF("DEV Conf_desc_req 0x%02X 0x%02X%02X ", packet[USB_bDescriptorIndex], packet[USB_wLengthHigh], packet[USB_wLength]);
			break;
		case USB_STRING_DESCRIPTOR_TYPE:
			// TODO: Handle language request. For now return standard language.
			switch(packet[USB_bDescriptorIndex]) {
#define USB_STRING(num, ...) \
			case num: \
				usb_desc_ptr = CAT(usb_str_desc,num); \
				break;
			USB_STRINGS
#undef USB_STRING
			default:
				usb_RequestError();
			}
			usb_desc_len = usb_desc_ptr[0];
			if (0u==packet[USB_wLengthHigh] && packet[USB_wLength] < usb_desc_len)
				usb_desc_len = packet[USB_wLength];
			DPRINTF("DEV Str_desc_req 0x%02X%02X 0x%02X%02X ", packet[USB_wValueHigh], packet[USB_wValue], packet[USB_wIndexHigh], packet[USB_wIndex]);
			break;
		case USB_INTERFACE_DESCRIPTOR_TYPE:
		case USB_ENDPOINT_DESCRIPTOR_TYPE:
		default:
			usb_RequestError();
		}
		usb_send_descriptor();																	// Send first part of packet right away
		usb_set_in_handler(0, usb_send_descriptor);
		break;
	case USB_REQUEST_GET_CONFIGURATION:
		rbdp->BDADDR[0] = usb_configured;
		rbdp->BDCNT = 1;
		rbdp->BDSTAT = UOWN + DTS + DTSEN;
		DPRINTF("DEV Get_Config\n");
		break;
	case USB_REQUEST_SET_CONFIGURATION:
		if (USB_NUM_CONFIGURATIONS >= packet[USB_wValue]) {

			/* Configure endpoints (UEPn – registers) */
			#define USB_EP(num, flow, typ, size, callback) \
			CAT(UEP,num) = flow;\
			usb_bdt[USB_CALC_BD(num, USB_DIR_OUT, USB_PP_EVEN)].BDCNT = size; \
			usb_bdt[USB_CALC_BD(num, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN; /* TODO: Should add DTSEN */ \
			//usb_bdt[USB_CALC_BD(num, USB_DIR_OUT, USB_PP_ODD)].BDCNT = size; \
			//usb_bdt[USB_CALC_BD(num, USB_DIR_OUT, USB_PP_ODD)].BDSTAT = UOWN; /* TODO: Should add DTSEN */ \
			usb_bdt[USB_CALC_BD(num, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = 0; /* TODO: Should be DTSEN */ \
			//usb_bdt[USB_CALC_BD(num, USB_DIR_IN, USB_PP_ODD)].BDSTAT = 0; /* TODO: Should be DTSEN */ \
			USB_ENDPOINTS
			#undef USB_EP

			usb_configured = packet[USB_wValue];
			rbdp->BDCNT = 0;
			rbdp->BDSTAT = UOWN + DTS + DTSEN;
			DPRINTF("DEV Set_Config 0x%02X\n", packet[USB_wValue]);
		} else
			usb_RequestError();			
		break;
	case USB_REQUEST_SET_DESCRIPTOR:
	default:
		usb_RequestError();
	}
}

void usb_handle_StandardInterfaceRequest( BDentry *bdp ) {
	unsigned char *packet = bdp->BDADDR;

	switch (packet[USB_bRequest]) {
	case USB_REQUEST_GET_STATUS:
		rbdp->BDADDR[0] = 0x00;
		rbdp->BDADDR[1] = 0x00;
		rbdp->BDCNT = 2;
		rbdp->BDSTAT = 0xC8;
		DPRINTF("IF Get_Status\n");
		break;
	case USB_REQUEST_GET_INTERFACE:
		if (USB_NUM_INTERFACES > packet[USB_bInterface]) {
			// TODO: Implement alternative interfaces, or move responsibility to class/vendor functions.
			rbdp->BDADDR[0] = 0;
			rbdp->BDCNT = 1;
			rbdp->BDSTAT = UOWN + DTS + DTSEN;
			DPRINTF("IF Get_Interface\n");
		} else
			usb_RequestError();
		break;
	case USB_REQUEST_SET_INTERFACE:
		if (USB_NUM_INTERFACES > packet[USB_bInterface] && 0u == packet[USB_wValue]) {
			// TODO: Implement alternative interfaces...
			rbdp->BDCNT = 0;
			rbdp->BDSTAT = UOWN + DTS + DTSEN;
			DPRINTF("IF Set_Interface 0x%2X\n", packet[USB_bInterface]);
		} else
			usb_RequestError();
		break;
	case USB_REQUEST_CLEAR_FEATURE:
	case USB_REQUEST_SET_FEATURE:
	default:
		usb_RequestError();
	}
}

void usb_handle_StandardEndpointRequest( BDentry *bdp ) {
	unsigned char *packet;
	unsigned char *UEP;
	unsigned char epnum;
	unsigned char dir;
	BDentry	*epbd;

	packet = bdp->BDADDR;

	switch (packet[USB_bRequest]) {
	case USB_REQUEST_GET_STATUS:
		epnum = packet[USB_wIndex] & 0x0F;
		dir = packet[USB_wIndex] >> 7;
		UEP = (unsigned char *)&UEP0 + epnum;
		rbdp->BDADDR[0] = *UEP & 0x01;	// TODO: Remove magic (EPSTALL)
		rbdp->BDADDR[1] = 0x00;
		rbdp->BDCNT = 2;
		rbdp->BDSTAT = UOWN + DTS + DTSEN;
		DPRINTF("EP Get_Status\n");
		break;
	case USB_REQUEST_CLEAR_FEATURE:
		epnum = packet[USB_wIndex] & 0x0F;
		dir = packet[USB_wIndex] >> 7;
		epbd = &usb_bdt[USB_CALC_BD(epnum, dir, USB_PP_EVEN)];
		epbd->BDSTAT &= ~BSTALL;
		epbd = &usb_bdt[USB_CALC_BD(epnum, dir, USB_PP_ODD)];
		epbd->BDSTAT &= ~BSTALL;
		rbdp->BDCNT = 0;
		rbdp->BDSTAT = UOWN + DTS + DTSEN;
		DPRINTF("EP Clear_Feature 0x%02X\n", packet[USB_wIndex]);
		break;
	case USB_REQUEST_SET_FEATURE:
		epnum = packet[USB_wIndex] & 0x0F;
		dir = packet[USB_wIndex] >> 7;
		epbd = &usb_bdt[USB_CALC_BD(epnum, dir, USB_PP_EVEN)];
		epbd->BDSTAT |= BSTALL;
		epbd = &usb_bdt[USB_CALC_BD(epnum, dir, USB_PP_ODD)];
		epbd->BDSTAT |= BSTALL;
		rbdp->BDCNT = 0;
		rbdp->BDSTAT = UOWN + DTS + DTSEN;
		DPRINTF("EP Set_Feature 0x%02X\n", packet[USB_wIndex]);
		break;
	case USB_REQUEST_SYNCH_FRAME:
	default:
		usb_RequestError();
	}
}		

void usb_handle_ClassRequest( void ) {
	class_setup(); \
}


void usb_handle_VendorRequest( void ) {
	DPRINTF("Vendor\n");
}

void usb_handle_in( void ) {
	DPRINTF("In  EP: %u Handler: 0x%P\t", trn_status >> 3, in_handlers[trn_status>>3]);
	if (in_handlers[trn_status>>3]) {
		in_handlers[trn_status>>3]();
	} else {
		DPRINTF("\n");
	}
}

void usb_handle_out( void ) {
	DPRINTF("Out EP: %u Handler: 0x%P\t", trn_status >> 3, out_handlers[trn_status>>3]);
	//rbdp->BDSTAT &= ~UOWN;									// Reclaim reply buffer
	if (out_handlers[trn_status>>3]) {
		out_handlers[trn_status>>3]();
	} else {
		DPRINTF("\n");
	}
}

void usb_set_in_handler(int ep, usb_handler_t in_handler) {
	in_handlers[ep] = in_handler;
}

void usb_set_out_handler(int ep, usb_handler_t out_handler) {
	out_handlers[ep] = out_handler;
}

void usb_ack( BDentry *bd ) {
	bd->BDSTAT = ((bd->BDSTAT ^ DTS) & DTS) | UOWN + DTSEN;		// TODO: Accomodate for >=256 byte buffers
}

void usb_ack_zero( BDentry *bd ) {
	bd->BDCNT = 0;
	bd->BDSTAT = ((bd->BDSTAT ^ DTS) & DTS) | UOWN + DTSEN;
}

void usb_ack_out( BDentry *bd ) {
	bd->BDCNT = USB_MAX_BUFFER_SIZE;
	bd->BDSTAT = ((bd->BDSTAT ^ DTS) & DTS) | UOWN + DTSEN;
}

void usb_RequestError( void ) {
	unsigned int i;

	usb_bdt[USB_CALC_BD(0, USB_DIR_OUT, USB_PP_EVEN)].BDCNT = USB_MAX_BUFFER_SIZE;
	usb_bdt[USB_CALC_BD(0, USB_DIR_OUT, USB_PP_ODD)].BDCNT = USB_MAX_BUFFER_SIZE;

	usb_bdt[USB_CALC_BD(0, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = UOWN + BSTALL;
	usb_bdt[USB_CALC_BD(0, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN + BSTALL;
	usb_bdt[USB_CALC_BD(0, USB_DIR_IN, USB_PP_ODD)].BDSTAT = UOWN + BSTALL;
	usb_bdt[USB_CALC_BD(0, USB_DIR_OUT, USB_PP_ODD)].BDSTAT = UOWN + BSTALL;

	DPRINTF("Request error\n");
	for (i=0; i<bdp->BDCNT; i++)
		DPRINTF("0x%02X ", bdp->BDADDR[i]);
	DPRINTF("\n");
}

void usb_set_address( void ) {
	if (0x00u < usb_addr_pending && 0x80u > usb_addr_pending) {
		UADDR = usb_addr_pending;
		usb_addr_pending = 0xFF;
		DPRINTF("Address set 0x%02X\n", UADDR);
	}
	usb_unset_in_handler(0);								// Unregister handler
}

void usb_send_descriptor( void ) {
	unsigned int i;
	BDentry *bd;
	size_t packet_len;
	if (usb_desc_len) {
		packet_len = (usb_desc_len < USB_MAX_BUFFER_SIZE) ? usb_desc_len : USB_MAX_BUFFER_SIZE;
		bd = &usb_bdt[USB_CALC_BD(0, USB_DIR_IN, 0x01 ^ ((trn_status & 0x02)>>1))];
		memcpypgm2ram(rbdp->BDADDR, (const far rom void *) usb_desc_ptr, packet_len);
		DPRINTF("Send bd: 0x%P dst: 0x%P src: 0x%P len: %u Data: ", rbdp, rbdp->BDADDR, usb_desc_ptr, packet_len);
		for (i=0; i<packet_len; i++)
			DPRINTF("0x%02X ", rbdp->BDADDR[i]);
		DPRINTF("\n");
	} else {
		packet_len = 0;										// Send a last ack
		usb_unset_in_handler(0);
		DPRINTF("Send done\n");
	}
	rbdp->BDCNT = (unsigned char) packet_len;
	usb_ack(rbdp);											// Packet length always less then 256 on endpoint 0
	usb_desc_ptr += packet_len;
	usb_desc_len -= packet_len;
}
