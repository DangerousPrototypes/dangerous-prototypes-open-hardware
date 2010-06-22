#if !defined(AFX_OPZIONIPAGE_H__CB542BA1_E401_4791_842E_A7112BC121F5__INCLUDED_)
#define AFX_OPZIONIPAGE_H__CB542BA1_E401_4791_842E_A7112BC121F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpzioniPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OpzioniPage dialog

class COpzioniPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COpzioniPage)

// Construction
public:
	COpzioniPage();
	~COpzioniPage();

// Dialog Data
	//{{AFX_DATA(COpzioniPage)
	enum { IDD = IDD_OPZIONI };
	CComboBox	m_language;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COpzioniPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COpzioniPage)
	afx_msg void OnConnetti();
	afx_msg void OnSelchangeLanguage();
	afx_msg void OnTesthw();
	afx_msg void OnWlangfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPZIONIPAGE_H__CB542BA1_E401_4791_842E_A7112BC121F5__INCLUDED_)
