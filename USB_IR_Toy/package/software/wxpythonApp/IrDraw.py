import wx
import string

class IrDraw:
    
    #__NUMBITSOVERVIEW=512
    __NUMBITSOVERVIEW=512*2
    #__NUMBITSDETAILED=32
    __NUMBITSDETAILED=16*6
    __InitGraphics=False
    
    
    def GetBitMapSize(self):
        BMP_SZ_FILENAME='bitmap.cfg'
        f=open(BMP_SZ_FILENAME)
        cfg=f.readlines()
        self.BmpSz_X=int(string.strip(cfg[0]))
        self.BmpSz_Y=int(string.strip(cfg[1]))
        f.close()
        
    
    def __init__(self,MyFrame):
        self.GetBitMapSize()
        LIST_SIZE=40
        self.SetScalingFactor(7)
        self.__myFrame=MyFrame
        #self.__myFrame.Bind(wx.EVT_PAINT, self.OnPaint)
        self.__DataToDraw=[0]*(8*LIST_SIZE)
        #self.__DataByteLst=['\xAA']*5000
        
       
        
    def SetDataBytesList(self,DataBytesList):
        self.__DataByteLst=DataBytesList
        self.__myFrame.Refresh()
    
        
    def GetDataBytesList(self):
        #return [0xAA]*(self.__NUMBITSOVERVIEW/8)
        return self.__DataByteLst
        #return range(0,5000)
            
            
            
    def SetScalingFactor(self,scaleFactor):
        self.__scalefac=scaleFactor
    
    def GetScalingFactor(self):
        return float(self.__scalefac)
    
    
    
    
    def GenDrawing(self):
    #def OnPaint(self, event):
        #dc = wx.BufferedPaintDC(self.__myFrame)
        #dc = wx.PaintDC(self.__myFrame)
        #dc = wx.PaintDC(self.__myFrame)
        if(self.__InitGraphics==1):
            self.draw_bmp.Destroy()
            
            
        #self.draw_bmp = wx.EmptyBitmap(10000, 500)
        self.draw_bmp = wx.EmptyBitmap(self.BmpSz_X, self.BmpSz_Y)
        dc=wx.MemoryDC(self.draw_bmp)
        
        #dc=wx.ClientDC(self.__myFrame)
        
        
        #dc=wx.ClientDC(self.__myFrame)
        
        
        broad_x=5
        #broad_y=50
        broad_y=100
        broad_x_offset=1
        #broad_y_offset=20
        broad_y_offset=80
        
        #detailed_x=5
        detailed_x=30
        detailed_y=100
        #detailed_x_offset=32
        detailed_x_offset=10
        detailed_y_offset=20
        
        #NUM_COLUMN_DETAILED_WAVEFORM=10
        #NUM_COLUMN_DETAILED_WAVEFORM=12
        NUM_COLUMN_DETAILED_WAVEFORM=8
        #y_AddToHorizontalLine=40
        
        dc.SetFont(wx.Font(9, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, \
            wx.FONTWEIGHT_BOLD, False, 'Courier 10 Pitch'))
        
        #Broad WaveForm
        self.GenWaveListWaveForm(dc, wx.Pen('CORNFLOWER BLUE', 1),\
            #self.GetNBitListPoints(self.__NUMBITSOVERVIEW,self.GetDataBytesList(),broad_x,broad_y,broad_x_offset,broad_y_offset))
            self.GetNBitListPointsScalingMode(self.GetDataBytesList(),broad_x,broad_y,broad_y_offset,self.GetScalingFactor()))
        
        if(self.__InitGraphics==1):
            self.show_bmp.Destroy()
        
        self.show_bmp = wx.StaticBitmap(self.__myFrame)
        self.show_bmp.SetBitmap(self.draw_bmp)
        
        if(self.__InitGraphics==0):
            self.__InitGraphics=1        
        
        #self.show_bmp.Destroy()
        #dc.Destroy()
        
        #circles_image = self.show_bmp.GetBitmap()
        #circles_image.SaveFile("c:\\mycircles.png", wx.BITMAP_TYPE_PNG)
        
        return
    
        #Draw Horizontal Line
        horizontal_line_x_offset=50
        horizontal_line_y_offset=15
        horizontal_line_x_length=1000
        dc.SetPen(wx.Pen('white',2))
        dc.DrawLine(0,broad_y+horizontal_line_y_offset, \
            broad_x+horizontal_line_x_offset+horizontal_line_x_length,broad_y+horizontal_line_y_offset)
        
        #draw Vertical Lines
        y_AddToVertLine=600
        y_Decrement=5
        dc.SetPen(wx.Pen('VIOLET',1,wx.DOT))
        ctr=0
        while(ctr<(self.__NUMBITSDETAILED+1)):
            x=detailed_x+(ctr*detailed_x_offset)
            dc.DrawLine(x,detailed_y-y_Decrement,x,detailed_y+y_AddToVertLine)
            ctr+=1
                    
        #Detailed WaveForm
        self.DrawMultipleDetailedWaveForms(dc,wx.Pen('WHITE',1),  \
            self.GetDataBytesList(),NUM_COLUMN_DETAILED_WAVEFORM, \
            detailed_x,detailed_y,detailed_x_offset,detailed_y_offset)
            

    def GetNBitListPointsScalingMode(self,DataList,x,y,y_offset,scalingfactor):  
        #lstPoints=[wx.Point(x,y-y_offset)]
        lstPoints=[]
        IsLogicLow=True
        ctr=0
        boolpulse=True
        my_x=x
       
        while(ctr<len(DataList)):
            
            if(boolpulse==True):
                #lstPoints.append(wx.Point(my_x,y-y_offset))
                lstPoints.append(wx.Point(my_x,y-y_offset))
                temp=DataList[ctr]/scalingfactor  
                my_x+=int(temp)
                lstPoints.append(wx.Point(my_x,y-y_offset))
                boolpulse=False
            else:
                lstPoints.append(wx.Point(my_x,y))
                temp=DataList[ctr]/scalingfactor  
                my_x+=int(temp)
                ##                my_x+=DataList[ctr]
                lstPoints.append(wx.Point(my_x,y))
                boolpulse=True
            
##            if((  (DataList[ctr/8])  &(1<<(7-(ctr%8))) )!=0):
##                if(IsLogicLow):
##                    lstPoints.append(wx.Point(x,y-y_offset))
##                    IsLogicLow=False
##                lstPoints.append(wx.Point(x+x_offset,y-y_offset))
##            else:
##                if(IsLogicLow==False):
##                    lstPoints.append(wx.Point(x,y))
##                    IsLogicLow=True
##                lstPoints.append(wx.Point(x+x_offset,y))
            ctr+=1    
            #x+=x_offset  
        ctr=0
        return lstPoints           



    def DrawMultipleDetailedWaveForms(self,dc,pen,lstData,numColumn,detailed_x,detailed_y,detailed_x_offset,detailed_y_offset):
        INDEXINCREMENT=self.__NUMBITSDETAILED/8
        ctr=0
        DETAILED_Y_INCREMENT=50
        while(ctr<numColumn):
            index=ctr*(self.__NUMBITSDETAILED/8)
            self.GenWaveListWaveForm(dc, pen, \
                        self.GetNBitListPoints(self.__NUMBITSDETAILED,lstData[index:(index+INDEXINCREMENT)]  , \
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
            if((  (DataList[ctr/8])  &(1<<(7-(ctr%8))) )!=0):
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

##
##   def GetNBitListPoints(self,NumBits,DataList,x,y,x_offset,y_offset):
##        lstPoints=[wx.Point(x,y)]
##        IsLogicLow=True
##        ctr=0
##       
##        while(ctr<(NumBits)):
##            if((  (DataList[ctr/8])  &(1<<(7-(ctr%8))) )!=0):
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

##        while(ctr<(NumBits)):
##            if((  ord(DataList[ctr/8])  &(1<<(ctr%8)))!=0):
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