// Strings.h v0.7.5

enum S {				//
	S_noprog,			//
	S_prog,				//
	S_nodev_r,			//
	S_nodev_w,			//
	S_nodev,			//
	S_DevMismatch,		//
	S_noV33reg,			//
	S_progver,			//
	S_progid,			//
	S_FWver2old,		//
	S_lowUsbV,			//
	S_HiVPP,			//
	S_LowVPP,			//
	S_reg,				//
	S_dev_det,			//
	S_file,				//
	S_file2,			//
	S_fileEEP,			//
	S_noDLL,			//
	S_openEEfile,		//
	S_saveEEfile,		//
	S_IhexShort,		//
	S_IhexChecksum,		//
	S_InvHandle,		//
	S_LogFile,			//
	S_HVICSP,			//
	S_StartRead,		//
	S_Read,				//
	S_CodeReading1,		//
	S_CodeReading,		//
	S_CodeReading2,		//
	S_ReadEnd,			//
	S_ReadID_CONFIG,	//
	S_Read_CONFIG_A,	//
	S_Read_EXE_A,		//
	S_ReadEE,			//
	S_StartErase,		//
	S_Writing,			//
	S_StartCodeProg,	//
	S_CodeWriting,		//
	S_CodeWriting2,		//
	S_IDW,				//
	S_ConfigW,			//
	S_ConfigAreaW,		//
	S_EEAreaW,			//
	S_FuseAreaW,		//
	S_CodeV,			//
	S_CodeV2,			//
	S_IDV,				//
	S_ConfigV,			//
	S_EEV,				//
	S_IntW,				//
	S_TotErr,			//
	S_ComplErr,			//
	S_Compl,			//
	S_Ready,			//
	S_End,				//
	S_EndErr,			//
	S_ProtErase,		//
	S_Inohex,			//
	S_ReadErr,			//
	S_ReadCodeErr,		//
	S_ReadCodeErr2,		//
	S_ReadEEErr,		//
	S_ConfigErr,		//
	S_ReadConfigErr,	//
	S_ErrOsccal,		//
	S_CodeWError,		//
	S_CodeWError2,		//
	S_CodeWError3,		//
	S_CodeWError4,		//
	S_ConfigWErr,		//
	S_ConfigWErr2,		//
	S_ConfigWErr3,		//
	S_IDErr,			//
	S_ICDErr,			//
	S_Calib1Err,		//
	S_Calib2Err,		//
	S_CodeVError,		//
	S_CodeVError2,		//
	S_CodeVError3,		//
	S_ErrSing,			//
	S_ErrPlur,			//
	S_MaxErr,			//
	S_I2CInitErr,		//
	S_I2CAckErr,		//
	S_ComErr,			//
	S_InsErr,			//
	S_SyncErr,			//
	S_HVregErr,			//
	S_Log1,				//
	S_Log2,				//
	S_Log3,				//
	S_Log4,				//
	S_Log5,				//
	S_Log6,				//
	S_Log7,				//
	S_Log8,				//
	S_Log9,				//
	S_comTimeout,		//
	S_EraseTimeout,		//
	S_ConfigTimeout,	//
	S_ConfigTimeout2,	//
	S_CodeTimeout,		//
	S_CodeTimeout2,		//
	S_OsccalTimeout,	//
	S_EETimeout,		//
	S_ConfigWTimeout,	//
	S_CodeWTimeout,		//
	S_ConfigWTimeout2,	//
	S_EEWTimeout,		//
	S_IDWTimeout,		//
	S_ConfigNWTimeout,	//
	S_CodeVTimeout,		//
	S_ConfigVTimeout,	//
	S_ProgModeTimeout,	//
	S_ProgModeXTimeout,	//
	S_LogTimeout,		//
	S_CodeMem,			//
	S_EEMem,			//
	S_IDMem,			//
	S_ConfigMem,		//
	S_ConfigResMem,		//
	S_CodeMem2,			//
	S_ExeMem,			//
	S_LPOsc,			//
	S_XTOsc,			//
	S_IntOsc,			//
	S_RCOsc,			//
	S_WDTON,			//
	S_WDTOFF,			//
	S_CPOFF,			//
	S_CPON,				//
	S_MCLRON,			//
	S_MCLROFF,			//
	S_ChipID,			//
	S_ChipID2,			//
	S_BKOsccal,			//
	S_Osccal,			//
	S_DevID,			//
	S_DevID2,			//
	S_ConfigWord,		//
	S_ConfigWord2,		//
	S_ConfigWordX,		//
	S_Config2Cal1,		//
	S_ConfigWordH,		//
	S_ConfigWordL,		//
	S_CalibWord1,		//
	S_Calib1_2, 		//
	S_CalibWord2,		//
	S_CalibWordX,		//
	S_Protected,		//
	S_CodeLim,			//
	S_EELim,			//
	S_ConfigLim,		//
	S_WbufLim,			//
	S_MaxRetry,			//
	S_NoCode,			//
	S_NoCode2,			//
	S_NoCalibW,			//
	S_NoEEMem,			//
	S_NoConfigW,		//
	S_NoConfigW2,		//
	S_NoConfigW3,		//
	S_NoConfigW4,		//
	S_Empty,			//
// GUI strings
	I_Data,				//
	I_Opt,				//
	I_Dev,				//
	I_ReadRes,			//
	I_ID_BKo_W,			//
	I_EE,				//
	I_CalW,				//
	I_OSCW,				//
	I_OSC,				//
	I_BKOSC,			//
	I_OSCF,				//
	I_CONN,				//
	I_LOG,				//
	I_LANG,				//
	I_MAXERR,			//
	I_USBD,				//
	I_I2CDATAOUT,		//
	I_I2CDATATR,		//
	I_I2C_NB,			//
	I_I2CMode,			//
	I_I2CSend,			//
	I_I2CReceive,		//
	I_TestHW,			//
	I_TestHWB,			//
	I_AT_CONFIG,
	I_AT_FUSE,
	I_AT_FUSEH,
	I_AT_FUSEX,
	I_AT_LOCK,
	I_W_LANGFILE,
	I_ICD_ENABLE,
	I_ICD_ADDRESS,
//	command-line strings
	L_HELP,				//
	L_OPTERR,
	L_INFO1,
	L_INFO2,
	L_UNKNOWN,
	L_NAME,
	L_DEV_RO,
	L_DEV_RW,
	DIM};

