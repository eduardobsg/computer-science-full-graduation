/********************************************************************
	IMPLEMENTAÇÃO DA JANELA DE REGISTRADORES
	Criação:	02/08/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#include "stdafx.h"
#include "SimNorma.h"
#include "RegistersDlg.h"
#include "EditRegDlg.h"


/********************************************************************
	INICIALIZAÇÃO DA CLASSE DA JANELA DE REGISTRADORES */

IMPLEMENT_DYNAMIC(CRegistersDlg, CDialog)

BEGIN_MESSAGE_MAP(CRegistersDlg, CDialog)
	ON_BN_CLICKED(IDC_CLEARREGS, OnClearRegs)
	ON_BN_CLICKED(IDC_EDITREG, OnEditReg)
	ON_NOTIFY(NM_DBLCLK, IDC_REGISTERS, OnRegDlgClick)
END_MESSAGE_MAP()


/********************************************************************
	CLASSE DA JANELA DE REGISTRADORES */

CRegistersDlg::CRegistersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegistersDlg::IDD, pParent)
{
}

CRegistersDlg::~CRegistersDlg()
{
}

void CRegistersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REGISTERS, m_lstRegs);
	DDX_Control(pDX, IDC_CLEARREGS, m_btnClearRegs);
	DDX_Control(pDX, IDC_EDITREG, m_btnEditReg);
}

void CRegistersDlg::OnClearRegs()
{
	// limpa o valor de todos os registradores
	GetParent ()->SendMessage (WM_REGMSG, WRM_CLEAR);
}

void CRegistersDlg::OnEditReg()
{
	// muda o valor de um registrador específico
	int nRegIdx = m_lstRegs.GetSelectionMark ();

	if (nRegIdx != -1)
	{
		CEditRegDlg dlgEditReg;
		dlgEditReg.sRegName = m_lstRegs.GetItemText (nRegIdx, 0);
		dlgEditReg.sRegValue.Format ("%d", GetParent ()->SendMessage (WM_REGMSG, WRM_GETREG, nRegIdx));
		if (dlgEditReg.DoModal () == IDOK)
		{
			WORD nValue = atol (dlgEditReg.sRegValue);
			DWORD lParam = (nRegIdx << 16) | nValue;
			GetParent ()->SendMessage (WM_REGMSG, WRM_SETREG, lParam);
		}
	}
}

void CRegistersDlg::OnRegDlgClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnEditReg ();
	*pResult = 0;
}
