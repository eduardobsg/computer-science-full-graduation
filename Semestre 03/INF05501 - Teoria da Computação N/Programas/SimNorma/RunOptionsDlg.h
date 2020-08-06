/********************************************************************
	DECLARA플O DA JANELA DE OP합ES DA EXECU플O
	Cria豫o:	14/08/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#pragma once
#include "afxwin.h"


/********************************************************************
	CLASSE DA JANELA DE OP합ES DE EXECU플O */

class CRunOptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(CRunOptionsDlg)

public:
	CString sOutFile;
	DWORD dwDelay;
	bool bUseDelay, bUpdateControls, bUpdateRegs, bPrintComp, bSaveComp;

public:
	CRunOptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRunOptionsDlg();

// Dialog Data
	enum { IDD = IDD_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_txtDelay;
	CButton m_chkUseDelay;
	CButton m_chkUpdateControls;
	CButton m_chkUpdateRegs;
	CButton m_chkPrintComp;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CEdit m_txtOutputFile;
	afx_msg void OnBnClickedBrowse();
	CButton m_chkSaveComp;
};
