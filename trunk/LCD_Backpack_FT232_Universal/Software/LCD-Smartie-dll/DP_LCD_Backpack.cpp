#include <cstdio>
#include <fstream>
#include <String>
#include <cmath>
#include <iomanip>
#include "FTD2XX.H"
#include "DP_LCD_FT232.H"
#include "DP_LCD_Backpack.h"

using namespace std;

ofstream Log("DP_LCD_Backpack.log");


DP_Lcd_Backpack::DP_Lcd_Backpack()
{
	  BacklightOn = false; 

}
DP_Lcd_Backpack::~DP_Lcd_Backpack()
{

}

bool DP_Lcd_Backpack::InitializeFTDI_DLL()
{
	
	Log << "   Inside DP_Lcd_Backpack::InitializeFTDI_DLL() functions\n" ;
	// load library
	 DP_Lcd_Backpack::LoadDll();


	return OK;
}  

void DP_Lcd_Backpack::LoadDll()
{

	DP_Lcd_Backpack::m_hmodule = LoadLibrary("Ftd2xx.dll");	
	if(m_hmodule == NULL)	
		Log << "Error: Cannot Load ftd2xx.dll\n";	
	else
		Log << " Successfully loaded ftd2xx.dll\n" ;

	m_pWrite = (PtrToWrite)GetProcAddress(m_hmodule, "FT_Write");
	if (m_pWrite == NULL)
		Log << "Error: Cannot Find function FT_Write\n";	
	else
		Log << " Successfully Got FT_Write.\n" ;

	m_pRead = (PtrToRead)GetProcAddress(m_hmodule, "FT_Read");
	if (m_pRead == NULL)
		Log << "Error: Cannot Find function FT_Read\n";	
	else
		Log << " Successfully Got FT_Read.\n" ;

	m_pOpen = (PtrToOpen)GetProcAddress(m_hmodule, "FT_Open");
	if (m_pOpen == NULL)
		Log << "Error: Cannot Find function FT_Open\n";	
	else
		Log << " Successfully Got FT_Open.\n" ;

	m_pOpenEx = (PtrToOpenEx)GetProcAddress(m_hmodule, "FT_OpenEx");
	if (m_pOpenEx == NULL)
		Log << "Error: Cannot Find function FT_OpenEx\n";	
	else
		Log << " Successfully Got FT_OpenEx.\n" ;

	m_pListDevices = (PtrToListDevices)GetProcAddress(m_hmodule, "FT_ListDevices");
	if(m_pListDevices == NULL)
		Log << "Error: Cannot Find function FT_ListDevices\n";	
	else
		Log << " Successfully Got FT_ListDevices.\n" ;

	m_pClose = (PtrToClose)GetProcAddress(m_hmodule, "FT_Close");
	if (m_pClose == NULL)
		Log << "Error: Cannot Find function FT_Close\n";	
	else
		Log << " Successfully Got FT_Close.\n" ;

	m_pResetDevice = (PtrToResetDevice)GetProcAddress(m_hmodule, "FT_ResetDevice");
	if (m_pResetDevice == NULL)
		Log << "Error: Cannot Find function FT_ResetDevice\n";	
	else
		Log << " Successfully Got FT_ResetDevice.\n" ;

	m_pPurge = (PtrToPurge)GetProcAddress(m_hmodule, "FT_Purge");
	if (m_pPurge == NULL)
		Log << "Error: Cannot Find function FT_Purge\n";	
	else
		Log << " Successfully Got FT_Purge.\n" ;

	m_pSetTimeouts = (PtrToSetTimeouts)GetProcAddress(m_hmodule, "FT_SetTimeouts");
	if (m_pSetTimeouts == NULL)
		Log << "Error: Cannot Find function FT_SetTimeouts\n";	
	else
		Log << " Successfully Got FT_SetTimeouts.\n" ;

	m_pGetQueueStatus = (PtrToGetQueueStatus)GetProcAddress(m_hmodule, "FT_GetQueueStatus");
	if (m_pGetQueueStatus == NULL)
		Log << "Error: Cannot Find function FT_GetQueueStatus\n";	
	else
		Log << " Successfully Got FT_GetQueueStatus.\n" ;

	m_pSetLatencyTimer = (PtrToSetLatencyTimer)GetProcAddress(m_hmodule, "FT_SetLatencyTimer");
	if (m_pSetLatencyTimer == NULL)
		Log << "Error: Cannot Find function FT_SetLatencyTimer\n";	
	else
		Log << " Successfully Got FT_SetLatencyTimer.\n" ;
		

	m_pSetBitMode = (PtrToSetBitMode)GetProcAddress(m_hmodule, "FT_SetBitMode");
	if (m_pSetBitMode == NULL)
		Log << "Error: Cannot Find function FT_SetBitMode\n";	
	else
		Log << " Successfully Got FT_SetBitMode.\n" ;



	m_pSetBaudRate = (PtrToSetBaudRate)GetProcAddress(m_hmodule, "FT_SetBaudRate");
	if (m_pSetBaudRate == NULL)
		Log << "Error: Cannot Find function FT_SetBaudRate\n";	
	else
		Log << " Successfully Got FT_SetBaudRate.\n" ;

	

}

FT_STATUS DP_Lcd_Backpack::OpenDevice(char * startup_parameters)
{
	//open the device
	FT_STATUS status;
	FT_STATUS ftStatus;
	long locIdBuf[16];
	DWORD numDevs;
	ULONG x=0;
	Log << "Opening Dangerous Prototypes LCD Backpack Device \n";
	initializeBitMask();
	Initialize_SPI_Constants();

	//get devices here
	status = ListDevices((PVOID)locIdBuf,&numDevs,FT_LIST_ALL|FT_OPEN_BY_LOCATION);
	if (status == FT_OK)
		  {
			  // FT_ListDevices OK, location IDs are in locIdBuf,
			  // numDevs contains the number of devices connected

			  Log << "Enumerating Devices: \n";
			  for (DWORD i = 0; i < numDevs; i++)
			  {
				  Log << " Device found:" << i << locIdBuf[i] << "\n";
			  }

		 }
	else
	{
		Log << "OpenDevice: Device enumeration failed \n";
	
	}
	
	
	Log << "Opening Device based on smartie parameter: " << startup_parameters  << "\n";
	x = atoi(startup_parameters);
	if((x<0) || (x>64))
	{
		Log << "Device Error (0-64)  : " << x << "\n" ;
	}
	
	Log << "trying to open device: " << x << "\n";
	status = Open( (PVOID) x);   //load device no specified in x
	
	Log << "Open Devices Status:  " <<  status << "  Handle to device: " << m_ftHandle << "\n";

	// Set latency timer
	//status = SetLatency(2);
	status = SetLatencyTimer(2);
	if (status != FT_OK)
	{
		Log <<  "Error:  Set latency timer: " <<status << "\n";
	}

	// Reset the controller
	//status = SetBitMode(0, 0);
	ftStatus = SetBitMode(0,0);
	if (ftStatus != FT_OK)
	{
		 Log <<  "Error:  Reset Controller Status: " << ftStatus << "\n";
	}

	// Set synchronous bit bang mode
	ftStatus = SetBitMode((UCHAR) FT232Routputs, 4);  // Set device to mode 4 and sets outputs
	if (ftStatus !=FT_OK)
	{
		Log <<  "Error:  Set synchronous bit bang mode Status: " << ftStatus << "\n";
	}

	// Set baud rate/bit clock settings
	ftStatus = SetBaudRate(3000000);
	if (status != FT_OK)
	{
		  Log <<  "Error: Set baud rate/bit clock settings Status: " << ftStatus << "\n";
	}
	Log << "Entering presetShiftRegisterOutputs.......()\n";
	presetShiftRegisterOutputs();
	Log << "Exiting ....presetShiftRegisterOutputs()\n";
	// return (status);
	Log << "WriteToLCD : system_set_reset, SendCommand \n";
	writeToLCD(system_set_reset, SendCommand);
	Log << "WriteToLCD : System Reset-done!";

	//      wait 20ms after power up
	Sleep(20);
	//      write system_set_reset with RS = 0
		Log << "WriteToLCD : system_set_reset, SendCommand \n";
	writeToLCD(system_set_reset, SendCommand);
	//      wait 5ms
	Sleep(5);
	//      write system_set_reset with RS = 0 again
		Log << "WriteToLCD : system_set_reset, SendCommand \n";
	writeToLCD(system_set_reset, SendCommand);
	//     wait 5ms
	Sleep(5);
		Log << "WriteToLCD : system_set_reset, SendCommand \n";
	//      write system_set_reset with RS = 0 third time
	writeToLCD(system_set_reset, SendCommand);
	//      wait 5ms
	Sleep(5);
	//      write system_set_8_bit with RS = 0 (sets interface to 8 bits 2 lines)
	Log << "WriteToLCD : system_set_8_bit, SendCommand\n";
	writeToLCD(system_set_8_bit, SendCommand);
	//      wait 5ms
	Sleep(5);
	//      write display_off with RS = 0 (dont shift display hide cursor)
		Log << "WriteToLCD : display_off, SendCommand \n";
	writeToLCD(display_off, SendCommand);
	//      wait 5ms
	Sleep(5);
	//     write clear_lcd with RS = 0 (clear and home)
	Log << "WriteToLCD : clear_lcd, SendCommand \n";
	writeToLCD(clear_lcd, SendCommand);
	//      wait 5ms
	Sleep(5);
	//      write entry_mode with RS = 0 (move cursor to right direction)
	Log << "WriteToLCD : entry_mode, SendCommand \n";
	writeToLCD(entry_mode, SendCommand);
	//      wait 5ms
	Sleep(5);
	//      write display_on with RS = 0 (turn on display)
	 Log << "WriteToLCD : display_on, SendCommand \n";
	writeToLCD(display_on, SendCommand);
	//      wait 5ms
	Sleep(5);
	
	 Log <<  "Done Opening device : " << status << "\n";

	return status;
}

FT_STATUS DP_Lcd_Backpack::Open(PVOID pvDevice)
{
	FT_STATUS status;
	if (!m_pOpen)
	{
			
		Log << "FT_Open is not Valid\n";
		return FT_INVALID_HANDLE;
	}
	status= (*m_pOpen)(pvDevice, &m_ftHandle );
	
	Log << "FT_Open is Valid, Returned Status after opening device:  " << pvDevice << ", Status returned = " << status << "\n";
	

	return status;
}	

FT_STATUS DP_Lcd_Backpack::Close()
{
	FT_STATUS status;
	if (!m_pClose)
	{

		Log << "FT_Close is not Valid\n";
		return FT_INVALID_HANDLE;
	}
	status=  (*m_pClose)(m_ftHandle );

	Log << "FT_Close is Valid, Status:  " << status << "\n";
	
	Log.close();


	return status;
}	
FT_STATUS DP_Lcd_Backpack::ResetDevice()
{
	FT_STATUS status;
	if (!m_pResetDevice)
	{

		Log << "FT_ResetDevice is not Valid\n";
		return FT_INVALID_HANDLE;
	}
	status= (*m_pResetDevice)(m_ftHandle );
	Log << "FT_ResetDevice is Valid, Status:  " << status << "\n";
	

	return status;
}	

void DP_Lcd_Backpack::initializeBitMask()
{
	////////////////////////////////////////////////////////////////////////////
	// Mask constructors
	////////////////////////////////////////////////////////////////////////////
	D0mask = (UInt16)(pow((double)2, (int) LCD_D0));
	D1mask = (UInt16)(pow((double)2, (int) LCD_D1));
	D2mask = (UInt16)(pow((double)2, (int) LCD_D2));
	D3mask = (UInt16)(pow((double)2, (int) LCD_D3));
	D4mask = (UInt16)(pow((double)2, (int) LCD_D4));
	D5mask = (UInt16)(pow((double)2, (int) LCD_D5));
	D6mask = (UInt16)(pow((double)2, (int) LCD_D6));
	D7mask = (UInt16)(pow((double)2, (int) LCD_D7));
	RSmask = (UInt16)(pow((double)2, (int) LCD_RS));
	RWmask = (UInt16)(pow((double)2, (int) LCD_RW));
	Emask = (UInt16)(pow((double)2, (int) LCD_E));

	CTL3mask = (UInt16)(pow((double)2, (int) CTL3));
	CTL4mask = (UInt16)(pow((double)2, (int) CTL4));
	CTL5mask = (UInt16)(pow((double)2, (int)CTL5));
	CTL6mask = (UInt16)(pow((double)2, (int)CTL6));
	CTL7mask = (UInt16)(pow((double)2, (int) CTL7));

	MOSImask = (byte)(pow((double) 2, (int) MOSI));
	MISOmask = (byte)(pow((double) 2, (int) MISO));
	RCLKmask = (byte)(pow((double) 2, (int) RCLK));
	SRCLKmask = (byte)(pow((double) 2, (int)SRCLK));
	CLRmask = (byte)(pow((double) 2, (int) CLR));
	Gmask = (byte)(pow((double) 2, (int) G));
	BLmask = (byte)(pow((double) 2, (int) BL));
	FAULTmask = (byte)(pow((double) 2, (int) FAULT));

	DefaultMask = 0;  // default values

	FT232Routputs = 0; // outputs
	
}

void DP_Lcd_Backpack::Initialize_SPI_Constants()
{
	DefaultMask = (byte)(CLRmask | BLmask);  // default values are CLR and BL+ high all others low.

	FT232Routputs = (byte)(MOSImask | RCLKmask | SRCLKmask | CLRmask | Gmask | BLmask); // set outputs

}

FT_STATUS DP_Lcd_Backpack::ListDevices(PVOID pArg1, PVOID pArg2, DWORD dwFlags)
{
	if (!m_pListDevices)
	{
		Log << "FT_ListDevices is not valid! \n "; 
		return FT_INVALID_HANDLE;
	}
	Log << "FT_ListDevices: OK " << pArg1 << " , " << pArg2 << " , " << dwFlags << " \n "; 
	return (*m_pListDevices)(pArg1, pArg2, dwFlags);
}	

FT_STATUS DP_Lcd_Backpack::SetLatencyTimer(UCHAR pArg1)
{
	if (!m_pSetLatencyTimer)
	{
		Log << "FT_SetLatencyTimer is not valid! \n "; 
		return FT_INVALID_HANDLE;
	}
	Log << "FT_SetLatencyTimer: OK " << pArg1 << " \n "; 
	return (*m_pSetLatencyTimer)( m_ftHandle,pArg1);
}	

FT_STATUS DP_Lcd_Backpack::SetBitMode(UCHAR pArg1,UCHAR pArg2)
{
	if (!m_pSetBitMode)
	{
		Log << "FT_SetBitModer is not valid! \n "; 
		return FT_INVALID_HANDLE;
	}
	Log << "FT_SetBitMode: OK " << pArg1 << " , " << pArg2 << " \n "; 
	return (*m_pSetBitMode)( m_ftHandle,pArg1,pArg2);
}	

FT_STATUS DP_Lcd_Backpack::SetBaudRate(DWORD dwArg1)
{
	if (!m_pSetBaudRate)
	{
		Log << "FT_SetBaudRate is not valid! \n "; 
		return FT_INVALID_HANDLE;
	}
	Log << "FT_SetBaudRate: OK " << dwArg1 << " \n "; 
	return (*m_pSetBaudRate)( m_ftHandle,dwArg1);
}	

void DP_Lcd_Backpack::writeToLCD(byte dataToWrite, bool dataCommand) // dataCommand is true for data.
{
	uint outDataLength = 16;
	byte outPacket[0xFF];
	byte outPacket1[0xFF];
	byte outPacket2[0xFF];
	byte outPacket3[0xFF];
	uint outPacketLength = 0;
	uint outPacketLength1 = 0;
	uint outPacketLength2 = 0;
	uint outPacketLength3 = 0;
	Log << "Received by func writeToLCD( " << dataToWrite << " , " << dataCommand << ")\n";
	//-------------------------------------
	// remaps data as per hardware
	//-------------------------------------
	uint RemappedWord = ReMap(dataToWrite);     // remaps data
	// D4,D3,D2,D1,D0,C2,C1,C0,C7,C6,C5,C4,C3,D7,D6,D5. generic map
	// D4,D3,D2,D1,D0, E,RW,RS,C7,C6,C5,C4,C3,D7,D6,D5. specific map
	if (dataCommand)
		RemappedWord = RemappedWord | RSmask;   // sets RS signal to one if data
	//-------------------------------------
	// makes three packets
	//-------------------------------------
	uint outData = RemappedWord;

	Log << ":writeToLCD to makeSPIPacket( " << outData << " , " <<  outDataLength << " ,  " << outPacket1<< " , " << &outPacketLength1 << ") \n";
	makeSPIPacket(outData, outDataLength, outPacket1, &outPacketLength1);  // makes packet1

	outData = RemappedWord | Emask;                                             // sets E signal
	
	Log << ":writeToLCD to makeSPIPacket( " << outData << " , " <<  outDataLength << " ,  " << outPacket2 << " , " << &outPacketLength2 << ") \n";

	makeSPIPacket(outData, outDataLength,outPacket2, &outPacketLength2);  // makes packet2

	outData = RemappedWord;                                                     // resets E signal
	Log << ":writeToLCD to makeSPIPacket( " << outData << " , " <<  outDataLength << " ,  " << outPacket3 << " , " << &outPacketLength3 << ") \n";
	makeSPIPacket(outData, outDataLength, outPacket3,&outPacketLength3);  // makes packet3

	//BlockCopy(Array^ src,	int srcOffset,Array^ dst, int dstOffset, int count)

	for (byte i=0;i < outPacketLength1;i++)
	{			
	//System.Buffer.BlockCopy(outPacket1, 0, outPacket, 0, (int)outPacketLength1);
		outPacket[i]=outPacket1[i];
	
	}
	for (byte i=0;i <outPacketLength2;i++)
	{		
	//System.Buffer.BlockCopy(outPacket2, 0, outPacket, (int)outPacketLength1 - 1, (int)outPacketLength2);
	outPacket[outPacketLength1 - 1+i] = outPacket2[i];
	}

	for (byte i=0; i< outPacketLength3; i++)
	{	
	//System.Buffer.BlockCopy	(outPacket3, 0, outPacket, (int)(outPacketLength1 - 1 + outPacketLength2 - 1), (int)outPacketLength3);
		outPacket[outPacketLength1-1+outPacketLength2-1+i]=outPacket3[i];
	
	}
	//outPacket1.Concat(outPacket, 0);
	//outPacket2.CopyTo(outPacket, 0);
	//outPacket3.CopyTo(outPacket, 0);
	outPacketLength = (outPacketLength1-1) + (outPacketLength2-1) + (outPacketLength3-1);

	//-------------------------------------
	// sends three packets
	//-------------------------------------
	Log << "Inside writetoLCD: calling writeSPIPacket(" << outPacket << " ,  " << outPacketLength << ")\n";
	writeSPIPacket(outPacket, outPacketLength);                                 // sends packet
	//writeSPIPacket(outPacket1, outPacketLength);                                 // sends packet
	//writeSPIPacket(outPacket2, outPacketLength);                                 // sends packet
	//writeSPIPacket(outPacket3, outPacketLength);                                 // sends packet
}

uint DP_Lcd_Backpack::ReMap(byte LCDdata)     // remaps data byte to positions required by '595 output
{
	// 15,14,13,12,11,10,09,08,07,06,05,04,03,02,01,00
	//   ,  ,  ,  ,  ,  ,  ,  ,D7,D6,D5,D4,D3,D2,D1,D0.

	uint temp = (uint)(LCDdata & 0x1F) << 11;
	// D4,D3,D2,D1,D0,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  .

	uint RemappedWord = (uint)(LCDdata & 0xE0) >> 5;
	//   ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,D7,D6,D5.

	RemappedWord = RemappedWord | temp;
	// D4,D3,D2,D1,D0,  ,  ,  ,  ,  ,  ,  ,  ,D7,D6,D5.
	Log << "ReMap:  " << RemappedWord << "\n";
	return RemappedWord;
}

FT_STATUS DP_Lcd_Backpack::writeSPIPacket(byte *outPacket, uint outLength)
{
	FT_STATUS status;
	uint lBytesDone = 0;


	status = Purge(0x03);

		if (status != FT_OK)
		{
			if (!SIM) {
			    return (status);
			}
		}
	

	Log << "At WriteSPIPacket, Calling func: Write  with outPacket = " << outPacket << ", outLength = " << outLength << ", lBytesDone = " << lBytesDone << "\n";
	status = Write(outPacket,  outLength,  (LPDWORD) lBytesDone);
	
	if (status != FT_OK)
	{
		return (status);
	}
	return (status);
}

FT_STATUS DP_Lcd_Backpack::Write(LPVOID lpvBuffer, DWORD dwBuffSize, LPDWORD lpdwBytes)
{
	if (!m_pWrite)
	{
		Log << "FT_Write is not valid! \n"; 
		return FT_INVALID_HANDLE;
	}
	Log << "FT_Write is valid: m_ftHandle= " << m_ftHandle << ", lpvBuffer= " << lpvBuffer <<  ", dwBuffSize= " << dwBuffSize << ", lpdwBytes= " << lpdwBytes << "\n"; 
	return (*m_pWrite)(m_ftHandle, lpvBuffer, dwBuffSize, lpdwBytes);
}	

  //  public void makeSPIPacket(uint inData, uint inDataLength, ref byte[] outData, ref uint outDataLength)
void DP_Lcd_Backpack::makeSPIPacket(uint inData, uint inDataLength, byte *outData, uint *outDataLength)
{
	
	Log << "Receive inside Function: makeSPIPacket( " << inData << " , " <<  inDataLength << " , " <<  outData  << " ,  " << outDataLength << ") \n"; 
	
	int i, k;
	uint j;

	byte packet[0xFF];
	// byte sBuffer[0xFF];


	k = (int)inDataLength - 1;
	j = 0;

	if (BacklightOn)                                                        // test for backlight on
		DefaultMask = (byte)(DefaultMask & (~BLmask));                      // set bit as necessary
	else
		DefaultMask = (byte)(DefaultMask | BLmask);

	packet[j++] = DefaultMask;                                              // start with the Default states     
	Log << "packet default mask = " << setbase(16) <<  packet[j-1] << "\n";

	for (i = k; i >= 0; i--)                                                // walk through data
	{
		if (((uint)(pow((double)2,(int) i)) & inData) > 0)                          // and check for one
		{
			packet[j++] = (byte)(DefaultMask | MOSImask);                   // set Defaults plus MOSI = 1
			packet[j++] = (byte)(DefaultMask | MOSImask | SRCLKmask);       // set Defaults plus MOSI = 1 plus SRCLK = 1
		}
		else                                                                // and if zero
		{
			packet[j++] = (byte)(DefaultMask);                              // set Defaults plus MOSI = 0
			packet[j++] = (byte)(DefaultMask | SRCLKmask);                  // set Defaults plus SRCLK = 1
		}
		
		 
	}
	packet[j++] = (byte)(DefaultMask | RCLKmask);                          // set Defaults plus RCLK = 1

	packet[j++] = (byte)(DefaultMask);                                     // set Defaults 
	if (SIM) {
		Log << "Packet[] value:  ";
		for (uint x= 0; x < j; x++) {
			Log << "[" << packet[x] << "]";

		}
		Log << "\n  j =  " << j << "\n";
	}
	
	*outDataLength = j;
	
	outData = packet;

	Log << " Exiting Function: makeSPIPacket OutDataLength= " << outDataLength << ", outData = " << outData << "\n";

}

FT_STATUS DP_Lcd_Backpack::Purge(ULONG dwMask)
{
	if (!m_pPurge)
	{
		Log << "FT_Purge is not valid!\n"; 
		return FT_INVALID_HANDLE;
	}

	return (*m_pPurge)(m_ftHandle, dwMask);
}	

void DP_Lcd_Backpack::presetShiftRegisterOutputs()
{
	byte  outPacket[255];
	uint outDataLength = 0;
	uint inData = 0x000;
	uint inDataLength = 16;
	Log << "Sending to makeSPIPacket with params (" <<  inData <<" , " << inDataLength << " , "  << outPacket << " , " << &outDataLength << "\n";
	makeSPIPacket(inData, inDataLength, outPacket, &outDataLength);
	Log << "Got Value back From makeSPIPacket with (" <<  outPacket << " , " << outDataLength << ")\n";
	writeSPIPacket(outPacket, outDataLength);
	Log << "writeSPIPacket( " << outPacket << " , " <<  outDataLength << ") \n"; 
	}
