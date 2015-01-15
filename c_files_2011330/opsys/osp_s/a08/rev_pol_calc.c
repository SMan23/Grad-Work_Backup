/*
**  Suleyman Muhammad
**  Graduates Computer Engineer
**  Villanova University Class '10
**
**  ECE 8743: OSP
**  Assignment 8 Problem #1
**
**  REVERSE-POLISH CALCULATOR:
**  Accepts basic operators on a dynamic stack which uses a LIFO
**  (last in first out) queing style
*/

/* NEED TO IMPLEMENT PROPER USER INTERFACE; PROGRAM REPRINTS INPUT CHARACTERS FOR INPUT FILE REDIRECTION */

 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
 
int N = 0;  /* Stack SIZE*/
int n = 0;  /* Elements in Stack*/
double *s = 0; /* Stack */
 
void err_check(int err){/* ERROR CATCHING */
  char err_msg[100];
 
  sprintf(err_msg, "\nAn error occured, errno = %d:", err);
 
  if(errno != 0){
    perror(err_msg);
    exit (1);
  }/*if*/
  
  return;
}/*err_check*/

void clear( void){ n = 0; free(s); s = NULL; N = 0;} /* Change the # of elements to 0 */


double POP( void){/* POP the next value from the stack */

  if(n == 0){/* Stack empty */
    printf("Stack Empty\n"); return 0;
  }/*if*/

  --n; return s[n];/* Decrement # of elements, POP S[n]*/
}/*POP*/


void PUSH( double x){/* PUSH x into the stack, update # of elements*/
  int new_N; double *new_s;  

  if(n == N){/* Stack is Full or not initialized */
    new_N = 1.5*N + 5;/* Use temp values to protect your stack */
    new_s = realloc( s, new_N*sizeof(double));
    
    if(new_s == NULL){/* Reallocate failed */
      printf("ERROR, realloc returned NULL"); return;
    }/*if*/

    N = new_N; s = new_s;
  }/*if*/

  s[n] = x; ++n;
  return;
}/*PUSH*/

void duplicate( void){/* Duplicate the last value in the stack */

  if( n == 0){
    printf("Stack Empty\n"); return;
  }/*if*/

  PUSH(s[n-1]); return;/* PUSH duplicate onto the stack */
}/*duplicate*/


void print_contents( const char msg[], const double val[], int E){
  int i; 

  printf("%s:", msg);
  for(i = 0; i < E; ++i) printf("\t%f\n", val[i]);  

  return;
}/*print_contents*/


void parse_word( char word[]){
  int string_s; double x;

  if( strcmp( word, "dup") == 0) duplicate();
  else
    if(strcmp( word, "clear") == 0) clear();
  else
    if(strcmp( word, "exit") == 0) exit(0);
  else
    if(strcmp( word, "quit") == 0) exit(0);
  else
    if(strcmp( word, "sqrt") == 0) PUSH( sqrt( POP() ));
  else
    if(strcmp( word, "+") == 0) PUSH( POP() + POP() );
  else
    if(strcmp( word, "-") == 0){x = POP();  PUSH( POP()-x );}
  else
    if(strcmp( word, "*") == 0) PUSH( POP() * POP() );
  else
    if(strcmp( word, "/") == 0){x = POP();  PUSH( POP()/x );}
  else{
    string_s = sscanf(word, "%lf", &x); if( string_s < 0) return;
    if(string_s == 0){ printf("Invalid Input\n"); return;}
    PUSH(x);
  }/*else*/
  
  return;
}/*parse_word*/


#define SPACE " \t\r\n\f\v"

void parse_line( char line[]){/*Parse Line*/
  char *word;/* pointer to first word to parse */

  if( (word = strtok(line, SPACE)) != NULL){
    do{ parse_word(word);
    } while( (word = strtok( NULL, SPACE)) != NULL);
  }/*if*/

  return;
}/*parse_line*/


void parse(FILE *fp){/* Parse Standard Input*/
  char line[BUFSIZ];/* Line from file to parse */

  while( fgets(line, BUFSIZ, fp)){
    puts(line); 
    parse_line(line);
    print_contents("stack", s, n);
    printf("\n\n");
  }

  return;
}/*parse*/

 
int main( void){
  errno = 0;/* Initialize error number to 0 */

  setbuf( stdout, 0);/* Eliminate stdout buffering */

  parse( stdin);/* Begin Parsing Standard Input*/ 

  err_check(errno);
  return 0;
}/*main*/
