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
	// Class: clsDownloadSettings
	//-------------------------------------------------------------------------
	public class clsDownloadSettings
	{
        //---------------------------------------------------------------------
		// Default values
		//---------------------------------------------------------------------	
        public const int iPolltimeDefault = 100;
        public const int iTimeoutDefault = 5000;
        public const int iResetTimeDefault = 100;
        

        //---------------------------------------------------------------------
		// Basic
		//---------------------------------------------------------------------
        private bool bWriteProgram = false;
	    public bool writeProgram
		{
			get {
                return bWriteProgram;
			} set {
                bWriteProgram = value;
            }
        }

        private bool bWriteEEPROM = false;
        public bool writeEEPROM
		{
			get {
                return bWriteEEPROM;
			} set {
                bWriteEEPROM = value;
            }
        }
       	
		//---------------------------------------------------------------------
		// Advanced
		//---------------------------------------------------------------------
        private bool bWriteConfigs = false;
        public bool writeConfigs
		{
			get {
                return bWriteConfigs;
			} set {
                bWriteConfigs = value;
            }
        }

        private bool bAllowBlOverwrite = false;
		public bool allowBlOverwrite
		{
			get {
                return bAllowBlOverwrite;
			} set {
                bAllowBlOverwrite = value;
            }
        }

	    private bool bNoGoto = false;
		public bool noGoto
		{
			get {
                return bNoGoto;
			} set {
                bNoGoto = value;
            }
        } 
       	
	        
		//---------------------------------------------------------------------
		// Timing
		//---------------------------------------------------------------------
		private int iPolltime = iPolltimeDefault;
        public int polltime
		{
			get {
                return iPolltime;
			} set {
                iPolltime = value;
            }
        }         	
		
        private int iTimeout = iTimeoutDefault;
       	public int timeout
		{
			get {
                return iTimeout;
			} set {
                iTimeout = value;
            }
        }

        
        //---------------------------------------------------------------------
		// Reset
		//---------------------------------------------------------------------
       private bool bResetCommand = false;
        public bool resetCommand
		{
			get {
                return bResetCommand;
			} set {
                bResetCommand = value;
            }
        }

		private string strResetCommand = "";        
        public string resetCommandSequence
		{
			get {
                return strResetCommand;
			} set {
                strResetCommand = value;
            }
        }

		private int iResetBaudrate = 9600;
        public int resetBaudrate
		{
			get {
                return iResetBaudrate;
			} set {
                iResetBaudrate = value;
            }
        }

        private bool bResetDtr = false;
		public bool resetDtr
		{
			get {
                return bResetDtr;
			} set {
                bResetDtr = value;
            }
        }
  
		private bool bResetRts = false;
        public bool resetRts
		{
			get {
                return bResetRts;
			} set {
                bResetRts = value;
            }
        }

        private int iResetTime = iResetTimeDefault;
		public int resetTime
		{
			get {
                return iResetTime;
			} set {
                iResetTime = value;
            }
        }


		//---------------------------------------------------------------------
		// Activation 
		//---------------------------------------------------------------------
        private bool bActivateDTR = false;
		public bool activateDTR
		{
			get {
                return bActivateDTR;
			} set {
                bActivateDTR = value;
            }
        }

		private bool bActivateRTS = false;
        public bool activateRTS
		{
			get {
                return bActivateRTS;
			} set {
                bActivateRTS = value;
            }
        }
	}// Class: clsDownloadSettings
}
