#include "stdafx.h"
#include "Ethernet.h"
#include "ComPort.h"
#include "USB_HID.h"
#include "Hex.h"
#include "BootLoader.h"
#include "PIC32UBL.h"
#include "PIC32UBLDlg.h"
#include ".\pic32ubldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SOH 01
#define EOT 04
#define DLE 16


/**
 * Static table used for the table_driven implementation.
 *****************************************************************************/
static const unsigned short crc_table[16] = 
{
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
};

/****************************************************************************
 * Update the crc value with new data.
 *
 * \param crc      The current crc value.
 * \param data     Pointer to a buffer of \a data_len bytes.
 * \param len		Number of bytes in the \a data buffer.
 * \return         The updated crc value.
 *****************************************************************************/
unsigned short CalculateCrc(char *data, unsigned int len)
{
    unsigned int i;
    unsigned short crc = 0;
    
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

/****************************************************************************
 *  This thread calls receive and transmit tasks
 *
 * \param lpParam  this Pointer
 

 * \return  0 on exit.
 *****************************************************************************/
UINT RxTxThread(LPVOID lpParam)
{
	CBootLoader *bootloaderPtr = (CBootLoader *)lpParam;

	while(bootloaderPtr->ExitThread == FALSE)
	{
		
		bootloaderPtr->ReceiveTask();
		bootloaderPtr->TransmitTask();
		Sleep(1);
	}
	bootloaderPtr->ThreadKilled = TRUE;

	return 0;
}




/****************************************************************************
 * Shut down the Receive transmit thread.
 *
 * \param       
 * \param      
 * \param 		
 * \return         
 *****************************************************************************/
void CBootLoader::ShutdownThread( )
{
   HRESULT hr = S_OK;
  
   if(BtlThread)
   {
	   // Set a flag to exit the thread
	   ExitThread = TRUE;
	   ThreadKilled = FALSE;
	   Sleep(1000); // Sleep for 1 second.
	   if(ThreadKilled == FALSE)
	   {
		   // Thread was not killed. Kill thread by force.
			::TerminateThread( BtlThread, -1000 );
			// Close the handle and NULL it out
			::CloseHandle( BtlThread );
	   }

	   

	   // Set the thread handle to NULL
	   BtlThread = NULL;
   }
}

/****************************************************************************
 * Create	Thread
 *
 * \param   hWnd  Main Window Handle 
 * \param      
 * \param 		
 * \return         
 *****************************************************************************/
void CBootLoader::CreateRxTxThread(HWND hWnd)
{
	m_hWnd = hWnd; // required for posting messages
	if(BtlThread)
	{
		return; // Thread is already running.
		
	}
	ExitThread = false;
	BtlThread = ::AfxBeginThread(RxTxThread, this, THREAD_PRIORITY_NORMAL, 0, 0, 0);
	
}


/****************************************************************************
 *  Receive Task
 *
 * \param   
 * \param      
 * \param 		
 * \return         
 *****************************************************************************/
void CBootLoader::ReceiveTask(void)
{
	unsigned short BuffLen;
	char Buff[255];
	
	BuffLen = ReadPort((char*)Buff, (sizeof(Buff) - 10));
	BuildRxFrame((unsigned char*)Buff, BuffLen);
	if(RxFrameValid)
	{
		// Valid frame is received.
		// Disable further retries.
		StopTxRetries();
		RxFrameValid = false;
		// Handle Response
		HandleResponse();
	}
	else
	{
		// Retries exceeded. There is no reponse from the device.
		if(NoResponseFromDevice)
		{
			// Reset flags
			NoResponseFromDevice = false;
            RxFrameValid = false;		
			// Handle no response situation.
			HandleNoResponse();
		}
	}
}


/****************************************************************************
 *  Handle no response situation
 *
 * \param   
 * \param      
 * \param 		
 * \return         
 *****************************************************************************/
void CBootLoader::HandleNoResponse(void)
{
	// Handle no response situation depending on the last sent command.
	switch(LastSentCommand)
	{
		case READ_BOOT_INFO:
		case ERASE_FLASH:
		case PROGRAM_FLASH:
		case READ_CRC:
			// Notify main window that there was no reponse.
			::PostMessage(m_hWnd, WM_USER_BOOTLOADER_NO_RESP, (WPARAM)LastSentCommand, 0 );
			break;

	}
}

/****************************************************************************
 *  Handle Response situation
 *
 * \param   
 * \param      
 * \param 		
 * \return         
 *****************************************************************************/
void CBootLoader::HandleResponse(void)
{
	unsigned char cmd = RxData[0];
	char majorVer = RxData[3];
	char minorVer = RxData[4];
	CString string;
	 
	
	switch(cmd)
	{
	case READ_BOOT_INFO:
	case ERASE_FLASH:
	case READ_CRC:
		// Notify main window that command received successfully.
		::PostMessage(m_hWnd, WM_USER_BOOTLOADER_RESP_OK, (WPARAM)cmd, (LPARAM)&RxData[1] );
		break;

	case PROGRAM_FLASH:
		
		// If there is a hex record, send next hex record.
		ResetHexFilePtr = false; // No need to reset hex file pointer.
		if(!SendCommand(PROGRAM_FLASH, MaxRetry, TxRetryDelay))
		{
			// Notify main window that programming operation completed.
			::PostMessage(m_hWnd, WM_USER_BOOTLOADER_RESP_OK, (WPARAM)cmd, (LPARAM)&RxData[1] );		 
		}
		ResetHexFilePtr = true;
		break;
	}
}


/****************************************************************************
 *  Builds the response frame
 *
 * \param  buff: Pointer to the data buffer 
 * \param  buffLen: Buffer length    
 * \param 		
 * \return         
 *****************************************************************************/
void CBootLoader::BuildRxFrame(unsigned char *buff, unsigned short buffLen)
{

	static bool Escape = false;
	unsigned short crc;
	
	
	while((buffLen > 0) && (RxFrameValid == false))
	{
		buffLen --;

		if(RxDataLen >= (sizeof(RxData)-2))
		{
			RxDataLen = 0;			
		}

		switch(*buff)
		{
			
			
			case SOH: //Start of header
				if(Escape)
				{
					// Received byte is not SOH, but data.
					RxData[RxDataLen++] = *buff;
					// Reset Escape Flag.
					Escape = FALSE;
				}
				else
				{
					// Received byte is indeed a SOH which indicates start of new frame.
					RxDataLen = 0;					
				}		
				break;
				
			case EOT: // End of transmission
				if(Escape)
				{
					// Received byte is not EOT, but data.
					RxData[RxDataLen++] = *buff;
					// Reset Escape Flag.
					Escape = FALSE;
				}
				else
				{
					// Received byte is indeed a EOT which indicates end of frame.
					// Calculate CRC to check the validity of the frame.
					if(RxDataLen > 1)
					{
						crc = (RxData[RxDataLen-2]) & 0x00ff;
						crc = crc | ((RxData[RxDataLen-1] << 8) & 0xFF00);
						if((CalculateCrc(RxData, (RxDataLen-2)) == crc) && (RxDataLen > 2))
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
					RxData[RxDataLen++] = *buff;
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
			    RxData[RxDataLen++] = *buff;
			    // Reset Escape Flag.
			    Escape = FALSE;
				break;	
			
		}	
		// Increment the pointer.
		buff++;	
		
	}	
}


/****************************************************************************
 *  Transmit task: Transmits frame if there is a frame to send.
 *
 * \param   
 * \param   
 * \param 		
 * \return         
 *****************************************************************************/
void CBootLoader::TransmitTask(void)
{
	static unsigned long NextRetryTimeInMs;
 
	
	switch(TxState)
	{

	case FIRST_TRY:
		if(RetryCount)
		{
			// There is something to send.
			WritePort(TxPacket, TxPacketLen);
			RetryCount--;
			// If there is no response to "first try", the command will be retried.
			TxState = RE_TRY;
			// Next retry should be attempted only after a delay.
			NextRetryTimeInMs = GetTickCount() + TxRetryDelay;
		}
		break;

	case RE_TRY:
		if(RetryCount)
		{			
			if(NextRetryTimeInMs < GetTickCount())
			{
				// Delay elapsed. Its time to retry.
				NextRetryTimeInMs = GetTickCount() + TxRetryDelay;
				WritePort(TxPacket, TxPacketLen);
				// Decrement retry count.
				RetryCount--;
				
			}
		}
		else
		{	
			// Retries Exceeded
			NoResponseFromDevice = true;
			// Reset the state
			TxState = FIRST_TRY;
		}
		break;
	}
}


/****************************************************************************
 *  Stops transmission retries
 *
 * \param   
 * \param   
 * \param 		
 * \return         
 *****************************************************************************/
void CBootLoader::StopTxRetries(void)
{
	// Reset state.
	TxState = FIRST_TRY;
	RetryCount = 0;
}


/****************************************************************************
 *  Send Command
 *
 * \param		cmd:  Command  
 * \param		data: Pointer to data buffer if any
 * \param 		dataLen: Data length
 * \param		retries: Number of retries allowed
 * \param		retryDelayInMs: Delay between retries in milisecond
 * \return         
 *****************************************************************************/
char Buff[1000];

bool CBootLoader::SendCommand(char cmd, unsigned short Retries, unsigned short DelayInMs)
{
	
	
	unsigned short crc;
	
	unsigned int StartAddress,  Len;
	unsigned short BuffLen = 0;
	unsigned short HexRecLen;
	UINT totalRecords = 10;
	TxPacketLen = 0;

	// Store for later use.
	LastSentCommand = cmd;

	switch((unsigned char)cmd)
	{
	case READ_BOOT_INFO:
		Buff[BuffLen++] = cmd;
		MaxRetry = RetryCount = Retries;	
		TxRetryDelay = DelayInMs; // in ms
		break;

	case ERASE_FLASH:
		Buff[BuffLen++] = cmd;
		MaxRetry = RetryCount = Retries;	
		TxRetryDelay = DelayInMs; // in ms
		break;

	case JMP_TO_APP:
		Buff[BuffLen++] = cmd;
		MaxRetry = RetryCount = 1;	
		TxRetryDelay = 10; // in ms
		break;
	
	case PROGRAM_FLASH:
		Buff[BuffLen++] = cmd;
		if(ResetHexFilePtr)
		{
			if(!HexManager.ResetHexFilePointer())
			{
				// Error in resetting the file pointer
				return false;
			}
		}
		HexRecLen = HexManager.GetNextHexRecord(&Buff[BuffLen], (sizeof(Buff) - 5));
		if(HexRecLen == 0)
		{
			//Not a valid hex file.
			return false;
		}
		
		BuffLen = BuffLen + HexRecLen;
		while(totalRecords)
		{
			HexRecLen = HexManager.GetNextHexRecord(&Buff[BuffLen], (sizeof(Buff) - 5));
			BuffLen = BuffLen + HexRecLen;
			totalRecords--;
		}
		MaxRetry = RetryCount = Retries;	
		TxRetryDelay = DelayInMs; // in ms
		break;

	case READ_CRC:
		Buff[BuffLen++] = cmd;
		HexManager.VerifyFlash((unsigned int*)&StartAddress, (unsigned int*)&Len, (unsigned short*)&crc);
		Buff[BuffLen++] = (StartAddress);
		Buff[BuffLen++] = (StartAddress >> 8);
		Buff[BuffLen++] = (StartAddress >> 16);
		Buff[BuffLen++] = (StartAddress >> 24);
		Buff[BuffLen++] = (Len);
		Buff[BuffLen++] = (Len >> 8);
		Buff[BuffLen++] = (Len >> 16);
		Buff[BuffLen++] = (Len >> 24);
		Buff[BuffLen++] =  (char)crc;
		Buff[BuffLen++] =  (char)(crc >> 8);
		MaxRetry = RetryCount = Retries;	
		TxRetryDelay = DelayInMs; // in ms
		break;

	default:
		return false;
		break;

	}

	// Calculate CRC for the frame.
	crc = CalculateCrc(Buff, BuffLen);
	Buff[BuffLen++] = (char)crc;
	Buff[BuffLen++] = (char)(crc >> 8);

	// SOH: Start of header
	TxPacket[TxPacketLen++] = SOH;

	// Form TxPacket. Insert DLE in the data field whereever SOH and EOT are present.
	for(int i = 0; i < BuffLen; i++)
	{
		if((Buff[i] == EOT) || (Buff[i] == SOH)
				|| (Buff[i] == DLE))
		{
			TxPacket[TxPacketLen++] = DLE;			
		}
		TxPacket[TxPacketLen++] = Buff[i];
	}

	// EOT: End of transmission
	TxPacket[TxPacketLen++] = EOT;
	
	return true;
	
}

/****************************************************************************
 *  Gets the progress of each command. This function can be used for progress 
	bar.
 *
 * \param	Lower: Pointer to current count of the progress bar.	
 * \param	Upper: Pointer to max count.	
 * \param 		
 * \return         
 *****************************************************************************/
void CBootLoader::GetProgress(int* Lower, int* Upper)
{
	

	switch(LastSentCommand)
	{
	case READ_BOOT_INFO:
	case ERASE_FLASH:
	case READ_CRC:
	case JMP_TO_APP:
		// Progress with respect to retry count.
		*Lower = (MaxRetry - RetryCount); 
		*Upper = MaxRetry;
		break;

	case PROGRAM_FLASH:
		// Progress with respect to line counts in hex file.
		*Lower = HexManager.HexCurrLineNo;
		*Upper = HexManager.HexTotalLines; 
		break;

	}
}

/****************************************************************************
 *  Gets locally calculated CRC
 *
 * \param		
 * \param		
 * \param 		
 * \return 16 bit CRC      
 *****************************************************************************/
unsigned short CBootLoader::CalculateFlashCRC(void)
{
	unsigned int StartAddress,  Len;
	unsigned short crc;
	HexManager.VerifyFlash((unsigned int*)&StartAddress, (unsigned int*)&Len, (unsigned short*)&crc);
	return crc;
}

/****************************************************************************
 *  Loads hex file
 *
 * \param		
 * \param		
 * \param 		
 * \return 16 bit CRC      
 *****************************************************************************/
bool CBootLoader::LoadHexFile(void)
{
	return HexManager.LoadHexFile();
}



/****************************************************************************
 *  Open communication port (USB/COM/Eth)
 *
 * \param Port Type	(USB/COM)	
 * \param	com port	
 * \param 	baud rate
 * \param   vid
 * \param   pid
 * \return       
 *****************************************************************************/
void CBootLoader::OpenPort(UINT portType, UINT comport, UINT baud, UINT vid, UINT pid, USHORT skt, ULONG ip, HWND hwnd)
{
	
	PortSelected = portType;
	switch(portType)
	{
	case USB:
		(VOID)UsbHid.OpenUSBDevice(vid, pid, hwnd);
		break;

	case COM:
		ComPort.OpenComPort(comport, baud);
		break; 

	case ETH:
		Ethernet.OpenUdpPort(skt, ip);
		break;

	}
	 
}

/****************************************************************************
 *  Get communication port status.
 *
 * \param 
 * \return true: Port opened.
		   false: Port closed.
 *****************************************************************************/
BOOL CBootLoader::GetPortOpenStatus(UINT PortType)
{
	BOOL result;
	
    switch(PortType)
	{
	case USB:
		result = UsbHid.GetPortOpenStatus();
		break;

	case COM:
		result = ComPort.GetComPortOpenStatus();
		break; 

	case ETH:
		result = Ethernet.GetSocketOpenStatus();
		break;
	}


	return result;

}

/****************************************************************************
 *  Closes the communication port (USB/COM/ETH)
 *
 * \param 
 * \return 
 *****************************************************************************/
void CBootLoader::ClosePort(UINT PortType)
{

	switch(PortSelected)
	{
	case USB:
		 UsbHid.ClosePort();

		break;

	case COM:
		ComPort.CloseComPort();
		break;   

	case ETH:
		Ethernet.CloseUdpPort();
		break;
		

	}
}


/****************************************************************************
 *  Write communication port (USB/COM/ETH)
 *
 * \param Buffer, Len
 * \return 
 *****************************************************************************/
void CBootLoader::WritePort(char *buffer, int bufflen)
{

	switch(PortSelected)
	{
	case USB:
		UsbHid.WriteUSBDevice(buffer, bufflen);
		break;

	case COM:
		ComPort.SendComPort(buffer, bufflen);
		break;    

	case ETH:
		Ethernet.SendUdpPort((BYTE *)buffer, bufflen);
		break;

	}
}


/****************************************************************************
 *  Read communication port (USB/COM/ETH)
 *
 * \param Buffer, Len
 * \return 
 *****************************************************************************/
unsigned short CBootLoader::ReadPort(char *buffer, int bufflen)
{
	unsigned short bytesRead;
	switch(PortSelected)
	{
	case USB:
		bytesRead = UsbHid.ReadUSBDevice(buffer, bufflen);
		break;

	case COM:
		bytesRead = ComPort.ReadComPort(buffer, bufflen);
		break;   

	case ETH:
		bytesRead = Ethernet.ReadUdpPort((BYTE*)buffer, bufflen);
		break;
	}

	return bytesRead;
}


BOOL CBootLoader::NotifyDeviceChange(UINT portType, char *devPath)
{
	if(portType == USB)
	{
		return(UsbHid.OnDeviceChange(devPath));
	}

	return FALSE;
}



/*******************End of file**********************************************/