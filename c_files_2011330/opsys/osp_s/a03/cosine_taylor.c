/*
** Suleyman Muhammad
**
** ECE 8473: OSP
** Assignment 3 Problem #2
**
** Program that will compute a talor series of the math function cosine(), 
** then test it against the value given by the math header file (math.h)
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define PI 4*atan(1)
 
long int my_fac(int n){ /* compute pseudo factorial */
  
  n = n*(n-1);
 
  return n;
}/*my_fac*/
 
double my_cos(double x){ /* my cosine function */
  double val1 = 1, val2 = 0, fac, term, sign = -1;
  int expnt = 4;   
   
  if(x < 0){
    printf("Invalid x value: 0 <= x <= pi/2\n\n");
    printf("usage: echo x value | ./p3");
    exit(1);
  }/*else*/
  else if(x > (PI/2)){
    printf("Invalid x value: 0 <= x <= pi/2\n\n");
    printf("usage: echo x value | ./p3");
    exit(1);
  }/*else if*/
  
  else{
      fac = 2;
      term = x*x;
      val1 = val1 + sign*(term/fac); /* 1 - (x^2)/2 */
      sign = -1*sign;                /* sign = 1 */
    while(val1 != val2){             /* Compute cos(x) */
      val2 = val1;                   /* compute cosine taylor series */
      val1 = val1 + sign*(term * pow(x,2))/(fac*my_fac(expnt)); 
      expnt = expnt + 2;             /* increase exponent */
      sign = -1*sign;                /* change sign */
      fac = fac * my_fac(expnt);     /* expnt! */
      term = term * pow(x,2);        /* x^expnt */
    }/*while*/     
  }/*else*/
  
  return val1;      
}/*my_cos*/
 
int main(int argc, char *argv[]){
  double mathCOS = 0, compCOS = 0, x = 4, diff, per_diff;
 
  scanf("%lf", &x);
   
  mathCOS = cos(x);              /* math.h cosine function */
  compCOS = my_cos(x);           /* my computed cosine value */
  diff = compCOS-mathCOS;        /* difference */
  per_diff = (diff/mathCOS)*100; /* relative percent difference*/
 
  printf("math.h cos(%g) = %g\nmy_cos(%g) = %g\n\n", x, mathCOS, x, 
                                                            compCOS);
  printf("difference = %g\nRelative Percent Difference = %g%%\n\n", diff,  
                                                                 per_diff);
 
  return 0; /* exit program */
}/*main*/

