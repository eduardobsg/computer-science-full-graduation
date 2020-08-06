/********************************************************************
	DECLARAÇÃO DA JANELA DE MACROS
	Criação:	01/08/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#pragma once
#include "afxwin.h"

#define WM_MACROMSG		WM_USER + 1
#define WMM_HIDE		0
#define WMM_INSERTMACRO	1


/********************************************************************
	CLASSE DA JANELA DE MACROS */

class CMacrosDlg : public CDialog
{
	DECLARE_DYNAMIC(CMacrosDlg)

public:
	CMacrosDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMacrosDlg();

// Dialog Data
	enum { IDD = IDD_MACROS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lstMacros;
	afx_msg void OnClose();
	afx_msg void OnDblClick();
};