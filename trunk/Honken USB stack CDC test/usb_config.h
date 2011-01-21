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

Revision:
7 01/11/2011
	-	Commented USB_VID and USB_PID so that the #error on the
		usb_stack.h will be triggered once this two have no values

*/

#ifndef __USB_CONFIG_H__
#define __USB_CONFIG_H__
#if defined(__18F2450) || defined(__18F2550) || defined(__18F4450) || defined(__18F4550) || defined(__18F14K50) || defined(__18F24J50)
	#define PIC_18F
#elif defined(__PIC24FJ256GB106__) || defined(__PIC24FJ256GB110__)
	#define PIC_24F
#endif
/*
You need to supply your own VID/PID here. The usb organisation demands every unique USB
device has an unique VID/PID number. 

There aren't currently any 'free' opensource VID/PID pairs and no ranges for hobbyists.
Microchip offers an unique VID/PID for small quantities (max 10.000), non commercial
products.
*/



// TODO: Uncomment and provide the necessary PID,VID
//#define USB_VID 0x
//#define USB_PID 0x


#define USB_DEV 0x0002

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

#define USB_EP0_BUFFER_SIZE 8u
#define CDC_BUFFER_SIZE 8u
#define USB_MAX_BUFFER_SIZE	8u

//#define class_setup cdc_setup
//#define class_init cdc_init

/* Low Power Request 
 * Optional user supplied subroutine to set the circuit 
 * into low power mode during usb suspend.
 * Probably needed when bus powered as only 2.5mA should
 * be drawn from bus i suspend mode */
//#define usb_low_power_request() Nop()


/* Descriptors */

#define USB_NUM_CONFIGURATIONS	1u
#define USB_NUM_INTERFACES		2u
#define USB_NUM_ENDPOINTS		3u
#define USB_NUM_STRINGS			4u

/* String identifiers */
#define USB_iManufacturer		1u
#define USB_iProduct			2u
#define USB_iSerialNum			3u

#endif /* USB_CONFIG_H */
