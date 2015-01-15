/*
*Suleyman Muhammad
*
*ECE 8473: OSP
*Assignment 3 Problem #4
*
*Countdown to Fall Break:
*Program to compute the number of days, hours, minutes and seconds left 
*until Fall break. 
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
  time_t countdown, day, hour, minute, year, now;
  int val, num_years, num_days, num_hours, num_minutes, num_seconds, s; 
 
  now = time(0);
 
  printf("\n%ld\n", now);
  
  minute = 60;        /*Number of seconds in a minute*/
  hour   = 60*minute; /*Number of seconds in a hour*/
  day    = 24*hour;   /*Number of seconds in a day*/
  year   = 365*day;   /*Number of seconds in a year*/
 
  val = time_conv(now, year);
  num_years = val;
  now = now - val*year; 
 
  val = time_conv(now, day);
  num_days = val;
  now = now - val*day;
 
  val = time_conv(now, hour);
  num_hours = val;
  now = now - val*hour;
 
  val = time_conv(now, minute);
  num_minutes = val;
  now = now - val*minute;
  num_seconds = now;
 
  printf("There are %d years %d days %d hours %d minutes and %d seconds",\
          num_years, num_days, num_hours, num_minutes, num_seconds); 
  printf(" given from time(0)\n");
 
  return 0; 
}/*main*/

