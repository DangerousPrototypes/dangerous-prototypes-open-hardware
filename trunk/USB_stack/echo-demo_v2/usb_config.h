/*
This work is licensed under the Creative Commons Attribution 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
or send a letter to
        Creative Commons,
        171 Second Street,
        Suite 300,
        San Francisco,
        California,\
 * 
        94105,
        USA.

// JTR v0.1a
// JTR v0.1b  renamed BUSPIRATEV4 and all other wardware to be UPPERCASE 


/* JTR
This file operates as the global header for <function> implementation
It is applicable to both PIC18 and PIC24.

This is the main BOSS configuration file. It is to be included 
in:

usb_stack.c
cdc.c or other CLASS file.
configwords.h
main.c
descriptors.h

In this file you can define:

ENDPOINT SIZES Applies to EP0 and other class specific endpoints
PING-PONG MODE
BUS or SELF POWERED
VID & PID
USB TRANSCEIVER MODE
USB_NUM_CONFIGURATIONS  
USB_NUM_INTERFACES      
USB_NUM_ENDPOINTS
USB_NUM_STRINGS

USB configured LED
Other misc LEDs and hardware. 

Low power request macro
*/

//#if(0)

#ifndef __USB_CONFIG_H__
#define __USB_CONFIG_H__

// which class do we implement?
#define USE_CDC
//#define USE_HID

// usb hardware config
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

/* Low Power Request
 * Optional user supplied subroutine to set the circuit
 * into low power mode during usb suspend.
 * Probably needed when bus powered as only 2.5mA should
 * be drawn from bus i suspend mode */
//#define usb_low_power_request() Nop()

// place your vid/pid here
#define USB_VID (0x0000)
#define USB_PID (0x0000)
#define USB_DEV 0x0002

// place your usb descriptor strings here, assuming us english
#define USB_MANUFACT    42, USB_STRING_DESCRIPTOR_TYPE, 'D',0,'a',0,'n',0,'g',0,'e',0,'r',0,'o',0,'u',0,'s',0,' ',0,'P',0,'r',0,'o',0,'t',0,'o',0,'t',0,'y',0,'p',0,'e',0,'s',0
#define USB_PRODUCT     18, USB_STRING_DESCRIPTOR_TYPE, 'C',0,'D',0,'C',0,' ',0,'T',0,'e',0,'s',0,'t',0
#define USB_SERIAL      18, USB_STRING_DESCRIPTOR_TYPE, '0',0,'0',0,'0',0,'0',0,'0',0,'0',0,'0',0,'1',0

// general stuff ends here

// CDC specific
#ifdef USE_CDC

#define CDC_BUFFER_SIZE 64u
#define CDC_NOTICE_BUFFER_SIZE 10u

#define USB_NUM_CONFIGURATIONS          1u
#define USB_NUM_INTERFACES              2u
#define USB_NUM_ENDPOINTS               3u
#define USB_NUM_STRINGS                 4u
#define MAX_EPNUM_USED                  2u

#elif USE_HID

#endif

#endif /* CDC_CONFIG_H */
