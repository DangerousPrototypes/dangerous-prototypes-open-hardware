#Boa:Frame:Frame1

import wx
import wx.lib.analogclock
import IrDraw

STR_TITLE='IR Decoder 00.08.01 Powered by wxPython'

def create(parent):
    return Frame1(parent)

[wxID_FRAME1, wxID_FRAME1ANALOGCLOCK1, wxID_FRAME1BUTTON1, 
 wxID_FRAME1CHOICECOMPORT, wxID_FRAME1PANEL1, wxID_FRAME1PNLWAVEFORM, 
 wxID_FRAME1STATICBOX1, 
] = [wx.NewId() for _init_ctrls in range(7)]

class Frame1(wx.Frame):
    
    
    
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_FRAME1, name='', parent=prnt,
              pos=wx.Point(485, 187), size=wx.Size(1080, 698),
              style=wx.DEFAULT_FRAME_STYLE, title='Frame1')
        self.SetClientSize(wx.Size(1072, 664))
        self.SetHelpText('')
        self.SetToolTipString('Frame1')
        self.SetWindowVariant(wx.WINDOW_VARIANT_SMALL)
        self.SetIcon(wx.Icon(u'c:/Dev-Cpp/Icons/Software.ico',
              wx.BITMAP_TYPE_ICO))

        self.panel1 = wx.Panel(id=wxID_FRAME1PANEL1, name='panel1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(1072, 664),
              style=wx.TAB_TRAVERSAL)

        self.staticBox1 = wx.StaticBox(id=wxID_FRAME1STATICBOX1,
              label='COM Port Settings', name='staticBox1', parent=self.panel1,
              pos=wx.Point(16, 8), size=wx.Size(280, 56), style=0)
        self.staticBox1.SetFont(wx.Font(10, wx.SWISS, wx.NORMAL, wx.NORMAL,
              False, 'Tahoma'))

        self.button1 = wx.Button(id=wxID_FRAME1BUTTON1, label='Connect',
              name='button1', parent=self.panel1, pos=wx.Point(32, 32),
              size=wx.Size(120, 24), style=0)
        self.button1.SetFont(wx.Font(10, wx.SWISS, wx.NORMAL, wx.NORMAL, False,
              'Tahoma'))

        self.choiceComPort = wx.Choice(choices=[], id=wxID_FRAME1CHOICECOMPORT,
              name='choiceComPort', parent=self.panel1, pos=wx.Point(160, 32),
              size=wx.Size(125, 24), style=0)
        self.choiceComPort.SetFont(wx.Font(10, wx.SWISS, wx.NORMAL, wx.NORMAL,
              False, 'Tahoma'))

        self.analogClock1 = wx.lib.analogclock.analogclock.AnalogClock(id=wxID_FRAME1ANALOGCLOCK1,
              name='analogClock1', parent=self.panel1, pos=wx.Point(312, 16),
              size=wx.Size(80, 48), style=0)
        self.analogClock1.SetFaceBorderWidth(2)
        self.analogClock1.SetBackgroundColour(wx.Colour(192, 192, 192))

        self.pnlWaveForm = wx.Panel(id=wxID_FRAME1PNLWAVEFORM,
              name='pnlWaveForm', parent=self.panel1, pos=wx.Point(16, 72),
              size=wx.Size(1040, 576), style=wx.TAB_TRAVERSAL)
        self.pnlWaveForm.SetBackgroundColour(wx.Colour(192, 192, 192))

    def __init__(self, parent):
        self._init_ctrls(parent)
        self.SetLabel(STR_TITLE)
        self.MyIrDraw=IrDraw.IrDraw(self.pnlWaveForm)
        #self.MyIrDraw=IrDraw.IrDraw(self.scrollWindowsWaveForm)
        self.WindowStyle
        self.Centre()
        self.SetMaxSize(self.GetSize())
        self.SetMinSize(self.GetSize())
        self.Show(True)
        self.choiceComPort.Clear()
        ComList=[]
        for x in range(1,100):
            ComList.append('COM' + str(x))
        self.choiceComPort.SetItems(ComList)
        #self.choiceComPort.SetItems(['hehe','heherhe'])
        self.choiceComPort.Select(0)
        #self.scrollWindowsWaveForm.SetVirtualSize(wx.Size(1000, 1000))
        #self.scrollWindowsWaveForm.SetScrollbars(20,20,1000,1000)

        

    def OnSliderWaveFormViewCommandScroll(self, event):
        self.choiceComPort.Select(self.sliderWaveFormView.GetValue())
        event.Skip()


if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = create(None)
    frame.Show()

    app.MainLoop()
