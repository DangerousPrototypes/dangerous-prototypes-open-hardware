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

#include "queue.h"

extern int verbose;

void IRqueue(char *param_fname,int fd)
{
    FILE *fp=NULL;
    FILE *fpq=NULL;
	int res,i;
    char buffer[255] = {0};  //   buffer
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
                                printf(" ######Sending -%d- Bytes to IRToy...\n", res);
                                for(i=0;i<res;i++)
                                    printf(" %02X ",(uint8_t) buffer[i]);
                                printf("\n");
                            }
                            comsresult = serial_write( fd, buffer, res);
                            if (comsresult != res){
                                printf("## comms error bytes sent %d <> bytes supposed to be sent %d\n", comsresult, res);
                                serial_write( fd, "\xFF\xFF\x00\x00\x00\x00\x00", 7);       //trying to 'reset' IR Toy after error
                                exit(-1);
                            }
                            comsresult = 0;
#ifdef _WIN32
                            Sleep(500);                                       //wait 500 milliseconds - for comms to finish, else get errors. Could try smaller, but no delay always fails & locks up the ORToy!
#else
                            sleep(500);                                      //wait 500 milliseconds - for comms to finish, else get errors. Could try smaller, but no delay always fails & locks up the ORToy!
#endif
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
}
