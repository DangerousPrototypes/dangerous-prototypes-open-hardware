import wx

class IrDraw:
    
    __NUMBITSOVERVIEW=512
    __NUMBITSDETAILED=32
    
    def __init__(self,MyFrame):
        LIST_SIZE=40
        self.__myFrame=MyFrame
        self.__myFrame.Bind(wx.EVT_PAINT, self.OnPaint)
        self.__DataToDraw=[0]*(8*LIST_SIZE)
        
    def GetDataBytesList(self):
        #return [0xAA]*(self.__NUMBITSOVERVIEW/8)
        return range(0,5000)
            
    def OnPaint(self, event):
        dc = wx.PaintDC(self.__myFrame)
        broad_x=5
        broad_y=50
        broad_x_offset=2
        broad_y_offset=20
        
        detailed_x=5
        detailed_y=100
        detailed_x_offset=32
        detailed_y_offset=20
        
        #NUM_COLUMN_DETAILED_WAVEFORM=10
        NUM_COLUMN_DETAILED_WAVEFORM=12
        #y_AddToHorizontalLine=40
        
        dc.SetFont(wx.Font(9, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, \
            wx.FONTWEIGHT_BOLD, False, 'Courier 10 Pitch'))
        
        #Broad WaveForm
        self.GenWaveListWaveForm(dc, wx.Pen('blue', 1),\
            self.GetNBitListPoints(self.__NUMBITSOVERVIEW,self.GetDataBytesList(),broad_x,broad_y,broad_x_offset,broad_y_offset))
            
        #Draw Horizontal Line
        horizontal_line_x_offset=50
        horizontal_line_y_offset=15
        horizontal_line_x_length=1000
        dc.SetPen(wx.Pen('white',2))
        dc.DrawLine(0,broad_y+horizontal_line_y_offset, \
            broad_x+horizontal_line_x_offset+horizontal_line_x_length,broad_y+horizontal_line_y_offset)
        
        
        #Detailed WaveForm
        self.DrawMultipleDetailedWaveForms(dc,wx.Pen('black',1),  \
            self.GetDataBytesList(),NUM_COLUMN_DETAILED_WAVEFORM, \
            detailed_x,detailed_y,detailed_x_offset,detailed_y_offset)
            
        #draw Vertical Lines
        #y_AddToVertLine=450
        y_AddToVertLine=600
        dc.SetPen(wx.Pen('GREY',1,wx.DOT))
        ctr=0
        while(ctr<(self.__NUMBITSDETAILED+1)):
            x=detailed_x+(ctr*detailed_x_offset)
            dc.DrawLine(x,detailed_y,x,detailed_y+y_AddToVertLine)
            ctr+=1
        

    def DrawMultipleDetailedWaveForms(self,dc,pen,lstData,numColumn,detailed_x,detailed_y,detailed_x_offset,detailed_y_offset):
        ctr=0
        DETAILED_Y_INCREMENT=50
        while(ctr<numColumn):
            index=ctr*(self.__NUMBITSDETAILED/8)
            self.GenWaveListWaveForm(dc, pen, \
                        self.GetNBitListPoints(self.__NUMBITSDETAILED,lstData[index:(index+4)]  , \
                        detailed_x,detailed_y,detailed_x_offset,detailed_y_offset)) 
            ctr+=1 
            detailed_y+=DETAILED_Y_INCREMENT

   
    
    def GenWaveListWaveForm(self,dc,pen,lstDataBytes):
        if(pen!=None):
            dc.SetPen(pen)
        dc.DrawLines(lstDataBytes) 
        

        
    def GetNBitListPoints(self,NumBits,DataList,x,y,x_offset,y_offset):
        lstPoints=[wx.Point(x,y)]
        IsLogicLow=True
        ctr=0
       
        while(ctr<(NumBits)):
            if((DataList[ctr/8]&(1<<(ctr%8)))!=0):
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
        return lstPoints    
    


########## EVERYTHING BELOW WILL BE USED AS SCRATCH



   
##    def DrawNBitPoints(self,NumByte,Data,x,y,x_offset,y_offset):
##        lstPoints=[]
##        IsLogicLow=True
##        ctr=0
##        while(ctr<(NumByte*8)):
##            #draw horizontal line
##            #dc.DrawLine(x,y,x,y-y_AddToHorizontalLine)
##            
##            #dc.DrawText(str(ctr),x+2,y-40)
##            
##            if((Data&(1<<ctr))!=0):
##                if(IsLogicLow):
##                    lstPoints.append(wx.Point(x,y-y_offset))
##                    IsLogicLow=False
##                lstPoints.append(wx.Point(x+x_offset,y-y_offset))
##            else:
##                if(IsLogicLow==False):
##                    lstPoints.append(wx.Point(x,y))
##                    IsLogicLow=True
##                lstPoints.append(wx.Point(x+x_offset,y))
##            ctr+=1    
##            x+=x_offset  
##        return lstPoints 