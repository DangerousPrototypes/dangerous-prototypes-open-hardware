/*
 * This file is part of the #twatch project (dangerousprototypes.com).
 * NOTE: this code requires the Microchip TCP/IP stack, which is released under the Microchip license.
 *       Code written by the #twatch project is released into the public domain, 
 *		 The Microchip license still applies to the Microchip TCP/IP stack.
 *
 * Originally written by Ian Lesnet <ian@dangerousprototypes.com>
 *
 * To the extent possible under law, Ian Lesnet <ian@dangerousprototypes.com> has
 * waived all copyright and related or neighboring rights to this code. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "HD44780.h" //include LCD display functions

#define SERVER_PORT	1337 //set the server listening port

//define the Matrix Orbital command set
#define MATRIX_ORBITAL_COMMAND 254 //0xfe
#define BACKLIGHT_ON 66 //0x42, 1 parameter (minutes 00=forever)
#define BACKLIGHT_OFF 70 //0x46
#define CLEAR 88
#define HOME 72
#define POSITION 71 //2 parameters (col, row)
#define UNDERLINE_CURSER_ON 74
#define UNDERLINE_CURSER_OFF 75
#define BLOCK_CURSER_ON 83
#define BLOCK_CURSER_OFF 84
#define BACKLIGHT_BRIGHTNESS 152 //1 parameter (brightness)
#define CUSTOM_CHARACTER 78 //9 parameters (character #, 8 byte bitmap)
#define NETWORK_CONFIG 153 //show node connection details (custom)
#define EXIT 154 //exit Matrix orbital mode and resume screeensaver

//main TCP server state machine
//returns 0 (nothing) 1 (stop the #twatch client) 2 (start the #twatch client)
unsigned char MatrixOrbitalTCPServer(void)
{
	BYTE i, workingCommand, ret=0;
	WORD w, w2;
	BYTE AppBuffer[32];
	WORD wMaxGet, wCurrentChunk;
	static TCP_SOCKET MySocket;
	static enum _TCPServerState
	{
		SM_HOME = 0,
		SM_LISTENING,
	} TCPServerState = SM_HOME; //server status state machine

	static enum _LCDmode{
		TEXT=0,
		COMMAND,
		COMMAND_PARAMETERS,
	}LCDmode=TEXT; //matrix orbital command parser state machine
	
	static unsigned char parameters, parCnt, par[9]; //variables to store LCD incoming commands

	//this state machine responds to incomming TCP packets and parses it for matrix orbital commands
	switch(TCPServerState)
	{
		case SM_HOME://start server listening
			MySocket = TCPOpen(0, TCP_OPEN_SERVER, SERVER_PORT, TCP_PURPOSE_GENERIC_TCP_SERVER); //setup server
			if(MySocket == INVALID_SOCKET) //if invalid, try again next time
				return 0;

			TCPServerState = SM_LISTENING; //server listening
			break;

		case SM_LISTENING://service the TCP server
			if(!TCPIsConnected(MySocket)) //if no connections, break
				return 0;

			wMaxGet = TCPIsGetReady(MySocket);	//get TCP RX byte count

			// Process all bytes that we can
			// This is implemented as a loop, processing up to sizeof(AppBuffer) bytes at a time.  
			// This limits memory usage while maximizing performance.  Single byte Gets and Puts are a lot slower than multibyte GetArrays and PutArrays.
			wCurrentChunk = sizeof(AppBuffer);
			for(w = 0; w < wMaxGet; w += sizeof(AppBuffer))
			{
				if(w + sizeof(AppBuffer) > wMaxGet) //adjust for odd size arrays
					wCurrentChunk = wMaxGet - w;

				TCPGetArray(MySocket, AppBuffer, wCurrentChunk); //get data
				
				for(w2 = 0; w2 < wCurrentChunk; w2++)
				{
					i = AppBuffer[w2];
					//-------------------------------//
					//parser
				switch(LCDmode){ //this is a state machine that grabs the incoming commands one byte at a time
					case TEXT: //assume text, if 254 then enter command mode
						if(i==MATRIX_ORBITAL_COMMAND){
							LCDmode=COMMAND; //next byte is actual command
							break;
						}	
						LCD_WriteChar(i); //not a command, just write it to the display
						break;
					case COMMAND://previous byte was 254, now get actual command
						switch(i){//switch on the command
							case BACKLIGHT_ON: //1 parameter (minutes 00=forever)
								LCD_Backlight(1);//turn it on, we ignore the parameter
								LCDmode=COMMAND_PARAMETERS;//get one more byte before processing
								parameters=1;
								break;
							case BACKLIGHT_OFF:
								LCD_Backlight(0);//backlight off
								break;
							case CLEAR:
								LCD_Clear();
								break;
							case HOME:
								LCD_Home();
								break;
							case POSITION: //2 parameters (col, row)
								LCDmode=COMMAND_PARAMETERS; //get 2 more bytes before processing
								parameters=2;
								break;
							case UNDERLINE_CURSER_ON:
								LCD_UnderlineCursor(1);
								break;
							case UNDERLINE_CURSER_OFF:
								LCD_UnderlineCursor(0);
								break;
							case BLOCK_CURSER_ON:
								LCD_BlinkCursor(1);
								break;
							case BLOCK_CURSER_OFF:
								LCD_BlinkCursor(0);
								break;
							case BACKLIGHT_BRIGHTNESS://1 parameter (brightness)
								LCDmode=COMMAND_PARAMETERS; //get one more byte before processing
								parameters=1;
								break;
							case CUSTOM_CHARACTER: //9 parameters (character #, 8 byte bitmap)
								LCDmode=COMMAND_PARAMETERS; //get 9 more bytes before processing
								parameters=9;
								break;
							case NETWORK_CONFIG: //show node connection details (custom)
								break;
							case EXIT: //restore screensaver mode (custom)
 								ret=2;//return 2 to restore twatch
								break;
							default: //error
								break;
						}
						
						if(LCDmode==COMMAND_PARAMETERS){//if we have more bytes to get, store the command so we know what to do with them
							workingCommand=i; //store command so we know how to deal with the parameters
							parCnt=0;//reset the parameter counter
						}else{//all done with command
							LCDmode=TEXT;//next byte is text or begins new command				
						}
						break;

					case COMMAND_PARAMETERS:
						
						par[parCnt]=i;//store each parameter in a buffer
						parCnt++;
						if(parCnt<parameters) break; //if not all parameters yet, quit

						switch(workingCommand){ //got all the parameters, now process the command
							case BACKLIGHT_ON: //1 parameter (minutes 00=forever)
								 //ignore value
								break;
							case POSITION: //2 parameters (col, row)
								i=( ((par[1]-1)*20) + par[0] ); //convert to 20x4 layout (used defined lines, add rows...)
								LCD_CursorPosition(i);
								if(i==1) ret=1;//return 1 to stop twatch...
								break;
							case BACKLIGHT_BRIGHTNESS://1 parameter (brightness)
								break; //do nothing, no brightness control (yet), use PWM on pin...
							case CUSTOM_CHARACTER: //9 parameters (character #, 8 byte bitmap)
								LCD_WriteCGRAM(par[0]);//write character address
								for(i=1; i<9; i++) LCD_WriteRAM(par[i]); //send 8 bitmap bytes
								break; //do nothing, no special characters yet
							default: //error
								break;
						}
						
						LCDmode=TEXT; //end of command with parameters, next byte is text or new command...
						break;					
					}
					//------------------------------//
				}
				
			}

			break;
	}
	return ret;//return status info //return 1 to stop twatch...
}

/*
command reference: http://www.freewebs.com/x7jay7x/Blank%20Page%205.htm
-[254]
- Backlight On Command, (066  000)
Turns LCD backlight on. 
- Backlight Off Command, (070)
Turns LCD backlight off. 
- Position Command, (071 [col] [row]) 0x47
Moves the cursor to the specified [col] and [row].  Columns have the values 1 to 40; rows have the values 1 to 4.  These values depend on the LCD type you are using.  For example, a 4x20 LCD would have a column of 1 to 20 and a row of 1 to 4.
 - Home Command, (072)
Returns the cursor to the home position.  The home position is the top left of the display.
- Underline Cursor On, (074)
Turns the underline cursor on.  This shows where the current text insertion point is.  The underline cursor is off by default.
- Underline Cursor Off, (075)
Turns the underline cursor off. 
- Custom Character Command, (078 [c] [8 bytes]) 0x4e
The display can hold up to 8 custom characters defined using this command.  After the control command of [78d] is send, the number of the custom character to be defined [c] is given.  The value of [c] is from 0 to 7.  The next 8 bytes define to character.
- Block Cursor On, (083)
Turns the block cursor on.  This shows the current text insertion point.  Block cursor is off by default.
- Block Cursor Off, (084)
Turns off block cursor.
- Clear Display Command, (088)
Clears the contents of the display screen and sets the cursor to the “home” position.
- Backlight Brightness, (152 [b])
Controls the LCD Backlight Brightness.  After the command of 152, [b] is a value of 0 to 255d.  The brightness is a percentage of the total 255.  
*/

