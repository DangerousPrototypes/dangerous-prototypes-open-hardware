import wx

class IrDraw:
    def __init__(self,MyFrame):
        self.__myFrame=MyFrame
        self.__myFrame.Bind(wx.EVT_PAINT, self.OnPaint)
        
            
    def OnPaint(self, event):
        dc = wx.PaintDC(self.__myFrame)
        x=100
        y=100
        x_offset=30
        y_offset=20
        y_AddToHorizontalLine=40
        
        dc.SetFont(wx.Font(9, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, \
            wx.FONTWEIGHT_BOLD, False, 'Courier 10 Pitch'))
        
        
        ##Draw Upper and Lower Line
        x_guideLine_Offset=960
        y_guideLine_Offset=3
        #lower
        dc.SetPen(wx.Pen('black', 1))
        dc.DrawLine(x, y+y_guideLine_Offset, x+x_guideLine_Offset, y+y_guideLine_Offset)
        dc.SetPen(wx.Pen('blue', 1,wx.DOT))
        #upper
        dc.DrawLine(x, y-y_guideLine_Offset-y_offset, x+x_guideLine_Offset, y-y_guideLine_Offset-y_offset)
        
        lst=0xAAAAAAAA # TODO: put this outside
        IsLogicLow=True
        lstPoints=[wx.Point(x,y)]
        ctr=0
        dc.SetPen(wx.Pen('black', 1,wx.DOT))
        while(ctr<32):
            #draw horizontal line
            dc.DrawLine(x,y,x,y-y_AddToHorizontalLine)
            
            dc.DrawText(str(ctr),x+2,y-40)
            
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
        dc.SetPen(wx.Pen('red', 2))
        dc.DrawLines(lstPoints) 
            
    def DrawHi(self,x,y):
        pass
    
    def DrawLo(self,x,y):
        pass


##########