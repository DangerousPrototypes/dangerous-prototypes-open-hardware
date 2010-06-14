using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WindowsFormsApplication1
{
    public class P18_P24Script
    {
        string FileName;

        public enum Commands
        {
            //PIC24
            SIX=0,
            ENTERICSPNORMAL,
            EXITICSP,
            FORCEDSIX,
            REGOUT,
            SIX_AFTER_REGOUT,

            //PIC18
            PIC18ENTERICSP,
            SEND4BITCOMMANDLSBFIRST,
            SEND16BITDATALSBFIRST,
            READ8BITLSBFIRST,
            SEND8BITDATALSBFIRST,
            DELAYCLKON4THBIT
        }



        public struct ScriptData
        {
            public Commands Command;
            public uint HexData;
            public int Delay;
        }



        public P18_P24Script(string FileName)
        {
        this.FileName=FileName;
        }


        public ScriptData[] GetScriptData()
        {
        List<ScriptData> myList=new List<ScriptData>();
        string [] StringArray=File.ReadAllLines(FileName);

        for(int ctr=0;ctr<StringArray.Length;ctr++)
            {
            string temp=StringArray[ctr].Trim();
            if(temp.StartsWith("//")||(temp==String.Empty)) 
                continue; // this is a comment

            string [] splitstr=temp.Split(new char[]{','});
            ScriptData myScriptData= new ScriptData();

            try
                {
                if(splitstr[0].Trim().ToUpper()=="SIX")
                    myScriptData.Command=Commands.SIX;
                else if(splitstr[0].Trim().ToUpper()=="ENTERICSPNORMALMODE")
                    myScriptData.Command=Commands.ENTERICSPNORMAL;
                else if(splitstr[0].Trim().ToUpper()=="FORCEDSIX")
                    myScriptData.Command=Commands.FORCEDSIX;
                else if(splitstr[0].Trim().ToUpper()=="EXIT_ICSP")
                    myScriptData.Command=Commands.EXITICSP;
                else if(splitstr[0].Trim().ToUpper()=="REGOUT")
                    myScriptData.Command=Commands.REGOUT;
                else if(splitstr[0].Trim().ToUpper()=="SIX_AFTER_REGOUT")
                    myScriptData.Command=Commands.SIX_AFTER_REGOUT;

                //PIC18
                else if(splitstr[0].Trim().ToUpper()=="PIC18ENTERICSP")
                    myScriptData.Command=Commands.PIC18ENTERICSP;
                else if(splitstr[0].Trim().ToUpper()=="SEND4BITCOMMANDMSBFIRST") // this must be changed TODO
                    myScriptData.Command=Commands.SEND4BITCOMMANDLSBFIRST;
                else if(splitstr[0].Trim().ToUpper()=="SEND16BITDATALSBFIRST")
                    myScriptData.Command=Commands.SEND16BITDATALSBFIRST;
                else if(splitstr[0].Trim().ToUpper()=="READ8BITLSBFIRST")
                    myScriptData.Command=Commands.READ8BITLSBFIRST;
                else if(splitstr[0].Trim().ToUpper()=="SEND8BITDATALSBFIRST")
                    myScriptData.Command=Commands.SEND8BITDATALSBFIRST;
                else if(splitstr[0].Trim().ToUpper()=="DELAYCLKON4THBIT")
                    myScriptData.Command=Commands.DELAYCLKON4THBIT;
                else
                    throw new ApplicationException();

                myScriptData.HexData=Convert.ToUInt32(splitstr[1].Trim(),16);
                myScriptData.Delay=Convert.ToInt32(splitstr[2].Trim());
                myList.Add(myScriptData);
                }
            catch
                {
                throw new ApplicationException("Error in Line #" + (ctr+1).ToString()  + "!");
                }
            }
        return myList.ToArray();
        }


    }
}


#if N_COMP
test.scrp24
//Sample Script
//Command, Data Byte(in hex),Delay (in msec), comment

ENTERICSPNORMALMODE,0x000000,10, This is for entering ICSP Mode. The Data is not used.  It has a delay of 10msec

FORCEDSIX,0x000000,10, This is forced SIX Command usually sent after entering to ICSP Mode. It sends 0x000000 Data. It has a delay of 10msec

SIX,0x000000,10, This is for SIX Command. It sends 0x000000 Data. It has a delay of 10msec
SIX,0x0000FF,20, This is for SIX Command. It sends 0x0000FF Data. It has a delay of 20msec

REGOUT,0x000000,20, This is for reading. The Data is not used. It has a delay of 20msec

EXIT_ICSP,0x000000,10, This is for exiting ICSP Mode. The Data is not used. It has a delay of 10msec

#endif