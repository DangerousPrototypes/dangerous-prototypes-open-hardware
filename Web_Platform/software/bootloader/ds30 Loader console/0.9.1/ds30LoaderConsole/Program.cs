//-----------------------------------------------------------------------------
//    This file is part of ds30 Loader Console.
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
using GHelper;

namespace ds30_Loader_Console
{
    //-------------------------------------------------------------------------
    // Class: Program
    //-------------------------------------------------------------------------
    class Program
    {
        //---------------------------------------------------------------------
        // Main()
        //---------------------------------------------------------------------
        static int Main(string[] args)
        {
            clsDebugTextbox.bConsole = true;

            // Create object
            clsds30LConsole objds30LConsole = new clsds30LConsole();

            //
            bool bResult = false;
            objds30LConsole.DoMagic( args, ref bResult );

            // Make sure the user can read the output
            DisplayPressAnyKey();
            
            // Check result
            if ( bResult == false ) {
                System.Environment.ExitCode = -1;
                return -1;
            } else {
                System.Environment.ExitCode = 0;
                return 0;
            }
        }// Main()


        //---------------------------------------------------------------------
        // DisplayPressAnyKey()
        //---------------------------------------------------------------------
        static public void DisplayPressAnyKey()
        {
            Console.WriteLine( "" );
            Console.WriteLine( "Press any key to continue" );
            Console.ReadKey();
        }// DisplayPressAnyKey

    }// Class: Program
}
