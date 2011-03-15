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

// JTR V0.1a

#include <string.h>
// JTR added
#include "cdc_config.h" // Standard header for this implementation of the USB stack (CDC-ACM)
#include "usb_stack.h"
// JTR moved this to main.c N/A here
// #include "descriptors.h"

// CDC Request Codes
#define CDC_SEND_ENCAPSULATED_COMMAND               0x00
#define CDC_GET_ENCAPSULATED_RESPONSE               0x01
#define CDC_SET_COMM_FEATURE                        0x02
#define CDC_GET_COMM_FEATURE                        0x03
#define CDC_CLEAR_COMM_FEATURE                      0x04
//              RESERVED (future use)               0x05-0x0F
#define CDC_SET_AUX_LINE_STATE                      0x10
#define CDC_SET_HOOK_STATE                          0x11
#define CDC_PULSE_SETUP                             0x12
#define CDC_SEND_PULSE                              0x13
#define CDC_SET_PULSE_TIME                          0x14
#define CDC_RING_AUX_JACK                           0x15
//              RESERVED (future use)               0x16-0x1F
#define CDC_SET_LINE_CODING                         0x20
#define CDC_GET_LINE_CODING                         0x21
#define CDC_SET_CONTROL_LINE_STATE                  0x22
#define CDC_SEND_BREAK                              0x23
//              RESERVED (future use)               0x24-0x2F
#define CDC_SET_RINGER_PARMS                        0x30
#define CDC_GET_RINGER_PARMS                        0x31
#define CDC_SET_OPERATION_PARMS                     0x32
#define CDC_GET_OPERATION_PARMS                     0x33
#define CDC_SET_LINE_PARMS                          0x34
#define CDC_GET_LINE_PARMS                          0x35
#define CDC_DIAL_DIGITS                             0x36
#define CDC_SET_UNIT_PARAMETER                      0x37
#define CDC_GET_UNIT_PARAMETER                      0x38
#define CDC_CLEAR_UNIT_PARAMETER                    0x39
#define CDC_GET_PROFILE                             0x3A
//              RESERVED (future use)               0x3B-0x3F
#define CDC_SET_ETHERNET_MULTICAST_FILTERS          0x40
#define CDC_SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER        0x41
#define CDC_GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER        0x42
#define CDC_SET_ETHERNET_PACKET_FILTER                          0x43
#define CDC_GET_ETHERNET_STATISTIC                              0x44
//              RESERVED (future use)                           0x45-0x4F
#define CDC_SET_ATM_DATA_FORMAT                                 0x50
#define CDC_GET_ATM_DEVICE_STATISTICS                           0x51
#define CDC_SET_ATM_DEFAULT_VC                                  0x52
#define CDC_GET_ATM_VC_STATISTICS                               0x53
//              RESERVED (future use)                           0x54-0x5F
//              MDLM Semantic-Model specific Requests           0x60�0x7F
//              RESERVED (future use)                           0x80-0xFF

// CDC Notification Codes
#define CDC_NETWORK_CONNECTION                    0x00
#define CDC_RESPONSE_AVAILABLE                    0x01
//              RESERVED (future use)             0x02-0x07
#define CDC_AUX_JACK_HOOK_STATE                   0x08
#define CDC_RING_DETECT                           0x09
//              RESERVED (future use)             0x0A-0x1F
#define CDC_SERIAL_STATE                          0x20
//              RESERVED (future use)             0x21-0x27
#define CDC_CALL_STATE_CHANGE                     0x28
#define CDC_LINE_STATE_CHANGE                     0x29
#define CDC_CONNECTION_SPEED_CHANGE               0x2A
//              RESERVED                          0x2B-0x3F
//              MDML SEMANTIC-MODEL-SPECIFIC NOTIFICATION       0x40-0x5F
//              RESERVED (future use)             0x60-0xFF

void cdc_setup( void );
void cdc_set_line_coding_data( void );
void cdc_set_line_coding_status( void );
void cdc_get_line_coding( void );
void cdc_set_control_line_state_status( void );
//void cdc _acm _out( void );   // JTR not part of the CDC-ACM class. Trash this prototype
//void cdc_acm_in( void );      // JTR useless in current form
//void cdc_rx( void );          // JTR removed some stuff that others can fight over.
//void cdc_tx( void );
//void cdc_flush_tx( void );
void CheckCDC_In( void );   // JTR part of temp CDC testing suite
void user_configured_init( void );  // JTR added. Sets up CDC endpoints after device configured.
void usb_ack_dat1( BDentry *rbdp, int bdcnt ); 	// JTR added standard for both STD and CLASS

enum stopbits {one=0, oneandahalf=1, two=2};
enum parity {none=0, odd=1, even=2, mark=3, space=4};
const char parity_str[] = {'N','O','E','M','S'};

struct cdc_LineCodeing {
	unsigned long int	dwDTERate;
	enum stopbits		bCharFormat;
	enum parity		bParityType;
	unsigned char		bDataBits;
} linecodeing;

struct cdc_ControlLineState {
	int	DTR:1;
	int	RTS:1;
	int unused1:6;
	char unused2;
} cls;

unsigned char *data, *data_end;
BDentry *rxbdp, *txbdp;
volatile unsigned char CDC_trf_state;	// JTR don't see that it is really volatile in current context may be in future.

#pragma udata usb_data
//unsigned char cdc _acm _out _buffer[CDC_BUFFER_SIZE];	//JTR removed and trashed. not required with CDC - ACM.
unsigned char cdc_rx_buffer[CDC_BUFFER_SIZE];
unsigned char cdc_tx_buffer[CDC_BUFFER_SIZE];
unsigned char cdc_acm_in_buffer[CDC_NOTICE_BUFFER_SIZE];    //JTR NEWLY defined NOTICE BUFFER SIZE and increased from 8 to 10 bytes in usb_config.h

#pragma udata

unsigned int SOFCOUNT;

void initCDC(void) {

// JTR The function usb_init() is now called from main.c prior to anything else belonging to the CDC CLASS
// If we have multiple functions we want the USB initialization to be in only one consistant place.

    //	usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS);	// TODO: Remove magic with macro

// The sort of things we would do in InitCDC would be to setup I/O pins and the HARDWARE UART so it
// is not transmitting junk between a RESET and the device being enumerated. Hardware CTS/RTS
// would also be setup here if being used.

	linecodeing.dwDTERate = 115200;
	linecodeing.bCharFormat = one;
	linecodeing.bParityType = none;
	linecodeing.bDataBits = 8;
	cls.DTR = 0;
	cls.RTS = 0;
	usb_register_class_setup_handler(cdc_setup);
	data = data_end = 0;


// JTR These things below should be done after the device is enumerated and configured.
// They have been moved to user_configured_init()
// There are further changes and comments to this code in user_configured_init()

//  usb_register_endpoint(1, USB_EP_IN, CDC_NOTICE_BUFFER_SIZE, NULL, cdc_acm_in_buffer, NULL, cdc_acm_in);
//	usb_register_endpoint(2, USB_EP_INOUT, CDC_BUFFER_SIZE, cdc_rx_buffer, cdc_tx_buffer, cdc_rx, cdc_tx);
// NO! 	usb_register_sof_handler(cdc_flush_tx);

// JTR change we are separating the basic stack from the user function so we don't do this here
//      usb_start();
}

void user_configured_init(void)
{
// JTR NEW FUNCTION
// After the device is enumerated and configured then we set up non EP0 endpoints.
// We only enable the endpoints we are using, not all of them.
// Prior to this they are held in a disarmed state.

// This function belongs to the current USB function and IS NOT generic. This is CLASS specific
// and will vary from implementation to implementation.


// JTR many commented out lines came from initCDC()

//int i;
//	#if defined(__18F14K50)
//				for (i=1; i<MAX_CHIP_EP; i++) {   // JTR change index from 0 to 1 as EP0 already armed
//	#else
//				for (i=1; i<16; i++) {
//	#endif
//					/* Configure buffer descriptors */
//	#if USB_PP_BUF_MODE == 0
//					usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDCNT  = endpoints[i].buffer_size;
//					usb_bdt[USB_CALC_BD(i, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN + DTSEN;
//					usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDCNT  = 0;
//					usb_bdt[USB_CALC_BD(i, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = DTS + DTSEN;	// Set DTS => First packet inverts, ie. is Data0
//	#else
//					// TODO: Implement Ping-Pong buffering setup.
//					#error "PP Mode not implemented yet"
//#endif
//}


// JTR change. Handle only IN requirements for the NOTICE INTERRUPT EP. There is no OUT NOTICE INTERRUPT EP
// JTR discontinued using this.
//  usb_register_endpoint(1, USB_EP_IN, CDC_NOTICE_BUFFER_SIZE, NULL, cdc_acm_in_buffer, NULL, cdc_acm_in);

// JTR DEBUG temp disable handlers and replace with NULLs. This is for testing purposes only.
// as we do not want handlers for the CDC at this time.
//  usb_register_endpoint(2, USB_EP_INOUT, CDC_BUFFER_SIZE, cdc_rx_buffer, cdc_tx_buffer, cdc_rx, cdc_tx);

    // JTR discontinued using this
//  usb_register_endpoint(2, USB_EP_INOUT, CDC_BUFFER_SIZE, cdc_rx_buffer, cdc_tx_buffer, NULL, NULL);

    usb_unset_in_handler(1);
    usb_unset_in_handler(2);
    usb_unset_out_handler(2);   // JTR Macro has bug fix

// JTR remove all USB_UEP[x] indexing from stack due to pointer bug (fixed?).
// JTR experiment is the UEPx pointer system working? Lets try!
// PASSED on PIC24

    //USB_UEP[1] = USB_EP_IN;
    //USB_UEP[2] = USB_EP_INOUT;

    USB_UEP1 = USB_EP_IN;
    USB_UEP2 = USB_EP_INOUT;

        /* Configure buffer descriptors */
    #if USB_PP_BUF_MODE == 0
// JTR Setup CDC LINE_NOTICE EP (Interrupt IN)
        usb_bdt[USB_CALC_BD(1, USB_DIR_IN, USB_PP_EVEN)].BDCNT  = 0;
	usb_bdt[USB_CALC_BD(1, USB_DIR_IN, USB_PP_EVEN)].BDADDR  = cdc_acm_in_buffer;
	usb_bdt[USB_CALC_BD(1, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = DTS + DTSEN;	// Set DTS => First packet inverts, ie. is Data0

	usb_bdt[USB_CALC_BD(2, USB_DIR_OUT, USB_PP_EVEN)].BDCNT  = CDC_BUFFER_SIZE; // JTR N/A endpoints[i].buffer_size;
	usb_bdt[USB_CALC_BD(2, USB_DIR_OUT, USB_PP_EVEN)].BDADDR  = cdc_rx_buffer;
	usb_bdt[USB_CALC_BD(2, USB_DIR_OUT, USB_PP_EVEN)].BDSTAT = UOWN + DTSEN;

        usb_bdt[USB_CALC_BD(2, USB_DIR_IN, USB_PP_EVEN)].BDCNT  = 0;
	usb_bdt[USB_CALC_BD(2, USB_DIR_IN, USB_PP_EVEN)].BDADDR  = cdc_tx_buffer;
	usb_bdt[USB_CALC_BD(2, USB_DIR_IN, USB_PP_EVEN)].BDSTAT = DTS + DTSEN;	// Set DTS => First packet inverts, ie. is Data0

	#else
	// TODO: Implement Ping-Pong buffering setup.
	#error "PP Mode not implemented yet"
#endif

// JTR  This is what causes the first transfer to be duplicated!
//      usb_register_sof_handler(cdc_flush_tx);

	usb_register_class_setup_handler(cdc_setup);
	CDC_trf_state = 0;
	rxbdp = &usb_bdt[USB_CALC_BD(2, USB_DIR_OUT, USB_PP_EVEN)];
	txbdp = &usb_bdt[USB_CALC_BD(2, USB_DIR_IN, USB_PP_EVEN)];
}

void cdc_setup(void){
	unsigned char *packet;
	size_t reply_len;
	packet = bdp->BDADDR;
	switch (packet[USB_bmRequestType] & (USB_bmRequestType_TypeMask | USB_bmRequestType_RecipientMask)) {
	case (USB_bmRequestType_Class | USB_bmRequestType_Interface):
		switch (packet[USB_bRequest]) {

//JTR This is just a dummy, nothing defined to do for CDC ACM
                    case CDC_SEND_ENCAPSULATED_COMMAND:		//
			//usb_ack_zero(rbdp);
                        usb_ack_dat1( rbdp, 0 );
			break;

//JTR This is just a dummy, nothing defined to do for CDC ACM
		case CDC_GET_ENCAPSULATED_RESPONSE:		//
			//usb_ack_zero(rbdp);
                        usb_ack_dat1( rbdp, 0 );
			break;

		case CDC_SET_COMM_FEATURE:			// Optional
		case CDC_GET_COMM_FEATURE:			// Optional
		case CDC_CLEAR_COMM_FEATURE:			// Optional
			usb_RequestError();		// Not advertised in ACM functional descriptor
			break;

		case CDC_SET_LINE_CODING:				// Optional, strongly recomended
			usb_set_out_handler(0, cdc_set_line_coding_data);	// Register out handler function
			break;

		case CDC_GET_LINE_CODING:				// Optional, strongly recomended
// JTR reply length (7) is always going to be less than minimum EP0 size (8)

			reply_len = *((unsigned int *) &packet[USB_wLength]);
			if (sizeof(struct cdc_LineCodeing) < reply_len) {
				reply_len = sizeof(struct cdc_LineCodeing);
			}
			memcpy(rbdp->BDADDR, (const void *) &linecodeing, reply_len);
			usb_ack_dat1( rbdp, reply_len );	// JTR common addition for STD and CLASS ACK

			//rbdp->BDCNT = reply_len;  // JTR done above
 			//usb_ack(rbdp);	// JTR depreciated

                        usb_set_in_handler(0, cdc_get_line_coding); // JTR why bother? There is nothing more to do.

			break;

		case CDC_SET_CONTROL_LINE_STATE:		// Optional
			cls = *((struct cdc_ControlLineState *) &packet[USB_wValue]);
			usb_set_in_handler(0, cdc_set_control_line_state_status); // JTR why bother?
      		//usb_ack_zero(rbdp);  		// JTR Status stage is always a DAT1 ZLP
			usb_ack_dat1( rbdp, 0 );	// JTR common addition for STD and CLASS ACK


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
}

void cdc_set_line_coding_data( void ) {		// JTR handling an OUT token In the CDC stack this is the only function that handles an OUT data stage.
	memcpy(&linecodeing, (const void *) bdp->BDADDR, sizeof(struct cdc_LineCodeing));
	usb_unset_out_handler(0);               // Unregister OUT handler; JTR serious bug fix in macro!
	usb_set_in_handler(0, cdc_set_line_coding_status); // JTR why bother?
	//	usb_ack_zero(rbdp);  //JTR Status stage is always a DAT1 ZLP
	usb_ack_dat1( rbdp, 0 );	// JTR common addition for STD and CLASS ACK

// JTR This part of the USB-CDC stack is worth highlighting
// This is the only place that we have an OUT DATA packet on
// EP0. At this point it has been completed. This stack unlike
// the microchip stack does not have a common IN or OUT data
// packet complete tail and therefore it is the responsibility
// of each section to ensure that EP0 is set-up correctly for
// the next setup packet.

//  This next line inverts the DTS so that it is now ready for
//  a DAT0 packet. However it only works because we had one data
//  packet. For any amount of EVEN data packets it would not be
//  correct.
//	usb_ack_out(bdp);  // JTR N/A Good for only odd number of data packets.

//  The correct thing to do is to force EP0 OUT to the DAT0 state
//  after we have all our data packets.
	bdp->BDCNT = USB_EP0_BUFFER_SIZE;
	bdp->BDSTAT = UOWN | DTSEN;
}

void cdc_set_line_coding_status( void ) {
	usb_unset_in_handler(0);
}

void cdc_set_control_line_state_status( void ) {
	usb_unset_in_handler(0);
}

// JTR N/A. There is no LINE_NOTIFICATION_OUT in CDC-ACM
//void cdc _acm _out( void ) {
//}

// JTR keep this fragment as it may be useful later if reworked a little
//void cdc_acm_in( void ) {

// JTR LINE_NOTIFICATION EP has been increased to ten bytes.
// This is because if it were ever to be used it is more likely
// that it will be for the Serial State Notification which has
// two bytes of data to include in the packet.

// Also we will not actually come to this code if the LINE_NOTIFICATION
// endpoint is not already armed and we do not arm this end point
// until we have something to send. Therefore we have a chicken and egg
// deadlock and this function is of no value the way it is currently coded.
// There is no IN token if the endpoint is not armed!
// No IN handler is required nor a state machine as there is no need for a ZLP

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
		// JTR past below bdp->BDCNT = 8;
		usb_ack_dat1(bdp, 8);
	} else if (0) {	// Network Connection Notification
	} else if (0) {	// Serial State Notification
	}
} */
/* END OF CDC CLASS REQUESTS HANDLING

 Below are the CDC USBUART functions */

void sof_counter_handler(){
    if (SOFCOUNT == 0) return;
    SOFCOUNT--;
}
unsigned char USBUSARTIsTxTrfReady( void){
   return (txbdp->BDSTAT & UOWN); // returns 0 if TX buffer is ready
}
// JTR added debug code. For testing purposes only.
// Note this is a striped down version that I used
// while trying to debug something else.
// Just too tired to

void CDCService(void) 	{

    if(CDC_trf_state == 2)	// JTR if SM = 2 then send ZLP
	{
		if(!(txbdp->BDSTAT & UOWN)) // When ready
		{
			txbdp->BDCNT = 0;
			txbdp->BDSTAT = ((txbdp->BDSTAT ^ DTS) & DTS) | (UOWN + DTSEN);
			CDC_trf_state = 1;
		}
	}

	if(CDC_trf_state == 0) {
            CheckCDC_In();
			 return;
	}

	if (CDC_trf_state == 1){  // We have sent something
            if(!(txbdp->BDSTAT & UOWN))  // If IN EP not busy (data sent) Arm OUT EP
                {
				rxbdp->BDCNT = CDC_BUFFER_SIZE;
				rxbdp->BDSTAT = ((rxbdp->BDSTAT ^ DTS) & DTS) | (UOWN + DTSEN);
				CDC_trf_state = 0;  // Reset state machine
                }
  				return;
  	}
}
void CheckCDC_In(void)
{
	if(0 ==(rxbdp->BDSTAT & UOWN))  // Do we have a packet from host?
   	{

		if(rxbdp->BDCNT != 0)
		{   // Not a ZLP
                    txbdp->BDCNT = rxbdp->BDCNT;
                    memcpy(txbdp->BDADDR, rxbdp->BDADDR, rxbdp->BDCNT);
                    CDC_trf_state = 1;
                    if(CDC_BUFFER_SIZE == txbdp->BDCNT)
                    CDC_trf_state = 2;   // = 2 meaning ZLP required after packet sent;
                    txbdp->BDSTAT = ((txbdp->BDSTAT ^ DTS) & DTS) | (UOWN + DTSEN);
#if defined(BPv4)
			MODELED = !MODELED;	// Toggle MODE led to show transfers
#endif
		} // snipped ZLP OUT handler while debugging.
	}
}


