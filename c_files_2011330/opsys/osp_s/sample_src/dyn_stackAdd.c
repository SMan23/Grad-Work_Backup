/* an array-based stack, with ``add'' command */

#include <stdio.h>
#include <stdlib.h> /* for qsort() */
#include <string.h>

#define N 30 /* stack size */
int s[N];    /* the stack */
int n; 	     /* number of elements on the stack */

void push( int x)
{
  if( n == N) { printf( "stack is full!\n"); return; }

  s[n] = x;

  ++n;
}

int pop( void) /*** this function was not tested ***/
{
  if( n == 0) { printf( "stack is empty!\n"); return 0; } /*** WARNING: this line of code was not tested ***/

  --n;

  return s[n];
}

void clear( void) { n=0; } /*** this function was not tested ***/

void print( const char msg[], const int a[], int m)
{
  int i;

  printf( "%s:\n", msg);

  for( i = 0; i < m; ++i) printf( "\t%i\n", a[i]);
}

int main( void)
{
  char line[BUFSIZ];
  int i, ss; 

  while( fgets( line, BUFSIZ, stdin))
  {
   if( strcmp( line, "add\n") == 0)
   {
    push( pop() + pop() );
   }
   else
   {
    ss = sscanf( line, "%i", &i); if( ss < 0) break;
    if( ss == 0) { printf( "bad input!\n"); break; }
    push(i);
   }
  }

  print( "stack", s, n);

  return 0;
}

/*

sample run:

% ./a.out
1
2
3
add
^D
stack:
        1
        5
% 

*/












