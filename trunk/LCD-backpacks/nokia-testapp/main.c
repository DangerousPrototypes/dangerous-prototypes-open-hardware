//Image sender for NOKIA

// reference link http://dangerousprototypes.com/forum/index.php?topic=1056.0


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef WIN32

#include <conio.h>
#include <windef.h>
#include <windows.h>
#include <wingdi.h>
#include <WinDef.h>

#else

//#include <curses.h>
#define usleep(x) Sleep(x);

#endif


#include "serial.h"




char *dumpfile;
HANDLE dumphandle;
int modem =FALSE;   // use by command line switch -m to set to true
#define FREE(x) if(x) free(x);

#define MAX_BUFFER 16384   //16kbytes

//structure of bmp header
#ifndef _WIN32
//taken from msdn
typedef struct tagBITMAPFILEHEADER {
  unsigned short bfType;
  unsigned long bfSize;
  unsigned short bfReserved1;
  unsigned short bfReserved2;
  unsigned long bfOffBits;
} BITMAPFILEHEADER;


typedef struct tagBITMAPINFO {
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD bmiColors[1];
} BITMAPINFO;
#endif


#  define BF_TYPE 0x4D42                   // MB
int print_usage(char * appname)
{
		//print usage
		printf("\n");
		printf("\n");
	    printf(" Help Menu\n");
        printf(" Usage:              \n");
		printf("   %s  -p device -f sample.bmp -s speed  \n ",appname);
		printf("\n");
		printf("   Example Usage:   %s -d COM1 -s 115200 -f sample.bmp \n",appname);
		printf("\n");
		printf("           Where: -p device is port e.g.  COM1  \n");
		printf("                  -s Speed is port Speed  default is 115200 \n");
		printf("                  -f Filename of BMP file \n");
		printf("\n");

        printf("-----------------------------------------------------------------------------\n");


		return 0;
}

int main(int argc, char** argv)
{
	   int opt;
	   char buffer[MAX_BUFFER]={0};
	   int fd;
	   int res,c;
	   FILE *fp;
	   char *param_port = NULL;
	   char *param_speed = NULL;
	   char *param_imagefile=NULL;
       BITMAPFILEHEADER header;
       BITMAPINFO *headerinfo;
       int headersize;
       int chunksize=0;
		printf("-----------------------------------------------------------------------------\n");
		printf("\n");
		printf(" BMP image sender for Nokia LCD Backpack \n");
		printf(" http://www.dangerousprototypes.com\n");
		printf("\n");
		printf("-----------------------------------------------------------------------------\n");



		if (argc <= 1)  {
			print_usage(argv[0]);
			exit(-1);
		}


		while ((opt = getopt(argc, argv, "ms:p:f:")) != -1) {

			switch (opt) {
				case 'p':  // device   eg. com1 com12 etc
					if ( param_port != NULL){
						printf("Device/PORT error!\n");
						exit(-1);
					}
					param_port = strdup(optarg);
					break;

				case 'f':      // clock edge
					if (param_imagefile != NULL) {
						printf("Invalid Parameter after Option -f \n");
						exit(-1);
					}
					param_imagefile = strdup(optarg);

					break;
				case 's':
					if (param_speed != NULL) {
						printf("Speed should be set: eg  115200 \n");
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
					exit(-1);
					break;
			}
		}

		if (param_port==NULL){
        printf(" No serial port specified\n");
		print_usage(argv[0]);
 		exit(-1);
     }

		if (param_speed==NULL)
           param_speed=strdup("115200");  //default is 115200kbps

		if (param_imagefile !=NULL) {   //checks is needed to make sure this is a valid bmp file
			//open the Imagefile  file
			   if ((fp = fopen(param_imagefile, "rb")) == NULL) {
				   printf(" Cannot open image file: %s\n",param_imagefile);
				   exit(-1);
			   }
			    if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1){
                    printf(" Invalid Image file.. requires BMP file \n");
                    fclose(fp);
                    exit(-1);
               }
                if (header.bfType != BF_TYPE) {    //BM as signature
                     printf("File: %s is not a valid bitmap file! \n ",param_imagefile);
                     fclose(fp);
                     exit(-1);
               }
               headersize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

               if ((headerinfo = (BITMAPINFO *)malloc(headersize)) == NULL){


               }



		}
        else{
            printf("Error: Image file is required\n");
            exit(-1);
        }
        //close and reopen bmp file
        fclose(fp);
        fp = fopen(param_imagefile, "rb");


		printf(" Opening Port on %s at %sbps, using image file %s \n", param_port, param_speed,param_imagefile);
		fd = serial_open(param_port);
		if (fd < 0) {
			fprintf(stderr, " Error opening serial port\n");
			return -1;
		}

		//setup port and speed
		serial_setup(fd,(speed_t) param_speed);

		if (modem==TRUE){
			printf(" Using modem..\n");
			//send AT commands
			serial_write( fd, "ATI7\x0D\0",5 );
			Sleep(1);
			res= serial_read(fd, buffer, sizeof(buffer));
			printf("\n %s\n",buffer);
		}

        printf(" Offset to image data is %lu bytes\n",header.bfOffBits);

        // i Reset and initialize the LCD.
        //  buffer[0]='i';
	    //	serial_write( fd, buffer,1 );

        //send the command 	//Send 'p' or 'P' send page of image data.
		printf(" Setting image mode \n");
        buffer[0]='P';
		serial_write( fd, buffer,1 );

		printf(" Sending some bytes \n");
        //read first bytes and ignore it (BM)

        //   fread(&buffer,sizeof(unsigned char),2,fp) ;  //enable this if header info is needed

        // jump to where the data is
        fseek(fp,header.bfOffBits,SEEK_SET); //and disable this if above fgets is enabled

        chunksize=6;  //send 4kbytes at a time- should be the buffer size of the backpack

		while(!feof(fp)) {
		    if ((res=fread(&buffer,sizeof(unsigned char),chunksize,fp)) > 0) {
		        char b[3];

		        //the LCD needs 12bit color, this is 24bit
                //we need to discard the lower 4 bits of each byte
                //and pack six half bytes into 3 bytes to send the LCD
                //if we only have one pixel to process (3bytes) instead of 2, then the last should be 0
                //need to do checks for end of data, make this more effecient
                //BMP byte order of BGR...
                //R G
                b[0]=((buffer[2]&0xf0)|((buffer[1]>>4)&0x0f));
                //B R2
                b[1]=(buffer[0]&0xf0)|((buffer[5]>>4)&0x0f);
                //G2 B2
                b[2]=(buffer[4]&0xf0)|((buffer[3]>>4)&0x0f);

				//send to bp
				printf(" sending image data.. ");
				//disable if annoying
				for (c=0; c<res; c++)
                    printf("%02X ", (uint8_t) buffer[c]);

                printf("-> ");

                for(c=0; c<res/2;c++)
                     printf("%02X ", (uint8_t) b[c]);

				printf("\n");

				serial_write( fd, b,chunksize/2 );

			}
		}


	Sleep(1);
	res= serial_read(fd, buffer, sizeof(buffer));
	printf("\n Reply received: %c\n",buffer[0]);

    printf(" Done! :-)\n\n");

    //close lcd


    fclose(fp);
	FREE(param_port);
 	FREE(param_speed);
    FREE(param_imagefile);
    return 0;
 }  //end main()
