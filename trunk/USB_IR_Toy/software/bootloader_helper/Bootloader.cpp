    // BootLoader.cpp : Defines the entry point for the console application.
    //
//By Dukey/Ian Davis: http://dangerousprototypes.com/forum/viewtopic.php?f=29&t=2721&p=26627#p26580
//GPL
    #include <stdio.h>
    #include <stdlib.h>
    #include <Windows.h>

    int main(int argc, char* argv[]) {

       //===================
       char   comPort[16];
       HANDLE   hComPort;
       UCHAR   buffer[2];
       DWORD   bytesWritten;
       DCB      dcb = {0};
       //===================

       if(argc<2) {
          return 0;
       }

       sprintf(comPort,"\\\\.\\COM%i",atoi(argv[1]));

       //
       // Open Port
       //
       hComPort = CreateFile(comPort,GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

       if(hComPort==INVALID_HANDLE_VALUE) {
          printf("Could not open com port.\n");
          return 0;
       }

       //
       // Setup Port
       //
       dcb.DCBlength   = sizeof(dcb);
       dcb.BaudRate   = 115200;
       dcb.ByteSize   = 8;
       dcb.Parity      = NOPARITY;
       dcb.StopBits   = ONESTOPBIT;

       if(!SetCommState(hComPort, &dcb)) {
          printf("Could not set com port properties.\n");
          CloseHandle(hComPort);
          return 0;
       }
       
       buffer[0] = 0;
       buffer[1] = 0;

       WriteFile(hComPort,buffer,2,&bytesWritten,NULL);

       Sleep(100);

       buffer[0] = '$';
       WriteFile(hComPort,buffer,1,&bytesWritten,NULL);

       CloseHandle(hComPort);
             
       return 0;
    }
