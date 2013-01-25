#pragma once

// Notify message IDs
#define WM_USER_BOOTLOADER_RESP_OK WM_USER+1
#define WM_USER_BOOTLOADER_NO_RESP WM_USER+2

// Trasnmission states
#define FIRST_TRY 0
#define RE_TRY 1

// Commands
typedef enum
{
	READ_BOOT_INFO = 1,
	ERASE_FLASH, 
	PROGRAM_FLASH,
	READ_CRC,
	JMP_TO_APP
	
}T_COMMANDS;	

typedef enum
{
	USB,
	COM,
	ETH
}T_PORTTYPE;
	

// Main Bootloader class
class CBootLoader
{

private:
	CWinThread *BtlThread;
	HWND m_hWnd;
	char TxPacket[1000];
	unsigned short TxPacketLen;
	char RxData[255];
	unsigned short RxDataLen;
	unsigned short RetryCount;

	bool RxFrameValid;
	unsigned char LastSentCommand;
	bool NoResponseFromDevice;
	unsigned int TxState;
	unsigned short MaxRetry;
	unsigned short TxRetryDelay;
	CHexManager HexManager;
	bool ResetHexFilePtr;
	UINT PortSelected;
	void WritePort(char *buffer, int bufflen);
	unsigned short ReadPort(char *buffer, int bufflen);
	

public:
	bool ExitThread;
	bool ThreadKilled; 
	CComPort ComPort;
	CUsbHid  UsbHid;
	CEthernet Ethernet;
	
	// Constructor
	CBootLoader()
	{
		BtlThread = NULL;
		// Initialization of some flags and variables
		RxFrameValid = false;
		NoResponseFromDevice = false;
		TxState = FIRST_TRY;
		RxDataLen = 0;
		ResetHexFilePtr = true;
	}

	// Destructor
	~CBootLoader()
	{
		ShutdownThread( );
	}

	void ShutdownThread( );
	void CreateRxTxThread(HWND);
	void TransmitTask(void);
	void ReceiveTask(void);	
	bool SendCommand(char cmd, unsigned short Retries, unsigned short RetryDelayInMs);	
	void BuildRxFrame(unsigned char*, unsigned short);
	void HandleResponse(void);	
	void StopTxRetries(void);
	void NotifyEvent(unsigned int lEvent);
	void GetRxData(char *buff);
	void GetProgress(int *Lower, int *Upper);
	void HandleNoResponse(void);
	unsigned short CalculateFlashCRC(void);
	bool LoadHexFile(void);
	void OpenPort(UINT portType, UINT comport, UINT baud, UINT vid, UINT pid, USHORT skt, ULONG ip, HWND hwnd);
	BOOL GetPortOpenStatus(UINT PortType);
	void ClosePort(UINT PortType);
	BOOL NotifyDeviceChange(UINT portType, char *devPath); 
	

	
};

extern unsigned short CalculateCrc(char *data, unsigned int len);



