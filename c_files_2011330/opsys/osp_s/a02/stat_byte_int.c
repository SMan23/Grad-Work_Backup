#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define MAX_SIZE 1001
 
int main(void){
  int n=0;
  double val1, val2, tempX, temp0, temp1, temp2,\
         S1, S2, C, average, stdDEV;
/*temp0 = interim Y0*Y1 + Y1*Y2 ... Yn-2*Yn-1 value 
  temp1 = interim S1 value
  temp2 = interim S2 value*/  
 
  if((scanf("%lf", &val1)) == EOF){
    printf("NO INPUT, TRY AGAIN");
    exit(1);
  }/*if*/
  else ++n;
 
  if((scanf("%lf", &val2)) == EOF){
    printf("NEED MORE THAN ONE VALUE, TRY AGAIN");
    exit(1);
  }/*if*/
  else ++n;
 
  tempX = val1;/*Compute Initial Values for temp values*/
  temp0 = val1*val2;
  temp1 = val1;
  temp2 = val1*val1;
   
  while((scanf("%lf", &val1)) != EOF){/*Running Computation for temp values */
    if(n >= MAX_SIZE)
      break;
    else n++;
    temp0 = temp0 + val2*val1;  
    temp1 = temp1 + val2;
    temp2 = temp2 + val2*val2;
    val2 = val1;
  }/*while*/
 
  temp0 = temp0 + val1*tempX;/*Yn-1*Y0*/
  temp1 = temp1 + val2;/*Compute Last Iteration of S1 & S2*/
  temp2 = temp2 + val2*val2;
  S1 = temp1;
  S2 = temp2;
  printf("temp0 = %f\nS1 = %f\nS2 = %f\nn = %d\n\n", temp0, S1, S2, n);
  
  C = (n*(temp0) - S2*S2)/(n*(S2-S1*S1));
  average = S1/n;
  stdDEV = sqrt(S2/n - average*average);
 
  printf("Correlation Coefficient = %f\nAverage = %f\nStandard Deviation = %f\n",
          C, average, stdDEV);
 
  return 0;
}/*main*/

