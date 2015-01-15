/*
** Suleyman Muhammad
** Graduates Computer Engineer
** Villanova University Class '10
**
** ECE 8743: OSP
** Assignment 6 Problem #1
**
** Program which computes the N-point average of an input sample set using an array to hold temp N values
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
 
void err_check(int err){
  char err_msg[100];
 
  sprintf(err_msg, "\nAn error occured, errno = %d:", err);
 
  if(errno != 0){
    perror(err_msg);
    exit (1);
  }/*if*/
  
  return;
}/*err_check*/
 
 
void N_point(int N, double *p){
  int i = 0;/* begin at second value to leave room for next value */
  double sum = 0, ave, temp;
 
  for(i; i < N-1; ++i){ /* Replace point_array[1] with point_array[2] */
    sum += p[i+1]; 
    p[i] = p[i+1];    /* and so on until point_array[N-1] = point_array[N-2]*/
  }/*for*/
    
  if(scanf("%lf", (p+(N-1))) == 1){
    sum += *(p+(N-1));
    ave = sum/N;
    printf("\nAverage = %lf", ave);
    N_point(N, p);
  }/*if*/
  else{
    printf("\n\nComputation Complete, Goodbye\n\n"); 
    return;
  }/*else*/
 
}/*N_point*/
 
 
int main(int argc, char *argv[]){
  errno = 0;/*Initialize error number to 0*/
 
  int check = 0, i=0, temp, N = atoi(argv[1]);
  double point_array[N], sum = 0, ave, *p;
  
  if(argc != 2){
    printf("\nN-Point Average: Input Error\n\nUsage: {Program_Name} N_value\n\n");
    exit(0);
  }
 
  printf("\n\n%d-Point Average\n\nInput Data\n", N);
 
  for(i; i < N; i++){/* Initialize array and compute initial Point Averages*/
    temp = i;
 
    if(scanf("%lf", &point_array[i]) == 1){
      for(temp; temp+1 > 0; --temp){
          sum += point_array[temp];
          ave = sum/(i+1);
      }/*for*/
      printf("\nAverage = %lf",ave);
      sum = 0;
    }/*if*/
 
    else{ /* Input is a smaller number than the Point average */
      err_check(errno);
      printf("The # of inputs are less than the desired %d-point average\n", N);
      printf("The current average is %lf\n", ave);
      exit(0);
    }/*else*/
 
  }/*for*/
 
  p = point_array; /* p = point_array[0] */
 
  N_point(N, p);
    
  err_check(errno);
  return 0;
}/*main*/
