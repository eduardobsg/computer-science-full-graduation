/********************************************************************
	DECLARAÇÃO DA JANELA DE ERRO DE COMPILAÇÃO
	Criação:	02/08/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#pragma once
#include "afxwin.h"


/********************************************************************
	CLASSE DA JANELA DE ERRO DE COMPILAÇÃO */

class CCompilerErrorDlg : public CDialog
{
	DECLARE_DYNAMIC(CCompilerErrorDlg)

public:
	CCompilerErrorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCompilerErrorDlg();

// Dialog Data
	enum { IDD = IDD_COMPILERERROR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString sErrorFile, sErrorDescrip;
	CStatic m_imgIcon;
	CEdit m_txtErrorFile;
	CEdit m_txtErrorDescrip;
	virtual BOOL OnInitDialog();
};