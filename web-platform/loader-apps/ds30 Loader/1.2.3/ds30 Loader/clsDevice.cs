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


namespace ds30Loader
{
	//-------------------------------------------------------------------------
	// Class: clsDevice
	//-------------------------------------------------------------------------
	public class clsDevice
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
		private clsDeviceFamily objParentDeviceFamily = null;
		private int iID = -1;
		private string strName = "";
		private int iFlashSizeP = -1;
        private int iPageSizeR = -1;
        private int iRowSizeW = -1;
		private int iEEPROMSizeB = -1;
		private int iConfigCount = -1;
		
		
		//---------------------------------------------------------------------
		// Constructor()
		//---------------------------------------------------------------------	
		public clsDevice( clsDeviceFamily pobjParentDeviceFamily, int piID, string pstrName, int piFlashSizeP, int piEEPROMSizeB, int piConfigCount ) 
		{
			objParentDeviceFamily = pobjParentDeviceFamily;
			iID = piID;
			strName = pstrName;
			iFlashSizeP = piFlashSizeP;
			iEEPROMSizeB = piEEPROMSizeB;
			iConfigCount = piConfigCount;
		}// Constructor()

		
		//---------------------------------------------------------------------
		// Constructor()
		//---------------------------------------------------------------------	
		public clsDevice( clsDeviceFamily pobjParentDeviceFamily, int piID, string pstrName, int piFlashSizeP, int piEEPROMSizeB, int piConfigCount, int piPageSizeR, int piRowSizeW ) 
		{
			objParentDeviceFamily = pobjParentDeviceFamily;
			iID = piID;
			strName = pstrName;
			iFlashSizeP = piFlashSizeP;
            iPageSizeR = piPageSizeR;
            iRowSizeW = piRowSizeW;
			iEEPROMSizeB = piEEPROMSizeB;
			iConfigCount = piConfigCount;
		}// Constructor()


 		//---------------------------------------------------------------------
		// Property: configCount
		//---------------------------------------------------------------------
		public int configCount
		{
			get {
				return iConfigCount;
			}
        }//Property: configCount
                
        
 		//---------------------------------------------------------------------
		// Property: eepromSizeB
		//---------------------------------------------------------------------
		public int eepromSizeB
		{
			get {
				return iEEPROMSizeB;
			}
        }//Property: eepromSizeB
        
          
 		//---------------------------------------------------------------------
		// Property: eepromSizeW
		//---------------------------------------------------------------------
		public int eepromSizeW
		{
			get {
				return eepromSizeB / 2;
			}
        }//Property: eepromSizeW
        
              	
   		//---------------------------------------------------------------------
		// Property: eepromStartAddress
		//---------------------------------------------------------------------
		public int eepromStartAddress
		{
			get {
				return  0x800000 - eepromSizeB;
			}
        }//Property: eepromStartAddress
             
              
 		//---------------------------------------------------------------------
		// Property: family
		//---------------------------------------------------------------------
		public clsDeviceFamily family
		{
			get {
				return objParentDeviceFamily;
			}
        }//Property: family  
        
                      				
		//---------------------------------------------------------------------
		// Property: flashSizeP
		//---------------------------------------------------------------------
		public int flashSizeP
		{
			get {
				return iFlashSizeP;
			}
        }//Property: flashSizeP	
        
         	
		//---------------------------------------------------------------------
		// Property: id
		//---------------------------------------------------------------------
		public int id
		{
			get {
				return iID;
			}
        }//Property: id 
        
               	
		//---------------------------------------------------------------------
		// Property: name
		//---------------------------------------------------------------------
		public string name
		{
			get {
				return objParentDeviceFamily.name + strName;
			}
        }//Property: name 	
          		      
          		        
		//---------------------------------------------------------------------
		// Property: pageSizeR
		// Description: blocksize in instructions
		//---------------------------------------------------------------------
		public int pageSizeR
		{
			get {
                if ( iPageSizeR == -1 ) {
				    return objParentDeviceFamily.pageSizeR;
                } else {
                    return iPageSizeR;
                }
			}
        }//Property: pageSizeR   
        
        		        
		//---------------------------------------------------------------------
		// Property: rowsizeW
		// Description: blocksize in instructions
		//---------------------------------------------------------------------
		public int rowsizeW
		{
			get {
                if ( iRowSizeW == -1 ) {
				    return objParentDeviceFamily.rowSizeW;
                } else {
                    return iRowSizeW;
                }
			}
        }//Property: rowsizeW           	
        
	}// Class: clsDevice
}
