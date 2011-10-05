/*
 *
 *	USB infrared remote control receiver transmitter firmware v1.0
 *	License: creative commons - attribution, share-alike
 *	Copyright Ian Lesnet 2010
 *	http://dangerousprototypes.com
 *
 */
//
//Depending on the install location you may need to tweak the include paths under Project->build options.

//SET HARDWARE IN HardwareProfile.h!!!
//#define DOUBLE_BUFFER_OUTPUT //double-buffered CDC output to PC
#define SIMPLE_CDC //simple array in and out CDC demo
//#define USB_INTERRUPTS //use interrupts instead of polling

//USB stack
#include "globals.h"
#include "configwords.h"	// JTR only included in main.c
#include "descriptors.h"	// JTR Only included in main.c

#ifdef IRTOY
	#define REMAPPED_RESET_VECTOR_ADDRESS		0x800
	#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
	#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818
#endif

extern unsigned char usb_device_state; // JTR2 corrected type
extern unsigned char cdc_trf_state;
extern BYTE cdc_In_buffer[64];
extern BDentry *Inbdp;

extern BYTE *InPtr;
extern BYTE *OutPtr;

void user_configured_init(void);
void usb_start(void);
void initCDC(void);
void usb_init(ROMPTR const unsigned char*, ROMPTR const unsigned char*, ROMPTR const unsigned char*, int);
BYTE FAST_usb_handler(void);

#pragma udata
BYTE inByte; // JTR3 Global
void SetupBoard(void);
void InterruptHandlerHigh();
void InterruptHandlerLow();
void USBDeviceTasks(void);

#pragma code
#ifdef PIC_18F
void main(void)
#else
int main(void)
#endif
{
	unsigned int dly=0xffff;

	//while(dly--);

    initCDC(); // JTR this function has been highly modified It no longer sets up CDC endpoints.
    SetupBoard(); //setup the hardware, USB
//dly=0xffff;
//while(dly--);
    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS); // TODO: Remove magic with macro
//dly=0xffff;
//while(dly--);
    usb_start();
	#if defined (USB_INTERRUPTS)
   		//EnableUsbInterrupt(USB_TRN + USB_SOF + USB_UERR + USB_URST);
		EnableUsbInterrupt(USB_STALL + USB_IDLE + USB_TRN + USB_ACTIV + USB_SOF + USB_UERR + USB_URST);
   		EnableUsbInterrupts();
	#endif
    usbbufflush(); //flush USB input buffer system

        do {

            #ifndef USB_INTERRUPTS
				//service USB tasks 
				//Guaranteed one pass in polling mode 
				//even when usb_device_state == CONFIGURED_STATE
				if (!TestUsbInterruptEnabled()){
                	USBDeviceTasks(); 
				}
			#endif

            if ((usb_device_state < DEFAULT_STATE)) { // JTR2 no suspendControl available yet || (USBSuspendControl==1) ){

            } else if (usb_device_state < CONFIGURED_STATE) {

            }else if((usb_device_state == CONFIGURED_STATE)){



			}

        } while (usb_device_state < CONFIGURED_STATE);
		
//		LedOff();

		#if defined (DOUBLE_BUFFER_OUTPUT)
		    ArmCDCInDB(); // Set up CDC IN double buffer
		#endif

    //	Never ending loop services each task in small increments
    while (1) {
        #ifndef USB_INTERRUPTS
			//service USB tasks 
			//Guaranteed one pass in polling mode 
			//even when usb_device_state == CONFIGURED_STATE
			if (!TestUsbInterruptEnabled()){
               	USBDeviceTasks(); 
			}
		#endif

        usbbufservice(); //service USB buffer system
		
		if (usbbufgetbyte(&inByte) == 1) { //break; //get (and remove!) a single byte from the USB buffer
//			LedOn();

			#if defined(SIMPLE_CDC)
				WaitInReady();
				cdc_In_buffer[0] = inByte; //answer OK
				putUnsignedCharArrayUsbUsart(cdc_In_buffer, 1);
			#elif defined (DOUBLE_BUFFER_OUTPUT)
				*InPtr = inByte;
				InPtr++;
				SendCDC_In_ArmNext(1);
				FAST_usb_handler();
			#endif

//			LedOff();
		}//if byte

    }//end while
}//end main


void SetupBoard(void) {
#if defined (BUSPIRATEV4)
	volatile unsigned long delay=0xffff;
    CLKDIV = 0x0000; // Set PLL prescaler (1:1)
    //	BP_LEDUSB_DIR=0;	// output
    CORCONbits.PSV = 1; // JTR PIC24 fixup ?? PSV not being initialized. May have been done by c_init though.
    PSVPAG = 0; //
    OSCCONbits.SOSCEN = 0;
    AD1PCFGL = 0x7FD8; //BUSPIRATEV4 has five analog pins b0, b1, b2, b5, b15
    AD1PCFGH = 0x2;
	while(delay--);
#endif

#if defined (IRTOY)
    //disable some defaults
    ADCON1 |= 0b1111; //all pins digital
    CVRCON = 0b00000000;

    //INTCONbits.GIEL = 1; //enable peripheral interrupts
    //INTCONbits.GIEH = 1; //enable HIGH proirity interrupts
#endif

#if defined (IANS18FJ)
	unsigned int cnt = 2048;
	
	//all pins digital
    ANCON0 = 0xFF;                  
    ANCON1 = 0b00011111;// updated for lower power consumption. See datasheet page 343                  

	//make sure everything is input (should be on startup, but just in case)
	TRISA=0xff;
	TRISB=0xff;
	TRISC=0b11111111; 

	//on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
	OSCTUNEbits.PLLEN = 1;  //enable PLL
	while(cnt--); //wait for lock



#endif

    //visual indicator LED config
    //LedOn(); //start with LED ON till USB connect
    //LED_TRIS &= (~LED_PIN); //direction output
}


#if defined(USB_INTERRUPTS)
	#if defined(BUSPIRATEV4)
		#pragma interrupt _USB1Interrupt
		void __attribute__((interrupt, no_auto_psv)) _USB1Interrupt() {
		
		    //USB interrupt
		    //IRQ enable IEC5bits.USB1IE
		    //IRQ flag	IFS5bits.USB1IF
		    //IRQ priority IPC21<10:8>
		    //{
		    usb_handler();
		    IFS5bits.USB1IF = 0; //	PIR2bits.USBIF = 0;
		    //}
		}
	#endif

	#if defined(IRTOY)
		//	Interrupt remap chain
		//
		//This function directs the interrupt to
		// the proper function depending on the mode
		// set in the mode variable.
		#pragma interrupt InterruptHandlerHigh nosave= PROD, PCLATH, PCLATU, TBLPTR, TBLPTRU, TABLAT, section (".tmpdata"), section("MATH_DATA")
		
		void InterruptHandlerHigh(void) {
		}
		
		//We didn't use the low priority interrupts,
		// but you could add your own code here
		#pragma interruptlow InterruptHandlerLow
		
		void InterruptHandlerLow(void) {
		}
		
		//these statements remap the vector to our function
		//When the interrupt fires the PIC checks here for directions
		#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
		
		void Remapped_High_ISR(void) {
		    _asm goto InterruptHandlerHigh _endasm
		}
		
		#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
		
		void Remapped_Low_ISR(void) {
		    _asm goto InterruptHandlerLow _endasm
		}
		
		//relocate the reset vector
		extern void _startup(void);
		#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
		
		void _reset(void) {
		    _asm goto _startup _endasm
		}
		//set the initial vectors so this works without the bootloader too.
		#pragma code HIGH_INTERRUPT_VECTOR = 0x08
		
		void High_ISR(void) {
		    _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
		}
		#pragma code LOW_INTERRUPT_VECTOR = 0x18
		
		void Low_ISR(void) {
		    _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
		}
	#endif
#endif
#pragma code
//#endif

