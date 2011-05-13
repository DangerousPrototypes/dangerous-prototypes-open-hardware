/*
    Written and maintained by the IR TOY Project and http://dangerousprototypes.com
    WIKI page:    http://dangerousprototypes.com/usb-ir-toy-manual/
    Forum page:   http://dangerousprototypes.com/forum/viewforum.php?f=29&sid=cdcf3a3177044bc1382305a921585bca
********************************************************************************************************************

Copyright (C) 2011 Where Labs, LLC (DangerousPrototypes.com/Ian Lesnet)

This work is free: you can redistribute it and/or modify it under the terms of Creative Commons Attribution ShareAlike license v3.0

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the License for more details. You should have received a copy of the License along with this program. If not, see <http://creativecommons.org/licenses/by-sa/3.0/>.

Contact Details: http://www.DangerousPrototypes.com
Where Labs, LLC, 208 Pine Street, Muscatine, IA 52761,USA

********************************************************************************************************************* */

#include "bin.h"

extern int modem;
extern int verbose;
int IRrecord(char *param_fname,int fd,float resolution)
{
    uint8_t IRCode;
    double NewIRcode;

    #ifndef _WIN32
    bool no_data_yet=TRUE, file_created=FALSE;
    #else
	BOOL no_data_yet=TRUE, file_created=FALSE;
	#endif
	int res,c;
	int fcounter;
    char buffer[255] = {0};  //   buffer
    char fnameseq[255];
	FILE *fp=NULL;
	int cnt, flag;
    file_created=FALSE;
	no_data_yet=TRUE;

    cnt=0;
    c=0;
    flag=0;
    fcounter=0;

		printf(" Recording started.....\n");
        printf(" Press a button on the remote. \n");
        printf("\n Waiting..any key to exit..\n");

		while (1) {

			while ((res= serial_read(fd, buffer, sizeof(buffer))) > 0){
			    no_data_yet=FALSE;
                if (file_created==FALSE) {
                    // check if fileextension is specified
                    if((strcmpi(param_fname,".bin")) <= 0)
                    {
                        printf("file has bin ");
                        sprintf(fnameseq,"%s",param_fname);
                    }
                    else {
                    sprintf(fnameseq,"%s_%03d.bin",param_fname,fcounter);
                    }

                    printf(" Creating file: %s\n",fnameseq);

                    fp=fopen(fnameseq,"wb");
                    if (fp==NULL) {
                        printf("Cannot open output file: %s \n",param_fname);
                        exit(-1);
                    }
                    else {
                       file_created=TRUE;
                    }
                }

				printf(" IR Toy said: \n");

				for(c=0; c<res; c++){
                   IRCode= (uint8_t) buffer[c];

                   if (IRCode==0xFF){
                         flag=1;
                         cnt++;
                       //  printf("Count = %i\n",cnt);
                   }
                   else {
                       flag=0;
                       cnt=0;
                   }

                   NewIRcode=((double)IRCode*21.3333)/resolution;
                   buffer[c]=(uint8_t)NewIRcode;
                   if(flag==0)
                      printf(" %02X ",(uint8_t)buffer[c]);
                   else
                     printf(" %02X ",(uint8_t)IRCode);

                   if (cnt > 1) {    //close the file
                        buffer[0]=0xFF;
                        buffer[1]=0xFF;
                        fwrite(buffer, 2, 1, fp);
                        printf(" \nwriting %s\n",fnameseq);
                        fclose(fp);
                        file_created=FALSE;
                        cnt=0;
                        flag=0;
                        fcounter++;
                        no_data_yet=TRUE;
                        printf("\n Waiting..  Any key to exit..");
                        break;

                   }

				}
				fwrite(buffer, res, 1, fp);
				printf("\n");

				if( no_data_yet==TRUE) {

				      break;
				}

			}

			if (kbhit()){
			        break;

   			}
	}
    if (file_created==TRUE)  //should error here if file doesn' have ffff at end
        fclose(fp);

	printf("\n Recording ends..\n\n");

	return 0;
}

void IRplay(char *param_fname,int fd,char *param_delay,char *param_buff)
{
  #ifndef _WIN32
  	bool no_data_yet=TRUE, file_created=FALSE, soloplay=FALSE;
  #else
	BOOL no_data_yet=TRUE, file_created=FALSE,soloplay=FALSE;
  #endif
	int res;
	int fcounter;
    char fnameseq[255];
	FILE *fp=NULL;
	int i;
    file_created=FALSE;
	no_data_yet=TRUE;
	soloplay=FALSE;
	char inkey;
    char *buffer;
	int pbuff=atoi(param_buff);
    if ((buffer = (char *)malloc(pbuff * sizeof(char))) == NULL) {
        printf("ERROR: Cannot allocate memory.");
        free(buffer);
        exit(-1);
    }

        printf(" Entering Player Mode \n");
        fcounter=0;
        inkey=0;
        int delay = atoi(param_delay) ;
        int firstfile = 0;


        while (1) {
            // added for single file play.. check existence of file an run it
            // try opening the file if succesful we have to play it singly
            //check filename if exist
              fp=fopen(param_fname,"rb");
              if (fp==NULL) {
                  //we got a sequence then
                sprintf(fnameseq,"%s_%03d.bin",param_fname,fcounter);
                fp=fopen(fnameseq,"rb");
                if (fp==NULL) {
                    if (fcounter > 0)
                        printf(" No more file(s). \n");
                    else
                        printf(" Bin File does not exits. \n");

                   break;
                }

              } else {

                 //got solo play
                 strcpy(fnameseq,param_fname);
                 printf("Playing single file %s\n",fnameseq);
                 soloplay=TRUE;              }


            if (delay< 0){
				printf(" Press a key to start playing %s or X to exit \n",fnameseq);
				while (1) {
				  if(kbhit()) {
					#ifdef _WIN32
                        inkey=getch();
                    # else
                        inkey=getchar_unlocked();
                    # endif

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
                printf(" Auto playing %s with %d seconds delay. \n",fnameseq,atoi(param_delay));

#ifdef _WIN32

                Sleep(atoi(param_delay)*1000);           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#else
                sleep(atoi(param_delay));           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#endif
            }

            int retries;
            int Error_flag=0;
            int comsresult = 0;
            serial_write( fd, "\x03", 1);
            while(!feof(fp)) {
               if ((res=fread(&buffer[0],sizeof(char),pbuff,fp)) > 0) {
                    for (retries=0;retries <5;retries++) {
                        if (verbose){
                            printf(" Sending %d Bytes to IRToy...\n", res);
                            for(i=0;i<res;i++)
                            printf(" %02X ",(uint8_t) buffer[i]);
                            printf("\n");
                        }

                            comsresult = serial_write( fd, buffer, res);
                            printf(" checking comresult....");
                            if (comsresult != res){
                                printf(" \n## comms error bytes sent %d <> bytes supposed to send %d\n", comsresult, res);
                                serial_write( fd, "\xFF\xFF\x00\x00\x00\x00\x00", 7);   //trying to 'reset' IR Toy after error
                                serial_write( fd, "\x03", 1);
                                printf("trying again...%i\n",retries+1);
                                Error_flag=1;

                            }
                            else {
                            printf(" ok\n");
                            Error_flag=0;
                            break;
                            }
                        }
                    if (Error_flag==1){
                       printf("error sending IR code, exiting..");
                       exit(-1);
                    }

                    comsresult = 0;
                    if (delay > 0) {

#ifdef _WIN32
   // temporary disabled to alow to pass here.. in win64 param_delay with -1 seems to wait forever. --Need to confirm
               Sleep(atoi(param_delay)*1000);           //milliseconds auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#else
       //         printf("Sleeping..\n");
             sleep(atoi(param_delay));           //seconds auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#endif
                    }
               }
           }
           printf(" End of file reached: %s \n",fnameseq);

           fclose(fp);
           if (soloplay==TRUE) {
               break;
           }
           fcounter++;
        }
     //  printf("pass here \n");
       //  serial_write( fd, "\xFF\xFF\x00\x00\x00\x00\x00", 7);   //trying to 'reset' IR Toy
}
