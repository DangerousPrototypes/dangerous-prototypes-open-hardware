#include "rtcc.h"
#include "HardwareProfile.h"


void inline rtcc_reg_unlock(void)
{
	//TODO - disable interupts for this section
	//diable all ints
	asm volatile (	"mov #0x55,w0 \n"
					"mov w0, NVMKEY \n"
					"mov #0xAA, w0 \n"
					"mov w0, NVMKEY \n");
	RCFGCALbits.RTCWREN = 1;
	//enable all ints
}

void inline rtcc_reg_lock(void)
{
	asm volatile (	"mov #0x55,w0 \n"
					"mov w0, NVMKEY \n"
					"mov #0xAA, w0 \n"
					"mov w0, NVMKEY \n");

	RCFGCALbits.RTCWREN = 0;
		
}

void rtcc_enable(void)
{
	rtcc_reg_unlock();
	RCFGCALbits.RTCEN = 1;	
	rtcc_reg_lock();
}

void rtcc_init(void)
{
	//start seconary osc, and enable rtcc
	//OSCCONbits.LPOSCEN = 1;
	unsigned char oscconl = OSCCON & 0x0f;
	oscconl |= 0x02; //LPOSCEN
	__builtin_write_OSCCONL(oscconl);

	rtcc_enable();
}

unsigned char bcdL2char( short val )
{
	unsigned char result = val & 0x0f;
	result += ( (val & 0xf0 ) >> 4 ) * 10 ;
	return result;
}

unsigned char bcdH2char( short val )
{
	val = val >> 8;
	return bcdL2char(val);
}

unsigned short short2bcd( short val )
{
	return (( val / 10 ) << 4 ) + val % 10;
}


void rtcc_get_tm(struct tm *tptr)
{
	while(RCFGCALbits.RTCSYNC==1);
	RCFGCALbits.RTCPTR=3;
	short year=RTCVAL;
	short month_date=RTCVAL;
	short wday_hour=RTCVAL;
	short min_sec=RTCVAL;
	
	tptr->tm_sec = bcdL2char( min_sec );
	tptr->tm_min = bcdH2char( min_sec );
	tptr->tm_hour = bcdL2char( wday_hour );
	tptr->tm_wday = wday_hour >> 8;
	tptr->tm_mday = bcdL2char( month_date );
	tptr->tm_mon = bcdH2char( month_date ) - 1; //struct tm has 0 - 11 for month
	tptr->tm_year = year + 100; //assuming rtcc year is years since 2000
}


void rtcc_tm_to_vals( const struct tm time, short *year, short *month_date, short *wday_hour, short *min_sec )
{
	*year=time.tm_year - 100;
	*month_date=short2bcd((short)time.tm_mday) + (short2bcd((short)time.tm_mon) << 8);
	*wday_hour=short2bcd((short)time.tm_hour) + (short2bcd((short)time.tm_wday) << 8);
	*min_sec=short2bcd((short)time.tm_sec) + (short2bcd((short)time.tm_min) << 8);
}

void rtcc_set_tm(const struct tm time)
{
	short year, month_date, wday_hour, min_sec;
	rtcc_tm_to_vals( time, &year, &month_date, &wday_hour, &min_sec );
	
	rtcc_reg_unlock();
	RCFGCALbits.RTCEN = 0;
	RCFGCALbits.RTCPTR=3;
	RTCVAL= year;
	RTCVAL= month_date;
	RTCVAL = wday_hour;
	RTCVAL = min_sec;
	RCFGCALbits.RTCEN = 1;
	rtcc_reg_lock();
	
}


void rtcc_set_alarm(struct tm time, unsigned char mask, unsigned char repeat, bool chime  )
{
	ALCFGRPTbits.ALRMEN=0;

	short year, month_date, wday_hour, min_sec;
	rtcc_tm_to_vals( time, &year, &month_date, &wday_hour, &min_sec );

	ALCFGRPTbits.ALRMPTR=2;
	ALRMVAL= month_date;
	ALRMVAL = wday_hour;
	ALRMVAL = min_sec;

	ALCFGRPTbits.AMASK=mask;
	ALCFGRPTbits.ARPT = repeat;
	ALCFGRPTbits.CHIME = chime;

	ALCFGRPTbits.ALRMEN=1;

}

void rtcc_enable_alarm()
{
	IPC15bits.RTCIP = 7;
	IEC3bits.RTCIE = 1;
}