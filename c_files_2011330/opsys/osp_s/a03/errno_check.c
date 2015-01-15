/*
** Suleyman Muhammad
**
** ECE 8473: OSP
** Assignment 3 Problem #2
**
** Program that with the error number header file (errno.h) determines which
** error value which is passed when one attempts to calculate the square root *of -1
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
 
int main(void){
  char err_msg[100];
  float bad;
  errno = 0; /*initialize error number to zero*/
 
  bad = sqrt(-1);
 
  sprintf(err_msg, "Error Number for sqrt(-1) is %d", errno);  
 
  perror( err_msg );/*print error number : error message */ 
 
  return 0; /*exit program*/
}/*main*/

