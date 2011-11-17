/* header */

// defines
// I2C defines/state machine
#define I2CADDEE        0xA0
#define I2CADDADC		0x10
#define I2CADDDAC		0x20
#define I2CADDMASK      0xFE	// use only 1 address    
#define I2CMASK         0x03

// I2C statemachine defines
#define I2CSTATMASK     0x25
#define MWA             0x01    //Master Writes Address
#define MWD             0x21	//Master Writes Data
#define MRA             0x05	//Master Reads Address
#define MRD             0x24	//Master Reads Data

// forward declarations
void initI2C(void);				// init I2C hardware, setup interrupts etc
void I2CWrite(unsigned char c);	// write a byte on the bus
void I2CEEworker(void);			// main I2C processing loop EEPROM
void I2Cworker(void);		// main I2C processing loop ADC

// isr macro
// I2C doesn't have an isr (although It should have one!)
#define I2Cisr	do { ;\
} while(0);