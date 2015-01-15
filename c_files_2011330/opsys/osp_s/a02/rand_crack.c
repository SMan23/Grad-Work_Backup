/*
** Suleyman Muhammad
**
** Cracking Rand()
**
** Inputs into the program are the first 3 rand() values used for encryption
** and from that it is easy to crack because the rand() is initialized at some 
** time (time(0)). Using the reverse method one is able to decrypt.
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
  
int main(void){
  int i = 1, temp0, temp1, temp2,\
          c, test0, test1, test2; 
 
  srand(time(0));
 
  temp0 = rand();/*temporary rand() values*/
  temp1 = rand();
  temp2 = rand();
  scanf("%d",&test0);/*Given rand() values*/
  scanf("%d",&test1);
  scanf("%d",&test2);
 
  while(temp0 != test0 || temp1 != test1 || temp2 != test2){
    srand(time(0)-i); /*Continue rand() intitialization until testX = tempX*/
    temp0 = rand();
    temp1 = rand();
    temp2 = rand();
    ++i;
  }/*while*/
 
  getchar(); /*handles new line character*/
 
  while(1){
    if((c = getchar()) == EOF) break;
    else putchar(c^rand());/*decryption*/
  }/*while*/
 
  return 0;/*exit program*/
}/*main*/

