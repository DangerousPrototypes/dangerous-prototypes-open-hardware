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
                    sprintf(fnameseq,"%s_%03d.bin",param_fname,fcounter);
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

void IRplay(	char *param_fname,int fd,char *param_delay)
{
  #ifndef _WIN32
  	bool no_data_yet=TRUE, file_created=FALSE;
  #else
	BOOL no_data_yet=TRUE, file_created=FALSE;
  #endif
	int res;
	int fcounter;
    char buffer[255] = {0};  //   buffer
    char fnameseq[255];
	FILE *fp=NULL;
	int i;
    file_created=FALSE;
	no_data_yet=TRUE;
	char inkey;

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
                    printf(" Bin File does not exits. \n");

               break;
            }
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


            int comsresult = 0;
            serial_write( fd, "\x03", 1);
            while(!feof(fp)) {
               if ((res=fread(&buffer,sizeof(unsigned char),sizeof(buffer),fp)) > 0) {
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
                       // serial_write( fd, "\xFF\xFF\x00\x00\x00\x00\x00", 7);   //trying to 'reset' IR Toy after error
                        exit(-1);
                    }
                    else
                        printf(" ok\n");
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
           fcounter++;
        }
     //  printf("pass here \n");
}
