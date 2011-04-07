

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#define MAX_BUFFER 42048
#define FALSE  -1
#define TRUE   1

void  prog_desc()
{
    printf("----------------------------------------------------------------------\n");
    printf("  Partlist to HTML/WIKI Converter V.03\n");
    printf(" \n");
    printf("  Converts text file exported from BOM of Eagle Layout Editor\n");
    printf("\n\n");
    printf("  http://www.dangerousprototypes.com\n");

    printf("----------------------------------------------------------------------\n");

}
void helpme(char *argv[])
{
         printf("Usage: - %s --i inputfile.txt  --wiki wikioutput.wiki --html htmloutput.html \n\n",argv[0]);
         exit(1);
 }

int main(int argc, char *argv[])
{
    FILE *in=NULL, *wikiout=NULL,*htmlout=NULL;
    char EagleFound;
    char *header[]={"Part ","Value ","Device ","Package ","Library ","Sheet"};
    char line[6][MAX_BUFFER];
    char buffer[MAX_BUFFER];
    int column=0,start,end,buflen;
    int header_good=FALSE;
    int c,index, option_index = 0;
    char *param_wiki_output=NULL;
    char *param_html_output=NULL;
    char *param_file_input=NULL;

    static struct option long_options[] = {
            {"wiki", 1, 0, 0},
            {"html", 1, 0, 0},
            {"i", 1, 0, 0}
     };

    int j=0,i=0,k=0,count;
    int headeridx[6];
    char testchar;

    prog_desc(argv);  //program descripton and title
    while(1) {
        c = getopt_long (argc, argv,"",long_options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 0:
                index=option_index;
                switch (index) {
                   case 0:  //wiki
                        param_wiki_output = optarg;
                        break;
                   case 1:  // html
                        param_html_output = optarg;
                        break;
                    case 2:  // input
                        param_file_input = optarg;
                        break;
                    default:
                        printf("Unknown Parameter: %i\n",index);
                        helpme(argv);

                }
                break;
            default:
                        printf("Invalid Parameter: %i\n",c);
                        helpme(argv);

        }
    }

    if (optind < argc) {
        printf (" Ignored no option parameter(s): ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");
    }


    if ((param_wiki_output==NULL) &&( param_html_output==NULL)) {

         printf(" Error:  No output file specified:  use --wiki fname or --html fname\n\n");
         helpme(argv);

    }
    else {
		if (param_wiki_output !=NULL){
            wikiout=fopen(param_wiki_output,"w");
            if(wikiout==NULL ){
                printf("Can't create wiki output file %s\n",param_wiki_output);
                exit(1);
            }
		}
		if (param_html_output !=NULL) {
            htmlout=fopen(param_html_output,"w");
            if(htmlout==NULL ){
                printf("Can't create html output file %s\n",param_html_output);
                exit(1);
            }
        }
    }
    if (param_file_input ==NULL){
        printf("input text file required\n");
        helpme(argv);
    }
    else {
       in =fopen(param_file_input,"r");
       if(in==NULL ){
             printf("Can't open input file %s\n",param_file_input);
             exit(1);
       }
    }

     EagleFound = FALSE;  //eagle signature

     while(!feof(in)) {
        if(fgets(buffer, MAX_BUFFER, in)) {
            buflen=strlen(buffer);

            if (isalpha(buffer[0])) {
                if(header_good==FALSE) {
                //find headers get fix column
                    column=0;

                    for(i=0;i < buflen;i++){
                        testchar=header[column][0];
                        if (buffer[i]==testchar){
                            k=strlen(header[column]);
                            count=0;
                            for (j=0;j < k;j++) {
                                if(buffer[i+j]==header[column][j]) {
                                    count++;
                                }

                            }
                            if(count>=k) {
                                //we have a match
                                //grab i;
                                headeridx[column]=i;
                                column++;
                             }


                            }
                        }
                        if(column==6){
                             header_good=TRUE;
                             //print the header
                             if (htmlout!=NULL){
                                 fprintf(htmlout,"<table class='wikitable' border='1'>\n");
                                 fprintf(htmlout,"<tr>\n");
                                 fprintf(htmlout,"<th scope='col'>%s</th>\n",header[0]);
                                 fprintf(htmlout,"<th scope='col'>%s</th>\n",header[1]);
                                 fprintf(htmlout,"<th scope='col'>%s</th>\n",header[3]);
                                 fprintf(htmlout,"</tr>\n");
                             }
                             if (wikiout!=NULL){
                                 fprintf(wikiout,"== Partlist ==\n\n");
                                 fprintf(wikiout,"{| border='1' class='wikitable'\n");
                                 fprintf(wikiout,"!%s!!%s!!%s\n",header[0],header[1],header[3]);

                             }


                        }
                }
                else {
                // headeridx[] contains
                 count=0;
                 start=headeridx[count];

                 while(1){
                     //grab chars from start and end of buffer
                      if (count < 5)
                         end=headeridx[count+1]-1;
                      else
                         end=buflen-1;
                      k=0;
                      for(j=start;j < end ;j++){
                            line[count][k++]=buffer[j];
                      }
                      line[count][k]='\0';
                      //printf("%s \n",line[count]);
                      count++;
                      start=end;
                      if(count >5)
                           break;
                 }
                 if (htmlout!=NULL){
                     fprintf(htmlout,"<tr>");
                     fprintf(htmlout,"<td>%s</td> ",line[0]);
                     fprintf(htmlout,"<td>%s</td> ",line[1]);
                     fprintf(htmlout,"<td>%s</td> ",line[3]);
                     fprintf(htmlout,"</tr>\n");

                 }
                  if (wikiout!=NULL){
                     fprintf(wikiout,"|-\n");
                     fprintf(wikiout,"|%s||%s||%s\n",line[0],line[1],line[3]);

                 }
                }
             }
        }
     }
    if (htmlout!=NULL){
        fprintf(htmlout,"</table>\n\n");
        printf("\n HTML FIle created: %s\n",param_html_output);
    }
   if (wikiout!=NULL){
        fprintf(wikiout,"|}\n\n");
        printf("\n Wiki FIle created: %s\n",param_wiki_output);
    }


    fclose(in);
    if(htmlout!=NULL ){
         fclose(htmlout);
    }
     if(wikiout!=NULL ) {
         fclose(wikiout);
     }
    return 0;
}
