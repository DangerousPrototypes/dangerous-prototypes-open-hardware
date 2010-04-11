using System;
using System.Collections.Generic;
using System.Text;
using System.IO.Ports;
using System.Threading;

namespace Sevenstring.HWInterface
{
    public class PIC24Program
    {
        BusPirate myBusPirate;

        public const uint SECURE_ID_ENHANCED_ICSP = 0x4D434850;
        public const uint SECURE_ID_NORMAL_ICSP = 0x4D434851;

        // PEC= Programming executive command
        public const ushort PEC_READC=0x01;


        public BusPirate BusPirate
        {
        get {return myBusPirate;}
        }


        public PIC24Program(BusPirate busPirate)
        {
        myBusPirate=busPirate;
        }


        public void Open()
        {
        myBusPirate.Open();
        }


        public void Close(bool Dispose)
        {
        myBusPirate.Close(Dispose);
        }


        public bool EnterICSPMode(uint SecureID)
        {
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
        Thread.Sleep(10); // P19 1ms
        MCLRHigh();
        Thread.Sleep(30); // P7 25ms
        return true;
        }


        public bool ExitICSPMode()
        {
        return MCLRLow();
        }

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




        public void SendSixSerialExec(bool InitialRun,uint Data)
        {
        int ctr;
        DataLow();
        for(ctr=0;ctr<4;ctr++)
            {
            ClockHigh();
            ClockLow();
            }
#if N_COMP
            // 5 byte
            for(ctr=0;ctr<5;ctr++)
                {
                //if( (Data1&(1<<ctr)) !=0)
                //    DataHigh();
                //else
                //    DataLow();
                ClockHigh();
                ClockLow();
                }
#endif

        if(InitialRun)
            {
            // 5 byte
            for(ctr=0;ctr<5;ctr++)
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
        }
        



        public uint SendRegOut()
        {
        uint Result=0;
        int ctr;


        DataHigh();
        ClockHigh();
        ClockLow();

        DataLow();
        for(ctr=0;ctr<7;ctr++)
            {
            ClockHigh();
            ClockLow();
            }

        for(ctr=0;ctr<24;ctr++)
            {
            ClockHigh();

            if(myBusPirate.BusPirateRawWire.PeekAtInputPin()==true)
                Result|=(1U<<ctr);

            ClockLow();
            }
        return Result;
        }




#region Pin Manipulations

        public bool MCLRLow()
        {
        //return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.CS,BusPirateRawWire.PinState.Hi);
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.CS,BusPirateRawWire.PinState.Lo);
        }

        public bool MCLRHigh()
        {
        //return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.CS,BusPirateRawWire.PinState.Lo);
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.CS,BusPirateRawWire.PinState.Hi);
        }

        private bool ClockLow()
        {
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.Clock,BusPirateRawWire.PinState.Lo);
        }

        private bool ClockHigh()
        {
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.Clock,BusPirateRawWire.PinState.Hi);
        }

        private bool DataLow()
        {
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.Data,BusPirateRawWire.PinState.Lo);
        }

        private bool DataHigh()
        {
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.Data,BusPirateRawWire.PinState.Hi);
        }

#endregion


        public uint [] ReadCodeMem(uint Address)
        {
        uint [] MyReturn=new uint[3];
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
        MyReturn[0]=SendRegOut();
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0xBADBB6);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0xBAD3D6);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0);
        MyReturn[1]=SendRegOut();
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0xBA0BB6);
        SendSixSerialExec(false,0);
        SendSixSerialExec(false,0);
        MyReturn[2]=SendRegOut();
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

    }
}
