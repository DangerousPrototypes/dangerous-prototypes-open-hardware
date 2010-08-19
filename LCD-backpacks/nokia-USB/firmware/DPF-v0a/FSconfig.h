//HACKADAY:configure the options to use
//features change the amount of RAM and program memory required
//see the application note for a table of space requirements.
//this is our own minimal config file for licensing reasons.
//SEE \Microchip Solutions\MDD File System-SD Card\Pic24f\FSconfig.h for all possible options
#ifndef _FS_DEF_
#include "HardwareProfile.h"

#define FS_MAX_FILES_OPEN 	1
#define MEDIA_SECTOR_SIZE 		512
#define ALLOW_FILESEARCH
#define ALLOW_WRITES
#define ALLOW_FORMATS
#define ALLOW_DIRS
#define SUPPORT_FAT32

#define USEREALTIMECLOCK
//#define USERDEFINEDCLOCK
//#define INCREMENTTIMESTAMP

#define MDD_MediaInitialize     MDD_SDSPI_MediaInitialize
#define MDD_MediaDetect         MDD_SDSPI_MediaDetect
#define MDD_SectorRead          MDD_SDSPI_SectorRead
#define MDD_SectorWrite         MDD_SDSPI_SectorWrite
#define MDD_InitIO              MDD_SDSPI_InitIO
#define MDD_ShutdownMedia       MDD_SDSPI_ShutdownMedia
#define MDD_WriteProtectState   MDD_SDSPI_WriteProtectState

#endif
