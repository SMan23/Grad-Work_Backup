/*
** Suleyman Muhammad
** Graduates Computer Engineer
** Villanova University Class '10
**
** ECE 8743: OSP
** Assignment 5 Problem #3
**
** Program which generates random birth months and then calculates the
** probability of collisions or in other words the probability that
** there are at least 2 individuals with the same birthday month
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <time.h>

#define BUFFER 4096
 
 
void err_check(int err){
  char err_msg[100];
 
  sprintf(err_msg, "\nAn error occured, errno = %d:\n", err);
 
  if(errno != 0){
    perror(err_msg);
    exit (1);
  }/*if*/
  
  return;
}/*err_check*/
 
  
int calc_trials(int ppl, int *p){/* Calculate # of Collisions */
  int b_array[12], i=ppl-1, j, k=0;
 
  for(i; i >= 0 ; --i){
    j = *(p+i);
    if(b_array[j] == 1){
      ++k;
    }/*if*/
    else b_array[j] = 1;
  }/*for*/
 
  return k;
 
}/*cacl_trials*/
 
 
int birth_function(int ppl){
  int bmonth[BUFFER];
  int person, i = ppl-1, *p;

  p = bmonth;
 
  for(i; i >= 0 ; --i){ /* Generate a random month for N people */
    person =  12*(rand()/((double)RAND_MAX+1));
    bmonth[i] = person;
  }/*for*/
 
  return calc_trials(ppl, p);
 
}/*birth_function*/
 
 
int main(void){
  int s, people, collisions;
  double probability; 
 
  errno = 0;      /* Initialize error number to 0 */
  srand(time(0)); /* Initialize rand() seed */
  
  printf("\nInput number of people involved in study SIMULATION:\n");
  s = scanf("%d", &people); /* Input # of people in the study */
  
  if(people > 4096){ /* Number of people too large for buffer */
    printf("\nToo many individuals for buffer, try smaller value:\n");
    s = scanf("%d", &people); 
  }/*if*/

  if(s != 1){               /* scanf input error catching */
    printf("\nInput Error\n");
    exit (0);
  }/*if*/
 
  collisions = birth_function(people);
  err_check(errno);/*Error Catching*/
 
  probability = collisions/(people-1.0);/* First Individual cannot be 
                                             considered a trial */
  probability = probability*100;
 
  printf("\nThe Estimated Probabilty of Collison is %f%%\n\n", probability);
 
  return 0;
}/*main*/