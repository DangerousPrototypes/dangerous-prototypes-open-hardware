//-----------------------------------------------------------------------------
//
// Title:			ds30 Loader
//
// Copyright:		Copyright © 08-09, Mikael Gustafsson
//
// Version:			1.2.3 november 2009
//
// Link:			http://mrmackey.no-ip.org/elektronik/ds30loader/
//
// History:			1.2.3 Input buffer is cleared when resetting
//                        New reset method: command sequence
//                  1.2.2 More improvements in FindLoader() to reduce time from hello to download
//                        Added public versionstring
//                        Alot of non-functional code improvements
//                        PIC18FJ: fixed bug in WriteFlash()
//                        PIC18FJ: fixed incorrect flashsize for most devices
//                        PIC18FJ: fixed bootloader placement to 2nd last page, configs are stored in last page
//                  1.2.1 Added support for PIC18F 1.5 version
//                        Minor improvements in FindLoader()
//                  1.2.0 Added a settings class that's to be passed to Download()
//                        Reset device options added
//                        Activate device options added
//                        Added debug output for all devicefamilies/firmware versions
//                        Improvements in FindLoader()
//                        Fixed eeprom and config write for dsPIC30F firmware >= 2.0
//                  1.1.1 Fixed dsPIC30F3011 device id, from 3 to 13
//                  1.1.0 Major code rework making it more independent and easier to integrate to 3rd party gui
//                  1.0.4 Some improvements in clsSerialPort
//                        GUI and actual bootloader code is now separated
//                        clsSerialport and debugtext moved to separate helper library
//                  1.0.3 Added recognition of new fw versions
//                  1.0.2 Added support for PIC18FJ
//                        Added debugmode
//                  1.0.1 Fixed incorrect bootloder size for PIC18 with rowsize <> 16 words
//                  1.0.0 Added support for PIC24H
//                        Split PIC24F to PIC24F and PIC24FJ
//                        Added support for PIC18F
//                        Fixed som copy/paste errors
//                  0.9.9 Fixed configs not found in dsPIC33
//                        Fixed dsPIC33F config write, byte instead of word
//                  0.9.9 Added support for PIC24F
//                        Fixed incorrect addresscheck in ParseHex()
//                  0.9.8 EEPROM buffer is now properly sized
//						  Optimized ParseHex()
//						  Added support for dsPIC33F
//					0.9.7 Added support for eeprom programming
//						  Better error handling
//						  Added chek for config count
//					0.9.6 Fixed checksum calc for configs
//                  0.9.5 Fixed broken support for dsPIC30F3013
//                        Added support for 1010, 2020, 2023, 5016 and 6015
//					0.9.4 Fixed a bug that caused invalid goto on devices with flash size > ??
//					0.9.3 Fixed a bug in ParseHex()
//					0.9.2 Support for new 0.9.2 algoritm where only 96bytes are sent for each row instead of 128, ~25% faster
//					0.9.0 Initial release
//
//-----------------------------------------------------------------------------

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
using GHelper;
using System.Threading;
using System.Windows.Forms;

namespace ds30Loader
{



	//-------------------------------------------------------------------------
	// Class: clsds30Loader
	//-------------------------------------------------------------------------
	static public class clsds30Loader
	{
		//---------------------------------------------------------------------
		// Size suffixes
		//---------------------------------------------------------------------
		// R - rows
		// W - words
		// P - program counter units
		// B3 - bytes				
		// B4 - bytes		

			
		//---------------------------------------------------------------------
		// Variables 
		//---------------------------------------------------------------------
        static private int iBootloaderSizeR;
        static private int iFWVerMaj = 9;
        static private int iFWVerMin = 9;
        static private int iFWVerRev = 9;

		static private bool bAbort = false;			//external abortsignal
        static private bool bDebugmode = false;


		//---------------------------------------------------------------------
		// Test-mode
		//--------------------------------------------------------------------- 
        static private bool bTestMode = false;
        private const int iTestDeviceID = 468;
        private const int iTestVerMaj = 0;
        private const int iTestVerMin = 9;
        private const int iTestVerRev = 0;


		//---------------------------------------------------------------------
		// Constants
		//---------------------------------------------------------------------        
        public const string strVersion = "1.2.3";

        private const byte cHello = 0xC1;
		private const char cOK = 'K';
		private const char cChecksumErr = 'N';
        private const char cVerifyErr = 'V';
		
		private const byte cCmdErasePage = 1;   //bit 0
		private const byte cCmdWriteRow = 2;    //bit 1
        private const byte cCmdWriteEEWord = 4; //bit 2
		private const byte cCmdWriteConfig = 8; //bit 3
        private const byte cCmdRead = 16;       //bit 4


		// 
		public delegate void DownloadingDelegate( object sender, clsDownloadingEventArgs e );
		static public event DownloadingDelegate Downloading;		

		        
		//---------------------------------------------------------------------
		// Event: Downloading
		//---------------------------------------------------------------------
		static internal void OnDownloading( clsDownloadingEventArgs e )
		{
			// Event will be null if no client has hooked up a delegate to the event
			if ( Downloading != null ) {
				Downloading( null, e );
			}
		}//Event: FileValidated
		

 		//---------------------------------------------------------------------
		// Property: debugMode
		//---------------------------------------------------------------------
		static public bool debugMode
		{
			get {
				return bDebugmode;
			} set {
                 bDebugmode = value;
            }
        }//Property: family  	
	

		//---------------------------------------------------------------------
		// Abort()
		//---------------------------------------------------------------------
		static public void Abort()
		{
			bAbort = true;
		}// Abort()       

        
		//---------------------------------------------------------------------
		// Download()
		//---------------------------------------------------------------------
		static public void Download ( clsDevice pobjDevice, clsSerialPort pobjPort, clsHex pobjHex, clsDownloadSettings pobjSettings, int iTabLevel, ref bool pbResult )
		{
            //
            bool bWriteSuccess = false;
            bool bParseResult = false;

            pbResult = false;
            bAbort = false;
            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.started, "Initiating download...", iTabLevel++) );
            
            // Test-mode
            if ( bTestMode == true ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.warning, "Test-mode is active", iTabLevel) );
            }


			//--------------------------------------------------------------------------
			// Reset device
			//--------------------------------------------------------------------------
            bool bResetResult = false;
            ResetDevice( pobjPort, pobjSettings, iTabLevel, ref bResetResult );
            if ( bResetResult == false ) {
                return;
            }

    			
		    //--------------------------------------------------------------------------
		    // Open port
		    //--------------------------------------------------------------------------
		    bool bOpenPortResult = false;
            PortOpen( pobjPort, pobjSettings, ref bOpenPortResult );


			//--------------------------------------------------------------------------
			// Find loader
			//--------------------------------------------------------------------------
            bool bFindLoaderResult = false;
            FindLoader( pobjDevice, pobjPort, pobjSettings, iTabLevel, ref bFindLoaderResult );
            if ( bFindLoaderResult == false ) {
				PortClose( pobjPort );
                return;
            }
            		    

			//--------------------------------------------------------------------------
			// Init progressbar
			//--------------------------------------------------------------------------
            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progressStarted, "", 0) );


			//--------------------------------------------------------------------------
			// Determine size of the bootloader found
			//--------------------------------------------------------------------------
            bool bGetBLSizeResult = false;
            iBootloaderSizeR = GetBLSize( pobjDevice, ref bGetBLSizeResult );
            if ( bGetBLSizeResult == false ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Unknown firmware version", iTabLevel) );
                PortClose( pobjPort );
                return;
            }
            

			//--------------------------------------------------------------------------
			// 
			//--------------------------------------------------------------------------
            bool WaitBLReadyResponseResult = false;
            WaitBLReadyResponse( pobjPort, iTabLevel, ref WaitBLReadyResponseResult );
            if ( WaitBLReadyResponseResult == false ) {
                PortClose( pobjPort );
                return;
            }


			//--------------------------------------------------------------------------
			// Setup parse settings
			//--------------------------------------------------------------------------
            clsParseSettings objParseSettings = new clsParseSettings( iBootloaderSizeR, pobjDevice, false, pobjSettings.noGoto );

            
            //--------------------------------------------------------------------------
            // PIC18F
            //--------------------------------------------------------------------------
            if ( pobjDevice.family.name == "PIC18F" ) {
                clsHex18F objHex18F = (clsHex18F)pobjHex;	
                
                // Parse				
                objHex18F.ParseHexFile( objParseSettings, iTabLevel, ref bParseResult );
                if ( bParseResult == false ) {
                    PortClose( pobjPort );
                    return;
				}

                // Write versions 0.9.0 - 1.0.0
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 2 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 1 )
                ) {
                    bWriteSuccess = WriteFlash18F_0_9_0( pobjPort, pobjDevice, objHex18F, pobjSettings.writeProgram, pobjSettings.writeEEPROM, pobjSettings.writeConfigs, iTabLevel );
                
                    // Write versions 1.5
                } else if ( 
                    ( iFWVerMaj == 1 && iFWVerMin == 5 )
                ) {                    
                    bWriteSuccess = WriteFlash18F_0_9_0( pobjPort, pobjDevice, objHex18F, pobjSettings.writeProgram, false, false, iTabLevel );  
              
                // Unkown version
                } else {
                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Unknown firmware version", iTabLevel) );
                    PortClose( pobjPort );
					return;
                }


            //--------------------------------------------------------------------------
            // PIC18FJ
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "PIC18FJ" ) {
                clsHex18FJ objHex18FJ = (clsHex18FJ)pobjHex;	
                
                // Parse
                objHex18FJ.ParseHexFile( objParseSettings, iTabLevel, ref bParseResult );
                if ( bParseResult == false ) {		
			        PortClose( pobjPort );
                    return;
				}

                // Write versions 0.9.0 - 0.9.1
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 )
                ) {
                    bWriteSuccess = WriteFlash18FJ_0_9_0( pobjPort, pobjDevice, objHex18FJ, pobjSettings.writeProgram, iTabLevel );
            
                
                // Unkown version
                } else {
                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Unknown firmware version", iTabLevel) );
                    PortClose( pobjPort );
					return;
                }


            //--------------------------------------------------------------------------
            // PIC24F
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "PIC24F" ) {
                clsHex24F objHex24F = (clsHex24F)pobjHex;
                
                // Parse
                objHex24F.ParseHexFile( objParseSettings, iTabLevel, ref bParseResult );
                if ( bParseResult == false ) {
                    PortClose( pobjPort );
                    return;
				}

                // Write versions 0.9.0 - 0.9.0
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1 )
                ) {
                    bWriteSuccess = WriteFlash24F_0_9_0( pobjPort, pobjDevice, objHex24F, pobjSettings.writeProgram, pobjSettings.writeEEPROM, pobjSettings.writeConfigs, iTabLevel );
            
                
                // Unkown version
                } else {
                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Unknown firmware version", iTabLevel) );
                    PortClose( pobjPort );
					return;
                }
   

            //--------------------------------------------------------------------------
            // PIC24FJ
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "PIC24FJ" ) {
                clsHex24FJ objHex24FJ = (clsHex24FJ)pobjHex;
                
                // Parse
                objHex24FJ.ParseHexFile( objParseSettings, iTabLevel, ref bParseResult );
                if ( bParseResult == false ) {	
				    PortClose( pobjPort );
                    return;
				}

                // Write versions 0.9.0 - 1.0.1
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 2 ) 
                ) {
                    bWriteSuccess = WriteFlash24FJ_1_0_0( pobjPort, pobjDevice, objHex24FJ, pobjSettings.writeProgram, pobjSettings.writeEEPROM, pobjSettings.writeConfigs, iTabLevel );
            
                
                // Unkown version
                } else {
                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Unknown firmware version", iTabLevel) );
                    PortClose( pobjPort );
					return;
                }
                
            //--------------------------------------------------------------------------
            // PIC24H
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "PIC24H" ) {
                clsHex24H objHex24H = (clsHex24H)pobjHex;	
                
                // Parse
                objHex24H.ParseHexFile( objParseSettings, iTabLevel, ref bParseResult );
                if ( bParseResult == false ) {		
			        PortClose( pobjPort );
                    return;
				}

                // Write versions 0.9.0 - 0.9.1
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) || 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 ) 
                ) {
                    bWriteSuccess = WriteFlash24H_0_9_0( pobjPort, pobjDevice, objHex24H, pobjSettings.writeProgram, pobjSettings.writeConfigs, iTabLevel );            
                
                // Unkown version
                } else {
                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Unknown firmware version", iTabLevel) );
                    PortClose( pobjPort );
					return;
                }

            //--------------------------------------------------------------------------
            // dsPIC30F
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "dsPIC30F" ) {
                clsHex30F objHex30F = (clsHex30F)pobjHex;
                
                // Parse
                objHex30F.ParseHexFile( objParseSettings, iTabLevel, ref bParseResult );
                if ( bParseResult == false ) {					
                    PortClose( pobjPort );
                    return;
				}

                // Write versions 0.9.4 - 1.0.1
                if ( 
					( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 4 ) ||
					( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 1 )
				) {
                    bWriteSuccess = WriteFlash30_1_0_1( pobjPort, pobjDevice, objHex30F, pobjSettings.writeProgram, pobjSettings.writeEEPROM, pobjSettings.writeConfigs, iTabLevel );
                
                // Versions 2.0.0 - 2.0.2
                } else if ( 
                    ( iFWVerMaj == 2 && iFWVerMin == 0 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 2 && iFWVerMin == 0 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 2 && iFWVerMin == 0 && iFWVerRev == 2 )
				) {
                    bWriteSuccess = WriteFlash30_2_0_0( pobjPort, pobjDevice, objHex30F, pobjSettings.writeProgram, pobjSettings.writeEEPROM, pobjSettings.writeConfigs, iTabLevel );

                // Unkown version
                } else {
                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Unknown firmware version", iTabLevel) );
                    PortClose( pobjPort );
					return;
                }
            
            //--------------------------------------------------------------------------
            // dsPIC33F
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "dsPIC33FJ" ) {
                clsHex33FJ objHex33F = (clsHex33FJ)pobjHex;	
                
                // Parse
                objHex33F.ParseHexFile( objParseSettings, iTabLevel, ref bParseResult );
                if ( bParseResult == false ) {					
                    PortClose( pobjPort );
                    return;
				}

                // Write vrsions 0.9.0 - 1.0.0
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 2 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 3 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 4 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 ) || 
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 2 ) 
                ) {
                    bWriteSuccess = WriteFlash33_1_0_0( pobjPort, pobjDevice, objHex33F, pobjSettings.writeProgram, pobjSettings.writeConfigs, iTabLevel );
            
                
                // Unkown version
                } else {
                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Unknown firmware version", iTabLevel) );
                    PortClose( pobjPort );
					return;
                }
            }
						
					    
			//--------------------------------------------------------------------------
			// Download completed
			//--------------------------------------------------------------------------
            pobjPort.Close();

            if ( bWriteSuccess == true ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.completed, "Download finished", iTabLevel) );	                
            }

            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progressEnded, "", 0) );
            pbResult = bWriteSuccess;
		}// Download()
		
		
		//---------------------------------------------------------------------
		// FindLoader()
		//---------------------------------------------------------------------
		static public void FindLoader( clsDevice pobjDevice, clsSerialPort pobjPort , clsDownloadSettings pobjSettings, int iTabLevel, ref bool pbResult )
		{
            int iDeviceIdFound = -1;
            bool bGetResponseResult = false;
            bool bPortWasOpened = false;

            pbResult = false;

            //-----------------------------------------------------------------
            // Test-mode
            //-----------------------------------------------------------------
            if ( bTestMode == true ) {
                iFWVerMaj = iTestVerMaj;
                iFWVerMin = iTestVerMin;
                iFWVerRev = iTestVerRev;
                iDeviceIdFound = iTestDeviceID;
                //return true;
            
                
            //-----------------------------------------------------------------
            // Real-mode
            //-----------------------------------------------------------------
            } else {
			    
                int iVerMaj = 0, iVerMinRev = 0;
                int iTimeIdReceived = 0;                
    			
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Searching for bl ", iTabLevel) );

			    //--------------------------------------------------------------------------
			    // Open port if not open
			    //--------------------------------------------------------------------------
                if ( pobjPort.isOpen == false ) {
                    pobjPort.Open();
                    if ( pobjPort.isOpen == false ) {
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Failed to open port", iTabLevel) );
                        return;
                    }
                    bPortWasOpened = true;
                }

                
                // Empty buffers prior to hello command incase there's some crap
                pobjPort.EmptyBuffers( true, false );


			    //--------------------------------------------------------------------------
			    // Send hello to bootloader
			    //--------------------------------------------------------------------------
			    bool bDeviceIDReceived = false;
                {
                    int iLastSend = Environment.TickCount - pobjSettings.polltime;
                    int iLastPoll = Environment.TickCount - pobjSettings.polltime;
                    int iStartTime = Environment.TickCount;
                    
                    bool bByteReceived = false;
                    
                    bool bTimedOut = false;

                    do {  
                        // Check first byte, discard if null
                        if ( Environment.TickCount - iLastPoll >= pobjSettings.polltime/10) {     
                            iLastPoll = Environment.TickCount;                            
                            
                            if ( bByteReceived == false && pobjPort.inBufferCount > 0 ) {
                                bByteReceived = true;
                                iDeviceIdFound = GetResponse( pobjPort, ref bGetResponseResult );
                                if ( bGetResponseResult == false ) {
                                    if ( bPortWasOpened == true ) pobjPort.Close();
                                    return;
                                }
                                if ( iDeviceIdFound == 0 ) {
                                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "(discarded null byte)", -1) );
                                } else {
                                    bDeviceIDReceived = true;
                                    iTimeIdReceived = Environment.TickCount;
                                    break;                            
                                }
                             
                            }
                        }

                        // Send hello                    
                       if ( Environment.TickCount - iLastSend >= pobjSettings.polltime ) {                        
                            iLastSend = Environment.TickCount;
                            pobjPort.SendByte( cHello );
                            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, ". ", -1) );
                        }

                        // Check for timeout
                        bTimedOut = ( Environment.TickCount - iStartTime >= pobjSettings.timeout );

                        // Handle message queue
                        Application.DoEvents();
                    } while ( 
                        bAbort == false && 
                        bTimedOut == false &&
                        (bByteReceived == false || pobjPort.inBufferCount == 0)                
                    );
                    
                    if ( bAbort == true  ) {
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted", -1) );
                        bAbort = false;
                        if ( bPortWasOpened == true ) pobjPort.Close();
                        return;
                    } else if ( bTimedOut == true ) {
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "timed out", -1) );
                        if ( bPortWasOpened == true ) pobjPort.Close();
                        return;
                    }
                }


                //--------------------------------------------------------------------------
			    // Read device id
			    //--------------------------------------------------------------------------			
			    if ( bDeviceIDReceived == false ) {
                    iDeviceIdFound = GetResponse( pobjPort, ref bGetResponseResult );
                    if ( bGetResponseResult == false ) {
                        iTimeIdReceived = Environment.TickCount;
                        if ( bPortWasOpened == true ) pobjPort.Close();
				        return;
			        }
                }
    			
    			
			    //--------------------------------------------------------------------------
			    // Delay to receive firmware version if any
			    //--------------------------------------------------------------------------
                int iTime = 1 + 30000 / pobjPort.baudrate;
                while ( Environment.TickCount - iTimeIdReceived < iTime && pobjPort.inBufferCount < 3 ) {            
                }
    			

                //--------------------------------------------------------------------------
                // Firmware doesn´t send version, assume 0.9.4
                //--------------------------------------------------------------------------
                if ( pobjPort.inBufferCount == 1 ) {
                        iFWVerMaj = 0;
                        iFWVerMin = 9;
                        iFWVerRev = 4;
                
                    
                //--------------------------------------------------------------------------
                // Firmware that sends major and minor
                //--------------------------------------------------------------------------
                } else if ( pobjPort.inBufferCount == 2 ) {
                    iVerMaj = GetResponse( pobjPort, ref bGetResponseResult );
                    if ( bGetResponseResult == false ) {
                        if ( bPortWasOpened == true ) pobjPort.Close();
			            return;
                    } 
                    iFWVerMaj = ( (iVerMaj & 0x70) >> 4 );
                    iFWVerMin = ( iVerMaj & 0xF );
                    iFWVerRev = 0;


                //--------------------------------------------------------------------------
                // Firmware that sends major, minor and revision
                //--------------------------------------------------------------------------
                } else if ( pobjPort.inBufferCount == 3 ) {
                    iVerMaj = GetResponse( pobjPort, ref bGetResponseResult );
                    if ( bGetResponseResult == false ) {
                        if ( bPortWasOpened == true ) pobjPort.Close();
			            return;
                    } 
                    iVerMinRev = GetResponse( pobjPort, ref bGetResponseResult );
		            if ( bGetResponseResult == false ) {
                        if ( bPortWasOpened == true ) pobjPort.Close();
			            return;
		            }		    			
        
                    iFWVerMaj = ( iVerMaj & 0x7F );
                    iFWVerMin = ( (iVerMinRev & 0xF0) >> 4 );
                    iFWVerRev = ( iVerMinRev & 0xF );
		        }


                //--------------------------------------------------------------------------
                // PIC18 indicated by msb in fw ver major
                //--------------------------------------------------------------------------
                if ( (iVerMaj & 0x80) > 0 ) {
                    iDeviceIdFound += 300;
                }
            }//Test-/real-mode

            
			//--------------------------------------------------------------------------
			// Find device from device id
			//--------------------------------------------------------------------------
			clsDevice objFoundDevice = clsDevices.DeviceGet( iDeviceIdFound );

			
            //--------------------------------------------------------------------------
            // Invalid ID returned
            //--------------------------------------------------------------------------
			if ( objFoundDevice == null ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Found unknown device id(" + iDeviceIdFound.ToString() + ") fw ver. " + iFWVerMaj.ToString() + "." + iFWVerMin.ToString() + "." + iFWVerRev.ToString(), iTabLevel) );
                if ( bPortWasOpened == true ) pobjPort.Close();
				return;
			}


            //--------------------------------------------------------------------------
            // Bootloader found
            //--------------------------------------------------------------------------
            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "Found " + objFoundDevice.name + " fw ver. " + iFWVerMaj.ToString() + "." + iFWVerMin.ToString() + "." + iFWVerRev.ToString(), iTabLevel) );

            
            //--------------------------------------------------------------------------
            // Different device found from choosen
            //--------------------------------------------------------------------------
            if ( objFoundDevice.id != pobjDevice.id ) {
                OnDownloading(new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Wrong pic detected(" + objFoundDevice.id.ToString() + ")/selected(" + pobjDevice.id.ToString() + "), aborting", iTabLevel));
                if ( bPortWasOpened == true ) pobjPort.Close();
				return;
			}

			pbResult = true;

            // Close port if it was openeed
            if ( bPortWasOpened == true ) {
                pobjPort.Close();
            }
		}// FindLoader()

		
        //---------------------------------------------------------------------
		// WaitBLReadyResponse()
		//---------------------------------------------------------------------
		static private void WaitBLReadyResponse( clsSerialPort pobjPort, int iTabLevel, ref bool pbResult )
        {
            int iResponse = -1;
            pbResult = false;

            //--------------------------------------------------------------------------
			// Get bootloader ready response
			//--------------------------------------------------------------------------
            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Waiting for bootloader to be ready...", iTabLevel) );
			bool bGetResponseResult = false;
            iResponse = GetResponse( pobjPort, ref bGetResponseResult);
            if ( bGetResponseResult == false ) {
				return;
			}
		    
			if ( iResponse != cOK ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "unknown response, aborting", -1) );
				return;
			}
            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
            pbResult = true;
        }//WaitBLReadyResponse()


        //---------------------------------------------------------------------
		// GetBLSize()
		//---------------------------------------------------------------------
		static private int GetBLSize( clsDevice pobjDevice, ref bool pbResult )
		{
            int iBootloaderSizeR = 0;


			//--------------------------------------------------------------------------
            // PIC18F
            //--------------------------------------------------------------------------
            if ( pobjDevice.family.name == "PIC18F" ) {
                // Firmware version 0.9.0 - 0.9.1
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1 )
                ){
                    iBootloaderSizeR = pobjDevice.pageSizeR * 4;    //bl size is 4 pages, rowsize varies among devices
                
                // Firmware version 0.9.2 - 1.0.0
                } else if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 2 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 2 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 1 )
                ){
                    iBootloaderSizeR = pobjDevice.pageSizeR * 5;    //bl size is 5 pages, rowsize varies among devices   
                 
                // Firmware version 1.5 - 1.5
                } else if ( 
                    ( iFWVerMaj == 1 && iFWVerMin == 5 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 5 )
                ){
                    iBootloaderSizeR = pobjDevice.pageSizeR * 3;    //bl size is 3 pages, rowsize varies among devices   
    
                // Unknown firmware version
                } else {
					pbResult = false;
                    return 0;
				}


            //--------------------------------------------------------------------------
            // PIC18FJ
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "PIC18FJ" ) {
                // Firmware version 0.9.0 - 0.9.1
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 )
                ){
                    iBootloaderSizeR = 16;
                    
                // Unknown firmware version
                } else {
					pbResult = false;
                    return 0;
				}	


            //--------------------------------------------------------------------------
            // PIC24F
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "PIC24F" ) {
                // Firmware version 0.9.0 - 0.9.1
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1  )
                ){
                    iBootloaderSizeR = 4;
                    
                // Unknown firmware version
                } else {
					pbResult = false;
                    return 0;
				}	
   

            //--------------------------------------------------------------------------
            // PIC24FJ
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "PIC24FJ" ) {
                // Firmware version 0.9.0 - 1.0.1
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 2 ) 
                ){
                    iBootloaderSizeR = 8;
                    
                // Unknown firmware version
                } else {
					pbResult = false;
                    return 0;
				}	
            
                
            //--------------------------------------------------------------------------
            // PIC24H
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "PIC24H" ) {
                // Firmware version 0.9.0 - 0.9.1 
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 ) 
                ){
                    iBootloaderSizeR = 8;
                    
                // Unknown firmware version
                } else {
					pbResult = false;
                    return 0;
				}	


            //--------------------------------------------------------------------------
            // dsPIC30F
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "dsPIC30F" ) {
                // Firmware version 0.9.4 - 1.0.1
                if ( 
					( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 4 ) ||
					( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 1 )					
				) {
                    iBootloaderSizeR = 3;
                
                // Firmware version 2.0.0 - 2.0.2
                } else if ( 
                    ( iFWVerMaj == 2 && iFWVerMin == 0 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 2 && iFWVerMin == 0 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 2 && iFWVerMin == 0 && iFWVerRev == 2 )
                ) {
					iBootloaderSizeR = 4;
					
                // Unknown firmware version
                } else {
					pbResult = false;
                    return 0;
                }

            
            //--------------------------------------------------------------------------
            // dsPIC33F
            //--------------------------------------------------------------------------
            } else if ( pobjDevice.family.name == "dsPIC33FJ" ) {
                // Firmware version 0.9.0 - 1.0.1
                if ( 
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 2 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 3 ) ||
                    ( iFWVerMaj == 0 && iFWVerMin == 9 && iFWVerRev == 4 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 0 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 1 ) ||
                    ( iFWVerMaj == 1 && iFWVerMin == 0 && iFWVerRev == 2 )
                ) {
                    iBootloaderSizeR = 8;
                    
                // Unknown firmware version
                } else {
					pbResult = false;
                    return 0;
				}	
            }

            pbResult = true;
            return iBootloaderSizeR;
		}// GetBLSize()
		
		
		//---------------------------------------------------------------------
		// GetResponse()
		//---------------------------------------------------------------------
		static private int GetResponse( clsSerialPort pobjPort, ref bool pbResult )
		{
            int iResponse = -1;
            pbResult = false;

            // Test-mode
            if ( bTestMode == true ) {
                pbResult = true;
                return cOK;
            }

            //
			int iStartTime = System.Environment.TickCount;
		    while ( pobjPort.inBufferCount < 1 && System.Environment.TickCount - iStartTime < 2000 && bAbort == false ) {
				Application.DoEvents();
			}

            // Abort
            if ( bAbort == true ) {
                return -1;
            }
			
			// Timeout
			if ( pobjPort.inBufferCount < 1 ) {     
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "response timed out", -1) );
				return -1;
			}			
		    
			pobjPort.ReadByte( ref iResponse );
			pbResult = true;
            return iResponse;
		}// GetResponse()

        
        //---------------------------------------------------------------------
		// PortClose()
		//---------------------------------------------------------------------
		static private void PortClose( clsSerialPort pobjPort )
		{
            pobjPort.Close();
		}// PortClose()


		//---------------------------------------------------------------------
		// PortOpen()
		//---------------------------------------------------------------------
		static private void PortOpen( clsSerialPort pobjPort, clsDownloadSettings pobjSettings, ref bool pbResult )
		{
            pbResult = false;

            // Activate device when we open port
            try {
			    pobjPort.objPort.DtrEnable = pobjSettings.activateDTR;
                pobjPort.objPort.RtsEnable = pobjSettings.activateRTS;
            } catch {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "failed setting dtr & rts", -1) );  
            }

            // Allready open?
            if ( pobjPort.isOpen == true ) {
                pbResult = true;
                return;
            }

            try {
                pobjPort.Open();
            } catch {
            }

            if ( pobjPort.isOpen == false ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "failed to open port", -1) );  
            }

            pbResult = pobjPort.isOpen;
		}// PortOpen()


		//---------------------------------------------------------------------
		// ProcessWriteResponse()
		//---------------------------------------------------------------------
		static private void ProcessWriteResponse( clsSerialPort pobjPort, ref int piRetries, int piTabLevel, string pstrWriteType, ref bool pbRetry, ref bool pbResult )
		{
            int iResponse = -1;
            pbResult = false;

            // Get response
            bool bGetResponseResult = false;
            iResponse = GetResponse( pobjPort, ref bGetResponseResult );
            if ( bGetResponseResult == false ) {
                return;
            }

            // Check response
		    if ( iResponse != cOK ) {
			    if ( ++piRetries == 3 ) {
                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "download failed", -1) );
				    return;
			    } else {
				    if ( iResponse == cChecksumErr ) {
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "checksum error," + piRetries.ToString() + " try", -1) );
                        pbRetry = true;
                    } else if ( iResponse == cVerifyErr ) {
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "verify error," + piRetries.ToString() + " try", -1) );
                        pbRetry = true;
                    } else {
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "unknown response," + piRetries.ToString() + " try", -1) );
                        pbRetry = true;
                    }
				    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing flash...", piTabLevel) );
			    }
		    } else {
                pbRetry = false;
            }

            pbResult = true;
		}// ProcessWriteResponse()


		//---------------------------------------------------------------------
		// ResetDevice()
		//---------------------------------------------------------------------
		static private void ResetDevice( clsSerialPort pobjPort, clsDownloadSettings pobjSettings, int iTabLevel, ref bool pbResult )
		{
            pbResult = false;

            //--------------------------------------------------------------------------
		    // Reset - command
		    //--------------------------------------------------------------------------
            if ( pobjSettings.resetCommand == true ) {
                // Inform user
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Sending reset command", iTabLevel) );
                
                // Parse resetcommand
                bool bSplitResult = false;
                byte[] bBytes = pobjPort.SplitHexStringToBytes( pobjSettings.resetCommandSequence, ref bSplitResult );
                if ( bSplitResult == false ) {
                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "Couldn't parse reset command sequence", iTabLevel) );
                    return;
                }
                /*string[] strBytes = pobjSettings.resetCommandSequence.Split( ';' );
                byte[] bBytes = new byte[ strBytes.Length ];
                int iIndex = 0;
                foreach ( string strByte in strBytes ) {
                    bBytes[iIndex] = byte.Parse( strByte, System.Globalization.NumberStyles.HexNumber );
                    ++iIndex;
                }*/

                // Open port
                int iOldBaudrate = pobjPort.baudrate;                
                pobjPort.baudrate = pobjSettings.resetBaudrate;                
                bool bOpenPortResult = false;
                PortOpen( pobjPort, pobjSettings, ref bOpenPortResult );                
                
                // Send reset command and close port            
                pobjPort.SendBytes( ref bBytes, bBytes.Length );
                while ( pobjPort.outBufferCount > 0 );
                pobjPort.Close();

                // Restore baudrate
                pobjPort.baudrate = iOldBaudrate;

                SleepResponsive( pobjSettings.resetTime );


		    //--------------------------------------------------------------------------
		    // Reset - dtr
		    //--------------------------------------------------------------------------            
            } else if ( pobjSettings.resetDtr == true ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Resetting by dtr", iTabLevel) );
                pobjPort.dtrEnable = true;
                SleepResponsive( pobjSettings.resetTime );
                pobjPort.dtrEnable = false;


		    //--------------------------------------------------------------------------
		    // Reset - rts
		    //--------------------------------------------------------------------------           
            } else if ( pobjSettings.resetRts == true ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Resetting by rts", iTabLevel) );
                pobjPort.rtsEnable = true;
                SleepResponsive( pobjSettings.resetTime );
                pobjPort.rtsEnable = false;
            }

            pbResult = true;
        }//ResetDevice()


        //---------------------------------------------------------------------
		// SleepResponsive()
		//---------------------------------------------------------------------
		static private void SleepResponsive( int piTime )
		{
            int iStartTime = Environment.TickCount;
            while ( Environment.TickCount - iStartTime < piTime ) {
                Application.DoEvents();
            }
        }//SleepResponsive()


        #region WriteFlash

        //---------------------------------------------------------------------
        // WriteFlash18F_0_9_0()
        //---------------------------------------------------------------------
        static private bool WriteFlash18F_0_9_0(clsSerialPort pobjPort, clsDevice pobjDevice, clsHex18F pobjHex, bool pbWriteProgram, bool pbWriteEEPROM, bool pbWriteConfigs, int iTabLevel)
        {
            //--------------------------------------------------------------------------
            // Variables
            //--------------------------------------------------------------------------
            int iChecksum;
            int iSum;
            int iAddrP;
            int iRetries;
            byte[] bBuffer = new byte[256];
            int iBufferIndx;
            byte bAddrU, bAddrH, bAddrL, bSize, bProg;
            bool bRetry = false;
            int iByteToWrite = pobjHex.BytesToWrite( pobjDevice, pbWriteProgram, pbWriteEEPROM, pbWriteConfigs );
            int iBytesWritten = 0;
            bool bProcessWriteResponseResult = false;


            //--------------------------------------------------------------------------
            // Write flash
            //--------------------------------------------------------------------------
            int iRow;

            if ( pbWriteProgram == true ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing flash...", iTabLevel) );
                

                //-------------------------------------------------------------
                // Iterate pages
                //-------------------------------------------------------------
                for ( int iPage = 0; iPage < clsHex18F.iProgPageUsedBufferSize; iPage++ ) {
                    if ( pobjHex.bProgPageUsed[iPage] == true ) {
                        iRetries = 0;
                        do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Erasing page " + iPage.ToString(), iTabLevel) );
                            }

                            //---------------------------------------------------------
                            // Erase page
                            //---------------------------------------------------------
                            iSum = 0;
                            iBufferIndx = 0;

                            // Calculate
                            iAddrP = iPage * pobjDevice.pageSizeR * pobjDevice.rowsizeW * 2;//24-bit address in memory to write to
                            bAddrU = Convert.ToByte((iAddrP & 0xff0000) >> 16);				//address upper byte			               
                            bAddrH = Convert.ToByte((iAddrP & 0x00ff00) >> 8);				//address high byte
                            bAddrL = Convert.ToByte((iAddrP & 0x0000ff) >> 0);				//address low byte
                            bSize = Convert.ToByte(1/*checksum*/ );

                            //
                            bBuffer[iBufferIndx++] = bAddrU; iSum += bAddrU;
                            bBuffer[iBufferIndx++] = bAddrH; iSum += bAddrH;
                            bBuffer[iBufferIndx++] = bAddrL; iSum += bAddrL;
                            bBuffer[iBufferIndx++] = cCmdErasePage; iSum += cCmdErasePage;
                            bBuffer[iBufferIndx++] = bSize; iSum += bSize;

                            // Calculate checksum and add to buffer
                            iSum %= 256;
                            iChecksum = Convert.ToInt16((256 - iSum) % 256);
                            bBuffer[iBufferIndx++] = Convert.ToByte(iChecksum);

                            // Send address, command, packetsize & checksum
                            pobjPort.SendBytes(ref bBuffer, iBufferIndx);

                            // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }

                            //
                            Application.DoEvents();
                        } while ( bRetry == true && bAbort == false);


                        //---------------------------------------------------------
                        // Iterate rows, write all rows in page even if not in hex-file
                        //---------------------------------------------------------
                        for ( iRow = iPage * pobjDevice.pageSizeR; iRow < iPage * pobjDevice.pageSizeR + pobjDevice.pageSizeR; iRow++ ) {
                            iRetries = 0;
                            do {
                                if ( clsds30Loader.debugMode ) {
                                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing row " + iRow.ToString(), iTabLevel) );
                                }

                                iBufferIndx = 0;
                                iSum = 0;

                                // Calculate
                                iAddrP = 2 * iRow * pobjDevice.rowsizeW;				//24-bit address in memory to write to
                                bAddrU = Convert.ToByte((iAddrP & 0xff0000) >> 16);	    //address upper byte			               
                                bAddrH = Convert.ToByte((iAddrP & 0x00ff00) >> 8);	    //address high byte
                                bAddrL = Convert.ToByte((iAddrP & 0x0000ff));			//address low byte
                                bSize = Convert.ToByte(pobjDevice.rowsizeW * 2 + 1/*checksum*/ );

                                //
                                bBuffer[iBufferIndx++] = bAddrU; iSum += bAddrU;
                                bBuffer[iBufferIndx++] = bAddrH; iSum += bAddrH;
                                bBuffer[iBufferIndx++] = bAddrL; iSum += bAddrL;
                                bBuffer[iBufferIndx++] = cCmdWriteRow; iSum += cCmdWriteRow;
                                bBuffer[iBufferIndx++] = bSize; iSum += bSize;

						        // Buffer row
						        for ( int iByte = 0; iByte < pobjDevice.rowsizeW * 2; iByte++ ) {
								    bProg = Convert.ToByte( pobjHex.iProgMem[iAddrP + iByte] );
							        bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
						        }

                                // Calculate checksum and add to buffer
                                iSum %= 256;
                                iChecksum = Convert.ToInt16((256 - iSum) % 256);
                                bBuffer[iBufferIndx++] = Convert.ToByte(iChecksum);

                                // Send address, command, packetsize, row & checksum
                                pobjPort.SendBytes( ref bBuffer, iBufferIndx );

                                // Get response, checksum ok
                                ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                                if ( bProcessWriteResponseResult == false ) {
                                    return false;
                                }

                                //
                                Application.DoEvents();
                            } while ( bRetry == true && bAbort == false );

                            //
                            if (bAbort == true) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
                                return false;
                            }

                            //
                            iBytesWritten += pobjDevice.rowsizeW * 2;
                            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );

                        }//for ( iRow = 0; iRow < iRowUsedBufferSize; iRow++ ) {

                    } //if ( bPageUsed[iIter] == true ) {

                }//for ( iPage = 0; iPage < iPageUsedBufferSize; iPage++ ) {

                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
            }//if ( pbWriteProgram == true ) {


            //--------------------------------------------------------------------------
            // Write EEPROM
            //--------------------------------------------------------------------------
            if ( pbWriteEEPROM == true ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing eeprom...", iTabLevel) );
				
			    for ( int iEEPROMWord = 0; iEEPROMWord < pobjDevice.eepromSizeB; iEEPROMWord++ ) {					
				    if ( pobjHex.bEEWordUsed[iEEPROMWord] == true ) {
						iRetries = 0;
					    do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing eeprom byte " + iEEPROMWord.ToString(), iTabLevel) );
                            }

						    iBufferIndx = 0;
						    iSum = 0;
    		                
		                    // Calculate
		                    iAddrP = iEEPROMWord;		                            //24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
						    bSize = Convert.ToByte( 1 + 1/*checksum*/ );
    						
						    //
						    bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
						    bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
						    bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
                            bBuffer[ iBufferIndx++ ] = cCmdWriteEEWord; iSum += cCmdWriteEEWord;
						    bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;

							// EEPROM byte
						    bProg = Convert.ToByte( pobjHex.iEEMem[iEEPROMWord] );
						    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
    		                
						    // Calculate checksum and add to buffer
						    iSum %= 256;
						    iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
						    bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
    						
						    // Send address, command, size, eeprom byte & checksum
						    pobjPort.SendBytes( ref bBuffer, iBufferIndx );
    		                
		                    // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }
    		                
		                    //
						    Application.DoEvents();
					    } while ( bRetry == true && bAbort == false );
    		            
		                //
					    if ( bAbort == true ) {
						    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
						    return false;
					    }
    		            
    		            //
					    iBytesWritten += 1;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
				     }//if (  bEEWordUsed[iEEPROMWord] == true ) {				     
				     
			    }//for ( iIter = 0; iIter < pobjDevice.eepromSizeB/2; iIter++ ) {
			    
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
            }//if ( pbWriteEEPROM == true ) {

            
            //--------------------------------------------------------------------------
			// Write Config Bits
			//--------------------------------------------------------------------------
            if ( pbWriteConfigs == true ) {
                int iConfig;
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing configs...", iTabLevel) );
				iRetries = 0;
				
				for ( iConfig = 0; iConfig < clsHex18F.iConfigWordsUsedBufferSize; iConfig++ ) {
					if ( pobjHex.bConfigWordUsed[iConfig] == true ) {
                        iRetries = 0;
						do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing config byte " + iConfig.ToString(), iTabLevel) );
                            }

						    iBufferIndx = 0;
						    iSum = 0;						
						
						    // Calculate
						    iAddrP = 0x300000 + iConfig;               				//24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
						    bSize = Convert.ToByte( 1 + 1/*checksum*/ );
							
						    //
						    bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
						    bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
						    bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
						    bBuffer[ iBufferIndx++ ] = cCmdWriteConfig;iSum += cCmdWriteConfig;
						    bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;	
		                    
						    // Buffer config word
						    bProg = Convert.ToByte( pobjHex.iConfigMem[ iConfig ] );
						    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;	
							
						    // Calculate checksum and add to buffer
						    iSum %= 256;
						    iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
						    bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
							
						    // Send row+checksum
						    pobjPort.SendBytes( ref bBuffer, iBufferIndx );
		                    
						    // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }

                            Application.DoEvents();
						} while ( bRetry == true && bAbort == false );
		                
						//
						if ( bAbort == true ) {
							OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
							return false;
						}
						
                        //
						iBytesWritten += 1;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
					}//if ( bConfigUsed[iIter] == true ) {
					
				}//for ( iIter = 0;  iIter < iConfigUsedBufferSize; iIter++ ) { 
				
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );				
			}//if ( bWriteConfigs == true )


            //--------------------------------------------------------------------------
            // Write completed
            //--------------------------------------------------------------------------
            return true;
        }// WriteFlash18F_0_9_0()


        //---------------------------------------------------------------------
        // WriteFlash18FJ_0_9_0()
        //---------------------------------------------------------------------
        static private bool WriteFlash18FJ_0_9_0(clsSerialPort pobjPort, clsDevice pobjDevice, clsHex18FJ pobjHex, bool pbWriteProgram, int iTabLevel)
        {
            //--------------------------------------------------------------------------
            // Variables
            //--------------------------------------------------------------------------
            int iChecksum;
            int iSum;
            int iAddrP;
            int iRetries;
            byte[] bBuffer = new byte[256];
            int iBufferIndx;
            byte bAddrU, bAddrH, bAddrL, bSize, bProg;
            bool bRetry = false;
            int iByteToWrite = pobjHex.BytesToWrite( pobjDevice, pbWriteProgram, false, false );
            int iBytesWritten = 0;
            bool bProcessWriteResponseResult = false;


            //--------------------------------------------------------------------------
            // Write flash
            //--------------------------------------------------------------------------
            int iRow;

            if ( pbWriteProgram == true ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing flash...", iTabLevel) );
                

                //-------------------------------------------------------------
                // Iterate pages
                //-------------------------------------------------------------
                for ( int iPage = 0; iPage < clsHex18FJ.iProgPageUsedBufferSize; iPage++ ) {
                    if ( pobjHex.bProgPageUsed[iPage] == true ) {
                        iRetries = 0;
                        do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Erasing page " + iPage.ToString(), iTabLevel) );
                            }

                            //---------------------------------------------------------
                            // Erase page
                            //---------------------------------------------------------
                            iSum = 0;
                            iBufferIndx = 0;

                            // Calculate
                            iAddrP = iPage * pobjDevice.pageSizeR * pobjDevice.rowsizeW * 2;	//24-bit address in memory to write to
                            bAddrU = Convert.ToByte((iAddrP & 0xff0000) >> 16);				//address upper byte			               
                            bAddrH = Convert.ToByte((iAddrP & 0x00ff00) >> 8);				//address high byte
                            bAddrL = Convert.ToByte((iAddrP & 0x0000ff) >> 0);				//address low byte
                            bSize = Convert.ToByte(1/*checksum*/ );

                            //
                            bBuffer[iBufferIndx++] = bAddrU; iSum += bAddrU;
                            bBuffer[iBufferIndx++] = bAddrH; iSum += bAddrH;
                            bBuffer[iBufferIndx++] = bAddrL; iSum += bAddrL;
                            bBuffer[iBufferIndx++] = cCmdErasePage; iSum += cCmdErasePage;
                            bBuffer[iBufferIndx++] = bSize; iSum += bSize;

                            // Calculate checksum and add to buffer
                            iSum %= 256;
                            iChecksum = Convert.ToInt16((256 - iSum) % 256);
                            bBuffer[iBufferIndx++] = Convert.ToByte(iChecksum);

                            // Send address, command, packetsize & checksum
                            pobjPort.SendBytes(ref bBuffer, iBufferIndx);

                            // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }

                            //
                            Application.DoEvents();
                        } while ( bRetry == true && bAbort == false );


                        //---------------------------------------------------------
                        // Iterate rows, write all rows in page even if not in hex-file
                        //---------------------------------------------------------
                        for ( iRow = iPage * pobjDevice.pageSizeR; iRow < iPage * pobjDevice.pageSizeR + pobjDevice.pageSizeR; iRow++ ) {
                            iRetries = 0;
                            do {
                                if ( clsds30Loader.debugMode ) {
                                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing row " + iRow.ToString(), iTabLevel) );
                                }

                                iBufferIndx = 0;
                                iSum = 0;

                                // Calculate
                                iAddrP = 2 * iRow * pobjDevice.rowsizeW;				//24-bit address in memory to write to
                                bAddrU = Convert.ToByte((iAddrP & 0xff0000) >> 16);	    //address upper byte			               
                                bAddrH = Convert.ToByte((iAddrP & 0x00ff00) >> 8);	    //address high byte
                                bAddrL = Convert.ToByte((iAddrP & 0x0000ff));			//address low byte
                                bSize = Convert.ToByte(pobjDevice.rowsizeW * 2 + 1/*checksum*/ );

                                //
                                bBuffer[iBufferIndx++] = bAddrU; iSum += bAddrU;
                                bBuffer[iBufferIndx++] = bAddrH; iSum += bAddrH;
                                bBuffer[iBufferIndx++] = bAddrL; iSum += bAddrL;
                                bBuffer[iBufferIndx++] = cCmdWriteRow; iSum += cCmdWriteRow;
                                bBuffer[iBufferIndx++] = bSize; iSum += bSize;

						        // Buffer row
						        for ( int iByte = 0; iByte < pobjDevice.rowsizeW * 2; iByte++ ) {
								    bProg = Convert.ToByte( pobjHex.iProgMem[iAddrP + iByte] );
							        bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
						        }

                                // Calculate checksum and add to buffer
                                iSum %= 256;
                                iChecksum = Convert.ToInt16((256 - iSum) % 256);
                                bBuffer[iBufferIndx++] = Convert.ToByte(iChecksum);

                                // Send address, command, packetsize, row & checksum
                                pobjPort.SendBytes( ref bBuffer, iBufferIndx );

                                // Get response, checksum ok
                                ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                                if ( bProcessWriteResponseResult == false ) {
                                    return false;
                                }

                                //
                                Application.DoEvents();
                            } while ( bRetry == true && bAbort == false );

                            //
                            if (bAbort == true) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
                                return false;
                            }

                            //
                            iBytesWritten += pobjDevice.rowsizeW * 2;
                            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );

                        }//for ( iRow = 0; iRow < iRowUsedBufferSize; iRow++ ) {

                    } //if ( bPageUsed[iIter] == true ) {

                }//for ( iPage = 0; iPage < iPageUsedBufferSize; iPage++ ) {

                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
            }//if ( pbWriteProgram == true ) {


            //--------------------------------------------------------------------------
            // Write completed
            //--------------------------------------------------------------------------
            return true;
        }// WriteFlash18FJ_0_9_0()


        //---------------------------------------------------------------------
        // WriteFlash24F_0_9_0()
        //---------------------------------------------------------------------
        static private bool WriteFlash24F_0_9_0(clsSerialPort pobjPort, clsDevice pobjDevice, clsHex24F pobjHex, bool pbWriteProgram, bool pbWriteEEPROM, bool pbWriteConfigs, int iTabLevel)
        {
            //--------------------------------------------------------------------------
			// Variables
			//--------------------------------------------------------------------------
			int iIter2;
			int iChecksum;
			int iSum;
			int iAddrP;
			int iRetries;
			byte [] bBuffer = new byte [256];
			int iBufferIndx;
			byte bAddrU, bAddrH, bAddrL, bSize, bProg;		
            bool bRetry = false;
            int iByteToWrite = pobjHex.BytesToWrite( pobjDevice, pbWriteProgram, pbWriteEEPROM, pbWriteConfigs );
            int iBytesWritten = 0;	
			bool bProcessWriteResponseResult = false;
		

			//--------------------------------------------------------------------------
			// Write flash
			//--------------------------------------------------------------------------
			if ( pbWriteProgram == true ) {
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing flash...", iTabLevel) );
				
				
				//-------------------------------------------------------------
				// Iterate rows
				//-------------------------------------------------------------
				for ( int iRow = 0; iRow < clsHex24F.iProgRowUsedBufferSize; iRow++ ) {
                    if ( pobjHex.bProgRowUsed[iRow] == true ) {
                        iRetries = 0;
					    do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing row " + iRow.ToString(), iTabLevel) );
                            }

						    iBufferIndx = 0;
						    iSum = 0;                                
			                
						    // Calculate
						    iAddrP = iRow * (pobjDevice.rowsizeW * 2);				//24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
						    bSize = Convert.ToByte( pobjDevice.rowsizeW * 3 + 1/*checksum*/ );
							
						    //
						    bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
						    bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
						    bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
						    bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;
							
						    // Calculate startindex in hex-buffer
						    iAddrP = iRow * pobjDevice.rowsizeW * 3;	
											
						    // Buffer row, upper-low-high, ordered in ParseHex()
						    for ( int iByte = 0; iByte < pobjDevice.rowsizeW*3; iByte++ ) {
								bProg = Convert.ToByte( pobjHex.iProgMem[iAddrP + iByte] );
							    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
						    }				    
		                
						    // Calculate checksum and add to buffer
						    iSum %= 256;
						    iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
						    bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
							
						    // Send address, command, packetsize, row & checksum
						    pobjPort.SendBytes( ref bBuffer, iBufferIndx );
			                
						    // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }
			                
						    //
						    Application.DoEvents();
					    } while ( bRetry == true && bAbort == false );
				            
					    //
					    if ( bAbort == true ) {
						    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
						    return false;
					    }
			            
					    //
					    iBytesWritten += pobjDevice.rowsizeW * 3;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
                        
				
				    } //if ( bProgRowUsed[iIter] == true ) {
                }//for ( iRow = 0; iRow < iProgRowUsedBufferSize; iRow++ ) {
									
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
			}//if ( pbWriteProgram == true ) {


		    //--------------------------------------------------------------------------
            // Write EEPROM
            //--------------------------------------------------------------------------
            if ( pbWriteEEPROM == true ) {
			    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing eeprom...", iTabLevel) );
				
			    for ( int iEEPROMWord = 0; iEEPROMWord < pobjDevice.eepromSizeB/2; iEEPROMWord++ ) {					
				    if (  pobjHex.bEEWordUsed[iEEPROMWord] == true ) {
						iRetries = 0;
						
					    do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing eeprom word " + iEEPROMWord.ToString(), iTabLevel) );
                            }

						    iBufferIndx = 0;
						    iSum = 0;
    		                
		                    // Calculate
		                    iAddrP = pobjDevice.eepromStartAddress + iEEPROMWord * 2;		//24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
						    bSize = Convert.ToByte( 2 + 1/*checksum*/ );
    						
						    //
						    bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
						    bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
						    bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
						    bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;

							// Low byte
						    bProg = Convert.ToByte( pobjHex.iEEMem[iEEPROMWord*2 + 0] );
						    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
							
							// High byte								    
						    bProg = Convert.ToByte( pobjHex.iEEMem[iEEPROMWord*2 + 1] );
						    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
    		                
						    // Calculate checksum and add to buffer
						    iSum %= 256;
						    iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
						    bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
    						
						    // Send row+checksum
						    pobjPort.SendBytes( ref bBuffer, iBufferIndx );
    		                
		                    // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }
    		                
		                    //
						    Application.DoEvents();
					    } while ( bRetry == true && bAbort == false );
    		            
		                //
					    if ( bAbort == true ) {
						    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
						    return false;
					    }
    		            
    		            //
					    iBytesWritten += 2;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
				     }//if (  bEEWordUsed[iEEPROMWord] == true ) {				     
				     
			    }//for ( iIter = 0; iIter < pobjDevice.eepromSizeB/2; iIter++ ) {
			    
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
            }//if ( pbWriteEEPROM == true ) {


			//--------------------------------------------------------------------------
			// Write Config Bits
			//--------------------------------------------------------------------------
			if ( pbWriteConfigs == true ) {
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing configs...", iTabLevel) );
								
				for ( int iConfig = 0;  iConfig < clsHex24F.iConfigWordsUsedBufferSize; iConfig++ ) {
					if ( pobjHex.bConfigWordUsed[iConfig] == true ) {
						iRetries = 0;
						
						do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing config word " + iConfig.ToString(), iTabLevel) );
                            }

							iBufferIndx = 0;
							iSum = 0;						
						
							// Calculate
							iAddrP = 0xF80000 + iConfig * 2;						//24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
							bSize = Convert.ToByte( 2 + 1/*checksum*/ );
							
							//
							bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
							bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
							bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
							bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;	
		                    
							// Buffer config word
							for ( iIter2 = 0; iIter2 < 2; iIter2++ ) {
								bProg = Convert.ToByte( pobjHex.iConfigMem[ iConfig * 2 + iIter2 ] );
								bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;	
							}
							
							// Calculate checksum and add to buffer
							iSum %= 256;
							iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
							bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
							
							// Send row+checksum
							pobjPort.SendBytes( ref bBuffer, iBufferIndx );
		                    
							// Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }

                            //
                            Application.DoEvents();
						} while ( bRetry == true && bAbort == false );
		                
						//
						if ( bAbort == true ) {
							OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
							return false;
						}
						
                        //
						iBytesWritten += 2;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
					}//if ( bConfigWordUsed[iIter] == true ) {
					
				}//for ( iIter = 0;  iIter < iConfigUsedBufferSize; iIter++ ) { 
				
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );				
			}//if ( bWriteConfigs == true )

		    
			//--------------------------------------------------------------------------
			// Write completed
			//--------------------------------------------------------------------------
			return true;
        }// WriteFlash24F_0_9_0()


        //---------------------------------------------------------------------
        // WriteFlash24FJ_1_0_0()
        //---------------------------------------------------------------------
        static private bool WriteFlash24FJ_1_0_0(clsSerialPort pobjPort, clsDevice pobjDevice, clsHex24FJ pobjHex, bool pbWriteProgram, bool pbWriteEEPROM, bool pbWriteConfigs, int iTabLevel)
        {
            //--------------------------------------------------------------------------
            // Variables
            //--------------------------------------------------------------------------
            int iChecksum;
            int iSum;
            int iAddrP;
            int iRetries;
            byte[] bBuffer = new byte[256];
            int iBufferIndx;
            byte bAddrU, bAddrH, bAddrL, bSize, bProg;
            bool bRetry = false;
            int iByteToWrite = pobjHex.BytesToWrite( pobjDevice, pbWriteProgram, pbWriteEEPROM, pbWriteConfigs );
            int iBytesWritten = 0;
            bool bProcessWriteResponseResult = false;


            //--------------------------------------------------------------------------
            // Write flash
            //--------------------------------------------------------------------------
            int iRow;

            if ( pbWriteProgram == true ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing flash...", iTabLevel) );
                

                //-------------------------------------------------------------
                // Iterate pages
                //-------------------------------------------------------------
                for ( int iPage = 0; iPage < clsHex24FJ.iProgPageUsedBufferSize; iPage++ ) {
                    if ( pobjHex.bProgPageUsed[iPage] == true ) {
                        iRetries = 0;
                        do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Erasing page " + iPage.ToString(), iTabLevel) );
                            }

                            //---------------------------------------------------------
                            // Erase page
                            //---------------------------------------------------------
                            iSum = 0;
                            iBufferIndx = 0;

                            // Calculate
                            iAddrP = iPage * pobjDevice.pageSizeR * pobjDevice.rowsizeW * 2;	//24-bit address in memory to write to
                            bAddrU = Convert.ToByte((iAddrP & 0xff0000) >> 16);				//address upper byte			               
                            bAddrH = Convert.ToByte((iAddrP & 0x00ff00) >> 8);				//address high byte
                            bAddrL = Convert.ToByte((iAddrP & 0x0000ff) >> 0);				//address low byte
                            bSize = Convert.ToByte(1/*checksum*/ );

                            //
                            bBuffer[iBufferIndx++] = bAddrU; iSum += bAddrU;
                            bBuffer[iBufferIndx++] = bAddrH; iSum += bAddrH;
                            bBuffer[iBufferIndx++] = bAddrL; iSum += bAddrL;
                            bBuffer[iBufferIndx++] = cCmdErasePage; iSum += cCmdErasePage;
                            bBuffer[iBufferIndx++] = bSize; iSum += bSize;

                            // Calculate checksum and add to buffer
                            iSum %= 256;
                            iChecksum = Convert.ToInt16((256 - iSum) % 256);
                            bBuffer[iBufferIndx++] = Convert.ToByte(iChecksum);

                            // Send address, command, packetsize & checksum
                            pobjPort.SendBytes(ref bBuffer, iBufferIndx);

                            // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }

                            //
                            Application.DoEvents();
                        } while ( bRetry == true && bAbort == false );


                        //---------------------------------------------------------
                        // Iterate rows, write all rows in page even if not in hex-file
                        //---------------------------------------------------------
                        for ( iRow = iPage * pobjDevice.pageSizeR; iRow < iPage * pobjDevice.pageSizeR + pobjDevice.pageSizeR; iRow++ ) {
                            iRetries = 0;
                            do {
                                if ( clsds30Loader.debugMode ) {
                                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing row " + iRow.ToString(), iTabLevel) );
                                }

                                iBufferIndx = 0;
                                iSum = 0;

                                // Calculate
                                iAddrP = iRow * (pobjDevice.rowsizeW * 2);				//24-bit address in memory to write to
                                bAddrU = Convert.ToByte((iAddrP & 0xff0000) >> 16);	    //address upper byte			               
                                bAddrH = Convert.ToByte((iAddrP & 0x00ff00) >> 8);	    //address high byte
                                bAddrL = Convert.ToByte((iAddrP & 0x0000ff));			//address low byte
                                bSize = Convert.ToByte(pobjDevice.rowsizeW * 3 + 1/*checksum*/ );

                                //
                                bBuffer[iBufferIndx++] = bAddrU; iSum += bAddrU;
                                bBuffer[iBufferIndx++] = bAddrH; iSum += bAddrH;
                                bBuffer[iBufferIndx++] = bAddrL; iSum += bAddrL;
                                bBuffer[iBufferIndx++] = cCmdWriteRow; iSum += cCmdWriteRow;
                                bBuffer[iBufferIndx++] = bSize; iSum += bSize;

                                // Calculate startindex in hex-buffer
                                iAddrP = iRow * pobjDevice.rowsizeW * 3;

						        // Buffer row, upper-low-high, ordered in ParseHex()
						        for ( int iByte = 0; iByte < pobjDevice.rowsizeW * 3; iByte++ ) {
								    bProg = Convert.ToByte( pobjHex.iProgMem[iAddrP + iByte] );
							        bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
						        }

                                // Calculate checksum and add to buffer
                                iSum %= 256;
                                iChecksum = Convert.ToInt16((256 - iSum) % 256);
                                bBuffer[iBufferIndx++] = Convert.ToByte(iChecksum);

                                // Send address, command, packetsize, row & checksum
                                pobjPort.SendBytes(ref bBuffer, iBufferIndx);

                                // Get response, checksum ok
                                ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                                if ( bProcessWriteResponseResult == false ) {
                                    return false;
                                }  

                                //
                                Application.DoEvents();
                            } while ( bRetry == true && bAbort == false );

                            //
                            if (bAbort == true) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
                                return false;
                            }

                            //
                            iBytesWritten += pobjDevice.rowsizeW * 3;
                            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );

                        }//for ( iRow = 0; iRow < iRowUsedBufferSize; iRow++ ) {

                    } //if ( bPageUsed[iIter] == true ) {

                }//for ( iPage = 0; iPage < iPageUsedBufferSize; iPage++ ) {

                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
            }//if ( pbWriteProgram == true ) {


            //--------------------------------------------------------------------------
            // Write completed
            //--------------------------------------------------------------------------
            return true;
        }// WriteFlash24FJ_1_0_0()


        //---------------------------------------------------------------------
        // WriteFlash24H_0_9_0()
        //---------------------------------------------------------------------
        static private bool WriteFlash24H_0_9_0(clsSerialPort pobjPort, clsDevice pobjDevice, clsHex24H pobjHex, bool pbWriteProgram, bool pbWriteConfigs, int iTabLevel)
        {
            //--------------------------------------------------------------------------
            // Variables
            //--------------------------------------------------------------------------
            int iChecksum;
            int iSum;
            int iAddrP;
            int iRetries;
            byte[] bBuffer = new byte[256];
            int iBufferIndx;
            byte bAddrU, bAddrH, bAddrL, bSize, bProg;
            bool bRetry = false;
            int iByteToWrite = pobjHex.BytesToWrite( pobjDevice, pbWriteProgram, false, pbWriteConfigs );
            int iBytesWritten = 0;
            bool bProcessWriteResponseResult = false;


            //--------------------------------------------------------------------------
            // Write flash
            //--------------------------------------------------------------------------
            int iRow;

            if ( pbWriteProgram == true ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing flash...", iTabLevel) );
                

                //-------------------------------------------------------------
                // Iterate pages
                //-------------------------------------------------------------
                for ( int iPage = 0; iPage < clsHex24H.iProgPageUsedBufferSize; iPage++ ) {
                    if ( pobjHex.bProgPageUsed[iPage] == true ) {
                        iRetries = 0;
                        do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Erasing page " + iPage.ToString(), iTabLevel) );
                            }

                            //---------------------------------------------------------
                            // Erase page
                            //---------------------------------------------------------
                            iSum = 0;
                            iBufferIndx = 0;

                            // Calculate
                            iAddrP = iPage * pobjDevice.pageSizeR * pobjDevice.rowsizeW * 2;	//24-bit address in memory to write to
                            bAddrU = Convert.ToByte((iAddrP & 0xff0000) >> 16);				//address upper byte			               
                            bAddrH = Convert.ToByte((iAddrP & 0x00ff00) >> 8);				//address high byte
                            bAddrL = Convert.ToByte((iAddrP & 0x0000ff) >> 0);				//address low byte
                            bSize = Convert.ToByte(1/*checksum*/ );

                            //
                            bBuffer[iBufferIndx++] = bAddrU; iSum += bAddrU;
                            bBuffer[iBufferIndx++] = bAddrH; iSum += bAddrH;
                            bBuffer[iBufferIndx++] = bAddrL; iSum += bAddrL;
                            bBuffer[iBufferIndx++] = cCmdErasePage; iSum += cCmdErasePage;
                            bBuffer[iBufferIndx++] = bSize; iSum += bSize;

                            // Calculate checksum and add to buffer
                            iSum %= 256;
                            iChecksum = Convert.ToInt16((256 - iSum) % 256);
                            bBuffer[iBufferIndx++] = Convert.ToByte(iChecksum);

                            // Send address, command, packetsize & checksum
                            pobjPort.SendBytes(ref bBuffer, iBufferIndx);

                            // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }

                            //
                            Application.DoEvents();
                        } while ( bRetry == true && bAbort == false );


                        //---------------------------------------------------------
                        // Iterate rows, write all rows in page even if not in hex-file
                        //---------------------------------------------------------
                        for ( iRow = iPage * pobjDevice.pageSizeR; iRow < iPage * pobjDevice.pageSizeR + pobjDevice.pageSizeR; iRow++ ) {
                            iRetries = 0;
                            do {
                                if ( clsds30Loader.debugMode ) {
                                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing row " + iRow.ToString(), iTabLevel) );
                                }

                                iBufferIndx = 0;
                                iSum = 0;

                                // Calculate
                                iAddrP = iRow * (pobjDevice.rowsizeW * 2);				//24-bit address in memory to write to
                                bAddrU = Convert.ToByte((iAddrP & 0xff0000) >> 16);	    //address upper byte			               
                                bAddrH = Convert.ToByte((iAddrP & 0x00ff00) >> 8);	    //address high byte
                                bAddrL = Convert.ToByte((iAddrP & 0x0000ff));			//address low byte
                                bSize = Convert.ToByte(pobjDevice.rowsizeW * 3 + 1/*checksum*/ );

                                //
                                bBuffer[iBufferIndx++] = bAddrU; iSum += bAddrU;
                                bBuffer[iBufferIndx++] = bAddrH; iSum += bAddrH;
                                bBuffer[iBufferIndx++] = bAddrL; iSum += bAddrL;
                                bBuffer[iBufferIndx++] = cCmdWriteRow; iSum += cCmdWriteRow;
                                bBuffer[iBufferIndx++] = bSize; iSum += bSize;

                                // Calculate startindex in hex-buffer
                                iAddrP = iRow * pobjDevice.rowsizeW * 3;

						        // Buffer row, upper-low-high, ordered in ParseHex()
						        for ( int iByte = 0; iByte < pobjDevice.rowsizeW * 3; iByte++ ) {
								    bProg = Convert.ToByte( pobjHex.iProgMem[iAddrP + iByte] );
							        bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
						        }

                                // Calculate checksum and add to buffer
                                iSum %= 256;
                                iChecksum = Convert.ToInt16((256 - iSum) % 256);
                                bBuffer[iBufferIndx++] = Convert.ToByte(iChecksum);

                                // Send address, command, packetsize, row & checksum
                                pobjPort.SendBytes(ref bBuffer, iBufferIndx);

                                // Get response, checksum ok
                                ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                                if ( bProcessWriteResponseResult == false ) {
                                    return false;
                                }  

                                //
                                Application.DoEvents();
                            } while ( bRetry == true && bAbort == false );

                            //
                            if (bAbort == true) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
                                return false;
                            }

                            //
                            iBytesWritten += pobjDevice.rowsizeW * 3;
                            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );

                        }//for ( iRow = 0; iRow < iRowUsedBufferSize; iRow++ ) {

                    } //if ( bPageUsed[iIter] == true ) {

                }//for ( iPage = 0; iPage < iPageUsedBufferSize; iPage++ ) {

                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
            }//if ( pbWriteProgram == true ) {

            
            //--------------------------------------------------------------------------
			// Write Config Bits
			//--------------------------------------------------------------------------
            if ( pbWriteConfigs == true ) {
                int iConfig;
                int iByte;
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing configs...", iTabLevel) );
				iRetries = 0;
				
				for ( iConfig = 0; iConfig < clsHex24H.iConfigWordsUsedBufferSize; iConfig++ ) {
					if ( pobjHex.bConfigWordUsed[iConfig] == true ) {
                        iRetries = 0;
						do {
                            for ( iByte = 0; iByte < 2; iByte++ ) {
                                if ( clsds30Loader.debugMode ) {
                                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing config byte " + (iConfig*2 + iByte).ToString(), iTabLevel) );
                                }

							    iBufferIndx = 0;
							    iSum = 0;						
    						
							    // Calculate
							    iAddrP = 0xF80000 + iConfig * 2 + iByte;				//24-bit address in memory to write to
							    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
							    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
							    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
							    bSize = Convert.ToByte( 1 + 1/*checksum*/ );
    							
							    //
							    bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
							    bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
							    bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
							    bBuffer[ iBufferIndx++ ] = cCmdWriteConfig;iSum += cCmdWriteConfig;
							    bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;	
    		                    
							    // Buffer config word
							    bProg = Convert.ToByte( pobjHex.iConfigMem[ iConfig * 2 + iByte ] );
							    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;	
    							
							    // Calculate checksum and add to buffer
							    iSum %= 256;
							    iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
							    bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
    							
							    // Send row+checksum
							    pobjPort.SendBytes( ref bBuffer, iBufferIndx );
    		                    
							    // Get response, checksum ok
                                ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                                if ( bProcessWriteResponseResult == false ) {
                                    return false;
                                }
                            }
                            Application.DoEvents();
						} while ( bRetry == true && bAbort == false );
		                
						//
						if ( bAbort == true ) {
							OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
							return false;
						}
						
                        //
						iBytesWritten += 2;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
					}//if ( bConfigUsed[iIter] == true ) {
					
				}//for ( iIter = 0;  iIter < iConfigUsedBufferSize; iIter++ ) { 
				
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );				
			}//if ( bWriteConfigs == true )


            //--------------------------------------------------------------------------
            // Write completed
            //--------------------------------------------------------------------------
            return true;
        }// WriteFlash24H_0_9_0()

        
        //---------------------------------------------------------------------
		// WriteFlash30_1_0_1()
		//---------------------------------------------------------------------
		static private bool WriteFlash30_1_0_1( clsSerialPort pobjPort, clsDevice pobjDevice, clsHex30F pobjHex, bool pbWriteProgram, bool pbWriteEEPROM, bool pbWriteConfigs, int iTabLevel )
		{
			//--------------------------------------------------------------------------
			// Variables
			//--------------------------------------------------------------------------
			int iIter2;
			int iChecksum;
			int iSum;
			int iAddrP;
			int iRetries;
			byte [] bBuffer = new byte [256];
			int iBufferIndx;
			byte bAddrU, bAddrH, bAddrL, bSize, bProg;			
            bool bRetry = false;
            int iByteToWrite = pobjHex.BytesToWrite( pobjDevice, pbWriteProgram, pbWriteEEPROM, pbWriteConfigs );
            int iBytesWritten = 0;
			bool bProcessWriteResponseResult = false;
		

			//--------------------------------------------------------------------------
			// Write flash
			//--------------------------------------------------------------------------
			if ( pbWriteProgram == true ) {
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing flash...", iTabLevel) );
				
				
				//-------------------------------------------------------------
				// Iterate rows
				//-------------------------------------------------------------
				for ( int iRow = 0; iRow < clsHex30F.iProgRowsUsedBufferSize; iRow++ ) {
                    if ( pobjHex.bProgRowUsed[iRow] == true ) {
                        iRetries = 0;
					    do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing row " + iRow.ToString(), iTabLevel) );
                            }

						    iBufferIndx = 0;
						    iSum = 0;                                
			                
						    // Calculate
						    iAddrP = iRow * (pobjDevice.rowsizeW * 2);				//24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
						    bSize = Convert.ToByte( pobjDevice.rowsizeW * 3 + 1/*checksum*/ );
							
						    //
						    bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
						    bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
						    bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
						    bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;
							
						    // Calculate startindex in hex-buffer
						    iAddrP = iRow * pobjDevice.rowsizeW * 3;	
											
						    // Buffer row, upper-low-high, ordered in ParseHex()
						    for ( int iByte = 0; iByte < pobjDevice.rowsizeW*3; iByte++ ) {
								bProg = Convert.ToByte( pobjHex.iProgMem[iAddrP + iByte] );
							    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
						    }				    
		                
						    // Calculate checksum and add to buffer
						    iSum %= 256;
						    iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
						    bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
							
						    // Send address, command, packetsize, row & checksum
						    pobjPort.SendBytes( ref bBuffer, iBufferIndx );
			                
						    // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }
			                
						    //
						    Application.DoEvents();
					    } while ( bRetry == true && bAbort == false );
				            
					    //
					    if ( bAbort == true ) {
						    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
						    return false;
					    }
			            
					    //
					    iBytesWritten += pobjDevice.rowsizeW * 3;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
				
				    } //if ( bProgRowUsed[iIter] == true ) {
                }//for ( iRow = 0; iRow < iProgRowUsedBufferSize; iRow++ ) {
									
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
			}//if ( pbWriteProgram == true ) {


		    //--------------------------------------------------------------------------
            // Write EEPROM
            //--------------------------------------------------------------------------
            if ( pbWriteEEPROM == true ) {
			    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing eeprom...", iTabLevel) );
				
			    for ( int iEEPROMWord = 0; iEEPROMWord < pobjDevice.eepromSizeB/2; iEEPROMWord++ ) {					
				    if (  pobjHex.bEEWordUsed[iEEPROMWord] == true ) {
						iRetries = 0;
						
					    do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing eeprom word " + iEEPROMWord.ToString(), iTabLevel) );
                            }

						    iBufferIndx = 0;
						    iSum = 0;
    		                
		                    // Calculate
		                    iAddrP = pobjDevice.eepromStartAddress + iEEPROMWord * 2;		//24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
						    bSize = Convert.ToByte( 2 + 1/*checksum*/ );
    						
						    //
						    bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
						    bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
						    bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
						    bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;

							// Low byte
						    bProg = Convert.ToByte( pobjHex.iEEMem[iEEPROMWord*2 + 0] );
						    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
							
							// High byte								    
						    bProg = Convert.ToByte( pobjHex.iEEMem[iEEPROMWord*2 + 1] );
						    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
    		                
						    // Calculate checksum and add to buffer
						    iSum %= 256;
						    iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
						    bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
    						
						    // Send row+checksum
						    pobjPort.SendBytes( ref bBuffer, iBufferIndx );
    		                
		                    // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }
    		                
		                    //
						    Application.DoEvents();
					    } while ( bRetry == true && bAbort == false );
    		            
		                //
					    if ( bAbort == true ) {
						    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
						    return false;
					    }
    		            
    		            //
					    iBytesWritten += 2;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
				     }//if (  bEEWordUsed[iEEPROMWord] == true ) {				     
				     
			    }//for ( iIter = 0; iIter < pobjDevice.eepromSizeB/2; iIter++ ) {
			    
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
            }//if ( pbWriteEEPROM == true ) {


			//--------------------------------------------------------------------------
			// Write Config Bits
			//--------------------------------------------------------------------------
			if ( pbWriteConfigs == true ) {
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing configs...", iTabLevel) );
								
				for ( int iConfig = 0;  iConfig < clsHex30F.iConfigWordsUsedBufferSize; iConfig++ ) {
					if ( pobjHex.bConfigWordUsed[iConfig] == true ) {
						iRetries = 0;
						
						do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing config word " + iConfig.ToString(), iTabLevel) );
                            }

							iBufferIndx = 0;
							iSum = 0;						
						
							// Calculate
							iAddrP = 0xF80000 + iConfig * 2;						//24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
							bSize = Convert.ToByte( 2 + 1/*checksum*/ );
							
							//
							bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
							bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
							bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
							bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;	
		                    
							// Buffer config word
							for ( iIter2 = 0; iIter2 < 2; iIter2++ ) {
								bProg = Convert.ToByte( pobjHex.iConfigMem[ iConfig * 2 + iIter2 ] );
								bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;	
							}
							
							// Calculate checksum and add to buffer
							iSum %= 256;
							iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
							bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
							
							// Send row+checksum
							pobjPort.SendBytes( ref bBuffer, iBufferIndx );
		                    
							// Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }

                            //
                            Application.DoEvents();
						} while ( bRetry == true && bAbort == false );
		                
						//
						if ( bAbort == true ) {
							OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
							return false;
						}
						
                        //
						iBytesWritten += 2;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
					}//if ( bConfigWordUsed[iIter] == true ) {
					
				}//for ( iIter = 0;  iIter < iConfigUsedBufferSize; iIter++ ) { 
				
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );				
			}//if ( bWriteConfigs == true )

		    
			//--------------------------------------------------------------------------
			// Write completed
			//--------------------------------------------------------------------------
			return true;
		}// WriteFlash30_1_0_1()


		//---------------------------------------------------------------------
		// WriteFlash30_2_0_0()
		//---------------------------------------------------------------------
		static private bool WriteFlash30_2_0_0( clsSerialPort pobjPort, clsDevice pobjDevice, clsHex30F pobjHex, bool pbWriteProgram, bool pbWriteEEPROM, bool pbWriteConfigs, int iTabLevel )
		{
			//--------------------------------------------------------------------------
			// Variables
			//--------------------------------------------------------------------------
			int iIter2;
			int iChecksum;
			int iSum;
			int iAddrP;
			int iRetries;
			byte [] bBuffer = new byte [256];
			int iBufferIndx;
			byte bAddrU, bAddrH, bAddrL, bSize, bProg;			
            bool bRetry = false;
            int iByteToWrite = pobjHex.BytesToWrite( pobjDevice, pbWriteProgram, pbWriteEEPROM, pbWriteConfigs );
            int iBytesWritten = 0;
			bool bProcessWriteResponseResult = false;
		

			//--------------------------------------------------------------------------
			// Write flash
			//--------------------------------------------------------------------------
			if ( pbWriteProgram == true ) {
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing flash...", iTabLevel) );
				
				
				//-------------------------------------------------------------
				// Iterate rows
				//-------------------------------------------------------------
				for ( int iRow = 0; iRow < clsHex30F.iProgRowsUsedBufferSize; iRow++ ) {
                    if ( pobjHex.bProgRowUsed[iRow] == true ) {
                        iRetries = 0;
					    do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing row " + iRow.ToString(), iTabLevel) );
                            }

						    iBufferIndx = 0;
						    iSum = 0;                                
			                
						    // Calculate
						    iAddrP = iRow * (pobjDevice.rowsizeW * 2);				//24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
						    bSize = Convert.ToByte( pobjDevice.rowsizeW * 3 + 1/*checksum*/ );
							
						    //
						    bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
						    bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
						    bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
                            bBuffer[ iBufferIndx++ ] = cCmdWriteRow; iSum += cCmdWriteRow;
						    bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;
							
						    // Calculate startindex in hex-buffer
						    iAddrP = iRow * pobjDevice.rowsizeW * 3;	
											
						    // Buffer row, upper-low-high, ordered in ParseHex()
						    for ( int iByte = 0; iByte < pobjDevice.rowsizeW*3; iByte++ ) {
								bProg = Convert.ToByte( pobjHex.iProgMem[iAddrP + iByte] );
							    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
						    }				    
		                
						    // Calculate checksum and add to buffer
						    iSum %= 256;
						    iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
						    bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
							
						    // Send address, command, packetsize, row & checksum
						    pobjPort.SendBytes( ref bBuffer, iBufferIndx );
			                
						    // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }
			                
						    //
						    Application.DoEvents();
					    } while ( bRetry == true && bAbort == false );
				            
					    //
					    if ( bAbort == true ) {
						    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
						    return false;
					    }
			            
					    //
					    iBytesWritten += pobjDevice.rowsizeW * 3;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
				
				    } //if ( bProgRowUsed[iIter] == true ) {
                }//for ( iRow = 0; iRow < iProgRowUsedBufferSize; iRow++ ) {
									
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
			}//if ( pbWriteProgram == true ) {


		    //--------------------------------------------------------------------------
            // Write EEPROM
            //--------------------------------------------------------------------------
            if ( pbWriteEEPROM == true ) {
			    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing eeprom...", iTabLevel) );
				
			    for ( int iEEPROMWord = 0; iEEPROMWord < pobjDevice.eepromSizeB/2; iEEPROMWord++ ) {					
				    if (  pobjHex.bEEWordUsed[iEEPROMWord] == true ) {
						iRetries = 0;
						
					    do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing eeprom word " + iEEPROMWord.ToString(), iTabLevel) );
                            }

						    iBufferIndx = 0;
						    iSum = 0;
    		                
		                    // Calculate
		                    iAddrP = pobjDevice.eepromStartAddress + iEEPROMWord * 2;		//24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
						    bSize = Convert.ToByte( 2 + 1/*checksum*/ );
    						
						    //
						    bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
						    bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
						    bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
                            bBuffer[ iBufferIndx++ ] = cCmdWriteEEWord; iSum += cCmdWriteEEWord;
						    bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;

							// Low byte
						    bProg = Convert.ToByte( pobjHex.iEEMem[iEEPROMWord*2 + 0] );
						    bBuffer[ iBufferIndx++ ] = bProg; iSum += bProg;
							
							// High byte								    
						    bProg = Convert.ToByte( pobjHex.iEEMem[iEEPROMWord*2 + 1] );
						    bBuffer[ iBufferIndx++ ] = bProg; iSum += bProg;
    		                
						    // Calculate checksum and add to buffer
						    iSum %= 256;
						    iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
						    bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
    						
						    // Send address, size, word and checksum
						    pobjPort.SendBytes( ref bBuffer, iBufferIndx );
    		                
		                    // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }
    		                
		                    //
						    Application.DoEvents();
					    } while ( bRetry == true && bAbort == false );
    		            
		                //
					    if ( bAbort == true ) {
						    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
						    return false;
					    }
    		            
    		            //
					    iBytesWritten += 2;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
				     }//if (  bEEWordUsed[iEEPROMWord] == true ) {				     
				     
			    }//for ( iIter = 0; iIter < pobjDevice.eepromSizeB/2; iIter++ ) {
			    
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
            }//if ( pbWriteEEPROM == true ) {


			//--------------------------------------------------------------------------
			// Write Config Bits
			//--------------------------------------------------------------------------
			if ( pbWriteConfigs == true ) {
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing configs...", iTabLevel) );
								
				for ( int iConfig = 0;  iConfig < clsHex30F.iConfigWordsUsedBufferSize; iConfig++ ) {
					if ( pobjHex.bConfigWordUsed[iConfig] == true ) {
						iRetries = 0;
						
						do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing config word " + iConfig.ToString(), iTabLevel) );
                            }

							iBufferIndx = 0;
							iSum = 0;						
						
							// Calculate
							iAddrP = 0xF80000 + iConfig * 2;						//24-bit address in memory to write to
						    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
						    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
						    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte                            
							bSize = Convert.ToByte( 2 + 1/*checksum*/ );
							
							//
							bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
							bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
							bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
                            bBuffer[ iBufferIndx++ ] = cCmdWriteConfig; iSum += cCmdWriteConfig;
							bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;	
		                    
							// Buffer config word
							for ( iIter2 = 0; iIter2 < 2; iIter2++ ) {
								bProg = Convert.ToByte( pobjHex.iConfigMem[ iConfig * 2 + iIter2 ] );
								bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;	
							}
							
							// Calculate checksum and add to buffer
							iSum %= 256;
							iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
							bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
							
							// Send row+checksum
							pobjPort.SendBytes( ref bBuffer, iBufferIndx );
		                    
							// Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }

                            //
                            Application.DoEvents();
						} while ( bRetry == true && bAbort == false );
		                
						//
						if ( bAbort == true ) {
							OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
							return false;
						}
						
                        //
						iBytesWritten += 2;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
					}//if ( bConfigWordUsed[iIter] == true ) {
					
				}//for ( iIter = 0;  iIter < iConfigUsedBufferSize; iIter++ ) { 
				
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );				
			}//if ( bWriteConfigs == true )

		    
			//--------------------------------------------------------------------------
			// Write completed
			//--------------------------------------------------------------------------
			return true;
		}// WriteFlash30_2_0_0()

		        
        //---------------------------------------------------------------------
        // WriteFlash33_1_0_0()
        //---------------------------------------------------------------------
        static private bool WriteFlash33_1_0_0(clsSerialPort pobjPort, clsDevice pobjDevice, clsHex33FJ pobjHex, bool pbWriteProgram, bool pbWriteConfigs, int iTabLevel)
        {
            //--------------------------------------------------------------------------
            // Variables
            //--------------------------------------------------------------------------
            int iChecksum;
            int iSum;
            int iAddrP;
            int iRetries;
            byte[] bBuffer = new byte[256];
            int iBufferIndx;
            byte bAddrU, bAddrH, bAddrL, bSize, bProg;
            bool bRetry = false;
            int iByteToWrite = pobjHex.BytesToWrite( pobjDevice, pbWriteProgram, false, pbWriteConfigs );
            int iBytesWritten = 0;
            bool bProcessWriteResponseResult = false;


            //--------------------------------------------------------------------------
            // Write flash
            //--------------------------------------------------------------------------
            int iRow;

            if ( pbWriteProgram == true ) {
                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing flash...", iTabLevel) );
                

                //-------------------------------------------------------------
                // Iterate pages
                //-------------------------------------------------------------
                for ( int iPage = 0; iPage < clsHex33FJ.iProgPageUsedBufferSize; iPage++ ) {
                    if ( pobjHex.bProgPageUsed[iPage] == true ) {
                        iRetries = 0;
                        do {
                            if ( clsds30Loader.debugMode ) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Erasing page " + iPage.ToString(), iTabLevel) );
                            }

                            //---------------------------------------------------------
                            // Erase page
                            //---------------------------------------------------------
                            iSum = 0;
                            iBufferIndx = 0;

                            // Calculate
                            iAddrP = iPage * pobjDevice.pageSizeR * pobjDevice.rowsizeW * 2;	//24-bit address in memory to write to
                            bAddrU = Convert.ToByte((iAddrP & 0xff0000) >> 16);				//address upper byte			               
                            bAddrH = Convert.ToByte((iAddrP & 0x00ff00) >> 8);				//address high byte
                            bAddrL = Convert.ToByte((iAddrP & 0x0000ff) >> 0);				//address low byte
                            bSize = Convert.ToByte(1/*checksum*/ );

                            //
                            bBuffer[iBufferIndx++] = bAddrU; iSum += bAddrU;
                            bBuffer[iBufferIndx++] = bAddrH; iSum += bAddrH;
                            bBuffer[iBufferIndx++] = bAddrL; iSum += bAddrL;
                            bBuffer[iBufferIndx++] = cCmdErasePage; iSum += cCmdErasePage;
                            bBuffer[iBufferIndx++] = bSize; iSum += bSize;

                            // Calculate checksum and add to buffer
                            iSum %= 256;
                            iChecksum = Convert.ToInt16((256 - iSum) % 256);
                            bBuffer[iBufferIndx++] = Convert.ToByte(iChecksum);

                            // Send address, command, packetsize & checksum
                            pobjPort.SendBytes(ref bBuffer, iBufferIndx);
                            
                            // Get response, checksum ok
                            ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                            if ( bProcessWriteResponseResult == false ) {
                                return false;
                            }

                            //
                            Application.DoEvents();
                        } while (bRetry == true && bAbort == false);


                        //---------------------------------------------------------
                        // Iterate rows, write all rows in page even if not in hex-file
                        //---------------------------------------------------------
                        for ( iRow = iPage * pobjDevice.pageSizeR; iRow < iPage * pobjDevice.pageSizeR + pobjDevice.pageSizeR; iRow++ ) {
                            iRetries = 0;
                            do {
                                if ( clsds30Loader.debugMode ) {
                                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing row " + iRow.ToString(), iTabLevel) );
                                }

                                iBufferIndx = 0;
                                iSum = 0;

                                // Calculate
                                iAddrP = iRow * (pobjDevice.rowsizeW * 2);				//24-bit address in memory to write to
                                bAddrU = Convert.ToByte((iAddrP & 0xff0000) >> 16);	    //address upper byte			               
                                bAddrH = Convert.ToByte((iAddrP & 0x00ff00) >> 8);	    //address high byte
                                bAddrL = Convert.ToByte((iAddrP & 0x0000ff));			//address low byte
                                bSize = Convert.ToByte(pobjDevice.rowsizeW * 3 + 1/*checksum*/ );

                                //
                                bBuffer[iBufferIndx++] = bAddrU; iSum += bAddrU;
                                bBuffer[iBufferIndx++] = bAddrH; iSum += bAddrH;
                                bBuffer[iBufferIndx++] = bAddrL; iSum += bAddrL;
                                bBuffer[iBufferIndx++] = cCmdWriteRow; iSum += cCmdWriteRow;
                                bBuffer[iBufferIndx++] = bSize; iSum += bSize;

                                // Calculate startindex in hex-buffer
                                iAddrP = iRow * pobjDevice.rowsizeW * 3;

						        // Buffer row, upper-low-high, ordered in ParseHex()
						        for ( int iByte = 0; iByte < pobjDevice.rowsizeW * 3; iByte++ ) {
								    bProg = Convert.ToByte( pobjHex.iProgMem[iAddrP + iByte] );
							        bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;
						        }

                                // Calculate checksum and add to buffer
                                iSum %= 256;
                                iChecksum = Convert.ToInt16((256 - iSum) % 256);
                                bBuffer[iBufferIndx++] = Convert.ToByte(iChecksum);

                                // Send address, command, packetsize, row & checksum
                                pobjPort.SendBytes(ref bBuffer, iBufferIndx);

                                // Get response, checksum ok
                                ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                                if ( bProcessWriteResponseResult == false ) {
                                    return false;
                                }

                                //
                                Application.DoEvents();
                            } while ( bRetry == true && bAbort == false );

                            //
                            if (bAbort == true) {
                                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
                                return false;
                            }

                            //
                            iBytesWritten += pobjDevice.rowsizeW * 3;
                            OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );

                        }//for ( iRow = 0; iRow < iRowUsedBufferSize; iRow++ ) {

                    } //if ( bPageUsed[iIter] == true ) {

                }//for ( iPage = 0; iPage < iPageUsedBufferSize; iPage++ ) {

                OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );
            }//if ( pbWriteProgram == true ) {

            
            //--------------------------------------------------------------------------
			// Write Config Bits
			//--------------------------------------------------------------------------
            if ( pbWriteConfigs == true ) {
                int iConfig;
                int iByte;
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing configs...", iTabLevel) );
				iRetries = 0;
				
				for ( iConfig = 0; iConfig < clsHex33FJ.iConfigWordsUsedBufferSize; iConfig++ ) {
					if ( pobjHex.bConfigWordUsed[iConfig] == true ) {
                        iRetries = 0;
						do {
                            for ( iByte = 0; iByte < 2; iByte++ ) {
                                if ( clsds30Loader.debugMode ) {
                                    OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.info, "Writing config byte " + (iConfig*2 + iByte).ToString(), iTabLevel) );
                                }

                                iBufferIndx = 0;
							    iSum = 0;						
    						
							    // Calculate
							    iAddrP = 0xF80000 + iConfig * 2 + iByte;				//24-bit address in memory to write to
							    bAddrU = Convert.ToByte( (iAddrP & 0xff0000) >> 16 );	//address upper byte			               
							    bAddrH = Convert.ToByte( (iAddrP & 0x00ff00) >> 8 );	//address high byte
							    bAddrL = Convert.ToByte( (iAddrP & 0x0000ff) );			//address low byte
							    bSize = Convert.ToByte( 1 + 1/*checksum*/ );
    							
							    //
							    bBuffer[ iBufferIndx++ ] = bAddrU;	iSum += bAddrU;
							    bBuffer[ iBufferIndx++ ] = bAddrH;	iSum += bAddrH;
							    bBuffer[ iBufferIndx++ ] = bAddrL;	iSum += bAddrL;
							    bBuffer[ iBufferIndx++ ] = cCmdWriteConfig;iSum += cCmdWriteConfig;
							    bBuffer[ iBufferIndx++ ] = bSize;	iSum += bSize;	
    		                    
							    // Buffer config word
							    bProg = Convert.ToByte( pobjHex.iConfigMem[ iConfig * 2 + iByte ] );
							    bBuffer[ iBufferIndx++ ] = bProg; iSum = (iSum + bProg) % 256;	
    							
							    // Calculate checksum and add to buffer
							    iSum %= 256;
							    iChecksum = Convert.ToInt16( (256 - iSum) % 256 );
							    bBuffer[ iBufferIndx++ ] = Convert.ToByte(iChecksum);
    							
							    // Send row+checksum
							    pobjPort.SendBytes( ref bBuffer, iBufferIndx );
    		                    
							    // Get response, checksum ok
                                ProcessWriteResponse( pobjPort, ref iRetries, iTabLevel, "flash", ref bRetry, ref bProcessWriteResponseResult );
                                if ( bProcessWriteResponseResult == false ) {
                                    return false;
                                }
                            }
                            Application.DoEvents();
						} while ( bRetry == true && bAbort == false );
		                
						//
						if ( bAbort == true ) {
							OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.error, "aborted by user", -1) );
							return false;
						}
						
                        //
						iBytesWritten += 2;
                        OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.progress, "", (100 * iBytesWritten) / iByteToWrite ) );
					}//if ( bConfigUsed[iIter] == true ) {
					
				}//for ( iIter = 0;  iIter < iConfigUsedBufferSize; iIter++ ) { 
				
				OnDownloading( new clsDownloadingEventArgs(clsDownloadingEventArgs.EventType.success, "ok", -1) );				
			}//if ( bWriteConfigs == true )


            //--------------------------------------------------------------------------
            // Write completed
            //--------------------------------------------------------------------------
            return true;
        }// WriteFlash33_1_0_0()

        #endregion

    }// Class: clsds30Loader
}
