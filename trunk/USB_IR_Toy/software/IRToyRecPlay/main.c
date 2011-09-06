/*
    Written and maintained by the IR TOY Project and http://dangerousprototypes.com
    WIKI page:    http://dangerousprototypes.com/usb-ir-toy-manual/
    Forum page:   http://dangerousprototypes.com/forum/viewforum.php?f=29&sid=cdcf3a3177044bc1382305a921585bca
********************************************************************************************************************

Copyright (C) 2011 Where Labs, LLC (DangerousPrototypes.com/Ian Lesnet)

This work is free: you can redistribute it and/or modify it under the terms of Creative Commons Attribution ShareAlike license v3.0

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the License for more details. You should have received a copy of the License along with this program. If not, see <http://creativecommons.org/licenses/by-sa/3.0/>.

Contact Details: http://www.DangerousPrototypes.com

********************************************************************************************************************* */

/* spanner 2010-10 v0.31
 * some minor tidy up of text, finished implementation of a v minimal verbose display option
 * Added two automated / macro play modes to the original play mode:
 * Three play modes:
 * 1. -p f NAME
 *     This is the unchanged method form the origianl release.
 *     Plays all bin files matching NAME_nnn.bin, where nnn starts at 000 and consists of SEQUENTIAL numbers. Stops at first gap in numbers, or last file.
 *     In this mode user MUST press any key, except 'x', to play next file/command.
 * 2. -p f NAME - a nnn
 *     Plays as above, except does NOT wait for any key to be pressed, instead delays nnn miliseconds between sending each file.
 *     500 is recommended as a starting delay. On old P4 computer, no delay always hangs the IRToy (have to uplug & plug in again to reset).
 * 3. -q -f NAME
 *     Play command files listed in the file indicated in -f parameter (requires -f )
 *
 *         Note the file names can be random, ie the numbered sequential rule does not apply.
 *         Sample file content:
 *         sanyo_000.bin
 *         sanyo_010.bin
 *         sanyo_020.bin
 *         sanyo_500.bin
 *
 *         Files can be in a subdirectory if use the following syntax:
 *         .\\dvd\\sanyo_000.bin
 *         .\\dvd\\sanyo_010.bin
 *         .\\dvd\\sanyo_020.bin
 *         .\\dvd\\sanyo_500.bin
 */

// added: enhanced to support continous stream of data from irtoy.
//        support for conversion to OLS format, via commandline option -o
//

//  version 0.06 added the experimental conversion (untested) for other resolution:

//  ( newbytes*newresolution)=(irtoybytes*21.3333)
//  (prontocodes*prontoresolution)=(irtoycodes*21.3333)
//  prontocodes=(irtoycodes*21.3333)/protoresolution
//
// *** new in v0.8
// added -b buffer parameter for playback, e.g -b 32 , to  finetune playback
// added single playing file when an complete filename with extension .bin is specified
// in recording mode, filename with extension bin is overwritten. (overwrites the same file in single mode)

// 6/4/2011   (fix transmit problem)http://dangerousprototypes.com/forum/viewtopic.php?f=29&t=2363
// 6/6/2011    added fix to other file format.

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#ifdef _WIN32
#include <conio.h>
#include <windef.h>
#include <windows.h>

#else

#include <sys/select.h>
#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>

// #define printf printw

#endif

#include "serial.h"
#include "txt.h"
#include "ols.h"
#include "bin.h"
#include "queue.h"


#define FREE(x) if(x) free(x)
#define IRTOY_VERSION "v21"


//int modem =FALSE;   //set this to TRUE of testing a MODEM
int verbose = 0;
char useHandshake = 1;
char  completereq = 1;
char countreq = 1;


int print_usage(char * appname)
{

    //print usage
    printf("\n\n");
    printf(" IRToy version: %s\n", IRTOY_VERSION);
    printf(" Usage:              \n");
    printf("   IRtoy.exe  -d device [-s speed]\n ");
    printf("\n");
    printf("   Example Usage:   IRtoy.exe  -d COM1 -s speed -f outputfile  -r -p \n");
    printf("                    IRtoy.exe  -d COM1 -s speed -f outputfile  -r -p -t -o\n");
    printf("\n");
#ifdef _WIN32
    printf("           Where: -d device is port e.g.  COM1  \n");
#else
    printf("           Where: -d device is port e.g.  /dev/ttyS0  \n");
    printf("           Where: -d device is port e.g.   /dev/ttyACM0  \n");
#endif
    printf("                  -s Speed is port Speed  default is 115200 \n");
    printf("                  -f Output/input file is a base filename for recording/playing");
    printf("                     pulses  \n");
    printf("                  -r Record into a file indicated in -f parameter (requires -f) \n");
    printf("                  -p Play the file/sequence of file indicated in -f parameter");
    printf("                     (requires -f \n");
    printf("                  -n Output and convert codes to other resolutions  (default is 21.33us)\n");
    printf("                     (requires -f \n");
    printf("                  -q Play command files listed in the file indicated in -f");
    printf("                     parameter (requires -f )\n");
    printf("                  -a Optional automatic play (does not wait for keypress). \n");
    printf("                     You must specify delay in milliseconds between sending \n");
    printf("                     each command.\n");
    printf("                  -v Display verbose output, have to specify level 0, 1 etc,\n");
    printf("                     although at present it is only on or off :).\n");
    printf("                  -o Create OLS file based on the filename format \n");
    printf("                     ext. \"ols\" (Requires -f)  \n");
    printf("                  -t Create or Play text files based on the filename format\n");
    printf("                     ext. \"txt\" (Requires -f)  \n");
    printf("                  -h [on] [off] Specify Handshake to be used between player packets\n");
    printf("                  -e Specify End of transmision to be returned when player has transmitted last value\n");
    printf("                  -c Specify Count of bytes received by player\n");
    printf("\n");
#ifdef _WIN32
    printf("           IRtoy.exe -d com3    - default used is: -s 115200, displays data from IRTOY\n");
#else
    printf("           IRtoy.exe -d /dev/ttyS2    - default used is: -s 115200, displays data from IRTOY\n");
    printf("           IRtoy.exe -d /dev/ttyACM0   - default used is: -s 115200, displays data from IRTOY\n");
#endif
    printf("\n");
    printf(" To record and play a text file test_000.txt, use \n");
    printf("           IRtoy.exe -d  com3  -f test -p -t -r\n\n");
    printf(" NOTE:     Except for -q command, Use only the base name of the\n");
    printf("           output/input file, without the numeric sequence:\n");
    printf("           use -f test instead of -f test_000.bin \n");
    printf("           _000 to _999 will be supplied by this utility. \n");
    printf("           You may also edit the resulting text file and replace \n");
    printf("           it with your own values, and should end with FFFF.\n");
    printf("\n\n");

    printf("-------------------------------------------------------------------------\n");

    return 0;
}


int main(int argc, char** argv)
{
    int cnt, i,flag;
    int opt;
    char buffer[4096] = {0};  // 4k buffer

    int fd,fcounter;
    int res,c;
    char *param_port = NULL;
    char *param_speed = NULL;
    char *param_handshake = NULL;
    char *param_fname=NULL;
    char *param_delay=NULL;
    char *param_timer=NULL;
    char *param_buffin = NULL;
    float resolution;

#ifndef _WIN32
    typedef bool BOOL;

#endif
    BOOL record=FALSE, play=FALSE, queue=FALSE, OLS =FALSE,textfile=FALSE;
    char dummy[2];
    int FIRMWARE_VERSION=0;
    printf("-------------------------------------------------------------------------\n");
    printf("\n");
    printf(" IR TOY Recorder/Player utility %s (CC-0)\n", IRTOY_VERSION);
    printf(" http://dangerousprototypes.com\n");
    printf("\n");
    printf("-------------------------------------------------------------------------\n");

    if (argc <= 1)
    {

        print_usage(argv[0]);
        exit(-1);
    }

    while ((opt = getopt(argc, argv, "torpqsvcen:a:d:f:b:h:")) != -1)
    {
        // printf("%c  \n",opt);
        switch (opt)
        {

        case 'v':
            verbose=1;
            break;
        case 'e':
            completereq=1;
            break;
        case 'c':
            countreq = 1;
            break;
        case 'h':
            param_handshake = strdup(optarg);
            if (!strcmp((param_handshake), ("off")))
                useHandshake= 0;
            if (!strcmp((param_handshake), ("on")))
                useHandshake= 1;
            break;
        case 'a':  // delay in miliseconds
            if ( param_delay != NULL)
            {
                printf(" delay error!\n");
                exit(-1);
            }
            param_delay = strdup(optarg);
            // printf("delay %s - %d \n", param_delay, atoi(param_delay));
            break;
        case 'd':  // device   eg. com1 com12 etc
            if ( param_port != NULL)
            {
                printf(" Device/PORT error!\n");
                exit(-1);
            }
            param_port = strdup(optarg);
            break;
        case 's':
            if (param_speed != NULL)
            {
                printf(" Speed should be set: eg  115200 \n");
                exit(-1);
            }
            param_speed = strdup(optarg);

            break;
        case 'f':  // device   eg. com1 com12 etc
            if ( param_fname != NULL)
            {
                printf(" Error: File Name parameter error!\n");
                exit(-1);
            }
            param_fname = strdup(optarg);

            break;
        case 'b':  //buffer receive size, default is 512 - note starting v21, play buffer is 62  bytes only, while read can be adjusted

            if ( param_buffin != NULL)
            {
                printf(" Error: Buffer-In parameter error!\n");
                exit(-1);
            }
            param_buffin = strdup(optarg);

            break;
        case 'n':    //use to change sample timer: default is 21.3333us
            if (param_timer!=NULL)
            {
                printf("Sample timer error!\n");
                exit(-1);
            }
            param_timer=strdup(optarg);
            break;
        case 'p':    //play
            play =TRUE;
            break;
        case 'q':    //play command queue from file (ie macro command list)
            queue =TRUE;
            break;
        case 'r':    //record
            record =TRUE;
            break;
        case 't':    //text file: record or play text file
            textfile =TRUE;
            break;
        case 'o':    //write to OLS format file
            OLS =TRUE;
            break;
        default:
            printf(" Invalid argument %c", opt);
            print_usage(argv[0]);
            //exit(-1);
            break;
        }
    }

//defaults here --------------
    if (param_delay==NULL)
        param_delay=strdup("-1");
    if (param_handshake==NULL)
        useHandshake= 1;

    if (param_port==NULL)
    {
        printf(" No serial port set\n");
        print_usage(argv[0]);
        exit(-1);
    }
    if (param_timer==NULL)
    {
        param_timer=strdup("21.3333");
    }

    if (param_buffin==NULL)
    {
        param_buffin=strdup("512");  //default buffer size for recieving
    }
    if (param_speed==NULL) {
        param_speed=strdup("115200");    //default port speed
        // printf("Speed: %s\n",param_speed);
    }
    if (record==TRUE)
    {
        if ((param_fname==NULL) && (record==TRUE))     //either 'r' or 'p' or both should be used  witout filename it will just display it
        {
            printf(" Error: -f Parameter is required\n");
            print_usage(argv[0]);
            exit(-1);
        }
    }
    if(OLS==TRUE)    // -f must be specified + r or p  or both
    {
        if (param_fname==NULL)
        {
            printf(" Error: -f Parameter is required, ignoring OLS writing.\n");
            OLS=FALSE;
        }
    }
    resolution=atof(param_timer);
    printf(" Opening IR Toy on %s at %sbps...\n", param_port, param_speed);

    fd = serial_open(param_port);
    if (fd < 0)
    {
        printf(" Error opening serial port\n");
        return -1;
    }
    #ifdef _WIN32
    serial_setup(fd, (unsigned long) param_speed);
    #else
      serial_setup(fd, strtoul(param_speed,NULL,10));
    #endif
   // printf(" Pass serial_setup\n");

    cnt=0;
    serial_write( fd, "\xFF", 1);
    //printf(" Pass write 0xff 1\n");
    serial_write( fd, "\xFF", 1);
       //printf(" Pass write 0xff 1\n");
    for (i=0; i<5; i++)
    {
        //send 5x, just to make sure it exit the sump mode too
        serial_write( fd, "\x00", 1);
    }
      // printf(" Pass write 0x00 x5\n");
    while (1)
    {
        serial_write( fd, "v", 1);
           //printf(" Pass write v\n");
        res= serial_read(fd, buffer, sizeof(buffer));  //get version
        if (res > 0)
        {

            printf(" IR Toy Firmware version: ");
            for (i=0; i<res; i++)
            {
                printf("%c",buffer[i]);
            }
            buffer[i]='\0';
            printf("\n");
            break;
        }
        else
        {
            cnt++;
            if (cnt > 10)
            {
                printf(" Cannot Read Firmware Version. \n");

                break;
            }


        }
    }

    cnt=0;
    // strict checking is needed because sometimes there are garbages.
    if (res==4)    //restric firmware to version greater than 14
    {
        for (i=2; i< res; i++)
        {
            dummy[cnt++]=buffer[i];
        }
        dummy[cnt]='\0';
        FIRMWARE_VERSION=atoi(dummy);
    }
    else
    {
        printf("\n");
        printf(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        printf(" Found Garbage data when reading the firmware version.. \n");
        printf(" Please re-start this utility again \n" );
        printf(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        printf("\n");
        return -1;
    }


    if (FIRMWARE_VERSION < 20)
    {
        printf(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        printf(" This utility is for firmware version 20 and up.\n");
        printf(" Please update your IR TOY firmware version %i to the latest firmware.\n",FIRMWARE_VERSION);
        printf(" See documentation and firmware update procedures at \n");
        printf(" http://dangerousprototypes.com/docs/USB_Infrared_Toy#Firmware\n");
        printf(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        return -1;

    }

    cnt=0;
    while(1)
    {
        printf(" Entering IR sample mode .... ");
        for (i=0; i<5; i++)
        {
            //send 5x, just to make sure it exit the sump mode too
            serial_write( fd, "\x00", 1);
        }
        printf(" Done. \n");

        serial_write( fd, "S", 1);
        res= serial_read(fd, buffer, sizeof(buffer));  //get protocol version

        if (res >= 3)
        {
            if (buffer[0]=='S')
            {
                printf(" IR Toy Protocol version: ");
                for (i=0; i<3; i++)
                    printf("%c",buffer[i]);
                printf("\n");

                break;
            }
            else   //got garbage, retry again
            {
                for (i=0; i< 512; i++)
                {
                    buffer[i]='\0';   // assigne null
                }

            }

        }
        else
        {
            cnt++;
            if (cnt> 10)
            {
                printf(" Error: IR Toy doesn't have a reply\n ");

                exit(-1);
            }
            else
            {
                serial_write( fd, "\xFF", 1);
                serial_write( fd, "\xFF", 1);
            }
        }

    }

    printf(" Current sample timer Resolution: %sus\n",param_timer);

    cnt=0;
    c=0;
    flag=0;
    fcounter=0;

    if (textfile == FALSE)
    {
        if(record==TRUE)  //open the file
        {
            printf(" Recording at Resolution= %fus\n",resolution);

            if ( IRrecord(param_fname,fd,resolution,param_buffin)==-1)
            {
                FREE(param_port);
                FREE(param_speed);
                FREE(param_fname);
                exit(-1);
            }
        }

        if (play==TRUE)
        {
            IRplay(	param_fname,fd,param_delay,param_buffin);

        } // play=true
    }
    if (textfile==TRUE)
    {
        if (record==TRUE)
        {
            IRtxtrecord(param_fname);

        }

        if (play==TRUE)
        {
            IRtxtplay(param_fname,fd,param_delay);
        }

    }
    if (OLS==TRUE)
    {

        create_ols(param_fname);

    }  //OLS==true

    if (queue==TRUE)
    {

        IRqueue(param_fname,fd);
    } // queue=true

    #ifdef _WIN32
    Sleep(2000);     // windows: Sleep for 2000 milliseconds
    #else
    sleep(2);    // linux: sleep for 2 secs
    #endif
    serial_close(fd);
    FREE(param_port);
    FREE(param_speed);
    FREE(param_fname);
    FREE(param_buffin);
    printf("\n Thank you for playing with the IR Toy! Utility version: %s. \n", IRTOY_VERSION);

    return 0;
}  //main
