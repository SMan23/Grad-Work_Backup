/*
** Suleyman Muhammad
** Graduates Computer Engineer
** Villanova University Class '10
**
** ECE 8743: OSP
** Assignment 6 Problem #2
**
** Program which reads double precision floating-point data and passes it through an N-point flter *and directs it to standard output
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "b.h"
 
double val[N];
 
void err_check(int err){ /* ERROR CHECKING */
  char err_msg[100];
 
  sprintf(err_msg, "\nAn error occured, errno = %d:", err);
 
  if(errno != 0){
    perror(err_msg);
    exit (1);
  }/*if*/
   
  return;
}/*err_check*/
 
 
void N_filter(void){
  int i = 0, j = 0, s;
  double sum = 0;
 
  for(; i < N; ++i)    sum += val[i] * b[i];
 
  printf("%f\n", sum);
 
  for(; j < N-1; ++j) val[j] = val[j+1]; /* slide the filter window */
                                                /*down one */
  s = scanf("%lf", &val[N-1]);/* Add new input value to bottom of the window */
  if(s == 1) N_filter();
  else return;
 
}/*N_filter*/
 
 
int main(void){
  int i = 0, s;
  
  errno = 0; /* Initialize error number to 0 */
  
   /* Initialize and populateArray */
  for(; i < N; i++){
    s = scanf("%lf", &val[i]);
    if(s != 1){ printf("\nInput Error\n"); exit(0);}/*if*/
  }/*for*/
 
  N_filter();
 
  err_check(errno);
  return 0;
}/*main*/

