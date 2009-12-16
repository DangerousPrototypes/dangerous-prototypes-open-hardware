// DangerousPrototypes.com web platform demo
// SD card web server
//
//BEFORE YOU COMPILE!!!!
//Due to licensing issues, we can't redistribute the "Microchip Applications Libraries" (TCPIP stack, etc). 
//You can get them from the Microchip website for free: 
//http://www.microchip.com/tcpip
//
//1.Download and install the "Microchip Applications Libraries". 
//   These files install to c:\Microchip Soultions\ by default.
//2.Put the replacement files in this folder into the Microchip MDD HTTP demo 
//   directory (C:\Microchip Solutions\TCPIP MDD Demo App\)
//   Replace 6 files in total: 
//	 Maindemo.c/.h, HardwareProfile.h, TCPIPConfig.h, TCPIP MDD SD Card Demo App-C30.mcw/.mcp
//3.That's it. You've got the latest source and we're compliant with the license.
//4.Depending on the install location you may need to tweak the include paths 
//   under Project->build options. 
//
// See C:\Microchip Solutions\Microchip\Help\ for the MDD Server help document
//
//EXTRA STEPS FOR BOOTLOADER:
//To use this firmware with the dsPIC30 bootloader:
//1. Export the firmware (File->Export)
//2. Set 0x153FE as the end memory address
//3. Save the firmware and bootload as normal