// OpenProgDlg.h : header file
//

#include "setupapi.h"
#include "hidsdi.h"

#if !defined(AFX_OPENPROGDLG_H__12487EFD_63E5_4629_8C6C_99B644EB1118__INCLUDED_)
#define AFX_OPENPROGDLG_H__12487EFD_63E5_4629_8C6C_99B644EB1118__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COpenProgDlg dialog

class COpenProgDlg : public CDialog
{
// Construction
public:
	void msDelay(double delay);
	void ChangeLanguage();
	void OnRead();
	void OnConnect();
	void OnFileSave();
	void OnFileOpen();
	void OnWrite();
	int  StartHVReg(double V);
	int  CheckV33Regulator();
	void ProgID();
	int  FindDevice();
	void PrintMessage(LPCTSTR s);
	void Read12F5xx(int dim,int dim2);
	void Read16Fxxx(int dim,int dim2,int dim3,int vdd);
	void Read16F1xxx(int dim,int dim2,int dim3,int options);
	void Read18Fx(int dim,int dim2,int options);
	void Read24Fx(int dim,int dim2,int options,int appIDaddr,int executiveArea);
	void ReadI2C(int dim,int addr);
	void ReadAT(int dim, int dim2,int options);
	void Read93x(int dim, int na,int options);
	void Read25xx(int dim);
	void Write12F5xx(int dim,int OscAddr);
	void Write12F6xx(int dim,int dim2);
	void Write12F61x(int dim);
	void Write16F8x(int dim,int dim2);
	void Write16F87x(int dim,int dim2);
	void Write16F87xA(int dim,int dim2,int seq);
	void Write16F81x(int dim,int dim2);
	void Write16F62x(int dim,int dim2);
	void Write12F62x(int dim,int dim2);
	void Write16F88x(int dim,int dim2);
	void Write16F7x(int dim,int vdd);
	void Write16F71x(int dim,int vdd);
	void Write16F1xxx(int dim,int dim2,int options);
	void Write18Fx(int dim,int dim2,int wbuf,int eraseW1,int eraseW2,int options);
	void Write24Fx(int dim,int dim2,int options,int appIDaddr,int rowSize, double wait);
	void WriteI2C(int dim,int addr,int page, float wait);
	void WriteAT(int dim, int dim2);
	void WriteATmega(int dim, int dim2,int page,int options);
	void Write93Sx(int dim, int na,int page, double wait);
	void Write93Cx(int dim,int na, int options);
	void Write25xx(int dim,int page,float wait);
	void OpenLogFile();
	void CloseLogFile();
	void WriteLog(CString str);
	void WriteLogIO();
	void PIC16_ID(int id);
	void PIC18_ID(int id);
	void PIC24_ID(int id);
	void AtmelID(BYTE id[3]);
	void CheckData(int a,int b, int addr,int &err);
	void DisplayEE();
	void SaveEE();
	void LoadEE();
	unsigned int htoi(const char *hex, int length);
	CToolBar			ToolBar;
	CStatusBarCtrl		StatusBar;
	CPropertySheet		m_dlgPropSheet;
	CDatiPage			m_DatiPage;
	COpzioniPage		m_OpzioniPage;
	CDispositivoPage	m_DispoPage;
	CI2CSPIPage			m_I2CSPIPage;
	UINT				*lpIDArray;
	CString argv[32];
	int argc;
	int FWVersion;
	unsigned char		bufferI[128];
	unsigned char		bufferU[128];
	char **strings;
	char **strings_ID;
	int MinRit,maxerr,hvreg;
	int saveLog,max_err,load_calibword,programID,load_osccal,ICDenable,ICDaddr;
	DWORD BytesWritten;
	ULONG Result;
	FILE* logfile;
	CString langs[32];
	CWordArray	dati_hex;
	CByteArray	memCODE;
	CByteArray	memEE;
	CByteArray	memID;
	CByteArray	memCONFIG;
	CString messaggi,dati;//,lang;
	PSP_DEVICE_INTERFACE_DETAIL_DATA detailData;
	HANDLE DeviceHandle;
	HANDLE hEventObject;
	HANDLE hDevInfo;
	GUID HidGuid;
	OVERLAPPED HIDOverlapped;
	ULONG Length;
	bool MyDeviceDetected; 
	CString MyDevicePathName;
	DWORD NumberOfBytesRead;
	HANDLE ReadHandle;
	ULONG Required;
	HANDLE WriteHandle;
	CString rfile;
	CString wfile;
	COpenProgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COpenProgDlg)
	enum { IDD = IDD_OPENPROG_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenProgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COpenProgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnI2cspiR();
	afx_msg void OnI2cspiS();
	afx_msg void OnTestHw();
	afx_msg void OnWriteLangFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENPROGDLG_H__12487EFD_63E5_4629_8C6C_99B644EB1118__INCLUDED_)



