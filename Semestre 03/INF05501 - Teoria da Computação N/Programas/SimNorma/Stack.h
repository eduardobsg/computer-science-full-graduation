/********************************************************************
	DECLARAÇÃO DA CLASSE STACK
	Criação:	28/05/2003
	Copyright:	(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#ifndef STACK_HEADER
#define STACK_HEADER


#include <stdlib.h>
#include <string.h>
#include "Program.h"


/********************************************************************
	CLASSE STACK */

struct STACK_ITEM
{
	void *pData;
	bool pDestroy;
	STACK_ITEM *pNext;
};

class STACK
{
private:
	STACK_ITEM *pBase;
	unsigned int nCount;

	void Clear (STACK_ITEM *pItem);

public:
	STACK ();
	~STACK ();

	void Clear ();
	unsigned int Count ();
	bool Push (void *pData);
	bool StrPush (char *pStr);
	void *Pop ();

	bool IsInStack (char *pData);
	bool IsInStack (void *pData);

	friend class UPDATESTACK;

};


/********************************************************************
	CLASSE UPDATESTACK */

#define UPDATE_NONE		0
#define UPDATE_TRUE		1
#define UPDATE_FALSE	2

struct UPDATESTACK_ITEM
{
	LABEL *pLabel;
	unsigned char nFlags;
};

class UPDATESTACK: public STACK
{
public:
	~UPDATESTACK ();

	void Clear ();
	bool Push (LABEL *pLabel, unsigned char nFlags);
	LABEL *Pop (unsigned char *nFlags);

	bool IsInStack (LABEL *pLabel);

};


#endif