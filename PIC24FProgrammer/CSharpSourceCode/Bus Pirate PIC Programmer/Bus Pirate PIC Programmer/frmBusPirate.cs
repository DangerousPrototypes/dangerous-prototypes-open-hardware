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
using System.IO;
using Sevenstring.HexParser;

namespace WindowsFormsApplication1
{
    public partial class frmBusPirate : Form
    {
        private const string FRM_VERSION= " 00.08.36 Alpha Version";
        private const string FRM_TITLE="PIC Pirate Bus Tester .NET" + FRM_VERSION;

        private const int TEMP_DELAY=200;

        private const string STR_PIC18F24J50="PIC18F24J50";

        private string [] DEVICE_LIST=
            {
            STR_PIC18F24J50,
            };
        
        BusPirate myBusPirate=null;
        PIC24Program myPIC24Program=null;
        PIC18Program myPIC18Program=null;

        public frmBusPirate()
        {
        InitializeComponent();
        }

        
        private void frmBusPirate_Load(object sender, EventArgs e)
        {

        cmbDevice.Items.Clear();
        cmbDevice.Items.AddRange(DEVICE_LIST);
        cmbDevice.SelectedIndex=0;

        this.Text=FRM_TITLE;
        
        tabBPControls.Enabled=false;
        txtStatus.Text=FRM_TITLE;

        cmbSerial.Items.Clear();
        cmbSerial.Items.Add("COM1");

        cmbSerial.Items.Clear();
        cmbSerial.Items.AddRange(SerialPort.GetPortNames());
        cmbSerial.SelectedIndex=0;
        
        }

        
        private void btnConnect_Click(object sender, EventArgs e)
        {
        SerialPort mySerial=new SerialPort(cmbSerial.SelectedItem.ToString());
        myBusPirate=new BusPirate(mySerial);
        myBusPirate.Open();
        myPIC24Program=new PIC24Program(myBusPirate);
        myPIC18Program=new PIC18Program(myBusPirate);
        //myPIC24Program.Open();

        grpSerial.Enabled=false;
        tabBPControls.Enabled=true;
        txtStatus.Clear();
        SetStatusString(String.Format("Connected to {0}!\r\n ============ \r\n",cmbSerial.SelectedItem.ToString()));

        BPInit();
        }


        private void SetStatusString(string Status)
        {
        Application.DoEvents();
        txtStatus.AppendText(Status);
        }

        private void frmBusPirate_FormClosing(object sender, FormClosingEventArgs e)
        {
        //if(myPIC24Program!=null)
        //    myPIC24Program.Close(true);
        if(myBusPirate!=null)
            myBusPirate.Close(true);
        }




#if N_COMP
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
            myPIC24Program.SendSixSerialExec(true,true,0); // send NOP 
            SetStatusString("Erase Chip!\r\n");
            //myPIC24Program.EraseChip();
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
#endif



#if N_COMP
        private void btnInitMCLR_Click(object sender, EventArgs e)
        {
        txtStatus.Clear();
        SetStatusString("Entering Normal ICSP!\r\n");
        if(myPIC24Program.EnterICSPMode(PIC24Program.SECURE_ID_NORMAL_ICSP)==false)
            {
            SetStatusString("Error Entering Normal ICSP!\r\n");
            }
        else
            {
            SetStatusString("Entered Normal ICSP!\r\n");
            myPIC24Program.SendSixSerialExec(true,true,0); // send NOP immediately
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
#endif
     

#if N_COMP
        private void btnInitBusPirate_Click(object sender, EventArgs e)
        {
        btnInitBusPirate.Enabled=false;
        BPInit();
        btnInitBusPirate.Enabled=true;
        }
#endif
       


        private void BPInit()
        {
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
            goto IMMEDIATE_EXIT;
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
            goto IMMEDIATE_EXIT;
            }

        SetStatusString("===============================\r\n");
        SetStatusString("Configure!\r\n");
        //if(myPIC24Program.BusPirate.BusPirateRawWire.SetModeConfig(true,true,true)==true)
        if(myPIC24Program.BusPirate.BusPirateRawWire.SetModeConfig(true,false,false)==true) //MSB FIRST!
            {
            SetStatusString("SetModeConfig Successful!\r\n");
            }
        else
            {
            SetStatusString("SetModeConfig Failed!\r\n");
            goto IMMEDIATE_EXIT;
            }
        if(myPIC24Program.BusPirate.BusPirateRawWire.SetPeripheralConfig(true,true,true,true)==true)
            {
            SetStatusString("SetPeripheralConfig Successful!\r\n");
            }
        else
            {
            SetStatusString("SetPeripheralConfig Failed!\r\n");
            goto IMMEDIATE_EXIT;
            }

        IMMEDIATE_EXIT:
        Application.DoEvents();
        }



        private void btnOpenAndLoadScript_Click(object sender, EventArgs e)
        {
        string temp;
        P18_P24Script.ScriptData [] myScriptData;
        txtStatus.Clear();

        SetStatusString("Pinging Bus Pirate...\r\n");
        if(myPIC24Program.ExitICSPMode()==false)
            {
            SetStatusString("Error Pinging Bus Pirate!\r\n");
            MessageBox.Show("No Response from Bus Pirate!","Error",MessageBoxButtons.OK,MessageBoxIcon.Error);
            return;
            }

        if(ofdScipt.ShowDialog()==DialogResult.OK)
            {
            temp=String.Format("Running Script {0} ...\r\n",ofdScipt.FileName);
            SetStatusString(temp);
            P18_P24Script myScript=new P18_P24Script(ofdScipt.FileName);

            try
                {
                myScriptData= myScript.GetScriptData();
                }
            catch(Exception ex)
                {
                SetStatusString("Error!\r\n");
                MessageBox.Show(ex.Message,"Error",MessageBoxButtons.OK,MessageBoxIcon.Error);
                return;
                }

            for(int ctr=0;ctr<myScriptData.Length;ctr++)
                {
                Application.DoEvents();
                if(myScriptData[ctr].Command==P18_P24Script.Commands.ENTERICSPNORMAL)
                    {
                    myPIC24Program.EnterICSPMode(PIC24Program.SECURE_ID_NORMAL_ICSP);
                    SetStatusString("Entering ICSP Normal Mode!\r\n");
                    }
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.EXITICSP)
                    {
                    myPIC24Program.ExitICSPMode();
                    SetStatusString("Exit ICSP Mode!\r\n");
                    }
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.FORCEDSIX)
                    {
                    temp=String.Format("Sending ForcedSix Command with Data: 0x{0:x6}!\r\n",myScriptData[ctr].HexData);
                    SetStatusString(temp);
                    //myPIC24Program.SendSixSerialExec(true,myScriptData[ctr].HexData);
                    myPIC24Program.SendSixSerialExec(true,true,myScriptData[ctr].HexData);
                    }
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.SIX)
                    {
                    temp=String.Format("Sending Six Command with Data: 0x{0:x6}!\r\n",myScriptData[ctr].HexData);
                    SetStatusString(temp);
                    myPIC24Program.SendSixSerialExec(true,false,myScriptData[ctr].HexData);
                    }
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.SIX_AFTER_REGOUT)
                    {
                    temp=String.Format("Sending Six After Regout Command with Data: 0x{0:x6}!\r\n",myScriptData[ctr].HexData);
                    SetStatusString(temp);
                    myPIC24Program.SendSixSerialExecAfterRegout(myScriptData[ctr].HexData);
                    }
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.REGOUT)
                    {
                    uint ? MyReading=myPIC24Program.ReadRegOut();
                    temp=String.Format("Data Read: 0x{0:x6}!\r\n",MyReading);
                    SetStatusString(temp);
                    }

                // PIC18
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.PIC18ENTERICSP)
                    {
                    myPIC18Program.EnterICSPMode();
                    SetStatusString("Entering PIC18 ICSP Mode!\r\n");
                    }
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.SEND4BITCOMMANDLSBFIRST)
                    {
                    temp=String.Format("Sending 4-bit Command with Data: 0x{0:x2}!\r\n",myScriptData[ctr].HexData);
                    SetStatusString(temp);
                    myPIC18Program.Send4BitCommandLSBFirst((byte)myScriptData[ctr].HexData);
                    }
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.SEND16BITDATALSBFIRST)
                    {
                    temp=String.Format("Sending 16-bit data: 0x{0:x4}!\r\n",myScriptData[ctr].HexData);
                    SetStatusString(temp);
                    //myPIC18Program.Send16BitDataLSBFirst(myScriptData[ctr].HexData);
                    myPIC18Program.Send16BitLSBFirst(myScriptData[ctr].HexData);
                    }
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.READ8BITLSBFIRST)
                    {
                    uint ? MyReading=myPIC18Program.Read8BitLSBFirst();
                    temp=String.Format("8-bit Data Read: 0x{0:x2}!\r\n",MyReading);
                    SetStatusString(temp);
                    }
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.SEND8BITDATALSBFIRST)
                    {
                    temp=String.Format("Sending 8-bit data: 0x{0:x2}!\r\n",myScriptData[ctr].HexData);
                    SetStatusString(temp);
                    myPIC18Program.Send8BitLSBFirst(myScriptData[ctr].HexData);
                    }
                else if(myScriptData[ctr].Command==P18_P24Script.Commands.DELAYCLKON4THBIT)
                    {
                    temp=String.Format("Sending 4-bit clock with delay 5 msec\r\n");
                    SetStatusString(temp);
                    myPIC18Program.DelayOn4thClk(myScriptData[ctr].Delay);
                    myPIC18Program.Send8BitLSBFirst(myScriptData[ctr].HexData);
                    continue;
                    }
                Thread.Sleep(myScriptData[ctr].Delay);
                }
            SetStatusString("Done!");
            }
        else
            {
            SetStatusString("Aborted!\r\n");
            }
        }
        



        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
        Application.Exit();
        }



        private void btnShowSampleScript_Click(object sender, EventArgs e)
        {
        txtStatus.Text=File.ReadAllText(Application.StartupPath + "\\" + "samplescript.txt");
        }

        private void btnReadDevID_Click(object sender, EventArgs e)
        {
        txtStatus.Clear();
        string SelectedItem=cmbDevice.SelectedItem.ToString().Trim();
        if(SelectedItem==STR_PIC18F24J50)
            {
            PIC18F2xJxx p=new PIC18F2xJxx(myPIC18Program);
            txtStatus.AppendText("Starting Read Dev ID...\r\n");
            Application.DoEvents();
            ulong ? Result=p.ReadDeviceID();
            if(Result==null)
                txtStatus.AppendText("Error Reading Device ID!");
            else
                {
                if((Result&0xFFE0)==0x4C00)
                    {
                    string temp=String.Format("Found PIC18F24J50 Device ID: 0x{0:x4} Revision {1}",Result&0xFFE0,Result&0x1F);
                    txtStatus.AppendText(temp);
                    }
                else
                    txtStatus.AppendText("Device Unknown!");
                }
            }
        else
            {
            txtStatus.AppendText("Device Unknown!");
            }
        }




        private void btnErase_Click(object sender, EventArgs e)
        {
        //StringBuilder strResult=new StringBuilder();
        txtStatus.Clear();
        string SelectedItem=cmbDevice.SelectedItem.ToString().Trim();
        if(SelectedItem==STR_PIC18F24J50)
            {
            PIC18F2xJxx p=new PIC18F2xJxx(myPIC18Program);
            txtStatus.AppendText("Starting Erase...\r\n");
            Application.DoEvents();
            if(p.Erase()==true)
                txtStatus.AppendText("Erase Operation Done!");
            else 
                txtStatus.AppendText("Erase Operation Unsuccessful!");
            }
        else
            {
            txtStatus.AppendText("Device Unknown!");
            }
        }



        private void btnProgramMCU_Click(object sender, EventArgs e)
        {
        string HexFileName=txtHexFileName.Text.Trim();
        if(HexFileName==String.Empty)
            {
            MessageBox.Show("No File Specified!",FRM_TITLE,MessageBoxButtons.OK,MessageBoxIcon.Error);
            return;
            }

        txtStatus.Clear();
        string SelectedItem=cmbDevice.SelectedItem.ToString().Trim();
        if(SelectedItem==STR_PIC18F24J50)
            {
            PIC18F2xJxx p=new PIC18F2xJxx(myPIC18Program);
            txtStatus.AppendText("Starting Erase!\r\n");
            Application.DoEvents();
            if(p.Erase()==true)
                txtStatus.AppendText("Erase Operation Done!\r\n");
            else 
                {
                txtStatus.AppendText("Erase Operation Unsuccessful!");
                return;
                }

            txtStatus.AppendText("Starting to Program! Please wait...\r\n");
            Application.DoEvents();
            if(p.Program(HexFileName,txtStatus)==true)
                txtStatus.AppendText("Program Operation Done!");
            else 
                {
                txtStatus.AppendText("Program Operation Unsuccessful!");
                return;
                }
            }
        else
            {
            txtStatus.AppendText("Device Unknown!");
            }
        }





        private void btnReadMCU_Click(object sender, EventArgs e)
        {
        MessageBox.Show("in progress :)");
        }

        private void btnChooseHex_Click(object sender, EventArgs e)
        {
        if(ofdHex.ShowDialog()==DialogResult.OK)
            {
            txtHexFileName.Text=ofdHex.FileName.Trim();
            toolTip1.SetToolTip(txtHexFileName,txtHexFileName.Text);
            }
        }





#if N_COMP
        private void btnEraseChip_Click(object sender, EventArgs e)
        {
        txtStatus.Clear();

        SetStatusString("Pinging Bus Pirate...\r\n");
        if(myPIC24Program.MCLRLow()==false)
            {
            SetStatusString("Error Pinging Bus Pirate!\r\n");
            MessageBox.Show("No Response from Bus Pirate!","Error",MessageBoxButtons.OK,MessageBoxIcon.Error);
            return;
            }
        myPIC24Program.EraseChip();
        SetStatusString("Erase Instruction Done!\r\n");
        }



        private void btnReadDevID_Click(object sender, EventArgs e)
        {
        txtStatus.Clear();

        SetStatusString("Pinging Bus Pirate...\r\n");
        if(myPIC24Program.MCLRLow()==false)
            {
            SetStatusString("Error Pinging Bus Pirate!\r\n");
            MessageBox.Show("No Response from Bus Pirate!","Error",MessageBoxButtons.OK,MessageBoxIcon.Error);
            return;
            }
        uint ? ReadDevID=myPIC24Program.ReadDevID();
        string temp= String.Format("Device ID: 0x{0:x4}!\r\n",ReadDevID);
        SetStatusString(temp);
        }
#endif


#if N_COMP
        private void EraseChip()
        {
        myPIC24Program.EnterICSPMode(PIC24Program.SECURE_ID_NORMAL_ICSP);
        myPIC24Program.SendSixSerialExec(true,true,0x040200);

        myPIC24Program.SendSixSerialExec(true,false,0x040200);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);

        myPIC24Program.SendSixSerialExec(true,false,0x040200);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0x2404FA);
        myPIC24Program.SendSixSerialExec(true,false,0x883B0A);

        myPIC24Program.SendSixSerialExec(true,false,0xA8E761);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);


        myPIC24Program.SendSixSerialExec(true,false,0xA9E761);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);
        myPIC24Program.SendSixSerialExec(true,false,0);

        myPIC24Program.ExitICSPMode();
        }
#endif


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
