
int basquiet;		//surpress output from the protos

#include "basic.h"


// for compiler hapiness
#define bpBR	bpWline("");
#define bpSP	UART1TX(' ');
extern int getnumber(int def, int max, int x);
extern void bpWstring(char *s);
extern void bpWinthex(unsigned int c);
extern void bpWstring(char *s);
extern void bpWline(char *s);
extern void UART1TX(char c);
extern void bpDelayUS(const unsigned char delay);



int vars[26];					// var a-z
int stack[GOSUBMAX];				// max 5 gosubs
struct forloop forloops[FORMAX];			// max 2 nested forloop
int pc;							//programcounter
int fors;						// current for
int gosubs;						// current gosubs
int datapos;					// read pointer.


unsigned char pgmspace[PGMSIZE]={	// 1kb basic memory

/*

100 rem basictest
110 let a=10
120 for b=1 to 20
130 print "A=":a:"B=":b;
140 next b
200 input "enter c",c
210 gosub 1000
220 if c=20 then print "c=20!!";
230 goto 100
1000 print "C=":c;
1010 return

*/

TOK_LEN+ 1, 0,  10, TOK_START,
TOK_LEN+ 1, 0,  11, TOK_STARTR,
TOK_LEN+ 1, 0,  12, TOK_STOP,
TOK_LEN+ 1, 0,  13, TOK_STOPR,

TOK_LEN+ 3, 0,  20, TOK_AUX, ',', '0',
TOK_LEN+ 3, 0,  21, TOK_AUX, ',', '1',
TOK_LEN+ 4, 0,  22, TOK_LET, 'C', '=', '0',
TOK_LEN+ 3, 0,  23, TOK_AUX, ',', 'C',
TOK_LEN+ 4, 0,  24, TOK_LET, 'C', '=', '1',
TOK_LEN+ 3, 0,  25, TOK_AUX, ',', 'C',
TOK_LEN+ 4, 0,  26, TOK_LET, 'C', '=', TOK_AUX,
TOK_LEN+ 5, 0,  27, TOK_GOSUB, '1', '0', '0', '0',

TOK_LEN+ 3, 0,  30, TOK_CLK, ',', '0',
TOK_LEN+ 3, 0,  31, TOK_CLK, ',', '1',
TOK_LEN+ 3, 0,  32, TOK_CLK, ',', '2',

TOK_LEN+ 3, 0,  35, TOK_DAT, ',', '0',
TOK_LEN+ 3, 0,  36, TOK_DAT, ',', '1',
TOK_LEN+ 4, 0,  37, TOK_LET, 'C', '=', TOK_DAT,
TOK_LEN+ 5, 0,  38, TOK_GOSUB, '1', '0', '0', '0',

TOK_LEN+ 3, 0,  40, TOK_PSU, ',', '0',
TOK_LEN+ 3, 0,  41, TOK_PSU, ',', '1',
TOK_LEN+ 3, 0,  42, TOK_PRINT, TOK_PSU,

TOK_LEN+10, 0, 100, TOK_REM, 'b', 'a', 's', 'i', 'c', 't', 'e', 's', 't',
TOK_LEN+ 7, 0, 110, TOK_LET, 'A', '=', 'C', '+', '1', '6',
TOK_LEN+ 6, 0, 120, TOK_FOR, 'B', '=', '1', TOK_TO, '2',
TOK_LEN+ 6, 0, 125, TOK_FOR, 'D', '=', '0', TOK_TO, '1',
TOK_LEN+23, 0, 130, TOK_PRINT, '\"', 'A', '=', '\"', ';', 'A', ';', '\"', ' ', 'B', '=', '\"', ';', 'B', ';', '\"', ' ', 'D', '=', '\"', ';', 'D', //';',
TOK_LEN+ 2, 0, 135, TOK_NEXT, 'D',
TOK_LEN+ 2, 0, 140, TOK_NEXT, 'B',
TOK_LEN+12, 0, 200, TOK_INPUT, '\"', 'E', 'n', 't', 'e', 'r', ' ', 'C', '\"', ',','C',
TOK_LEN+ 2, 0, 201, TOK_READ, 'C',
TOK_LEN+ 5, 0, 202, TOK_GOSUB, '1', '0', '0', '0',
TOK_LEN+ 2, 0, 203, TOK_READ, 'C',
TOK_LEN+ 5, 0, 204, TOK_GOSUB, '1', '0', '0', '0',
TOK_LEN+ 2, 0, 205, TOK_READ, 'C',
TOK_LEN+ 5, 0, 206, TOK_GOSUB, '1', '0', '0', '0',
TOK_LEN+ 2, 0, 207, TOK_READ, 'C',
TOK_LEN+ 5, 0, 210, TOK_GOSUB, '1', '0', '0', '0',
TOK_LEN+26, 0, 220, TOK_IF, 'C', '=', '2', '0', TOK_THEN, TOK_PRINT, '\"', 'C', '=', '2', '0', '!', '!', '\"', ';', TOK_ELSE, TOK_PRINT, '\"', 'C', '!', '=', '2', '0', '"', ';',
//TOK_LEN+ 4, 0, 230, TOK_GOTO, '1', '0', '0',
TOK_LEN+ 1, 0, 230, TOK_END,
TOK_LEN+ 7, 3, 232, TOK_PRINT, '\"', 'C', '=', '\"', ';', 'C',
TOK_LEN+ 1, 3, 242, TOK_RETURN,
TOK_LEN+ 6, 7, 208, TOK_DATA, '1', ',', '2', ',', '3',
TOK_LEN+ 2, 7, 218, TOK_DATA, '4',
TOK_LEN+ 1, 255, 255, TOK_END,
0x00,0x00,
};


// testsubbs:
// dummy protocol :)
void protostart(void)
{	bpWline("START");
}
void protostartr(void)
{	bpWline("START");
}
void protostop(void)
{	bpWline("STOP");
}
void protostopr(void)
{	bpWline("STOPR");
}
void protoauxl(void)
{	bpWline("AUXLOW");
}
void protoauxh(void)
{	bpWline("AUXHI");
}
int protogetaux(void)
{	return 1;
}
int protogetdat(void)
{	return 1;
}
void protopsuon(void)
{	bpWline("PSUON");
}
void protopsuoff(void)
{	bpWline("PSUOFF");
}
void protodatl(void)
{	bpWline("DATLOW");
}
void protodath(void)
{	bpWline("DATHI");
}
void protoclkl(void)
{	bpWline("CLKLOW");
}
void protoclkh(void)
{	bpWline("CLKHI");
}
void protoclk(void)
{	bpWline("CLKPULSE");
}
void protopullupon(void)
{	bpWline("PULLUPON");
}
void protopullupoff(void)
{	bpWline("PULLUOPOFF");
}
void protowrite(unsigned int c)
{	bpWstring("WRITE: ");
	bpWinthex(c);
	bpSP;
}
unsigned int protoread(void)
{	bpWline("READ");
	return 0xAA;
}
unsigned int protobitr(void)
{	bpWline("BITR");
	return 1;
}

// end of testsubs


// basicinterpreter starts here

void handleelse(void)
{	if(pgmspace[pc]==TOK_ELSE)
	{	pc++;
		while(pgmspace[pc]<=TOK_LEN)
		{	pc++;
		}
	}
}

unsigned int searchlineno(unsigned int line)
{	int i;
	int len;
	int lineno;

	i=0;

	//bpWinthex(line);
	//UART1TX('?');

	while(1)
	{	len=pgmspace[i]-TOK_LEN;
		lineno=(pgmspace[i+1]<<8)+pgmspace[i+2];
		if(line==lineno)
		{	return i;
		}
		if(i>PGMSIZE)
		{	return -1;
		}
		i+=len+3;
	}
	return 0;
}

int getnumvar(void)
{	int temp;
	temp=0;

	if((pgmspace[pc]>='A')&&(pgmspace[pc]<='Z'))
	{	//bpWstring("var ");
		//bpWhex(pgmspace[pc]);
		//bpSP;
		return vars[pgmspace[pc++]-'A'];				//increment pc
	}
	else if(pgmspace[pc]>TOKENS)			// looks for tokens like aux, clk and dat
	{	switch(pgmspace[pc++])					// increment pc
		{	case TOK_RECEIVE:	temp=protoread();
							//temp=protos[bpConfig.busMode].protocol_read();
							break;
			case TOK_AUX:	temp=protogetaux();
							//temp=
							break;
			case TOK_DAT:	temp=protogetdat();
							//temp=protos[bpConfig.busMode].protocol_dats();
							break;
			case TOK_BITREAD:	temp=protobitr();
							//temp=protos[bpConfig.busMode].protocol_bitr();
							break;
			case TOK_PSU:	//temp=modeConfig.vregEN;
							break;
			case TOK_PULLUP:	//temp=modeConfig.pullupEN;
							break;
#if defined( BUSPIRATEV1A) || defined (BUSPIRATEV2)
			case TOK_ADC:	//temp=bpADC(12);
							break;
#endif
			default:		temp=0;
		}
	}
	else
	{	while((pgmspace[pc]>='0')&&(pgmspace[pc]<='9'))
		{	temp*=10;
			temp+=pgmspace[pc]-'0';
			pc++;
		}
	}
	//bpWstring("int ");
	//bpWinthex(temp);
	//bpSP;
	return temp;
}

int assign(void)
{	unsigned int temp;
	
	//pc+=2;
	temp=getnumvar();

	if((pgmspace[pc]!='-')&&(pgmspace[pc]!='+')&&(pgmspace[pc]!='*')&&(pgmspace[pc]!='/'))
	{	return temp;
	}
	else									// assume operand
	{	//bpWstring("op ");
		//UART1TX(pgmspace[pc]);
		//bpSP;
		switch(pgmspace[pc++])
		{	case '-': 	//UART1TX('-');
						temp-=getnumvar();
						break;
			case '+':	//UART1TX('+');
						temp+=getnumvar();
						break;
			case '*':	//UART1TX('*');
						temp*=getnumvar();
						break;
			case '/':	//UART1TX('/');
						temp/=getnumvar();
						break;
			default:	break;
		}
		return temp;
	}			
}

int evaluate(void)
{	int left;
	int right;
	int i;

	char op[2];		// operand

	left=vars[pgmspace[pc++]-'A'];

	i=0;

	while((!((pgmspace[pc]>='A')&&(pgmspace[pc]<='Z')))&&(!((pgmspace[pc]>='0')&&(pgmspace[pc]<='9'))))
	{	op[i]=pgmspace[pc++];
		i++;
	}

	right=assign();

	//bpSP; 
	//bpWinthex(left); bpSP;
	//UART1TX(op[0]); 
	//UART1TX(op[1]); bpSP; 
	//bpWinthex(right); bpSP; 

	
	switch (op[0])
	{	case '=':	return (left==right);
		case '>':	if(op[1]=='=') 
					{	return (left>=right);
					}
					else
					{	return (left>right);
					}
		case '<':	if(op[1]=='=') 
					{	return (left<=right);
					}
					else
					{	return (left<right);
					}
		case '!':	if(op[1]=='=')	
					{	return (left!=right);
					}
		default:	return 0;				
	}
	return 0;
}

void interpreter(void)
{	int len;
	unsigned int lineno;
	int i;
//	int pc; 			//became global
	int stop;
	int pcupdated;
	int ifstat;

	int temp;

	// init
	pc=0;
	stop=0;
	pcupdated=0;
	ifstat=0;
	fors=0;
	gosubs=0;
	datapos=0;
	basquiet=1;				// turn echoing off

	for(i=0; i<26; i++) vars[i]=0;

	while(!stop)
	{	if(!ifstat)
		{	if(pgmspace[pc]<TOK_LEN)
			{	stop=NOLEN;
				break;
			}

			len=pgmspace[pc]-TOK_LEN;
			lineno=((pgmspace[pc+1]<<8)|pgmspace[pc+2]);

			//bpBR;
			//bpWinthex(pc);
			//bpSP;
			//bpWinthex(lineno);
			//bpSP;
			//bpWhex(len);
			//bpSP;
		}

		ifstat=0;

		switch(pgmspace[pc+3])					// first token
		{	case TOK_LET:	//bpWstring(STAT_LET);
							//bpSP;
							//for(i=4; i<len+3; i++)
							//{	UART1TX(pgmspace[pc+i]);
							//}

							pcupdated=1;
							pc+=6;		// 4(len lineno lineno token) +2 ("A=")

							vars[pgmspace[pc-2]-0x41]=assign();
							handleelse();
							
							//bpBR;
							break;
			case TOK_IF:	//bpWstring(STAT_IF);
							//bpSP;
							//i=4;
							//while(pgmspace[pc+i]<0x80)
							//{	UART1TX(pgmspace[pc+i]);		// print if condition
							//	i++;
							//}
							//bpSP;
							//if(pgmspace[pc+i]==TOK_THEN)
							//{	bpWstring(STAT_THEN);
							//	bpSP;
							//	i++;
							//	while((pgmspace[pc+i]!=TOK_ELSE)&&(i<len))
							//	{	UART1TX(pgmspace[pc+i]);
							//		i++;
							//	}
							//}
							//if(pgmspace[pc+i]==TOK_ELSE)
							//{	bpWstring(STAT_ELSE);
							//	bpSP;
							//	i++;
							//	for( ; i<len+3; i++)
							//	{	UART1TX(pgmspace[pc+i]);
							//	} 
							//}

							pcupdated=1;
							pc+=4;
		
							temp=pc;
		
							if(evaluate())
							{	//bpWline("TRUE");	// execute statement then
								if(pgmspace[pc++]==TOK_THEN)
								{	//bpWstring ("THEN");
									ifstat=1;
									pc-=3;					// simplest way (for now)
								}
							}
							else
							{	//bpWline("FALSE");
								while((pgmspace[pc]!=TOK_ELSE)&&(pgmspace[pc]<=TOK_LEN))
								{	pc++;
								}
								if(pgmspace[pc++]==TOK_ELSE)
								{	//bpWstring ("ELSE");
									ifstat=1;
									pc-=3;					// simplest way (for now)
								}
							}
	
							//bpWstring(" endif ");
							break;
			case TOK_GOTO:	//bpWstring(STAT_GOTO);
							//bpSP;
							//for(i=4; i<len+3; i++)
							//{	UART1TX(pgmspace[pc+i]);
							//} 

							pcupdated=1;
							pc+=4;
	
							temp=searchlineno(assign());
							//bpSP; bpWinthex(temp); bpSP;
							if(temp!=-1)
							{	pc=temp;
							}
							else
							{	stop=GOTOERROR;
							}


							break;
			case TOK_GOSUB:	//bpWstring(STAT_GOSUB);
							//bpSP;
							//for(i=4; i<len+3; i++)
							//{	UART1TX(pgmspace[pc+i]);
							//} 

							pcupdated=1;
							pc+=4;
	
							if(gosubs<GOSUBMAX)
							{	stack[gosubs]=pc+len-1;
								gosubs++;
								temp=searchlineno(assign());
								//bpSP; bpWinthex(temp); bpSP;
								if(temp!=-1)
								{	pc=temp;
								}
								else
								{	stop=GOTOERROR;
								}
							}
							else
							{	stop=STACKERROR;
							}
							//bpBR;

							break;
			case TOK_RETURN:	//bpWstring(STAT_RETURN);
						
							pcupdated=1;
							if(gosubs)
							{	pc=stack[--gosubs];
							}
							else
							{	stop=RETURNERROR; 
							}
							//bpBR
							break;
			case TOK_REM:	//bpWstring(STAT_REM);
							//bpSP;
							//for(i=4; i<len+3; i++)
							//{	UART1TX(pgmspace[pc+i]);
							//} 
							//bpBR;

							pcupdated=1;
							pc+=len+3;
							break;
			case TOK_PRINT:	//bpWstring(STAT_PRINT);
							//bpSP;
							//for(i=4; i<len+3; i++)
							//{	UART1TX(pgmspace[pc+i]);
							//} 

							pcupdated=1;
							basquiet=0;		// we want to print
							pc+=4;
							while(pgmspace[pc]<TOKENS)
							{	if(pgmspace[pc]=='\"')						// is it a string?
								{	pc++;
									while(pgmspace[pc]!='\"')
									{	UART1TX(pgmspace[pc++]);
									}
									pc++;
								}
								else if((pgmspace[pc]>='A')&&(pgmspace[pc]<='Z'))	//  var
								{	bpWinthex(assign());
								}
								else if(pgmspace[pc]==';')						// spacer
								{	pc++;
								}
							}
							if(pgmspace[pc-1]!=';') bpBR;
							handleelse();
							basquiet=1;		// quietmode
							break;
			case TOK_INPUT:	//bpWstring(STAT_INPUT);
							//bpSP;
							//for(i=4; i<len+3; i++)
							//{	UART1TX(pgmspace[pc+i]);
							//} 

							pcupdated=1;
							basquiet=0;		// print prompt
							pc+=4;
	
							if(pgmspace[pc]=='\"')						// is it a string?
							{	pc++;
								while(pgmspace[pc]!='\"')
								{	UART1TX(pgmspace[pc++]);
								}
								pc++;
							}
							if(pgmspace[pc]==',')
							{	pc++;
							}
							else
							{	stop=SYNTAXERROR;
							}
	
							vars[pgmspace[pc]-'A']=getnumber(0, 0x7FFF, 0);
							pc++;
							handleelse();
							basquiet=1;
							break;
			case TOK_FOR:	//bpWstring(STAT_FOR);
							//bpSP;
							//i=0;
							//while(pgmspace[pc+4+i]<0x80)
							//{	UART1TX(pgmspace[pc+4+i]);		// print for condition
							//	i++;
							//}
							//bpSP;
							//if(pgmspace[pc+4+i]==TOK_TO)
							//{	bpWstring(STAT_TO);
							//	bpSP;
							//}
							//i++;
							//while(len>(1+i))
							//{	UART1TX(pgmspace[pc+4+i]);		// print to
							//	i++;
							//}

							pcupdated=1;
							pc+=4;
							if(fors<FORMAX)
							{	fors++;	
							}
							else
							{	stop=FORERROR;				// to many nested fors
							}
							forloops[fors].var=pgmspace[pc++]-'A';
	
							if(pgmspace[pc]=='=')
							{	pc++;
								vars[forloops[fors].var]=assign();
							}
							if(pgmspace[pc++]==TOK_TO)
							{	//bpWstring(STAT_TO);
								forloops[fors].to=assign();
							}
							if(pgmspace[pc]>=TOK_LEN)
							{	forloops[fors].forstart=pc;
							}
							//bpSP;
							//bpWinthex(forloops[fors].var); bpSP;
							//bpWinthex(forloops[fors].to); bpSP;
							//bpWinthex(forloops[fors].forstart); bpSP;
							//bpBR;

							handleelse();

							break;
			case TOK_NEXT:	//bpWstring(STAT_NEXT);
							//bpSP;
							//for(i=4; i<len+3; i++)
							//{	UART1TX(pgmspace[pc+i]);
							//}

							pcupdated=1;
							pc+=4;
	
							temp=pgmspace[pc++]-'A';
							stop=NEXTERROR;
	
							for(i=0; i<=fors; i++)
							{	if(forloops[i].var==temp)
								{	if(vars[temp]<forloops[i].to)
									{	vars[temp]++;
										pc=forloops[i].forstart;
									}
									else
									{	fors--;
									}
									stop=0;
								}
							}
							handleelse();
							break;
			case TOK_READ:	pcupdated=1;
							pc+=4;

							if(datapos==0)
							{	i=0;
								while((pgmspace[i+3]!=TOK_DATA)&&(pgmspace[i]!=0x00))
								{	i+=(pgmspace[i]-TOK_LEN)+3;
									//bpWinthex(i); bpSP;
								}
								//bpWinthex(pgmspace[i]);
								if(pgmspace[i])
								{	datapos=i+4;
								}
								else
								{	stop=DATAERROR;
								}
							}
							//bpWstring("datapos ");
							//bpWinthex(datapos); bpSP; 
							//UART1TX(pgmspace[datapos]); bpSP;
							temp=pc;
							pc=datapos;
							vars[pgmspace[temp]-'A']=getnumvar();
							datapos=pc;
							pc=temp+1;
	
							if(pgmspace[datapos]==',')
							{	datapos++;
							}
							if(pgmspace[datapos]>TOK_LEN)
							{	if(pgmspace[datapos+3]!=TOK_DATA)
								{	datapos=0;							// rolover
								}
								else
								{	datapos+=4;
								}
							}						
	
							handleelse();

							break;
			case TOK_DATA:	pcupdated=1;
							pc+=len+3;
							break;


// buspirate subs

			case TOK_START:	pcupdated=1;
							pc+=4;
		
							//protos[bpConfig.busMode].protocol_start();
							protostart();
							break;
			case TOK_STARTR:	pcupdated=1;
							pc+=4;
		
							//protos[bpConfig.busMode].protocol_startR();
							protostartr();
							break;
			case TOK_STOP:	pcupdated=1;
							pc+=4;
		
							//protos[bpConfig.busMode].protocol_stop();
							protostop();
							break;
			case TOK_STOPR:	pcupdated=1;
							pc+=4;
		
							//protos[bpConfig.busMode].protocol_stopR();
							protostopr();
							break;
			case TOK_SEND:	pcupdated=1;
							pc+=4;
							if(pgmspace[pc]==',')
							{	pc++;
							}
							else
							{	stop=SYNTAXERROR;
							}
							protowrite(getnumvar());
							//protos[bpConfig.busMode].protocol_send(sendw);
							break;
			case TOK_AUX:	pcupdated=1;
							pc+=4;
							if(pgmspace[pc]==',')
							{	pc++;
							}
							else
							{	stop=SYNTAXERROR;
							}

							if(getnumvar())
							{	protoauxh();
								//bpAuxHigh();
							}
							else
							{	protoauxl();
								//bpAuxLow();
							}
							
							break;
			case TOK_PSU:	pcupdated=1;
							pc+=4;
							if(pgmspace[pc]==',')
							{	pc++;
							}
							else
							{	stop=SYNTAXERROR;
							}

							if(getnumvar())
							{	protopsuon();
								//BP_VREG_ON();
								//modeConfig.vregEN=1;
							}
							else
							{	protopsuoff();
								//BP_VREG_OFF();
								//modeConfig.vregEN=0;
							}
						
							break;
			case TOK_DAT:	pcupdated=1;
							pc+=4;
							if(pgmspace[pc]==',')
							{	pc++;
							}
							else
							{	stop=SYNTAXERROR;
							}

							if(getnumvar())
							{	protodath();
								//protos[bpConfig.busMode].protocol_dath();
							}
							else
							{	protodatl();
								//protos[bpConfig.busMode].protocol_datl();
							}
						
							break;
			case TOK_CLK:	pcupdated=1;
							pc+=4;
							if(pgmspace[pc]==',')
							{	pc++;
							}
							else
							{	stop=SYNTAXERROR;
							}

							switch(getnumvar())
							{	case 0:	protoclkl();
										//protos[bpConfig.busMode].protocol_clkl();
										break;
								case 1:	protoclkh();
										//protos[bpConfig.busMode].protocol_clkh();
										break;
								case 2: protoclk();
										//protos[bpConfig.busMode].protocol_clk();
										break;
							}
						
							break;
			case TOK_PULLUP:	pcupdated=1;
							pc+=4;
							if(pgmspace[pc]==',')
							{	pc++;
							}
							else
							{	stop=SYNTAXERROR;
							}
#if defined( BUSPIRATEV0A) || defined( BUSPIRATEV2)
//#if(0)
							if(getnumvar())
							{	protopullupon();
								//BP_PULLUP_ON(); 
								//modeConfig.pullupEN=1;
							}
							else
							{	protopullupoff();
								//BP_PULLUP_OFF();
								//modeConfig.pullupEN=0;
							}
#else
							pc+=len-1; 	// fail silently
#endif							
							break;
			case TOK_DELAY:	pcupdated=1;
							pc+=4;
							if(pgmspace[pc]==',')
							{	pc++;
							}
							else
							{	stop=SYNTAXERROR;
							}
							bpDelayUS(getnumvar());
							break;
			case TOK_END:	//bpWstring(STAT_END);
							stop=1; 
							break;
			default:		stop=SYNTAXERROR;
							break;	
		}

		if(!pcupdated)
		{	pc+=len+3;
			//bpBR;
		}
		pcupdated=0;
	}

	if(stop!=NOERROR)
	{	bpWstring("Error(");
		bpWinthex(stop);
		bpWstring(") @line:");
		bpWinthex(lineno);
		bpWstring(" @pgmspace:");
		bpWinthex(pc);
		bpBR;
	}

	basquiet=0;			// turn echoing from protocols on

	//bpWinthex(vars[0]); bpSP;
	//bpWinthex(vars[1]); bpSP;
	//bpWinthex(vars[2]); bpSP;
}

void printstat(char *s)
{	bpSP;
	bpWstring(s);
	bpSP;
}

void list(void)
{	unsigned char c;
	unsigned int lineno;

	pc=0;

	while(pgmspace[pc])
	{	c=pgmspace[pc];
		switch(c)
		{	case TOK_LET:	printstat(STAT_LET);
							break;
			case TOK_IF:	printstat(STAT_IF);
							break;
			case TOK_THEN:	printstat(STAT_THEN);
							break;
			case TOK_ELSE:	printstat(STAT_ELSE);
							break;
			case TOK_GOTO:	printstat(STAT_GOTO);
							break;
			case TOK_GOSUB:	printstat(STAT_GOSUB);
							break;
			case TOK_RETURN:printstat(STAT_RETURN);
							break;
			case TOK_REM:	printstat(STAT_REM);
							break;
			case TOK_PRINT:	printstat(STAT_PRINT);
							break;
			case TOK_INPUT:	printstat(STAT_INPUT);
							break;
			case TOK_FOR:	printstat(STAT_FOR);
							break;
			case TOK_TO:	printstat(STAT_TO);
							break;
			case TOK_NEXT:	printstat(STAT_NEXT);
							break;
			case TOK_READ:	printstat(STAT_READ);
							break;
			case TOK_DATA:	printstat(STAT_DATA);
							break;
			case TOK_START:	printstat(STAT_START);
							break;
			case TOK_STARTR:	printstat(STAT_STARTR);
							break;
			case TOK_STOP:	printstat(STAT_STOP);
							break;
			case TOK_STOPR:	printstat(STAT_STOPR);
							break;
			case TOK_SEND:	printstat(STAT_SEND);
							break;
			case TOK_RECEIVE:	printstat(STAT_RECEIVE);
							break;
			case TOK_CLK:	printstat(STAT_CLK);
							break;
			case TOK_DAT:	printstat(STAT_DAT);
							break;
			case TOK_ADC:	printstat(STAT_ADC);
							break;
			case TOK_AUX:	printstat(STAT_AUX);
							break;
			case TOK_PSU:	printstat(STAT_PSU);
							break;
			case TOK_PULLUP:	printstat(STAT_PULLUP);
							break;
			case TOK_DELAY:	printstat(STAT_DELAY);
							break;
			case TOK_BITREAD:	printstat(STAT_BITREAD);
							break;
			case TOK_END:	printstat(STAT_END);
							break;
			default:		if(c<TOK_LEN)
							{	UART1TX(c);
							}
							else
							{	bpBR;
								lineno=(pgmspace[pc+1]<<8)+pgmspace[pc+2];
								pc+=2;
								bpWinthex(lineno);
								bpSP;
							}
		}
		pc++;
	}
	bpBR;
	bpWinthex(pc-1);
	bpWline(" bytes");
}




