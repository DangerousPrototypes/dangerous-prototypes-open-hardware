/* header */
#ifndef PWM_H
#define PWM_H
#include <pic.h>

void enablePWM(void);
void disablePWM(void);
void setPeriod(unsigned char);
void setDuty(unsigned char);


extern unsigned char PWMduty;
extern unsigned char PWMperiod;
#endif