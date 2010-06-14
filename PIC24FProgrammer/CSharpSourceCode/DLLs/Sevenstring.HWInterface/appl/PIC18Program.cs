using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace Sevenstring.HWInterface
{
    public class PIC18Program:PICProgrammer
    {

        
        public const uint ICSP_CODE= 0x4D434850;

        BusPirate myBusPirate;

        public BusPirate BusPirate
        {
        get {return myBusPirate;}
        }



        public PIC18Program(BusPirate busPirate):base(busPirate)
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



        public bool EnterICSPMode()
        {
        return base.EnterICSPMode(ICSP_CODE,0,0);
        }



        public bool DelayOn4thClk(int Delay)
        {
        if(myBusPirate.BusPirateRawWire.SendFlexibleBitTransferMSBFirst(3,0)==false) return false;
        base.ClockHigh();
        Thread.Sleep(Delay);
        base.ClockLow();
        return true;
        }

        public bool Send4bitLSBThen16bitLSB(byte Cmd,uint Data)
        {
        if (base.Send4BitCommandLSBFirst(Cmd)==false) return false;
        base.Send16BitLSBFirst(Data);
        return true;
        }



#if N_COMP
        public bool DelayOn4thClk(int Delay)
        {
        if (base.ClockHigh()==false) return false;
        base.ClockLow();

        base.ClockHigh();
        base.ClockLow();

        base.ClockHigh();
        base.ClockLow();

        base.ClockHigh();
        Thread.Sleep(Delay);
        base.ClockLow();

        return true;
        }
#endif


#if N_COMP
        public bool Send4BitCommandLSBFirst(byte Cmd)
        {
        if(ClockLow()==false) return false;
        //int ctr=3;

        for(int ctr=0;ctr<4;ctr++)
            {
            if((Cmd&(1<<ctr))!=0)
                DataHigh();
            else
                DataLow();
            ClockHigh();
            ClockLow();
            }
        return true;

#if N_COMP
        if(ClockLow()==false) return false;
        int ctr=3;

        do
            {
            if((Cmd&(1U<<ctr))!=0)
                DataHigh();
            else
                DataLow();
            ClockHigh();
            ClockLow();
            ctr--;
            }while(ctr!=-1);
        return true;
#endif
        }
#endif



#if N_COMP
        public bool Send16BitDataLSBFirst(uint Data)
        {
        return base.Send16BitLSBFirst(Data);
#if N_COMP
        if(ClockLow()==false) return false;

        for(int ctr=0;ctr<16;ctr++)
            {
            if( (Data&(1U<<ctr)) !=0)
                DataHigh();
            else
                DataLow();
            ClockHigh();
            ClockLow();
            }

        return true;
#endif
        }
#endif


#if N_COMP
        public bool ExitICSPMode()
        {
        return MCLRLow();
        }
#endif



    }
}
