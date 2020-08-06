/********************************************************************
	DECLARAÇÃO DAS CLASSES LABEL, MACRO E PROGRAM
	Criação:	27/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#ifndef PROGRAM_HEADER
#define PROGRAM_HEADER


#include <stdlib.h>
#include <string.h>
#include "stdafx.h"


/********************************************************************
	CLASSE STACK EXTERNA */
class STACK;


/********************************************************************
	CLASSE LABEL */

struct FLOWCHART_ITEM
{
	long int nLeft, nTop;
	//bool bTop, bLeft, bBottom, bRight;
	RECT rPos;
};

enum LABEL_TYPE {ltOperation, ltTest, ltMacroOperation, ltMacroTest};

class LABEL
{
public:
	LABEL_TYPE lType;
	unsigned int nIdx;
	char *sData;
	LABEL *pTrue, *pFalse;
	char **pParams;
	unsigned int nParamsCount;

	FLOWCHART_ITEM fiFlowData;
	RECT rInstructRect;

	LABEL ();
	~LABEL ();

	bool CopyFrom (LABEL *pSource);
	void SetLastJump (LABEL *pJumpTo, LABEL *pEndJump);
	void SetData (char *lpData);
	bool AddParam (char *lpParam);

};


/********************************************************************
	CLASSE PROGRAM_BASE */

class PROGRAM_BASE
{
private:
	LABEL **pLabels;
	unsigned int nLabelsCount;

public:
	FLOWCHART_ITEM fiStart, fiEnd;

	PROGRAM_BASE ();
	~PROGRAM_BASE ();

	void Clear ();
	unsigned int Count ();
	LABEL *AddLabel ();

	LABEL *&operator[] (unsigned int nIdx);

	void OrganizeFlowchart (CDC *pDC, CString &sStart, CString &sEnd);
	void OrganizeFlowchart (CDC *pDC, STACK &pStack, LABEL *pLabel, long int nX, long int nY, unsigned int &nWidth, unsigned int &nHeight);
	friend bool MonoCompiler (PROGRAM_BASE *pProgram);

};


/********************************************************************
	CLASSE MACRO */

enum MACRO_TYPE {mtMono, mtIteractive};

struct MACRO_PARAM
{
	char *sName;
	char *sValue;
};

class MACRO: public PROGRAM_BASE
{
private:
	char *sName, *sTest, *sData, *sLibName;
	MACRO_TYPE mType;
	MACRO_PARAM *pParams;
	unsigned int nParamsCount;
	bool bExternalMacro;

	MACRO_PARAM *GetParam (char *lpName);

public:
	MACRO ();
	~MACRO ();

	void SetName (char *lpName);
	char *GetName ();

	void SetTest (char *lpTest);
	char *GetTest ();

	void SetType (MACRO_TYPE mtNewType) {mType = mtNewType;};
	MACRO_TYPE GetType () {return mType;};

	void SetData (char *lpData) {sData = lpData;};
	char *GetData () {return sData;};

	void SetLibName (char *lpLibName) {sLibName = lpLibName;};
	char *GetLibName () {return sLibName;};

	void SetExternalMacro (bool bIsExternalMacro) {bExternalMacro = bIsExternalMacro;};
	bool GetExternalMacro () {return bExternalMacro;};

	void ClearParams ();
	unsigned int ParamsCount ();
	bool AddParameter (char *lpName, char *lpValue);
	bool IsParam (char *lpName) {return GetParam (lpName);};
	char *GetParamName (unsigned int nIdx);

	bool SetValue (char *lpName, char *lpValue);
	bool SetValue (unsigned int nIdx, char *lpValue);
	char *GetValue (char *lpName);
	char *GetValue (unsigned int nIdx);

};


/********************************************************************
	CLASSE PROGRAM */

class PROGRAM: public PROGRAM_BASE
{
private:
	MACRO **pMacros;
	unsigned int nMacrosCount;

public:
	LABEL *pMacroReturn;

	PROGRAM ();
	~PROGRAM ();

	void ClearMacros (bool bEditorClear = false);
	unsigned int MacrosCount ();
	MACRO *AddMacro ();
	MACRO *GetMacro (unsigned int nIdx);
	MACRO *GetMacro (char *lpMacroName);

};


#endif