#include "bin.h"

extern int modem;
extern int verbose;
int IRrecord(char *param_fname,int fd)
{
    uint8_t IRCode;
	BOOL no_data_yet=TRUE, file_created=FALSE;
	int res,c;
	int fcounter;
    char buffer[8*1024] = {0};  //   buffer
    char fnameseq[255];
	FILE *fp=NULL;
	int cnt, flag;
    file_created=FALSE;
	no_data_yet=TRUE;

#ifndef _WIN32
    int get_me_out=0;    // 0=no, 1=yes
#else
    char inkey;
    int i;
#endif
    cnt=0;
    c=0;
    flag=0;
    fcounter=0;

		printf(" Recording started.....\n");
        printf(" Press a button on the remote. \n");
        #ifndef _WIN32
        printf("\n Waiting for IR Signal\n");
        #else
        printf("\n Waiting for IR signal  Any key to exit..\n");
        #endif
		while (1) {
			  // get reply
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

                        #ifndef _WIN32
                           // get me out from here and the while loop too
                            get_me_out=1;
                        #else
                                		printf(" Recording started.....\n");
                                        printf(" Press a button on the remote. \n");
                        #endif
                        break;

                   }
			    }
				printf("\n");
				#ifndef _WIN32
				  if (get_me_out==1)
				       break;
				#endif

			}

#ifdef _WIN32

			if (kbhit()){
			    if (modem==TRUE) {  //emulate data-modems are sometimes built into systems and can echo characters
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
                        c = rand() % 1024;
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
#else

				 if (get_me_out==1) {
                      int ch;

                      printf(" Hit 'X' then [enter] at the keyboard to stop, or any other key+[enter] to record again.\n");
                      ch=getc(stdin);
                     // ch=getchar();

                        if ((ch == 'x')||(ch == 'X')){
                                printf("Breaking out..\n");
                                break ;  // break out of while(1) loop
                        }
                       else {
                            get_me_out=0;
                          	printf(" Recording started.....\n");
                            printf(" Press a button on the remote. \n");
                       }

				 }

#endif

	}



    if (file_created==TRUE)  //should error here if file doesn' have ffff at end
        fclose(fp);

	printf("\n Recording ends..\n\n");
	return 0;
}

void IRplay(	char *param_fname,int fd,char *param_delay)
{

	BOOL no_data_yet=TRUE, file_created=FALSE;
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
        printf("\n Entering Player Mode \n");
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
				printf(" \nPress a key to start playing %s or X to exit \n",fnameseq);
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
			}
            if ((delay > 0) && (firstfile++ > 0)){
                if (verbose)
                    printf("....delay is %d miliseconds.\n", atoi(param_delay));
#ifdef _WIN32
  //              Sleep(atoi(param_delay));           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#else
                 sleep(atoi(param_delay));           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#endif
            }

            printf("\n Playing file: %s\n",fnameseq);
             for (i=0;i<5;i++) {
            //send 5x, just to make sure it exit the sump mode too
            serial_write( fd, "\x00", 1);
            }

            serial_write( fd, "S", 1);
            res= serial_read(fd, buffer, sizeof(buffer));
            int comsresult = 0;
            serial_write( fd, "\x03", 1);
            while(!feof(fp)) {
               if ((res=fread(&buffer,sizeof(unsigned char),sizeof(buffer),fp)) > 0) {
                    if (verbose){
                        printf("     Sending %d Bytes to IRToy...\n", res);
                        for(i=0;i<res;i++)
                            printf(" %02X ",(uint8_t) buffer[i]);
                        printf("\n");
                    }
                    comsresult = serial_write( fd, buffer, res);
                    if (comsresult != res){
                        printf("## comms error bytes sent %d <> bytes supposed to send %d\n", comsresult, res);
                        serial_write( fd, "\xFF\xFF\x00\x00\x00\x00\x00", 7);   //trying to 'reset' IR Toy after error
                        exit(-1);
                    }
                    comsresult = 0;
#ifdef _WIN32
   // temporary disabled to alow to pass here.. in win64 param_delay with -1 seems to wait forever. --Need to confirm
   //             Sleep(atoi(param_delay));           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#else
      //          sleep(atoi(param_delay));           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#endif

               }
           }
          // printf(" Reached end of file reached: %s \n",fnameseq);
           fclose(fp);
           fcounter++;
        }

}
