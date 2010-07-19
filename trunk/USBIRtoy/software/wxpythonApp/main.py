#Boa:Frame:Frame1

import wx
import wx.lib.analogclock
import IrDraw
import DialogComPort
import ComIRDevice
import threading

STR_TITLE='IR Decoder 00.08.0 Powered by wxPython'

def create(parent):
    return Frame1(parent)

[wxID_FRAME1, wxID_FRAME1PANEL1, wxID_FRAME1PNLWAVEFORM, 
] = [wx.NewId() for _init_ctrls in range(3)]

class Frame1(wx.Frame):
    
    
    
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_FRAME1, name='', parent=prnt,
              pos=wx.Point(167, 126), size=wx.Size(1080, 803),
              style=wx.DEFAULT_FRAME_STYLE, title='Frame1')
        self.SetClientSize(wx.Size(1072, 769))
        self.SetHelpText('')
        self.SetToolTipString('Frame1')
        self.SetWindowVariant(wx.WINDOW_VARIANT_SMALL)
        self.SetIcon(wx.Icon(u'c:/Dev-Cpp/Icons/Software.ico',
              wx.BITMAP_TYPE_ICO))
        self.SetFont(wx.Font(10, wx.SWISS, wx.NORMAL, wx.NORMAL, False,
              'Tahoma'))

        self.panel1 = wx.Panel(id=wxID_FRAME1PANEL1, name='panel1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(1072, 769),
              style=wx.TAB_TRAVERSAL)

        self.pnlWaveForm = wx.Panel(id=wxID_FRAME1PNLWAVEFORM,
              name='pnlWaveForm', parent=self.panel1, pos=wx.Point(16, 16),
              size=wx.Size(1040, 736), style=wx.TAB_TRAVERSAL)
        self.pnlWaveForm.SetBackgroundColour(wx.Colour(192, 192, 192))

    def __init__(self, parent):
        self._init_ctrls(parent)
        #self.SetFont()
        
        self.__sb=self.CreateStatusBar()
        self.__sb.SetStatusText('Welcome To IR Decoder!')   
        
        self.GenerateMenu()
        
        self.SetLabel(STR_TITLE)
        self.MyIrDraw=IrDraw.IrDraw(self.pnlWaveForm)
        #self.MyIrDraw.SetDataBytesList(range(1,10000))
        self.MyIrDraw.SetDataBytesList([0]*1000)
        #self.MyIrDraw=IrDraw.IrDraw(self.scrollWindowsWaveForm)
        self.WindowStyle
        self.Centre()
        self.SetMaxSize(self.GetSize())
        self.SetMinSize(self.GetSize())
        self.Show(True)
        #self.scrollWindowsWaveForm.SetVirtualSize(wx.Size(1000, 1000))
        #self.scrollWindowsWaveForm.SetScrollbars(20,20,1000,1000)
        
        d=DialogComPort.DialogComPort(self)
        d.ShowModal()
        if(d.ReturnCode==0):
            self.__sb.SetStatusText("COM: %s BaudRate:%sbps" % (d.ComNum,d.Baud))   
            self.__myComIR=ComIRDevice.ComIRDevice(d.ComNum,int(d.Baud))
            d.Destroy()
            #self.MyIrDraw.SetDataBytesList(self.__myComIR.GetData(40*8))
            #threading.Thread(target=self.__WaitForData())
            dlg = wx.MessageDialog(self, 'After pressing ok, this software will wait for bytes of data for 5 sec', 'IR Remote', wx.OK|wx.ICON_INFORMATION)
            dlg.ShowModal()
            dlg.Destroy()
            if(self.__WaitForData()==False):
                dlg = wx.MessageDialog(self, 'No or Less than 500 data bytes received. Exiting...', 'IR Remote', wx.OK|wx.ICON_INFORMATION)
                dlg.ShowModal()
                dlg.Destroy()
                self.Close()
            
            #self.__myComIR.GetData(40*8)
            
            #ser = serial.Serial()
        else:
            self.Close()
        
    def __WaitForData(self):
        #if(self.__myComIR.GetSerialPort().inWaiting()==(40*8)):
        dat=list(self.__myComIR.GetData(500))
        if (len(dat)> (40*8)):
            self.MyIrDraw.SetDataBytesList(dat)
            return True
        return False
        
        
        
##        
##        dlg=wx.MessageDialog(self, str(g), 'Talmud', wx.OK|wx.ICON_INFORMATION)
##        dlg.ShowModal()
##        dlg.Destroy()




        



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
    
if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = create(None)
    frame.Show()

    app.MainLoop()
