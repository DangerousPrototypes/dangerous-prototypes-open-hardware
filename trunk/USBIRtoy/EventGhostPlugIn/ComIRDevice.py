# This file is part of EventGhost.
# Copyright (C) 2005 Lars-Peter Voss <bitmonster@eventghost.org>
# 
# EventGhost is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# EventGhost is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with EventGhost; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
#--------------------------------------------------------------------------------------------
#  USB IR Toy plugin serial port helper
#  The USB Infrared Toy is an open source infrared receiver/transmitter
#   http://dangerousprototypes.com/docs/USB_Infrared_Toy
# This is object needs an eg.SerialThread object
# By 7

import eg
import time


class ComIRDevice:

    def __init__(self,mySerialThread=None):
        self.__ser=mySerialThread
        self.FlushBuffers()

    def GetData(self,numData,intTimeout):
        mylist=list(self.__ser.Read(numData,intTimeout))
        return mylist
    
    def ReadString(self,numData):
        return str(self.__ser.Read(numData,.1))

    def GetSerialPort(self):
        return self.__ser

    def Close(self):
        if(self.__ser.isOpen()):
            self.__ser.close()
            
    def SendAscii(self,ascdata):
        self.__ser.Write(chr(ascdata))
    
    def SendChar(self,chardata):
        self.__ser.Write(chardata)
       
    def FlushBuffers(self):
        self.__ser.Flush()
             
    def ResetMode(self):
        self.SendAscii(0x00)
        self.SendAscii(0x00)
        self.SendAscii(0x00)
        self.SendAscii(0x00)
        self.SendAscii(0x00)
        time.sleep(.05)
        self.FlushBuffers()
        
    def GetVersion(self):
        self.FlushBuffers()
        self.SendChar('v')
        try:
            retStr= str(self.__ser.Read(4,.1))
            return retStr
        except:
            return "No USB IR Toy Detected!"    
        
    
    def EnterSamplingMode(self,strSamplingMode):
        self.ResetMode()
        self.SendChar('s') # sampling mode
        strTemp=self.ReadString(3)
        #print strTemp
        if(strTemp==strSamplingMode):
            return True
        return False
        

   