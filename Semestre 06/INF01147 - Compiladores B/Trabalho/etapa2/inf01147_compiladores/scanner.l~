%{
    
    #include "hashtable.h"
    #include "y.tab.h"
    
    Hashtable *hashtable;

    int running = 1;
    int lineNumber = 1;
    
%}


%X BLOCK_COMMENT
%%

word                                { return KW_WORD;   }
bool                                { return KW_BOOL;   }
byte                                { return KW_BYTE;   }
if                                  { return KW_IF;     }
then                                { return KW_THEN;   }
else                                { return KW_ELSE;   }
loop                                { return KW_LOOP;   }
input                               { return KW_INPUT;  }
return                              { return KW_RETURN; }
output                              { return KW_OUTPUT; }
        
FALSE|false                         { add(hashtable, yytext, LIT_FALSE); return LIT_FALSE; }
TRUE|true                           { add(hashtable, yytext, LIT_TRUE ); return LIT_TRUE;  }
        
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
        
[A-Za-z][A-Za-z0-9_]*         	 	{ yylval.entry  = add(hashtable, yytext, TK_IDENTIFIER);         return TK_IDENTIFIER;   }
-?[0-9][a-fA-F0-9]*                 { yylval.number = atoi(yytext); return LIT_INTEGER;              }

[0-9][A-Za-z_]+             		{ add(hashtable, yytext, TOKEN_ERROR  ); return TOKEN_ERROR;    /* wrong identifier*/   }

'.'                                 { add(hashtable, yytext, LIT_CHAR   ); return LIT_CHAR;         }
\"([^\\\"]|\\.)*\"                  { add(hashtable, yytext, LIT_STRING ); return LIT_STRING;       }

.                                   {               }
\n                                  { lineNumber++; }

%%

void initMe(void) {
    // init hashtable
    hashtable = create(TABLE_SIZE);
	fprintf(stderr, "Table has been created.\n");
}

void destroyMe(void) {
    // free some memory
    destroy(hashtable);
}

int isRunning(void) {
    return running;
}

int getLineNumber(void) {
    return lineNumber;
}

int yywrap() {
    running = 0;
    print(hashtable);
    return 1;
}
