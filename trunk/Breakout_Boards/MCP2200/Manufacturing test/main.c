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


#include "serial.h"


int modem =FALSE;   //set this to TRUE of testing a MODEM
int verbose = 0;

int print_usage(char * appname)
	{
		//print usage
		printf("\n\n");


        printf(" Usage:              \n");
		printf("   %s  -d device [-s speed]\n ",appname);
		printf("\n");
		printf("   Example Usage:   %s COM1  \n",appname);
		printf("\n");
		printf("           Where: -d device is port e.g.  COM1  \n");
		printf("                  -s Speed is port Speed  default is 115200 \n");
		printf("\n");

        printf("\n");

	    printf("-------------------------------------------------------------------------\n");


		return 0;
	}



int main(int argc, char** argv)
{
  int opt;
  char buffer[256] = {0},IRCode;
  char version[4];
  int fd;
  int res,c;
  int flag=0,firsttime=0;
  char *param_port = NULL;
  char *param_speed = NULL;
  int j,repeat_test =1;   // repeat test several times
    printf("-------------------------------------------------------------------------\n");

    printf("\n");
    printf(" MCP2200 TEST utility v0.1 (CC-0)\n");
    printf(" http://dangerousprototypes.com\n");
    printf("\n");
    printf("-------------------------------------------------------------------------\n");



if (argc <= 1)  {

		print_usage(argv[0]);
		exit(-1);
	}

while ((opt = getopt(argc, argv, "ms:d:")) != -1) {
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
 			case 'm':    //modem debugging for testing
                   modem =TRUE;   // enable modem mode
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




    printf("\n Parameters used: Device = %s,  Speed = %s\n\n",param_port,param_speed);


    flag=0;
    //
    // Loop and repeat test as needed for manufacturing
    //
    //TO DO: add loop here
     printf(" Press Esc to exit, any other key to start the self-test \n\n");
    while(1){

     //pause for space, or ESC to exit

     if (flag==1)
     {
     printf("\n--------------------- Starting a new Self Test-------------------------\n");

     }

     printf("\n Connect TXD and RXD for the self-test \n");

	 while(1){
        Sleep(1);
        if (flag==1){
            flag=0;   //has flag been set to just go testing?
            break;    // proceed with test
         }
        if(kbhit()){
           c = getch();
           if(c == 27){
                printf("\n Esc key hit, stopping...\n");
                printf(" (Bye for now!)\n");
                exit(-1);
            }else {//make space only
                printf("\n Starting test! \n");
                break;
            }
        }
    }


    //
    // Open serial port
    //

	printf(" Opening %s at %sbps...\n", param_port, param_speed);
	fd = serial_open(param_port);
	if (fd < 0) {
		fprintf(stderr, " Error opening serial port\n");
		return -1;
	}

    //
	// Enter binary mode, then enter a protocol mode
	//
	serial_setup(fd,(speed_t) param_speed);


    printf(" Starting self-test...\n");

    serial_write( fd, "T", 1);       //sent as 'v','\0'    //ask version
    Sleep(100);
    res= serial_read(fd, version, 1);  //get version

    if (res>0 && version[0]=='T'){
        printf(" Self test PASSED!!! RX (D1) and TX (D2) LEDs should be ON\n");
    }
    else{
        fprintf(stderr," Error: bad reply (%x), failed self test\n ", version[0]);
    }

        printf(" Press any key to continue...\n");
        while(1){
            serial_write( fd, "TEST", 4);       //sent as 'v','\0'    //ask version
            res= serial_read(fd, version, 4);  //get version
            Sleep(1);
            if(kbhit()){
               c = getch();
                break;
            }
        }

       //close port so they can attach the next Bus Pirate
        serial_close(fd);


        //TODO: Loop back to pause after this
        printf("\n Connect another and press any key to start the self-test again \n");
        printf(" Or hit ESC key to stop and end the test.\n");

        while(1){
        Sleep(1);
        if(kbhit()){
           c = getch();
           if(c == 27){
                printf("\n Esc key hit, stopping...\n");
                printf(" (Bye for now!)\n");
                exit(-1);
            }else {//make space only
                flag=1;  //flag to tell the other loop to bypass another keypress

                break;
            }
        }
    }

  } // while (1)
#define FREE(x) if(x) free(x);
	FREE(param_port);
	FREE(param_speed);
    return 0;
}  //main
