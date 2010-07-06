import wx

class IrDraw:
    def __init__(self,MyFrame):
        self.__myFrame=MyFrame
        self.__myFrame.Bind(wx.EVT_PAINT, self.OnPaint)
        
            
    def OnPaint(self, event):
        dc = wx.PaintDC(self.__myFrame)
        dc.SetPen(wx.Pen('red', 2))
        x=20
        y=100
        x_offset=30
        y_offset=30
        
        lst=0xAAAAAAAA # TODO: put this outside
        IsLogicLow=True
        lstPoints=[wx.Point(x,y)]
        ctr=0
        while(ctr<32):
            if((lst&(1<<ctr))!=0):
                if(IsLogicLow):
                    lstPoints.append(wx.Point(x,y-y_offset))
                    IsLogicLow=False
                lstPoints.append(wx.Point(x+x_offset,y-y_offset))
            else:
                if(IsLogicLow==False):
                    lstPoints.append(wx.Point(x,y))
                    IsLogicLow=True
                lstPoints.append(wx.Point(x+x_offset,y))
            ctr+=1    
            x+=x_offset
        dc.DrawLines(lstPoints) 
            
    def DrawHi(self,x,y):
        pass
    
    def DrawLo(self,x,y):
        pass


##########