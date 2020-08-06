/* 
 * Lista dos tokens, com valores constantes associados.
 * Este arquivo serah posterioremente substituido, nao acrescente nada.
 * Os valores das constantes sao arbitrarios, mas nao podem ser alterados.
 * Cada valor deve ser distinto e fora da escala ascii. 
 * Assim, nao conflitam entre si e com os tokens representados pelo proprio
 * valor ascii de caracteres isolados. 
 */
 
#define KW_INT        256
#define KW_FLOAT      257
#define KW_BOOL       258
#define KW_CHAR       259
#define KW_IF         261
#define KW_THEN       262
#define KW_ELSE       263
#define KW_WHILE      264
#define KW_DO         265
#define KW_INPUT      266
#define KW_RETURN     267
#define KW_OUTPUT     268

#define OPERATOR_LE   270
#define OPERATOR_GE   271
#define OPERATOR_EQ   272
#define OPERATOR_NE   273
#define OPERATOR_AND  274
#define OPERATOR_OR   275

#define TK_IDENTIFIER 280
#define LIT_INTEGER   281
#define LIT_FLOA      282
#define LIT_FALSE     283
#define LIT_TRUE	    284
#define LIT_CHAR      285
#define LIT_STRING    286

#define TOKEN_ERROR   290

/* END OF FILE */

