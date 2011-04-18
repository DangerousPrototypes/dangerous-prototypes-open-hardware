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

/*

Here's another self-test we need:
http://www.whereisian.com/files/j-lcd-backpack.swf
http://www.whereisian.com/files/j-lcd-backpack_001.swf

Strings are:
fe 00 fe 42 00 fe 58 fe 48 fe 53
"Backlight should be ON :)"


Here's the wiki with a little more info on the procedure we want to follow:
http://dangerousprototypes.com/docs/PIC_LCD_Backpack_manufacturing_resources

Please make a 'manufacturing' folder and check the soure/compiled code in here:
http://code.google.com/p/dangerous-prototypes-open-hardware/source/browse/#svn%2Ftrunk%2FLCD-backpacks%2FHD44780-USB-PIC

*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <windef.h>


#include "serial.h"


//define the Matrix Orbital command set
#define MATRIX_ORBITAL_COMMAND   "\xFE"     //0xFE
#define BACKLIGHT_ON             "\x42"     //0x42    1 parameter (minutes 00=forever)
#define BACKLIGHT_OFF            "\x46"     //0x46
#define CLEAR                    "\x58"      //0x58
#define HOME                     "\x48"     //0x48
#define POSITION                 "\x47"     //0x47    2 parameters (col, row)
#define UNDERLINE_CURSER_ON      "\x4A"     //0x4A
#define UNDERLINE_CURSER_OFF     "\x4B"     //0x4B
#define BLOCK_CURSER_ON          "\x53"     //0x53
#define BLOCK_CURSER_OFF         "\x54"     //0x54
#define BACKLIGHT_BRIGHTNESS     "\x98"     //0x98     1 parameter (brightness)
#define CUSTOM_CHARACTER         "\x4E"     //0x4E     9 parameters (character #, 8 byte bitmap)
#define NETWORK_CONFIG           "\x99"     //0x99     show node connection details (custom)
#define LCD_RESET_INIT           "\x00"     //0x00     reset and init the lcd
#define EXIT                     "\x9A"      //0x9A     exit Matrix orbital mode and resume screeensaver

#define DISPLAY_TEXT             "Backlight should be ON :)"

int modem =FALSE;                           //set this to TRUE of testing a MODEM not used
int verbose = 0;

int print_usage(char * appname)
	{
		//print usage
		printf("\n\n");


        printf(" Usage:              \n");
		printf("   %s  -p port [-s speed]\n ",appname);
		printf("\n");
		printf("   Example Usage:   %s COM1  \n",appname);
		printf("\n");
		printf("           Where: -d Port is port name e.g.  COM1  \n");
		printf("                  -s Speed is port Speed  default is 115200 \n");
		printf("\n");

        printf("\n");

	    printf("-------------------------------------------------------------------------\n");


		return 0;
	}



int main(int argc, char** argv)
{
	int opt;
	int fd;
	int c;
	int flag=0,firsttime=0;
	char *param_port = NULL;
	char *param_speed = NULL;
	int j,repeat_test =1;   // repeat test several times

	printf("-------------------------------------------------------------------------\n");
	printf("\n");
	printf(" LCD Backpack Manufacturing Test utility v0.1 (CC-0)\n");
	printf(" http://dangerousprototypes.com\n");
	printf("\n");
	printf("-------------------------------------------------------------------------\n");



	if (argc <= 1)  {

		print_usage(argv[0]);
		exit(-1);
	}

	while ((opt = getopt(argc, argv, "s:p:")) != -1) {
		switch (opt) {

			case 'p':  // device   eg. com1 com12 etc
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

		if (param_speed==NULL) {
			  param_speed=strdup("115200");
		}

		printf("\n Parameters used: Device = %s,  Speed = %s\n\n",param_port,param_speed);

		flag=0;
		//
		// Loop and repeat test as needed for manufacturing
		//

		 printf(" Press Esc to exit, any other key to start the self-test \n\n");
		while(1){
		 //pause for space, or ESC to exit
		 if (flag==1)
		 {
			printf("\n --------------- Starting a new LCD Backpack Test-------------\n");
		 }

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
					exit(0);
				}else {//make space only
					printf("\n Starting test! \n");
					break;
				}
			}
		}
		//
		// Open serial port
		//
		printf(" Opening LCD Back pack Test on %s at %sbps...\n", param_port, param_speed);
		fd = serial_open(param_port);
		if (fd < 0) {
			fprintf(stderr, " Error opening serial port\n");
			return -1;
		}
		serial_setup(fd,(speed_t) param_speed);
		printf(" Starting LCD Backpack Test ...\n");

		for (j=0;j<repeat_test;j++)
		{
			/*
			printf(" Test no: %i of %i \n",j+1,repeat_test);
			serial_write( fd, MATRIX_ORBITAL_COMMAND, 1);   // send Orbital command
			serial_write( fd, LCD_RESET_INIT,1);            //reset command
			Sleep(1);
			serial_write( fd, MATRIX_ORBITAL_COMMAND, 1);   // send Orbital command
			serial_write( fd, BACKLIGHT_ON,1);              // Backlight on
			serial_write( fd, "\x00", 1);                   // time=00= forever
			Sleep(1);
			serial_write( fd, MATRIX_ORBITAL_COMMAND, 1);   // send Orbital command
			serial_write( fd, CLEAR,1);                     //clear screen
			Sleep(1);
			serial_write( fd, MATRIX_ORBITAL_COMMAND, 1);   // send Orbital command
			serial_write( fd, HOME,1);                      // Home
			Sleep(1);
			serial_write( fd, MATRIX_ORBITAL_COMMAND, 1);   // send Orbital command
			serial_write( fd, BLOCK_CURSER_ON,1);           // Block Cursor On
            Sleep(1);
            serial_write( fd,DISPLAY_TEXT,sizeof(DISPLAY_TEXT));  //Write to LCD the text
             */
             serial_write( fd, "\xfe\x00\xfe\x42\x00\xfe\x58\xfe\x48\xfe\x53",11);

             serial_write( fd, "Backlight should be ON :)",25);
             printf("\n You should see the text below displayed on the LCD: \n\n");
             printf("\n  %s \n\n\n",DISPLAY_TEXT);


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
		printf("\n Connect another LCD Backpack Board \n and press any key to start testing again \n");
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
