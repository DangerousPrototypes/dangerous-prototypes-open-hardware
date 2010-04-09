using System;
using System.Collections.Generic;
using System.Text;
using System.IO.Ports;
using System.Threading;





#if DONTCOMPILE
===============================
Reset (Send 0x00 more than 20 times)!
Sending Data: 0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  
Delay 500 milliseconds...
Reply Received: BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1
===============================
Enter BitBang Mode!
Sending Data: 0x05  
Delay 200 milliseconds...
Reply Received: BBIO1



===============================
Reset (Send 0x00 more than 20 times)!
Sending Data: 0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  
Delay 500 milliseconds...
Reply Received: BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1BBIO1
===============================
Enter BitBang Mode!
Sending Data: 0x05  
Delay 200 milliseconds...
Reply Received: BBIO1




    * 00000000 – Enter raw bitbang mode, reset to raw bitbang mode
    * 00000001 – Mode version string (RAW1)
    * 0000001x – I2C-style start (0) / stop (1) bit
    * 0000010x- CS low (0) / high (1)
    * 00000110 – Read byte
    * 00000111 – Read bit
    * 00001000 – Peek at input pin
    * 00001001 – Clock tick
    * 0000101x – Clock low (0) / high (1)
    * 0000110x – Data low (0) / high (1)
    * 0001xxxx – Bulk transfer, send 1-16 bytes (0=1byte!)
    * 0010xxxx – Bulk clock ticks, send 1-16 ticks
    * 0100wxyz – Configure peripherals, w=power, x=pullups, y=AUX, z=CS
    * 0110000x – Set speed, low (0=~5kHz) / high (1=~50kHz) changed in v4.2
    * 011000xx – Set speed, 3=~400kHz, 2=~100kHz, 1=~50kHz, 0=~5kHz
    * 1000wxyz – Configure mode, w=output type, x=2/3wire, y=msb/lsb, z=n/a
    
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


    * 00000000 – Reset, responds “BBIO1″
    * 00000001  – Enter binary SPI mode, responds “SPI1″
    * 00000010 – Enter binary I2C mode, responds “I2C1″
    * 00000011 – Enter binary UART mode, responds “ART1″
    * 00000100 – Enter binary 1-Wire mode, responds “1W01″
    * 00000101 – Enter binary raw-wire mode, responds “RAW1″
    * 0000xxxx – Reserved for future raw protocol modes
    * 00001111 – Reset Bus Pirate (returns to user terminal)
    * 00010000 – Short binary mode self-test
    * 00010001 – Long test (requires jumpers between +5 and Vpu, +3.3 and ADC)
    
        * 00010010 – Setup pulse-width modulation (requires 5 byte setup)
    * 00010011 – Clear/disable PWM
    * 00010100 – Take voltage probe measurement (returns 2 bytes)
    * 010xxxxx  – Set pins as input(1) or output(0), responds with read
    * 1xxxxxxx  – Set pins high (1) or low (0), responds with read

#endif


namespace Sevenstring.HWInterface
{
    public class BusPirate
    {

#region CONSTANT_VARIABLES

        // BPC - Bus Pirate Command
        public const byte BPC_Reset=0x00;
        public const byte BPC_SpiMode=0x01;
        public const byte BPC_I2cMode=0x02;
        public const byte BPC_UartMode=0x03;
        public const byte BPC_OneWireMode=0x04;
        public const byte BPC_RawWireMode=0x05;
        public const byte BPC_ResetBusPirateToUserTerm=0x0F;
        public const byte BPC_BinModeSelfTest=0x10;
        public const byte BPC_LongTest=0x11;
        public const byte BPC_SetupPwm=0x12;
        public const byte BPC_ClearDisablePWM=0x13;
        public const byte BPC_VoltageMeasurement=0x14;
        public const byte BPC_SetPinTris=0x40;
        public const byte BPC_SetPinPort=0x80;

#endregion




#region INSTANCE_VARIABLES

        SerialPort mySerialPort;
        BusPirateRawWire myBusPirateRawWire=null;

#endregion



        public BusPirate(SerialPort COMPort)
        {
        myBusPirateRawWire=new BusPirateRawWire(this);
        mySerialPort=COMPort;
        }


#region UART_SECTION

        public void SetDefaultSerialParam()  // TODO: temporary
        {
        mySerialPort.BaudRate=115200;
        mySerialPort.DataBits=8;
        mySerialPort.Parity=Parity.None;
        mySerialPort.ReadTimeout=500;
        mySerialPort.ReadBufferSize=20000;
        mySerialPort.WriteBufferSize=20000;
        }


        public void Open()
        {
        SetDefaultSerialParam();
        mySerialPort.Open();
        }


        public void Close(bool Dispose)
        {
        mySerialPort.Close();
        if(Dispose)
            mySerialPort.Dispose();
        }

#endregion




#region PUBLIC_PROPERTIES
        public SerialPort BusPirateSerialPort
        {
        get {return mySerialPort;}
        }

        public BusPirateRawWire BusPirateRawWire
        {
        get {return myBusPirateRawWire;}
        }
#endregion


#region HELPER_FUNCTIONS

        /// <summary>
        /// This checks for the string reply.
        /// </summary>
        internal bool SendUartDataAndCheckReply(byte [] MyDataByte, string StringToCheck, int DelayMsec)
        {
        mySerialPort.DiscardInBuffer();
        mySerialPort.Write(MyDataByte,0,MyDataByte.Length);
        Thread.Sleep(DelayMsec);
            if(mySerialPort.BytesToRead!=0)
                {
                string strTemp=mySerialPort.ReadExisting();
                if(  (strTemp.Length!=0)   &&   (strTemp.Contains(StringToCheck))   )
                    {
                    return true;
                    }
                }
        return false;
        }




        /// <summary>
        /// This checks for the 1 and 0 reply.
        /// </summary>
        internal bool SendUartDataAndCheckReply(byte [] MyDataByte, int DelayMsec) 
        {
        //const int FAILURE=0x00;
        const int SUCCESS=0x01;
        mySerialPort.DiscardInBuffer();
        mySerialPort.ReadTimeout=DelayMsec;
        mySerialPort.Write(MyDataByte,0,MyDataByte.Length);
        try
            {
            if(mySerialPort.ReadByte()==SUCCESS)
                return true;
            }
        catch
            {
            return false;
            }
        return false;
        }

#endregion



#region COMMAND_TRANSACTIONS


        public bool EnterReset()
        {
        const int DELAY=20;
        const int NUMTRIES=25;
        const string STRING_TO_COMPARE="BBIO";

        for(int ctr=0;ctr<NUMTRIES;ctr++)
            {
            if (SendUartDataAndCheckReply(new byte[]{BPC_Reset},STRING_TO_COMPARE,DELAY) == true)
                return true;
            }

        return false;
        }



        public bool EnterRawWireMode()
        {
        const int DELAY=1000;
        const string STRING_TO_COMPARE="RAW1";

        return SendUartDataAndCheckReply(new byte[]{BPC_RawWireMode},STRING_TO_COMPARE ,DELAY);
        }


#endregion

    }
}
