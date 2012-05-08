/*
*
*       USB infrared remote control receiver transmitter firmware v1.0
*       License: creative commons - attribution, share-alike 
*       Copyright Ian Lesnet 2010
*       http://dangerousprototypes.com
*
*/
// What pins do what

#ifndef MAIN_H
#define MAIN_H

void SetupBoard(void);
void InterruptHandlerHigh();
void InterruptHandlerLow();
void SelfTest(void);
void GetUsbIrToyVersion(void);
void cleanup(void);
void ProcessDefaultMainMode(void);
void SetUpDefaultMainMode(void);
//void DefaultISR(void);
void DispatchISR(void);
void USBWakeFromSuspend(void);
void USBSuspend(void);
#endif
