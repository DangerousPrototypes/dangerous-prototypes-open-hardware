


#include "hardware.h"
#include "dummy2.h"


void bpWstring(char *s);
void bpWinthex(unsigned int c);
void bpWline(char *s);


// implementation of buspirate commands

void DUMMY2_start(int repeat)
{	bpWline("--dummy2 start");
}

void DUMMY2_startR(int repeat)
{	bpWline("--dummy2 startR");
}

void DUMMY2_stop(int repeat)
{	bpWline("--dummy2 stop");
}

void DUMMY2_stopR(int repeat)
{	bpWline("--dummy2 stop");
}

void DUMMY2_send(unsigned int c, int repeat)
{	bpWline("--dummy2 send");
	bpWstring("--- send ");
	bpWinthex(c);
	bpWstring(" ");
	bpWinthex(repeat);
	bpWline(" times");
}

void DUMMY2_read(int repeat)
{	bpWline("--dummy2 read");
}

void DUMMY2_clkh(int repeat)
{	bpWline("--dummy2 clk h");
}

void DUMMY2_clkl(int repeat)
{	bpWline("--dummy2 clk l");
}

void DUMMY2_dath(int repeat)
{	bpWline("--dummy2 dat h");
}

void DUMMY2_datl(int repeat)
{	bpWline("--dummy2 dat l");
}

void DUMMY2_dats(int repeat)
{	bpWline("--dummy2 dat state");
}

void DUMMY2_clk(int repeat)
{	bpWline("--dummy2 clk");
}

void DUMMY2_bitr(int repeat)
{	bpWline("--dummy2 bitread");
}


