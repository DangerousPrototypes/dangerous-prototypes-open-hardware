#if !defined(AFX_DISPOSITIVOPAGE_H__A53E525C_6D85_4207_B49F_FA1D50EB9D30__INCLUDED_)
#define AFX_DISPOSITIVOPAGE_H__A53E525C_6D85_4207_B49F_FA1D50EB9D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DispositivoPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDispositivoPage dialog

class CDispositivoPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDispositivoPage)

// Construction
public:
	CDispositivoPage();
	~CDispositivoPage();

// Dialog Data
	//{{AFX_DATA(CDispositivoPage)
	enum { IDD = IDD_DISP };
	CComboBox	m_dispo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDispositivoPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDispositivoPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPOSITIVOPAGE_H__A53E525C_6D85_4207_B49F_FA1D50EB9D30__INCLUDED_)
