#ifndef USB_HARDWARE_PROFILE_H
#define USB_HARDWARE_PROFILE_H


//#define CLOCK_FREQ 48000000
//#define BAUDCLOCK_FREQ 12000000 // (48000000 /4) required for baud rate calculations
//#define UART_BAUD_setup(x)  SPBRG = x & 0xFFu; SPBRGH = (x >> 8) & 0xFFu
//#define CDC_FLUSH_MS 4 // how many ms timeout before cdc in to host is sent

#define USB_VID (0x4d8)
#define USB_PID (0x000a)  // Microchip CDC  
#define USB_DEV 0x0002

#define USB_NUM_CONFIGURATIONS          1u
#define USB_NUM_INTERFACES              2u
#define USB_NUM_ENDPOINTS               3u


#define MAX_EPNUM_USED                  2u

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
#define CDC_NOTICE_BUFFER_SIZE 10u

/* Low Power Request
 * Optional user supplied subroutine to set the circuit
 * into low power mode during usb suspend.
 * Probably needed when bus powered as only 2.5mA should
 * be drawn from bus i suspend mode */
//#define usb_low_power_request() Nop()

#if defined (__PIC24FJ256GB106__)
#define BUSPIRATEV4
#endif
#if defined (__18F2550)
#define IRTOY
#endif
//#define EA14k //Embedded adventures PIC18F14K50 module
//#define JTR_PIC24GB002        // JTR's PIC24..GB002 mockup
//#define IANS18FJ      //Ian's PIC18F24J50 test bed
//#define LPC14K  // Microchip low pin count demo board
//JTR_18FXXJ53 // JTR PIC18F27J53

#ifdef IRTOY

#define CDC_BUFFER_SIZE 64u

#define CLOCK_FREQ 48000000
#define BAUDCLOCK_FREQ 12000000 // (48000000 /4) required for baud rate calculations
#define UART_BAUD_setup(x)  SPBRG = x & 0xFFu; SPBRGH = (x >> 8) & 0xFFu
#define CDC_FLUSH_MS 4 // how many ms timeout before cdc in to host is sent

        // LED A0 (2)
        #define LED_LAT  LATA
        #define LED_TRIS TRISA
        #define LED_PIN  0b1

        #define LedOff()  LED_LAT &=(~LED_PIN)  //JTR TODO uncomment
        #define LedOn() LED_LAT|=LED_PIN //JTR TODO uncomment
        #define LedToggle() LED_LAT ^=LED_PIN
        //#define USB_INTERRUPTS //use interrupts instead of polling
        

#endif

#ifdef BUSPIRATEV4

#define CDC_BUFFER_SIZE 64u

#define CLOCK_FREQ 32000000
#define BAUDCLOCK_FREQ 16000000 //  required for baud rate calculations
#define UART_BAUD_setup(x)  U1BRG = x 
#define CDC_FLUSH_MS 4 // how many ms timeout before cdc in to host is sent

        //RB10
        #define LED_LAT  LATB
        #define LED_TRIS TRISB
        #define LED_PIN  0b10000000000

        #define LedOn()  LED_TRIS &=(~LED_PIN)  //JTR TODO uncomment
        #define LedOff() LED_TRIS|=LED_PIN //JTR TODO uncomment
        #define LedToggle() LED_LAT ^=LED_PIN

#define uLedOn() LATBbits.LATB10 = 0
#define uLedOff() LATBbits.LATB10 = 1
#define uLedToggle() LATBbits.LATB10 ^= LATBbits.LATB10

#define mLedOn() LATBbits.LATB8 = 1
#define mLedOff() LATBbits.LATB8 = 0
#define mLedToggle() LATBbits.LATB8 ^= LATBbits.LATB8

#define vLedOn() LATBbits.LATB9 = 1
#define vLedOff() LATBbits.LATB9 = 0
#define vLedToggle() LATBbits.LATB9 ^= LATBbits.LATB9

        //#define USB_INTERRUPTS //use interrupts instead of polling

#endif

#if defined (__18F14K50)

#define CDC_BUFFER_SIZE 32u

#define CLOCK_FREQ 48000000
#define BAUDCLOCK_FREQ 12000000 // (48000000 /4) required for baud rate calculations
#define UART_BAUD_setup(x)  SPBRG = x & 0xFFu; SPBRGH = (x >> 8) & 0xFFu
#define CDC_FLUSH_MS 4 // how many ms timeout before cdc in to host is sent

//        #define LED_LAT  LATA
//        #define LED_TRIS TRISA
//        #define LED_PIN  0b1

//        #define LedOff()  LED_LAT &=(~LED_PIN)   
//        #define LedOn() LED_LAT|=LED_PIN 
//        #define LedToggle() LED_LAT ^=LED_PIN
        
#define USB_INTERRUPTS //use interrupts instead of polling
        

#endif

#endif
