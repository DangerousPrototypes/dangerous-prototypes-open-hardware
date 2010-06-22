// I2CSPIPage.cpp : implementation file
//

#include "stdafx.h"
#include "OpenProg.h"
#include "I2CSPIPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CI2CSPIPage property page

IMPLEMENT_DYNCREATE(CI2CSPIPage, CPropertyPage)

CI2CSPIPage::CI2CSPIPage() : CPropertyPage(CI2CSPIPage::IDD)
{
	//{{AFX_DATA_INIT(CI2CSPIPage)
	//}}AFX_DATA_INIT
}

CI2CSPIPage::~CI2CSPIPage()
{
}

void CI2CSPIPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CI2CSPIPage)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CI2CSPIPage, CPropertyPage)
	//{{AFX_MSG_MAP(CI2CSPIPage)
	ON_BN_CLICKED(IDC_REC, OnRead)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CI2CSPIPage message handlers

void CI2CSPIPage::OnRead() 
{
	SendMessage(WM_COMMAND, ID_I2CSPI_R, 0L);		
}

void CI2CSPIPage::OnSend() 
{
	SendMessage(WM_COMMAND, ID_I2CSPI_S, 0L);		
}
