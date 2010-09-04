import time
#import serial

class ComIRDevice:
    def __init__(self,ComNo,Baud=115200,TimeOut=0.5):
        self.__ser=eg.SerialThread()
        self.__ser.Open(ComNo)
        self.__ser.Start()
        #self.__ser=serial.Serial(ComNo,Baud,timeout=TimeOut)
        self.FlushBuffers()
       
    def __init__(self,mySerialThread=None):
        self.__ser=mySerialThread
        #self.__ser.Open(ComNo)
        #self.__ser.Start()
        #self.__ser=serial.Serial(ComNo,Baud,timeout=TimeOut)
        self.FlushBuffers()


        #self.__ser.baudrate=Baud

    def GetData(self,numData,intTimeout):
        #return self.__ser.read(numData)
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
        #time.sleep(.5)
        try:
            retStr= str(self.__ser.Read(4,.1))
            return retStr
        except:
            return "No USB IR Toy Detected!"    
        
    
    def EnterSamplingMode(self):
        self.ResetMode()
        self.SendChar('s') # sampling mode
        strTemp=self.ReadString(3)
        #print strTemp
        print strTemp
        if(strTemp=='S01'):
            return True
        return False
        




##class ComIRDevice:
##    def __init__(self,ComNo,Baud=115200,TimeOut=0.5):
##        self.__ser=serial.Serial(ComNo,Baud,timeout=TimeOut)
##        self.__ser.flushInput()
##                x=eg.SerialThread()
##        print x.GetAllPorts()
##
##        #self.__ser.baudrate=Baud
##
##    def GetData(self,numData):
##        #return self.__ser.read(numData)
##        mylist=list(self.__ser.read(numData))
##        return mylist
##    
##    def ReadString(self,numData):
##        return str(self.__ser.read(numData))
##
##    def GetSerialPort(self):
##        return self.__ser
##
##    def Close(self):
##        if(self.__ser.isOpen()):
##            self.__ser.close()
##            
##    def SendAscii(self,ascdata):
##        self.__ser.write(chr(ascdata))
##    
##    def SendChar(self,chardata):
##        self.__ser.write(chardata)
##       
##    def FlushBuffers(self):
##        self.__ser.flushInput()
##        self.__ser.flush()
##        self.__ser.flushOutput()   
##             
##    def ResetMode(self):
##        self.SendAscii(0x00)
##        self.SendAscii(0x00)
##        self.SendAscii(0x00)
##        self.SendAscii(0x00)
##        self.SendAscii(0x00)
##        time.sleep(.05)
##        self.FlushBuffers()
##        
##    def GetVersion(self):
##        self.FlushBuffers()
##        self.SendChar('v')
##        time.sleep(.05)
##        return str(self.__ser.read(4))
##    
##    def EnterSamplingMode(self):
##        self.ResetMode()
##        self.SendChar('s') # sampling mode    
##        if(self.ReadString(3)=='S01'):
##            return True
        return False        