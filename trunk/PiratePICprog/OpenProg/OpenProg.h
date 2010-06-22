// OpenProg.h : main header file for the OPENPROG application
//

#if !defined(AFX_OPENPROG_H__C2F6CC5C_8FF6_4C82_82D6_8C8F49F5B14C__INCLUDED_)
#define AFX_OPENPROG_H__C2F6CC5C_8FF6_4C82_82D6_8C8F49F5B14C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COpenProgApp:
// See OpenProg.cpp for the implementation of this class
//

class COpenProgApp : public CWinApp
{
public:
	COpenProgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenProgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COpenProgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENPROG_H__C2F6CC5C_8FF6_4C82_82D6_8C8F49F5B14C__INCLUDED_)
