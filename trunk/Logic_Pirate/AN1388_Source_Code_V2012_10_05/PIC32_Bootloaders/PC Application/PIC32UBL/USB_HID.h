#pragma once

extern "C" {
#include <setupapi.h>
}

typedef struct _HIDD_ATTRIBUTES
{
	ULONG Size; // = sizeof (struct _HIDD_ATTRIBUTES)
	USHORT VendorID;
	USHORT ProductID;
	USHORT VersionNumber;
} HIDD_ATTRIBUTES, *PHIDD_ATTRIBUTES;



typedef  _SP_DEVICE_INTERFACE_DATA SP_DEVICE_INTERFACE_DATA;//, *PSP_DEVICE_INTERFACE_DATA;


typedef BOOL (__stdcall *PtrHidD_GetAttributes)(HANDLE, PHIDD_ATTRIBUTES);
typedef VOID (__stdcall *PtrHidD_GetHidGuid)(LPGUID);


class CUsbHid
{
private:
	
	BOOL HidDllLoaded;
	
	HINSTANCE HID_dll;
	PtrHidD_GetAttributes HidD_GetAttributes;
	PtrHidD_GetHidGuid HidD_GetHidGuid;
	
	GUID HidGuid;
	HDEVINFO DeviceInfoSet;
	HANDLE WriteDeviceHandle;
	HANDLE ReadDeviceHandle;
	BOOL DeviceFound;
public:   

	// Constructor
	CUsbHid(void)
	{
		//Load the HID library (This is a standard dll from Microsoft Windows)
		HID_dll = LoadLibrary("HID.DLL");

		if(HID_dll != NULL)
		{
			//Update the API pointers from HID.dll
			HidD_GetHidGuid = (PtrHidD_GetHidGuid) GetProcAddress(HID_dll, "HidD_GetHidGuid");
			HidD_GetAttributes = (PtrHidD_GetAttributes) GetProcAddress(HID_dll, "HidD_GetAttributes");
			HidDllLoaded = true;
		}
		else
		{
			
			HidDllLoaded = false; 
			
		}

		// Initialize read and write handle to NULL
		WriteDeviceHandle = NULL;
		ReadDeviceHandle = NULL;
	}

	// Destructor
	~CUsbHid(void)
	{
		HidDllLoaded = false;
		// Set read and write handle to NULL
		WriteDeviceHandle = NULL;
		ReadDeviceHandle = NULL;
		// Set device found to false.
		DeviceFound = FALSE;
	}

	BOOL OpenUSBDevice(UINT vid, UINT pid, HWND hwnd);
	BOOL WriteUSBDevice(CHAR *buffer, INT bufflen);
	USHORT ReadUSBDevice(CHAR* buffer, INT bufflen);
	BOOL GetPortOpenStatus(VOID);
	VOID ClosePort(VOID);
	BOOL OnDeviceChange(char* path);

};
