import serial,time
IsUsbIrToyUsed=True
COMPort='COM17' # Change this if needed :)
mySer=serial.Serial(COMPort, 9600, timeout=2)

try:
    if(IsUsbIrToyUsed):
        mySer.write('\x00\x00\x00\x00\x00u') # set to UART Mode
        time.sleep(.2)
    mySer.flushInput()
    
    print "ID Card #: " + "".join(["0x%2x " %(ord(c)) for c in list(mySer.readall())])
finally:
    mySer.close()
