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


/* #include<math.h> */
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
  double f, f1, f2, x;
  int s;

  if(argc != 2){ /* Gather Inputs */
    printf("\nPlease Input x value:\n\n"); 
    s = scanf("%lf", &x);
    if(s != 1) printf("&MAIN ERROR: Inputs");
  }/*if*/
  else x = atoi(argv[1]);

  f1 = ((x - 2)*x + 1)*x - 6.3; /* Calculate numerator */
  f2 = (x + 0.05005)*x - 3.14;   /* and denominator */

  f = f1/f2; /* Calculate Final Function */

  printf("\nx value = %g\n", x);
  printf("f1(x) = %g ", f1);
  printf(" f2(x) = %g\n", f2);
  printf("f(x) = %g\n", f);

return 0;
}
