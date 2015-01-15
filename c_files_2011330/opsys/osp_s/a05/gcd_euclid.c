/*
** Suleyman Muhammad
** Graduates Computer Engineer
** Villanova University Class '10
**
** ECE 8743: OSP
** Assignment 5 Problem #2
**
** My program to compute the gcd (Greatest Common Denominator)
** of two integers using a recursive function based on Euclid's Algorithm
** for GCD
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
 
 
int my_gcd(int p, int q){
  int temp;
 
  if (p < q){ /* Test if p < q*/
    temp = p;
    p = q;
    q = temp;    
  }/*if*/
  
  p -= q;/*subtract q from p*/
  
  if(p == 0)/*computation completed*/
    return q;
  else
    return my_gcd(p,q);
}/*gcd*/
 
 
int test_gcd(void){
  int s, val1, val2;
  
  printf("\nGreatest Common Demoninator:\nPlease input two integers\n\n");
  s = scanf("%d %d", &val1, &val2);

  if(val1 == 0 || val2 == 0){
    printf("\n ZERO is invalid input \n");
    exit (0);
  }/*if*/
 
  if(s != 2){
    printf("\nInput Error, Try again\n\n");
    exit (0);
  }/*if*/
  
  return my_gcd(val1, val2);
}
 
 
int main(void){
  int x;
  errno = 0;/*Initialize error number to 0*/
  
  printf("\nEuclid's GCD\n");
  x = test_gcd();
  printf("\nThe GCD is %d\n", x);
 
  err_check(errno);
  return 0;
}/*main*/
