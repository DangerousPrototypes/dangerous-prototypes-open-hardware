#ifndef RTCC_H
#define RTCC_H

//#include <time.h>
#include <stdbool.h>


struct tm
	{	/* date and time components */
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	};

struct rtcc_bcd_tm
{
	unsigned char sec; //tens = sec >> 4; ones = sec & 0x0f
	unsigned char min;
	unsigned char hour;
	unsigned char day;
	unsigned char mon;
	unsigned char year; //two digits only 
};
/*
* Initialise the RTCC to run from the secondary osc
*/
void rtcc_init(void);

/*
Enable the RTCC
*/
void rtcc_enable(void);

/*
Get the current time and date from the RTCC in a tm struct 
*/
void rtcc_get_tm(struct tm *tptr);

/*
Get the current time and date from the RTCC in a BCD encoded tm struct 
*/
void rtcc_get_bcd_tm(struct rtcc_bcd_tm *tptr);


/*
Set the current time and date of the RTCC from a tm struct 
*/
void rtcc_set_tm(const struct tm time);

/*
Set the parameters of the RTCC alarm.
You must implement the _RTCCInterrupt handler somewhere to handle the alarm
*/
void rtcc_set_alarm(struct tm time, unsigned char mask, unsigned char repeat, bool chime  );

/*
Enable the RTCC alarm interrupt
*/
void rtcc_enable_alarm();



#endif

