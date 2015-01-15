 
/*------------------------------------------------------------*/
/*  Program chapter2_1                                        */
/*                                                            */
/*  This program prints two                                   */
/*  values as characters and integers.                        */
 
#include <stdio.h>
 
int main(void)
{
   /*  Declare and initialize variables.  *
   char ch ='a';
   **/
   int  ch = 97;    /* Change Char to Int*/
   int  i= 97;
 
   /**
   ++ch; ++i;       * Char and Int incrementors*/

   /**/
   ch += 2; i += 2; /* Char and Int incremented by 2*/
   

   /*  Print both values as characters.  */
   printf("value of ch: %c; value of i: %c \n",ch,i);
 
   /*  Print both values as integers.  */
   printf("value of ch: %i; value of i: %i \n",ch,i);
   
   /*   Exit program.  */
   return 0;
}
/*------------------------------------------------------------*/
 
