// DatiPage.cpp : implementation file
//

#include "stdafx.h"
#include "OpenProg.h"
#include "DatiPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatiPage property page

IMPLEMENT_DYNCREATE(CDatiPage, CPropertyPage)

CDatiPage::CDatiPage() : CPropertyPage(CDatiPage::IDD)
{
	//{{AFX_DATA_INIT(CDatiPage)
	//}}AFX_DATA_INIT
}

CDatiPage::~CDatiPage()
{
}

void CDatiPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatiPage)
	DDX_Control(pDX, IDC_DATI, m_dati);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDatiPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDatiPage)
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatiPage message handlers



BOOL CDatiPage::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::DestroyWindow();
}

void CDatiPage::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	m_dati.SetWindowText("");
	CPropertyPage::OnRButtonDblClk(nFlags, point);
}
