/* 
** Suleyman Muhammad
** Graduate Computer Engineer
** Villanova University Class '10
** Villanova Grad Class '11
**
** Teachers Assistant SPR Semester: ECE 1620 - Freshman Programming
** 
** ASSIGNMENT #3 Problem 1 (convert polynomial on bottom of pg 47 of EPS w/ C by D. M. ETTER)
*/


#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
  double f, f1, f2, x;
  int s;

  printf("\nPlease Input x value:\n\n"); /* THIS VERSION IS FOR PROFESSOR PERRY's INPUT CONSTRUCT*/
  s = scanf("%lf", &x);
  if(s != 1 && argc == 2){x = atoi(argv[1]);} 
  else if(s != 1) {printf("ERROR: inputs"); exit(0);} /* Catch Input Error */

  f1 = ((x - 2)*x + 1)*x - 6.3; /* Calculate numerator */
  f2 = (x + 0.05005)*x - 3.14;   /* and denominator */

  f = f1/f2; /* Calculate Final Function */

  printf("\nx value = %g\n", x);
  printf("f1(x) = %g ", f1);
  printf(" f2(x) = %g\n", f2);
  printf("f(x) = %g\n", f);
  printf("floor %g\n", floor(ceil(10.8)));

return 0;
}
