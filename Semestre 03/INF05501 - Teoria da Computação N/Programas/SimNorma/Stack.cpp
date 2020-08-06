/********************************************************************
	IMPLEMENTAÇÃO DA CLASSE STACK
	Criação:	28/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#include "stdafx.h"
#include "Stack.h"


/********************************************************************
	CLASSE STACK */

STACK::STACK ()
{
	// STACK - cria a classe de pilha
	pBase = NULL;
	nCount = 0;
}

STACK::~STACK ()
{
	// ~STACK - destrói a classe de pilha
	Clear ();
}

void STACK::Clear (STACK_ITEM *pItem)
{
	// Clear - destrói o item pItem e seus sucessores
	STACK_ITEM *pCur = pItem;
	while (pCur)
	{
		pItem = pCur;
		pCur = pCur->pNext;
		if (pItem->pDestroy)
			free (pItem->pData);
		free (pItem);
	}
}

void STACK::Clear ()
{
	// Clear - destrói toda a pilha
	Clear (pBase);
	pBase = NULL;
	nCount = 0;
}

unsigned int STACK::Count ()
{
	// Count - retorna o total de itens na pilha
	return nCount;
}

bool STACK::Push (void *pData)
{
	// Push - inclui um novo item na pilha
	STACK_ITEM *pNext = pBase;
	if (!(pBase = (STACK_ITEM*) malloc (sizeof (STACK_ITEM))))
		return false;
	pBase->pData = pData;
	pBase->pDestroy = false;
	pBase->pNext = pNext;
	nCount++;
	return true;
}

bool STACK::StrPush (char *pStr)
{
	// StrPush - inclui uma cópia da string no topo da pilha
	char *lpStr = (char*) malloc ((strlen (pStr) + 1) * sizeof(char));
	if (!lpStr)
		return false;
	strcpy (lpStr, pStr);
	if (!Push ((void*) lpStr))
	{
		free (lpStr);
		return false;
	}
	pBase->pDestroy = true;
	return true;
}

void *STACK::Pop ()
{
	// Pop - retorna um item da pilha
	if (!pBase)
		return NULL;
	else
	{
		STACK_ITEM *pNext = pBase->pNext;
		void *pResult = pBase->pData;
		free (pBase);
		pBase = pNext;
		nCount--;
		return pResult;
	}
}

bool STACK::IsInStack (char *pData)
{
	// IsInStack - verifica se um dado está na pilha
	STACK_ITEM *pCurItem = pBase;
	while (pCurItem)
	{
		if (stricmp ((char*) pCurItem->pData, pData) == 0)
			return true;
		pCurItem = pCurItem->pNext;
	}
	// não está na pilha
	return false;
}

bool STACK::IsInStack (void *pData)
{
	// IsInStack - verifica se um dado está na pilha
	STACK_ITEM *pCurItem = pBase;
	while (pCurItem)
	{
		if (pCurItem->pData == pData)
			return true;
		pCurItem = pCurItem->pNext;
	}
	// não está na pilha
	return false;
}


/********************************************************************
	CLASSE UPDATESTACK */

UPDATESTACK::~UPDATESTACK ()
{
	// ~UPDATESTACK - destrói a pilha de atualização
	Clear ();
}

void UPDATESTACK::Clear ()
{
	// Clear - limpa a pilha de atualização
	STACK_ITEM *pItem = pBase;
	while (pItem)
	{
		free (pItem->pData);
		pItem = pItem->pNext;
	}
	STACK::Clear ();
}

bool UPDATESTACK::Push (LABEL *pLabel, unsigned char nFlags)
{
	// Push - adiciona um novo item na pilha de atualização
	UPDATESTACK_ITEM *pItem = (UPDATESTACK_ITEM*) malloc (sizeof(UPDATESTACK_ITEM));
	if (!pItem)
		return false;
	pItem->pLabel = pLabel;
	pItem->nFlags = nFlags;
	return STACK::Push (pItem);
}

LABEL *UPDATESTACK::Pop (unsigned char *nFlags)
{
	// Pop - retira um item da pilha de atualização
	UPDATESTACK_ITEM *pItem = (UPDATESTACK_ITEM*) STACK::Pop ();
	LABEL *pResult;
	if (!pItem)
		return NULL;
	pResult = pItem->pLabel;
	if (nFlags)
		*nFlags = pItem->nFlags;
	free (pItem);
	return pResult;
}

bool UPDATESTACK::IsInStack (LABEL *pLabel)
{
	// IsInStack - verifica se o rótulo encontra-se na pilha
	STACK_ITEM *pItem = pBase;
	UPDATESTACK_ITEM *pUItem;
	while (pItem)
	{
		pUItem = (UPDATESTACK_ITEM*) pItem->pData;
		if (pUItem->pLabel == pLabel)
			return true;
	}
	return false;
}