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

#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550)
#include <p18cxxx.h>
#elif defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
#include <p24fxxxx.h>
#endif
#include <string.h>

#include "usb_stack.h"

ROM const unsigned char *usb_device_descriptor;
ROM const unsigned char *usb_config_descriptor;
ROM const unsigned char *usb_string_descriptor;
int usb_num_string_descriptors;
usb_ep_t endpoints[16];

/* Allocate buffers for buffer description table and the actual buffers */
#pragma udata usb_bdt
BDentry usb_bdt[32];			// TODO: Dynamic allocation reflecting number of used endpoints. (How to do counting in preprocessor?)

#pragma udata usb_data
/* TODO: Move all user defined ep buffers to user application compile time allocation. 
	Only claim buffer for ep 0 */
#if USB_PP_BUF_MODE == 0
unsigned char usb_ep0_out_buf[USB_MAX_BUFFER_SIZE];
unsigned char usb_ep0_in_buf[USB_MAX_BUFFER_SIZE];
#else
#error "Ping pong buffer not implemented yet!"
#endif
#pragma udata

unsigned int usb_device_status;
unsigned int usb_configured;
unsigned char usb_addr_pending;

usb_status_t trn_status;					// Global since it is needed everywere
BDentry *bdp, *rbdp;						// Dito

ROM const unsigned char *usb_desc_ptr;
unsigned int usb_desc_len;

/* Forward Reference Prototypes */
void usb_handle_error( void );
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

void usb_init(	ROM const unsigned char *device_descriptor, 
				ROM const unsigned char *config_descriptor, 
				ROM const unsigned char *string_descriptor,
				int num_string_descriptors ) {
	int i;

	DPRINTF("USB init ");

	usb_device_descriptor = device_descriptor;
	usb_config_descriptor = config_descriptor;
	usb_string_descriptor = string_descriptor;
	usb_num_string_descriptors = num_string_descriptors;

	ResetPPbuffers();

	DisableAllUsbInterrupts();
	EnableAllUsbErrorInterrupts();				// Enable all errors to set flag in UIR

	ClearAllUsbErrorInterruptFlags();
	ClearAllUsbInterruptFlags();
	
	ConfigureUsbHardware();

	usb_register_endpoint(0, USB_EP_CONTROL, USB_EP0_BUFFER_SIZE, usb_ep0_out_buf, usb_ep0_in_buf, NULL, NULL);		// Register ep0 - no handlers

	/* Configure endpoints */
	for (i=0; i<16; i++) {
		/* Configure endpoints (USB_UEPn - registers) */
		USB_UEP[i] = endpoints[i].type;
		/* Configure buffer descriptors */
#if USB_PP_BUF_MODE == 0
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDCNT  = endpoints[i].buffer_size;
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDADDR = endpoints[i].out_buffer;
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN + DTSEN;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDCNT  = 0;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDADDR = endpoints[i].in_buffer;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = DTS + DTSEN;					// Set DTS => First packet inverts, ie. is Data0
#else
		// TODO: Implement Ping-Pong buffering setup.
		#error "PP Mode not implemented yet"
#endif
	}

#ifdef USB_SELF_POWERED
	usb_device_status = 0x0001;
#else
	usb_device_status = 0x0000;
#endif
	usb_configured = 0x00;
	usb_addr_pending = 0x00;
}

void usb_start( void ) {

	DPRINTF("Starting usb ");
	EnableUsb();					// Enable USB-hardware
	while(SingleEndedZeroIsSet());	// Busywait for initial power-up
	EnableUsbInterrupt(STALL + IDLE + TRN + ACTIV + UERR + URST);

	DPRINTF("sucessful\n");
}

void usb_handler( void ) {
	if (USB_ERROR_FLAG) {
		usb_handle_error();
		DPRINTF("Error\n");
	} else if (USB_RESET_FLAG) {
		usb_handle_reset();
		DPRINTF("Reset\n");
	} else if (USB_ACTIVITY_FLAG) {
		/* Activity - unsuspend */
		WakeupUsb();
		DPRINTF("Active\n");
	} else if (USB_IDLE_FLAG) {
		/* Idle - suspend */
		USB_IDLE_FLAG = 0;
		SuspendUsb();
		usb_low_power_request();
		DPRINTF("Idle\n");
	} else if (USB_STALL_FLAG) {
		/* Stall detected
		 * Not sure when this interrupt fires
		 * as the host never should send out a stall.
		 * Perhaps as a respons to our own stalls? 
		 * For now just ignore it. */
		USB_STALL_FLAG = 0;
		DPRINTF("Stall int fired");
	} else if (USB_SOF_FLAG) {
		/* Start-of-frame - ignore */
		USB_SOF_FLAG = 0;
	} else if (USB_TRANSACTION_FLAG) {
		usb_handle_transaction();
	}
}

void usb_handle_error( void ) {
	/* No errorhandler for now, just clear offending flag*/
	ClearAllUsbErrorInterruptFlags();
	ClearUsbInterruptFlag(USB_ERROR_FLAG);
}

void usb_handle_reset( void ) {

	int i;

#ifdef USB_SELF_POWERED
	usb_device_status = 0x0001;
#else
	usb_device_status = 0x0000;
#endif
	usb_configured = 0x00;
	usb_addr_pending = 0x00;

	USB_TRANSACTION_FLAG = 0;		// Advance USTAT FIFO four times to clear
	USB_TRANSACTION_FLAG = 0;
	USB_TRANSACTION_FLAG = 0;
	USB_TRANSACTION_FLAG = 0;
	USB_UEP0 = 0;				// Disable all endpoints
	USB_UEP1 = 0;
	USB_UEP2 = 0;
	USB_UEP3 = 0;
	USB_UEP4 = 0;
	USB_UEP5 = 0;
	USB_UEP6 = 0;
	USB_UEP7 = 0;
	USB_UEP8 = 0;
	USB_UEP9 = 0;
	USB_UEP10 = 0;
	USB_UEP11 = 0;
	USB_UEP12 = 0;
	USB_UEP13 = 0;
	USB_UEP14 = 0;
	USB_UEP15 = 0;

	SetUsbAddress(0);			// After reset we don't have an address
	ClearAllUsbInterruptFlags();
	ClearAllUsbErrorInterruptFlags();

/* Configure endpoints (USB_UEPn - registers) */
	for (i=0; i<16; i++) {
		USB_UEP[i] = endpoints[i].type;
		/* Configure buffer descriptors */
#if USB_PP_BUF_MODE == 0
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDCNT  = endpoints[i].buffer_size;
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDADDR = endpoints[i].out_buffer;
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN + DTSEN;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDCNT  = 0;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDADDR = endpoints[i].in_buffer;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = DTS + DTSEN;				// Set DTS => First packet inverts, ie. is Data0
#else
		// TODO: Implement Ping-Pong buffering setup.
		#error "PP Mode not implemented yet"
#endif
	}
	EnableAllUsbErrorInterrupts();
}

void usb_handle_transaction( void ) {

	trn_status = GetUsbTransaction();
	USB_TRANSACTION_FLAG = 0;								// Clear interrupt and advance USTAT FIFO
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
	bdp->BDCNT = USB_MAX_BUFFER_SIZE;	// TODO: Fix correct size for current EP
	bdp->BDSTAT = (!(bdp->BDADDR[USB_bmRequestType] & USB_bmRequestType_PhaseMask) &&
					(bdp->BDADDR[USB_wLength] || bdp->BDADDR[USB_wLengthHigh]))? UOWN + DTS + DTSEN : UOWN + DTSEN;
	EnablePacketTransfer();
}

void usb_handle_StandardDeviceRequest( BDentry *bdp ) {
	unsigned char *packet = bdp->BDADDR;
	int i;
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
			if (packet[USB_bDescriptorIndex] >= usb_device_descriptor[17])	// TODO: remove magic
				usb_RequestError();
			usb_desc_ptr = usb_config_descriptor;
			usb_desc_len = usb_desc_ptr[2] + usb_desc_ptr[3] * 256;
			for (i=0; i<packet[USB_bDescriptorIndex]; i++) {				// Implicit linked list traversal until requested configuration
				usb_desc_ptr += usb_desc_len;
				usb_desc_len = usb_desc_ptr[2] + usb_desc_ptr[3] * 256;
			}
			if ((packet[USB_wLengthHigh] <  usb_desc_ptr[3]) || 
				(packet[USB_wLengthHigh] == usb_desc_ptr[3] && packet[USB_wLength] < usb_desc_ptr[2]))
				usb_desc_len = packet[USB_wLength] + packet[USB_wLengthHigh] * 256;
			DPRINTF("DEV Conf_desc_req 0x%02X 0x%02X%02X ", packet[USB_bDescriptorIndex], packet[USB_wLengthHigh], packet[USB_wLength]);
			break;
		case USB_STRING_DESCRIPTOR_TYPE:
			// TODO: Handle language request. For now return standard language.
			if (packet[USB_bDescriptorIndex] >= usb_num_string_descriptors)
				usb_RequestError();
			usb_desc_ptr = usb_string_descriptor;
			usb_desc_len = usb_desc_ptr[0];
			for (i=0; i<packet[USB_bDescriptorIndex]; i++) {				// Implicit linked list traversal until requested configuration
				usb_desc_ptr += usb_desc_len;
				usb_desc_len = usb_desc_ptr[0];
			}
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

			/* Configure endpoints (USB_UEPn - registers) */
			for (i=0; i<16; i++) {
				USB_UEP[i] = endpoints[i].type;
				/* Configure buffer descriptors */
#if USB_PP_BUF_MODE == 0
				usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDCNT  = endpoints[i].buffer_size;
				usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN + DTSEN;
				usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDCNT  = 0;
				usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = DTS + DTSEN;	// Set DTS => First packet inverts, ie. is Data0
#else
				// TODO: Implement Ping-Pong buffering setup.
				#error "PP Mode not implemented yet"
#endif
			}
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
	unsigned char epnum;
	unsigned char dir;
	BDentry	*epbd;

	packet = bdp->BDADDR;

	switch (packet[USB_bRequest]) {
	case USB_REQUEST_GET_STATUS:
		epnum = packet[USB_wIndex] & 0x0F;
		dir = packet[USB_wIndex] >> 7;
		rbdp->BDADDR[0] = USB_UEP[epnum] & USB_UEP_EPSTALL;
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
	DPRINTF("In  EP: %u Handler: 0x%p\t", trn_status >> 3, endpoints[USB_STAT2EP(trn_status)].in_handler);
	if (endpoints[USB_STAT2EP(trn_status)].in_handler) {
		endpoints[USB_STAT2EP(trn_status)].in_handler();
	} else {
		DPRINTF("No handler\n");
	}
}

void usb_handle_out( void ) {
	DPRINTF("Out EP: %u Handler: 0x%p\t", trn_status >> 3, endpoints[USB_STAT2EP(trn_status)].out_handler);
	//rbdp->BDSTAT &= ~UOWN;									// Reclaim reply buffer
	if (endpoints[USB_STAT2EP(trn_status)].out_handler) {
		endpoints[USB_STAT2EP(trn_status)].out_handler();
	} else {
		DPRINTF("No handler\n");
	}
}

void usb_register_endpoint(	unsigned int ep, usb_uep_t type, unsigned int buf_size, 
							unsigned char *out_buf, unsigned char *in_buf, 
							usb_handler_t out_handler, usb_handler_t in_handler ) {
	endpoints[ep].type			= type;
	endpoints[ep].buffer_size	= buf_size;
	endpoints[ep].out_buffer	= out_buf;
	endpoints[ep].in_buffer		= in_buf;
	endpoints[ep].out_handler	= out_handler;
	endpoints[ep].in_handler	= in_handler;
}

void usb_set_in_handler(int ep, usb_handler_t in_handler) {
	endpoints[ep].in_handler = in_handler;
}

void usb_set_out_handler(int ep, usb_handler_t out_handler) {
	endpoints[ep].out_handler = out_handler;
}

void usb_ack( BDentry *bd ) {
	bd->BDSTAT = ((bd->BDSTAT ^ DTS) & DTS) | UOWN | DTSEN;		// TODO: Accomodate for >=256 byte buffers
}

void usb_ack_zero( BDentry *bd ) {
	bd->BDCNT = 0;
	bd->BDSTAT = ((bd->BDSTAT ^ DTS) & DTS) | UOWN | DTSEN;
}

void usb_ack_out( BDentry *bd ) {
	bd->BDCNT = USB_MAX_BUFFER_SIZE;	// TODO: Fix correct size for current EP
	bd->BDSTAT = ((bd->BDSTAT ^ DTS) & DTS) | UOWN | DTSEN;
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
		SetUsbAddress(usb_addr_pending);
		usb_addr_pending = 0xFF;
		DPRINTF("Address set 0x%02X\n", GetUsbAddress());
	}
	usb_unset_in_handler(0);								// Unregister handler
}

void usb_send_descriptor( void ) {
	unsigned int i;
	BDentry *bd;
	size_t packet_len;
	if (usb_desc_len) {
		packet_len = (usb_desc_len < USB_MAX_BUFFER_SIZE) ? usb_desc_len : USB_MAX_BUFFER_SIZE;		// Allways on EP0 so use MAX_BUFFER_SIZE
		bd = &usb_bdt[USB_CALC_BD(0, USB_DIR_IN, 0x01 ^ ((trn_status & 0x02)>>1))];
		DPRINTF("Send bd: 0x%p dst: 0x%p src: 0x%p len: %u Data: ", rbdp, rbdp->BDADDR, usb_desc_ptr, packet_len);
		//ARCH_memcpy(rbdp->BDADDR, usb_desc_ptr, packet_len);
		for (i=0; i<packet_len; i++) {
			rbdp->BDADDR[i] = usb_desc_ptr[i];
			DPRINTF("0x%02X ", rbdp->BDADDR[i]);
		}
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
