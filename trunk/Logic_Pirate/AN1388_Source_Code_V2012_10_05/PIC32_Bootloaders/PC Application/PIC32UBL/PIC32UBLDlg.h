// PIC32UBLDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPIC32UBLDlg dialog
class CPIC32UBLDlg : public CDialog
{
// Construction
public:
	CPIC32UBLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PIC32UBL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CBootLoader mBootLoader;
	bool EraseProgVer;
	bool ConnectionEstablished;
	void PrintKonsole(CString string);
	void ClearKonsole(void);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	UINT PortSelected;
public:
	afx_msg void OnBnClickedCancel();
	CComboBox ctrlComboBoxComPort;
	afx_msg void OnBnClickedButtonConnect();

// PIC32 Bootloader functions.
	void ExtraInitialization(void);
	void StartSendReceiveTimers(void);
	void ProgressBarTask(void);
	void EnableAllButtons(bool enbl);
	void ProgramHexFile(void);
	void ButtonStatus(unsigned int oprn);
	

	afx_msg LRESULT OnReceiveResponse(WPARAM, LPARAM);
	afx_msg LRESULT OnTransmitFailure(WPARAM, LPARAM);
	
	
	char TxCommand;
	char TxData[255];

	CComboBox ctrlComboBoxBaudRate;
	CButton ctrlButtonProgram;
	CButton ctrlButtonLoadHex;
	CButton ctrlButtonErase;
	CButton ctrlButtonVerify;
	CButton ctrlButtonRunApplication;
	afx_msg void OnTimer(UINT nIDEvent);
	CEdit ctrlEditConsole;
	CString cstringEditConsole;
	CProgressCtrl ctrlProgressBar;
	afx_msg void OnBnClickedButtonErase();
	CButton ctrlButtonConnectDevice;
	afx_msg void OnBnClickedButtonLoadhex();

	afx_msg void OnBnClickedButtonProgram();
	afx_msg void OnBnClickedButtonDisconnect();
	CButton ctrlButtonEraseProgVerify;
	afx_msg void OnBnClickedButtonVerify();
	afx_msg void OnBnClickedButtonEraseProgVerify();
	afx_msg void OnBnClickedButtonRunapplication();
	afx_msg void OnBnClickedButtonBootVer();
	CButton ctrlButtonBootloaderVer;
	unsigned long uLongEditBoxVID;
	unsigned long uLongEditBoxPID;
	bool boolRadioEnableCom;
	bool boolRadioEnableUSB;
	afx_msg void OnBnClickedRadioEnableCom();
	BOOL boolCheckComEnable;
	BOOL boolCheckUsbEnable;
	afx_msg void OnBnClickedCheckComEnable();
	CButton ctrlCheckBoxComEnable;
	CButton ctrlCheckBoxUSBEnable;
	afx_msg void OnBnClickedCheckUsbEnable();
	CEdit ctrlEditBoxUSBVID;
	CEdit ctrlEditBoxUSBPID;
	CString stringEditBoxUSBVID;
	CString stringEditBoxUSBPID;
	afx_msg void OnBnClickedCheckEthEnable();
	CButton ctrlCheckBoxEthEnable;
	BOOL boolCheckEthEnable;
	DWORD ip_value;
	UINT valEditBoxSocket;
	CIPAddressCtrl ctrlEditBoxIPaddress;
	CEdit ctrlEditBoxSocketaddress;
	BOOL OnDeviceChange(UINT wParam, DWORD lParam);
	afx_msg void OnDevModeChange(LPTSTR lpDeviceName);
};
