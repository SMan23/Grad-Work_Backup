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
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
 
int rows = 0, cols = 0;/* Global Variable for sparse 
                          matrix rows and columns */
 
typedef struct element{/* Sparse Matrix Element structure */
  double value;
  struct element *next;/* Creates a Linked List for each row */
} Link_List; 
 
typedef struct element *p_struct; 
 
p_struct *matrix; /* struct pointer to the matrix elements */ 
                  /* matrix[r][c] represents a particular element struct */
 
void err_check(int err){/* ERROR CATCHING */
  char err_msg[100];
 
  sprintf(err_msg, "\nAn error occured, errno = %d:", err);
 
  if(errno != 0){
    perror(err_msg);
    exit (1);
  }/*if*/
  
  return;
}/*err_check*/
  
 
void print_header( int cols){
  int i;
 
  printf("\nROW/COL |");
 
  for(i = 0; i < cols; ++i){
    if(i < 10 || i > -10) printf("  %d   ", i);
    else printf("  %d  ", i);
  }/*for*/
 
  printf("\n---------");  
 
  for(i = 0; i < cols; ++i){
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
 
  for( r = 0; r < rows; ++r){
 
    tmp = matrix[r];
    if(r < 10 || r > -10) printf("    %d   |", r);
    else printf("   %d   |", r);
    
 
    for( c = 0; c < cols; ++c){
      if(tmp[c].value != 0)
        printf("%5.3g", tmp[c].value);
      else
        printf("      ");
    }/*for*/
 
    printf("\n        |\n");  
  }/*for*/
  
  printf("\n");
 
  return;
}/*print_matrix*/
 
 
void scale_matrix( void){/* Scale Matrix */
  int r, c;
  double val = 0;
  
  for( r = 0; r < rows; ++r){/* FIND MAXIMUM */
    for( c = 0; c < cols; ++c){
      if(abs(matrix[r][c].value) > val) val = abs(matrix[r][c].value); 
    }/*for*/
  }/*for*/
 
  for( r = 0; r < rows; ++r){/* SCALE MATRIX */
    for( c = 0; c < cols; ++c){
        matrix[r][c].value = matrix[r][c].value/val;
    }/*for*/
  }/*for*/
 
} 
 
 
void pop_matrix( void){/* Populate Sparse Matrix w/ User input */
  int in = 3, r, c, s=0;
  double val;
  
  printf("\n\nPlease input data in format:\n");
  printf("row col value\n");
 
  while( (s=scanf("%d %d %lg", &r, &c, &val)) == in){
 
    if( r > rows-1 || r < 0 || c > cols-1 || c < 0){/* INVALID ROW/COL */
      printf("Error Last Input Not Recognized\n Invalid Row or Col\n"); 
      return;
    }/*if*/
    else{
      matrix[r][c].value = val;
    }/*else*/
  }/*while*/
 
  return;
}/*pop_matrix*/
 
 
void init_row(p_struct row_head){/* Initialize row */
  int c;
  p_struct tmp;
 
  tmp = row_head;
    
  for(c = 0; c < cols-1; ++c){/* For elements in row execept last*/
 
    tmp->next = &tmp[c+1];
    tmp = tmp->next;
  
  }/*for*/
  tmp->next = NULL; /* Final element in row */
 
  return;
}/*init_row*/
 
 
void alloc_mem( void){/* CREATE ROWS and COLS  */
  int r;
  p_struct *tmp;
  
  tmp = (p_struct *) malloc( rows*sizeof(p_struct)); /* Create Rows */
  if(tmp == NULL){/* Allocation Failed */
    printf("ERROR, malloc returned NULL\n"); return;
  }/*if*/
 
  matrix = tmp;
 
  for( r = 0; r < rows; ++r){
 
    tmp[r] = (p_struct) malloc( cols*sizeof(Link_List));/* Create Elements */
    if(tmp[r] == NULL){/* Allocation Failed */
      printf("ERROR, malloc returned NULL\n"); return;
    }/*if*/
 
    matrix[r] = tmp[r];
 
    init_row( tmp[r]);
      
  }/*for*/
 
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
 
  if(rows < 1 || cols < 1 || s != 2){
    printf("\nInvalid Input for rows/columns\n");
    printf("Usage: pgm_name <-<stdin> 'ROWS COLS row col value ...' \n");
    exit(0);
  }/*if*/
 
   
  /* Allocate Memory, Print */
  alloc_mem();
   
  err_check(errno);
  return 0;
}/*main*/
