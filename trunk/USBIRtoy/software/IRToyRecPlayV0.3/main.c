/*
 * This file is part of the Bus Pirate project (http://code.google.com/p/the-bus-pirate/).
 *
 * Written and maintained by the Bus Pirate project and http://dangerousprototypes.com
 *
 * To the extent possible under law, the project has
 * waived all copyright and related or neighboring rights to Bus Pirate. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <time.h>
#ifdef _WIN32
#include <conio.h>
#include <windef.h>
#include <windows.h>
#else
#include <sys/select.h>
#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>

//#define int BOOL

#endif

#include "serial.h"
#define FREE(x) if(x) free(x);#define IRTOY_VERSION "v0.031"




int modem =FALSE;   //set this to TRUE of testing a MODEM
int verbose = 0;

#ifndef _WIN32
static int peek = -1;
static struct termios orig,new;


int kbhit()
{

  char ch;
  int nread;

  if(peek != -1) return 1;
  new.c_cc[VMIN]=0;
  tcsetattr(0, TCSANOW, &new);
  nread = read(0,&ch,1);
  new.c_cc[VMIN]=1;
  tcsetattr(0, TCSANOW, &new);

  if(nread == 1) {
   peek = ch;
   return 1;
  }

  return 0;
}

int readch()
{

  char ch;

  if(peek != -1) {
    ch = peek;
    peek = -1;
    return ch;
  }

  read(0,&ch,1);
  return ch;
}



#endif
int print_usage(char * appname)
	{

		//print usage
		printf("\n\n");
       printf(" IRToy version: %s\n", IRTOY_VERSION);
        printf(" Usage:              \n");
		printf("   %s  -d device [-s speed]\n ",appname);
		printf("\n");
		printf("   Example Usage:   %s  -d COM1 -s speed -f outputfile  -r -p \n",appname);
		printf("\n");
#ifdef _WIN32
		printf("           Where: -d device is port e.g.  COM1  \n");
#else
		printf("           Where: -d device is port e.g.  /dev/ttyS0  \n");
#endif
		printf("                  -s Speed is port Speed  default is 115200 \n");
		printf("                  -f Output/input file is a base filename for recording/playing pulses  \n");
        printf("                  -r Record into a file indicated in -f parameter (requires -f) \n");
		printf("                  -p Play the file/sequence of file indicated in -f parameter (requires -f \n");
		printf("                  -q Play command files listed in the file indicated in -f parameter (requires -f )\n");
		printf("                  -a Optional automatic play (does not wait for keypress). \n\t\t\tYou must specify delay in milliseconds between sending each command.\n");
		printf("                  -v Display verbose output, have to specify level 0, 1 etc, although at present it is only on or off :).\n");
		printf("\n");
#ifdef _WIN32
		printf("           %s -d com3    - default used is: -s 115200, displays data from IRTOY\n", appname);
#else
		printf("           %s -d /dev/ttyS2    - default used is: -s 115200, displays data from IRTOY\n", appname);

#endif
		printf("\n");

        printf("\n");

	    printf("-------------------------------------------------------------------------\n");


		return 0;
	}


int main(int argc, char** argv)
{
	int cnt, i,flag;
	int opt;
	char buffer[256] = {0};
	uint8_t IRCode;
	int fd,fcounter;
	int res,c;
	char *param_port = NULL;
	char *param_speed = NULL;
	char *param_fname=NULL;
	char *param_delay=NULL;
	char inkey;
	FILE *fp=NULL;
	char fnameseq[80];
	#ifndef _WIN32
	typedef bool BOOL;
	#endif
	BOOL record=FALSE, play=FALSE, queue=FALSE, no_data_yet=TRUE, file_created=FALSE;

	#ifndef _WIN32
//just to get the display need required on linux
  tcgetattr(0, &orig);
  new = orig;
  new.c_lflag &= ~ICANON;
  new.c_lflag &= ~ECHO;
  new.c_lflag &= ~ISIG;
  new.c_cc[VMIN] = 1;
  new.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &new);

#endif

	printf("-------------------------------------------------------------------------\n");
	printf("\n");
	printf(" IR TOY Recorder/Player utility %s (CC-0)\n", IRTOY_VERSION);
	printf(" http://dangerousprototypes.com\n");
	printf("\n");
	printf("-------------------------------------------------------------------------\n");
	if (argc <= 1)  {

			print_usage(argv[0]);
			exit(-1);
		}

	while ((opt = getopt(argc, argv, "mrpqsv:a:d:f:")) != -1) {
       // printf("%c  \n",opt);
		switch (opt) {

			case 'v':  // verbose output
                verbose=-1;
				break;
			case 'a':  // delay in miliseconds
				if ( param_delay != NULL){
					printf(" delay error!\n");
					exit(-1);
				}
				param_delay = strdup(optarg);
				//printf("delay %s - %d \n", param_delay, atoi(param_delay));
				break;
			case 'd':  // device   eg. com1 com12 etc
				if ( param_port != NULL){
					printf(" Device/PORT error!\n");
					exit(-1);
				}
				param_port = strdup(optarg);
				break;
            case 's':
				if (param_speed != NULL) {
					printf(" Speed should be set: eg  115200 \n");
					exit(-1);
				}
				param_speed = strdup(optarg);

				break;
            case 'f':  // device   eg. com1 com12 etc
				if ( param_fname != NULL){
					printf(" Error: File Name parameter error!\n");
					exit(-1);
				}
				param_fname = strdup(optarg);

				break;
 			case 'm':    //modem debugging for testing
                   modem =TRUE;   // enable modem mode, for testing only
				break;
            case 'p':    //play
                play =TRUE;   // enable modem mode
				break;
            case 'q':    //play command queue from file (ie macro command list)
                queue =TRUE;
				break;
			case 'r':    //record
                record =TRUE;   // enable modem mode
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
    if (param_port==NULL){
        printf(" No serial port set\n");
		print_usage(argv[0]);
		exit(-1);
    }

    if (param_speed==NULL)
		param_speed=strdup("115200");
    if (record==TRUE){

        if ((param_fname==NULL) && (record==TRUE)){    //either 'r' or 'p' or both should be used  witout filename it will just display it
            printf(" Error: -f Parameter is required\n");
            print_usage(argv[0]);
            exit(-1);
        }
    }
  	printf(" Opening IR Toy on %s at %sbps...\n", param_port, param_speed);
	fd = serial_open(param_port);
	if (fd < 0) {
		fprintf(stderr, " Error opening serial port\n");
		return -1;
	}
    serial_setup(fd,(speed_t) param_speed);
    printf(" Entering IR sample mode ....\n ");
    for (i=0;i<5;i++) {
        //send 5x, just to make sure it exit the sump mode too
        serial_write( fd, "\x00", 1);
    }

    serial_write( fd, "S", 1);
    res= serial_read(fd, buffer, sizeof(buffer));  //get version

    if (res>0){
        printf("IR Toy Protocol version: ");
        for (i=0;i<res;i++)
            printf(" %c ",buffer[i]);
        printf("\n");
    }
    else{
        fprintf(stderr," Error: IR Toy doesn't have a reply\n ");
        exit(-1);
    }
    cnt=0;
    c=0;
    flag=0;
    fcounter=0;
    if(record==TRUE){ //open the file
        file_created=FALSE;
		no_data_yet=TRUE;
		printf(" Recording started.....\n");
        printf(" Press a button on the remote. \n");
        printf("\n Waiting..any key to exit..\n");
		while (1) {
			res= serial_read(fd, buffer, sizeof(buffer));  // get reply
			if (res > 0){

			    no_data_yet=FALSE;
                if (file_created==FALSE) {
                    sprintf(fnameseq,"%s_%03d.bin",param_fname,fcounter);
                    printf(" Creating file: %s\n",fnameseq);
                    fp=fopen(fnameseq,"wb");
                    if (fp==NULL) {
                        printf("Cannot open output file: %s \n",param_fname);
                        FREE(param_port);
                        FREE(param_speed);
                        FREE(param_fname);
                        exit(-1);
                    }
                    else {
                       file_created=TRUE;
                    }
                }

			    fwrite(buffer, res, 1, fp);
				printf(" IR Toy said: \n");
				for(c=0; c<res; c++){
                   IRCode= (uint8_t) buffer[c];
                   printf(" %02X ",(uint8_t)IRCode);

                   if (IRCode==0xFF){
                         flag=1;
                         cnt++;
                       //  printf("Count = %i\n",cnt);
                   }
                   else {
                       flag=0;
                       cnt=0;
                   }

                   if (cnt > 1) {    //close the file
                        printf(" \nwriting %s\n",fnameseq);
                        fclose(fp);
                        file_created=FALSE;
                        cnt=0;
                        flag=0;
                        fcounter++;
                        no_data_yet=TRUE;
                        printf("\n Waiting..any key to exit..");
                   }
				}
				printf("\n");

			}



			if (kbhit()){
			    if (modem==TRUE) {  //emulate data
#ifdef _WIN32
                  inkey=getch();
#else
                  inkey = fgetc(stdin);
#endif

                   if (inkey=='h') {
                        strncpy(buffer,"HELLO From IRTOY ",17);
                        serial_write( fd, buffer, 17);
                        buffer[0]=0xFF;
                        buffer[1]=0xFF;
                        serial_write( fd, buffer, 2);
                    }
                    else if (inkey=='r') {  //random
                        srand ( time(NULL) );
                        c = rand() % 16;
                        for (i=0; i< c;i++) {
                            buffer[0]=0x00;
                            buffer[1]=rand() % 256;  //0-255
                            serial_write( fd, buffer, 2);
                        }
                        buffer[0]=0xFF;
                        buffer[1]=0xFF;
                        serial_write( fd, buffer, 2);

                    }
                    else
                        break;
			    }
			    else {
                    break;
			    }
			}


		}
    if (file_created==TRUE)  //should error here if file doesn' have ffff at end
        fclose(fp);

	printf("\n Recording ends..\n\n");
	}

    if (play==TRUE){

        //check filename if exist
        printf(" Entering Player Mode \n");
        fcounter=0;
        inkey=0;
        int delay = atoi(param_delay) ;
        int firstfile = 0;
        while (1) {
            sprintf(fnameseq,"%s_%03d.bin",param_fname,fcounter);
            fp=fopen(fnameseq,"rb");
            if (fp==NULL) {
                if (fcounter > 0)
                    printf(" No more file(s). \n");
                else
                    printf(" File does not exits. \n");

               break;
            }
            if (delay< 0){
				printf(" Press a key to start playing %s or X to exit \n",fnameseq);
				while (1) {
				  if(kbhit()) {
#ifdef _WIN32
					  inkey=getch();
#else
					  inkey = fgetc(stdin);
#endif

					 if ((inkey=='x') || (inkey=='X')) {
						 break;
					 }
					 else
						break;

				  }

				}
				if (inkey=='x'|| inkey=='X'){
					  break;
				}
			}
            if ((delay > 0) && (firstfile++ > 0)){
                if (verbose)
                    printf("....delay is %d miliseconds.\n", atoi(param_delay));
                Sleep(atoi(param_delay));           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
            }

            printf("\n Playing file: %s\n",fnameseq);

            serial_write( fd, "\x03", 1);
            while(!feof(fp)) {
		       if ((res=fread(&buffer,sizeof(unsigned char),sizeof(buffer),fp)) > 0) {
                    if (verbose){
						printf(" Sending Bytes to IRToy...\n");
						for(i=0;i<res;i++)
							printf(" %02X ",(uint8_t) buffer[i]);
						printf("\n");
					}
                    serial_write( fd, buffer, res);

               }
           }
          // printf(" Reached end of file reached: %s \n",fnameseq);
           fclose(fp);
           fcounter++;
        }

    } // play=true
    if (queue==TRUE){
        FILE *fpq=NULL;

        //check filename if exist
        printf(" Entering Queue mode: play commands from file\n");

        fpq=fopen(param_fname,"r");
        if (fpq==NULL)
            printf(" Queue command file does not exist. \n");
        else {
            char cmdfile[255];
            int len = 0;
            while (fgets(cmdfile, sizeof(cmdfile), fpq )){
                len = strlen(cmdfile);
                if( cmdfile[len-1] == '\n' )
                    cmdfile[len-1] = 0;
                fp=fopen(cmdfile,"rb");
                if (fp==NULL) {
                    printf("    Comand file %s does not exist. \n", cmdfile);
                    break;
                }
                else{
                    printf("      Sending command file %s \n", cmdfile);
                    serial_write( fd, "\x03", 1);
                    int comsresult = 0;
                    while(!feof(fp)) {
                       if ((res=fread(&buffer,sizeof(unsigned char),sizeof(buffer),fp)) > 0) {
                            if (verbose){
                                printf(" Sending Bytes to IRToy...\n");
                                for(i=0;i<res;i++)
                                    printf(" %02X ",(uint8_t) buffer[i]);
                                printf("\n");
                            }
                            comsresult = serial_write( fd, buffer, res);
                            if (comsresult != res){
                                printf("comms error level 2 %d\n", comsresult);
                                break;
                            }
                            comsresult = 0;
                            //wait 500 milliseconds - for comms to finish, else get errors. Could try smaller, but no delay always fails & locks up the ORToy!
                            Sleep(500);             //check if same on unix, ....
                       }
                    }
                    if(comsresult){
                        printf("comms error level 1 %d\n", comsresult);
                        break;
                    }
                }
                fclose(fp);
            }
        }
        fclose(fpq);
    } // queue=true

    printf("\n Thank you for playing with the IRToy version: %s. \n", IRTOY_VERSION);
    serial_close(fd);
	FREE(param_port);
	FREE(param_speed);
	FREE(param_fname);
    return 0;
}  //main
