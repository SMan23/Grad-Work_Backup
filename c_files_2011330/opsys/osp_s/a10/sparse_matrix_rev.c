/*
*  Suleyman Muhammad
*  Graduates Computer Engineer
*  Villanova University Class '10
*
*  ECE 8743: OSP
*  Assignment 10
*
*  C program which takes as its input initially the total number of 
*  rows/columns a sparse matrix will contain. Every triple set of
*  inputs subsequent to that will be the row column and value of 
*  an element of the matrix. Once the matrix is fully populated
*  it is then scaled by the largest (absolute) element value
*
*  REVISION: MATRIX changed to a 1 dimensional array of pointers to 
*  the heads of linked lists
*/

/** UNFINISHED... SEG FAULTS WHEN ALLOCATING MEMORY AND OTHER ISSUES **
    I WAS WORKING LAST ON THE INTERM POINTER ARRAY(NOT SUITABLE) **/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
 
int rows = 0, cols = 0;/* Global Variable for sparse 
                          matrix rows and columns */


 
typedef struct element{/* Sparse Matrix Element structure */
  double value;
  int column;
  struct element *next;/* Creates a Linked List for each row */
} Link_List; 
 
typedef struct element *p_struct; 


int *r_count;     /* Row array which keeps track of the number of elements in individual rows */

p_struct *interm; /* Intermediate pointer to matrix of elements */
p_struct matrix;  /* Struct pointer to the matrix elements */ 
                  /* Matrix[r] represents the head of a list of elements */
 
void err_check(int err){/* ERROR CATCHING */
  char err_msg[100];
 
  sprintf(err_msg, "\nAn error occured, errno = %d:", err);
 
  if(errno != 0)
  {
    perror(err_msg);
    exit (1);
  }/*if*/
  
  return;
}/*err_check*/
  
 
void print_header( int cols){
  int i;
 
  printf("\nROW/COL |");
 
  for(i = 0; i < cols; ++i)
  {
    if(i < 10 || i > -10) printf("  %d   ", i);
    else printf("  %d  ", i);
  }/*for*/
 
  printf("\n---------");  
 
  for(i = 0; i < cols; ++i)
  {
    printf("------");
  }/*for*/
 
  printf("\n");
 
  return;
}/*print_header*/
 
 
void print_matrix( void){/* Print Matrix */
  int r, c;
  p_struct tmp;/* temporary pointer to a matrix element */
               /* along a particular row */ 
  printf("\n");
 
  print_header(cols);
 
  for( r = 0; r < rows; ++r)
  {
    tmp = &matrix[r];
    
    if(r < 10 || r > -10) printf("    %d   |", r);
    else printf("   %d   |", r);
    
    for( c = 0; c < cols; ++c)
    {
      while(tmp != NULL)
      {
        if(tmp->column == c)
          printf("%3g  ", tmp->value);
        else
          printf("      ");
        tmp = tmp->next;
      }/*while*/

    }/*for*/
 
    printf("\n        |\n");  
  }/*for*/
  
  printf("\n");
 
  return;
}/*print_matrix*/
 
 
void scale_matrix( void){/* Scale Matrix */
  int r;
  double val = 0;
  p_struct tmp;
  
  for( r = 0; r < rows; ++r)/* FIND MAXIMUM */
  {
    tmp = &matrix[r];
    while(tmp != NULL)
    {
      if(abs(tmp->value) > val) val = tmp->value;
      tmp = tmp->next; 
    }/*while*/
  }/*for*/
 
  for( r = 0; r < rows; ++r)/* SCALE MATRIX */
  {
    while(tmp != NULL)
    {
      tmp->value = tmp->value/val;
      tmp = tmp->next;
    }/*for*/
  }/*for*/
 
} 
 
 
void add_element( int r, int c, double val){/* Add element into Linked List, update # of elements */
  p_struct tmp;  

  tmp = malloc( sizeof(p_struct));
  if(tmp == NULL)/* malloc failed */
  {
    printf("ERROR, malloc returned NULL"); return;
  }/*if*/

  interm[r]->next = tmp;
  interm[r]->column = c;

  interm[r] = tmp;
  interm[r]->next = NULL;
    
  return;
}/*add_element*/
 
 
void pop_matrix( void){/* Populate Sparse Matrix w/ User input */
  int in=3, r, c, s=0;
  double val;
  
  printf("\n\nPlease input data in format:\n");
  printf("row col value\n");
 
  while( (s=scanf("%d %d %lg", &r, &c, &val)) == in)
  { 
    if( r > rows-1 || r < 0 || c > cols-1 || c < 0)/* INVALID ROW/COL */
    {
      printf("Error Last Input Not Recognized\n Invalid Row or Col\n"); 
      return;
    }/*if*/
    else
    {
      printf("test 1\n");
      add_element(r,c,val);
      printf("test 2\n");
    }/*else*/
  }/*while*/
 
  return;
}/*pop_matrix*/
 
 
void alloc_mem( void){/* CREATE ROWS and COLS  */
  int i;
 
  matrix = malloc( rows*sizeof(p_struct)); /* Create Rows */
  if(matrix == NULL)/* Allocation Failed */
  {
    printf("ERROR, malloc returned NULL\n"); return;
  }/*if*/

  for(i = 0; i < rows; ++i) interm[i] = &matrix[i];
 
  r_count = calloc( cols, sizeof(int));
  pop_matrix();
 
  printf("\n\n  UNSCALED SPARSE MATRIX  ");
  print_matrix();
 
  scale_matrix();
 
  printf("\n   SCALED SPARSE MATRIX  ");
  print_matrix();
 
  free(matrix);
 
  return;
}/*alloc_mem*/
  
  
int main( void){
  int s;
  
  errno = 0;/* Initialize error number to 0 */
 
  s = scanf("%d %d", &rows, &cols);
 
  if(rows < 1 || cols < 1 || s != 2)
  {
    printf("\nInvalid Input for rows/columns\n");
    printf("Usage: pgm_name <-<stdin> 'ROWS COLS row col value ...' \n");
    exit(0);
  }/*if*/
 
   
  /* Allocate Memory, Print */
  alloc_mem();
   
  err_check(errno);
  return 0;
}/*main*/
