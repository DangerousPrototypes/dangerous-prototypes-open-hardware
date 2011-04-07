using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using FTD2XX_NET;

namespace USB_LCD_Backback
{
    public partial class FTDI_SPI
    {
        FTDI.FT_STATUS ftStatus = FTDI.FT_STATUS.FT_OK;
 
        const byte TXD = 0; 
        const byte RXD = 1; 
        const byte RTS = 2; 
        const byte CTS = 3; 
        const byte DTR = 4; 
        const byte DSR = 5; 
        const byte DCD = 6; 
        const byte RI  = 7; 

        const byte MOSI  = 0;
        const byte MISO  = 1;
        const byte RCLK  = 2;
        const byte SRCLK = 3;
        const byte CLR   = 4;
        const byte G     = 5;
        const byte BL    = 6;
        const byte FAULT = 7;

        byte MOSImask = (byte)(Math.Pow(2, MOSI));
        byte MISOmask = (byte)(Math.Pow(2, MISO));
        byte RCLKmask = (byte)(Math.Pow(2, RCLK));
        byte SRCLKmask = (byte)(Math.Pow(2, SRCLK));
        byte CLRmask = (byte)(Math.Pow(2, CLR));
        byte Gmask = (byte)(Math.Pow(2, G));
        byte BLmask = (byte)(Math.Pow(2, BL));
        byte FAULTmask = (byte)(Math.Pow(2, FAULT));

        bool BacklightOn = false;     // 2010/10/29 McZ Added BacklightOn flag to control BLmask bit in DefaultMask

 
        static byte DefaultMask = 0;  // default values
        
        static byte FT232Routputs = 0; // outputs

        static FTDI SPI_Device;

        //-------------------------------------------------------------------------------------------------
        public void Initialize_SPI_Constants()
        {
            DefaultMask = (byte)(CLRmask | BLmask);  // default values are CLR and BL+ high all others low.

            FT232Routputs = (byte)(MOSImask | RCLKmask | SRCLKmask | CLRmask | Gmask | BLmask); // set outputs

        }
        //-------------------------------------------------------------------------------------------------
        public FTDI.FT_STATUS InitializeFTDI()
        {
            // Create new instance of the FTDI device class
             SPI_Device= new FTDI();
            uint ftdiDeviceCount = 0;

            int i;

            Initialize_SPI_Constants();

            // Determine the number of FTDI devices connected to the machine
            ftStatus = SPI_Device.GetNumberOfDevices(ref ftdiDeviceCount);

            // Check status
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }

            // If no devices available, return
            if (ftdiDeviceCount == 0)
            {
                ftStatus = FTDI.FT_STATUS.FT_DEVICE_NOT_FOUND;
                return (ftStatus);
            }

            // Allocate storage for device info list
            FTDI.FT_DEVICE_INFO_NODE[] ftdiDeviceList = new FTDI.FT_DEVICE_INFO_NODE[ftdiDeviceCount];

            // Populate our device list
            ftStatus = SPI_Device.GetDeviceList(ftdiDeviceList);

            if (ftStatus == FTDI.FT_STATUS.FT_OK)
            {
                for (i = 0; i < ftdiDeviceCount; i++)
                {
                    //MessageBox.Show("Device Index: " + i.ToString());
                    //MessageBox.Show("Flags: " + String.Format("{0:x}", ftdiDeviceList[i].Flags));
                    //MessageBox.Show("Type: " + ftdiDeviceList[i].Type.ToString());
                    //MessageBox.Show("ID: " + String.Format("{0:x}", ftdiDeviceList[i].ID));
                    //MessageBox.Show("Location ID: " + String.Format("{0:x}", ftdiDeviceList[i].LocId));
                    //MessageBox.Show("Serial Number: " + ftdiDeviceList[i].SerialNumber.ToString());
                    //MessageBox.Show("Description: " + ftdiDeviceList[i].Description.ToString());
                    //MessageBox.Show("");
                }
            }


            // Open first device in our list by serial number
            ftStatus = SPI_Device.OpenBySerialNumber(ftdiDeviceList[0].SerialNumber);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }
            // Set latency timer
            ftStatus = SPI_Device.SetLatency(2);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }

            // Reset the controller
            ftStatus = SPI_Device.SetBitMode(0, 0);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }

            // Set synchronous bit bang mode
            ftStatus = SPI_Device.SetBitMode(FT232Routputs, 4);  // Set device to mode 4 and sets outputs
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }

            // Set baud rate/bit clock settings
            ftStatus = SPI_Device.SetBaudRate(3000000);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }

            presetShiftRegisterOutputs();

            return (ftStatus);
        }

        //-------------------------------------------------------------------------------------------------
        // 2010/10/29 McZ Added BacklightOn flag to control BLmask bit in DefaultMask
        //
        public void makeSPIPacket(uint inData, uint inDataLength, ref byte[] outData, ref uint outDataLength)
        {
            int i, k;
            uint j;

            byte[] packet = new byte[0xFF];
            byte[] sBuffer = new byte[0xFF];


            k = (int)inDataLength - 1;
            j = 0;

            if (BacklightOn)                                                        // test for backlight on
                DefaultMask = (byte)(DefaultMask & (~BLmask));                      // set bit as necessary
            else
                DefaultMask = (byte)(DefaultMask | BLmask);

            packet[j++] = DefaultMask;                                              // start with the Default states     


            for (i = k; i >= 0; i--)                                                // walk through data
            {
                if (((uint)(Math.Pow(2, i)) & inData) > 0)                          // and check for one
                {
                    packet[j++] = (byte)(DefaultMask | MOSImask);                   // set Defaults plus MOSI = 1
                    packet[j++] = (byte)(DefaultMask | MOSImask | SRCLKmask);       // set Defaults plus MOSI = 1 plus SRCLK = 1
                }
                else                                                                // and if zero
                {
                    packet[j++] = (byte)(DefaultMask);                              // set Defaults plus MOSI = 0
                    packet[j++] = (byte)(DefaultMask | SRCLKmask);                  // set Defaults plus SRCLK = 1
                }

            }
            packet[j++] = (byte)(DefaultMask | RCLKmask);                          // set Defaults plus RCLK = 1

            packet[j++] = (byte)(DefaultMask);                                     // set Defaults 

            outDataLength = j;
            outData = packet;

        }

        //-------------------------------------------------------------------------------------------------
        public FTDI.FT_STATUS writeSPIPacket(byte[] outPacket, uint outLength)
        {
            uint lBytesDone = 0;


            ftStatus = SPI_Device.Purge(0x03);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }

            ftStatus = SPI_Device.Write(outPacket, (int)outLength, ref lBytesDone);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }
            return (ftStatus);
        }

        //-------------------------------------------------------------------------------------------------
        public FTDI.FT_STATUS readSPIPacket(ref byte[] inPacket, ref uint inLength)
        {

            uint RxQueue = 0;
            ftStatus = SPI_Device.GetRxBytesAvailable(ref RxQueue);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }
            // get the input data
            // read the input data
            ftStatus = SPI_Device.Read(inPacket, RxQueue, ref inLength);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }
            return (ftStatus);
        }
        //-------------------------------------------------------------------------------------------------
        public FTDI.FT_STATUS checkPinState(ref byte pins)
        {

            ftStatus = SPI_Device.GetPinStates(ref pins);
            if (ftStatus != FTDI.FT_STATUS.FT_OK)
            {
                return (ftStatus);
            }
            return (ftStatus);
        }
        //-------------------------------------------------------------------------------------------------
        public uint parseSPIPacket(byte[] inpacket, uint inLength)
        {

            uint bitmask = 0;
            byte bTemp = 0;
            uint i, j;

            // Parse the input data
            uint lDin = 0;
            j = (inLength / 2) - 2;
            // Parse out the n input bits from the data buffer


            for (i = 2; i <= (inLength - 1); i = i + 2)
            {
                // Get a character and convert to numeric

                bTemp = inpacket[i];

                // And it with the MISO bitmask, and activate that bit if a 1 was read

                bitmask = (uint)(Math.Pow(2, j));

                if ((bTemp & MISOmask) > 0)               // do we have a 1?
                    lDin = lDin | bitmask;                  // If so, then set a 1
                else                                      // else we're a 0
                    lDin = lDin & ~bitmask;                 // set a 0

                j = j - 1;

            }// end for loop
            return lDin;
        }
        //-------------------------------------------------------------------------------------------------
        public void pulseRCLK()                         // stores data from shift register into output registers
        {
            uint outLength = 2;
            byte[] outPacket = new byte[0x3];
            outPacket[0] = (byte)(DefaultMask | RCLKmask);  // set RCLK high
            outPacket[1] = (byte)(DefaultMask);             // set to defaults

            writeSPIPacket(outPacket, outLength);
        }
        //-------------------------------------------------------------------------------------------------
        // 2010/10/29 McZ State of BL output was reversed, corrected. Added BacklightOn flag.
        //
        public void turnBacklightOn()                         
        {
            uint outLength = 1;
            byte[] outPacket = new byte[0x3];
            outPacket[0] = (byte)(DefaultMask & (~BLmask));    // set BL low
            //outPacket[1] = (byte)(DefaultMask);                 // set to defaults

            writeSPIPacket(outPacket, outLength);
            BacklightOn = true;
        }
        //-------------------------------------------------------------------------------------------------
        // 2010/10/29 McZ State of BL output was reversed, corrected. Added BacklightOn flag.
        //
        public void turnBacklightOff()
        {
            uint outLength = 1;
            byte[] outPacket = new byte[0x3];
            outPacket[0] = (byte)(DefaultMask | BLmask);  // set BL high
            //outPacket[1] = (byte)(DefaultMask);             // set to defaults

            writeSPIPacket(outPacket, outLength);
            BacklightOn = false;
        }
        //-------------------------------------------------------------------------------------------------
        public void pulseCLR()                          // clears the shift register requires a pulse RCLK to clear output
        {
            uint outLength = 2;
            byte[] outPacket = new byte[0x3];
            outPacket[0] = (byte)(DefaultMask & (~CLRmask));    // set CLR low
            outPacket[1] = (byte)(DefaultMask);                 // set to defaults

            writeSPIPacket(outPacket, outLength);

        }

        //-------------------------------------------------------------------------------------------------
        public void presetShiftRegisterOutputs()
        {
            byte[] outPacket = new byte[0xFF];
            uint outDataLength = 0;
            uint inData = 0x000;
            uint inDataLength = 16;
            makeSPIPacket(inData, inDataLength, ref outPacket, ref outDataLength);
            writeSPIPacket(outPacket, outDataLength);
        }

    }
}
//-------------------------------------------------------------------------------------------------
 
