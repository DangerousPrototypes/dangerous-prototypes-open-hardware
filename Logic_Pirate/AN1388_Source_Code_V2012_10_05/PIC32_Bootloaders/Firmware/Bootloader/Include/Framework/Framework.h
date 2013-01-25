 // Copyright (c) 2002-2010,  Microchip Technology Inc.
//
// Microchip licenses this software to you solely for use with Microchip
// products.  The software is owned by Microchip and its licensors, and
// is protected under applicable copyright laws.  All rights reserved.
//
// SOFTWARE IS PROVIDED "AS IS."  MICROCHIP EXPRESSLY DISCLAIMS ANY
// WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  IN NO EVENT SHALL
// MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
// CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR
// EQUIPMENT, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY
// OR SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED
// TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION,
// OR OTHER SIMILAR COSTS.
//
// To the fullest extent allowed by law, Microchip and its licensors
// liability shall not exceed the amount of fees, if any, that you
// have paid directly to Microchip to use this software.
//
// MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE
// OF THESE TERMS.
#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#define SOH 01
#define EOT 04
#define DLE 16

#define FRAMEWORK_BUFF_SIZE					1000

#define FRAMEWORK_FrameWorkTask 			FrameWorkTask
#define FRAMEWORK_BuildRxFrame  			BuildRxFrame
#define FRAMEWORK_GetTransmitFrame 			GetTransmitFrame
#define FRAMEWORK_ExitFirmwareUpgradeMode 	ExitFirmwareUpgradeMode

// Exported functions
extern void FRAMEWORK_FrameWorkTask(void);
extern void FRAMEWORK_BuildRxFrame(UINT8 *RxData, INT16 RxLen);
extern UINT FRAMEWORK_GetTransmitFrame(UINT8* Buff);
extern BOOL FRAMEWORK_ExitFirmwareUpgradeMode(void);


#endif
