/* an dynamically allocated array-based stack */

#include <stdio.h>
#include <stdlib.h> /* for qsort() */

int N;	     /* stack size */
int *s;      /* the stack */
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
  int first = 1, i, ss; 

  while( 1) /* read integers until EOF */
  {
    ss = scanf( "%i", &i); if( ss < 0) break;

    if( ss == 0) { printf( "bad input!\n"); break; } /*** WARNING: this line of code was not tested ***/

    if( first) { first = 0; N = i; s = malloc( N*sizeof(int) );
     if( s == 0) { printf( "malloc failed\n"); return 1; }
     printf( "N = %d\n", N);
    }
    else
      push(i);
  }

  print( "stack", s, n);

  return 0;
}

/*

sample run:

% ./a.out
4
N = 4
1
2
3
4
5
stack is full!
^D
stack:
        1
        2
        3
        4
% 

*/












