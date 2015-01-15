/*
*  Suleyman Muhammad
*  Graduates Computer Engineer
*  Villanova University Class '10
*
*  ECE 8743: OSP
*  Assignment 1 Problem #2 part 2
*
*  Program which converts input into PREFORMATTED HTML then
*  writes that into a specified file
*
*  NOT COMPLETE*** append not working correctly *** first input string not recognized
*/

#include <stdio.h>

#define MAX_SIZE 10000

int main(void){
  char c, f_name[MAX_SIZE], input[MAX_SIZE];
  int i;
  FILE *ofp;/*outfile pointer*/

  printf("\nPlease Input File Name:\n");
  scanf("%s", f_name);

  ofp = fopen(f_name,"a");/*create pointer to "file.html"*/
  printf("File \"%s\" opened or created\n", f_name);
  
  printf("\nPlease Input Text To Convert\n");
  scanf("%s", input);
  
  fprintf(ofp,"<pre>\n");
  for(i = 0; (c = getchar()) != '\n'; i++){
    if( c == '&'){
       input[i]='&';
       input[i+1] = 'a';
       input[i+2] = 'm';
       input[i+3] = 'p'; i = i + 3;
    }/*if*/
    else if(c == '>'){
       input[i] = '&';
       input[i+1] = 'g';
       input[i+2] = 't'; i = i + 2;
    }/*else if*/
    else if(c == '<'){
       input[i] = '&';
       input[i+1] = 'l';
       input[i+2] = 't'; i = i + 2;
    }/*else if*/
    else{input[i] = c;}
  }/*for*/
  
  fprintf(ofp, "%s", input);

  fprintf(ofp, "\n<pre\\n>\n");
  fclose(ofp);

  printf("BUFSIZ = %d MAX_SIZE = %d\n", BUFSIZ, MAX_SIZE);

  return 0;
}

