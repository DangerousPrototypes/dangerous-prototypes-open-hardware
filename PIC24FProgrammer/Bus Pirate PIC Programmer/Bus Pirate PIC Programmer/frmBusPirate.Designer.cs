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
        this.grpSerial = new System.Windows.Forms.GroupBox();
        this.cmbSerial = new System.Windows.Forms.ComboBox();
        this.btnConnect = new System.Windows.Forms.Button();
        this.txtStatus = new System.Windows.Forms.TextBox();
        this.btnRunTest = new System.Windows.Forms.Button();
        this.grpTest = new System.Windows.Forms.GroupBox();
        this.grpSerial.SuspendLayout();
        this.grpTest.SuspendLayout();
        this.SuspendLayout();
        // 
        // grpSerial
        // 
        this.grpSerial.Controls.Add(this.btnConnect);
        this.grpSerial.Controls.Add(this.cmbSerial);
        this.grpSerial.Location = new System.Drawing.Point(12, 12);
        this.grpSerial.Name = "grpSerial";
        this.grpSerial.Size = new System.Drawing.Size(138, 78);
        this.grpSerial.TabIndex = 0;
        this.grpSerial.TabStop = false;
        this.grpSerial.Text = "Serial Port";
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
        // btnConnect
        // 
        this.btnConnect.Location = new System.Drawing.Point(6, 46);
        this.btnConnect.Name = "btnConnect";
        this.btnConnect.Size = new System.Drawing.Size(126, 23);
        this.btnConnect.TabIndex = 1;
        this.btnConnect.Text = "Connect";
        this.btnConnect.UseVisualStyleBackColor = true;
        this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
        // 
        // txtStatus
        // 
        this.txtStatus.Location = new System.Drawing.Point(12, 96);
        this.txtStatus.Multiline = true;
        this.txtStatus.Name = "txtStatus";
        this.txtStatus.ReadOnly = true;
        this.txtStatus.ScrollBars = System.Windows.Forms.ScrollBars.Both;
        this.txtStatus.Size = new System.Drawing.Size(284, 186);
        this.txtStatus.TabIndex = 1;
        // 
        // btnRunTest
        // 
        this.btnRunTest.Location = new System.Drawing.Point(7, 25);
        this.btnRunTest.Name = "btnRunTest";
        this.btnRunTest.Size = new System.Drawing.Size(126, 23);
        this.btnRunTest.TabIndex = 2;
        this.btnRunTest.Text = "RunTest";
        this.btnRunTest.UseVisualStyleBackColor = true;
        this.btnRunTest.Click += new System.EventHandler(this.btnRunTest_Click);
        // 
        // grpTest
        // 
        this.grpTest.Controls.Add(this.btnRunTest);
        this.grpTest.Location = new System.Drawing.Point(156, 18);
        this.grpTest.Name = "grpTest";
        this.grpTest.Size = new System.Drawing.Size(140, 72);
        this.grpTest.TabIndex = 3;
        this.grpTest.TabStop = false;
        this.grpTest.Text = "Test";
        // 
        // frmBusPirate
        // 
        this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(313, 299);
        this.Controls.Add(this.grpTest);
        this.Controls.Add(this.txtStatus);
        this.Controls.Add(this.grpSerial);
        this.Name = "frmBusPirate";
        this.Text = "Form1";
        this.Load += new System.EventHandler(this.frmBusPirate_Load);
        this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmBusPirate_FormClosing);
        this.grpSerial.ResumeLayout(false);
        this.grpTest.ResumeLayout(false);
        this.ResumeLayout(false);
        this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox grpSerial;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.ComboBox cmbSerial;
        private System.Windows.Forms.TextBox txtStatus;
        private System.Windows.Forms.Button btnRunTest;
        private System.Windows.Forms.GroupBox grpTest;
    }
}

