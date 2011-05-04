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
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Net;
using System.IO;
using ds30Loader;

namespace ds30_Loader_GUI
{
    
	//---------------------------------------------------------------------
	// Class: frmVersion
    //---------------------------------------------------------------------
    public partial class frmVersion : Form
    {
        private clsLatestVersionInfo objLatestVersionInfo = null;

 
		//---------------------------------------------------------------------
		// Constructor()
        //---------------------------------------------------------------------
        public frmVersion()
        {
            //
            InitializeComponent();

            //
            lblCVds30LoaderGUI.Text = frmDS30Loader.verGUI.ToString();
            lblCVds30Loader.Text = clsds30Loader.strVersion;

            //
            objLatestVersionInfo = new clsLatestVersionInfo();
            CheckLatestVersion();
        }// Constructor()

        
        //---------------------------------------------------------------------
		// CheckLatestVersion()
		// Description:
		//---------------------------------------------------------------------
        public void CheckLatestVersion()		
        {   
            if ( objLatestVersionInfo.CheckLatestVersion() == false ) {
                lblLVds30Loader.Text = "unknown";
                lblLVds30LoaderGUI.Text = "unknown";
                btnDownload.Enabled = false;
                btnUpdate.Enabled = false;
            } else {
                lblLVds30Loader.Text = objLatestVersionInfo.lvds30Loader.ToString();
                lblLVds30LoaderGUI.Text = objLatestVersionInfo.lvds30LoaderGUI.ToString();

                // A new version is availible
                if ( new Version(clsds30Loader.strVersion) < objLatestVersionInfo.lvds30Loader || frmDS30Loader.verGUI < objLatestVersionInfo.lvds30LoaderGUI ) {
                    this.Text = "A new version is available";
                    btnDownload.Enabled = objLatestVersionInfo.allowDownload;
                    btnUpdate.Enabled = objLatestVersionInfo.allowUpdate;
                
                // This is the latest version
                } else {
                    this.Text = "This is the latest version";
                    btnDownload.Enabled = false;
                    btnUpdate.Enabled = false;
                }
            }
        }// CheckLatestVersion()


        //---------------------------------------------------------------------
		// btnVisitHomepage_Click()
		//---------------------------------------------------------------------
        private void btnVisitHomepage_Click(object sender, EventArgs e)
        {
            frmDS30Loader.VisitHomepage();
        }//btnVisitHomepage_Click()


        //---------------------------------------------------------------------
		// btnClose_Click()
		//---------------------------------------------------------------------
        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }//btnClose_Click()


        //---------------------------------------------------------------------
		// btnDownload_Click()
		//---------------------------------------------------------------------
        private void btnDownload_Click(object sender, EventArgs e)
        {
            frmDS30Loader.DownloadLatestPackage( objLatestVersionInfo );
        }//btnDownload_Click()
        

        //---------------------------------------------------------------------
		// btnUpdate_Click()
		//---------------------------------------------------------------------
        private void btnUpdate_Click(object sender, EventArgs e)
        {
            frmDS30Loader.UpdateGUI( objLatestVersionInfo );
        }//btnUpdate_Click()

    }// Class: frmVersion
}
