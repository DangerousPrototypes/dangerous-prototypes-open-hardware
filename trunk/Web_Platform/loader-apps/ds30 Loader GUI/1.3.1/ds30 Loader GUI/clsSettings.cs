//-----------------------------------------------------------------------------
//    This file is part of ds30 Loader GUI.
//
//    ds30 Loader GUI is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation.
//
//    ds30 Loader GUI is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with ds30 Loader GUI.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------- 

using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.Xml;
using System.Xml.Serialization;

namespace ds30_Loader_GUI
{
    //---------------------------------------------------------------------------
    // Class: settings
    //---------------------------------------------------------------------------
    [XmlRoot("ds30LoaderSettings")]
    public class clsSettings
    {
		//---------------------------------------------------------------------
		// Options
        //---------------------------------------------------------------------
        private bool bDebugmode;
        public bool Debugmode {
	        get {
		        return bDebugmode;
	        } set {
		        bDebugmode = value;
	        }
        }

        private bool bCheckVerStart;
        public bool CheckVerStart {
	        get {
		        return bCheckVerStart;
	        } set {
		        bCheckVerStart = value;
	        }
        }


		//---------------------------------------------------------------------
		// View options
        //---------------------------------------------------------------------
        private bool bWindowOnTop;
        public bool WindowOnTop {
	        get {
		        return bWindowOnTop;
	        } set {
		        bWindowOnTop = value;
	        }
        }
        private bool bAdvancedMode;
        public bool advancedMode {
	        get {
		        return bAdvancedMode;
	        } set {
		        bAdvancedMode = value;
	        }
        }


		//---------------------------------------------------------------------
		// Window size
        //---------------------------------------------------------------------
        private int iWindowWidth;
		public int WindowWidth {
	        get {
		        return iWindowWidth;
	        } set {
		        iWindowWidth = value;
	        }
        }

        private int iWindowHeight;
        public int WindowHeight {
	        get {
		        return iWindowHeight;
	        } set {
		        iWindowHeight = value;
	        }
        }


		//---------------------------------------------------------------------
		// Tab basic settings
        //---------------------------------------------------------------------
        private string strFilename;		
		public string Filename {
	        get {
		        return strFilename;
	        } set {
		        strFilename = value;
	        }
        }
        private string strPortname;
		public string Portname {
	        get {
		        return strPortname;
	        } set {
		        strPortname = value;
	        }
        }
        private string strBaudrate;
		public string Baudrate {
	        get {
		        return strBaudrate;
	        } set {
		        strBaudrate = value;
	        }
        }
        private string strFamilyname;
		public string Familyname {
	        get {
		        return strFamilyname;
	        } set {
		        strFamilyname = value;
	        }
        }
        private string strDevicename;
        public string Devicename {
	        get {
		        return strDevicename;
	        } set {
		        strDevicename = value;
	        }
        }
        private bool bWriteProgram;
		public bool WriteProgram {
	        get {
		        return bWriteProgram;
	        } set {
		        bWriteProgram = value;
	        }
        }
        private bool bWriteEEPROM;
        public bool WriteEEPROM {
	        get {
		        return bWriteEEPROM;
	        } set {
		        bWriteEEPROM = value;
	        }
        }

              
        
        //---------------------------------------------------------------------
		// Tab advanced
        //---------------------------------------------------------------------
        private bool bWriteConfigs;
        public bool WriteConfigs {
	        get {
		        return bWriteConfigs;
	        } set {
		        bWriteConfigs = value;
	        }
        }
        private bool bNoGoto;
        public bool NoGoto {
	        get {
		        return bNoGoto;
	        } set {
		        bNoGoto = value;
	        }
        }        
        private bool bIgnoreBLOverwrite;
        public bool ignoreBLOverwrite {
	        get {
		        return bIgnoreBLOverwrite;
	        } set {
		        bIgnoreBLOverwrite = value;
	        }
        } 

		//---------------------------------------------------------------------
		// Tab timing
        //---------------------------------------------------------------------
        private string strPolltime;
        public string Polltime {
	        get {
		        return strPolltime;
	        } set {
		        strPolltime = value;
	        }
        }

        private string strTimeout;
        public string Timeout {
	        get {
		        return strTimeout;
	        } set {
		        strTimeout = value;
	        }
        }


		//---------------------------------------------------------------------
		// Tab reset
        //---------------------------------------------------------------------
        private bool bCommandReset;
        public bool CommandReset {
	        get {
		        return bCommandReset;
	        } set {
		        bCommandReset = value;
	        }
        }

        private string strResetCommand;
        public string ResetCommand {
	        get {
		        return strResetCommand;
	        } set {
		        strResetCommand = value;
	        }
        }

        private int iResetBaudrate;
        public int resetBaudrate {
	        get {
		        return iResetBaudrate;
	        } set {
		        iResetBaudrate = value;
	        }
        }

        private bool bDTRReset;
        public bool DTRReset {
	        get {
		        return bDTRReset;
	        } set {
		        bDTRReset = value;
	        }
        }

        private bool bManualReset;
        public bool ManualReset {
	        get {
		        return bManualReset;
	        } set {
		        bManualReset = value;
	        }
        }

        private bool bRTSReset;
        public bool RTSReset {
	        get {
		        return bRTSReset;
	        } set {
		        bRTSReset = value;
	        }
        }

        private int iResetTime;
        public int ResetTime {
	        get {
		        return iResetTime;
	        } set {
		        iResetTime = value;
	        }
        }


		//---------------------------------------------------------------------
		// Tab activation
        //---------------------------------------------------------------------
        private bool bActivateDTR;
        public bool ActivateDTR {
	        get {
		        return bActivateDTR;
	        } set {
		        bActivateDTR = value;
	        }
        }

        private bool bActivateRTS;  
        public bool ActivateRTS {
	        get {
		        return bActivateRTS;
	        } set {
		        bActivateRTS = value;
	        }
        }


		//---------------------------------------------------------------------
		// Tab terminal
        //---------------------------------------------------------------------
        private bool bTermSwithTo;
        public bool termSwithTo {
	        get {
		        return bTermSwithTo;
	        } set {
		        bTermSwithTo = value;
	        }
        }

        private int iTermBaudrate;  
        public int termBaudrate {
	        get {
		        return iTermBaudrate;
	        } set {
		        iTermBaudrate = value;
	        }
        }
    }// Class: settings
}
