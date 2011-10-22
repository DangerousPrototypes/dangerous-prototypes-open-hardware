#ifndef DUMMY2H 
#define DUMMY2H



// cmd structure
extern char cmdbuf[CMDBUFLEN];
extern unsigned int end;
extern unsigned int start;


// implementation of buscommands
void DUMMY2_start(int repeat);
void DUMMY2_startR(int repeat);
void DUMMY2_stop(int repeat);
void DUMMY2_stopR(int repeat);
void DUMMY2_send(unsigned int c, int repeat);
void DUMMY2_read(int);
void DUMMY2_clkh(int repeat);
void DUMMY2_clkl(int repeat);
void DUMMY2_dath(int repeat);
void DUMMY2_datl(int repeat);
void DUMMY2_dats(int repeat);
void DUMMY2_clk(int repeat);
void DUMMY2_bitr(int repeat);



#endif
