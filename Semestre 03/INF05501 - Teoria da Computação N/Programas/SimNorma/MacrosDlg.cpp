/********************************************************************
	IMPLEMENTAÇÃO DA JANELA DE MACROS
	Criação:	01/08/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#include "stdafx.h"
#include "SimNorma.h"
#include "MacrosDlg.h"


/********************************************************************
	INICIALIZAÇÃO DA CLASSE DA JANELA DE MACROS */

IMPLEMENT_DYNAMIC(CMacrosDlg, CDialog)

BEGIN_MESSAGE_MAP(CMacrosDlg, CDialog)
	ON_WM_CLOSE()
	ON_LBN_DBLCLK(IDC_MACROS, OnDblClick)
END_MESSAGE_MAP()


/********************************************************************
	CLASSE DA JANELA DE MACROS */

CMacrosDlg::CMacrosDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMacrosDlg::IDD, pParent)
{
}

CMacrosDlg::~CMacrosDlg()
{
}

void CMacrosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MACROS, m_lstMacros);
}

void CMacrosDlg::OnClose()
{
	GetParent ()->SendMessage (WM_MACROMSG, WMM_HIDE);
	CDialog::OnClose();
}

void CMacrosDlg::OnDblClick()
{
	if (m_lstMacros.GetCurSel () != LB_ERR)
		GetParent ()->SendMessage (WM_MACROMSG, WMM_INSERTMACRO);
}
