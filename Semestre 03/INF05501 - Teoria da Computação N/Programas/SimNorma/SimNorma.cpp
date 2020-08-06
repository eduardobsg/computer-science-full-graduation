/********************************************************************
	IMPLEMENTAÇÃO DO PROGRAMA PRINCIPAL SIMNORMA
	Criação:	30/07/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#include "stdafx.h"
#include "SimNorma.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/********************************************************************
	VARIÁVEIS GLOBAIS */

CSimNormaApp theApp;


/********************************************************************
	CLASSE DO PROGRAMA SIMNORMA */

BEGIN_MESSAGE_MAP(CSimNormaApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()

CSimNormaApp::CSimNormaApp ()
{
}

BOOL CSimNormaApp::InitInstance ()
{
	// InitInstance - incializa o aplicativo SimNorma
	CWinApp::InitInstance();

	// inicia o controles comuns do Windows
	InitCommonControls();

	// tenta abrir a DLL do Scintilla
	if (!(hLib = LoadLibrary ("SciLexer.DLL")))
	{
		AfxMessageBox ("SimNorma não pode abrir a DLL do editor. Verifique se o arquivo SciLexer.dll encontra-se no diretório do SimNorma.", MB_ICONERROR);
		return FALSE;
	}

	// incia as bibliotecas OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer ();

	// atualiza o nome da chave do registro que guarda as configurações desta aplicação
	SetRegistryKey (_T("SimNorma"));

	// cria a janela principal do programa
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// abre a janela principal
	pFrame->LoadFrame (IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	// abre o projeto da linha de comando
	if (m_lpCmdLine[0] != '\0')
		pFrame->OpenProjectFile (m_lpCmdLine);

	// exibe a janela e a atualiza
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

int CSimNormaApp::ExitInstance()
{
	if (hLib)
		FreeLibrary (hLib);

	return CWinApp::ExitInstance();
}


/********************************************************************
	CLASSE DO DIÁLOGO SOBRE */

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange (CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog (CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange (CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

void CSimNormaApp::OnAppAbout ()
{
	// exibe o diálogo sobre
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}