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
//notes on twitter:
// requests must be URL encoded (%xx), the hex equivilent
// in data, " and UTF8 characters are escaped with '\'
// in tweet search results, character are HTML encoded and some are UTF8 encoded
// in trend results, characters are UTF8 encoded
#include "TCPIP Stack/TCPIP.h"
#include "tweet_treev1.h"
#include "shiftbrite.h"

//#define DEBUG
#define NAMECHARS 20 //max name length
#define TWEETCHARS 140 //how long can a tweet be?
#define MAX_IDCHARS 20 //length of MAX_ID value buffer
#define HTTP_MAX_RETRY 3 //how many times to retry before delaying
#ifdef DEBUG
	#define REFRESH_INTERVAL 0 //max refresh interval in munites
#else
	#define REFRESH_INTERVAL 30 //max refresh interval in seconds
#endif	
#define HOLD_SECONDS 2	//how long to hold a solid color after fading (if there are more colors to show)

#define PRINTER_WIDTH 32

//static BYTE ServerName[] =	"192.168.1.124"; //twitter address
static BYTE ServerName[] =	"search.twitter.com"; //twitter address
static WORD ServerPort = 80; //http server port number
//#ifdef DEBUG
//	static ROM BYTE SearchURL[] = "/search.json?rpp=50&q=%40dangerousproto&since_id=6856568500"; //tweet search JSON datafeed URL
//#else
	static ROM BYTE SearchURL[] = "/search.json?rpp=11&q=%40dangerousproto&since_id="; //tweet search JSON datafeed
	//static ROM BYTE SearchURL[] = "/search.json?rpp=1&q=%40dangerousproto&since_id=83239303286759424"; //tweet search JSON datafeed URL
//#endif



#define UART_EMPTY() (U1STAbits.UTXBF == 0)

void UARTTX(unsigned char a);
void UART2TX(unsigned char a);

struct _jsonParser{
	unsigned char *searchTag; //pointer to the tag to search for
	unsigned char searchTagLength;//length of the tag
	unsigned char tagCharMatchCnt;//counts number of tag characters that have matched
	unsigned char *valueBuffer; //pointer to array to hold tag value
	unsigned char valueBufferLength; //length of the array
	unsigned char valueEndChar;//how does the value end? (" or ,)
	unsigned char valueBufferCounter; //counts number of tag value bytes stored
	unsigned char foundTag:1;//found tag flag, start grabbing value
	unsigned char escape:1; //tells parser that an escape sequence was detected
	unsigned char xmlencode:1; //xml encoding was detected
	unsigned char xmlencharcnt;//counts characters in xmlencoding
	unsigned char xmlenchar[2]; //holds first two bytes of xmlencoding for use with xmldecode function
	unsigned char UTF; //tells parser UTF8 character detected, ignores UTF bytes
};
static unsigned char nameTag[]="\"from_user\":\"";//JSON tag that identifies ID
static unsigned char textTag[]="\"text\":\"";//JSON tag that identifies tweets
static unsigned char max_idTag[]="\"id\":";//JSON tag that identifies max ID number to search for next time

static unsigned char nameBuf[NAMECHARS+1]; //store user name here
static unsigned char tweetBuf[TWEETCHARS+1];//store tweet text here 
static unsigned char lastidBuf[(MAX_IDCHARS+1)];//20 character array to hold maximum ID for next time, 1 extra char to assure 0 termination
static unsigned char lastidTempBuf[(MAX_IDCHARS+1)];

static struct _jsonParser nameParser;
static struct _jsonParser searchParser;
static struct _jsonParser max_idParser;


#define TWEET_BUFFER	2046
static struct _T{
	unsigned char t[TWEET_BUFFER];
	unsigned int cnt;
	unsigned int read;
	unsigned char lncnt;
}T;

//private functions
unsigned char tagSearch(unsigned char inBuf, struct _jsonParser *P);//statemachine that looks for a given JSON tag and extracts the value to a buffer
unsigned char XMLdecode(unsigned char x0, unsigned char x1); //decode XML entities to ASCII
unsigned char URLencodeChar(unsigned char buf, unsigned char *URLencoded); //URL encode a character, if needed
void processtweet(unsigned char len);
void addColor(unsigned char R, unsigned char G, unsigned char B);
unsigned char hex2bin(unsigned char H, unsigned char L);
void resetJSONparser(struct _jsonParser *P); //clears values in JSON parser struct for a new search
void addValueByte(unsigned char inBuf, struct _jsonParser *P);
unsigned char incrementColor(unsigned char *currentValue, unsigned char destinationValue);
void processname(unsigned char len);
void twatchTasks(void){ //this state machine services the #twatch

   static enum _twitterTCPstate{
		TWITTER_INIT=0,
		HOLD_COLOR,
		TWITTER_IDLE,
		TWITTER_SEARCH_TCP_START,
		TWITTER_SEARCH_TCP_SOCKET_OBTAINED,
		TWITTER_SEARCH_TCP_PROCESS_RESPONSE,
		TWITTER_SEARCH_TCP_DISCONNECT,
	} twitterTCPstate = TWITTER_INIT; //massive twitter parsing state machine

   static enum _HTTPstatus{
		UNKNOWN=0,
		OK,
		ERROR,
	} HTTPstatus = UNKNOWN; //get and track HTTP status and handle errors
	static unsigned char HTTPheaderBuf[20]; //used to store HTTP headers 
	static unsigned char HTTPheaderBufCnt; //pointer

	static BYTE HTTPretry=0, gotID=0;//extra static vars for twitter parser

	unsigned char tcpReadBytes, cnt;
	unsigned int	tcpTotalBytes; //for TCPsocket length, can be >256
	#define TCPBUF_LENGTH 50 //best size
	unsigned char	tcpBuf[TCPBUF_LENGTH];
	static DWORD		Timer;
	static TCP_SOCKET	TCPSocket = INVALID_SOCKET;

	static struct _timekeeper{
		DWORD	ticks;
		unsigned char minutes;
		unsigned char seconds;
		unsigned char runsec; //running seconds counter
	} time;

	//a minutes counter for determining when to refresh the search results
	if(TickGet() - time.ticks >= TICK_SECOND){
		time.ticks = TickGet();
		time.seconds++;
		time.runsec++;
		if(time.seconds>59){
			time.seconds=0;
			time.minutes++;
			if(time.minutes>59){
				time.minutes=0;
			}
		}
	}

	switch(twitterTCPstate){

		case TWITTER_INIT: //setup JSON parser structs on first run
			searchParser.searchTag=textTag;//tag to search for
			searchParser.searchTagLength=(sizeof(textTag)-1);//length of search tag
			searchParser.valueBuffer=tweetBuf; //assign buffer to this struct
			searchParser.valueBufferLength=TWEETCHARS;//buffer length
			searchParser.valueEndChar='"'; //text tag, value ends with "

			nameParser.searchTag=nameTag;//tag to name for
			nameParser.searchTagLength=(sizeof(nameTag)-1);//length of name tag
			nameParser.valueBuffer=nameBuf; //assign buffer to this struct
			nameParser.valueBufferLength=NAMECHARS;//buffer length
			nameParser.valueEndChar='"'; //text tag, value ends with "

			max_idParser.searchTag=max_idTag;//tag to search for
			max_idParser.searchTagLength=(sizeof(max_idTag)-1);//length of search tag
			max_idParser.valueBuffer=lastidTempBuf; //assign buffer to this struct
			max_idParser.valueBufferLength=MAX_IDCHARS;//buffer length
			max_idParser.valueEndChar=','; //text tag, value ends with "
			max_idParser.valueBuffer[20]='\0'; //ensure 0 termination

			//zero the last ID before first call
			lastidBuf[0]='\0';
			lastidBuf[1]='\0';

			//reset printer
			UARTTX(0x1b);
			UARTTX('@');
			//Control parameter command
			UARTTX(0x1b);
			UARTTX(0x37);
			UARTTX(0x07);//max printing dots
			UARTTX(0xFF);//heating time
			UARTTX(0x05);	//heating interval
			twitterTCPstate=TWITTER_SEARCH_TCP_START; //start TCP data grabber next cycle

			break;
		case HOLD_COLOR:
			if(time.runsec<HOLD_SECONDS){
				break;
			}		
			twitterTCPstate=TWITTER_IDLE;	
		case TWITTER_IDLE:	//if this variable set, then start the refresh process		
			//have we played all the buffered text
			if(T.cnt>0 && UART_EMPTY()){//step through text when idle
				
				if(T.t[T.read]==0xFF){//0xFF, end of tweet. reset line counter
					T.lncnt=0;
				}else{
					UARTTX(T.t[T.read]);
					T.lncnt++;

					//send a LF at the end of each X characters
					if(T.lncnt==PRINTER_WIDTH){
						UARTTX(0x0a);
						T.lncnt=0;
						
						twitterTCPstate=HOLD_COLOR;//next time hold solid color
					}
				}

				T.read++;
				//is this the final text?
				T.cnt--;
				if(T.cnt==0){//done with text
					time.runsec=0;//clear running counter for pause
					#ifndef DEBUG
						UARTTX(0x0a);
						UARTTX(0x0a);
						twitterTCPstate=HOLD_COLOR;//next time hold solid color
					#endif
				}

			}else if(time.seconds>=REFRESH_INTERVAL){ //if it has been at least X minutes, get tweet search results
				time.seconds=0;
				HTTPretry=0; //reset the number of retries	
				twitterTCPstate=TWITTER_SEARCH_TCP_START; //start TCP data grabber next cycle
			}			
			break;
		case TWITTER_SEARCH_TCP_START: //begins search for tweets 
			//setup the search parser struct
			resetJSONparser(&nameParser);
			resetJSONparser(&searchParser);
			resetJSONparser(&max_idParser);
			gotID=0; //reset the ID finder
			T.cnt=0; //reset the tweet letter counter	
			T.read=0; //reset the read pointer	
			HTTPstatus = UNKNOWN; //clear the HTTP status checker
			HTTPheaderBufCnt=0;
					
			//connect to twitter
			TCPSocket = TCPOpen((DWORD)&ServerName[0], TCP_OPEN_RAM_HOST, ServerPort, TCP_PURPOSE_GENERIC_TCP_CLIENT);

			if(TCPSocket == INVALID_SOCKET) break; //abort on error

			twitterTCPstate=TWITTER_SEARCH_TCP_SOCKET_OBTAINED;
			Timer = TickGet();
			break;

		case TWITTER_SEARCH_TCP_SOCKET_OBTAINED:
			//wait for server, with timeout
			if(!TCPIsConnected(TCPSocket)){
				if(TickGet()-Timer > 5*TICK_SECOND){
					TCPDisconnect(TCPSocket);
					TCPSocket = INVALID_SOCKET;
					twitterTCPstate--;
				}
				break;
			}

			Timer = TickGet();

			if(TCPIsPutReady(TCPSocket) < 125u) break; //socket ready for writes?
			
			TCPPutROMString(TCPSocket, (ROM BYTE*)"GET "); //setup the HTTP GET request 
			TCPPutROMString(TCPSocket, SearchURL);	//JSON search datafeed URL

			//add the last ID to the JSON search URL. (usually requires urlencoding, but we have numbers only)
			//#ifdef 0
			if(lastidBuf[0]!='\0'){ //don't put 0 length IDs into TCP, kills socket
				TCPPutString(TCPSocket, lastidBuf); //put the string in the TCP buffer
			}
			//#endif

			//form the rest of the HTTP request
			TCPPutROMString(TCPSocket, (ROM BYTE*)" HTTP/1.0\r\nHost: ");
			TCPPutString(TCPSocket, ServerName);
			TCPPutROMString(TCPSocket, (ROM BYTE*)"\r\nConnection: close\r\n\r\n");

			TCPFlush(TCPSocket); //send the HTTP request to the Twitter server

			twitterTCPstate=TWITTER_SEARCH_TCP_PROCESS_RESPONSE;
			break;

		case TWITTER_SEARCH_TCP_PROCESS_RESPONSE:
			if(!TCPIsConnected(TCPSocket)) twitterTCPstate = TWITTER_SEARCH_TCP_DISCONNECT; //check for connection // Do not break;  We might still have data in the TCP RX FIFO waiting for us

			tcpTotalBytes = TCPIsGetReady(TCPSocket);	//how many bytes waiting?
			tcpReadBytes = TCPBUF_LENGTH;

			while(tcpTotalBytes){ //process server reply
				if(tcpTotalBytes < tcpReadBytes){
					tcpReadBytes = tcpTotalBytes;
				}
				tcpTotalBytes -= TCPGetArray(TCPSocket, tcpBuf, tcpReadBytes);

				for(cnt=0;cnt<tcpReadBytes;cnt++){
					UART2TX(tcpBuf[cnt]);
					//---------------//
					switch(HTTPstatus){
						case UNKNOWN: //check header for response code before extracting tags
							HTTPheaderBuf[HTTPheaderBufCnt]=tcpBuf[cnt];//add to the headerbuf array
							if(HTTPheaderBufCnt<19) HTTPheaderBufCnt++; //if it won't overrun the array, increment the counter
						
							if(tcpBuf[cnt]==0x0d){//current character is a line break, examine the header for the response code
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
							if(tagSearch(tcpBuf[cnt], &nameParser)){//process the tweet for color data
								processname(nameParser.valueBufferCounter);
							}
							if(tagSearch(tcpBuf[cnt], &searchParser)){//process the tweet for color data
								processtweet(searchParser.valueBufferCounter);
							}
							if(gotID==0){//get only the first (highest) tweet ID to append to the URL next time
								if(tagSearch(tcpBuf[cnt], &max_idParser)){
									addValueByte('\0', &max_idParser);
									for(gotID=0; gotID<21; gotID++){
										lastidBuf[gotID]=lastidTempBuf[gotID];//only overwrite if comlete
									}
									gotID=1;
								}
							}
							break;
						case ERROR://do nothing because we need to clear the buffer
							break;
					}
					//------------------//
				}//for loop
				
				if(twitterTCPstate == TWITTER_SEARCH_TCP_PROCESS_RESPONSE) break;
			}//while
	
			break;
	
		case TWITTER_SEARCH_TCP_DISCONNECT:
			TCPDisconnect(TCPSocket); //close the socket
			TCPSocket = INVALID_SOCKET;

			//did not get valid HTML, retry, got no tags, retry once if no tags
			if(HTTPstatus!=OK ){
				HTTPretry++;
				if(HTTPretry>(HTTP_MAX_RETRY-1)){//retry, then wait till next time...
					twitterTCPstate = TWITTER_IDLE;
					time.seconds=0;					break;
				}
				twitterTCPstate = TWITTER_SEARCH_TCP_START;
				break;
			}
			HTTPretry=0; //success, clear number or retries

			twitterTCPstate = TWITTER_IDLE;
			break;

	}//switch
	
}//function

//this function is a state machine that processes the tweet search json one byte at a time. It works ont he global searchParser structure
//it looks for a tag, and then grabs the tag value into a buffer.
//does OK with escape, removes XMLentities from the text completely, this could be improved.
unsigned char tagSearch(unsigned char inBuf, struct _jsonParser *P ){

#define SEARCHING_FOR_TAG 	0
#define GRABBING_TAG		1

	switch(P->foundTag){
		case SEARCHING_FOR_TAG://search for tag
			//compare current byte to next byte in tag
			//if no match, need to check one more time to see if the beginning of a new sequence
			if( (P->tagCharMatchCnt==0) || (inBuf!=P->searchTag[P->tagCharMatchCnt]) ){
				P->tagCharMatchCnt=0; //no match, reset
				if(inBuf!=P->searchTag[0]) break; //no match, break
			}
			P->tagCharMatchCnt++; //match, increment counter
			if(P->tagCharMatchCnt==P->searchTagLength){//whole tag matches
				P->tagCharMatchCnt=0; //reset the match counter
				P->foundTag=GRABBING_TAG;
				P->xmlencode=0;
				P->escape=0;
				P->UTF=0;	
				P->valueBufferCounter=0;
			}
			break;
		case GRABBING_TAG://tag found, get value

			//discard UTF characters, could decode and do a few umlouts and other international characters the LCD can display
			if(P->UTF>0){//ignore UTF8 characters (LCD can't display, PIC char can't handle)
				P->UTF--;
				break;
			}

			if(P->xmlencode==1){ //already saw &, suck down the code
				if(inBuf==';'){//; is end of code, process and clean up
					P->xmlencode=0; //done grabbing encoded character
					inBuf=XMLdecode(P->xmlenchar[0], P->xmlenchar[1]); //decode it, reuse inBuf character
					if(inBuf!=0){//if 0, error, just skip it, else add to valueBuffer
						addValueByte(inBuf, P);//add character to the value buffer
 					}
					break; 
				}else{ //if not end of xmlencode, get another character
					if(P->xmlencharcnt<2){ //we only need the first 2 character to identify the ecoding
						P->xmlenchar[P->xmlencharcnt]=inBuf;
					}	
					
					P->xmlencharcnt++;
					if(P->xmlencharcnt>5){//quit if it goes over the max of 5 characters
						P->xmlencode=0; //quit encoding, there was an error, resume normal on next character
					}

					break;	//don't save byte
				}
			}

			if(P->escape==1){  //ESCAPED, check for /\" and UTF8
				P->escape=0; //clear escape
				if(inBuf=='u' || inBuf=='U'){//only escape /\", add a \ back to buffer otherwise
					P->UTF=4;	//next 4 bytes are UFT encoded characters, ignore
					break;
				}else if(inBuf=='n' || inBuf=='N'){ //\n is line break, ignore....
					break;
				}
			}else{ //NOT ESCAPED, check for end and escape
				if(inBuf==P->valueEndChar){ //end on value end character
					P->foundTag=SEARCHING_FOR_TAG;
					return 1; //tag complete
					//break;
				}else if(inBuf==0x5c){ //if this is escape char and escape not set, then set escape and break  (0x5c= '\')
					P->escape=1;	
					break;
				}else if(inBuf=='&'){ //begin XML encoded character
					P->xmlencode=1; //set flag
					P->xmlencharcnt=0; //clear encoded character counter
					break; //don't save this character
				}
			}
			
			if(inBuf>=0x20 && inBuf<=0x7e){//only allow standard ASCII characters, otherwise ignore
				addValueByte(inBuf, P);//add character to the value buffer
			}
			break;
	}
	return 0; //tag not complete
}

void addValueByte(unsigned char inBuf, struct _jsonParser *P){
	if(P->valueBufferCounter<P->valueBufferLength){
		P->valueBuffer[P->valueBufferCounter]=(inBuf);	//add character to output buffer
		P->valueBufferCounter++;//increment if won't overrun
	}
}

//suck the individual tweet into a big array
void processtweet(unsigned char len){
unsigned char i; //tweet is max 144 (we hope, lol)
	for(i=0; i<len; i++){
		if(T.cnt==TWEET_BUFFER)break;
		T.t[T.cnt]=searchParser.valueBuffer[i];
		T.cnt++;
	}
	if((T.cnt+7)==TWEET_BUFFER)return;
	for(i=0; i<3; i++){
		T.t[T.cnt]='.';
		T.cnt++;
	}
	T.t[T.cnt]=0x0a;
	T.cnt++;
	T.t[T.cnt]=0x0a;
	T.cnt++;
	T.t[T.cnt]=0xFF;
	T.cnt++;

}

void processname(unsigned char len){
unsigned char i; //tweet is max 144 (we hope, lol)
	T.t[T.cnt]=0x1d;
	T.cnt++;
	T.t[T.cnt]='B';
	T.cnt++;
	T.t[T.cnt]=0b00000001;
	T.cnt++;
	for(i=0; i<len; i++){
		if(T.cnt==TWEET_BUFFER)break;
		T.t[T.cnt]=nameParser.valueBuffer[i];
		T.cnt++;
	}
	if((T.cnt+7)==TWEET_BUFFER)return;
	T.t[T.cnt]=':';
	T.cnt++;
	T.t[T.cnt]=0x1d;
	T.cnt++;
	T.t[T.cnt]='B';
	T.cnt++;
	T.t[T.cnt]=0x00;
	T.cnt++;
	T.t[T.cnt]=0x0a;//line feed
	T.cnt++;
	T.t[T.cnt]=0xFF;//reset counter
	T.cnt++;

}

void resetJSONparser(struct _jsonParser *P){
	P->foundTag=0;
	P->tagCharMatchCnt=0;
	P->escape=0;
}

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

unsigned char hex2bin(unsigned char H, unsigned char L){
	unsigned char value;

	//30-39 a-f41-46, A-F61-66 
	if(H<0x40){
		value=(H-0x30);
	}else if (H<0x47){
		value=(H-0x37);
	}else{
		value=(H-0x57);
	}
	value*=0x10;
	if(L<0x40){
		value+=(L-0x30);
	}else if (L<0x47){
		value+=(L-0x37);
	}else{
		value+=(L-0x57);
	}
	return value;
}


void UARTTX(unsigned char a){
	while(!(U1STAbits.UTXBF == 0));
	U1TXREG=a;
}

void UART2TX(unsigned char a){
	while(!(U2STAbits.UTXBF == 0));
	U2TXREG=a;
}

/*
void savesettings(unsigned char R,unsigned char G,unsigned char B ){
	unsigned char xcrc;
	//disable write latch
	CS=1;
	CS=0;
	SPI(0x06);
	CS=1;

	//save config settings starting at address 0
	CS=0;
	SPI(2);
	SPI(0);
	SPI(0);
	SPI(0);

	//save last color
	xcrc=0;
	SPI(R);
	xcrc^=R;
	SPI(G);
	xcrc^=G;
	SPI(B);
	xcrc^=B;
	//save simple check
	SPI(xcrc);

	//save lastidBuf
	xcrc=0;
	for(i=0; i<20; i++){
		SPI(lastidBuf[i]);
		xcrc^=lastidBuf[i];
	}
	//save simple check
	SPI(xcrc);
	
	CS=1;
}

void readsettings(unsigned char R,unsigned char G,unsigned char B ){
	unsigned char xcrc;

	//read config settings starting at address 0
	CS=0;
	SPI(3);
	SPI(0);
	SPI(0);
	SPI(0);

	//get last color
	xcrc=0;
	SPI(R);
	xcrc^=R;
	SPI(G);
	xcrc^=G;
	SPI(B);
	xcrc^=B;
	//save simple check
	SPI(xcrc);

	//save lastidBuf
	xcrc=0;
	for(i=0; i<20; i++){
		SPI(lastidBuf[i]);
		xcrc^=lastidBuf[i];
	}
	//save simple check
	SPI(xcrc);
	
	CS=1;
}


*/


