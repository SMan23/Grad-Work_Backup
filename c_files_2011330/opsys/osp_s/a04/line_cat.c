/*
** Suleyman Muhammad
** Graduates Computer Engineer
** Villanova University Class '10
**
** ECE 8743: OSP
** Assignment 4 Problem #1
**
** Program to read two lines then concatinate them into one
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void){
  
  char line[BUFSIZ];
  char slash[] = "\\", n[] = "n", space[] = " ";
  int i=1, j=0, k=1;

  while( fgets(line, BUFSIZ, stdin)){
    
    while(line[k] != EOF){     /* While not end of file */
      if(line[j] == slash[0] && line[k] == n[0]){/* check for newline */
        if(i%2 == 1){          /* If an odd newline*/
          line[j] = space[0];  /* remove newline character*/
          line[k] = line[k+1];
        }/*if*/
        ++i;                   /* increment i */
      }/*if*/
      ++j; ++k;  
    }/*while*/
  
  }/*while*/

  printf("%s",line);  
 
  return 0;
}/*main*/
