//-----------------------------------------------------------------------------
//    This file is part of ds30 Loader GUI.
//
//    ds30 Loader GUI is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation.
//
//    ds30 Loader GUI is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with ds30 Loader GUI.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------- 

namespace ds30_Loader_GUI
{
	partial class frmDS30Loader
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose( bool disposing )
		{
			if ( disposing && ( components != null ) )
			{
				components.Dispose();
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmDS30Loader));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.mnuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEdit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuOptDebugmode = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuOptCheckVerStart = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuOptResetSettings = new System.Windows.Forms.ToolStripMenuItem();
            this.commandsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCmdAbort = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCmdDownload = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCmdCheckForBl = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuView = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewMicro = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewOntop = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewAdvanced = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewOutput = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuHelpDoc = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuHelpDocAPI = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuHelpCheckLatest = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuHelpVisitHomepage = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuHelpAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.lblVersion = new System.Windows.Forms.ToolStripStatusLabel();
            this.btnBrowse = new System.Windows.Forms.Button();
            this.cboBaudrate = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.cboCOMPort = new System.Windows.Forms.ComboBox();
            this.cboFamily = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cboDevice = new System.Windows.Forms.ComboBox();
            this.txtFilename = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.txtInfo = new System.Windows.Forms.RichTextBox();
            this.chkWriteConfigs = new System.Windows.Forms.CheckBox();
            this.chkNoGoto = new System.Windows.Forms.CheckBox();
            this.chkWriteEEPROM = new System.Windows.Forms.CheckBox();
            this.chkWriteProgram = new System.Windows.Forms.CheckBox();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.btnDownload2 = new System.Windows.Forms.ToolStripButton();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabAdvanced = new System.Windows.Forms.TabPage();
            this.chkAllowBlOverwrite = new System.Windows.Forms.CheckBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.txtTimeout = new System.Windows.Forms.TextBox();
            this.txtPolltime = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.label10 = new System.Windows.Forms.Label();
            this.cboResetBaudrate = new System.Windows.Forms.ComboBox();
            this.lblIncorrectFormat = new System.Windows.Forms.Label();
            this.txtResettime = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.txtResetCommand = new System.Windows.Forms.TextBox();
            this.rdbResetCommand = new System.Windows.Forms.RadioButton();
            this.rdbResetRts = new System.Windows.Forms.RadioButton();
            this.rdbResetDtr = new System.Windows.Forms.RadioButton();
            this.rdbResetManual = new System.Windows.Forms.RadioButton();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.rdbActivateNone = new System.Windows.Forms.RadioButton();
            this.rdActivatebRTS = new System.Windows.Forms.RadioButton();
            this.rdbActivateDTR = new System.Windows.Forms.RadioButton();
            this.tabTerminal = new System.Windows.Forms.TabPage();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.btnTermClearRx = new System.Windows.Forms.Button();
            this.txtTermTxHex = new System.Windows.Forms.TextBox();
            this.txtTermTxChar = new System.Windows.Forms.TextBox();
            this.txtTermRx = new System.Windows.Forms.TextBox();
            this.btnTermClose = new System.Windows.Forms.Button();
            this.chkTermSwitchTo = new System.Windows.Forms.CheckBox();
            this.btnTermOpen = new System.Windows.Forms.Button();
            this.cboTermBaudrate = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.toolStrip2 = new System.Windows.Forms.ToolStrip();
            this.btnCheck = new System.Windows.Forms.ToolStripButton();
            this.btnDownload = new System.Windows.Forms.ToolStripButton();
            this.btnAbort = new System.Windows.Forms.ToolStripButton();
            this.btnShowOutput = new System.Windows.Forms.ToolStripButton();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabAdvanced.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.tabTerminal.SuspendLayout();
            this.toolStrip2.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFile,
            this.mnuEdit,
            this.commandsToolStripMenuItem,
            this.mnuView,
            this.mnuHelp});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(391, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // mnuFile
            // 
            this.mnuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFileExit});
            this.mnuFile.Name = "mnuFile";
            this.mnuFile.Size = new System.Drawing.Size(37, 20);
            this.mnuFile.Text = "&File";
            // 
            // mnuFileExit
            // 
            this.mnuFileExit.Name = "mnuFileExit";
            this.mnuFileExit.Size = new System.Drawing.Size(92, 22);
            this.mnuFileExit.Text = "E&xit";
            this.mnuFileExit.Click += new System.EventHandler(this.mnuFileExit_Click);
            // 
            // mnuEdit
            // 
            this.mnuEdit.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuOptDebugmode,
            this.mnuOptCheckVerStart,
            this.mnuOptResetSettings});
            this.mnuEdit.Name = "mnuEdit";
            this.mnuEdit.Size = new System.Drawing.Size(61, 20);
            this.mnuEdit.Text = "&Options";
            // 
            // mnuOptDebugmode
            // 
            this.mnuOptDebugmode.CheckOnClick = true;
            this.mnuOptDebugmode.Name = "mnuOptDebugmode";
            this.mnuOptDebugmode.Size = new System.Drawing.Size(248, 22);
            this.mnuOptDebugmode.Text = "&Debugmode";
            this.mnuOptDebugmode.CheckedChanged += new System.EventHandler(this.mnuEditDebugmode_CheckedChanged);
            // 
            // mnuOptCheckVerStart
            // 
            this.mnuOptCheckVerStart.CheckOnClick = true;
            this.mnuOptCheckVerStart.Name = "mnuOptCheckVerStart";
            this.mnuOptCheckVerStart.Size = new System.Drawing.Size(248, 22);
            this.mnuOptCheckVerStart.Text = "Check for new version on startup";
            // 
            // mnuOptResetSettings
            // 
            this.mnuOptResetSettings.Name = "mnuOptResetSettings";
            this.mnuOptResetSettings.Size = new System.Drawing.Size(248, 22);
            this.mnuOptResetSettings.Text = "Reset all settings to default";
            this.mnuOptResetSettings.Click += new System.EventHandler(this.mnuOptResetSettings_Click);
            // 
            // commandsToolStripMenuItem
            // 
            this.commandsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuCmdAbort,
            this.mnuCmdDownload,
            this.mnuCmdCheckForBl});
            this.commandsToolStripMenuItem.Name = "commandsToolStripMenuItem";
            this.commandsToolStripMenuItem.Size = new System.Drawing.Size(81, 20);
            this.commandsToolStripMenuItem.Text = "&Commands";
            // 
            // mnuCmdAbort
            // 
            this.mnuCmdAbort.Enabled = false;
            this.mnuCmdAbort.Name = "mnuCmdAbort";
            this.mnuCmdAbort.ShortcutKeys = System.Windows.Forms.Keys.F3;
            this.mnuCmdAbort.Size = new System.Drawing.Size(186, 22);
            this.mnuCmdAbort.Text = "&Abort";
            this.mnuCmdAbort.Click += new System.EventHandler(this.mnuCmdAbort_Click);
            // 
            // mnuCmdDownload
            // 
            this.mnuCmdDownload.Name = "mnuCmdDownload";
            this.mnuCmdDownload.ShortcutKeys = System.Windows.Forms.Keys.F2;
            this.mnuCmdDownload.Size = new System.Drawing.Size(186, 22);
            this.mnuCmdDownload.Text = "&Download";
            this.mnuCmdDownload.Click += new System.EventHandler(this.mnuCmdDownload_Click);
            // 
            // mnuCmdCheckForBl
            // 
            this.mnuCmdCheckForBl.Name = "mnuCmdCheckForBl";
            this.mnuCmdCheckForBl.Size = new System.Drawing.Size(186, 22);
            this.mnuCmdCheckForBl.Text = "Check for bootloader";
            this.mnuCmdCheckForBl.Click += new System.EventHandler(this.mnuCmdCheckForBl_Click);
            // 
            // mnuView
            // 
            this.mnuView.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuViewMicro,
            this.mnuViewOntop,
            this.mnuViewAdvanced,
            this.mnuViewOutput});
            this.mnuView.Name = "mnuView";
            this.mnuView.Size = new System.Drawing.Size(44, 20);
            this.mnuView.Text = "&View";
            // 
            // mnuViewMicro
            // 
            this.mnuViewMicro.Name = "mnuViewMicro";
            this.mnuViewMicro.ShortcutKeys = System.Windows.Forms.Keys.F11;
            this.mnuViewMicro.Size = new System.Drawing.Size(174, 22);
            this.mnuViewMicro.Text = "&Micro";
            this.mnuViewMicro.Click += new System.EventHandler(this.mnuViewMicro_Click);
            // 
            // mnuViewOntop
            // 
            this.mnuViewOntop.CheckOnClick = true;
            this.mnuViewOntop.Name = "mnuViewOntop";
            this.mnuViewOntop.ShortcutKeys = System.Windows.Forms.Keys.F10;
            this.mnuViewOntop.Size = new System.Drawing.Size(174, 22);
            this.mnuViewOntop.Text = "&Always on top";
            this.mnuViewOntop.CheckedChanged += new System.EventHandler(this.mnuViewOntop_CheckedChanged);
            // 
            // mnuViewAdvanced
            // 
            this.mnuViewAdvanced.Checked = true;
            this.mnuViewAdvanced.CheckOnClick = true;
            this.mnuViewAdvanced.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mnuViewAdvanced.Name = "mnuViewAdvanced";
            this.mnuViewAdvanced.Size = new System.Drawing.Size(174, 22);
            this.mnuViewAdvanced.Text = "A&dvanced mode";
            this.mnuViewAdvanced.CheckedChanged += new System.EventHandler(this.mnuViewAdvanced_CheckedChanged);
            // 
            // mnuViewOutput
            // 
            this.mnuViewOutput.Checked = true;
            this.mnuViewOutput.CheckOnClick = true;
            this.mnuViewOutput.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mnuViewOutput.Name = "mnuViewOutput";
            this.mnuViewOutput.Size = new System.Drawing.Size(174, 22);
            this.mnuViewOutput.Text = "Output";
            this.mnuViewOutput.Click += new System.EventHandler(this.mnuViewOutput_Click);
            // 
            // mnuHelp
            // 
            this.mnuHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuHelpDoc,
            this.toolStripMenuItem2,
            this.mnuHelpCheckLatest,
            this.mnuHelpVisitHomepage,
            this.toolStripMenuItem1,
            this.mnuHelpAbout});
            this.mnuHelp.Name = "mnuHelp";
            this.mnuHelp.Size = new System.Drawing.Size(44, 20);
            this.mnuHelp.Text = "&Help";
            // 
            // mnuHelpDoc
            // 
            this.mnuHelpDoc.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuHelpDocAPI});
            this.mnuHelpDoc.Name = "mnuHelpDoc";
            this.mnuHelpDoc.Size = new System.Drawing.Size(188, 22);
            this.mnuHelpDoc.Text = "&Documents";
            this.mnuHelpDoc.Visible = false;
            // 
            // mnuHelpDocAPI
            // 
            this.mnuHelpDocAPI.Name = "mnuHelpDocAPI";
            this.mnuHelpDocAPI.Size = new System.Drawing.Size(92, 22);
            this.mnuHelpDocAPI.Text = "API";
            this.mnuHelpDocAPI.Click += new System.EventHandler(this.mnuHelpDocAPI_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(185, 6);
            this.toolStripMenuItem2.Visible = false;
            // 
            // mnuHelpCheckLatest
            // 
            this.mnuHelpCheckLatest.Name = "mnuHelpCheckLatest";
            this.mnuHelpCheckLatest.Size = new System.Drawing.Size(188, 22);
            this.mnuHelpCheckLatest.Text = "&Check latest version...";
            this.mnuHelpCheckLatest.Click += new System.EventHandler(this.mnuHelpCheckLatest_Click);
            // 
            // mnuHelpVisitHomepage
            // 
            this.mnuHelpVisitHomepage.Name = "mnuHelpVisitHomepage";
            this.mnuHelpVisitHomepage.Size = new System.Drawing.Size(188, 22);
            this.mnuHelpVisitHomepage.Text = "&Visit homepage";
            this.mnuHelpVisitHomepage.Click += new System.EventHandler(this.mnuHelpVisitHomepage_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(185, 6);
            // 
            // mnuHelpAbout
            // 
            this.mnuHelpAbout.Name = "mnuHelpAbout";
            this.mnuHelpAbout.Size = new System.Drawing.Size(188, 22);
            this.mnuHelpAbout.Text = "&About...";
            this.mnuHelpAbout.Click += new System.EventHandler(this.mnuHelpAbout_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolStripStatusLabel3,
            this.lblVersion});
            this.statusStrip1.Location = new System.Drawing.Point(0, 399);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(391, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(268, 17);
            this.toolStripStatusLabel1.Spring = true;
            this.toolStripStatusLabel1.Text = "Copyright © 08-09, Mikael Gustafsson";
            this.toolStripStatusLabel1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(77, 17);
            this.toolStripStatusLabel3.Text = "GPL Licensed";
            // 
            // lblVersion
            // 
            this.lblVersion.Name = "lblVersion";
            this.lblVersion.Size = new System.Drawing.Size(31, 17);
            this.lblVersion.Text = "1.2.2";
            // 
            // btnBrowse
            // 
            this.btnBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnBrowse.Location = new System.Drawing.Point(317, 11);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size(24, 20);
            this.btnBrowse.TabIndex = 2;
            this.btnBrowse.Text = "...";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new System.EventHandler(this.btnBrowse_Click);
            // 
            // cboBaudrate
            // 
            this.cboBaudrate.FormattingEnabled = true;
            this.cboBaudrate.Items.AddRange(new object[] {
            "9600",
            "14400",
            "19200",
            "28800",
            "38400",
            "56000",
            "57600",
            "115200",
            "128000",
            "256000"});
            this.cboBaudrate.Location = new System.Drawing.Point(67, 64);
            this.cboBaudrate.Name = "cboBaudrate";
            this.cboBaudrate.Size = new System.Drawing.Size(79, 21);
            this.cboBaudrate.TabIndex = 4;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(161, 40);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(39, 13);
            this.label4.TabIndex = 1;
            this.label4.Text = "Family:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 67);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Baudrate:";
            // 
            // cboCOMPort
            // 
            this.cboCOMPort.FormattingEnabled = true;
            this.cboCOMPort.Location = new System.Drawing.Point(67, 37);
            this.cboCOMPort.Name = "cboCOMPort";
            this.cboCOMPort.Size = new System.Drawing.Size(79, 21);
            this.cboCOMPort.TabIndex = 3;
            // 
            // cboFamily
            // 
            this.cboFamily.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboFamily.FormattingEnabled = true;
            this.cboFamily.Location = new System.Drawing.Point(206, 37);
            this.cboFamily.Name = "cboFamily";
            this.cboFamily.Size = new System.Drawing.Size(135, 21);
            this.cboFamily.Sorted = true;
            this.cboFamily.TabIndex = 5;
            this.cboFamily.SelectedIndexChanged += new System.EventHandler(this.cboFamily_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(11, 40);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(55, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "COM-port:";
            // 
            // cboDevice
            // 
            this.cboDevice.DropDownHeight = 400;
            this.cboDevice.FormattingEnabled = true;
            this.cboDevice.IntegralHeight = false;
            this.cboDevice.Location = new System.Drawing.Point(206, 64);
            this.cboDevice.Name = "cboDevice";
            this.cboDevice.Size = new System.Drawing.Size(135, 21);
            this.cboDevice.Sorted = true;
            this.cboDevice.TabIndex = 6;
            this.cboDevice.SelectedIndexChanged += new System.EventHandler(this.cboDevice_SelectedIndexChanged);
            // 
            // txtFilename
            // 
            this.txtFilename.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.txtFilename.Location = new System.Drawing.Point(67, 11);
            this.txtFilename.Name = "txtFilename";
            this.txtFilename.ReadOnly = true;
            this.txtFilename.Size = new System.Drawing.Size(244, 20);
            this.txtFilename.TabIndex = 1;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(161, 67);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "Device:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 14);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Hex-file:";
            // 
            // progressBar
            // 
            this.progressBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.progressBar.Location = new System.Drawing.Point(271, 7);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(108, 10);
            this.progressBar.TabIndex = 7;
            this.progressBar.Value = 50;
            this.progressBar.Visible = false;
            // 
            // txtInfo
            // 
            this.txtInfo.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.txtInfo.BackColor = System.Drawing.SystemColors.Window;
            this.txtInfo.Location = new System.Drawing.Point(3, 3);
            this.txtInfo.Name = "txtInfo";
            this.txtInfo.ReadOnly = true;
            this.txtInfo.Size = new System.Drawing.Size(353, 143);
            this.txtInfo.TabIndex = 12;
            this.txtInfo.Text = "";
            this.txtInfo.TextChanged += new System.EventHandler(this.txtInfo_TextChanged);
            // 
            // chkWriteConfigs
            // 
            this.chkWriteConfigs.AutoSize = true;
            this.chkWriteConfigs.Location = new System.Drawing.Point(11, 60);
            this.chkWriteConfigs.Name = "chkWriteConfigs";
            this.chkWriteConfigs.Size = new System.Drawing.Size(88, 17);
            this.chkWriteConfigs.TabIndex = 13;
            this.chkWriteConfigs.Text = "Write configs";
            this.chkWriteConfigs.UseVisualStyleBackColor = true;
            // 
            // chkNoGoto
            // 
            this.chkNoGoto.AutoSize = true;
            this.chkNoGoto.Location = new System.Drawing.Point(11, 14);
            this.chkNoGoto.Name = "chkNoGoto";
            this.chkNoGoto.Size = new System.Drawing.Size(138, 17);
            this.chkNoGoto.TabIndex = 12;
            this.chkNoGoto.Text = "Don\'t write goto at 0x00";
            this.chkNoGoto.UseVisualStyleBackColor = true;
            this.chkNoGoto.CheckedChanged += new System.EventHandler(this.chkNoGoto_CheckedChanged);
            // 
            // chkWriteEEPROM
            // 
            this.chkWriteEEPROM.AutoSize = true;
            this.chkWriteEEPROM.Location = new System.Drawing.Point(14, 114);
            this.chkWriteEEPROM.Name = "chkWriteEEPROM";
            this.chkWriteEEPROM.Size = new System.Drawing.Size(89, 17);
            this.chkWriteEEPROM.TabIndex = 11;
            this.chkWriteEEPROM.Text = "Write eeprom";
            this.chkWriteEEPROM.UseVisualStyleBackColor = true;
            // 
            // chkWriteProgram
            // 
            this.chkWriteProgram.AutoSize = true;
            this.chkWriteProgram.Location = new System.Drawing.Point(14, 91);
            this.chkWriteProgram.Name = "chkWriteProgram";
            this.chkWriteProgram.Size = new System.Drawing.Size(92, 17);
            this.chkWriteProgram.TabIndex = 10;
            this.chkWriteProgram.Text = "Write program";
            this.chkWriteProgram.UseVisualStyleBackColor = true;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton1,
            this.btnDownload2});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(388, 25);
            this.toolStrip1.TabIndex = 16;
            this.toolStrip1.Text = "toolStrip1";
            this.toolStrip1.Visible = false;
            this.toolStrip1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.toolStrip1_MouseDown);
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(46, 22);
            this.toolStripButton1.Text = "Return";
            this.toolStripButton1.Click += new System.EventHandler(this.toolStripButton1_Click);
            // 
            // btnDownload2
            // 
            this.btnDownload2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.btnDownload2.Image = ((System.Drawing.Image)(resources.GetObject("btnDownload2.Image")));
            this.btnDownload2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnDownload2.Name = "btnDownload2";
            this.btnDownload2.Size = new System.Drawing.Size(65, 22);
            this.btnDownload2.Text = "Download";
            this.btnDownload2.Click += new System.EventHandler(this.btnDownload2_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabAdvanced);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Controls.Add(this.tabTerminal);
            this.tabControl1.Location = new System.Drawing.Point(3, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(357, 171);
            this.tabControl1.TabIndex = 0;
            this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1_SelectedIndexChanged);
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.Transparent;
            this.tabPage1.Controls.Add(this.chkWriteProgram);
            this.tabPage1.Controls.Add(this.btnBrowse);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.chkWriteEEPROM);
            this.tabPage1.Controls.Add(this.cboBaudrate);
            this.tabPage1.Controls.Add(this.label5);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Controls.Add(this.txtFilename);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.cboDevice);
            this.tabPage1.Controls.Add(this.cboCOMPort);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.cboFamily);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(349, 145);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Basic";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabAdvanced
            // 
            this.tabAdvanced.Controls.Add(this.chkAllowBlOverwrite);
            this.tabAdvanced.Controls.Add(this.chkNoGoto);
            this.tabAdvanced.Controls.Add(this.chkWriteConfigs);
            this.tabAdvanced.Location = new System.Drawing.Point(4, 22);
            this.tabAdvanced.Name = "tabAdvanced";
            this.tabAdvanced.Size = new System.Drawing.Size(349, 145);
            this.tabAdvanced.TabIndex = 5;
            this.tabAdvanced.Text = "Advanced";
            this.tabAdvanced.UseVisualStyleBackColor = true;
            // 
            // chkAllowBlOverwrite
            // 
            this.chkAllowBlOverwrite.AutoSize = true;
            this.chkAllowBlOverwrite.Location = new System.Drawing.Point(11, 37);
            this.chkAllowBlOverwrite.Name = "chkAllowBlOverwrite";
            this.chkAllowBlOverwrite.Size = new System.Drawing.Size(162, 17);
            this.chkAllowBlOverwrite.TabIndex = 14;
            this.chkAllowBlOverwrite.Text = "Allow overwrite of bootloader";
            this.chkAllowBlOverwrite.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.Color.Transparent;
            this.tabPage2.Controls.Add(this.txtTimeout);
            this.tabPage2.Controls.Add(this.txtPolltime);
            this.tabPage2.Controls.Add(this.label7);
            this.tabPage2.Controls.Add(this.label6);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(349, 145);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Timing";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // txtTimeout
            // 
            this.txtTimeout.Location = new System.Drawing.Point(96, 43);
            this.txtTimeout.Name = "txtTimeout";
            this.txtTimeout.Size = new System.Drawing.Size(43, 20);
            this.txtTimeout.TabIndex = 2;
            this.txtTimeout.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // txtPolltime
            // 
            this.txtPolltime.Location = new System.Drawing.Point(96, 17);
            this.txtPolltime.Name = "txtPolltime";
            this.txtPolltime.Size = new System.Drawing.Size(43, 20);
            this.txtPolltime.TabIndex = 1;
            this.txtPolltime.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(16, 46);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(70, 13);
            this.label7.TabIndex = 1;
            this.label7.Text = "Timeout [ms]:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(18, 20);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(68, 13);
            this.label6.TabIndex = 0;
            this.label6.Text = "Polltime [ms]:";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.label10);
            this.tabPage3.Controls.Add(this.cboResetBaudrate);
            this.tabPage3.Controls.Add(this.lblIncorrectFormat);
            this.tabPage3.Controls.Add(this.txtResettime);
            this.tabPage3.Controls.Add(this.label8);
            this.tabPage3.Controls.Add(this.txtResetCommand);
            this.tabPage3.Controls.Add(this.rdbResetCommand);
            this.tabPage3.Controls.Add(this.rdbResetRts);
            this.tabPage3.Controls.Add(this.rdbResetDtr);
            this.tabPage3.Controls.Add(this.rdbResetManual);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(349, 145);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Reset";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(160, 85);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(53, 13);
            this.label10.TabIndex = 17;
            this.label10.Text = "Baudrate:";
            // 
            // cboResetBaudrate
            // 
            this.cboResetBaudrate.Enabled = false;
            this.cboResetBaudrate.FormattingEnabled = true;
            this.cboResetBaudrate.Items.AddRange(new object[] {
            "9600",
            "14400",
            "19200",
            "28800",
            "38400",
            "56000",
            "57600",
            "115200",
            "128000",
            "256000"});
            this.cboResetBaudrate.Location = new System.Drawing.Point(228, 82);
            this.cboResetBaudrate.Name = "cboResetBaudrate";
            this.cboResetBaudrate.Size = new System.Drawing.Size(79, 21);
            this.cboResetBaudrate.TabIndex = 16;
            // 
            // lblIncorrectFormat
            // 
            this.lblIncorrectFormat.AutoSize = true;
            this.lblIncorrectFormat.ForeColor = System.Drawing.Color.Red;
            this.lblIncorrectFormat.Location = new System.Drawing.Point(25, 129);
            this.lblIncorrectFormat.Name = "lblIncorrectFormat";
            this.lblIncorrectFormat.Size = new System.Drawing.Size(81, 13);
            this.lblIncorrectFormat.TabIndex = 15;
            this.lblIncorrectFormat.Text = "Incorrect format";
            this.lblIncorrectFormat.Visible = false;
            // 
            // txtResettime
            // 
            this.txtResettime.Enabled = false;
            this.txtResettime.Location = new System.Drawing.Point(228, 59);
            this.txtResettime.Name = "txtResettime";
            this.txtResettime.Size = new System.Drawing.Size(79, 20);
            this.txtResettime.TabIndex = 6;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(131, 62);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(82, 13);
            this.label8.TabIndex = 14;
            this.label8.Text = "Reset time [ms]:";
            // 
            // txtResetCommand
            // 
            this.txtResetCommand.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.txtResetCommand.Enabled = false;
            this.txtResetCommand.Location = new System.Drawing.Point(28, 109);
            this.txtResetCommand.Name = "txtResetCommand";
            this.txtResetCommand.Size = new System.Drawing.Size(306, 20);
            this.txtResetCommand.TabIndex = 3;
            this.txtResetCommand.TextChanged += new System.EventHandler(this.txtResetCommand_TextChanged);
            // 
            // rdbResetCommand
            // 
            this.rdbResetCommand.AutoSize = true;
            this.rdbResetCommand.Location = new System.Drawing.Point(11, 83);
            this.rdbResetCommand.Name = "rdbResetCommand";
            this.rdbResetCommand.Size = new System.Drawing.Size(75, 17);
            this.rdbResetCommand.TabIndex = 2;
            this.rdbResetCommand.Text = "Command:";
            this.rdbResetCommand.UseVisualStyleBackColor = true;
            this.rdbResetCommand.CheckedChanged += new System.EventHandler(this.rdbCommandReset_CheckedChanged);
            // 
            // rdbResetRts
            // 
            this.rdbResetRts.AutoSize = true;
            this.rdbResetRts.Location = new System.Drawing.Point(11, 37);
            this.rdbResetRts.Name = "rdbResetRts";
            this.rdbResetRts.Size = new System.Drawing.Size(47, 17);
            this.rdbResetRts.TabIndex = 4;
            this.rdbResetRts.Text = "RTS";
            this.rdbResetRts.UseVisualStyleBackColor = true;
            // 
            // rdbResetDtr
            // 
            this.rdbResetDtr.AutoSize = true;
            this.rdbResetDtr.Location = new System.Drawing.Point(11, 60);
            this.rdbResetDtr.Name = "rdbResetDtr";
            this.rdbResetDtr.Size = new System.Drawing.Size(48, 17);
            this.rdbResetDtr.TabIndex = 5;
            this.rdbResetDtr.Text = "DTR";
            this.rdbResetDtr.UseVisualStyleBackColor = true;
            // 
            // rdbResetManual
            // 
            this.rdbResetManual.AutoSize = true;
            this.rdbResetManual.Checked = true;
            this.rdbResetManual.Location = new System.Drawing.Point(11, 14);
            this.rdbResetManual.Name = "rdbResetManual";
            this.rdbResetManual.Size = new System.Drawing.Size(60, 17);
            this.rdbResetManual.TabIndex = 1;
            this.rdbResetManual.TabStop = true;
            this.rdbResetManual.Text = "Manual";
            this.rdbResetManual.UseVisualStyleBackColor = true;
            this.rdbResetManual.CheckedChanged += new System.EventHandler(this.rdbResetManual_CheckedChanged);
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.rdbActivateNone);
            this.tabPage4.Controls.Add(this.rdActivatebRTS);
            this.tabPage4.Controls.Add(this.rdbActivateDTR);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(349, 145);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "Activation";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // rdbActivateNone
            // 
            this.rdbActivateNone.AutoSize = true;
            this.rdbActivateNone.Checked = true;
            this.rdbActivateNone.Location = new System.Drawing.Point(11, 14);
            this.rdbActivateNone.Name = "rdbActivateNone";
            this.rdbActivateNone.Size = new System.Drawing.Size(60, 17);
            this.rdbActivateNone.TabIndex = 5;
            this.rdbActivateNone.TabStop = true;
            this.rdbActivateNone.Text = "Manual";
            this.rdbActivateNone.UseVisualStyleBackColor = true;
            // 
            // rdActivatebRTS
            // 
            this.rdActivatebRTS.AutoSize = true;
            this.rdActivatebRTS.Location = new System.Drawing.Point(11, 37);
            this.rdActivatebRTS.Name = "rdActivatebRTS";
            this.rdActivatebRTS.Size = new System.Drawing.Size(47, 17);
            this.rdActivatebRTS.TabIndex = 4;
            this.rdActivatebRTS.Text = "RTS";
            this.rdActivatebRTS.UseVisualStyleBackColor = true;
            // 
            // rdbActivateDTR
            // 
            this.rdbActivateDTR.AutoSize = true;
            this.rdbActivateDTR.Location = new System.Drawing.Point(11, 60);
            this.rdbActivateDTR.Name = "rdbActivateDTR";
            this.rdbActivateDTR.Size = new System.Drawing.Size(48, 17);
            this.rdbActivateDTR.TabIndex = 3;
            this.rdbActivateDTR.Text = "DTR";
            this.rdbActivateDTR.UseVisualStyleBackColor = true;
            // 
            // tabTerminal
            // 
            this.tabTerminal.Controls.Add(this.label12);
            this.tabTerminal.Controls.Add(this.label11);
            this.tabTerminal.Controls.Add(this.btnTermClearRx);
            this.tabTerminal.Controls.Add(this.txtTermTxHex);
            this.tabTerminal.Controls.Add(this.txtTermTxChar);
            this.tabTerminal.Controls.Add(this.txtTermRx);
            this.tabTerminal.Controls.Add(this.btnTermClose);
            this.tabTerminal.Controls.Add(this.chkTermSwitchTo);
            this.tabTerminal.Controls.Add(this.btnTermOpen);
            this.tabTerminal.Controls.Add(this.cboTermBaudrate);
            this.tabTerminal.Controls.Add(this.label9);
            this.tabTerminal.Location = new System.Drawing.Point(4, 22);
            this.tabTerminal.Name = "tabTerminal";
            this.tabTerminal.Size = new System.Drawing.Size(349, 145);
            this.tabTerminal.TabIndex = 4;
            this.tabTerminal.Text = "Terminal";
            this.tabTerminal.UseVisualStyleBackColor = true;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(164, 71);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(29, 13);
            this.label12.TabIndex = 18;
            this.label12.Text = "Hex:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(12, 71);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(32, 13);
            this.label11.TabIndex = 18;
            this.label11.Text = "Char:";
            // 
            // btnTermClearRx
            // 
            this.btnTermClearRx.Location = new System.Drawing.Point(164, 39);
            this.btnTermClearRx.Name = "btnTermClearRx";
            this.btnTermClearRx.Size = new System.Drawing.Size(75, 23);
            this.btnTermClearRx.TabIndex = 17;
            this.btnTermClearRx.Text = "Clear Rx";
            this.btnTermClearRx.UseVisualStyleBackColor = true;
            this.btnTermClearRx.Click += new System.EventHandler(this.btnTermClearRx_Click);
            // 
            // txtTermTxHex
            // 
            this.txtTermTxHex.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.txtTermTxHex.Enabled = false;
            this.txtTermTxHex.Location = new System.Drawing.Point(199, 68);
            this.txtTermTxHex.Name = "txtTermTxHex";
            this.txtTermTxHex.Size = new System.Drawing.Size(136, 20);
            this.txtTermTxHex.TabIndex = 16;
            this.txtTermTxHex.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtTermTxHex_KeyDown);
            // 
            // txtTermTxChar
            // 
            this.txtTermTxChar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.txtTermTxChar.Enabled = false;
            this.txtTermTxChar.Location = new System.Drawing.Point(46, 68);
            this.txtTermTxChar.Name = "txtTermTxChar";
            this.txtTermTxChar.Size = new System.Drawing.Size(112, 20);
            this.txtTermTxChar.TabIndex = 16;
            this.txtTermTxChar.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtTermTxChar_KeyDown);
            // 
            // txtTermRx
            // 
            this.txtTermRx.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.txtTermRx.Location = new System.Drawing.Point(15, 94);
            this.txtTermRx.Multiline = true;
            this.txtTermRx.Name = "txtTermRx";
            this.txtTermRx.ReadOnly = true;
            this.txtTermRx.Size = new System.Drawing.Size(320, 38);
            this.txtTermRx.TabIndex = 15;
            // 
            // btnTermClose
            // 
            this.btnTermClose.Location = new System.Drawing.Point(245, 16);
            this.btnTermClose.Name = "btnTermClose";
            this.btnTermClose.Size = new System.Drawing.Size(75, 23);
            this.btnTermClose.TabIndex = 14;
            this.btnTermClose.Text = "Close";
            this.btnTermClose.UseVisualStyleBackColor = true;
            this.btnTermClose.Click += new System.EventHandler(this.btnTermClose_Click);
            // 
            // chkTermSwitchTo
            // 
            this.chkTermSwitchTo.AutoSize = true;
            this.chkTermSwitchTo.Location = new System.Drawing.Point(15, 45);
            this.chkTermSwitchTo.Name = "chkTermSwitchTo";
            this.chkTermSwitchTo.Size = new System.Drawing.Size(143, 17);
            this.chkTermSwitchTo.TabIndex = 13;
            this.chkTermSwitchTo.Text = "Switch to after download";
            this.chkTermSwitchTo.UseVisualStyleBackColor = true;
            // 
            // btnTermOpen
            // 
            this.btnTermOpen.Location = new System.Drawing.Point(164, 16);
            this.btnTermOpen.Name = "btnTermOpen";
            this.btnTermOpen.Size = new System.Drawing.Size(75, 23);
            this.btnTermOpen.TabIndex = 12;
            this.btnTermOpen.Text = "Open";
            this.btnTermOpen.UseVisualStyleBackColor = true;
            this.btnTermOpen.Click += new System.EventHandler(this.btnTermOpen_Click);
            // 
            // cboTermBaudrate
            // 
            this.cboTermBaudrate.FormattingEnabled = true;
            this.cboTermBaudrate.Items.AddRange(new object[] {
            "9600",
            "14400",
            "19200",
            "28800",
            "38400",
            "56000",
            "57600",
            "115200",
            "128000",
            "256000"});
            this.cboTermBaudrate.Location = new System.Drawing.Point(68, 18);
            this.cboTermBaudrate.Name = "cboTermBaudrate";
            this.cboTermBaudrate.Size = new System.Drawing.Size(79, 21);
            this.cboTermBaudrate.TabIndex = 10;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(12, 21);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(53, 13);
            this.label9.TabIndex = 11;
            this.label9.Text = "Baudrate:";
            // 
            // toolStrip2
            // 
            this.toolStrip2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.btnCheck,
            this.btnDownload,
            this.btnAbort,
            this.btnShowOutput});
            this.toolStrip2.Location = new System.Drawing.Point(0, 24);
            this.toolStrip2.Name = "toolStrip2";
            this.toolStrip2.Size = new System.Drawing.Size(391, 25);
            this.toolStrip2.TabIndex = 17;
            this.toolStrip2.Text = "toolStrip2";
            // 
            // btnCheck
            // 
            this.btnCheck.Image = ((System.Drawing.Image)(resources.GetObject("btnCheck.Image")));
            this.btnCheck.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnCheck.Name = "btnCheck";
            this.btnCheck.Size = new System.Drawing.Size(91, 22);
            this.btnCheck.Text = "Check for bl";
            this.btnCheck.Click += new System.EventHandler(this.btnCheck_Click);
            // 
            // btnDownload
            // 
            this.btnDownload.Image = ((System.Drawing.Image)(resources.GetObject("btnDownload.Image")));
            this.btnDownload.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnDownload.Name = "btnDownload";
            this.btnDownload.Size = new System.Drawing.Size(81, 22);
            this.btnDownload.Text = "Download";
            this.btnDownload.Click += new System.EventHandler(this.btnDownload_Click);
            // 
            // btnAbort
            // 
            this.btnAbort.Enabled = false;
            this.btnAbort.Image = ((System.Drawing.Image)(resources.GetObject("btnAbort.Image")));
            this.btnAbort.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnAbort.Name = "btnAbort";
            this.btnAbort.Size = new System.Drawing.Size(57, 22);
            this.btnAbort.Text = "Abort";
            this.btnAbort.Click += new System.EventHandler(this.btnAbort_Click);
            // 
            // btnShowOutput
            // 
            this.btnShowOutput.BackColor = System.Drawing.SystemColors.Control;
            this.btnShowOutput.Checked = true;
            this.btnShowOutput.CheckOnClick = true;
            this.btnShowOutput.CheckState = System.Windows.Forms.CheckState.Checked;
            this.btnShowOutput.Image = ((System.Drawing.Image)(resources.GetObject("btnShowOutput.Image")));
            this.btnShowOutput.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnShowOutput.Name = "btnShowOutput";
            this.btnShowOutput.Size = new System.Drawing.Size(65, 22);
            this.btnShowOutput.Text = "Output";
            this.btnShowOutput.CheckedChanged += new System.EventHandler(this.btnShowOutput_CheckedChanged);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(12, 52);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.tabControl1);
            this.splitContainer1.Panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer1_Panel1_Paint);
            this.splitContainer1.Panel1MinSize = 177;
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.txtInfo);
            this.splitContainer1.Size = new System.Drawing.Size(363, 330);
            this.splitContainer1.SplitterDistance = 177;
            this.splitContainer1.TabIndex = 19;
            // 
            // tabControl2
            // 
            this.tabControl2.Location = new System.Drawing.Point(375, 289);
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            this.tabControl2.Size = new System.Drawing.Size(16, 22);
            this.tabControl2.TabIndex = 20;
            this.tabControl2.Visible = false;
            // 
            // frmDS30Loader
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(391, 421);
            this.Controls.Add(this.tabControl2);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.toolStrip2);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.toolStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.MaximumSize = new System.Drawing.Size(5000, 5000);
            this.MinimumSize = new System.Drawing.Size(50, 36);
            this.Name = "frmDS30Loader";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ds30 Loader";
            this.Shown += new System.EventHandler(this.frmDSLoader_Shown);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.frmDSLoader_MouseDown);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmDSLoader_FormClosing);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabAdvanced.ResumeLayout(false);
            this.tabAdvanced.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            this.tabTerminal.ResumeLayout(false);
            this.tabTerminal.PerformLayout();
            this.toolStrip2.ResumeLayout(false);
            this.toolStrip2.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem mnuFile;
		private System.Windows.Forms.ToolStripMenuItem mnuFileExit;
		private System.Windows.Forms.StatusStrip statusStrip1;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel lblVersion;
		private System.Windows.Forms.ComboBox cboBaudrate;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.ComboBox cboCOMPort;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox txtFilename;
        private System.Windows.Forms.Label label1;
		private System.Windows.Forms.RichTextBox txtInfo;
		private System.Windows.Forms.Button btnBrowse;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.ProgressBar progressBar;
		private System.Windows.Forms.CheckBox chkWriteProgram;
		private System.Windows.Forms.CheckBox chkWriteEEPROM;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.CheckBox chkNoGoto;
		private System.Windows.Forms.ComboBox cboFamily;
		private System.Windows.Forms.CheckBox chkWriteConfigs;
		private System.Windows.Forms.ComboBox cboDevice;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ToolStripMenuItem mnuEdit;
        private System.Windows.Forms.ToolStripMenuItem mnuOptDebugmode;
        private System.Windows.Forms.ToolStripMenuItem mnuHelp;
        private System.Windows.Forms.ToolStripMenuItem mnuHelpCheckLatest;
        private System.Windows.Forms.ToolStripMenuItem mnuHelpAbout;
        private System.Windows.Forms.ToolStripMenuItem mnuHelpVisitHomepage;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.ToolStripButton btnDownload2;
        private System.Windows.Forms.ToolStripMenuItem mnuView;
        private System.Windows.Forms.ToolStripMenuItem mnuViewMicro;
        private System.Windows.Forms.ToolStripMenuItem mnuViewOntop;
        private System.Windows.Forms.ToolStripMenuItem commandsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mnuCmdDownload;
        private System.Windows.Forms.ToolStripMenuItem mnuCmdAbort;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TextBox txtTimeout;
        private System.Windows.Forms.TextBox txtPolltime;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TextBox txtResetCommand;
        private System.Windows.Forms.RadioButton rdbResetCommand;
        private System.Windows.Forms.RadioButton rdbResetRts;
        private System.Windows.Forms.RadioButton rdbResetDtr;
        private System.Windows.Forms.RadioButton rdbResetManual;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.TextBox txtResettime;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.RadioButton rdActivatebRTS;
        private System.Windows.Forms.RadioButton rdbActivateDTR;
        private System.Windows.Forms.RadioButton rdbActivateNone;
        private System.Windows.Forms.ToolStripMenuItem mnuOptCheckVerStart;
        private System.Windows.Forms.ToolStripMenuItem mnuHelpDoc;
        private System.Windows.Forms.ToolStripMenuItem mnuHelpDocAPI;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStrip toolStrip2;
        private System.Windows.Forms.ToolStripButton btnCheck;
        private System.Windows.Forms.ToolStripButton btnDownload;
        private System.Windows.Forms.ToolStripButton btnAbort;
        private System.Windows.Forms.ToolStripButton btnShowOutput;
        private System.Windows.Forms.Label lblIncorrectFormat;
        private System.Windows.Forms.TabPage tabTerminal;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Button btnTermOpen;
        private System.Windows.Forms.ComboBox cboTermBaudrate;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.CheckBox chkTermSwitchTo;
        private System.Windows.Forms.Button btnTermClose;
        private System.Windows.Forms.TextBox txtTermRx;
        private System.Windows.Forms.TextBox txtTermTxChar;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ComboBox cboResetBaudrate;
        private System.Windows.Forms.ToolStripMenuItem mnuOptResetSettings;
        private System.Windows.Forms.ToolStripMenuItem mnuViewAdvanced;
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.Button btnTermClearRx;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox txtTermTxHex;
        private System.Windows.Forms.TabPage tabAdvanced;
        private System.Windows.Forms.CheckBox chkAllowBlOverwrite;
        private System.Windows.Forms.ToolStripMenuItem mnuCmdCheckForBl;
        private System.Windows.Forms.ToolStripMenuItem mnuViewOutput;
	}
}

