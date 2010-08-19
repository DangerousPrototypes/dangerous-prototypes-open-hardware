//********************************************************************
//
//			Color LCD (128x128) Basic Library
//             (Written for ARM LPC2148)
//
//    					3-9-2008
//			Copyright Spark Fun Electronics© 2008
//						Ryan Owens
//					ryan at sparkfun.com
//
//		See LCD_driver.h for I/O pin and register definitions
//			*Delays assume a 16MHz external clock
//				(should be adjusted accordingly)
//
//
//		Reference: Jim Lynch's "Nokia 6100 LCD Display Driver"
//(http://www.sparkfun.com/tutorial/Nokia%206100%20LCD%20Display%20Driver.pdf)
//	
//		Special thanks to Rich for the heads up on the new driver and
//			for pointing us in the right direction on the
//						initialization code.
//********************************************************************
#include "LCD_driver.h"

//Usage: LCD_command(DISPON);
//Inputs: char data - The command character to be sent to the LCD
//Outputs: None
//Description: This function sends a command signal and an 8 bit command
//				character to the LCD in a 9-bit package
void LCD_command(unsigned char data)
{
	char j;

	LCD_SCK=0;    
	LCD_CS=0;      	// Enable Chip (Bring CS signal LOW)
 
   	LCD_DIO=0;     	// Prepare Data Line (Bring DIO signal LOW)

    LCD_SCK=0;      	// send clock pulse (Bring clock signal LOW)
    LCD_SCK=1;		// (Bring clock signal HIGH)

    for (j = 0; j < 8; j++)
    {
        if ((data & 0x80) == 0x80) LCD_DIO=1;	//Set data line HIGH
        else LCD_DIO=0;							//Set data line LOW

    	LCD_SCK=0;      	// send clock pulse (Bring clock signal LOW)
    	LCD_SCK=1;			// (Bring clock signal HIGH)

        data <<= 1;
    }

    LCD_CS=1;    		// Disable Chip (Bring CS signal HIGH)

}

//Usage: LCD_data(0x03);
//Inputs: char data - The data character to be sent to the LCD
//Outputs: None
//Description: This function sends a data signal and an 8 bit data character
//				to the LCD in a 9-bit package
void LCD_data(unsigned char data)
{
	char j;

	LCD_SCK=0;     
	LCD_CS=0;      	// Enable Chip (Bring CS signal LOW)    

	LCD_DIO=1;    	// Prepare Data Line (Bring DIO signal HIGH!!!)

    LCD_SCK=0;    	// send clock pulse (Bring clock signal LOW)
    LCD_SCK=1;		// (Bring clock signal HIGH)

	for (j = 0; j < 8; j++)
    {
        if ((data & 0x80) == 0x80) LCD_DIO=1;	//Set data line HIGH
        else LCD_DIO=0;							//Set data line LOW

        LCD_SCK=0;   							// send clock pulse (Bring clock signal LOW)
        LCD_SCK=1;								// (Bring clock signal HIGH)
  
      	data <<= 1;
    }

    LCD_CS=1;     		// Disable Chip (Bring CS signal HIGH)
}

//Usage: LCD_init();
//Inputs: None
//Outputs: None
//Description: This function will initialize the LCD, regardless of whether the
//				LCD contains the EPSON or PHILLIPS driver
void LCD_init(void)
{
    long j;
	
    // reset display
	LCD_SCK_DIR=0; //Assign LCD pins as Outputs
	LCD_DIO_DIR=0;			 
	LCD_RES_DIR=0; 	
	LCD_CS_DIR=0;	

// test
/*
   LCD_SCK=1;		
   LCD_DIO=1;					
   LCD_RES=1; 	
   LCD_CS=1;	
   LCD_RES=0; 	
   LCD_CS=0;	
*/ 
    LCD_SCK=0;						//output_low (SPI_CLK);
	LCD_DIO=0;						//output_low (SPI_DO);

    LCD_CS=1;				//output_high (LCD_CS);
    for (j = 0; j < 16; j++);
    LCD_RES=0;				//output_low (LCD_RESET);
    for (j = 0; j < 300000; j++);
    LCD_RES=1;				//output_high (LCD_RESET);
    LCD_SCK=1;
	LCD_DIO=1;
    for (j = 0; j < 300000; j++);	//delay_ms(100);


    LCD_command(DISCTL);  	// display control(EPSON)
    LCD_data(0x0c);   	//0xc (0x00) 12 = 1100 - CL dividing ratio [don't divide] switching period 8H (default)
    LCD_data(0x20);		//0c20
    LCD_data(0x02);		//0x02 (0x0a)	
	
    LCD_command(COMSCN);  	// common scanning direction(EPSON)
    LCD_data(0x01);
    
    LCD_command(OSCON);  	// internal oscialltor ON(EPSON)
    
    LCD_command(SLPOUT);  	// sleep out(EPSON)
	LCD_command(SLEEPOUT);	//sleep out(PHILLIPS)
    
    LCD_command(VOLCTR);  	// electronic volume, this is the contrast/brightness(EPSON)
    LCD_data(0x18);   	// volume (contrast) setting - fine tuning, original
    LCD_data(0x03);   	// internal resistor ratio - coarse adjustment
	LCD_command(SETCON);	//Set Contrast(PHILLIPS)
	LCD_data(0x30);	
	
    LCD_command(TMPGRD);
	LCD_data(0x00);		// default
    
    LCD_command(PWRCTR); 	// power ctrl(EPSON)
    LCD_data(0x0F);    //everything on, no external reference resistors
    LCD_command(BSTRON);	//Booset On(PHILLIPS)
	
    LCD_command(DISINV);  	// invert display mode(EPSON)
	LCD_command(INVON);	// invert display mode(PHILLIPS)

	LCD_command(PTLOUT);	// Partial Out (no partial display)    

    LCD_command(DATCTL);  	// data control(EPSON)
    LCD_data(0b111);	//bit2 adscan dir, bit1 col, bit0 page
    LCD_data(0x00);   	//0x00 normal RGB arrangement
    //LCD_data(0x01);   	//0x01 8-bit grayscale
 	//see: http://www.idcomm.com/personal/lorenblaney/sparkfun.html
	LCD_data(0x04);  // special mode selects 12-bit color for single pixels


	LCD_command(MADCTL);	//Memory Access Control(PHILLIPS)
	LCD_data(0xC8);
	
	LCD_command(COLMOD);	//Set Color Mode(PHILLIPS)
	LCD_data(0x02);	
	
 /*   
    LCD_command(RGBSET8);   // setup 8-bit color lookup table  [RRRGGGBB](EPSON)
    //RED
    LCD_data(0);
    LCD_data(2);
    LCD_data(4);
    LCD_data(6);
    LCD_data(8);
    LCD_data(10);
    LCD_data(12);
    LCD_data(15);
    // GREEN
    LCD_data(0);
    LCD_data(2);
    LCD_data(4);
    LCD_data(6);
    LCD_data(8);
    LCD_data(10);
    LCD_data(12);
    LCD_data(15);
    //BLUE
    LCD_data(0);
    LCD_data(4);
    LCD_data(9);
    LCD_data(15);
    */
    LCD_command(NOP);  	// nop(EPSON)
	LCD_command(NOPP);		// nop(PHILLIPS)

    LCD_command(DISON);   	// display on(EPSON)
	LCD_command(DISPON);	// display on(PHILLIPS)
}

//  sets the starting page(row) and column (x & y) coordinates in ram,
//  then writes the colour to display memory.  The ending x & y are left
//  maxed out so one can continue sending colour data bytes to the 'open'
//  RAMWR command to fill further memory.  issuing any other command
//  finishes RAMWR.
void pset(unsigned char color, unsigned char x, unsigned char y)
{

	#ifdef EPSON
		LCD_command(PASET);   // page start/end ram
		LCD_data(x);
		//LCD_data(x);
		LCD_data(ENDPAGE);
  
		LCD_command(CASET);   // column start/end ram
		LCD_data(y);
		//LCD_data(y);
		LCD_data(ENDCOL);
  
		LCD_command(RAMWR);    // write
		LCD_data(color);
	#endif
}

//this function creates a boundary box for data input that starts at x,y 
//and extends to the edge of the screen
//used to re-zero the data pointer for image drawing
//exits with RAMWR command, use LCD_data() to send pixel data
void fillBox(unsigned char x, unsigned char y){

		LCD_command(PASET);   // page start/end ram
		LCD_data(x);
		//LCD_data(x);
		LCD_data(ENDPAGE-1);
  
		LCD_command(CASET);   // column start/end ram
		LCD_data(y);
		//LCD_data(y);
		LCD_data(ENDCOL);
		
		//now ready for data
		LCD_command(RAMWR);    // write
}