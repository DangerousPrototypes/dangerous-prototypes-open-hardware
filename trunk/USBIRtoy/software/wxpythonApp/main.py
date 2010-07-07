#Boa:Frame:Frame1

import wx
import IrDraw

STR_TITLE='IR Decoder 00.08.01 Powered by wxPython'

def create(parent):
    return Frame1(parent)

[wxID_FRAME1, wxID_FRAME1BUTTON1, wxID_FRAME1CHOICECOMPORT, wxID_FRAME1PANEL1, 
 wxID_FRAME1PANEL2, 
] = [wx.NewId() for _init_ctrls in range(5)]

class Frame1(wx.Frame):
    
    
    
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_FRAME1, name='', parent=prnt,
              pos=wx.Point(97, 455), size=wx.Size(1140, 164),
              style=wx.DEFAULT_FRAME_STYLE, title='Frame1')
        self.SetClientSize(wx.Size(1132, 130))
        self.SetHelpText('')
        self.SetToolTipString('Frame1')
        self.SetWindowVariant(wx.WINDOW_VARIANT_SMALL)
        self.SetIcon(wx.Icon(u'c:/Dev-Cpp/Icons/Software.ico',
              wx.BITMAP_TYPE_ICO))

        self.panel1 = wx.Panel(id=wxID_FRAME1PANEL1, name='panel1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(1132, 130),
              style=wx.TAB_TRAVERSAL)

        self.panel2 = wx.Panel(id=wxID_FRAME1PANEL2, name='panel2',
              parent=self.panel1, pos=wx.Point(24, 8), size=wx.Size(288, 40),
              style=wx.TAB_TRAVERSAL)
        self.panel2.SetBackgroundStyle(wx.BG_STYLE_SYSTEM)
        self.panel2.SetBackgroundColour(wx.Colour(188, 205, 190))

        self.button1 = wx.Button(id=wxID_FRAME1BUTTON1, label='Connect',
              name='button1', parent=self.panel2, pos=wx.Point(16, 8),
              size=wx.Size(120, 24), style=0)
        self.button1.SetFont(wx.Font(10, wx.SWISS, wx.NORMAL, wx.NORMAL, False,
              'Tahoma'))

        self.choiceComPort = wx.Choice(choices=[], id=wxID_FRAME1CHOICECOMPORT,
              name='choiceComPort', parent=self.panel2, pos=wx.Point(152, 8),
              size=wx.Size(125, 24), style=0)
        self.choiceComPort.SetFont(wx.Font(10, wx.SWISS, wx.NORMAL, wx.NORMAL,
              False, 'Tahoma'))

    def __init__(self, parent):
        self._init_ctrls(parent)
        self.SetLabel(STR_TITLE)
        self.MyIrDraw=IrDraw.IrDraw(self.panel1)
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


if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = create(None)
    frame.Show()

    app.MainLoop()
