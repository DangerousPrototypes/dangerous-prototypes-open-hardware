using System;
using System.Collections.Generic;
using System.Text;
using System.IO.Ports;

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
        uint secureID = SecureID;
        int ctr;

        if(ClockLow()==false) return false;
        MCLRLow();
        MCLRHigh();
        MCLRLow();
   
        ctr=31;
        do
	        {
            if((secureID& (1<<ctr))!=0)
                DataHigh();
            else
                DataLow();

            ClockHigh();
            ClockLow();
            ctr--;
	        } while (ctr!=-1);

        DataLow();
        MCLRHigh();
        return true;
        }





        public void Send16BitCommamd(uint Data)
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





        public void SendSixSerialExec(uint Data1,uint Data2)
        {
        int ctr;
        DataLow();
        for(ctr=0;ctr<4;ctr++)
            {
            ClockHigh();
            ClockLow();
            }

        // 5 byte
        for(ctr=0;ctr<5;ctr++)
            {
            if( (Data1&(1<<ctr)) !=0)
                DataHigh();
            else
                DataLow();
            ClockHigh();
            ClockLow();
            
            }

        // 24 byte
        for(ctr=0;ctr<24;ctr++)
            {
            if( (Data2&(1<<ctr)) !=0)
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

        private bool MCLRLow()
        {
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.CS,BusPirateRawWire.PinState.Hi);
        }

        private bool MCLRHigh()
        {
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.CS,BusPirateRawWire.PinState.Lo);
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


    }
}
