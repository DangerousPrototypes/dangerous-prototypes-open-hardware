/*****************************************************************************
 *  General purpous digital input/output pin functions
 *****************************************************************************
 * FileName:        gpio.h
 * Processor:       dsPIC33
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Eric Walker			20101120	Initial File Creation
 *****************************************************************************/
#ifndef _gpio_h
#define _gpio_h

/* Onboard LEDs */
#define LD1_TRIS			TRISAbits.TRISA8
#define LD1_IO				LATAbits.LATA8
#define LD2_TRIS			TRISAbits.TRISA9
#define LD2_IO				LATAbits.LATA9

/* SD card LED */
#define SD_TRIS				TRISAbits.TRISA10
#define SD_IO				LATAbits.LATA10

/* Chip Select line for SD card socket */
#define SD_CS				LATBbits.LATB13
#define SD_CS_TRIS			TRISBbits.TRISB13

/* SPI peripheral registers used for the SD card */
#define SD_SPICON1				SPI2CON1
#define SD_SPICON2				SPI2CON2
#define SD_SPISTAT				SPI2STAT
#define SD_SPIBUF				SPI2BUF
#define SD_SPISTAT_RBF			SPI2STATbits.SPIRBF
#define SD_SPIENABLE           	SPI2STATbits.SPIEN
//#define SD_SPICON1bits			SPI2CON1bits
//#define SD_SPISTATbits			SPI2STATbits

/* Chip Select line for onboard 25LC1024 EEPROM */
#define EEPROM_CS_TRIS		TRISCbits.TRISC7
#define EEPROM_CS_IO		LATCbits.LATC7



void SetupGPIO(void);

#endif /* _gpio_h */

/*EOF*/
