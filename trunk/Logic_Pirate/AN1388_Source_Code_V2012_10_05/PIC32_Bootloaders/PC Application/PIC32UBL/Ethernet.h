#pragma once
#include <winsock.h>
class CEthernet
{
private:
	WSADATA	wsaData;
	SOCKET	SendSocket;
	sockaddr_in RecvAddr;
	

public:
// Constructor
	CEthernet(void)
	{
		SendSocket = INVALID_SOCKET;

	}


// Destructor
	~CEthernet(void)
	{
		// if comport is already opened close it.
		if(SendSocket != INVALID_SOCKET)
		{
			CloseUdpPort();
		}
	}

	
	BOOL OpenUdpPort(USHORT, ULONG);
	void CloseUdpPort(void);
	void SendUdpPort(BYTE*, INT);
	USHORT ReadUdpPort(BYTE*, INT);
	BOOL GetSocketOpenStatus(void);
};
