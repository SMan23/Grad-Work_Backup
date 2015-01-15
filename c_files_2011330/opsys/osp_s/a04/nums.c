/*
** Suleyman Muhammad
** Graduates Computer Engineer
** Villanova University Class '10
**
** ECE 8743: OSP
** Assignment 4 Problem #4
**
** Program which is the equivalent of the shell script from 
** Assignment 4 Problem #3 in which a countdown is printed using user input arguments
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main( int argc, char* argv[]){
  int check = 0;
  int  r, s, t;
 
  r = atoi(argv[1]);
  s = atoi(argv[2]);
 
 
  if(argv[3] != NULL) t = atoi(argv[3]);/* check if increment given */
  else t = 1;                           /* default increment */ 
  
  if(argc < 3){
    printf("\n usage: nums (or program_name) start stop [inc] \n\n");
    exit(0);
  }/*if*/
 
  if(r == s) printf("\n%d\n", r);  /* start = stop */

  else if(r > s){                  /* start > stop */
    while(r >= s){             
      printf("%d\n", r);
      if(t <= 0) r += t; /* negative increment (decrement should be viable option) */
      else r -= t;             /* subtract positive increment */
    }/*while*/
  }/*else if*/

  else if(r < s){              /* start < stop */
    if(t <= 0) printf("\nnums: infinate loop\n");
    else while(r <= s){
      printf("%d\n", r);
      r += t;                  /* add positive increment */
    }/*else while*/
  }/*else if*/

  printf("\n");  

  return 0;
}/*main*/
