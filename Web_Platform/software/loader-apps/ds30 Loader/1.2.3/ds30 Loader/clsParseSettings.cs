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

using System;

namespace ds30Loader
{
	//-------------------------------------------------------------------------
	// Class: clsParseSettings
	//-------------------------------------------------------------------------
	public class clsParseSettings
	{
		//---------------------------------------------------------------------
		// Variables
		//---------------------------------------------------------------------			
        private int iBootloaderSizeR;
        private clsDevice objDevice;
        private DateTime dtFileTimestamp;
        private bool bAllowBlOverwrite;
        private bool bNoGoto;


 		//---------------------------------------------------------------------
		// Constructor()
		//---------------------------------------------------------------------
		public clsParseSettings()
		{
        }// Constructor()


 		//---------------------------------------------------------------------
		// Constructor()
		//---------------------------------------------------------------------
		public clsParseSettings( int piBootloaderSizeR, clsDevice pobjDevice, bool pbIgnoreOverwrit, bool pbNoGoto )
		{
            bootloaderSizeR = piBootloaderSizeR;
            device = pobjDevice;
            allowBlOverwrite = pbIgnoreOverwrit;
            noGoto = pbNoGoto;
        }// Constructor()


 		//---------------------------------------------------------------------
		// Property: bootloaderSizeR
		// Description: 
		//---------------------------------------------------------------------
		public int bootloaderSizeR
		{
			get {
                return iBootloaderSizeR;
			} set {
                iBootloaderSizeR = value;
            }
        }//Property: bootloaderSizeR


		//---------------------------------------------------------------------
		// Property: device
		// Description: 
		//---------------------------------------------------------------------
		public clsDevice device
		{
			get {
                return objDevice;
			} set {
                objDevice = value;
            }
        }//Property: device 


 		//---------------------------------------------------------------------
		// Property: fileTimestamp
		// Description: 
		//---------------------------------------------------------------------
		public DateTime fileTimestamp
		{
			get {
                return dtFileTimestamp;
			} set {
                dtFileTimestamp = value;
            }
        }//Property: fileTimestamp 	

       	
		//---------------------------------------------------------------------
		// Property: allowBlOverwrite
		// Description: 
		//---------------------------------------------------------------------
		public bool allowBlOverwrite
		{
			get {
                return bAllowBlOverwrite;
			} set {
                bAllowBlOverwrite = value;
            }
        }//Property: allowBlOverwrite
	    
    
		//---------------------------------------------------------------------
		// Property: noGoto
		// Description: 
		//---------------------------------------------------------------------
		public bool noGoto
		{
			get {
                return bNoGoto;
			} set {
                bNoGoto = value;
            }
        }//Property: noGoto   

        
	    //---------------------------------------------------------------------
		// CompareTo()
        // Returns: true if equal, false if not equal
		//---------------------------------------------------------------------
		public bool CompareTo( clsParseSettings pobjSettings )
		{
            return (
                bootloaderSizeR == pobjSettings.bootloaderSizeR &&
                device == pobjSettings.device &&
                fileTimestamp == pobjSettings.fileTimestamp &&
                allowBlOverwrite == pobjSettings.allowBlOverwrite &&
                noGoto == pobjSettings.noGoto
            );
        }// CompareTo()


	    //---------------------------------------------------------------------
		// CopyFrom()
		//---------------------------------------------------------------------
		public void CopyFrom( clsParseSettings pobjSettings )
		{
            bootloaderSizeR = pobjSettings.bootloaderSizeR;
            device = pobjSettings.device;
            fileTimestamp = pobjSettings.fileTimestamp;
            allowBlOverwrite = pobjSettings.allowBlOverwrite;
            noGoto = pobjSettings.noGoto;
        }// CopyFrom()

	}// Class: Compare
}

