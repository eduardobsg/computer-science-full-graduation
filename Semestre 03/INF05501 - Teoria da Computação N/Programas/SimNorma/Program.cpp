/********************************************************************
	IMPLEMENTAÇÃO DAS CLASSES LABEL, MACRO E PROGRAM_BASE
	Criação:	27/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#include "stdafx.h"
#include "Program.h"
#include "Stack.h"


/********************************************************************
	CLASSE LABEL */

LABEL::LABEL ()
{
	// LABEL - cria a classe de rótulo
	lType = ltOperation;
	nIdx = 0;
	sData = NULL;
	pTrue = pFalse = NULL;
	pParams = NULL;
	nParamsCount = 0;
}

LABEL::~LABEL ()
{
	// ~LABEL - destrói a classe de rótulo
	free (sData);
	if (pParams)
	{
		unsigned int i;
		for (i = 0; i < nParamsCount; i++)
			free (pParams[i]);
		free (pParams);
	}
}

bool LABEL::CopyFrom (LABEL *pSource)
{
	// CopyFrom - copia os dados de uma outra label
	lType = pSource->lType;
	if (pSource->sData)
	{
		if (!(sData = (char*) malloc ((strlen (pSource->sData) + 1) * sizeof(char))))
			return false;
		strcpy (sData, pSource->sData);
	}
	else
		sData = NULL;
	pTrue = pSource->pTrue;
	pFalse = pSource->pFalse;
}

void LABEL::SetLastJump (LABEL *pJumpTo, LABEL *pEndJump)
{
	// SetLastJump - modifica o último pulo da intrução
	if (!pTrue || (pTrue == pEndJump))
		pTrue = pJumpTo;
	if (!pFalse || (pFalse == pEndJump))
		pFalse = pJumpTo;
}

void LABEL::SetData (char *lpData)
{
	// SetData - modifica a propriedade sData
	if (lpData)
	{
		sData = (char*) realloc (sData, (strlen (lpData) + 1) * sizeof(char));
		strcpy (sData, lpData);
	}
	else if (sData)
	{
		free (sData);
		sData = NULL;
	}
}

bool LABEL::AddParam (char *lpParam)
{
	// AddParam - adiciona um novo parâmetro
	if (!(pParams = (char**) realloc (pParams, (nParamsCount + 1) * sizeof(char*))))
		return false;
	pParams[nParamsCount++] = lpParam;
	return true;
}


/********************************************************************
	CLASSE PROGRAM_BASE_BASE */

PROGRAM_BASE::PROGRAM_BASE ()
{
	// PROGRAM_BASE - cria a classe base de programa
	pLabels = NULL;
	nLabelsCount = 0;
}

PROGRAM_BASE::~PROGRAM_BASE ()
{
	// ~PROGRAM_BASE - destrói a classe base de programa
	Clear ();
}

void PROGRAM_BASE::Clear ()
{
	// Clear - limpa o programa, removendo todos os labels
	if (pLabels)
	{
		unsigned int i;
		// destrói cada classe de label
		for (i = 0; i < nLabelsCount; i++)
			delete pLabels[i];
		// destrói o array de labels
		free (pLabels);
		pLabels = NULL;
	}
	// zera o contador de labels
	nLabelsCount = 0;
}

unsigned int PROGRAM_BASE::Count ()
{
	// Count - retorna o total de rótulos do programa
	return nLabelsCount;
}

LABEL *PROGRAM_BASE::AddLabel ()
{
	// AddLabel - adiciona um label no programa
	pLabels = (LABEL**) realloc (pLabels, (nLabelsCount + 1) * sizeof(LABEL*));
	if (!pLabels)
		return NULL;
	else
	{
		// cria a classe de rótulo
		nLabelsCount++;
		pLabels[nLabelsCount - 1] = new LABEL ();
		return pLabels[nLabelsCount - 1];
	}
}

LABEL *&PROGRAM_BASE::operator[] (unsigned int nIdx)
{
	// operador [] - retorna o label de índice nIdx
	static LABEL *pNullLabel = NULL;

	if (nIdx < nLabelsCount)
		return pLabels[nIdx];
	else
		return pNullLabel;
}

void PROGRAM_BASE::OrganizeFlowchart (CDC *pDC, CString &sStart, CString &sEnd)
{
	// OrganizeFlowchart - organiza o fluxograma
	CSize szText = pDC->GetTextExtent ("AOjg");
	unsigned int nItemHeight = szText.cy;

	if (nLabelsCount)
	{
		STACK pStack;
		unsigned int nWidth, nItemWidth;

		// atualiza a posição da partida e da parada
		fiStart.nTop = fiEnd.nTop = 8;
		szText = pDC->GetTextExtent (sStart);
		nItemWidth = szText.cx + 8;

		// atualiza a posição padrão para todos os rótulos
		for (unsigned int i = 0; i < nLabelsCount; i++)
			pLabels[i]->fiFlowData.nLeft = pLabels[i]->fiFlowData.nTop = 0;

		// atualiza a posição do primeiro item
		OrganizeFlowchart (pDC, pStack, pLabels[0], 8, (2 * nItemHeight + 16) + fiStart.nTop, nWidth, nItemHeight);

		// atualiza a posição X da parada
		szText = pDC->GetTextExtent (sEnd);
		fiEnd.nLeft = (nWidth / 2) - (szText.cx / 2);

		// calcula a largura do primeiro item
		szText = pDC->GetTextExtent (pLabels[0]->sData);
		if ((pLabels[0]->lType == ltTest) || (pLabels[0]->lType == ltMacroTest))
			nWidth = ((12 + szText.cy) * (4 + szText.cx)) / 12;
		else
			nWidth = szText.cx + 16;

		// atualiza a posição da partida e da parada
		fiStart.nLeft = /*fiEnd.nLeft = */pLabels[0]->fiFlowData.nLeft + (nWidth / 2) - (nItemWidth / 2);
	}
	else
	{
		// atualiza o fluxograma vazio
		fiStart.nTop = 8;
		fiEnd.nTop = (2 * nItemHeight + 16) + fiStart.nTop;
		fiStart.nLeft = fiEnd.nLeft = 8;
	}
}

void PROGRAM_BASE::OrganizeFlowchart (CDC *pDC, STACK &pStack, LABEL *pLabel, long int nX, long int nY, unsigned int &nWidth, unsigned int &nHeight)
{
	// OrganizeFlowchar - organiza uma sub-árvore do fluxograma
	CSize szText = pDC->GetTextExtent (pLabel->sData);
	unsigned int nFalseWidth = 0, nItemTop, nItemWidth;

	// atualiza as variáveis
	nWidth = 0;
	pStack.Push (pLabel);
	if ((pLabel->lType == ltTest) || (pLabel->lType == ltMacroTest))
	{
		nItemTop = nY + 2 * nHeight + 20;
		nItemWidth = ((12 + szText.cy) * (4 + szText.cx)) / 12;
	}
	else
	{
		nItemTop = nY + 2 * nHeight + 16;
		nItemWidth = szText.cx + 16;
	}

	// verifica se o caminho falso existe
	if (pLabel->pFalse)
	{
		// verifica se já não foi visitado
		if (!pStack.IsInStack (pLabel->pFalse))
			OrganizeFlowchart (pDC, pStack, pLabel->pFalse, nX, nItemTop, nFalseWidth, nHeight);
	}

	// verifica se o caminho verdadeiro existe
	if ((pLabel->lType == ltTest) || (pLabel->lType == ltMacroTest))
	{
		if (pLabel->pTrue)
		{
			// verifica se já não foi visitado
			if (!pStack.IsInStack (pLabel->pTrue))
			{
				if (nFalseWidth)
				{
					OrganizeFlowchart (pDC, pStack, pLabel->pTrue, nX + nFalseWidth + nItemWidth + 8, nItemTop, nWidth, nHeight);
					nWidth += nItemWidth;
				}
				else
					OrganizeFlowchart (pDC, pStack, pLabel->pTrue, nX, nItemTop, nWidth, nHeight);
			}
		}
	}

	// atualiza a posição da parada
	if (fiEnd.nTop < nItemTop)
		fiEnd.nTop = nItemTop;

	// atualiza a posição do label
	if (nWidth)
		pLabel->fiFlowData.nLeft = nX + nFalseWidth + 4;
	else if (nFalseWidth)
		pLabel->fiFlowData.nLeft = nX + (nFalseWidth / 2) - (nItemWidth / 2);
	else
		pLabel->fiFlowData.nLeft = nX;
	pLabel->fiFlowData.nTop = nY;

	// atualiza tamanho da sub-árvore
	if (!nWidth && !nFalseWidth)
		nWidth = nItemWidth;
	else
		nWidth += nFalseWidth;
}


/********************************************************************
	CLASSE MACRO */

MACRO::MACRO () : PROGRAM_BASE ()
{
	// MACRO - cria a classe de macro
	sName = sTest = sData = sLibName = NULL;
	mType = mtIteractive;
	pParams = NULL;
	nParamsCount = 0;
}

MACRO::~MACRO ()
{
	// ~MACRO - destrói a classe de macro
	free (sName);
	free (sTest);
	Clear ();
	// destrói a classe pai
	PROGRAM_BASE::~PROGRAM_BASE ();
}

void MACRO::SetName (char *lpName)
{
	// SetName - modifica o nome da macro
	if (lpName)
	{
		sName = (char*) realloc (sName, (strlen (lpName) + 1) * sizeof(char));
		strcpy (sName, lpName);
	}
	else if (sName)
	{
		free (sName);
		sName = NULL;
	}
}

char *MACRO::GetName ()
{
	// GetName - retorna o nome da macro
	return sName;
}

void MACRO::SetTest (char *lpTest)
{
	// SetTest - modifica o nome do teste relacionado a esta macro
	if (lpTest)
	{
		sTest = (char*) realloc (sTest, (strlen (lpTest) + 1) * sizeof(char));
		strcpy (sTest, lpTest);
	}
	else if (sTest)
	{
		free (sTest);
		sTest = NULL;
	}
}

char *MACRO::GetTest ()
{
	// GetTest - retorna o nome da macro
	return sTest;
}

void MACRO::ClearParams ()
{
	// Clear - remove todos os parâmetros relacionado com a macro atual
	if (pParams)
	{
		unsigned int i;
		// destrói cada parâmetro
		for (i = 0; i < nParamsCount; i++)
		{
			free (pParams[i].sName);
			free (pParams[i].sValue);
		}
		// destrói o arranjo
		free (pParams);
		pParams = NULL;
	}
	// atualiza o contador de parâmetros
	nParamsCount = 0;
}

unsigned int MACRO::ParamsCount ()
{
	// Count - retorna o número de parâmetros da macro
	return nParamsCount;
}

bool MACRO::AddParameter (char *lpName, char *lpValue)
{
	// AddParameter - adiciona um novo parâmetro na macro
	pParams = (MACRO_PARAM*) realloc (pParams, ++nParamsCount * sizeof(MACRO_PARAM));
	if (!pParams)
		return false;
	// atualiza as propriedades
	pParams[nParamsCount - 1].sName = (char*) malloc ((strlen (lpName) + 1) * sizeof(char));
	strcpy (pParams[nParamsCount - 1].sName, lpName);
	pParams[nParamsCount - 1].sValue = (char*) malloc ((strlen (lpValue) + 1) * sizeof(char));
	strcpy (pParams[nParamsCount - 1].sValue, lpValue);
	// retorna OK
	return true;
}

MACRO_PARAM *MACRO::GetParam (char *lpName)
{
	// GetParam - retorna o parâmetro de nome lpName
	unsigned int i;
	// procura cada parâmetro
	for (i = 0; i < nParamsCount; i++)
	{
		if (!stricmp (pParams[i].sName, lpName))
			return &pParams[i];
	}
	// não encontrou
	return NULL;
}

char *MACRO::GetParamName (unsigned int nIdx)
{
	// GetParamName - retorna o nome de um parâmetro
	if (nIdx < nParamsCount)
		return pParams[nIdx].sName;
	else
		return NULL;
}

bool MACRO::SetValue (char *lpName, char *lpValue)
{
	// SetValue - modifica um parâmetro
	MACRO_PARAM *pParam = GetParam (lpName);
	if (!pParam)
		return false;
	else
	{
		pParam->sValue = (char*) realloc (pParam->sValue, (strlen (lpValue) + 1) * sizeof(char));
		if (!pParam->sValue)
			return false;
		else
		{
			strcpy (pParam->sValue, lpValue);
			return true;
		}
	}
}

bool MACRO::SetValue (unsigned int nIdx, char *lpValue)
{
	// SetValue - modifica um parâmetro
	if (nIdx < nParamsCount)
	{
		pParams[nIdx].sValue = (char*) realloc (pParams[nIdx].sValue, (strlen (lpValue) + 1) * sizeof(char));
		if (!pParams[nIdx].sValue)
			return false;
		else
		{
			strcpy (pParams[nIdx].sValue, lpValue);
			return true;
		}
	}
	else
		return false;
}

char *MACRO::GetValue (char *lpName)
{
	// GetValue - retorna o valor de um parâmetro
	MACRO_PARAM *pParam = GetParam (lpName);
	if (!pParam)
		return NULL;
	else
		return pParam->sValue;
}

char *MACRO::GetValue (unsigned int nIdx)
{
	// GetValue - retorna o valor de um parâmetro
	if (nIdx < nParamsCount)
		return pParams[nIdx].sValue;
	else
		return NULL;
}


/********************************************************************
	CLASSE PROGRAM */

PROGRAM::PROGRAM () : PROGRAM_BASE ()
{
	// PROGRAM - iniciliza a classe de programa
	pMacros = NULL;
	nMacrosCount = 0;
	// cria o rótulo de retorno de macro
	pMacroReturn = new LABEL ();
}

PROGRAM::~PROGRAM ()
{
	// ~PROGRAM - destrói a classe de program
	ClearMacros ();
	delete pMacroReturn;
	PROGRAM_BASE::~PROGRAM_BASE ();
}

void PROGRAM::ClearMacros (bool bEditorClear)
{
	// ClearMacros - remove todos os macros do programa
	unsigned int nNewCount = 0;
	if (pMacros)
	{
		long i;
		MACRO **pNewMacros;
		// aloca espaço para os macros que não serão removidos
		if (bEditorClear)
		{
			// calcula o total de macros que serão mantidos
			for (i = 0; i < nMacrosCount; i++)
			{
				if (pMacros[i]->GetExternalMacro ())
					nNewCount++;
			}
			// aloca o espaço necessário
			pNewMacros = (MACRO**) malloc (nNewCount * sizeof(MACRO*));
			nNewCount = 0;
		}
		// destrói cada classe de macro
		for (i = 0; i < nMacrosCount; i++)
		{
			if (bEditorClear)
			{
				if (pMacros[i]->GetExternalMacro () && pNewMacros)
					pNewMacros[nNewCount++] = pMacros[i];
				else
					delete pMacros[i];
			}
			else
				delete pMacros[i];
		}
		// destrói o array de macros
		free (pMacros);
		if (bEditorClear)
			pMacros = pNewMacros;
		else
			pMacros = NULL;
	}
	// zera o contador de macros
	if (bEditorClear)
		nMacrosCount = nNewCount;
	else
		nMacrosCount = 0;
}

unsigned int PROGRAM::MacrosCount ()
{
	// MacrosCount - retorna o número de macros do programa
	return nMacrosCount;
}

MACRO *PROGRAM::AddMacro ()
{
	// AddMacro - adiciona uma macro no programa
	pMacros = (MACRO**) realloc (pMacros, (nMacrosCount + 1) * sizeof(MACRO*));
	if (!pMacros)
		return NULL;
	else
	{
		// cria a classe de macro
		nMacrosCount++;
		pMacros[nMacrosCount - 1] = new MACRO ();
		return pMacros[nMacrosCount - 1];
	}
}

MACRO *PROGRAM::GetMacro (unsigned int nIdx)
{
	// GetMacro - retorna uma macro baseada no seu índice
	if (nIdx < nMacrosCount)
		return pMacros[nIdx];
	else
		return NULL;
}

MACRO *PROGRAM::GetMacro (char *lpMacroName)
{
	// GetMacro - retorna uma macro baseada no nome dela
	unsigned int i;
	// verifica cada macro
	for (i = 0; i < nMacrosCount; i++)
	{
		if (!stricmp (pMacros[i]->GetName (), lpMacroName))
			return pMacros[i];
	}
	// a macro não foi encontrada
	return NULL;
}