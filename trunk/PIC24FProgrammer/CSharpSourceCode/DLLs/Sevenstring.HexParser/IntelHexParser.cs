using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace Sevenstring.HexParser
{
    public class IntelHexParser
    {
        string FileName;

        public struct HexAddressData
        {
            public uint Address;
            public byte[] Data;
        };

        
        public IntelHexParser(string FileName)
        {
        if(!File.Exists(FileName)) 
            throw new ApplicationException("File Not Found!");
        this.FileName = FileName;
        }




#if N_COMP
        public Dictionary<uint,byte[]> GetAddressAndDataDictionary(HexAddressData[] myHexAddDataArray)
        {
        Dictionary<uint,byte[]> myDictionary=new Dictionary<uint,byte[]>();
        foreach(HexAddressData x in myHexAddDataArray)
            {
            myDictionary.Add(x.Address,x.Data);
            }
        return myDictionary;
        }
#endif


        public byte[] PrepareHexDataToArray(int ArraySize)
        {
        byte [] MyArray=new byte[ArraySize];
        for(int ctr=0;ctr<ArraySize;ctr++)
            MyArray[ctr]=0xFF;

        foreach(HexAddressData had in this.GetAddressAndData())
            {
            for(uint ctr=0;ctr<had.Data.Length;ctr++)
                MyArray[had.Address+ctr]=had.Data[ctr];
            }

        return MyArray;
        }



        private HexAddressData [] GetAddressAndData()
        {
        List <HexAddressData> retAddressData=new List<HexAddressData>();

        string [] strList = File.ReadAllLines(FileName);

        foreach(string x in strList)
            {
            string temp=x.Trim();
            if(temp.Substring(7,2)=="00")
                {
                HexAddressData hexAddData=new HexAddressData();

                // Extract Address
                hexAddData.Address=Convert.ToUInt32(temp.Substring(3,4),16);

                // Extract Data
                List<byte> dataBytes= new List<byte>();
                temp=temp.Substring(9);
                temp=temp.Substring(0,temp.Length-2);
                int ctr=0;
                while(ctr < temp.Length)
                    {
                    dataBytes.Add(Convert.ToByte(temp.Substring(ctr,2),16));
                    ctr+=2;
                    }
                hexAddData.Data=dataBytes.ToArray();

                retAddressData.Add(hexAddData);
                }
            
            }
        return retAddressData.ToArray();
        }


        public bool CheckIfConsecutiveByteExist(HexAddressData [] hexAddData,byte Data,int listCount, int offset)
        {
        for(int ctr=offset;ctr<(offset+listCount);ctr++)
            {
            foreach(byte x in hexAddData[ctr].Data)
                {
                if(x!=Data)
                    return false;
                }
            }
        return true;
        }

    }
}
