/********************************************************************
	DECLARAÇÃO DO PROGRAMA PRINCIPAL SIMNORMA
	Criação:	30/07/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#pragma once
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"


/********************************************************************
	VARIÁVEIS GLOBAIS */

//extern CSimNormaApp theApp;


/********************************************************************
	CLASSE DO PROGRAMA SIMNORMA */

class CSimNormaApp : public CWinApp
{
public:
	HMODULE hLib;
	CSimNormaApp ();

public:
	virtual BOOL InitInstance ();

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	virtual int ExitInstance();
//	virtual void HtmlHelp(DWORD_PTR dwData, UINT nCmd = 0x000F);
};