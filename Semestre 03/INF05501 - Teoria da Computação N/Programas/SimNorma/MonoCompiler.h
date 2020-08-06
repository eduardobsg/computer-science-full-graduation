/********************************************************************
	DECLARAÇÃO DAS FUNÇÕES MONOCOMPILER
	Criação:	30/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
	Descrição:	
				Funções de compilação para programa completamente
				monolítico sem macros.
********************************************************************/


#ifndef MONOCOMPILER_HEADER
#define MONOCOMPILER_HEADER


#include "Program.h"
#include "ParserData.h"
#include "Stack.h"


bool MonoCompiler (PROGRAM_BASE *pBaseProg);

bool MC_AddLabel (LABEL *pLabel, LABEL **&pLabels, unsigned int &nLabelsCount);
bool MC_UpdateMacroLabel (MACRO *pMacro, LABEL *pLabel);
bool MC_IncludeMacro (PROGRAM *pProgram, MACRO *pMacro, UPDATESTACK *pStack, LABEL *pCaller, LABEL **&pLabels, unsigned int &nLabelsCount, unsigned int nFirstIdx, unsigned int &nSecondIdx);
LABEL *MC_LabelFromIdx (LABEL **pLabels, unsigned int nLabelsCount, unsigned int nIdx);


/********************************************************************
	CLASSE MAPPER */

struct MAPPER_ITEM
{
	unsigned int nNum1, nNum2;
};

class MAPPER
{
private:
	MAPPER_ITEM *pItems;
	unsigned int nItemsCount;

public:
	MAPPER ();
	~MAPPER ();

	bool Map (unsigned int nNum1, unsigned int nNum2);
	unsigned int operator[] (unsigned int nNum1);

};


#endif