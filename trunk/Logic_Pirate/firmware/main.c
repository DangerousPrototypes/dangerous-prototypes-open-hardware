// C:\Program Files (x86)\Microchip\mplabc32\v2.01\pic32mx\include\proc\p32mx220f032b.h
// C:\Program Files (x86)\Microchip\mplabc32\v2.01\pic32mx\lib\proc\32MX220F032B\configuration.data

// DEVCFG3:
#pragma config FVBUSONIO = OFF           // VBUS_ON pin is controlled by the port function
#pragma config FUSBIDIO  = OFF           // USBID pin is controlled by the port function
#pragma config IOL1WAY   = OFF           // Peripheral Pin Select Configuration
// DEVCFG2:
#pragma config FPLLODIV  = DIV_2         // PLL Output Divider
#pragma config UPLLEN    = ON            // USB PLL Enabled
#pragma config UPLLIDIV  = DIV_2         // USB PLL Input Divider
#pragma config FPLLMUL   = MUL_20        // PLL Multiplier
#pragma config FPLLIDIV  = DIV_2         // PLL Input Divider
// DEVCFG1:
#pragma config FWDTEN    = OFF           // Watchdog Timer
#pragma config WDTPS     = PS1           // Watchdog Timer Postscale
#pragma config FCKSM     = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config FPBDIV    = DIV_2         // Peripheral Clock divisor
#pragma config OSCIOFNC  = OFF           // CLKO Enable
#pragma config POSCMOD   = XT            // Primary Oscillator
#pragma config IESO      = OFF           // Internal/External Switch-over
#pragma config FSOSCEN   = OFF           // Secondary Oscillator Enable (KLO was off)
#pragma config FNOSC     = PRIPLL        // Oscillator Selection
// DEVCFG0:
#pragma config CP        = OFF           // Code Protect
#pragma config BWP       = ON            // Boot Flash Write Protect
#pragma config PWP       = OFF           // Program Flash Write Protect
#pragma config ICESEL    = ICS_PGx3      // ICE/ICD Comm Channel Select
#pragma config JTAGEN    = OFF           // JTAG Enable
#pragma config DEBUG     = OFF           // Background Debugger Enable

//#define OVERCLOCK

#if defined( OVERCLOCK )
#define SYSCLK 60000000L
#else
#define SYSCLK 40000000L
#endif
#define PBCLK ( SYSCLK / 2 )

#include <stdbool.h>
#include <stdint.h>

#include <USB/usb.h>
#include <USB/usb_device.h>
#include <USB/usb_function_cdc.h>

#include "usb_config.h"

static char USB_In_Buffer[ USB_IN_ENDPOINT_PACKET_SIZE ];
//static char USB_Out_Buffer[ 64 ];

static void user_init();
static void process_io();
static void set_led_fading();
static void set_led_blinking( uint16_t frequency, uint8_t duty_percentage );
#define set_led_on() set_led_blinking( 10000, 100 )
#define set_led_off() set_led_blinking( 10000, 0 )

int main()
{
    user_init();

    USBDeviceInit(); // usb_device.c.  Initializes USB module SFRs and firmware variables to known states.

    while( true ) {
#if defined( USB_INTERRUPT )
        if ( USBGetDeviceState() == DETACHED_STATE ) {
            USBDeviceAttach();
        }
#endif

#if defined( USB_POLLING )
        // Check bus status and service USB interrupts.
        USBDeviceTasks(); // Interrupt or polling method.  If using polling, must call
                          // this function periodically.  This function will take care
                          // of processing and responding to SETUP transactions
                          // (such as during the enumeration process when you first
                          // plug in).  USB hosts require that USB devices should accept
                          // and process SETUP packets in a timely fashion.  Therefore,
                          // when using polling, this function should be called
                          // regularly (such as once every 1.8ms or faster** [see
                          // inline code comments in usb_device.c for explanation when
                          // "or faster" applies])  In most cases, the USBDeviceTasks()
                          // function does not take very long to execute (ex: <100
                          // instruction cycles) before it returns.
#endif

        process_io();
    }
}

typedef struct {
	uint32_t divider;
	uint32_t read_count;
	uint32_t delay_count;
	uint8_t trigger_mask;
	bool use_trigger;
} config_t;

#define RAM_SCK LATBbits.LATB13
#define SET_RAM_CLOCK_MANUAL ( RPB13Rbits.RPB13R = 0 ) // (PPS) No Connect
#define SET_RAM_CLOCK_REFCLKO ( RPB13Rbits.RPB13R = 7 ) // (PPS) REFCLKO

#define BUF_OE LATBbits.LATB14
#define SET_BUF_ON ( BUF_OE = 0 )
#define SET_BUF_OFF ( BUF_OE = 1 )

#define RAM_CS LATBbits.LATB15
#define SET_RAM_ON ( RAM_CS = 0 )
#define SET_RAM_OFF \
    Nop();          \
    Nop();          \
    Nop();          \
    RAM_CS = 1
// 50 ns nCS hold time.

#define SET_PARALLEL_IN ( TRISB |= 0x01BF )
#define SET_PARALLEL_OUT ( TRISB &= ~0x01BF )
static inline uint8_t parallel_read()
{
    const uint32_t pins = PORTB & 0x01BF;
    return pins | ( ( pins & 0x0100 ) >> 2 );
}
static inline void parallel_write( uint8_t data )
{
    LATB = LATB & ~0x01BF | data | ( ( data & 0x0040 ) << 2 );
}

// Write bit_count bits from data to both RAM chips using SPI.
static void spi_write( uint32_t data, uint8_t bit_count )
{
    SET_RAM_CLOCK_MANUAL;
    SET_BUF_OFF;

    SET_PARALLEL_OUT;
    SET_RAM_ON;
    LATBbits.LATB3 = 1; // HOLD not active
    LATBbits.LATB7 = 1;
    uint32_t mask = 1L << ( bit_count - 1 );
    while ( mask != 0 ) {
        RAM_SCK = 0;
        if ( ( data & mask ) != 0 ) {
            LATBbits.LATB0 = 1;
            LATBbits.LATB4 = 1;
        } else {
            LATBbits.LATB0 = 0;
            LATBbits.LATB4 = 0;
        }
        mask >>= 1;
        RAM_SCK = 1;
    }
    RAM_SCK = 0;
    SET_RAM_OFF;
    LATBbits.LATB0 = 0;
    LATBbits.LATB4 = 0;
    SET_PARALLEL_IN;
}

// Write four bytes to both chips using SQI.
static void sqi_write( uint32_t data )
{
    uint32_t mask = 0xF0000000;
    uint32_t nibble_count = 8;
    while ( nibble_count-- > 0 ) {
        const uint8_t nibble = ( data & mask ) >> 28;
        RAM_SCK = 0;
        parallel_write( ( nibble << 4 ) | nibble );
        data <<= 4;
        RAM_SCK = 1;
    }
    RAM_SCK = 0;
    parallel_write( 0x00 );
}

static uint16_t get_rodiv( config_t * const config )
{
    uint16_t rodiv;
    switch( config->divider ) { // divider = ( 100 MHz / sample-rate ) - 1
#if defined( OVERCLOCK )
    case 0: rodiv = 0; break; // 60 MHz
    case 2: rodiv = 1; break; // 30 MHz
    case 5: rodiv = 2; break; // 15 MHz
    case 9: rodiv = 3; break; // 10 MHz
    case 19: rodiv = 6; break; // 5 MHz
    case 49: rodiv = 15; break; // 2 MHz
    case 99: rodiv = 30; break; // 1 MHz
    case 199: rodiv = 60; break; // 500 kHz
    case 499: rodiv = 150; break; // 200 kHz
    case 999: rodiv = 300; break; // 100 kHz
    case 1999: rodiv = 600; break; // 50 kHz
    case 4999: rodiv = 1500; break; // 20 kHz
    case 9999: rodiv = 3000; break; // 10 kHz
    case 19999: rodiv = 6000; break; // 5 kHz
    case 49999: rodiv = 15000; break; // 2 kHz
    default: rodiv = 3; break; // 10 MHz
#else
    case 1: rodiv = 0; break; // 40 MHz
    case 4: rodiv = 1; break; // 20 MHz
    case 9: rodiv = 2; break; // 10 MHz
    case 19: rodiv = 4; break; // 5 MHz
    case 49: rodiv = 10; break; // 2 MHz
    case 99: rodiv = 20; break; // 1 MHz
    case 199: rodiv = 40; break; // 500 kHz
    case 499: rodiv = 100; break; // 200 kHz
    case 999: rodiv = 200; break; // 100 kHz
    case 1999: rodiv = 400; break; // 50 kHz
    case 4999: rodiv = 1000; break; // 20 kHz
    case 9999: rodiv = 2000; break; // 10 kHz
    case 19999: rodiv = 4000; break; // 5 kHz
    case 49999: rodiv = 10000; break; // 2 kHz
    default: rodiv = 2; break; // 10 MHz
#endif
    }
    return rodiv;
}

static inline uint32_t timer_multiplier( uint32_t rodiv )
{
    return ( rodiv == 0 ) ? ( 1 ) : ( 2 * rodiv );
}

#define LATENCY_CORRECTION 31 // Empirically tuned: It takes LATENCY_CORRECTION timer ticks from the time the IRQ happens until the RAM clock gets switched off.
#define TRIGGER_LATENCY_CORRECTION 53
static volatile uint32_t trigger_timer_value = 0;
static volatile uint32_t delay_timer_period = 0;
static void setup_clock( config_t * const config )
{
    const uint16_t rodiv = get_rodiv( config );
    REFOCONbits.RODIV = rodiv;
    REFOCONbits.DIVSWEN = 1;
    while ( REFOCONbits.DIVSWEN == 1 );

    const uint32_t m = timer_multiplier( rodiv );
    trigger_timer_value = 0;
    delay_timer_period = ( 2 * m * config->delay_count // ( 0x20000 * m ) * ( config->delay_count / 0x10000 )
                           - ( config->use_trigger ? TRIGGER_LATENCY_CORRECTION : LATENCY_CORRECTION ) );
    OpenTimer45( T4_OFF | T4_PS_1_1 | T4_SOURCE_INT, config->use_trigger ? 0x20000 * m - 1 : delay_timer_period );
    //ConfigIntTimer45( T5_INT_ON | T5_INT_PRIOR_7 | T5_INT_SUB_PRIOR_0 );
    mT5SetIntPriority( 6 );
    mT5ClearIntFlag();
    mT5IntEnable( config->use_trigger ? 0 : 1 );
}

static void setup_trigger( config_t * const config )
{
    const uint32_t status = INTDisableInterrupts();
    CNCONBbits.ON = 1; // Enable the CN Module ON bit.
    const uint8_t mask = config->trigger_mask;
    CNENB = mask | ( ( mask & 0x40 ) << 2 ); // Enable individual CN input pins,
    PORTB; // Read register to clear mismatch condition on CN input pins.
    IPC8bits.CNIP = 6; // Configure the CN interrupt priority.
    IFS1bits.CNBIF = 0; // Clear the CN interrupt flag bit.
    IEC1bits.CNBIE = 1; // Enable the CN interrupt enable bit.
    INTRestoreInterrupts( status );
}

static bool is_ram_dirty = false;
static void start_sampling( config_t * const config )
{
    SET_RAM_CLOCK_MANUAL;
    SET_BUF_OFF;

    SET_PARALLEL_OUT;
    SET_RAM_ON;
    sqi_write( 0x02000000 ); // Write data to memory array beginning at address 0.
    SET_PARALLEL_IN;
    SET_BUF_ON;

    setup_clock( config );
    TMR4 = 0;
    if ( config->use_trigger ) {
        set_led_blinking( 15, 50 );
        setup_trigger( config );
    } else {
        set_led_on();
    }

    SET_RAM_CLOCK_REFCLKO;
    T4CONbits.ON = 1;

    is_ram_dirty = true;
}

static inline void stop_sampling()
{
    SET_RAM_CLOCK_MANUAL;

    T4CONbits.ON = 0;
    mT5IntEnable( 0 );

    IEC1bits.CNBIE = 0; // Disable the CN interrupt enable bit.
    IFS1bits.CNBIF = 0; // Clear the CN interrupt flag bit.

    SET_RAM_OFF;
    SET_BUF_OFF;
    SET_PARALLEL_IN;

    set_led_off();
}

static volatile bool do_send_to_host = false;
// Our ipl's must be below 7 (maybe the USB ipl?), otherwise transmitting of the data does not work.
void __ISR( _TIMER_5_VECTOR, ipl6 ) timer5_interrupt()
{
    stop_sampling();
    do_send_to_host = true;
    mT5ClearIntFlag();
}

void __ISR( _CHANGE_NOTICE_VECTOR, ipl6 ) change_notice_interrupt()
{
    trigger_timer_value = TMR4;
    TMR4 = 0;
    PR4 = delay_timer_period;
    mT5ClearIntFlag();
    mT5IntEnable( 1 );

    set_led_on();

    IEC1bits.CNBIE = 0; // Disable the CN interrupt enable bit.
    IFS1bits.CNBIF = 0; // Clear the CN interrupt flag bit.
}

#define ADDRESS_CORRECTION 18 // Another timing related correction.
// Buffer sizes less than 4 kB seem to not get sent.
// We are not investigating this further but just limit the selectable sizes to be 4 kB and larger.
static void send_to_host( config_t * const config )
{
    SET_RAM_CLOCK_MANUAL;
    SET_BUF_OFF;

    SET_PARALLEL_OUT;
    SET_RAM_ON;
    const uint32_t m = timer_multiplier( get_rodiv( config ) );
    const uint32_t address = ( ( trigger_timer_value ) / m
                               + 0x20000
                               - ( config->use_trigger ? ADDRESS_CORRECTION : 0 ) / m
                               - config->read_count * 2
                               + config->delay_count * 2 ) % 0x20000;
    sqi_write( 0x03000000 | address ); // Read data from memory array beginning at address.
    RAM_SCK = 1; // Dummy Byte
    RAM_SCK = 0;
    RAM_SCK = 1;
    RAM_SCK = 0;
    SET_PARALLEL_IN;

    uint32_t count = config->read_count << 2;
    uint32_t index = 0;
    while ( count > 0 ) {
        --count;
        RAM_SCK = 1;
        USB_In_Buffer[ index++ ] = parallel_read();
        RAM_SCK = 0;
        if ( index >= USB_IN_ENDPOINT_PACKET_SIZE ) {
            index = 0;
            putUSBUSART( USB_In_Buffer, USB_IN_ENDPOINT_PACKET_SIZE );
            while ( ! USBUSARTIsTxTrfReady() ) {
                CDCTxService();
#if defined( USB_POLLING )
                USBDeviceTasks();
#endif
            }
        }
    }

    SET_RAM_OFF;
}

#if defined( OVERCLOCK )
#define PWM_FREQUENCY 242 // sqrt( PBCLK / 256 / PWM_FREQUENCY / 2 )
#else
#define PWM_FREQUENCY 197
#endif
static volatile bool do_increment = true;
void __ISR( _TIMER_2_VECTOR, ipl1 ) timer2_interrupt()
{
    uint32_t oc3rs = OC3RS;
    const int32_t fade_step = oc3rs < PBCLK / 256 / PWM_FREQUENCY / 4 ? 1 : 2; // PBCLK / 256 / PWM_FREQUENCY / PWM_FREQUENCY ~ 2
    if ( do_increment ) {
        oc3rs += fade_step;
    } else {
        oc3rs -= fade_step;
    }

    if ( oc3rs >= PBCLK / 256 / PWM_FREQUENCY / 2 ) {
        do_increment = false;
    } else if ( oc3rs == 0 ) {
        do_increment = true;
    }
    OC3RS = oc3rs;

    mT2ClearIntFlag();
}

static void set_led_fading()
{
    OC3RS = 0;
    do_increment = true;
    T2CONbits.ON = 0;
    PR2 = PBCLK / 256 / PWM_FREQUENCY - 1; // Led PWM frequency is PWM_FREQUENCY Hz.
    TMR2 = 0;
    T2CONbits.ON = 1;
    mT2SetIntPriority( 1 );
    mT2ClearIntFlag();
    mT2IntEnable( 1 );
}

static void set_led_blinking( uint16_t frequency, uint8_t duty_percentage )
{
    if ( frequency < 2 ) {
        frequency = 2;
    }
    mT2IntEnable( 0 );
    OC3RS = PBCLK / 256 / frequency * duty_percentage / 100;
    T2CONbits.ON = 0;
    PR2 = PBCLK / 256 / frequency - 1;
    TMR2 = 0;
    T2CONbits.ON = 1;
}

static void set_test_pin( uint16_t period, uint16_t duty_cycle )
{
    mT3IntEnable( 0 );
    OC4RS = duty_cycle;
    T3CONbits.ON = 0;
    PR3 = period;
    TMR3 = 0;
    T3CONbits.ON = 1;
}

static void fill_ram()
{
    SET_RAM_CLOCK_MANUAL;
    SET_BUF_OFF;

    SET_PARALLEL_OUT;
    SET_RAM_ON;
    sqi_write( 0x02000000 ); // Write data to memory array beginning at address 0.
    uint32_t i;
    for ( i = 0; i < 32768; ++i ) {
        sqi_write( 0xF0F0F0F0 );
    }
    SET_RAM_OFF;
    SET_PARALLEL_IN;

    is_ram_dirty = false;
    set_led_fading();
}

static void user_init()
{
#if defined( OVERCLOCK )
    // If we directly switch to 60 MHz in one call, the MCU gets stuck sometimes.
    OSCConfig( OSC_POSC_PLL, OSC_PLL_MULT_15, OSC_PLL_POST_2, 0 ); // Run at 30 MHz.
    OSCConfig( OSC_POSC_PLL, OSC_PLL_MULT_15, OSC_PLL_POST_1, 0 ); // Run at 60 MHz.
#endif

    //SYSTEMConfigPerformance( SYSCLK ); // This also changes PBDIV.

    // Configure the device for maximum performance but do not change the PBDIV
    // Given the options, this function will change the flash wait states, RAM
    // wait state and enable prefetch cache but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above..
    SYSTEMConfig( SYSCLK, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE );

    INTEnableSystemMultiVectoredInt();

    ANSELA = 0x0000; // All digital pins.
    ANSELB = 0x0000;

    // LED pin:
    OpenOC3( OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0 );
    OpenTimer2( T2_ON | T2_PS_1_256 | T2_SOURCE_INT, PBCLK / 256 / 2 - 1 ); // 2 Hz
    OC3RS = 0; // 0 % duty cycle.
    RPB9Rbits.RPB9R = 5; // (PPS) OC3

    // TEST pin:
    OpenOC4( OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0 );
    OpenTimer3( T3_ON | T3_PS_1_1 | T3_SOURCE_INT, PBCLK / 1000 - 1 ); // 1 kHz TEST signal.
    OC4RS = PBCLK / 1000 * 3 / 4; // 75 % duty cycle.
    RPA4Rbits.RPA4R = 5; // (PPS) OC4

    // RAM_SCK pin
    RPB13Rbits.RPB13R = 7; // (PPS) REFCLKO
    REFOCONbits.RODIV = 1; // SYSCLK / ( 2 * 1 ) MHz
    //REFOCONbits.DIVSWEN = 1;
    REFOCONbits.OE = 1;
    REFOCONbits.ON = 1;
    //REFOTRIMbits.ROTRIM = 0;
    SET_RAM_CLOCK_MANUAL;

    // IO
    TRISBbits.TRISB13 = 0; // RAM_SCK
    RAM_SCK = 0;
    TRISBbits.TRISB14 = 0; // BUF_OE
    SET_BUF_OFF;
    TRISBbits.TRISB15 = 0; // RAM_CS
    SET_RAM_OFF;

    SET_PARALLEL_IN;

    spi_write( 0x0140, 16 ); // Write Mode Register: Sequential mode (default operation)
    spi_write( 0x38, 8 ); // Enter Quad I/O access

    fill_ram();
}

// http://www.sump.org/projects/analyzer/protocol/
// http://dangerousprototypes.com/docs/Logic_Analyzer_core:_Background#2.3_The_SUMP_Protocol
#define SC_RESET                       0x00
#define SC_RUN                         0x01
#define SC_ID                          0x02
#define SC_TEST                        0x03
#define SC_META                        0x04
#define SC_XON                         0x11
#define SC_XOFF                        0x13
#define LC_SET_DIVIDER                 0x80
#define LC_SET_READ_AND_DELAY_COUNT    0x81
#define LC_SET_FLAGS                   0x82
#define LC_SET_TRIGGER_MASK_0          0xC0 // 0xC4 0xC8 0xCC
#define LC_SET_TRIGGER_VALUES_0        0xC1 // 0xC5 0xC9 0xCD
#define LC_SET_TRIGGER_CONFIGURATION_0 0xC2 // 0xC6 0xCA 0xCE

// http://dangerousprototypes.com/docs/The_Logic_Sniffer%27s_extended_SUMP_protocol#Metadata_command
static const char meta_info[] = { "\x01" "Logic Pirate ("
#if defined( OVERCLOCK )
                                  "60"
#else
                                  "40"
#endif
                                  " MHz)" "\x00" "\x02" "2013-02-01" "\x00" "\x00" };
static config_t config = { 0 };
static bool do_fill_ram = false;
static uint32_t delayed_fill_counter = 0;
static void process_io()
{
    if ( ( USBDeviceState < CONFIGURED_STATE ) || ( USBSuspendControl == 1 ) ) {
        return;
    }

    uint8_t byte_count;
    uint8_t command;
    uint8_t lc[ 5 ];
    // The following mechanism to read data currently relies on the fact, that the OLS sends
    // one command at a time.  Calling getsUSBUSART() seems to consume all the bytes in the USB
    // buffer, even when specifying less bytes, e.g. 5, and additional bytes eventually available
    // are lost and not returned in the next call to getsUSBUSART().  So be carefull.
    // Example: sending 0x00 0x00 0x00 0x00 0x00 and then 0x02 works, but if it would be sent as
    // 0x00 0x00 0x00 0x00 0x00 0x02 in one transfer, 0x02 would get lost.
    byte_count = getsUSBUSART( lc, 5 );
    if ( byte_count > 0 ) {
        command = lc[ 0 ];
        switch ( command ) {
        case SC_RESET:
            if ( is_ram_dirty ) {
                stop_sampling();
                do_fill_ram = true;
                delayed_fill_counter = 0;
                // We call the time consuming (~100 ms) fill_ram() function asynchronously,
                // otherwise finnishing the OLS acquire process gets unneccessarily delayed.
            }
            break;
        case SC_RUN:
            start_sampling( &config );
            break;
        case SC_ID:
            putrsUSBUSART( "1ALS" );
            break;
        case SC_META:
            putUSBUSART( (char *)meta_info, sizeof( meta_info ) );
            break;
        case LC_SET_DIVIDER:
        case LC_SET_TRIGGER_MASK_0:
        case LC_SET_TRIGGER_VALUES_0:
        case LC_SET_TRIGGER_CONFIGURATION_0:
        case LC_SET_READ_AND_DELAY_COUNT:
        case LC_SET_FLAGS:
        case 't':
        case 'p':
            switch ( command ) {
            case LC_SET_DIVIDER:
                config.divider = ( lc[ 3 ] << 16 ) | ( lc[ 2 ] << 8 ) | lc[ 1 ];
                break;
            case LC_SET_TRIGGER_MASK_0:
                config.trigger_mask = lc[ 1 ];
                config.use_trigger = config.trigger_mask != 0;
                break;
            case LC_SET_READ_AND_DELAY_COUNT:
                config.read_count = ( lc[ 2 ] << 8 ) | lc[ 1 ];
                ++config.read_count; // Seems to be a quirk of the SUMP protocol.
                ++config.read_count;
                config.delay_count = ( lc[ 4 ] << 8 ) | lc[ 3 ];
                ++config.delay_count;
                if ( config.delay_count < LATENCY_CORRECTION + 1 ) { // Workaround to prevent the timer period from becoming 0 or negative.
                    config.delay_count = LATENCY_CORRECTION + 1;
                }
                break;
            case 't':
                set_test_pin( ( lc[ 2 ] << 8 ) | lc[ 1 ], ( lc[ 4 ] << 8 ) | lc[ 3 ] );
                break;
            case 'p':
                T3CONbits.TCKPS = lc[ 1 ];
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    } else {
        ++delayed_fill_counter;
        if ( do_fill_ram && delayed_fill_counter > 100000 ) {
            do_fill_ram = false;
            fill_ram();
        }
    }
    CDCTxService();

    if ( do_send_to_host ) {
        do_send_to_host = false;
        send_to_host( &config );
    }
}
