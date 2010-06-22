#if !defined(AFX_I2CSPIPAGE_H__D32B4B52_56F6_4599_8984_F328ACC0E69F__INCLUDED_)
#define AFX_I2CSPIPAGE_H__D32B4B52_56F6_4599_8984_F328ACC0E69F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// I2CSPIPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CI2CSPIPage dialog

class CI2CSPIPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CI2CSPIPage)

// Construction
public:
	CI2CSPIPage();
	~CI2CSPIPage();

// Dialog Data
	//{{AFX_DATA(CI2CSPIPage)
	enum { IDD = IDD_I2C_SPI };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CI2CSPIPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CI2CSPIPage)
	afx_msg void OnRead();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_I2CSPIPAGE_H__D32B4B52_56F6_4599_8984_F328ACC0E69F__INCLUDED_)
