/*

 USB CDC echo demo on pic18f24j50

 (C)hris2011 for dangerousprototypes.com

 */

// includes
#include<HardwareProfile.h>
#include<p18cxxx.h>
#include<GenericTypeDefs.h>
#include<usb_config.h>
#include<usb_stack.h>
#include<cdc.h>
#include<cdc_descriptors.h>
#include<delays.h>

// configwords
     #pragma config WDTEN = OFF

     #pragma config PLLDIV = 4           //Divide by 5 (20 MHz oscillator input)
     #pragma config STVREN = ON
     #pragma config XINST = OFF
     #pragma config CPUDIV = OSC1
     #pragma config CP0 = OFF
     #pragma config OSC = HSPLL
     #pragma config T1DIG = ON
     #pragma config LPT1OSC = OFF
     #pragma config FCMEN = OFF
     #pragma config IESO = OFF
     #pragma config WDTPS = 32768
     #pragma config DSWDTOSC = INTOSCREF
     #pragma config RTCOSC = T1OSCREF
     #pragma config DSBOREN = OFF
     #pragma config DSWDTEN = OFF
     #pragma config DSWDTPS = 8192
     #pragma config IOL1WAY = OFF
     #pragma config MSSP7B_EN = MSK7
     #pragma config WPFP = PAGE_1
     #pragma config WPEND = PAGE_0
     #pragma config WPCFG = OFF
     #pragma config WPDIS = OFF

// defines

// forward declarations
void init(void);
void delayms(unsigned int i);

// globals

void main(void)
{
    unsigned char c,x,y;

    init();

    initCDC();
    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS); // TODO: Remove magic with macro
    usb_start();
#if defined (USB_INTERRUPTS)
    //EnableUsbInterrupt(USB_TRN + USB_SOF + USB_UERR + USB_URST);
    EnableUsbInterrupt(USB_STALL + USB_IDLE + USB_TRN + USB_ACTIV + USB_SOF + USB_UERR + USB_URST);
    EnableUsbInterrupts();
#endif
    usbbufflush(); //flush USB input buffer system

    do
    {
#ifndef USB_INTERRUPTS
        //service USB tasks
        //Guaranteed one pass in polling mode
        //even when usb_device_state == CONFIGURED_STATE
        if (!TestUsbInterruptEnabled())
        {
            USBDeviceTasks();
        }
#endif

        if ((usb_device_state < DEFAULT_STATE))
        { // JTR2 no suspendControl available yet || (USBSuspendControl==1) ){

        } else if (usb_device_state < CONFIGURED_STATE)
        {

        }else if((usb_device_state == CONFIGURED_STATE))
        {

        }
    } while (usb_device_state < CONFIGURED_STATE);



    while(1)
    {
#ifndef USB_INTERRUPTS
        //service USB tasks
        //Guaranteed one pass in polling mode
        //even when usb_device_state == CONFIGURED_STATE
        if (!TestUsbInterruptEnabled())
            USBDeviceTasks();
#endif
        usbbufservice(); //service USB buffer system

        if (usbbufgetbyte(&c) == 1)
        {
            WaitInReady();
            cdc_In_buffer[0] = c; //answer OK
            putUnsignedCharArrayUsbUsart(cdc_In_buffer, 1);
        }

    }
}

void init(void)
{
    // no analogue
    ANCON0=0xFF;
    ANCON1=0x0F;

    // everything is input for now
    TRISA=0xFF;
    TRISB=0xFF;
    TRISC=0xFF;

    // wait for PLL lock
    //on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
    OSCTUNEbits.PLLEN = 1;  //enable PLL
    delayms(5);


}

void delayms(unsigned int i)
{
    while(i)
    {
        Delay100TCYx (120);
        i--;
    }
}

