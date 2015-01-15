/*
** Suleyman Muhammad
** Graduates Computer Engineer
** Villanova University Class '10
**
** ECE 8743: OSP
** Assignment 7 Problem #1
**
** Program which implements and tests some string functions    
** written from scratch
*/
 
#include <stdio.h>
#include <stdlib.h>
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
 
 
int SLF( const char s[]){/* String Length Function */
  int len = 0;
  
  while(s[len] != '\0') ++len;
 
  return len;
}/*SLF*/
 
/*char *test( char funct, char string)*/
 
 
char *strcpy( char s1[], const char s2[]){
  int len2 = SLF(s2), i;
 
  for(i = 0; i < len2; ++i){/* Copy Characters from */
    s1[i] = s2[i];              /* s2 into s1 */
  }/*for*/
 
  s1[i] = '\0'; /* input end character at s1[len1] */
  
  return s1;
}/*strcpy*/
 
 
char *strdog( const char s1[], char s2[]){/* Prepend s1 to s2 */
  int len1 = SLF(s1), len2 = SLF(s2), i, j, k;
  
  i = len1-1; j = len2-1; 
  k = len1 + len2 -1;  
 
  for(; j >= 0; --j, --k) s2[k] = s2[j];/* copy the values of  
                                         s2 into the correct */ 
                                           /* position */
 
  for(; i >= 0; --i) s2[i] = s1[i];/* Prepend s1 into the start
                                              of s2 */
  return s2;
}/*strdog*/
 
 
char *strrm( char s1[], const char s2[]){/* Remove Characters in
                                               s2 from s1 */
  int len1 = SLF(s1), len2 = SLF(s2),\
      i = 0, j = 0, k = 0;
 
  for(; k < len2; ++k){/* for each value s2[k] */
 
    for(; i < len1; ++i){     
      if( s1[i] != s2[k]){
        s1[j] = s1[i]; /* Overwrite array only with characters */
        ++j;                  /* not included in s2 */
      }/*else*/
    }/*for*/
    
    s1[j] = '\0'; /* INPUT ARRAY END CHARACTER */
    i = 0; j = 0;
 
  }/*for*/
 
  return s1;
}/*strrm*/
 
 
char *strcrm( char s1[], const char s2[]){/* Remove Compliment 
                                             of characters in  */
                                          /*   s2 from s1      */
  int len1 = SLF(s1), len2 = SLF(s2),\
    i, j = 0, k;

  for(i = len1; i < 2*len1; ++i) s1[i] = ' ';
 
  for(i = 0; i < len1; ++i){

    for(k = 0; k < len2; ++k){/* for each value s2[k] */
      if( s1[i] == s2[k]){
        s1[len1+i] = s1[i]; /* Overwrite array only with characters */
        ++j;                  /* included in s2 */
      }/*if*/
    }/*for*/ 
 
  }/*for*/

  s1[j] = '\0';

  j = 0;

  for(i = len1; i < 2*len1; ++i){
    if(s1[i] != ' '){
      s1[j] = s1[i];
      ++j;
    }/*if*/
  }/*for*/  
 
  return s1;
}/*strcrm*/
 
 
char *strrev( char s[]){/* Reverse order of characters in */
  int len = SLF(s), i, j;
  j = 2*len - 1;
  
  /* Store the reverse of s in upper half of the array*/
  for(i = 0; i < len; ++i, --j) s[j] = s[i];
  /* Slide the reverse of s into position */
  for(i = 0, j = len; i < len; ++i, ++j ) s[i] = s[j];
  /* Insert End of Array character at s[len] */
  s[i] = '\0';
  
  return s;
}/*strrev*/
 
 
int main( void){
  char s[BUFSIZ] = "abc", s1[BUFSIZ] = "defg",\
       s2[BUFSIZ] = "hijkl", *p, *q;  
 
  errno = 0;/* Initialize error number to 0 */

  printf( "\nString Function Test:\n");
   
  printf( "\ns1 = \"%s\" s2 = \"%s\"", s1, s2); 
  printf( "\nstrdog s2 = \"%s\"\n", strdog(s1, s2)); 
 
  p = strcpy( s1, "AABZBAADZDAA");
  printf( "\ns1 = \"%s\" s2 = \"%s\"", s1, "ZA");
  printf( "\nstrrm s1 = \"%s\"\n", strrm( p, "ZA"));
 
  q = strcpy( s1, "AABZBAADZDAA");
  printf( "\ns1 = \"%s s2 = %s\"", s1, "ZA");
  printf( "\nstrcrm s1 = \"%s\"\n", strcrm( q, "ZA"));
 
  printf( "\ns = \"%s\"", s);
  printf("\nstrrev s = \"%s\"\n\n", strrev(s));
 
  err_check(errno);
  return 0;
}/*main*/

