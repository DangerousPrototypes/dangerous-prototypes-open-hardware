// Dangerous Prototypes FT232 LCD Backpack Display Driver for Smartie 
// 
// As a minimum, implement Init, Done, SetPosition, and Write functions to get an LCD up and running

#include <cstdio>
#include <fstream>
#include <String>
#include "ftd2xx.h"
#include "DP_LCD_Backpack.h"
#include "DP_LCD_FT232.H"

DP_Lcd_Backpack DP;

byte Line1Address = 0x00;
byte Line2Address = 0x40;
byte Line3Address = 0x14;
byte Line4Address = 0x54;

using namespace std;

ofstream LogFile("DP_LCD_FT232.log");


// +-----------------+
// ! DISPLAYDLL_Init !
// +-----------------+
//! Initializes the plugin.
//! All initialization stuff goes there: opening and configuring IO ports, device detection and probing...
//! Sets ok to 1 if initialization is successful, 0 otherwise.
//! Returns an error message in case of failure, NULL otherwise.

/*
Function: DISPLAYDLL_Init

Parameters: SizeX,SizeY : byte; StartupParameters : pchar; OK : pboolean; 

Result: none 

Function description: First function called when LCD Smartie starts a display 
or comes back from standby. First two parameters are bytes that describe the 
size that LCD Smartie believes the display to be, the third parameter are the 
startup parameters as a null terminated string, and the fourth parameter is a 
pointer to a boolean that the DLL can use to pass back success or failure of 
DLL startup. (For example, if the calling application, LCD Smartie, wants the 
driver to start a COM port that doesn't exist, pass back false to indicate the 
start of the COM port failed). 

*/

DLL_EXPORT(char *) DISPLAYDLL_Init(LCDS_BYTE size_x,LCDS_BYTE size_y,char *startup_parameters,LCDS_BOOL *ok) {

   FT_STATUS status;
   LogFile <<  "DISPLAYDLL_Init( " <<  size_x << "," << size_y << "," << startup_parameters<< "," << ok << ")\n";
   // load and initialize FT232 DLL 
   if(DP.InitializeFTDI_DLL()==OK) 
   {
		 LogFile << "DISPLAYDLL_Init:: Succesful Initialization!\n";
	
   }   
   // Open the hardware
   if (DP.OpenDevice(startup_parameters)==OK)
   {
		LogFile << "DISPLAYDLL_Init:: Successfully Opened the Device!\n";
		// reset the device
		LogFile << "Resetting Device ";
		 status=DP.ResetDevice();
		LogFile << "And Got status returned: " << status << "\n";

			
   }
   else
   {
	   LogFile << "DISPLAYDLL_INIT: OpenDevice Got error! \n";
   }
   if (SIM) {
	   LogFile << "SIMULATE: DISPLAYDLL_Init:: Successfully Opened the Device!\n";
	   // reset the device
	   LogFile << "Resetting Device ";
	   status=DP.ResetDevice();
	   LogFile << "SIMULATE: And Got status returned: " << status << "\n";
   }
	*ok=1;
	 return NULL;
}

// +-----------------------+
// ! DISPLAYDLL_DriverName !
// +-----------------------+
//! Returns the driver name.
//! The driver name is used by the driver selection GUI to identify the driver.
//! It's good practice to return a proper name and version for the driver so that
//! it can be clearly identified (or else we would have to rely on the plugin name
//! which is subject to modifications).
DLL_EXPORT(char *) DISPLAYDLL_DriverName(void) {
  static char plugin_name[]="Dangerous Prototypes LCD Backpack FT232 V0.1";
	LogFile <<"DISPLAYDLL_DriverName(void): Dangerous Prototypes LCD Backpack FT232 V0.1\n";
  return plugin_name;
}

// +------------------+
// ! DISPLAYDLL_Usage !
// +------------------+
//! Returns plugin usage hints.
//! The usage text describes the main plugin parameters and how they are assembled
//! in the parameter string (syntax indications).
DLL_EXPORT(char *) DISPLAYDLL_Usage(void) {
  static char plugin_usage[]="Set your USB ports";
	LogFile << "DISPLAYDLL_Usage(void): Set your USB ports\n";
  return plugin_usage;
}

// +------------------------------+
// ! DISPLAYDLL_DefaultParameters !
// +------------------------------+
//! Returns the plugin default parameters.
//! The default parameters string is used as parameter string after the driver
//! has been initialized.
DLL_EXPORT(char *) DISPLAYDLL_DefaultParameters(void) {
	static char plugin_default_parameters[]="USB";
	LogFile << " DISPLAYDLL_DefaultParameters(void): " << plugin_default_parameters  << "\n";
	return plugin_default_parameters;
}

// +------------------------+
// ! DISPLAYDLL_SetPosition !
// +------------------------+
//! Moves the display cursor at a given position.

/*
Function: DISPLAYDLL_SetPosition 

Parameters: X,Y : byte 

Result: none 

Function description: Tells LCD where to position the cursor for the next 
display command. For example, when LCD Smartie wants to update the second 
line on the display, it will call this command with 1,2 parameters. The 
coordinates are "1" based, meaning the upper left corner is 1,1. 


*/

DLL_EXPORT(void) DISPLAYDLL_SetPosition(LCDS_BYTE x,LCDS_BYTE y) {


	LogFile << "DISPLAYDLL_SetPosition(  x== " <<  x << " , y== " << y << ")\n";

	byte DisplayAddress;

	switch (x){
		//line 1  = 0,0
	   case 1: DisplayAddress = (byte)(0x80 | Line1Address);
			  break;
	   //line 2 =1,- 
	   case 2:  DisplayAddress = (byte)(0x80 | Line2Address);
			  break;
	   case 3:  DisplayAddress = (byte)(0x80 | Line3Address);
		   break;
	   case 4:  DisplayAddress = (byte)(0x80 | Line4Address);
		   break;
	   default: 
			 DisplayAddress = (byte)(0x80 | Line1Address);
			 LogFile << "Error in Set Position: " << x << ", " << y << "\n";

	}
	LogFile << "DISPLAYDLL_SetPosition: DisplayAddess:  " << DisplayAddress << "," << " SendCommand= " << SendCommand << ")\n";
	
	DP.writeToLCD(DisplayAddress, SendCommand);

	 

}

// +------------------+
// ! DISPLAYDLL_Write !
// +------------------+
//! Writes the given string on the display.
//! The string is displayed at the current cursor position (see DISPLAYDLL_SetPosition).
//! It is assumed that the cursor position has been set so that the string can fit.
/*
Function: DISPLAYDLL_Write 

Parameters: Str : pchar 

Result: none 

Function description: Write the null terminated string at the current 
cursor position. This is the primary function LCD Smartie uses to write to 
the display. 


*/

DLL_EXPORT(void) DISPLAYDLL_Write(char *str) {

	byte dataToWrite;
	LogFile << "DISPLAYDLL_Write( " << str << ")\n";

	int Len=strlen(str);
	LogFile << "String to write: " << str << "Length of String to Write to LCD: " << Len << " \n";
	for (int i=0;i < Len; i++)
	{
		dataToWrite = (byte)str[i];
	//	LogFile << "DISPLAYDLL_Write: dataToWrite (byte)  " << dataToWrite <<  ")\n";
		DP.writeToLCD(dataToWrite, SendData);
	}

	LogFile << "DISPLAYDLL_Write: Writen " << Len << " characters \n";
}

// +--------------------------+
// ! DISPLAYDLL_SetBrightness !
// +--------------------------+
DLL_EXPORT(void) DISPLAYDLL_SetBrightness(LCDS_BYTE brightness) {
	 LogFile << "DISPLAYDLL_SetBrightness(" <<  brightness << ")\n";
}

// +-----------------------+
// ! DISPLAYDLL_CustomChar !
// +-----------------------+
DLL_EXPORT(void) DISPLAYDLL_CustomChar(LCDS_BYTE chr,LCDS_BYTE *data) {
	LogFile <<"DISPLAYDLL_CustomChar(" << chr << "," << data << ")\n";
}

// +----------------------------+
// ! DISPLAYDLL_CustomCharIndex !
// +----------------------------+
DLL_EXPORT(LCDS_BYTE) DISPLAYDLL_CustomCharIndex(LCDS_BYTE index) {
	LogFile << "DISPLAYDLL_CustomCharIndex(" << index << ") \n";

  --index;
  if (0==index) index=8;
  return index;
}

// +-----------------+
// ! DISPLAYDLL_Done !
// +-----------------+

/*
Function: DISPLAYDLL_Done 

Parameters: None 

Result: none 

Function description: Called when LCD Smartie closes the display to enter 
standby or close the application 


*/
DLL_EXPORT(void) DISPLAYDLL_Done(void) {
	FT_STATUS ftStatus;
	LogFile <<"DISPLAYDLL_Done(void)\n";
	LogFile << "thank you for using DP LCD Backpack for Smartie\n";
	LogFile.close();
	//close ftd2xx driver
	ftStatus=DP.Close();
	if (ftStatus==FT_OK)
	{
		LogFile << "Successfully Closed the Device \n";
	}
	else
	{
		LogFile << "Error Closing Device \n";
	}



}

// +--------------------+
// ! DISPLAYDLL_ReadKey !
// +--------------------+
DLL_EXPORT(LCDS_WORD) DISPLAYDLL_ReadKey(void) {
		LogFile << "DISPLAYDLL_ReadKey(void)\n";

  return 0;
}

// +-------------------------+
// ! DISPLAYDLL_SetBacklight !
// +-------------------------+
DLL_EXPORT(void) DISPLAYDLL_SetBacklight(LCDS_BOOL light_on) {

		LogFile <<"DISPLAYDLL_SetBacklight( " << light_on << ")\n";
}

// +------------------------+
// ! DISPLAYDLL_SetContrast !
// +------------------------+
DLL_EXPORT(void) DISPLAYDLL_SetContrast(LCDS_BYTE contrast) {
	LogFile <<"DISPLAYDLL_SetContrast( " <<  contrast << ")\n";
}

// +------------------------+
// ! DISPLAYDLL_PowerResume !
// +------------------------+
DLL_EXPORT(void) DISPLAYDLL_PowerResume(void) {
		LogFile << "DISPLAYDLL_PowerResume(void)\n";
}

// +-------------------+
// ! DISPLAYDLL_SetGPO !
// +-------------------+
DLL_EXPORT(void) DISPLAYDLL_SetGPO(LCDS_BYTE gpo,LCDS_BOOL gpo_on) {
		LogFile <<"DISPLAYDLL_SetGPO(" <<  gpo << "," <<  gpo_on << ")\n";
}

// +-------------------+
// ! DISPLAYDLL_SetFan !
// +-------------------+
DLL_EXPORT(void) DISPLAYDLL_SetFan(LCDS_BYTE t1,LCDS_BYTE t2) {
		LogFile <<"DISPLAYDLL_SetFan(" << t1 << "," << t2 << ")\n";
}
