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

//#error "Must supply VID, PID. These are just indication on of how to write"
#define USB_VID 0x04D8
#define USB_PID 0XFD08
#define USB_DEV 0x0410

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

//#define USB_EP0_BUFFER_SIZE 8u
#define CDC_BUFFER_SIZE 32u
#define USB_MAX_BUFFER_SIZE	32u

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
	USB_EP(2, USB_EP_OUT, USB_EP_BULK, CDC_BUFFER_SIZE, cdc_rx) \
	USB_EP(3, USB_EP_IN, USB_EP_BULK, CDC_BUFFER_SIZE, cdc_tx)

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

#define USB_NUM_CONFIGURATIONS	1u
#define USB_NUM_INTERFACES		3u
#define USB_NUM_ENDPOINTS		3u

/* String identifiers */
#define USB_iManufacturer		1u
#define USB_iProduct			2u
#define USB_iSerialNum			3u

#endif /* USB_CONFIG_H */
