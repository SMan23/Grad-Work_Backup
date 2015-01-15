/*
*  Suleyman Muhammad
*  Graduates Computer Engineer
*  Villanova University Class '10
*
*  ECE 8743: OSP
*  Assignment 1 Problem #1 W/ MACROS
*
*  Program which implements sys_test.c Using MACROS
*/


/* Determine if char is signed or unsigned,
   find max power of 2 for char, short, int, long,
   and min/max power of 2 for float and double.
   Also determine if machine is big or little endian.
*/
#include <stdio.h>

#define LARGEST( msg, fmt, x1, x2, x3) { \
int i=0; x1 = 1; x2 = x1*2; x3 = x2/2; \
while( x3 == x1) { ++i; x1 = x2; x2 = x1*2; x3 = x2/2; } \
printf( "\t%6s: 2**%d = " fmt "\n", msg, i, x1); \
}

#define SMALLEST( msg, fmt, x1, x2, x3) { \
int i=0; x1 = 1; x2 = x1/2; x3 = x2*2; \
while( x3 == x1) { --i; x1 = x2; x2 = x1/2; x3 = x2*2; } \
printf( "\t%6s: 2**%d = " fmt "\n", msg, i, x1); \
}

int main( void)
{
  char   c1, c2, c3;
  short  s1, s2, s3;
  int    i1, i2, i3;
  long   g1, g2, g3;
  float  f1, f2, f3;
  double d1, d2, d3;
  int buf = 1;

  printf( "largest powers of 2\n");

  LARGEST( "char", "%d", c1, c2, c3);

  printf( "\t(char is %s)\n", (c2 < 0) ? "signed" : "unsigned");

  LARGEST( "short", "%d", s1, s2, s3);

  LARGEST( "int", "%d", i1, i2, i3);

  LARGEST( "long", "%ld", g1, g2, g3);

  LARGEST( "float", "%g", f1, f2, f3);

  LARGEST( "double", "%g", d1, d2, d3);

  printf( "smallest powers of 2\n");

  SMALLEST( "float", "%g", f1, f2, f3);

  SMALLEST( "double", "%g", d1, d2, d3);

  printf( "machine is %s-endian\n", ( *(char *)&buf == 1) ? "little" : "big" );

  return 0;
}

