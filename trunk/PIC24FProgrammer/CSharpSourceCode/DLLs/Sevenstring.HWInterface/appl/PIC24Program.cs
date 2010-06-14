using System;
using System.Collections.Generic;
using System.Text;
using System.IO.Ports;
using System.Threading;

namespace Sevenstring.HWInterface
{
    public class PIC24Program:PICProgrammer
    {
        BusPirate myBusPirate;

        public const uint SECURE_ID_ENHANCED_ICSP = 0x4D434850;
        public const uint SECURE_ID_NORMAL_ICSP = 0x4D434851;



        public BusPirate BusPirate
        {
        get {return myBusPirate;}
        }


        public PIC24Program(BusPirate busPirate):base(busPirate)
        {
        myBusPirate=busPirate;
        }

#if N_COMP
        public void Open()
        {
        myBusPirate.Open();
        }


        public void Close(bool Dispose)
        {
        myBusPirate.Close(Dispose);
        }
#endif

        public bool EnterICSPMode(uint SecureID)
        {
        return base.EnterICSPMode(SecureID,5,30);
#if N_COMP
        //uint secureID = SecureID;
        int ctr;

        if(ClockLow()==false) return false;
        DataLow();
        MCLRLow();
        MCLRHigh();
        MCLRLow();
   
        ctr=31;
        do
	        {
            if((SecureID& (1<<ctr))!=0)
                DataHigh();
            else
                DataLow();

            ClockHigh();
            ClockLow();
            ctr--;
	        } while (ctr!=-1);

        DataLow();
        Thread.Sleep(5); // P19 1ms
        MCLRHigh();
        Thread.Sleep(30); // P7 25ms
        return true;
#endif
        }

#if N_COMP
        public bool ExitICSPMode()
        {
        return base.ExitICSPMode();
        }
#endif

#if N_COMP
        public void Send16BitCommand(uint Data)
        {
        //MSB first
        int ctr=15;
        do
            {
            if( (Data&(1U<<ctr))!=0)
                DataHigh();
            else
                DataLow();

            if (ClockHigh()==false) return;
            ClockLow();
            }while(ctr!=-1);
        }




        public uint Read16BitCommamd()
        {
        //MSB first
        uint Result=0;
        int ctr=15;
        do
            {
            if(ClockHigh()==false) return 0xABCD;
            if(myBusPirate.BusPirateRawWire.PeekAtInputPin()==true)
                Result|=(1U<<ctr);
            ClockLow();
            }while(ctr!=-1);
        return Result;
        }
#endif


        public bool SendSixSerialExecAfterRegout(uint Data)
        {
        int ctr;
        if(DataLow()==false) return false;

        ClockHigh();
        ClockLow();

        DataHigh();
        ClockHigh();
        ClockLow();
        DataLow();

        ClockHigh();
        ClockLow();

        ClockHigh();
        ClockLow();

        // 24 byte
        for(ctr=0;ctr<24;ctr++)
            {
            if( (Data&(1U<<ctr)) !=0)
                DataHigh();
            else
                DataLow();
            ClockHigh();
            ClockLow();
            }
        return true;
        }




        public bool SendSixSerialExec(bool SendSixCommand, bool InitialRun,uint Data)
        {
        int ctr;
        if(DataLow()==false) return false;

        if(InitialRun)
            {
            // 5 byte
            for(ctr=0;ctr<5;ctr++)
                {
                ClockHigh();
                ClockLow();
                }
            }

        if(SendSixCommand)
            {
            for(ctr=0;ctr<4;ctr++)
                {
                ClockHigh();
                ClockLow();
                }
            }
        // 24 byte
        for(ctr=0;ctr<24;ctr++)
            {
            if( (Data&(1U<<ctr)) !=0)
                DataHigh();
            else
                DataLow();
            ClockHigh();
            ClockLow();
            }
        return true;
        }
        



        public uint? ReadRegOut()
        {
        uint? Result=0;
        int ctr;

        if(DataHigh()==false)return null;
        ClockHigh();
        ClockLow();

        DataLow();

        //for(ctr=0;ctr<7;ctr++)
        for(ctr=0;ctr<11;ctr++)
            {
            ClockHigh();
            ClockLow();
            }

        //for(ctr=0;ctr<24;ctr++)
        for(ctr=0;ctr<16;ctr++)
            {
            ClockHigh();

            if(myBusPirate.BusPirateRawWire.PeekAtInputPin()==true)
                Result|=(1U<<ctr);
            ClockLow();
            }
        return Result;
        }



#if N_COMP


        public void EraseChip()
        {
        this.EnterICSPMode(PIC24Program.SECURE_ID_NORMAL_ICSP);
        this.SendSixSerialExec(true,true,0x040200);

        this.SendSixSerialExec(true,false,0x040200);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);

        this.SendSixSerialExec(true,false,0x040200);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0x2404FA);
        this.SendSixSerialExec(true,false,0x883B0A);

        this.SendSixSerialExec(true,false,0xA8E761);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);


        this.SendSixSerialExec(true,false,0xA9E761);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);

        this.ExitICSPMode();
        }


        public uint ? ReadDevID()
        {
        uint ? ReturnData=0;
        this.EnterICSPMode(PIC24Program.SECURE_ID_NORMAL_ICSP);
        this.SendSixSerialExec(true,true,0x040200);

        this.SendSixSerialExec(true,false,0x040200);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);

        this.SendSixSerialExec(true,false,0x040200);
        this.SendSixSerialExec(true,false,0);

        this.SendSixSerialExec(true,false,0x200FF0);
        this.SendSixSerialExec(true,false,0x880190);
        this.SendSixSerialExec(true,false,0x200006);

        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);

        this.SendSixSerialExec(true,false,0x200007);
        this.SendSixSerialExec(true,false,0xBA0BB6);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);

        this.SendSixSerialExec(true,false,0x883C20);
        this.SendSixSerialExec(true,false,0);

        ReturnData=this.ReadRegOut();
        this.SendSixSerialExec(true,false,0);

        this.SendSixSerialExecAfterRegout(0);
        this.SendSixSerialExec(true,false,0);
        this.SendSixSerialExec(true,false,0);

        return ReturnData;
        }
#endif








#if N_COMP
        public uint? [] ReadCodeMem(uint Address)
        {
        uint? [] MyReturn=new uint?[3];
        uint temp;
        SendSixSerialExec(false,0);//nop
        SendSixSerialExec(false,0x040200);
        SendSixSerialExec(false,0);//nop

        temp=(Address>>16)&0xFF;
        SendSixSerialExec(false,0x200000 | (temp<<4));
        SendSixSerialExec(false,0x880190);
        temp=Address&0xFFFF;
        SendSixSerialExec(false,0x200006 | (temp<<4));

        SendSixSerialExec(false,0x207847);
        SendSixSerialExec(false,0);

        SendSixSerialExec(false,0xBA0B96);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0);
        MyReturn[0]=ReadRegOut();
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0xBADBB6);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0xBAD3D6);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0);
        MyReturn[1]=ReadRegOut();
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0xBA0BB6);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0);
        MyReturn[2]=ReadRegOut();
        SendSixSerialExec(false,0);

        SendSixSerialExec(false,0x040200);
        SendSixSerialExec(false,0);
        return MyReturn;
        }



        public void EraseChip()
        {
        SendSixSerialExec(false,0);
        //SendSixSerialExec(false,0);
        SendSixSerialExec(false,0x040200);
        SendSixSerialExec(false,0);

        SendSixSerialExec(false,0x2404FA);
        SendSixSerialExec(false,0x883B0A);

        SendSixSerialExec(false,0x200000);
        SendSixSerialExec(false,0x880190);
        SendSixSerialExec(false,0x200000);
        SendSixSerialExec(false,0xBB0800);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0);

        SendSixSerialExec(false,0xA8E761);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0);

        System.Threading.Thread.Sleep(2000);

        SendSixSerialExec(false,0x040200);
        SendSixSerialExec(false,0);
        /*
        SendSixSerialExec(false,0x803B02);
        SendSixSerialExec(false,0x883C22);
        SendSixSerialExec(false,0);
        System.Threading.Thread.Sleep(2000);
        SendSixSerialExec(false,0);
        */

        }
#endif

    }
}
