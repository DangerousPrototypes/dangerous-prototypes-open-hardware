using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;


namespace USB_LCD_Backback
{
    public class LCD_Interface : FTDI_SPI
    {
        
        ////////////////////////////////////////////////////////////////////////////
        // LCD Commands ( Refer to LCD Data Sheet ) RS = 0
        ////////////////////////////////////////////////////////////////////////////
        const byte write_data               = 0x00; // With RS = 1
        const byte clear_lcd                = 0x01; // Clear Display
        const byte return_home              = 0x02; // Cursor to Home position
        const byte entry_mode               = 0x06; // Normal entry mode
        const byte entry_mode_rev           = 0x04; // Normal entry mode  -reverse direction
        const byte entry_mode_scroll        = 0x07; // - with shift
        const byte entry_mode_scroll_rev    = 0x05; // reverse direction
        const byte display_off              = 0x08; // Display off
        const byte display_on               = 0x0C; // Display ON - 2 line mode
        const byte cursor_off               = 0x0C; // Switch Cursor OFF
        const byte cursor_on                = 0x0E; // Switch Cursor ON
        const byte cursor_blink_on          = 0x0F; // Cursor plus blink

        public static byte cursor_shift_left        = 0x10; // Move cursor left
        const byte cursor_shift_right       = 0x14; // Move cursor right
        const byte display_shift_left       = 0x18; // Scroll display left
        const byte display_shift_right      = 0x1C; // Scroll display right

        const byte system_set_4_bit         = 0x28; // 4 bit data mode 2 line ( 5x7 font )

        const byte system_set_reset         = 0x30; // Reset code
        const byte system_set_8_bit         = 0x38; // 8 bit data mode 2 line ( 5x7 font )

        // DDRAM addressing - add column number to base.

        const byte set_dd_line1             = 0x80; // Line 1 position 1
        const byte set_dd_line2             = 0xC0; // Line 2 position 1
        const byte set_dd_line3             = 0x94; // Line 3 position 1  
        const byte set_dd_line4             = 0xD4; // Line 4 position 1  

        ////////////////////////////////////////////////////////////////////////////
        // LCD bit assignments
        //
        // 15,14,13,12,11,10,09,08,07,06,05,04,03,02,01,00
        // D4,D3,D2,D1,D0,C2,C1,C0,C7,C6,C5,C4,C3,D7,D6,D5.
        // D4,D3,D2,D1,D0, E,RW,RS,C7,C6,C5,C4,C3,D7,D6,D5.
        //
        ////////////////////////////////////////////////////////////////////////////

        const byte LCD_D0 = 11;
        const byte LCD_D1 = 12;
        const byte LCD_D2 = 13;
        const byte LCD_D3 = 14;
        const byte LCD_D4 = 15;
        const byte LCD_D5 = 00;
        const byte LCD_D6 = 01;
        const byte LCD_D7 = 02;
        const byte LCD_RS = 08;
        const byte LCD_RW = 09;
        const byte LCD_E  = 10;
        const byte LCD_E1 = 10;      //
        const byte LCD_E2 = 03;     // some of the larger displays require a two E signals
        const byte CTL3   = 03;
        const byte CTL4   = 04;
        const byte CTL5   = 05;
        const byte CTL6   = 06;
        const byte CTL7   = 07;

        UInt16 D0mask;
        UInt16 D1mask;
        UInt16 D2mask;
        UInt16 D3mask;
        UInt16 D4mask;
        UInt16 D5mask;
        UInt16 D6mask;
        UInt16 D7mask;
        UInt16 RSmask;
        UInt16 RWmask;
        UInt16 Emask;

        UInt16 CTL3mask;
        UInt16 CTL4mask;
        UInt16 CTL5mask;
        UInt16 CTL6mask;
        UInt16 CTL7mask;


        FTDI_SPI SPI_Device = new FTDI_SPI();  // Create new instance of the FTDI device class

        const bool SendData = true;
        const bool SendCommand = false;


        //-------------------------------------------------------------------------------------------------
        public void initializeBitMask()
        {
            ////////////////////////////////////////////////////////////////////////////
            // Mask constructors
            ////////////////////////////////////////////////////////////////////////////
            D0mask = (UInt16)(Math.Pow(2, LCD_D0));
            D1mask = (UInt16)(Math.Pow(2, LCD_D1));
            D2mask = (UInt16)(Math.Pow(2, LCD_D2));
            D3mask = (UInt16)(Math.Pow(2, LCD_D3));
            D4mask = (UInt16)(Math.Pow(2, LCD_D4));
            D5mask = (UInt16)(Math.Pow(2, LCD_D5));
            D6mask = (UInt16)(Math.Pow(2, LCD_D6));
            D7mask = (UInt16)(Math.Pow(2, LCD_D7));
            RSmask = (UInt16)(Math.Pow(2, LCD_RS));
            RWmask = (UInt16)(Math.Pow(2, LCD_RW));
            Emask = (UInt16)(Math.Pow(2, LCD_E));

            CTL3mask = (UInt16)(Math.Pow(2, CTL3));
            CTL4mask = (UInt16)(Math.Pow(2, CTL4));
            CTL5mask = (UInt16)(Math.Pow(2, CTL5));
            CTL6mask = (UInt16)(Math.Pow(2, CTL6));
            CTL7mask = (UInt16)(Math.Pow(2, CTL7));
        }
        
        //-------------------------------------------------------------------------------------------------
        public void initializeLCD()
        {

            initializeBitMask();
            SPI_Device.InitializeFTDI();

            //      wait 20ms after power up
            Thread.Sleep(20);
            //      write system_set_reset with RS = 0
            writeToLCD(system_set_reset, SendCommand);
            //      wait 5ms
            Thread.Sleep(5);
            //      write system_set_reset with RS = 0 again
            writeToLCD(system_set_reset, SendCommand);
            //     wait 5ms
            Thread.Sleep(5);
            //      write system_set_reset with RS = 0 third time
            writeToLCD(system_set_reset, SendCommand);
            //      wait 5ms
            Thread.Sleep(5);
            //      write system_set_8_bit with RS = 0 (sets interface to 8 bits 2 lines)
            writeToLCD(system_set_8_bit, SendCommand);
            //      wait 5ms
            Thread.Sleep(5);
            //      write display_off with RS = 0 (dont shift display hide cursor)
            writeToLCD(display_off, SendCommand);
            //      wait 5ms
            Thread.Sleep(5);
            //     write clear_lcd with RS = 0 (clear and home)
            writeToLCD(clear_lcd, SendCommand);
            //      wait 5ms
            Thread.Sleep(5);
            //      write entry_mode with RS = 0 (move cursor to right direction)
            writeToLCD(entry_mode, SendCommand);
            //      wait 5ms
            Thread.Sleep(5);
            //      write display_on with RS = 0 (turn on display)
            writeToLCD(display_on, SendCommand);
            //      wait 5ms
            Thread.Sleep(5);
 
        }
        //-------------------------------------------------------------------------------------------------
        public uint ReMap(byte LCDdata)     // remaps data byte to positions required by '595 output
        {
            // 15,14,13,12,11,10,09,08,07,06,05,04,03,02,01,00
            //   ,  ,  ,  ,  ,  ,  ,  ,D7,D6,D5,D4,D3,D2,D1,D0.

            uint temp = (uint)(LCDdata & 0x1F) << 11;
            // D4,D3,D2,D1,D0,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  .

            uint RemappedWord = (uint)(LCDdata & 0xE0) >> 5;
            //   ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,D7,D6,D5.

            RemappedWord = RemappedWord | temp;
            // D4,D3,D2,D1,D0,  ,  ,  ,  ,  ,  ,  ,  ,D7,D6,D5.

            return RemappedWord;
        }

        //-------------------------------------------------------------------------------------------------
         public void writeToLCD(byte dataToWrite, bool dataCommand) // dataCommand is true for data.
        {
            uint outDataLength = 16;
            byte[] outPacket = new byte[0xFF];
            byte[] outPacket1 = new byte[0xFF];
            byte[] outPacket2 = new byte[0xFF];
            byte[] outPacket3 = new byte[0xFF];
            uint outPacketLength = 0;
            uint outPacketLength1 = 0;
            uint outPacketLength2 = 0;
            uint outPacketLength3 = 0;
            
            //-------------------------------------
            // remaps data as per hardware
            //-------------------------------------
            uint RemappedWord = ReMap(dataToWrite);     // remaps data
            // D4,D3,D2,D1,D0,C2,C1,C0,C7,C6,C5,C4,C3,D7,D6,D5. generic map
            // D4,D3,D2,D1,D0, E,RW,RS,C7,C6,C5,C4,C3,D7,D6,D5. specific map
            if (dataCommand)
                RemappedWord = RemappedWord | RSmask;   // sets RS signal to one if data
            //-------------------------------------
            // makes three packets
            //-------------------------------------
            uint outData = RemappedWord;

            makeSPIPacket(outData, outDataLength, ref outPacket1, ref outPacketLength1);  // makes packet1

            outData = RemappedWord | Emask;                                             // sets E signal

            makeSPIPacket(outData, outDataLength, ref outPacket2, ref outPacketLength2);  // makes packet2

            outData = RemappedWord;                                                     // resets E signal

            makeSPIPacket(outData, outDataLength, ref outPacket3, ref outPacketLength3);  // makes packet3

            System.Buffer.BlockCopy
            (outPacket1, 0, outPacket, 0, (int)outPacketLength1);

            System.Buffer.BlockCopy
            (outPacket2, 0, outPacket, (int)outPacketLength1 - 1, (int)outPacketLength2);

            System.Buffer.BlockCopy
            (outPacket3, 0, outPacket, (int)(outPacketLength1 - 1 + outPacketLength2 - 1), (int)outPacketLength3);
            //outPacket1.Concat(outPacket, 0);
            //outPacket2.CopyTo(outPacket, 0);
            //outPacket3.CopyTo(outPacket, 0);
            outPacketLength = (outPacketLength1-1) + (outPacketLength2-1) + (outPacketLength3-1);

            //-------------------------------------
            // sends three packets
            //-------------------------------------
            writeSPIPacket(outPacket, outPacketLength);                                 // sends packet
            //writeSPIPacket(outPacket1, outPacketLength);                                 // sends packet
            //writeSPIPacket(outPacket2, outPacketLength);                                 // sends packet
            //writeSPIPacket(outPacket3, outPacketLength);                                 // sends packet
        }
//-------------------------------------------------------------------------------------------------
        public void clearLCD()
        {
            writeToLCD(clear_lcd, SendCommand);
        }
        //-------------------------------------------------------------------------------------------------
        public void Backlight(bool state)
        {
            if (state)
                turnBacklightOn();
            else
                turnBacklightOff();
        }
       //-------------------------------------------------------------------------------------------------
        public void moveDisplayLCD(byte direction)
        {
            if (direction == display_shift_right)
                writeToLCD(cursor_shift_right, SendCommand);
            else if (direction == display_shift_left)
                writeToLCD(cursor_shift_left, SendCommand);
        }
//-------------------------------------------------------------------------------------------------
        public void moveCursorLCD(byte direction)
        {
            if (direction == cursor_shift_right)
                writeToLCD(cursor_shift_right, SendCommand);
            else if (direction == cursor_shift_left)
                writeToLCD(cursor_shift_left, SendCommand);
        }
//-------------------------------------------------------------------------------------------------
        public void test(uint data)                              // this routine sends a known packet
        {
            byte[] outPacket = new byte[0xFF];
            uint outDataLength = 0;
            uint inData = data;
            uint inDataLength = 16;
            makeSPIPacket(inData, inDataLength, ref outPacket, ref outDataLength);
            writeSPIPacket(outPacket, outDataLength);
        }

                      // writeToLCD(0x18, SendCommand);

//-------------------------------------------------------------------------------------------------
    }
}
//-------------------------------------------------------------------------------------------------
