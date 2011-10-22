
#ifndef DUMMYH 
#define DUMMYH



// cmd structure
extern char cmdbuf[CMDBUFLEN];
extern unsigned int end;
extern unsigned int start;


// implementation of buscommands
void DUMMY_start(int repeat);
void DUMMY_startR(int repeat);
void DUMMY_stop(int repeat);
void DUMMY_stopR(int repeat);
void DUMMY_send(unsigned int c, int repeat);
void DUMMY_read(int repeat);
void DUMMY_read(int repeat);
void DUMMY_clkh(int repeat);
void DUMMY_clkl(int repeat);
void DUMMY_dath(int repeat);
void DUMMY_datl(int repeat);
void DUMMY_dats(int repeat);
void DUMMY_clk(int repeat);
void DUMMY_bitr(int repeat);


#endif
