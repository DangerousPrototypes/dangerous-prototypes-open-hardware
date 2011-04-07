//-----------------------------------------------------------------------------
//    This file is part of ds30 Loader.
//
//    ds30 Loader is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation.
//
//    ds30 Loader is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with ds30 Loader.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------------  

using System.Collections;

namespace ds30Loader
{
	//-------------------------------------------------------------------------
	// Class: clsDevices
	//-------------------------------------------------------------------------
	static public class clsDevices
	{
		//---------------------------------------------------------------------
		// Variables
		//---------------------------------------------------------------------
		static private Hashtable htDeviceFamilys = null;
        		

		//---------------------------------------------------------------------
		// DeviceFamilyAdd()
		// Description: adds a device to this devicefamily
		//---------------------------------------------------------------------
		static public void DeviceFamilyAdd( clsDeviceFamily pobjDeviceFamily, ref bool pbResult )
		{
			// Check for existence
			if ( DeviceFamilyExists( pobjDeviceFamily.name ) == true ) {
				pbResult = false;
                return;
			}
			
			//
			htDeviceFamilys.Add( pobjDeviceFamily.name, pobjDeviceFamily );
			pbResult = true;
        }// DeviceFamilyAdd()   
		
		
		//---------------------------------------------------------------------
		// DeviceFamilyExists()
		// Description: checks if a devicefamily exists
		//---------------------------------------------------------------------
		static public bool DeviceFamilyExists( string pstrDeviceFamilyName )
		{
			return htDeviceFamilys.Contains( pstrDeviceFamilyName );
        }// DeviceFamilyExists() 
		
		
		//---------------------------------------------------------------------
		// DeviceFamilyGet()
		// Description: returns the devicefamily with the specified name if it exists
		//---------------------------------------------------------------------
		static public clsDeviceFamily DeviceFamilyGet( string pstrDeviceFamilyName )
		{
			// Check for existence
			if ( DeviceFamilyExists(pstrDeviceFamilyName) == false ) {
				return null;
			}
			
			//
			return (clsDeviceFamily)htDeviceFamilys[ pstrDeviceFamilyName ];
        }// DeviceFamilyGet()
        
				
		//---------------------------------------------------------------------
		// DeviceFamiliesGet()
		// Description: 
		//---------------------------------------------------------------------
		static public Hashtable DeviceFamiliesGet()
		{
			return htDeviceFamilys;
        }// DeviceFamiliesGet()
        
                
   		//---------------------------------------------------------------------
		// DeviceGet()
		// Description: returns the device with the specified name if it exists
		//---------------------------------------------------------------------
		static public clsDevice DeviceGet( string pstrDeviceName )
		{
			clsDevice objDevice = null;            

			foreach ( clsDeviceFamily objFamily in htDeviceFamilys.Values ) {
				objDevice = objFamily.DeviceGet( pstrDeviceName );
				if ( objDevice != null ) return objDevice;
			}
			return null;
        }// DeviceGet()
         
                
   		//---------------------------------------------------------------------
		// DeviceGet()
		// Description: returns the device with the specified name if it exists
		//---------------------------------------------------------------------
		static public clsDevice DeviceGet( int piID )
		{
			clsDevice objDevice = null;
			foreach ( clsDeviceFamily objFamily in htDeviceFamilys.Values ) {
				objDevice = objFamily.DeviceGet( piID );
				if ( objDevice != null ) return objDevice;
			}

            return null;
        }// DeviceGet()

               
 		//---------------------------------------------------------------------
		// Init()
		// Description:
		//---------------------------------------------------------------------
		static public void Init()
		{   
            bool bDeviceAddResult = false;
            bool bDeviceFamilyAddResult = false;
			//
			htDeviceFamilys = new Hashtable( 7 );			
			
			// Add devices and devicefamilies, this should be read from xml some day
			clsDeviceFamily objDeviceFamily;
			clsDevice objDevice;


            //-----------------------------------------------------------------
            // PIC18F
            //-----------------------------------------------------------------
            objDeviceFamily = new clsDeviceFamily( "PIC18F", 2, 16); DeviceFamilyAdd(objDeviceFamily, ref bDeviceFamilyAddResult );

            objDevice = new clsDevice( objDeviceFamily, 301, "1220", 0x1000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 302, "1230", 0x1000, 128, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 303, "2220", 0x1000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 304, "2221", 0x1000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 305, "4220", 0x1000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 306, "4221", 0x1000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 307, "1320", 0x2000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 308, "1330", 0x2000, 128, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 309, "13K22",0x2000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 310, "13K50",0x2000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 311, "2320", 0x2000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 312, "2321", 0x2000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 313, "2331", 0x2000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 314, "23K20",0x2000, 256, 16, 4, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 315, "4320", 0x2000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 316, "4321", 0x2000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 317, "4331", 0x2000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 318, "43K20",0x2000, 256, 16, 4, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 319, "14K22",0x4000, 256, 16, 4,  8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 320, "14K50",0x4000, 256, 16, 4,  8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 321, "2420", 0x4000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 322, "2423", 0x4000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 323, "2431", 0x4000, 256, 16, 8,  4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 324, "2450", 0x4000,   0, 16, 4,  8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 325, "2480", 0x4000, 256, 16, 8,  4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 326, "24K20",0x4000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 327, "4420", 0x4000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 328, "4423", 0x4000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 329, "4431", 0x4000, 256, 16, 8,  4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 330, "4450", 0x4000,   0, 16, 4,  8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 331, "4480", 0x4000, 256, 16, 8,  4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 332, "44K20",0x4000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 333, "2455", 0x6000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 334, "2458", 0x6000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 335, "4455", 0x6000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 336, "4458", 0x6000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 337, "2520", 0x8000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 338, "2523", 0x8000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 339, "2550", 0x8000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 340, "2553", 0x8000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 341, "2580", 0x8000, 256, 16, 8,  4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 342, "25K20",0x8000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 343, "4520", 0x8000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 344, "4523", 0x8000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 345, "4550", 0x8000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 346, "4553", 0x8000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 347, "4580", 0x8000, 256, 16, 8,  4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 348, "45K20",0x8000, 256, 16, 2, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 349, "6520", 0x8000,1024, 16, 8,  4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 350, "8520", 0x8000,1024, 16, 8,  4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 351, "2525", 0xC000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 352, "2585", 0xC000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 353, "4525", 0xC000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 354, "4585", 0xC000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 355, "6527", 0xC000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 356, "8527", 0xC000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 357, "2620", 0x10000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 358, "2680", 0x10000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 359, "26K20",0x10000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 360, "4620", 0x10000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 361, "4680", 0x10000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 362, "46K20",0x10000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 363, "6622", 0x10000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 364, "8622", 0x10000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 365, "2682", 0x14000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 366, "4682", 0x14000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 367, "2685", 0x18000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 368, "4685", 0x18000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 369, "6627", 0x18000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 370, "6628", 0x18000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 371, "8627", 0x18000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 372, "8628", 0x18000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 373, "6722", 0x20000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 374, "6723", 0x20000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 375, "8722", 0x20000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 376, "8723", 0x20000, 1024, 16, 1, 32 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 377, "452", 0x8000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 378, "458", 0x8000, 256, 16, 8, 4 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );


            //-----------------------------------------------------------------
            // PIC18FJ
            //-----------------------------------------------------------------
            objDeviceFamily = new clsDeviceFamily( "PIC18FJ", 16, 32); DeviceFamilyAdd(objDeviceFamily, ref bDeviceFamilyAddResult);

            objDevice = new clsDevice( objDeviceFamily, 400, "63J11", 0x2000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 401, "63J90", 0x2000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 402, "83J11", 0x2000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 403, "83J90", 0x2000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 404, "24J10", 0x4000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 405, "24J11", 0x4000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 406, "24J50", 0x4000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 407, "44J10", 0x4000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 408, "44J11", 0x4000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 409, "44J50", 0x4000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 410, "64J11", 0x4000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 411, "64J90", 0x4000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 412, "84J11", 0x4000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 413, "84J90", 0x4000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 414, "25J10", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 415, "25J11", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 416, "25J50", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 417, "45J10", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 418, "45J11", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 419, "45J50", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 420, "65J10", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 421, "65J11", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 422, "65J50", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 423, "65J90", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 424, "85J10", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 425, "85J11", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 426, "85J50", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 427, "85J90", 0x8000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 428, "65J15", 0xC000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 429, "85J15", 0xC000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 430, "26J11", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 431, "26J50", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 432, "46J11", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 433, "46J50", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 434, "66J10", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 435, "66J11", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 436, "66J50", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 437, "66J60", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 438, "66J90", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 439, "66J93", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 440, "86J10", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 441, "86J11", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 442, "86J50", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 443, "86J60", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 444, "86J90", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 445, "86J93", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 446, "96J60", 0x10000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 447, "66J15", 0x18000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 448, "66J16", 0x18000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 449, "66J55", 0x18000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 450, "66J65", 0x18000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 451, "86J15", 0x18000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 452, "86J16", 0x18000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 453, "86J55", 0x18000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 454, "86J65", 0x18000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 455, "96J65", 0x18000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 456, "67J10", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 457, "67J11", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 458, "67J50", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 459, "67J60", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 460, "67J90", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 461, "67J93", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 462, "87J10", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 463, "87J11", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 464, "87J50", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 465, "87J60", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 466, "87J90", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 467, "87J93", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 468, "97J60", 0x20000, 0, 16 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );


            //-----------------------------------------------------------------
            // PIC24F
            //-----------------------------------------------------------------
            objDeviceFamily = new clsDeviceFamily( "PIC24F", 1, 32); DeviceFamilyAdd(objDeviceFamily, ref bDeviceFamilyAddResult);

            objDevice = new clsDevice( objDeviceFamily, 200, "04KA200", 0xB00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 201, "04KA201", 0xB00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 202, "08KA101", 0x1600, 512, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 203, "08KA102", 0x1600, 512, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 204, "16KA101", 0x2C00, 512, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 205, "16KA102", 0x2C00, 512, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            
            //-----------------------------------------------------------------
            // PIC24FJ
            //-----------------------------------------------------------------
            objDeviceFamily = new clsDeviceFamily( "PIC24FJ", 8, 64); DeviceFamilyAdd(objDeviceFamily, ref bDeviceFamilyAddResult);

            objDevice = new clsDevice( objDeviceFamily, 206, "16GA002", 0x2C00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 207, "16GA004", 0x2C00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            
            objDevice = new clsDevice( objDeviceFamily, 208, "32GA002", 0x5800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 209, "32GA004", 0x5800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 210, "48GA002", 0x8400, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 211, "48GA004", 0x8400, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 212, "64GA002", 0xAC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 213, "64GA004", 0xAC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 214, "64GA006", 0xAC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 215, "64GA008", 0xAC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 216, "64GA010", 0xAC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 217, "64GB106", 0xAC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 218, "64GB108", 0xAC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 219, "64GB110", 0xAC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 220, "96GA006", 0x10000, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 221, "96GA008", 0x10000, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 222, "96GA010", 0x10000, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 223, "128GA006", 0x15800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 224, "128GA008", 0x15800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 225, "128GA010", 0x15800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 226, "128GA106", 0x15800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 227, "128GA108", 0x15800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 228, "128GA110", 0x15800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 229, "128GB106", 0x15800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 230, "128GB108", 0x15800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 231, "128GB110", 0x15800, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 232, "192GA106", 0x20C00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 233, "192GA108", 0x20C00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 234, "192GA110", 0x20C00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 235, "192GB106", 0x20C00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 236, "192GB108", 0x20C00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 237, "192GB110", 0x20C00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 238, "256GA106", 0x2AC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 239, "256GA108", 0x2AC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 240, "256GA110", 0x2AC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 241, "256GB106", 0x2AC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 242, "256GB108", 0x2AC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 243, "256GB110", 0x2AC00, 0, 0 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            //-----------------------------------------------------------------
            // PIC24H
            //-----------------------------------------------------------------
            objDeviceFamily = new clsDeviceFamily( "PIC24H", 8, 64); DeviceFamilyAdd(objDeviceFamily, ref bDeviceFamilyAddResult );

            objDevice = new clsDevice( objDeviceFamily, 40, "J12GP201", 0x2000, 0, 7 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 41, "J12GP202", 0x2000, 0, 7 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 42, "J16GP304", 0x2C00, 0, 7 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 43, "J32GP202", 0x5800, 0, 7 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 44, "J32GP204", 0x5800, 0, 7 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 45, "J32GP302", 0x5800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 46, "J32GP304", 0x5800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            
            objDevice = new clsDevice( objDeviceFamily, 47, "J64GP202", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 48, "J64GP204", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 49, "J64GP206", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 50, "J64GP210", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 51, "J64GP210A", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 52, "J64GP502", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 53, "J64GP504", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 54, "J64GP506", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 55, "J64GP506A", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 56, "J64GP510", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 57, "J64GP510A", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 58, "J128GP202", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 59, "J128GP204", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 60, "J128GP206", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 61, "J128GP210", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 62, "J128GP210A", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 63, "J128GP306", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 64, "J128GP310", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 65, "J128GP310A", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 66, "J128GP502", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 67, "J128GP504", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 68, "J128GP506", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 69, "J128GP506A", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 70, "J128GP510", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 71, "J128GP510A", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

            objDevice = new clsDevice( objDeviceFamily, 72, "J256GP206", 0x2AC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 73, "J256GP210", 0x2AC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
            objDevice = new clsDevice( objDeviceFamily, 74, "J256GP610", 0x2AC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );


            //-----------------------------------------------------------------
			// dsPIC30F
            //-----------------------------------------------------------------
			objDeviceFamily = new clsDeviceFamily( "dsPIC30F", 1, 32 ); DeviceFamilyAdd( objDeviceFamily, ref bDeviceFamilyAddResult );		
			
			objDevice = new clsDevice( objDeviceFamily, 30, "1010", 0x1000, 0, 7 );		objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			
			objDevice = new clsDevice( objDeviceFamily, 10, "2010", 8192, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 20, "2011", 8192, 0, 5 );		objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 22, "2012", 8192, 0, 5 );		objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );			
			objDevice = new clsDevice( objDeviceFamily, 31, "2020", 8192, 0, 7);		objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );			
			objDevice = new clsDevice( objDeviceFamily, 32, "2023", 8192, 0, 7 );		objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );						
			
			objDevice = new clsDevice( objDeviceFamily, 11, "3010", 16384, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 13, "3011", 16384, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );			
			objDevice = new clsDevice( objDeviceFamily, 21, "3012", 16384, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 23, "3013", 16384, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily,  1, "3014", 16384, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			
			objDevice = new clsDevice( objDeviceFamily, 14, "4011", 32768, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );			
			objDevice = new clsDevice( objDeviceFamily, 12, "4012", 32768, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily,  2, "4013", 32768, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			
			objDevice = new clsDevice( objDeviceFamily,  3, "5011", 45056, 1024, 7 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily,  6, "5013", 45056, 1024, 7 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 15, "5015", 45056, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 33, "5016", 45056, 1024, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			
			objDevice = new clsDevice( objDeviceFamily, 16, "6010", 98304, 4096, 7 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily,  4, "6011", 90112, 2048, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily,  4, "6011A", 90112, 2048, 7 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily,  5, "6012", 98304, 4096, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );			
			objDevice = new clsDevice( objDeviceFamily,  5, "6012A", 98304, 4096, 7 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );			
			objDevice = new clsDevice( objDeviceFamily,  7, "6013", 90112, 2048, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );			
			objDevice = new clsDevice( objDeviceFamily,  7, "6013A", 90112, 2048, 7 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );			
			objDevice = new clsDevice( objDeviceFamily,  8, "6014", 98304, 4096, 5 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );		
			objDevice = new clsDevice( objDeviceFamily,  8, "6014A", 98304, 4096, 7 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );		
			objDevice = new clsDevice( objDeviceFamily, 34, "6015", 98304, 4096, 7 );	objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );


            //-----------------------------------------------------------------
			// dsPIC33FJ
            //-----------------------------------------------------------------
			objDeviceFamily = new clsDeviceFamily( "dsPIC33FJ", 8, 64 ); DeviceFamilyAdd( objDeviceFamily, ref bDeviceFamilyAddResult );
						
			objDevice = new clsDevice( objDeviceFamily, 100, "06GS101", 0x1000, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 101, "06GS102", 0x1000, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 102, "06GS202", 0x1000, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

			objDevice = new clsDevice( objDeviceFamily, 110, "12GP201", 0x2000, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 111, "12GP202", 0x2000, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 112, "12MC201", 0x2000, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 113, "12MC202", 0x2000, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

			objDevice = new clsDevice( objDeviceFamily, 120, "16GP304", 0x2C00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 121, "16GS402", 0x2C00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 122, "16GS404", 0x2C00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 123, "16GS502", 0x2C00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 124, "16GS504", 0x2C00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 125, "16MC304", 0x2C00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

			objDevice = new clsDevice( objDeviceFamily, 130, "32GP202", 0x5800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 131, "32GP204", 0x5800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 132, "32GP302", 0x5800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 133, "32GP304", 0x5800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 134, "32MC202", 0x5800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 135, "32MC204", 0x5800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 136, "32MC302", 0x5800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 137, "32MC304", 0x5800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

			objDevice = new clsDevice( objDeviceFamily, 140, "64GP202", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 141, "64GP204", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 142, "64GP206", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 143, "64GP306", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 144, "64GP310", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 145, "64GP706", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 146, "64GP706A", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 147, "64GP708", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 148, "64GP710", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 149, "64GP802", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 150, "64GP804", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 151, "64MC202", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 152, "64MC204", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 153, "64MC506", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 154, "64MC508", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 155, "64MC510", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 156, "64MC510A", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 157, "64MC706", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 158, "64MC710", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 159, "64MC802", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 160, "64MC804", 0xAC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

			objDevice = new clsDevice( objDeviceFamily, 170, "128GP202", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 171, "128GP204", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 172, "128GP206", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 173, "128GP206A", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 174, "128GP306", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 175, "128GP306A", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 176, "128GP310", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 177, "128GP706", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 178, "128GP708", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 179, "128GP710", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 180, "128GP802", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 181, "128GP804", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 182, "128MC202", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 183, "128MC204", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 184, "128MC506", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 185, "128MC510", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 186, "128MC706", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 187, "128MC708", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 188, "128MC710", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 189, "128MC802", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 190, "128MC804", 0x15800, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

			objDevice = new clsDevice( objDeviceFamily, 195, "256GP506", 0x2AC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 196, "256GP510", 0x2AC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 197, "256GP710", 0x2AC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 198, "256MC510", 0x2AC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );
			objDevice = new clsDevice( objDeviceFamily, 199, "256MC710", 0x2AC00, 0, 8 ); objDeviceFamily.DeviceAdd( objDevice, ref bDeviceAddResult );

        }// DeviceFamilyGet()	  		

	}// Class: clsDevices
}
