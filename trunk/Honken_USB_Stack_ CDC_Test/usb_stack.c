/*
$Id$

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

#if defined(PIC_18F)
#include <p18cxxx.h>
#elif defined(PIC_24F) 
#include <p24fxxxx.h>
#endif

#include <stddef.h>
#include "usb_stack.h"

ROMPTR const unsigned char *usb_device_descriptor;
ROMPTR const unsigned char *usb_config_descriptor;
ROMPTR const unsigned char *usb_string_descriptor;
int usb_num_string_descriptors;
usb_handler_t reset_handler;
usb_handler_t sof_handler;
usb_handler_t class_setup_handler[USB_NUM_INTERFACES];
usb_handler_t vendor_setup_handler;

usb_ep_t endpoints[USB_ARCH_NUM_EP];

/* Allocate buffers for buffer description table and the actual buffers */
// CvD: linkscript puts it in the right memory location
#pragma udata usb_bdt
volatile BDentry usb_bdt[2*USB_ARCH_NUM_EP]			// TODO: Dynamic allocation reflecting number of used endpoints. (How to do counting in preprocessor?)
#if defined(PIC_24F)
__attribute__((aligned(512)))
#endif
;

#pragma udata usb_data
/* Only claim buffer for ep 0 */
#if USB_PP_BUF_MODE == 0
unsigned char usb_ep0_out_buf[USB_EP0_BUFFER_SIZE];
unsigned char usb_ep0_in_buf[USB_EP0_BUFFER_SIZE];
#else
#error "Ping pong buffer not implemented yet!"
#endif

#pragma udata

unsigned int usb_device_status;
unsigned int usb_configured;
unsigned char usb_addr_pending;
volatile unsigned char usb_state;
usb_status_t trn_status;					// Global since it is needed everywere
volatile BDentry *bdp, *rbdp;				// Dito

ROM const unsigned char *usb_desc_ptr;
size_t usb_desc_len;

/* Forward Reference Prototypes */
void usb_handle_error( void );
void usb_handle_reset( void );
void usb_handle_transaction( void );
void usb_handle_setup( void );
void usb_handle_out( void );
void usb_handle_in( void );
void usb_handle_StandardDeviceRequest( void );
void usb_handle_StandardInterfaceRequest( void );
void usb_handle_StandardEndpointRequest( void );
//void usb_handle_ClassRequest( void );
//void usb_handle_VendorRequest( void );
void usb_RequestError( void );

void usb_set_address( void );
void usb_send_descriptor( void );

// TODO: Make generic and move specifics into usb_p24f.h /Honken
/*
//implemented only for pic24f for now
//attach the device to the bus, enabling the D+ pull-up
void usb_attach()
{
	#ifdef PIC_24F	
	//should check for VBUS	
	usb_state=USB_STATE_ATTACHED;	
	DisableUsbInterrupts();
	DisableAllUsbInterrupts();
	//do we need to clear the interupt flags
	ClearAllUsbInterruptFlags();
	ClearAllUsbErrorInterruptFlags();	
	EnableUsb();
	while(SingleEndedZeroIsSet());	// wait for D+ voltage to stabilize, should find a way to do it asynchronously, maybe using idle interupt
	usb_state=USB_STATE_POWERED;
	EnableAllUsbInterrupts();
	EnableUsbInterrupts();

	
	
	
	#endif
};

//detach the device from the bus, disabling the D+ pull-up
void usb_detach()
{
	#ifdef PIC24f
	DisableUsbInterrupts();
	DisableAllUsbInterrupt();
	ClearAllUsbInterruptFlags();
	ClearAllErrorUsbInterruptFlags();
	usb_state=USB_STATE_DETACHED;
	DisableUsb();		
	#endif	
};
*/
void usb_init(	ROMPTR const unsigned char *device_descriptor, 
				ROMPTR const unsigned char *config_descriptor, 
				ROMPTR const unsigned char *string_descriptor,
				int num_string_descriptors ) {
	int i;

	DPRINTF("USB init ");

	usb_device_descriptor = device_descriptor;
	usb_config_descriptor = config_descriptor;
	usb_string_descriptor = string_descriptor;
	usb_num_string_descriptors = num_string_descriptors;

	ResetPPbuffers();

	DisableUsbInterrupts();
	DisableAllUsbInterrupts();
	DisableAllUsbErrorInterrupts();

	ClearAllUsbErrorInterruptFlags();
	ClearAllUsbInterruptFlags();
	
	ConfigureUsbHardware();
	EnablePacketTransfer();

	reset_handler = usb_handle_reset;
	sof_handler = NULL;
	vendor_setup_handler = NULL;

	for (i=0; i<USB_ARCH_NUM_EP; i++) {
		endpoints[i].type = 0;
		endpoints[i].buffer_size = 0;
		endpoints[i].out_buffer = NULL;
		endpoints[i].in_buffer = NULL;
		endpoints[i].out_handler = NULL;
		endpoints[i].in_handler = NULL;
	}

	usb_register_endpoint(0, USB_EP_CONTROL, USB_EP0_BUFFER_SIZE, usb_ep0_out_buf, usb_ep0_in_buf, NULL, NULL);		// Register ep0 - no handlers

	/* Configure endpoints TODO: Only ep0 ? */
	for (i=0; i<USB_ARCH_NUM_EP; i++) {
		/* Configure endpoints (USB_UEPn - registers) */
		USB_UEP[i] = endpoints[i].type;
		/* Configure buffer descriptors */
#if USB_PP_BUF_MODE == 0
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDCNT  = endpoints[i].buffer_size;
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDADDR = endpoints[i].out_buffer;
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN + DTSEN;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDCNT  = 0;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDADDR = endpoints[i].in_buffer;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = DTS;						// Set DTS => First packet inverts, ie. is Data0
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
	DisableUsbInterrupts();
	EnableUsb();					// Enable USB-hardware
	while(SingleEndedZeroIsSet());	// Busywait for initial power-up
	DPRINTF("sucessful\n");
	EnableAllUsbErrorInterrupts();	// Enable all errors to set flag in UIR
	EnableUsbInterrupt(USB_STALL + USB_IDLE + USB_TRN + USB_ACTIV + USB_SOF + USB_UERR + USB_URST);
	EnableUsbInterrupts();
}

void usb_stop( void ) {
	DPRINTF("Stopping usb ");
	DisableUsbInterrupts();
	DisableUsb();
	DPRINTF("detached\n");
}

void usb_handler( void ) {
	if (USB_ERROR_FLAG) {
		usb_handle_error();
		ClearUsbInterruptFlag(USB_UERR);
	} else if (USB_RESET_FLAG) {
		reset_handler();
		ClearUsbInterruptFlag(USB_URST);
	} else if (USB_ACTIVITY_FLAG) {
		/* Activity - unsuspend */
		WakeupUsb();
		ClearUsbInterruptFlag(USB_ACTIV);
		DPRINTF("Active\n");
	} else if (USB_IDLE_FLAG) {
		/* Idle - suspend */
		SuspendUsb();
		ClearUsbInterruptFlag(USB_IDLE);
		usb_low_power_request();
		DPRINTF("Idle\n");
	} else if (USB_STALL_FLAG) {
		/* Stall detected
		 * Not sure when this interrupt fires
		 * as the host never should send out a stall.
		 * Perhaps as a respons to our own stalls? 
		 * For now just ignore it. */
		ClearUsbInterruptFlag(USB_STALL);
		DPRINTF("Stall interrupt fired");
	} else if (USB_SOF_FLAG) {
		/* Start-of-frame */
		if (sof_handler) sof_handler();
		ClearUsbInterruptFlag(USB_SOF);
	} else {
		//process all pending transactions
		while(USB_TRANSACTION_FLAG) {
			usb_handle_transaction();
			ClearUsbInterruptFlag(USB_TRN);		// Side effect: advance USTAT Fifo
		}
	}
}

void usb_handle_error( void ) {
	DPRINTF("Error 0x%X\n", UsbErrorInterruptFlags());
	/* No errorhandler for now, just clear offending flag*/
	ClearAllUsbErrorInterruptFlags();
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

	for (i=0; i<USB_USTAT_FIFO_DEPTH; i++)
		ClearUsbInterruptFlag(USB_TRN);		// Advance USTAT FIFO to clear

	for (i=0; i<USB_ARCH_NUM_EP; i++)
		USB_UEP[i] = 0;				// Disable all endpoints

	SetUsbAddress(0);			// After reset we don't have an address
	ClearAllUsbInterruptFlags();
	ClearAllUsbErrorInterruptFlags();

	// TODO: Only configure ep0 ?
/* Configure endpoints (USB_UEPn - registers) */
	for (i=0; i<USB_ARCH_NUM_EP; i++) {
		USB_UEP[i] = endpoints[i].type;
		/* Configure buffer descriptors */
#if USB_PP_BUF_MODE == 0
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDCNT  = endpoints[i].buffer_size;
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDADDR = endpoints[i].out_buffer;
		usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN + DTSEN;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDCNT  = 0;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDADDR = endpoints[i].in_buffer;
		usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = DTS;				// Set DTS => First packet inverts, ie. is Data0
#else
		// TODO: Implement Ping-Pong buffering setup.
		#error "PP Mode not implemented yet"
#endif
	}
	EnableAllUsbErrorInterrupts();
	DPRINTF("Reset\n");
	usb_state=USB_STATE_DEFAULT;
}

void usb_handle_transaction( void ) {

	trn_status = GetUsbTransaction();
	bdp  = &usb_bdt[USB_USTAT2BD(trn_status)];
	rbdp = &usb_bdt[USB_CALC_BD(USB_STAT2EP(trn_status),
								USB_DIR_IN,
								USB_PP_EVEN)];		// All replies in IN direction, TODO: Accomodate Ping Pong buffers

//	DPRINTF("USTAT: 0x%02X PID 0x%02X DATA%c ", trn_status, bdp->BDSTAT % USB_TOKEN_Mask, (bdp->BDSTAT & 0x40)?'1':'0');
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
		/* Default case of unknown TOKEN - discard */
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
			usb_handle_StandardDeviceRequest();
			break;
		case USB_bmRequestType_Interface:
			usb_handle_StandardInterfaceRequest();
			break;
		case USB_bmRequestType_Endpoint:
			usb_handle_StandardEndpointRequest();
			break;
		default:
			usb_RequestError();
		}
		break;
	case USB_bmRequestType_Class:
		if (USB_NUM_INTERFACES > bdp->BDADDR[USB_bInterface] && class_setup_handler[bdp->BDADDR[USB_bInterface]])
			class_setup_handler[bdp->BDADDR[USB_bInterface]]();
		else
			usb_RequestError();
		break;
	case USB_bmRequestType_Vendor:
		if (vendor_setup_handler)
			vendor_setup_handler();
		else
			usb_RequestError();
		break;
	default:
		usb_RequestError();
	}
	/* Prepare endpoint for new reception */
	bdp->BDCNT = USB_EP0_BUFFER_SIZE;	// TODO: Fix correct size for current EP, should always be ep0?
	bdp->BDSTAT = (!(bdp->BDADDR[USB_bmRequestType] & USB_bmRequestType_PhaseMask) &&
					(bdp->BDADDR[USB_wLength] || bdp->BDADDR[USB_wLengthHigh]))? UOWN + DTS + DTSEN : UOWN + DTSEN;
	EnablePacketTransfer();
}

void usb_handle_StandardDeviceRequest( void ) {
	unsigned char *packet = bdp->BDADDR;
	int i;
	DPRINTF("0x%02X ", packet[USB_bRequest]);
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
			rbdp->BDSTAT = UOWN + DTS + DTSEN;
			DPRINTF("DEV Clear_Feature 0x%02X\n", packet[USB_wValue]);
		} else
			usb_RequestError();
		break;
	case USB_REQUEST_SET_FEATURE:
		if (0x01u == packet[USB_wValue])	{	// TODO: Remove magic (REMOTE_WAKEUP_FEATURE)
			usb_device_status |= 0x0002;
			rbdp->BDCNT = 0;
			rbdp->BDSTAT = UOWN + DTS + DTSEN;
			DPRINTF("DEV Set_Feature 0x%02X\n", packet[USB_wValue]);
		} else
			usb_RequestError();
		break;
	case USB_REQUEST_SET_ADDRESS:
		if (0x00u == packet[USB_wValueHigh] && 0x7Fu >= packet[USB_wValue]) {
			usb_addr_pending = packet[USB_wValue];
			rbdp->BDCNT = 0;
			rbdp->BDSTAT = UOWN + DTS + DTSEN;
			usb_set_in_handler(0, usb_set_address);
			DPRINTF("DEV Set address 0x%02X\n", usb_addr_pending);
		} else
			usb_RequestError();
		break;
	case USB_REQUEST_GET_DESCRIPTOR:
		DPRINTF("0x%02X ", packet[USB_bDescriptorType]);
		switch (packet[USB_bDescriptorType]) {
		case USB_DEVICE_DESCRIPTOR_TYPE:
			usb_desc_ptr = usb_device_descriptor;
			usb_desc_len = usb_device_descriptor[0];
			if ((0 == packet[USB_wLengthHigh] && packet[USB_wLength] < usb_desc_ptr[0]))
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
			DPRINTF("DEV Str_desc_req 0x%02X 0x%02X%02X ", packet[USB_bDescriptorIndex], packet[USB_wLengthHigh], packet[USB_wLength]);
			if (packet[USB_bDescriptorIndex] >= usb_num_string_descriptors)
				usb_RequestError();
			usb_desc_ptr = usb_string_descriptor;
			usb_desc_len = usb_desc_ptr[0];
			for (i=0; i<packet[USB_bDescriptorIndex]; i++) {				// Implicit linked list traversal until requested configuration
				usb_desc_ptr += usb_desc_len;
				usb_desc_len = usb_desc_ptr[0];
			}
			if ((0 == packet[USB_wLengthHigh] && packet[USB_wLength] < usb_desc_ptr[0]))
				usb_desc_len = packet[USB_wLength];
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
			// TODO: Support multiple configurations
			/* Configure endpoints (USB_UEPn - registers) */
			for (i=0; i<USB_ARCH_NUM_EP; i++) {
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

void usb_handle_StandardInterfaceRequest( void ) {
	unsigned char *packet = bdp->BDADDR;

	switch (packet[USB_bRequest]) {
	case USB_REQUEST_GET_STATUS:
		rbdp->BDADDR[0] = 0x00;
		rbdp->BDADDR[1] = 0x00;
		rbdp->BDCNT = 2;
		rbdp->BDSTAT = UOWN + DTS + DTSEN;
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

void usb_handle_StandardEndpointRequest( void ) {
	unsigned char *packet;
	unsigned char epnum;
	unsigned char dir;
	volatile BDentry	*epbd;

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

/*
void usb_handle_ClassRequest( void ) {
	class_setup(); // TODO: Refactor
}


void usb_handle_VendorRequest( void ) {
	DPRINTF("Vendor\n");
}
*/

void usb_handle_in( void ) {
//	DPRINTF("In  EP: %u Handler: 0x%p\t", trn_status >> 3, endpoints[USB_STAT2EP(trn_status)].in_handler);
	if (endpoints[USB_STAT2EP(trn_status)].in_handler) {
		endpoints[USB_STAT2EP(trn_status)].in_handler();
	} else {
//		DPRINTF("No handler\n");
	}
}

void usb_handle_out( void ) {
//	DPRINTF("Out EP: %u Handler: 0x%p\t", trn_status >> 3, endpoints[USB_STAT2EP(trn_status)].out_handler);
	//rbdp->BDSTAT &= ~UOWN;									// Reclaim reply buffer
	if (endpoints[USB_STAT2EP(trn_status)].out_handler) {
		endpoints[USB_STAT2EP(trn_status)].out_handler();
	} else {
//		DPRINTF("No handler\n");
	}
}

void usb_register_reset_handler( usb_handler_t handler ) {
	if (handler)
		reset_handler = handler;
	else
		reset_handler = &usb_handle_reset;
}

void usb_register_sof_handler( usb_handler_t handler ) {
	sof_handler = handler;
}

void usb_register_class_setup_handler( unsigned char iface, usb_handler_t handler ) {
	if (USB_NUM_INTERFACES > iface)
		class_setup_handler[iface] = handler;
	// Else silently ignore
}

void usb_register_vendor_setup_handler( usb_handler_t handler ) {
	vendor_setup_handler = handler;
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

void usb_ack( volatile BDentry *bd ) {
	bd->BDSTAT = ((bd->BDSTAT ^ DTS) & DTS) | UOWN | DTSEN;		// TODO: Accomodate for >=256 byte buffers
}

void usb_ack_zero( volatile BDentry *bd ) {
	bd->BDCNT = 0;
	bd->BDSTAT = ((bd->BDSTAT ^ DTS) & DTS) | UOWN | DTSEN;
}

void usb_ack_out( volatile BDentry *bd ) {
	bd->BDCNT = USB_MAX_BUFFER_SIZE;	// TODO: Fix correct size for current EP
	bd->BDSTAT = ((bd->BDSTAT ^ DTS) & DTS) | UOWN | DTSEN;
}

void usb_RequestError( void ) {
	unsigned int i;

	usb_bdt[USB_CALC_BD(0, USB_DIR_OUT, USB_PP_EVEN)].BDCNT = USB_EP0_BUFFER_SIZE;
	usb_bdt[USB_CALC_BD(0, USB_DIR_OUT, USB_PP_ODD)].BDCNT = USB_EP0_BUFFER_SIZE;

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
		usb_state=USB_STATE_ADDRESS;
		DPRINTF("Address set 0x%02X\n", GetUsbAddress());
	}
	usb_unset_in_handler(0);								// Unregister handler
}

void usb_send_descriptor( void ) {
	unsigned int i;
	size_t packet_len;
	if (usb_desc_len) {
		packet_len = (usb_desc_len < USB_EP0_BUFFER_SIZE) ? usb_desc_len : USB_EP0_BUFFER_SIZE;		// Allways on EP0 so use MAX_BUFFER_SIZE
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
