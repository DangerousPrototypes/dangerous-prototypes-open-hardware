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
*/

#include <string.h>
#include "usb_stack.h"
#include "descriptors.h"

// CDC Request Codes
#define CDC_SEND_ENCAPSULATED_COMMAND						0x00
#define CDC_GET_ENCAPSULATED_RESPONSE						0x01
#define CDC_SET_COMM_FEATURE								0x02
#define CDC_GET_COMM_FEATURE								0x03
#define CDC_CLEAR_COMM_FEATURE								0x04
//		RESERVED (future use)								0x05-0x0F
#define CDC_SET_AUX_LINE_STATE								0x10
#define CDC_SET_HOOK_STATE									0x11
#define CDC_PULSE_SETUP										0x12
#define CDC_SEND_PULSE										0x13
#define CDC_SET_PULSE_TIME									0x14
#define CDC_RING_AUX_JACK									0x15
//		RESERVED (future use)								0x16-0x1F
#define CDC_SET_LINE_CODING									0x20
#define CDC_GET_LINE_CODING									0x21
#define CDC_SET_CONTROL_LINE_STATE							0x22
#define CDC_SEND_BREAK										0x23
//		RESERVED (future use)								0x24-0x2F
#define CDC_SET_RINGER_PARMS								0x30
#define CDC_GET_RINGER_PARMS								0x31
#define CDC_SET_OPERATION_PARMS								0x32
#define CDC_GET_OPERATION_PARMS								0x33
#define CDC_SET_LINE_PARMS									0x34
#define CDC_GET_LINE_PARMS									0x35
#define CDC_DIAL_DIGITS										0x36
#define CDC_SET_UNIT_PARAMETER								0x37
#define CDC_GET_UNIT_PARAMETER								0x38
#define CDC_CLEAR_UNIT_PARAMETER							0x39
#define CDC_GET_PROFILE										0x3A
//		RESERVED (future use)								0x3B-0x3F
#define CDC_SET_ETHERNET_MULTICAST_FILTERS					0x40
#define CDC_SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER	0x41
#define CDC_GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER	0x42
#define CDC_SET_ETHERNET_PACKET_FILTER						0x43
#define CDC_GET_ETHERNET_STATISTIC							0x44
//		RESERVED (future use)								0x45-0x4F
#define CDC_SET_ATM_DATA_FORMAT								0x50
#define CDC_GET_ATM_DEVICE_STATISTICS						0x51
#define CDC_SET_ATM_DEFAULT_VC								0x52
#define CDC_GET_ATM_VC_STATISTICS							0x53
//		RESERVED (future use)								0x54-0x5F
//		MDLM Semantic-Model specific Requests				0x60–0x7F
//		RESERVED (future use)								0x80-0xFF

// CDC Notification Codes
#define CDC_NETWORK_CONNECTION								0x00
#define CDC_RESPONSE_AVAILABLE								0x01
//		RESERVED (future use)								0x02-0x07
#define CDC_AUX_JACK_HOOK_STATE								0x08
#define CDC_RING_DETECT										0x09
//		RESERVED (future use)								0x0A-0x1F
#define CDC_SERIAL_STATE									0x20
//		RESERVED (future use)								0x21-0x27
#define CDC_CALL_STATE_CHANGE								0x28
#define CDC_LINE_STATE_CHANGE								0x29
#define CDC_CONNECTION_SPEED_CHANGE							0x2A
//		RESERVED											0x2B-0x3F
//		MDML SEMANTIC-MODEL-SPECIFIC NOTIFICATION			0x40-0x5F
//		RESERVED (future use)								0x60-0xFF

void cdc_setup( void );
void cdc_set_line_coding_data( void );
void cdc_set_line_coding_status( void );
void cdc_get_line_coding( void );
void cdc_set_control_line_state_status( void );
void cdc_acm_out( void );
void cdc_acm_in( void );
void cdc_rx( void );
void cdc_tx( void );
void cdc_flush_tx( void );

enum stopbits {one=0, oneandahalf=1, two=2};
enum parity {none=0, odd=1, even=2, mark=3, space=4};
const char parity_str[] = {'N','O','E','M','S'};

struct cdc_LineCodeing {
	unsigned long int	dwDTERate;
	enum stopbits		bCharFormat;
	enum parity			bParityType;
	unsigned char		bDataBits;
} linecodeing;

struct cdc_ControlLineState {
	int	DTR:1;
	int	RTS:1;
	int unused1:6;
	char unused2;
} cls;

unsigned char *data, *data_end;
volatile BDentry *rxbdp, *txbdp;

#pragma udata usb_data
unsigned char cdc_acm_out_buffer[CDC_BUFFER_SIZE];
unsigned char cdc_acm_in_buffer[CDC_BUFFER_SIZE];
unsigned char cdc_rx_buffer[CDC_BUFFER_SIZE];
unsigned char cdc_tx_buffer[CDC_BUFFER_SIZE];
#pragma udata

void InitCDC(void) {

	usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS);	// TODO: Remove magic with macro

	linecodeing.dwDTERate = 115200;
	linecodeing.bCharFormat = one;
	linecodeing.bParityType = none;
	linecodeing.bDataBits = 8;
	cls.DTR = 0;
	cls.RTS = 0;
	rxbdp = &usb_bdt[USB_CALC_BD(2, USB_DIR_OUT, USB_PP_EVEN)];
	txbdp = &usb_bdt[USB_CALC_BD(2, USB_DIR_IN, USB_PP_EVEN)];
	data = data_end = 0;
	usb_register_endpoint(1, USB_EP_INOUT, CDC_BUFFER_SIZE, cdc_acm_out_buffer, cdc_acm_in_buffer, cdc_acm_out, cdc_acm_in);
	usb_register_endpoint(2, USB_EP_INOUT, CDC_BUFFER_SIZE, cdc_rx_buffer, cdc_tx_buffer, cdc_rx, cdc_tx);
	usb_register_sof_handler(cdc_flush_tx);
	usb_register_class_setup_handler(0, cdc_setup);
	usb_start();
}

void cdc_setup(void){
	unsigned char *packet;
	unsigned int i;
	size_t reply_len;
	packet = bdp->BDADDR;
	switch (packet[USB_bmRequestType] & (USB_bmRequestType_TypeMask | USB_bmRequestType_RecipientMask)) {
	case (USB_bmRequestType_Class | USB_bmRequestType_Interface):
		switch (packet[USB_bRequest]) {

		case CDC_SEND_ENCAPSULATED_COMMAND:		// Required TODO: Implement
			usb_ack_zero(rbdp);
			DPRINTF("CDC_SEND_ENCAPSULATED_COMMAND\n");
			break;

		case CDC_GET_ENCAPSULATED_RESPONSE:		// Required TODO: Implement
			usb_ack_zero(rbdp);
			DPRINTF("CDC_SEND_ENCAPSULATED_RESPONSE\n");
			break;

		case CDC_SET_COMM_FEATURE:				// Optional
		case CDC_GET_COMM_FEATURE:				// Optional
		case CDC_CLEAR_COMM_FEATURE:			// Optional
			usb_RequestError();		// Not advertised in ACM functional descriptor
			break;

		case CDC_SET_LINE_CODING:				// Optional, strongly recomended
			usb_set_out_handler(0, cdc_set_line_coding_data);	// Register out handler function
			DPRINTF("CDC_SET_LINE_CODING\n");
			break;

		case CDC_GET_LINE_CODING:				// Optional, strongly recomended
			reply_len = *((unsigned int *) &packet[USB_wLength]);
			if (sizeof(struct cdc_LineCodeing) < reply_len) {
				reply_len = sizeof(struct cdc_LineCodeing);
			}
			memcpy(rbdp->BDADDR, (const void *) &linecodeing, reply_len);
			rbdp->BDCNT = reply_len;
			usb_ack(rbdp);
			usb_set_in_handler(0, cdc_get_line_coding);

			DPRINTF("CDC_GET_LINE_CODING bd: 0x%p len: %u Data: ", rbdp, reply_len);
			for (i=0; i<rbdp->BDCNT; i++)
				DPRINTF("0x%02X ", rbdp->BDADDR[i]);
			DPRINTF("\n");
			break;

		case CDC_SET_CONTROL_LINE_STATE:		// Optional
			cls = *((struct cdc_ControlLineState *) &packet[USB_wValue]);
			usb_set_in_handler(0, cdc_set_control_line_state_status);
			usb_ack_zero(rbdp);

			DPRINTF("CDC_SET_LINE_STATE 0x%04X\n", *((int *) (&cls)));
			break;

		case CDC_SEND_BREAK:					// Optional
		default:
			usb_RequestError();
		}
		break;
	default:
		usb_RequestError();
	}
}

void cdc_get_line_coding( void ) {
	usb_unset_in_handler(0);					// Unregister IN handler;
	DPRINTF("CDC_GET_LINE_CODING Done\n");
}

void cdc_set_line_coding_data( void ) {
	memcpy(&linecodeing, (const void *) bdp->BDADDR, sizeof(struct cdc_LineCodeing));
	usb_unset_out_handler(0);					// Unregister OUT handler;
	usb_set_in_handler(0, cdc_set_line_coding_status);
	usb_ack_zero(rbdp);
	usb_ack_out(bdp);

	DPRINTF("CDC_SET_LINE_CODING %lu-%c-%hhu-%hhu\n", 
			linecodeing.dwDTERate, 
			(int) parity_str[(unsigned char) linecodeing.bParityType],
			linecodeing.bDataBits,
			linecodeing.bCharFormat + 1);
}

void cdc_set_line_coding_status( void ) {
	usb_unset_in_handler(0);
	DPRINTF("CDC_SET_LINE_CODING Done\n");
}

void cdc_set_control_line_state_status( void ) {
	usb_unset_in_handler(0);
	DPRINTF("CDC_SET_CONTROL_LINE_STATE Done\n");
}

void cdc_acm_out( void ) {
	DPRINTF("cdc_acm_out\n");
}

void cdc_acm_in( void ) {
	DPRINTF("cdc_acm_in\n");
	/*
	if (0) { // Response Available Notification
		// Not TODO: Probably never implement this, we're not a modem.
		// Is this correct placement of the response notification?
		bdp->BDADDR[USB_bmRequestType]	= USB_bmRequestType_D2H | USB_bmRequestType_Class | USB_bmRequestType_Interface;
		bdp->BDADDR[USB_bRequest]		= CDC_RESPONSE_AVAILABLE;
		bdp->BDADDR[USB_wValue]			= 0;
		bdp->BDADDR[USB_wValueHigh]		= 0;
		bdp->BDADDR[USB_wIndex]			= 0;
		bdp->BDADDR[USB_wIndexHigh]		= 0;
		bdp->BDADDR[USB_wLength]		= 0;
		bdp->BDADDR[USB_wLengthHigh]	= 0;
		bdp->BDCNT = 8;
		usb_ack(bdp);
	} else if (0) {	// Network Connection Notification
	} else if (0) {	// Serial State Notification
	}
	*/
}

void cdc_rx( void ) {
	data = rxbdp->BDADDR;
	data_end = rxbdp->BDADDR + rxbdp->BDCNT;
	DPRINTF("cdc_rx 0x%p bytes recv %u\t", rxbdp, rxbdp->BDCNT);
	DPRINTF("'%.*s'\n", (int) rxbdp->BDCNT, rxbdp->BDADDR);
	if (0 == rxbdp->BDCNT)	usb_ack_out(rxbdp);
}

void cdc_tx( void ) {
	DPRINTF("cdc_tx 0x%p 0x%02X bytes sent %u\n", bdp, txbdp->BDSTAT, bdp->BDCNT);
	txbdp->BDCNT = 0;
	usb_register_sof_handler(cdc_flush_tx);
}

void cdc_flush_tx( void ) {
	if (txbdp->BDCNT && !(txbdp->BDSTAT & UOWN)) {
		usb_ack(txbdp);
		DPRINTF("Flush  0x%p 0x%02X bytes to send %u\n", txbdp, txbdp->BDSTAT, txbdp->BDCNT);
		usb_register_sof_handler(NULL);
	}
}

/* Configure the USART. */
void OpenCDC(unsigned char config, unsigned int spbrg) {
//	config;
//	spbrg;
}

/* Disable the CDC. */
void CloseCDC( void ) {
}

/* Is the CDC transmitting? */
char BusyCDC( void ) {
	return ((txbdp->BDSTAT & UOWN) /*|| (txbdp->BDCNT)*/);	// TODO: Implement PP buffering
}

/* Is data available in the CDC read buffer? */
char DataRdyCDC( void ) {
	return !(data == data_end);
}

/* Read a byte from the CDC. */
char getcCDC( void ) {
	char c;
	while (data==data_end);
	c = *data++;
	if (data == data_end) usb_ack_out(rxbdp);
	return c;
}

/* Read an array from the USBART. */
unsigned char getaCDC( char *buffer, unsigned char len ) {
	unsigned char pkt_len = (unsigned char) (data_end - data);
	if (pkt_len > len)
		pkt_len = len;
	memcpy(buffer, (const void *) data, pkt_len);
	data += pkt_len;
	if (pkt_len && data == data_end) usb_ack_out(rxbdp);	// Do not ack if we didn't recieve something in the first place
	return pkt_len;
}
	
/* Read a string from the CDC ACM. */
void getsCDC( char *buffer, unsigned char len) {
	unsigned char i;
	for (i=0; i<len; i++) *buffer++ = getcCDC();
}

/* Write a byte to the USART. */
void putcCDC( char c ) {
	// DPRINTF("putc   0x%p 0x%02X bytes so far %u\n", txbdp, txbdp->BDSTAT, txbdp->BDCNT);
	// TODO: Verify thread (interrupt) safety
	while (txbdp->BDSTAT & UOWN);
	DisableUsbInterrupts();
	txbdp->BDADDR[txbdp->BDCNT++] = c;
	//DPRINTF(" added '%c' bytes to send %u (0x%02X)\n", c, txbdp->BDCNT, txbdp->BDSTAT);
	if (CDC_BUFFER_SIZE == txbdp->BDCNT) {
		DPRINTF("Buffer full ");
		cdc_flush_tx();
		// TODO: An extra packet of length zero needs to be sent to tell host no more data available.
	}
	EnableUsbInterrupts();
}

/*
int _user_putc( char c ) {
	// TODO: Implement thread (interrupt) safety
	while (txbdp->BDSTAT & UOWN);
	DisableUsbInterrupts();
	txbdp->BDADDR[txbdp->BDCNT++] = c;
	usb_ack(txbdp);
	EnableUsbInterrupts();
	return (int) c;
}
*/

/* Write an array from data memory to the USBART. */
void putaCDC( const char *str, unsigned int len ) {
	/* Really want to use duffs device here, but it'll make this overly complex :-( */
	unsigned char pkt_len;
	while (len) {
		while (BusyCDC());
		DisableUsbInterrupts();
		pkt_len = (len<CDC_BUFFER_SIZE)? (unsigned char) len : CDC_BUFFER_SIZE;
		memcpy(txbdp->BDADDR, str, pkt_len);
		txbdp->BDCNT = pkt_len;
		len -= pkt_len;
		cdc_flush_tx();
		EnableUsbInterrupts();
	}
}

/* Write a string from data memory to the USART. */
void putsCDC( const char *str ) {
	while(*str)
		putcCDC(*str++);
}

/* Write a string from program memory to the USART. */
void putrsCDC( const char *str ) {
	while(*str)
		putcCDC(*str++);
}

/* Set the baud rate configuration bits for enhanced USART. */
void baudCDC( unsigned char baudconfig ) {
//	baudconfig;
}

