#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20110908

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "yacc.y"
    #include "hashtable.h"
    #include "lex.yy.h"
    
    void yyerror(char *);
    int getLineNumber();

    /* Just put it here.*/
    /* "-Sir: no touching of the*/
    /* symbols, please..."*/
    #define SYMBOL_UNDEFINED    0 
    #define SYMBOL_LIT_INTEGER  1 
    #define SYMBOL_LIT_FLOATING 2 
    #define SYMBOL_LIT_TRUE     3 
    #define SYMBOL_LIT_FALSE    4 
    #define SYMBOL_LIT_CHAR     5 
    #define SYMBOL_LIT_STRING   6 
    #define SYMBOL_IDENTIFIER   7
#line 21 "yacc.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
    Entry* entry;
    int number;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 49 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#define YYERROR_DECL() yyerror(const char *s)
#define YYERROR_CALL(msg) yyerror(msg)

extern int YYPARSE_DECL();

#define KW_WORD 257
#define KW_BOOL 258
#define KW_BYTE 259
#define KW_IF 260
#define KW_THEN 261
#define KW_ELSE 262
#define KW_LOOP 263
#define KW_INPUT 264
#define KW_RETURN 265
#define KW_OUTPUT 266
#define OPERATOR_LE 267
#define OPERATOR_GE 268
#define OPERATOR_EQ 269
#define OPERATOR_NE 270
#define OPERATOR_AND 271
#define OPERATOR_OR 272
#define TK_IDENTIFIER 273
#define LIT_INTEGER 274
#define LIT_FALSE 275
#define LIT_TRUE 276
#define LIT_CHAR 277
#define LIT_STRING 278
#define TOKEN_ERROR 279
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    0,    1,    1,    1,    3,    8,    8,    8,
    6,    6,    6,    7,    7,    7,    7,    7,    4,    4,
    9,    9,    5,    2,    2,   12,   13,   13,   15,   15,
   10,   10,   16,   16,   11,   17,   17,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   19,   19,   20,
   20,   20,   14,   14,   14,   14,   14,   14,   14,   14,
   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,
   14,
};
static const short yylen[] = {                            2,
    2,    2,    0,    1,    1,    1,    5,    2,    2,    0,
    1,    1,    1,    1,    1,    1,    1,    1,    6,    8,
    2,    1,    6,    7,    6,    4,    2,    0,    3,    0,
    3,    0,    4,    0,    3,    3,    0,    3,    6,    5,
    8,    5,    2,    2,    2,    1,    0,    2,    2,    3,
    3,    0,    1,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    2,    2,    3,    1,    4,
    1,
};
static const short yydefred[] = {                         0,
   11,   12,   13,    0,    0,    0,    4,    5,    6,    0,
    1,    2,    0,    0,    0,    0,    0,    0,   14,   15,
   16,   17,   18,    0,    0,    0,    0,    0,    7,    0,
    0,    0,    0,    0,   19,    0,   31,    0,    0,    0,
    0,    0,   25,   23,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   46,    0,    0,    8,    9,    0,   24,
   21,   20,    0,    0,    0,   43,    0,    0,    0,    0,
   71,   53,    0,    0,    0,   44,    0,    0,   35,    0,
   33,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   48,   49,    0,    0,   36,    0,    0,    0,    0,
    0,   68,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   42,   70,
   26,    0,   27,   50,   51,    0,    0,    0,    0,    0,
   29,   41,
};
static const short yydgoto[] = {                          4,
    5,    6,    7,    8,    9,   10,   71,   42,   46,   27,
   54,   72,  110,   73,  133,   37,   55,   56,   76,  102,
};
static const short yysindex[] = {                      -240,
    0,    0,    0,    0, -240, -240,    0,    0,    0,  -25,
    0,    0,  -18, -253,  -49, -238, -240,  -20,    0,    0,
    0,    0,    0,  -13,  -51, -214,   38,  -49,    0,   42,
   19, -102,   24,  -49,    0, -240,    0,  -82, -240, -240,
  -24,  -42,    0,    0,  -49,   37, -171,   64,   81, -166,
  -32,  -38,  -30,    0,   -6,   70,    0,    0,  111,    0,
    0,    0,   19,  -32,  -32,    0,    3,  -32,  -32,  -32,
    0,    0,   50,   91,   22,    0,  -32,  -32,    0,  -82,
    0,   -8,    8, -132,  -32,   15,   50,   50,  -32,  -32,
  -32,  -32,  -32,  -32,  -32,  -32,  -32,  -32,  -32,  -32,
  -38,    0,    0,   29,   50,    0, -110,  -82,   80,  122,
   43,    0,   50,   50,   50,   50,   50,   50,   50,   50,
   50,   50,   50,   50,   91,   22,  119,  -82,    0,    0,
    0,  -32,    0,    0,    0,  -32,  -92,   43,   50,  -82,
    0,    0,
};
static const short yyrindex[] = {                       187,
    0,    0,    0,    0,  187,  187,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   38,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  149,    0,    0,    0,    0,    0,    0,  -45,   69,   69,
    0,    0,    0,    0,  137,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  149,    0,    0,    0,  -15,    0,    0,    0,
    0,    0,  -58,  -56,  -56,    0,    0,    0,    0,  -45,
    0,    0,    0,    0,  154,    0,   65,   67,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -54,    0,    0,  -52,    0,    0,
  158,    0,   72,   73,   74,   79,   84,   86,   93,   95,
  100,  105,  109,  130,  -56,  -56,    0,  -50,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  158,  -46,  -52,
    0,    0,
};
static const short yygindex[] = {                       156,
    0,    0,  -16,    0,  108,  311,  179,  136,  152,    0,
  -17,    0,    0,  304,   62,  138,  123,   77,    0,  -27,
};
#define YYTABLESIZE 440
static const short yytable[] = {                         70,
   45,   68,   52,   69,   38,   70,   47,   68,   40,   69,
   14,   14,   39,   47,   43,   39,    1,    2,    3,   18,
   38,   17,   39,   39,   60,   69,   69,   69,   69,   69,
   78,   69,  107,  100,   97,   25,   98,   28,   99,   15,
   38,   30,   85,   69,   69,   29,   69,  103,  108,  100,
   97,   96,   98,   95,   99,  112,  100,   97,   31,   98,
   77,   99,   36,  100,   97,  101,   98,   96,   99,   95,
  100,   97,   16,   98,   96,   99,   95,   69,   32,   37,
   38,   96,   44,   95,  100,   97,  132,   98,   96,   99,
   95,  100,   97,   84,   98,   62,   99,  134,  135,   34,
   35,   63,   96,   64,   95,   66,   66,   67,   66,   96,
   67,   95,   54,   55,   56,   54,   55,   56,   79,   57,
   65,  127,   57,   66,   59,   67,   58,   59,   80,   58,
   54,   55,   56,   60,  101,   61,   60,   57,   61,   40,
   62,  109,   59,   62,   58,   63,   40,   40,   63,   64,
  128,   60,   64,   61,    1,    2,    3,   66,   62,   67,
   11,   12,  131,   63,   54,   55,   56,   64,   15,  140,
   65,   57,  130,   65,   57,   58,   59,   48,   58,  136,
   49,   50,   51,   52,  129,   60,    3,   61,   65,   34,
   53,   10,   62,   24,   28,   22,   61,   63,   30,  141,
   81,   64,  106,   45,  137,   52,   33,   38,    0,   47,
    0,   40,   45,    0,    0,   39,  142,    0,    1,    2,
    3,    0,   65,   45,   19,   20,   21,   22,   23,    0,
    0,    0,    0,    0,   67,   19,   20,   21,   22,   23,
   67,   19,   20,   21,   22,   23,   69,   13,   59,    0,
    0,   69,   69,   69,   69,   69,   69,    0,   89,   90,
   91,   92,   93,   94,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   89,   90,   91,   92,   93,   94,
    0,   89,   90,   91,   92,   93,   94,    0,   89,   90,
   91,   92,   93,   94,    0,   89,   90,   91,   92,   93,
   94,    0,    0,    0,    0,    0,    0,    0,    0,   89,
   90,   91,   92,   93,   94,    0,   89,   90,   91,   92,
   93,   94,    0,    0,    0,    0,   66,   26,   67,    0,
    0,    0,    0,   54,   55,   56,    0,    0,    0,    0,
   57,    0,   41,    0,    0,   59,   47,   58,    0,   41,
   41,    0,    0,    0,   60,   75,   61,    0,    0,    0,
    0,   62,   74,    0,    0,    0,   63,   82,   83,    0,
   64,   86,   87,   88,    0,    0,    0,    0,    0,    0,
  104,  105,    0,    0,    0,    0,    0,    0,  111,    0,
    0,   65,  113,  114,  115,  116,  117,  118,  119,  120,
  121,  122,  123,  124,  126,    0,    0,    0,    0,    0,
    0,  125,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  138,    0,    0,    0,  139,
};
static const short yycheck[] = {                         38,
   59,   40,   59,   42,   59,   38,   59,   40,   59,   42,
   36,   36,   59,   59,   32,   32,  257,  258,  259,  273,
  123,   40,   39,   40,   42,   41,   42,   43,   44,   45,
   61,   47,   41,   42,   43,  274,   45,   58,   47,   58,
  123,   93,   40,   59,   60,   59,   62,   75,   41,   42,
   43,   60,   45,   62,   47,   41,   42,   43,  273,   45,
   91,   47,   44,   42,   43,   44,   45,   60,   47,   62,
   42,   43,   91,   45,   60,   47,   62,   93,   41,  125,
  123,   60,   59,   62,   42,   43,   44,   45,   60,   47,
   62,   42,   43,   91,   45,   59,   47,  125,  126,   58,
   59,  273,   60,   40,   62,   41,  273,   41,   44,   60,
   44,   62,   41,   41,   41,   44,   44,   44,  125,   41,
   40,   93,   44,   59,   41,   59,   41,   44,   59,   44,
   59,   59,   59,   41,   44,   41,   44,   59,   44,   32,
   41,  274,   59,   44,   59,   41,   39,   40,   44,   41,
  261,   59,   44,   59,  257,  258,  259,   93,   59,   93,
    5,    6,   41,   59,   93,   93,   93,   59,   58,  262,
   41,   93,   93,   44,   39,   40,   93,  260,   93,   61,
  263,  264,  265,  266,  108,   93,    0,   93,   59,   41,
  273,  123,   93,   15,   41,   59,   45,   93,   41,  138,
   63,   93,   80,  262,  128,  262,   28,  262,   -1,  262,
   -1,  262,   34,   -1,   -1,  262,  140,   -1,  257,  258,
  259,   -1,   93,   45,  274,  275,  276,  277,  278,   -1,
   -1,   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,
  273,  274,  275,  276,  277,  278,  262,  273,  273,   -1,
   -1,  267,  268,  269,  270,  271,  272,   -1,  267,  268,
  269,  270,  271,  272,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  267,  268,  269,  270,  271,  272,
   -1,  267,  268,  269,  270,  271,  272,   -1,  267,  268,
  269,  270,  271,  272,   -1,  267,  268,  269,  270,  271,
  272,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  267,
  268,  269,  270,  271,  272,   -1,  267,  268,  269,  270,
  271,  272,   -1,   -1,   -1,   -1,  262,   17,  262,   -1,
   -1,   -1,   -1,  262,  262,  262,   -1,   -1,   -1,   -1,
  262,   -1,   32,   -1,   -1,  262,   36,  262,   -1,   39,
   40,   -1,   -1,   -1,  262,   52,  262,   -1,   -1,   -1,
   -1,  262,   52,   -1,   -1,   -1,  262,   64,   65,   -1,
  262,   68,   69,   70,   -1,   -1,   -1,   -1,   -1,   -1,
   77,   78,   -1,   -1,   -1,   -1,   -1,   -1,   85,   -1,
   -1,  262,   89,   90,   91,   92,   93,   94,   95,   96,
   97,   98,   99,  100,  101,   -1,   -1,   -1,   -1,   -1,
   -1,  101,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  132,   -1,   -1,   -1,  136,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 279
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'$'",0,"'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,
0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_WORD","KW_BOOL","KW_BYTE","KW_IF",
"KW_THEN","KW_ELSE","KW_LOOP","KW_INPUT","KW_RETURN","KW_OUTPUT","OPERATOR_LE",
"OPERATOR_GE","OPERATOR_EQ","OPERATOR_NE","OPERATOR_AND","OPERATOR_OR",
"TK_IDENTIFIER","LIT_INTEGER","LIT_FALSE","LIT_TRUE","LIT_CHAR","LIT_STRING",
"TOKEN_ERROR",
};
static const char *yyrule[] = {
"$accept : program",
"program : decl program",
"program : func program",
"program :",
"decl : simple_decl",
"decl : array_decl",
"decl : pointer_decl",
"simple_decl : types TK_IDENTIFIER ':' literals ';'",
"decl_func_list : simple_decl decl_func_list",
"decl_func_list : pointer_decl decl_func_list",
"decl_func_list :",
"types : KW_WORD",
"types : KW_BOOL",
"types : KW_BYTE",
"literals : LIT_INTEGER",
"literals : LIT_FALSE",
"literals : LIT_TRUE",
"literals : LIT_CHAR",
"literals : LIT_STRING",
"array_decl : types TK_IDENTIFIER '[' LIT_INTEGER ']' ';'",
"array_decl : types TK_IDENTIFIER '[' LIT_INTEGER ']' ':' lit_recursive ';'",
"lit_recursive : literals lit_recursive",
"lit_recursive : literals",
"pointer_decl : types '$' TK_IDENTIFIER ':' literals ';'",
"func : types TK_IDENTIFIER '(' param_list ')' decl_func_list command_block",
"func : types TK_IDENTIFIER '(' param_list ')' command_block",
"func_call : TK_IDENTIFIER '(' call_list ')'",
"call_list : exp call_list_recursive",
"call_list :",
"call_list_recursive : ',' exp call_list_recursive",
"call_list_recursive :",
"param_list : types TK_IDENTIFIER param_list_recursive",
"param_list :",
"param_list_recursive : ',' types TK_IDENTIFIER param_list_recursive",
"param_list_recursive :",
"command_block : '{' commands_ended '}'",
"commands_ended : commands ';' commands_ended",
"commands_ended :",
"commands : TK_IDENTIFIER '=' exp",
"commands : TK_IDENTIFIER '[' exp ']' '=' exp",
"commands : KW_IF '(' exp ')' KW_THEN",
"commands : KW_IF '(' exp ')' KW_THEN commands KW_ELSE commands",
"commands : KW_LOOP '(' exp ')' commands",
"commands : KW_INPUT TK_IDENTIFIER",
"commands : KW_OUTPUT output_list",
"commands : KW_RETURN exp",
"commands : command_block",
"commands :",
"output_list : types output_list_recursive",
"output_list : exp output_list_recursive",
"output_list_recursive : ',' types output_list_recursive",
"output_list_recursive : ',' exp output_list_recursive",
"output_list_recursive :",
"exp : func_call",
"exp : exp OPERATOR_LE exp",
"exp : exp OPERATOR_GE exp",
"exp : exp OPERATOR_EQ exp",
"exp : exp OPERATOR_NE exp",
"exp : exp OPERATOR_OR exp",
"exp : exp OPERATOR_AND exp",
"exp : exp '>' exp",
"exp : exp '<' exp",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : exp '/' exp",
"exp : exp '*' exp",
"exp : '*' exp",
"exp : '&' exp",
"exp : '(' exp ')'",
"exp : TK_IDENTIFIER",
"exp : TK_IDENTIFIER '[' LIT_INTEGER ']'",
"exp : literals",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 190 "yacc.y"

void yyerror(char *s) {
	fprintf(stderr, "Error on line %d: %s\n", getLineNumber(), s);
}
#line 410 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
