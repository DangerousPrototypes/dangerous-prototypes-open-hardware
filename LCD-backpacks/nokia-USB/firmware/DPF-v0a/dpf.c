#include "FSIO.h"
#include "LCD_driver.h"
#define SDLED LATBbits.LATB13

//struct stuff
static struct BMIH { //declares BitMap Info Header structure
	unsigned long biSize;
	unsigned long biWidth;
	unsigned long biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned long biCompression;
	unsigned long biSizeImage;
	unsigned long biXPelsPerMeter;
	unsigned long biYPelsPerMeter;
	unsigned long biClrUsed;
	unsigned long biClrImportant;
}BMPInfo;

static struct BMFH { //declares BitMap File Header structure
	unsigned short bfType; //might need to be a char
	unsigned long bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long bfOffBits;
}BMPHeader;

void msDelay(const unsigned int delay);
void usDelay(const unsigned int delay);

void dpfTasks(void)
{
   static FSFILE * pointer;
   static SearchRec rec;
   static unsigned char attributes;
   static enum _gfxState
	{
		GFX_INIT = 0,
		GFX_FIND_FILE,
		GFX_OPEN_FILE,
		GFX_PARSE_FILE,
		GFX_DELAY,
	} gfxState = GFX_INIT;
	static struct BMP24 {
		unsigned char B;
		unsigned char G;
		unsigned char R;
	}BMP24PX;
	unsigned char error=0, px;
	unsigned int pxi,i;
	static unsigned char pictureChangeDelay=1;

	switch(gfxState)
	{
		case GFX_INIT:
			SDLED=1;//SD access LED
	   		if(!MDD_MediaDetect())break;
		   // Initialize the library
	   		if(!FSInit())break;
			// Change directory to the root dir
	   		if(FSchdir("\\")) break;
			// Set attributes
	   		attributes = ATTR_DIRECTORY | ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN;
			
			//check for config file
	   		if (FindFirst ("config.ini", attributes, &rec)){
				//not found, use default 1 second delay, 
				// Create the file
				pointer = FSfopen ("config.ini", "w");
				if (pointer == NULL){gfxState=GFX_INIT;break;}//error, try again....

				// Write the string to it
				if (FSfwrite ("1", 1, 1, pointer) != 1){gfxState=GFX_INIT;break;}//error, try again....

				
				// Close the file
				if (FSfclose (pointer)){gfxState=GFX_INIT;break;}//error, try again....

			}
			pointer = FSfopen ("config.ini", "r");
			if (pointer == NULL){gfxState=GFX_INIT;break;}//error, try again....

			//update here for delays greater than 9 seconds...
		   	if (FSfread (&pictureChangeDelay, 1, 1, pointer) != 1){gfxState=GFX_INIT;break;}//error, try again....
			pictureChangeDelay-=0x30;//adjust for ASCII
			if (FSfclose (pointer)){gfxState=GFX_INIT;break;}//error, try again....

	   		// Find the first file with any (or none) of those attributes
	   		if (FindFirst ("*.BMP", attributes, &rec))break;//return on no files found, should do an error...
			gfxState=GFX_OPEN_FILE;
			break;
		case GFX_FIND_FILE:
   			// Keep finding files
			SDLED=1;//SD access LED
			if (FindNext (&rec)){//does not loop. get again...
		       // Set attributes
			   attributes = ATTR_DIRECTORY | ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN;
			   // Find the first seq file with any (or none) of those attributes
			   if (FindFirst ("*.BMP", attributes, &rec)){gfxState=GFX_INIT;break;}
			}
			gfxState=GFX_OPEN_FILE;
			break;
		case GFX_OPEN_FILE:	
		   // open the file
	   		pointer = FSfopen (rec.filename, "r");
	   		if (pointer == NULL){gfxState=GFX_INIT;break;}//error, try again....
//get first header, is it BMP?
			SDLED=1;//SD access LED
		   	if (FSfread (&BMPHeader, sizeof(BMPHeader), 1, pointer) != 1){gfxState=GFX_INIT;break;}//error, try again....
			SDLED=0;//SD access LED
			if(BMPHeader.bfType!=0x4d42){//BM
			   	// Close the file
			   	if (FSfclose (pointer)){gfxState=GFX_INIT;break;}//error, try again....
			   	gfxState=GFX_FIND_FILE;//get the next file
				break;
			}
//get second header, can we read? 
			SDLED=1;//SD access LED
		   	if (FSfread (&BMPInfo, sizeof(BMPInfo), 1, pointer) != 1){gfxState=GFX_INIT;break;}//error, try again....
			SDLED=0;//SD access LED
			error=0;
			if(BMPInfo.biSize!=40){error=1;}//unknown header format/length
			if(BMPInfo.biWidth!=132){error=1;}//image wrong size
			if(BMPInfo.biHeight!=132){error=1;}
			if(BMPInfo.biPlanes!=1){error=1;}//this should be 1
			if(BMPInfo.biCompression!=0){error=1;}//0=no compression
			if(error==1){
			   	// Close the file
			   	if (FSfclose (pointer)){gfxState=GFX_INIT;break;}//error, try again....
			   	gfxState=GFX_FIND_FILE;//get the next file
				break;
			}
//configure screen and continue
			switch(BMPInfo.biBitCount){
				case 1:
					break;
				case 4:
					break;
				case 8:
					break;
				case 24:
					break;
				default://error, unknown color depth
					// Close the file
			   		if (FSfclose (pointer)){gfxState=GFX_INIT;break;}//error, try again....
			   		gfxState=GFX_FIND_FILE;//get the next file
					break;
			}						
			
			//set curser to 0,0, prepare for new data
			fillBox(0,0);

			gfxState=GFX_PARSE_FILE;
			break;
		case GFX_PARSE_FILE:
		   // Check if this is the end of the file
	   		if(FSfeof(pointer)){
			   	// Close the file
			   	if (FSfclose (pointer)){gfxState=GFX_INIT;break;}//error, try again....
			   	gfxState=GFX_FIND_FILE;//get the next file
				break;
			}		

			//get next pixel data, this is slow and could be much improved
			//by grabbing multiple pixs and processing all at once, but its
			//clean and simple.
			SDLED=1;//SD access LED
		   	if (FSfread (&BMP24PX, sizeof(BMP24PX), 1, pointer) != 1){
				//gfxState=GFX_INIT;
				//break;
			   	// Close the file
			   	if (FSfclose (pointer)){gfxState=GFX_INIT;break;}//error, try again....
			   	gfxState=GFX_DELAY;//do a delay until next file
				break;
			}//error, try again....
		    SDLED=0;//SD access LED

			//process the sector into screen data		
			pxi=(BMP24PX.R&= (~0b00001111));	//clear unneeded bits
			pxi+=(BMP24PX.G&= (~0b00001111))>>4;
			pxi=pxi<<4;
			pxi+=(BMP24PX.B&= (~0b00001111))>>4;
			
			//use this for 12 bits
			//for 12bit single px: 0000RRRR GGGGBBBB
			LCD_data(pxi>>8);
			LCD_data(pxi);

/*			//use this for 8 bits
		    //process the sector into screen data		
			px=(BMP24PX.R&= (~0b00011111));	//clear unneeded bits
			px+=(BMP24PX.G&= (~0b00011111))>>3;
			px+=(BMP24PX.B&= (~0b00011111))>>6;

			//use this for the LCD
			LCD_data(px);		
*/							

			gfxState=GFX_PARSE_FILE;
			break;
		case GFX_DELAY:		
			//delay
			for(i=0;i<pictureChangeDelay;i++){
				msDelay(1000);
			}
			//now find and display the next BMP file	
			gfxState=GFX_FIND_FILE;
			break;
	}//switch

	SDLED=0;//SD access LED off if we exited early

}//function

void msDelay(const unsigned int delay)
{
	volatile unsigned int i;
	
	for(i=0;i<delay;i++){
		usDelay(1000);
	}
}


void usDelay(const unsigned int delay)
{
	volatile unsigned int i;
	
	for(i=0;i<delay;i++){//@32MHz = 16MIPS, 16I/uS
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
		asm( "nop" );
	}
}

