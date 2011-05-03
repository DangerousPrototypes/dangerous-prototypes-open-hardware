using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;


using USB_LCD_Backpack;

namespace USB_LCD_Backback
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        bool CursorOn = false;
        bool CursorBlinkOn = false;
        uint DisplayRowsCount = 2;
        uint DisplayColumnsCount = 16;
        bool ScrollOn = false;
        uint ScrollRateCount = 500;
        bool BacklightOn = false;

        byte Line1Address = 0x00;
        byte Line2Address = 0x40;
        byte Line3Address = 0x14;
        byte Line4Address = 0x54;

        LCD_Interface thisLCD_Interface = new LCD_Interface(); // Create new instance of the LCD device class

        const bool SendData = true;
        const bool SendCommand = false;

        DispatcherTimer ScrollTimer = new System.Windows.Threading.DispatcherTimer();

        

        public MainWindow()
        {
            InitializeComponent();
            thisLCD_Interface.initializeLCD();
            //  DispatcherTimer setup
            ScrollTimer.Tick += new EventHandler(ScrollTimer_Tick);
            ScrollTimer.Interval = new TimeSpan(5000000);

        }
        //--------------------------------------------------------------------------
        private void CursorOnOff_Click(object sender, RoutedEventArgs e)
        {
            if (CursorOn)
            {
                thisLCD_Interface.writeToLCD(0x0C, SendCommand);
                CursorOn = false;
                CursorBlinkOn = false;
                CursorOnOff.Header = "CursorOn";
                CursorBlink.Header = "BlinkOn";
            }
            else
            {
                thisLCD_Interface.writeToLCD(0x0E, SendCommand);
                CursorOn = true;
                CursorOnOff.Header = "CursorOff";
            }
        }
        private void CursorBlink_Click(object sender, RoutedEventArgs e)
        {
            if (CursorBlinkOn)
            {
                thisLCD_Interface.writeToLCD(0x0E, SendCommand);
                CursorBlinkOn = false;
                CursorBlink.Header = "BlinkOn";
            }
            else
            {
                thisLCD_Interface.writeToLCD(0x0F, SendCommand);
                CursorBlinkOn = true;
                CursorOn = true;
                CursorBlink.Header = "BlinkOff";
                CursorOnOff.Header = "CursorOff";

            }

        }
        //--------------------------------------------------------------------------
        private void ShiftCursorLeft_Click(object sender, RoutedEventArgs e)
        {

            //thisLCD_Interface.writeToLCD(cursor_shift_left, SendCommand);
            thisLCD_Interface.writeToLCD(0x10, SendCommand);
        }
        private void ShiftCursorRight_Click(object sender, RoutedEventArgs e)
        {
            thisLCD_Interface.writeToLCD(0x14, SendCommand);


        }
        //--------------------------------------------------------------------------
        private void ShiftDataLeft_Click(object sender, RoutedEventArgs e)
        {
            thisLCD_Interface.writeToLCD(0x18, SendCommand);
        }
        private void ShiftDataRight_Click(object sender, RoutedEventArgs e)
        {
            thisLCD_Interface.writeToLCD(0x1C, SendCommand);
        }
        //--------------------------------------------------------------------------
        private void ScrollOnOff_Click(object sender, RoutedEventArgs e)
        {
            if (ScrollOn)
            {
                ScrollOn = false;
                ScrollOnOff.Header = "ScrollOn";
                ScrollTimer.Stop();

            }
            else
            {
                ScrollOn = true;
                ScrollOnOff.Header = "ScrollOff";
                ScrollTimer.Start();

            }

        }
        private void ScrollRate_Click(object sender, RoutedEventArgs e)
        {
            
        }
        private void ScrollTimer_Tick(object sender, EventArgs e)
        {
            thisLCD_Interface.writeToLCD(0x18, SendCommand);
        }
        //--------------------------------------------------------------------------
        private void BacklightOnOff_Click(object sender, RoutedEventArgs e)
        {
            if (BacklightOn)
            {
                BacklightOn = false;
                BacklightOnOff.Header = "BacklightOn";
                thisLCD_Interface.Backlight(false);
            }
            else
            {
                BacklightOn = true;
                BacklightOnOff.Header = "BacklightOff";
                thisLCD_Interface.Backlight(true);
            }
        }
        //--------------------------------------------------------------------------
        private void Help_Click(object sender, RoutedEventArgs e)
        {

        }
        //--------------------------------------------------------------------------
        private void Line1TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        private void Line2TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        private void Line3TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        private void Line4TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        //--------------------------------------------------------------------------
        private void ClearAll_Click(object sender, RoutedEventArgs e)
        {
            thisLCD_Interface.clearLCD();
        }
        //--------------------------------------------------------------------------
        private void Line1Enter_Click(object sender, RoutedEventArgs e)
        {
            byte DisplayAddress = (byte)(0x80 | Line1Address);
            byte dataToWrite;
            string text = Line1TextBox.Text.ToString();
            thisLCD_Interface.writeToLCD(DisplayAddress, SendCommand);
            byte i;
            for (i = 0; i < text.Length; i++)
            {
                dataToWrite = (byte)text[i];
                thisLCD_Interface.writeToLCD(dataToWrite, SendData);
            }

        }
        private void Line2Enter_Click(object sender, RoutedEventArgs e)
        {
            byte DisplayAddress = (byte)(0x80 | Line2Address);
            byte dataToWrite;
            string text = Line2TextBox.Text.ToString();
            thisLCD_Interface.writeToLCD(DisplayAddress, SendCommand);
            byte i;
            for (i = 0; i < text.Length; i++)
            {
                dataToWrite = (byte)text[i];
                thisLCD_Interface.writeToLCD(dataToWrite, SendData);
            }

        }
        private void Line3Enter_Click(object sender, RoutedEventArgs e)
        {
            byte DisplayAddress = (byte)(0x80 | Line3Address);
            byte dataToWrite;
            string text = Line3TextBox.Text.ToString();
            thisLCD_Interface.writeToLCD(DisplayAddress, SendCommand);
            byte i;
            for (i = 0; i < text.Length; i++)
            {
                dataToWrite = (byte)text[i];
                thisLCD_Interface.writeToLCD(dataToWrite, SendData);
            }

        }
        private void Line4Enter_Click(object sender, RoutedEventArgs e)
        {
            byte DisplayAddress = (byte)(0x80 | Line4Address);
            byte dataToWrite;
            string text = Line4TextBox.Text.ToString();
            thisLCD_Interface.writeToLCD(DisplayAddress, SendCommand);
            byte i;
            for (i = 0; i < text.Length; i++)
            {
                dataToWrite = (byte)text[i];
                thisLCD_Interface.writeToLCD(dataToWrite, SendData);
            }

        }
        //--------------------------------------------------------------------------
        private void Line1Clear_Click(object sender, RoutedEventArgs e)
        {
            Line1TextBox.Text = "";
             
            byte DisplayAddress = (byte)(0x80 | Line1Address);
         
            thisLCD_Interface.writeToLCD(DisplayAddress, SendCommand);
            byte i;
            for (i = 0; i < DisplayColumnsCount; i++)
            {
                thisLCD_Interface.writeToLCD(0XA0, SendData);
            }

        }
        private void Line2Clear_Click(object sender, RoutedEventArgs e)
        {
            Line2TextBox.Text = "";

            byte DisplayAddress = (byte)(0x80 | Line2Address);

            thisLCD_Interface.writeToLCD(DisplayAddress, SendCommand);
            byte i;
            for (i = 0; i < DisplayColumnsCount; i++)
            {
                thisLCD_Interface.writeToLCD(0XA0, SendData);
            }

        }
        private void Line3Clear_Click(object sender, RoutedEventArgs e)
        {
            Line3TextBox.Text = "";

            byte DisplayAddress = (byte)(0x80 | Line3Address);

            thisLCD_Interface.writeToLCD(DisplayAddress, SendCommand);
            byte i;
            for (i = 0; i < DisplayColumnsCount; i++)
            {
                thisLCD_Interface.writeToLCD(0XA0, SendData);
            }

        }
        private void Line4Clear_Click(object sender, RoutedEventArgs e)
        {
            Line4TextBox.Text = "";

            byte DisplayAddress = (byte)(0x80 | Line4Address);

            thisLCD_Interface.writeToLCD(DisplayAddress, SendCommand);
            byte i;
            for (i = 0; i < DisplayColumnsCount; i++)
            {
                thisLCD_Interface.writeToLCD(0XA0, SendData);
            }

        }
        //--------------------------------------------------------------------------
        private void Display40x4_Checked(object sender, RoutedEventArgs e)
        {
            DisplayColumnsCount = 40;
            DisplayRowsCount = 4;
            Line2TextBox.Visibility = Visibility.Visible;
            Line3TextBox.Visibility = Visibility.Visible;
            Line4TextBox.Visibility = Visibility.Visible;

            Line2Enter.Visibility = Visibility.Visible;
            Line3Enter.Visibility = Visibility.Visible;
            Line4Enter.Visibility = Visibility.Visible;

            Line2Clear.Visibility = Visibility.Visible;
            Line3Clear.Visibility = Visibility.Visible;
            Line4Clear.Visibility = Visibility.Visible;

            Line1Address = 0x00;
            Line2Address = 0x40;
            Line3Address = 0x00;
            Line4Address = 0x40;

        }
        private void Display20x4_Checked(object sender, RoutedEventArgs e)
        {
            DisplayColumnsCount = 20;
            DisplayRowsCount = 4;
            Line2TextBox.Visibility = Visibility.Visible;
            Line3TextBox.Visibility = Visibility.Visible;
            Line4TextBox.Visibility = Visibility.Visible;

            Line2Enter.Visibility = Visibility.Visible;
            Line3Enter.Visibility = Visibility.Visible;
            Line4Enter.Visibility = Visibility.Visible;

            Line2Clear.Visibility = Visibility.Visible;
            Line3Clear.Visibility = Visibility.Visible;
            Line4Clear.Visibility = Visibility.Visible;

            Line1Address = 0x00;
            Line2Address = 0x40;
            Line3Address = 0x14;
            Line4Address = 0x54;

        }
        private void Display16x4_Checked(object sender, RoutedEventArgs e)
        {
            DisplayColumnsCount = 16;
            DisplayRowsCount = 4;
            Line2TextBox.Visibility = Visibility.Visible;
            Line3TextBox.Visibility = Visibility.Visible;
            Line4TextBox.Visibility = Visibility.Visible;

            Line2Enter.Visibility = Visibility.Visible;
            Line3Enter.Visibility = Visibility.Visible;
            Line4Enter.Visibility = Visibility.Visible;

            Line2Clear.Visibility = Visibility.Visible;
            Line3Clear.Visibility = Visibility.Visible;
            Line4Clear.Visibility = Visibility.Visible;

            Line1Address = 0x00;
            Line2Address = 0x40;
            Line3Address = 0x10;
            Line4Address = 0x50;

        }
        private void Display40x2_Checked(object sender, RoutedEventArgs e)
        {
            DisplayColumnsCount = 40;
            DisplayRowsCount = 2;
            Line2TextBox.Visibility = Visibility.Visible;
            Line3TextBox.Visibility = Visibility.Hidden;
            Line4TextBox.Visibility = Visibility.Hidden;

            Line2Enter.Visibility = Visibility.Visible;
            Line3Enter.Visibility = Visibility.Hidden;
            Line4Enter.Visibility = Visibility.Hidden;

            Line2Clear.Visibility = Visibility.Visible;
            Line3Clear.Visibility = Visibility.Hidden;
            Line4Clear.Visibility = Visibility.Hidden;

            Line1Address = 0x00;
            Line2Address = 0x40;
            Line3Address = 0x14;
            Line4Address = 0x54;

        }
        private void Display24x2_Checked(object sender, RoutedEventArgs e)
        {
            DisplayColumnsCount = 24;
            DisplayRowsCount = 2;
            Line2TextBox.Visibility = Visibility.Visible;
            Line3TextBox.Visibility = Visibility.Hidden;
            Line4TextBox.Visibility = Visibility.Hidden;

            Line2Enter.Visibility = Visibility.Visible;
            Line3Enter.Visibility = Visibility.Hidden;
            Line4Enter.Visibility = Visibility.Hidden;

            Line2Clear.Visibility = Visibility.Visible;
            Line3Clear.Visibility = Visibility.Hidden;
            Line4Clear.Visibility = Visibility.Hidden;

            Line1Address = 0x00;
            Line2Address = 0x40;
            Line3Address = 0x14;
            Line4Address = 0x54;

        }
        private void Display20x2_Checked(object sender, RoutedEventArgs e)
        {
            DisplayColumnsCount = 20;
            DisplayRowsCount = 2;
            Line2TextBox.Visibility = Visibility.Visible;
            Line3TextBox.Visibility = Visibility.Hidden;
            Line4TextBox.Visibility = Visibility.Hidden;

            Line2Enter.Visibility = Visibility.Visible;
            Line3Enter.Visibility = Visibility.Hidden;
            Line4Enter.Visibility = Visibility.Hidden;

            Line2Clear.Visibility = Visibility.Visible;
            Line3Clear.Visibility = Visibility.Hidden;
            Line4Clear.Visibility = Visibility.Hidden;

            Line1Address = 0x00;
            Line2Address = 0x40;
            Line3Address = 0x14;
            Line4Address = 0x54;

        }
        private void Display16x2_Checked(object sender, RoutedEventArgs e)
        {
            DisplayColumnsCount = 16;
            DisplayRowsCount = 2;
            Line2TextBox.Visibility = Visibility.Visible;
            Line3TextBox.Visibility = Visibility.Hidden;
            Line4TextBox.Visibility = Visibility.Hidden;

            Line2Enter.Visibility = Visibility.Visible;
            Line3Enter.Visibility = Visibility.Hidden;
            Line4Enter.Visibility = Visibility.Hidden;

            Line2Clear.Visibility = Visibility.Visible;
            Line3Clear.Visibility = Visibility.Hidden;
            Line4Clear.Visibility = Visibility.Hidden;

            Line1Address = 0x00;
            Line2Address = 0x40;
            Line3Address = 0x14;
            Line4Address = 0x54;

        }
        private void Display8x2_Checked(object sender, RoutedEventArgs e)
        {
            DisplayColumnsCount = 8;
            DisplayRowsCount = 2;
            Line2TextBox.Visibility = Visibility.Visible;
            Line3TextBox.Visibility = Visibility.Hidden;
            Line4TextBox.Visibility = Visibility.Hidden;

            Line2Enter.Visibility = Visibility.Visible;
            Line3Enter.Visibility = Visibility.Hidden;
            Line4Enter.Visibility = Visibility.Hidden;

            Line2Clear.Visibility = Visibility.Visible;
            Line3Clear.Visibility = Visibility.Hidden;
            Line4Clear.Visibility = Visibility.Hidden;

            Line1Address = 0x00;
            Line2Address = 0x40;
            Line3Address = 0x14;
            Line4Address = 0x54;

        }
        private void Display16x1_Checked(object sender, RoutedEventArgs e)
        {
            DisplayColumnsCount = 16;
            DisplayRowsCount = 1;
            Line2TextBox.Visibility = Visibility.Hidden;
            Line3TextBox.Visibility = Visibility.Hidden;
            Line4TextBox.Visibility = Visibility.Hidden;

            Line2Enter.Visibility = Visibility.Hidden;
            Line3Enter.Visibility = Visibility.Hidden;
            Line4Enter.Visibility = Visibility.Hidden;

            Line2Clear.Visibility = Visibility.Hidden;
            Line3Clear.Visibility = Visibility.Hidden;
            Line4Clear.Visibility = Visibility.Hidden;

            Line1Address = 0x00;
            Line2Address = 0x40;
            Line3Address = 0x14;
            Line4Address = 0x54;

        }
        private void Display8x1_Checked(object sender, RoutedEventArgs e)
        {
            DisplayColumnsCount = 8;
            DisplayRowsCount = 1;
            Line2TextBox.Visibility = Visibility.Hidden;
            Line3TextBox.Visibility = Visibility.Hidden;
            Line4TextBox.Visibility = Visibility.Hidden;

            Line2Enter.Visibility = Visibility.Hidden;
            Line3Enter.Visibility = Visibility.Hidden;
            Line4Enter.Visibility = Visibility.Hidden;

            Line2Clear.Visibility = Visibility.Hidden;
            Line3Clear.Visibility = Visibility.Hidden;
            Line4Clear.Visibility = Visibility.Hidden;

            Line1Address = 0x00;
            Line2Address = 0x40;
            Line3Address = 0x14;
            Line4Address = 0x54;

        }
        //--------------------------------------------------------------------------
        private void about_Click(object sender, RoutedEventArgs e)
        {
            USB_LCD_Backpack.About aboutWindow = new About();
            aboutWindow.ShowDialog();
        }
        //--------------------------------------------------------------------------

    }
}
