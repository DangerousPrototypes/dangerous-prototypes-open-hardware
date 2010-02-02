#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "config.h"
#include "HardwareProfile.h"
#include "./USB/usb.h"
#include "./USB/usb_function_cdc.h"
#include "usb_config.h"
#include "USB\usb_device.h"
#include "USB\usb.h"

#pragma udata
static struct _usbbuffer{
	unsigned char inbuf[64];
	unsigned char cnt;
	unsigned char rdptr;
} ubuf;

unsigned char buf[64];

#define COMMAND 0
#define ID 1
#define WRITE 2
#define READ 3
#define SUCCESS 4
#define ERASE 5
#define ERROR 6
#define STATUS 7
#define VERSION 8

static struct _sm {
	unsigned char state;
	unsigned int repeat;
	unsigned char crc;
	unsigned char cmdcnt;
	unsigned char cmdbuf[4];
}sm;

static void init(void);
void setupROMSPI(void);
void teardownROMSPI(void);
unsigned char spi(unsigned char c);
void usbbufservice(void);
void usbbufflush(void);
unsigned char usbbufgetbyte(unsigned char* c);

#pragma code
void main(void){   
#define SUMP 0
#define UPGRADE 1
	unsigned char i,j,inbuf, mode=SUMP, uartincnt=0;

    init();
	usbbufflush();//setup the USB byte buffer
	
	if(PIN_UPDATE==0){
		mode=UPGRADE;
	}else{//self test (move to function)
		//self test
		if( PIN_PROG_B==0){
			while(1){
				unsigned long timer=0x20000;
				while(timer--);
				PIN_LED^=1;
			}
		}
	
		//wait for DONE to go high
		i=0;
		while(PIN_DONE==0){
			unsigned int timer=0xffff;
			while(timer--);
			PIN_LED^=1;
			i++;
			if(i==0x50){
				mode=UPGRADE;
				break;
			}
		}
	
		PIN_LED=0; //OK, LED on
	}

	if(mode==UPGRADE){
		PIN_LED=1;
		setupROMSPI();
		sm.state=COMMAND;
		sm.cmdcnt=0;
	}

    while(1){
        USBDeviceTasks(); 

    	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) continue;
		usbbufservice();//load any USB data into byte buffer

		if(mode==SUMP){
		
			if(TXSTA2bits.TRMT==1){//grabbing a byte before we know the UART is ready is bad, do it after
				if(usbbufgetbyte(&inbuf)==1){
					PIN_LED=1;
					TXREG2=inbuf; //put inbuf in UART
					PIN_LED=0; 
				}
			}
		
			if(PIR3bits.RC2IF==1){
				//get UART to buf
				PIN_LED=1;
				buf[uartincnt] = RCREG2;
				++uartincnt;
				PIN_LED=0;
			}
		
			if((mUSBUSARTIsTxTrfReady()) && (uartincnt > 0)){
				PIN_LED=1;
				putUSBUSART(&buf[0], uartincnt);
				uartincnt = 0;
				PIN_LED=0;
			}

    		CDCTxService();
			continue; //skip the upgrade below
					//this will eventually be improved
					//for now, it's rough and ready
		}

		switch(sm.state){
			case COMMAND:
				if(!usbbufgetbyte(&inbuf)) continue; //wait for more data
				sm.cmdbuf[sm.cmdcnt]=inbuf;//grab and hold for later 
				sm.cmdcnt++;
				if(sm.cmdcnt>3){//got all four command bytes
					sm.cmdcnt=0;
					switch(sm.cmdbuf[0]){
						case 0x00:
							sm.state=VERSION;
							break;
						case 0x01: //CMD_ID:	//read out ID and send back 0x01 00 00 00
							sm.state=ID;
							break;
						case 0x02: //CMD_WRITE: //packet of 0x84+ A3 A2 A1 + data page (264)+CRC
							sm.state=WRITE;
							sm.repeat=265;
							sm.crc=0;
							//setup for write
							PIN_FLASH_CS=0; //CS low
							spi(0x84);//write page buffer 1 command
							spi(0);//send buffer address
							spi(0);
							spi(0);
							break;		
						case 0x03://CMD_READ packet of 0x03 A3 A2 A1 
							sm.state=READ;
							sm.repeat=264;
							//setup for write
							PIN_FLASH_CS=0; //CS low
							spi(0x03);//read array command
							spi(sm.cmdbuf[1]);//send read address
							spi(sm.cmdbuf[2]);
							spi(sm.cmdbuf[3]);	
							//spi(0x00);//one don't care bytes	
							break;
						case 0x04://CMD_ERASE chip
							sm.state=ERASE;
							PIN_FLASH_CS=0; //CS low
							spi(0xc7);//erase code, takes up to 12 seconds!
							spi(0x94);//erase code, takes up to 12 seconds!
							spi(0x80);//erase code, takes up to 12 seconds!
							spi(0x9a);//erase code, takes up to 12 seconds!
							PIN_FLASH_CS=1; //CS high
							break;
						case 0x05://CMD_STATUS
							sm.state=STATUS;
							break;
						case '$': //jump to bootloader
							BootloaderJump();
							break;
						case 0xff://return to normal mode
							//sm.state=COMMAND;
							//sm.cmdcnt=0;
							//PIN_LED=0;
							//mode==SUMP;
							teardownROMSPI();
							_asm RESET _endasm;
							break;
						default:
							sm.state=ERROR;//return 0xff or 0x00		
					}
				}
				break;
			case VERSION:
				if(mUSBUSARTIsTxTrfReady()){
					buf[0]='H';
					buf[1]=0x01;
					buf[2]='F';
					buf[3]=0x00;
					buf[4]=0x01;
					buf[5]='B';
					//read 0x7fe for the bootloader version string
					TBLPTRU=0;
					TBLPTRH=0x7;
					TBLPTRL=0xfe;
					_asm TBLRDPOSTINC _endasm; //read into TABLAT and increment
					buf[6]=TABLAT;
					//_asm TBLRDPOSTINC _endasm; //read into TABLAT and increment
					//buf[6]=TABLAT;
					putUSBUSART(buf,7);
					sm.state=COMMAND;
				}
				break;
			case ID:
				if(mUSBUSARTIsTxTrfReady()){
					PIN_FLASH_CS=0; //CS low
					spi(0x9f);//get ID command
					buf[0]=spi(0xff);
					buf[1]=spi(0xff);
					buf[2]=spi(0xff);
					buf[3]=spi(0xff);
					PIN_FLASH_CS=1;
					putUSBUSART(buf,4);
					sm.state=COMMAND;
				}
				break;

			case ERASE:
				PIN_FLASH_CS=0;
				spi(0xd7);//read status command
				i=spi(0xff);
				if((i & 0b10000000)!=0 ){
					sm.state=SUCCESS; //send success
				}
				PIN_FLASH_CS=1;	
				break;

			case WRITE:
				if(!usbbufgetbyte(&inbuf)) continue; //wait for more data
				if(sm.repeat>1){
					spi(inbuf);
					sm.crc+=inbuf;//add to CRC
					sm.repeat--;
				}else{
					PIN_FLASH_CS=1;//disable CS
					sm.crc^=0xff;//calculate CRC
					sm.crc++;
					if(sm.crc==inbuf){//check CRC
						//slight delay
						PIN_FLASH_CS=0;
						spi(0x83);//save buffer to memory command
						spi(sm.cmdbuf[1]);//send write page address
						spi(sm.cmdbuf[2]);
						spi(sm.cmdbuf[3]);	
						PIN_FLASH_CS=1;//disable CS
				
						PIN_FLASH_CS=0;
						spi(0xd7);//read status command
						while(1){//wait for status to go ready
							i=spi(0xff);
							if((i & 0b10000000)!=0 ) break; 
						}
						PIN_FLASH_CS=1;
						sm.state=SUCCESS;
					}else{
						sm.state=ERROR;	
					}
				}
				break;

			case READ: //read more bytes
				if(mUSBUSARTIsTxTrfReady()){
	

					if(sm.repeat<64) 
						j=sm.repeat; //if less left then adjust
					else
						j=64;//read 64 bytes

					sm.repeat-=j; //remove from total bytes to read
	
					for(i=0; i<j; i++) buf[i]=spi(0xff); //read j bytes
	
					putUSBUSART(buf,j); //send the bytes over USB
					
					if(sm.repeat==0){//end of read bytes,
						PIN_FLASH_CS=1; //disable the chip
						sm.state=COMMAND;  //wait for next instruction packet
					}
				}
				break;
			case STATUS:
				if(mUSBUSARTIsTxTrfReady()){
					PIN_FLASH_CS=0;
					spi(0xd7);//read status command
					buf[0]=spi(0xff);
					PIN_FLASH_CS=1;	
	
					putUSBUSART(buf,1); //send the bytes over USB
					sm.state=COMMAND;  //wait for next instruction packet
				}
				break;
			case SUCCESS:
				if(mUSBUSARTIsTxTrfReady()){
					buf[0]=0x01;
					putUSBUSART(buf,1); //send the bytes over USB
					sm.state=COMMAND;  //wait for next instruction packet
				}
				break;
			case ERROR:
				if(mUSBUSARTIsTxTrfReady()){
					buf[0]=0x00;
					putUSBUSART(buf,1); //send the bytes over USB
					sm.state=COMMAND;  //wait for next instruction packet
				}
				break;
		}//switch

    	CDCTxService();

    }//end while
}//end main

static void init(void){
	unsigned int cnt = 700;
	//on 18f24j50 we must manually enable PLL and wait at least 2ms for a lock
	OSCTUNEbits.PLLEN = 1;  //enable PLL
	while(cnt--); //wait for lock

	//all pins digital
    ANCON0 = 0xFF;                  
    ANCON1 = 0xFF;                  

	//there are some sensative FPGA pins, 
	//make sure everything is input (should be on startup, but just in case)
	TRISA=0xff;
	TRISB=0xff;
	TRISC=0b11111011; //LED out

	//setup UART1 (C6=TX/C7=RX)
	TRIS_UART1_TX=0;//transmit to output
	PIN_UART1_TX=0; //pin to ground
	
	SPBRGH1=0;
	SPBRG1=25;
	BAUDCON1=0b00000000;
	TXSTA1=0b00100110;
	RCSTA1=0b10010000;

	//pins: TX=B1/RP4 RX=B0/RP3
	TRIS_UART2_TX=0;//transmit to output
	PIN_UART2_TX=0; //pin to ground
	//assign RP4= TX2 (5)
	RPOR4=5;
	//assign RX2=RP3
	RPINR16=3;

	SPBRGH2=0;
	SPBRG2=25;//25=115200, 77=38400
	BAUDCON2=0b00000000;
	TXSTA2=0b00100110;
	RCSTA2=0b10010000;

    USBDeviceInit();//setup usb
	PIN_LED=0;
}

unsigned char spi(unsigned char c){
	SSP2BUF=c;
	while(SSP2STATbits.BF==0);
	c=SSP2BUF;
	return c;
}

void setupROMSPI(void){
	//setup SPI for ROM
	//!!!leave unconfigured (input) except when PROG_B is held low!!!
	PIN_PROG_B=0; //ground
	TRIS_PROG_B=0; //output
	//A0 PR0 flash_si
	//A1 PR1 flash_so
	//B5 RP8 flash_sck
	//A2 flash_cs

	//CS disabled
	PIN_FLASH_CS=1; //CS high
	TRIS_FLASH_CS=0; //CS output

	//TRIS_FLASH_MISO=1;
	RPINR21=1;//PPS input

	TRIS_FLASH_MOSI=0;
	PIN_FLASH_MOSI=0;
	RPOR0=9; //PPS output
	
	TRIS_FLASH_SCK=0;
	PIN_FLASH_SCK=0;
	RPOR8=10; //PPS output

	SSP2CON1=0b00100000; //SSPEN/ FOSC/4
	SSP2STAT=0b01000000; //cke=1
}

void teardownROMSPI(void){

	SSP2CON1=0; //disable SPI
	//A0 PR0 flash_si
	//A1 PR1 flash_so
	//B5 RP8 flash_sck
	//A2 flash_cs
	//TRIS_FLASH_MISO=1;
	RPINR21=0b11111; //move PPS to nothing

	TRIS_FLASH_MOSI=1;
	RPOR0=0;
	
	TRIS_FLASH_SCK=1;
	RPOR8=0;
	
	//CS disabled
	TRIS_FLASH_CS=1; //CS input
	PIN_FLASH_CS=0; //CS low

	TRIS_PROG_B=1; //input, release PROG_B
}

void usbbufservice(void){
	if(ubuf.cnt==0){//if the buffer is empty, get more data
		ubuf.cnt = getsUSBUSART(ubuf.inbuf,64);
		ubuf.rdptr=0;
	}
}

//puts a byte from the buffer in the byte, returns 1 if byte
unsigned char usbbufgetbyte(unsigned char* c){
	if(ubuf.cnt>0){
		*c=ubuf.inbuf[ubuf.rdptr];
		ubuf.cnt--;
		ubuf.rdptr++;
		return 1;
	}
	return 0;
}

void usbbufflush(void){
	ubuf.cnt = 0;
	ubuf.rdptr=0;
}

//
//
//the stack calls these, if they aren't here we get errors. 
//
//
void USBCBSuspend(void){}
void USBCBWakeFromSuspend(void){}
void USBCB_SOF_Handler(void){}
void USBCBErrorHandler(void){}
void USBCBCheckOtherReq(void){USBCheckCDCRequest();}//end
void USBCBStdSetDscHandler(void){}//end
void USBCBInitEP(void){CDCInitEP();}
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size){
    switch(event){
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER:
            Nop();
            break;
        default:
            break;
    }      
    return TRUE; 
}

#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818

//We didn't use the low priority interrupts, 
// but you could add your own code here
#pragma interruptlow InterruptHandlerLow
void InterruptHandlerLow(void){}

//We didn't use the low priority interrupts, 
// but you could add your own code here
#pragma interrupthigh InterruptHandlerHigh
void InterruptHandlerHigh(void){}

//these statements remap the vector to our function
//When the interrupt fires the PIC checks here for directions
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void){
     _asm goto InterruptHandlerHigh _endasm
}

#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
void Remapped_Low_ISR (void){
     _asm goto InterruptHandlerLow _endasm
}

//relocate the reset vector
extern void _startup (void);  
#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
void _reset (void){
    _asm goto _startup _endasm
}
//set the initial vectors so this works without the bootloader too.
#pragma code HIGH_INTERRUPT_VECTOR = 0x08
void High_ISR (void){
     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
}
#pragma code LOW_INTERRUPT_VECTOR = 0x18
void Low_ISR (void){
     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
}

