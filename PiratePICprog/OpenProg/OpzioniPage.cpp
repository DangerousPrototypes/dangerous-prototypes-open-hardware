// OpzioniPage.cpp : implementation file
//

#include "stdafx.h"
#include "OpenProg.h"
#include "OpzioniPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OpzioniPage property page

IMPLEMENT_DYNCREATE(COpzioniPage, CPropertyPage)

COpzioniPage::COpzioniPage() : CPropertyPage(COpzioniPage::IDD)
{
	//{{AFX_DATA_INIT(COpzioniPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COpzioniPage::~COpzioniPage()
{
}

void COpzioniPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpzioniPage)
	DDX_Control(pDX, IDC_LANGUAGE, m_language);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpzioniPage, CPropertyPage)
	//{{AFX_MSG_MAP(COpzioniPage)
	ON_BN_CLICKED(IDC_CONNETTI, OnConnetti)
	ON_CBN_SELCHANGE(IDC_LANGUAGE, OnSelchangeLanguage)
	ON_BN_CLICKED(IDC_TESTHW, OnTesthw)
	ON_BN_CLICKED(IDC_WLANGFILE, OnWlangfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void COpzioniPage::OnConnetti() 
{
	SendMessage(WM_COMMAND, ID_OPZIONI_PROGRAMMATORE_CONNETTI, 0L);	
}


void COpzioniPage::OnSelchangeLanguage() 
{
	SendMessage(WM_COMMAND, ID_CAMBIA_LINGUA, 0L);		
}

void COpzioniPage::OnTesthw() 
{
	SendMessage(WM_COMMAND, ID_TEST_HW, 0L);		
}


void COpzioniPage::OnWlangfile() 
{
	SendMessage(WM_COMMAND, ID_WRITE_LANG_FILE, 0L);		
}
