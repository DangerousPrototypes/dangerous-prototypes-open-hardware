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
using System.Text;
using System.IO;
using GHelper;


namespace ds30Loader
{
	//-------------------------------------------------------------------------
	// Class: clsHex
	//-------------------------------------------------------------------------
	public class clsHex
	{
		//---------------------------------------------------------------------
		// Variables
		//---------------------------------------------------------------------
        protected string strFilename = "";
		
        protected bool bIsParsed = false;        
        
        clsParseSettings objParsedSettings;

        protected bool bHasValidProgram = false;
		protected bool bHasValidEEPROM = false;
		protected bool bHasValidConfigs = false;
        

		// These are filled in by ParseHexFile(), not all families use all of theese	
        public int [] iProgMem;		

        protected int iProgPagesUsed;
        public bool [] bProgPageUsed;

		public bool [] bProgRowUsed;		        
        protected int iProgRowsUsed;	
	
		protected int iProgWordsUsed;

		public int [] iEEMem;
		public bool [] bEEWordUsed;
		protected int iEEWordsUsed;
				
		public int [] iConfigMem;
		public bool [] bConfigWordUsed;		
		protected int iConfigWordsUsed;

		// 
		public delegate void HexFileValidateDelegate( object sender, clsHexFileValidateEventArgs e );
		public event HexFileValidateDelegate HexFileValidate;	

		// 
		public delegate void HexFileParseDelegate( object sender, clsHexFileParseEventArgs e );
		public event HexFileParseDelegate HexFileParse;	


        //---------------------------------------------------------------------
		// Constructor()
		//---------------------------------------------------------------------
		public clsHex()
		{
            objParsedSettings = new clsParseSettings();
		}// Constructor()


		//---------------------------------------------------------------------
		// Constructor()
		//---------------------------------------------------------------------
		public clsHex( string pstrFilename )
		{
            objParsedSettings = new clsParseSettings();
            strFilename = pstrFilename;
		}// Constructor()
		
						        
		//---------------------------------------------------------------------
		// Event: HexFileParse
		//---------------------------------------------------------------------
		protected internal void OnHexFileParse( clsHexFileParseEventArgs e )
		{
			// Event will be null if no client has hooked up a delegate to the event
			if ( HexFileParse != null ) {
				HexFileParse( this, e );
			}
		}//Event: HexFileParse	
		
		        
		//---------------------------------------------------------------------
		// Event: FileValidate
		//---------------------------------------------------------------------
		protected internal void OnHexFileValidate( clsHexFileValidateEventArgs e )
		{
			// Event will be null if no client has hooked up a delegate to the event
			if ( HexFileValidate != null ) {
				HexFileValidate( this, e );
			}
		}//Event: FileValidated

 
 		//---------------------------------------------------------------------
		// Property: configWordsUsed
		//---------------------------------------------------------------------
		public int configWordsUsed
		{
			get {
				return iConfigWordsUsed;
			}
        }//Property: configWordsUsed


 		//---------------------------------------------------------------------
		// Property: eeWordsUsed
		//---------------------------------------------------------------------
		public int eeWordsUsed
		{
			get {
				return iEEWordsUsed;
			}
        }//Property: eeWordsUsed


 		//---------------------------------------------------------------------
		// Property: filename
		//---------------------------------------------------------------------
		public string filename
		{
			get {
				return strFilename;
			} set {
				if ( value != strFilename ) {
					strFilename = value;
                    
                    bIsParsed = false;
                    bHasValidProgram = false;
		            bHasValidEEPROM = false;
		            bHasValidConfigs = false;
				}
			}
        }//Property: filename
       

 		//---------------------------------------------------------------------
		// Property: hasValidProgram
		//---------------------------------------------------------------------
		public bool hasValidProgram
		{
			get {
				return bHasValidProgram;
			}
        }//Property: hasValidProgram

        
 		//---------------------------------------------------------------------
		// Property: hasValidEEPROM
		//---------------------------------------------------------------------
		public bool hasValidEEPROM
		{
			get {
				return bHasValidEEPROM;
			}
        }//Property: hasValidEEPROM

        
 		//---------------------------------------------------------------------
		// Property: hasValidConfigs
		//---------------------------------------------------------------------
		public bool hasValidConfigs
		{
			get {
				return bHasValidConfigs;
			}
        }//Property: hasValidConfigs


 		//---------------------------------------------------------------------
		// Property: isParsed
		//---------------------------------------------------------------------
		protected bool isParsed
		{
			get {
				return bIsParsed;
			}
        }//Property: isParsed


 		//---------------------------------------------------------------------
		// Property: progRowsUsed
		//---------------------------------------------------------------------
		public int progRowsUsed
		{
			get {
				return iProgRowsUsed;
			}
        }//Property: progRowsUsed


  		//---------------------------------------------------------------------
		// Property: progWordsUsed
		//---------------------------------------------------------------------
		public int progWordsUsed
		{
			get {
				return iProgWordsUsed;
			}
        }//Property: progWordsUsed


        //---------------------------------------------------------------------
		// BytesToWrite()
		//---------------------------------------------------------------------
		virtual public int BytesToWrite( clsDevice pobjDevice, bool pbWriteProgram, bool pbWriteEEPROM, bool pbWriteConfigs )
		{
			return 0;
		}// BytesToWrite()
        

  		//---------------------------------------------------------------------
		// NeedsParsing()
		//---------------------------------------------------------------------
		protected bool NeedsParsing( clsParseSettings pobjSettings )
		{
			return ( pobjSettings.CompareTo(objParsedSettings) == false || isParsed == false );
        }//Property: NeedsParsing()


  		//---------------------------------------------------------------------
		// UpdateParsedSettings()
		//---------------------------------------------------------------------
        protected void UpdateParsedSettings( clsParseSettings pobjSettings )         
        {
            bIsParsed = true;
            objParsedSettings.CopyFrom( pobjSettings );
        }// UpdateParsedSettings()


        //---------------------------------------------------------------------
		// ParseHexFile()
		//---------------------------------------------------------------------
		virtual public void ParseHexFile( clsParseSettings pobjSettings, int iTabLevel, ref bool pbResult )
		{
			pbResult = false;
            return;
		}// ParseHexFile()


        //---------------------------------------------------------------------
		// ValidateHexFile()
		// Description: validates a microchip hex-file
		//---------------------------------------------------------------------
		public void ValidateHexFile( int iTabLevel, ref bool pbResult )
		{	
			int iChecksum;
			string strInFileLine;
			int iDataCount;
			int iAddrCode;
			int iAddress;
			int iData;
			int iIter;
			
			OnHexFileValidate( new clsHexFileValidateEventArgs(clsHexFileValidateEventArgs.EventType.started, "Validating hexfile...", iTabLevel++ ) );
		    
			//--------------------------------------------------------------------------
			// Check file existense
			//--------------------------------------------------------------------------
			if ( strFilename == string.Empty || File.Exists(strFilename) == false) {
				OnHexFileValidate( new clsHexFileValidateEventArgs(clsHexFileValidateEventArgs.EventType.failed, "nonexisting file specified", -1) );
				pbResult = false;
                return;
			}
		    
		    
			//--------------------------------------------------------------------------
			// Create file reader object
			//--------------------------------------------------------------------------
		    TextReader textReader = new StreamReader( strFilename );
		    
		    
			//--------------------------------------------------------------------------
			// Check for an empty file
			//--------------------------------------------------------------------------
			if ( textReader.Peek() == -1 ) {
                OnHexFileValidate( new clsHexFileValidateEventArgs(clsHexFileValidateEventArgs.EventType.failed, "hex-file is empty", -1) );
				textReader.Close();
				pbResult = false;
                return;
			}
		    
		    
			//--------------------------------------------------------------------------
			// Do validation
			//--------------------------------------------------------------------------
			while ( textReader.Peek() != -1 ) {
				strInFileLine = textReader.ReadLine();

				iAddrCode = 0;
				string strDataByte = strInFileLine.Substring(0, 1);
				
				if ( strDataByte == string.Empty ) {
					iData = (int)Encoding.ASCII.GetBytes( " " )[0];
					//iData = Asc(" ");
				} else {
					iData = (int)Encoding.ASCII.GetBytes( strInFileLine.Substring(0, 1) )[0];
					//iData = Asc(  );
				}
		        
				// Check the line
				if ( strDataByte == ":" ) {
					iAddrCode = int.Parse( strInFileLine.Substring(7, 2), System.Globalization.NumberStyles.HexNumber );
					iDataCount = int.Parse( strInFileLine.Substring(1, 2), System.Globalization.NumberStyles.HexNumber );
					iAddress = int.Parse( strInFileLine.Substring(3, 4), System.Globalization.NumberStyles.HexNumber ) & 65535;
	                
					// Check count and alignment of regular data
					/*if ( iAddrCode == 0 ) {
						if ( (iDataCount % 16) != 0 ) {
                            OnHexFileValidate( new clsHexFileValidateEventArgs(clsHexFileValidateEventArgs.EventType.error, "invalid datacount", -1) );
							return false;
						}
						if ( lAddress % 16 != 0 ) {
                            OnHexFileValidate( new clsHexFileValidateEventArgs(clsHexFileValidateEventArgs.EventType.error, "invalid address alignment", -1) );
							return false;
						}
					}*/
	            
					iChecksum = 0;
					for ( iIter = 0; iIter <= iDataCount + 4; iIter++ ) {
						iAddress = iChecksum + int.Parse( strInFileLine.Substring((2 * iIter) + 1, 2), System.Globalization.NumberStyles.HexNumber ) & 65535;
					}
	            
					if ( (iChecksum & 255) != 0 ) {
                        OnHexFileValidate( new clsHexFileValidateEventArgs(clsHexFileValidateEventArgs.EventType.failed, "crc-error in hex-file", -1) );
						textReader.Close();
						pbResult = false;
                        return;
					}
				} else if ( strDataByte == " " || strDataByte == "\t" || strDataByte == "\r" || strDataByte == "\n" ) {

				} else {
                    OnHexFileValidate( new clsHexFileValidateEventArgs(clsHexFileValidateEventArgs.EventType.failed, "invalid file format", -1) );
					textReader.Close();
					pbResult = false;
                    return;
				}
		        
				if ( iAddrCode == 1  ) {
					break;
				}
		        
				if ( textReader.Peek() == -1 ) {
                    OnHexFileValidate( new clsHexFileValidateEventArgs(clsHexFileValidateEventArgs.EventType.failed, "hex-file is incomplete", -1) );
					textReader.Close();
					pbResult = false;
                    return;
				}
			}//while ( textReader.Peek() != -1 ) {
		    

            //            
            textReader.Close();

            //
            OnHexFileValidate( new clsHexFileValidateEventArgs(clsHexFileValidateEventArgs.EventType.success, "", -1) );		    
			pbResult = true;
            return;
		}// ValidateHexFile()
 
	}// Class: clsHex


    
    
}
