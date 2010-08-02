import time
import serial

class ComIRDevice:
    def __init__(self,ComNo,Baud):
        self.__ser=serial.Serial(ComNo,Baud,timeout=.3)
        self.__ser.flushInput()
        #self.__ser.baudrate=Baud

    def GetData(self,numData):
        #return self.__ser.read(numData)
        mylist=list(self.__ser.read(numData))
        return mylist
    
    def ReadString(self,numData):
        return str(self.__ser.read(numData))

    def GetSerialPort(self):
        return self.__ser

    def Close(self):
        if(self.__ser.isOpen()):
            self.__ser.close()
            
    def SendAscii(self,ascdata):
        self.__ser.write(chr(ascdata))
    
    def SendChar(self,chardata):
        self.__ser.write(chardata)
       
    def FlushBuffers(self):
        self.__ser.flushInput()
        self.__ser.flush()
        self.__ser.flushOutput()   
             
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
        time.sleep(.05)
        return str(self.__ser.read(4))
    
    def EnterSamplingMode(self):
        self.ResetMode()
        self.SendChar('s') # sampling mode    
        if(self.ReadString(3)=='S01'):
            return True
        return False
        
        