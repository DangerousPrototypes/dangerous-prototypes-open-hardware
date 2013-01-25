// Copyright (c) 2002-2010,  Microchip Technology Inc.
//
// Microchip licenses this software to you solely for use with Microchip
// products.  The software is owned by Microchip and its licensors, and
// is protected under applicable copyright laws.  All rights reserved.
//
// SOFTWARE IS PROVIDED "AS IS."  MICROCHIP EXPRESSLY DISCLAIMS ANY
// WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  IN NO EVENT SHALL
// MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
// CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR
// EQUIPMENT, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY
// OR SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED
// TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
// OR OTHER SIMILAR COSTS.
//
// To the fullest extent allowed by law, Microchip and its licensors
// liability shall not exceed the amount of fees, if any, that you
// have paid directly to Microchip to use this software.
//
// MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE
// OF THESE TERMS.
#ifndef __HARDWAREPROFILE_PIC32MX_PIM_EXPLORER_16_H__
#define __HARDWAREPROFILE_PIC32MX_PIM_EXPLORER_16_H__


/*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #define self_power          1

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
    #define USB_BUS_SENSE       1

#if defined(__PIC32MX1XX_2XX__)
		/* The 44 pins of PIC32MX1xx/2xx PIM are not mapped to any of the LEDs/Switches
		of Explorer-16 board. User has to modify the LED and switch mapping as required.
		*/
        //#error "If you are compiling this project for PIC32MX1xx/2xx devices, please read the supplied document pic321xx_2xxx_support.htm and then proceed"

		#define mLED LATBbits.LATB9
	    // Blinks LED 5 on explorer 16 board
	    #define BlinkLED() (mLED = ((ReadCoreTimer() & 0x0800000) == 0))
	    #define InitLED() (TRISBbits.TRISB9 = 0)
	    // Switch ON all the LEDs to indicate Error.
	    #define Error() (mLED = 1)

	    // Switch S3 on Explorer 16.
	    #define ReadSwitchStatus() 1
#elif defined(__PIC32MX3XX_7XX__)
	#define mLED              LATAbits.LATA2
	// Blinks LED 5 on explorer 16 board
	#define BlinkLED() (mLED = ((ReadCoreTimer() & 0x0800000) == 0))
	#define InitLED() do{DDPCON = 0; TRISA = 0x00; LATA= 0;}while(0)
	// Switch ON all the LEDs to indicate Error.
	#define Error()   (LATA = 0xFF)

	// Switch S3 on Explorer 16.
	#define ReadSwitchStatus() (PORTReadBits(IOPORT_D, BIT_6) & BIT_6)
#endif


	#ifdef TRANSPORT_LAYER_SD_CARD
		// Define following only for SD card bootloader.
		#define USE_SD_INTERFACE_WITH_SPI
	#endif

#endif
