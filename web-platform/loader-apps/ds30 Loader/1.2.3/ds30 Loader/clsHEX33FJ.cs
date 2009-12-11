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
using System.IO;
using GHelper;


namespace ds30Loader
{
	//-------------------------------------------------------------------------
	// Class: clsHex33FJ
	//-------------------------------------------------------------------------
	public class clsHex33FJ : clsHex
	{
		//---------------------------------------------------------------------
		// Size suffixes
		//---------------------------------------------------------------------
		// R - rows
		// W - words
		// P - program counter units
		// B3 - bytes		
	

		//---------------------------------------------------------------------
		// 
		//---------------------------------------------------------------------
		// 1 page = 8 rows = 512 words = 1024 pcu = 1536 bytes 


		//---------------------------------------------------------------------
		// Constants
		//---------------------------------------------------------------------

        // dsPIC33F
        private const int iPageSizeR = 8;        
        
		public const int iProgPageUsedBufferSize = 512;
		public const int iProgRowUsedBufferSize = iProgPageUsedBufferSize * iPageSizeR;
		public const int iProgMemBufferSize = iProgRowUsedBufferSize * 64 * 3;
		
        public const int iConfigWordsUsedBufferSize = 8;
        public const int iConfigMemBufferSize = iConfigWordsUsedBufferSize * 2;
		


        //---------------------------------------------------------------------
		// Constructor()
		//---------------------------------------------------------------------
		public clsHex33FJ() : base ()
		{

		}// Constructor()


		//---------------------------------------------------------------------
		// Constructor()
		//---------------------------------------------------------------------
		public clsHex33FJ( string pstrFilename ) : base ( pstrFilename )
		{
			// Size buffer arrays
			bProgPageUsed = new bool[ iProgPageUsedBufferSize ];
			bProgRowUsed = new bool[ iProgRowUsedBufferSize ];
			iProgMem = new int[ iProgMemBufferSize ];
			
			iConfigMem = new int[ iConfigMemBufferSize ];
			bConfigWordUsed = new bool[ iConfigWordsUsedBufferSize ];
		}// Constructor()
				

        //---------------------------------------------------------------------
		// BytesToWrite()
		//---------------------------------------------------------------------
		override public int BytesToWrite( clsDevice pobjDevice, bool pbWriteProgram, bool pbWriteEEPROM, bool pbWriteConfigs )
		{
			return 
                Convert.ToInt32(pbWriteProgram) * (iProgPagesUsed * pobjDevice.pageSizeR * pobjDevice.rowsizeW * 3) + 
                Convert.ToInt32(pbWriteConfigs ) * iConfigWordsUsed * 2
            ;
		}// BytesToWrite()


        //---------------------------------------------------------------------
		// ParseHexFile()
		//---------------------------------------------------------------------
        override public void ParseHexFile( clsParseSettings pobjSettings, int iTabLevel, ref bool pbResult )
		{
			string strFileLine;
            int[] iInData = new int[ 256 ];
            string strLineData;
            int iLineByteCount;
            int iLineAddr;
            int iLineCode;
            int iOutAddr;
            int iLineAddrHigh = 0;
            TextReader textReader;
            int iIter;
            int iAddress;
            int iWordCount;

            
            //---------------------------------------------------------------------
		    // Allready parsed?
		    //---------------------------------------------------------------------
            pobjSettings.fileTimestamp = File.GetLastWriteTime( filename );
            if ( NeedsParsing(pobjSettings) == false ) {
                pbResult = true;
                return; 
            }



            //
            OnHexFileParse( new clsHexFileParseEventArgs(clsHexFileParseEventArgs.EventType.started, "Parsing hexfile...", iTabLevel++) );

            //
            bIsParsed = false;
			bHasValidProgram = true;
			bHasValidEEPROM = false;
			bHasValidConfigs = true;
			
		    
		    //---------------------------------------------------------------------
		    // Validate hex-file
		    //---------------------------------------------------------------------
            bool bValidateResult = false;
            ValidateHexFile( iTabLevel, ref bValidateResult );
            if ( bValidateResult == false ) {
                OnHexFileParse( new clsHexFileParseEventArgs(clsHexFileParseEventArgs.EventType.failed, "Parsing of hex-file failed", iTabLevel++) );
                pbResult = false;
                return;
            }


            //--------------------------------------------------------------------------
            // Open hex-file
            //--------------------------------------------------------------------------
            textReader = new StreamReader( strFilename );


            //--------------------------------------------------------------------------
            // Initialize arrays to default values
            //--------------------------------------------------------------------------			
            for ( iIter = 0; iIter < iProgPageUsedBufferSize; iIter++ ) bProgPageUsed[ iIter ] = false;
            for ( iIter = 0; iIter < iProgRowUsedBufferSize; iIter++ ) bProgRowUsed[ iIter ] = false;
            for ( iIter = 0; iIter < iProgMemBufferSize; iIter++ ) iProgMem[ iIter ] = 0xFF;

            for ( iIter = 0; iIter < iConfigWordsUsedBufferSize; iIter++ ) bConfigWordUsed[iIter] = false;
			for ( iIter = 0; iIter < iConfigMemBufferSize; iIter++ ) iConfigMem[iIter] = 255;


            //--------------------------------------------------------------------------
            // do actual parsing
            //
            // Hex-file format
            //
            // : 10 8000 00 0800 fa00 000f 8001
            // | |  |    |  |-Data
            // | |  |    |----Line code
            // | |  |---------Line address
            // | |------------Line data count
            // |--------------Just a simple colon
            //
            //--------------------------------------------------------------------------
            while ( textReader.Peek() != -1 ) {
                strFileLine = textReader.ReadLine();

                //Init the array with 0xFF
                for ( iIter = 0; iIter < 256; iIter++ ) {
                    iInData[ iIter ] = 255;
                }

                iLineCode = 0;
                if ( strFileLine.Substring( 0, 1 ) == ":" ) {
                    //Parse the line
                    iLineByteCount = int.Parse( strFileLine.Substring( 1, 2 ), System.Globalization.NumberStyles.HexNumber );
                    iLineAddr = ( int.Parse( strFileLine.Substring( 3, 4 ), System.Globalization.NumberStyles.HexNumber ) & 65535 );
                    iLineCode = int.Parse( strFileLine.Substring( 7, 2 ), System.Globalization.NumberStyles.HexNumber );
                    strLineData = strFileLine.Substring( 9, ( iLineByteCount * 2 ) );

                    iAddress = ( (iLineAddrHigh << 16) + iLineAddr ) / 2;

                    // Data record
                    if ( iLineCode == 0 ) {
                        iWordCount = iLineByteCount / 4;

                        // Regular program memory
                        if ( iAddress <= 0x02AC00 ) {
							iOutAddr = (iAddress * 3) / 2;
							
							for ( int iWord = 0; iWord < iWordCount; iWord++ ) {
								//upper-low-high								
								iProgMem[iOutAddr + iWord*3 + 0] = int.Parse( strLineData.Substring(iWord*8 + 4, 2), System.Globalization.NumberStyles.HexNumber );
								iProgMem[iOutAddr + iWord*3 + 1] = int.Parse( strLineData.Substring(iWord*8 + 0, 2), System.Globalization.NumberStyles.HexNumber );
								iProgMem[iOutAddr + iWord*3 + 2] = int.Parse( strLineData.Substring(iWord*8 + 2, 2), System.Globalization.NumberStyles.HexNumber );
								++iProgWordsUsed;								
                                bProgPageUsed[ (iAddress/2 + iWord) / ( pobjSettings.device.pageSizeR * pobjSettings.device.rowsizeW)  ] = true;
								bProgRowUsed[ (iAddress/2 + iWord) / pobjSettings.device.rowsizeW  ] = true;
							}	
							                        
						// Config memory
						} else if ( iAddress >= 0xF80000 && iAddress <= 0xF8000E) {	
							iOutAddr = iAddress - 0xF80000;
							
							for ( int iWord = 0; iWord < iWordCount; iWord++ ) {
								iConfigMem[iOutAddr + iWord*2 + 0] = int.Parse( strLineData.Substring(iWord*8 + 0, 2), System.Globalization.NumberStyles.HexNumber );
								iConfigMem[iOutAddr + iWord*2 + 1] = int.Parse( strLineData.Substring(iWord*8 + 2, 2), System.Globalization.NumberStyles.HexNumber );
								
								bConfigWordUsed[iOutAddr/2 + iWord] = true;
							}	
                        }

                    // End Of File record
                    } else if ( iLineCode == 1 ) {
                        break;

                    // Extended Linear Address Record
                    // The two data bytes represent the upper 16 bits of the 32 bit address, when combined with the address of the 00 type record.
                    } else if ( iLineCode == 4 ) {
                        iLineAddrHigh = ( int.Parse( strFileLine.Substring( 9, 4 ), System.Globalization.NumberStyles.HexNumber ) & 65535 );
                    }
                }
            }


            //--------------------------------------------------------------------------
            // Close files
            //--------------------------------------------------------------------------
            textReader.Close();


            //--------------------------------------------------------------------------
            // Calculate adresses
            //--------------------------------------------------------------------------
            int iBootloaderStartRow = (pobjSettings.device.flashSizeP / 2 - pobjSettings.device.pageSizeR * pobjSettings.device.rowsizeW) / pobjSettings.device.rowsizeW;
            int iBootloaderEndRow = iBootloaderStartRow + pobjSettings.bootloaderSizeR - 1;
            int iBootloaderStartAdress = pobjSettings.device.flashSizeP - pobjSettings.device.pageSizeR * pobjSettings.device.rowsizeW * 2;   //bootloader is placed in 2nd last page

            int iBootloaderStartAdressB3 = (iBootloaderStartAdress / 2) * 3;	//starting index in buffer
            int iUserAppGotoAdressB3 = iBootloaderStartAdressB3 - 6;			//starting index in buffer


            //--------------------------------------------------------------------------
            // Check for code that would overwrite the bootloader
            //--------------------------------------------------------------------------
            bool bOk = true;

            for ( iIter = iBootloaderStartRow; iIter <= iBootloaderEndRow; iIter++ ) {
                if ( bProgRowUsed[ iIter ] == true ) {
                    bOk = false;
                    break;
                }
            }
			if ( bOk == false ) {
                OnHexFileParse( new clsHexFileParseEventArgs(clsHexFileParseEventArgs.EventType.warning, "The hex-file contains code that will overwrite the bootloader", iTabLevel) );
				if ( pobjSettings.allowBlOverwrite == false ) {
					bHasValidProgram = false;
				}
			}


            //--------------------------------------------------------------------------
            // Check for GOTO at 0x00
            //--------------------------------------------------------------------------
            if ( pobjSettings.noGoto == false ) {
                bOk = false;
                for ( iIter = 0; iIter < 6; iIter++ ) {
                    if ( iProgMem[ iIter ] != 255 ) {
                        bOk = true;
                        break;
                    }
                }
                if ( bOk == false || bProgRowUsed[0] == false ) {
                    OnHexFileParse( new clsHexFileParseEventArgs(clsHexFileParseEventArgs.EventType.warning, "There's no GOTO at location 0x00", iTabLevel) );
                    bHasValidProgram = false;
                }

                //--------------------------------------------------------------------------
                // Swap user goto at 0x00 to bootloader usr:, se firmware code
                // It´s important that this instruction is placed just before a new program row
                //--------------------------------------------------------------------------
                for ( iIter = 0; iIter < 6; iIter++ ) {
                    iProgMem[iUserAppGotoAdressB3 + iIter] = iProgMem[iIter];
                }
                bProgPageUsed[iUserAppGotoAdressB3 / (pobjSettings.device.pageSizeR * pobjSettings.device.rowsizeW * 3)] = true;
                bProgRowUsed[iUserAppGotoAdressB3 / (pobjSettings.device.rowsizeW * 3)] = true;
            }


            //--------------------------------------------------------------------------
            // Find out how many pages are used
            //--------------------------------------------------------------------------
            iProgPagesUsed = 0;
            for ( iIter = 0; iIter < iProgPageUsedBufferSize; iIter++ ) {
                if ( bProgPageUsed[ iIter ] == true ) {
                    ++iProgPagesUsed;
                    if ( clsds30Loader.debugMode ) {
                        OnHexFileParse( new clsHexFileParseEventArgs(clsHexFileParseEventArgs.EventType.info, "program page " + iIter.ToString() + " is used", iTabLevel) );
                    }
                }
            }


            //--------------------------------------------------------------------------
            // Find out how many program rows are used
            //--------------------------------------------------------------------------
            iProgRowsUsed = 0;
            for ( iIter = 0; iIter < iProgRowUsedBufferSize; iIter++ ) {
                if ( bProgRowUsed[ iIter ] == true ) {
                    ++iProgRowsUsed;
                    if ( clsds30Loader.debugMode ) {
                        OnHexFileParse( new clsHexFileParseEventArgs(clsHexFileParseEventArgs.EventType.info, "program row " + iIter.ToString() + " is used", iTabLevel) );
                    }
                }
            }
            if ( iProgRowsUsed == 0 ) {
                bHasValidProgram = false;
            }

					    
			//--------------------------------------------------------------------------
			// Find out how many configurations are used
			//--------------------------------------------------------------------------
			iConfigWordsUsed = 0;
			for ( iIter = 0; iIter < iConfigWordsUsedBufferSize; iIter++ ) {
				if ( bConfigWordUsed[iIter] == true ) { 
					++iConfigWordsUsed;
				}
			}
			if ( iConfigWordsUsed > pobjSettings.device.configCount ) {
				OnHexFileParse( new clsHexFileParseEventArgs(clsHexFileParseEventArgs.EventType.warning, "hex-file contains more config locations than the device has", iTabLevel) );
				bHasValidConfigs = false;
			} else if ( iConfigWordsUsed == 0 ) {
				bHasValidConfigs = false;
			}


            //--------------------------------------------------------------------------
            // Set GOTO to bootloader at 0x0000
            //--------------------------------------------------------------------------
            if ( pobjSettings.noGoto == false ) {
                // First goto word
                iProgMem[0] = 0x04;												//goto instruction
                iProgMem[1] = ((iBootloaderStartAdress & 0x0000FE));			//low adress byte			
                iProgMem[2] = ((iBootloaderStartAdress & 0x00FF00) >> 8);		//high adress byte				
                // Second goto word
                iProgMem[3] = 0x00;												//not used by goto
                iProgMem[4] = ((iBootloaderStartAdress & 0x7F0000) >> 16);	    //upper adress byte
                iProgMem[5] = 0x00;												//not used by goto	
            }


			//--------------------------------------------------------------------------
			// Return
			//--------------------------------------------------------------------------
            OnHexFileParse( new clsHexFileParseEventArgs(clsHexFileParseEventArgs.EventType.success, "Hex-file successfully parsed", iTabLevel) );
            
            
            bIsParsed = true;

			pbResult = true;
		}// ParseHexFile()
         
	}// Class: clsHex33FJ
}
