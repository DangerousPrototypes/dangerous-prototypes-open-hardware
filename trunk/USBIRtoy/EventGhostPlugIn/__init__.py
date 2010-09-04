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
#
# $LastChangedDate: 2009-03-18 22:43:55 +0100 (Mi, 18 Mrz 2009) $
# $LastChangedRevision: 855 $
# $LastChangedBy: Bitmonster $

from __future__ import with_statement
import eg

eg.RegisterPlugin(
    name = "USB IR Toy Based on UIRT2",
    author = ":)",
    #version = "1.1." + "$LastChangedRevision: 855 $".split()[1],
    version = "00.08.00" ,
    kind = "remote",
    canMultiLoad = True,
    description = (
        'Hardware plugin for the <a href="http://dangerousprototypes.com/">'
        'USB IR Toy</a>.'
    ),
    icon = (
        "iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAAaElEQVR42mNkoBAwDgMD"
        "/jMw/IeaRLJhIL1gAw4eOMBg7+AANwQsgYWNrrkR2QWkGALTXE+uAQ1APkgziguQQpU8"
        "F5BiAE4XNEIkGYkJRJghcANgmkmJRpAhjA1QA0jVjORlysDAGwAAHWBIBf4cTRAAAAAA"
        "SUVORK5CYII="
    ),
)

import wx
from threading import Thread, Event
from time import sleep, clock
from binascii import hexlify, unhexlify
from Queue import Queue, Full
from string import hexdigits
from ComIRDevice import ComIRDevice

# currently unused stuff

#def GetStructTime(code, start):
#    tvalue = (ord(code[start+1]) * 256) + ord(code[start+2])
#    bBits = ord(code[start+3])
#    bHdr1 = ord(code[start+4])
#    bHdr0 = ord(code[start+5])
#    bOff0 = ord(code[start+6])
#    bOff1 = ord(code[start+7])
#    bOn0 = ord(code[start+8])
#    bOn1 = ord(code[start+9])
#    tvalue += bHdr1 + bHdr0
#    for i in range(0, bBits):
#        bit = (ord(code[start + 10 + (i / 8)]) >> (i % 8)) & 1
#        if (i % 2) == 0:
#            if bit:
#                tvalue += bOn1
#            else:
#                tvalue += bOn0
#        else:
#            if bit:
#                tvalue += bOff1
#            else:
#                tvalue += bOff0
#    return tvalue
#
#
#def CalcTime(code):
#    tvalue = 0
#    if code[0] == "\x36":  
#        # RAW
#        length = ord(code[1])
#        tvalue = (ord(code[2]) * 256) + ord(code[3])
#        for i in range(4, length + 4):
#            tvalue += ord(code[i])
#        tvalue = tvalue * (ord(code[-2]) & 0x1F)
#        #tvalue -= (ord(code[2]) * 256) + ord(code[3])
#    elif (ord(code[0]) & 0x1F) > 0:
#        # REMSTRUCT1
#        repeat = ord(code[0]) & 0x1F
#        tvalue = GetStructTime(code, 0) * repeat
#        #tvalue -= (ord(code[1]) * 256) + ord(code[2])
#
#    else:
#        # REMSTRUCT2
#        tvalue = GetStructTime(code, 0)
#        repeat = ord(code[26]) & 0x1F
#        tvalue = tvalue + (GetStructTime(code, 26) * repeat)
#    return tvalue * SAMPLE_TIME


def CalcChecksum(data):
    checksum = 0
    for byte in data:
        checksum += ord(byte)
        checksum %= 256
    checksum = (0x100 - checksum) % 256
    return chr(checksum)
    

class HexValidator(wx.PyValidator):
    
    def __init__(self, maxLength=100, allowRaw=False):
        self.maxLength = maxLength
        self.allowRaw = allowRaw
        wx.PyValidator.__init__(self)
        self.Bind(wx.EVT_CHAR, self.OnChar)


    def Clone(self):
        return HexValidator(self.maxLength, self.allowRaw)


    def TransferToWindow(self):
        return True
        
        
    def TransferFromWindow(self):
        return True


    @eg.LogIt
    def Validate(self, win):
        val = win.GetValue()
        for x in val:
            if x not in hexdigits:
                return False
        return True


    def OnChar(self, event):
        key = event.KeyCode

        if key < wx.WXK_SPACE or key == wx.WXK_DELETE or key > 255:
            event.Skip()
            return

        textCtrl = self.GetWindow()
        startPos, endPos = textCtrl.GetSelection()
        length = textCtrl.GetLastPosition() - (endPos - startPos)
        if length >= self.maxLength:
            if not wx.Validator_IsSilent():
                wx.Bell()
            return
        
        if(
            self.allowRaw 
            and textCtrl.GetInsertionPoint() == 0 
            and chr(key).upper() == "R"
        ):
            textCtrl.WriteText("R")
            return 
        
        if chr(key) in hexdigits:
            textCtrl.WriteText(chr(key).upper())
            return

        if not wx.Validator_IsSilent():
            wx.Bell()

        # Returning without calling event.Skip eats the event before it
        # gets to the text control
        return



class UIRT2(eg.IrDecoderPlugin):

    #modify this if necessary... by 7
    __USBIRTOYFWVERSION="V107"
    #__SAMPLINGPERIOD=21.1111
    __SAMPLINGPERIOD=50.0
    
    def __init__(self):
        eg.IrDecoderPlugin.__init__(self, self.__SAMPLINGPERIOD)
        self.buffer = ""
        #self.buffer = []
        self.AddAction(TransmitIR)


    def __start__(self, comport=0):
        serialThread = self.serialThread = eg.SerialThread()
        serialThread.Open(comport, 115200)
        serialThread.Start()
        #serialThread.SetRts()
        self.MyComIrDevice=ComIRDevice(mySerialThread=serialThread)
        #self.MyComIrDevice.ResetMode()

        #print self.MyComIrDevice.GetVersion()
        #print self.MyComIrDevice.GetVersion()
        #print self.MyComIrDevice.GetVersion()
        
        for dummyCounter in range(3):
            sleep(0.05)
            self.MyComIrDevice.ResetMode()
            USBIrToyFWVer=self.MyComIrDevice.GetVersion()
            print "USB IR Toy Version",USBIrToyFWVer
            if(USBIrToyFWVer!=self.__USBIRTOYFWVERSION):
                continue

            print "Entering Sampling Mode"
            if(self.MyComIrDevice.EnterSamplingMode() == False):
                continue
            
            break
##            serialThread.Flush()            
##            serialThread.Write("\x23\xdd") # get version
##            if serialThread.Read(3, 0.2) != "\x01\x04\xFB":
##                continue            
##            serialThread.Write("\x21\xdf") # set RAW mode
##            if serialThread.Read(1, 0.1) != "\x21":
##                continue
            
#break
        else:
            serialThread.Close()
            raise self.Exceptions.InitFailed
        self.buffer = ""
        serialThread.SetReadEventCallback(self.OnReceive)
        self.sendQueue = Queue(50)
        self.alive = True
        Thread(target=self.SendLoop).start()
        print "USB IR Toy Connection Successful!"


    @eg.LogIt
    def __stop__(self):
        self.alive = False
        self.sendQueue.put((StopIteration, None))
        self.serialThread.SuspendReadEvents()
        self.serialThread.Write("\x20\xe0")
        self.serialThread.Close()
        
        
    def __close__(self):
        self.irDecoder.Close()


## This is the data when i press enter on my remote (Orange)
##[422, 210, 26, 26, 26, 25, 27, 25, 26, 26, 26, 25, 27, 25, 26, 26, 26, 26, 27, 78,
## 26, 78, 26, 79, 27, 78, 26, 78, 26, 79, 27, 78, 26, 78, 26, 26, 26, 25, 27, 25, 26,
## 26, 27, 24, 27, 24, 26, 79, 26, 25, 26, 79, 28, 77, 27, 77, 25, 80, 27, 78, 27, 77,
## 27, 25, 27, 77, 27, 1871, 421, 105, 26, 65535]
        

    #@eg.LogIt
    __SCALE=21.33/50.0
    def OnReceive(self, serialThread):
        self.buffer += serialThread.Read(1024)
##        for x in self.buffer:
##            print ("%x ") % (ord(x))
##        return
        while True:
            #terminatorPos = self.buffer.find("\xff")
            terminatorPos = self.buffer.find("\xff\xff")
            #print terminatorPos
            if terminatorPos < 0:
                break
            #data = self.buffer[2:terminatorPos+1]
            #self.buffer = self.buffer[terminatorPos+1:]

            #data = self.buffer[0:terminatorPos+2]
            data=""
            ctr=0

            #convert the 16bit data to 8 bit data            
            while(ctr<terminatorPos):
                x=(ord(self.buffer[ctr]))<<8
                y=ord(self.buffer[ctr+1])
                #print ("%x ") % (x+y)
                tempInt=(int)((x+y)*(self.__SCALE))
                data+=chr(tempInt&0xFF)
                ctr+=2                
            
            self.buffer = self.buffer[terminatorPos+2:]
            
            if len(data) < 2:
                continue
            strtemp=""
            print "IR Data Received!"

            for x in data:
                strtemp+=("0x%x ") % (ord(x))    
                #print ("%x ") % (ord(x))
            print strtemp
            self.irDecoder.Decode(data, len(data))

            self.buffer = '' # empty buffer TODO:Temporary buffer emptying
        
        
    @eg.LogItWithReturn
    def SendLoop(self):
        while self.alive:
            code, event = self.sendQueue.get()
            if code == StopIteration:
                return
            with self.serialThread as serial:
                serial.Write(code)
                sleep(0.05)

                USBIrToyFWVer=self.MyComIrDevice.GetVersion()
                print "USB IR Toy Version",USBIrToyFWVer
                
                data = serial.Read(1)
                if data != " ":
                    self.PrintError("Error sending IR code to UIRT2")
                data = ""
                startTime = clock()
                while data != "\x21":
                    if (clock() - startTime) > 5.0:
                        self.PrintError("Transmitting timed out")
                        break
                    serial.Write("\x21\xdf")
                    sleep(0.05)
                    data = serial.Read(1)
            event.set()
            
    
    def Configure(self, comport=0):
        panel = eg.ConfigPanel()
        portCtrl = panel.SerialPortChoice(comport)
        panel.AddLine("COM-Port:", portCtrl)
        while panel.Affirmed():
            panel.SetResult(portCtrl.GetValue())
    
    
    
class TransmitIR(eg.ActionBase):
    name = "Transmit IR"
    
    def __call__(self, code, waitUntilFinished=True):
        finishEvent = Event()
        try:
            self.plugin.sendQueue.put((code, finishEvent), False)
        except Full:
            self.PrintError("Too many transmissions pending")
            return
        if waitUntilFinished:
            finishEvent.wait(10.0)
                        

    def GetLabel(self, *dummyArgs):
        return self.name
    
    
    def Configure(self, code="", waitUntilFinished=True):
        panel = eg.ConfigPanel()
        code1 = ""
        code2 = ""
        repeatCount = 4
        carrier = 0
        if code:
            code += (48 * "\x00") 
            if code[0] == "\x36":
                length = ord(code[1])
                code1 = "R" + hexlify(code[2:length]).upper()
                repeatCount = ord(code[length]) & 0x1F
                carrier = ord(code[length]) >> 6
            else:
                repeatCount = ord(code[0]) & 0x1F
                if repeatCount > 0:
                    carrier = ord(code[0]) >> 6
                    code1 = hexlify(code[1:26]).upper()
                else:
                    repeatCount = ord(code[26]) & 0x1F
                    carrier = ord(code[0]) >> 6
                    code1 = hexlify(code[1:26]).upper()
                    code2 = hexlify(code[27:48]).upper()
        if carrier < 0:
            carrier = 0
        elif carrier > 3:
            carrier = 3
        if repeatCount < 1:
            repeatCount = 1
        elif repeatCount > 31:
            repeatCount = 31
        sizer = wx.FlexGridSizer(4, 2, 5, 5)
        sizer.AddGrowableCol(1)
        
        sizer.Add(panel.StaticText("Code 1:"), 0, wx.ALIGN_CENTER_VERTICAL)
        code1Ctrl = panel.TextCtrl(
            code1, 
            size=(325, -1),
            validator=HexValidator(allowRaw=True),
        )
        sizer.Add(code1Ctrl)
        
        sizer.Add(panel.StaticText("Code 2:"), 0, wx.ALIGN_CENTER_VERTICAL)
        code2Ctrl = panel.TextCtrl(
            code2, 
            size=(275, -1), 
            validator=HexValidator()
        )
        sizer.Add(code2Ctrl)
        
        sizer.Add(panel.StaticText("Repeat:"), 0, wx.ALIGN_CENTER_VERTICAL)
        repeatCtrl = eg.SpinIntCtrl(panel, -1, repeatCount, 1, 31)
        repeatCtrl.SetInitialSize((50, -1))
        sizer.Add(repeatCtrl, 0)
        
        sizer.Add(panel.StaticText("Carrier:"), 0, wx.ALIGN_CENTER_VERTICAL)
        choices = ('35.7 kHz', '37.0 kHz', '38.4 kHz', '40.0 kHz')
        carrierCtrl = wx.Choice(panel, -1, choices=choices)
        carrierCtrl.SetSelection(3 - carrier)
        sizer.Add(carrierCtrl, 0)
                    
        panel.sizer.Add(sizer, 0, wx.EXPAND)
        
        panel.sizer.Add((5, 5))
        waitUntilFinishedCtrl = panel.CheckBox(
            waitUntilFinished, 
            "Pause till transmission is finished"
        )
        panel.sizer.Add(waitUntilFinishedCtrl)

        while panel.Affirmed():
            code1 = code1Ctrl.GetValue()
            if len(code1) == 0:
                panel.SetResult("", waitUntilFinishedCtrl.GetValue())
                continue
            code2 = code2Ctrl.GetValue()
            repeatCount = repeatCtrl.GetValue()
            carrier = 3 - carrierCtrl.GetSelection()
            if code1[0] == "R":
                data = unhexlify(code1[1:])
                bCmd = repeatCount | (carrier << 6)
                code = "\x36" + chr(len(data) + 2) + data + chr(bCmd)
            elif len(code2) == 0:
                data = unhexlify(code1)
                bCmd = repeatCount | (carrier << 6)
                code = chr(bCmd) + data
            else:
                bCmd = 0 | (carrier << 6)
                bCmd2 = repeatCount | (carrier << 6)
                code = chr(bCmd) + unhexlify(code1) \
                       + chr(bCmd2) + unhexlify(code2)
            panel.SetResult(
                code + CalcChecksum(code), 
                waitUntilFinishedCtrl.GetValue()
            )




##    #@eg.LogIt
##    def OnReceive(self, serialThread):
##        self.buffer += serialThread.Read(1024)
####        for x in self.buffer:
####            print ("%x ") % (ord(x))
####        return
##        while True:
##            #terminatorPos = self.buffer.find("\xff")
##            terminatorPos = self.buffer.find("\xff\xff")
##            #print terminatorPos
##            if terminatorPos < 0:
##                break
##            #data = self.buffer[2:terminatorPos+1]
##            #self.buffer = self.buffer[terminatorPos+1:]
##
##            data = self.buffer[0:terminatorPos+2]
##            self.buffer = self.buffer[terminatorPos+2:]
##            
##            if len(data) < 2:
##                continue
##            strtemp=""
##            print "IR Data Received!"
##            for x in data:
##                strtemp+=("0x%x ") % (ord(x))    
##                #print ("%x ") % (ord(x))
##            print strtemp
##            self.irDecoder.Decode(data, len(data))
