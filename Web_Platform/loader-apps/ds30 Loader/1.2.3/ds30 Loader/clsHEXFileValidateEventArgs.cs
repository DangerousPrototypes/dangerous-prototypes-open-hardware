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
	// Class: clsHexFileValidateEventArgs
	//-------------------------------------------------------------------------
	public class clsHexFileValidateEventArgs
	{
        //---------------------------------------------------------------------
        // Enum: EventType
        //---------------------------------------------------------------------
	    public enum EventType {
		    started,
		    failed,
            success
	    }//Enum: EventType
        
        
        //---------------------------------------------------------------------
		// Variables
		//---------------------------------------------------------------------	
		private EventType eEventType;
        private string strMessage;
		private int iTabLevel;

				
		//---------------------------------------------------------------------
		// Constructor
		//---------------------------------------------------------------------
		public clsHexFileValidateEventArgs( EventType peEventType, string pstrMessage, int piTabLevel )
		{
			eEventType = peEventType;
			strMessage = pstrMessage;
            iTabLevel = piTabLevel;
		}//Constructor		


		//---------------------------------------------------------------------
		// Property: eventType
		//---------------------------------------------------------------------
		public EventType eventType
		{
			get {
				return eEventType;
			}
		}//Property: eventType 
		
		
		//---------------------------------------------------------------------
		// Property: message
		//---------------------------------------------------------------------
		public string message
		{
			get {
				return strMessage;
			}
		}//Property: message 	
		

		//---------------------------------------------------------------------
		// Property: tabLevel
		//---------------------------------------------------------------------
		public int tabLevel
		{
			get {
				return iTabLevel;
			}
		}//Property: tabLevel 
		
	}// Class: clsHexFileValidateEventArgs
		
}   