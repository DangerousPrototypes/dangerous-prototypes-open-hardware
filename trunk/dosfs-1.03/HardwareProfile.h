#include <p33Fxxxx.h>

//these are shortcut names for the LED and IO pins
#define SD_TRIS			(TRISAbits.TRISA10)
#define SD_I			(PORTAbits.RA10)
#define SD_O			(LATAbits.LATA10)
#define LD1_TRIS		(TRISAbits.TRISA8)		// LD1
#define LD1_I			(PORTAbits.RA8)
#define LD1_O			(LATAbits.LATA8)
#define IO1_TRIS		(TRISAbits.TRISA9)		// LD2 (I/O 1)
#define IO1_I			(PORTAbits.RA9)	
#define IO1_O			(LATAbits.LATA9)	
#define IO2_TRIS		TRISCbits.TRISC3	// I/O 2
#define IO2_I			PORTCbits.RC3
#define IO3_TRIS		TRISCbits.TRISC4	// I/O 3
#define IO3_I			PORTCbits.RC4
#define IO4_TRIS		TRISCbits.TRISC5	// I/O 4
#define IO4_I			PORTCbits.RC5
#define IO5_TRIS		TRISBbits.TRISB6	//I/O 5
#define	IO5_I			PORTBbits.RB6
#define IO6_TRIS		TRISBbits.TRISB5	//I/O 6
#define	IO6_I			PORTBbits.RB5
#define IO7_TRIS		TRISBbits.TRISB8	//I/O 7
#define	IO7_I			PORTBbits.RB8
#define IO8_TRIS		TRISBbits.TRISB7	//I/O 8
#define	IO8_I			PORTBbits.RB7
	

//custom pin assignments for our hardware
// ENC28J60 I/O pins
//mapping:
//A2 ETH-INT
//C2 MISO
//C1 MOSI
//C0 CLK
//B3 CS
//B2 RST
//CS and RST pins
#define ENC_RST_TRIS		(TRISBbits.TRISB2)	
#define ENC_RST_IO			(PORTBbits.RB2)
#define ENC_RST_LAT         (LATBbits.LATB2)
#define ENC_CS_TRIS			(TRISBbits.TRISB3)
#define ENC_CS_IO			(PORTBbits.RB3)
#define ENC_CS_LAT          (LATBbits.LATB3)
//assign SPI module to ENC28J60
#define ENC_SPI_IF			(IFS0bits.SPI1IF)
#define ENC_SSPBUF			(SPI1BUF)
#define ENC_SPISTAT			(SPI1STAT)
#define ENC_SPISTATbits		(SPI1STATbits)
#define ENC_SPICON1			(SPI1CON1)
#define ENC_SPICON1bits		(SPI1CON1bits)
#define ENC_SPICON2			(SPI1CON2)

//define the SPI interface to use with the SD card
#define SD_CS				LATBbits.LATB13
#define SD_CS_TRIS			TRISBbits.TRISB13
//#define SD_CD				PORTAbits.RA2
//#define SD_CD_TRIS			TRISAbits.TRISA2

//SPI module setup
#define SPICON1				SPI2CON1
#define SPICON2			SPI2CON2
#define SPISTAT				SPI2STAT
#define SPIBUF				SPI2BUF
#define SPISTAT_RBF			SPI2STATbits.SPIRBF
#define SPICON1bits			SPI2CON1bits
#define SPISTATbits			SPI2STATbits
#define SPIENABLE           SPI2STATbits.SPIEN

//TRIS for SCK/SDI/SDO lines
#define SPICLOCK			TRISBbits.TRISB11
#define SPIIN				TRISBbits.TRISB10
#define SPIOUT				TRISBbits.TRISB12

//EEPROM setup
// 25LC I/O pins
#define EEPROM_CS_TRIS      (TRISCbits.TRISC7)
#define EEPROM_CS_IO		(PORTCbits.RC7)//could be LAT for output...
#define EEPROM_SCK_TRIS		(TRISCbits.TRISC6)
#define EEPROM_SDI_TRIS		(TRISBbits.TRISB9)
#define EEPROM_SDO_TRIS		(TRISCbits.TRISC8)

#define EEPROM_SPI_IF		(IFS2bits.SPI2IF)
#define EEPROM_SSPBUF		(SPI2BUF)
#define EEPROM_SPICON1		(SPI2CON1)
#define EEPROM_SPICON1bits	(SPI2CON1bits)
#define EEPROM_SPICON2		(SPI2CON2)
#define EEPROM_SPISTAT		(SPI2STAT)
#define EEPROM_SPISTATbits	(SPI2STATbits)


// PPS input registers RPINR20bits.SDI1R
#define INT1R_I	RPINR0bits.INT1R
#define INT2R_I RPINR1bits.INT2R
#define T2CKR_I RPINR3bits.T2CKR
#define T3CKR_I RPINR3bits.T3CKR
#define T4CKR_I RPINR4bits.T4CKR
#define T5CKR_I RPINR4bits.T5CKR
#define IC1R_I RPINR7bits.IC1R
#define IC2R_I RPINR7bits.IC2R
#define IC7R_I RPINR10bits.IC7R
#define IC8R_I RPINR10bits.IC8R
#define OCFAR_I RPINR11bits.OCFAR
#define U1CTSR_I RPINR18bits.U1CTSR
#define U1RXR_I RPINR18bits.U1RXR
#define U2CTSR_I RPINR19bits.U2CTSR
#define U2RXR_I RPINR19bits.U2RXR
#define SDI1R_I RPINR20bits.SDI1R
#define SCK1R_I RPINR20bits.SCK1R
#define SS1R_I RPINR21bits.SS1R
#define SDI2R_I RPINR22bits.SDI2R
#define SCK2R_I RPINR22bits.SCK2R
#define SS2R_I RPINR23bits.SS2R


// Peripheral Pin Select Outputs
#define NULL_O		0
#define C1OUT_O		1
#define C2OUT_O		2
#define U1TX_O		3
#define U1RTS_O		4
#define U2TX_O		5
#define U2RTS_O		6
#define SDO1_O		7
#define SCK1OUT_O	8
#define SS1OUT_O	9
#define SDO2_O		10
#define SCK2OUT_O	11
#define SS2OUT_O	12
#define OC1_O		18
#define OC2_O		19
#define OC3_O		20
#define OC4_O		21
#define OC5_O		22

// Peripheral Pin Select pin output registers
#define RP0_O RPOR0bits.RP0R
#define RP1_O RPOR0bits.RP1R
#define RP2_O RPOR1bits.RP2R
#define RP3_O RPOR1bits.RP3R
#define RP4_O RPOR2bits.RP4R
#define RP5_O RPOR2bits.RP5R
#define RP6_O RPOR3bits.RP6R
#define RP7_O RPOR3bits.RP7R
#define RP8_O RPOR4bits.RP8R
#define RP9_O RPOR4bits.RP9R
#define RP10_O RPOR5bits.RP10R
#define RP11_O RPOR5bits.RP11R
#define RP12_O RPOR6bits.RP12R
#define RP13_O RPOR6bits.RP13R
#define RP14_O RPOR7bits.RP14R
#define RP15_O RPOR7bits.RP15R
#define RP16_O RPOR8bits.RP16R
#define RP17_O RPOR8bits.RP17R
#define RP18_O RPOR9bits.RP18R
#define RP19_O RPOR9bits.RP19R
#define RP20_O RPOR10bits.RP20R
#define RP21_O RPOR10bits.RP21R
#define RP22_O RPOR11bits.RP22R
#define RP23_O RPOR11bits.RP23R
#define RP24_O RPOR12bits.RP24R

#define u8 unsigned char
#define uint8_t u8
#define u16 unsigned short
#define uint16_t u16 
#define u32 unsigned long
#define uint32_t u32 
#define CS_EN()    ENC_CS_LAT=0 
#define CS_DIS()   ENC_CS_LAT=1
#define HARDRESET() ENC_RST_LAT = 0; delay_ms(10);ENC_RST_LAT = 1
#define SPI_BUF     ENC_SSPBUF
#define SPITXRX() 	while(!ENC_SPI_IF)
