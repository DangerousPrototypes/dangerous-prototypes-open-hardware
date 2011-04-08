//
//
//
//
//  Convertion Utility:
//  Purpose:  Convert HEX file into Bin FILE
//
//  Created by: James L. Santos
//
//
//
//
//
//  Copyright (c) 2010  http://www.dangerousprototypes.com by Ian Lesnet
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <limits.h>

#define LEN 256     // max dos path
#define MAXCHAR  512

#define PIC_EMPTY  0xff
#include "data_file.h"





char *replace_ext(char *fname,char *ext)
{
        char szPath[LEN];
        strcpy(szPath,fname);
        char *pFile = strrchr(szPath, '/');
        pFile = pFile == NULL ? szPath : pFile+1;
        char *pExt = strrchr(pFile, '.');

        if (pExt != NULL)
            strcpy(pExt, ext);
         else
            strcat(pFile, ext);

         return pFile;
}


int main(int argc, char *argv[])

{

    FILE   *fp;
    char bname[LEN];  // storage for output filename
    uint8_t *buf_write;   // thise is where the data will be transferred
    uint32_t read_size;


    printf("\n\n HEX to BIN FILE Converter\n");
    printf(" http://www.dangerousprototypes.com\n\n");
    if (argc < 2)  {
         fprintf(stderr, "This small utility will create a new bin file based on the input HEX file\n\nUsage: %s filename.hex\n ", argv[0]);
         exit(-1);
    }
     //open source hex file
     if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr,"Can't open input file.\n");
        exit(-1);
    }
    //get the file size
    long fsize;
    fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fclose(fp);  // close it because it will be reopen

    buf_write = (uint8_t*)malloc(fsize);
	memset(buf_write, PIC_EMPTY, sizeof(buf_write));

    //create same file name with bin extenstion
    strcpy(bname,replace_ext(argv[1],".bin"));


    read_size = HEX_ReadFile(argv[1], buf_write,fsize);
    if (read_size!=0){
	      BIN_WriteFile(bname, buf_write,read_size);

         printf("\nConversion Successful. File(s) created: \n");
         printf("%s  ---->   %s \n",argv[1],bname);
      }
       else
          printf("\nConversion NOT successful. File(s) not created: \n");

	free(buf_write);

    return 0;
}
