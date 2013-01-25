#include "stdafx.h"


#include "Ethernet.h"
#include "ComPort.h"
#include "Hex.h"
#include "USB_HID.h"
#include "BootLoader.h"
#include "PIC32UBL.h"
#include "PIC32UBLDlg.h"



#include <windows.h>
#include <wtypes.h>
//#define WINVER  0x500
#include <dbt.h>
//#include <initguid.h>
#include <Setupapi.h>
#define USB_BUFFER_SIZE 64
static CHAR DevicePath[500]; 

HDEVNOTIFY DeviceNotificationHandle;

/****************************************************************************
 *  Open USB device
 *
 * \param  vid: Vendor Id 
 * \param  pid: Product Id    
 * \param 		
 * \return         
 *****************************************************************************/
BOOL CUsbHid::OpenUSBDevice(UINT vid, UINT pid, HWND hwnd)
{
	BOOL Result;
	BOOL DeviceAttached;
	SP_DEVICE_INTERFACE_DATA MyDeviceInterfaceData;
	DWORD DeviceIndex = 0;
	ULONG Length;
	PSP_DEVICE_INTERFACE_DETAIL_DATA DetailData;
	HIDD_ATTRIBUTES Attributes;
	
	DEV_BROADCAST_DEVICEINTERFACE  DevBroadcastDeviceInterface;
	
	
	// Initialize device found to false.
	DeviceFound = FALSE;

	

	//Obtain the device interface GUID for the HID class
    HidD_GetHidGuid(&HidGuid);
	
	// Requesting a pointer to a device information set
	DeviceInfoSet = SetupDiGetClassDevs(&HidGuid, NULL, NULL, DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
	
	MyDeviceInterfaceData.cbSize = sizeof(MyDeviceInterfaceData);
	
	// Get device interface data. Loop to get device interface data of all the attached devices.
	do{
		DeviceAttached = SetupDiEnumDeviceInterfaces(DeviceInfoSet, 0, &HidGuid, DeviceIndex, &MyDeviceInterfaceData);
		DeviceIndex++;

		if(DeviceAttached) // A device is found
		{
            // Get the size of the DeviceInterfaceData
			Result = SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &MyDeviceInterfaceData, NULL, 0, &Length, NULL);

			
			DetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);

			DetailData -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			// Get the structure that contains the device path name.
			Result = SetupDiGetDeviceInterfaceDetail(DeviceInfoSet,&MyDeviceInterfaceData,DetailData,Length, &Length, NULL);
			
			

			// get device handle
			WriteDeviceHandle=CreateFile(DetailData->DevicePath, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 
									(LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING,0/*FILE_FLAG_OVERLAPPED*/, NULL);


			// get device handle
			ReadDeviceHandle=CreateFile(DetailData->DevicePath, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 
									(LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING,FILE_FLAG_OVERLAPPED, NULL);


			
			// Set the Size member to the number of bytes
			// in the structure.
			Attributes.Size = sizeof(Attributes);
			// Get the attribute
			Result = HidD_GetAttributes(ReadDeviceHandle,&Attributes);
			
			// Check the vendor ID and product ID.
			if ((Attributes.VendorID == vid) && (Attributes.ProductID == pid))
			{
				DeviceFound = TRUE;
				// Save the path.
				strcpy(DevicePath, DetailData->DevicePath);
				
				// Register device change notification.
				DevBroadcastDeviceInterface.dbcc_size = sizeof(DevBroadcastDeviceInterface);
				DevBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
				DevBroadcastDeviceInterface.dbcc_classguid = HidGuid;
				DeviceNotificationHandle = RegisterDeviceNotification(hwnd, &DevBroadcastDeviceInterface, DEVICE_NOTIFY_WINDOW_HANDLE);

			}
		}


	}while(DeviceAttached && (DeviceFound == FALSE));

	if(!DeviceFound)
	{
		CString error;
		error.FormatMessage("USB Device with VID= 0x%1!X! and PID= 0x%2!X! is not found", vid, pid);
		MessageBox(NULL, error, NULL, MB_ICONERROR);
	}


	return DeviceFound;
}


/****************************************************************************
 *  Write USB device
 *
 * \param  *buffer: Pointer to the buffer 
 * \param  bufflen: Buffer length    
 * \param 		
 * \return         
 *****************************************************************************/
BOOL CUsbHid::WriteUSBDevice(CHAR *buffer, INT bufflen)
{
	BOOL Result = 0;
	DWORD BytesWritten;
	CHAR UsbReport[USB_BUFFER_SIZE + 1];

	if(DeviceFound == FALSE)
	{
		return 0;
	}

	if(WriteDeviceHandle != NULL)
	{
		while(bufflen > 0)
		{
			// Set output buffer to 0xFF.
			memset(UsbReport, 0xFF,  sizeof(UsbReport));
			UsbReport[0] = 0;  // Report ID = 0
			memcpy(&UsbReport[1], buffer, USB_BUFFER_SIZE);
			bufflen -= USB_BUFFER_SIZE;
/*			if(bufflen > 0)
			{
				//Sleep(5); // sleep for 30ms. (allow sometime betweeen frames)
			}*/
			buffer = (CHAR *)&buffer[USB_BUFFER_SIZE];
			// WriteFile is a blocking call. It will be a good design if made a non-blocking.
			Result = WriteFile(WriteDeviceHandle, UsbReport, USB_BUFFER_SIZE+1, &BytesWritten, NULL); 
		}

	}

	return Result;

}


/****************************************************************************
 *  Read USB device
 *
 * \param  *buffer: Pointer to the buffer 
 * \param  bufflen: Maximum size of the read buffer. (Not used, since USB buffer is always 64bytes)   
 * \param 		
 * \return         
 *****************************************************************************/
USHORT CUsbHid::ReadUSBDevice(CHAR* buffer, INT bufflen)
{

	CHAR UsbReport[USB_BUFFER_SIZE + 1];
	DWORD BytesRead = 0;
	DWORD Result;
	HANDLE hEventObject;
	OVERLAPPED HIDOverlapped;

	if(DeviceFound == FALSE)
	{
		return 0;
	}

	if(ReadDeviceHandle == NULL)
	{
		// Just return.
		return 0;
	}

	hEventObject = CreateEvent((LPSECURITY_ATTRIBUTES)NULL,	FALSE,	TRUE, 	"");
	HIDOverlapped.hEvent = hEventObject;
	HIDOverlapped.Offset = 0;
	HIDOverlapped.OffsetHigh = 0;
	// Set the first byte in the buffer to the Report ID.
	UsbReport[0] = 0;

		
	(void)ReadFile(ReadDeviceHandle, UsbReport,	USB_BUFFER_SIZE+1,	&BytesRead,	(LPOVERLAPPED) &HIDOverlapped);
    Result = WaitForSingleObject(hEventObject,	100);//100ms timeout period

	switch (Result)
	{
	case WAIT_OBJECT_0: 
		// Success;
		// Use the report data;
		memcpy(buffer, &UsbReport[1], USB_BUFFER_SIZE);
		return USB_BUFFER_SIZE;
		break;
	
	case WAIT_TIMEOUT: 
		// Timeout error;
		//Cancel the read operation.
		CancelIo(ReadDeviceHandle);
		break;
	
	default: 
		// Undefined error;
		//Cancel the read operation.
		CancelIo(ReadDeviceHandle);
		break;
	
	}

	

	//CloseHandle(ReadDeviceHandle);
	return 0;
}

/****************************************************************************
 *  Check if USB port is already opened.
 *
 * \param   
 * \param  
 * \param 		
 * \return         
 *****************************************************************************/
BOOL CUsbHid::GetPortOpenStatus(void)
{
	if(DeviceFound)
	{
		return true;
	}
	else
	{
		return false;
	}

}



/****************************************************************************
 *  Close port
 *
 * \param   
 * \param     
 * \param 		
 * \return         
 *****************************************************************************/
VOID CUsbHid::ClosePort(VOID)
{
	

	if(WriteDeviceHandle)
	{
		CloseHandle(WriteDeviceHandle);
	}
	if(ReadDeviceHandle)
	{
		CloseHandle(ReadDeviceHandle);
	}
	if(DeviceFound == TRUE)
	{
		// Initialize device found to false.
		DeviceFound = FALSE;
		UnregisterDeviceNotification(DeviceNotificationHandle);
	}
}



BOOL CUsbHid::OnDeviceChange(char *path)
{
	CString strPath, strDevPath;

	strPath = path;
	strDevPath = DevicePath;

	strPath.MakeLower();
	strDevPath.MakeLower();

	if(strPath == strDevPath)
	{
		//ClosePort();
		return(TRUE);

	}

	return FALSE;

}

/***************************End ********************************************/