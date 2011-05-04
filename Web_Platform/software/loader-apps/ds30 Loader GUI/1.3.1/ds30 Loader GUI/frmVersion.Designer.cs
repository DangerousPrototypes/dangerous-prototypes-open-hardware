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
    partial class frmVersion
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
            this.btnClose = new System.Windows.Forms.Button();
            this.btnDownload = new System.Windows.Forms.Button();
            this.btnUpdate = new System.Windows.Forms.Button();
            this.btnVisitHomepage = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.lblLVds30LoaderGUI = new System.Windows.Forms.Label();
            this.lblCVds30LoaderGUI = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lblCVds30Loader = new System.Windows.Forms.Label();
            this.lblCVGHelper = new System.Windows.Forms.Label();
            this.lblLVds30Loader = new System.Windows.Forms.Label();
            this.lblLVGHelper = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(330, 124);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 23);
            this.btnClose.TabIndex = 0;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnDownload
            // 
            this.btnDownload.Enabled = false;
            this.btnDownload.Location = new System.Drawing.Point(249, 124);
            this.btnDownload.Name = "btnDownload";
            this.btnDownload.Size = new System.Drawing.Size(75, 23);
            this.btnDownload.TabIndex = 1;
            this.btnDownload.Text = "Download";
            this.btnDownload.UseVisualStyleBackColor = true;
            this.btnDownload.Click += new System.EventHandler(this.btnDownload_Click);
            // 
            // btnUpdate
            // 
            this.btnUpdate.Enabled = false;
            this.btnUpdate.Location = new System.Drawing.Point(168, 124);
            this.btnUpdate.Name = "btnUpdate";
            this.btnUpdate.Size = new System.Drawing.Size(75, 23);
            this.btnUpdate.TabIndex = 2;
            this.btnUpdate.Text = "Update";
            this.btnUpdate.UseVisualStyleBackColor = true;
            this.btnUpdate.Click += new System.EventHandler(this.btnUpdate_Click);
            // 
            // btnVisitHomepage
            // 
            this.btnVisitHomepage.Location = new System.Drawing.Point(12, 124);
            this.btnVisitHomepage.Name = "btnVisitHomepage";
            this.btnVisitHomepage.Size = new System.Drawing.Size(150, 23);
            this.btnVisitHomepage.TabIndex = 3;
            this.btnVisitHomepage.Text = "Visit homepage";
            this.btnVisitHomepage.UseVisualStyleBackColor = true;
            this.btnVisitHomepage.Click += new System.EventHandler(this.btnVisitHomepage_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.lblLVGHelper);
            this.groupBox1.Controls.Add(this.lblLVds30Loader);
            this.groupBox1.Controls.Add(this.lblLVds30LoaderGUI);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.lblCVGHelper);
            this.groupBox1.Controls.Add(this.lblCVds30Loader);
            this.groupBox1.Controls.Add(this.lblCVds30LoaderGUI);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(393, 106);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            // 
            // lblLVds30LoaderGUI
            // 
            this.lblLVds30LoaderGUI.AutoSize = true;
            this.lblLVds30LoaderGUI.Location = new System.Drawing.Point(201, 74);
            this.lblLVds30LoaderGUI.Name = "lblLVds30LoaderGUI";
            this.lblLVds30LoaderGUI.Size = new System.Drawing.Size(69, 13);
            this.lblLVds30LoaderGUI.TabIndex = 1;
            this.lblLVds30LoaderGUI.Text = "latest version";
            // 
            // lblCVds30LoaderGUI
            // 
            this.lblCVds30LoaderGUI.AutoSize = true;
            this.lblCVds30LoaderGUI.Location = new System.Drawing.Point(201, 42);
            this.lblCVds30LoaderGUI.Name = "lblCVds30LoaderGUI";
            this.lblCVds30LoaderGUI.Size = new System.Drawing.Size(77, 13);
            this.lblCVds30LoaderGUI.TabIndex = 1;
            this.lblCVds30LoaderGUI.Text = "current version";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(11, 74);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Latest version:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 42);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(81, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Current version:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(201, 16);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(88, 13);
            this.label3.TabIndex = 1;
            this.label3.Text = "ds30 Loader GUI";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(103, 16);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(66, 13);
            this.label4.TabIndex = 1;
            this.label4.Text = "ds30 Loader";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(305, 16);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(46, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "GHelper";
            this.label5.Visible = false;
            // 
            // lblCVds30Loader
            // 
            this.lblCVds30Loader.AutoSize = true;
            this.lblCVds30Loader.Location = new System.Drawing.Point(103, 42);
            this.lblCVds30Loader.Name = "lblCVds30Loader";
            this.lblCVds30Loader.Size = new System.Drawing.Size(77, 13);
            this.lblCVds30Loader.TabIndex = 1;
            this.lblCVds30Loader.Text = "current version";
            // 
            // lblCVGHelper
            // 
            this.lblCVGHelper.AutoSize = true;
            this.lblCVGHelper.Location = new System.Drawing.Point(305, 42);
            this.lblCVGHelper.Name = "lblCVGHelper";
            this.lblCVGHelper.Size = new System.Drawing.Size(77, 13);
            this.lblCVGHelper.TabIndex = 1;
            this.lblCVGHelper.Text = "current version";
            this.lblCVGHelper.Visible = false;
            // 
            // lblLVds30Loader
            // 
            this.lblLVds30Loader.AutoSize = true;
            this.lblLVds30Loader.Location = new System.Drawing.Point(103, 74);
            this.lblLVds30Loader.Name = "lblLVds30Loader";
            this.lblLVds30Loader.Size = new System.Drawing.Size(69, 13);
            this.lblLVds30Loader.TabIndex = 1;
            this.lblLVds30Loader.Text = "latest version";
            // 
            // lblLVGHelper
            // 
            this.lblLVGHelper.AutoSize = true;
            this.lblLVGHelper.Location = new System.Drawing.Point(305, 74);
            this.lblLVGHelper.Name = "lblLVGHelper";
            this.lblLVGHelper.Size = new System.Drawing.Size(69, 13);
            this.lblLVGHelper.TabIndex = 1;
            this.lblLVGHelper.Text = "latest version";
            this.lblLVGHelper.Visible = false;
            // 
            // frmVersion
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(415, 159);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnVisitHomepage);
            this.Controls.Add(this.btnUpdate);
            this.Controls.Add(this.btnDownload);
            this.Controls.Add(this.btnClose);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmVersion";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Version control";
            this.TopMost = true;
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Button btnDownload;
        private System.Windows.Forms.Button btnUpdate;
        private System.Windows.Forms.Button btnVisitHomepage;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label lblLVds30LoaderGUI;
        private System.Windows.Forms.Label lblCVds30LoaderGUI;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lblCVds30Loader;
        private System.Windows.Forms.Label lblCVGHelper;
        private System.Windows.Forms.Label lblLVGHelper;
        private System.Windows.Forms.Label lblLVds30Loader;
    }
}