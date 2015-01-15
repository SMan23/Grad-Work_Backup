/*
*  Suleyman Muhammad
*  Graduate Computer Engineer
*  Villanova University Class '10
*  Villanova Grad Class '11
*
*  Program which tests which is larger e^pi or pi^e
*
*  OUTPUT: Print statement designating the larger of the two 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 4*atan(1)

int main(void){
  double e2pi, pi2e;
 
  e2pi = exp(pi);
  pi2e = pow(pi, exp(1));

  printf("\ne^pi = %g\n", e2pi);
  printf("pi^e = %g\n\n", pi2e);

  if(e2pi > pi2e) printf("e^pi is greater\n\n");
  else printf("pi^e is greater\n\n");

  return 0;
}/*main*/
