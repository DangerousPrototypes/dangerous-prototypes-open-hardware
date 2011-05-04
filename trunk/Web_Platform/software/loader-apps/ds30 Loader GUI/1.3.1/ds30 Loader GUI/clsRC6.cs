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
    //-------------------------------------------------------------------------
    // Class: clsRC6
    //-------------------------------------------------------------------------    
    public class clsRC6
    {
        //---------------------------------------------------------------------
        // Default values
        //---------------------------------------------------------------------
        private const int iDefaultRounds = 20;
        private const uint iDefaultP32 = 0xB7E15163;
        private const uint iDefaultQ32 = 0x9E3779B9;

        private const uint w = 32;


        //---------------------------------------------------------------------
        // Variables
        //---------------------------------------------------------------------
        private int r = 20;
        //private int b = 16;
        private uint p;
        private uint q;

        // Key  
        uint[] S;
        //bool bKeyIsInitialized = false;

        // w = wordsize [bits]
        // r = rounds []
        // b = keylenght [bytes]
        
        // P = magic constant
        // Q = magic constant


        //---------------------------------------------------------------------
        // Constructor
        //---------------------------------------------------------------------
        public clsRC6() 
        {
            Setup ( iDefaultRounds, iDefaultP32, iDefaultQ32 );
        }// Constructor
        
        
        //---------------------------------------------------------------------
        // Encrypt()
        //---------------------------------------------------------------------
        public void Encrypt( byte[] pbData ) 
        {
            uint A, B, C, D, A2;
            int t, u;

            A = pbData[0];
            B = pbData[1];
            C = pbData[2];
            D = pbData[3];
            
            B = B + S[0];
            D = D + S[1];

            for ( int i = 1; i <= r; i++ ) {                   
                t = (int)(B * (2*B + 1)) << LogW();
                u = (int)(D * (2*D + 1)) << LogW();
                A = (uint)((A ^ t) << u) + S[2*i];
                C = (uint)((C ^ u) << t) + S[2*i+ 1];
                
                A2 = A;
                A = B;
                B = C;
                C = D;
                D = A2;
            }
            
            A = A + S[2*r + 2];
            C = C + S[2*r + 3];
        }// Encrypt()


        //---------------------------------------------------------------------
        // LogW()
        //---------------------------------------------------------------------
        public int LogW() 
        {
            if ( w == 32 ) {
                return 5;
            } else if ( w == 16 ) {
                return 4;
            }
        }// LogW()


        //---------------------------------------------------------------------
        // KeyGen()
        //---------------------------------------------------------------------
        public void KeyGen( byte[] pbKey ) 
        {
            uint A, B, i, j, v, s, c;
            S = new uint[2*r+4];                        
            
            c = 8 * (uint)pbKey.Length / w;

            // Key bytes -> key words
            uint[] L = new uint[ c ];
            for ( int abcd = 0; abcd < c; abcd++ ) {
                if ( abcd+3 < pbKey.Length ) {
                    L[abcd] = (uint)( pbKey[abcd] + (pbKey[abcd+1] << 8) + (pbKey[abcd+2] << 16) + (pbKey[abcd+3] << 24) );
                } else {
                    L[abcd] = 0;
                }
            }
            
            S[0] = p;

            for ( i = 1; i <= 2*r+3; i++ ) {
                S[i] = S[i-1] + q;
            }

            A = B = i = j = 0;

            v = 3 * (uint)Math.Max( c, 2*r + 4 );
            for ( s = 1; s <= v; s++ ) {
                A = S[i] = (S[i] + A + B) << 3;
                B = L[j] = (uint)( (int)(L[j] + A + B) << (int)(A + B) );
                i = (uint)( (i + 1) % (2*r + 4) );       
                j = (j + 1) % c;
                
            }

            //bKeyIsInitialized = true;
        }// KeyGen()


        //---------------------------------------------------------------------
        // Setup()
        //---------------------------------------------------------------------
        public void Setup( int piRounds, uint piP, uint piQ ) 
        {
            r = piRounds;
            p = piP;
            q = piQ;
        }// Setup()

    }// Class: clsRC6
}
