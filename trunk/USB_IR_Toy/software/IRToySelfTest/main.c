/********************************************************************************************************************

Released into the public domain, 2011 Where Labs, LLC (DangerousPrototypes.com/Ian Lesnet)

This work is free: you can redistribute it and/or modify it under the terms of Creative Commons Zero license v1.0

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the License for more details. You should have received a copy of the License along with this program.
If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

Contact Details: http://www.DangerousPrototypes.com
Where Labs, LLC, 208 Pine Street, Muscatine, IA 52761,USA
***********************************************************************************************************************
    Written and maintained by http://dangerousprototypes.com
    WIKI page:    http://dangerousprototypes.com/usb-ir-toy-manual/
    Forum:   http://dangerousprototypes.com/forum/viewforum.php?f=29
***********************************************************************************************************************/


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
    printf(" IR TOY SELF TEST utility v0.1 (CC-0)\n");
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
     printf("\n--------------------- Starting a new IR Toy Self Test-------------------------\n");

     }

     printf("\n Hold the IR Toy very close to something white for the self-test \n");

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

	printf(" Opening IR Toy on %s at %sbps...\n", param_port, param_speed);
	fd = serial_open(param_port);
	if (fd < 0) {
		fprintf(stderr, " Error opening serial port\n");
		return -1;
	}

    //
	// Enter binary mode, then enter a protocol mode
	//
	serial_setup(fd,(speed_t) param_speed);


    printf(" Starting IR TOY self-test...\n");


    serial_write( fd, "\x00", 1);

    printf(" Getting self-test result...\n");
    //Sleep(1000);  // how long to wait to get response?
    //res= serial_read(fd, buffer, sizeof(buffer)); //put reply to buffer ...
    //printf("%s\n",buffer);
    serial_write( fd, "v", 1);       //sent as 'v','\0'    //ask version
    res= serial_read(fd, version, 4);  //get version

    if (res>0){
        printf(" IR Toy version: %s\n",buffer);
    }
    else{
        fprintf(stderr," Error: IR Toy doesn't have a reply for version command\n ");
    }
    //    loop here if needed to send test commnd repeatedly
    for (j=0;j<repeat_test;j++)
    {
       printf("Test no: %i of %i \n",j+1,repeat_test);

    serial_write( fd, "t", 1);   // send test command

    Sleep(1000);
    res= serial_read(fd, buffer, sizeof(buffer));  // get reply


    if (res >0){   //we have a replay
          printf(" IR Toy Self Test Reply: %s\n",buffer);
           printf(" ");
           for(c=0; c<res; c++){
               IRCode=buffer[c];
               printf("%c", IRCode);
            }
            printf("\n");

            if (strncmp(version, buffer, 4)==0) {    // get version
                //get and display version, test is good
                printf("\n\n Test passed! OK! :) \n\n");
            }else{
                printf("\n\n ERROR: test FAILED! :( \n\n");
               //  FAI1 - IR receiver error (error bit 0)
              //  FAI2 - IR LED error (error bit 1)
              //  FAI3 - both errors (error bits 0 & 1)
                // c has character value '1'...'3'
               switch (buffer[3]){
                  case '1':
                          fprintf(stderr," FAI1 - IR receiver error \n ");
                          break;
                  case '2':
                          fprintf(stderr," FAI2 - FAI2 - IR LED error\n ");
                          break;
                  case '3':
                          fprintf(stderr," FAI3 - IR receiver error  and FAI2 - IR LED error\n ");
                          break;
                  default:
                         fprintf(stderr," Invalid response from IR Toy\n ");
                          break;
                } //switch
            }  // fail code

        }else{ // if (res >0)
             printf(" IR Toy did not reply anything.. Please check connections. \n");
        }

    }
       if (firsttime==0){    // run here once and don't say again the next time
        printf(" Press any key to continue...\n");
        firsttime=1;
        while(1){
            Sleep(1);
            if(kbhit()){
               c = getch();
                break;
            }
        }
       }

       //close port so they can attach the next Bus Pirate
        serial_close(fd);


        //TODO: Loop back to pause after this
        printf("\n Connect another IR Toy  and press any key to start the self-test again \n");
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
