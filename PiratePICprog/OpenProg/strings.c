// Strings.c v0.7.5

char *STR_ID[DIM];

STR_ID[S_noprog]="S_noprog";
STR_ID[S_prog]="S_prog";
STR_ID[S_nodev_r]="S_nodev_r";
STR_ID[S_nodev_w]="S_nodev_w";
STR_ID[S_nodev]="S_nodev";
STR_ID[S_DevMismatch]="S_DevMismatch";
STR_ID[S_noV33reg]="S_noV33reg";
STR_ID[S_progver]="S_progver";
STR_ID[S_progid]="S_progid";
STR_ID[S_FWver2old]="S_FWver2old";
STR_ID[S_lowUsbV]="S_lowUsbV";
STR_ID[S_HiVPP]="S_HiVPP";
STR_ID[S_LowVPP]="S_LowVPP";
STR_ID[S_reg]="S_reg";
STR_ID[S_dev_det]="S_dev_det";
STR_ID[S_file]="S_file";
STR_ID[S_file2]="S_file2";
STR_ID[S_fileEEP]="S_fileEEP";
STR_ID[S_noDLL]="S_noDLL";
STR_ID[S_openEEfile]="S_openEEfile";
STR_ID[S_saveEEfile]="S_saveEEfile";
						//
STR_ID[S_IhexShort]="S_IhexShort";
STR_ID[S_IhexChecksum]="S_IhexChecksum";
STR_ID[S_InvHandle]="S_InvHandle";
STR_ID[S_LogFile]="S_LogFile";
						//
STR_ID[S_HVICSP]="S_HVICSP";
STR_ID[S_StartRead]="S_StartRead";
STR_ID[S_Read]="S_Read";
STR_ID[S_CodeReading]="S_CodeReading";
STR_ID[S_CodeReading1]="S_CodeReading1";
STR_ID[S_CodeReading2]="S_CodeReading2";
STR_ID[S_ReadEnd]="S_ReadEnd";
STR_ID[S_ReadID_CONFIG]="S_ReadID_CONFIG";
STR_ID[S_Read_CONFIG_A]="S_Read_CONFIG_A";
STR_ID[S_Read_EXE_A]="S_Read_EXE_A";
STR_ID[S_ReadEE]="S_ReadEE";
STR_ID[S_StartErase]="S_StartErase";
STR_ID[S_Writing]="S_Writing";
STR_ID[S_StartCodeProg]="S_StartCodeProg";
STR_ID[S_CodeWriting]="S_CodeWriting";
STR_ID[S_CodeWriting2]="S_CodeWriting2";
STR_ID[S_IDW]="S_IDW";
STR_ID[S_ConfigW]="S_ConfigW";
STR_ID[S_ConfigAreaW]="S_ConfigAreaW";
STR_ID[S_EEAreaW]="S_EEAreaW";
STR_ID[S_FuseAreaW]="S_FuseAreaW";
STR_ID[S_CodeV]="S_CodeV";
STR_ID[S_CodeV2]="S_CodeV2";
STR_ID[S_IDV]="S_IDV";
STR_ID[S_ConfigV]="S_ConfigV";
STR_ID[S_EEV]="S_EEV";
STR_ID[S_IntW]="S_IntW";
STR_ID[S_TotErr]="S_TotErr";
STR_ID[S_ComplErr]="S_ComplErr";
STR_ID[S_Compl]="S_Compl";
STR_ID[S_Ready]="S_Ready";
STR_ID[S_End]="S_End";
STR_ID[S_EndErr]="S_EndErr";
STR_ID[S_ProtErase]="S_ProtErase";
						//
STR_ID[S_Inohex]="S_Inohex";
STR_ID[S_ReadErr]="S_ReadErr";
STR_ID[S_ReadCodeErr]="S_ReadCodeErr";
STR_ID[S_ReadCodeErr2]="S_ReadCodeErr2";
STR_ID[S_ReadEEErr]="S_ReadEEErr";
STR_ID[S_ConfigErr]="S_ConfigErr";
STR_ID[S_ReadConfigErr]="S_ReadConfigErr";
STR_ID[S_ErrOsccal]="S_ErrOsccal";
STR_ID[S_CodeWError]="S_CodeWError";
STR_ID[S_CodeWError2]="S_CodeWError2";
STR_ID[S_CodeWError3]="S_CodeWError3";
STR_ID[S_CodeWError4]="S_CodeWError4";
STR_ID[S_ConfigWErr]="S_ConfigWErr";
STR_ID[S_ConfigWErr2]="S_ConfigWErr2";
STR_ID[S_ConfigWErr3]="S_ConfigWErr3";
STR_ID[S_IDErr]="S_IDErr";
STR_ID[S_ICDErr]="S_ICDErr";
STR_ID[S_Calib1Err]="S_Calib1Err";
STR_ID[S_Calib2Err]="S_Calib2Err";
STR_ID[S_CodeVError]="S_CodeVError";
STR_ID[S_CodeVError2]="S_CodeVError2";
STR_ID[S_CodeVError3]="S_CodeVError3";
STR_ID[S_ErrSing]="S_ErrSing";
STR_ID[S_ErrPlur]="S_ErrPlur";
STR_ID[S_MaxErr]="S_MaxErr";
STR_ID[S_I2CInitErr]="S_I2CInitErr";
STR_ID[S_I2CAckErr]="S_I2CAckErr";
STR_ID[S_ComErr]="S_ComErr";
STR_ID[S_InsErr]="S_InsErr";
STR_ID[S_SyncErr]="S_SyncErr";
STR_ID[S_HVregErr]="S_HVregErr";
						//
STR_ID[S_Log1]="S_Log1";
STR_ID[S_Log2]="S_Log2";
STR_ID[S_Log3]="S_Log3";
STR_ID[S_Log4]="S_Log4";
STR_ID[S_Log5]="S_Log5";
STR_ID[S_Log6]="S_Log6";
STR_ID[S_Log7]="S_Log7";
STR_ID[S_Log8]="S_Log8";
STR_ID[S_Log9]="S_Log9";
						//
STR_ID[S_comTimeout]="S_comTimeout";
STR_ID[S_EraseTimeout]="S_EraseTimeout";
STR_ID[S_ConfigTimeout]="S_ConfigTimeout";
STR_ID[S_ConfigTimeout2]="S_ConfigTimeout2";
STR_ID[S_CodeTimeout]="S_CodeTimeout";
STR_ID[S_CodeTimeout2]="S_CodeTimeout2";
STR_ID[S_OsccalTimeout]="S_OsccalTimeout";
STR_ID[S_EETimeout]="S_EETimeout";
STR_ID[S_ConfigWTimeout]="S_ConfigWTimeout";
STR_ID[S_CodeWTimeout]="S_CodeWTimeout";
STR_ID[S_ConfigWTimeout2]="S_ConfigWTimeout2";
STR_ID[S_EEWTimeout]="S_EEWTimeout";
STR_ID[S_IDWTimeout]="S_IDWTimeout";
STR_ID[S_ConfigNWTimeout]="S_ConfigNWTimeout";
STR_ID[S_CodeVTimeout]="S_CodeVTimeout";
STR_ID[S_ConfigVTimeout]="S_ConfigVTimeout";
STR_ID[S_ProgModeTimeout]="S_ProgModeTimeout";
STR_ID[S_ProgModeXTimeout]="S_ProgModeXTimeout";
STR_ID[S_LogTimeout]="S_LogTimeout";
						//
STR_ID[S_CodeMem]="S_CodeMem";
STR_ID[S_EEMem]="S_EEMem";
STR_ID[S_IDMem]="S_IDMem";
STR_ID[S_ConfigMem]="S_ConfigMem";
STR_ID[S_ConfigResMem]="S_ConfigResMem";
STR_ID[S_CodeMem2]="S_CodeMem2";
STR_ID[S_ExeMem]="S_ExeMem";
						//
STR_ID[S_LPOsc]="S_LPOsc";
STR_ID[S_XTOsc]="S_XTOsc";
STR_ID[S_IntOsc]="S_IntOsc";
STR_ID[S_RCOsc]="S_RCOsc";
STR_ID[S_WDTON]="S_WDTON";
STR_ID[S_WDTOFF]="S_WDTOFF";
STR_ID[S_CPOFF]="S_CPOFF";
STR_ID[S_CPON]="S_CPON";
STR_ID[S_MCLRON]="S_MCLRON";
STR_ID[S_MCLROFF]="S_MCLROFF";
STR_ID[S_ChipID]="S_ChipID";
STR_ID[S_ChipID2]="S_ChipID2";
STR_ID[S_BKOsccal]="S_BKOsccal";
STR_ID[S_Osccal]="S_Osccal";
STR_ID[S_DevID]="S_DevID";
STR_ID[S_DevID2]="S_DevID2";
STR_ID[S_ConfigWord]="S_ConfigWord";
STR_ID[S_ConfigWord2]="S_ConfigWord2";
STR_ID[S_ConfigWordX]="S_ConfigWordX";
STR_ID[S_ConfigWordH]="S_ConfigWordH";
STR_ID[S_ConfigWordL]="S_ConfigWordL";
STR_ID[S_Config2Cal1]="S_Config2Cal1";
STR_ID[S_CalibWord1]="S_CalibWord1";
STR_ID[S_Calib1_2]="S_Calib1_2";
STR_ID[S_CalibWord2]="S_CalibWord2";
STR_ID[S_CalibWordX]="S_CalibWordX";
STR_ID[S_Protected]="S_Protected";
						//
STR_ID[S_CodeLim]="S_CodeLim";
STR_ID[S_EELim]="S_EELim";
STR_ID[S_ConfigLim]="S_ConfigLim";
STR_ID[S_WbufLim]="S_WbufLim";
STR_ID[S_MaxRetry]="S_MaxRetry";
						//
STR_ID[S_NoCode]="S_NoCode";
STR_ID[S_NoCode2]="S_NoCode2";
STR_ID[S_NoCalibW]="S_NoCalibW";
STR_ID[S_NoEEMem]="S_NoEEMem";
STR_ID[S_NoConfigW]="S_NoConfigW";
STR_ID[S_NoConfigW2]="S_NoConfigW2";
STR_ID[S_NoConfigW3]="S_NoConfigW3";
STR_ID[S_NoConfigW4]="S_NoConfigW4";
STR_ID[S_Empty]="S_Empty";
						//
STR_ID[I_Data]="I_Data";
STR_ID[I_Opt]="I_Opt";
STR_ID[I_Dev]="I_Dev";
STR_ID[I_ReadRes]="I_ReadRes";
STR_ID[I_ID_BKo_W]="I_ID_BKo_W";
STR_ID[I_EE]="I_EE";
STR_ID[I_CalW]="I_CalW";
STR_ID[I_OSCW]="I_OSCW";
STR_ID[I_OSC]="I_OSC";
STR_ID[I_BKOSC]="I_BKOSC";
STR_ID[I_OSCF]="I_OSCF";
STR_ID[I_CONN]="I_CONN";
STR_ID[I_LOG]="I_LOG";
STR_ID[I_LANG]="I_LANG";
STR_ID[I_MAXERR]="I_MAXERR";
STR_ID[I_USBD]="I_USBD";
STR_ID[I_I2CDATAOUT]="I_I2CDATAOUT";
STR_ID[I_I2CDATATR]="I_I2CDATATR";
STR_ID[I_I2C_NB]="I_I2C_NB";
STR_ID[I_I2CMode]="I_I2CMode";
STR_ID[I_I2CSend]="I_I2CSend";
STR_ID[I_I2CReceive]="I_I2CReceive";
STR_ID[I_TestHW]="I_TestHW";
STR_ID[I_TestHWB]="I_TestHWB";
STR_ID[I_AT_CONFIG]="I_AT_CONFIG";
STR_ID[I_AT_FUSE]="I_AT_FUSE";
STR_ID[I_AT_FUSEH]="I_AT_FUSEH";
STR_ID[I_AT_FUSEX]="I_AT_FUSEX";
STR_ID[I_AT_LOCK]="I_AT_LOCK";
STR_ID[I_W_LANGFILE]="I_W_LANGFILE";
STR_ID[I_ICD_ENABLE]="I_ICD_ENABLE";
STR_ID[I_ICD_ADDRESS]="I_ICD_ADDRESS";
						//
STR_ID[L_HELP]="L_HELP";
STR_ID[L_OPTERR]="L_OPTERR";
STR_ID[L_INFO1]="L_INFO1";
STR_ID[L_INFO2]="L_INFO2";
STR_ID[L_UNKNOWN]="L_UNKNOWN";
STR_ID[L_NAME]="L_NAME";
STR_ID[L_DEV_RO]="L_DEV_RO";
STR_ID[L_DEV_RW]="L_DEV_RW";


char *strings_it[DIM];
strings_it[S_noprog]="Programmatore non rilevato\r\n";
strings_it[S_prog]="Programmatore rilevato\r\n";
strings_it[S_nodev_r]="Dispositivo non supportato in lettura\r\n";
strings_it[S_nodev_w]="Dispositivo non supportato in scrittura\r\n";
strings_it[S_nodev]="Dispositivo sconosciuto\r\n";
strings_it[S_DevMismatch]="Attenzione: il dispositivo è diverso da quello specificato nei dati\r\n";
strings_it[S_noV33reg]="Regolatore a 3.3V non rilevato\r\n";
strings_it[S_progver]="Versione firmware %d.%d.%d\r\n";
strings_it[S_progid]="ID Hardware: %d.%d.%d";
strings_it[S_FWver2old]="Questo firmware è troppo vecchio. E' richiesta la versione %s\r\n";
strings_it[S_lowUsbV]="Tensione USB troppo bassa (VUSB<4.5V)\r\n";
strings_it[S_HiVPP]="Attenzione: tensione regolatore troppo alta\r\n\r\n";
strings_it[S_LowVPP]="Attenzione: tensione regolatore troppo bassa\r\n\r\n";
strings_it[S_reg]="Regolatore avviato e funzionante dopo T=%d ms VPP=%.1fV\r\n\r\n";
strings_it[S_dev_det]="Dispositivo rilevato: vid=0x%04X pid=0x%04X\r\nPercorso: %s\r\n";
strings_it[S_file]="File Hex8 (*.hex)|*.hex|Tutti i file (*.*)|*.*||";
strings_it[S_file2]="File Hex8 (*.hex)|*.hex|File binari (*.bin)|*.bin|Tutti i file (*.*)|*.*||";
strings_it[S_fileEEP]="File Hex8 (*.hex *.eep)|*.hex;*.eep|Tutti i file (*.*)|*.*||";
strings_it[S_noDLL]="Impossibile aprire hid.dll";
strings_it[S_openEEfile]="Apri file EEPROM";
strings_it[S_saveEEfile]="Salva file EEPROM";
					//
strings_it[S_IhexShort]="Linea Ihex8 troppo corta:\r\n%s\r\n";
strings_it[S_IhexChecksum]="Errore di checksum nella linea Ihex8:\r\n%s\r\n";
strings_it[S_InvHandle]="Handle invalido\r\n";
strings_it[S_LogFile]="Registro.txt";
					//
strings_it[S_HVICSP]="ICSP ad alta tensione\r\n";
strings_it[S_StartRead]="Inizio lettura...\r\n";
strings_it[S_Read]="Lettura ... ";
strings_it[S_CodeReading1]="Lettura codice ... ";
strings_it[S_CodeReading]="Lettura: %d%%, ind. %03X";
strings_it[S_CodeReading2]="Lettura: %d%%, ind. %05X";
strings_it[S_ReadEnd]="Lettura completata: %d word\r\n";
strings_it[S_ReadID_CONFIG]="Lettura ID e CONFIG";
strings_it[S_Read_CONFIG_A]="Lettura area CONFIG ... ";
strings_it[S_Read_EXE_A]="Lettura area Executive ... ";
strings_it[S_ReadEE]="Lettura area EEPROM ... ";
strings_it[S_StartErase]="Cancellazione ... ";
strings_it[S_Writing]="Inizio scrittura...\r\n";
strings_it[S_StartCodeProg]="Scrittura codice ... ";
strings_it[S_CodeWriting]="Scrittura: %d%%, ind. %03X";
strings_it[S_CodeWriting2]="Scrittura: %d%%, ind. %04X";
strings_it[S_IDW]="Scrittura ID ... ";
strings_it[S_ConfigW]="Scrittura CONFIG ... ";
strings_it[S_ConfigAreaW]="Scrittura area CONFIG ... ";
strings_it[S_EEAreaW]="Scrittura area EEPROM ... ";
strings_it[S_FuseAreaW]="Scrittura area FUSE ... ";
strings_it[S_CodeV]="Verifica codice ... ";
strings_it[S_CodeV2]="Verifica: %d%%, ind. %04X";
strings_it[S_IDV]="Verifica ID ... ";
strings_it[S_ConfigV]="Verifica CONFIG ... ";
strings_it[S_EEV]="Verifica EEPROM ... ";
strings_it[S_IntW]="Scrittura interrotta\r\n";
strings_it[S_TotErr]="completata, %d errori totali\r\n";
strings_it[S_ComplErr]="completata, %d errori\r\n";
strings_it[S_Compl]="completata\r\n";
strings_it[S_Ready]="pronto";
strings_it[S_End]="\r\nFine (%.2f s)\r\n\r\n";
strings_it[S_EndErr]="\r\nFine (%.2f s) %d %s\r\n\r\n";
strings_it[S_ProtErase]="Il dispositivo è protetto, sovrascrivo la protezione.\r\n";
					//
strings_it[S_Inohex]="Errore: '%.4s' non sembra molto esadecimale, vero?\n";
strings_it[S_ReadErr]="Errore in lettura: word richieste=%d, lette=%d\r\n";
strings_it[S_ReadCodeErr]="Errore in lettura area programma, richieste %d word, lette %d\r\n";
strings_it[S_ReadCodeErr2]="Errore in lettura area programma, richiesti %d byte, letti %d\r\n";
strings_it[S_ReadEEErr]="Errore in lettura area EEPROM, richiesti %d byte, letti %d\r\n";
strings_it[S_ConfigErr]="Errore in lettura area configurazione, richieste %d word, lette %d\r\n";
strings_it[S_ReadConfigErr]="Errore in lettura area configurazione, richiesti %d byte, letti %d\r\n";
strings_it[S_ErrOsccal]="Errore in lettura OSCCAL e BKOSCCAL";
strings_it[S_CodeWError]="Errore in scrittura all'indirizzo %3X: scritto %03X, letto %03X\r\n";
strings_it[S_CodeWError2]="Errore in scrittura all'indirizzo %3X: scritto %04X, letto %04X\r\n";
strings_it[S_CodeWError3]="Errore in scrittura all'indirizzo %4X: scritto %02X, letto %02X\r\n";
strings_it[S_CodeWError4]="Errore in scrittura area programma, richiesti %d byte, scritti %d\r\n";
strings_it[S_ConfigWErr]="Errore in scrittura config: scritto %03X, letto %03X\r\n";
strings_it[S_ConfigWErr2]="Errore in scrittura CONFIG";
strings_it[S_ConfigWErr3]="Errore in scrittura config: scritto %04X, letto %04X\r\n";
strings_it[S_IDErr]="Errore in scrittura ID%d: scritto %04X, letto %04X\r\n";
strings_it[S_ICDErr]="Errore in scrittura ICD (0x%X): scritto %04X, letto %04X\r\n";
strings_it[S_Calib1Err]="Errore in scrittura Calib1: scritto %04X, letto %04X\r\n";
strings_it[S_Calib2Err]="Errore in scrittura Calib2: scritto %04X, letto %04X\r\n";
strings_it[S_CodeVError]="Errore in verifica, indirizzo %04X (%d), scritto %02X, letto %02X\r\n";
strings_it[S_CodeVError2]="Errore in verifica area programma, richiesti %d byte, letti %d\r\n";
strings_it[S_CodeVError3]="Errore in verifica area programma, richiest3 %d word, lett3 %d\r\n";
strings_it[S_ErrSing]="errore";
strings_it[S_ErrPlur]="errori";
strings_it[S_MaxErr]="Superato il massimo numero di errori (%d), scrittura interrotta\r\n";
strings_it[S_I2CInitErr]="Errore di inizializzazione bus I2C\r\n";
strings_it[S_I2CAckErr]="Errore di acknowledge I2C\r\n";
strings_it[S_ComErr]="Errore di comunicazione\r\n";
strings_it[S_InsErr]="Istruzione sconosciuta\r\n";
strings_it[S_SyncErr]="Errore di sincronizzazione\r\n";
strings_it[S_HVregErr]="Errore sul regolatore HV\r\n";
					//
strings_it[S_Log1]="i=%d(0x%X), k=%d(0x%X)  NumberOfBytesRead=%d\n";
strings_it[S_Log2]="i=%d, k=%d, errori=%d, NumberOfBytesRead=%d\n\n";
strings_it[S_Log3]="i=%d, k2=%d NumberOfBytesRead=%d\n";
strings_it[S_Log4]="Area config. 	errori=%d   NumberOfBytesRead=%d\n";
strings_it[S_Log5]="dim=%d(0x%X), dimx=%d(0x%X), dimx/wbuf=%d \n\n";
strings_it[S_Log6]="i=%d(0x%X),  NumberOfBytesRead=%d\n\n";
strings_it[S_Log7]="i=%d(0x%X), k=%d(0x%X)\n";
strings_it[S_Log8]="i=%d(0x%X), k=%d(0x%X), errori=%d\n";
strings_it[S_Log9]="Area config. 	errori=%d\n";
					//
strings_it[S_comTimeout]="Timeout comunicazione\r\n";
strings_it[S_EraseTimeout]="Timeout in cancellazione\r\n";
strings_it[S_ConfigTimeout]="Timeout in lettura config\r\n";
strings_it[S_ConfigTimeout2]="Timeout in lettura area config\r\n";
strings_it[S_CodeTimeout]="Timeout in lettura, indirizzo %02X (%d)\r\n";
strings_it[S_CodeTimeout2]="Timeout in lettura, indirizzo %04X (%d)\r\n";
strings_it[S_OsccalTimeout]="Timeout in lettura osccal\r\n";
strings_it[S_EETimeout]="Timeout in lettura EEPROM, indirizzo %02X (%d)\r\n";
strings_it[S_ConfigWTimeout]="Timeout in verifica config\r\n";
strings_it[S_CodeWTimeout]="Timeout in scrittura, indirizzo %02X (%d)\r\n";
strings_it[S_ConfigWTimeout2]="Timeout in scrittura area config\r\n";
strings_it[S_EEWTimeout]="Timeout in scrittura EEPROM, indirizzo %03X (%d)\r\n";
strings_it[S_IDWTimeout]="Timeout in scrittura ID\r\n";
strings_it[S_ConfigNWTimeout]="Timeout in scrittura CONFIG%d\r\n";
strings_it[S_CodeVTimeout]="Timeout in verifica, indirizzo %04X (%d)\r\n";
strings_it[S_ConfigVTimeout]="Timeout in verifica area config\r\n";
strings_it[S_ProgModeTimeout]="Timeout in entrata program mode\r\n";
strings_it[S_ProgModeXTimeout]="Timeout in uscita programmazione\r\n";
strings_it[S_LogTimeout]="Timeout\n";
					//
strings_it[S_CodeMem]="\r\nmemoria CODICE:\r\n";
strings_it[S_EEMem]="\r\nmemoria EEPROM:\r\n";
strings_it[S_IDMem]="\r\nmemoria ID:\r\n";
strings_it[S_ConfigMem]="\r\nmemoria CONFIG:\r\n";
strings_it[S_ConfigResMem]="\r\nMemoria configurazione e riservata:\r\n";
strings_it[S_CodeMem2]="\r\nMemoria programma:\r\n";
strings_it[S_ExeMem]="\r\nmemoria Executive:\r\n";
					//
strings_it[S_LPOsc]="LP oscillator\r\n";
strings_it[S_XTOsc]="XT oscillator\r\n";
strings_it[S_IntOsc]="Internal osc.\r\n";
strings_it[S_RCOsc]="RC oscillator\r\n";
strings_it[S_WDTON]="WDT ON\r\n";
strings_it[S_WDTOFF]="WDT OFF\r\n";
strings_it[S_CPOFF]="Code protection OFF\r\n";
strings_it[S_CPON]="Code protection ON\r\n";
strings_it[S_MCLRON]="Master clear ON\r\n";
strings_it[S_MCLROFF]="Master clear OFF\r\n";
strings_it[S_ChipID]="ID%d: 0x%03X   ID%d: 0x%03X\r\n";
strings_it[S_ChipID2]="ID%d: 0x%02X   ID%d: 0x%02X\r\n";
strings_it[S_BKOsccal]="Backup OSCCAL: 0x%03X\r\n";
strings_it[S_Osccal]="OSCCAL: 0x%03X\r\n";
strings_it[S_DevID]="DevID: 0x%04X\r\n";
strings_it[S_DevID2]="DevID: 0x%02X%02X\r\n";
strings_it[S_ConfigWord]="Configuration word: 0x%03X\r\n";
strings_it[S_Config2Cal1]="Configuration word2 o calibration word 1: 0x%03X\r\n";
strings_it[S_ConfigWord2]="Configuration word2: 0x%04X\r\n";
strings_it[S_ConfigWordX]="Configuration word %d: 0x%04X\r\n";
strings_it[S_ConfigWordH]="CONFIG%dH: 0x%02X\t";
strings_it[S_ConfigWordL]="CONFIG%dL: 0x%02X\r\n";
strings_it[S_CalibWord1]="Calibration word1: 0x%04X\r\n";
strings_it[S_Calib1_2]="Calibration word 1 or 2: 0x%04X\r\n";
strings_it[S_CalibWord2]="Calibration word2: 0x%04X\r\n";
strings_it[S_CalibWordX]="Calibration word %d: 0x%04X\r\n";
strings_it[S_Protected]="Dispositivo protetto";
					//
strings_it[S_CodeLim]="Dimensione programma oltre i limiti\r\n";
strings_it[S_EELim]="Dimensione eeprom oltre i limiti\r\n";
strings_it[S_ConfigLim]="Dimensione area config oltre i limiti\r\n";
strings_it[S_WbufLim]="Dimensione buffer scrittura oltre i limiti\r\n";
strings_it[S_MaxRetry]="Max tentativi di scrittura: %d\r\n";
					//
strings_it[S_NoCode]="Area dati vuota\r\n";
strings_it[S_NoCode2]="Niente da scrivere\r\n";
strings_it[S_NoCalibW]="Impossibile trovare i dati di calibrazione\r\n";
strings_it[S_NoEEMem]="Impossibile trovare i dati EEPROM\r\n";
strings_it[S_NoConfigW]="Impossibile leggere la config word\r\n";
strings_it[S_NoConfigW2]="Impossibile trovare la locazione CONFIG (0xFFF)\r\n";
strings_it[S_NoConfigW3]="Impossibile trovare la locazione CONFIG (0x2007)\r\nFine\r\n";
strings_it[S_NoConfigW4]="Impossibile trovare la locazione CONFIG (0x2008)\r\nFine\r\n";
strings_it[S_Empty]="(vuoto)\r\n";
					//
strings_it[I_Data]="Dati";
strings_it[I_Opt]="Opzioni";
strings_it[I_Dev]="Dispositivo";
strings_it[I_ReadRes]="Leggi area riservata";
strings_it[I_ID_BKo_W]="Programma ID e BKosccal";
strings_it[I_EE]="Leggi e programma EEPROM";
strings_it[I_CalW]="Programma Calib1 e 2";
strings_it[I_OSCW]="Scrivi OSCCal";
strings_it[I_OSC]="OSCCal";
strings_it[I_BKOSC]="Backup OSCCal";
strings_it[I_OSCF]="Da File";
strings_it[I_CONN]="Riconnetti";
strings_it[I_LOG]="Registra eventi su file";
strings_it[I_LANG]="Lingua";
strings_it[I_MAXERR]="Max errori in scrittura";
strings_it[I_USBD]="Ritardo minimo USB (ms)";
strings_it[I_I2CDATAOUT]="Dati da scrivere";
strings_it[I_I2CDATATR]="Dati trasferiti";
strings_it[I_I2C_NB]="Byte da scrivere/leggere";
strings_it[I_I2CMode]="Modalità";
strings_it[I_I2CSend]="Invia";
strings_it[I_I2CReceive]="Ricevi";
strings_it[I_TestHW]="Test hardware: rimuovere eventuali dispositivi dal programmatore";
strings_it[I_TestHWB]="Test hardware";
strings_it[I_AT_CONFIG]="Configurazione Atmel";
strings_it[I_AT_FUSE]="Scrivi Fuse Low";
strings_it[I_AT_FUSEH]="Scrivi Fuse High";
strings_it[I_AT_FUSEX]="Scrivi Extended Fuse";
strings_it[I_AT_LOCK]="Scrivi Lock";
strings_it[I_W_LANGFILE]="Scrivi file linguaggio";
strings_it[I_ICD_ENABLE]="Abilita ICD";
strings_it[I_ICD_ADDRESS]="Indirizzo routine ICD";
					//
strings_it[L_HELP]="op [opzioni]\n\
\n-BKosccal                   carica BKosccal da file\
\n-calib                      carica calibration da file\
\n-d, device <disp.>          dispositivo\
\n-delay <ms>                 ritardo minimo [2]\
\n-ee                         usa eeprom\
\n-err <max>                  imposta massimo errori in scrittura\
\n-fuse <val>                 scrive il byte fuse low (solo Atmel)\
\n-fuseh <val>                scrive il byte fuse high (solo Atmel)\
\n-fusex <val>                scrive il byte extended fuse (solo Atmel)\
\n-h, help                    guida\
\n-HWtest                     test hardware\
\n-i, info                    informazioni programmatore\
\n-icd <val>                  abilita ICD (goto indirizzo)\
\n-i2c_r <N Ctr Ind>          leggi N byte dal bus I2C\
\n-i2c_r2 <N Ctr Ind(2)>      leggi N byte dal bus I2C (indirizzi 16b)\
\n-i2c_w <N Ctr Ind Dati>     scrivi N byte sul bus I2C\
\n-i2c_w2 <N Ctr Ind(2) Dati> scrivi N byte sul bus I2C (indirizzi 16b)\
\n-id                         usa ID\
\n-l, log [=file]              salva registro\
\n-lock <val>                 scrive il byte lock (solo Atmel)\
\n-mode <mode>                SPI mode: 00,01,10,11\
\n-osccal                     carica osccal da file invece che dal valore salvato prima della cancellazione\
\n-p, path <percorso>         percorso programmatore [/dev/usb/hiddev0]\
\n-pid <pid>                  pid programmatore [0x100]\
\n-r, reserved                leggi area riservata\
\n-rep <n>                    dimensione report [64]\
\n-s, save <file>             salva su file Ihex\
\n-se, saveEE <file>          salva EEPROM su file Ihex (solo ATxxxx)\
\n-spi_r <N>                  leggi N byte dal bus SPI\
\n-spi_w <N Dati>             scrivi N byte sul bus SPI\
\n-support                    dispositivi supportati\
\n-use_BKosccal               copia BKosccal su osccal\
\n-v, version                 versione\
\n-vid <vid>                  vid programmatore [0x4D8]\
\n-w, write <file>            scrivi file Ihex\
\n-we, writeEE <file>         scrivi EEPROM file Ihex (solo ATxxxx)\
\n\
\nes.  op -d 12F683 -s prova.hex\n";
strings_it[L_OPTERR]="Errore nelle opzioni\n";
strings_it[L_INFO1]="vid 0x%04hx pid 0x%04hx versione 0x%04hx ";
strings_it[L_INFO2]="\nbus: %d devnum: %d ifnum: %d\n";
strings_it[L_UNKNOWN]="sconosciuto";
strings_it[L_NAME]="Il dispositivo su %s si chiama %s\n";
strings_it[L_DEV_RO]="Dispositivi supportati in sola lettura:";
strings_it[L_DEV_RW]="Dispositivi supportati in lettura e scrittura:";


char *strings_en[DIM];
strings_en[S_noprog]="Programmer not detected\r\n";
strings_en[S_prog]="Programmer detected\r\n";
strings_en[S_nodev_r]="Device not supported for reading\r\n";
strings_en[S_nodev_w]="Device not supported for writing\r\n";
strings_en[S_nodev]="Unknown device\r\n";
strings_en[S_DevMismatch]="Warning: the device is different from what specified in source data\r\n";
strings_en[S_noV33reg]="3.3V Regulator not detected\r\n";
strings_en[S_progver]="Firmware version %d.%d.%d\r\n";
strings_en[S_progid]="Hardware ID: %d.%d.%d";
strings_en[S_FWver2old]="This firmware is too old. Version %s is required\r\n";
strings_en[S_lowUsbV]="USB voltage too low (VUSB<4.5V)\r\n";
strings_en[S_HiVPP]="Warning: regulator voltage too high\r\n\r\n";
strings_en[S_LowVPP]="Warning: regulator voltage too low\r\n\r\n";
strings_en[S_reg]="Regulator up and running after T=%d ms VPP=%.1fV\r\n\r\n";
strings_en[S_dev_det]="Device detected: vid=0x%04X pid=0x%04X\r\nPath: %s\r\n";
strings_en[S_file]="Hex8 files (*.hex)|*.hex|All files (*.*)|*.*||";
strings_en[S_file2]="Hex8 files (*.hex)|*.hex|Binary files (*.bin)|*.bin|All files (*.*)|*.*||";
strings_en[S_fileEEP]="Hex8 files (*.hex *.eep)|*.hex;*.eep|All files (*.*)|*.*||";
strings_en[S_noDLL]="Error opening hid.dll";
strings_en[S_openEEfile]="Open EEPROM file";
strings_en[S_saveEEfile]="Save EEPROM file";
					//
strings_en[S_IhexShort]="Intel hex8 line too short:\r\n%s\r\n";
strings_en[S_IhexChecksum]="Intel hex8 checksum error in line:\r\n%s\r\n";
strings_en[S_InvHandle]="Invalid handle\r\n";
strings_en[S_LogFile]="Log.txt";
	//
strings_en[S_HVICSP]="High Voltage ICSP\r\n";
strings_en[S_StartRead]="Reading ...\r\n";
strings_en[S_Read]="Reading ... ";
strings_en[S_CodeReading1]="Reading code ... ";
strings_en[S_CodeReading]="Reading: %d%%, add. %03X";
strings_en[S_CodeReading2]="Reading: %d%%, add. %05X";
strings_en[S_ReadEnd]="Reading completed: %d words\r\n";
strings_en[S_ReadID_CONFIG]="Reading ID and CONFIG";
strings_en[S_Read_CONFIG_A]="Reading CONFIG area ... ";
strings_en[S_Read_EXE_A]="Reading Executive area ... ";
strings_en[S_ReadEE]="Reading EEPROM ... ";
strings_en[S_StartErase]="Erasing ... ";
strings_en[S_Writing]="Writing ...\r\n";
strings_en[S_StartCodeProg]="Writing code ... ";
strings_en[S_CodeWriting]="Writing: %d%%, add. %03X";
strings_en[S_CodeWriting2]="Writing: %d%%, add. %04X";
strings_en[S_IDW]="Writing ID ... ";
strings_en[S_ConfigW]="Writing CONFIG ... ";
strings_en[S_ConfigAreaW]="Writing CONFIG area ... ";
strings_en[S_EEAreaW]="Writing EEPROM ... ";
strings_en[S_FuseAreaW]="Writing FUSE area ... ";
strings_en[S_CodeV]="Verifying code ... ";
strings_en[S_CodeV2]="Verifying: %d%%, add. %04X";
strings_en[S_IDV]="Verifying ID ... ";
strings_en[S_ConfigV]="Verifying CONFIG ... ";
strings_en[S_EEV]="Verifying EEPROM ... ";
strings_en[S_IntW]="Write interrupted\r\n";
strings_en[S_TotErr]="completed, %d total errors\r\n";
strings_en[S_ComplErr]="completed, %d errors\r\n";
strings_en[S_Compl]="completed\r\n";
strings_en[S_Ready]="ready";
strings_en[S_End]="\r\nEnd (%.2f s)\r\n\r\n";
strings_en[S_EndErr]="\r\nEnd (%.2f s) %d %s\r\n\r\n";
strings_en[S_ProtErase]="Device protected, overriding protection.\r\n";
	//
strings_en[S_Inohex]="Error: '%.4s' doesn't look very hexadecimal, right?\n";
strings_en[S_ReadErr]="Read error: requested words=%d, read=%d\r\n";
strings_en[S_ReadCodeErr]="Error reading code area, requested %d words, read %d\r\n";
strings_en[S_ReadCodeErr2]="Error reading code area, requested %d bytes, read %d\r\n";
strings_en[S_ReadEEErr]="Error reading EEPROM area, requested %d bytes, read %d\r\n";
strings_en[S_ConfigErr]="Error reading configuration area, requested %d words, read %d\r\n";
strings_en[S_ReadConfigErr]="Error reading configuration area, requested %d bytes, read %d\r\n";
strings_en[S_ErrOsccal]="Error reading OSCCAL and BKOSCCAL";
strings_en[S_CodeWError]="Error writing address %3X: written %03X, read %03X\r\n";
strings_en[S_CodeWError2]="Error writing address %3X: written %04X, read %04X\r\n";
strings_en[S_CodeWError3]="Error writing address %4X: written %02X, read %02X\r\n";
strings_en[S_CodeWError4]="Error writing code area, requested %d bytes, written %d\r\n";
strings_en[S_ConfigWErr]="Error writing config area: written %03X, read %03X\r\n";
strings_en[S_ConfigWErr2]="Error writing CONFIG";
strings_en[S_ConfigWErr3]="Error writing config area: written %04X, read %04X\r\n";
strings_en[S_IDErr]="Error writing ID%d: written %04X, read %04X\r\n";
strings_en[S_ICDErr]="Error writing ICD (0x%X): written %04X, read %04X\r\n";
strings_en[S_Calib1Err]="Error writing Calib1: written %04X, read %04X\r\n";
strings_en[S_Calib2Err]="Error writing Calib2: written %04X, read %04X\r\n";
strings_en[S_CodeVError]="Error verifying address %04X (%d), written %02X, read %02X\r\n";
strings_en[S_CodeVError2]="Error verifying code area, requested %d bytes, read %d\r\n";
strings_en[S_CodeVError3]="Error verifying code area, requested %d words, read %d\r\n";
strings_en[S_ErrSing]="error";
strings_en[S_ErrPlur]="errors";
strings_en[S_MaxErr]="Exceeded maximum number of errors (%d), write interrupted\r\n";
strings_en[S_I2CInitErr]="Error initializing I2C bus\r\n";
strings_en[S_I2CAckErr]="I2C acknowledge error\r\n";
strings_en[S_ComErr]="Communication error\r\n";
strings_en[S_InsErr]="Unknown instruction\r\n";
strings_en[S_SyncErr]="Synchronization error\r\n";
strings_en[S_HVregErr]="HV regulator error\r\n";
	//
strings_en[S_Log1]="i=%d(0x%X), k=%d(0x%X)  NumberOfBytesRead=%d\n";
strings_en[S_Log2]="i=%d, k=%d, errors=%d, NumberOfBytesRead=%d\n\n";
strings_en[S_Log3]="i=%d, k2=%d NumberOfBytesRead=%d\n";
strings_en[S_Log4]="Config area. 	errors=%d   NumberOfBytesRead=%d\n";
strings_en[S_Log5]="dim=%d(0x%X), dimx=%d(0x%X), dimx/wbuf=%d \n\n";
strings_en[S_Log6]="i=%d(0x%X),  NumberOfBytesRead=%d\n\n";
strings_en[S_Log7]="i=%d(0x%X), k=%d(0x%X)\n";
strings_en[S_Log8]="i=%d(0x%X), k=%d(0x%X), errors=%d\n";
strings_en[S_Log9]="Config area. 	errors=%d\n";
	//
strings_en[S_comTimeout]="Communication timeout\r\n";
strings_en[S_EraseTimeout]="Timeout during erase\r\n";
strings_en[S_ConfigTimeout]="Timeout reading CONFIG\r\n";
strings_en[S_ConfigTimeout2]="Timeout reading config area\r\n";
strings_en[S_CodeTimeout]="Timeout reading address %02X (%d)\r\n";
strings_en[S_CodeTimeout2]="Timeout reading address %04X (%d)\r\n";
strings_en[S_OsccalTimeout]="Timeout reading osccal\r\n";
strings_en[S_EETimeout]="Timeout reading EEPROM, address %02X (%d)\r\n";
strings_en[S_ConfigWTimeout]="Timeout verifying config\r\n";
strings_en[S_CodeWTimeout]="Timeout writing address %02X (%d)\r\n";
strings_en[S_ConfigWTimeout2]="Timeout writing config area\r\n";
strings_en[S_EEWTimeout]="Timeout writing EEPROM, address %03X (%d)\r\n";
strings_en[S_IDWTimeout]="Timeout writing ID\r\n";
strings_en[S_ConfigNWTimeout]="Timeout writing CONFIG%d\r\n";
strings_en[S_CodeVTimeout]="Timeout verifying address %04X (%d)\r\n";
strings_en[S_ConfigVTimeout]="Timeout verifying config area\r\n";
strings_en[S_ProgModeTimeout]="Timeout entering program mode\r\n";
strings_en[S_ProgModeXTimeout]="Timeout exiting program mode\r\n";
strings_en[S_LogTimeout]="Timeout\n";
	//
strings_en[S_CodeMem]="\r\nCode memory:\r\n";
strings_en[S_EEMem]="\r\nEEPROM memory:\r\n";
strings_en[S_IDMem]="\r\nID:\r\n";
strings_en[S_ConfigMem]="\r\nCONFIG:\r\n";
strings_en[S_ConfigResMem]="\r\nConfiguration and reserved memory:\r\n";
strings_en[S_CodeMem2]="\r\nCode memory:\r\n";
strings_en[S_ExeMem]="\r\nExecutive memory:\r\n";
	//
strings_en[S_LPOsc]="LP oscillator\r\n";
strings_en[S_XTOsc]="XT oscillator\r\n";
strings_en[S_IntOsc]="Internal osc.\r\n";
strings_en[S_RCOsc]="RC oscillator\r\n";
strings_en[S_WDTON]="WDT ON\r\n";
strings_en[S_WDTOFF]="WDT OFF\r\n";
strings_en[S_CPOFF]="Code protection OFF\r\n";
strings_en[S_CPON]="Code protection ON\r\n";
strings_en[S_MCLRON]="Master clear ON\r\n";
strings_en[S_MCLROFF]="Master clear OFF\r\n";
strings_en[S_ChipID]="ID%d: 0x%03X   ID%d: 0x%03X\r\n";
strings_en[S_ChipID2]="ID%d: 0x%02X   ID%d: 0x%02X\r\n";
strings_en[S_BKOsccal]="Backup OSCCAL: 0x%03X\r\n";
strings_en[S_Osccal]="OSCCAL: 0x%03X\r\n";
strings_en[S_DevID]="DevID: 0x%04X\r\n";
strings_en[S_DevID2]="DevID: 0x%02X%02X\r\n";
strings_en[S_ConfigWord]="Configuration word: 0x%03X\r\n";
strings_en[S_Config2Cal1]="Configuration word2 or calibration word 1: 0x%03X\r\n";
strings_en[S_ConfigWord2]="Configuration word2: 0x%04X\r\n";
strings_en[S_ConfigWordX]="Configuration word %d: 0x%04X\r\n";
strings_en[S_ConfigWordH]="CONFIG%dH: 0x%02X\t";
strings_en[S_ConfigWordL]="CONFIG%dL: 0x%02X\r\n";
strings_en[S_CalibWord1]="Calibration word1: 0x%04X\r\n";
strings_en[S_Calib1_2]="Calibration word 1 or 2: 0x%04X\r\n";
strings_en[S_CalibWord2]="Calibration word2: 0x%04X\r\n";
strings_en[S_CalibWordX]="Calibration word %d: 0x%04X\r\n";
strings_en[S_Protected]="protected device";
	//
strings_en[S_CodeLim]="Code size exceeds limits\r\n";
strings_en[S_EELim]="Eeprom size exceeds limits\r\n";
strings_en[S_ConfigLim]="Config area size exceeds limits\r\n";
strings_en[S_WbufLim]="Write buffer size exceeds limits\r\n";
strings_en[S_MaxRetry]="Max retries in writing: %d\r\n";
	//
strings_en[S_NoCode]="Data area is empty\r\n";
strings_en[S_NoCode2]="Nothing to write\r\n";
strings_en[S_NoCalibW]="Can't find calibration data\r\n";
strings_en[S_NoEEMem]="Can't find EEPROM data\r\n";
strings_en[S_NoConfigW]="Impossibile leggere la config word\r\n";
strings_en[S_NoConfigW2]="Can't find CONFIG location (0xFFF)\r\n";
strings_en[S_NoConfigW3]="Can't find CONFIG location (0x2007)\r\nEnd\r\n";
strings_en[S_NoConfigW4]="Can't find CONFIG location (0x2008)\r\nEnd\r\n";
strings_en[S_Empty]="(empty)\r\n";
	//
strings_en[I_Data]="Data";
strings_en[I_Opt]="Options";
strings_en[I_Dev]="Device";
strings_en[I_ReadRes]="Read reserved area";
strings_en[I_ID_BKo_W]="Write ID and BKosccal";
strings_en[I_EE]="Read and write EEPROM";
strings_en[I_CalW]="Write Calib1 e 2";
strings_en[I_OSCW]="Write OSCCal";
strings_en[I_OSC]="OSCCal";
strings_en[I_BKOSC]="Backup OSCCal";
strings_en[I_OSCF]="From File";
strings_en[I_CONN]="Reconnect";
strings_en[I_LOG]="Log activity";
strings_en[I_LANG]="Language";
strings_en[I_MAXERR]="Max errors in writing";
strings_en[I_USBD]="Min USB delay (ms)";
strings_en[I_I2CDATAOUT]="Data to send";
strings_en[I_I2CDATATR]="Data transferred";
strings_en[I_I2C_NB]="Bytes to read/write";
strings_en[I_I2CMode]="Mode";
strings_en[I_I2CSend]="Send";
strings_en[I_I2CReceive]="Receive";
strings_en[I_TestHW]="Hardware test: remove any device from programmer";
strings_en[I_TestHWB]="Hardware test";
strings_en[I_AT_CONFIG]="Atmel configuration";
strings_en[I_AT_FUSE]="Write Fuse Low";
strings_en[I_AT_FUSEH]="Write Fuse High";
strings_en[I_AT_FUSEX]="Write Extended Fuse";
strings_en[I_AT_LOCK]="Write Lock";
strings_en[I_W_LANGFILE]="Write language file";
strings_en[I_ICD_ENABLE]="Enable ICD";
strings_en[I_ICD_ADDRESS]="ICD routine address";
	//
strings_en[L_HELP]="op [options]\n\
	\n-BKosccal                   load BKosccal from file\
	\n-calib                      load calibration from file\
	\n-d, device <dev.>           device\
	\n-delay <ms>                 minimum delay [2]\
	\n-ee                         use eeprom\
	\n-err <max>                  max errors during writing\
	\n-fuse <val>                 write fuse low byte (Atmel only)\
	\n-fuseh <val>                write fuse high byte (Atmel only)\
	\n-fusex <val>                write extended fuse byte (Atmel only)\
	\n-h, help                    help\
	\n-HWtest                     hardware test\
	\n-i, info                    informations about programmer\
	\n-i2c_r <N Ctr Addr>         read N bytes from I2C bus\
	\n-i2c_r2 <N Ctr Addr(2)>     read N bytes from I2C bus (16b address)\
	\n-i2c_r <N Ctr Addr Data>    write N bytes to I2C bus\
	\n-i2c_r <N Ctr Addr(2) Data> write N bytes to I2C bus (16b address)\
	\n-id                         use ID\
	\n-icd <val>                  enable ICD (goto address)\
	\n-l, log [=file]             save log\
	\n-lock <val>                 write lock byte (Atmel only)\
	\n-mode <mode>                SPI mode: 00,01,10,11\
	\n-osccal                     loads osccal from file instead of using the value saved before erase\
	\n-p, path <path>             programmer path [/dev/usb/hiddev0]\
	\n-pid <pid>                  programmer pid [0x100]\
	\n-r, reserved                read reserved area\
	\n-rep <n>                    report size [64]\
	\n-s, save <file>             save Ihex file\
	\n-se, saveEE <file>          save EEPROM on Ihex file (ATxxxx only)\
	\n-spi_r <N>                  read N bytes from SPI bus\
	\n-spi_w <N Data>             write N bytes to SPI bus\
	\n-support                    supported devices\
	\n-use_BKosccal               copy BKosccal to osccal\
	\n-v, version                 version\
	\n-vid <vid>                  programmer vid [0x4D8]\
	\n-w, write <file>            write Ihex file\
	\n-we, writeEE <file>         write EEPROM on Ihex file (ATxxxx only)\
	\n\
	\nex.  op -d 12F683 -s test.hex\n";
strings_en[L_OPTERR]="Error in command-line options\n";
strings_en[L_INFO1]="vid 0x%04hx pid 0x%04hx version 0x%04hx ";
strings_en[L_INFO2]="\nbus: %d devnum: %d ifnum: %d\n";
strings_en[L_UNKNOWN]="Unknown";
strings_en[L_NAME]="The device on %s says its name is %s\n";
strings_en[L_DEV_RO]="Devices supported for reading only:";
strings_en[L_DEV_RW]="Devices supported for reading and writing:";

