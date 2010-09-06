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
        

   