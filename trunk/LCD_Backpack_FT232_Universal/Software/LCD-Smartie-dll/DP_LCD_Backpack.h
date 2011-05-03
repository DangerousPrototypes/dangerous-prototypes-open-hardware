#include <string>
#include <Windows.h>
#include <WinVer.h>
#include <iostream>
#include "ftd2xx.h"
#define SIM  TRUE       // Simulation; in the absent of device, bypass all erros


#define LCD_D0  11
#define LCD_D1  12
#define LCD_D2  13
#define LCD_D3  14
#define LCD_D4  15
#define LCD_D5  00
#define LCD_D6  0x01
#define LCD_D7  0x02
#define LCD_RS  0x08
#define LCD_RW  0x09
#define LCD_E   10
#define LCD_E1  10      //
#define LCD_E2  0x03     // some of the larger displays require a two E signals
#define CTL3    0x03
#define CTL4    0x04
#define CTL5    0x05
#define CTL6    0x06
#define CTL7    0x07

#define TXD  0 
#define RXD  1 
#define RTS  2 
#define CTS  3 
#define DTR  4 
#define DSR  5 
#define DCD  6 
#define RI   7 

#define MOSI   0
#define MISO   1
#define RCLK   2
#define SRCLK  3
#define CLR    4
#define G      5
#define BL     6
#define FAULT  7

#define SendData  true
#define SendCommand  false


////////////////////////////////////////////////////////////////////////////
// LCD bit assignments
//
// 15,14,13,12,11,10,09,08,07,06,05,04,03,02,01,00
// D4,D3,D2,D1,D0,C2,C1,C0,C7,C6,C5,C4,C3,D7,D6,D5.
// D4,D3,D2,D1,D0, E,RW,RS,C7,C6,C5,C4,C3,D7,D6,D5.
//
////////////////////////////////////////////////////////////////////////////

#define LCD_D0  11
#define LCD_D1  12
#define LCD_D2  13
#define LCD_D3  14
#define LCD_D4  15
// #define LCD_D5  0x00
#define LCD_D6  0x01
#define LCD_D7  0x02
#define LCD_RS  0x08
#define LCD_RW  0x09
#define LCD_E   10
#define LCD_E1  10      //
#define LCD_E2  0x03     // some of the larger displays require a two E signals
#define CTL3    0x03
#define CTL4    0x04
#define CTL5    0x05
#define CTL6    0x06
#define CTL7    0x07

#define system_set_reset  0x30 // Reset code


////////////////////////////////////////////////////////////////////////////
// LCD Commands ( Refer to LCD Data Sheet ) RS = 0
////////////////////////////////////////////////////////////////////////////
#define write_data                0x00 // With RS = 1
#define clear_lcd                 0x01 // Clear Display
#define return_home               0x02 // Cursor to Home position
#define entry_mode                0x06 // Normal entry mode
#define entry_mode_rev            0x04 // Normal entry mode  -reverse direction
#define entry_mode_scroll         0x07 // - with shift
#define entry_mode_scroll_rev     0x05 // reverse direction
#define display_off               0x08 // Display off
#define display_on                0x0C // Display ON - 2 line mode
#define cursor_off                0x0C // Switch Cursor OFF
#define cursor_on                 0x0E // Switch Cursor ON
#define cursor_blink_on           0x0F // Cursor plus blink

#define cursor_shift_left          0x10 // Move cursor left
#define cursor_shift_right        0x14 // Move cursor right
#define display_shift_left        0x18 // Scroll display left
#define display_shift_right       0x1C // Scroll display right

#define system_set_4_bit          0x28 // 4 bit data mode 2 line ( 5x7 font )

#define system_set_reset          0x30 // Reset code
#define system_set_8_bit          0x38 // 8 bit data mode 2 line ( 5x7 font )

// DDRAM addressing - add column number to base.

#define set_dd_line1              0x80 // Line 1 position 1
#define set_dd_line2              0xC0 // Line 2 position 1
#define set_dd_line3              0x94 // Line 3 position 1  
#define set_dd_line4              0xD4 // Line 4 position 1  



typedef unsigned int UInt16;
typedef UINT uint;

class DP_Lcd_Backpack {
private:
	int flag;
	int i,j,k;      // general purpose



	protected: 

		UInt16 D0mask;
		UInt16 D1mask;
		UInt16 D2mask;
		UInt16 D3mask;
		UInt16 D4mask;
		UInt16 D5mask;
		UInt16 D6mask;
		UInt16 D7mask;
		UInt16 RSmask;
		UInt16 RWmask;
		UInt16 Emask;

		UInt16 CTL3mask;
		UInt16 CTL4mask;
		UInt16 CTL5mask;
		UInt16 CTL6mask;
		UInt16 CTL7mask;	

		byte MOSImask;
		byte MISOmask;
		byte RCLKmask;
		byte SRCLKmask;
		byte CLRmask;
		byte Gmask;
		byte BLmask;
		byte FAULTmask;

		byte DefaultMask;

		byte FT232Routputs;
		
	    bool BacklightOn; 

	  HMODULE m_hmodule;
	  FT_HANDLE m_ftHandle;
	
	  typedef FT_STATUS (WINAPI *PtrToOpen)(PVOID, FT_HANDLE *); 
	  PtrToOpen m_pOpen; 
	  FT_STATUS Open(PVOID);

	  typedef FT_STATUS (WINAPI *PtrToOpenEx)(PVOID, DWORD, FT_HANDLE *); 
	  PtrToOpenEx m_pOpenEx; 
	  FT_STATUS OpenEx(PVOID, DWORD);

	  typedef FT_STATUS (WINAPI *PtrToListDevices)(PVOID, PVOID, DWORD);
	  PtrToListDevices m_pListDevices; 
	  FT_STATUS ListDevices(PVOID, PVOID, DWORD);

	  typedef FT_STATUS (WINAPI *PtrToClose)(FT_HANDLE);
	  PtrToClose m_pClose;
	 // FT_STATUS Close();

	  typedef FT_STATUS (WINAPI *PtrToRead)(FT_HANDLE, LPVOID, DWORD, LPDWORD);
	  PtrToRead m_pRead;
	  FT_STATUS Read(LPVOID, DWORD, LPDWORD);

	  typedef FT_STATUS (WINAPI *PtrToWrite)(FT_HANDLE, LPVOID, DWORD, LPDWORD);
	  PtrToWrite m_pWrite;
	  FT_STATUS Write(LPVOID, DWORD, LPDWORD);

	  typedef FT_STATUS (WINAPI *PtrToResetDevice)(FT_HANDLE);
	  PtrToResetDevice m_pResetDevice;
	//  FT_STATUS ResetDevice();

	  typedef FT_STATUS (WINAPI *PtrToPurge)(FT_HANDLE, ULONG);
	  PtrToPurge m_pPurge;
	  FT_STATUS Purge(ULONG);

	  typedef FT_STATUS (WINAPI *PtrToSetTimeouts)(FT_HANDLE, ULONG, ULONG);
	  PtrToSetTimeouts m_pSetTimeouts;
	  FT_STATUS SetTimeouts(ULONG, ULONG);

	  typedef FT_STATUS (WINAPI *PtrToGetQueueStatus)(FT_HANDLE, LPDWORD);
	  PtrToGetQueueStatus m_pGetQueueStatus;
	  FT_STATUS GetQueueStatus(LPDWORD);

	  //	status = FT_SetLatencyTimer(m_ftHandle, 2);

	  typedef FT_STATUS (WINAPI *PtrToSetLatencyTimer)(FT_HANDLE,UCHAR);
	  PtrToSetLatencyTimer m_pSetLatencyTimer;
	  FT_STATUS SetLatencyTimer(UCHAR);

	  //ftStatus = FT_SetBitMode(m_ftHandle, 0,0);
	  typedef FT_STATUS (WINAPI *PtrToSetBitMode)(FT_HANDLE,UCHAR,UCHAR);
	  PtrToSetBitMode m_pSetBitMode;
	  FT_STATUS SetBitMode(UCHAR,UCHAR);

	  typedef FT_STATUS (WINAPI *PtrToSetBaudRate)(FT_HANDLE,DWORD);
	  PtrToSetBaudRate m_pSetBaudRate;
	  FT_STATUS SetBaudRate(DWORD);





public:
	  DP_Lcd_Backpack();
	~ DP_Lcd_Backpack();
	  bool InitializeFTDI_DLL();
	  void LoadDll();
	
	  void initializeBitMask();
	  void Initialize_SPI_Constants();
	  void writeToLCD(byte , bool );
	  uint ReMap(byte); 
	  void makeSPIPacket(uint, uint, byte *, uint * ); 
	  void presetShiftRegisterOutputs();
	  FT_STATUS OpenDevice(char *);
	  FT_STATUS writeSPIPacket(byte *outPacket, uint outLength); 
	  FT_STATUS Close();
	  FT_STATUS ResetDevice();
	

};

