#Boa:Frame:Frame1

import wx
import wx.lib.intctrl
import wx.lib.analogclock
import IrDraw
import DialogComPort
import ComIRDevice
import threading,time


STR_TITLE='IR Decoder 00.08.0 Powered by wxPython'

def create(parent):
    return Frame1(parent)

[wxID_FRAME1, wxID_FRAME1BTNSTARTRECORD, wxID_FRAME1BTNSTOPRECORD, 
 wxID_FRAME1INTCTRLSCALE, wxID_FRAME1INTCTRLSTOPVAL, wxID_FRAME1PANEL1, 
 wxID_FRAME1SCRLWNDWAVEFORM, wxID_FRAME1STATICTEXT1, wxID_FRAME1STATICTEXT2, 
 wxID_FRAME1TXTIRDATA, 
] = [wx.NewId() for _init_ctrls in range(10)]

class Frame1(wx.Frame):
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_FRAME1, name='', parent=prnt,
              pos=wx.Point(373, 174), size=wx.Size(1080, 392),
              style=wx.DEFAULT_FRAME_STYLE, title='Frame1')
        self.SetClientSize(wx.Size(1072, 358))
        self.SetHelpText('')
        self.SetToolTipString('Frame1')
        self.SetWindowVariant(wx.WINDOW_VARIANT_SMALL)
        self.SetIcon(wx.Icon(u'c:/Dev-Cpp/Icons/Software.ico',
              wx.BITMAP_TYPE_ICO))
        self.SetFont(wx.Font(10, wx.SWISS, wx.NORMAL, wx.NORMAL, False,
              'Tahoma'))
        self.Bind(wx.EVT_CLOSE, self.OnFrame1Close)

        self.panel1 = wx.Panel(id=wxID_FRAME1PANEL1, name='panel1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(1072, 358),
              style=wx.TAB_TRAVERSAL)

        self.txtIRData = wx.TextCtrl(id=wxID_FRAME1TXTIRDATA, name='txtIRData',
              parent=self.panel1, pos=wx.Point(288, 8), size=wx.Size(768, 64),
              style=wx.VSCROLL | wx.TE_MULTILINE, value='')

        self.btnStartRecord = wx.Button(id=wxID_FRAME1BTNSTARTRECORD,
              label='Record', name='btnStartRecord', parent=self.panel1,
              pos=wx.Point(24, 16), size=wx.Size(75, 32), style=0)
        self.btnStartRecord.SetHelpText('')
        self.btnStartRecord.SetBackgroundColour(wx.Colour(0, 128, 0))
        self.btnStartRecord.Bind(wx.EVT_BUTTON, self.OnBtnStartRecordButton,
              id=wxID_FRAME1BTNSTARTRECORD)

        self.btnStopRecord = wx.Button(id=wxID_FRAME1BTNSTOPRECORD,
              label='Stop', name='btnStopRecord', parent=self.panel1,
              pos=wx.Point(24, 64), size=wx.Size(75, 34), style=0)
        self.btnStopRecord.SetBackgroundColour(wx.Colour(255, 0, 0))
        self.btnStopRecord.Bind(wx.EVT_BUTTON, self.OnBtnStopRecordButton,
              id=wxID_FRAME1BTNSTOPRECORD)

        self.scrlwndWaveForm = wx.ScrolledWindow(id=wxID_FRAME1SCRLWNDWAVEFORM,
              name='scrlwndWaveForm', parent=self.panel1, pos=wx.Point(24, 144),
              size=wx.Size(1032, 168), style=wx.HSCROLL | wx.VSCROLL)
        self.scrlwndWaveForm.SetLabel('scrolledWindow1')
        self.scrlwndWaveForm.SetBackgroundColour(wx.Colour(0, 0, 0))
        self.scrlwndWaveForm.SetTargetWindow(self.scrlwndWaveForm)
        self.scrlwndWaveForm.SetThemeEnabled(True)

        self.intctrlStopVal = wx.lib.intctrl.IntCtrl(allow_long=False,
              allow_none=False, default_color=wx.BLACK,
              id=wxID_FRAME1INTCTRLSTOPVAL, limited=False, max=None, min=None,
              name='intctrlStopVal', oob_color=wx.RED, parent=self.panel1,
              pos=wx.Point(136, 24), size=wx.Size(100, 24), style=0, value=0)

        self.staticText1 = wx.StaticText(id=wxID_FRAME1STATICTEXT1,
              label='Max Timeout (1 to 65535)', name='staticText1',
              parent=self.panel1, pos=wx.Point(112, 8), size=wx.Size(149, 16),
              style=0)

        self.intctrlScale = wx.lib.intctrl.IntCtrl(allow_long=False,
              allow_none=False, default_color=wx.BLACK,
              id=wxID_FRAME1INTCTRLSCALE, limited=False, max=None, min=None,
              name='intctrlScale', oob_color=wx.RED, parent=self.panel1,
              pos=wx.Point(136, 72), size=wx.Size(100, 24), style=0, value=0)

        self.staticText2 = wx.StaticText(id=wxID_FRAME1STATICTEXT2,
              label='Scaling Factor', name='staticText2', parent=self.panel1,
              pos=wx.Point(144, 56), size=wx.Size(81, 16), style=0)

    def __init__(self, parent):
        self._init_ctrls(parent)
        #self.SetFont()
        
        self.__sb=self.CreateStatusBar()
        self.__sb.SetStatusText('Welcome To IR Decoder!')   
        
        self.GenerateMenu()
        
        self.intctrlScale.SetValue(5)
        self.intctrlScale.SetMax(100)
        self.intctrlScale.SetMin(1)
        
        
        self.intctrlStopVal.SetValue(0xFFFF)
        self.intctrlStopVal.SetMax(65535)
        self.intctrlStopVal.SetMin(1)
        
        self.SetLabel(STR_TITLE)
        
        #self.MyIrDraw=IrDraw.IrDraw(self.pnlWaveForm)
        
        self.MyIrDraw=IrDraw.IrDraw(self.scrlwndWaveForm)
        self.MyIrDraw.SetDataBytesList([ord('\x10')]*1000)
        self.MyIrDraw.GenDrawing()
        
        
        self.scrlwndWaveForm.SetScrollbars(1, 1,3000, 0)
        self.scrlwndWaveForm.SetVirtualSize((20000, 500))
        self.scrlwndWaveForm.SetScrollRate(1, 1)
        
        

        
        self.Centre()
        self.SetMaxSize(self.GetSize())
        self.SetMinSize(self.GetSize())
        self.Show(True)
        self.Refresh()
        
        self.btnStopRecord.Enable(False)
        #self.scrollWindowsWaveForm.SetVirtualSize(wx.Size(1000, 1000))
        #self.scrollWindowsWaveForm.SetScrollbars(20,20,1000,1000)
        #return
        d=DialogComPort.DialogComPort(self)
        d.ShowModal()
        if(d.ReturnCode==0):
            self.__myComIR=ComIRDevice.ComIRDevice(d.ComNum,int(d.Baud))
            #self.__myComIR=ComIRDevice.ComIRDevice('COM17',int(d.Baud))
            self.__myComIR.ResetMode()
            #self.__sb.SetStatusText("USB IR Toy: %s at %s BaudRate: %s bps" % (self.__myComIR.GetVersion(),d.ComNum,d.Baud))   
            self.__sb.SetStatusText("USB IR Toy: %s at %s " % (self.__myComIR.GetVersion(),d.ComNum))   
            self.__myComIR.ResetMode()
            d.Destroy()
            self.Refresh()
            #self.MyIrDraw.SetDataBytesList(self.__myComIR.GetData(40*8))
            #threading.Thread(target=self.__WaitForData())
##            dlg = wx.MessageDialog(self, 'After pressing ok, this software will wait for bytes of data for 5 sec', 'IR Remote', wx.OK|wx.ICON_INFORMATION)
##            dlg.ShowModal()
##            dlg.Destroy()
##            if(self.__WaitForData()==False):
##                dlg = wx.MessageDialog(self, 'No or Less than 500 data bytes received. Exiting...', 'IR Remote', wx.OK|wx.ICON_INFORMATION)
##                dlg.ShowModal()
##                dlg.Destroy()
##                self.Close()

        else:
            self.Close()
            self.Destroy()
        
        
##    def __WaitForData(self):
##        #self.__myComIR.GetSerialPort().write('x') # IRIO
##        self.__myComIR.ResetMode()
##        self.__myComIR.GetSerialPort().write('s') # sampling mode
##        #time.sleep(.5)
##        #self.__myComIR.GetSerialPort().flushInput()
##        #self.__myComIR.GetSerialPort().flush()
##        #self.__myComIR.GetSerialPort().flushOutput()
##        UPPERLIMIT=1000
##        dat=self.__myComIR.GetData(UPPERLIMIT)
##        
##        #if (len(dat)> (UPPERLIMIT-5)):
##        if (len(dat)> 1):
##            
##            temp=''
##            for x in dat:
##                temp+= '0x%x  ' % (ord(x))
##            
##            self.txtIRData.SetValue(temp)
##            
##            #self.MyIrDraw.SetDataBytesList(dat)
##            return True
##        return False
        
        



    def GenerateMenu(self):
        ID_QUIT=105
        menubar = wx.MenuBar()
        file = wx.Menu()
        #edit = wx.Menu()
        #help = wx.Menu()
#        file.Append(101, '&Open', 'Open a new document')
#        file.Append(102, '&Save', 'Save the document')
#        file.AppendSeparator()
        quit = wx.MenuItem(file, ID_QUIT, '&Quit\tCtrl+Q', 'Quit the Application')
        file.AppendItem(quit)
        
        wx.EVT_MENU(self,ID_QUIT,self.OnQuit)
        
        
        menubar.Append(file, '&File')
        #menubar.Append(edit, '&Edit')
        #menubar.Append(help, '&Help')    
        self.SetMenuBar(menubar)              

    def OnSliderWaveFormViewCommandScroll(self, event):
        self.choiceComPort.Select(self.sliderWaveFormView.GetValue())
        event.Skip()

    def OnQuit(self, event):
        self.Close()
        
        
    

    def OnBtnStartRecordButton(self, event):
        self.btnStartRecord.Enable(False)
        self.btnStopRecord.Enable(True)
        self.txtIRData.SetValue('')
        if(self.__myComIR.EnterSamplingMode()==True):
            #self.__myComIR.ResetMode()
            #self.__myComIR.GetSerialPort().write('s') # sampling mode
            self.__serrecord=SerialRecorder()
            self.__serrecord.SetCOMIrDevice(self.__myComIR)
            self.__serrecord.Set2ByteLimit(self.intctrlStopVal.GetValue())
            self.__serrecord.SetTxtBox(self.txtIRData)
            self.__serrecord.start()
        else:
            dlg = wx.MessageDialog(self, 'Error going to sampling mode', 'IR Remote', wx.OK|wx.ICON_INFORMATION)
            dlg.ShowModal()
            dlg.Destroy()   
                     
    def StopRecording(self):
        self.btnStartRecord.Enable(True)
        self.__serrecord.StopRecording(True)
        self.txtIRData.SetValue(str(self.__serrecord.GetDataList()))
        if(len(self.__serrecord.GetDataList())>0):
            self.MyIrDraw.SetDataBytesList(self.__serrecord.GetDataList())
            self.MyIrDraw.SetScalingFactor(self.intctrlScale.GetValue())
            self.MyIrDraw.GenDrawing()
            #self.Refresh()
            #self.MyIrDraw.SetDataBytesList([ord('\x00')]*5000)
        self.Refresh()

    def OnBtnStopRecordButton(self, event):
        self.StopRecording()

    def OnFrame1Close(self, event):
        self.__myComIR.GetSerialPort().close()
        self.Close()
        self.Destroy()


class SerialRecorder(threading.Thread):
    
    def SetTxtBox(self,txtbox):
        self.__mytxt=txtbox

    def StopRecording(self,boolStopRecording):
        self.__boolRecording=boolStopRecording
   
    def GetRecodingThreadRunningStatus(self):
        return self.__boolRecording
    
    def SetCOMIrDevice(self,comIRDevice):
        self.__mycomIRDevice=comIRDevice
    
    def Set2ByteLimit(self,ByteLimit):
        self.__bytelimit=ByteLimit
    
    def Get2ByteLimit(self):
        return self.__bytelimit
        
    def run ( self ):
        self.__lstSerialData=[]
        self.StopRecording(False)
        #ctr=0
#        self.__lstSerialData=[12,3]
        while(self.GetRecodingThreadRunningStatus()==False):
            try:
                lstdata=self.__mycomIRDevice.GetSerialPort().read(2)
                intTemp=ord(lstdata[0])<<8
                intTemp|=ord(lstdata[1])
                #if(intTemp>=self.Get2ByteLimit()):
                self.__lstSerialData.append(intTemp)
                if(intTemp>=0xFFFF):
                    self.StopRecording(True)
                #self.__lstSerialData.append(lstdata[1])
            except:
                pass
        self.__mytxt.SetValue("Finished Aquiring Data, Press Stop")  
        #self.__stopmeth()

    def GetDataList(self):
        return self.__lstSerialData
    
    
if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = create(None)
    frame.Show()

    app.MainLoop()
