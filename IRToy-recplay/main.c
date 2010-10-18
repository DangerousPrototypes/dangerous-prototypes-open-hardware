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

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <windef.h>
#include <time.h>
#include "serial.h"
#define FREE(x) if(x) free(x);

int modem =FALSE;   //set this to TRUE of testing a MODEM
int verbose = 0;

int print_usage(char * appname)
	{

		//print usage
		printf("\n\n");
        printf(" Usage:              \n");
		printf("   %s  -d device [-s speed]\n ",appname);
		printf("\n");
		printf("   Example Usage:   %s  -d COM1 -s speed -f outputfile  -r -p \n",appname);
		printf("\n");
		printf("           Where: -d device is port e.g.  COM1  \n");
		printf("                  -s Speed is port Speed  default is 115200 \n");
		printf("                  -f Output/input file is a base filename for recording/playing pulses  \n");
        printf("                  -r Record into a file indicated in -f parameter (requires -f) \n");
		printf("                  -p means play the file/sequence of file indicated in -f parameter (requires -f \n");
		printf("\n");
		printf("           %s -d com3    - default used is: -s 115200, displays data from IRTOY\n", appname);
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
	char inkey;
	FILE *fp=NULL;
	char fnameseq[80];
	BOOL record=FALSE, play=FALSE,no_data_yet=TRUE,file_created=FALSE;
	printf("-------------------------------------------------------------------------\n");
	printf("\n");
	printf(" IR TOY Recorder/Player utility v0.2 (CC-0)\n");
	printf(" http://dangerousprototypes.com\n");
	printf("\n");
	printf("-------------------------------------------------------------------------\n");
	if (argc <= 1)  {

			print_usage(argv[0]);
			exit(-1);
		}

	while ((opt = getopt(argc, argv, "mrps:d:f:")) != -1) {
       // printf("%c  \n",opt);
		switch (opt) {

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
        } /*
        else {
            //test open file

            fcounter=0;
            sprintf(fnameseq,"%s_%03d.bin",param_fname,fcounter);
            fp=fopen(fnameseq,"wb");

			else {
              //close it
              fclose(fp);
            }
		} */
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

                    inkey=getch();

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
            printf(" Press a key to start playing %s or X to exit \n",fnameseq);
            while (1) {
              if(kbhit()) {
                 inkey=getch();
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
            printf("\n Playing file: %s\n",fnameseq);

            serial_write( fd, "\x03", 1);
            while(!feof(fp)) {
		       if ((res=fread(&buffer,sizeof(unsigned char),sizeof(buffer),fp)) > 0) {
		            printf(" Sending Bytes to IRToy...\n");
		            for(i=0;i<res;i++)
		                printf(" %02X ",(uint8_t) buffer[i]);
		            printf("\n");
                    serial_write( fd, buffer, res);

               }
           }
          // printf(" Reached end of file reached: %s \n",fnameseq);
           fclose(fp);
           fcounter++;
        }

    } // play=true
    printf("\n Thank you for playing with the IRToy. \n");
    serial_close(fd);
	FREE(param_port);
	FREE(param_speed);
	FREE(param_fname);
    return 0;
}  //main
