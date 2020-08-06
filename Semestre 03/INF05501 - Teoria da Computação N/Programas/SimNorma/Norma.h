/********************************************************************
	DECLARAÇÃO DA CLASSE SIMNORMA
	Criação:	31/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#ifndef NORMA_HEADER
#define NORMA_HEADER


#include <ctype.h>
#include "Program.h"
#include "ParserData.h"


#define WM_NORMAMSG		WM_USER + 2
#define WNM_PRINT		0


enum N_ERROR_TYPE	{netInvalidOperation, netInvalidTest, etInvalidRegister};
typedef LABEL*		CUR_STEP;

class SIMNORMA
{
private:
	unsigned long *pRegs;
	unsigned int nRegsCount;

	N_ERROR_TYPE err_type;
	char *err_data;

	void DestroyRegs ();
	bool GrowRegs (unsigned int nNewRegsCount);
	unsigned int GetRegNumber (char *sReg);
	void PrintRegs ();

public:
	PROGRAM *pProgram;

	SIMNORMA ();
	~SIMNORMA ();

	bool CheckProgram ();
	bool CheckRegister (char *sReg, MACRO *pMacro = NULL);

	N_ERROR_TYPE GetError () {return err_type;};
	char *GetErrorData () {return err_data;};

	void ClearRegs ();
	CUR_STEP Step (HWND hwndParent, CUR_STEP pCurStep = NULL, bool bPrintTuple = false);

	unsigned int GetCount () {return nRegsCount;};
	unsigned long &operator[] (unsigned int nIdx);

};


#endif