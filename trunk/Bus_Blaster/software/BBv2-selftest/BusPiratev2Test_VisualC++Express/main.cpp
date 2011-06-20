/*
 * BusBlaster v2.x tester app 
 * http://dangerousprototypes.com/docs/Bus_Blaster
 * 
 * Author: Bogdan Kecman <bogdan.kecman@crsn.rs>
 * Date: 2011-06-10
 * 
 * Licence: OPEN - do whatever you want with this code on your own risk
 * 
 * Liability: Author is not lieable in any way for any damage this source might cause to you, use at your own risk
 * 
 */

#include <Windows.h>
#include <WinDef.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#include "ftdi/ftd2xx.h"

#define MAX_DEVICES 10


FT_HANDLE     ftHandle;
char         *pcBufLD[MAX_DEVICES + 1];
char          cBufLD[MAX_DEVICES][64];
char          bNuber[10];
int           iDevicesOpen;
unsigned char outputBuffer[10];
unsigned char inputBuffer[65535];
DWORD         BytesWritten;
DWORD         BytesReceived;
DWORD         BytesToRead;
int           iNumDevs;
FT_STATUS     ftStatus;
int           shortDelay;


struct timespec {
   int tv_sec;        /* seconds */
   long   tv_nsec;       /* nanoseconds */
};


struct timespec T;



void nanosleep(struct timespec *x, struct timespec *y){
	if (shortDelay){
	   Sleep(10);
	}else{
       Sleep(1000*x->tv_sec+x->tv_nsec/100000000);
	}
}

unsigned char kbhit_getc()
{
    return getchar();
}

unsigned char kbhit()
{
    return getchar();
}



void fterror(FT_STATUS ftStatus) {
    switch (ftStatus) {
    case FT_OK:
        fprintf(stderr,"FT_OK\n");
        break;
    case FT_INVALID_HANDLE:
        fprintf(stderr,"FT_INVALID_HANDLE\n");
        break;
    case FT_DEVICE_NOT_FOUND:
        fprintf(stderr,"FT_DEVICE_NOT_FOUND\n");
        break;
    case FT_DEVICE_NOT_OPENED:
        fprintf(stderr,"FT_DEVICE_NOT_OPENED\n");
        break;
    case FT_IO_ERROR:
        fprintf(stderr,"FT_IO_ERROR\n");
        break;
    case FT_INSUFFICIENT_RESOURCES:
        fprintf(stderr,"FT_INSUFFICIENT_RESOURCES\n");
        break;
    case FT_INVALID_PARAMETER:
        fprintf(stderr,"FT_INVALID_PARAMETER\n");
        break;
    case FT_INVALID_BAUD_RATE:
        fprintf(stderr,"FT_INVALID_BAUD_RATE\n");
        break;
    case FT_DEVICE_NOT_OPENED_FOR_ERASE:
        fprintf(stderr,"FT_DEVICE_NOT_OPENED_FOR_ERASE\n");
        break;
    case FT_DEVICE_NOT_OPENED_FOR_WRITE:
        fprintf(stderr,"FT_DEVICE_NOT_OPENED_FOR_WRITE\n");
        break;
    case FT_FAILED_TO_WRITE_DEVICE:
        fprintf(stderr,"FT_FAILED_TO_WRITE_DEVICE\n");
        break;
    case FT_EEPROM_READ_FAILED:
        fprintf(stderr,"FT_EEPROM_READ_FAILED\n");
        break;
    case FT_EEPROM_WRITE_FAILED:
        fprintf(stderr,"FT_EEPROM_WRITE_FAILED\n");
        break;
    case FT_EEPROM_ERASE_FAILED:
        fprintf(stderr,"FT_EEPROM_ERASE_FAILED\n");
        break;
    case FT_EEPROM_NOT_PRESENT:
        fprintf(stderr,"FT_EEPROM_NOT_PRESENT\n");
        break;
    case FT_EEPROM_NOT_PROGRAMMED:
        fprintf(stderr,"FT_EEPROM_NOT_PROGRAMMED\n");
        break;
    case FT_INVALID_ARGS:
        fprintf(stderr,"FT_INVALID_ARGS\n");
        break;
    case FT_NOT_SUPPORTED:
        fprintf(stderr,"FT_NOT_SUPPORTED\n");
        break;
    case FT_OTHER_ERROR:
        fprintf(stderr,"FT_OTHER_ERROR\n");
        break;
    }
}


int outputADBUS( unsigned char x) {
    int i;

    // output 0xff to ADBUS
    outputBuffer[0] = 0x80; //set ADBUS
    outputBuffer[1] = x; //value
    outputBuffer[2] = 0xFF; //direction (all out)

    if ((ftStatus = FT_Write(ftHandle, outputBuffer, 3, &BytesWritten)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }

    T.tv_sec = 1;
	T.tv_nsec = 0;
    nanosleep(&T, NULL);

    if ((ftStatus = FT_GetQueueStatus(ftHandle, &BytesToRead)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }

    if (BytesToRead > 0) {
        //fprintf(stderr, "ERROR: queue is not empty (%i) \n", BytesToRead );
        if ((ftStatus = FT_Read(ftHandle, inputBuffer, BytesToRead, &BytesReceived)) != FT_OK) {
            fterror(ftStatus);
        }
        for (i = 0; i < BytesReceived; i++) fprintf(stderr, "\t\t%i: 0x%X\n", i, inputBuffer[i]);
        //return -1; //non crytical error
    }
    return 0;
}

int readACBUS() {

    T.tv_sec = 1;
	T.tv_nsec = 0;
    nanosleep(&T, NULL);

    outputBuffer[0] = 0x83; //read ACBUS
    if ((ftStatus = FT_Write(ftHandle, outputBuffer, 1, &BytesWritten)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }

    T.tv_sec = 1;
	T.tv_nsec = 0;
    nanosleep(&T, NULL);

    if ((ftStatus = FT_GetQueueStatus(ftHandle, &BytesToRead)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }

    if (BytesToRead > 0) {
        //if (BytesToRead != 1) fprintf(stderr, "ERROR: %i bytes in queue\n", BytesToRead );
        if ((ftStatus = FT_Read(ftHandle, inputBuffer, BytesToRead, &BytesReceived)) != FT_OK) {
            fterror(ftStatus);
        } else {
            //for (i = 0; i< BytesReceived; i++) fprintf(stderr, "\t%i:\t 0x%X\n", i, inputBuffer[i]);
            return inputBuffer[BytesReceived-1];
        }
    } else {
        printf("no data ?!\n");
    }
    return -1;
}

int syncMPSSE() {
    outputBuffer[0] = 0x84;
    if ((ftStatus = FT_Write(ftHandle, outputBuffer, 1, &BytesWritten)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }
    if ((ftStatus = FT_GetQueueStatus(ftHandle, &BytesToRead)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }
    if (BytesToRead > 0) {
        if ((ftStatus = FT_Read(ftHandle, inputBuffer, BytesToRead, &BytesReceived)) != FT_OK) { //should be empty
            fterror(ftStatus);
            return -1;
        }
    }

    T.tv_sec = 0;
    nanosleep(&T, NULL);

    outputBuffer[0] = 0xAB;
    if ((ftStatus = FT_Write(ftHandle, outputBuffer, 1, &BytesWritten)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }

    T.tv_sec = 0;
    nanosleep(&T, NULL);

    if ((ftStatus = FT_GetQueueStatus(ftHandle, &BytesToRead)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }
    if ((ftStatus = FT_Read(ftHandle, inputBuffer, BytesToRead, &BytesReceived)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }

    T.tv_sec = 2;
    nanosleep(&T, NULL);

    //  TURN OFF LOOPBACK
    outputBuffer[0] = 0x85;
    if ((ftStatus = FT_Write(ftHandle, outputBuffer, 1, &BytesWritten)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }

    if ((ftStatus = FT_GetQueueStatus(ftHandle, &BytesToRead)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }
    if (BytesToRead > 0) {
        if ((ftStatus = FT_Read(ftHandle, inputBuffer, BytesToRead, &BytesReceived)) != FT_OK) {
            fterror(ftStatus);
            return -1;
        }
    }


    T.tv_sec = 0;
    nanosleep(&T, NULL);


    return 0;
}

void toB(int x) {
    int i,j;
    j=0;
    for (i = 128; i > 0; i >>= 1) bNuber[j++] = ((x & i) == i) ? '1' : '0' ;
    bNuber[j] = '\0';
}


int setup(){

    if ((ftStatus = FT_ResetDevice(ftHandle)) != FT_OK) {
        fterror(ftStatus);
        fprintf(stderr, "ERROR: can not reset\n");
        return -1;
    }
    fprintf(stdout, "SUCCESS (reset)\n");
    if ((ftStatus = FT_SetUSBParameters(ftHandle, 4096, 0)) != FT_OK) {
        fterror(ftStatus);
        fprintf(stderr, "ERROR: can not set usb parameters\n");
        return -1;
    }
    fprintf(stdout, "SUCCESS (usb parameters set)\n");
    if ((ftStatus = FT_SetChars(ftHandle,0,0,0,0)) != FT_OK) {
        fterror(ftStatus);
        fprintf(stderr, "ERROR: can not disable event chars\n");
        return -1;
    }
    fprintf(stdout, "SUCCESS (event chars disabled)\n");
    if ((ftStatus = FT_SetTimeouts(ftHandle, 10, 10)) != FT_OK) {
        fterror(ftStatus);
        fprintf(stderr, "ERROR: can not set timeouts\n");
        return -1;
    }
    fprintf(stdout, "SUCCESS (timeouts set)\n");
    if ((ftStatus = FT_SetLatencyTimer(ftHandle, 2)) != FT_OK) {
        fterror(ftStatus);
        fprintf(stderr, "ERROR: can not set latency\n");
        return -1;
    }
    fprintf(stdout, "SUCCESS (latency set)\n");
    if ((ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x11, 0x13)) != FT_OK) {
        fterror(ftStatus);
        fprintf(stderr, "ERROR: can not set flow controll\n");
        return -1;
    }
    fprintf(stdout, "SUCCESS (flow control disabled)\n");
    if ((ftStatus = FT_SetBitMode(ftHandle, 0,0)) != FT_OK) {
        fterror(ftStatus);
        fprintf(stderr, "ERROR: can not reset MPSSE\n");
        return -1;
    }
    fprintf(stdout, "SUCCESS (MSSPE reset)\n");
    if ((ftStatus = FT_SetBitMode(ftHandle, 0, 2)) != FT_OK) {
        fterror(ftStatus);
        fprintf(stderr, "ERROR: can not turn on MPSSE\n");
        return -1;
    }
    fprintf(stdout, "SUCCESS (MPSSE on)\n");

    T.tv_sec  = 1;
    T.tv_nsec = 0;
    nanosleep(&T, NULL);

	return 0;
}

void usage(char *x){
			printf("USAGE:\n\t%s [-nX] [-short] [-delay]\n\n",x);
			printf("\t\t\tX - id number of the device you want to test\n");
			printf("\t\t\t-short - perform only a short test\n");
			printf("\t\t\t-delay - use a short delay while performing test\n");
}
int main( int argc, char **argv )
{
    int i,j,errorCounter;
	int fast;
    unsigned char c;

	fast = 0;
	shortDelay = 0;
	c = '\0';

	//c = argc>1?argv[1][0]:'\0';

	for (i = 1; i < argc; i++){
		if (argv[i][0] == '-'){
			switch (argv[i][1]){
			case 'n': c = argv[i][2];
				break;
			case 's': fast = 1;
				break;
			case 'd': shortDelay = 1;
				break;
			default: usage(argv[0]); return -2;
			}
		} else {
			usage(argv[0]);
			return -2;
		}
	}


    T.tv_nsec = 100000000;
    T.tv_sec = 0;

    iNumDevs = 0;

    for (i = 0; i < MAX_DEVICES; i++) {
        pcBufLD[i] = cBufLD[i];
    }

    pcBufLD[i] = NULL;
    if ((ftStatus = FT_ListDevices(pcBufLD, &iNumDevs, FT_LIST_ALL | FT_OPEN_BY_SERIAL_NUMBER)) != FT_OK) {
        fprintf(stderr, "ERROR: FT_ListDevices\n");
        return -1;
    } //list devices
    if (iNumDevs < 1) {
        fprintf(stderr, "ERROR: No FTDI devices found\n");
        return -1;
    }
    fprintf(stdout, "Select device:\n");
    for (i = 0; ( (i < MAX_DEVICES) && (i < iNumDevs) ); i++) {
        printf("Device %d (Serial Number: %s\n", i, cBufLD[i]);
    }

    while (c < '0' || c > iNumDevs-1+'0') c = kbhit_getc();

    if ((ftStatus = FT_OpenEx(cBufLD[c-'0'], FT_OPEN_BY_SERIAL_NUMBER, &ftHandle)) != FT_OK) {
        fterror(ftStatus);
        fprintf(stderr, "ERROR: FT_OpenEx (%s)\n", cBufLD[c-'0']);
        return -1;
    }
    fprintf(stdout, "\n======================================================\n");
    fprintf(stdout, "SUCCESS (Connected to the FTDI.%s)\n", cBufLD[c-'0']);	
	
	if (setup()) return -1;

    fprintf(stdout, "START TESTING\n");
    fprintf(stdout, "\n======================================================\n");

    if (syncMPSSE()) return -1;    //sync failed
    if (outputADBUS(0)) return -1; //GPIO failed

    // set ACBUS as input
    outputBuffer[0] = 0x82; //set ACBUS
    outputBuffer[1] = 0x00; //value
    outputBuffer[2] = 0x00; //direction

    if ((ftStatus = FT_Write(ftHandle, outputBuffer, 3, &BytesWritten)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }

    T.tv_sec = 0;
	T.tv_nsec = 1000000000;
    nanosleep(&T, NULL);

    if ((ftStatus = FT_GetQueueStatus(ftHandle, &BytesToRead)) != FT_OK) {
        fterror(ftStatus);
        return -1;
    }

    if (BytesToRead > 0) {
        //fprintf(stderr, "ERROR: queue is not empty (%i)\n", BytesToRead );
        if ((ftStatus = FT_Read(ftHandle, inputBuffer, BytesToRead, &BytesReceived)) != FT_OK) {
            fterror(ftStatus);
            fprintf(stderr, "ERROR: can't read queue\n" );
        }
        //for (i = 0; i< BytesReceived; i++) printf("%i: 0x%X\n", i, inputBuffer[i]);
    }

    T.tv_sec = 0;
	T.tv_nsec = 100000000;
    nanosleep(&T, NULL);

    outputADBUS(0);
    errorCounter = 0;	
		
	if (!fast) for (i=0;i<9;i++) {
        c = 1 << i;
        outputADBUS(c);
        toB(c);
        printf("\t%s\t", bNuber);
        j = readACBUS();
        toB(j);
        printf("%s\n", bNuber);
        
        T.tv_sec = 0;
	    T.tv_nsec = 100000000;
        nanosleep(&T, NULL);


        if (c != j) errorCounter++;
    }

    c = 0xAA;
    outputADBUS(c);
    toB(c);
    printf("\t%s\t", bNuber);
    j = readACBUS();
    toB(j);
    printf("%s\n", bNuber);
    if (c != j) errorCounter++;

	T.tv_sec = 0;
	T.tv_nsec = 100000000;
    nanosleep(&T, NULL);

    c = 0x55;
    outputADBUS(c);
    toB(c);
    printf("\t%s\t", bNuber);
    j = readACBUS();
    toB(j);
    printf("%s\n", bNuber);
    if (c != j) errorCounter++;

	T.tv_sec = 0;
	T.tv_nsec = 100000000;
    nanosleep(&T, NULL);

    c = 0x00;
    outputADBUS(c);
    toB(c);
    printf("\t%s\t", bNuber);
    j = readACBUS();
    toB(j);
    printf("%s\n", bNuber);
    if (c != j) errorCounter++;

	T.tv_sec = 0;
	T.tv_nsec = 100000000;
    nanosleep(&T, NULL);

    c = 0xFF;
    outputADBUS(c);
    toB(c);
    printf("\t%s\t", bNuber);
    j = readACBUS();
    toB(j);
    printf("%s\n", bNuber);
    if (c != j) errorCounter++;

    fprintf(stdout, "Testing complete, errors: %i\n", errorCounter);

    FT_Close(ftHandle);
}
