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
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Virtual Flash.
#define KB (1024)
#define MB (KB*KB)

// 5 MB flash
static unsigned char VirtualFlash[5*MB]; 

#define BOOT_SECTOR_BEGIN 0x9FC00000
#define APPLICATION_START 0x9D000000
#define PA_TO_VFA(x)	(x-APPLICATION_START)
#define PA_TO_KVA0(x)   (x|0x80000000)

#define DATA_RECORD 		0
#define END_OF_FILE_RECORD 	1
#define EXT_SEG_ADRS_RECORD 2
#define EXT_LIN_ADRS_RECORD 4


/****************************************************************************
 * Loads hex file
 *
 * \param  
 * \param   
 * \param 
 * \return  true if hex file loads successfully      
 *****************************************************************************/
bool CHexManager::LoadHexFile(void)
{
	int iRet;
	char HexRec[255];
		

	CFileDialog fileDialog(TRUE,NULL,NULL,OFN_OVERWRITEPROMPT,"Hex File (*.hex)|*.hex|");
	iRet = fileDialog.DoModal();
	if(iRet != 1)
	{
		return false;
	}
    
    HexFilePath = fileDialog.GetPathName();
	
	// Open file
	HexFilePtr = fopen(HexFilePath, "r");

	if(HexFilePtr == NULL)
	{
		// Failed to open hex file.
		return false;
	}
	else
	{

		HexTotalLines = 0;
		while(!feof(HexFilePtr))
		{
			fgets(HexRec, sizeof(HexRec), HexFilePtr);
			HexTotalLines++;
		}

	}

	return true;
}


/****************************************************************************
 * Gets next hex record from the hex file
 *
 * \param  HexRec: Pointer to HexRec.
 * \param  BuffLen: Buffer Length 
 * \param 
 * \return Length of the hex record in bytes.  
 *****************************************************************************/
static char Ascii[1000];
unsigned short CHexManager::GetNextHexRecord(char *HexRec, unsigned int BuffLen)
{
	unsigned short len = 0;
	
	if(!feof(HexFilePtr))
	{
		fgets(Ascii, BuffLen, HexFilePtr);

		if(Ascii[0] != ':')
		{
			// Not a valid hex record.
			return 0;
		}
		// Convert rest to hex.
		len = ConvertAsciiToHex((void *)&Ascii[1], (void *)HexRec);

		HexCurrLineNo++;
		
	}	
	return len;
}

/****************************************************************************
 * Resets hex file pointer.
 *
 * \param  
 * \param   
 * \param 
 * \return  True if resets file pointer.     
 *****************************************************************************/
bool CHexManager::ResetHexFilePointer(void)
{
	// Reset file pointer.
	if(HexFilePtr == NULL)
	{
		return false;
	}
	else
	{
		fseek(HexFilePtr, 0, 0);
		HexCurrLineNo = 0;
		return true;
	}
}


/****************************************************************************
 * Converts ASCII to hex.
 *
 * \param  VdAscii: Hex Record in ASCII format.
 * \param  VdHexRec: Hex record in Hex format.
 * \param 
 * \return  Number of bytes in Hex record(Hex format)    
 *****************************************************************************/
unsigned short CHexManager::ConvertAsciiToHex(void *VdAscii, void *VdHexRec)
{
	char temp[5] = {'0','x',NULL, NULL, NULL};
	unsigned int i = 0;
	char *Ascii;
	char *HexRec;

	Ascii = (char *)VdAscii;
	HexRec = (char *)VdHexRec;

	while(1)
	{
		temp[2] = Ascii[i++];
		temp[3] = Ascii[i++];
		if((temp[2] == NULL) || (temp[3] == NULL))
		{
			// Not a valid ASCII. Stop conversion and break.
			i -= 2;
			break;			
		}
		else
		{
			// Convert ASCII to hex.
			sscanf(temp, "%x", HexRec);
			HexRec++;			
		}
	}

	return (i/2); // i/2: Because, an representing Hex in ASCII takes 2 bytes.
}


/****************************************************************************
 * Verifies flash
 *
 * \param  StartAddress: Pointer to program start address
 * \param  ProgLen: Pointer to Program length in bytes 
 * \param  crc : Pointer to CRC
 * \return      
 *****************************************************************************/
void CHexManager::VerifyFlash(unsigned int* StartAdress, unsigned int* ProgLen, unsigned short* crc)
{
	unsigned short HexRecLen;
	char HexRec[255];
	T_HEX_RECORD HexRecordSt;
	unsigned int VirtualFlashAdrs;
	unsigned int ProgAddress;
	
	// Virtual Flash Erase (Set all bytes to 0xFF)
	memset((void*)VirtualFlash, 0xFF, sizeof(VirtualFlash));


	// Start decoding the hex file and write into virtual flash
	// Reset file pointer.
	fseek(HexFilePtr, 0, 0);

	// Reset max address and min address.
	HexRecordSt.MaxAddress = 0;
	HexRecordSt.MinAddress = 0xFFFFFFFF;

    while((HexRecLen = GetNextHexRecord(&HexRec[0], 255)) != 0)
	{
		HexRecordSt.RecDataLen = HexRec[0];
		HexRecordSt.RecType = HexRec[3];	
		HexRecordSt.Data = (unsigned char*)&HexRec[4];

		switch(HexRecordSt.RecType)
		{

			case DATA_RECORD:  //Record Type 00, data record.
				HexRecordSt.Address = (((HexRec[1] << 8) & 0x0000FF00) | (HexRec[2] & 0x000000FF)) & (0x0000FFFF);
				HexRecordSt.Address = HexRecordSt.Address + HexRecordSt.ExtLinAddress + HexRecordSt.ExtSegAddress;
				
				ProgAddress = PA_TO_KVA0(HexRecordSt.Address);

				if(ProgAddress < BOOT_SECTOR_BEGIN) // Make sure we are not writing boot sector.
				{
					if(HexRecordSt.MaxAddress < (ProgAddress + HexRecordSt.RecDataLen))
					{
						HexRecordSt.MaxAddress = ProgAddress + HexRecordSt.RecDataLen;
					}

					if(HexRecordSt.MinAddress > ProgAddress)
					{
						HexRecordSt.MinAddress = ProgAddress;
					}
				
					VirtualFlashAdrs = PA_TO_VFA(ProgAddress); // Program address to local virtual flash address

					memcpy((void *)&VirtualFlash[VirtualFlashAdrs], HexRecordSt.Data, HexRecordSt.RecDataLen);
				}
				break;
			
			case EXT_SEG_ADRS_RECORD:  // Record Type 02, defines 4 to 19 of the data address.
				HexRecordSt.ExtSegAddress = ((HexRecordSt.Data[0] << 16) & 0x00FF0000) | ((HexRecordSt.Data[1] << 8) & 0x0000FF00);				
				HexRecordSt.ExtLinAddress = 0;
				break;
					
			case EXT_LIN_ADRS_RECORD:
				HexRecordSt.ExtLinAddress = ((HexRecordSt.Data[0] << 24) & 0xFF000000) | ((HexRecordSt.Data[1] << 16) & 0x00FF0000);
				HexRecordSt.ExtSegAddress = 0;
				break;


			case END_OF_FILE_RECORD:  //Record Type 01
			default: 
				HexRecordSt.ExtSegAddress = 0;
				HexRecordSt.ExtLinAddress = 0;
				break;
		}	
	}

	HexRecordSt.MinAddress -= HexRecordSt.MinAddress % 4;
	HexRecordSt.MaxAddress += HexRecordSt.MaxAddress % 4;

	*ProgLen = HexRecordSt.MaxAddress - HexRecordSt.MinAddress;
	*StartAdress = HexRecordSt.MinAddress;
	VirtualFlashAdrs = PA_TO_VFA(HexRecordSt.MinAddress);
	*crc = CalculateCrc((char*)&VirtualFlash[VirtualFlashAdrs], *ProgLen);	
}

/********************End of file************************************************/