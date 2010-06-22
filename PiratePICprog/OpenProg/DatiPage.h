#if !defined(AFX_DATIPAGE_H__354A1D32_1816_4385_A371_B10947D33BA1__INCLUDED_)
#define AFX_DATIPAGE_H__354A1D32_1816_4385_A371_B10947D33BA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DatiPage.h : header file
//

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDatiPage dialog

class CDatiPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDatiPage)

// Construction
public:
	CDatiPage();
	~CDatiPage();

// Dialog Data
	//{{AFX_DATA(CDatiPage)
	enum { IDD = IDD_DATI };
	CEdit	m_dati;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatiPage)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatiPage)
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATIPAGE_H__354A1D32_1816_4385_A371_B10947D33BA1__INCLUDED_)
