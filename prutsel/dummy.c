

#include "hardware.h"
#include "dummy.h"

void bpWstring(char *s);
void bpWinthex(unsigned int c);
void bpWline(char *s);

// implementation of buspirate commands

void DUMMY_start(int repeat)
{	bpWline("--dummy start");
}

void DUMMY_startR(int repeat)
{	bpWline("--dummy startR");
}

void DUMMY_stop(int repeat)
{	bpWline("--dummy stop");
}

void DUMMY_stopR(int repeat)
{	bpWline("--dummy stop");
}

void DUMMY_send(unsigned int c, int repeat)
{	bpWline("--dummy send");
	bpWstring("--- send ");
	bpWinthex(c);
	bpWstring(" ");
	bpWinthex(repeat);
	bpWline(" times");
}

void DUMMY_read(int repeat)
{	bpWline("--dummy read");
}

void DUMMY_clkh(int repeat)
{	bpWline("--dummy clk h");
}

void DUMMY_clkl(int repeat)
{	bpWline("--dummy clk l");
}

void DUMMY_dath(int repeat)
{	bpWline("--dummy dat h");
}

void DUMMY_datl(int repeat)
{	bpWline("--dummy dat l");
}

void DUMMY_dats(int repeat)
{	bpWline("--dummy dat state");
}

void DUMMY_clk(int repeat)
{	bpWline("--dummy clk");
}

void DUMMY_bitr(int repeat)
{	bpWline("--dummy bitread");
}


