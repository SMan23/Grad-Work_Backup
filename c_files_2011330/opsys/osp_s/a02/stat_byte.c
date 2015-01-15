/*
** Suleyman Muhammad
**
** ECE 8472: OSP 
** Assignment 2 Problem #4
**
** Program that can read up to 1001 bytes from standard input and compute 
** and display the average, standard deviation, and serial correlation coefficient of the previously mentioned bytes 
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define MAX_SIZE 1001
 
int main(void){
  char c;
  int  n=0, c1, c2;
  double C,  tempX, temp0,   temp1, temp2;
  double S1, S2,    average, stdDEV;
 
  /*
  temp0 = interim Y0*Y1 + Y1*Y2 ... Yn-2*Yn-1 + Yn-1*Y0 value 
  temp1 = interim S1 value
  temp2 = interim S2 value
  */  
 
  if((c = getchar()) == EOF){/*Test if there is no input*/
    printf("NO INPUT, TRY AGAIN");
    exit(1);
  }/*if*/
  else{++n; c1 = (int) c;}
 
  if((c = getchar()) == EOF){/*Test if there is only one input*/
    printf("NEED MORE THAN ONE VALUE, TRY AGAIN");
    exit(1);
  }/*if*/
  else{++n; c2 = (int) c;}
 
  tempX = c1;/*Compute Initial Value for temp*/
  temp0 = c1 * c2;
  temp1 = c1;
  temp2 = c1 * c1;
   
  while((c = getchar()) != EOF){/*Running Computation for temp values */
    if(n >= MAX_SIZE)
      break;
    else n++;
    c1 = (int) c;
    temp0 = temp0 + (c2 * c1);  
    temp1 = temp1 +  c2;
    temp2 = temp2 + (c2 * c2);
    c2 = c1;
  }/*while*/
 
  temp0 = temp0 + (c1 * tempX); /** Yn-1*Y0 **/
 
  S1 = temp1 +  c2;          /*Compute Last Iteration*/
  S2 = temp2 + (c2 * c2);          /*of S1 & S2*/
 
  printf("temp0 = %g\nS1 = %g\nS2 = %g\nn = %d\n\n", temp0, S1, S2, n);
  
  C = (n*(temp0) - S1*S1)/((n*S2)-(S1*S1));/*Correlation Coefficient*/
  average = S1/n;                          /*Average*/
  stdDEV = sqrt(S2/n - average*average);   /*Standard Deviation*/
 
  printf("Corr. Coefficient = %g\nAverage = %g\nStandard Deviation=%g\
          \n\n", C, average, stdDEV);
 
  return 0;/*exit program*/
}/*main*/

