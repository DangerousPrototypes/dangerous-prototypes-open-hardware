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
//#define JSON_DEBUG
#include "TCPIP Stack/TCPIP.h"
#include "HD44780.h"
#include "twatchv1.h"

///this is a TCP client that grabbs 10 twitter trend terms, then grabbs a few tweets for each
//notes on twitter:
// requests must be URL encoded (%xx), the hex equivilent
// in data, " and UTF8 characters are escaped with '\'
// in tweet search results, character are HTML encoded and some are UTF8 encoded
// in trend results, characters are UTF8 encoded

#define TREND_PARSER_BUFFER 225 //255 byte buffer to hold maximum trend terms buffer
#define SEARCH_PARSER_BUFFER 2100 //432 byte buffer for each of MAX_TREND_TERMS x tweet search results
#define MAX_TREND_TERMS 10 //maximum number of trending terms to expect/use
#define HTTP_MAX_RETRY 3 //how many times to retry before delaying
#define TWATCH_REFRESH_INTERVAL 4 //refresh interval in munites, -1

#ifndef JSON_DEBUG
	//April 2011 Twitter changed the feed location to http://api.twitter.com/1/trends/current.json
	//October 23, 2011 Twitter depricated the old feed, now use: http://api.twitter.com/1/trends/1.json
	static BYTE ServerName[] =	"api.twitter.com"; //twitter address
	static WORD ServerPort = 80; //http server port number
	static ROM BYTE TrendURL[] = "/1/trends/1.json"; //trending topics JSON datafeed URL
	static ROM BYTE SearchURL[] = "/1/search.json?rpp=2&q="; //tweet search JSON datafeed URL
#else
	static BYTE ServerName[] =	"www.whereisian.com"; //twitter address
	static WORD ServerPort = 80; //http server port number
	static ROM BYTE TrendURL[] = "/files/current.json"; //trending topics JSON datafeed URL
	static ROM BYTE SearchURL[] = "/files/search.json"; //tweet search JSON datafeed URL
#endif

static ROM BYTE jsonTrendTag[]=",\"name\":\""; //JSON tag that identifies trending topics
static ROM unsigned char jsonSearchTag[]="\"text\":\"";//JSON tag that identifies tweets

static enum _displayMode{
	IDLE,
	UPDATE,
	NEWSCROLL,
	SCROLL,	
}displayMode=IDLE;//lcd operating state

#if defined(__18CXX) //twatch v2, 18F
#pragma udata trends //dont need this, the compiler is smart enough to match it with the blocks in the linker file
#endif
static struct _trendParser{
	unsigned char foundTag:1; //for state machine: currently processing a JSON tag
	unsigned char escape:1; //for state machine: last character was an escape character
	unsigned char xmlencode:1; //for state machine:procesing an XML encoded entity
	unsigned char updatingData:1; //tells screen updater that we're grabbing new data
	unsigned char success:1; //flag is set on first twitter success so we know when to clear away IP conenction info
	unsigned char UTF;
	unsigned char xmlencharcnt;
	unsigned char xmlenchar[2];
	unsigned char tagCharMatchCnt; //we're looking for a tag, now many characters have we matched so far?
	unsigned char tagTotalCnt; //how many trend tags have we detected and parsed?
	unsigned int bufWritePointer; //where we're writing the current value in the buffer
	unsigned char bufValueStartPosition[MAX_TREND_TERMS]; //array of 10 bytes, indicates where each term ends in the buff
	unsigned char bufValueEndPosition[MAX_TREND_TERMS]; //array of 10 bytes, indicates where each term ends in the buff
	unsigned char buf[TREND_PARSER_BUFFER]; //the trend terms as they're scrolled on screen
}trendParser;

#if defined(__18CXX) //twatch v2, 18F
#pragma udata tweets //dont need this, the compiler is smart enough to match it with the blocks inthe linker file
#endif
static struct _searchParser{
	unsigned char foundTag:1;
	unsigned char escape:1;
	unsigned char xmlencode:1;
	unsigned char success:1;
	unsigned char UTF;
	unsigned char xmlencharcnt;
	unsigned char xmlenchar[2];
	unsigned char tagCharMatchCnt;
	unsigned char term;
	unsigned char tagTotalCnt;
	unsigned int bufWritePointer;
	unsigned int bufValueEndPosition[MAX_TREND_TERMS]; //array of 10 bytes, indicates where each term ends in the buff
	unsigned char buf[SEARCH_PARSER_BUFFER];//432
}searchParser;

static unsigned int scrollPointer,scrollOffset=0,scrollPointer2,scrollOffset2=0; //used to track scroll position in the LCD updater

//private functions
void procTrend(unsigned char inBuf);//process trending topics
void procSearch(unsigned char inBuf);//process search results
unsigned char addToTrendBuffer(unsigned char c);//add a byte to buffer, checks for overrun and stores pointer position
unsigned char addToSearchBuffer(unsigned char c);//add a byte to buffer, checks for overrun and stores pointer position
unsigned char XMLdecode(unsigned char x0, unsigned char x1); //decode XML entities to ASCII
unsigned char URLencodeChar(unsigned char buf, unsigned char *URLencoded); //URL encode a character, if needed

void twatchTasks(char frameAdvance){ //this state machine services the #twatch

   static enum _twatchState
	{
		TWATCH_INIT=0,
		TWATCH_IDLE,
		TWATCH_TRENDS_TCP_START,
		TWATCH_TRENDS_TCP_SOCKET_OBTAINED,
		TWATCH_TRENDS_TCP_PROCESS_RESPONSE,
		TWATCH_TRENDS_TCP_DISCONNECT,
		TWATCH_SEARCH_TCP_START,
		TWATCH_SEARCH_TCP_SOCKET_OBTAINED,
		TWATCH_SEARCH_TCP_PROCESS_RESPONSE,
		TWATCH_SEARCH_TCP_DISCONNECT,
	} twatchState = TWATCH_INIT; //massive twitter parsing state machine

   static enum _HTTPstatus
	{
		UNKNOWN=0,
		OK,
		ERROR,
	} HTTPstatus = UNKNOWN; //get and track HTTP status and handle errors
	static unsigned char HTTPheaderBuf[20]; //used to store HTTP headers 
	static unsigned char HTTPheaderBufCnt; //pointer

	static BYTE refreshFeeds=0, HTTPretry=0, URLencode[]="%20";//extra static vars for twitter parser

	BYTE 				i,k;
	WORD				w;
	BYTE				vBuffer[51];
	BYTE				cnt;
	static TICK			Timer;
	static TCP_SOCKET	MySocket = INVALID_SOCKET;
	
	if(frameAdvance==1) refreshFeeds++; //counts the minutes

	switch(twatchState)
	{
		case TWATCH_INIT:
			trendParser.success=0; //clear these flag on first run
			searchParser.success=0;//display IP address and info until valid connection
			twatchState=TWATCH_TRENDS_TCP_START; //start TCP data grabber next cycle
			break;
		case TWATCH_IDLE:	//if this variable set, then start the refresh process		
			if(refreshFeeds>TWATCH_REFRESH_INTERVAL){ //if it has been at least 5 minutes, get new trends and tweet search results
				refreshFeeds=0;
				HTTPretry=0; //reset the number of retries
				twatchState=TWATCH_TRENDS_TCP_START; //start TCP data grabber next cycle
			}
			break;
		case TWATCH_TRENDS_TCP_START:
			//connect to twitter server
			MySocket = TCPOpen((DWORD)&ServerName[0], TCP_OPEN_RAM_HOST, ServerPort, TCP_PURPOSE_GENERIC_TCP_CLIENT);
			
			if(MySocket == INVALID_SOCKET) break; //abort if error, try again next time
			
			trendParser.updatingData=1; //updating data flag (probably not used anywhere)
			displayMode=UPDATE; //next LCD refresh will draw the update screen and then idle
			twatchState=TWATCH_TRENDS_TCP_SOCKET_OBTAINED;
			Timer = TickGet();
			break;

		case TWATCH_TRENDS_TCP_SOCKET_OBTAINED:
			// Wait for the remote server to accept our connection request
			if(!TCPIsConnected(MySocket))
			{
				// Time out if too much time is spent in this state
				if(TickGet()-Timer > 5*TICK_SECOND)
				{
					// Close the socket so it can be used by other modules
					TCPDisconnect(MySocket);
					MySocket = INVALID_SOCKET;
					twatchState--;
				}
				break;
			}

			Timer = TickGet();

			if(TCPIsPutReady(MySocket) < 125u) break; //if socket error, break and wait
	
			//form our trending topics JSON datafeed request
			TCPPutROMString(MySocket, (ROM BYTE*)"GET ");
			TCPPutROMString(MySocket, TrendURL); //use the trend URL
			TCPPutROMString(MySocket, (ROM BYTE*)" HTTP/1.0\r\nHost: ");
			TCPPutString(MySocket, ServerName);
			TCPPutROMString(MySocket, (ROM BYTE*)"\r\nConnection: close\r\n\r\n");

			TCPFlush(MySocket); //send HTTP request to Twitter
			
			//setup/clear the parser struct
			trendParser.bufWritePointer=0;
			trendParser.foundTag=0;
			trendParser.tagCharMatchCnt=0;
			trendParser.tagTotalCnt=0;
			trendParser.bufWritePointer=0;
			searchParser.bufWritePointer=0;//reset the tweet buffer write pointer
			searchParser.term=0; //reset the number of terns in the tweet search parser structure
			for(i=0; i<MAX_TREND_TERMS; i++) searchParser.bufValueEndPosition[i]=0;//reset all buffer positions to 0
			HTTPstatus = UNKNOWN; //reset the http status checker
			HTTPheaderBufCnt=0; //status checker buffer counter

			twatchState=TWATCH_TRENDS_TCP_PROCESS_RESPONSE; //next time process any incoming data
			break;

		case TWATCH_TRENDS_TCP_PROCESS_RESPONSE:

			if(!TCPIsConnected(MySocket)) twatchState = TWATCH_TRENDS_TCP_DISCONNECT; //check if we're still connected // Do not break;  We might still have data in the TCP RX FIFO waiting for us
	
			w = TCPIsGetReady(MySocket);//how many bytes waiting?	
	
			//process the server reply
			i = sizeof(vBuffer)-1;
			vBuffer[i] = '\0';
			while(w){
				if(w < i){
					i = w;
					vBuffer[i] = '\0';
				}
				w -= TCPGetArray(MySocket, vBuffer, i);

				for(cnt=0;cnt<i;cnt++){
					//---------------//
					switch(HTTPstatus){ //check the first few bytes for HTTP/1.1 200 OK
						case UNKNOWN: //cache until a line break, then check header for response code before extracting tags
							HTTPheaderBuf[HTTPheaderBufCnt]=vBuffer[cnt];//add to the headerbuf array
							if(HTTPheaderBufCnt<19) HTTPheaderBufCnt++; //if it won't overrun the array, increment the counter
						
							if(vBuffer[cnt]==0x0d){//if current character is a line break, examine the header for the response code
								//is it HTTP?
								if(HTTPheaderBuf[0]=='H' &&	HTTPheaderBuf[1]=='T' && 
								HTTPheaderBuf[2]=='T' && HTTPheaderBuf[3]=='P' ){						
									//loop past /1.x and space
									HTTPheaderBufCnt=4;
									while(HTTPheaderBuf[HTTPheaderBufCnt]!=' '){
										HTTPheaderBufCnt++;
										if(HTTPheaderBufCnt>19) break; //buffer overrun
									}
									HTTPheaderBufCnt++;
									//is it 200? (should be a ASCII->int loop that gets the actual value for error handling.... check for overrun
									if( (HTTPheaderBufCnt <=17 ) && HTTPheaderBuf[HTTPheaderBufCnt]=='2' &&	HTTPheaderBuf[HTTPheaderBufCnt+1]=='0' && 
										HTTPheaderBuf[HTTPheaderBufCnt+2]=='0'){
										HTTPstatus=OK;//200 OK
									}else{
										HTTPstatus=ERROR; //other status, error
									}
								}
							}
							break;
						case OK: //HTTP is OK, process the byte
							procTrend(vBuffer[cnt]); //json parsing state maching
							break;
						case ERROR://do nothing because we need to clear the buffer
							break;
					}
					//------------------//
				}//for loop
				
				if(twatchState == TWATCH_TRENDS_TCP_PROCESS_RESPONSE) break;
			}//while
	
			break;
	
		case TWATCH_TRENDS_TCP_DISCONNECT:
			TCPDisconnect(MySocket); //close the socket
			MySocket = INVALID_SOCKET;
	
			//did not get valid HTML, retry, got no tags, retry
			if(HTTPstatus!=OK || trendParser.tagTotalCnt==0 ){
				HTTPretry++;
				if(HTTPretry>HTTP_MAX_RETRY){//retry 3 times, then wait a minute....
					twatchState = TWATCH_IDLE;
					LCD_CursorPosition(21); //display waiting error
					LCD_WriteString("*Error, waiting 5min");
					break;
				}
				LCD_CursorPosition(21); //display retry error
				LCD_WriteString("*Error, reconnecting");
				twatchState = TWATCH_TRENDS_TCP_START;
				break;
			}
			HTTPretry=0;
		
			addToTrendBuffer(' ');//add trailing space
			
			trendParser.updatingData=0; //data update complete, clear update flag
			if(trendParser.success==0){ //if this is the first time throuigh, set the success flag
				trendParser.success=1; //set success flag, used to identify the very first successful xfer and clear IP address screen
				LCD_refresh(); //clear IP, show update screen
			}
			displayMode=NEWSCROLL;//start scrolling the terms, tweets will show when available in the parser struct
			twatchState = TWATCH_SEARCH_TCP_START; //will start searching on each term next time. searchParser.term set to 0 above...
			break;

		case TWATCH_SEARCH_TCP_START: //begins searching for recent tweets for each trending term
			
			//don't continue if there's no more term, an error, or overrun
			if(searchParser.term>=trendParser.tagTotalCnt || searchParser.term>=MAX_TREND_TERMS ){//don't continue if there's no more terms left to search
				twatchState = TWATCH_IDLE; //go back to idle
				break;
			}
			
			//skip if 0 length term
			if(trendParser.bufValueStartPosition[searchParser.term]==trendParser.bufValueEndPosition[searchParser.term]) {
				searchParser.term++; //increment to next trend term
				twatchState = TWATCH_SEARCH_TCP_START; //try again with the next trend term
				break;
			}
		
			//connect to twitter
			MySocket = TCPOpen((DWORD)&ServerName[0], TCP_OPEN_RAM_HOST, ServerPort, TCP_PURPOSE_GENERIC_TCP_CLIENT);

			if(MySocket == INVALID_SOCKET) break; //abort on error

			twatchState=TWATCH_SEARCH_TCP_SOCKET_OBTAINED;
			Timer = TickGet();
			break;

		case TWATCH_SEARCH_TCP_SOCKET_OBTAINED:
			// Wait for the remote server to accept our connection request
			if(!TCPIsConnected(MySocket)){
				// Time out if too much time is spent in this state
				if(TickGet()-Timer > 5*TICK_SECOND){
					// Close the socket so it can be used by other modules
					TCPDisconnect(MySocket);
					MySocket = INVALID_SOCKET;
					twatchState--;
					//searchParser.term++; //increment to next trend term, don't get stuck in loop
										//should add retries
				}
				break;
			}

			Timer = TickGet();

			if(TCPIsPutReady(MySocket) < 125u) break; //socket ready for writes?

			
			TCPPutROMString(MySocket, (ROM BYTE*)"GET "); //setup the HTTP GET request 
			TCPPutROMString(MySocket, SearchURL);	//JSON search datafeed URL
			#ifndef JSON_DEBUG
			//add the search term to the JSON search URL. Requires urlencoding
			i=trendParser.bufValueStartPosition[searchParser.term]; //get the starting position of the term in the trend term buffer
			k=trendParser.bufValueEndPosition[searchParser.term]-1; //end position is one less because of auto increment
			//add each character of the trend term to the search URL
			while((i<k) && i<TREND_PARSER_BUFFER ){ //append each byte to the URL until the end position
				//URLencode anything not a-zA-Z0-9 -_.!~*'()
				if(URLencodeChar(trendParser.buf[i], &URLencode[0])==0){
					TCPPut(MySocket, trendParser.buf[i]); //no URLencode required;
				}else{
					TCPPutString(MySocket, URLencode); //use the URLencoded character now in URLencode array
				}
				i++;
			}
			#endif
			//form the rest of the HTTP request
			TCPPutROMString(MySocket, (ROM BYTE*)" HTTP/1.0\r\nHost: ");
			TCPPutString(MySocket, ServerName);
			TCPPutROMString(MySocket, (ROM BYTE*)"\r\nConnection: close\r\n\r\n");

			TCPFlush(MySocket); //send the HTTP request to the Twitter server

			//setup the search parser struct
			searchParser.foundTag=0;
			searchParser.tagCharMatchCnt=0;
			searchParser.tagTotalCnt=0;
			searchParser.escape=0;
			HTTPstatus = UNKNOWN; //clear the HTTP status checker
			HTTPheaderBufCnt=0;

			addToSearchBuffer(0xff); //add beginning block to the text

			twatchState=TWATCH_SEARCH_TCP_PROCESS_RESPONSE;
			break;

		case TWATCH_SEARCH_TCP_PROCESS_RESPONSE:
			if(!TCPIsConnected(MySocket)) twatchState = TWATCH_SEARCH_TCP_DISCONNECT; //check for connection // Do not break;  We might still have data in the TCP RX FIFO waiting for us
	
			w = TCPIsGetReady(MySocket);	//how many bytes waiting?
	
			i = sizeof(vBuffer)-1;
			vBuffer[i] = '\0'; //add trailing 0 to array.

			while(w){ //process server reply
				if(w < i){
					i = w;
					vBuffer[i] = '\0';
				}
				w -= TCPGetArray(MySocket, vBuffer, i);

				for(cnt=0;cnt<i;cnt++){
					//---------------//
					switch(HTTPstatus){
						case UNKNOWN: //check header for response code before extracting tags
							HTTPheaderBuf[HTTPheaderBufCnt]=vBuffer[cnt];//add to the headerbuf array
							if(HTTPheaderBufCnt<19) HTTPheaderBufCnt++; //if it won't overrun the array, increment the counter
						
							if(vBuffer[cnt]==0x0d){//current character is a line break, examine the header for the response code
								//is it HTTP?
								if(HTTPheaderBuf[0]=='H' &&	HTTPheaderBuf[1]=='T' && 
								HTTPheaderBuf[2]=='T' && HTTPheaderBuf[3]=='P' ){						
									//loop past /1.x and space
									HTTPheaderBufCnt=4;
									while(HTTPheaderBuf[HTTPheaderBufCnt]!=' '){
										HTTPheaderBufCnt++;
										if(HTTPheaderBufCnt>19) break; //buffer overrun
									}
									HTTPheaderBufCnt++;
									//is it 200? (should be a ASCII->int loop that gets the actual value for error handling....
									if( ((HTTPheaderBufCnt+2) < 20) && HTTPheaderBuf[HTTPheaderBufCnt]=='2' &&	HTTPheaderBuf[HTTPheaderBufCnt+1]=='0' && 
										HTTPheaderBuf[HTTPheaderBufCnt+2]=='0'){
										HTTPstatus=OK;
									}else{
										HTTPstatus=ERROR;
									}
								}
							}
							break;
						case OK:
							procSearch(vBuffer[cnt]);
							break;
						case ERROR://do nothing because we need to clear the buffer
							break;
					}
					//------------------//
				}//for loop
				
				if(twatchState == TWATCH_SEARCH_TCP_PROCESS_RESPONSE) break;
			}//while
	
			break;
	
		case TWATCH_SEARCH_TCP_DISCONNECT:
			TCPDisconnect(MySocket); //close the socket
			MySocket = INVALID_SOCKET;

			//did not get valid HTML, retry, got no tags, retry once if no tags
			if(HTTPstatus!=OK ){
				HTTPretry++;
				if(HTTPretry>HTTP_MAX_RETRY){//retry, then wait till next time...
					twatchState = TWATCH_IDLE;
					break;
				}
				twatchState = TWATCH_SEARCH_TCP_START;
				break;
			}
			HTTPretry=0; //success, clear number or retries

			//repeat for each trend term
			searchParser.success=1;
			searchParser.term++;
			twatchState = TWATCH_SEARCH_TCP_START;
			break;

	}//switch
	
}//function

//send the first two characters to return the XML decoded character
//returns 0 for error
unsigned char XMLdecode(unsigned char x0, unsigned char x1){
	/*  * &amp; ? & (ampersand, U+0026)
	    * &lt; ? < (less-than sign, U+003C)
	    * &gt; ? > (greater-than sign, U+003E)
	    * &quot; ? " (quotation mark, U+0022)
	    * &apos; ? ' (apostrophe, U+0027)
	*/
	if(x0<='A' && x0>='Z')x0+=0x20; //adjust to lowercase
	switch(x0){
		case 'l':return '<';
		case 'g':return '>';
		case 'q':return '"';
		case 'a':
			if(x1=='m' || x1=='M') return '&';
			return '\'';
		default : return 0;
	}//switch
}

//determines if a character needs to be URLencoded (0=false, 1=true)
//places URLencoded value in *URLencoded array
const unsigned char HEXASCII[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
unsigned char URLencodeChar(unsigned char buf, unsigned char *URLencoded){

	if( (buf>='a' && buf<='z') ||
		(buf>='A' && buf<='Z') ||
		(buf>='0' && buf<='9') ||
		buf=='-' || buf=='_' ||
		buf=='.' || buf=='!' ||
		buf=='~' || buf=='*' ||
		buf=='\'' || buf=='(' ||
		buf==')' ){
		return 0;
	}else{
		//convert byte to hex value
		//add %
		*URLencoded='%';
	    *(URLencoded+1)=HEXASCII[((buf>>4) & 0x0F)];
	    *(URLencoded+2)=HEXASCII[(buf & 0x0F)];
		return 1;
	}
}

//this function redraws the LCD, takes care of scrolling
void LCD_refresh(void){
	static unsigned char searchTerm=0;
	unsigned char i,j,k;
	
	if(trendParser.success==0) return; //don't clear the IP address until we successfully connect to terms feed

	switch(displayMode){
		case IDLE: break;//do nothing
		case UPDATE: //this section draws the basic frame with updating... in the scroll area
			//
			//	Basic screen layout (all lines)
			//
			//clear screen
			LCD_Clear();
			//Write line 1: Trending now:
			LCD_CursorPosition(1);
			LCD_WriteString("Trending now:");
			//write line 3: 
			LCD_CursorPosition(41);
			LCD_WriteString(">Recent tweets");
			//write line 2/4: updating...
			LCD_CursorPosition(21);
			LCD_WriteString("   updating...");
			LCD_CursorPosition(61);
			LCD_WriteString("   updating...");
			searchTerm=0;//reset the local searchTerm index variable that tracks which trend term is presently highlighted
			scrollOffset=0;//clear both scroll offsets
			scrollOffset2=0;
			displayMode=IDLE; //next time, the dislay does nothing
			break;
		case NEWSCROLL: //this draws the highlighted trend term on line three and continues to the scroll function
			//
			//	Update current trend (line 3)
			//
			LCD_CursorPosition(41); //line 3, position 1
			LCD_WriteString("                    ");//clear old term
			LCD_CursorPosition(41);

			//get the start position of the currently highlighted term
			//if it's 0, start at 0, else start at the end of the last term+1
			i=0;
			if(searchTerm!=0) i=trendParser.bufValueEndPosition[(searchTerm-1)];//get start postion (already +1 because of auto increment)
			j=0;
			k=(trendParser.bufValueEndPosition[searchTerm]-1); //save a few operations if we're not optimizing well
			while(i<k){ //repeat untill the end positon //<=
				if(j==20 || i==TREND_PARSER_BUFFER )break; //prevent overruns and line over-writes
				LCD_WriteChar(trendParser.buf[i]); //write the character fromt he buffer to the LCD
				i++;
				j++;
			}
			displayMode=SCROLL; //next time just scroll
		case SCROLL:

			//
			//	Trend scroll	(line 2)
			//
			LCD_CursorPosition(21);//line 2
			scrollPointer=scrollOffset; //adjust the scroll position based on the previous position

			HD44780_RSData(); //setup LCD for rapid data entry function (sets RS high for data input)

			for(i=0; i<20; i++){ //draw 20 characters, offset one from the previous time, loop 0 is we hit the end
				scrollPointer++;
				if(scrollPointer>=trendParser.bufWritePointer || scrollPointer>=TREND_PARSER_BUFFER ) scrollPointer=0;
				//LCD_WriteChar(trendParser.buf[scrollPointer]); //write the character to the LCD
				HD44780_FastText(trendParser.buf[scrollPointer]); //writes without cursor correction, betware!
			}

			scrollOffset++; //next time start one positon further in the text buffer
				if(scrollOffset>=trendParser.bufWritePointer || scrollOffset>= TREND_PARSER_BUFFER){ //reset at the end, prevent overruns
				scrollOffset=0;
			}

			//
			//	Tweet scroll (line 4)
			//
			if(searchParser.term!=0){//if at least one trend term is populated, scroll the stored tweets (search results)

				LCD_CursorPosition(61);//line 4
				scrollPointer2=scrollOffset2; //get the offset from last time
				j=searchParser.bufValueEndPosition[searchTerm];//store this so it's easier to get each time
			
				HD44780_RSData(); //setup LCD for rapid data entry function (sets RS high for data input)

				for(i=0; i<20; i++){ //write 20 characters from the tweet search parser buffer
					scrollPointer2++;
					if((scrollPointer2>j) || (scrollPointer2>= SEARCH_PARSER_BUFFER)){
						if(scrollPointer2<searchParser.bufWritePointer)
							//LCD_WriteChar(searchParser.buf[scrollPointer2]); //display the next character 	HD44780_WriteByte(DATA, c);
							HD44780_FastText(searchParser.buf[scrollPointer2]);
						else
							//LCD_WriteChar(' ');//lead out the end of the line end with blanks, don't do a partial repeat
							HD44780_FastText(' ');
					}else{
						//LCD_WriteChar(searchParser.buf[scrollPointer2]); //display the next character
						HD44780_FastText(searchParser.buf[scrollPointer2]);
					}

				}

				scrollOffset2++;//increment the scroll offset
				//if we're at the end (10 from the end) or overrun, reset the scroll offset and change the highlighted trend term
				if((scrollOffset2+10)>=searchParser.bufValueEndPosition[searchTerm] || scrollOffset2>= SEARCH_PARSER_BUFFER){
					while(1){
						searchTerm++;//next term
						if(searchTerm==searchParser.term || searchTerm>=MAX_TREND_TERMS){
							searchTerm=0; //if more terms than we have fetched, or more than max, go back to 0
							scrollOffset2=0;//start at beginning next time
							break;//get out of this loop if we're starting over!
						}else{
							if(searchParser.bufValueEndPosition[searchTerm]!=0){
								scrollOffset2=(searchParser.bufValueEndPosition[(searchTerm-1)]);//get the end postion of the next tweet section
								scrollOffset2=scrollOffset2-10;//adjust for continous scroll
								break; //if there's no data for this term, skip it
							}
						}
					}
					displayMode=NEWSCROLL; //update the currently highlighted term next time before scrolling
				}
				
			}//scroll line 4

			break;
	}

}


//this function is a state machine that processes the tweet search json one byte at a time. It works ont he global searchParser structure
//it looks for a tag, and then grabs the tag value into a buffer.
//does OK with escape, removes XMLentities from the text completely, this could be improved.
void procSearch(unsigned char inBuf){
	switch(searchParser.foundTag){
		case 0://search for tag
			//compare current byte to next byte in tag
			//if no match, need to check one more time to see if the beginning of a new sequence
			if( (searchParser.tagCharMatchCnt==0) || (inBuf!=jsonSearchTag[searchParser.tagCharMatchCnt]) ){
				searchParser.tagCharMatchCnt=0; //no match, reset
				#if defined(__18CXX)//there's something about the C18 compiler that wants this or the next instruction is always false..
				Nop();
				#endif
				if(inBuf!=jsonSearchTag[0]) break; //no match, break
			}
			searchParser.tagCharMatchCnt++; //match, increment counter
			if(searchParser.tagCharMatchCnt==(sizeof(jsonSearchTag)-1)){//whole tag matches
				searchParser.tagCharMatchCnt=0; //reset the match counter
				searchParser.tagTotalCnt++; //increment the total tag counter
				searchParser.foundTag=1;
				searchParser.xmlencode=0;
				searchParser.escape=0;
				searchParser.UTF=0;	
				addToSearchBuffer(' ');
			}
			break;
		case 1://tag found, get value

			//discard UTF characters, could decode and do a few umlouts and other international characters the LCD can display
			if(searchParser.UTF>0){//ignore UTF8 characters (LCD can't display, PIC char can't handle)
				searchParser.UTF--;
				break;
			}

			if(searchParser.xmlencode==1){ //already saw &, suck down the code
				if(inBuf==';'){//; is end of code, process and clean up
					searchParser.xmlencode=0; //done grabbing encoded character
					inBuf=XMLdecode(searchParser.xmlenchar[0], searchParser.xmlenchar[1]); //decode it, reuse inBuf character
					if(inBuf!=0) addToSearchBuffer(inBuf); //if 0, error, just skip it, else add to searchBuffer
					break; 
				}else{ //if not end of xmlencode, get another character
					if(searchParser.xmlencharcnt<2){ //we only need the first 2 character to identify the ecoding
						searchParser.xmlenchar[searchParser.xmlencharcnt]=inBuf;
					}	
					
					searchParser.xmlencharcnt++;
					if(searchParser.xmlencharcnt>5){//quit if it goes over the max of 5 characters
						searchParser.xmlencode=0; //quit encoding, there was an error, resume normal on next character
					}

					break;	//don't save byte
				}
			}

			if(searchParser.escape==1){  //ESCAPED, check for /\" and UTF8
				searchParser.escape=0; //clear escape
				if(inBuf=='u' || inBuf=='U'){//only escape /\", add a \ back to buffer otherwise
					searchParser.UTF=4;	//next 4 bytes are UFT encoded characters, ignore
					break;
				}else if(inBuf=='n' || inBuf=='N'){ //\n is line break, ignore....
					break;
				}
				//don't need this, escape character is always escaped
				//else if(!(inBuf=='/' || inBuf==0x5c || inBuf=='"')){//only escape /\", add a \ back to buffer otherwise
				//	addToSearchBuffer('|'); //continue as normal, add current byte to searchbuffer at the end...
				//}
			}else{ //NOT ESCAPED, check for end and escape
				if(inBuf=='"'){ //end on " if not escaped
					//add block between entries
					addToSearchBuffer(' ');				
					addToSearchBuffer(0xff);
					searchParser.foundTag=0;
					break;
				}else if(inBuf==0x5c){ //if this is escape char and escape not set, then set escape and break  (0x5c= '\')
					searchParser.escape=1;	
					break;
				}else if(inBuf=='&'){ //begin XML encoded character
					searchParser.xmlencode=1; //set flag
					searchParser.xmlencharcnt=0; //clear encoded character counter
					break; //don't save this character
				}
			}
			
			if(inBuf>=0x20 && inBuf<=0x7e){//only allow standard ASCII characters, otherwise ignore
				if(inBuf==0x5c) inBuf='|'; //LCD has no '\', use |
				if(inBuf=='~') inBuf='-'; //LCD has no "~", use - 
				addToSearchBuffer(inBuf);	//add character to output buffer
			}
			break;
	}
}

//adds a byte to the currently configured searchParser buffer
//checks for buffer overrun
unsigned char addToSearchBuffer(unsigned char c){
	if((searchParser.bufWritePointer < SEARCH_PARSER_BUFFER) && (searchParser.term<10) ){ 
		searchParser.buf[searchParser.bufWritePointer]=c;	//add character to output buffer
		searchParser.bufValueEndPosition[searchParser.term]=searchParser.bufWritePointer; //store the end position of these tweets
		searchParser.bufWritePointer++;//increment the write pointer if it won't overflow
		return 1;
	}
	return 0;
}

//statemachine that processes trend term json one byte at a time
//looks for the tag, then gobbles up the tag value into a buffer
//stores the beginning and end position of the tag so we can append it to the search queries and display it in the tweet search scroll
void procTrend(unsigned char inBuf){
    unsigned char c,d,j,m,k=0;

	switch(trendParser.foundTag){
		case 0://search for tag
			//compare current byte to next byte in tag
			//if no match, need to check one more time to see if the beginning of a new sequence
			if( (trendParser.tagCharMatchCnt==0) || (inBuf!=jsonTrendTag[trendParser.tagCharMatchCnt]) ){
				trendParser.tagCharMatchCnt=0; //no match, reset
				if(inBuf!=jsonTrendTag[0]) break; //no match, break
			}

			trendParser.tagCharMatchCnt++; //match, increment counter

			if(trendParser.tagCharMatchCnt==(sizeof(jsonTrendTag)-1)){//whole tag matches
				trendParser.tagCharMatchCnt=0; //reset the match counter
				trendParser.foundTag=1;
				trendParser.escape=0;
				trendParser.xmlencode=0;
				trendParser.UTF=0;

				//add the ASCII number label for this trend term (1. 2., etc)
				c=trendParser.tagTotalCnt+1; 		
				d=100;
				for(j=0; j<2; j++){
					m=c/d;
					if(k || m){
						addToTrendBuffer(m + '0');	//add character to output buffer
					    c = c - (m*d);
						k=1;
					}
					d/=10;	
				}
				addToTrendBuffer(c + '0');
				addToTrendBuffer('.'); //add the .
	
				trendParser.bufValueStartPosition[trendParser.tagTotalCnt]=trendParser.bufWritePointer;//record the term starting position to use in the search query
			
			}
			break;
		case 1://tag found, get value

			//discard UTF characters, 
			//could decode and do a few umlouts and other international characters the LCD can display
			//HOWEVER it is an entire other encoding system to use the terms to make a search query....
			if(trendParser.UTF>0){//ignore UTF8 characters (LCD can't display, PIC char can't handle)
				trendParser.UTF--;
				break;
			}
/*
			if(trendParser.xmlencode==1){ //already saw &, suck down the code
				if(inBuf==';'){//; is end of code, process and clean up
					trendParser.xmlencode=0; //done grabbing encoded character
					inBuf=XMLdecode(trendParser.xmlenchar[0], trendParser.xmlenchar[1]); //decode it, reuse inBuf character
					if(inBuf!=0) addToTrendBuffer(inBuf); //if 0, error, just skip it, else add to searchBuffer
					break; 
				}else{ //if not end of xmlencode, get another character
					if(trendParser.xmlencharcnt<2){ //we only need the first 2 character to identify the ecoding
						trendParser.xmlenchar[trendParser.xmlencharcnt]=inBuf;
					}	
					
					trendParser.xmlencharcnt++;
					if(trendParser.xmlencharcnt>5){//quit if it goes over the max of 5 characters
						trendParser.xmlencode=0; //quit encoding, there was an error, resume normal on next character
					}

					break;	//don't save byte
				}
			}
*/
			if(trendParser.escape==1){  //ESCAPED, check for /\" 
				trendParser.escape=0; //clear escape
				if(inBuf=='u' || inBuf=='U'){//UTF encoding, ignore this escape
					trendParser.UTF=4; //skip the next four bytes \u0000
					break;
				}else if(inBuf=='n' || inBuf=='N'){ //\n is line break, ignore....
					break;
				}
			}else{ //NOT ESCAPED, check for end and escape
				if(inBuf=='"'){ //end on " if not escaped
					trendParser.foundTag=0;
					addToTrendBuffer(' ');//add a space between trend words
					trendParser.tagTotalCnt++; //increment the total tag counter
					break;
				}else if(inBuf==0x5c){ //if this is escape char and escape not set, then set escape and break  (0x5c= '\')
					trendParser.escape=1;	
					break;
				}/*else if(inBuf=='&'){ //begin XML encoded character
					trendParser.xmlencode=1; //set flag
					trendParser.xmlencharcnt=0; //clear encoded character counter
					break; //don't save this character
				}*/
			}
			
			if(inBuf>=0x20 && inBuf<=0x7e){//only allow standard ASCII characters, otherwise ignore
				if(inBuf==0x5c) inBuf='|'; //LCD has no '\', use |
				if(inBuf=='~') inBuf='-'; //LCD has no "~", use - 
				addToTrendBuffer(inBuf);	//add character to output buffer
			}
			break;
	}
}

//adds a byte to the Trend term Parser buffer
//checks for buffer overrun
unsigned char addToTrendBuffer(unsigned char c){
	if(trendParser.bufWritePointer < TREND_PARSER_BUFFER ){
		trendParser.buf[trendParser.bufWritePointer]=c;	//add character to output buffer
		trendParser.bufWritePointer++;//increment the write pointer if it won't overflow
		if(trendParser.tagTotalCnt<MAX_TREND_TERMS){
			trendParser.bufValueEndPosition[trendParser.tagTotalCnt]=trendParser.bufWritePointer;
		}
		return 1;
	}
	return 0;
}
