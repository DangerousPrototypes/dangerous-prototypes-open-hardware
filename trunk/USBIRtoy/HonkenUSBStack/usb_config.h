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

#ifndef __USB_CONFIG_H__
#define __USB_CONFIG_H__

/* Power source setting
 *  _BUS_  - MCU is powered from USB connector
 *  _SELF_ - MCU is provided by independent power supply
 */
#define USB_BUS_POWERED 1
#define USB_INTERNAL_TRANSCIEVER 1
#define USB_INTERNAL_PULLUPS 1
#define USB_INTERNAL_VREG 1
#define USB_FULL_SPEED_DEVICE 1

/* PingPong Buffer Mode 
 * Valid values 
 * 0 - No PingPong Buffers
 * 1 - PingPong on EP0
 * 2 - PingPong on all EP
 * 3 - PingPong on all except EP0
 */
#define USB_PP_BUF_MODE 0

#define USB_MAX_BUFFER_SIZE	8u
#define RXTX_BUFFER_SIZE 32u

/* Configure endpoints
 *	Define a list (row concatenations "\") of USB_EP-macros
 *
 *	USB_EP( 0-15,
			USB_EP_CONTROL / USB_EP_IN / USB_EP_OUT / USB_EP_INOUT,
			USB_EP_BULK/USB_EP_INTERRUPT/USB_EP_ISOCHRONOUS,
			buffer size (8, 16, 32, 64, 128)
			callback function of prototype "void (*callback)(unsigned char)"
 *
 *  Note:
 *   Endpoint Zero must not be configured.
 *   Endpoint numbers must be consecutive, for now.
 *   Buffer size must be one of 8, 16, 32, 64, 128 for now.
 *
 *	example:
 *
 */
#define USB_ENDPOINTS \
	USB_EP(1, USB_EP_CONTROL, USB_EP_INTERRUPT, 16, cdc_acm) \
	USB_EP(2, USB_EP_OUT, USB_EP_BULK, RXTX_BUFFER_SIZE, cdc_rx) \
	USB_EP(3, USB_EP_IN, USB_EP_BULK, RXTX_BUFFER_SIZE, cdc_tx)

#define class_setup cdc_setup
#define class_init cdc_init

extern void cdc_rx( void );
extern void cdc_tx( void );

/* Low Power Request 
 * Optional user supplied subroutine to set the circuit 
 * into low power mode during usb suspend.
 * Probably needed when bus powered as only 2.5mA should
 * be drawn from bus i suspend mode */
//#define usb_low_power_request() Nop()


/* Descriptors */

//#error "Must supply VID, PID. These are just indication on of how to write"
//#define USB_VID 0x0000
//#define USB_PID 0X0000
#include "USBID.h"
#define USB_DEV 0x0410

#define USB_NUM_CONFIGURATIONS	1u
#define USB_NUM_INTERFACES		2u
#define USB_NUM_ENDPOINTS		3u

/* String identifiers */
#define USB_iManufacturer		1u
#define USB_iProduct			2u
#define USB_iSerialNum			3u

/* Strings
 * USB_STRING(0-255,		// String identifier
 *            0-255,		// String length in number of codepoints
 *            codepoints)	// two bytes per UTF-16 codepoint in little endian order
 * string 0 is actually a list of supported languages, only 1 language supported for now
 * All real strings is supposed to be encoded UTF-16LE (ie. a null byte after every 7-bit ASCII character */
#define USB_STRINGS \
	USB_STRING(0, 1, USB_LANGID_English_United_States) \
	USB_STRING(USB_iManufacturer,  6, 'H',0,'o',0,'n',0,'k',0,'e',0,'n',0) \
	USB_STRING(USB_iProduct,      15, 'G',0,'e',0,'n',0,'e',0,'r',0,'i',0,'c',0,' ',0,'p',0,'r',0,'o',0,'d',0,'u',0,'c',0,'t',0) \
	USB_STRING(USB_iSerialNum,     8, '0',0,'0',0,'0',0,'0',0,'0',0,'0',0,'0',0,'1',0)

#endif /* USB_CONFIG_H */
