/*
*
*	USB infrared remote control receiver transmitter firmware
*	License: creative commons - attribution, share-alike 
*	Copyright Ian Lesnet 2010
*	http://dangerousprototypes.com
*
*/
//Our custom USB configuration
//see XXXX for a full list of options
#ifndef USBCFG_H
#define USBCFG_H

#define USB_EP0_BUFF_SIZE 8									
#define USB_MAX_NUM_INT 1

#define USB_USER_DEVICE_DESCRIPTOR &device_dsc
#define USB_USER_DEVICE_DESCRIPTOR_INCLUDE extern ROM USB_DEVICE_DESCRIPTOR device_dsc

#define USB_USER_CONFIG_DESCRIPTOR USB_CD_Ptr
#define USB_USER_CONFIG_DESCRIPTOR_INCLUDE extern ROM BYTE *ROM USB_CD_Ptr[]

#define USB_PING_PONG_MODE USB_PING_PONG__FULL_PING_PONG

#define USB_POLLING
//#define USB_INTERRUPT

#define USB_PULLUP_OPTION USB_PULLUP_ENABLE

#define USB_TRANSCEIVER_OPTION USB_INTERNAL_TRANSCEIVER

#define USB_SPEED_OPTION USB_FULL_SPEED

#define USB_NUM_STRING_DESCRIPTORS 3

#define USB_SUPPORT_DEVICE
#define USB_ENABLE_ALL_HANDLERS //needed for CDC service
#define USB_USE_CDC

#define USB_MAX_EP_NUMBER	    3

#define CDC_COMM_INTF_ID        0x0
#define CDC_COMM_EP              2
#define CDC_COMM_IN_EP_SIZE      8

#define CDC_DATA_INTF_ID        0x01
#define CDC_DATA_EP             3
#define CDC_DATA_OUT_EP_SIZE    64
#define CDC_DATA_IN_EP_SIZE     64

#define USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D1 



#endif //USBCFG_H
