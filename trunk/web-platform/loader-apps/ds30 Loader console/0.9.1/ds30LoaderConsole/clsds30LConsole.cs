//-----------------------------------------------------------------------------
//
// Title:			ds30 Loader console
//
// Copyright:		Copyright © 2009, Mikael Gustafsson
//
// Version:			0.9.1 november 2009
//
// Link:			http://mrmackey.no-ip.org/elektronik/ds30loader/
//
// History:			0.9.1 Added option that when used doesn're require user interaction
//                  0.9.0 Initial release
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//    This file is part of ds30 Loader console.
//
//    ds30 Loader console is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation.
//
//    ds30 Loader console is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with ds30 Loader console.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------------    

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.IO.Ports;

using ds30Loader;
using GHelper;

namespace ds30_Loader_Console
{
    //-------------------------------------------------------------------------
    // Class: clsds30LConsole
    //-------------------------------------------------------------------------
    class clsds30LConsole
    {
        //---------------------------------------------------------------------
        // Variables
        //---------------------------------------------------------------------
        
        // From ValidateParseArgs()
        private string strFile = "";
        private string strPort = "";
        private int iBaudrate = 0;
        private bool bNonInteractive = false;

        //
        private clsDevice objDevice = null;
        private clsHex objHex = null;
        private clsSerialPort objPort = null;

        
        //---------------------------------------------------------------------
        // Constants
        //---------------------------------------------------------------------
        private const string strURLHomepage = "http://mrmackey.no-ip.org/elektronik/ds30loader/";        
        private const string strVersion = "0.9.1";


        //---------------------------------------------------------------------
        // Constructor
        //---------------------------------------------------------------------
        public clsds30LConsole()
        {
            Console.Clear();
            clsDevices.Init();    
       
            clsds30Loader.Downloading += new clsds30Loader.DownloadingDelegate( ds30L_Downloading );
        }// Constructor


        //---------------------------------------------------------------------
		// ds30L_Downloading()
		//---------------------------------------------------------------------
        private void ds30L_Downloading( object obj, clsDownloadingEventArgs e ) 
        {
	        if ( e.eventType == clsDownloadingEventArgs.EventType.started ) {
                clsDebugTextbox.OutputInfo( e.message, e.tabLevel );
            
            } else if ( e.eventType == clsDownloadingEventArgs.EventType.error ) {
                clsDebugTextbox.OutputError( e.message, e.tabLevel );

            } else if ( e.eventType == clsDownloadingEventArgs.EventType.warning ) {
                clsDebugTextbox.OutputWarning( e.message, e.tabLevel );
            
            } else if ( e.eventType == clsDownloadingEventArgs.EventType.info ) {
                clsDebugTextbox.OutputInfo( e.message, e.tabLevel );

            } else if ( e.eventType == clsDownloadingEventArgs.EventType.success ) {
                clsDebugTextbox.OutputSuccess( e.message, e.tabLevel );

            } else if ( e.eventType == clsDownloadingEventArgs.EventType.progressStarted ) {
                //progressBar.Value = e.tabLevel;
                //progressBar.Visible = true;
            
            } else if ( e.eventType == clsDownloadingEventArgs.EventType.progress ) {
                //progressBar.Value = e.tabLevel;
            
            } else if ( e.eventType == clsDownloadingEventArgs.EventType.progressEnded ) {
                //progressBar.Value = 0;
                //progressBar.Visible = false;            

            } else if ( e.eventType == clsDownloadingEventArgs.EventType.completed ) {
                clsDebugTextbox.OutputInfo( objPort.bytesSentStr + " sent", 1 ); 
	            clsDebugTextbox.OutputInfo( objPort.bytesReceivedStr + " received", 1 );			 
                clsDebugTextbox.OutputSuccess( e.message, e.tabLevel );
            }            
        }//ds30L_Downloading()	

        
        //---------------------------------------------------------------------
        // Constructor
        //---------------------------------------------------------------------
        public void DoMagic( string[] pstrArgs, ref bool pbResult ) 
        {
            pbResult = false;            

            
            //-----------------------------------------------------------------
            // If no argumentsa are specified, display help
            //-----------------------------------------------------------------
            if ( pstrArgs.Length == 0 ) {
                PrintHelp();
                return;
            }


            //-----------------------------------------------------------------
            // Validate arguments
            //-----------------------------------------------------------------
            bool bResult = false;
            clsParseSettings objParseSettings = new clsParseSettings();
            clsDownloadSettings objDownloadSettings = new clsDownloadSettings();
            ValidateParseArgs( pstrArgs, objParseSettings, objDownloadSettings, ref bResult );
            if ( bResult == false ) {
                return;
            }


            //-----------------------------------------------------------------
            // Nothing to do?
            //-----------------------------------------------------------------
			if ( objDownloadSettings.writeProgram == false && objDownloadSettings.writeEEPROM == false && objDownloadSettings.writeConfigs == false  ) {
				Console.WriteLine( "Nothing to do." );
				return;
			}


            //-----------------------------------------------------------------
            // Parse
            //-----------------------------------------------------------------
            objParseSettings.device = objDevice;
            DoParse( objParseSettings, objDownloadSettings );

            
            //-----------------------------------------------------------------
            // Create port
            //-----------------------------------------------------------------
            objPort = new clsSerialPort();
            objPort.Setup( strPort, iBaudrate );


            //-----------------------------------------------------------------
            // Increase process priority if polltime is low
            //-----------------------------------------------------------------
            if ( objDownloadSettings.polltime < 100 ) {
                try {
                    System.Diagnostics.Process.GetCurrentProcess().PriorityClass = System.Diagnostics.ProcessPriorityClass.AboveNormal;
                } catch {
                    clsDebugTextbox.OutputInfo( "Setting proccess priority failed." );
                }
            }


            //-----------------------------------------------------------------
            // Print settings
            //-----------------------------------------------------------------
            Console.WriteLine( "" );
            Console.WriteLine( "" );
            Console.WriteLine( "{0,-10} {1, -8}", "File:", strFile );
            Console.WriteLine( "{0,-10} {1, -8}", "Port:", strPort );
            Console.WriteLine( "{0,-10} {1, -8}", "Baudrate:", iBaudrate.ToString() );
            Console.WriteLine( "{0,-10} {1, -8}", "Device:", objDevice.name );


            //-----------------------------------------------------------------
            // 
            //-----------------------------------------------------------------            
            Console.WriteLine( "" );
            Console.WriteLine( "" );
            if ( bNonInteractive == false ) {
                Console.WriteLine( "Press any key to begin download" );
                Console.WriteLine( "" );
                Console.ReadKey();
            }
            

            //-----------------------------------------------------------------
            // Download
            //-----------------------------------------------------------------
            bool bDownloadResult = false;
            int iStartTime = Environment.TickCount;
            clsds30Loader.Download( objDevice, objPort, objHex, objDownloadSettings, 0, ref bDownloadResult );
            int iEndTime = Environment.TickCount;


            //-----------------------------------------------------------------
            // Restore process priority
            //-----------------------------------------------------------------
            if ( objDownloadSettings.polltime < 100 ) {
                try {
                    System.Diagnostics.Process.GetCurrentProcess().PriorityClass = System.Diagnostics.ProcessPriorityClass.Normal;
                } catch {
                    clsDebugTextbox.OutputInfo( "Setting proccess priority failed." );
                }
            }

            //-----------------------------------------------------------------
            // Download finished
            //-----------------------------------------------------------------            
            objPort.Close();
            if ( clsds30Loader.debugMode ) {
                clsDebugTextbox.OutputInfo( "Elapsed time: " + String.Format( "{0:0.#}", Convert.ToSingle(iEndTime - iStartTime) / 1000.0 ) + " seconds", 1 );			
            } 
            pbResult = bDownloadResult;
        }// DoMagic()


		//---------------------------------------------------------------------
		// DoParse()
		// Description:
		//---------------------------------------------------------------------
		private void DoParse( clsParseSettings pobjParseSettings, clsDownloadSettings pobjDownloadSettings )
		{	
			int iBootLoaderSizeR = 0;
            bool bParseResult = false;

            // Here we only assume a bootloader size to be able to parse the hex-file            
            if ( objDevice.family.name == "PIC18F" ) {
                objHex = new clsHex18F( strFile );
                iBootLoaderSizeR = 5 * objDevice.pageSizeR;

             } else if ( objDevice.family.name == "PIC18FJ" ) {
                objHex = new clsHex18FJ( strFile );
                iBootLoaderSizeR = 16;
           
            } else if ( objDevice.family.name == "PIC24F" ) {
                objHex = new clsHex24F( strFile );
                iBootLoaderSizeR = 4;

            } else if ( objDevice.family.name == "PIC24FJ" ) {
                objHex = new clsHex24FJ( strFile );
                iBootLoaderSizeR = 8;
            
            } else if ( objDevice.family.name == "PIC24H" ) {
                objHex = new clsHex24H( strFile );
                iBootLoaderSizeR = 8;

            } else if ( objDevice.family.name == "dsPIC30F" ) {				
				objHex = new clsHex30F( strFile );
				iBootLoaderSizeR = 4;				
			
            } else if ( objDevice.family.name == "dsPIC33FJ" ) {
				objHex = new clsHex33FJ( strFile );				
				iBootLoaderSizeR = 8;
            
            } else {
				return;
			}
	        
            // Check file existence
            if ( File.Exists(strFile) == false ) {
                return;
            }

            // Enum events
            objHex.HexFileValidate += new clsHex.HexFileValidateDelegate( Hex_Validate );
            objHex.HexFileParse += new clsHex.HexFileParseDelegate( Hex_Parse );

            // Parse
			if ( objDevice != null ) {
				objHex.ParseHexFile( pobjParseSettings, 0, ref bParseResult );
				
				pobjDownloadSettings.writeProgram &= objHex.hasValidProgram;
                pobjDownloadSettings.writeEEPROM &= objHex.hasValidEEPROM;
                pobjDownloadSettings.writeConfigs &= objHex.hasValidConfigs;
			}		
		}//DoParse();


		//---------------------------------------------------------------------
		// Hex_Parse()
		//---------------------------------------------------------------------
		private void Hex_Parse( object obj, clsHexFileParseEventArgs e ) 
        { 
            clsHex objHex = (clsHex)obj;

			if ( e.eventType == clsHexFileParseEventArgs.EventType.started ) {
                clsDebugTextbox.OutputInfo( "Parsing hex-file...", e.tabLevel );

            } else if ( e.eventType == clsHexFileParseEventArgs.EventType.warning ) {
                clsDebugTextbox.OutputWarning( e.message, e.tabLevel );
            
            } else if ( e.eventType == clsHexFileParseEventArgs.EventType.info ) {
                clsDebugTextbox.OutputInfo( e.message, e.tabLevel );
            
            } else if ( e.eventType == clsHexFileParseEventArgs.EventType.failed ) {
                clsDebugTextbox.OutputError( "Parsing of hex-file failed", e.tabLevel );                

            } else if ( e.eventType == clsHexFileParseEventArgs.EventType.success ) {
                clsDebugTextbox.OutputSuccess( "Hex-file successfully parsed", e.tabLevel );
                clsDebugTextbox.OutputInfo( "", 0 );
                clsDebugTextbox.OutputInfo( objHex.progWordsUsed.ToString() + " program words found in " + objHex.progRowsUsed.ToString() + " rows " /*+ (objHex.progWordsUsed * 3 ).ToString() + " bytes)"*/, e.tabLevel );
                clsDebugTextbox.OutputInfo( objHex.eeWordsUsed.ToString() + " eeprom words found " /*+ (objHex.eeWordsUsed * 2).ToString() + " bytes)"*/, e.tabLevel);
                clsDebugTextbox.OutputInfo( objHex.configWordsUsed.ToString() + " config words found " /*+ (objHex.configWordsUsed*2).ToString() + " bytes)"*/, e.tabLevel );			
                
            }            
		}//Hex_Parse()	


        //---------------------------------------------------------------------
		// Hex_Validate()
		//---------------------------------------------------------------------
		private void Hex_Validate( object obj, clsHexFileValidateEventArgs e ) 
        {
			if ( e.eventType == clsHexFileValidateEventArgs.EventType.started ) {
                clsDebugTextbox.OutputInfo( "Validating hex-file...", e.tabLevel );
            
            } else if ( e.eventType == clsHexFileValidateEventArgs.EventType.failed ) {
                clsDebugTextbox.OutputError( e.message );

            } else if ( e.eventType == clsHexFileValidateEventArgs.EventType.success ) {
                clsDebugTextbox.OutputSuccess( "ok" );
               
            }
		}//Hex_Validate()	


        //-------------------------------------------------------------------------
        // OutputOption()
        //-------------------------------------------------------------------------
        private void OutputOption( string pstrShort, string pstrLong, string pstrDescription )
        {
            Console.WriteLine("{0,-8} {1, -8} {2,-24} {3,-32}", "", "-"+pstrShort, "--"+pstrLong, pstrDescription );
        }// OutputOption


        //-------------------------------------------------------------------------
        // PrintHelp()
        //-------------------------------------------------------------------------
        private void PrintHelp()
        {
            //---------------------------------------------------------------------
            // Header
            //---------------------------------------------------------------------            
            Console.WriteLine( "" );
            Console.WriteLine( "" );
            Console.WriteLine( "ds30 Loader console " + strVersion + " / " + clsds30Loader.strVersion);
            Console.WriteLine( strURLHomepage );
            Console.WriteLine( "" );
            Console.WriteLine( "" );
            Console.WriteLine( "Usage: ds30loaderconsole options" );


            //---------------------------------------------------------------------
            // Non-optional options
            //---------------------------------------------------------------------
            Console.WriteLine( "" );
            Console.WriteLine( "" );
            Console.WriteLine( "NON-OPTIONAL OPTIONS" );
            OutputOption( "f=val", "file=filename", "Hex-file" );
            OutputOption( "d=val", "device=devicename", "Devicename" );
            OutputOption( "k=val", "port=portname", "Portname" );
            OutputOption( "r=val", "baudrate=value", "Baudrate" );


            //---------------------------------------------------------------------
            // Optional options
            //---------------------------------------------------------------------
            Console.WriteLine( "" );
            Console.WriteLine( "" );
            Console.WriteLine( "OPTIONAL OPTIONS" );
            OutputOption( "h", "help", "Displays help" );
            OutputOption( "l", "debugmode", "Debugmode" );
            OutputOption( "o", "non-interactive", "Starts download without user interaction" );
            Console.WriteLine( "" );
            OutputOption( "p", "write-program", "Downloads program" );
            OutputOption( "e", "write-eeprom", "Downloads eeprom" );
            OutputOption( "c", "write-config", "Downloads configs" );
            OutputOption( "g", "no-goto", "Don't write goto" );
            Console.WriteLine( "" );
            OutputOption( "a=val", "polltime=time", "Polltime [ms] [" + clsDownloadSettings.iPolltimeDefault + "]" );
            OutputOption( "t=val", "timeout=time", "Time before timeout [ms] [" + clsDownloadSettings.iTimeoutDefault + "]"  );
            Console.WriteLine( "" );
            OutputOption( "q=val", "reset-command", "Reset device by specified command" );
            OutputOption( "u=val", "reset-baudrate", "Baudrate for reset command" );
            OutputOption( "m", "reset-dtr", "Reset device by dtr" );
            OutputOption( "n", "reset-rts", "Reset device by rts" );
            OutputOption( "b=val", "resettime=time", "Resettime [ms] [" + clsDownloadSettings.iResetTimeDefault + "]" );
            Console.WriteLine( "" );
            OutputOption( "i", "activate-dtr", "Activate device by dtr" );
            OutputOption( "j", "activate-rts", "Activate device by rts" );
            Console.WriteLine( "" );
            Console.WriteLine( "" );
        }// PrintHelp()


        //-------------------------------------------------------------------------
        // ValidateParseArgs()
        //-------------------------------------------------------------------------
        private void ValidateParseArgs( string[] pstrArgs, clsParseSettings pobjParseSettings, clsDownloadSettings pobjDownloadSettings, ref bool pbResult ) 
        {
            pbResult = false;

            //
            string [] strSplitArgs;
            string strOption;
            string strOptionValue;
            string strArgument;

            //
            bool bFileSpecified = false;
            bool bPortSpecified = false;
            bool bBaudrateSpecified = false;
            bool bDeviceSpecified = false;


            foreach ( string strArg in pstrArgs ) {
                //
                strArgument = strArg;
                if ( strArg.EndsWith("=") ) {
                    strArgument += "0";
                }
                strSplitArgs = strArgument.Split('=');
                
                // Argument                
                strOption = strSplitArgs[0].ToLower();
                
                // Argument value
                if ( strSplitArgs.Length == 2 ) {
                    strOptionValue = strSplitArgs[1];
                } else if (strSplitArgs.Length == 1 ) {
                    strOptionValue = "";
                } else {
                    Console.WriteLine( "Invalid argument: " + strArg );
                    return;
                }

                switch ( strOption ) {
                    //---------------------------------------------------------
                    // Misc
                    //---------------------------------------------------------

                    // Help
                    case "-h":
                    case "--help":
                        PrintHelp();
                        return;

                    // Debugmode
                    case "-l":
                    case "--debugmode":
                        clsds30Loader.debugMode = true;
                        return;

                    // Non-interactive
                    case "-o":
                    case "--non-interactive":
                        bNonInteractive = true;
                        return;

                    
                    //---------------------------------------------------------
                    // Basic
                    //---------------------------------------------------------

                    // Devicename
                    case "-d":
                    case "--device":
                        objDevice = clsDevices.DeviceGet( strOptionValue );
                        if ( objDevice == null ) {
                            Console.WriteLine( "Unknown device specified." );
                            return;
                        }
                        bDeviceSpecified = true;
                        break;

                    // Hex-file
                    case "-f":
                    case "--file":
                        strFile = strOptionValue;    
                        if ( File.Exists(strFile) == false ) {
                            Console.WriteLine( "Non-existing file specified." );
                            return;
                        }
                        bFileSpecified = true;
                        
                        break;                        

                    // Portname
                    case "-k":
                    case "--port":
                        strPort = strOptionValue;
                        bPortSpecified = true;
                        break; 
                    
                    // Baudrate
                    case "-r":
                    case "--baudrate":
                        try {
                            iBaudrate = int.Parse( strOptionValue );
                        } catch {
                            Console.WriteLine( "Invalid baudrate specified." );
                            return;
                        }
                        if ( iBaudrate <= 0 ) {
                            Console.WriteLine( "Invalid baudrate specified." );
                            return;
                        }
                        bBaudrateSpecified = true;
                        break;
                    
                    // Write program
                    case "-p":
                    case "--write-program":
                        pobjDownloadSettings.writeProgram = true;
                        break;
                    
                    // Write eeprom
                    case "-e":
                    case "--write-eeprom":
                        pobjDownloadSettings.writeEEPROM = true;
                        break;                    
                    

                    //---------------------------------------------------------
                    // Advanced
                    //---------------------------------------------------------

                    // Write configs
                    case "-c":
                    case "--write-configs":
                        pobjDownloadSettings.writeConfigs = true;
                        break;
                    
                    // Don't write goto
                    case "-g":
                    case "--no-goto":
                        pobjParseSettings.noGoto = true;
                        pobjDownloadSettings.noGoto = true;
                        break;
                     
                    // Allow overwrite of bootloader
                    case "-s":
                    case "--allow-bl-overwrite":
                        pobjParseSettings.allowBlOverwrite = true;
                        pobjDownloadSettings.allowBlOverwrite = true;
                        break;
                   

                    //---------------------------------------------------------
                    // Timing
                    //---------------------------------------------------------

                    // Polltime
                    case "-a":
                    case "--polltime":
                        int iPolltime;
                        try {
                            iPolltime = int.Parse( strOptionValue );
                        } catch {
                            Console.WriteLine( "Invalid polltime specified." );
                            return;
                        }
                        if ( iPolltime <= 0 ) {
                            Console.WriteLine( "Invalid polltime specified." );
                            return;
                        }
                        pobjDownloadSettings.polltime = iPolltime;
                        break;
                    
                    // Timeout
                    case "-t":
                    case "--timeout":
                        int iTimeout;
                        try {
                            iTimeout = int.Parse( strOptionValue );
                        } catch {
                            Console.WriteLine( "Invalid timeout specified." );
                            return;
                        }
                        if ( iTimeout <= 0 ) {
                            Console.WriteLine( "Invalid timeout specified." );
                            return;
                        }
                        pobjDownloadSettings.timeout = iTimeout;
                        break;


                    //---------------------------------------------------------
                    // Reset
                    //---------------------------------------------------------

                    // Reset by command
                    case "-q":
                    case "--reset-command":
                        pobjDownloadSettings.resetCommand = true;
                        pobjDownloadSettings.resetCommandSequence = strOptionValue;
                        break;

                     // Reset baudrate
                    case "-u":
                    case "--reset-baudrate":
                        int iResetBaudrate;
                        try {
                            iResetBaudrate = int.Parse( strOptionValue );
                        } catch {
                            Console.WriteLine( "Invalid reset baudrate specified." );
                            return;
                        }
                        if ( iResetBaudrate <= 0 ) {
                            Console.WriteLine( "Invalid reset baudrate specified." );
                            return;
                        }
                        pobjDownloadSettings.resetBaudrate = iResetBaudrate;
                        break;
                   
                    // Reset by dtr
                    case "-m":
                    case "--reset-dtr":
                        pobjDownloadSettings.resetDtr = true;
                        break;

                    // Reset by rts
                    case "-n":
                    case "--reset-rts":
                        pobjDownloadSettings.resetRts = true;
                        break;
                    
                    // Resettime
                    case "-b":
                    case "--resettime":
                        int iResettime;
                        try {
                            iResettime = int.Parse( strOptionValue );
                        } catch {
                            Console.WriteLine( "Invalid resettime specified." );
                            return;
                        }
                        if ( iResettime <= 0 ) {
                            Console.WriteLine( "Invalid resettime specified." );
                            return;
                        }
                        pobjDownloadSettings.resetTime = iResettime;
                        break;


                    //---------------------------------------------------------
                    // Activation
                    //---------------------------------------------------------

                    // Activate by dtr
                    case "-i":
                    case "--activate-dtr":
                        pobjDownloadSettings.activateDTR = true;
                        break;

                    // Activate by rts
                    case "-j":
                    case "--activate-rts":
                        pobjDownloadSettings.activateRTS = true;
                        break;


                    //---------------------------------------------------------
                    // Unknown option
                    //---------------------------------------------------------
                    default:
                        Console.WriteLine( "Unknown option \"" + strArg + "\"" );
                        Console.WriteLine( "" );
                        return;

                }
            }

            if ( bFileSpecified == false ) {
                Console.WriteLine( "File not specified" );
                return;
            }
            if ( bPortSpecified == false ) {
                Console.WriteLine( "Port not specified" );
                return;
            }
            if ( bBaudrateSpecified == false ) {
                Console.WriteLine( "Baudrate not specified" );
                return;
            }
            if ( bDeviceSpecified == false ) {
                Console.WriteLine( "Device not specified" );
                return;
            }

            pbResult = true;
        }// ValidateParseArgs()

    }// Class: clsds30LConsole
}
