/*
*  Suleyman Muhammad
*  Graduates Computer Engineer
*  Villanova University Class '10
*
*  ECE 8743: OSP
*  Assignment 1 Problem #1
*
*  Program to test BIG or LITTLE endian and tests C types
*/


#include <stdio.h>

int main(void){
/* MAIN VARIABLE DEFINITION */
  char a = 1, a1 = 1, a2 = 1;
  short b = 1, b1;
  int c = 1, c1, x = 1;
  long d = 1, d1;
  float e = 1, e1 = 1, e2 = 1, g = 1, g1;
  double f = 1, f1 = 1, f2 = 1, h = 1, h1;
  int i=0, j=0, k=0, l=0, m=0, n=0, o=0, p=0;
  char *y = (char *) &x;/* make a char cast for an int = 1 to determine if 
                           BIG or little endian */ 

/* DETERMINE IF CHAR IS SIGNED & IF YOUR MACHINE IS BIG ENDIAN OR LITTLE ENDIAN */

  /* Compute (a*2)/2 until the value is not equal to the original a for      
     char short int long float and double. This implies that the
     representation of that value is incorrect.  */

  while(a1 > 0){/* char */
    a = a1;
    a1 = a*2;
    a2 = a1/2;
    i++;
  }/*while*/

  if(a2 != 0) printf("char is signed\n");
  else        printf("char is unsigned\n");

  /* BIG ENDIAN or LITTLE ENDIAN */
  if(y[0] == 0) printf("This machine is BIG endian\n");
  else         printf("This machine is little endian\n");   

  while(b > 0){/* short */
    b = b*2;
    b1 = b/2;
    j++;
  }/*while*/

  while(c > 0){/* int */
    c = c*2;
    c1 = c/2;
    k++;
  }/*while*/

  while(d > 0){/* long */
    d = d*2;
    d1 = d/2;
    l++;
  }/*while*/

  while(e == e2){/* float */
    e = e1;
    e1 = e*2;
    e2 = e1/2;
    m++;
  }/*while*/

  while(g > 0){/* float negative exp */
    g = g/2;
    g1 = g*2;
    o++;
  }/*while*/


  while(f == f2){/* double */
    f = f1;
    f1 = f*2;
    f2 = f1/2;
    n++;
  }/*while*/

  while(h > 0){/* double negative exp */
    h = h/2;
    h1 = h*2;
    p++;
  }/*while*/

  /*This section is because the iterations count the power of 2 that 
  cannot be represented by the corresponding data type*/
  i = i-1;
  j = j-1;
  k = k-1;
  l = l-1;
  m = m-1;
  n = n-1;
  o = o-1;
  p = p-1;

printf("The largest positive power of 2 represented with char  is %d\n", i);
printf("The largest positive power of 2 represented with short is %d\n", j);
printf("The largest positive power of 2 represented with int is %d\n", k);
printf("The largest positive power of 2 represented with long is %d\n", l);
printf("The largest positive and negative powers of 2 represented with float are %d and %d respectively\n", m, o);
printf("The largest positive and negative powers of 2 represented with double are %d and %d respectively\n", n, p);

return 0;
}

