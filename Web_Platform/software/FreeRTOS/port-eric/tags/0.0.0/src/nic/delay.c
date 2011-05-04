#include "delay.h"


void delay_ms(unsigned char ms)
{
    unsigned short delay_cnt = F_CPU/1000;
    //unsigned short delay_cnt = 2400;   //*KU* for 14.745600 MHz Clock
    unsigned short delay_cnt_buffer;

    while (ms--) {
        delay_cnt_buffer = delay_cnt;
        while (delay_cnt_buffer--);
    }

}





