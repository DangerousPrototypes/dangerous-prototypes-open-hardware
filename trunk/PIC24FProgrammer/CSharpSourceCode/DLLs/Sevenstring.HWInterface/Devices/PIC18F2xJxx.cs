using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Sevenstring.HexParser;
using System.Windows.Forms;

namespace Sevenstring.HWInterface
{
    public class PIC18F2xJxx:IMCUProgrammable
    {
        PIC18Program myPIC18;

        
        public PIC18F2xJxx(PIC18Program myPIC18)
        {
        this.myPIC18=myPIC18;
        }


        


        public ulong? ReadDeviceID()
        {
        ulong ? Result=null;
        
        if(myPIC18.EnterICSPMode()==false)return null;

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x0E3F);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x6EF8);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x0EFF);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x6EF7);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x0EFE);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x6EF6);

        myPIC18.Send4BitCommandLSBFirst(0x09);
        myPIC18.Send8BitLSBFirst(0);
        Result=myPIC18.Read8BitLSBFirst();

        myPIC18.Send4BitCommandLSBFirst(0x09);
        myPIC18.Send8BitLSBFirst(0);
        Result|=((uint)myPIC18.Read8BitLSBFirst())<<8;
        //Result&=0xFFE0;

        myPIC18.ExitICSPMode();
        return Result;
        }




        public bool Erase()
        {
        if(myPIC18.EnterICSPMode()==false) return false;

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x0E3C);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x6EF8);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x0E00);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x6EF7);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x0E05);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x6EF6);

        myPIC18.Send4BitCommandLSBFirst(0x0C);
        myPIC18.Send16BitLSBFirst(0x0101);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x0E3C);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x6EF8);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x0E00);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x6EF7);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x0E04);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0x6EF6);

        myPIC18.Send4BitCommandLSBFirst(0x0C);
        myPIC18.Send16BitLSBFirst(0x8080);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0);

        myPIC18.Send4BitCommandLSBFirst(0);
        myPIC18.Send16BitLSBFirst(0);
        Thread.Sleep(1000);
        return true;
        }





        public bool Program(string FileName,TextBox myTxtBox)
        {
        
        IntelHexParser myHexParse=new IntelHexParser(FileName);
        byte [] DataFromHexFile=myHexParse.PrepareHexDataToArray(50000);

        byte [] Data=new byte[64];
        StringBuilder sb=new StringBuilder();

        for(int ctr=0;(ctr*64)<0x3F90;ctr++)
            {
            try
                {
                Array.Copy(DataFromHexFile,ctr*64,Data,0,64);
                }
            catch
                {
                return true;
                }
            
            for(int m=0;m<Data.Length;m++) // foreach should do it :)
                {
                if(Data[m]!=0xFF)
                    {
                    sb=new StringBuilder(null);
                    WriteToProgramMemory((uint)(ctr*64),Data,64);
                    sb.AppendFormat("\r\nAddress 0x{0:x} \r\nData:",(ctr*64));
                    for(int i=0;i<64;i++)
                        {
                        sb.AppendFormat("{0:x2} ",Data[i]);
                        }
                    myTxtBox.AppendText(sb.ToString());
                    break;
                    }
                }
            }

        //Write Config Word
        for(int ctr=0;ctr<Data.Length;ctr++)
            Data[ctr]=0xFF;

        Data[56]=DataFromHexFile[0x3FF8];
        Data[57]=DataFromHexFile[0x3FF9];

        Data[58]=DataFromHexFile[0x3FFA];
        Data[59]=DataFromHexFile[0x3FFB];
        
        Data[60]=DataFromHexFile[0x3FFC];
        Data[61]=DataFromHexFile[0x3FFD];

        Data[62]=DataFromHexFile[0x3FFE];
        Data[63]=DataFromHexFile[0x3FFF];


        WriteToProgramMemory(0x3FC0,Data,64);
      
        sb=new StringBuilder(null);
        sb.AppendFormat("\r\nAddress 0x{0:x} \r\nData:",0x3FC0);
        for(int i=0;i<64;i++)
            {
            sb.AppendFormat("{0:x2} ",Data[i]);
            }
        myTxtBox.AppendText(sb.ToString());
        return true;
        }


        /// <summary>
        /// Up to 64 bytes Write
        /// </summary>
        /// <param name="hexAddData"></param>
        /// <param name="offset"></param>
        /// <returns></returns>
        private bool WriteToProgramMemory(uint tblptr,byte[] Data, int length)
        {
        uint DataByte;
        if(myPIC18.EnterICSPMode()==false) return false;

        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x8EA6);
        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x9CA6);
        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x84A6);
        
        // set TBLPTR
        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x0E00 | ((tblptr>>16)&0xFF));
        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x6EF8);
        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x0E00 | ((tblptr>>8)&0xFF));
        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x6EF7);
        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x0E00 | (tblptr&0xFF));
        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x6EF6);

        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x6AA6);
        myPIC18.Send4bitLSBThen16bitLSB(0x00,0x88A6);

        for(int ctr=0;ctr<length-2;ctr+=2)
            {
            DataByte=Data[ctr+1];
            DataByte=DataByte<<8;
            DataByte|=Data[ctr];
            myPIC18.Send4bitLSBThen16bitLSB(0x0D,DataByte);
            }
        DataByte=Data[length-1];
        DataByte=DataByte<<8;
        DataByte|=Data[length-2];
        myPIC18.Send4bitLSBThen16bitLSB(0x0F,DataByte);

        myPIC18.DelayOn4thClk(10);
        myPIC18.Send16BitLSBFirst(0);

        myPIC18.ExitICSPMode();
        return true;
        }
    }
}
