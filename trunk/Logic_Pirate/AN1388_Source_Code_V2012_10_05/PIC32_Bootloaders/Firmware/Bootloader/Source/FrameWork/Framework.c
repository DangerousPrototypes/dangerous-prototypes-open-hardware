/*********************************************************************
 *
 *                  PIC32 Boot Loader
 *
 *********************************************************************
 * FileName:        Framework.c
 * Dependencies:
 * Processor:       PIC32
 *
 * Compiler:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32 Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC32 Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * $Id:  $
 * $Name: $
 *
 **********************************************************************/

#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "Include\BootLoader.h"
#include "Include\Framework\Framework.h"
#include "Include\NVMem.h"
#include  <string.h>
#include <plib.h>





#define DATA_RECORD 		0
#define END_OF_FILE_RECORD 	1
#define EXT_SEG_ADRS_RECORD 2
#define EXT_LIN_ADRS_RECORD 4

#if defined(__PIC32MX1XX_2XX__)
    // PIC32MX1xx and PIC32MX2xx devices
    #define FLASH_PAGE_SIZE		 		1024
    #define DEV_CONFIG_REG_BASE_ADDRESS 0x9FC00BF0
    #define DEV_CONFIG_REG_END_ADDRESS   0x9FC00BFF
#elif defined(__PIC32MX3XX_7XX__)
    // PIC32MX3xx to PIC32MX7xx devices
    #define FLASH_PAGE_SIZE		 		4096
    #define DEV_CONFIG_REG_BASE_ADDRESS 0x9FC02FF0
    #define DEV_CONFIG_REG_END_ADDRESS   0x9FC02FFF
#endif





typedef enum
{
	READ_BOOT_INFO = 1,
	ERASE_FLASH, 
	PROGRAM_FLASH,
	READ_CRC,
	JMP_TO_APP
	
}T_COMMANDS;	


typedef struct
{
	UINT Len;
	UINT8 Data[FRAMEWORK_BUFF_SIZE];
	
}T_FRAME;

typedef struct 
{
	UINT8 RecDataLen;
	DWORD_VAL Address;
	UINT8 RecType;
	UINT8* Data;
	UINT8 CheckSum;	
	DWORD_VAL ExtSegAddress;
	DWORD_VAL ExtLinAddress;
}T_HEX_RECORD;	


static const UINT8 BootInfo[2] =
{
    MAJOR_VERSION,
    MINOR_VERSION
};


static T_FRAME RxBuff;
static T_FRAME TxBuff;
static BOOL RxFrameValid;
static BOOL TriggerBaudChange;
static DWORD_VAL NewBaud;
static BOOL RunApplication = FALSE;


void HandleCommand(void);
void BuildRxFrame(UINT8 *RxData, INT16 RxLen);
UINT GetTransmitFrame(UINT8* Buff);
void WriteHexRecord2Flash(UINT8* HexRecord, UINT totalRecLen);
BOOL BaudRateChangeRequested(void);
UINT16 CalculateCrc(UINT8 *data, UINT32 len);


/********************************************************************
* Function: 	FrameWorkTask()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Process the command if there is a valid fame.
*
*			
* Note:		 	None.
********************************************************************/
void FrameWorkTask(void)
{

	if(RxFrameValid)
	{
		// Valid frame received, process the command.
		HandleCommand();	
		// Reset the flag.
		RxFrameValid = FALSE;			
	}        
}


/********************************************************************
* Function: 	HandleCommand()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Process the received frame and take action depending on
				the command received.
*
*			
* Note:		 	None.
********************************************************************/
void HandleCommand(void)
{
	UINT8 Cmd;
	DWORD_VAL Address;
	UINT8 i;
	DWORD_VAL Length;
	UINT8 *DataPtr;
	UINT Result;
	WORD_VAL crc;
	void* pFlash;
	
	// First byte of the data field is command.
	Cmd = RxBuff.Data[0];
	// Partially build response frame. First byte in the data field carries command.
	TxBuff.Data[0] = RxBuff.Data[0];
	
	// Reset the response length to 0.
	TxBuff.Len = 0;
				
	// Process the command.		
	switch(Cmd)
	{
		case READ_BOOT_INFO: // Read boot loader version info.
			memcpy(&TxBuff.Data[1], BootInfo, 2);
			//Set the transmit frame length.
			TxBuff.Len = 2 + 1; // Boot Info Fields	+ command
			break;
			
		case ERASE_FLASH:
			pFlash = (void*)APP_FLASH_BASE_ADDRESS;									
			for( i = 0; i < ((APP_FLASH_END_ADDRESS - APP_FLASH_BASE_ADDRESS + 1)/FLASH_PAGE_SIZE); i++ )
			{
				
				Result = NVMemErasePage( pFlash + (i*FLASH_PAGE_SIZE) );
				// Assert on NV error. This must be caught during debug phase.
				ASSERT(Result==0);
			
			}		           
            //Set the transmit frame length.
            TxBuff.Len = 1; // Command
			break;
		
		case PROGRAM_FLASH:
		    WriteHexRecord2Flash(&RxBuff.Data[1], RxBuff.Len-3);	//Negate length of command and CRC RxBuff.Len.
		    //Set the transmit frame length.
            TxBuff.Len = 1; // Command	    	
		   	break;
		   
		   
		case READ_CRC:
			 // Get address from the packet.
    	    memcpy(&Address.v[0], &RxBuff.Data[1], sizeof(Address.Val));
    	    memcpy(&Length.v[0], &RxBuff.Data[5], sizeof(Length.Val));
			crc.Val = CalculateCrc((UINT8 *)Address.Val, Length.Val);
			memcpy(&TxBuff.Data[1], &crc.v[0], 2);	
			
			//Set the transmit frame length.
            TxBuff.Len = 1 + 2;	// Command + 2 bytes of CRC.
			
			break;
	    
	    case JMP_TO_APP:
	    	// Exit firmware upgrade mode.
	    	RunApplication = TRUE;
	    	break;
	    	
	    default:
	    	// Nothing to do.
	    	break;
	}   
	

		
}


/********************************************************************
* Function: 	BuildRxFrame()
*
* Precondition: 
*
* Input: 		Pointer to Rx Data and Rx byte length.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Builds rx frame and checks CRC.
*
*			
* Note:		 	None.
********************************************************************/
void BuildRxFrame(UINT8 *RxData, INT16 RxLen)
{
	static BOOL Escape = FALSE;
	WORD_VAL crc;
	
	
	while((RxLen > 0) && (!RxFrameValid)) // Loop till len = 0 or till frame is valid
	{
		RxLen--;
		
		if(RxBuff.Len >= sizeof(RxBuff.Data))
		{
			RxBuff.Len = 0;
		}	
		
		switch(*RxData)
		{
			
			case SOH: //Start of header
				if(Escape)
				{
					// Received byte is not SOH, but data.
					RxBuff.Data[RxBuff.Len++] = *RxData;
					// Reset Escape Flag.
					Escape = FALSE;
				}
				else
				{
					// Received byte is indeed a SOH which indicates start of new frame.
					RxBuff.Len = 0;				
				}		
				break;
				
			case EOT: // End of transmission
				if(Escape)
				{
					// Received byte is not EOT, but data.
					RxBuff.Data[RxBuff.Len++] = *RxData;
					// Reset Escape Flag.
					Escape = FALSE;
				}
				else
				{
					// Received byte is indeed a EOT which indicates end of frame.
					// Calculate CRC to check the validity of the frame.
					if(RxBuff.Len > 1)
					{
						crc.byte.LB = RxBuff.Data[RxBuff.Len-2];
						crc.byte.HB = RxBuff.Data[RxBuff.Len-1];
						if((CalculateCrc(RxBuff.Data, (UINT32)(RxBuff.Len-2)) == crc.Val) && (RxBuff.Len > 2))
						{
							// CRC matches and frame received is valid.
							RxFrameValid = TRUE;
												
						}
					}		
					
				}							
				break;
				
				
		    case DLE: // Escape character received.
				if(Escape)
				{
					// Received byte is not ESC but data.
					RxBuff.Data[RxBuff.Len++] = *RxData;
					// Reset Escape Flag.
					Escape = FALSE;					
				}
				else
				{
					// Received byte is an escape character. Set Escape flag to escape next byte.
					Escape = TRUE;					
				}	
				break;
			
			default: // Data field.
			    RxBuff.Data[RxBuff.Len++] = *RxData;
			    // Reset Escape Flag.
			    Escape = FALSE;
				break;	
			
		}

		//Increment the pointer.
		RxData++;	
	
	}	
	
}	


/********************************************************************
* Function: 	GetTransmitFrame()
*
* Precondition: 
*
* Input: 		Buffer pointer.
*
* Output:		Length of the buffer.
*
* Side Effects:	None.
*
* Overview: 	Gets the complete transmit frame into the "Buff".
*
*			
* Note:		 	None.
********************************************************************/
UINT GetTransmitFrame(UINT8* Buff)
{
	INT BuffLen = 0;
	WORD_VAL crc;
	UINT8 i;
	
	if(TxBuff.Len) 
	{
		//There is something to transmit.
		// Calculate CRC of the frame.
		crc.Val = CalculateCrc(TxBuff.Data, (UINT32)TxBuff.Len);
		TxBuff.Data[TxBuff.Len++] = crc.byte.LB;
		TxBuff.Data[TxBuff.Len++] = crc.byte.HB; 	
		
		// Insert SOH (Indicates beginning of the frame)	
		Buff[BuffLen++] = SOH;
		
		// Insert Data Link Escape Character.
		for(i = 0; i < TxBuff.Len; i++)
		{
			if((TxBuff.Data[i] == EOT) || (TxBuff.Data[i] == SOH)
				|| (TxBuff.Data[i] == DLE))
			{
				// EOT/SOH/DLE repeated in the data field, insert DLE.
				Buff[BuffLen++] = DLE;			
			}
			Buff[BuffLen++] = TxBuff.Data[i];
		} 
		
		// Mark end of frame with EOT.
		Buff[BuffLen++] = EOT;
		
		TxBuff.Len = 0; // Purge this buffer, no more required.
	}	
	
	return(BuffLen); // Return buffer length.
	
}	


/********************************************************************
* Function: 	WriteHexRecord2Flash()
*
* Precondition: 
*
* Input: 		HexRecord buffer.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview:     Writes hex record to flash.
*
*			
* Note:		 	None.
********************************************************************/	
void WriteHexRecord2Flash(UINT8* HexRecord, UINT totalHexRecLen)
{
	static T_HEX_RECORD HexRecordSt;
	UINT8 Checksum = 0;
	UINT i;
	UINT WrData;
	UINT RdData;
	void* ProgAddress;
	UINT Result;
	UINT nextRecStartPt = 0;
	UINT8 temp[4];

	while(totalHexRecLen>=5) // A hex record must be atleast 5 bytes. (1 Data Len byte + 1 rec type byte+ 2 address bytes + 1 crc)
	{
		HexRecord = &HexRecord[nextRecStartPt];
		HexRecordSt.RecDataLen = HexRecord[0];
		HexRecordSt.RecType = HexRecord[3];	
		HexRecordSt.Data = &HexRecord[4];
		
		//Determine next record starting point.
		nextRecStartPt = HexRecordSt.RecDataLen + 5;	
		
		// Decrement total hex record length by length of current record.
		totalHexRecLen = totalHexRecLen - nextRecStartPt;
		
		// Hex Record checksum check.
		Checksum = 0;
		for(i = 0; i < HexRecordSt.RecDataLen + 5; i++)
		{
			Checksum += HexRecord[i];
		}	
		
	    if(Checksum != 0)
	    {
		    //Error. Hex record Checksum mismatch.
		} 
		else
		{
			// Hex record checksum OK.
			switch(HexRecordSt.RecType)
			{
				case DATA_RECORD:  //Record Type 00, data record.
					HexRecordSt.Address.byte.MB = 0;
					HexRecordSt.Address.byte.UB = 0;
					HexRecordSt.Address.byte.HB = HexRecord[1];
					HexRecordSt.Address.byte.LB = HexRecord[2];
					
					// Derive the address.
					HexRecordSt.Address.Val = HexRecordSt.Address.Val + HexRecordSt.ExtLinAddress.Val + HexRecordSt.ExtSegAddress.Val;
							
					while(HexRecordSt.RecDataLen) // Loop till all bytes are done.
					{
											
						// Convert the Physical address to Virtual address. 
						ProgAddress = PA_TO_KVA0(HexRecordSt.Address.Val);
						
						// Make sure we are not writing boot area and device configuration bits.
						if(((ProgAddress >= (void *)APP_FLASH_BASE_ADDRESS) && (ProgAddress <= (void *)APP_FLASH_END_ADDRESS))
						   && ((ProgAddress < (void*)DEV_CONFIG_REG_BASE_ADDRESS) || (ProgAddress > (void*)DEV_CONFIG_REG_END_ADDRESS)))
						{
							if(HexRecordSt.RecDataLen < 4)
							{
								
								// Sometimes record data length will not be in multiples of 4. Appending 0xFF will make sure that..
								// we don't write junk data in such cases.
								WrData = 0xFFFFFFFF;
								memcpy(&WrData, HexRecordSt.Data, HexRecordSt.RecDataLen);	
							}
							else
							{	
								memcpy(&WrData, HexRecordSt.Data, 4);
							}		
							// Write the data into flash.	
							Result = NVMemWriteWord(ProgAddress, WrData);	
							// Assert on error. This must be caught during debug phase.		
							ASSERT(Result==0);					
						}	
						
						// Increment the address.
						HexRecordSt.Address.Val += 4;
						// Increment the data pointer.
						HexRecordSt.Data += 4;
						// Decrement data len.
						if(HexRecordSt.RecDataLen > 3)
						{
							HexRecordSt.RecDataLen -= 4;
						}	
						else
						{
							HexRecordSt.RecDataLen = 0;
						}	
					}
					break;
				
				case EXT_SEG_ADRS_RECORD:  // Record Type 02, defines 4th to 19th bits of the data address.
				    HexRecordSt.ExtSegAddress.byte.MB = 0;
					HexRecordSt.ExtSegAddress.byte.UB = HexRecordSt.Data[0];
					HexRecordSt.ExtSegAddress.byte.HB = HexRecordSt.Data[1];
					HexRecordSt.ExtSegAddress.byte.LB = 0;
					// Reset linear address.
					HexRecordSt.ExtLinAddress.Val = 0;
					break;
					
				case EXT_LIN_ADRS_RECORD:   // Record Type 04, defines 16th to 31st bits of the data address. 
					HexRecordSt.ExtLinAddress.byte.MB = HexRecordSt.Data[0];
					HexRecordSt.ExtLinAddress.byte.UB = HexRecordSt.Data[1];
					HexRecordSt.ExtLinAddress.byte.HB = 0;
					HexRecordSt.ExtLinAddress.byte.LB = 0;
					// Reset segment address.
					HexRecordSt.ExtSegAddress.Val = 0;
					break;
					
				case END_OF_FILE_RECORD:  //Record Type 01, defines the end of file record.
				default: 
					HexRecordSt.ExtSegAddress.Val = 0;
					HexRecordSt.ExtLinAddress.Val = 0;
					break;
			}		
		}	
	}//while(1)	
		
}	


/**
 * Static table used for the table_driven implementation.
 *****************************************************************************/
static const UINT16 crc_table[16] = 
{
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
};

/********************************************************************
* Function: 	CalculateCrc()
*
* Precondition: 
*
* Input: 		Data pointer and data length
*
* Output:		CRC.
*
* Side Effects:	None.
*
* Overview:     Calculates CRC for the given data and len
*
*			
* Note:		 	None.
********************************************************************/	
UINT16 CalculateCrc(UINT8 *data, UINT32 len)
{
    UINT i;
    UINT16 crc = 0;
    
    while(len--)
    {
        i = (crc >> 12) ^ (*data >> 4);
	    crc = crc_table[i & 0x0F] ^ (crc << 4);
	    i = (crc >> 12) ^ (*data >> 0);
	    crc = crc_table[i & 0x0F] ^ (crc << 4);
	    data++;
	} 

    return (crc & 0xFFFF);
}


/********************************************************************
* Function: 	ExitFirmwareUpgradeMode()
*
* Precondition: 
*
* Input: 		Void
*
* Output:		True if firmware upgrade mode has to be exited.
*
* Side Effects:	None.
*
* Overview:     This function returns true if firmware mode has to be exited.
*
*			
* Note:		 	None.
********************************************************************/
BOOL ExitFirmwareUpgradeMode(void)
{
	return RunApplication;
}	

/**************************End of file**************************************************/

