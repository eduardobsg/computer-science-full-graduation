#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20121003

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
	/* 	Arrumar shift/reduce: yacc -v parser.y
		Arquivo y.output é gerado
 	*/

	#include "hashtable.h"
    #include "astree.c"
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
#line 26 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
    int valor;
	Entry *symbol;
	ASTREE *astree;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 55 "y.tab.c"

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
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

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
#define TOKEN_ERROR 267
#define TK_IDENTIFIER 268
#define LIT_INTEGER 269
#define LIT_FALSE 270
#define LIT_TRUE 271
#define LIT_CHAR 272
#define LIT_STRING 273
#define OPERATOR_AND 274
#define OPERATOR_OR 275
#define UNARY_MINUS 276
#define POINTER 277
#define OPERATOR_LE 278
#define OPERATOR_GE 279
#define OPERATOR_EQ 280
#define OPERATOR_NE 281
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    1,    1,    2,    2,    2,    3,   20,
   21,   21,   21,   19,   19,   19,   19,   19,    4,    4,
    6,    6,    5,    7,    7,    7,    7,    8,    8,    9,
    9,    9,    9,   15,   14,   14,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   18,   18,   16,   16,   17,
   17,   10,   10,   10,   10,   10,   10,   10,   11,   11,
   11,   11,   11,   11,   11,   12,   12,   12,   12,   12,
   12,   12,   12,
};
static const short yylen[] = {                            2,
    1,    2,    1,    2,    1,    1,    1,    1,    5,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    6,    8,
    2,    1,    6,    7,    6,    6,    5,    4,    2,    2,
    2,    1,    1,    3,    3,    0,    3,    6,    6,    8,
    5,    2,    2,    2,    1,    3,    1,    4,    3,    3,
    1,    1,    1,    1,    2,    2,    2,    3,    3,    3,
    3,    3,    1,    1,    4,    3,    3,    3,    3,    3,
    3,    3,    3,
};
static const short yydefred[] = {                         0,
   11,   12,   13,    0,    1,    0,    6,    7,    8,    0,
    0,    2,    4,   10,    0,    0,    0,    0,    0,    0,
    0,   14,   15,   16,   17,   18,    0,    0,    0,    0,
    0,    0,    9,    0,    0,    0,    0,    0,   27,    0,
    0,    0,   23,    0,   19,    0,    0,    0,    0,    0,
    0,    0,   45,    0,   30,   31,   25,    0,    0,   26,
    0,    0,    0,    0,    0,   42,    0,    0,    0,    0,
    0,   52,   53,   54,   63,    0,    0,    0,   43,    0,
   34,    0,    0,   24,   28,   20,   21,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   35,    0,
    0,    0,    0,   58,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   73,    0,   49,    0,    0,
   46,    0,    0,   41,   65,    0,   48,    0,    0,   50,
    0,    0,   40,
};
static const short yydgoto[] = {                          4,
    5,    6,   36,    8,   37,   62,   10,   30,   38,   77,
   72,   73,   51,   52,   53,   74,  130,   79,   75,   76,
   40,
};
static const short yysindex[] = {                      -151,
    0,    0,    0,    0,    0, -151,    0,    0,    0, -151,
  -14,    0,    0,    0, -263,  136,  -38,   11, -256,  -34,
   11,    0,    0,    0,    0,    0,  -29,  -46,  -87,   10,
 -263,    7,    0,   75,  188, -151, -151,  -54,    0,  -14,
  -87,   29,    0,   11,    0,   50,   73, -263,  103,  103,
   36,   22,    0,   70,    0,    0,    0,   91,  -54,    0,
 -151,   93,   11,  103,  103,    0,  103,  103,  103,  103,
   41,    0,    0,    0,    0,   21,   41,  109,    0,  188,
    0, -114,  103,    0,    0,    0,    0,  -18,  -10,  113,
  113,  113,   -2,  103,  103,  103,  103,  103,  103,  103,
  103,  103,  103,  103,  103, -101,   97,  103,    0,   86,
   41,  -83,  188,    0,   49,   55,   63,   63,  113,  113,
   25,  -45,    8,   54,  120,    0,   94,    0,   20,  156,
    0,  137,  188,    0,    0,  103,    0,  103,  -58,    0,
   41,  188,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,  205,    0,    0,    0,  206,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   90,   95,  107,    0,    0,    0,
    0,  179,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  185,    0,    0,    0,    0,    0,    0,    0,
  -43,    0,    0,    0,    0,  -41,    0,   12,    0,   90,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  115,
  122,  141,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   -3,    0,    0,    0,  244,  172,  158,  305,  148,  167,
  208,   85,   77,   34,  -33,    0,    0,    0,  202,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  199,    0,
   40,    0,    0,
};
static const short yygindex[] = {                         0,
   43,    0,  140,    0,  222,  203,    0,  214,  344,  426,
   -4,    0,  184,  227,  371,    0,  174,  210,  133,  347,
   28,
};
#define YYTABLESIZE 580
static const short yytable[] = {                         64,
   64,   64,   64,   64,   14,   64,   29,   72,   72,   72,
   72,   72,   28,   72,  105,   44,  104,   64,   64,   21,
   64,   15,  112,   99,   96,   72,   97,   11,   98,   33,
  113,   99,   96,   11,   97,   35,   98,   11,  114,   99,
   96,  105,   97,  104,   98,   78,   34,   31,   12,  105,
   41,  104,   13,   52,   52,   37,   52,  105,   52,  104,
  107,   99,   96,  136,   97,   43,   98,  105,   35,  104,
   47,   52,   61,   52,   69,   69,   69,   69,   69,  105,
   69,  104,   99,   96,  105,   97,  104,   98,   31,   64,
   99,   96,   69,   97,   80,   98,   99,   96,   38,   97,
  105,   98,  104,   78,   99,    1,    2,    3,  105,   98,
  104,  106,   65,  105,  105,  104,  104,   68,   68,   68,
   68,   68,  105,   68,  104,   67,   67,   67,   67,   67,
   83,   67,   44,   45,   69,   68,   70,  128,   68,    7,
   69,   67,   70,   67,   68,    7,   81,   67,   18,    7,
   27,   86,  108,   32,  110,   55,   55,   55,   55,   55,
   82,   55,   56,   56,   56,   56,   56,  127,   56,    1,
    2,    3,  105,   55,  104,   20,   63,  133,  132,  105,
   56,   57,   57,   57,   57,   57,  135,   57,   61,   61,
   61,   61,   61,   18,   61,   63,  137,  138,   59,   57,
   59,   59,   59,  142,    3,    5,   61,   62,   62,   62,
   62,   62,   70,   62,   36,   70,   59,   32,   44,   29,
   64,    9,    1,    2,    3,   62,   19,    9,   72,   33,
   70,    9,   64,   64,  102,  103,   64,   64,   64,   64,
   72,   72,   51,   22,   72,   72,   72,   72,   66,   66,
   66,   66,   66,   14,   66,   94,   95,   39,   37,  100,
  101,  102,  103,   94,   95,   87,   66,  100,  101,  102,
  103,   94,   95,   47,   85,  100,  101,  102,  103,   22,
   23,   24,   25,   26,   71,   52,   52,   71,  103,   52,
   52,   52,   52,   94,   95,   69,  134,  100,  101,  102,
  103,   38,   71,  101,  102,  103,  109,   69,   69,  140,
   35,   69,   69,   69,   94,   95,  139,  131,  100,  101,
  102,  103,    0,   95,    0,  143,  100,  101,  102,  103,
    0,    0,  100,  101,  102,  103,    0,    0,   68,    0,
  100,  101,  102,  103,    0,   60,   67,   60,   60,   60,
   68,   68,    0,    0,   68,   68,    0,   16,   67,   67,
    0,   17,   67,   60,   14,   22,   23,   24,   25,   26,
   14,   22,   23,   24,   25,   26,   55,   42,    0,   55,
   56,   54,    0,   56,   59,    0,   58,    0,   55,   55,
  100,  101,  102,  103,   66,   56,   56,    0,    0,   39,
    0,    0,   57,    0,    0,    0,    0,    0,   57,   61,
    0,   60,    0,    0,   57,   57,    0,    0,    0,   59,
    0,   61,   61,    0,    0,    0,   54,    0,   62,   84,
    0,   59,   59,   70,    0,    0,    0,    0,    0,    0,
   62,   62,    0,    0,    0,   70,   70,   46,    0,    0,
   47,   48,   49,   50,    0,   14,    0,    0,    0,   54,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   66,
    0,    0,    0,    0,   71,    0,    0,    0,    0,   54,
    0,   66,   66,    0,    0,    0,    0,    0,   54,   88,
   89,    0,   90,   91,   92,   93,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   71,    0,    0,  111,    0,
    0,    0,    0,    0,    0,    0,    0,   71,    0,  115,
  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,
  126,    0,  129,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  129,    0,  141,    0,    0,   60,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   60,   60,
};
static const short yycheck[] = {                         41,
   42,   43,   44,   45,  268,   47,   41,   41,   42,   43,
   44,   45,  269,   47,   60,   59,   62,   59,   60,   58,
   62,   36,   41,   42,   43,   59,   45,    0,   47,   59,
   41,   42,   43,    6,   45,  123,   47,   10,   41,   42,
   43,   60,   45,   62,   47,   50,   93,   20,    6,   60,
   41,   62,   10,   42,   43,   59,   45,   60,   47,   62,
   40,   42,   43,   44,   45,   59,   47,   60,  123,   62,
   59,   60,   44,   62,   41,   42,   43,   44,   45,   60,
   47,   62,   42,   43,   60,   45,   62,   47,   61,   40,
   42,   43,   59,   45,   59,   47,   42,   43,   59,   45,
   60,   47,   62,  108,   42,  257,  258,  259,   60,   47,
   62,   91,   40,   60,   60,   62,   62,   41,   42,   43,
   44,   45,   60,   47,   62,   41,   42,   43,   44,   45,
   61,   47,   58,   59,   38,   59,   40,   41,   42,    0,
   38,   45,   40,   59,   42,    6,  125,   45,   58,   10,
   18,   59,   44,   21,  269,   41,   42,   43,   44,   45,
   91,   47,   41,   42,   43,   44,   45,  269,   47,  257,
  258,  259,   60,   59,   62,   40,   44,  261,   93,   60,
   59,   41,   42,   43,   44,   45,   93,   47,   41,   42,
   43,   44,   45,   58,   47,   63,   41,   61,   41,   59,
   43,   44,   45,  262,    0,    0,   59,   41,   42,   43,
   44,   45,   41,   47,  125,   44,   59,  123,  262,   41,
  262,    0,  257,  258,  259,   59,   91,    6,  262,  123,
   59,   10,  274,  275,  280,  281,  278,  279,  280,  281,
  274,  275,   41,   59,  278,  279,  280,  281,   41,   42,
   43,   44,   45,  268,   47,  274,  275,   59,  262,  278,
  279,  280,  281,  274,  275,   63,   59,  278,  279,  280,
  281,  274,  275,  262,   61,  278,  279,  280,  281,  269,
  270,  271,  272,  273,   41,  274,  275,   44,  281,  278,
  279,  280,  281,  274,  275,  262,  113,  278,  279,  280,
  281,  262,   59,  279,  280,  281,   80,  274,  275,  136,
  123,  278,  279,  280,  274,  275,  133,  108,  278,  279,
  280,  281,   -1,  275,   -1,  142,  278,  279,  280,  281,
   -1,   -1,  278,  279,  280,  281,   -1,   -1,  262,   -1,
  278,  279,  280,  281,   -1,   41,  262,   43,   44,   45,
  274,  275,   -1,   -1,  278,  279,   -1,   11,  274,  275,
   -1,   15,  278,   59,  268,  269,  270,  271,  272,  273,
  268,  269,  270,  271,  272,  273,  262,   31,   -1,   36,
   37,   35,   -1,  262,   41,   -1,   40,   -1,  274,  275,
  278,  279,  280,  281,   48,  274,  275,   -1,   -1,   29,
   -1,   -1,  262,   -1,   -1,   -1,   -1,   -1,   38,  262,
   -1,   41,   -1,   -1,  274,  275,   -1,   -1,   -1,  262,
   -1,  274,  275,   -1,   -1,   -1,   80,   -1,  262,   59,
   -1,  274,  275,  262,   -1,   -1,   -1,   -1,   -1,   -1,
  274,  275,   -1,   -1,   -1,  274,  275,  260,   -1,   -1,
  263,  264,  265,  266,   -1,  268,   -1,   -1,   -1,  113,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,
   -1,   -1,   -1,   -1,   49,   -1,   -1,   -1,   -1,  133,
   -1,  274,  275,   -1,   -1,   -1,   -1,   -1,  142,   64,
   65,   -1,   67,   68,   69,   70,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  262,   -1,   -1,   83,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  274,   -1,   94,
   95,   96,   97,   98,   99,  100,  101,  102,  103,  104,
  105,   -1,  107,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  136,   -1,  138,   -1,   -1,  262,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  274,  275,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 281
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
"KW_THEN","KW_ELSE","KW_LOOP","KW_INPUT","KW_RETURN","KW_OUTPUT","TOKEN_ERROR",
"TK_IDENTIFIER","LIT_INTEGER","LIT_FALSE","LIT_TRUE","LIT_CHAR","LIT_STRING",
"OPERATOR_AND","OPERATOR_OR","UNARY_MINUS","POINTER","OPERATOR_LE",
"OPERATOR_GE","OPERATOR_EQ","OPERATOR_NE",
};
static const char *yyrule[] = {
"$accept : begin",
"begin : program",
"program : decl program",
"program : decl",
"program : func program",
"program : func",
"decl : simple_decl",
"decl : array_decl",
"decl : pointer_decl",
"simple_decl : types identifier ':' literals ';'",
"identifier : TK_IDENTIFIER",
"types : KW_WORD",
"types : KW_BOOL",
"types : KW_BYTE",
"literals : LIT_INTEGER",
"literals : LIT_FALSE",
"literals : LIT_TRUE",
"literals : LIT_CHAR",
"literals : LIT_STRING",
"array_decl : types identifier '[' LIT_INTEGER ']' ';'",
"array_decl : types identifier '[' LIT_INTEGER ']' ':' lit_list ';'",
"lit_list : literals lit_list",
"lit_list : literals",
"pointer_decl : types '$' identifier ':' literals ';'",
"func : types identifier '(' param_list ')' decl_func_list command_block",
"func : types identifier '(' ')' decl_func_list command_block",
"func : types identifier '(' param_list ')' command_block",
"func : types identifier '(' ')' command_block",
"param_list : types identifier ',' param_list",
"param_list : types identifier",
"decl_func_list : simple_decl decl_func_list",
"decl_func_list : pointer_decl decl_func_list",
"decl_func_list : simple_decl",
"decl_func_list : pointer_decl",
"command_block : '{' command_list '}'",
"command_list : command ';' command_list",
"command_list :",
"command : identifier '=' exp",
"command : identifier '[' LIT_INTEGER ']' '=' exp",
"command : KW_IF '(' exp ')' KW_THEN command",
"command : KW_IF '(' exp ')' KW_THEN command KW_ELSE command",
"command : KW_LOOP '(' exp ')' command",
"command : KW_INPUT identifier",
"command : KW_OUTPUT output_list",
"command : KW_RETURN exp",
"command : command_block",
"output_list : exp_arit ',' output_list",
"output_list : exp_arit",
"func_call : identifier '(' func_call_list ')'",
"func_call : identifier '(' ')'",
"func_call_list : exp ',' func_call_list",
"func_call_list : exp",
"exp : exp_arit",
"exp : exp_logic",
"exp : func_call",
"exp : '-' exp",
"exp : '*' exp",
"exp : '&' exp",
"exp : '(' exp ')'",
"exp_arit : exp '+' exp",
"exp_arit : exp '-' exp",
"exp_arit : exp '/' exp",
"exp_arit : exp '*' exp",
"exp_arit : literals",
"exp_arit : identifier",
"exp_arit : identifier '[' LIT_INTEGER ']'",
"exp_logic : exp OPERATOR_LE exp",
"exp_logic : exp OPERATOR_GE exp",
"exp_logic : exp OPERATOR_EQ exp",
"exp_logic : exp OPERATOR_NE exp",
"exp_logic : exp OPERATOR_OR exp",
"exp_logic : exp OPERATOR_AND exp",
"exp_logic : exp '>' exp",
"exp_logic : exp '<' exp",

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
#line 246 "parser.y"

void yyerror(char *s) {
	fprintf(stderr, "Error on line %d: %s\n", getLineNumber(), s);
}
#line 454 "y.tab.c"

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
case 1:
#line 80 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_PROGRAM, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL); astreePrintTree(0, yyval.astree); astreeTranslate(yyval.astree); }
break;
case 2:
#line 84 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_DECL, NULL, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, NULL);		}
break;
case 3:
#line 85 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_DECL, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL);	}
break;
case 4:
#line 86 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC, NULL, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, NULL);		}
break;
case 5:
#line 87 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL);	}
break;
case 6:
#line 91 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 7:
#line 92 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 8:
#line 93 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 9:
#line 97 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SIMPLE_DECL, NULL, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, NULL, NULL); }
break;
case 10:
#line 101 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL); }
break;
case 14:
#line 111 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL); }
break;
case 15:
#line 112 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL); }
break;
case 16:
#line 113 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL); }
break;
case 17:
#line 114 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL); }
break;
case 18:
#line 115 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL); }
break;
case 19:
#line 119 "parser.y"
	{ 
			yyval.astree = astreeCreate(ASTREE_ARRAY_DECL, 
							  NULL, 
							  yystack.l_mark[-4].astree, 
							  astreeCreate(ASTREE_SYMBOL, yystack.l_mark[-2].symbol, NULL, NULL, NULL, NULL), 
							  NULL,
							  NULL);
		}
break;
case 20:
#line 128 "parser.y"
	{ 
			yyval.astree = astreeCreate(ASTREE_ARRAY_DECL_INI, 
							  NULL, 
							  yystack.l_mark[-6].astree, 
							  astreeCreate(ASTREE_SYMBOL, yystack.l_mark[-4].symbol, NULL, NULL, NULL, NULL), 
							  yystack.l_mark[-1].astree,
							  NULL);
		}
break;
case 21:
#line 139 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ARRAY_DECL_LITS, NULL, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, NULL);		}
break;
case 22:
#line 140 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ARRAY_DECL_LITS, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL);	}
break;
case 23:
#line 144 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_POINTER_DECL, NULL, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, NULL, NULL); /* astreePrintTree(0, $$); */ }
break;
case 24:
#line 148 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC1, NULL, yystack.l_mark[-5].astree, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, yystack.l_mark[0].astree);	}
break;
case 25:
#line 149 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC2, NULL, yystack.l_mark[-4].astree, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL);	}
break;
case 26:
#line 150 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC3, NULL, yystack.l_mark[-4].astree, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL);		}
break;
case 27:
#line 151 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC4, NULL, yystack.l_mark[-3].astree, yystack.l_mark[0].astree, NULL, NULL);	}
break;
case 28:
#line 155 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC_PARAM, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL);	}
break;
case 29:
#line 156 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC_PARAM, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL);	}
break;
case 30:
#line 160 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC_DECL, NULL, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 31:
#line 161 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC_DECL, NULL, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 32:
#line 162 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC_DECL, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL); }
break;
case 33:
#line 163 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC_DECL, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL); }
break;
case 34:
#line 167 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_BLOCK, NULL, yystack.l_mark[-1].astree, NULL, NULL, NULL); }
break;
case 35:
#line 171 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMDL, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 36:
#line 172 "parser.y"
	{ yyval.astree = NULL; }
break;
case 37:
#line 176 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SCALA_ASS, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 38:
#line 177 "parser.y"
	{
			yyval.astree = astreeCreate(ASTREE_VECT_SCALA_ASS,
					NULL, yystack.l_mark[-5].astree, 
					astreeCreate(ASTREE_SYMBOL, yystack.l_mark[-3].symbol, NULL, NULL, NULL, NULL),
					yystack.l_mark[0].astree, NULL);
	}
break;
case 39:
#line 183 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_IF, NULL, yystack.l_mark[-3].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 40:
#line 184 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_IF_ELSE, NULL, yystack.l_mark[-5].astree, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL); }
break;
case 41:
#line 185 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LOOP, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 42:
#line 186 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_INPUT, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL); }
break;
case 43:
#line 187 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OUTPUT, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL); }
break;
case 44:
#line 188 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_RETURN, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL); }
break;
case 45:
#line 189 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 46:
#line 194 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OUTPUT_LIST, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 47:
#line 196 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 48:
#line 200 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC_CALL, NULL, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, NULL, NULL);	}
break;
case 49:
#line 201 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC_CALL, NULL, yystack.l_mark[-2].astree, NULL, NULL, NULL);	}
break;
case 50:
#line 205 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC_CALL_LIST, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 51:
#line 206 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC_CALL_LIST, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL); }
break;
case 52:
#line 210 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 53:
#line 211 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 54:
#line 212 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 55:
#line 213 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_UNARY_MINUS, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL);		}
break;
case 56:
#line 214 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_POINTER, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL);			}
break;
case 57:
#line 215 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_DEREFERENCE, NULL, yystack.l_mark[0].astree, NULL, NULL, NULL);		}
break;
case 58:
#line 216 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_EXP_PARENTESIS, NULL, yystack.l_mark[-1].astree, NULL, NULL, NULL);	}
break;
case 59:
#line 220 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ADD, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 60:
#line 221 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SUB, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 61:
#line 222 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_DIV, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 62:
#line 223 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_MUL, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 63:
#line 224 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 64:
#line 225 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 65:
#line 226 "parser.y"
	{ 
			yyval.astree = astreeCreate(ASTREE_VECT_ACCESS, 
								NULL, yystack.l_mark[-3].astree, 
								astreeCreate(ASTREE_SYMBOL, yystack.l_mark[-1].symbol, NULL, NULL, NULL, NULL), 
								NULL, NULL); 
	}
break;
case 66:
#line 235 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OPERATOR_LE, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 67:
#line 236 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OPERATOR_GE, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 68:
#line 237 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OPERATOR_EQ, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 69:
#line 238 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OPERATOR_NE, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 70:
#line 239 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OPERATOR_OR, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 71:
#line 240 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OPERATOR_AND, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 72:
#line 241 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OPERATOR_GREATER, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
case 73:
#line 242 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OPERATOR_LESS, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL); }
break;
#line 964 "y.tab.c"
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
