// PIC32UBLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComPort.h"
#include "Ethernet.h"
#include "USB_HID.h"
#include "Hex.h"
#include "BootLoader.h"
#include "PIC32UBL.h"
#include "PIC32UBLDlg.h"
#include ".\pic32ubldlg.h"
#include <windows.h>
#include <wtypes.h>
#include <dbt.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BOOTLOADER_ROUTINE_TIMER 1
#define BOOTLOADER_GUI_UPDATE_TIMER 2
#define SWAP(x)   ( ((x<<24)&(0xFF000000)) | ((x<<8)&(0x00FF0000))  | ((x>>24)&(0x000000FF)) | ((x>>8)&(0x0000FF00)) )

#define SAVE 1
#define RESTORE 2

#define SaveButtonStatus() ButtonStatus(SAVE)
#define RestoreButtonStatus() ButtonStatus(RESTORE)

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPIC32UBLDlg dialog



CPIC32UBLDlg::CPIC32UBLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPIC32UBLDlg::IDD, pParent)
	, cstringEditConsole(_T(""))
	, uLongEditBoxVID(0)
	, uLongEditBoxPID(0)
	, boolRadioEnableCom(false)
	, boolRadioEnableUSB(false)
	, boolCheckComEnable(FALSE)
	, boolCheckUsbEnable(FALSE)
	, stringEditBoxUSBVID(_T(""))
	, stringEditBoxUSBPID(_T(""))
	, boolCheckEthEnable(FALSE)
	, ip_value(0)
	, valEditBoxSocket(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPIC32UBLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPORT, ctrlComboBoxComPort);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, ctrlComboBoxBaudRate);
	DDX_Control(pDX, IDC_BUTTON_PROGRAM, ctrlButtonProgram);
	DDX_Control(pDX, IDC_BUTTON_LOADHEX, ctrlButtonLoadHex);
	DDX_Control(pDX, IDC_BUTTON_ERASE, ctrlButtonErase);
	DDX_Control(pDX, IDC_BUTTON_VERIFY, ctrlButtonVerify);
	DDX_Control(pDX, IDC_BUTTON_RUNAPPLICATION, ctrlButtonRunApplication);
	DDX_Control(pDX, IDC_EDIT_CONSOLE, ctrlEditConsole);
	DDX_Text(pDX, IDC_EDIT_CONSOLE, cstringEditConsole);
	DDX_Control(pDX, IDC_PROGRESS_BAR, ctrlProgressBar);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, ctrlButtonConnectDevice);
	DDX_Control(pDX, IDC_BUTTON_ERASE_PROG_VERIFY, ctrlButtonEraseProgVerify);
	DDX_Control(pDX, IDC_BUTTON_BOOT_VER, ctrlButtonBootloaderVer);
	DDX_Check(pDX, IDC_CHECK_COM_ENABLE, boolCheckComEnable);
	DDX_Check(pDX, IDC_CHECK_USB_ENABLE, boolCheckUsbEnable);
	DDX_Control(pDX, IDC_CHECK_COM_ENABLE, ctrlCheckBoxComEnable);
	DDX_Control(pDX, IDC_CHECK_USB_ENABLE, ctrlCheckBoxUSBEnable);
	DDX_Control(pDX, IDC_EDIT_USB_VID, ctrlEditBoxUSBVID);
	DDX_Control(pDX, IDC_EDIT_USB_PID, ctrlEditBoxUSBPID);
	DDX_Text(pDX, IDC_EDIT_USB_VID, stringEditBoxUSBVID);
	DDX_Text(pDX, IDC_EDIT_USB_PID, stringEditBoxUSBPID);
	DDX_Control(pDX, IDC_CHECK_ETH_ENABLE, ctrlCheckBoxEthEnable);
	DDX_Check(pDX, IDC_CHECK_ETH_ENABLE, boolCheckEthEnable);
	DDX_IPAddress(pDX, IDC_IP_ADDRESS, ip_value);
	DDX_Text(pDX, IDC_SOCKET, valEditBoxSocket);
	DDX_Control(pDX, IDC_IP_ADDRESS, ctrlEditBoxIPaddress);
	DDX_Control(pDX, IDC_SOCKET, ctrlEditBoxSocketaddress);
}

BEGIN_MESSAGE_MAP(CPIC32UBLDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnBnClickedButtonConnect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnBnClickedButtonErase)
	ON_BN_CLICKED(IDC_BUTTON_LOADHEX, OnBnClickedButtonLoadhex)
	ON_MESSAGE(WM_USER_BOOTLOADER_RESP_OK, OnReceiveResponse)
	ON_MESSAGE(WM_USER_BOOTLOADER_NO_RESP, OnTransmitFailure)
	ON_BN_CLICKED(IDC_BUTTON_PROGRAM, OnBnClickedButtonProgram)
	ON_BN_CLICKED(IDC_BUTTON_VERIFY, OnBnClickedButtonVerify)
	ON_BN_CLICKED(IDC_BUTTON_ERASE_PROG_VERIFY, OnBnClickedButtonEraseProgVerify)
	ON_BN_CLICKED(IDC_BUTTON_RUNAPPLICATION, OnBnClickedButtonRunapplication)
	ON_BN_CLICKED(IDC_BUTTON_BOOT_VER, OnBnClickedButtonBootVer)
	
	ON_BN_CLICKED(IDC_CHECK_COM_ENABLE, OnBnClickedCheckComEnable)
	ON_BN_CLICKED(IDC_CHECK_USB_ENABLE, OnBnClickedCheckUsbEnable)
	ON_BN_CLICKED(IDC_CHECK_ETH_ENABLE, OnBnClickedCheckEthEnable)
	ON_WM_DEVICECHANGE()
	ON_WM_DEVMODECHANGE()
END_MESSAGE_MAP()


// CPIC32UBLDlg message handlers

BOOL CPIC32UBLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	ExtraInitialization();


	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPIC32UBLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPIC32UBLDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPIC32UBLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/****************************************************************************
 * Invoked just before dialog is closed
 *
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedCancel()
{
	int confirm;
	// TODO: Add your control notification handler code here
	confirm = MessageBox("Confirm Exit?", "Exit", MB_YESNO|MB_ICONQUESTION);
	if(confirm == 6)
	{
		// Exit confirmed
		OnCancel();
	}
}






//extern HDEVINFO SetupDiGetClassDevs(CONST GUID*, PCTSTR, HWND, DWORD);

/****************************************************************************
 * Invoked when connect button is clicked
 *
 *  
 *****************************************************************************/

void CPIC32UBLDlg::OnBnClickedButtonConnect()
{
	INT comport;
	INT baud;
	CString string;
	UINT vid;
	UINT pid;
	ULONG ip;
	USHORT skt;
	UpdateData(TRUE);
	
	if(ConnectionEstablished)
	{
		// Already connected. Disconnect now.
		ConnectionEstablished = false;

		// Shut down the rx-tx thread, if already opened.
			mBootLoader.ShutdownThread();
		
		if(mBootLoader.GetPortOpenStatus(PortSelected))
		{
			// com port already opened. close com port
			mBootLoader.ClosePort(PortSelected);			
		}

		

		// Print console.
		PrintKonsole("Device disconnected");
					
		EnableAllButtons(FALSE);
		

		ctrlButtonConnectDevice.SetWindowText("Connect");
		ctrlButtonConnectDevice.EnableWindow(TRUE);
	}
	else
	{
		// Establish new connection.
		comport = ctrlComboBoxComPort.GetCurSel();
		baud = ctrlComboBoxBaudRate.GetCurSel();

		sscanf(stringEditBoxUSBVID, "%X", &vid);
		sscanf(stringEditBoxUSBPID, "%X", &pid);
		// Update the screen with what VID and PID we have read.
		stringEditBoxUSBVID.FormatMessage("0x%1!X!",vid);
		stringEditBoxUSBPID.FormatMessage("0x%1!X!",pid);
		// Read ip address;
		ip = SWAP(ip_value);
		skt = (USHORT)valEditBoxSocket;
		UpdateData(FALSE);
		
		if(mBootLoader.GetPortOpenStatus(PortSelected))
		{
			// com port already opened. close com port
			mBootLoader.ClosePort(PortSelected);			
		}
		// Open Communication port freshly.
		mBootLoader.OpenPort(PortSelected, comport, baud, vid, pid, skt, ip, GetSafeHwnd());
        
		
		if(mBootLoader.GetPortOpenStatus(PortSelected))
		{	// COM port opened.
			// Shut down the rx-tx thread, if already opened.
			mBootLoader.ShutdownThread();
			// Create a new thread to do Rx Tx in the back ground.			
			mBootLoader.CreateRxTxThread(GetSafeHwnd()); // Create Rx Tx thread.
			// Trigger Read boot info command
			mBootLoader.SendCommand(READ_BOOT_INFO, 30, 200);					
			
			// Start timer to handle GUI updates.
			SetTimer(BOOTLOADER_GUI_UPDATE_TIMER, 300, NULL);  // Timer elapses every 300 ms.

			// Print a message to user/
			PrintKonsole("Please reset device and invoke bootloader");
			// Save button status.
			SaveButtonStatus();
			// Disable all buttons to avoid further operations
			EnableAllButtons(false);
		}

		
	}
}

/****************************************************************************
 * Invoked just after dialog is created. Do some extra initialization
 * like enabling and disabling buttons and so on.
 *  
 *****************************************************************************/
void CPIC32UBLDlg::ExtraInitialization()
{
	char com[9][5] = { "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9"};
	char baud[5][10] = {"9600", "19200", "38400", "57600", "115200"};

	EraseProgVer = false;

	// Fill Com Port Combo Box with "COM1, COM2 ........, COM9"	
	for(int i = 8; i >= 0; i--)
	{
		ctrlComboBoxComPort.InsertString(0, com[i]);
	}

	// By default set "COM1" in com port combo box 
	ctrlComboBoxComPort.SetCurSel(0);

	

	// Fill Baud Rate Combo Box with "9600, 19200, 38400, 57600, 115200"
	for(i = 4; i >= 0; i--)
	{
		ctrlComboBoxBaudRate.InsertString(0, baud[i]);
	}
	// By default set "115200" in baud rate combo box
	ctrlComboBoxBaudRate.SetCurSel(4);
	

	// Mask all buttons, except for "Connect Device"
	EnableAllButtons(false);
	ctrlButtonConnectDevice.EnableWindow(true);

	// Mark this flag as false.
	ConnectionEstablished = false;

	// Display default VID and PID in edit box. This is default value for Microchip device to work.
	stringEditBoxUSBVID = "0x4D8";
	stringEditBoxUSBPID = "0x03C";
	// Select communication "Com Port" by default.
	 boolCheckComEnable = 1;
	PortSelected = COM;
	// Diasble serial port selection and baud rate selection.
	ctrlComboBoxBaudRate.EnableWindow(TRUE);
	ctrlComboBoxComPort.EnableWindow(TRUE);
	// Enable USB VID and PID edit boxes.
	ctrlEditBoxUSBVID.EnableWindow(FALSE);
	ctrlEditBoxUSBPID.EnableWindow(FALSE);
	// Enable IP Address and Socket 
	ctrlEditBoxIPaddress.EnableWindow(FALSE);
	ctrlEditBoxSocketaddress.EnableWindow(FALSE);


	
	// Set default IP address to 192.168.1.11
	ip_value = inet_addr("192.168.1.11");
	ip_value = SWAP(ip_value);
	valEditBoxSocket = 6234;
	UpdateData(FALSE);

	

}

/****************************************************************************
 * Just do some mundane things here, like getting progress bar status, 
	disabling buttons if connection cuts.
   This function is called everytime the timer elapses.
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnTimer(UINT nIDEvent)
{
	int Lower;
	int Upper;

	if(nIDEvent == BOOTLOADER_GUI_UPDATE_TIMER)
	{
		// Update progress bar.
		mBootLoader.GetProgress(&Lower, &Upper);
		ctrlProgressBar.SetRange( 0, Upper );
		ctrlProgressBar.SetPos(Lower);		
	}

	
	
	CDialog::OnTimer(nIDEvent);
}

/****************************************************************************
 * Invoked when button erase is clicked.
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedButtonErase()
{
	SaveButtonStatus();
	// Disable all buttons, to avoid further operation.
	EnableAllButtons(false);
	mBootLoader.SendCommand(ERASE_FLASH, 3, 5000); //5s retry delay, becuse erase takes considerable time.
}


/****************************************************************************
 * Enables all button, if the parameter passed is true.
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::EnableAllButtons(bool enbl)
{
	// Mask all buttons, except for "Connect Device"
	ctrlButtonProgram.EnableWindow(enbl);
	ctrlButtonLoadHex.EnableWindow(enbl);
	ctrlButtonErase.EnableWindow(enbl);
	ctrlButtonVerify.EnableWindow(enbl);
	ctrlButtonRunApplication.EnableWindow(enbl);
//	ctrlButtonConnectDevice.EnableWindow(enbl);
	ctrlButtonEraseProgVerify.EnableWindow(enbl);
	ctrlButtonBootloaderVer.EnableWindow(enbl);

}


/****************************************************************************
 * Invoked when load hex button is clicked.
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedButtonLoadhex()
{
	CString string;
	// Save button status.
	SaveButtonStatus();
	if(mBootLoader.LoadHexFile())
	{
		PrintKonsole("Hex file loaded successfully");
		// Enable Program button
		ctrlButtonProgram.EnableWindow(true);
		ctrlButtonEraseProgVerify.EnableWindow(true);
	}
	else
	{
		PrintKonsole("Hex file loading failed");
	}	
}


/****************************************************************************
 * This function is invoked when there is a response from the device.
 Process the response based on the command.
 * 
 *  
 *****************************************************************************/
LRESULT CPIC32UBLDlg::OnReceiveResponse(WPARAM cmd, LPARAM RxDataPtrAdrs)
{
	char MajorVer;// = RxData[3];
	char MinorVer ;//= RxData[4];
	char *RxData;
	CString string;
	unsigned short crc;

	RxData = (char *)RxDataPtrAdrs;
	MajorVer = RxData[0];
	MinorVer = RxData[1];

	switch(cmd)
	{
	case READ_BOOT_INFO:
		if(ConnectionEstablished == false)
		{
			// New connection.
			ClearKonsole();
			string.FormatMessage("Device connected"); 
			PrintKonsole(string);
		}
		string.FormatMessage("Bootloader Firmware Version: %1!d!.%2!d!", MajorVer, MinorVer);
		PrintKonsole(string);		
		// Enable only load hex, Disconnect and erase buttons for next operation.
		ctrlButtonLoadHex.EnableWindow(true);
		ctrlButtonErase.EnableWindow(true);
		// Change the connect button to disconnect.
		ConnectionEstablished = true;
		ctrlButtonConnectDevice.SetWindowText("Disconnect");
		// Disable baud rate and com port combo boxes.
		ctrlComboBoxBaudRate.EnableWindow(false);
		ctrlComboBoxComPort.EnableWindow(false);
		// Disable USB VID and PID boxes.
		ctrlEditBoxUSBVID.EnableWindow(false);
		ctrlEditBoxUSBPID.EnableWindow(false);

		// Also enable bootloader version info.
		ctrlButtonBootloaderVer.EnableWindow(true);
		break;

	case ERASE_FLASH:
		PrintKonsole("Flash Erased");
		if(EraseProgVer)// Operation Erase->Program->Verify
		{
			// Erase completed. Next operation is programming.
			mBootLoader.SendCommand(PROGRAM_FLASH, 3, 500); // 500ms delay	
		}
		// Restore button status to allow further operations.
		RestoreButtonStatus();
		break;

	case PROGRAM_FLASH:
		PrintKonsole("Programming completed");
		// Restore button status to allow further operations.
		RestoreButtonStatus();
		ctrlButtonVerify.EnableWindow(true);
		ctrlButtonRunApplication.EnableWindow(true);

		if(EraseProgVer)// Operation Erase->Program->Verify
		{
			// Programming completed. Next operation is verification.
			mBootLoader.SendCommand(READ_CRC, 3, 5000);// 5 second delay
		}
		break;

	case READ_CRC:
		crc = ((RxData[1] << 8) & 0xFF00) | (RxData[0] & 0x00FF);
		
		if(crc == mBootLoader.CalculateFlashCRC())
		{
			PrintKonsole("Verification successfull");
		}
		else
		{
			PrintKonsole("Verification failed");
		}
		// Reset erase->program-verify operation.
		EraseProgVer = false;
		// Restore button status to allow further operations.
		RestoreButtonStatus();
		ctrlButtonVerify.EnableWindow(true);
		ctrlButtonRunApplication.EnableWindow(true);
		break;
	}
	
	if(!ConnectionEstablished)
	{
		// Disable all buttons, if disconnected.
		EnableAllButtons(false);
	}
	return 1;
}


/****************************************************************************
 *  This function is invoked when there is no resonse from the device, even after
	retries.
 *  
 *****************************************************************************/
LRESULT CPIC32UBLDlg::OnTransmitFailure(WPARAM cmd, LPARAM)
{
	CString string;
	
	EraseProgVer = false;
	switch(cmd)
	{
	case READ_BOOT_INFO:		
	case ERASE_FLASH:
	case PROGRAM_FLASH:
	case READ_CRC:
		PrintKonsole("No Response from the device. Operation failed");
		RestoreButtonStatus();
		break;
	}

	if(!ConnectionEstablished)
	{
		// Disable all buttons, if disconnected.
		EnableAllButtons(false);
	}

	return 1;
}


/****************************************************************************
 * Invoked when the button program is clicked.
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedButtonProgram()
{
	// Save button status.
	SaveButtonStatus();
	// Disable all buttons to avoid further operations
	EnableAllButtons(false);
	mBootLoader.SendCommand(PROGRAM_FLASH, 3, 5000); // 500ms delay
		
}


/****************************************************************************
 * This function is invoked when button verify is clicked
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedButtonVerify()
{
	// Save button status.
	SaveButtonStatus();
	// Disable all buttons to avoid further operations
	EnableAllButtons(false);
	mBootLoader.SendCommand(READ_CRC, 3, 5000);
}


/****************************************************************************
 * This function is invoked when button Erase-Program-Verify is clicked
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedButtonEraseProgVerify()
{
	// TODO: Add your control notification handler code here
	// Save button status.
	SaveButtonStatus();
	// Disable all buttons to avoid further operations
	EnableAllButtons(false);

	EraseProgVer = true;
	// Start with erase. Rest is automatically handled by state machine.
	mBootLoader.SendCommand(ERASE_FLASH, 3, 5000); // 5s delay

}


/****************************************************************************
 * This function is invoked when button run application is clicked
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedButtonRunapplication()
{
	CString string;

	mBootLoader.SendCommand(JMP_TO_APP, 1, 10); // 10ms delay
	PrintKonsole("\nCommand issued to run application");
}

/****************************************************************************
 * This function is invoked when button Read Version is clicked
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedButtonBootVer()
{
	// TODO: Add your control notification handler code here
	// Save button status.
	SaveButtonStatus();
	// Disable all buttons to avoid further operations
	EnableAllButtons(false);
	mBootLoader.SendCommand(READ_BOOT_INFO, 50, 200);
}


/****************************************************************************
 * Print Konsole
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::PrintKonsole(CString string)
{

	cstringEditConsole += string;
	string.FormatMessage("\n");
	cstringEditConsole += string;
	UpdateData(false);
	// Set the console window vertical scroll to the end.
	ctrlEditConsole.SetSel(32767, 32767);
}

/****************************************************************************
 * Clears konsole
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::ClearKonsole(void)
{

	cstringEditConsole = "";
	
	UpdateData(false);
	// Set the console window vertical scroll to the end.
	ctrlEditConsole.SetSel(32767, 32767);
}


/****************************************************************************
 * Saves the current status of the button and restores the button
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::ButtonStatus(unsigned int oprn)
{
	static unsigned int status;
	

	if(oprn == SAVE)
	{
		(ctrlButtonProgram.IsWindowEnabled())? status |= 0x01: status &= ~0x01;
		(ctrlButtonLoadHex.IsWindowEnabled())? status |= 0x02: status &= ~0x02;
		(ctrlButtonErase.IsWindowEnabled())? status |= 0x04: status &= ~0x04;
		(ctrlButtonVerify.IsWindowEnabled())? status |= 0x08: status &= ~0x08;
		(ctrlButtonRunApplication.IsWindowEnabled())? status |= 0x10: status &= ~0x10;
		(ctrlButtonConnectDevice.IsWindowEnabled())? status |= 0x20: status &= ~0x20;
		(ctrlButtonEraseProgVerify.IsWindowEnabled())? status |= 0x40: status &= ~0x40;
		(ctrlButtonBootloaderVer.IsWindowEnabled())? status |= 0x80: status &= ~0x80;
	}
	else
	{
		// Restore
		(status & 0x01)? ctrlButtonProgram.EnableWindow(true): ctrlButtonProgram.EnableWindow(false);
		(status & 0x02)? ctrlButtonLoadHex.EnableWindow(true): ctrlButtonLoadHex.EnableWindow(false);
		(status & 0x04)? ctrlButtonErase.EnableWindow(true): ctrlButtonErase.EnableWindow(false);
		(status & 0x08)? ctrlButtonVerify.EnableWindow(true): ctrlButtonVerify.EnableWindow(false);
		(status & 0x10)? ctrlButtonRunApplication.EnableWindow(true): ctrlButtonRunApplication.EnableWindow(false);
		(status & 0x20)? ctrlButtonConnectDevice.EnableWindow(true): ctrlButtonConnectDevice.EnableWindow(false);
		(status & 0x40)? ctrlButtonEraseProgVerify.EnableWindow(true): ctrlButtonEraseProgVerify.EnableWindow(false);
		(status & 0x80)? ctrlButtonBootloaderVer.EnableWindow(true): ctrlButtonBootloaderVer.EnableWindow(false);
	}


}


/****************************************************************************
 * COM check box button clicked.
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedCheckComEnable()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	boolCheckComEnable = 1;
	boolCheckUsbEnable = 0;	
	boolCheckEthEnable = 0;
	PortSelected = COM;

	// Enable serial port selection and baud rate selection.
	ctrlComboBoxBaudRate.EnableWindow(TRUE);
	ctrlComboBoxComPort.EnableWindow(TRUE);
	// Disable USB VID and PID edit boxes.
	ctrlEditBoxUSBVID.EnableWindow(FALSE);
	ctrlEditBoxUSBPID.EnableWindow(FALSE);
	// Disable IP Address and Socket 
	ctrlEditBoxIPaddress.EnableWindow(FALSE);
	ctrlEditBoxSocketaddress.EnableWindow(FALSE);


	UpdateData(FALSE);
}


/****************************************************************************
 * USB check box button clicked.
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedCheckUsbEnable()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	boolCheckUsbEnable = 1;
	boolCheckComEnable = 0;
	boolCheckEthEnable = 0;
	PortSelected = USB;

	// Diasble serial port selection and baud rate selection.
	ctrlComboBoxBaudRate.EnableWindow(FALSE);
	ctrlComboBoxComPort.EnableWindow(FALSE);
	// Enable USB VID and PID edit boxes.
	ctrlEditBoxUSBVID.EnableWindow(TRUE);
	ctrlEditBoxUSBPID.EnableWindow(TRUE);
	// Enable IP Address and Socket 
	ctrlEditBoxIPaddress.EnableWindow(FALSE);
	ctrlEditBoxSocketaddress.EnableWindow(FALSE);


	UpdateData(FALSE);
}


/****************************************************************************
 * Ethernet check box button clicked.
 * 
 *  
 *****************************************************************************/
void CPIC32UBLDlg::OnBnClickedCheckEthEnable()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	boolCheckEthEnable = 1;
	boolCheckComEnable = 0;
	boolCheckUsbEnable = 0;
	PortSelected = ETH;

	// Diasble serial port selection and baud rate selection.
	ctrlComboBoxBaudRate.EnableWindow(FALSE);
	ctrlComboBoxComPort.EnableWindow(FALSE);
	// Enable USB VID and PID edit boxes.
	ctrlEditBoxUSBVID.EnableWindow(FALSE);
	ctrlEditBoxUSBPID.EnableWindow(FALSE);
	// Enable IP Address and Socket 
	ctrlEditBoxIPaddress.EnableWindow(TRUE);
	ctrlEditBoxSocketaddress.EnableWindow(TRUE);

	UpdateData(FALSE);
}



BOOL CPIC32UBLDlg::OnDeviceChange(UINT wParam, DWORD lParam)
{
	UINT k = 0;
	DEV_BROADCAST_DEVICEINTERFACE *pdevBroadCastHdr;

	if(lParam != 0)
	{
		pdevBroadCastHdr = (DEV_BROADCAST_DEVICEINTERFACE *)lParam;

		if(pdevBroadCastHdr->dbcc_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
		{
			switch(wParam)
			{
				case DBT_DEVICEARRIVAL:					
					return TRUE;
				case DBT_DEVICEREMOVECOMPLETE:
				case DBT_DEVICEQUERYREMOVE:
				case DBT_DEVICEQUERYREMOVEFAILED:
				case DBT_DEVICEREMOVEPENDING:
				case DBT_DEVICETYPESPECIFIC:
					if(mBootLoader.NotifyDeviceChange(PortSelected, pdevBroadCastHdr->dbcc_name))
					{
						OnBnClickedButtonConnect();
					}
					return TRUE;
				default:
					return TRUE;
			}
		}
	}

	return TRUE;
}
/********************************End of file**********************************/
void CPIC32UBLDlg::OnDevModeChange(LPTSTR lpDeviceName)
{
	CDialog::OnDevModeChange(lpDeviceName);

	// TODO: Add your message handler code here
}
