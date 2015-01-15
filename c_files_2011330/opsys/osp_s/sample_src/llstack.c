/* linked-list stack */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef
struct element
{
  int value;
  struct element *next;
} Element;

struct element *s = NULL;    /* the stack */

void push( int x)
{
  Element *e = malloc( sizeof(Element) );
  if( e == NULL) { printf( "malloc failed\n"); return; }
/*
  s == e2 -> e1 -> NULL

  s == e -> e2 -> ...
*/
  e->value = x;

  e->next = s;
  s = e;
}

int pop( void)
{
  int r; Element *e;

  if( s == NULL) { printf( "stack is empty!\n"); return 0; }

  r = s->value;

  e = s;
  s = s->next;
  free( e);

  return r;
}

void clear( void) {  }

void print( const char msg[])
{
  Element *e;

  printf( "%s:\n", msg);

  for( e = s; e != NULL; e = e->next) printf( "\t%i\n", e->value);
}

void add( void)
{
    push( pop() + pop() );
}

typedef void (*Func)(void);

struct { char *name; Func f; } table[] =
{
	{ "add", add },
	{ "+",   add },
	{   0,   0   }
};

void process_word( char word[])
{
   int i, ss;
/* need loop here, check table[i].name ... */
   if( strcmp( word, table[0].name) == 0)
   {
    table[0].f();  return;
   }
   else
   {
    ss = sscanf( word, "%i", &i); if( ss < 0) return; /*** FIX ME! ***/
    if( ss == 0) { printf( "bad input!\n"); return; }
    push(i);
   }
}

#define SPACE " \t\r\n\f\v"

void process_line( char line[])
{
   char *word;
   if( (word = strtok( line, SPACE)) != NULL )
   do {
    process_word( word);
   } while( (word = strtok( NULL, SPACE)) != NULL);

   print( "stack");
}

void process_file( FILE *fp)
{
  char line[BUFSIZ];
  while( fgets( line, BUFSIZ, fp) )
   process_line( line);
}

int main( void)
{
 process_file( stdin);
 return 0;
}

/*

sample run:

% ./a.out
1 2 3
stack:
        3
        2
        1
4 add 5
stack:
        5
        7
        2
        1
%

*/











