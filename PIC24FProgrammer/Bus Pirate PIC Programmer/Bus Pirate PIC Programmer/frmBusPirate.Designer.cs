namespace WindowsFormsApplication1
{
    partial class frmBusPirate
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
        if (disposing && (components != null))
        {
        components.Dispose();
        }
        base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
        this.components = new System.ComponentModel.Container();
        this.grpSerial = new System.Windows.Forms.GroupBox();
        this.btnConnect = new System.Windows.Forms.Button();
        this.cmbSerial = new System.Windows.Forms.ComboBox();
        this.txtStatus = new System.Windows.Forms.TextBox();
        this.btnRunTest = new System.Windows.Forms.Button();
        this.btnInitBusPirate = new System.Windows.Forms.Button();
        this.panel1 = new System.Windows.Forms.Panel();
        this.btnReadData = new System.Windows.Forms.Button();
        this.btnSend24Bit = new System.Windows.Forms.Button();
        this.txtReadData = new System.Windows.Forms.TextBox();
        this.mtxt_SendData = new System.Windows.Forms.MaskedTextBox();
        this.label1 = new System.Windows.Forms.Label();
        this.btnInitMCLRPin = new System.Windows.Forms.Button();
        this.btnExitMCLR = new System.Windows.Forms.Button();
        this.btnInitICSP = new System.Windows.Forms.Button();
        this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
        this.tabBPControls = new System.Windows.Forms.TabControl();
        this.tabPage1 = new System.Windows.Forms.TabPage();
        this.tabPage2 = new System.Windows.Forms.TabPage();
        this.tabPage3 = new System.Windows.Forms.TabPage();
        this.btnOpenAndLoadScript = new System.Windows.Forms.Button();
        this.ofdScipt = new System.Windows.Forms.OpenFileDialog();
        this.menuStrip1 = new System.Windows.Forms.MenuStrip();
        this.fToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.btnShowSampleScript = new System.Windows.Forms.Button();
        this.grpSerial.SuspendLayout();
        this.panel1.SuspendLayout();
        this.tabBPControls.SuspendLayout();
        this.tabPage1.SuspendLayout();
        this.tabPage2.SuspendLayout();
        this.tabPage3.SuspendLayout();
        this.menuStrip1.SuspendLayout();
        this.SuspendLayout();
        // 
        // grpSerial
        // 
        this.grpSerial.Controls.Add(this.btnConnect);
        this.grpSerial.Controls.Add(this.cmbSerial);
        this.grpSerial.Location = new System.Drawing.Point(13, 35);
        this.grpSerial.Name = "grpSerial";
        this.grpSerial.Size = new System.Drawing.Size(140, 113);
        this.grpSerial.TabIndex = 0;
        this.grpSerial.TabStop = false;
        this.grpSerial.Text = "Serial Port";
        // 
        // btnConnect
        // 
        this.btnConnect.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.btnConnect.Location = new System.Drawing.Point(7, 46);
        this.btnConnect.Name = "btnConnect";
        this.btnConnect.Size = new System.Drawing.Size(126, 61);
        this.btnConnect.TabIndex = 1;
        this.btnConnect.Text = "Connect";
        this.btnConnect.UseVisualStyleBackColor = true;
        this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
        // 
        // cmbSerial
        // 
        this.cmbSerial.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
        this.cmbSerial.FormattingEnabled = true;
        this.cmbSerial.Location = new System.Drawing.Point(6, 19);
        this.cmbSerial.Name = "cmbSerial";
        this.cmbSerial.Size = new System.Drawing.Size(126, 21);
        this.cmbSerial.TabIndex = 0;
        // 
        // txtStatus
        // 
        this.txtStatus.Location = new System.Drawing.Point(13, 154);
        this.txtStatus.Multiline = true;
        this.txtStatus.Name = "txtStatus";
        this.txtStatus.ReadOnly = true;
        this.txtStatus.ScrollBars = System.Windows.Forms.ScrollBars.Both;
        this.txtStatus.Size = new System.Drawing.Size(487, 156);
        this.txtStatus.TabIndex = 1;
        // 
        // btnRunTest
        // 
        this.btnRunTest.Enabled = false;
        this.btnRunTest.Location = new System.Drawing.Point(529, 180);
        this.btnRunTest.Name = "btnRunTest";
        this.btnRunTest.Size = new System.Drawing.Size(139, 23);
        this.btnRunTest.TabIndex = 2;
        this.btnRunTest.Text = "Run Test";
        this.btnRunTest.UseVisualStyleBackColor = true;
        this.btnRunTest.Visible = false;
        this.btnRunTest.Click += new System.EventHandler(this.btnRunTest_Click);
        // 
        // btnInitBusPirate
        // 
        this.btnInitBusPirate.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.btnInitBusPirate.Location = new System.Drawing.Point(6, 6);
        this.btnInitBusPirate.Name = "btnInitBusPirate";
        this.btnInitBusPirate.Size = new System.Drawing.Size(321, 73);
        this.btnInitBusPirate.TabIndex = 9;
        this.btnInitBusPirate.Text = "Initialize Bus Pirate";
        this.toolTip1.SetToolTip(this.btnInitBusPirate, "This initializes the peripheral and mode configuration.");
        this.btnInitBusPirate.UseVisualStyleBackColor = true;
        this.btnInitBusPirate.Click += new System.EventHandler(this.btnInitBusPirate_Click);
        // 
        // panel1
        // 
        this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
        this.panel1.Controls.Add(this.btnReadData);
        this.panel1.Controls.Add(this.btnSend24Bit);
        this.panel1.Controls.Add(this.txtReadData);
        this.panel1.Controls.Add(this.mtxt_SendData);
        this.panel1.Controls.Add(this.label1);
        this.panel1.Location = new System.Drawing.Point(151, 11);
        this.panel1.Name = "panel1";
        this.panel1.Size = new System.Drawing.Size(175, 63);
        this.panel1.TabIndex = 8;
        // 
        // btnReadData
        // 
        this.btnReadData.Location = new System.Drawing.Point(3, 33);
        this.btnReadData.Name = "btnReadData";
        this.btnReadData.Size = new System.Drawing.Size(65, 23);
        this.btnReadData.TabIndex = 2;
        this.btnReadData.Text = "Read";
        this.btnReadData.UseVisualStyleBackColor = true;
        this.btnReadData.Click += new System.EventHandler(this.btnReadData_Click);
        // 
        // btnSend24Bit
        // 
        this.btnSend24Bit.Location = new System.Drawing.Point(3, 4);
        this.btnSend24Bit.Name = "btnSend24Bit";
        this.btnSend24Bit.Size = new System.Drawing.Size(65, 23);
        this.btnSend24Bit.TabIndex = 0;
        this.btnSend24Bit.Text = "Send";
        this.btnSend24Bit.UseVisualStyleBackColor = true;
        this.btnSend24Bit.Click += new System.EventHandler(this.btnSend24Bit_Click);
        // 
        // txtReadData
        // 
        this.txtReadData.Location = new System.Drawing.Point(74, 35);
        this.txtReadData.Name = "txtReadData";
        this.txtReadData.ReadOnly = true;
        this.txtReadData.Size = new System.Drawing.Size(92, 20);
        this.txtReadData.TabIndex = 8;
        // 
        // mtxt_SendData
        // 
        this.mtxt_SendData.Location = new System.Drawing.Point(91, 6);
        this.mtxt_SendData.Mask = "aaaaaa";
        this.mtxt_SendData.Name = "mtxt_SendData";
        this.mtxt_SendData.Size = new System.Drawing.Size(75, 20);
        this.mtxt_SendData.TabIndex = 1;
        this.toolTip1.SetToolTip(this.mtxt_SendData, " Enter Hexadecimal Here!");
        // 
        // label1
        // 
        this.label1.AutoSize = true;
        this.label1.Location = new System.Drawing.Point(74, 9);
        this.label1.Name = "label1";
        this.label1.Size = new System.Drawing.Size(18, 13);
        this.label1.TabIndex = 11;
        this.label1.Text = "0x";
        // 
        // btnInitMCLRPin
        // 
        this.btnInitMCLRPin.Location = new System.Drawing.Point(6, 46);
        this.btnInitMCLRPin.Name = "btnInitMCLRPin";
        this.btnInitMCLRPin.Size = new System.Drawing.Size(65, 23);
        this.btnInitMCLRPin.TabIndex = 1;
        this.btnInitMCLRPin.Text = "MCLR Hi";
        this.btnInitMCLRPin.UseVisualStyleBackColor = true;
        this.btnInitMCLRPin.Click += new System.EventHandler(this.btnInitMCLRPin_Click);
        // 
        // btnExitMCLR
        // 
        this.btnExitMCLR.Location = new System.Drawing.Point(75, 46);
        this.btnExitMCLR.Name = "btnExitMCLR";
        this.btnExitMCLR.Size = new System.Drawing.Size(70, 23);
        this.btnExitMCLR.TabIndex = 2;
        this.btnExitMCLR.Text = "MCLR Low";
        this.btnExitMCLR.UseVisualStyleBackColor = true;
        this.btnExitMCLR.Click += new System.EventHandler(this.btnExitMCLR_Click);
        // 
        // btnInitICSP
        // 
        this.btnInitICSP.Location = new System.Drawing.Point(6, 15);
        this.btnInitICSP.Name = "btnInitICSP";
        this.btnInitICSP.Size = new System.Drawing.Size(139, 23);
        this.btnInitICSP.TabIndex = 0;
        this.btnInitICSP.Text = "Init ICSP";
        this.toolTip1.SetToolTip(this.btnInitICSP, "A forced NOP is sent here as well.");
        this.btnInitICSP.UseVisualStyleBackColor = true;
        this.btnInitICSP.Click += new System.EventHandler(this.btnInitMCLR_Click);
        // 
        // tabBPControls
        // 
        this.tabBPControls.Controls.Add(this.tabPage1);
        this.tabBPControls.Controls.Add(this.tabPage2);
        this.tabBPControls.Controls.Add(this.tabPage3);
        this.tabBPControls.Location = new System.Drawing.Point(159, 37);
        this.tabBPControls.Name = "tabBPControls";
        this.tabBPControls.SelectedIndex = 0;
        this.tabBPControls.Size = new System.Drawing.Size(341, 111);
        this.tabBPControls.TabIndex = 0;
        // 
        // tabPage1
        // 
        this.tabPage1.Controls.Add(this.btnInitBusPirate);
        this.tabPage1.Location = new System.Drawing.Point(4, 22);
        this.tabPage1.Name = "tabPage1";
        this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
        this.tabPage1.Size = new System.Drawing.Size(333, 85);
        this.tabPage1.TabIndex = 0;
        this.tabPage1.Text = "Initalization";
        this.tabPage1.UseVisualStyleBackColor = true;
        // 
        // tabPage2
        // 
        this.tabPage2.Controls.Add(this.panel1);
        this.tabPage2.Controls.Add(this.btnInitICSP);
        this.tabPage2.Controls.Add(this.btnInitMCLRPin);
        this.tabPage2.Controls.Add(this.btnExitMCLR);
        this.tabPage2.Location = new System.Drawing.Point(4, 22);
        this.tabPage2.Name = "tabPage2";
        this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
        this.tabPage2.Size = new System.Drawing.Size(333, 85);
        this.tabPage2.TabIndex = 1;
        this.tabPage2.Text = "Manual Control";
        this.tabPage2.UseVisualStyleBackColor = true;
        // 
        // tabPage3
        // 
        this.tabPage3.Controls.Add(this.btnShowSampleScript);
        this.tabPage3.Controls.Add(this.btnOpenAndLoadScript);
        this.tabPage3.Location = new System.Drawing.Point(4, 22);
        this.tabPage3.Name = "tabPage3";
        this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
        this.tabPage3.Size = new System.Drawing.Size(333, 85);
        this.tabPage3.TabIndex = 2;
        this.tabPage3.Text = "Script Mode";
        this.tabPage3.UseVisualStyleBackColor = true;
        // 
        // btnOpenAndLoadScript
        // 
        this.btnOpenAndLoadScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.btnOpenAndLoadScript.Location = new System.Drawing.Point(6, 5);
        this.btnOpenAndLoadScript.Name = "btnOpenAndLoadScript";
        this.btnOpenAndLoadScript.Size = new System.Drawing.Size(321, 34);
        this.btnOpenAndLoadScript.TabIndex = 0;
        this.btnOpenAndLoadScript.Text = "Open and Load Script";
        this.btnOpenAndLoadScript.UseVisualStyleBackColor = true;
        this.btnOpenAndLoadScript.Click += new System.EventHandler(this.btnOpenAndLoadScript_Click);
        // 
        // ofdScipt
        // 
        this.ofdScipt.Filter = ".NET Programmer Script File|*.scrp24";
        // 
        // menuStrip1
        // 
        this.menuStrip1.BackColor = System.Drawing.Color.Silver;
        this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fToolStripMenuItem});
        this.menuStrip1.Location = new System.Drawing.Point(0, 0);
        this.menuStrip1.Name = "menuStrip1";
        this.menuStrip1.Size = new System.Drawing.Size(508, 24);
        this.menuStrip1.TabIndex = 5;
        this.menuStrip1.Text = "menuStrip1";
        // 
        // fToolStripMenuItem
        // 
        this.fToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
        this.fToolStripMenuItem.Name = "fToolStripMenuItem";
        this.fToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
        this.fToolStripMenuItem.Text = "File";
        // 
        // exitToolStripMenuItem
        // 
        this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
        this.exitToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
        this.exitToolStripMenuItem.Text = "Exit";
        this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
        // 
        // btnShowSampleScript
        // 
        this.btnShowSampleScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.btnShowSampleScript.Location = new System.Drawing.Point(6, 45);
        this.btnShowSampleScript.Name = "btnShowSampleScript";
        this.btnShowSampleScript.Size = new System.Drawing.Size(321, 34);
        this.btnShowSampleScript.TabIndex = 1;
        this.btnShowSampleScript.Text = "Show Sample Script";
        this.btnShowSampleScript.UseVisualStyleBackColor = true;
        this.btnShowSampleScript.Click += new System.EventHandler(this.btnShowSampleScript_Click);
        // 
        // frmBusPirate
        // 
        this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(508, 320);
        this.Controls.Add(this.btnRunTest);
        this.Controls.Add(this.tabBPControls);
        this.Controls.Add(this.txtStatus);
        this.Controls.Add(this.grpSerial);
        this.Controls.Add(this.menuStrip1);
        this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
        this.MainMenuStrip = this.menuStrip1;
        this.MaximizeBox = false;
        this.Name = "frmBusPirate";
        this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
        this.Text = "Form1";
        this.Load += new System.EventHandler(this.frmBusPirate_Load);
        this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmBusPirate_FormClosing);
        this.grpSerial.ResumeLayout(false);
        this.panel1.ResumeLayout(false);
        this.panel1.PerformLayout();
        this.tabBPControls.ResumeLayout(false);
        this.tabPage1.ResumeLayout(false);
        this.tabPage2.ResumeLayout(false);
        this.tabPage3.ResumeLayout(false);
        this.menuStrip1.ResumeLayout(false);
        this.menuStrip1.PerformLayout();
        this.ResumeLayout(false);
        this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox grpSerial;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.ComboBox cmbSerial;
        private System.Windows.Forms.TextBox txtStatus;
        private System.Windows.Forms.Button btnRunTest;
        private System.Windows.Forms.Button btnExitMCLR;
        private System.Windows.Forms.Button btnInitICSP;
        private System.Windows.Forms.Button btnInitMCLRPin;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button btnReadData;
        private System.Windows.Forms.Button btnSend24Bit;
        private System.Windows.Forms.TextBox txtReadData;
        private System.Windows.Forms.MaskedTextBox mtxt_SendData;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnInitBusPirate;
        private System.Windows.Forms.TabControl tabBPControls;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Button btnOpenAndLoadScript;
        private System.Windows.Forms.OpenFileDialog ofdScipt;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.Button btnShowSampleScript;
    }
}

