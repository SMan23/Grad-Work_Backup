/*
** Suleyman Muhammad
** ECE 8473: OSP
** Assignment 3 Problem #1
**
** Program to discover which is larger pi^e or 3^pi
**
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define PI 4*atan(1)
#define e  exp(1)
 
int main(void){
  
  double e2p = pow(e, PI);/*e^pi*/
  double p2e = pow(PI, e);/*pi^e*/
 
  printf("e^pi = %g\npi^e = %g\n\n", e2p, p2e);
   
  if(p2e > e2p) printf("pi^e is greater than e^pi\n");/*Greater Than*/
  else printf("e^pi is greater than pi^e");            /*Condition*/
 
  return 0;/*exit program*/
}/*main*/

