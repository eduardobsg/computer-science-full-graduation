/********************************************************************
	IMPLEMENTA플O DA JANELA DE EDI플O DE REGISTRADORES
	Cria豫o:	07/08/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#include "stdafx.h"
#include "SimNorma.h"
#include "EditRegDlg.h"


/********************************************************************
	INICIALIZA플O DA CLASSE DA JANELA DE EDI플O DE REGISTRADORES */

IMPLEMENT_DYNAMIC(CEditRegDlg, CDialog)

BEGIN_MESSAGE_MAP(CEditRegDlg, CDialog)
END_MESSAGE_MAP()


/********************************************************************
	CLASSE DA JANELA DE EDI플O DE REGISTRADORES */

CEditRegDlg::CEditRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditRegDlg::IDD, pParent)
{
}

CEditRegDlg::~CEditRegDlg()
{
}

void CEditRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REGNAME, m_txtRegName);
	DDX_Control(pDX, IDC_REGVALUE, m_txtRegValue);
}

BOOL CEditRegDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// inicializa o valor dos controles
	m_txtRegName.SetWindowText (sRegName);
	m_txtRegValue.SetWindowText (sRegValue);
	m_txtRegValue.SetFocus ();

	return TRUE;
}

void CEditRegDlg::OnOK()
{
	// atualiza o valor do registrador
	m_txtRegValue.GetWindowText (sRegValue);

	CDialog::OnOK();
}
