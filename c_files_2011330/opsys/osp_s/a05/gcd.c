/*
** Suleyman Muhammad
** Graduates Computer Engineer
** Villanova University Class '10
**
** ECE 8743: OSP
** Assignment 5 Problem #1
**
** Program to compute gcd (Greatest Common Denominator)
** using a recursive function
**
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
 
 
int gcd(int p, int q){
  int r;
 
  if ((r = p % q) == 0)/* test if p mod q = 0*/
    return q;
  else
    return gcd(q, r);
}/*gcd*/
 
 
int test_gcd(void){
  int s, val1, val2;
  
  printf("\nGreatest Common Demoninator:\nPlease input two integers\n\n");
  s = scanf("%d %d", &val1, &val2);
 
  if(s != 2){
    printf("\nInput Error, Try again\n\n");
    exit (0);
  }/*if*/
  
  return gcd(val1, val2);
}
 
 
int main(void){
  int x;
  errno = 0;/*Initialize error number to 0*/
 
  x = test_gcd();
  printf("\nThe GCD is %d\n", x);
 
  err_check(errno);
  return 0;
}/*main*/
