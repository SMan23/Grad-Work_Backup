/*
*  Suleyman Muhammad
*  Graduates Computer Engineer
*  Villanova University Class '10
*
*  ECE 8743: OSP
*  Assignment 1 Problem #2
*
*  Program which converts regular text to PREFORMATTED HTML
*  NOT COMPLETE***
*/

#include <stdio.h>

#define MAX_SIZE 10000

int main(void){
  int c;
  printf("<pre>\n");
  
  while((c = getchar()) != EOF){
    if( c == '&'){
      putchar('&'); putchar('a');
      putchar('m'); putchar('p');
      putchar(';');
    }/*if*/
    else if(c == '>'){
      putchar('&'); putchar('g');
      putchar('t'); putchar(';');
    }/*else if*/
    else if(c == '<'){
      putchar('&'); putchar('l');
      putchar('t'); putchar(';');
    }/*else if*/
    else putchar(c);
  }/*while*/

  printf("</pre>\n");

  return 0;
}

