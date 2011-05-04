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
    // Class: clsLatestVersionInfo
    //---------------------------------------------------------------------------
    public class clsLatestVersionInfo
    {
        private Version verds30LoaderGUI = null;  
        private Version verds30Loader = null;  
        private string strURLLatestPackage = "";  
        private string strURLds30LoaderGUI_exe = "";  
        private string strURLds30Loader_dll = "";  
        private string strLatestVersionInfo = "";
        private bool bAllowUpdate = false;
        private bool bAllowDownload = false;


		//---------------------------------------------------------------------
		// Property: allowUpdate
        //---------------------------------------------------------------------
        public bool allowUpdate {
	        get {
		        return bAllowUpdate;
	        } set {
		        bAllowUpdate = value;
	        }
        }// Property: allowUpdate


		//---------------------------------------------------------------------
		// Property: allowDownload
        //---------------------------------------------------------------------
        public bool allowDownload {
	        get {
		        return bAllowDownload;
	        } set {
		        bAllowDownload = value;
	        }
        }// Property: allowDownload


		//---------------------------------------------------------------------
		// Property: lvds30Loader
        //---------------------------------------------------------------------
        public Version lvds30Loader {
	        get {
		        return verds30Loader;
	        } set {
		        verds30Loader = value;
	        }
        }// Property: lvds30Loader


		//---------------------------------------------------------------------
		// Property: lvds30LoaderGUI
        //---------------------------------------------------------------------
        public Version lvds30LoaderGUI {
	        get {
		        return verds30LoaderGUI;
	        } set {
		        verds30LoaderGUI = value;
	        }
        }// Property: lvds30LoaderGUI


		//---------------------------------------------------------------------
		// Property: urlLatestPackage
        //---------------------------------------------------------------------
        public string urlLatestPackage {
	        get {
		        return strURLLatestPackage;
	        } set {
		        strURLLatestPackage = value;
	        }
        }// Property: urlLatestPackage


		//---------------------------------------------------------------------
		// Property: urlds30Loader_dll
        //---------------------------------------------------------------------
        public string urlds30Loader_dll {
	        get {
		        return strURLds30Loader_dll;
	        } set {
		        strURLds30Loader_dll = value;
	        }
        }// Property: urlds30Loader_dll


		//---------------------------------------------------------------------
		// Property: urlds30LoaderGUI_exe
        //---------------------------------------------------------------------
        public string urlds30LoaderGUI_exe {
	        get {
		        return strURLds30LoaderGUI_exe;
	        } set {
		        strURLds30LoaderGUI_exe = value;
	        }
        }// Property: urlds30LoaderGUI_exe
        

		//---------------------------------------------------------------------
		// Property: latestVersionInfo
        //---------------------------------------------------------------------
        public string latestVersionInfo {
	        get {
		        return strLatestVersionInfo;
	        } set {
		        strLatestVersionInfo = value;
	        }
        }// Property: latestVersionInfo


		//---------------------------------------------------------------------
		// CheckLatestVersion()
		// Description:
		//---------------------------------------------------------------------
		public bool CheckLatestVersion()		
        {
            try  
                {  
                string xmlURL = frmDS30Loader.strURLHomepage + "data/latestversions_v1.xml";  
                XmlTextReader reader = new XmlTextReader(xmlURL);  

                // skip the junk at the beginning  
                reader.MoveToContent();  
                
                string elementName = "";                  
                
                if ( reader.NodeType == XmlNodeType.Element && reader.Name == "gui" )  {  
                    while ( reader.Read() ) { 
                        if ( reader.NodeType == XmlNodeType.Element ) {
                            elementName = reader.Name;  
                        } else {  
                            if ( reader.NodeType == XmlNodeType.Text && reader.HasValue ) { 
                                switch ( elementName ) {  
                                    case "versionds30Loader":  
                                        verds30Loader = new Version(reader.Value); 
                                        break;  
                                     case "versionds30LoaderGUI":  
                                        verds30LoaderGUI = new Version(reader.Value); 
                                        break;  
                                    case "urlPackage":  
                                        strURLLatestPackage = reader.Value;  
                                        break;  
                                    case "allowUpdate":
                                        bAllowUpdate = bool.Parse( reader.Value );
                                        break;
                                    case "allowPackageDownload":
                                        bAllowDownload = bool.Parse( reader.Value );
                                        break;
                                    case "info":
                                        strLatestVersionInfo = reader.Value;
                                        break;
                                    case "urlds30Loder_dll":
                                        strURLds30Loader_dll = reader.Value;
                                        break;
                                    case "urlds30LoderGUI_exe":
                                        strURLds30LoaderGUI_exe = reader.Value;
                                        break;
                                }  
                            }  
                        }  
                    }  
                }  
                reader.Close();  
            } catch {  
                return false;
            }

            return true;
        }// CheckLatestVersion()

    }// Class: clsLatestVersionInfo
}
