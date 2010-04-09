using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Sevenstring.HWInterface;
using System.IO.Ports;
using System.Threading;

namespace WindowsFormsApplication1
{
    public partial class frmBusPirate : Form
    {
        private const string FRM_VERSION= " 00.08.10 Alpha Version";
        private const string FRM_TITLE="Pirate Bus Tester .NET (SVN)";

        private const int TEMP_DELAY=200;
        //BusPirate myBusPirate=null;
        PIC24Program myPIC24Program=null;

        //StringBuilder prvStrBuilder=new StringBuilder();

        public frmBusPirate()
        {
        InitializeComponent();
        }

        
        private void frmBusPirate_Load(object sender, EventArgs e)
        {
        this.Text=FRM_TITLE;
        cmbSerial.Items.Clear();
        cmbSerial.Items.AddRange(SerialPort.GetPortNames());
        cmbSerial.SelectedIndex=0;
        grpTest.Enabled=false;
        txtStatus.Text=FRM_TITLE+FRM_VERSION;
        }

        
        private void btnConnect_Click(object sender, EventArgs e)
        {
        SerialPort mySerial=new SerialPort(cmbSerial.SelectedItem.ToString());
        BusPirate myBusPirate=new BusPirate(mySerial);
        myPIC24Program=new PIC24Program(myBusPirate);
        myPIC24Program.Open();


        grpSerial.Enabled=false;
        grpTest.Enabled=true;
        txtStatus.Clear();
        SetStatusString(String.Format("Connected to {0}!",cmbSerial.SelectedItem.ToString()));
        }


        private void SetStatusString(string Status)
        {
        Application.DoEvents();
        txtStatus.AppendText(Status);
        }

        private void frmBusPirate_FormClosing(object sender, FormClosingEventArgs e)
        {
        if(myPIC24Program!=null)
            myPIC24Program.Close(true);
        }





        private void btnRunTest_Click(object sender, EventArgs e)
        {
        btnRunTest.Enabled=false;
        txtStatus.Clear();
        SetStatusString("===============================\r\n");
        SetStatusString("Reset!\r\n");
        if(myPIC24Program.BusPirate.EnterReset()==true)
            {
            SetStatusString("Reset Successful!\r\n");
            }
        else
            {
            SetStatusString("Reset Failed!\r\n");
            }


        SetStatusString("===============================\r\n");
        SetStatusString("Enter Raw Wire Mode!\r\n");
        if(myPIC24Program.BusPirate.EnterRawWireMode()==true)
            {
            SetStatusString("Raw Wire Mode Successful!\r\n");
            }
        else
            {
            SetStatusString("Raw Wire Mode Failed!\r\n");
            }

        SetStatusString("===============================\r\n");
        SetStatusString("Configure!\r\n");
        //if(myPIC24Program.BusPirate.BusPirateRawWire.SetModeConfig(true,true,true)==true)
        if(myPIC24Program.BusPirate.BusPirateRawWire.SetModeConfig(true,false,false)==true)
            {
            SetStatusString("SetModeConfig Successful!\r\n");
            }
        else
            {
            SetStatusString("SetModeConfig Failed!\r\n");
            }
        if(myPIC24Program.BusPirate.BusPirateRawWire.SetPeripheralConfig(true,true,true,true)==true)
            {
            SetStatusString("SetPeripheralConfig Successful!\r\n");
            }
        else
            {
            SetStatusString("SetPeripheralConfig Failed!\r\n");
            }

        SetStatusString("Delay 2000msec!\r\n");
        Thread.Sleep(2000);

        SetStatusString("Entering Normal ICSP!\r\n");
        if(myPIC24Program.EnterICSPMode(PIC24Program.SECURE_ID_NORMAL_ICSP)==false)
            {
            SetStatusString("Error Entering Normal ICSP!\r\n");
            }
        else
            {
            myPIC24Program.SendSixSerialExec(true,0); // send NOP 
            SetStatusString("Erase Chip!\r\n");
            myPIC24Program.EraseChip();
            myPIC24Program.ExitICSPMode();
#if N_COMP // DONT COMPILE
            uint [] RetDat;
            string temp;
            SetStatusString("Reading 0xFF0000!\r\n");
            RetDat= myPIC24Program.ReadCodeMem(0xFF0000);
            
            temp=String.Format("Data: {0:x2} {1:x2} {2:x2} \r\n",RetDat[0],RetDat[1],RetDat[2]);
            SetStatusString(temp);

            SetStatusString("Reading 0xFF0002!\r\n");
            myPIC24Program.SendSixSerialExec(false,0);
            RetDat= myPIC24Program.ReadCodeMem(0xFF0002);
            temp=String.Format("Data: {0:x2} {1:x2} {2:x2} \r\n",RetDat[0],RetDat[1],RetDat[2]);
            SetStatusString(temp);
#endif
            }

#if N_COMP // DONT COMPILE
        //Read device ID
        myPIC24Program.Send16BitCommamd((PIC24Program.PEC_READC<<12)|3);
        myPIC24Program.Send16BitCommamd((8U<<8)|0xFF);
        myPIC24Program.Send16BitCommamd(0x0000);


        for(int ctr=0;ctr<8;ctr++)
            {
            SetStatusString(String.Format("Dev ID Experiment: 0x{0:x4} \r\n",myPIC24Program.Read16BitCommamd() ) );
            }
#endif
        SetStatusString("Done!\r\n");
        Application.DoEvents();
        btnRunTest.Enabled=true;
        }



        private void btnInitMCLR_Click(object sender, EventArgs e)
        {
        txtStatus.Clear();
        SetStatusString("Entering Normal ICSP!\r\n");
        if(myPIC24Program.EnterICSPMode(PIC24Program.SECURE_ID_NORMAL_ICSP)==false)
            {
            SetStatusString("Error Entering Normal ICSP!\r\n");
            }
        }



        private void btnExitMCLR_Click(object sender, EventArgs e)
        {
        txtStatus.Clear();
        SetStatusString("MCLR Low!\r\n");
        myPIC24Program.MCLRLow();
        }

        private void btnInitMCLRPin_Click(object sender, EventArgs e)
        {
        txtStatus.Clear();
        SetStatusString("MCLR High!\r\n");
        myPIC24Program.MCLRHigh();
        }





#if N_COMP // DONT COMPILE
        private void SendTestCodes(string StartingMsg,byte [] DataBytes,int intDelay)
        {
        SetStatusString("===============================\r\n");
        SetStatusString(StartingMsg);
        myPIC24Program.BusPirate.BusPirateSerialPort.DiscardInBuffer();
        
        StringBuilder sb=new StringBuilder();
        foreach(byte x in DataBytes)
            {
            sb.AppendFormat("0x{0:x2}  ",x);
            }
        SetStatusString("Sending Data: " + sb.ToString() + "\r\n");

        myPIC24Program.BusPirate.BusPirateSerialPort.BusPirateSerialPort.Write(DataBytes,0,DataBytes.Length);
        SetStatusString(String.Format("Delay {0} milliseconds...\r\n",intDelay));
        Thread.Sleep(intDelay);
        if(myBusPirate.BusPirateSerialPort.BytesToRead==0)
            SetStatusString("No Reply Received!\r\n");
        else
            {
            SetStatusString("Reply Received: ");
            SetStatusString(myBusPirate.BusPirateSerialPort.ReadExisting() + "\r\n");
            }
        }
#endif

#if NOT_DEFINED // DONT COMPILE
        private void  btnRunTest_Click(object sender, EventArgs e)
        {
        SetStatusString("===============================\r\n");
        SetStatusString("Enter BitBang Mode\r\n");
        myBusPirate.BusPirateSerialPort.DiscardInBuffer();
        myBusPirate.BusPirateSerialPort.Write(new byte[]{BusPirate.BPC_EnterOrRstRawBitBangMode},0,1);
        Thread.Sleep(TEMP_DELAY);
        if(myBusPirate.BusPirateSerialPort.BytesToRead==0)
            SetStatusString("No Data Received\r\n");
        else
            SetStatusString(myBusPirate.BusPirateSerialPort.ReadExisting() + "\r\n");


        }



        private void btnRunTest_Click(object sender, EventArgs e)
        {
        txtStatus.Clear();
        Application.DoEvents();
        SendTestCodes("Reset (Send 0x00 more than 20 times)!\r\n",new byte[]
            {0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0
            },3000);

        SendTestCodes("Enter BitBang Mode!\r\n",new byte[]{0x05},3000); // enter raw binary mode
        }








#endif

    }
}
