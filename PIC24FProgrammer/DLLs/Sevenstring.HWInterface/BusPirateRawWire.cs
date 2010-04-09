using System;
using System.Collections.Generic;
using System.Text;

namespace Sevenstring.HWInterface
{
    public class BusPirateRawWire
    {
        // BPC - Bus Pirate Command
        public const byte BPC_ModeVersionStringRaw1=0x01;
        public const byte BPC_I2CStyleBit=0x02;
        public const byte BPC_ChipSelectPort=0x04;
        public const byte BPC_ReadByte=0x06;
        public const byte BPC_ReadBit=0x07;
        public const byte BPC_PeekAtInputPin=0x08;
        public const byte BPC_ClockTick=0x09;
        public const byte BPC_ClockStatus=0x0A;
        public const byte BPC_DataStatus=0x0C;
        public const byte BPC_BulkTransfer=0x10;
        public const byte BPC_BulkClockTicks=0x20;
        public const byte BPC_PeriphConfig=0x40;
        public const byte BPC_SetSpeed=0x60;
        public const byte BPC_ModeConfig=0x80;
        
        public const byte BPC_SPD_400KHZ=3;
        public const byte BPC_SPD_100KHZ=2;
        public const byte BPC_SPD_50KHZ=1;
        public const byte BPC_SPD_5KHZ=0;
        
        BusPirate myBusPirate;

        
        public enum Pins
        {
        CS=0x00,
        Clock,
        Data
        }
        

        public enum PinState
        {
        Lo=0x00,
        Hi
        }

        internal BusPirateRawWire(BusPirate busPirate)
        {

        myBusPirate=busPirate;
        }


        public bool PeekAtInputPin()
        {
        const int DELAY=100;
        return myBusPirate.SendUartDataAndCheckReply(new byte[] {(byte)(BPC_PeekAtInputPin)} ,DELAY);
        }



        public bool SetPortState(Pins pins,PinState pinState)
        {
        const int DELAY=100;
        bool Status=false;
        byte ByteToBeOred=0;
        if(pinState==PinState.Hi)
            ByteToBeOred=1;


        switch (pins)
            {
            case Pins.CS:
                Status=myBusPirate.SendUartDataAndCheckReply(new byte[] {(byte)(BPC_ChipSelectPort|ByteToBeOred)} ,DELAY);
                break;
            case Pins.Clock:
                Status=myBusPirate.SendUartDataAndCheckReply(new byte[] {(byte)(BPC_ClockStatus|ByteToBeOred)} ,DELAY);
                break;
            case Pins.Data:
                Status=myBusPirate.SendUartDataAndCheckReply(new byte[] {(byte)(BPC_DataStatus|ByteToBeOred)} ,DELAY);
                break;
            default:
                Status=false;
                break;
            }

        return Status;
        }


        
        
        /*
        1000wxyz – Config, w=HiZ/3.3v, x=2/3wire, y=msb/lsb, z=not used

        Configure the raw-wire mode settings. w= pin output type HiZ(0)/3.3v(1). x= protocol wires (0=2, 1=3), toggles between a shared 
        input/output pin (raw2wire), and a separate input pin (raw3wire). y= bit order (0=MSB, 1=LSB). The Bus Pirate responds 0×01 on success.
        */
        public bool SetModeConfig(bool Volt3V3,bool Wires3, bool LSBFirst)
        {
        const int DELAY=100;
        uint ByteToBeOred=0;

        if(Volt3V3)
            ByteToBeOred|=0x08;
        if(Wires3)
            ByteToBeOred|=0x04;
        if(LSBFirst)
            ByteToBeOred|=0x02;


        return myBusPirate.SendUartDataAndCheckReply(new byte[] {(byte)(BPC_ModeConfig|ByteToBeOred)} ,DELAY);
        }



        /*
        0100wxyz – Configure peripherals w=power, x=pullups, y=AUX, z=CS

        Enable (1) and disable (0) Bus Pirate peripherals and pins. Bit w enables the power supplies, 
        bit x toggles the on-board pull-up resistors, y sets the state of the auxiliary pin, and z sets the chip select pin. 
        Features not present in a specific hardware version are ignored. Bus Pirate responds 0×01 on success.

        Note: CS pin always follows the current HiZ pin configuration. AUX is always a normal pin output (0=GND, 1=3.3volts).
        */
        public bool SetPeripheralConfig(bool PowerSupplies,bool PullUps, bool Aux3v3, bool CS)
        {
        const int DELAY=100;
        uint ByteToBeOred=0;

        if(PowerSupplies)
            ByteToBeOred|=0x08;
        if(PullUps)
            ByteToBeOred|=0x04;
        if(Aux3v3)
            ByteToBeOred|=0x02;
        if(CS)
            ByteToBeOred|=0x01;


        return myBusPirate.SendUartDataAndCheckReply(new byte[] {(byte)(BPC_PeriphConfig|ByteToBeOred)} ,DELAY);
        }


    }
}
