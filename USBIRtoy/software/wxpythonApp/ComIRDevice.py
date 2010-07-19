import serial

class ComIRDevice:
    def __init__(self,ComNo,Baud):
        self.__ser=serial.Serial(ComNo,Baud,timeout=5)
        self.__ser.flushInput()
        #self.__ser.baudrate=Baud

    def GetData(self,numData):
        return self.__ser.read(numData)

    def GetSerialPort(self):
        return self.__ser

    def Close(self):
        if(self.__ser.isOpen()):
            self.__ser.close()
    