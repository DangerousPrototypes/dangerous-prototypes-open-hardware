/*
LIN HAL in master mode
Author: 7
 */


#include "globals.h"


#define HAL_LIN_M_MAX_BUF_SZ_RX		10

static u8 RxBuffer[HAL_LIN_M_MAX_BUF_SZ_RX+2];
static u8 RxBufferCtrOut,RxBufferCtrIn;


#define hal_Lin_M_ResetRxBufferCtr()   	RxBufferCtrOut=0;RxBufferCtrIn=0;
#define hal_Lin_M_HasRxData()  			(RxBufferCtrOut!=RxBufferCtrIn)


void hal_Lin_M_Init(void)
{
TXSTA=0x24;
RCSTA=0x80;
BAUDCON=0x08;

// TODO this must be flexible
SPBRGH=0x00;
SPBRG=0x00;
}

#if 0
// if this returns 0, it is done sending the header
u8 hal_Lin_M_IsDoneSendingSyncBreak()
{
return  TXSTAbits.SENDB;
}
#endif



#define hal_Lin_M_IsDoneSendingSyncBreak() 	TXSTAbits.SENDB

static u8 NumbytesToReceive=0xFF;


void hal_Lin_M_SendSyncBreakHeaderID(u8 ID)
{
//send break
TXSTAbits.TXEN=1;
TXSTAbits.SENDB=1;
TXREG='j'; // dummy value

while(hal_Lin_M_IsDoneSendingSyncBreak()==1);

TXREG=0x55; //sync byte
while(PIR1bits.TXIF);

hal_Lin_M_ResetRxBufferCtr();

TXREG=ID; //ID byte
while(PIR1bits.TXIF);

}



void hal_Lin_M_SendData(u8 * Data, u8 NumBytes)
{
u8 ctr;

for(ctr=0;ctr<NumBytes;ctr++)
	{
	TXREG=Data[ctr]; //sync byte
	while(PIR1bits.TXIF);
	}
}



// returns if data is ok
u8 hal_Lin_M_IsDataRxOk(u8 NumBytes)
{
return (NumBytes==RxBufferCtrIn)?TRUE:FALSE;
}



//high priority interrupt routine
#pragma interrupt hal_Lin_M_HandlerHigh
void hal_Lin_M_HandlerHigh (void)
{
// this will contain the RX interrupt FIFO Buffering
if(RcIf)
	{
	RxBuffer[RxBufferCtrIn]=RCREG;
	RxBufferCtrIn++;

	if(RxBufferCtrIn>HAL_LIN_M_MAX_BUF_SZ_RX)
		RxBufferCtrIn=0;

	}
}




//////////

