/*
*  Suleyman Muhammad
*  Graduates Computer Engineer
*  Villanova University Class '10
*
*  ECE 8743: OSP
*  Assignment X Problem #X
*
* Template C program
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
 
 
void err_check(int err){/* ERROR CATCHING */
  char err_msg[100];
 
  sprintf(err_msg, "\nAn error occured, errno = %d:", err);
 
  if(errno != 0){
    perror(err_msg);
    exit (1);
  }/*if*/
  
  return;
}/*err_check*/

/* INPUT FUNCTIONS HERE */ 
 
int main(void){
  /* VARIABLE DECLARATION HERE */
  errno = 0;/* Initialize error number to 0 */
 
  /* INPUT MAIN CODE HERE */
 
  err_check(errno);
  return 0;
}/*main*/
