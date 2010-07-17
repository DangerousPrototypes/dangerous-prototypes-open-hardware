#Boa:Dialog:DialogComPort

import wx

def create(parent):
    return DialogComPort(parent)

[wxID_DIALOGCOMPORT, wxID_DIALOGCOMPORTBTNOK, wxID_DIALOGCOMPORTCHOICEBAUD, 
 wxID_DIALOGCOMPORTCHOICECOMPORT, wxID_DIALOGCOMPORTPANEL1, 
 wxID_DIALOGCOMPORTSTATICTEXT1, wxID_DIALOGCOMPORTSTATICTEXT2, 
] = [wx.NewId() for _init_ctrls in range(7)]

class DialogComPort(wx.Dialog):
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Dialog.__init__(self, id=wxID_DIALOGCOMPORT, name='DialogComPort',
              parent=prnt, pos=wx.Point(691, 250), size=wx.Size(248, 158),
              style=wx.STATIC_BORDER | wx.DEFAULT_DIALOG_STYLE,
              title='Com Port Setting')
        self.SetClientSize(wx.Size(240, 124))

        self.panel1 = wx.Panel(id=wxID_DIALOGCOMPORTPANEL1, name='panel1',
              parent=self, pos=wx.Point(8, 8), size=wx.Size(224, 104),
              style=wx.TAB_TRAVERSAL)
        self.panel1.SetBackgroundColour(wx.Colour(192, 192, 192))

        self.choiceComPort = wx.Choice(choices=[],
              id=wxID_DIALOGCOMPORTCHOICECOMPORT, name='choiceComPort',
              parent=self.panel1, pos=wx.Point(88, 11), size=wx.Size(130, 21),
              style=0)

        self.staticText1 = wx.StaticText(id=wxID_DIALOGCOMPORTSTATICTEXT1,
              label='COM Number:', name='staticText1', parent=self.panel1,
              pos=wx.Point(8, 16), size=wx.Size(68, 13), style=0)

        self.choiceBaud = wx.Choice(choices=[], id=wxID_DIALOGCOMPORTCHOICEBAUD,
              name='choiceBaud', parent=self.panel1, pos=wx.Point(88, 43),
              size=wx.Size(130, 21), style=0)

        self.staticText2 = wx.StaticText(id=wxID_DIALOGCOMPORTSTATICTEXT2,
              label='Baud Rate:', name='staticText2', parent=self.panel1,
              pos=wx.Point(20, 47), size=wx.Size(55, 13), style=0)

        self.btnOk = wx.Button(id=wxID_DIALOGCOMPORTBTNOK, label='Ok',
              name='btnOk', parent=self.panel1, pos=wx.Point(89, 70),
              size=wx.Size(127, 23), style=0)
        self.btnOk.Bind(wx.EVT_BUTTON, self.OnBtnOkButton,
              id=wxID_DIALOGCOMPORTBTNOK)

    def __init__(self, parent):
        self._init_ctrls(parent)
        self.Center()
        self.SetReturnCode(1)
        
        #COM Number
        self.choiceComPort.Clear()
        ComList=[]
        for x in range(0,100):
            ComList.append(str(x))
        self.choiceComPort.SetItems(ComList)
        self.choiceComPort.Select(0)
        
        #COM BaudRate
        self.choiceBaud.Clear()
        BaudRateList=['9600','19200','115200']
        self.choiceBaud.SetItems(BaudRateList)
        self.choiceBaud.Select(0)


    def OnBtnOkButton(self, event):
        self.Baud=self.choiceBaud.GetString(self.choiceBaud.GetSelection())
        self.ComNum=self.choiceComPort.GetString(self.choiceComPort.GetSelection())
        #self.SetReturnCode(0)
        self.EndModal(0)
        #self.Close()
        #dlg=wx.MessageDialog(self, str(g), 'jeff', wx.OK|wx.ICON_INFORMATION)
        #dlg.ShowModal()
        #dlg.Destroy()        
        #event.Skip()



############


