/*
 * Openprog - control program for the open programmer
 * Copyright (C) 2009-2010 Alberto Maccioni
 * for detailed info see:
 * http://openprog.altervista.org/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 USA
 * or see <http://www.gnu.org/licenses/>
 */

// OpenProgDlg.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "setupapi.h"
#include "hidsdi.h"
#include "DatiPage.h"
#include "DispositivoPage.h"
#include "OpzioniPage.h"
#include "I2CSPIPage.h"
#include "OpenProg.h"
#include "OpenProgDlg.h"
#include <string.h>
#include "strings.h"
#include "instructions.h"

#define DIMBUF 65
#define COL 16
#define VERSION "0.7.5"
#define G (12.0/34*1024/5)		//=72,2823529412
#define  LOCK	1
#define  FUSE	2
#define  FUSE_H 4
#define  FUSE_X	8
#define  CAL	16
#define  SLOW	256

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PrintMessage1(s,p) {str.Format(s,p); PrintMessage(str);}
#define PrintMessage2(s,p1,p2) {str.Format(s,p1,p2); PrintMessage(str);}
#define PrintMessage3(s,p1,p2,p3) {str.Format(s,p1,p2,p3); PrintMessage(str);}
#define PrintMessage4(s,p1,p2,p3,p4) {str.Format(s,p1,p2,p3,p4); PrintMessage(str);}
#define PrintStatus(s,p1,p2) {str.Format(s,p1,p2); StatusBar.SetWindowText(str);}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_license;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_license = _T("");
	//}}AFX_DATA_INIT
	m_license.Format("  OpenProg v.%s - control program for the open programmer\
\r\n	For detailed info see http://openprog.altervista.org/\
\r\n \
\r\n               Copyright (C) 2009-2010 Alberto Maccioni\
\r\n \
\r\n  This program is free software; you can redistribute it and/or modify\
\r\n  it under the terms of the GNU General Public License as published by\
\r\n  the Free Software Foundation; either version 2 of the License, or \
\r\n  (at your option) any later version.\
\r\n  \
\r\n  This program is distributed in the hope that it will be useful,\
\r\n  but WITHOUT ANY WARRANTY; without even the implied warranty of\
\r\n  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\
\r\n  See the GNU General Public License for more details.\
\r\n  \
\r\n  You should have received a copy of the GNU General Public License\
\r\n  along with this program; if not, write to the Free Software\
\r\n  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 USA\
\r\n  or see <http://www.gnu.org/licenses/>",VERSION);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_LICENSE, m_license);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenProgDlg dialog

COpenProgDlg::COpenProgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenProgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenProgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenProgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenProgDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COpenProgDlg, CDialog)
	//{{AFX_MSG_MAP(COpenProgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_COMMAND(ID_I2CSPI_R, OnI2cspiR)
	ON_COMMAND(ID_I2CSPI_S, OnI2cspiS)
	ON_COMMAND(ID_TEST_HW, OnTestHw)
	ON_COMMAND(ID_LEGGI, OnRead)
	ON_COMMAND(ID_OPZIONI_PROGRAMMATORE_CONNETTI, OnConnect)
	ON_COMMAND(ID_FILE_SALVA, OnFileSave)
	ON_COMMAND(ID_FILE_APRI, OnFileOpen)
	ON_COMMAND(ID_SCRIVI, OnWrite)
	ON_COMMAND(ID_CAMBIA_LINGUA, ChangeLanguage)
	ON_COMMAND(ID_WRITE_LANG_FILE, OnWriteLangFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenProgDlg message handlers

BOOL COpenProgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CStdioFile f;
	CString lang="English";
	strings=0;
	CString s,dev="12F683",vid="0x04D8",pid="0x0100";
	wfile=rfile="";
	maxerr=200;
	MinRit=5;
	hvreg=0;
	logfile=0;
	s.Format("OpenProg v%s",VERSION);
	this->SetWindowText(s);
	s=GetCommandLine();
	s+=" ";
	CString t;
	int gui=0,delta_v=0;
	argc=0;
	int q=0;
	for(int i=0;i<s.GetLength()&&argc<32;i++){
		if(!q){
			if(s[i]==' '){
				if(t!="")argv[argc++]=t;
				t="";
			}
			else if(s[i]=='"') q=1;
			else t+=s[i];
		}
		else{ 
			if(q&&s[i]=='"'){
				argv[argc]=t;
				t="";
				argc++;
				q=0;
			}
			else t+=s[i];
		}

	}
	s=argv[0];
	s.Replace(".exe",".ini");
	if (f.Open(s,CFile::modeRead))	{
		CString line;
		char temp[256];
		for(;f.ReadString(line);){
			if(sscanf(line,"device %s",temp)>0)dev=temp;
			if(sscanf(line,"language %s",temp)>0)lang=temp;
			if(sscanf(line,"vid %s",temp)>0)vid=temp;
			if(sscanf(line,"pid %s",temp)>0)pid=temp;
			sscanf(line,"maxerr %d",&maxerr);
			sscanf(line,"usb_delay %d",&MinRit);
			//sscanf(line,"delta_v %d",&delta_v);
		}
		f.Close();
	}
	for(i=0;i<argc;i++){
		if(argv[i]=="-d"&&i+1<argc){
			dev=argv[++i];
			dev.MakeUpper();
		}
		else if(argv[i]=="-w"&&i+1<argc){
			wfile=argv[++i];
		}
		else if(argv[i]=="-r"&&i+1<argc){
			rfile=argv[++i];
		}
		else if(argv[i]=="-gui"){
			gui=1;
		}
	}
	dati_hex.SetSize(0x2400);
	for(i=0;i<0x2400;i++) dati_hex[i]=0x3fff;
	StatusBar.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,0);
	ToolBar.Create(this);
	ToolBar.LoadToolBar(IDR_TOOLBAR1);
	ToolBar.SetBarStyle(ToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	m_dlgPropSheet.AddPage(&m_DatiPage);
	m_dlgPropSheet.AddPage(&m_DispoPage);
	m_dlgPropSheet.AddPage(&m_OpzioniPage);
	m_dlgPropSheet.AddPage(&m_I2CSPIPage);
	m_dlgPropSheet.Create(this,WS_CHILD|WS_VISIBLE|WS_TABSTOP,WS_EX_CONTROLPARENT);
	m_dlgPropSheet.SetActivePage(3);
	m_dlgPropSheet.SetActivePage(2);
	m_dlgPropSheet.SetActivePage(1);
	m_dlgPropSheet.SetActivePage(0);
	m_OpzioniPage.m_language.AddString("Italiano");
	m_OpzioniPage.m_language.AddString("English");
	m_DispoPage.m_dispo.AddString("10F200");
	m_DispoPage.m_dispo.AddString("10F202");
	m_DispoPage.m_dispo.AddString("10F204");
	m_DispoPage.m_dispo.AddString("10F206");
	m_DispoPage.m_dispo.AddString("10F220");
	m_DispoPage.m_dispo.AddString("10F222");
	m_DispoPage.m_dispo.AddString("12C508/A");
	m_DispoPage.m_dispo.AddString("12C509/A");
	m_DispoPage.m_dispo.AddString("12F508");
	m_DispoPage.m_dispo.AddString("12F509");
	m_DispoPage.m_dispo.AddString("12F510");
	m_DispoPage.m_dispo.AddString("12F519");
	m_DispoPage.m_dispo.AddString("12F609");
	m_DispoPage.m_dispo.AddString("12F615");
	m_DispoPage.m_dispo.AddString("12F629");
	m_DispoPage.m_dispo.AddString("12F635");
	m_DispoPage.m_dispo.AddString("12C671");
	m_DispoPage.m_dispo.AddString("12C672");
	m_DispoPage.m_dispo.AddString("12CE673");
	m_DispoPage.m_dispo.AddString("12CE674");
	m_DispoPage.m_dispo.AddString("12F675");
	m_DispoPage.m_dispo.AddString("12F683");
	m_DispoPage.m_dispo.AddString("16F505");
	m_DispoPage.m_dispo.AddString("16F506");
	m_DispoPage.m_dispo.AddString("16F526");
	m_DispoPage.m_dispo.AddString("16F54");
	m_DispoPage.m_dispo.AddString("16F57");
	m_DispoPage.m_dispo.AddString("16F59");
	m_DispoPage.m_dispo.AddString("16F610");
	m_DispoPage.m_dispo.AddString("16F616");
	m_DispoPage.m_dispo.AddString("16F627");
	m_DispoPage.m_dispo.AddString("16F627A");
	m_DispoPage.m_dispo.AddString("16F628");
	m_DispoPage.m_dispo.AddString("16F628A");
	m_DispoPage.m_dispo.AddString("16F630");
	m_DispoPage.m_dispo.AddString("16F631");
	m_DispoPage.m_dispo.AddString("16F636");
	m_DispoPage.m_dispo.AddString("16F639");
	m_DispoPage.m_dispo.AddString("16F648A");
	m_DispoPage.m_dispo.AddString("16F676");
	m_DispoPage.m_dispo.AddString("16F677");
	m_DispoPage.m_dispo.AddString("16F684");
	m_DispoPage.m_dispo.AddString("16F685");
	m_DispoPage.m_dispo.AddString("16F687");
	m_DispoPage.m_dispo.AddString("16F688");
	m_DispoPage.m_dispo.AddString("16F689");
	m_DispoPage.m_dispo.AddString("16F690");
	m_DispoPage.m_dispo.AddString("16F716");
	m_DispoPage.m_dispo.AddString("16F73");
	m_DispoPage.m_dispo.AddString("16F737");
	m_DispoPage.m_dispo.AddString("16F74");
	m_DispoPage.m_dispo.AddString("16F747");
	m_DispoPage.m_dispo.AddString("16F76");
	m_DispoPage.m_dispo.AddString("16F767");
	m_DispoPage.m_dispo.AddString("16F77");
	m_DispoPage.m_dispo.AddString("16F777");
	m_DispoPage.m_dispo.AddString("16F785");
	m_DispoPage.m_dispo.AddString("16F818");
	m_DispoPage.m_dispo.AddString("16F819");
	m_DispoPage.m_dispo.AddString("16C83");
	m_DispoPage.m_dispo.AddString("16F83");
	m_DispoPage.m_dispo.AddString("16F83A");
	m_DispoPage.m_dispo.AddString("16C84");
	m_DispoPage.m_dispo.AddString("16F84");
	m_DispoPage.m_dispo.AddString("16F84A");
	m_DispoPage.m_dispo.AddString("16F87");
	m_DispoPage.m_dispo.AddString("16F870");
	m_DispoPage.m_dispo.AddString("16F871");
	m_DispoPage.m_dispo.AddString("16F872");
	m_DispoPage.m_dispo.AddString("16F873");
	m_DispoPage.m_dispo.AddString("16F873A");
	m_DispoPage.m_dispo.AddString("16F874");
	m_DispoPage.m_dispo.AddString("16F874A");
	m_DispoPage.m_dispo.AddString("16F876");
	m_DispoPage.m_dispo.AddString("16F876A");
	m_DispoPage.m_dispo.AddString("16F877");
	m_DispoPage.m_dispo.AddString("16F877A");
	m_DispoPage.m_dispo.AddString("16F88");
	m_DispoPage.m_dispo.AddString("16F882");
	m_DispoPage.m_dispo.AddString("16F883");
	m_DispoPage.m_dispo.AddString("16F884");
	m_DispoPage.m_dispo.AddString("16F886");
	m_DispoPage.m_dispo.AddString("16F887");
	m_DispoPage.m_dispo.AddString("16F913");
	m_DispoPage.m_dispo.AddString("16F914");
	m_DispoPage.m_dispo.AddString("16F916");
	m_DispoPage.m_dispo.AddString("16F917");
	m_DispoPage.m_dispo.AddString("16F946");
	m_DispoPage.m_dispo.AddString("16F1822");
	m_DispoPage.m_dispo.AddString("16F1823");
	m_DispoPage.m_dispo.AddString("16F1824");
	m_DispoPage.m_dispo.AddString("16F1825");
	m_DispoPage.m_dispo.AddString("16F1826");
	m_DispoPage.m_dispo.AddString("16F1827");
	m_DispoPage.m_dispo.AddString("16F1828");
	m_DispoPage.m_dispo.AddString("16F1829");
	m_DispoPage.m_dispo.AddString("16F1933");
	m_DispoPage.m_dispo.AddString("16F1934");
	m_DispoPage.m_dispo.AddString("16F1936");
	m_DispoPage.m_dispo.AddString("16F1937");
	m_DispoPage.m_dispo.AddString("16F1938");
	m_DispoPage.m_dispo.AddString("16F1939");
	m_DispoPage.m_dispo.AddString("16F1946");
	m_DispoPage.m_dispo.AddString("16F1947");
	m_DispoPage.m_dispo.AddString("18F242");
	m_DispoPage.m_dispo.AddString("18F248");
	m_DispoPage.m_dispo.AddString("18F252");
	m_DispoPage.m_dispo.AddString("18F258");
	m_DispoPage.m_dispo.AddString("18F442");
	m_DispoPage.m_dispo.AddString("18F448");
	m_DispoPage.m_dispo.AddString("18F452");
	m_DispoPage.m_dispo.AddString("18F458");
	m_DispoPage.m_dispo.AddString("18F1220");
	m_DispoPage.m_dispo.AddString("18F1230");
	m_DispoPage.m_dispo.AddString("18F1320");
	m_DispoPage.m_dispo.AddString("18F1330");
	m_DispoPage.m_dispo.AddString("18F13K50");
	m_DispoPage.m_dispo.AddString("18F14K50");
	m_DispoPage.m_dispo.AddString("18F2220");
	m_DispoPage.m_dispo.AddString("18F2221");
	m_DispoPage.m_dispo.AddString("18F2320");
	m_DispoPage.m_dispo.AddString("18F23K20");
	m_DispoPage.m_dispo.AddString("18F2321");
	m_DispoPage.m_dispo.AddString("18F2331");
	m_DispoPage.m_dispo.AddString("18F2410");
	m_DispoPage.m_dispo.AddString("18F24J10");
	m_DispoPage.m_dispo.AddString("18F24J11");
	m_DispoPage.m_dispo.AddString("18F2420");
	m_DispoPage.m_dispo.AddString("18F24K20");
	m_DispoPage.m_dispo.AddString("18F2423");
	m_DispoPage.m_dispo.AddString("18F2431");
	m_DispoPage.m_dispo.AddString("18F2439");
	m_DispoPage.m_dispo.AddString("18F2450");
	m_DispoPage.m_dispo.AddString("18F24J50");
	m_DispoPage.m_dispo.AddString("18F2455");
	m_DispoPage.m_dispo.AddString("18F2458");
	m_DispoPage.m_dispo.AddString("18F2480");
	m_DispoPage.m_dispo.AddString("18F2510");
	m_DispoPage.m_dispo.AddString("18F25J10");
	m_DispoPage.m_dispo.AddString("18F25J11");
	m_DispoPage.m_dispo.AddString("18F2515");
	m_DispoPage.m_dispo.AddString("18F25K20");
	m_DispoPage.m_dispo.AddString("18F2520");
	m_DispoPage.m_dispo.AddString("18F2523");
	m_DispoPage.m_dispo.AddString("18F2525");
	m_DispoPage.m_dispo.AddString("18F2539");
	m_DispoPage.m_dispo.AddString("18F2550");
	m_DispoPage.m_dispo.AddString("18F25J50");
	m_DispoPage.m_dispo.AddString("18F2553");
	m_DispoPage.m_dispo.AddString("18F2580");
	m_DispoPage.m_dispo.AddString("18F2585");
	m_DispoPage.m_dispo.AddString("18F2610");
	m_DispoPage.m_dispo.AddString("18F26J11");
	m_DispoPage.m_dispo.AddString("18F26J13");
	m_DispoPage.m_dispo.AddString("18F2620");
	m_DispoPage.m_dispo.AddString("18F26K20");
	m_DispoPage.m_dispo.AddString("18F26J50");
	m_DispoPage.m_dispo.AddString("18F26J53");
	m_DispoPage.m_dispo.AddString("18F2680");
	m_DispoPage.m_dispo.AddString("18F2682");
	m_DispoPage.m_dispo.AddString("18F2685");
	m_DispoPage.m_dispo.AddString("18F27J13");
	m_DispoPage.m_dispo.AddString("18F27J53");
	m_DispoPage.m_dispo.AddString("18F4220");
	m_DispoPage.m_dispo.AddString("18F4221");
	m_DispoPage.m_dispo.AddString("18F4320");
	m_DispoPage.m_dispo.AddString("18F43K20");
	m_DispoPage.m_dispo.AddString("18F4321");
	m_DispoPage.m_dispo.AddString("18F4331");
	m_DispoPage.m_dispo.AddString("18F4410");
	m_DispoPage.m_dispo.AddString("18F44J10");
	m_DispoPage.m_dispo.AddString("18F44J11");
	m_DispoPage.m_dispo.AddString("18F4420");
	m_DispoPage.m_dispo.AddString("18F44K20");
	m_DispoPage.m_dispo.AddString("18F4423");
	m_DispoPage.m_dispo.AddString("18F4431");
	m_DispoPage.m_dispo.AddString("18F4439");
	m_DispoPage.m_dispo.AddString("18F4450");
	m_DispoPage.m_dispo.AddString("18F44J50");
	m_DispoPage.m_dispo.AddString("18F4455");
	m_DispoPage.m_dispo.AddString("18F4458");
	m_DispoPage.m_dispo.AddString("18F4480");
	m_DispoPage.m_dispo.AddString("18F4510");
	m_DispoPage.m_dispo.AddString("18F45J10");
	m_DispoPage.m_dispo.AddString("18F45J11");
	m_DispoPage.m_dispo.AddString("18F4515");
	m_DispoPage.m_dispo.AddString("18F4520");
	m_DispoPage.m_dispo.AddString("18F45K20");
	m_DispoPage.m_dispo.AddString("18F4523");
	m_DispoPage.m_dispo.AddString("18F4525");
	m_DispoPage.m_dispo.AddString("18F4539");
	m_DispoPage.m_dispo.AddString("18F4550");
	m_DispoPage.m_dispo.AddString("18F45J50");
	m_DispoPage.m_dispo.AddString("18F4553");
	m_DispoPage.m_dispo.AddString("18F4580");
	m_DispoPage.m_dispo.AddString("18F4585");
	m_DispoPage.m_dispo.AddString("18F4610");
	m_DispoPage.m_dispo.AddString("18F46J11");
	m_DispoPage.m_dispo.AddString("18F46J13");
	m_DispoPage.m_dispo.AddString("18F4620");
	m_DispoPage.m_dispo.AddString("18F46K20");
	m_DispoPage.m_dispo.AddString("18F46J50");
	m_DispoPage.m_dispo.AddString("18F46J53");
	m_DispoPage.m_dispo.AddString("18F4680");
	m_DispoPage.m_dispo.AddString("18F4682");
	m_DispoPage.m_dispo.AddString("18F4685");
	m_DispoPage.m_dispo.AddString("18F47J13");
	m_DispoPage.m_dispo.AddString("18F47J53");
	m_DispoPage.m_dispo.AddString("18F8722");
	m_DispoPage.m_dispo.AddString("24F04KA200");
	m_DispoPage.m_dispo.AddString("24F04KA201");
	m_DispoPage.m_dispo.AddString("24F08KA101");
	m_DispoPage.m_dispo.AddString("24F08KA102");
	m_DispoPage.m_dispo.AddString("24F16KA101");
	m_DispoPage.m_dispo.AddString("24F16KA102");
	m_DispoPage.m_dispo.AddString("24FJ16GA002");
	m_DispoPage.m_dispo.AddString("24FJ16GA004");
	m_DispoPage.m_dispo.AddString("24FJ32GA002");
	m_DispoPage.m_dispo.AddString("24FJ32GA004");
	m_DispoPage.m_dispo.AddString("24FJ48GA002");
	m_DispoPage.m_dispo.AddString("24FJ48GA004");
	m_DispoPage.m_dispo.AddString("24FJ64GA002");
	m_DispoPage.m_dispo.AddString("24FJ64GA004");
	m_DispoPage.m_dispo.AddString("24FJ64GA006");
	m_DispoPage.m_dispo.AddString("24FJ64GA008");
	m_DispoPage.m_dispo.AddString("24FJ64GA010");
	m_DispoPage.m_dispo.AddString("24FJ96GA006");
	m_DispoPage.m_dispo.AddString("24FJ96GA008");
	m_DispoPage.m_dispo.AddString("24FJ96GA010");
	m_DispoPage.m_dispo.AddString("24FJ128GA006");
	m_DispoPage.m_dispo.AddString("24FJ128GA008");
	m_DispoPage.m_dispo.AddString("24FJ128GA010");
	m_DispoPage.m_dispo.AddString("24FJ32GA102");
	m_DispoPage.m_dispo.AddString("24FJ32GA104");
	m_DispoPage.m_dispo.AddString("24FJ32GB002");
	m_DispoPage.m_dispo.AddString("24FJ32GB004");
	m_DispoPage.m_dispo.AddString("24FJ64GA102");
	m_DispoPage.m_dispo.AddString("24FJ64GA104");
	m_DispoPage.m_dispo.AddString("24FJ64GB002");
	m_DispoPage.m_dispo.AddString("24FJ64GB004");
	m_DispoPage.m_dispo.AddString("24FJ64GB106");
	m_DispoPage.m_dispo.AddString("24FJ64GB108");
	m_DispoPage.m_dispo.AddString("24FJ64GB110");
	m_DispoPage.m_dispo.AddString("24FJ128GA106");
	m_DispoPage.m_dispo.AddString("24FJ128GB106");
	m_DispoPage.m_dispo.AddString("24FJ128GA108");
	m_DispoPage.m_dispo.AddString("24FJ128GB108");
	m_DispoPage.m_dispo.AddString("24FJ128GA110");
	m_DispoPage.m_dispo.AddString("24FJ128GB110");
	m_DispoPage.m_dispo.AddString("24FJ192GA106");
	m_DispoPage.m_dispo.AddString("24FJ192GB106");
	m_DispoPage.m_dispo.AddString("24FJ192GA108");
	m_DispoPage.m_dispo.AddString("24FJ192GB108");
	m_DispoPage.m_dispo.AddString("24FJ192GA110");
	m_DispoPage.m_dispo.AddString("24FJ192GB110");
	m_DispoPage.m_dispo.AddString("24FJ256GA106");
	m_DispoPage.m_dispo.AddString("24FJ256GB106");
	m_DispoPage.m_dispo.AddString("24FJ256GA108");
	m_DispoPage.m_dispo.AddString("24FJ256GB108");
	m_DispoPage.m_dispo.AddString("24FJ256GA110");
	m_DispoPage.m_dispo.AddString("24FJ256GB110");
	m_DispoPage.m_dispo.AddString("24HJ12GP201");
	m_DispoPage.m_dispo.AddString("24HJ12GP202");
	m_DispoPage.m_dispo.AddString("24HJ16GP304");
	m_DispoPage.m_dispo.AddString("24HJ32GP202");
	m_DispoPage.m_dispo.AddString("24HJ32GP204");
	m_DispoPage.m_dispo.AddString("24HJ32GP302");
	m_DispoPage.m_dispo.AddString("24HJ32GP304");
	m_DispoPage.m_dispo.AddString("24HJ64GP202");
	m_DispoPage.m_dispo.AddString("24HJ64GP204");
	m_DispoPage.m_dispo.AddString("24HJ64GP206");
	m_DispoPage.m_dispo.AddString("24HJ64GP210");
	m_DispoPage.m_dispo.AddString("24HJ64GP502");
	m_DispoPage.m_dispo.AddString("24HJ64GP504");
	m_DispoPage.m_dispo.AddString("24HJ64GP506");
	m_DispoPage.m_dispo.AddString("24HJ64GP510");
	m_DispoPage.m_dispo.AddString("24HJ128GP202");
	m_DispoPage.m_dispo.AddString("24HJ128GP204");
	m_DispoPage.m_dispo.AddString("24HJ128GP206");
	m_DispoPage.m_dispo.AddString("24HJ128GP210");
	m_DispoPage.m_dispo.AddString("24HJ128GP306");
	m_DispoPage.m_dispo.AddString("24HJ128GP310");
	m_DispoPage.m_dispo.AddString("24HJ128GP502");
	m_DispoPage.m_dispo.AddString("24HJ128GP504");
	m_DispoPage.m_dispo.AddString("24HJ128GP506");
	m_DispoPage.m_dispo.AddString("24HJ128GP510");
	m_DispoPage.m_dispo.AddString("24HJ256GP206");
	m_DispoPage.m_dispo.AddString("24HJ256GP210");
	m_DispoPage.m_dispo.AddString("24HJ256GP610");
	m_DispoPage.m_dispo.AddString("30F2010");
	m_DispoPage.m_dispo.AddString("30F2011");
	m_DispoPage.m_dispo.AddString("30F2012");
	m_DispoPage.m_dispo.AddString("30F3010");
	m_DispoPage.m_dispo.AddString("30F3011");
	m_DispoPage.m_dispo.AddString("30F3012");
	m_DispoPage.m_dispo.AddString("30F3013");
	m_DispoPage.m_dispo.AddString("30F3014");
	m_DispoPage.m_dispo.AddString("30F4011");
	m_DispoPage.m_dispo.AddString("30F4012");
	m_DispoPage.m_dispo.AddString("30F4013");
	m_DispoPage.m_dispo.AddString("30F5011");
	m_DispoPage.m_dispo.AddString("30F5013");
	m_DispoPage.m_dispo.AddString("30F5015");
	m_DispoPage.m_dispo.AddString("30F5016");
	m_DispoPage.m_dispo.AddString("30F6010");
	m_DispoPage.m_dispo.AddString("30F6011");
	m_DispoPage.m_dispo.AddString("30F6012");
	m_DispoPage.m_dispo.AddString("30F6013");
	m_DispoPage.m_dispo.AddString("30F6014");
	m_DispoPage.m_dispo.AddString("30F6015");
	m_DispoPage.m_dispo.AddString("33FJ06GS101");
	m_DispoPage.m_dispo.AddString("33FJ06GS102");
	m_DispoPage.m_dispo.AddString("33FJ06GS202");
	m_DispoPage.m_dispo.AddString("33FJ12GP201");
	m_DispoPage.m_dispo.AddString("33FJ12GP202");
	m_DispoPage.m_dispo.AddString("33FJ12MC201");
	m_DispoPage.m_dispo.AddString("33FJ12MC202");
	m_DispoPage.m_dispo.AddString("33FJ16GP304");
	m_DispoPage.m_dispo.AddString("33FJ16GS402");
	m_DispoPage.m_dispo.AddString("33FJ16GS404");
	m_DispoPage.m_dispo.AddString("33FJ16GS502");
	m_DispoPage.m_dispo.AddString("33FJ16GS504");
	m_DispoPage.m_dispo.AddString("33FJ16MC304");
	m_DispoPage.m_dispo.AddString("33FJ32GP202");
	m_DispoPage.m_dispo.AddString("33FJ32GP204");
	m_DispoPage.m_dispo.AddString("33FJ32GP302");
	m_DispoPage.m_dispo.AddString("33FJ32GP304");
	m_DispoPage.m_dispo.AddString("33FJ32GS406");
	m_DispoPage.m_dispo.AddString("33FJ32GS606");
	m_DispoPage.m_dispo.AddString("33FJ32GS608");
	m_DispoPage.m_dispo.AddString("33FJ32GS610");
	m_DispoPage.m_dispo.AddString("33FJ32MC202");
	m_DispoPage.m_dispo.AddString("33FJ32MC204");
	m_DispoPage.m_dispo.AddString("33FJ32MC302");
	m_DispoPage.m_dispo.AddString("33FJ32MC304");
	m_DispoPage.m_dispo.AddString("33FJ64GP202");
	m_DispoPage.m_dispo.AddString("33FJ64GP204");
	m_DispoPage.m_dispo.AddString("33FJ64GP206");
	m_DispoPage.m_dispo.AddString("33FJ64GP306");
	m_DispoPage.m_dispo.AddString("33FJ64GP310");
	m_DispoPage.m_dispo.AddString("33FJ64GP706");
	m_DispoPage.m_dispo.AddString("33FJ64GP708");
	m_DispoPage.m_dispo.AddString("33FJ64GP710");
	m_DispoPage.m_dispo.AddString("33FJ64GP802");
	m_DispoPage.m_dispo.AddString("33FJ64GP804");
	m_DispoPage.m_dispo.AddString("33FJ64GS406");
	m_DispoPage.m_dispo.AddString("33FJ64GS606");
	m_DispoPage.m_dispo.AddString("33FJ64GS608");
	m_DispoPage.m_dispo.AddString("33FJ64GS610");
	m_DispoPage.m_dispo.AddString("33FJ64MC202");
	m_DispoPage.m_dispo.AddString("33FJ64MC204");
	m_DispoPage.m_dispo.AddString("33FJ64MC506");
	m_DispoPage.m_dispo.AddString("33FJ64MC508");
	m_DispoPage.m_dispo.AddString("33FJ64MC510");
	m_DispoPage.m_dispo.AddString("33FJ64MC706");
	m_DispoPage.m_dispo.AddString("33FJ64MC710");
	m_DispoPage.m_dispo.AddString("33FJ64MC802");
	m_DispoPage.m_dispo.AddString("33FJ64MC804");
	m_DispoPage.m_dispo.AddString("33FJ128GP202");
	m_DispoPage.m_dispo.AddString("33FJ128GP204");
	m_DispoPage.m_dispo.AddString("33FJ128GP206");
	m_DispoPage.m_dispo.AddString("33FJ128GP306");
	m_DispoPage.m_dispo.AddString("33FJ128GP310");
	m_DispoPage.m_dispo.AddString("33FJ128GP706");
	m_DispoPage.m_dispo.AddString("33FJ128GP708");
	m_DispoPage.m_dispo.AddString("33FJ128GP710");
	m_DispoPage.m_dispo.AddString("33FJ128GP802");
	m_DispoPage.m_dispo.AddString("33FJ128GP804");
	m_DispoPage.m_dispo.AddString("33FJ128MC202");
	m_DispoPage.m_dispo.AddString("33FJ128MC204");
	m_DispoPage.m_dispo.AddString("33FJ128MC506");
	m_DispoPage.m_dispo.AddString("33FJ128MC510");
	m_DispoPage.m_dispo.AddString("33FJ128MC706");
	m_DispoPage.m_dispo.AddString("33FJ128MC708");
	m_DispoPage.m_dispo.AddString("33FJ128MC710");
	m_DispoPage.m_dispo.AddString("33FJ128MC802");
	m_DispoPage.m_dispo.AddString("33FJ128MC804");
	m_DispoPage.m_dispo.AddString("33FJ256GP506");
	m_DispoPage.m_dispo.AddString("33FJ256GP510");
	m_DispoPage.m_dispo.AddString("33FJ256GP710");
	m_DispoPage.m_dispo.AddString("33FJ256MC510");
	m_DispoPage.m_dispo.AddString("33FJ256MC710");
	m_DispoPage.m_dispo.AddString("AT90S1200");
	m_DispoPage.m_dispo.AddString("AT90S2313");
	m_DispoPage.m_dispo.AddString("AT90S8515");
	m_DispoPage.m_dispo.AddString("AT90S8535");
	m_DispoPage.m_dispo.AddString("ATmega8");
	m_DispoPage.m_dispo.AddString("ATmega8A");
	m_DispoPage.m_dispo.AddString("ATmega8515");
	m_DispoPage.m_dispo.AddString("ATmega8535");
	m_DispoPage.m_dispo.AddString("ATmega16");
	m_DispoPage.m_dispo.AddString("ATmega16A");
	m_DispoPage.m_dispo.AddString("ATmega32");
	m_DispoPage.m_dispo.AddString("ATmega32A");
	m_DispoPage.m_dispo.AddString("ATmega64");
	m_DispoPage.m_dispo.AddString("ATmega64A");
	m_DispoPage.m_dispo.AddString("ATtiny2313");
	m_DispoPage.m_dispo.AddString("2400");
	m_DispoPage.m_dispo.AddString("2401");
	m_DispoPage.m_dispo.AddString("2402");
	m_DispoPage.m_dispo.AddString("2404");
	m_DispoPage.m_dispo.AddString("2408");
	m_DispoPage.m_dispo.AddString("2416");
	m_DispoPage.m_dispo.AddString("2432");
	m_DispoPage.m_dispo.AddString("2464");
	m_DispoPage.m_dispo.AddString("24128");
	m_DispoPage.m_dispo.AddString("24256");
	m_DispoPage.m_dispo.AddString("24512");
	m_DispoPage.m_dispo.AddString("241024");
	m_DispoPage.m_dispo.AddString("241025");
	m_DispoPage.m_dispo.AddString("25010");
	m_DispoPage.m_dispo.AddString("25020");
	m_DispoPage.m_dispo.AddString("25040");
	m_DispoPage.m_dispo.AddString("25080");
	m_DispoPage.m_dispo.AddString("25160");
	m_DispoPage.m_dispo.AddString("25320");
	m_DispoPage.m_dispo.AddString("25640");
	m_DispoPage.m_dispo.AddString("25128");
	m_DispoPage.m_dispo.AddString("25256");
	m_DispoPage.m_dispo.AddString("25512");
	m_DispoPage.m_dispo.AddString("251024");
	m_DispoPage.m_dispo.AddString("93S46");
	m_DispoPage.m_dispo.AddString("93x46");
	m_DispoPage.m_dispo.AddString("93x46A");
	m_DispoPage.m_dispo.AddString("93S56");
	m_DispoPage.m_dispo.AddString("93x56");
	m_DispoPage.m_dispo.AddString("93x56A");
	m_DispoPage.m_dispo.AddString("93S66");
	m_DispoPage.m_dispo.AddString("93x66");
	m_DispoPage.m_dispo.AddString("93x66A");
	m_DispoPage.m_dispo.AddString("93x76");
	m_DispoPage.m_dispo.AddString("93x76A");
	m_DispoPage.m_dispo.AddString("93x86");
	m_DispoPage.m_dispo.AddString("93x86A");

	s.Replace("OpenProg.ini","languages.rc");
	if (f.Open(s,CFile::modeRead))	{
		CString line;
		char temp[256];
		for(;f.ReadString(line);){
			if(sscanf(line,"[%s]",temp)>0){
				line=temp;
				line.Remove(']');
				for(int i=m_OpzioniPage.m_language.GetCount();i;i--){
					m_OpzioniPage.m_language.GetLBText(i-1,s);
					if(s==line)	break;
				}
				if(!i)	m_OpzioniPage.m_language.AddString(line);
			}
		}
		f.Close();
	}
	if(m_OpzioniPage.m_language.SelectString(-1,lang)==CB_ERR)
		m_OpzioniPage.m_language.SelectString(-1,"English");

	ChangeLanguage();
	m_OpzioniPage.SetDlgItemText(IDC_VID,vid);
	m_OpzioniPage.SetDlgItemText(IDC_PID,pid);
	m_OpzioniPage.SetDlgItemInt(IDC_USBDMIN,MinRit);
	m_DispoPage.SetDlgItemText(IDC_ICDADDR,"1FF0");
	if(m_DispoPage.m_dispo.SelectString(-1,dev)==CB_ERR)
		m_DispoPage.m_dispo.SelectString(-1,"12F683");
	RECT rect;
	m_dlgPropSheet.GetClientRect(&rect);
	rect.top+=25;
	rect.bottom+=25;
	m_dlgPropSheet.MoveWindow(&rect,FALSE);
	CSpinButtonCtrl*e=(CSpinButtonCtrl*)m_I2CSPIPage.GetDlgItem(IDC_NB);
	e->SetRange(0,60);
	CButton* b=(CButton*)m_DispoPage.GetDlgItem(IDC_IDPROG);
	b->SetCheck(0);
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_OSC_LOAD);
	b->SetCheck(0);
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_OSC_OSCCAL);
	b->SetCheck(0);
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_OSC_BK);
	b->SetCheck(1);
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_EEPROM);
	b->SetCheck(1);
	b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_I2C8B);
	b->SetCheck(1);
	m_OpzioniPage.SetDlgItemInt(IDC_ERRMAX,maxerr);
	m_I2CSPIPage.SetDlgItemInt(IDC_NUMB,1);
	MyDeviceDetected = FALSE;
	hEventObject=0;
	FindDevice();	//connect to USB programmer
	ProgID();		//get firmware version and reset
	//PrintMessage(GetCommandLine());
	//for(i=0;i<argc;i++) PrintMessage(argv[i]);
	if(wfile!=""){
		OnFileOpen();
		OnWrite();
		wfile="";
		if(!gui) exit(0);
	}
	if(rfile!=""){
		OnRead();
		OnFileSave();
		rfile="";
		if(!gui) exit(0);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}



void COpenProgDlg::ChangeLanguage()
{
	CString lang;
	m_OpzioniPage.m_language.GetLBText(m_OpzioniPage.m_language.GetCurSel(),lang);
	#include "strings.c"
	strings_ID=new char*[DIM];
	CString ss;
	for(int i=0;i<DIM;i++){
		ss.Format("%s#%s",STR_ID[i],strings_en[i]);
		ss.Replace("\r","\\r");
		ss.Replace("\n","\\n");
		ss.Replace("\t","\\t");
		ss.Replace("#","\t\t\t");
		ss+="\n";
		strings_ID[i]=new char[ss.GetLength()+1];
		strcpy(strings_ID[i],ss);
	}
	strings=new char*[DIM];
	for(i=0;i<DIM;i++) strings[i]=0;
	if(lang=="Italiano"){
		for(i=0;i<DIM;i++){
			strings[i]=new char[strlen(strings_it[i])+1];
			strcpy(strings[i],strings_it[i]);
		}
	}
	else if(lang!="English"){
		CStdioFile f;
		CString s;
		s="languages.rc";
		if (f.Open(s,CFile::modeRead))	{
			CString line,id;
			char temp[256];
			temp[0]=0;
			lang+="]";
			for(;f.ReadString(line);){
				if(sscanf(line,"[%s]",temp)&&lang==temp) break;
			}
			if(lang==temp){
				for(int i=0;i<DIM;i++) strings[i]=0;
				for(;f.ReadString(line);){
					if(line.GetLength()>0&&line[0]=='[') break;
					id=line;
					id.Replace('\t',' ');
					id=id.Left(id.Find(" "));
					line.Replace(id,"");
					line.TrimLeft();
					line.Replace("\\n","\n");
					line.Replace("\\r","\r");
					line.Replace("\\t","\t");
					for(int j=0;j<DIM;j++){
						if(id==STR_ID[j]){
							strings[j]=new char[line.GetLength()+1];
							strcpy(strings[j],line);
							j=DIM;
						}
					}
				}
				for(i=0;i<DIM;i++){
					if(strings[i]==0){
						strings[i]=new char[strlen(strings_en[i])+1];
						strcpy(strings[i],strings_en[i]);
					}
				}
			}
			else lang="English";
			f.Close();
		}
		else lang="English";
	}
	if(lang=="English"){				//english or any error
		for(int i=0;i<DIM;i++){
			strings[i]=new char[strlen(strings_en[i])+1];
			strcpy(strings[i],strings_en[i]);
		}
	}
    CTabCtrl* pTab =m_dlgPropSheet.GetTabControl();
    ASSERT (pTab);
    TC_ITEM ti;
    ti.mask = TCIF_TEXT;
    ti.pszText = strings[I_Data];
    VERIFY (pTab->SetItem (0, &ti));
    ti.pszText = strings[I_Dev];
    VERIFY (pTab->SetItem (1, &ti));
    ti.pszText = strings[I_Opt];
    VERIFY (pTab->SetItem (2, &ti));
	m_DispoPage.SetDlgItemText(IDC_STATICdev,strings[I_Dev]);
	m_DispoPage.SetDlgItemText(IDC_RISERVATA,strings[I_ReadRes]);
	m_DispoPage.SetDlgItemText(IDC_IDPROG,strings[I_ID_BKo_W]);
	m_DispoPage.SetDlgItemText(IDC_EEPROM,strings[I_EE]);
	m_DispoPage.SetDlgItemText(IDC_CALIB_LOAD,strings[I_CalW]);
	m_DispoPage.SetDlgItemText(IDC_STATIC2,strings[I_OSCW]);
	m_DispoPage.SetDlgItemText(IDC_OSC_OSCCAL,strings[I_OSC]);
	m_DispoPage.SetDlgItemText(IDC_OSC_BK,strings[I_BKOSC]);
	m_DispoPage.SetDlgItemText(IDC_OSC_LOAD,strings[I_OSCF]);
	m_DispoPage.SetDlgItemText(IDC_STATICdev,strings[I_Dev]);
	m_DispoPage.SetDlgItemText(IDC_ATCONF,strings[I_AT_CONFIG]);
	m_DispoPage.SetDlgItemText(IDC_FUSE_P,strings[I_AT_FUSE]);
	m_DispoPage.SetDlgItemText(IDC_FUSEH_P,strings[I_AT_FUSEH]);
	m_DispoPage.SetDlgItemText(IDC_FUSEX_P,strings[I_AT_FUSEX]);
	m_DispoPage.SetDlgItemText(IDC_LOCK_P,strings[I_AT_LOCK]);
	m_DispoPage.SetDlgItemText(IDC_ICD_EN,strings[I_ICD_ENABLE]);
	m_DispoPage.SetDlgItemText(IDC_ICD_ADDR,strings[I_ICD_ADDRESS]);
	m_OpzioniPage.SetDlgItemText(IDC_CONNETTI,strings[I_CONN]);
	m_OpzioniPage.SetDlgItemText(IDC_REGISTRO,strings[I_LOG]);
	m_OpzioniPage.SetDlgItemText(IDC_STATICerr,strings[I_MAXERR]);
	m_OpzioniPage.SetDlgItemText(IDC_STATIC_L,strings[I_LANG]);
	m_OpzioniPage.SetDlgItemText(IDC_STATIC_USBD,strings[I_USBD]);
	m_OpzioniPage.SetDlgItemText(IDC_TESTHW,strings[I_TestHWB]);
	m_OpzioniPage.SetDlgItemText(IDC_WLANGFILE,strings[I_W_LANGFILE]);
	m_I2CSPIPage.SetDlgItemText(IDC_MODE,strings[I_I2CMode]);
	m_I2CSPIPage.SetDlgItemText(IDC_NBS,strings[I_I2C_NB]);
	m_I2CSPIPage.SetDlgItemText(IDC_REC,strings[I_I2CReceive]);
	m_I2CSPIPage.SetDlgItemText(IDC_SEND,strings[I_I2CSend]);
	m_I2CSPIPage.SetDlgItemText(IDC_msgSTRI,strings[I_I2CDATAOUT]);
	m_I2CSPIPage.SetDlgItemText(IDC_msgSTRU,strings[I_I2CDATATR]);
}


void COpenProgDlg::OnClose()
{
	CStdioFile f;
	CString s,t;
	MinRit=m_OpzioniPage.GetDlgItemInt(IDC_USBDMIN);
	s=argv[0];
	s.Replace(".exe",".ini");
	if (f.Open((LPCTSTR)s,CFile::modeCreate | CFile::modeWrite)){
		CString dev;
		m_DispoPage.m_dispo.GetLBText(m_DispoPage.m_dispo.GetCurSel(),dev);
		s.Format("device %s\n",dev);
		f.WriteString(s);
		m_OpzioniPage.m_language.GetLBText(m_OpzioniPage.m_language.GetCurSel(),t);
    	s.Format("language %s\n",t);
		f.WriteString(s);
		int vid=0,pid=0,maxerr=200;
		CString a;
		m_OpzioniPage.GetDlgItemText(IDC_VID,a);
		sscanf(a,"0x%X",&vid);
		m_OpzioniPage.GetDlgItemText(IDC_PID,a);
		sscanf(a,"0x%X",&pid);
		s.Format("vid 0x%x\n",vid);
		f.WriteString(s);
		s.Format("pid 0x%x\n",pid);
		f.WriteString(s);
		m_OpzioniPage.GetDlgItemText(IDC_ERRMAX,a);
		sscanf(a,"%d",&maxerr);
		s.Format("maxerr %d\n",maxerr);
		f.WriteString(s);
		s.Format("usb_delay %d\n",MinRit);
		f.WriteString(s);
		//int Dvreg=m_OpzioniPage.GetDlgItemInt(IDC_HVDV);
		//s.Format("delta_v %d\n",Dvreg);
		//f.WriteString(s);
		f.Close();
	}
	CDialog::OnClose();
}

void COpenProgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenProgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenProgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

#define EQ(s) !strncmp(s,dev,64)

void COpenProgDlg::OnWrite()
{
	char dev[64];
	int ee;
	if(MyDeviceDetected==FALSE) return;
	if (ReadHandle == INVALID_HANDLE_VALUE){
		PrintMessage(strings[S_InvHandle]);	//"Handle invalido\r\n"
		return;
	}
	MinRit=m_OpzioniPage.GetDlgItemInt(IDC_USBDMIN);
	m_DispoPage.m_dispo.GetLBText(m_DispoPage.m_dispo.GetCurSel(),dev);
	CButton* b=(CButton*)m_OpzioniPage.GetDlgItem(IDC_REGISTRO);
	saveLog=b->GetCheck();
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_EEPROM);
	ee=b->GetCheck();
	if(ee) ee=0xffff;
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_IDPROG);
	programID=b->GetCheck();
	max_err=m_OpzioniPage.GetDlgItemInt(IDC_ERRMAX);
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_CALIB_LOAD);
	load_calibword=b->GetCheck();
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_OSC_LOAD);
	load_osccal=b->GetCheck();
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_ICD_EN);
	ICDenable=b->GetCheck();
	CString str;
	m_DispoPage.GetDlgItemText(IDC_ICDADDR,str);
	int i=sscanf(str,"%x",&ICDaddr);
	if(i!=1||ICDaddr<0||ICDaddr>0xFFFF) ICDaddr=0x1FF0;
	if(!hvreg&&!strncmp(dev,"16F1",4)); // StartHVReg(8.5);
	else if(!hvreg&&(!strncmp(dev,"10",2)||!strncmp(dev,"12",2)||!strncmp(dev,"16",2))) StartHVReg(13);
//-------------PIC10-16---------------------------------------------------------
	if(!strncmp(dev,"10",2)||!strncmp(dev,"12",2)||!strncmp(dev,"16",2)){
		if(EQ("10F200")||EQ("10F204")||EQ("10F220")){
			Write12F5xx(0x100,0xFF);						//256
		}
		else if(EQ("12F508")||EQ("10F202")||EQ("10F206")||EQ("10F222")){
			Write12F5xx(0x200,0x1FF);						//512
		}
		else if(EQ("16F54")){
			Write12F5xx(0x200,-1);							//512, no osccal
		}
		else if(EQ("16C83")||EQ("16F83")||EQ("16F83A")){
			Write16F8x(0x200,ee?0x40:0);					//512, 64
		}
		else if(EQ("12F509")||EQ("12F510")||EQ("16F505")||EQ("16F506")){
			Write12F5xx(0x400,0x3FF);						//1K
		}
		else if(EQ("12F519")||EQ("16F526")){
			Write12F5xx(0x440,0x3FF);						//1K + 64
		}
		else if(EQ("12F609")||EQ("12F615")||EQ("16F610")){
			Write12F61x(0x400);								//1K
		}
		else if(EQ("16C84")||EQ("16F84")||EQ("16F84A")){
			Write16F8x(0x400,ee?0x40:0);					//1K, 64
		}
		else if(EQ("12F629")||EQ("12F675")||EQ("16F630")||EQ("16F676")){
			Write12F62x(0x400,ee?0x80:0);					//1K, 128
		}
		else if(EQ("16F627")){
			Write16F62x(0x400,ee?0x80:0);					//1K, 128
		}
		else if(EQ("12F635")||EQ("16F631")||EQ("16F627A")||EQ("16F785")){
			Write12F6xx(0x400,ee?0x80:0);					//1K, 128
		}
		else if(EQ("16F818")){
			Write16F81x(0x400,ee?0x80:0);					//1K, 128, vdd no delay
		}
		else if(EQ("16F57")||EQ("16F59")){
			Write12F5xx(0x800,-1);							//2K, no osccal
		}
		else if(EQ("16F616")){
			Write12F61x(0x800);								//2K
		}
		else if(EQ("16F716")){
			Write16F71x(0x800,1);							//2K, vdd
		}
		else if(EQ("16F870")||EQ("16F871")||EQ("16F872")){
			Write16F87x(0x800,ee?0x40:0);					//2K, 64
		}
		else if(EQ("16F628A")){
			Write12F6xx(0x800,ee?0x80:0);					//2K, 128
		}
		else if(EQ("16F628")){
			Write16F62x(0x800,ee?0x80:0);					//2K, 128
		}
		else if(EQ("16F882")){
			Write16F88x(0x800,ee?0x80:0);					//2K, 128
		}
		else if(EQ("12F683")||EQ("16F636")||EQ("16F639")||EQ("16F677")||EQ("16F684")||EQ("16F687")||EQ("16F785")){
			Write12F6xx(0x800,ee?0x100:0);					//2K, 256
		}
		else if(EQ("16F819")){
			Write16F81x(0x800,ee?0x100:0);					//2K, 256, vdd no delay
		}
		else if(EQ("16F1822")||EQ("16F1823")||EQ("16F1826")){
			Write16F1xxx(0x800,ee?0x100:0,0);				//2K, 256
		}
		else if(EQ("16F73")||EQ("16F74")){
			Write16F7x(0x1000,0);							//4K
		}
		else if(EQ("16F737")||EQ("16F747")){
			Write16F7x(0x1000,1);							//4K, vdd no delay
		}
		else if(EQ("16F873")||EQ("16F874")){
			Write16F87x(0x1000,ee?-0x80:0);					//4K, 128, ee@0x2200
		}
		else if(EQ("16F648A")||EQ("16F685")||EQ("16F688")||EQ("16F689")||EQ("16F690")||EQ("16F913")||EQ("16F914")){
			Write12F6xx(0x1000,ee?0x100:0);					//4K, 256
		}
		else if(EQ("16F873A")||EQ("16F874A")){
			Write16F87xA(0x1000,ee?0x80:0,0);				//4K, 128
		}
		else if(EQ("16F883")||EQ("16F884")){
			Write16F88x(0x1000,ee?0x100:0);					//4K, 256
		}
		else if(EQ("16F87")||EQ("16F88")){
			Write16F81x(0x1000,ee?0x100:0);					//4K, 256, vdd no delay
		}
		else if(EQ("16F1933")||EQ("16F1934")||EQ("16F1824")||EQ("16F1827")||EQ("16F1828")){
			Write16F1xxx(0x1000,ee?0x100:0,0);				//4K, 256
		}
		else if(EQ("16F76")||EQ("16F77")){
			Write16F7x(0x2000,0);							//8K
		}
		else if(EQ("16F767")||EQ("16F777")){
			Write16F7x(0x2000,1);							//8K, vdd no delay
		}
		else if(EQ("16F916")||EQ("16F917")||EQ("16F946")){
			Write12F6xx(0x2000,ee?0x100:0);					//8K, 256
		}
		else if(EQ("16F876")||EQ("16F877")){
			Write16F87x(0x2000,ee?-0x100:0);				//8K, 256, ee@0x2200
		}
		else if(EQ("16F876A")||EQ("16F877A")){
			Write16F87xA(0x2000,ee?0x100:0,0);				//8K, 256,
		}
		else if(EQ("16F886")||EQ("16F887")){
			Write16F88x(0x2000,ee?0x100:0);					//8K, 256
		}
		else if(EQ("16F1936")||EQ("16F1937")||EQ("16F1946")||EQ("16F1825")||EQ("16F1829")){
			Write16F1xxx(0x2000,ee?0x100:0,0);				//8K, 256
		}
		else if(EQ("16F1938")||EQ("16F1939")||EQ("16F1947")){
			Write16F1xxx(0x4000,ee?0x100:0,0);				//16K, 256
		}
		else{
			PrintMessage(strings[S_nodev_w]); //"Dispositivo non supportato in scrittura\r\n");
		}
	}
//-------------PIC18---------------------------------------------------------
// options:
//	bit [3:0]
//     0 = vdd before vpp (12V)
//     1 = vdd before vpp (9V)
//     2 = low voltage entry with 32 bit key
//	bit [7:4]
//     0 = normal eeprom write algoritm
//     1 = with unlock sequence 55 AA
//	bit [11:8]
//     0 = 5ms erase delay, 1ms code write time, 5ms EE write delay, 5ms config write time
//     1 = 550ms erase delay, 1.2ms code write time, no config or EEPROM
//     2 = 550ms erase delay, 3.4ms code write time, no config or EEPROM
	else if(!strncmp(dev,"18F",3)){
		if(EQ("18F1230")){
			Write18Fx(0x1000,ee?0x80:0,8,0x0F0F,0x8787,0);		//4K, 128, 8
		}
		else if(EQ("18F2221")||EQ("18F4221")){
			Write18Fx(0x1000,ee?0x100:0,8,0x3F3F,0x8F8F,0);		//4K, 256, 8
		}
		else if(EQ("18F1220")||EQ("18F2220")||EQ("18F4220")){
			Write18Fx(0x1000,ee?0x100:0,8,0x10000,0x80,0x10);		//4K, 256, 8, EE with unlock
		}
		else if(EQ("18F1330")){
			Write18Fx(0x2000,ee?0x80:0,8,0x0F0F,0x8787,0);		//8K, 128, 8
		}
		else if(EQ("18F2321")||EQ("18F4321")){
			Write18Fx(0x2000,ee?0x100:0,8,0x3F3F,0x8F8F,0);		//8K, 256, 8
		}
		else if(EQ("18F1320")||EQ("18F2320")||EQ("18F4320")||EQ("18F2331")||EQ("18F4331")){
			Write18Fx(0x2000,ee?0x100:0,8,0x10000,0x80,0x10);		//8K, 256, 8, EE with unlock
		}
		else if(EQ("18F13K50")){
			Write18Fx(0x2000,ee?0x100:0,8,0x0F0F,0x8F8F,1);		//8K, 256, 9V
		}
		else if(EQ("18F23K20")||EQ("18F43K20")){
			Write18Fx(0x2000,ee?0x100:0,16,0x0F0F,0x8F8F,1);		//8K, 256, 9V
		}
		else if(EQ("18F2439")||EQ("18F4439")){
			Write18Fx(0x3000,ee?0x100:0,8,0x10000,0x80,0x10);		//12K, 256, 8, EE with unlock
		}
		else if(EQ("18F2410")||EQ("18F4410")){
			Write18Fx(0x4000,0,32,0x3F3F,0x8F8F,0);				//16K, 0, 32
		}
		else if(EQ("18F24J10")||EQ("18F44J10")){
			Write18Fx(0x4000,0,64,0x0101,0x8080,0x202);				//16K, 0, 64, LV
		}
		else if(EQ("18F24J11")||EQ("18F24J50")||EQ("18F44J11")||EQ("18F44J50")){
			Write18Fx(0x4000,0,64,0x0101,0x8080,0x102);				//16K, 0, 64, LV
		}
		else if(EQ("18F2450")||EQ("18F4450")){
			Write18Fx(0x4000,0,16,0x3F3F,0x8F8F,0);				//16K, 0, 16
		}
		else if(EQ("18F14K50")){
			Write18Fx(0x4000,ee?0x100:0,16,0x0F0F,0x8F8F,1);	//16K, 256, 9V
		}
		else if(EQ("18F24K20")||EQ("18F44K20")){
			Write18Fx(0x4000,ee?0x100:0,32,0x0F0F,0x8F8F,1);	//16K, 256, 9V
		}
		else if(EQ("18F2431")||EQ("18F4431")||EQ("18F242")||EQ("18F248")||EQ("18F442")||EQ("18F448")){
			Write18Fx(0x4000,ee?0x100:0,8,0x10000,0x80,0x10);		//16K, 256, 8, EE with unlock
		}
		else if(EQ("18F2420")||EQ("18F2423")||EQ("18F4420")||EQ("18F4423")||EQ("18F2480")||EQ("18F4480")){
			Write18Fx(0x4000,ee?0x100:0,32,0x3F3F,0x8F8F,0);	//16K, 256, 32
		}
		else if(EQ("18F2455")||EQ("18F2458")||EQ("18F4455")||EQ("18F4458")){
			Write18Fx(0x6000,ee?0x100:0,32,0x3F3F,0x8F8F,0);	//24K, 256, 32
		}
		else if(EQ("18F2539")||EQ("18F4539")){
			Write18Fx(0x6000,ee?0x100:0,8,0x10000,0x80,0x10);	//24K, 256, 8, EE with unlock
		}
		else if(EQ("18F2510")||EQ("18F4510")){
			Write18Fx(0x8000,0,32,0x3F3F,0x8F8F,0);				//32K, 0, 32
		}
		else if(EQ("18F25J10")||EQ("18F45J10")){
			Write18Fx(0x8000,0,64,0x0101,0x8080,0x202);			//32K, 0, 64, LV
		}
		else if(EQ("18F25J11")||EQ("18F25J50")||EQ("18F45J11")||EQ("18F45J50")){
			Write18Fx(0x8000,0,64,0x0101,0x8080,0x102);			//32K, 0, 64, LV
		}
		else if(EQ("18F252")||EQ("18F258")||EQ("18F452")||EQ("18F458")){
			Write18Fx(0x8000,ee?0x100:0,8,0x10000,0x80,0x10);	//32K, 256, 8, EE with unlock
		}
		else if(EQ("18F2550")||EQ("18F2553")||EQ("18F4550")||EQ("18F4553")||EQ("18F2520")||EQ("18F2523")||EQ("18F4520")||EQ("18F4523")||EQ("18F2580")||EQ("18F4580")){
			Write18Fx(0x8000,ee?0x100:0,32,0x3F3F,0x8F8F,0);	//32K, 256, 32
		}
		else if(EQ("18F25K20")||EQ("18F45K20")){
			Write18Fx(0x8000,ee?0x100:0,32,0x0F0F,0x8F8F,1);	//32K, 256, 32, 9V
		}
		else if(EQ("18F2515")||EQ("18F4515")){
			Write18Fx(0xC000,0,64,0x3F3F,0x8F8F,0);				//48K, 0, 64
		}
		else if(EQ("18F2525")||EQ("18F2585")||EQ("18F4525")||EQ("18F4585")){
			Write18Fx(0xC000,ee?0x400:0,64,0x3F3F,0x8F8F,0);	//48K, 1K, 64
		}
		else if(EQ("18F2610")||EQ("18F4610")){
			Write18Fx(0x10000,0,64,0x3F3F,0x8F8F,0);			//64K, 0, 64
		}
		else if(EQ("18F26J11")||EQ("18F26J13")||EQ("18F26J50")||EQ("18F26J53")||EQ("18F46J11")||EQ("18F46J13")||EQ("18F46J50")||EQ("18F46J53")){
			Write18Fx(0x10000,0,64,0x0101,0x8080,0x102);		//64K, 0, 64, LV
		}
		else if(EQ("18F2620")||EQ("18F2680")||EQ("18F4620")||EQ("18F4680")){
			Write18Fx(0x10000,ee?0x400:0,64,0x3F3F,0x8F8F,0);	//64K, 1K, 64
		}
		else if(EQ("18F26K20")||EQ("18F46K20")){
			Write18Fx(0x10000,ee?0x100:0,64,0x0F0F,0x8F8F,1);	//64K, 256, 64, 9V
		}
		else if(EQ("18F2682")||EQ("18F4682")){
			Write18Fx(0x14000,ee?0x400:0,64,0x3F3F,0x8F8F,0);	//80K, 1K, 64
		}
		else if(EQ("18F2685")||EQ("18F4685")){
			Write18Fx(0x18000,ee?0x400:0,64,0x3F3F,0x8F8F,0);	//96K, 1K, 64
		}
		else if(EQ("18F27J13")||EQ("18F27J53")||EQ("18F47J13")||EQ("18F47J53")){
			Write18Fx(0x20000,0,64,0x0101,0x8080,0x102);		//128K, 0, 64, LV
		}
		else if(EQ("18F8722")){
			Write18Fx(0x20000,ee?0x400:0,64,0xFFFF,0x8787,0);	//128K, 1K, 64
		}
		else{
			PrintMessage(strings[S_nodev_w]); //"Dispositivo non supportato in scrittura\r\n");
		}
	}
//-------------PIC24---------------------------------------------------------
// options:
//	bit [3:0]
//     0 = low voltage ICSP entry
//     1 = High voltage ICSP entry (6V)
//     2 = High voltage ICSP entry (12V) + PIC30F sequence (additional NOPs)
//	bit [7:4]
//	   0 = config area in the last 2 program words
//	   1 = config area in the last 3 program words
//	   2 = config area in the last 4 program words
//	   3 = 0xF80000 to 0xF80010 except 02 (24F)
//     4 = 0xF80000 to 0xF80016 (24H-33F)
//     5 = 0xF80000 to 0xF8000C (x16 bit, 30F)
//     6 = 0xF80000 to 0xF8000E (30FSMPS)
//	bit [11:8]
//	   0 = code erase word is 0x4064, row write is 0x4004
//	   1 = code erase word is 0x404F, row write is 0x4001
//	   2 = code erase word is 0x407F, row write is 0x4001, 55AA unlock and external timing (2 ms)
//	   3 = code erase word is 0x407F, row write is 0x4001, 55AA unlock and external timing (200 ms)
//	bit [15:12]
//	   0 = eeprom erase word is 0x4050, write word is 0x4004
//	   1 = eeprom erased with bulk erase, write word is 0x4004
//	   2 = eeprom erased with special sequence, write word is 0x4004
//	bit [19:16]
//	   0 = config write is 0x4000
//	   1 = config write is 0x4003
//	   2 = config write is 0x4004
//	   3 = config write is 0x4008
	else if(!strncmp(dev,"24F",3)||!strncmp(dev,"24H",3)||!strncmp(dev,"30F",3)||!strncmp(dev,"33F",3)){
		if(EQ("24F04KA200")||EQ("24F04KA201")){
			Write24Fx(0xB00,0,0x20031,0x05BE,32,2.0);				//1.375KW, HV
		}
		else if(EQ("24F08KA101")||EQ("24F08KA102")){
			Write24Fx(0x1600,ee?0x200:0,0x20031,0x05BE,32,2.0);		//2.75KW, HV, 512
		}
		else if(EQ("24F16KA101")||EQ("24F16KA102")){
			Write24Fx(0x2C00,ee?0x200:0,0x20031,0x05BE,32,2.0);		//5.5KW, HV, 512
		}
		else if(EQ("24FJ16GA002")||EQ("24FJ16GA004")){
			Write24Fx(0x2C00,0,0x10100,0x05BE,64,2.0);				//5.5KW
		}
		else if(EQ("24FJ32GA002")||EQ("24FJ32GA004")){
			Write24Fx(0x5800,0,0x10100,0x05BE,64,2.0);				//11KW
		}
		else if(EQ("24FJ32GA102")||EQ("24FJ32GA104")||EQ("24FJ32GB002")||EQ("24FJ32GB004")){
			Write24Fx(0x5800,0,0x10120,0x07F0,64,2.0);				//11KW
		}
		else if(EQ("24FJ48GA002")||EQ("24FJ48GA004")){
			Write24Fx(0x8400,0,0x10100,0x05BE,64,2.0);				//16.5KW
		}
		else if(EQ("24FJ64GA002")||EQ("24FJ64GA004")||EQ("24FJ64GA006")||EQ("24FJ64GA008")||EQ("24FJ64GA010")){
			Write24Fx(0xAC00,0,0x10100,0x05BE,64,2.0);				//22KW
		}
		else if(EQ("24FJ64GA102")||EQ("24FJ64GA104")||EQ("24FJ64GB002")||EQ("24FJ64GB004")){
			Write24Fx(0xAC00,0,0x10120,0x07F0,64,2.0);				//22KW
		}
		else if(EQ("24FJ64GB106")||EQ("24FJ64GB108")||EQ("24FJ64GB110")){
			Write24Fx(0xAC00,0,0x10110,0x07F0,64,2.0);				//22KW
		}
		else if(EQ("24FJ96GA006")||EQ("24FJ96GA008")||EQ("24FJ96GA010")){
			Write24Fx(0x10000,0,0x10100,0x05BE,64,2.0);				//32KW
		}
		else if(EQ("24FJ128GA006")||EQ("24FJ128GA008")||EQ("24FJ128GA010")){
			Write24Fx(0x15800,0,0x10100,0x05BE,64,2.0);				//44KW
		}
		else if(EQ("24FJ128GA106")||EQ("24FJ128GA108")||EQ("24FJ128GA110")||EQ("24FJ128GB106")||EQ("24FJ128GB108")||EQ("24FJ128GB110")){
			Write24Fx(0x15800,0,0x10110,0x07F0,64,2.0);				//44KW
		}
		else if(EQ("24FJ192GA106")||EQ("24FJ192GA108")||EQ("24FJ192GA110")||EQ("24FJ192GB106")||EQ("24FJ192GB108")||EQ("24FJ192GB110")){
			Write24Fx(0x20C00,0,0x10110,0x07F0,64,2.0);				//68KW
		}
		else if(EQ("24FJ256GA106")||EQ("24FJ256GA108")||EQ("24FJ256GA110")||EQ("24FJ256GB106")||EQ("24FJ256GB108")||EQ("24FJ256GB110")){
			Write24Fx(0x2AC00,0,0x10110,0x07F0,64,2.0);				//88KW
		}
		else if(!strncmp(dev,"33FJ06",6)){
			Write24Fx(0x1000,0,0x00140,0x07F0,64,2.0);				//2KW
		}
		else if(!strncmp(dev,"24HJ12",6)||!strncmp(dev,"33FJ12",6)){
			Write24Fx(0x2000,0,0x00140,0x07F0,64,2.0);				//4KW
		}
		else if(!strncmp(dev,"24HJ16",6)||!strncmp(dev,"33FJ16",6)){
			Write24Fx(0x2C00,0,0x00140,0x07F0,64,2.0);				//5.5KW
		}
		else if(!strncmp(dev,"24HJ32",6)||!strncmp(dev,"33FJ32",6)){
			Write24Fx(0x5800,0,0x00140,0x07F0,64,2.0);				//11KW
		}
		else if(!strncmp(dev,"24HJ64",6)||!strncmp(dev,"33FJ64",6)){
			Write24Fx(0xAC00,0,0x00140,0x07F0,64,2.0);				//22KW
		}
		else if(!strncmp(dev,"24HJ128",7)||!strncmp(dev,"33FJ128",7)){
			Write24Fx(0x15800,0,0x00140,0x07F0,64,2.0);				//44KW
		}
		else if(!strncmp(dev,"24HJ256",7)||!strncmp(dev,"33FJ256",7)){
			Write24Fx(0x2AC00,0,0x00140,0x07F0,64,2.0);				//88KW
		}
		else if(EQ("30F2010")){
			Write24Fx(0x2000,ee?0x400:0,0x31252,0x05BE,32,2.0);		//4KW, 1K, HV12
		}
		else if(EQ("30F2011")||EQ("30F2012")){
			Write24Fx(0x2000,0,0x31252,0x05BE,32,2.0);				//4KW, HV12
		}
		else if(!strncmp(dev,"30F301",6)){
			Write24Fx(0x4000,ee?0x400:0,0x31252,0x05BE,32,2.0);		//8KW, 1K, HV12
		}
		else if(!strncmp(dev,"30F401",6)){
			Write24Fx(0x8000,ee?0x400:0,0x31252,0x05BE,32,2.0);		//16KW, 1K, HV12
		}
		else if(!strncmp(dev,"30F501",6)){
			Write24Fx(0xB000,ee?0x400:0,0x31252,0x05BE,32,2.0);		//22KW, 1K, HV12
		}
		else if(EQ("30F6011")||EQ("30F6013")){
			Write24Fx(0x16000,ee?0x800:0,0x31252,0x05BE,32,2.0);	//44KW, 2K, HV12
		}
		else if(EQ("30F6010")||EQ("30F6012")||EQ("30F6014")||EQ("30F6015")){
			Write24Fx(0x18000,ee?0x1000:0,0x31252,0x05BE,32,2.0);	//49KW, 4K, HV12
		}
		else{
			PrintMessage(strings[S_nodev_w]); //"Dispositivo non supportato in scrittura\r\n");
		}
	}
//-------------ATMEL---------------------------------------------------------
	else if(!strncmp(dev,"AT",2)){
		if(EQ("AT90S1200")){
			WriteAT(0x400,ee?0x40:0);						//1K, 64
		}
		else if(EQ("AT90S2313")){
			WriteAT(0x800,ee?0x80:0);						//2K, 128
		}
		else if(EQ("ATtiny2313")){
			WriteATmega(0x800,ee?0x80:0,16,SLOW);			//2K, 128
		}
		else if(EQ("AT90S8515")||EQ("AT90S8535")){
			WriteAT(0x2000,ee?0x100:0);						//8K, 256
		}
		else if(EQ("ATmega8")||EQ("ATmega8A")||EQ("ATmega8515")||EQ("ATmega8535")){
			WriteATmega(0x2000,ee?0x200:0,32,0);				//8K, 512
		}
		else if(EQ("ATmega16")||EQ("ATmega16A")){
			WriteATmega(0x4000,ee?0x200:0,64,0);				//16K, 512
		}
		else if(EQ("ATmega32")||EQ("ATmega32A")){
			WriteATmega(0x8000,ee?0x400:0,64,0);				//32K, 1K
		}
		else if(EQ("ATmega64")||EQ("ATmega64A")){
			WriteATmega(0x10000,ee?0x800:0,128,0);			//64K, 2K
		}
		else{
			PrintMessage(strings[S_nodev_w]); //"Dispositivo non supportato in scrittura\r\n");
		}
	}
//-------------I2C---------------------------------------------------------
	else if(!strncmp(dev,"24",2)||!strncmp(dev,"25",2)||!strncmp(dev,"93",2)){
		if(EQ("2400")){
			WriteI2C(0x10,0,1,10);			//16, 1B addr.
		}
		else if(EQ("2401")){
			WriteI2C(0x80,0,8,10);			//128, 1B addr.
		}
		else if(EQ("2402")){
			WriteI2C(0x100,0,8,10);			//256, 1B addr.
		}
		else if(EQ("2404")){
			WriteI2C(0x200,0,16,10);		//512, 1B addr.
		}
		else if(EQ("2408")){
			WriteI2C(0x400,0,16,10);		//1K, 1B addr.
		}
		else if(EQ("2416")){
			WriteI2C(0x800,0,16,10);		//2K, 1B addr.
		}
		else if(EQ("2432")){
			WriteI2C(0x1000,1,32,5);		//4K, 2B addr.
		}
		else if(EQ("2464")){
			WriteI2C(0x2000,1,32,5);		//8K, 2B addr.
		}
		else if(EQ("24128")){
			WriteI2C(0x4000,1,64,5);		//16K, 2B addr.
		}
		else if(EQ("24256")){
			WriteI2C(0x8000,1,64,5);		//32K, 2B addr.
		}
		else if(EQ("24512")){
			WriteI2C(0x10000,1,128,5);		//64K, 2B addr.
		}
		else if(EQ("241024")){
			WriteI2C(0x20000,0x201,256,5);	//128K, 2B addr.
		}
		else if(EQ("241025")){
			WriteI2C(0x20000,0x841,128,5);	//128K, 2B addr.
		}
//-------------Microwire EEPROM---------------------------------------------------------
		else if(EQ("93S46")){
			Write93Sx(0x80,6,8,10);							//128, 4W page, 10ms
		}
		else if(EQ("93x46")){
			Write93Cx(0x80,6,0);							//128,
		}
		else if(EQ("93x46A")){
			Write93Cx(0x80,7,1);							//128, x8
		}
		else if(EQ("93S56")){
			Write93Sx(0x100,8,8,10);						//256, 4W page, 10ms
		}
		else if(EQ("93x56")){
			Write93Cx(0x100,8,0);							//256,
		}
		else if(EQ("93x56A")){
			Write93Cx(0x100,9,1);							//256, x8
		}
		else if(EQ("93S66")){
			Write93Sx(0x200,8,8,10);						//512, 4W page, 10ms
		}
		else if(EQ("93x66")){
			Write93Cx(0x200,8,0);						//512,
		}
		else if(EQ("93x66A")){
			Write93Cx(0x200,9,1);						//512, x8
		}
		else if(EQ("93x76")){
			Write93Cx(0x400,10,0);						//1k
		}
		else if(EQ("93x76A")){
			Write93Cx(0x400,11,1);						//1k, x8
		}
		else if(EQ("93x86")){
			Write93Cx(0x800,10,0);						//2k,
		}
		else if(EQ("93x86A")){
			Write93Cx(0x800,11,1);						//2k, x8
		}
//-------------SPI---------------------------------------------------------
		else if(EQ("25010")){
			Write25xx(0x80,16,10);								//128
		}
		else if(EQ("25020")){
			Write25xx(0x100,16,10);								//256
		}
		else if(EQ("25040")){
			Write25xx(0x200,16,10);								//512
		}
		else if(EQ("25080")){
			Write25xx(0x400,16,5);								//1K
		}
		else if(EQ("25160")){
			Write25xx(0x800,16,5);								//2K
		}
		else if(EQ("25320")){
			Write25xx(0x1000,32,5);								//4K
		}
		else if(EQ("25640")){
			Write25xx(0x2000,32,5);								//8K
		}
		else if(EQ("25128")){
			Write25xx(0x4000,64,5);								//16K
		}
		else if(EQ("25256")){
			Write25xx(0x8000,64,5);								//32K
		}
		else if(EQ("25512")){
			Write25xx(0x10000,128,6);							//64K
		}
		else if(EQ("251024")){
			Write25xx(0x20000,256,5);							//128K
		}
		else{
			PrintMessage(strings[S_nodev_w]); //"Dispositivo non supportato in scrittura\r\n");
		}
	}
//-------------Unsupported device---------------------------------------------------------
	else{
		PrintMessage(strings[S_nodev_w]); //"Dispositivo non supportato in scrittura\r\n");
	}
}

void COpenProgDlg::OnRead()
{
	//CString c;
	char dev[64];
	int r,ee;
	if(MyDeviceDetected==FALSE) return;
	if (ReadHandle == INVALID_HANDLE_VALUE){
		PrintMessage(strings[S_InvHandle]);	//"Handle invalido\r\n"
		return;
	}
	MinRit=m_OpzioniPage.GetDlgItemInt(IDC_USBDMIN);
	m_DispoPage.m_dispo.GetLBText(m_DispoPage.m_dispo.GetCurSel(),dev);
	CButton* b=(CButton*)m_DispoPage.GetDlgItem(IDC_RISERVATA);
	r=b->GetCheck();
	if(r) r=0xffff;
	b=(CButton*)m_OpzioniPage.GetDlgItem(IDC_REGISTRO);
	saveLog=b->GetCheck();
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_EEPROM);
	ee=b->GetCheck();
	if(ee) ee=0xffff;
	if(!hvreg&&!strncmp(dev,"16F1",4)); // StartHVReg(8.5);
	else if(!hvreg&&(!strncmp(dev,"10",2)||!strncmp(dev,"12",2)||!strncmp(dev,"16",2))) StartHVReg(13);
//-------------PIC10-16---------------------------------------------------------
	if(!strncmp(dev,"10",2)||!strncmp(dev,"12",2)||!strncmp(dev,"16",2)){
		if(EQ("10F200")||EQ("10F204")||EQ("10F220")){
			Read12F5xx(0x100,r?0x40:5);						//256
		}
		else if(!strncmp(dev,"12C508",6)||EQ("16F54")){
			Read12F5xx(0x200,r?0x40:4);						//512
		}
		else if(EQ("12F508")||EQ("10F202")||EQ("10F206")||EQ("10F222")){
			Read12F5xx(0x200,r?0x40:5);						//512
		}
		else if(EQ("16C83")||EQ("16F83")||EQ("16F83A")){
			Read16Fxxx(0x200,ee?0x40:0,r?0x10:8,1);			//512, 64, vdd
		}
		else if(!strncmp(dev,"12C509",6)){
			Read12F5xx(0x400,r?0x40:4);						//1K
		}
		else if(EQ("12F509")||EQ("12F510")||EQ("16F505")||EQ("16F506")){
			Read12F5xx(0x400,r?0x40:5);						//1K
		}
		else if(EQ("12F519")||EQ("16F526")){
			Read12F5xx(0x440,r?0x60:8);						//1K + 64
		}
		else if(EQ("12C671")||EQ("12CE673")){
			Read16Fxxx(0x400,0,r?0x100:0,0);				//1K, vpp
		}
		else if(EQ("12F609")||EQ("12F615")||EQ("16F610")){
			Read16Fxxx(0x400,0,r?0x40:9,0);					//1K, vpp, cal1
		}
		else if(EQ("16C84")||EQ("16F84")||EQ("16F84A")){
			Read16Fxxx(0x400,ee?0x40:0,r?0x10:8,1);			//1K, 64, vdd
		}
		else if(EQ("12F635")){
			Read16Fxxx(0x400,ee?0x80:0,r?0x40:10,0);		//1K, 128, vpp, cal1 + cal2
		}
		else if(EQ("16F631")){
			Read16Fxxx(0x400,ee?0x80:0,r?0x80:9,0);			//1K, 128, vpp, cal1
		}
		else if(EQ("12F629")||EQ("12F675")||EQ("16F630")||EQ("16F676")){
			Read16Fxxx(0x400,ee?0x80:0,r?0x20:8,0);			//1K, 128, vpp
		}
		else if(EQ("16F627")){
			Read16Fxxx(0x400,ee?-0x80:0,r?0x10:8,0);		//1K, 128, vpp, ee@0x2200
		}
		else if(EQ("16F627A")){
			Read16Fxxx(0x400,ee?0x80:0,r?0x10:8,0);			//1K, 128, vpp
		}
		else if(EQ("16F818")){
			Read16Fxxx(0x400,ee?0x80:0,r?0x10:8,2);			//1K, 128, vdd short delay
		}
		else if(EQ("16F57")||EQ("16F59")){
			Read12F5xx(0x800,r?0x40:4);						//2K
		}
		else if(EQ("12C672")||EQ("12CE674")){
			Read16Fxxx(0x800,0,r?0x100:0,0);				//2K, vpp
		}
		else if(EQ("16F716")){
			Read16Fxxx(0x800,0,8,2);						//2K, vdd
		}
		else if(EQ("16F616")){
			Read16Fxxx(0x800,0,r?0x40:9,0);					//2K, vpp, cal1
		}
		else if(EQ("16F870")||EQ("16F871")||EQ("16F872")){
			Read16Fxxx(0x800,ee?0x40:0,r?0x100:8,1);		//2K, 64, vdd
		}
		else if(EQ("16F628")){
			Read16Fxxx(0x800,ee?-0x80:0,r?0x10:8,0);		//2K, 128, vpp, ee@0x2200
		}
		else if(EQ("16F628A")){
			Read16Fxxx(0x800,ee?0x80:0,r?0x10:8,0);			//2K, 128, vpp
		}
		else if(EQ("16F882")){
			Read16Fxxx(0x800,ee?0x80:0,r?0x80:10,0);		//2K, 128, vpp, config2 + cal1
		}
		else if(EQ("16F819")){
			Read16Fxxx(0x800,ee?0x100:0,r?0x10:8,2);		//2K, 256, vdd short delay
		}
		else if(EQ("12F683")||EQ("16F684")){
			Read16Fxxx(0x800,ee?0x100:0,r?0x40:9,0);		//2K, 256, vpp, cal1
		}
		else if(EQ("16F636")||EQ("16F639")||EQ("16F785")||EQ("16F785")){
			Read16Fxxx(0x800,ee?0x100:0,r?0x40:10,0);		//2K, 256, vpp, cal1 + cal2
		}
		else if(EQ("16F677")||EQ("16F687")){
			Read16Fxxx(0x800,ee?0x100:0,r?0x80:9,0);		//2K, 256, vpp, cal1
		}
		else if(EQ("16F1822")||EQ("16F1823")||EQ("16F1826")){
			Read16F1xxx(0x800,ee?0x100:0,r?0x200:11,0);		//2K, 256, vpp
		}
		else if(EQ("16F73")||EQ("16F74")){
			Read16Fxxx(0x1000,0,r?0x20:8,1);				//4K, vdd
		}
		else if(EQ("16F737")||EQ("16F747")){
			Read16Fxxx(0x1000,0,r?0x40:9,2);				//4K, vdd short delay
		}
		else if(EQ("16F873A")||EQ("16F874A")){
			Read16Fxxx(0x1000,ee?0x80:0,r?0x100:8,1);		//4K, 128, vdd
		}
		else if(EQ("16F873")||EQ("16F874")){
			Read16Fxxx(0x1000,ee?-0x80:0,r?0x100:8,1);		//4K, 128, vdd, ee@0x2200
		}
		else if(EQ("16F685")||EQ("16F689")||EQ("16F690")){
			Read16Fxxx(0x1000,ee?0x100:0,r?0x80:9,0);		//4K, 256, vpp, cal1
		}
		else if(EQ("16F688")){
			Read16Fxxx(0x1000,ee?0x100:0,r?0x40:9,0);		//4K, 256, vpp, cal1
		}
		else if(EQ("16F883")||EQ("16F884")){
			Read16Fxxx(0x1000,ee?0x100:0,r?0x80:10,0);		//4K, 256, vpp, config2 + cal1
		}
		else if(EQ("16F648A")){
			Read16Fxxx(0x1000,ee?0x100:0,r?0x10:8,0);		//4K, 256, vpp
		}
		else if(EQ("16F87")||EQ("16F88")){
			Read16Fxxx(0x1000,ee?0x100:0,r?0x10:9,2);		//4K, 256, vdd short delay
		}
		else if(EQ("16F913")||EQ("16F914")){
			Read16Fxxx(0x1000,ee?0x100:0,r?0x40:10,0);		//4K, 256, vpp, cal1 + cal2
		}
		else if(EQ("16F1933")||EQ("16F1934")||EQ("16F1824")||EQ("16F1827")||EQ("16F1828")){
			Read16F1xxx(0x1000,ee?0x100:0,r?0x200:11,0);	//4K, 256, vpp
		}
		else if(EQ("16F76")||EQ("16F77")){
			Read16Fxxx(0x2000,0,r?0x20:8,1);				//8K, vdd
		}
		else if(EQ("16F767")||EQ("16F777")){
			Read16Fxxx(0x2000,0,r?0x40:9,2);				//8K, vdd short delay
		}
		else if(EQ("16F876A")||EQ("16F877A")){
			Read16Fxxx(0x2000,ee?0x100:0,r?0x100:8,1);		//8K, 256, vdd
		}
		else if(EQ("16F876")||EQ("16F877")){
			Read16Fxxx(0x2000,ee?-0x100:0,r?0x100:8,1);		//8K, 256, vdd, ee@0x2200
		}
		else if(EQ("16F886")||EQ("16F887")){
			Read16Fxxx(0x2000,ee?0x100:0,r?0x80:10,0);		//8K, 256, vpp, config2 + cal1
		}
		else if(EQ("16F916")||EQ("16F917")||EQ("16F946")){
			Read16Fxxx(0x2000,ee?0x100:0,r?0x40:10,0);		//8K, 256, vpp, cal1 + cal2
		}
		else if(EQ("16F1936")||EQ("16F1937")||EQ("16F1946")||EQ("16F1825")||EQ("16F1829")){
			Read16F1xxx(0x2000,ee?0x100:0,r?0x200:11,0);	//8K, 256, vpp
		}
		else if(EQ("16F1938")||EQ("16F1939")||EQ("16F1947")){
			Read16F1xxx(0x4000,ee?0x100:0,r?0x200:11,0);	//16K, 256, vpp
		}
		else{
			PrintMessage(strings[S_nodev_r]); //"Dispositivo non supportato in lettura\r\n");
		}
	}
//-------------PIC18---------------------------------------------------------
	else if(!strncmp(dev,"18F",3)){
		if(EQ("18F1230")){
			Read18Fx(0x1000,ee?0x80:0,0);					//4K, 128
		}
		else if(EQ("18F2221")||EQ("18F4221")||EQ("18F1220")||EQ("18F2220")||EQ("18F4220")){
			Read18Fx(0x1000,ee?0x100:0,0);					//4K, 256
		}
		else if(EQ("18F1330")){
			Read18Fx(0x2000,ee?0x80:0,0);					//8K, 128
		}
		else if(EQ("18F2321")||EQ("18F4321")||EQ("18F1320")||EQ("18F2320")||EQ("18F4320")||EQ("18F2331")||EQ("18F4331")){
			Read18Fx(0x2000,ee?0x100:0,0);					//8K, 256
		}
		else if(EQ("18F13K50")||EQ("18F23K20")||EQ("18F43K20")){
			Read18Fx(0x2000,ee?0x100:0,1);					//8K, 256, 9V
		}
		else if(EQ("18F2439")||EQ("18F4439")){
			Read18Fx(0x3000,ee?0x100:0,0);					//12K, 256
		}
		else if(EQ("18F2410")||EQ("18F4410")||EQ("18F2450")||EQ("18F4450")){
			Read18Fx(0x4000,0,0);							//16K, 0
		}
		else if(EQ("18F24J10")||EQ("18F44J10")||EQ("18F24J11")||EQ("18F24J50")||EQ("18F44J11")||EQ("18F44J50")){
			Read18Fx(0x4000,0,2);							//16K, 0, LV
		}
		else if(EQ("18F2420")||EQ("18F2423")||EQ("18F4420")||EQ("18F4423")||EQ("18F2431")||EQ("18F4431")||EQ("18F2480")||EQ("18F4480")||EQ("18F242")||EQ("18F248")||EQ("18F442")||EQ("18F448")){
			Read18Fx(0x4000,ee?0x100:0,0);					//16K, 256
		}
		else if(EQ("18F14K50")||EQ("18F24K20")||EQ("18F44K20")){
			Read18Fx(0x4000,ee?0x100:0,1);					//16K, 256, 9V
		}
		else if(EQ("18F2455")||EQ("18F2458")||EQ("18F4455")||EQ("18F4458")||EQ("18F2539")||EQ("18F4539")){
			Read18Fx(0x6000,ee?0x100:0,0);					//24K, 256
		}
		else if(EQ("18F2510")||EQ("18F4510")){
			Read18Fx(0x8000,0,0);							//32K, 0
		}
		else if(EQ("18F25J10")||EQ("18F25J11")||EQ("18F25J50")||EQ("18F45J10")||EQ("18F45J11")||EQ("18F45J50")){
			Read18Fx(0x8000,0,2);							//32K, 0, LV
		}
		else if(EQ("18F2550")||EQ("18F2553")||EQ("18F4550")||EQ("18F4553")||EQ("18F2520")||EQ("18F2523")||EQ("18F4520")||EQ("18F4523")||EQ("18F2580")||EQ("18F4580")||EQ("18F252")||EQ("18F258")||EQ("18F452")||EQ("18F458")){
			Read18Fx(0x8000,ee?0x100:0,0);					//32K, 256
		}
		else if(EQ("18F25K20")||EQ("18F45K20")){
			Read18Fx(0x8000,ee?0x100:0,1);					//32K, 256, 9V
		}
		else if(EQ("18F2515")||EQ("18F4515")){
			Read18Fx(0xC000,0,0);							//48K, 0
		}
		else if(EQ("18F2525")||EQ("18F2585")||EQ("18F4525")||EQ("18F4585")){
			Read18Fx(0xC000,ee?0x400:0,0);					//48K, 1K
		}
		else if(EQ("18F2610")||EQ("18F4610")){
			Read18Fx(0x10000,0,0);							//64K, 0
		}
		else if(EQ("18F26J11")||EQ("18F26J13")||EQ("18F26J50")||EQ("18F26J53")||EQ("18F46J11")||EQ("18F46J13")||EQ("18F46J50")||EQ("18F46J53")){
			Read18Fx(0x10000,0,2);							//64K, 0, LV
		}
		else if(EQ("18F2620")||EQ("18F2680")||EQ("18F4620")||EQ("18F4680")){
			Read18Fx(0x10000,ee?0x400:0,0);					//64K, 1K
		}
		else if(EQ("18F26K20")||EQ("18F46K20")){
			Read18Fx(0x10000,ee?0x400:0,1);					//64K, 1K, 9V
		}
		else if(EQ("18F2682")||EQ("18F4682")){
			Read18Fx(0x14000,ee?0x400:0,0);					//80K, 1K
		}
		else if(EQ("18F2685")||EQ("18F4685")){
			Read18Fx(0x18000,ee?0x400:0,0);					//96K, 1K
		}
		else if(EQ("18F27J13")||EQ("18F27J53")||EQ("18F47J13")||EQ("18F47J53")){
			Read18Fx(0x20000,0,2);							//128K, 0, LV
		}
		else if(EQ("18F8722")){
			Read18Fx(0x20000,ee?0x400:0,0);					//128K, 1K
		}
		else{
			PrintMessage(strings[S_nodev_r]); //"Dispositivo non supportato in lettura\r\n");
		}
	}
//-------------PIC24---------------------------------------------------------
// options:
//	bit [3:0]
//     0 = low voltage ICSP entry
//     1 = High voltage ICSP entry (6V)
//     2 = High voltage ICSP entry (12V) + PIC30F sequence (additional NOPs)
//	bit [7:4]
//	   0 = config area in the last 2 program words
//	   1 = config area in the last 3 program words
//	   2 = config area in the last 4 program words
//	   3 = 0xF80000 to 0xF80010 except 02 (24F)
//     4 = 0xF80000 to 0xF80016 (24H-33F)
//     5 = 0xF80000 to 0xF8000C (x16 bit, 30F)
//     6 = 0xF80000 to 0xF8000E (30FSMPS)
	else if(!strncmp(dev,"24F",3)||!strncmp(dev,"24H",3)||!strncmp(dev,"30F",3)||!strncmp(dev,"33F",3)){
		if(EQ("24F04KA200")||EQ("24F04KA201")){
			Read24Fx(0xB00,0,0x31,0x05BE,r?0x800:0);				//1.375KW, HV
		}
		else if(EQ("24F08KA101")||EQ("24F08KA102")){
			Read24Fx(0x1600,ee?0x200:0,0x31,0x05BE,r?0x800:0);		//2.75KW, HV, 512
		}
		else if(EQ("24F16KA101")||EQ("24F16KA102")){
			Read24Fx(0x2C00,ee?0x200:0,0x31,0x05BE,r?0x800:0);		//5.5KW, HV, 512
		}
		else if(EQ("24FJ16GA002")||EQ("24FJ16GA004")){
			Read24Fx(0x2C00,0,0,0x05BE,r?0x800:0);					//5.5KW
		}
		else if(EQ("24FJ32GA002")||EQ("24FJ32GA004")){
			Read24Fx(0x5800,0,0,0x05BE,r?0x800:0);					//11KW
		}
		else if(EQ("24FJ48GA002")||EQ("24FJ48GA004")){
			Read24Fx(0x8400,0,0,0x05BE,r?0x800:0);					//16.5KW
		}
		else if(EQ("24FJ64GA002")||EQ("24FJ64GA004")||EQ("24FJ64GA006")||EQ("24FJ64GA008")||EQ("24FJ64GA010")){
			Read24Fx(0xAC00,0,0,0x05BE,r?0x800:0);					//22KW
		}
		else if(EQ("24FJ64GB106")||EQ("24FJ64GB108")||EQ("24FJ64GB110")){
			Read24Fx(0xAC00,0,0x10,0x07F0,r?0x800:0);					//22KW
		}
		else if(EQ("24FJ96GA006")||EQ("24FJ96GA008")||EQ("24FJ96GA010")){
			Read24Fx(0x10000,0,0,0x05BE,r?0x800:0);					//32KW
		}
		else if(EQ("24FJ128GA006")||EQ("24FJ128GA008")||EQ("24FJ128GA010")){
			Read24Fx(0x15800,0,0,0x05BE,r?0x800:0);					//44KW
		}
		else if(EQ("24FJ128GA106")||EQ("24FJ128GA108")||EQ("24FJ128GA110")||EQ("24FJ128GB106")||EQ("24FJ128GB108")||EQ("24FJ128GB110")){
			Read24Fx(0x15800,0,0x10,0x07F0,r?0x800:0);					//44KW
		}
		else if(EQ("24FJ192GA106")||EQ("24FJ192GA108")||EQ("24FJ192GA110")||EQ("24FJ192GB106")||EQ("24FJ192GB108")||EQ("24FJ192GB110")){
			Read24Fx(0x20C00,0,0x10,0x07F0,r?0x800:0);					//68KW
		}
		else if(EQ("24FJ256GA106")||EQ("24FJ256GA108")||EQ("24FJ256GA110")||EQ("24FJ256GB106")||EQ("24FJ256GB108")||EQ("24FJ256GB110")){
			Read24Fx(0x2AC00,0,0x10,0x07F0,r?0x800:0);					//88KW
		}
		else if(!strncmp(dev,"33FJ06",6)){
			Read24Fx(0x1000,0,0x40,0x07F0,r?0x800:0);				//2KW
		}
		else if(!strncmp(dev,"24HJ12",6)||!strncmp(dev,"33FJ12",6)){
			Read24Fx(0x2000,0,0x40,0x07F0,r?0x800:0);				//4KW
		}
		else if(!strncmp(dev,"24HJ16",6)||!strncmp(dev,"33FJ16",6)){
			Read24Fx(0x2C00,0,0x40,0x07F0,r?0x800:0);				//5.5KW
		}
		else if(!strncmp(dev,"24HJ32",6)||!strncmp(dev,"33FJ32",6)){
			Read24Fx(0x5800,0,0x40,0x07F0,r?0x1000:0);				//11KW
		}
		else if(!strncmp(dev,"24HJ64",6)||!strncmp(dev,"33FJ64",6)){
			Read24Fx(0xAC00,0,0x40,0x07F0,r?0x1000:0);				//22KW
		}
		else if(!strncmp(dev,"24HJ128",7)||!strncmp(dev,"33FJ128",7)){
			Read24Fx(0x15800,0,0x40,0x07F0,r?0x1000:0);				//44KW
		}
		else if(!strncmp(dev,"24HJ256",7)||!strncmp(dev,"33FJ256",7)){
			Read24Fx(0x2AC00,0,0x40,0x07F0,r?0x1000:0);				//88KW
		}
		else if(EQ("30F2010")){
			Read24Fx(0x2000,ee?0x400:0,0x52,0x05BE,r?0x600:0);		//4KW, 1K, HV12
		}
		else if(EQ("30F2011")||EQ("30F2012")){
			Read24Fx(0x2000,0,0x52,0x05BE,r?0x600:0);				//4KW, HV12
		}
		else if(!strncmp(dev,"30F301",6)){
			Read24Fx(0x4000,ee?0x400:0,0x52,0x05BE,r?0x600:0);		//8KW, 1K, HV12
		}
		else if(!strncmp(dev,"30F401",6)){
			Read24Fx(0x8000,ee?0x400:0,0x52,0x05BE,r?0x600:0);		//16KW, 1K, HV12
		}
		else if(!strncmp(dev,"30F501",6)){
			Read24Fx(0xB000,ee?0x400:0,0x52,0x05BE,r?0x600:0);		//22KW, 1K, HV12
		}
		else if(EQ("30F6011")||EQ("30F6013")){
			Read24Fx(0x16000,ee?0x800:0,0x52,0x05BE,r?0x600:0);		//44KW, 2K, HV12
		}
		else if(EQ("30F6010")||EQ("30F6012")||EQ("30F6014")||EQ("30F6015")){
			Read24Fx(0x18000,ee?0x1000:0,0x52,0x05BE,r?0x600:0);	//49KW, 4K, HV12
		}
		else{
			PrintMessage(strings[S_nodev_r]); //"Dispositivo non supportato in lettura\r\n");
		}
	}
//-------------ATMEL---------------------------------------------------------
	else if(!strncmp(dev,"AT",2)){
		if(EQ("AT90S1200")){
			ReadAT(0x400,ee?0x40:0,0);							//1K, 64
		}
		else if(EQ("AT90S2313")){
			ReadAT(0x800,ee?0x80:0,0);							//2K, 128
		}
		else if(EQ("ATtiny2313")){
			ReadAT(0x800,ee?0x80:0,LOCK+FUSE+FUSE_H+FUSE_X+CAL+SLOW);//2K, 128
		}
		else if(EQ("AT90S8515")||EQ("AT90S8535")){
			ReadAT(0x2000,ee?0x100:0,0);						//8K, 256
		}
		else if(EQ("ATmega8")||EQ("ATmega8A")||EQ("ATmega8515")||EQ("ATmega8535")){
			ReadAT(0x2000,ee?0x200:0,LOCK+FUSE+FUSE_H+CAL);		//8K, 512
		}
		else if(EQ("ATmega16")||EQ("ATmega16A")){
			ReadAT(0x4000,ee?0x200:0,LOCK+FUSE+FUSE_H+CAL);		//16K, 512
		}
		else if(EQ("ATmega32")||EQ("ATmega32A")){
			ReadAT(0x8000,ee?0x400:0,LOCK+FUSE+FUSE_H+CAL);		//32K, 1K
		}
		else if(EQ("ATmega64")||EQ("ATmega64A")){
			ReadAT(0x10000,ee?0x800:0,LOCK+FUSE+FUSE_H+FUSE_X+CAL);	//64K, 2K
		}
		else{
			PrintMessage(strings[S_nodev_r]); //"Dispositivo non supportato in lettura\r\n");
		}
	}
//-------------I2C---------------------------------------------------------
	else if(!strncmp(dev,"24",2)||!strncmp(dev,"25",2)||!strncmp(dev,"93",2)){
		if(EQ("2400")){
			ReadI2C(0x10,0);						//16, 1B addr.
		}
		else if(EQ("2401")){
			ReadI2C(0x80,0);						//128, 1B addr.
		}
		else if(EQ("2402")){
			ReadI2C(0x100,0);						//256, 1B addr.
		}
		else if(EQ("2404")){
			ReadI2C(0x200,0);						//512, 1B addr.
		}
		else if(EQ("2408")){
			ReadI2C(0x400,0);						//1K, 1B addr.
		}
		else if(EQ("2416")){
			ReadI2C(0x800,0);						//2K, 1B addr.
		}
		else if(EQ("2432")){
			ReadI2C(0x1000,1);						//4K, 2B addr.
		}
		else if(EQ("2464")){
			ReadI2C(0x2000,1);						//8K, 2B addr.
		}
		else if(EQ("24128")){
			ReadI2C(0x4000,1);						//16K, 2B addr.
		}
		else if(EQ("24256")){
			ReadI2C(0x8000,1);						//32K, 2B addr.
		}
		else if(EQ("24512")){
			ReadI2C(0x10000,1);					//64K, 2B addr.
		}
		else if(EQ("241024")){
			ReadI2C(0x20000,0x201);				//128K, 2B addr.
		}
		else if(EQ("241025")){
			ReadI2C(0x20000,0x841);				//128K, 2B addr.
		}
//-------------Microwire EEPROM---------------------------------------------------------
		else if(EQ("93S46")||EQ("93x46")){
			Read93x(0x80,6,0);						//128, 6b addr
		}
		else if(EQ("93x46A")){
			Read93x(0x80,7,1);						//128, 6b addr x8
		}
		else if(EQ("93S56")||EQ("93x56")){
			Read93x(0x100,8,0);						//256, 8b addr
		}
		else if(EQ("93x56A")){
			Read93x(0x100,9,1);						//256, 8b addr x8
		}
		else if(EQ("93S66")||EQ("93x66")){
			Read93x(0x200,8,0);						//512, 8b addr
		}
		else if(EQ("93x66A")){
			Read93x(0x200,9,1);						//512, 8b addr x8
		}
		else if(EQ("93x76")){
			Read93x(0x400,10,0);						//1k, 10b addr
		}
		else if(EQ("93x76A")){
			Read93x(0x400,11,1);						//1k, 10b addr x8
		}
		else if(EQ("93x86")){
			Read93x(0x800,10,0);						//2k, 10b addr
		}
		else if(EQ("93x86A")){
			Read93x(0x800,11,1);						//2k, 10b addr x8
		}
//-------------SPI---------------------------------------------------------
		else if(EQ("25010")){
			Read25xx(0x80);							//128
		}
		else if(EQ("25020")){
			Read25xx(0x100);						//256
		}
		else if(EQ("25040")){
			Read25xx(0x200);						//512
		}
		else if(EQ("25080")){
			Read25xx(0x400);						//1K
		}
		else if(EQ("25160")){
			Read25xx(0x800);						//2K
		}
		else if(EQ("25320")){
			Read25xx(0x1000);						//4K
		}
		else if(EQ("25640")){
			Read25xx(0x2000);						//8K
		}
		else if(EQ("25128")){
			Read25xx(0x4000);						//16K
		}
		else if(EQ("25256")){
			Read25xx(0x8000);						//32K
		}
		else if(EQ("25512")){
			Read25xx(0x10000);						//64K
		}
		else if(EQ("251024")){
			Read25xx(0x20000);						//128K
		}
		else{
			PrintMessage(strings[S_nodev_r]); //"Dispositivo non supportato in lettura\r\n");
		}
	}
//-------------Unsupported device---------------------------------------------------------
	else{
		PrintMessage(strings[S_nodev_r]); //"Dispositivo non supportato in lettura\r\n");
	}
}

#define CS 8
#define HLD 16
#define write()	Result=WriteFile(WriteHandle,bufferU,DIMBUF,&BytesWritten,NULL);
#define read()	Result = ReadFile(ReadHandle,bufferI,DIMBUF,&NumberOfBytesRead,(LPOVERLAPPED) &HIDOverlapped);\
				Result = WaitForSingleObject(hEventObject,10);\
				ResetEvent(hEventObject);\
				if(Result!=WAIT_OBJECT_0){\
					PrintMessage(strings[S_comTimeout]);	/*"Timeout comunicazione\r\n"*/\
				}
//					return;

void COpenProgDlg::OnI2cspiR()		// I2C/SPI receive
{
	DWORD BytesWritten=0;
	ULONG Result;
	int j=1;
	int nbyte=m_I2CSPIPage.GetDlgItemInt(IDC_NUMB);
	if(nbyte<0) nbyte=0;
	if(nbyte>60) nbyte=60;
	int mode=0;
	CButton* b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_I2C16B);
	if(b->GetCheck()) mode=1;	//I2C mode
	b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_SPI00);
	if(b->GetCheck()) mode=2;	//SPI mode 00
	b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_SPI01);
	if(b->GetCheck()) mode=3;	//SPI mode 01
	b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_SPI10);
	if(b->GetCheck()) mode=4;	//SPI mode 10
	b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_SPI11);
	if(b->GetCheck()) mode=5;	//SPI mode 11
	b=(CButton*)m_OpzioniPage.GetDlgItem(IDC_REGISTRO);
	int registro=b->GetCheck();
	CString str,t;
	m_I2CSPIPage.GetDlgItemText(IDC_STRI,str);
	char* tok;
	BYTE tmpbuf[128];
	int i=0;
	for(tok=strtok(str.GetBuffer(512)," ");tok&&i<128;tok=strtok(NULL," ")){
		if(sscanf(tok,"%x",&tmpbuf[i])) i++;
	}
	for(;i<128;i++) tmpbuf[i]=0;
	if(MyDeviceDetected==FALSE) return;
	if (ReadHandle == INVALID_HANDLE_VALUE){
		m_I2CSPIPage.SetDlgItemText(IDC_STRU,strings[S_InvHandle]);	//"Handle invalido\r\n"
		return;
	}
	CancelIo(ReadHandle);
	if(registro){
		OpenLogFile();	//"Log.txt"
		str.Format("I2C-SPI receive\tmode=%d\n",mode);
		WriteLog(str);
	}
	bufferU[0]=0;
	bufferU[j++]=VREG_DIS;		//Disable HV reg
	bufferU[j++]=EN_VPP_VCC;	//VDD
	bufferU[j++]=0x1;
	if(mode<2){					//I2C mode
		bufferU[j++]=I2C_INIT;
		bufferU[j++]=0;
	}
	else{						//SPI mode
		bufferU[j++]=EXT_PORT;	//CS=1
		bufferU[j++]=CS;
		bufferU[j++]=0;
		bufferU[j++]=EXT_PORT;	//CS=0
		bufferU[j++]=0;
		bufferU[j++]=0;
		bufferU[j++]=SPI_INIT;
		bufferU[j++]=mode-2;
	}
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(1);
	read();
	if(registro)WriteLogIO();
	j=1;
	if(mode==0){					//I2C read
		bufferU[j++]=I2C_READ;
		bufferU[j++]=nbyte>(DIMBUF-4)?DIMBUF-4:nbyte;
		bufferU[j++]=tmpbuf[0];		//Control byte
		bufferU[j++]=tmpbuf[1];		//Address;
	}
	else if(mode==1){				//I2C read 16bit
		bufferU[j++]=I2C_READ2;
		bufferU[j++]=nbyte>(DIMBUF-4)?DIMBUF-4:nbyte;
		bufferU[j++]=tmpbuf[0];		//Control byte
		bufferU[j++]=tmpbuf[1];		//Address H;
		bufferU[j++]=tmpbuf[2];		//Address L;
	}
	else if(mode>=2){					//SPI read
		bufferU[j++]=SPI_READ;
		bufferU[j++]=nbyte>(DIMBUF-5)?DIMBUF-5:nbyte;
		bufferU[j++]=EXT_PORT;		//CS=1
		bufferU[j++]=CS;
		bufferU[j++]=0;
	}
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(10);
	read();
	if(registro){
		WriteLogIO();
		CloseLogFile();
	}
	if(bufferI[1]==I2C_READ||bufferI[1]==I2C_READ2||bufferI[1]==SPI_READ){
		if(bufferI[2]==0xFD){
			m_I2CSPIPage.SetDlgItemText(IDC_STRU,strings[S_I2CAckErr]); //"Errore di acknowledge I2C"
		}
		else if(bufferI[2]>0xFA){
			m_I2CSPIPage.SetDlgItemText(IDC_STRU,strings[S_InsErr]); //"Istruzione sconosciuta"
		}
		else{
			str.Empty();
			if(mode==0)	str.Format("> %02X %02X\r\n",bufferU[3],bufferU[4]);
			if(mode==1)	str.Format("> %02X %02X %02X\r\n",bufferU[3],bufferU[4],bufferU[5]);
			str+="< ";
			for(UINT i=0;i<bufferI[2];i++){
				t.Format("%02X ",(BYTE)bufferI[i+3]);
				str+=t;
				if(i&&i%16==15){
					str+="\r\n";
				}
			}
			m_I2CSPIPage.SetDlgItemText(IDC_STRU,str);
		}
	}

}

void COpenProgDlg::OnI2cspiS() // I2C/SPI send
{
	DWORD BytesWritten=0;
	ULONG Result;
	int j=1;
	int nbyte=m_I2CSPIPage.GetDlgItemInt(IDC_NUMB);
	if(nbyte<0) nbyte=0;
	if(nbyte>57) nbyte=57;
	int mode=0;
	CButton* b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_I2C16B);
	if(b->GetCheck()) mode=1;	//I2C mode
	b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_SPI00);
	if(b->GetCheck()) mode=2;	//SPI mode 00
	b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_SPI01);
	if(b->GetCheck()) mode=3;	//SPI mode 01
	b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_SPI10);
	if(b->GetCheck()) mode=4;	//SPI mode 10
	b=(CButton*)m_I2CSPIPage.GetDlgItem(IDC_SPI11);
	if(b->GetCheck()) mode=5;	//SPI mode 11
	b=(CButton*)m_OpzioniPage.GetDlgItem(IDC_REGISTRO);
	int registro=b->GetCheck();
	CString str,t;
	m_I2CSPIPage.GetDlgItemText(IDC_STRI,str);
	char* tok;
	BYTE tmpbuf[128];
	int i=0;
	for(tok=strtok(str.GetBuffer(512)," ");tok&&i<128;tok=strtok(NULL," ")){
		if(sscanf(tok,"%x",&tmpbuf[i])) i++;
	}
	for(;i<128;i++) tmpbuf[i]=0;
	if(MyDeviceDetected==FALSE) return;
	if (ReadHandle == INVALID_HANDLE_VALUE){
		m_I2CSPIPage.SetDlgItemText(IDC_STRU,strings[S_InvHandle]);	//"Handle invalido\r\n"
		return;
	}
	CancelIo(ReadHandle);
	if(registro){
		OpenLogFile();	//"Log.txt"
		str.Format("I2C-SPI send\tmode=%d\n",mode);
		WriteLog(str);
	}
	bufferU[0]=0;
	bufferU[j++]=VREG_DIS;		//Disable HV reg
	bufferU[j++]=EN_VPP_VCC;	//VDD
	bufferU[j++]=0x1;
	if(mode<2){					//I2C mode
		bufferU[j++]=I2C_INIT;
		bufferU[j++]=0;
	}
	else{						//SPI mode
		bufferU[j++]=EXT_PORT;	//CS=1
		bufferU[j++]=CS;
		bufferU[j++]=0;
		bufferU[j++]=EXT_PORT;	//CS=0
		bufferU[j++]=0;
		bufferU[j++]=0;
		bufferU[j++]=SPI_INIT;
		bufferU[j++]=mode-2;
	}
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(1);
	read();
	if(registro)WriteLogIO();
	j=1;
	if(mode==0){					//I2C write
		bufferU[j++]=I2C_WRITE;
		bufferU[j++]=nbyte>(DIMBUF-5)?DIMBUF-5:nbyte;
		bufferU[j++]=tmpbuf[0];		//Control byte
		bufferU[j++]=tmpbuf[1];		//Address
		for(i=0;i<bufferU[2];i++) bufferU[j++]=tmpbuf[i+2];
	}
	else if(mode==1){				//I2C write 16bit
		bufferU[j++]=I2C_WRITE;
		bufferU[j++]=nbyte+1>(DIMBUF-5)?DIMBUF-5:nbyte+1;
		bufferU[j++]=tmpbuf[0];		//Control byte
		bufferU[j++]=tmpbuf[1];		//Address
		bufferU[j++]=tmpbuf[2];		//Address L
		for(i=0;i<bufferU[2]-1;i++) bufferU[j++]=tmpbuf[i+3];
	}
	if(mode==2){					//SPI write
		bufferU[j++]=SPI_WRITE;
		bufferU[j++]=nbyte>(DIMBUF-5)?DIMBUF-5:nbyte;
		for(i=0;i<bufferU[2];i++) bufferU[j++]=tmpbuf[i];
		bufferU[j++]=EXT_PORT;	//CS=1
		bufferU[j++]=CS;
		bufferU[j++]=0;
	}
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(20);
	read();
	if(registro){
		WriteLogIO();
		CloseLogFile();
	}
	if(bufferI[1]==I2C_WRITE||bufferI[1]==SPI_WRITE){
		if(bufferI[2]==0xFD){
			m_I2CSPIPage.SetDlgItemText(IDC_STRU,strings[S_I2CAckErr]); //"Errore di acknowledge I2C"
		}
		else if(bufferI[2]>0xFA){
			m_I2CSPIPage.SetDlgItemText(IDC_STRU,strings[S_InsErr]); //"Istruzione sconosciuta"
		}
		else{
			str="> ";
			int n=3;
			if(mode<2) n=5;
			for(i=3;i<bufferU[2]+n;i++){
				t.Format("%02X ",(BYTE)bufferU[i]);
				str+=t;
				if(i&&i%16==15){
					str+="\r\n";
				}
			}
			m_I2CSPIPage.SetDlgItemText(IDC_STRU,str);
		}
	}
	else m_I2CSPIPage.SetDlgItemText(IDC_STRU,strings[S_ComErr]);	//"Errore di comunicazione\r\n"
}

void COpenProgDlg::PrintMessage(LPCTSTR s)
{
	dati+=s;
	if(dati.GetLength()>100000) dati=dati.Right(100000);
	CEdit* e=(CEdit*)m_DatiPage.GetDlgItem(IDC_DATI);
	e->SetWindowText(dati);
	e->LineScroll(5000);
}

void COpenProgDlg::DisplayEE(){
	CString str,aux;
	int sizeEE=memEE.GetSize();
	char s[256],t[256],v[256];
	int valid=0,empty=1;
	int i,j;
	s[0]=0;
	v[0]=0;
	PrintMessage(strings[S_EEMem]);	//"\r\nmemoria EEPROM:\r\n"
	for(i=0;i<sizeEE;i+=COL){
		valid=0;
		for(j=i;j<i+COL&&j<sizeEE;j++){
			sprintf(t,"%02X ",memEE[j]);
			strcat(s,t);
			sprintf(t,"%c",isprint(memEE[j])?memEE[j]:'.');
			strcat(v,t);
			if(memEE[j]<0xff) valid=1;
		}
		if(valid){
			sprintf(t,"%04X: %s %s\r\n",i,s,v);
			aux+=t;
			empty=0;
		}
		s[0]=0;
		v[0]=0;
	}
	if(empty) PrintMessage(strings[S_Empty]);	//empty
	else PrintMessage(aux);
}

int COpenProgDlg::StartHVReg(double V)
{
	DWORD BytesWritten=0;
	ULONG Result;
	int j=1,z;
	int vreg=(int)(V*10.0);
	bufferU[0]=0;
	if(MyDeviceDetected==FALSE) return 0;
	DWORD t0,t;
	CString str;
	CancelIo(ReadHandle);
	if(V==-1){
		bufferU[j++]=VREG_DIS;			//disable HV regulator
		bufferU[j++]=FLUSH;
		write();
		msDelay(40);
		read();
		return -1;
	}
	t=t0=GetTickCount();
	bufferU[j++]=VREG_EN;			//enable HV regulator
	bufferU[j++]=SET_VPP;
	bufferU[j++]=vreg<80?vreg-8:vreg;		//set VPP, compensate for offset at low voltage
	bufferU[j++]=SET_PARAMETER;
	bufferU[j++]=SET_T3;
	bufferU[j++]=2000>>8;
	bufferU[j++]=2000&0xff;
	bufferU[j++]=WAIT_T3;
	bufferU[j++]=READ_ADC;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(20);
	read();
	for(z=1;z<DIMBUF-2&&bufferI[z]!=READ_ADC;z++);
	int v=(bufferI[z+1]<<8)+bufferI[z+2];
	if(v==0){
		PrintMessage(strings[S_lowUsbV]);	//"Tensione USB troppo bassa (VUSB<4.5V)\r\n"
		return 0;
	}
	for(;(v<(vreg/10.0-0.5)*G||v>(vreg/10.0+0.5)*G)&&t<t0+1500;t=GetTickCount()){
		j=1;
		bufferU[j++]=WAIT_T3;
		bufferU[j++]=READ_ADC;
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(20);
		read();
		for(z=1;z<DIMBUF-2&&bufferI[z]!=READ_ADC;z++);
		v=(bufferI[z+1]<<8)+bufferI[z+2];
//		printf("v=%d=%fV\n",v,v/G);
	}
	if(v>(vreg/10.0+0.7)*G){
		PrintMessage(strings[S_HiVPP]);	//"Attenzione: tensione regolatore troppo alta\r\n\r\n"
		StatusBar.SetWindowText(strings[S_HiVPP]);
		return 0;
	}
	else if(v<(vreg/10.0-0.7)*G){
		PrintMessage(strings[S_LowVPP]);	//"Attenzione: tensione regolatore troppo bassa\r\n\r\n"
		StatusBar.SetWindowText(strings[S_LowVPP]);
		return 0;
	}
	else if(v==0){
		PrintMessage(strings[S_lowUsbV]);	//"Tensione USB troppo bassa (VUSB<4.5V)\r\n"
		StatusBar.SetWindowText(strings[S_lowUsbV]);
		return 0;
	}
	else{
		PrintMessage2(strings[S_reg],t-t0,v/G);	//"Regolatore avviato e funzionante dopo T=%d ms VPP=%.1f\r\n\r\n"
		hvreg=1;
		CancelIo(ReadHandle);
		return vreg;
	}
}

void COpenProgDlg::ProgID()
{
	DWORD BytesWritten=0;
	ULONG Result;
	CString str;
	int j=1;
	bufferU[0]=0;
	if(MyDeviceDetected==FALSE) return;
	CancelIo(ReadHandle);
	bufferU[j++]=PROG_RST;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	str.Format(strings[S_progver],bufferI[2],bufferI[3],bufferI[4]); //"Programmatore versione %d.%d.%d\r\n"
	PrintMessage(str);
	FWVersion=(bufferI[2]<<16)+(bufferI[3]<<8)+bufferI[4];
	str.Format(strings[S_progid],bufferI[5],bufferI[6],bufferI[7]);	//"ID: %d.%d.%d\r\n"
	PrintMessage(str);
	if(bufferI[7]==1) str.Format(" (18F2550)\r\n\r\n");
	else if(bufferI[7]==2) str.Format(" (18F2450)\r\n\r\n");
	else str.Format(" (?)\r\n\r\n");
	PrintMessage(str);
	CancelIo(ReadHandle);
}

int COpenProgDlg::CheckV33Regulator()
{
	DWORD BytesWritten=0;
	ULONG Result;
	int i,j=1;
	bufferU[j++]=WRITE_RAM;
	bufferU[j++]=0x0F;
	bufferU[j++]=0x93;
	bufferU[j++]=0xFE;	//B0 = output
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=0x01;	//B0=1
	bufferU[j++]=0;
	bufferU[j++]=READ_RAM;
	bufferU[j++]=0x0F;
	bufferU[j++]=0x81;	//Check if B1=1
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=0x00;	//B0=0
	bufferU[j++]=0;
	bufferU[j++]=READ_RAM;
	bufferU[j++]=0x0F;
	bufferU[j++]=0x81;	//Check if B1=0
	bufferU[j++]=WRITE_RAM;
	bufferU[j++]=0x0F;
	bufferU[j++]=0x93;
	bufferU[j++]=0xFF;	//BX = input
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	for(j=1;j<DIMBUF-3&&bufferI[j]!=READ_RAM;j++);
	i=bufferI[j+3]&0x2;		//B1 should be high
	for(j+=3;j<DIMBUF-3&&bufferI[j]!=READ_RAM;j++);
	return (i+bufferI[j+3]&0x2)==2?1:0;
}


void COpenProgDlg::OnTestHw()
{
	DWORD BytesWritten=0;
	ULONG Result;
	int j=1;
	bufferU[0]=0;
	//CString str;
	if(MyDeviceDetected==FALSE) return;
	if(AfxMessageBox(strings[I_TestHW],MB_OKCANCEL)==IDOK){			//"Test hardware ..."
		StartHVReg(13);
		bufferU[j++]=SET_CK_D;
		bufferU[j++]=0x0;
		bufferU[j++]=EN_VPP_VCC;		//VDD+VPP
		bufferU[j++]=0x5;
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(20);
		read();
		AfxMessageBox("VDD=5V, VPP=13V, D=0V, CK=0V, PGM=0V");
		j=1;
		bufferU[j++]=SET_CK_D;
		bufferU[j++]=0x15;
		bufferU[j++]=EN_VPP_VCC;
		bufferU[j++]=0x1;			//VDD
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(20);
		read();
		AfxMessageBox("VDD=5V, VPP=0V, D=5V, CK=5V, PGM=5V");
		j=1;
		bufferU[j++]=SET_CK_D;
		bufferU[j++]=0x1;
		bufferU[j++]=EN_VPP_VCC;
		bufferU[j++]=0x4;			//VPP
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(20);
		read();
		AfxMessageBox("VDD=0V, VPP=13V, D=5V, CK=0V, PGM=0V");
		j=1;
		bufferU[j++]=SET_CK_D;
		bufferU[j++]=0x4;
		bufferU[j++]=EN_VPP_VCC;
		bufferU[j++]=0x0;
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(20);
		read();
		AfxMessageBox("VDD=0V, VPP=0V, D=0V, CK=5V, PGM=0V");
		j=1;
		bufferU[j++]=SET_CK_D;
		bufferU[j++]=0x0;
		bufferU[j++]=EN_VPP_VCC;
		bufferU[j++]=0x0;			//VPP
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(20);
		read();
	}
}

void COpenProgDlg::msDelay(double delay)
{
	Sleep((long)ceil(delay)>MinRit?(long)ceil(delay):MinRit);
}

void COpenProgDlg::OnConnect()
{
	FindDevice();
	ProgID();
}

int COpenProgDlg::FindDevice(){
	typedef struct _HIDD_ATTRIBUTES {
	    ULONG   Size;
	    USHORT  VendorID;
	    USHORT  ProductID;
	    USHORT  VersionNumber;
	} HIDD_ATTRIBUTES, *PHIDD_ATTRIBUTES;

	typedef void (__stdcall*GETHIDGUID) (OUT LPGUID HidGuid);
	typedef BOOLEAN (__stdcall*GETATTRIBUTES)(IN HANDLE HidDeviceObject,OUT PHIDD_ATTRIBUTES Attributes);
	typedef BOOLEAN (__stdcall*SETNUMINPUTBUFFERS)(IN  HANDLE HidDeviceObject,OUT ULONG  NumberBuffers);
	typedef BOOLEAN (__stdcall*GETNUMINPUTBUFFERS)(IN  HANDLE HidDeviceObject,OUT PULONG  NumberBuffers);
	typedef BOOLEAN (__stdcall*GETFEATURE) (IN  HANDLE HidDeviceObject, OUT PVOID ReportBuffer, IN ULONG ReportBufferLength);
	typedef BOOLEAN (__stdcall*SETFEATURE) (IN  HANDLE HidDeviceObject, IN PVOID ReportBuffer, IN ULONG ReportBufferLength);
	typedef BOOLEAN (__stdcall*GETREPORT) (IN  HANDLE HidDeviceObject, OUT PVOID ReportBuffer, IN ULONG ReportBufferLength);
	typedef BOOLEAN (__stdcall*SETREPORT) (IN  HANDLE HidDeviceObject, IN PVOID ReportBuffer, IN ULONG ReportBufferLength);
	typedef BOOLEAN (__stdcall*GETMANUFACTURERSTRING) (IN  HANDLE HidDeviceObject, OUT PVOID ReportBuffer, IN ULONG ReportBufferLength);
	typedef BOOLEAN (__stdcall*GETPRODUCTSTRING) (IN  HANDLE HidDeviceObject, OUT PVOID ReportBuffer, IN ULONG ReportBufferLength);
	typedef BOOLEAN (__stdcall*GETINDEXEDSTRING) (IN  HANDLE HidDeviceObject, IN ULONG  StringIndex, OUT PVOID ReportBuffer, IN ULONG ReportBufferLength);
	HIDD_ATTRIBUTES Attributes;
	SP_DEVICE_INTERFACE_DATA devInfoData;
	bool LastDevice = FALSE;
	int MemberIndex = 0;
	LONG Result;
//	char UsageDescription[256];

	Length=0;
	detailData=NULL;
	DeviceHandle=NULL;

	HMODULE hHID=0;
	GETHIDGUID HidD_GetHidGuid=0;
	GETATTRIBUTES HidD_GetAttributes=0;
	SETNUMINPUTBUFFERS HidD_SetNumInputBuffers=0;
	GETNUMINPUTBUFFERS HidD_GetNumInputBuffers=0;
	GETFEATURE HidD_GetFeature=0;
	SETFEATURE HidD_SetFeature=0;
	GETREPORT HidD_GetInputReport=0;
	SETREPORT HidD_SetOutputReport=0;
	GETMANUFACTURERSTRING HidD_GetManufacturerString=0;
	GETPRODUCTSTRING HidD_GetProductString=0;
	hHID = LoadLibrary("hid.dll");
	if(!hHID){
		MessageBox(strings[S_noDLL]);					//"no hid.dll"
		return 0;
	}
	HidD_GetHidGuid=(GETHIDGUID)GetProcAddress(hHID,"HidD_GetHidGuid");
	HidD_GetAttributes=(GETATTRIBUTES)GetProcAddress(hHID,"HidD_GetAttributes");
	HidD_SetNumInputBuffers=(SETNUMINPUTBUFFERS)GetProcAddress(hHID,"HidD_SetNumInputBuffers");
	HidD_GetNumInputBuffers=(GETNUMINPUTBUFFERS)GetProcAddress(hHID,"HidD_GetNumInputBuffers");
	HidD_GetFeature=(GETFEATURE)GetProcAddress(hHID,"HidD_GetFeature");
	HidD_SetFeature=(SETFEATURE)GetProcAddress(hHID,"HidD_SetFeature");
	HidD_GetInputReport=(GETREPORT)GetProcAddress(hHID,"HidD_GetInputReport");
	HidD_SetOutputReport=(SETREPORT)GetProcAddress(hHID,"HidD_SetOutputReport");
	HidD_GetManufacturerString=(GETMANUFACTURERSTRING)GetProcAddress(hHID,"HidD_GetManufacturerString");
	HidD_GetProductString=(GETPRODUCTSTRING)GetProcAddress(hHID,"HidD_GetProductString");
	if(HidD_GetHidGuid==NULL\
		||HidD_GetAttributes==NULL\
		||HidD_GetFeature==NULL\
		||HidD_SetFeature==NULL\
		||HidD_GetInputReport==NULL\
		||HidD_SetOutputReport==NULL\
		||HidD_GetManufacturerString==NULL\
		||HidD_GetProductString==NULL\
		||HidD_SetNumInputBuffers==NULL\
		||HidD_GetNumInputBuffers==NULL) return 0;


	HMODULE hSAPI=0;
	hSAPI = LoadLibrary("setupapi.dll");
	if(!hSAPI){
		MessageBox("Can't find setupapi.dll");
		return 0;
	}
	typedef HDEVINFO (WINAPI* SETUPDIGETCLASSDEVS) (CONST GUID*,PCSTR,HWND,DWORD);
	typedef BOOL (WINAPI* SETUPDIENUMDEVICEINTERFACES) (HDEVINFO,PSP_DEVINFO_DATA,CONST GUID*,DWORD,PSP_DEVICE_INTERFACE_DATA);
	typedef BOOL (WINAPI* SETUPDIGETDEVICEINTERFACEDETAIL) (HDEVINFO,PSP_DEVICE_INTERFACE_DATA,PSP_DEVICE_INTERFACE_DETAIL_DATA_A,DWORD,PDWORD,PSP_DEVINFO_DATA);
	typedef BOOL (WINAPI* SETUPDIDESTROYDEVICEINFOLIST) (HDEVINFO);
	SETUPDIGETCLASSDEVS SetupDiGetClassDevsA=0;
	SETUPDIENUMDEVICEINTERFACES SetupDiEnumDeviceInterfaces=0;
	SETUPDIGETDEVICEINTERFACEDETAIL SetupDiGetDeviceInterfaceDetailA=0;
	SETUPDIDESTROYDEVICEINFOLIST SetupDiDestroyDeviceInfoList=0;
	SetupDiGetClassDevsA=(SETUPDIGETCLASSDEVS) GetProcAddress(hSAPI,"SetupDiGetClassDevsA");
	SetupDiEnumDeviceInterfaces=(SETUPDIENUMDEVICEINTERFACES) GetProcAddress(hSAPI,"SetupDiEnumDeviceInterfaces");
	SetupDiGetDeviceInterfaceDetailA=(SETUPDIGETDEVICEINTERFACEDETAIL) GetProcAddress(hSAPI,"SetupDiGetDeviceInterfaceDetailA");
	SetupDiDestroyDeviceInfoList=(SETUPDIDESTROYDEVICEINFOLIST) GetProcAddress(hSAPI,"SetupDiDestroyDeviceInfoList");
	if(SetupDiGetClassDevsA==NULL\
		||SetupDiEnumDeviceInterfaces==NULL\
		||SetupDiDestroyDeviceInfoList==NULL\
		||SetupDiGetDeviceInterfaceDetailA==NULL) return 0;
	/*
	The following code is adapted from Usbhidio_vc6 application example by Jan Axelson
	for more information see see http://www.lvr.com/hidpage.htm
	*/
	/*
	API function: HidD_GetHidGuid
	Get the GUID for all system HIDs.
	Returns: the GUID in HidGuid.
	*/
	HidD_GetHidGuid(&HidGuid);

	/*
	API function: SetupDiGetClassDevs
	Returns: a handle to a device information set for all installed devices.
	Requires: the GUID returned by GetHidGuid.
	*/
	hDevInfo=SetupDiGetClassDevs(&HidGuid,NULL,NULL,DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
	devInfoData.cbSize = sizeof(devInfoData);

	//Step through the available devices looking for the one we want.
	//Quit on detecting the desired device or checking all available devices without success.
	MemberIndex = 0;
	LastDevice = FALSE;
	do
	{
		/*
		API function: SetupDiEnumDeviceInterfaces
		On return, MyDeviceInterfaceData contains the handle to a
		SP_DEVICE_INTERFACE_DATA structure for a detected device.
		Requires:
		The DeviceInfoSet returned in SetupDiGetClassDevs.
		The HidGuid returned in GetHidGuid.
		An index to specify a device.
		*/
		Result=SetupDiEnumDeviceInterfaces (hDevInfo, 0, &HidGuid, MemberIndex, &devInfoData);
		if (Result != 0)
		{
			//A device has been detected, so get more information about it.
			/*
			API function: SetupDiGetDeviceInterfaceDetail
			Returns: an SP_DEVICE_INTERFACE_DETAIL_DATA structure
			containing information about a device.
			To retrieve the information, call this function twice.
			The first time returns the size of the structure in Length.
			The second time returns a pointer to the data in DeviceInfoSet.
			Requires:
			A DeviceInfoSet returned by SetupDiGetClassDevs
			The SP_DEVICE_INTERFACE_DATA structure returned by SetupDiEnumDeviceInterfaces.

			The final parameter is an optional pointer to an SP_DEV_INFO_DATA structure.
			This application doesn't retrieve or use the structure.
			If retrieving the structure, set
			MyDeviceInfoData.cbSize = length of MyDeviceInfoData.
			and pass the structure's address.
			*/
			//Get the Length value.
			//The call will return with a "buffer too small" error which can be ignored.
			Result = SetupDiGetDeviceInterfaceDetail(hDevInfo, &devInfoData, NULL, 0, &Length, NULL);

			//Allocate memory for the hDevInfo structure, using the returned Length.
			detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);

			//Set cbSize in the detailData structure.
			detailData -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			//Call the function again, this time passing it the returned buffer size.
			Result = SetupDiGetDeviceInterfaceDetail(hDevInfo, &devInfoData, detailData, Length,&Required, NULL);

			// Open a handle to the device.
			// To enable retrieving information about a system mouse or keyboard,
			// don't request Read or Write access for this handle.
			/*
			API function: CreateFile
			Returns: a handle that enables reading and writing to the device.
			Requires:
			The DevicePath in the detailData structure
			returned by SetupDiGetDeviceInterfaceDetail.
			*/
			DeviceHandle=CreateFile(detailData->DevicePath,
				0, FILE_SHARE_READ|FILE_SHARE_WRITE,
				(LPSECURITY_ATTRIBUTES)NULL,OPEN_EXISTING, 0, NULL);

			/*
			API function: HidD_GetAttributes
			Requests information from the device.
			Requires: the handle returned by CreateFile.
			Returns: a HIDD_ATTRIBUTES structure containing
			the Vendor ID, Product ID, and Product Version Number.
			Use this information to decide if the detected device is
			the one we're looking for.
			*/

			//Set the Size to the number of bytes in the structure.
			Attributes.Size = sizeof(Attributes);
			Result = HidD_GetAttributes(DeviceHandle,&Attributes);

			//Is it the desired device?
			MyDeviceDetected = FALSE;
			CString a;
			int vid=0,pid=0;
			m_OpzioniPage.GetDlgItemText(IDC_VID,a);
			sscanf(a,"0x%X",&vid);
			m_OpzioniPage.GetDlgItemText(IDC_PID,a);
			sscanf(a,"0x%X",&pid);
			if (Attributes.VendorID == vid)
			{
				if (Attributes.ProductID == pid)
				{
					//Both the Vendor ID and Product ID match.
					MyDeviceDetected = TRUE;
					MyDevicePathName = detailData->DevicePath;
					a.Format(strings[S_dev_det],vid,pid,MyDevicePathName);	//"Device detected: vid=0x%04X pid=0x%04X\r\nPath: %s\r\n"
					PrintMessage(a);

					// Get a handle for writing Output reports.
					WriteHandle=CreateFile(detailData->DevicePath,
						GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
						(LPSECURITY_ATTRIBUTES)NULL,OPEN_EXISTING,0,NULL);

					//Get a handle to the device for the overlapped ReadFiles.
					ReadHandle=CreateFile(detailData->DevicePath,
						GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,(LPSECURITY_ATTRIBUTES)NULL,
						OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

					if (hEventObject) CloseHandle(hEventObject);
					hEventObject = CreateEvent(NULL,TRUE,TRUE,"");

					//Set the members of the overlapped structure.
					HIDOverlapped.hEvent = hEventObject;
					HIDOverlapped.Offset = 0;
					HIDOverlapped.OffsetHigh = 0;
					Result=HidD_SetNumInputBuffers(DeviceHandle,64);
				}
				else
					//The Product ID doesn't match.
					CloseHandle(DeviceHandle);
			}
			else
				//The Vendor ID doesn't match.
				CloseHandle(DeviceHandle);
		//Free the memory used by the detailData structure (no longer needed).
		free(detailData);
		}
		else
			//SetupDiEnumDeviceInterfaces returned 0, so there are no more devices to check.
			LastDevice=TRUE;
		//If we haven't found the device yet, and haven't tried every available device,
		//try the next one.
		MemberIndex = MemberIndex + 1;
	} //do
	while ((LastDevice == FALSE) && (MyDeviceDetected == FALSE));

	if (MyDeviceDetected == FALSE){
		PrintMessage(strings[S_noprog]);	//"Programmatore non rilevato\r\n"
		StatusBar.SetWindowText(strings[S_noprog]);
	}
	else{
		PrintMessage(strings[S_prog]);	//"Programmatore rilevato\r\n");
		StatusBar.SetWindowText(strings[S_prog]);
	}
	//Free the memory reserved for hDevInfo by SetupDiClassDevs.
	SetupDiDestroyDeviceInfoList(hDevInfo);
	hvreg=0;		//assume vreg not working
	return MyDeviceDetected?1:0;
}

void COpenProgDlg::OnWriteLangFile()
{
	CFileDialog dlg(FALSE,NULL,"languages.rc",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT);	//"File Hex8 (*.hex)|*.hex|File binari (*.bin)|*.bin|Tutti i file (*.*)|*.*||"
	if (dlg.DoModal()==IDOK){
		CFile f;
		if (f.Open(dlg.GetPathName(),CFile::modeWrite|CFile::modeCreate)){
			f.Write("[sample]\n",9);
			CString c;
			for(int i=0;i<DIM;i++){
				f.Write(strings_ID[i],strlen(strings_ID[i]));
			}
			f.Close();
		}
	}
}

// including code for various devices
// if anyone knows a better way to do it please tell me

#include "progP12.cpp"
#include "progP16.cpp"
#include "progP18.cpp"
#include "progP24.cpp"
#include "progEEPROM.cpp"
#include "progAVR.cpp"
#include "fileIO.cpp"


