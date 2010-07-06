#Boa:Frame:Frame1

import wx
import IrDraw

STR_TITLE='IR Decoder 00.08.00'

def create(parent):
    return Frame1(parent)

[wxID_FRAME1, wxID_FRAME1PANEL1, 
] = [wx.NewId() for _init_ctrls in range(2)]

class Frame1(wx.Frame):
    
    
    
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_FRAME1, name='', parent=prnt,
              pos=wx.Point(122, 204), size=wx.Size(1034, 195),
              style=wx.DEFAULT_FRAME_STYLE, title='Frame1')
        self.SetClientSize(wx.Size(1026, 161))

        self.panel1 = wx.Panel(id=wxID_FRAME1PANEL1, name='panel1', parent=self,
              pos=wx.Point(0, 0), size=wx.Size(1026, 161),
              style=wx.TAB_TRAVERSAL)

    def __init__(self, parent):
        self._init_ctrls(parent)
        self.SetLabel(STR_TITLE)
        #self.MyIrDraw=IrDraw.IrDraw(self)
        self.MyIrDraw=IrDraw.IrDraw(self.panel1)
        self.Centre()
        self.Show(True)

if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = create(None)
    frame.Show()

    app.MainLoop()
