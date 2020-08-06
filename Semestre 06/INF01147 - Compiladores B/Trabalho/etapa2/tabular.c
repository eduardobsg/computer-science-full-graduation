////////////////////////////////////////////////////////////////////////////////
//
//  Tabular Descendent Syntatic Analyzer
//  Marcelo Johann - PUCRS - Uruguaiana 2001
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Here we must define terminal and non terminal symbols, limited to 256.
// Terminals first, and FIRST_NON indicates the first non terminal char.
// MAX_TOKEN can be used to reduce table size, but limited to 256 (see below).

#define EPSILON		0
#define TER_ID		1
#define TER_PEV		2
#define TER_IGUAL	3
#define TER_MAIS	4
#define TER_MUL		5
#define TER_ABRE	6
#define TER_FECHA	7
#define TER_NUM		8
#define TER_BEG		9
#define TER_END		10
#define TER_FIM		11
#define FIRST_NON	12
#define NON_F		12
#define NON_S		13
#define NON_R		14
#define NON_T		15
#define NON_E		16
#define NON_CMD		17
#define NON_RESTO	18
#define NON_LCMD	19
#define NON_BL		20

#define MAX_TOKEN	21

// These are general defines for all parsers

#define FALSE		0
#define	TRUE		1
#define TERMINAL(a)	( a < FIRST_NON ? 1 : 0 )
#define MAX_STACK	20

// This is the Parser Table, again for all parsers
// Each entry contains 0 or a poiter to a right hand side of a production
// Productions are represented as strings, each char containing a TOKEN
// that can be a terminal or a non-terminal. That´s why the 256 limit.

char *Tab[MAX_TOKEN][MAX_TOKEN];

// Insert a production into the table to initialize it

void put(int x, int y,char a, char b, char c, char d, char e)
  {
  char * novo = 0;
  novo = (char*) calloc(6,sizeof(char));
  novo[0] = a;
  novo[1] = b;
  novo[2] = c;
  novo[3] = d;
  novo[4] = e;
  novo[5] = '\0';
  Tab[x][y] = novo;
  }

// Print parser table for debugging purpouses

int printTable()
  {
  int a,b;
  char *c;
  for (a=0; a < MAX_TOKEN; ++a)
    for (b=0; b < MAX_TOKEN; ++b)
      {
      c = Tab[a][b];
      if (Tab[a][b])
        printf("Tab[%d][%d] = %s\n",a,b,c);
      }
  }

void printSymbol(char s)
  {
  switch(s)
    {
    case EPSILON	: printf("epsilon "); break;
    case TER_ID		: printf("id "); break;
    case TER_PEV	: printf("; "); break;
    case TER_IGUAL	: printf("= "); break;
    case TER_MAIS	: printf("+ "); break;
    case TER_MUL	: printf("* "); break;
    case TER_ABRE	: printf("( "); break;
    case TER_FECHA	: printf(") "); break;
    case TER_NUM	: printf("num "); break;
    case TER_BEG	: printf("begin "); break;
    case TER_END	: printf("end "); break;
    case TER_FIM	: printf("$ "); break;
    case NON_F		: printf("F "); break;
    case NON_S		: printf("S "); break;
    case NON_R		: printf("R "); break;
    case NON_T		: printf("T "); break;
    case NON_E		: printf("E "); break;
    case NON_CMD	: printf("CMD "); break;
    case NON_RESTO	: printf("RESTO "); break;
    case NON_LCMD	: printf("LCMD "); break;
    case NON_BL		: printf("BL "); break;
    default		: printf("Unknown "); break;
    }
  }

// This is the stack in which the parser operates
// Is is tested for overflow/underflow but generates no error
// The ´user´ should test it before pushing/popping.

char Stack[MAX_STACK];
int StackTopPos = 0;
#define StackEmpty()	(StackTopPos? FALSE : TRUE)
#define StackFull()	(StackTopPos==MAX_STACK)
#define StackTop()	(StackTopPos? Stack[StackTopPos-1] : 0)
#define StackPop()	(StackTopPos? StackTopPos-- : FALSE )
#define StackPush(a)	(StackTopPos<MAX_STACK? Stack[StackTopPos++] = (a) : FALSE) 

// A simple function to test the stack

void testStack()
  {
  int i = 0;
  StackPush(5);
  StackPush(45);
  StackPush(2);
  StackPush(9);
  for (i =0; StackFull() == 0; StackPush(i) )
    {
    fprintf(stderr,"pusshing %d\n",i+10 );
    i += 10;
    }

  for (; StackEmpty() == 0; StackPop() )
    fprintf(stderr,"popping %d\n",(unsigned char) StackTop() ); 
  }

// This is our input, already in!!!!

int Entrada[256] = {TER_BEG,TER_ID,TER_IGUAL,TER_NUM,TER_PEV,
		TER_ID,TER_IGUAL,TER_ID,TER_END,TER_FIM};
int atual = 0;
int next_token()   
  {
  printf("Lendo token da entrada: ");
  printSymbol(Entrada[atual]);
  printf("\n");
  return Entrada[atual++];
  }

// Initialize Table with productions of our language

void initTab()
  {
  int a,b;

  // clean up all entries
  for (a=0; a < MAX_TOKEN; ++a)
    for (b=0; b < MAX_TOKEN; ++b)
      Tab[a][b] = 0;

  put(NON_BL,TER_BEG,TER_BEG,NON_LCMD,TER_END,'\0',0);
  put(NON_LCMD,TER_ID,NON_CMD,NON_RESTO,'\0',0,0);
  put(NON_LCMD,TER_PEV,NON_CMD,NON_RESTO,'\0',0,0);
  put(NON_LCMD,TER_END,NON_CMD,NON_RESTO,'\0',0,0);
  put(NON_RESTO,TER_PEV,TER_PEV,NON_LCMD,'\0',0,0);
  put(NON_RESTO,TER_END,EPSILON,'\0',0,0,0);
  put(NON_CMD,TER_ID,TER_ID,TER_IGUAL,NON_E,'\0',0);
  put(NON_CMD,TER_PEV,EPSILON,'\0',0,0,0);
  put(NON_CMD,TER_END,EPSILON,'\0',0,0,0);
  put(NON_E,TER_ID,NON_T,NON_R,'\0',0,0);
  put(NON_E,TER_ABRE,NON_T,NON_R,'\0',0,0);
  put(NON_E,TER_NUM,NON_T,NON_R,'\0',0,0);
  put(NON_T,TER_ID,NON_F,NON_S,'\0',0,0);
  put(NON_T,TER_ABRE,NON_F,NON_S,'\0',0,0);
  put(NON_T,TER_NUM,NON_F,NON_S,'\0',0,0);
  put(NON_R,TER_MAIS,TER_MAIS,NON_T,NON_R,'\0',0);
  put(NON_R,TER_PEV,EPSILON,'\0',0,0,0);
  put(NON_R,TER_FECHA,EPSILON,'\0',0,0,0);
  put(NON_R,TER_END,EPSILON,'\0',0,0,0);
  put(NON_S,TER_MUL,TER_MUL,NON_F,NON_S,'\0',0);
  put(NON_S,TER_PEV,EPSILON,'\0',0,0,0);
  put(NON_S,TER_FECHA,EPSILON,'\0',0,0,0);
  put(NON_S,TER_END,EPSILON,'\0',0,0,0);
  put(NON_S,TER_MAIS,EPSILON,'\0',0,0,0);
  put(NON_F,TER_ID,TER_ID,'\0',0,0,0);
  put(NON_F,TER_ABRE,TER_ABRE,NON_E,TER_FECHA,'\0',0);
  put(NON_F,TER_NUM,TER_NUM,'\0',0,0,0);
  }

void printRule(char x, char* prod)
  {
  int i = 0;
  int len = 0;

  printf("Rule: ");
  printSymbol(x);
  printf("-> ");
  for (i=0; i <= len; ++i)
    printSymbol(prod[i]);        
  printf("\n");        
  }

void printStack()
  {
  int i = 0;
  int len = 0;

  printf("STACK: ");
  for (i=0; i < StackTopPos; ++i)
    printSymbol(Stack[i]);        
  printf("\n");        
  }

// MAIN: need to say more?

int main(int argc, char **argv)
  {
  int i = 0;
  int len = 0;
  char x = 0;
  char ip = 0;
  char *prod = 0;

  initTab();
  StackPush(TER_FIM);
  StackPush(NON_BL);

  ip = next_token();
  do 
    {
    printStack();
    x = StackTop();
    if ( TERMINAL(x) )
      {
      // Terminal on top: must be what we expected
      if ( x == ip )
        {
        StackPop();
        printf("Desempilha terminal\n");
        ip = next_token();
        }
      else
        {
        fprintf(stderr,"Error: %d expected but %d was found!\n",x,ip);
        exit(0);
        }
      }
    else
      {
      // There is a non terminal at the top
      if ( prod = Tab[x][ip] )
        {
        StackPop();
        len = strlen(prod);
        for (i=len-1; i>=0; --i)
          StackPush(prod[i]);
        printRule(x,prod);
        }
      else
        {
        fprintf(stderr,"Error: No rule to match %d with non terminal %d!\n",ip,x);
        exit(0);
        }

      }
    }
    while( x != TER_FIM );
  fprintf(stderr,"FIM!\n");
  } 
