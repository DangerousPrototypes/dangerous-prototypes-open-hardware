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
        this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
        this.tabBPControls = new System.Windows.Forms.TabControl();
        this.tabPage2 = new System.Windows.Forms.TabPage();
        this.btnReadMCU = new System.Windows.Forms.Button();
        this.btnProgramMCU = new System.Windows.Forms.Button();
        this.btnChooseHex = new System.Windows.Forms.Button();
        this.txtHexFileName = new System.Windows.Forms.TextBox();
        this.btnReadDevID = new System.Windows.Forms.Button();
        this.btnErase = new System.Windows.Forms.Button();
        this.cmbDevice = new System.Windows.Forms.ComboBox();
        this.label1 = new System.Windows.Forms.Label();
        this.tabPage3 = new System.Windows.Forms.TabPage();
        this.btnShowSampleScript = new System.Windows.Forms.Button();
        this.btnOpenAndLoadScript = new System.Windows.Forms.Button();
        this.ofdScipt = new System.Windows.Forms.OpenFileDialog();
        this.menuStrip1 = new System.Windows.Forms.MenuStrip();
        this.fToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.ofdHex = new System.Windows.Forms.OpenFileDialog();
        this.grpSerial.SuspendLayout();
        this.tabBPControls.SuspendLayout();
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
        this.toolTip1.SetToolTip(this.btnConnect, "Connect and Initialize Bus Pirate");
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
        this.txtStatus.Size = new System.Drawing.Size(487, 277);
        this.txtStatus.TabIndex = 1;
        // 
        // tabBPControls
        // 
        this.tabBPControls.Controls.Add(this.tabPage2);
        this.tabBPControls.Controls.Add(this.tabPage3);
        this.tabBPControls.Location = new System.Drawing.Point(159, 37);
        this.tabBPControls.Name = "tabBPControls";
        this.tabBPControls.SelectedIndex = 0;
        this.tabBPControls.Size = new System.Drawing.Size(341, 111);
        this.tabBPControls.TabIndex = 0;
        // 
        // tabPage2
        // 
        this.tabPage2.Controls.Add(this.btnReadMCU);
        this.tabPage2.Controls.Add(this.btnProgramMCU);
        this.tabPage2.Controls.Add(this.btnChooseHex);
        this.tabPage2.Controls.Add(this.txtHexFileName);
        this.tabPage2.Controls.Add(this.btnReadDevID);
        this.tabPage2.Controls.Add(this.btnErase);
        this.tabPage2.Controls.Add(this.cmbDevice);
        this.tabPage2.Controls.Add(this.label1);
        this.tabPage2.Location = new System.Drawing.Point(4, 22);
        this.tabPage2.Name = "tabPage2";
        this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
        this.tabPage2.Size = new System.Drawing.Size(333, 85);
        this.tabPage2.TabIndex = 3;
        this.tabPage2.Text = "Auto Mode";
        this.tabPage2.UseVisualStyleBackColor = true;
        // 
        // btnReadMCU
        // 
        this.btnReadMCU.Location = new System.Drawing.Point(249, 32);
        this.btnReadMCU.Name = "btnReadMCU";
        this.btnReadMCU.Size = new System.Drawing.Size(75, 46);
        this.btnReadMCU.TabIndex = 7;
        this.btnReadMCU.Text = "Read";
        this.btnReadMCU.UseVisualStyleBackColor = true;
        this.btnReadMCU.Click += new System.EventHandler(this.btnReadMCU_Click);
        // 
        // btnProgramMCU
        // 
        this.btnProgramMCU.Location = new System.Drawing.Point(168, 32);
        this.btnProgramMCU.Name = "btnProgramMCU";
        this.btnProgramMCU.Size = new System.Drawing.Size(75, 46);
        this.btnProgramMCU.TabIndex = 6;
        this.btnProgramMCU.Text = "Program";
        this.btnProgramMCU.UseVisualStyleBackColor = true;
        this.btnProgramMCU.Click += new System.EventHandler(this.btnProgramMCU_Click);
        // 
        // btnChooseHex
        // 
        this.btnChooseHex.Location = new System.Drawing.Point(303, 6);
        this.btnChooseHex.Name = "btnChooseHex";
        this.btnChooseHex.Size = new System.Drawing.Size(24, 23);
        this.btnChooseHex.TabIndex = 5;
        this.btnChooseHex.Text = "...";
        this.btnChooseHex.UseVisualStyleBackColor = true;
        this.btnChooseHex.Click += new System.EventHandler(this.btnChooseHex_Click);
        // 
        // txtHexFileName
        // 
        this.txtHexFileName.Location = new System.Drawing.Point(191, 6);
        this.txtHexFileName.Name = "txtHexFileName";
        this.txtHexFileName.ReadOnly = true;
        this.txtHexFileName.Size = new System.Drawing.Size(106, 20);
        this.txtHexFileName.TabIndex = 4;
        // 
        // btnReadDevID
        // 
        this.btnReadDevID.Location = new System.Drawing.Point(87, 33);
        this.btnReadDevID.Name = "btnReadDevID";
        this.btnReadDevID.Size = new System.Drawing.Size(75, 46);
        this.btnReadDevID.TabIndex = 3;
        this.btnReadDevID.Text = "Read Device ID";
        this.btnReadDevID.UseVisualStyleBackColor = true;
        this.btnReadDevID.Click += new System.EventHandler(this.btnReadDevID_Click);
        // 
        // btnErase
        // 
        this.btnErase.Location = new System.Drawing.Point(6, 33);
        this.btnErase.Name = "btnErase";
        this.btnErase.Size = new System.Drawing.Size(75, 46);
        this.btnErase.TabIndex = 2;
        this.btnErase.Text = "Erase";
        this.btnErase.UseVisualStyleBackColor = true;
        this.btnErase.Click += new System.EventHandler(this.btnErase_Click);
        // 
        // cmbDevice
        // 
        this.cmbDevice.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
        this.cmbDevice.FormattingEnabled = true;
        this.cmbDevice.Location = new System.Drawing.Point(87, 6);
        this.cmbDevice.Name = "cmbDevice";
        this.cmbDevice.Size = new System.Drawing.Size(98, 21);
        this.cmbDevice.TabIndex = 1;
        // 
        // label1
        // 
        this.label1.AutoSize = true;
        this.label1.Location = new System.Drawing.Point(4, 9);
        this.label1.Name = "label1";
        this.label1.Size = new System.Drawing.Size(77, 13);
        this.label1.TabIndex = 0;
        this.label1.Text = "Select Device:";
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
        this.ofdScipt.Filter = "PIC24 Script File|*.scrp24|PIC18 Script File|*.scrp18";
        // 
        // menuStrip1
        // 
        this.menuStrip1.BackColor = System.Drawing.Color.Silver;
        this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fToolStripMenuItem});
        this.menuStrip1.Location = new System.Drawing.Point(0, 0);
        this.menuStrip1.Name = "menuStrip1";
        this.menuStrip1.Size = new System.Drawing.Size(514, 24);
        this.menuStrip1.TabIndex = 5;
        this.menuStrip1.Text = "menuStrip1";
        // 
        // fToolStripMenuItem
        // 
        this.fToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
        this.fToolStripMenuItem.Name = "fToolStripMenuItem";
        this.fToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
        this.fToolStripMenuItem.Text = "File";
        // 
        // exitToolStripMenuItem
        // 
        this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
        this.exitToolStripMenuItem.Size = new System.Drawing.Size(92, 22);
        this.exitToolStripMenuItem.Text = "Exit";
        this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
        // 
        // ofdHex
        // 
        this.ofdHex.Filter = "Hex Files|*.hex";
        // 
        // frmBusPirate
        // 
        this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(514, 443);
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
        this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmBusPirate_FormClosing);
        this.Load += new System.EventHandler(this.frmBusPirate_Load);
        this.grpSerial.ResumeLayout(false);
        this.tabBPControls.ResumeLayout(false);
        this.tabPage2.ResumeLayout(false);
        this.tabPage2.PerformLayout();
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
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.TabControl tabBPControls;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Button btnOpenAndLoadScript;
        private System.Windows.Forms.OpenFileDialog ofdScipt;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.Button btnShowSampleScript;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button btnReadMCU;
        private System.Windows.Forms.Button btnProgramMCU;
        private System.Windows.Forms.Button btnChooseHex;
        private System.Windows.Forms.TextBox txtHexFileName;
        private System.Windows.Forms.Button btnReadDevID;
        private System.Windows.Forms.Button btnErase;
        private System.Windows.Forms.ComboBox cmbDevice;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.OpenFileDialog ofdHex;
    }
}

