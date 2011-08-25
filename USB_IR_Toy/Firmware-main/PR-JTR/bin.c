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
extern char useHandshake;
extern char countreq;
extern char completereq;

int IRrecord(char *param_fname,int fd,float resolution)
{
    uint16_t IRCode;
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

    while (1)
    {

        while ((res= serial_read(fd, buffer, sizeof(buffer))) > 0)
        {
            if (res % 2)
                exit(-1); // JTR IRTOY should ALWAYS return even number of BYTE values

            no_data_yet=FALSE;
            if (file_created==FALSE)
            {
                // check if fileextension is specified
                if((strcmpi(param_fname,".bin")) <= 0)
                {
                    printf(" file has bin ");
                    sprintf(fnameseq,"%s",param_fname);
                }
                else
                {
                    sprintf(fnameseq,"%s_%03d.bin",param_fname,fcounter);
                }

                printf(" Creating file: %s\n",fnameseq);

                fp=fopen(fnameseq,"wb");
                if (fp==NULL)
                {
                    printf(" Cannot open output file: %s \n",param_fname);
                    exit(-1);
                }
                else
                {
                    file_created=TRUE;
                }
            }

            printf(" IR Toy said: \n");

            for(c=0; c<res; c+=2)
            {
                IRCode= (uint8_t) buffer[c];
                IRCode |= (buffer[c +1] << 8);

                if (IRCode==0xFFFF)
                {
                    flag=1;
                    printf(" %02X ",(uint8_t)IRCode);
                    printf(" %02X ",(uint8_t)((IRCode >> 8) & 0xFF));
                    buffer[0]=0xFF;
                    buffer[1]=0xFF;
                    fwrite(buffer, 2, 1, fp);
                    printf("\n writing %s\n",fnameseq);
                    fclose(fp);
                    file_created=FALSE;
                    cnt=0;
                    flag=0;
                    fcounter++;
                    no_data_yet=TRUE;
                    printf("\n Waiting..  Any key to exit..");
                    break;
                }
                else
                {
                    flag=0;
                    NewIRcode=((double)IRCode*21.3333)/resolution;
                    buffer[c]=(uint8_t)NewIRcode;
                    buffer[c+1]=(uint8_t)((NewIRcode) / 256) & 0xFF;
                    printf(" %02X ",(uint8_t)buffer[c]);
                    printf(" %02X ",(uint8_t)buffer[c + 1]);
                }
            }
            if (flag == 0)
            {
                fwrite(buffer, res, 1, fp);
            }
            printf("\n");

            if( no_data_yet==TRUE)
            {
                break;
            }
        }

        if (kbhit())
        {
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
    pbuff=64;   // added for 0x07 transmit 0x03 now obsolete
    if ((buffer = (char *)malloc(pbuff * sizeof(char))) == NULL)
    {
        printf("ERROR: Cannot allocate memory.");
        free(buffer);
        exit(-1);
    }

    printf(" Entering Player Mode \n");
    fcounter=0;
    inkey=0;
    int delay = atoi(param_delay) ;
    int firstfile = 0;


    while (1)
    {
        // added for single file play.. check existence of file an run it
        // try opening the file if succesful we have to play it singly
        //check filename if exist
        fp=fopen(param_fname,"rb");
        if (fp==NULL)
        {
            //we got a sequence then
            sprintf(fnameseq,"%s_%03d.bin",param_fname,fcounter);
            fp=fopen(fnameseq,"rb");
            if (fp==NULL)
            {
                if (fcounter > 0)
                    printf(" No more file(s). \n");
                else
                    printf(" Bin File does not exits. \n");

                break;
            }

        }
        else
        {

            //got solo play
            strcpy(fnameseq,param_fname);
            printf("Playing single file %s\n",fnameseq);
            soloplay=TRUE;
        }


        if (delay< 0)
        {
            printf(" Press a key to start playing %s or X to exit \n",fnameseq);
            while (1)
            {
                if(kbhit())
                {
#ifdef _WIN32
                    inkey=getch();
# else
                    inkey=getchar_unlocked();
# endif

                    if ((inkey=='x') || (inkey=='X'))
                    {
                        serial_write( fd, "\x00", 1);
                        break;
                    }
                    else
                        break;

                }

            }
            if (inkey=='x'|| inkey=='X')
            {
                serial_write( fd, "\x00", 1);
                break;
            }
        }
        if ((delay > 0) && (firstfile++ > 0))
        {
            printf(" Auto playing %s with %d seconds delay. \n",fnameseq,atoi(param_delay));

#ifdef _WIN32

         //   Sleep(atoi(param_delay)*1000);           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#else
            sleep(atoi(param_delay));           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#endif
        }
        char EOF_flag=0;  //flag for ffff
        int retries;
        int Error_flag=0;
        int comsresult = 0;
        int bytesrx;
        char bufferrx[1];
        char JTRbuffer[2];
        useHandshake = 1;

        if (useHandshake)
        {
            JTRbuffer[0] = 0x26; // causes packet handshake to be sent.
            serial_write( fd, JTRbuffer, 1);
        }
        if (countreq)
        {
            JTRbuffer[0] = 0x24;  // causes transmit count to be returned.
            serial_write( fd, JTRbuffer, 1);
        }
        if (completereq)
        {

            JTRbuffer[0] = 0x25;  // causes Compete message to be returned.
            serial_write( fd, JTRbuffer, 1);

        }

        serial_write( fd, "\x3", 1);     // was "\x03"
        if (useHandshake)
        {
            res= serial_read(fd, bufferrx, sizeof(bufferrx));
        }
        else
        {
            res = 1;
            bufferrx[0] = 62;
        }
        if (res!=0)
        {
            bytesrx=(bufferrx[0]);
            if (useHandshake)
            {
                printf(" Handshake mode ON. IR Toy ready for packet of %d bytes \n", bytesrx);
            }
            else
            {
                printf(" Handshake mode OFF. IR Toy ready for packet of %d bytes \n", bytesrx);
            }

        }
        else
        {
            printf(" Did not receive packet size from IR TOY. \n");
            exit(-1);
        }

        int totalbytes=0;

        while(!feof(fp))
        {

            if ((res=fread(&buffer[0],sizeof(char),/*pbuff */ bytesrx ,fp)) > 0)
            {
                EOF_flag=0;

                if ((uint8_t) buffer[res-1]==255)
                {
                    if ((uint8_t)buffer[res-2]==255)
                    {
                        EOF_flag=1;    // set flag thag we have ff ff
                        // printf("eof set\n");
                    }
                }
                for (retries=0; retries <1; retries++)
                {
                    if (verbose)
                    {
                        printf(" Sending %d Bytes to IRToy...\n\n", res);
                        for(i=0; i<res; i++)
                            printf(" %02X ",(uint8_t) buffer[i]);
                        printf("\n");
                    }

                    comsresult = serial_write( fd, buffer, res);
                    printf("\n Checking # of bytes sent....");
                    if (comsresult != res)
                    {
                        printf(" \n## comms error bytes sent %d <> bytes supposed to send %d\n", comsresult, res);
                        serial_write( fd, "\xFF\xFF\x00\x00\x00\x00\x00", 7);   //trying to 'reset' IR Toy after error
                        //close file and reopen again to start from begining
                        fclose(fp);
                        fp=fopen(param_fname,"rb");
                        if (fp==NULL)
                        {
                            fp=fopen(fnameseq,"rb");
                            if (fp==NULL)
                            {
                                printf(" Bin File gone.. \n");
                                printf(" Opening next bin file....\n");
                                retries=10;  // max out to exit loop
                                break;

                            }
                            else
                            {
                                printf(" Trying to replay file %s again...%i\n",fnameseq,retries+1);
                                Error_flag=1;

                            }

                        }
                        else
                        {
                            printf(" Trying to replay file %s again...%i\n",param_fname,retries+1);
                            Error_flag=1;
                        }

                        serial_write( fd, "/x3", 1);
                        res= serial_read(fd, bufferrx, sizeof(bufferrx));
                        if (res!=0)
                        {
                            bytesrx=(bufferrx[0]);
                            printf(" IR Toy asked for %d bytes \n", bytesrx);
                        }

                    }
                    else
                    {
                        printf(" %i bytes....ok.\n",comsresult);
                        totalbytes+=comsresult;
                        Error_flag=0;
                        // added here: bytes irtoy ready to recieve
                        // check for buffer[res] and buffer[res-1] == 0xff
                        int timecounter=0;
//                       int bytesrx;
//                       char bufferrx[1];

                        if (EOF_flag == 0)
                        {
                            if (useHandshake)
                            {
                                while(1)
                                {
                                    res= serial_read(fd, bufferrx, sizeof(bufferrx));
                                    if (res!=0)
                                    {
                                        bytesrx=(bufferrx[0]);
                                        printf(" IR Toy ready for %d more bytes \n", bytesrx);
                                        break;
                                    }
                                    else
                                    {
                                        Sleep(1);
                                        timecounter++;
                                        if (timecounter> 2000)
                                        {
                                            printf(" IRtoy Got no reply...\n");
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (useHandshake)
                            Sleep(200); // JTR6 added, give the IR TOY time to send the 0xFFFF
                                res= serial_read(fd, bufferrx, sizeof(bufferrx)); // JTR discard count
                            //   printf(" eof-- got 0xff \n");
                            // printf("\n");
                        }
                        break;
                    }
                }
                if (Error_flag==1)
                {
                    printf("error sending IR code, exiting..");
                    exit(-1);
                }

                comsresult = 0;
                if (delay > 0)
                {

#ifdef _WIN32
// temporary disabled to alow to pass here.. in win64 param_delay with -1 seems to wait forever. --Need to confirm
           //         Sleep(atoi(param_delay)*1000);           //milliseconds auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#else
                    //         printf("Sleeping..\n");
                    sleep(atoi(param_delay));           //seconds auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#endif
                }
            }
        }

        printf(" End of file reached: %s \n",fnameseq);
        //int timecounter=0;
        int bytestx;

        if (countreq)
        {

            res= serial_read(fd, buffer, 3); // sizeof(buffer));  //get number of bytes sent
            if (res >= 3)
            {
                if(buffer[0]=='t')
                {
                    bytestx=(buffer[1]<<8)+(uint8_t)buffer[2];
                    printf(" IR Toy got: %d bytes, file was %d bytes ", bytestx, totalbytes);
                    if(bytestx==totalbytes) printf("ok\n"); else printf("failed\n");
                }
                else
                {
                    printf(" Bad reply:");
                    for (i=0; i<3; i++)
                        printf(" %02X ",(uint8_t)buffer[i]);
                }
                printf("\n");
            }
            else
            {
                printf(" IR Toy Did not return correct No. of count bytes...\n");
            }
        }
        if (completereq)
        {
            res= serial_read(fd, buffer, 1); // sizeof(buffer));  //get number of bytes sent
            if (res >= 1)
            {
                if(buffer[0]=='C')
                {
                    printf(" Transmit was successful and glitch free!");
                }
                 else if(buffer[0]=='F')
                {
                    printf(" Error, transmit was interrupted at some point!!!");
                }
                else
                {
                    printf(" Bad reply:");
                }
                printf("\n");

            }
            else
            {
                printf(" IR Toy Did not return complete token...\n");
            }
        }

      //  Sleep(1000);

        fclose(fp);
        if (soloplay==TRUE)
        {
            break;
        }
        fcounter++;
    }
}
