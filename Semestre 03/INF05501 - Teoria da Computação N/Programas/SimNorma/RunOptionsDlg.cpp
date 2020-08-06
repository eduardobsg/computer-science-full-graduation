/********************************************************************
	IMPLEMENTA플O DA JANELA DE OP합ES DA EXECU플O
	Cria豫o:	14/08/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#include "stdafx.h"
#include "SimNorma.h"
#include "RunOptionsDlg.h"


/********************************************************************
	INICIALIZA플O DA CLASSE DA JANELA DE OP합ES */

IMPLEMENT_DYNAMIC(CRunOptionsDlg, CDialog)

BEGIN_MESSAGE_MAP(CRunOptionsDlg, CDialog)
	ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()


/********************************************************************
	CLASSE DA JANELA DE OP합ES DE EXECU플O */

CRunOptionsDlg::CRunOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRunOptionsDlg::IDD, pParent)
{
}

CRunOptionsDlg::~CRunOptionsDlg()
{
}

void CRunOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DELAY, m_txtDelay);
	DDX_Control(pDX, IDC_USEDELAY, m_chkUseDelay);
	DDX_Control(pDX, IDC_UPDATECONTROLS, m_chkUpdateControls);
	DDX_Control(pDX, IDC_UPDATEREGS, m_chkUpdateRegs);
	DDX_Control(pDX, IDC_PAINTCOMP, m_chkPrintComp);
	DDX_Control(pDX, IDC_OUTPUTFILE, m_txtOutputFile);
	DDX_Control(pDX, IDC_SAVECOMP, m_chkSaveComp);
}

BOOL CRunOptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// atualiza os controles
	CString sStr;
	m_txtOutputFile.SetWindowText (sOutFile);
	sStr.Format ("%d", dwDelay);
	m_txtDelay.SetWindowText (sStr);
	m_chkUseDelay.SetCheck (bUseDelay ? BST_CHECKED : BST_UNCHECKED);
	m_chkUpdateControls.SetCheck (bUpdateControls ? BST_CHECKED : BST_UNCHECKED);
	m_chkUpdateRegs.SetCheck (bUpdateRegs ? BST_CHECKED : BST_UNCHECKED);
	m_chkPrintComp.SetCheck (bPrintComp ? BST_CHECKED : BST_UNCHECKED);
	m_chkSaveComp.SetCheck (bSaveComp ? BST_CHECKED : BST_UNCHECKED);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRunOptionsDlg::OnOK()
{
	CString sStr;

	m_txtOutputFile.GetWindowText (sOutFile);

	m_txtDelay.GetWindowText (sStr);
	dwDelay = atol (sStr.GetBuffer (sStr.GetLength ()));
	sStr.ReleaseBuffer ();

	bUseDelay = (m_chkUseDelay.GetCheck () == BST_CHECKED);
	bUpdateControls = (m_chkUpdateControls.GetCheck () == BST_CHECKED);
	bUpdateRegs = (m_chkUpdateRegs.GetCheck () == BST_CHECKED);
	bPrintComp = (m_chkPrintComp.GetCheck () == BST_CHECKED);
	bSaveComp = (m_chkSaveComp.GetCheck () == BST_CHECKED);

	CDialog::OnOK();
}

void CRunOptionsDlg::OnBnClickedBrowse()
{
	CFileDialog dlgOpen (TRUE, "txt", sOutFile.GetBuffer (sOutFile.GetLength ()), OFN_HIDEREADONLY, "Arquivos de Texto (*.txt)|*.txt|Todos os Arquivos (*.*)|*.*||", this);
	sOutFile.ReleaseBuffer ();
	if (dlgOpen.DoModal () == IDOK)
	{
		sOutFile = dlgOpen.GetPathName ();
		m_txtOutputFile.SetWindowText (sOutFile);
	}
}