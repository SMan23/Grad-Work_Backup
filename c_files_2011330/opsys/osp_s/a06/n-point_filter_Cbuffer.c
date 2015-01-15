/*
* Suleyman Muhammad
* Graduates Computer Engineer
* Villanova University Class '10
*
* ECE 8743: OSP
* Assignment 6 Problem #2
*
* Program which reads double precision floating-point data and passes it 
* through an N-point filter and directs it to standard output 
* (USES A CIRCULAR BUFFER)
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
 
 
double computation(int start){
  int i = 0, j = start;
  double sum = 0;
 
  for(; i < N; ++i){   
    sum += val[j] * b[i];
    ++j; if(j >= N) j = 0;/* CIRCULAR BUFFER */
  }/*for*/ 
 
  return sum;
}/*computation*/ 
 
 
void N_filter(void){
  int start = 0;
 
  printf("%f\n", computation(start));
 
  while(scanf("%lf", &val[start]) == 1){
  
    ++start; if(start >= N) start = 0;
    printf("%f\n", computation(start));
   
  }/*while*/
  
  return;
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

