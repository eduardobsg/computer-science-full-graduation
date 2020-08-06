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
extern YYSTYPE yylval;
