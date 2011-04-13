/*
    Wiki page: http://dangerousprototypes.com/docs/Universal_Serial_Device_Manufacturing_Test
    Forum Page:

******************************************************************************************************

 Released into the public domain, 2011 Where Labs, LLC (DangerousPrototypes.com/Ian Lesnet)

This work is free: you can redistribute it and/or modify it under the terms of Creative Commons Zero license v1.0

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the License for more details. You should have received a copy of the License along with this program.
If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

Contact Details: http://www.DangerousPrototypes.com
Where Labs, LLC, 208 Pine Street, Muscatine, IA 52761,USA

******************************************************************************************************

 * OS independent serial interface
 *
 * Heavily based on Pirate-Loader:
 * http://the-bus-pirate.googlecode.com/svn/trunk/bootloader-v4/pirate-loader/source/pirate-loader.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <windef.h>


#include "serial.h"

int verbose = 0;

struct grouptest{
  char GroupName[255];   //string content <TestRoutine> </TestRoutine>
  int NeedReply;          // TRUE if need reply
  char outbuf[255];
  char inbuf[255];
  uint8_t hexout[255];   // converted hex from outbuf string
  int hexoutlen;           // lenght of converted hex
  uint8_t hexin[255];
  int hexinlen;
  char Fail_Message[255];   // if fail message here
  char Fail_Message_Extra[255]; // Other failed message to say
  char Success_Message[255];  // if success message here
  char Success_Message_Extra[255];  // Other success stories to tell
  char Gen_Mess[255];
  char Gen_Mess_Extra[255];
};


int print_usage(char * appname)
	{
		//print usage
		printf("\n\n");


        printf(" Usage:              \n");
		printf("   %s  -f configfile\n ",appname);
		printf("\n");
		printf("   Example Usage:   %s -f default.ini  \n",appname);
		printf("\n");
		printf("           Where: -f is the input configuration file for the device  \n");
			printf("\n");

        printf("\n");

	    printf("-------------------------------------------------------------------------\n");


		return 0;
	}
//convert string hex to real hex must be separated by space
uint8_t convert2hex(char *hex){

    int decval1,decval2;
  //  FF =255 or 16+16*16
    uint8_t value=0;
    if (hex[0]>= 'A' && hex[0] <='F') {
        decval1=hex[0]-'A'+10;
    }
    else {
        decval1=hex[0]-'0';
    }
     if (hex[1]>= 'A' && hex[1] <='F') {
        decval2=hex[1]-'A'+10;
    }
    else {
        decval2=hex[1]-'0';
    }
     value=decval2+decval1*16;

     return value;

}

void remove_nl(char *str,int len){
    if(len > 0 && str[len-1] == '\n'){
        str[len-1] = '\0';
    }
}



int main(int argc, char** argv)
{
	int opt;
	char buffer[256] = {0};
	uint8_t STCode;
	int fd;
	int i,res,c;
	int flag=0,firsttime=0;
	char *param_port = NULL;
	char *param_speed = NULL;
	char *board_name=NULL;
    char *initial_hex=NULL;
	char *reply_hex=NULL;
	char *reply_YN=NULL;
	char *failed_mess=NULL;
	char *success_mess=NULL;
	char *gen_mess=NULL;
	char *gen_mess_extra=NULL;
    char *param_repeatitions=NULL;
	int j,repeat_test =1;   // repeat test several times
    int init_flag=0;
    char *configfile=NULL;
    FILE *fp;
    int testindex=0;   // will be use to point to the array of test, 0 is for <initialize>
    char delims[] = " ";  // space delimeter

    int struct_counter=0;

    struct grouptest testarray[10];

	printf("-------------------------------------------------------------------------\n");
	printf("\n");
	printf(" Universal Serial Device Tester For Manufacturers v0.1 (CC-0)\n");
	printf(" http://dangerousprototypes.com\n");
	printf("\n");
	printf("-------------------------------------------------------------------------\n");



	if (argc <= 1)  {

		print_usage(argv[0]);
		exit(-1);
	}

	while ((opt = getopt(argc, argv, "f:")) != -1) {
		switch (opt) {

			case 'f':
			//load the file
			if ( configfile != NULL){
					printf(" Input file Error!\n");
					exit(-1);
				}
				 configfile = strdup(optarg);
                  fp=fopen(configfile,"rt");
				break;

			default:
				printf(" Invalid argument %c", opt);
				print_usage(argv[0]);
				//exit(-1);
				break;
		}
	}

if (configfile==NULL){
    printf(" No Config file.\n");
    print_usage(argv[0]);
    exit(-1);
}
// open config file and parse it
// # is a comment, ignore it
//use fgets
fp = fopen(configfile, "rt");
if (fp==NULL){
printf(" Error opening File.\n");
exit(1);

}
  // read the first line from the file

  fgets(buffer, sizeof(buffer), fp);

  while (!feof(fp)) {
        if (buffer[0]!='#') {
          //look for token
            char *result = NULL;
            char *param=NULL;
            result = strtok( buffer, delims );
            remove_nl(result,strlen(result));
            if ( result != NULL && strlen(result)> 1) {
               // printf( "Token is \"%s\"\n", result );
                if (strcmp(result,"PORT")==0) {
                    param= strtok( NULL, delims );
                    if (param !=NULL){
                        param_port=strdup(param);
                        remove_nl(param_port,strlen(param_port));
                    }
                }
                if (strcmp(result,"BOARD_NAME")==0) {  // grab line up to the end
                    param= strtok( NULL, "\n" );
                    if (param !=NULL){
                        board_name=strdup(param);
                        remove_nl(board_name,strlen(board_name));
                    }
                }
                else if (strcmp(result,"SPEED")==0) {
                    param= strtok( NULL, delims );
                    if (param !=NULL){
                            param_speed=strdup(param);
                            remove_nl(param_speed,strlen(param_speed));
                        }
                }
                else if (strcmp(result,"TEST_REPEAT")==0) {
                    param= strtok( NULL, delims );
                    if (param !=NULL){
                            param_repeatitions=strdup(param);
                            remove_nl(param_speed,strlen(param_repeatitions));
                            repeat_test=atoi(param_repeatitions);
                        }
                }
                else if (strcmp(result,"<Initialize>")==0) {
                    if (init_flag!=1) {
                      // printf("Start Initialize\n");
                    }
                    struct_counter=0;
                    init_flag=1;  // this flag when set, means all subsequent result goes in here
                    strcpy(testarray[struct_counter].GroupName,result);

                  //  printf("struct Counter= %i\n",struct_counter);
                }
                 else if (strcmp(result,"<TestRoutine>")==0) {
                    if (init_flag!=1) {
                   //    printf("Start Test Routine\n");
                    }
                    init_flag=1;  // this flag when set, means all subsequent result goes in here
                    strcpy(testarray[struct_counter].GroupName,result);
                 //   printf("struct Counter= %i\n",struct_counter);
                }
                else if (strcmp(result,"SEND_STRING")==0) {  //grab the reminder of the line
                     if (init_flag ==1) {
                        param= strtok( NULL, "\n" );
                        if (param !=NULL){
                            initial_hex=strdup(param);
                            remove_nl(initial_hex,strlen(initial_hex));  // removes newline
                       //     printf("String to send: %s\n",initial_hex);
                            strcpy(testarray[struct_counter].outbuf,initial_hex);  // put it in he structure

                        }
                    }
                }
                else if (strcmp(result,"OK_REPLY")==0) {  //grab the reminder of the line
                     if (init_flag ==1) {
                        param= strtok( NULL, "\n" );
                        if (param !=NULL){
                            reply_hex=strdup(param);
                            remove_nl(reply_hex,strlen(reply_hex));
                            strcpy(testarray[struct_counter].inbuf,reply_hex);
                        //    printf("String to expect: %s\n",testarray[struct_counter].inbuf);
                        }
                    }
                }
                 else if (strcmp(result,"REPLY")==0) {  //grab the reminder of the line
                     if (init_flag ==1) {
                        param= strtok( NULL, "\n" );
                        if (param !=NULL){
                            reply_YN=strdup(param);
                            remove_nl(reply_YN,strlen(reply_YN));
                            if (strcmp(reply_YN,"YES")==0){
                                testarray[struct_counter].NeedReply=1;
                            }
                            else {
                              testarray[struct_counter].NeedReply=0;
                            }
                       //     printf("Need a reply: %i\n",testarray[struct_counter].NeedReply);
                        }
                    }
                }
                else if (strcmp(result,"FAIL_MESS")==0) {  //grab the reminder of the line
                     if (init_flag ==1) {
                        param= strtok( NULL, "\n" );
                        if (param !=NULL){
                            failed_mess=strdup(param);
                            remove_nl(failed_mess,strlen(failed_mess));
                            strcpy(testarray[struct_counter].Fail_Message,failed_mess);
                       //     printf("Failed Message to Display: %s\n",testarray[struct_counter].Fail_Message);
                        }
                    }
                }
                else if (strcmp(result,"FAIL_MESS_EXTRA")==0) {  //grab the reminder of the line
                     if (init_flag ==1) {
                        param= strtok( NULL, "\n" );
                        if (param !=NULL){
                            failed_mess=strdup(param);
                            remove_nl(failed_mess,strlen(failed_mess));
                            strcpy(testarray[struct_counter].Fail_Message_Extra,failed_mess);
                       //     printf("Failed Message Extra to Display: %s\n",testarray[struct_counter].Fail_Message_Extra);
                        }
                    }
                }
                else if (strcmp(result,"SUCCESS_MESS")==0) {  //grab the reminder of the line
                     if (init_flag ==1) {
                        param= strtok( NULL, "\n" );
                        if (param !=NULL){
                            success_mess=strdup(param);
                            remove_nl(success_mess,strlen(success_mess));
                            strcpy(testarray[struct_counter].Success_Message,success_mess);
                       //     printf("Success Message to Display: %s\n",testarray[struct_counter].Success_Message);

                        }
                    }
                }
                else if (strcmp(result,"SUCCESS_MESS_EXTRA")==0) {  //grab the reminder of the line
                     if (init_flag ==1) {
                        param= strtok( NULL, "\n" );
                        if (param !=NULL){
                            success_mess=strdup(param);
                            remove_nl(success_mess,strlen(success_mess));
                            strcpy(testarray[struct_counter].Success_Message_Extra,success_mess);
                       //     printf("Success Message Extra to Display: %s\n",testarray[struct_counter].Success_Message_Extra);

                        }
                    }
                }
                 else if (strcmp(result,"GEN_MESS")==0) {  //grab the reminder of the line
                     if (init_flag ==1) {
                        param= strtok( NULL, "\n" );
                        if (param !=NULL){
                            gen_mess=strdup(param);
                            remove_nl(gen_mess,strlen(gen_mess));
                            strcpy(testarray[struct_counter].Gen_Mess,gen_mess);
                   //         printf("Gen Message to Display: %s\n",testarray[struct_counter].Gen_Mess);

                        }
                    }
                }
                else if (strcmp(result,"GEN_MESS_EXTRA")==0) {  //grab the reminder of the line
                     if (init_flag ==1) {
                        param= strtok( NULL, "\n" );
                        if (param !=NULL){
                            gen_mess_extra=strdup(param);
                            remove_nl(gen_mess_extra,strlen(gen_mess_extra));
                            strcpy(testarray[struct_counter].Gen_Mess_Extra,gen_mess_extra);
                     //       printf("Gen Message Extra to Display: %s\n",testarray[struct_counter].Gen_Mess_Extra);

                        }
                    }
                }

                else if (strcmp(result,"</Initialize>")==0) {
                        init_flag=0;  // so that it will not go here
                   //     printf("End Initialize\n\n");
                        //convert the string hex to actual hex

                        struct_counter++;
                    }
                else if (strcmp(result,"</TestRoutine>")==0) {
                        init_flag=0;  // so that it will not go here
                   //     printf("End Test Routine\n\n");
                          //convert the string hex to actual hex

                        struct_counter++;
                    }
            }
            else {  //result not null
                if(strlen(result)> 1) {
                  //  printf("Not recognize parameter %s \n",param);
                }
            }
            if (param !=NULL) {
           // printf("Parameter is %s \n",param);
            }

        }  // if (buffer[0]!='#')

        //  printf("%i line is %s\n",++counter,buffer);
        fgets(buffer, sizeof(buffer), fp);

  } // while (!feof(fp))
  // close the stream
  fclose(fp);

//run hex conversion here
for (i=0;i < struct_counter;i++){

    char delims[] = " ";  //separated by space
    char *result = NULL;
    int p=0,len=0;j=0;
    char * pch;

    pch=strchr(testarray[i].outbuf,'"');

    if (pch==NULL) {   //assume hex now
        result = strtok( testarray[i].outbuf, delims );
        while( result != NULL ) {
            len=strlen(result);
            if (len ==2) {
                testarray[i].hexout[p++]=convert2hex(result);
            }
            else {
                // treat as string literal


            }
            result = strtok( NULL, delims );
        }

    }
    else {
      len=strlen(testarray[i].outbuf);
    //remove double quotes
    p=0;
    for (j=0;j <len; j++) {
            if (testarray[i].outbuf[j] != '"') {
                testarray[i].hexout[p++] =testarray[i].outbuf[j];
            }
        }
    }
      testarray[i].hexoutlen=p;

       pch=strchr(testarray[i].inbuf,'"');
       if (pch==NULL) {   //assume hex now
        result = strtok( testarray[i].inbuf, delims );
        while( result != NULL ) {
            len=strlen(result);
            if (len ==2) {
                testarray[i].hexin[p++]=convert2hex(result);
            }
            else {
                // treat as string literal


            }
            result = strtok( NULL, delims );
        }

    }
    else {
      len=strlen(testarray[i].inbuf);
    //remove double quotes
    p=0;
    for (j=0;j <len; j++) {
            if (testarray[i].inbuf[j] != '"') {
                testarray[i].hexin[p++] =testarray[i].inbuf[j];
            }
        }
    }
      testarray[i].hexinlen=p;

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

		printf("\n Parameters used: Device = %s,  Speed = %s bps\n\n",param_port,param_speed);
        printf("\n Board Name: %s \n",board_name);

         if (param_repeatitions==NULL) {
              repeat_test=1;

         }

		flag=0;
		//
		// Loop and repeat test as needed for manufacturing
		//

		 printf(" Press Esc to exit, any other key to start the self-test \n\n");
		while(1){
		 //pause for space, or ESC to exit
		 if (flag==1)
		 {
			printf("\n --------------- Starting a new %s Self Test-------------\n",board_name);
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

		printf(" Opening %s Self Test on %s at %sbps...\n", board_name,param_port, param_speed);
		fd = serial_open(param_port);
		if (fd < 0) {
			fprintf(stderr, " Error opening serial port\n");
			return -1;
		}
		serial_setup(fd,(speed_t) param_speed);
		printf(" Starting %s Self Test...\n",board_name);
		// read instruction here

        // Use the group <initialize>
        testindex=0;
        // accept multiple entries for <Initialize>
        while (strcmp(testarray[testindex].GroupName,"<Initialize>")==0) {
           // printf(" %s\n",testarray[testindex].GroupName);
            serial_write( fd, (char *)testarray[0].hexout,testarray[0].hexoutlen );
            //need reply?
            if (testarray[testindex].NeedReply==1){
               // get reply str
               res= serial_read(fd, buffer, sizeof(buffer));  // get reply
               for(c=0; c<res; c++){
                        STCode=buffer[c];
                        if (STCode!=testarray[testindex].hexin[c]) {
                            printf("%s\n",testarray[testindex].Fail_Message );
                        }
              }

            }
            else {
              //No replay needed

            }
            int flag_mess=0;
            if (strcmp(testarray[testindex].Gen_Mess,"")!=0){
               printf("\n %s\n\n",testarray[testindex].Gen_Mess );
               flag_mess=1;
            }
             if (strcmp(testarray[testindex].Gen_Mess_Extra,"")!=0){
               printf("\n %s\n\n",testarray[testindex].Gen_Mess_Extra );
               flag_mess=1;
            }
            if(flag_mess==1){

                 while(1){
                    Sleep(1);
                    if(kbhit()){
                        c = getch();
                        break;
                    }
                }

            }



            testindex++;

        }
          for (j=1;j<repeat_test+1;j++)
            {
                printf("\n Test no: %i of %i \n",j,repeat_test);
                while (strcmp(testarray[testindex].GroupName,"<TestRoutine>")==0) {
                   //  printf("\n %s\n",testarray[testindex].GroupName);
                     i=testindex;
                // run <testroutine>

                    serial_write( fd,(char*)testarray[i].hexout, testarray[i].hexoutlen);

                    if (testarray[i].NeedReply==1) {
                        Sleep(1);
                        res= serial_read(fd, buffer, sizeof(buffer));  // get reply
                        if (res >0){   //we have a replay
                            int compare_ok=1;
                            // must compare one at a time
                            if(testarray[i].hexinlen!=0) {
                              // use literal text
                              int k;
                              for (k=0;k< testarray[i].hexinlen;k++){
                               if(buffer[k]!=testarray[i].hexin[k])
                                   compare_ok=0;
                               }

                            }
                            else{
                               //use hex
                                compare_ok=0;
                            }
                            if (compare_ok==1) {    // Test passed
                                   if (strcmp(testarray[i].Success_Message,"")!=0){
                                          printf("\n  0X%02X: %s %s  ",(uint8_t)buffer[0],board_name,testarray[i].Success_Message);
                                   }
                                if (strcmp(testarray[i].Success_Message_Extra,"")!=0){
                                  printf("\n %s \n\n",testarray[i].Success_Message_Extra);
                                }
                            }else{
                                  if (strcmp(testarray[i].Fail_Message,"")!=0){
                                printf(" 0X%02X: %s %s  \n",(uint8_t) buffer[0],board_name,testarray[i].Fail_Message);
                                  }

                            }
                        }else{ // if (res >0)
                            printf(" %s Selp Test did not reply anything.. Please check connections. \n",board_name);
                        }
                    }
                      //todo:  change to a link list end remove extra thing
                      if (strcmp(testarray[i].Gen_Mess,"")!=0){
                                   printf("\n %s\n",testarray[i].Gen_Mess);
                      }
                     if (strcmp(testarray[i].Gen_Mess_Extra,"")!=0){
                                 printf("\n %s\n",testarray[i].Gen_Mess_Extra );
                      }

                 testindex++;
                 if (testindex>struct_counter) {
                     break;
                 }
            }

        }
		if (firsttime==0){    // run here once and don't say again the next time
			printf("\n\n Press any key to continue...\n");
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
		printf("\n\n Connect another %s Board \n and press any key to start the self-test again \n",board_name);
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
	FREE(configfile);
	return 0;
}  //main
