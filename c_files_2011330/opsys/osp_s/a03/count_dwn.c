/*
** Suleyman Muhammad
**
** ECE 8473: OSP
** Assignment 3 Problem #4
**
** Countdown to Fall Break:
** Program to compute the number of days, hours, minutes and seconds left 
** until Fall break 2010. 
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <time.h>
 
int time_conv(time_t countdown, time_t unit_sec_val){
  int i = 0;
  while(countdown > 0){
    countdown = countdown - unit_sec_val;
    ++i;
  }/*while*/
 
  if(countdown < 0){
    countdown = countdown + unit_sec_val;
    i = i-1;
  }/*if*/
  
  return i;
}/*time_conv*/
 
int main(void){
  time_t countdown, day, hour, minute, now;
  int val, num_days, num_hours, num_minutes, num_seconds, s; 
 
  now = time(0);
  s = scanf("%ld", &countdown);
   
  countdown = countdown - now;
 
  day = 24*60*60;/*Number of seconds in a day*/
  hour = 60*60;  /*Number of seconds in a hour*/
  minute = 60;   /*Number of seconds in a minute*/
 
  val = time_conv(countdown, day);
  num_days = val;
  countdown = countdown - val*day;
 
  val = time_conv(countdown, hour);
  num_hours = val;
  countdown = countdown - val*hour;
 
  val = time_conv(countdown, minute);
  num_minutes = val;
  countdown = countdown - val*minute;
  num_seconds = countdown;
 
  printf("There are %d days %d hours %d minutes and %d seconds", num_days,\
          num_hours, num_minutes, num_seconds); 
  printf(" left before Fall Break!!!\n");
 
  return 0; 
}/*main*/

