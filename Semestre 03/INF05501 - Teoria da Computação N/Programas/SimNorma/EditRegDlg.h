/********************************************************************
	DECLARAÇÃO DA JANELA DE EDIÇÃO DE REGISTRADORES
	Criação:	07/08/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#pragma once
#include "afxwin.h"


/********************************************************************
	CLASSE DA JANELA DE EDIÇÃO DE REGISTRADORES */

class CEditRegDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditRegDlg)

public:
	CString sRegName;
	CString sRegValue;

public:
	CEditRegDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditRegDlg();

// Dialog Data
	enum { IDD = IDD_EDITREG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_txtRegName;
	CEdit m_txtRegValue;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};