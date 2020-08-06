/********************************************************************
	IMPLEMENTAÇÃO DAS FUNÇÕES MONOCOMPILER
	Criação:	30/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
	Descrição:	
				Funções de compilação para programa completamente
				monolítico sem macros.
********************************************************************/


#include "stdafx.h"
#include "MonoCompiler.h"


bool MonoCompiler (PROGRAM_BASE *pBaseProg)
{
	// MonoCompiler - compila um programa em um único monólito descartando macros
	PROGRAM *pProgram = (PROGRAM*) pBaseProg;
	LABEL **pSource = pBaseProg->pLabels, **pNew = NULL, *pCurLabel;
	UPDATESTACK pBaseLabels;
	unsigned int nCurLabel, nSourceCount = pBaseProg->nLabelsCount, nNewCount = 0, nNewIdx = nSourceCount;

	MACRO *pMacro;
	UPDATESTACK pStack;
	LABEL *pEndJump;
	unsigned char nUpdateFlags, nNewFlags;

	// adiciona cada rótulo cuidando especialmente das macros
	for (nCurLabel = 0; nCurLabel < nSourceCount; nCurLabel++)
	{
		// pega o rótulo
		pCurLabel = pSource[nCurLabel];
		// verifica se é algum rótulo de macro
		if ((pCurLabel->lType == ltMacroOperation) || (pCurLabel->lType == ltMacroTest))
		{
			// atualiza a macro chamada
			pMacro = pProgram->GetMacro (pCurLabel->sData);
			// inclui a macro
			if (!MC_IncludeMacro (pProgram, pMacro, &pStack, pCurLabel, pNew, nNewCount, pCurLabel->nIdx, nNewIdx))
				return false;
			// atualiza o rótulo de pulo final da macro
			if (pCurLabel->lType == ltMacroOperation)
				pEndJump = pCurLabel->pTrue;
			else
			{
				// adiciona o teste da macro
				pEndJump = new LABEL ();
				pEndJump->lType = ltTest;
				pEndJump->nIdx = nNewIdx++;
				pEndJump->pTrue = pCurLabel->pTrue;
				pEndJump->pFalse = pCurLabel->pFalse;
				pEndJump->SetData (pMacro->GetTest ());
				if (!MC_AddLabel (pEndJump, pNew, nNewCount))
				{
					delete pEndJump;
					return false;
				}
				// atualiza o rótulo
				if (!MC_UpdateMacroLabel (pMacro, pEndJump))
					return false;
				// adiciona na pilha das atualizações
				pBaseLabels.Push (pEndJump, UPDATE_TRUE | UPDATE_FALSE);
			}
			// atualiza os pulos dos rótulos finais das macros
			LABEL *pEndLabel;
			while (pEndLabel = (LABEL*) pStack.Pop (&nUpdateFlags))
			{
				nNewFlags = 0;
				if ((nUpdateFlags & UPDATE_TRUE) && !pEndLabel->pTrue || (pEndLabel->pTrue == pProgram->pMacroReturn))
				{
					pEndLabel->pTrue = pEndJump;
					nNewFlags |= UPDATE_TRUE;
				}
				if ((nUpdateFlags & UPDATE_FALSE) && !pEndLabel->pFalse || (pEndLabel->pFalse == pProgram->pMacroReturn))
				{
					pEndLabel->pFalse = pEndJump;
					nNewFlags |= UPDATE_FALSE;
				}
				// adiciona na pilha das atualizações
				pBaseLabels.Push (pEndLabel, nNewFlags);
			}
		}
		else
		{
			// adiciona o rótulo atual
			if (!MC_AddLabel (pCurLabel, pNew, nNewCount))
				return false;
			// adiciona na pilha das atualizações
			pBaseLabels.Push (pCurLabel, UPDATE_TRUE | UPDATE_FALSE);
		}
	}

	// atualiza os pulos dos rótulos que estão na pilha de atulização
	while (pCurLabel = (LABEL*) pBaseLabels.Pop (&nUpdateFlags))
	{
		// atualiza cada pulo
		if ((nUpdateFlags & UPDATE_TRUE) && pCurLabel->pTrue)
			pCurLabel->pTrue = MC_LabelFromIdx (pNew, nNewCount, pCurLabel->pTrue->nIdx);
		if ((nUpdateFlags & UPDATE_FALSE) && pCurLabel->pFalse)
			pCurLabel->pFalse = MC_LabelFromIdx (pNew, nNewCount, pCurLabel->pFalse->nIdx);
	}

	// atualiza os índices de todos os rótulos da nova lista
	for (nCurLabel = 0; nCurLabel < nNewCount; nCurLabel++)
		pNew[nCurLabel]->nIdx = nCurLabel;

	// destrói os rótulos de macro
	for (nCurLabel = 0; nCurLabel < nSourceCount; nCurLabel++)
	{
		// pega o rótulo
		pCurLabel = pSource[nCurLabel];
		// verifica se é algum rótulo de macro para o destruir
		if ((pCurLabel->lType == ltMacroOperation) || (pCurLabel->lType == ltMacroTest))
			delete pCurLabel;
	}

	// atualiza a lista do programa para a nova lista
	pBaseProg->pLabels = pNew;
	pBaseProg->nLabelsCount = nNewCount;
	free (pSource);

	// apaga as macros
	pProgram->ClearMacros ();

	// o programa foi compilado com sucesso
	return true;
}

bool MC_AddLabel (LABEL *pLabel, LABEL **&pLabels, unsigned int &nLabelsCount)
{
	// MC_AddLabel - adiciona um novo rótulo numa lista de rótulos
	if (!(pLabels = (LABEL**) realloc (pLabels, (nLabelsCount + 1) * sizeof (LABEL*))))
		return false;
	pLabels[nLabelsCount] = pLabel;
	nLabelsCount++;
	return true;
}

bool MC_UpdateMacroLabel (MACRO *pMacro, LABEL *pLabel)
{
	// MC_UpdateMacroLabel - atualiza o rótulo de uma macro substituindo os parâmetros
	// OBS: ESTA FUNÇÃO É ESPECÍFICA PARA A SIMULAÇÃO DA MÁQUINA NORMA
	if (!pLabel->sData)
		return true;
	char *sReg = pLabel->sData;
	// atualiza o nome do registrador
	while (*sReg)
		sReg++;
	sReg--;
	while ((*sReg != '-') && (sReg > pLabel->sData))
		sReg--;
	// verifica se a instrução usa algum registrador
	if (*sReg == '-')
	{
		// atualiza o registrador
		sReg++;
		// neste caso utiliza o registrador, verifica se ele é um parâmetro formal da macro
		if (pMacro->IsParam (sReg))
		{
			// atualiza com o seu valor
			char *sValue = pMacro->GetValue (sReg);
			// atualiza o dado do rótulo
			if (!(pLabel->sData = (char*) realloc (pLabel->sData, ((sReg - pLabel->sData) + strlen (sValue) + 1) * sizeof(char))))
				return false;
			// copia o valor do parâmetro
			strcpy (sReg, sValue);
		}
	}
	// a atualização foi feita com sucesso
	return true;
}

bool MC_IncludeMacro (PROGRAM *pProgram, MACRO *pMacro, UPDATESTACK *pStack, LABEL *pCaller, LABEL **&pLabels, unsigned int &nLabelsCount, unsigned int nFirstIdx, unsigned int &nSecondIdx)
{
	// MC_IncludeMacro - adiciona um novo macro numa lista de rótulos
	MAPPER pMap;
	UPDATESTACK pMacroLabels, pMacroStack;
	LABEL *pCurLabel, *pEndJump, *pEndLabel, *pNewLabel;
	MACRO *pCallMacro;
	char **pParams;
	bool bIsFirst = true;
	unsigned int i, nCurLabel, nNewIdx, nParamsCount, nMacroCount = pMacro->Count ();
	unsigned char nUpdateFlags, nNewFlags;


	// atualiza os parâmtros da macro
	for (i = 0; i < pCaller->nParamsCount; i++)
		pMacro->SetValue (i, pCaller->pParams[i]);

	// adiciona cada rótulo cuidando especialmente das macros
	for (nCurLabel = 0; nCurLabel < nMacroCount; nCurLabel++)
	{
		// pega o rótulo
		pCurLabel = (*pMacro)[nCurLabel];
		// verifica se é algum rótulo de macro
		if ((pCurLabel->lType == ltMacroOperation) || (pCurLabel->lType == ltMacroTest))
		{
			// mapeia o primeiro rótulo da macro
			if (bIsFirst)
			{
				nNewIdx = nFirstIdx;
				bIsFirst = false;
			}
			else
				nNewIdx = nSecondIdx++;
			// mapeia o rótulo para a macro
			pMap.Map (pCurLabel->nIdx, nNewIdx);
			// atualiza a macro chamada
			pCallMacro = pProgram->GetMacro (pCurLabel->sData);
			// guarda os parâmetros
			pParams = pCurLabel->pParams;
			nParamsCount = pCurLabel->nParamsCount;
			pCurLabel->pParams = NULL;
			pCurLabel->nParamsCount = 0;
			for (i = 0; i < nParamsCount; i++)
			{
				// verifica se é um parâmetro da macro atual
				if (pMacro->IsParam (pParams[i]))
					pCurLabel->AddParam (pMacro->GetValue (pParams[i]));
				else
					pCurLabel->AddParam (pParams[i]);
			}
			// inclui a macro
			if (!MC_IncludeMacro (pProgram, pCallMacro, &pMacroStack, pCurLabel, pLabels, nLabelsCount, nNewIdx, nSecondIdx))
			{
				// restaura os parâmetros antigos
				free (pCurLabel->pParams);
				pCurLabel->pParams = pParams;
				pCurLabel->nParamsCount = nParamsCount;
				// retorna falso
				return false;
			}
			// restaura os parâmetros antigos
			free (pCurLabel->pParams);
			pCurLabel->pParams = pParams;
			pCurLabel->nParamsCount = nParamsCount;
			// atualiza o rótulo de pulo final da macro
			if (pCurLabel->lType == ltMacroOperation)
				pEndJump = pCurLabel->pTrue;
			else
			{
				// calcula o novo índice
				nNewIdx = nSecondIdx++;
				// adiciona o teste da macro
				pEndJump = new LABEL ();
				pEndJump->lType = ltTest;
				pEndJump->nIdx = nNewIdx;
				pEndJump->pTrue = pCurLabel->pTrue;
				pEndJump->pFalse = pCurLabel->pFalse;
				pEndJump->SetData (pCallMacro->GetTest ());
				if (!MC_AddLabel (pEndJump, pLabels, nLabelsCount))
				{
					delete pEndJump;
					return false;
				}
				// atualiza o rótulo
				if (!MC_UpdateMacroLabel (pCallMacro, pEndJump))
					return false;
				// adiciona na pilha das atualizações
				pMacroLabels.Push (pEndJump, UPDATE_TRUE | UPDATE_FALSE);
			}
			// atualiza os pulos dos rótulos finais das macros
			while (pEndLabel = (LABEL*) pMacroStack.Pop (&nUpdateFlags))
			{
				nNewFlags = 0;
				if ((nUpdateFlags & UPDATE_TRUE) && !pEndLabel->pTrue || (pEndLabel->pTrue == pProgram->pMacroReturn))
				{
					pEndLabel->pTrue = pEndJump;
					nNewFlags |= UPDATE_TRUE;
				}
				if ((nUpdateFlags & UPDATE_FALSE) && !pEndLabel->pFalse || (pEndLabel->pFalse == pProgram->pMacroReturn))
				{
					pEndLabel->pFalse = pEndJump;
					nNewFlags |= UPDATE_FALSE;
				}
				// adiciona na pilha das atualizações
				pMacroLabels.Push (pEndLabel, nNewFlags);
			}
		}
		else
		{
			// calcula o novo índice
			if (bIsFirst)
			{
				nNewIdx = nFirstIdx;
				bIsFirst = false;
			}
			else
				nNewIdx = nSecondIdx++;
			// copia o rótulo
			pNewLabel = new LABEL ();
			pNewLabel->CopyFrom (pCurLabel);
			pNewLabel->nIdx = nNewIdx;
			// mapeia o rótulo que está sendo inserido
			pMap.Map (pCurLabel->nIdx, pNewLabel->nIdx);
			// adiciona o rótulo atual
			if (!MC_AddLabel (pNewLabel, pLabels, nLabelsCount))
				return false;
			// atualiza o rótulo
			if (!MC_UpdateMacroLabel (pMacro, pNewLabel))
				return false;
			// adiciona na pilha das atualizações
			pMacroLabels.Push (pNewLabel, UPDATE_TRUE | UPDATE_FALSE);
		}
	}

	// atualiza os pulos dos rótulos que estão na pilha de atulização
	while (pCurLabel = (LABEL*) pMacroLabels.Pop (&nUpdateFlags))
	{
		// verificam se algum rótulo pula para o fim
		if (!pCurLabel->pTrue || !pCurLabel->pFalse || (pCurLabel->pTrue == pProgram->pMacroReturn) || (pCurLabel->pFalse == pProgram->pMacroReturn))
			pStack->Push (pCurLabel, nUpdateFlags);
		// atualiza cada pulo
		if ((nUpdateFlags & UPDATE_TRUE) && pCurLabel->pTrue && (pCurLabel->pTrue != pProgram->pMacroReturn))
			pCurLabel->pTrue = MC_LabelFromIdx (pLabels, nLabelsCount, pMap[pCurLabel->pTrue->nIdx]);
		if ((nUpdateFlags & UPDATE_FALSE) && pCurLabel->pFalse && (pCurLabel->pFalse != pProgram->pMacroReturn))
			pCurLabel->pFalse = MC_LabelFromIdx (pLabels, nLabelsCount, pMap[pCurLabel->pFalse->nIdx]);
	}

	// a macro foi incluída com sucesso
	return true;
}

LABEL *MC_LabelFromIdx (LABEL **pLabels, unsigned int nLabelsCount, unsigned int nIdx)
{
	// MC_LabelFromIdx - retorna o rótulo baseado no seu índice
	LABEL *pCurLabel;
	unsigned int i;
	for (i = 0; i < nLabelsCount; i++)
	{
		// pega o rótulo
		pCurLabel = pLabels[i];
		// verifica o índice
		if (pCurLabel->nIdx == nIdx)
			return pCurLabel;
	}
	// neste caso o rótulo não foi encontrado
	return NULL;
}


/********************************************************************
	CLASSE MAPPER */

MAPPER::MAPPER ()
{
	// MAPPER - cria a classe de mapeamento
	pItems = NULL;
	nItemsCount = 0;
}
	
MAPPER::~MAPPER ()
{
	// ~MAPPER - destrói a classe de mapeamento
	free (pItems);
}

bool MAPPER::Map (unsigned int nNum1, unsigned int nNum2)
{
	// Map - mapeia um novo número
	if (!(pItems = (MAPPER_ITEM*) realloc (pItems, (nItemsCount + 1) * sizeof(MAPPER_ITEM))))
		return false;
	pItems[nItemsCount].nNum1 = nNum1;
	pItems[nItemsCount].nNum2 = nNum2;
	nItemsCount++;
	return true;
}

unsigned int MAPPER::operator[] (unsigned int nNum1)
{
	// [] - retorna o número mapeado por nNum1
	unsigned int i;
	for (i = 0; i < nItemsCount; i++)
	{
		if (pItems[i].nNum1 == nNum1)
			return pItems[i].nNum2;
	}
	return nNum1;
}