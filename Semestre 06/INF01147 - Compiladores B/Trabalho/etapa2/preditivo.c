//
// Predictive Descendent Syntatic Analyzer
//
// It was file aula17.c from 2002-1

#include <stdio.h>
#include <stdlib.h>
#define	TRUE	1
#define FALSE	0

// Tokens, from 0 to 255 are the ASCII chars
#define	IF	256
#define WHILE  	257
#define	THEN	258
#define DO	259
#define NUM	260
#define ID	261

// Prototypes
int func_BL();
int func_LCMD();
int func_CMD();
int func_RESTO();
int func_IF();
int func_ASS();
int func_WHI();
int func_L();
int func_E();

// This is my tokenized input
int Entrada[15] = {'{',IF,ID,THEN,ID,'=',NUM,
		';','*',ID,'=',NUM,'}','$'};
int Atual = 0;
int tok = 0;

// This is my lexical analizer workalike
int le_tok()
{
return Entrada[Atual++];
}

int main ()
{
printf("Sou um analisador...\n");
tok = le_tok();
if (func_CMD())
  if (tok == '$')
    printf("Success! Yupiiii !\n");
  else
    printf("Ok, ok, but there is waste at the end!\n");
else
  printf("Wrong program, not a CMD...\n");
}

int func_BL()
{
printf("Sou uma BL: tok = %d\n",tok);
if (tok == '{')
  {
  tok = le_tok();
  if (func_CMDL())
    {
    if (tok == '}')
      {
      tok = le_tok();
      return TRUE;
      }
    else
      return FALSE;
    }
  else  
    return FALSE; 
  }
else
  return FALSE;
}

int func_RESTO()
{
printf("Sou uma RESTO: tok = %d\n",tok);
if (tok == ';')
  {
  tok = le_tok();
  if (func_CMDL())
    return TRUE;
  else
    return FALSE;
  }
else
  return TRUE;		// epsilon production present
}

int func_CMDL()
{
printf("Sou uma CMDL: tok = %d\n",tok);
if (func_CMD())
  if (func_RESTO())
    return TRUE;
  else
    return FALSE;
else
  return FALSE;
}

int func_CMD()
{
printf("Sou uma CMD: tok = %d\n",tok);
if (tok == IF)
  if (func_IF())
    return TRUE;
  else
    return FALSE;
else
if (tok == '*' || tok == NUM || tok == ID)
  if (func_ASS())
    return TRUE;
  else
    return FALSE;
else
if (tok == WHILE)
  if (func_WHI())
    return TRUE;
  else
    return FALSE;
else
if (tok == '{')
  if (func_BL())
    return TRUE;
  else
    return FALSE;
else
  return FALSE;
}

int func_IF()
{
printf("Sou uma IF: tok = %d\n",tok);
if (tok == IF)
  {
  tok = le_tok();
  if (func_E())
    {
    if (tok == THEN)
      {
      tok = le_tok();
      if (func_CMD())
        return TRUE;
      else
        return FALSE;
      }
    else
      return FALSE;
    }
  else
    return FALSE;
  }
else
  return FALSE;
}

int func_WHI()
{
printf("Sou uma WHI: tok = %d\n",tok);
if (tok == WHILE)
  {
  tok = le_tok();
  if (func_E())
    {
    if (tok == DO)
      {
      tok = le_tok();
      if (func_CMD())
        return TRUE;
      else
        return FALSE;
      }
    else
      return FALSE;
    }
  else
    return FALSE;
  }
else
  return FALSE;
}

int func_ASS()
{
printf("Sou uma ASS: tok = %d\n",tok);
if (func_L())
  {
  if (tok == '=')
    {
    tok = le_tok();
    if (func_E())
      return TRUE;
    else
      return FALSE;
    }
  else
    return FALSE;
  }
else
  return FALSE;
}

int func_L()
{
printf("Sou uma L: tok = %d\n",tok);
if (tok == '*')
  {
  tok = le_tok();
  if (func_E())
    return TRUE;
  else
    return FALSE;
  }
else
  {
  if (func_E())
    return TRUE;
  else
    return FALSE;
  }
}

int func_E()
{
printf("Sou uma E: tok = %d\n",tok);
if (tok == NUM || tok == ID)
  {
  tok = le_tok();
  return TRUE;
  }
else
  return FALSE;
}


