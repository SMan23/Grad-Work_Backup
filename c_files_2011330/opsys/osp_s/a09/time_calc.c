/*
*  Suleyman Muhammad
*  Graduates Computer Engineer
*  Villanova University Class '10
*
*  ECE 8743: OSP
*  Assignment 9 Problem #2
*
*  Program which returns the current time. If an argument is given the program returns the current time - the input 
*  time which is effectively the time passed since the input time
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
 
 
void err_check(int err){/* ERROR CATCHING */
  char err_msg[100];
 
  sprintf(err_msg, "\nAn error occured, errno = %d:", err);
 
  if(errno != 0){
    perror(err_msg);
    exit (1);
  }/*if*/
  
  return;
}/*err_check*/

 
int main( int argc, char *argv[] ){
  int t; double start, stop;
  char t_val[BUFSIZ];

  struct timeval c_time;/*current time*/

  errno = 0;/* Initialize error number to 0 */ 

  if( argc == 1){
    t = gettimeofday( &c_time, NULL); if(t < 0) printf("\nERROR\n");
    sprintf(t_val, "\n%ld.%03ld\n\n", c_time.tv_sec, c_time.tv_usec);

    start = atof(t_val);

    printf("\n%.3f\n\n", start);
  }/*if*/
  else if( argc == 2){
    t = gettimeofday( &c_time, NULL); if(t < 0) printf("\nERROR\n");
    sprintf(t_val, "%ld.%03ld\n", c_time.tv_sec, c_time.tv_usec);
    
    start = atof(argv[1]);
    stop  = atof(t_val);

    printf("\nPrevious = %.3f  Current = %.3f\n\n", start, stop);
    printf("Time Interval = %.3f seconds\n\n", stop - start);
  }/*else if*/
  else printf("\nUsage: prgm_name <optional> prev_time\n\n");
 
  err_check(errno);
  return 0;
}/*main*/
