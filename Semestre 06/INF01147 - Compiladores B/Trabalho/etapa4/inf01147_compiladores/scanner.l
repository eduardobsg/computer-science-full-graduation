%{
    
    #include "hashtable.h"
	#include "astree.h"
	#include "semantics.h"
    #include "y.tab.h"
    
    Hashtable *hashtable;

    int lineNumber = 1;
    
%}


%X BLOCK_COMMENT
%%

word                                {
										// KW_WORD is not a type, per se, but
										// CAN BE used to tell the types appart.
										// Same goes to KW_BOOL and KW_BYTE
										yylval.value = KW_WORD; return KW_WORD;   
									}
bool                                { yylval.value = KW_BOOL; return KW_BOOL;   }
byte                                { yylval.value = KW_BYTE; return KW_BYTE;   }

if                                  { return KW_IF;     }
then                                { return KW_THEN;   }
else                                { return KW_ELSE;   }
loop                                { return KW_LOOP;   }
input                               { return KW_INPUT;  }
return                              { return KW_RETURN; }
output                              { return KW_OUTPUT; }
        
FALSE|false                         { yylval.symbol = add(hashtable, yytext, LIT_FALSE); return LIT_FALSE; }
TRUE|true                           { yylval.symbol = add(hashtable, yytext, LIT_TRUE ); return LIT_TRUE;  }
        
"<="                                { return OPERATOR_LE;  }
">="                                { return OPERATOR_GE;  }
"=="                                { return OPERATOR_EQ;  }
"!="                                { return OPERATOR_NE;  }
"&&"                                { return OPERATOR_AND; }
"||"                                { return OPERATOR_OR;  }
        
"//".*\n                            { lineNumber++;        }
"/*"                                { BEGIN BLOCK_COMMENT; }

[,;:\(\)\[\]\{\}\+\-\*\/\<\>=!&\$]  { return yytext[0];    /*** GOTTA ESCAPE THESE  \ " [ ] ^ - ? . * + | ( ) $ / { } % < >           ***/ }

<BLOCK_COMMENT>"*/"                 { BEGIN INITIAL; }
<BLOCK_COMMENT>.                    {                }
<BLOCK_COMMENT>\n                   { lineNumber++;  }
        
[A-Za-z][A-Za-z0-9_]*         	 	{ yylval.symbol = add(hashtable, yytext, TK_IDENTIFIER); return TK_IDENTIFIER;   }
[0-9][a-fA-F0-9]*               	{ yylval.symbol = add(hashtable, yytext, LIT_INTEGER); return LIT_INTEGER; }

[0-9][A-Za-z_]+             		{ add(hashtable, yytext, TOKEN_ERROR); return TOKEN_ERROR; /* wrong identifier */ }

'.'                                 { yylval.symbol = add(hashtable, yytext, LIT_CHAR   ); return LIT_CHAR;         }
\"([^\\\"]|\\.)*\"                  { yylval.symbol = add(hashtable, yytext, LIT_STRING ); return LIT_STRING;       }

.                                   {               }
\n                                  { lineNumber++; }

%%

void initMe(void) {
    // init hashtable
    hashtable = create(TABLE_SIZE);
	fprintf(stderr, "Table has been created.\n");
}

int getLineNumber(void) {
    return lineNumber;
}

int yywrap() {
    print(hashtable);
    return 1;
}
