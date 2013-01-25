// PIC32UBL.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CPIC32UBLApp:
// See PIC32UBL.cpp for the implementation of this class
//

class CPIC32UBLApp : public CWinApp
{
public:
	CPIC32UBLApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPIC32UBLApp theApp;