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
	// Class: clsDeviceFamily
	//-------------------------------------------------------------------------
	public class clsDeviceFamily
	{
		//---------------------------------------------------------------------
		// Size suffixes
		//---------------------------------------------------------------------
		// R - rows
		// W - words
		// P - program counter units
		// B - bytes	
		
		
        //---------------------------------------------------------------------
		// Variables
		//---------------------------------------------------------------------	
		private string strName = "";		
		private int iPageSizeR = 0;
		private int iRowSizeW = 0;				//size in instructions
		private Hashtable htDevices = null;
		
		
		//---------------------------------------------------------------------
		// Constructor()
		//---------------------------------------------------------------------	
		public clsDeviceFamily( string pstrName, int piPageSizeR, int piRowSizeW ) 
		{
			strName = pstrName;
			iPageSizeR = piPageSizeR;
			iRowSizeW = piRowSizeW;
			
			htDevices = new Hashtable( 61 );
		}// Constructor()
		
		
		//---------------------------------------------------------------------
		// Property: name
		// Description: the name of this devicefamily
		//---------------------------------------------------------------------
		public string name
		{
			get {
				return strName;
			}
        }//Property: name 
		
		
		//---------------------------------------------------------------------
		// Property: pageSizeR
		// Description: size in instructions
		//---------------------------------------------------------------------
		public int pageSizeR
		{
			get {
				return iPageSizeR;
			}
        }//Property: pageSizeR
        
        		
		//---------------------------------------------------------------------
		// Property: rowSizeW
		// Description: size in instructions
		//---------------------------------------------------------------------
		public int rowSizeW
		{
			get {
				return iRowSizeW;
			}
        }//Property: rowSizeW
		          
		          
		//---------------------------------------------------------------------
		// DeviceAdd()
		// Description: adds a device to this devicefamily
		//---------------------------------------------------------------------
		public void DeviceAdd( clsDevice pobjDevice, ref bool pbResult )
		{
			// Check for existence
			if ( DeviceExists( pobjDevice.id ) == true ) {
				pbResult = false;
                return;
			}
			
			//
			htDevices.Add( pobjDevice.id, pobjDevice );
			pbResult = true;
        }// DeviceAdd()   
		
		
		//---------------------------------------------------------------------
		// DeviceExists()
		// Description: checks if a devicename is added to this devicefamily
		//---------------------------------------------------------------------
		public bool DeviceExists( int piID )
		{
			return htDevices.Contains( piID );
        }// DeviceAdd() 
		
		
		//---------------------------------------------------------------------
		// DeviceGet()
		// Description: returns the device with the specified name if it exists
		//---------------------------------------------------------------------
		public clsDevice DeviceGet( string pstrDeviceName )
		{
			//string strDeviceNameWithFamilyName;

            foreach ( clsDevice objDevice in htDevices.Values ) {
                //strDeviceNameWithFamilyName = this.name + objDevice.name;
				if ( objDevice.name.ToLower() == pstrDeviceName.ToLower() /*|| objDevice.name == strDeviceNameWithFamilyName*/ ) {
					return objDevice;
				}
			}
			return null;
        }// DeviceGet()
        
                 
		//---------------------------------------------------------------------
		// DeviceGet()
		// Description: returns the device with the specified id if it exists
		//---------------------------------------------------------------------
		public clsDevice DeviceGet( int piID )
		{
			// Check for existence
			if ( DeviceExists(piID) == false ) {
				return null;
			}
			
			//
			return (clsDevice)htDevices[ piID ];
        }// DeviceGet()  
        		
		
		//---------------------------------------------------------------------
		// DevicesGet()
		// Description: returns devices hashtable
		//---------------------------------------------------------------------
		public Hashtable DevicesGet()
		{
			return htDevices;
        }// DevicesGet() 
                		          
	}// Class: clsDeviceFamily
}
