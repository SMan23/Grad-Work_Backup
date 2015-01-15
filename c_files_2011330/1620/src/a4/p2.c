/*
*  Suleyman Muhammad
*  Graduate Computer Engineer
*  Villanova University Class '10
*  Villanova Grad Class '11
*
*  Program which computes log_b(x)
*
*  INPUT: The double values of b and x
*
*  OUTPUT: Print statement indicating the value of log_b(x)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(void){
  double b, x, val, val2, f, g;
 
  printf("\nPlease input b and x values:\n");
  scanf("%lf %lf", &b, &x); 

  val  = log(x);
  val2 = log(b);

  f = val/val2; 

  printf("\nb = %g\n", b);
  printf("x = %g\n\n", x);

  printf("\nlog_e(x) = %g\n", val);
  printf("log_e(b) = %g\n\n", val2);

  printf("log_b(x) = %g\n\n", f);

  /* EXTRA */

  g = pow(b, f);
  printf("g = %g\n\n", g);

  if(x == g) printf("Recreated x = %g\n\n", g);
  
  if(x != g) printf("NOT =\n\n");

  return 0;
}/*main*/
