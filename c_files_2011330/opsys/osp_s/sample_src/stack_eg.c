/* an array-based stack */

/* with stack print modified to take string and array arguments */

#include <stdio.h>
#include <stdlib.h> /* for qsort() */

#define N 30 /* stack size */
int s[N];    /* the stack */
int n; 	     /* number of elements on the stack */

int compare( const void *v1, const void *v2)
{
  const int *pi1 = (const int *) v1;
  const int *pi2 = (const int *) v2;

  if( *pi1 < *pi2) return -1;	/* or use +1 here and -1 below to sort in decreasing order */

  else if (*pi1 > *pi2) return +1;

  else return 0;
}

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

/*** new and improved print function: ***/

void print( const char msg[], const int a[], int m)
{
  int i;

  printf( "%s:\n", msg);

  for( i = 0; i < m; ++i) printf( "\t%i\n", a[i]);
}

/*** ***/

int main( void)
{
  int i, ss; 

  while( 1) /* read integers until EOF */
  {
    ss = scanf( "%i", &i); if( ss < 0) break;

    if( ss == 0) { printf( "bad input!\n"); break; } /*** WARNING: this line of code was not tested ***/

    push(i);
  }

  print( "stack", s, n);	/* print the whole stack */

  print( "s+2,5", s+2, 5);	/* print part of the stack */

  qsort( s, n, sizeof(int), compare);

  print( "sorted", s, n);

  return 0;
}

/*

sample run:

% cat nums
1
2
4
7
10
6
3
9
8
5
% ./a.out < nums
stack:
        1
        2
        4
        7
        10
        6
        3
        9
        8
        5
s+2,5:
        4
        7
        10
        6
        3
sorted:
        1
        2
        3
        4
        5
        6
        7
        8
        9
        10
% 

*/












