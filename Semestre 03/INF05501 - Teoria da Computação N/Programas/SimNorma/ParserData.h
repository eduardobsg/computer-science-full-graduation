/********************************************************************
	DECLARAÇÃO DAS FUNÇÕES PARSERDATA
	Criação:	30/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#ifndef PARSERDATA_HEADER
#define PARSERDATA_HEADER


#include <stdio.h>


// constantes do parsing
#define DEFIMPORT		"importar"
#define DEFPROGRAM		"programa"
#define DEF_ITR			"iterativo"
#define DEF_MONO		"monolitico"
#define DEFMACRO		"macro"
#define DEFTEST			"teste"
#define DEFENDMACRO		"fimmacro"
#define DEFEXITMACRO	"retornar"

// constantes do parsing de programas iterativos e monolíticos
#define IF			"se"
#define THEN		"entao"
#define ELSE		"senao"
#define WHILE		"enquanto"
#define UNTIL		"ate"
#define DO			"faca"
#define GOTO		"va_para"

// contantes do analisador sintático
#define N_NULL		"V"
#define N_ZERO		"zero-"
#define N_ADD		"ad-"
#define N_SUB		"sub-"
#define N_PRINT		"print-"


// funções genéricas usadas pelo parsing
long fsize (FILE *f);
char *ExtractFileName (char *lpFilePath);


#endif