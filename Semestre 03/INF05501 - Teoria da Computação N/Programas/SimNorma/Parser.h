/********************************************************************
	DECLARAÇÃO DAS CLASSES DE PARSING
	Criação:	30/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#ifndef PARSER_HEADER
#define PARSER_HEADER


#include <stdlib.h>
#include <string.h>
#include "Program.h"
#include "Stack.h"


#define MAX_TOKEN	MAX_PATH


/********************************************************************
	CLASSE PARSER_BASE */

class PARSER_BASE
{
public:
	PROGRAM_BASE *pProgram;
	char *pSourceProg;

};


/********************************************************************
	CLASSE MONOPARSER */

enum  M_TOK_TYPE	{mttEnd, mttEndMacro,
					/* palavras chaves */
					mttIf, mttThen, mttElse, mttGoto, mttDo,
					/* operações e testes */
					mttLabel, mttFunction,
					/* delimitadores */
					mttDelimiter, mttEnter,
					/* erro */
					mttError};

enum M_ERROR_TYPE	{metEnd, metMemory, metEnterExpected, metLabelExpected,
					 metInstructionExpected, metTestNameExpected, metParenthesisExpected,
					 metOperationNameExpected, metThenExpected, metGotoExpected,
					 metLabelNameExpected, metElseExpected};

class MONOPARSER: public PARSER_BASE
{
private:
	char *prog;

	char **pLabels;
	unsigned int nLabelsCount;

	bool new_line;
	char token[MAX_TOKEN];
	M_TOK_TYPE tok_type;

	M_ERROR_TYPE err_type;
	char *err_pos;

	void get_token ();
	void put_back ();

	void ClearLabels ();
	bool AddLabel (char *lpName);
	unsigned int GetLabelIdx (char *lpName);

	bool evaluate_params (char **&pParams, unsigned int &nParamsCount);
	char *copy_string (char *lpStr);

public:
	MONOPARSER ();
	~MONOPARSER ();

	bool Parse (bool bIsMacro);

	M_ERROR_TYPE GetError () {return err_type;};
	char *GetErrorPos () {return err_pos;};

};


/********************************************************************
	CLASSE ITERACTIVEPARSER */

enum I_TOK_TYPE		{ittEnd, ittEndMacro,
					/* palavras chaves */
					ittIf, ittThen, ittElse, ittWhile, ittUntil, ittDo, ittExit,
					/* operações e testes */
					ittFunction,
					/* delimitadores */
					ittDelimiter,
					/* erro */
					ittError};

enum I_ERROR_TYPE	{ietEnd, ietSyntax, ietMemory, ietEndExpected, ietEndMacroExpected,
					ietParenthesisExpected, ietThenExpected, ietElseExpected, ietDoExpected};

class ITERACTIVEPARSER: public PARSER_BASE
{
private:
	char *prog;
	LABEL *end_label;

	bool support_exit, support_null;
	char token[MAX_TOKEN];
	I_TOK_TYPE tok_type;

	I_ERROR_TYPE err_type;
	char *err_pos;

	void get_token ();
	LABEL *evaluate_program ();
	bool evaluate_instruction (LABEL *&pResult, LABEL *pPrevious, LABEL *pEndJump, STACK *pEndLabels, bool bCodeBlock = false);
	LABEL *evaluate_condition (LABEL *pEndJump, STACK *pEndLabels);
	LABEL *evaluate_while (LABEL *pEndJump, STACK *pEndLabels);
	LABEL *evaluate_until (LABEL *pEndJump, STACK *pEndLabels);
	bool evaluate_params (char **&pParams, unsigned int &nParamsCount);

public:
	LABEL *pMacroReturn;

	bool Parse (bool bIsMacro, bool bRemoveNullOp = true);

	I_ERROR_TYPE GetError () {return err_type;};
	char *GetErrorPos () {return err_pos;};

};


/********************************************************************
	CLASSE PARSER */

struct LIB_INFO
{
	char *sName;
	char *sData;
};

enum TOK_TYPE	{ttEnd, ttEndMacro,
				/* palavras chaves */
				ttImport, ttMacro, ttTest, ttProgram, ttIteractive, ttMono,
				/* nomes e parâmetros */
				ttFunction,
				/* delimitadores */
				ttDelimiter,
				/* erro */
				ttError};

enum ERROR_TYPE	{etEnd, etMemory, etLibNameExpected, etLoadLibError, etProgTypeExpected,
				etMacroTypeExpected, etMacroNameExpected, etMacroParamsExpected,
				etParenthesisExpected, etTestNameExpected, etEndMacroExpected,
				etUndefinedMacro, etUndefinedMacroTest, etMacroCallParamsError,
				etMacroLoopError, etLibLoopError, etIteractiveError, etMonoError};

class PARSER: private PARSER_BASE
{
private:
	LIB_INFO *pLibs;
	unsigned int nLibsCount;

	char *prog;
	bool new_line;
	char token[MAX_TOKEN];
	TOK_TYPE tok_type;

	ERROR_TYPE err_type;
	M_ERROR_TYPE err_type_mono;
	I_ERROR_TYPE err_type_itr;
	char *err_libname, *err_source, *err_pos, *err_undefdata;

	void get_token ();
	void put_back ();
	bool evaluate_macro_params (MACRO *pMacro);

	void ClearLibs ();
	bool AddLibrary (char *sName, char *sData);
	bool AddLibrary (char *sFileName);
	char *GetLibraryData (char *sName);

	bool UpdateLibPath ();
	MACRO *DetectMacroLoop (MACRO *pMacro, STACK *pStack);

public:
	PROGRAM *pProgram;
	CString *sProgramPath;
	CString *sFilePath;

	PARSER ();
	~PARSER ();

	bool Parse (char *pSourceName, char *pSource, bool bEditor = false, bool bFullParse = true);

	ERROR_TYPE GetError () {return err_type;};
	M_ERROR_TYPE GetMonoError () {return err_type_mono;};
	I_ERROR_TYPE GetItrError () {return err_type_itr;};
	char *GetErrorLibName () {return err_libname;};
	char *GetErrorSource () {return err_source;};
	char *GetErrorSourcePos () {return err_pos;};
	char *GetErrorUndefData () {return err_undefdata;};

};


#endif