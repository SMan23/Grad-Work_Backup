/*
** Suleyman Muhammad
**
** ECE 8473: OSP
**
** Assignment 2 Problem #2
**
** Program which computes the 3-point moving average of floating point numbers 
** inputted to std input. The output of this program is suitable for plotting.
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int main(void){
  double x, y0, y1=0, y2=0, z;
 
  while((scanf("%lf",&z)) != EOF){
    y0 = y1;
    y1 = y2;
    y2 = z;
    x  = (y0+y1+y2)/3; /* average */
    printf("%f\n", x);
  }/*while*/
 
  return 0; /* exit program */
}/*main*/

