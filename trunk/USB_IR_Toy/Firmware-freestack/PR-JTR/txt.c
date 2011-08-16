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

#include "txt.h"

extern int modem;
extern int verbose;
void IRtxtrecord( char *param_fname)
{
    int i,flag;
    unsigned long absolute=0;

    unsigned long size=0;

    int fcounter;
    char inkey;
// char *param_delay=NULL;

    char fnameseq[255],fnameseq_txt[255];
    FILE *fp, *fp_txt=NULL;
    int res;
    uint16_t txt_buffer[1];
    char s[4];
    //check filename if exist
    printf(" Entering TXT conversion Mode \n");
    fcounter=0;
    inkey=0;
    while (1)
    {
        sprintf(fnameseq,"%s_%03d.bin",param_fname,fcounter);
        fp=fopen(fnameseq,"rb");
        if (fp==NULL)
        {
            if (fcounter > 0)
                printf(" No more file(s). \n\n");
            else
                printf(" File does not exits. \n");
            break;
        }

        sprintf(fnameseq_txt,"%s_%03d.txt",param_fname,fcounter);
        fp_txt=fopen(fnameseq_txt,"w");
        if (fp_txt==NULL)
        {
            printf(" Error: Cannot create txt file: %s. \n",fnameseq_txt);
            break;
        }

        printf("\n Creating txt file: %s \n\n",fnameseq_txt);
        size=0;
        absolute=0;
        char temp[4];
        flag=0;
        while(!feof(fp))
        {
            if ((res=fread(&txt_buffer,sizeof(uint16_t),sizeof(txt_buffer),fp)) > 0)
            {
                for(i=0; i<res; i++)
                {
                    sprintf(temp,"%04X",(uint16_t) txt_buffer[i]);
                    sprintf(s,"%c%c%c%c",temp[2],temp[3],temp[0],temp[1]);
                    if (verbose==TRUE)
                        printf(" %s",s);
                    fprintf(fp_txt,"%s ", s);
                }
            }

        }

        printf("\n .. Done.\n");
        fclose(fp);
        fclose(fp_txt);
        fcounter++;
    }
}

void IRtxtplay(	char *param_fname,int fd,char *param_delay)
{

#ifndef _WIN32
    bool no_data_yet=TRUE, file_created=FALSE;
#else
    BOOL no_data_yet=TRUE, file_created=FALSE;
#endif
    int res;
    int fcounter;
    char buffer[4*1024] = {0};  //   buffer
    char fnameseq[255];
    FILE *fp=NULL;
    int i;
    file_created=FALSE;
    no_data_yet=TRUE;
    char inkey;
    char temp[4];
    char *token;
    char hex1[2];
    char hex2[2];
    uint8_t buf[4*1024];

    //check filename if exist
    printf(" Entering Player Mode \n");
    fcounter=0;
    inkey=0;
    int delay = atoi(param_delay) ;
    int firstfile = 0;
    while (1)
    {
        sprintf(fnameseq,"%s_%03d.txt",param_fname,fcounter);
        fp=fopen(fnameseq,"rt");
        if (fp==NULL)
        {
            if (fcounter > 0)
                printf(" No more file(s). \n");
            else
                printf(" File does not exits. \n");

            break;
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
#else
                    inkey=getchar_unlocked();
                    //	  inkey = fgetc(stdin);
#endif

                    if ((inkey=='x') || (inkey=='X'))
                    {
                        serial_write( fd, "\x00", 1); // JTR
                        break;
                    }
                    else
                        break;

                }

            }
            if (inkey=='x'|| inkey=='X')
            {
                serial_write( fd, "\x00", 1);  // JTR
                break;
            }
        }
        if ((delay > 0) && (firstfile++ > 0))
        {
            printf(" Auto playing %s with %d seconds delay. \n",fnameseq,atoi(param_delay));
#ifdef _WIN32
            Sleep(atoi(param_delay));           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#else
            sleep(atoi(param_delay));           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#endif
        }

        printf("\n Playing file: %s\n",fnameseq);

        int comsresult = 0;
        //int bytestx;

        serial_write( fd, "\x03", 1);

        printf(" Sending IRCodes...\n\n");
        int c=0;
        while(!feof(fp))
        {
            for(i=0; i<sizeof(buffer); i++)
                buffer[i]='\0';
            if ((res=fread(&buffer,sizeof(unsigned char),sizeof(buffer),fp)) > 0)
            {

                token = strtok (buffer," ");
                while (token != NULL)
                {
                    strcpy(temp,token);
                    //convert hex string into real hex, by fair
                    sprintf(hex1,"%c%c",temp[0],temp[1]);
                    i = (uint8_t) strtoul(hex1, NULL, 16);
                    buf[c++]=i;
                    sprintf(hex2,"%c%c",temp[2],temp[3]);
                    i = (uint8_t) strtoul(hex2, NULL, 16);
                    buf[c++]=i;

                    if (verbose==TRUE)
                        printf(" %02X%02X",buf[c-2],buf[c-1]);

                    if ( c == 62)
                    {
                        comsresult = serial_write( fd, (char *) buf, c);
                        c = 0;
                    }
                    token = strtok (NULL, " ");
                }
                if (c != 0)
                    comsresult = serial_write( fd, (char *) buf, c);

                c=0;
                printf("\n");
                Sleep(2500);
//                comsresult = serial_write( fd, "\x24", 1);
//                res= serial_read(fd, buffer, 3);  //get number of bytes sent
//                if (res >= 3)
//                {
//                    if(buffer[0]=='t')
//                    {
//                        bytestx=(buffer[1]<<8)+(uint8_t)buffer[2];
//                        printf(" IR Toy transmitted: %d bytes\n", bytestx);
//                        //if(bytestx==totalbytes) ok else failed;
//                    }
//                    else
//                    {
//                        printf(" Bad reply:");
//                        for (i=0; i<3; i++)
//                            printf(" %02X ",(uint8_t)buffer[i]);
//                    }
//                    printf("\n");
//
//                    break;
//                }
//                else
//                {
//
//                    printf(" Bad reply:");
//                    for (i=0; i<3; i++)
//                        printf(" %02X ",(uint8_t)buffer[i]);
//                }

                if (delay > 0)
                {
#ifdef _WIN32
                    // temporary disabled to alow to pass here.. in win64 param_delay with -1 seems to wait forever. --Need to confirm
                    Sleep(atoi(param_delay)*1000);           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#else
                    sleep(atoi(param_delay));           //auto play. Do not wait for keyboard input, just wait the specified time (miliseconds)
#endif
                }
            }
        }
        // serial_write( fd, "\xFF\xFF", 1);

        printf("\n\n");
        printf(" Reached end of file: %s \n",fnameseq);
        fclose(fp);
        fcounter++;
    }

}
