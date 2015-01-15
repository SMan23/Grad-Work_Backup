/*
**  Suleyman A. Muhammad
**  Graduate Computer Engineer
**  Villanova University Class '10
**  Villanvoa Grad Class '11
**
**  Program to compute time until specific appointment (Eastern US timezone)
**  Partially written for Valentines day 2011
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

#define  HOUR_S 3600        /* Number of seconds in a hour */
#define  DAY_S  24*3600     /* Number of seconds in a day */
#define  YEAR_S 365*24*3600 /* Number of seconds in a year*/

int DBUG = 0;
int leap_bool = 0;

enum months{
  january,
  februrary,
  march,
  april,
  may,
  june,
  july,
  august,
  september,
  october,
  november,
  december
};/*enum*/

/*convert months from seconds*/
time_t month_op(int month_val){
  time_t secs;
  
  switch(month_val){
    case january:{/* JANUARY */
      secs = 0;
      break;
    } /* full month not complete; days contain sec val for days of month */
    case februrary:{/* FEBRURARY */
      secs = DAY_S*31;
      break;
    }  /* jan(31) */
    case march:{/* MARCH */
      secs = DAY_S*59;
      if(leap_bool) secs += DAY_S;
      break;
    }  /* jan + feb(28) */
    case april:{/* APRIL */
      secs = DAY_S*90;
      if(leap_bool) secs += DAY_S;
      break;
    }  /* jan + feb + march(31) */
    case may:{/* MAY */
      secs = DAY_S*120;
      if(leap_bool) secs += DAY_S;
      break;
    } /* jan + feb + march + april(30) */
    case june:{/* JUNE */
      secs = DAY_S*151;
      if(leap_bool) secs += DAY_S;
      break;
    } /* jan + feb + march + april + may(31) */
    case july:{/* JULY */
      secs = DAY_S*181;
      if(leap_bool) secs += DAY_S;
      break;
    } /* j + f + m + a + m + june(30) */
    case august:{/* AUGUST */  
      secs = DAY_S*212;
      if(leap_bool) secs += DAY_S;
      break;
    } /* j + f + m + a + m + j + july(31) */ 
    case september:{/* SEPTEMBER*/
      secs = DAY_S*243;
      if(leap_bool) secs += DAY_S;
      break;
    } /* j + f + m + a + m + j + j + august(31) */
    case october:{/* OCTOBER */
      secs = DAY_S*273;
      if(DBUG) printf("\nHERE\n");
      if(leap_bool) secs += DAY_S;
      break;
    } /* j + f + m + a + m + j + j + a + september(30)*/
    case november:{/* NOVEMBER */
      secs = DAY_S*304;
      if(leap_bool) secs += DAY_S;
      break;
    } /* j + f + m + a + m + j + j + a + s + october(31)*/
    case december:{/* DECEMBER */
      secs = DAY_S*334;
      if(leap_bool) secs += DAY_S;
      break;
    } /* j + f + m + a + m + j + j + a + s + o + november(30)*/
    default:{
      printf("Input error, INVALID MONTH: %d\n", (month_val+1));  
      exit(0);
    }/*default*/
  }/*switch*/

  return secs;
}/*month_op*/


int time_conv(time_t apptmnt_s, time_t unit_sec_val){
  int i = 0;
  while(apptmnt_s > 0){
    apptmnt_s -= unit_sec_val;
    ++i;
  }/*while*/
 
  if(apptmnt_s < 0){
    i = i-1;
  }/*if*/
  
  return i;
}/*time_conv*/


int check_date(int day, int month, int year){
  int check = 0, keish_age = 1987, my_age = 1988, a_year = 2009;

  char c;

  FILE *fd2;

  keish_age = year - keish_age;
  my_age = year - my_age;
  a_year = year - a_year;

  if(day == 26 && (month+1) == 1){/* 1/26 */

    /*Read File and Print to stdout*/
    fd2 = fopen("b_day.aa", "r");
    while((c = fgetc(fd2)) != EOF) putchar(c);
    fclose(fd2);

    printf("\n\tThats Your BIRTHDAY!!!... You will be %d years old, ", keish_age); 
    printf("\n\t\t\tWowiee old as hell\n\t\tImma get u something nice :-)\n\n");
    check = 1;
  }/*if*/

  if(day == 26 && (month+1) == 10){/* 10/26 */
    printf("\n\tThats my birthday, nothing special... I will be %d years old, ", my_age); 
    printf("\n\t\tYou dont have to get me anything\n\n");
    check = 2;
    if(year == 2012) check = 3;
  }/*if*/

  if(day == 22 && (month+1) == 2){/* 2/22 */
    
    /*Read File and Print to stdout*/
    fd2 = fopen("anniversary.aa", "r");
    while((c = fgetc(fd2)) != EOF) putchar(c);
    fclose(fd2);
      
    printf("\n\t\tThats our ANNIVERSARY!!!... %d years huh?, ", a_year); 
    printf("\n\tWe have many more after this, but each one is just as important\n\n");
    check = 4;
  }/*if*/

  if(day == 14 && (month+1) == 2 && year == 2011){/* 1/26 */
    printf("\n\n\tDang... we missed valentines day but...\n\n"); 
    check = 5;
  }/*if*/

  return check;
}/*check_date*/


/*MAIN*/
int main(int argc, char* argv[]){

  /*switch_offset used to allow correct ascii representation of data value for switch*/
  int  day, month, year, leap, year_offset, hour, i, j, check = 0, EST,\
       apptmnt_y, apptmnt_d, apptmnt_h, apptmnt_m, apptmnt_s, s, f;

  time_t  sec_h, sec_d, sec_m, sec_y, sec_total, current, raw_T, leap_offset, apptmnt_sec;

  struct tm * local_T;

  FILE *fd;/* File Descriptors */

  char P_A[2], c; /* PM or AM */
  char err_msg[100];

  if((argc == 2) && (atoi(argv[1]) == 1)) DBUG = 1;

  /* GENERIC ERROR CATCHING */
  sprintf(err_msg, "There was an error in your input, error# %d", errno);
  errno = 0; /*Initialize Error Number to 0*/

  /* GATHER INPUT DATA */
  if((argc == 2) && (atoi(argv[1]) == 0)){/* Shell Script */ /*REVISION COMMAND LINE DOES NOT USE*/
    fd = fopen("love.tmp", "r");
    f = fscanf(fd, "%d%s %d %d %d", &hour, P_A, &month, &day, &year);

    if(f != 5){/* fscanf error catching*/
      printf("\n\nInput Error: read error or insufficient arguments\n");
      printf("please use specified format\n\n");
      exit(0);
    }/*if*/

    fclose(fd);
  }/*if*/
  else{ /* Command Line * NEED FIX */
    /*printf("\nInput Appointment Date and Time in following format:\n\n");
    printf("Hour(PM/AM) Month Day Year\n");*/ 
    s = scanf("%d%s %d %d %d", &hour, P_A, &month, &day, &year);

    if(s != 5){/* scanf error catching */
      printf("\n\nInput Error: read error or insufficient arguments\n");
      printf("please use specified format\n\n");
      exit(0);
    }/*if*/
  }/*else*/
  

  month = month - 1; /* To account for enum zero index */

  /*Convert hour to Calculatable time format*/
  if( ((strcmp(P_A, "PM") == 0) || (strcmp(P_A, "pm") == 0)) && hour <= 12) hour += 12;


  /* DETERMINE UTC TIME OFFSET DEPENDING ON DST */
  time(&raw_T);
  local_T = localtime(&raw_T); /* tm structure containing local time information */

  if(local_T->tm_isdst) EST = 4; /* Daylight Savings Time */
  else EST = 5;

  current = time(0)-(EST*HOUR_S);/*time in seconds from 12AM on 1/1/1970 to now*/

  /* offset used by time(0) : begins 12AM 1/1/1970 */
  year_offset = year-1970;

  leap = 0; /* Initialize Leap Variable */

  for(j=1970; j <= year; ++j){
    if( (j % 4) == 0) ++leap; /* Increment leap for each leap year */
  }

  leap_offset = leap*DAY_S; /* Calculate # of Leap Years in seconds*/
  
  if((year % 4) == 0) leap_bool = 1;

  for(i='a'; i <= 'd'; ++i){
    switch(i){
      case 'a' :{
        sec_h = hour*HOUR_S;
        if(DBUG) printf("\nsec hours: %ld\n", sec_h);
        break;
      }/*case'a'*/
      case 'b':{
        sec_d = (day-1)*DAY_S; /* Do not want to count current day */
        if(DBUG) printf("\nsec days: %ld\n", sec_d);
        break;
      }/*case'b'*/
      case 'c':{
        sec_m = month_op(month);
        if(DBUG) printf("\nsec months: %ld\n", sec_m);
        break;
      }/*case'c'*/
      case 'd':{/*remove offset from input date*/
        sec_y  =  year_offset*YEAR_S;
        sec_y  += leap_offset;
        if(DBUG) printf("\nsec years: %ld\n", sec_y);
        break;
      }/*case'd'*/
      default: printf("ERROR counter out of domain\n");
    }/*switch*/
  }/*for*/

  sec_total = sec_h + sec_d + sec_m + sec_y;
  if(DBUG) printf("\ncalculated %ld\ncurrent %ld\n", sec_total, current);
  
  apptmnt_sec = sec_total - current;

  if(DBUG) printf("\ncheck %ld\n\n", (sec_total - current));

  check = check_date(day, month, year);  

  if(apptmnt_sec <= 0 && check !=5){
    if(check) printf("\n\tMama you know thats already passed\n\tI love you... but your crazy\n\n");
    else printf("\n\tSorry, Im pretty sure you already missed that appointment\n\n");

    if(check == 4){/* ANNIVERSARY */
       /*Read File and Print to stdout*/
       fd = fopen("anniversary3.aa", "r");
       while((c = fgetc(fd)) != EOF) putchar(c);
       fclose(fd);
    }/* if */

    exit(0);
  }/*if*/

  
  /*Convert from seconds to years, days, hours, minutes, and seconds */
  apptmnt_y = time_conv(apptmnt_sec, YEAR_S); apptmnt_sec -= apptmnt_y*YEAR_S;
  apptmnt_d = time_conv(apptmnt_sec, DAY_S);  apptmnt_sec -= apptmnt_d*DAY_S;
  apptmnt_h = time_conv(apptmnt_sec, HOUR_S); apptmnt_sec -= apptmnt_h*HOUR_S;
  apptmnt_m = time_conv(apptmnt_sec, 60);     apptmnt_sec -= apptmnt_m*60;
  apptmnt_s = apptmnt_sec;

  if(check != 5){

    if(check) printf("\n\tIt's in ");
    else printf("\n\tWhats so special about that date?\n\tIt's in ");
    /* OUTPUT TIME INFORMATION */
    if(apptmnt_y > 0){
      if(apptmnt_y > 1) printf("%d Years ", apptmnt_y);
      else printf("%d Year ", apptmnt_y);
    }/*if*/
    if(apptmnt_d > 0){
      if(apptmnt_d > 1) printf("%d Days ", apptmnt_d);
      else printf("%d Day ", apptmnt_d);
    }/*if*/
    if(apptmnt_h > 0){
      if(apptmnt_h > 1) printf("%d Hours ", apptmnt_h);
      else printf("%d Hour ", apptmnt_h);
    }/*if*/
    if(apptmnt_m > 0){
      if(apptmnt_m > 1) printf("%d Minutes ", apptmnt_m);
      else printf("%d Minute ", apptmnt_m);
    }/*if*/
    if(apptmnt_s > 0){
      if(apptmnt_s > 1) printf("and %d Seconds\n", apptmnt_s); 
      else printf("%d Second\n", apptmnt_s);
    }/*if*/
    printf("\n");

    if(check == 1){/* Keshia's Birthday */
       sleep(7);
       /*Read File and Print to stdout*/
       fd = fopen("b_day2.aa", "r");
       while((c = fgetc(fd)) != EOF) putchar(c);
       fclose(fd);
    }/*if*/
    else if(check == 4){/* Keshia's Birthday */
       /*Read File and Print to stdout*/
       fd = fopen("anniversary3.aa", "r");
       while((c = fgetc(fd)) != EOF) putchar(c);
       fclose(fd);
    }/*else if*/
  }/*if*/
  else{
    printf("\n\tI have a special surprise for you...");
    sleep(2);
    printf("\n\tIts a little puzzle\n");
    sleep(2);
    printf("\n\tWhat almost rhymes with Bronze Trash Table?");
    printf("\n\tYou have 30 seconds\n");
    sleep(30);
    printf("\n\tTimes up... Look in the Comcast Bag silly butt\n\n");
    printf("\n\t\tHAPPY VALENTINES DAY\n\n");
    
    /*Read File and Print to stdout*/
    fd = fopen("heart.aa", "r");
    while((c = fgetc(fd)) != EOF) putchar(c);
    fclose(fd);
  }

  if(errno != 0) perror(err_msg);

  return 0;
}/*main*/
