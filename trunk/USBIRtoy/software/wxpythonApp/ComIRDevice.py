import serial

class ComIRDevice:
    def __init__(self,ComNo,Baud):
        self.__ser=serial.Serial(ComNo,Baud,timeout=1)
        #self.__ser.baudrate=Baud

    def Close():
        if(self.__ser.isOpen()):
            self.__ser.close()
    