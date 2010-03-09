#include "delay.h"


void delay_ms(unsigned char ms)
{
   unsigned short delay_count = F_CPU / 4000;
/*#ifdef 0
    unsigned short cnt;
    asm volatile ("\n"
                  "L_dl1%=:\n\t"
                  "mov %A0, %A2\n\t"
                  "mov %B0, %B2\n"
                  "L_dl2%=:\n\t"
                  "sbiw %A0, 1\n\t"
                  "brne L_dl2%=\n\t"
                  "dec %1\n\t" "brne L_dl1%=\n\t":"=&w" (cnt)
                  :"r"(ms), "r"((unsigned short) (delay_count))
        );
#else
*/
    unsigned short delay_cnt = F_CPU/6000;
    //unsigned short delay_cnt = 2400;   //*KU* for 14.745600 MHz Clock
    unsigned short delay_cnt_buffer;

    while (ms--) {
        delay_cnt_buffer = delay_cnt;
        while (delay_cnt_buffer--);
    }
//#endif
}





