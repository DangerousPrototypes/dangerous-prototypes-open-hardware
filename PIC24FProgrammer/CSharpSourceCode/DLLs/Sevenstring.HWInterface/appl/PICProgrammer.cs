using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace Sevenstring.HWInterface
{
    public abstract class PICProgrammer
    {
        BusPirate myBusPirate;

        public PICProgrammer(BusPirate BusPirate)
        {
        myBusPirate=BusPirate;
        }




        protected bool Send8BitMSBFirst(uint Data)
        {
        return myBusPirate.BusPirateRawWire.SendByteBulkTransfer(1,new byte[]{(byte)Data});
#if N_COMP
        int ctr=7;
        do
	        {
            if((Data& (1<<ctr))!=0)
                {if(DataHigh()==false) return false;}
            else
                {if(DataLow()==false) return false;}
            ClockHigh();
            ClockLow();
            ctr--;
	        } while (ctr!=-1);
        return true;
#endif
        }



        public bool Send4BitCommandLSBFirst(byte Cmd)
        {
        //return myBusPirate.BusPirateRawWire.Send4BitTransfer(1,new byte[]{myBusPirate.BusPirateRawWire.RolloverDataByte(Cmd)});
        return myBusPirate.BusPirateRawWire.SendFlexibleBitTransferMSBFirst(4,myBusPirate.BusPirateRawWire.RolloverDataByte(Cmd));
#if N_COMP
        for(int ctr=0;ctr<4;ctr++)
            {
            if((Cmd&(1<<ctr))!=0)
                {if(DataHigh()==false) return false;}
            else
                {if(DataLow()==false) return false;}
            ClockHigh();
            ClockLow();
            }
        return true;
#endif
        }




        public bool Send8BitLSBFirst(uint Data)
        {
        Data=myBusPirate.BusPirateRawWire.RolloverDataByte((byte)Data);
        return myBusPirate.BusPirateRawWire.SendByteBulkTransfer(1,new byte[]{(byte)Data});
#if N_COMP
        for(int ctr=0;ctr<8;ctr++)
            {
            if( (Data&(1U<<ctr)) !=0)
                {if(DataHigh()==false) return false;}
            else
                {if(DataLow()==false) return false;}
            ClockHigh();
            ClockLow();
            }
        return true;
#endif
        }




        public bool Send16BitLSBFirst(uint Data)
        {
        if (Send8BitLSBFirst(Data&0xFF)==false) return false;
        if (Send8BitLSBFirst((Data>>8)&0xFF)==false) return false;
        return true;
        }




        /// <summary>
        /// This returns null if there is an error.
        /// </summary>
        /// <returns></returns>
        public uint? Read8BitLSBFirst()
        {
        uint? Result=0;

        for(int ctr=0;ctr<8;ctr++)
            {
            if(ClockHigh()==false) return null;

            if(myBusPirate.BusPirateRawWire.PeekAtInputPin()==true)
                Result|=(1U<<ctr);
            
            if(ClockLow()==false) return null;
            }
        return Result;
        }





        public bool EnterICSPMode(uint ID,int PosDelayBeforeMCLRHigh,int PosDelayAfterMCLRHigh)
        {
        if(ClockLow()==false) return false;
        DataLow();
        MCLRLow();
        MCLRHigh();
        MCLRLow();
   
        if(myBusPirate.BusPirateRawWire.SendByteBulkTransfer(4,new byte[]{(byte)(ID>>24),(byte)(ID>>16),(byte)(ID>>8),(byte)(ID)})==false)
            return false;

        DataLow();
        Thread.Sleep(PosDelayBeforeMCLRHigh);
        MCLRHigh();
        Thread.Sleep(PosDelayAfterMCLRHigh); 
        return true;
        }





        public bool ExitICSPMode()
        {
        if(MCLRLow()==false) return false;
        return true;
        }
        

        #region Pin Manipulations

        protected bool MCLRLow()
        {
        //return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.CS,BusPirateRawWire.PinState.Hi);
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.CS,BusPirateRawWire.PinState.Lo);
        }

        protected bool MCLRHigh()
        {
        //return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.CS,BusPirateRawWire.PinState.Lo);
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.CS,BusPirateRawWire.PinState.Hi);
        }

        protected bool ClockLow()
        {
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.Clock,BusPirateRawWire.PinState.Lo);
        }

        protected bool ClockHigh()
        {
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.Clock,BusPirateRawWire.PinState.Hi);
        }

        protected bool DataLow()
        {
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.Data,BusPirateRawWire.PinState.Lo);
        }

        protected bool DataHigh()
        {
        return myBusPirate.BusPirateRawWire.SetPortState(BusPirateRawWire.Pins.Data,BusPirateRawWire.PinState.Hi);
        }
#endregion        


    }
}
