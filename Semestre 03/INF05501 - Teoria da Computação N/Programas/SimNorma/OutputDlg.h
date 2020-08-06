/********************************************************************
	DECLARAÇÃO DA JANELA DE SAÍDA
	Criação:	02/08/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#pragma once
#include "afxwin.h"


/********************************************************************
	CLASSE DA JANELA DE SAÍDA */

class COutputDlg : public CDialog
{
	DECLARE_DYNAMIC(COutputDlg)

public:
	COutputDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COutputDlg();

// Dialog Data
	enum { IDD = IDD_OUTPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lstOutput;
};