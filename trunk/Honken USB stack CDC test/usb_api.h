
#define USB_STATE_DETACHED 0
#define USB_STATE_ATTACHED 0x01
#define USB_STATE_POWERED 0x02
#define USB_STATE_DEFAULT 0x04
#define USB_STATE_ADDRESS 0x08
#define USB_STATE_CONFIGURED 0x10
#define USB_STATE_SUSPENDED 0x20

void usb_arm_endpoint(unsigned char endpoint,unsigned char direction,
			const unsigned char* buffer,unsigned int size,unsigned char flags)
{
	usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDCNT  = endpoints[i].buffer_size;
	usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDADDR = endpoints[i].out_buffer;
	usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN + DTSEN;
	usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDCNT  = 0;
	usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDADDR = endpoints[i].in_buffer;
	usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = DTS;	
	
	
	
};
			
void usb_disarm_endpoint(unsigned char endpoint,unsigned char direction)
{
	
	
	
};