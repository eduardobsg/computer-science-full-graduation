/********************************************************************
	DECLARAÇÃO DA JANELA DE REGISTRADORES
	Criação:	02/08/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define WM_REGMSG		WM_USER + 3
#define WRM_CLEAR		0
#define WRM_GETREG		1
#define WRM_SETREG		2


/********************************************************************
	CLASSE DA JANELA DE REGISTRADORES */

class CRegistersDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegistersDlg)

public:
	CRegistersDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRegistersDlg();

// Dialog Data
	enum { IDD = IDD_REGISTERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstRegs;
	CButton m_btnClearRegs;
	CButton m_btnEditReg;
	afx_msg void OnClearRegs();
	afx_msg void OnEditReg();
	afx_msg void OnRegDlgClick(NMHDR *pNMHDR, LRESULT *pResult);
};