/********************************************************************
	IMPLEMENTAÇÃO DA JANELA PRINCIPAL DO SIMNORMA
	Criação:	30/07/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#include "stdafx.h"
#include "SimNorma.h"
#include "MainFrm.h"
#include "MacrosDlg.h"
#include "RegistersDlg.h"
#include "OutputDlg.h"
#include "CompilerErrorDlg.h"
#include "RunOptionsDlg.h"
#include "Parser.h"
#include "Norma.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define IDC_MONITECTRL		AFX_IDW_PANE_FIRST
#define IDC_FLOWCHARTCTRL	32778
#define IDC_INSTRUCTSCTRL	32779

#define SIMNORMA_KEY		"Software\\SimNorma"


/********************************************************************
	INICIALIZAÇÃO DA CLASSE DA JANELA PRINCIPAL */

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_NEWPROJ, NewProject)
	ON_COMMAND(ID_FILE_OPENPROJ, OpenProject)
	ON_COMMAND(ID_FILE_SAVEPROJ, OnSaveProject)
	ON_COMMAND(ID_FILE_SAVEASPROJ, OnSaveProjectAs)
	ON_COMMAND(ID_EDIT_UNDO, OnUndo)
	ON_COMMAND(ID_EDIT_REDOACTION, OnRedo)
	ON_COMMAND(ID_EDIT_CUT, OnCut)
	ON_COMMAND(ID_EDIT_COPY, OnCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnPaste)
	ON_COMMAND(ID_EDIT_DELETESEL, OnDelete)
	ON_COMMAND(ID_EDIT_SELECTALL, OnSelectAll)
	ON_COMMAND(ID_VIEW_MACROS, OnViewMacros)
	ON_COMMAND(ID_EDIT_REFRESH, OnRefresh)
	ON_COMMAND(ID_MODE_MONITE, OnModeMonite)
	ON_COMMAND(ID_MODE_FLOWCHART, OnModeFlowchart)
	ON_COMMAND(ID_MODE_INSTRUCTS, OnModeInstructs)
	ON_COMMAND(ID_MODE_RUN, OnRun)
	ON_COMMAND(ID_MODE_STEP, OnModeStep)
	ON_COMMAND(ID_MODE_PAUSE, OnModePause)
	ON_COMMAND(ID_MODE_STOP, OnModeStop)
	ON_UPDATE_COMMAND_UI(ID_MODE_RUN, OnUpdateModeRun)
	ON_UPDATE_COMMAND_UI(ID_MODE_STEP, OnUpdateModeStep)
	ON_UPDATE_COMMAND_UI(ID_MODE_PAUSE, OnUpdateModePause)
	ON_UPDATE_COMMAND_UI(ID_MODE_STOP, OnUpdateModeStop)
	ON_COMMAND(ID_MODE_OPTIONS, OnModeOptions)
	ON_COMMAND(ID_VIEW_REGISTERS, OnViewRegisters)
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_COMMAND(ID_HELP_TOPICS, OnHelpTopics)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


/********************************************************************
	FUNÇÕES INTERNAS */

void ExtractFilePath (CString &sFileName)
{
	// ExtractFilePath - extrai o path de um arquivo
	int nLength = sFileName.GetLength ();
	if (!nLength)
		return;
	nLength--;

	while (nLength && (sFileName[nLength] != '\\'))
		nLength--;

	if (nLength)
		sFileName = sFileName.Mid (0, nLength + 1);
}


/********************************************************************
	CLASSE DA JANELA PRINCIPAL */

CMainFrame::CMainFrame ()
{
	m_bAutoMenuEnable = FALSE;

	GetModuleFileName (AfxGetApp ()->m_hInstance, sSimNormaPath.GetBuffer (MAX_PATH), MAX_PATH);
	sSimNormaPath.ReleaseBuffer ();
	ExtractFilePath (sSimNormaPath);

	sProjectFileName = "";
	sProjectFilePath = "";
	emCurrentMode = emMonite;
	bIsRunning = false;
	sStart = "partida";
	sEnd = "parada";

	bModified = false;
	bNeedCompile = true;

	hOutFile = INVALID_HANDLE_VALUE;
	sOutFile = "";
	dwDelay = 200;
	bUseDelay = true;
	bUpdateControls = true;
	bUpdateRegs = true;
	bPrintComp = true;
	bSaveComp = false;
}

CMainFrame::~CMainFrame ()
{
}

int CMainFrame::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
	// cria os controles da janela principal
	CString sStr;
	if (CFrameWnd::OnCreate (lpCreateStruct) == -1)
		return -1;

	// atualiza o ícone da janela
	SetIcon (LoadIcon (AfxGetApp()->m_hInstance, MAKEINTRESOURCE (IDR_MAINFRAME)), FALSE);
	SetIcon (LoadIcon (AfxGetApp()->m_hInstance, MAKEINTRESOURCE (IDR_MAINFRAME)), TRUE);

	// cria o controle de edição do Monitè
	if (!m_wndMonite.Create (NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, IDC_MONITECTRL, NULL))
	{
		TRACE0("Erro ao criar o editor de Monitè\n");
		return -1;
	}
	m_wndMonite.pProgram = &pMacros;
	m_wndMonite.sSimNormaPath = &sSimNormaPath;
	m_wndMonite.sFilePath = &sProjectFilePath;
	m_wndMonite.sFileName = &sProjectFileName;

	// cria o controle de fluxograma
	if (!m_wndFlowchart.Create (NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, IDC_FLOWCHARTCTRL, NULL))
	{
		TRACE0("Erro ao criar o visualizador de fluxograma\n");
		return -1;
	}
	m_wndFlowchart.ShowWindow (SW_HIDE);
	m_wndFlowchart.pProgram = &pProgram;

	// cria o controle de instruções rotuladas
	if (!m_wndInstructs.Create (NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, IDC_INSTRUCTSCTRL, NULL))
	{
		TRACE0("Erro ao criar o visualizador de instruções rotuladas\n");
		return -1;
	}
	m_wndInstructs.ShowWindow (SW_HIDE);
	m_wndInstructs.pProgram = &pProgram;
	
	// cria a barra de ferramentas
	if (!m_wndToolBar.CreateEx (this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar (IDR_MAINFRAME))
	{
		TRACE0 ("Erro ao criar a barra de ferramentas\n");
		return -1;
	}
	sStr.LoadString (IDS_TOOLBAR);
	m_wndToolBar.SetWindowText (sStr);
	bToolbarVisible = true;

	// cria a barra de estatus
	if (!m_wndStatusBar.Create (this) ||
		!m_wndStatusBar.SetIndicators (indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Erro ao criar a barra de estatus\n");
		return -1;
	}
	bStatusVisible = true;

	// cria a janela de macros disponíveis
	if (!dlgMacros.Create (IDD_MACROS, this))
	{
		TRACE0("Erro ao criar a janela de macros\n");
		return -1;
	}

	// cria a janela de registradores
	if (!dlgRegisters.Create (IDD_REGISTERS, this))
	{
		TRACE0("Erro ao criar a janela de registradores\n");
		return -1;
	}
	// cria o header da janela
	dlgRegisters.m_lstRegs.SetExtendedStyle (dlgRegisters.m_lstRegs.GetExtendedStyle () | LVS_EX_FULLROWSELECT);
	dlgRegisters.m_lstRegs.InsertColumn (0, "Nome", LVCFMT_LEFT, 64);
	dlgRegisters.m_lstRegs.InsertColumn (1, "Valor", LVCFMT_CENTER, 104, 0);
	
	// cria a janela de saída
	if (!dlgOutput.Create (IDD_OUTPUT, this))
	{
		TRACE0("Erro ao criar a janela de saída\n");
		return -1;
	}

	// atualiza o modo
	emCurrentMode = emFlowchart;
	bIsRunning = false;
	SetMode (emMonite);

	// atualiza o título da janela
	UpdateTitle ();

	// abre as configurações da IDE
	LoadIDE ();

	return 0;
}

BOOL CMainFrame::PreCreateWindow (CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// atualiza as informações da classe da janela
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid () const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump (CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

void CMainFrame::OnSetFocus (CWnd* /*pOldWnd*/)
{
	// atualiza o foco para o controle ativo
	m_wndMonite.SetFocus ();
}

BOOL CMainFrame::OnCmdMsg (UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// verifica se o controle ativo pega esta mensagem
	if (m_wndMonite.OnCmdMsg (nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// caso controle, manda a mensagem para a função padrão
	return CFrameWnd::OnCmdMsg (nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// pega o tamanho do editor de Monitè
	RECT rRect;
	m_wndMonite.GetWindowRect (&rRect);
	ScreenToClient (&rRect);

	// atualiza o tamanho do fluxograma
	m_wndFlowchart.SetWindowPos (NULL, rRect.left, rRect.top, rRect.right - rRect.left, rRect.bottom - rRect.top, SWP_NOZORDER);

	// atualiza o tamanho das instruções rotuladas
	m_wndInstructs.SetWindowPos (NULL, rRect.left, rRect.top, rRect.right - rRect.left, rRect.bottom - rRect.top, SWP_NOZORDER);
}

void CMainFrame::OnClose ()
{
	// OnClose - verifica se o usuário quer salvar as modificações antes de fechar
	if (m_wndMonite.GetModified ())
	{
		CString sMsg;
		sMsg.LoadString (IDS_MSG1);
		int nReturn = MessageBox (sMsg, NULL, MB_YESNOCANCEL | MB_ICONQUESTION);

		switch (nReturn)
		{
		case IDCANCEL:
			return;
		case IDYES:
			if (!SaveProject ())
				return;
		}
	}

	// pára a execução
	rmRunMode = rmStop;

	// salva o ambiente
	SaveIDE ();

	CFrameWnd::OnClose();
}

LRESULT CMainFrame::WindowProc (UINT message, WPARAM wParam, LPARAM lParam)
{
	// WindowProc - manda as mensagens personalizadas aos editores

	switch (message)
	{
	case WM_COMMAND:
		{
			switch (wParam)
			{
			case ID_VIEW_TOOLBAR:
			case ID_VIEW_STATUS_BAR:
				{
					if (wParam == ID_VIEW_TOOLBAR)
						bToolbarVisible = !bToolbarVisible;
					if (wParam == ID_VIEW_STATUS_BAR)
						bStatusVisible = !bStatusVisible;
					LRESULT lResult = CFrameWnd::WindowProc(message, wParam, lParam);
					SendMessage (WM_SIZE);
					return lResult;
				}
			}

			break;
		}

	case WM_MACROMSG:
		{
			switch (wParam)
			{
			case WMM_HIDE:
				{
					GetMenu ()->GetSubMenu (2)->CheckMenuItem (ID_VIEW_MACROS, MF_UNCHECKED | MF_BYCOMMAND);
					bMacrosVisible = false;
					break;
				}

			case WMM_INSERTMACRO:
				{
					if (emCurrentMode == emMonite)
					{
						CString sMacro;
						dlgMacros.m_lstMacros.GetText (dlgMacros.m_lstMacros.GetCurSel (), sMacro);
						dlgMacros.m_lstMacros.SetCurSel (LB_ERR);
						m_wndMonite.SetSelText (sMacro);
						m_wndMonite.SetFocus ();
					}
					break;
				}

			}

			break;
		}

	case WM_NORMAMSG:
		{
			switch (wParam)
			{
			case WNM_PRINT:
				PrintOutput ((LPCSTR) lParam);
				break;
			}

			break;
		}

	case WM_REGMSG:
		{
			switch (wParam)
			{
			case WRM_CLEAR:
				pNorma.ClearRegs ();
				UpdateRegisters ();
				break;

			case WRM_GETREG:
				return pNorma[lParam];

			case WRM_SETREG:
				pNorma[HIWORD (lParam)] = LOWORD (lParam);
				UpdateRegisters ();
				break;

			}

			break;
		}

	case WM_MONITEMSG:
		{
			switch (wParam)
			{
			case WMM_RELOADMACROS:
				UpdateMacros ();
				break;

			}

			break;
		}

	case WM_NOTIFY:
		{
			switch (wParam)
			{
			case IDC_MONITECTRL:
				{
					SCNotification *notification = (SCNotification *)lParam;
					switch (notification->nmhdr.code)
					{
					case SCN_CHARADDED:
						m_wndMonite.CharAdded ((char)notification->ch);
						break;

					case SCN_MODIFIED:
						if (notification->modificationType & (SC_MOD_INSERTTEXT | SC_MOD_DELETETEXT))
							bNeedCompile = true;
						if (bModified != m_wndMonite.GetModified ())
						{
							bModified = m_wndMonite.GetModified ();
							UpdateTitle ();
						}
						break;

					}

					break;
				}

			}

			break;
		}
	}

	return CFrameWnd::WindowProc(message, wParam, lParam);
}


/********************************************************************
	FUNÇÕES DE EDIÇÃO */

bool RegReadDWORD (HKEY hKey, LPTSTR lpName, DWORD *dwValue)
{
	// RegReadDWORD - lê um DWORD do registro do Windows
	DWORD dwType, dwSize;

	if (!hKey)
		return false;

	if (RegQueryValueEx (hKey, lpName, NULL, &dwType, NULL, &dwSize) == ERROR_SUCCESS)
	{
		if (dwType == REG_DWORD)
		{
			if (RegQueryValueEx (hKey, lpName, NULL, &dwType, (LPBYTE) dwValue, &dwSize) == ERROR_SUCCESS)
				return true;
		}
	}

	return false;
}

bool RegReadString (HKEY hKey, LPTSTR lpName, CString &sStr)
{
	// RegReadString - lê uma string do registro do Windows
	DWORD dwType, dwSize;

	if (!hKey)
		return false;

	if (RegQueryValueEx (hKey, lpName, NULL, &dwType, NULL, &dwSize) == ERROR_SUCCESS)
	{
		if (dwType == REG_SZ)
		{
			if (RegQueryValueEx (hKey, lpName, NULL, &dwType, (LPBYTE) sStr.GetBuffer (dwSize), &dwSize) == ERROR_SUCCESS)
			{
				sStr.ReleaseBuffer ();
				return true;
			}
			sStr.ReleaseBuffer ();
		}
	}

	return false;
}

bool RegWriteDWORD (HKEY hKey, LPTSTR lpName, DWORD dwValue)
{
	// RegWriteDWORD - escreve um DWORD no registro do Windows
	if (!hKey)
		return false;

	if (RegSetValueEx (hKey, lpName, 0, REG_DWORD, (BYTE*) &dwValue, sizeof(DWORD)) == ERROR_SUCCESS)
		return true;
	else
		return false;
}

bool RegWriteString (HKEY hKey, LPTSTR lpName, CString sStr)
{
	// RegWriteString - escreve uma string no registro do Windows
	if (!hKey)
		return false;

	if (RegSetValueEx (hKey, lpName, 0, REG_SZ, (BYTE*)(LPCSTR) sStr, (sStr.GetLength () + 1) * sizeof(char)) == ERROR_SUCCESS)
		return true;
	else
		return false;
}

void CMainFrame::LoadIDE ()
{
	// LoadIDE - abre as configurações da IDE
	HKEY hKey;
	DWORD dwValue;
	POINT pPos;

	if (RegOpenKey (HKEY_CURRENT_USER, SIMNORMA_KEY, &hKey) != ERROR_SUCCESS)
		hKey = NULL;

	// abre as opções da execução
	RegReadString (hKey, "Out File", sOutFile);
	if (RegReadDWORD (hKey, "Delay", &dwValue))
        dwDelay = dwValue;
	if (RegReadDWORD (hKey, "Use Delay", &dwValue))
		bUseDelay = dwValue;
	if (RegReadDWORD (hKey, "Update Ctrls", &dwValue))
		bUpdateControls = dwValue;
	if (RegReadDWORD (hKey, "Update Regs", &dwValue))
		bUpdateRegs = dwValue;
	if (RegReadDWORD (hKey, "Print Comp", &dwValue))
		bPrintComp = dwValue;
	if (RegReadDWORD (hKey, "Save Comp", &dwValue))
		bSaveComp = dwValue;

	// barra de ferramentas
	if (RegReadDWORD (hKey, "Toolbar", &dwValue))
	{
		if (!dwValue)
			SendMessage (WM_COMMAND, ID_VIEW_TOOLBAR); 
	}

	// barra de estados
	if (RegReadDWORD (hKey, "Status", &dwValue))
	{
		if (!dwValue)
			SendMessage (WM_COMMAND, ID_VIEW_STATUS_BAR); 
	}

	// visibilidade da janela de macros
	if (RegReadDWORD (hKey, "Macros Visible", &dwValue))
	{
		bMacrosVisible = dwValue;
		GetMenu ()->GetSubMenu (2)->CheckMenuItem (ID_VIEW_MACROS, (bMacrosVisible ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		dlgMacros.ShowWindow (bMacrosVisible ? SW_SHOW : SW_HIDE);
	}
	else
	{
		bMacrosVisible = true;
		GetMenu ()->GetSubMenu (2)->CheckMenuItem (ID_VIEW_MACROS, MF_CHECKED | MF_BYCOMMAND);
		dlgMacros.ShowWindow (SW_SHOW);
	}

	// posição da janela de macro
	if (RegReadDWORD (hKey, "Macros X", &dwValue))
		pPos.x = dwValue;
	else
		pPos.x = 0;
	if (RegReadDWORD (hKey, "Macros Y", &dwValue))
		pPos.y = dwValue;
	else
		pPos.y = 0;
	dlgMacros.SetWindowPos (NULL, pPos.x, pPos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	// visibilidade da janela de registradores
	if (RegReadDWORD (hKey, "Regs Visible", &dwValue))
	{
		bRegsVisible = dwValue;
		GetMenu ()->GetSubMenu (2)->CheckMenuItem (ID_VIEW_REGISTERS, (bRegsVisible ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	}
	else
	{
		bRegsVisible = true;
		GetMenu ()->GetSubMenu (2)->CheckMenuItem (ID_VIEW_REGISTERS, MF_CHECKED | MF_BYCOMMAND);
	}

	// posição da janela de registradores
	if (RegReadDWORD (hKey, "Regs X", &dwValue))
		pPos.x = dwValue;
	else
		pPos.x = 0;
	if (RegReadDWORD (hKey, "Regs Y", &dwValue))
		pPos.y = dwValue;
	else
		pPos.y = 0;
	dlgRegisters.SetWindowPos (NULL, pPos.x, pPos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	// visibilidade da janela de saída
	if (RegReadDWORD (hKey, "Output Visible", &dwValue))
	{
		bOutputVisible = dwValue;
		GetMenu ()->GetSubMenu (2)->CheckMenuItem (ID_VIEW_OUTPUT, (bOutputVisible ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	}
	else
	{
		bOutputVisible = true;
		GetMenu ()->GetSubMenu (2)->CheckMenuItem (ID_VIEW_OUTPUT, MF_CHECKED | MF_BYCOMMAND);
	}

	// posição da janela de saída
	if (RegReadDWORD (hKey, "Output X", &dwValue))
		pPos.x = dwValue;
	else
		pPos.x = 0;
	if (RegReadDWORD (hKey, "Output Y", &dwValue))
		pPos.y = dwValue;
	else
		pPos.y = 0;
	dlgOutput.SetWindowPos (NULL, pPos.x, pPos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	// fecha a chave
	if (hKey)
		RegCloseKey (hKey);
}

void CMainFrame::SaveIDE ()
{
	// SaveIDE - salva as configurações da IDE
	HKEY hKey;
	DWORD dwValue;
	RECT rRect;

	if (RegCreateKey (HKEY_CURRENT_USER, SIMNORMA_KEY, &hKey) == ERROR_SUCCESS)
	{
		// salva as opções da execução
		RegWriteString (hKey, "Out File", sOutFile);
		RegWriteDWORD (hKey, "Delay", dwDelay);
		RegWriteDWORD (hKey, "Use Delay", (bUseDelay ? 1 : 0));
		RegWriteDWORD (hKey, "Update Ctrls", (bUpdateControls ? 1 : 0));
		RegWriteDWORD (hKey, "Update Regs", (bUpdateRegs ? 1 : 0));
		RegWriteDWORD (hKey, "Print Comp", (bPrintComp ? 1 : 0));
		RegWriteDWORD (hKey, "Save Comp", (bSaveComp ? 1 : 0));

		// barra de ferramentas
		dwValue = (bToolbarVisible ? 1 : 0);
		RegWriteDWORD (hKey, "Toolbar", dwValue);

		// barra de estados
		dwValue = (bStatusVisible ? 1 : 0);
		RegWriteDWORD (hKey, "Status", dwValue);

		// visibilidade da janela de macros
		dwValue = (bMacrosVisible ? 1 : 0);
		RegWriteDWORD (hKey, "Macros Visible", dwValue);

		// posição da janela de macro
		dlgMacros.GetWindowRect (&rRect);
		RegWriteDWORD (hKey, "Macros X", rRect.left);
		RegWriteDWORD (hKey, "Macros Y", rRect.top);

		// visibilidade da janela de registradores
		dwValue = (bRegsVisible ? 1 : 0);
		RegWriteDWORD (hKey, "Regs Visible", dwValue);

		// posição da janela de registradores
		dlgRegisters.GetWindowRect (&rRect);
		RegWriteDWORD (hKey, "Regs X", rRect.left);
		RegWriteDWORD (hKey, "Regs Y", rRect.top);

		// visibilidade da janela de saída
		dwValue = (bOutputVisible ? 1 : 0);
		RegWriteDWORD (hKey, "Output Visible", dwValue);

		// posição da janela de saída
		dlgOutput.GetWindowRect (&rRect);
		RegWriteDWORD (hKey, "Output X", rRect.left);
		RegWriteDWORD (hKey, "Output Y", rRect.top);

		// fecha a chave
		RegCloseKey (hKey);
	}
}

bool CMainFrame::CompileProject ()
{
	// CompileProject - compila o projeto atual
	CString sErrorFile;
	char *lpErrorData1, *lpErrorData2;
	bool bSelect = true;
	long nLine = 0;
	long nErrorIdx, nErrorParams = 0;

	PARSER pParser;
	char *lpData = m_wndMonite.GetData ();

	// abre o valor padrão para o nome do arquivo
	sErrorFile.LoadString (IDS_CURPROJ);

	// verifica se ocorreu erro ao alocar memória
	if (!lpData)
	{
		nErrorIdx = IDS_ERROR1;
		bSelect = false;
		goto error;
	}

	// inicia a análise sintática e semântica do Monitè
	pProgram.ClearMacros ();
	pProgram.Clear ();
	pParser.pProgram = &pProgram;
	pParser.sProgramPath = &sSimNormaPath;
	pParser.sFilePath = &sProjectFilePath;
	if (pParser.Parse (sProjectFileName.GetBuffer (sProjectFileName.GetLength ()), lpData))
	{
		// atualiza o buffer
		sProjectFileName.ReleaseBuffer ();

		// inicia a análise semântica do Monitè para Norma
		pNorma.pProgram = &pProgram;
		if (pNorma.CheckProgram ())
		{
			// compila as macros em um único código
			if (MonoCompiler (&pProgram))
			{
				// verifica se o programa resultante é vazio
				if (!pProgram.Count ())
				{
					nErrorIdx = IDS_ERROR17;
					bSelect = false;
					goto error;
				}

				// organiza o fluxograma
				CDC *pDC = m_wndFlowchart.GetDC ();
				STACK pStack;
				pDC->SelectObject (m_wndFlowchart.hItemsFont);
				pProgram.OrganizeFlowchart (pDC, sStart, sEnd);
				ReleaseDC (pDC);
				// lista os registradores
				LoadRegisters ();
				// atualiza as posições do fluxograma
				m_wndFlowchart.UpdatePos ();
				// atualiza as posições das instruções rotuladas
				m_wndInstructs.UpdatePos ();
			}
			else
			{
				nErrorIdx = IDS_ERROR1;
				bSelect = false;
				goto error;
			}
		}
		else
		{
			// ocorreu um erro, pega o índice do erro
			switch (pNorma.GetError ())
			{
			case netInvalidOperation:
				nErrorIdx = IDS_ERROR29;
				break;
			case netInvalidTest:
				nErrorIdx = IDS_ERROR30;
				break;
			case etInvalidRegister:
				nErrorIdx = IDS_ERROR31;
				break;
			}
			lpErrorData1 = pNorma.GetErrorData ();
			nErrorParams = 1;
			bSelect = false;
			goto error;
		}
	}
	else
	{
		// atualiza o buffer
		sProjectFileName.ReleaseBuffer ();

		// ocorreu um erro, pega o índice do erro
		switch (pParser.GetError ())
		{
		case etEnd:
			nErrorIdx = IDS_ERROR17;
			break;
		case etMemory:
			nErrorIdx = IDS_ERROR1;
			bSelect = false;
			break;
		case etLibNameExpected:
			nErrorIdx = IDS_ERROR3;
			break;
		case etLoadLibError:
			{
				nErrorIdx = IDS_ERROR4;
				lpErrorData1 = pParser.GetErrorSourcePos ();
				nErrorParams = 1;
				bSelect = false;
				break;
			}
		case etProgTypeExpected:
			nErrorIdx = IDS_ERROR5;
			break;
		case etMacroTypeExpected:
			nErrorIdx = IDS_ERROR6;
			break;
		case etMacroNameExpected:
			nErrorIdx = IDS_ERROR7;
			break;
		case etMacroParamsExpected:
			nErrorIdx = IDS_ERROR8;
			break;
		case etParenthesisExpected:
			nErrorIdx = IDS_ERROR9;
			break;
		case etTestNameExpected:
			nErrorIdx = IDS_ERROR10;
			break;
		case etEndMacroExpected:
			nErrorIdx = IDS_ERROR11;
			break;
		case etUndefinedMacro:
			{
				nErrorIdx = IDS_ERROR12;
				lpErrorData1 = pParser.GetErrorUndefData ();
				nErrorParams = 1;
				bSelect = false;
				break;
			}
		case etUndefinedMacroTest:
			{
				nErrorIdx = IDS_ERROR13;
				lpErrorData1 = pParser.GetErrorUndefData ();
				nErrorParams = 1;
				bSelect = false;
				break;
			}
		case etMacroCallParamsError:
			{
				nErrorIdx = IDS_ERROR14;
				lpErrorData1 = pParser.GetErrorUndefData ();
				nErrorParams = 1;
				bSelect = false;
				break;
			}
		case etMacroLoopError:
			{
				nErrorIdx = IDS_ERROR15;
				lpErrorData1 = pParser.GetErrorSourcePos ();
				lpErrorData2 = pParser.GetErrorUndefData ();
				nErrorParams = 2;
				bSelect = false;
				break;
			}
		case etLibLoopError:
			{
				nErrorIdx = IDS_ERROR16;
				lpErrorData1 = pParser.GetErrorLibName ();
				lpErrorData2 = pParser.GetErrorSourcePos ();
				nErrorParams = 2;
				bSelect = false;
				break;
			}
		case etIteractiveError:
			{
				switch (pParser.GetItrError ())
				{
				case ietEnd:
					nErrorIdx = IDS_ERROR17;
					break;
				case ietSyntax:
					nErrorIdx = IDS_ERROR18;
					break;
				case ietMemory:
					nErrorIdx = IDS_ERROR1;
					bSelect = false;
					break;
				case ietEndExpected:
					nErrorIdx = IDS_ERROR2;
					break;
				case ietEndMacroExpected:
					nErrorIdx = IDS_ERROR11;
					break;
				case ietParenthesisExpected:
					nErrorIdx = IDS_ERROR9;
					break;
				case ietThenExpected:
					nErrorIdx = IDS_ERROR19;
					break;
				case ietElseExpected:
					nErrorIdx = IDS_ERROR20;
					break;
				case ietDoExpected:
					nErrorIdx = IDS_ERROR21;
					break;
				}
				break;
			}
		case etMonoError:
			{
				switch (pParser.GetMonoError ())
				{
				case metEnd:
					nErrorIdx = IDS_ERROR17;
					break;
				case metMemory:
					nErrorIdx = IDS_ERROR1;
					bSelect = false;
					break;
				case metEnterExpected:
					nErrorIdx = IDS_ERROR22;
					break;
				case metLabelExpected:
					nErrorIdx = IDS_ERROR23;
					break;
				case metInstructionExpected:
					nErrorIdx = IDS_ERROR24;
					break;
				case metTestNameExpected:
					nErrorIdx = IDS_ERROR25;
					break;
				case metParenthesisExpected:
					nErrorIdx = IDS_ERROR9;
					break;
				case metOperationNameExpected:
					nErrorIdx = IDS_ERROR26;
					break;
				case metThenExpected:
					nErrorIdx = IDS_ERROR19;
					break;
				case metGotoExpected:
					nErrorIdx = IDS_ERROR27;
					break;
				case metLabelNameExpected:
					nErrorIdx = IDS_ERROR28;
					break;
				case metElseExpected:
					nErrorIdx = IDS_ERROR20;
					break;
				}
				break;
			}
		}
		if (pParser.GetErrorLibName ())
		{
			sErrorFile = pParser.GetErrorLibName ();
			bSelect = false;
		}
		if (bSelect)
			nLine = m_wndMonite.GetLineFromPosition (pParser.GetErrorSourcePos () - pParser.GetErrorSource ());
		goto error;
	}

	// limpa a memória
	free (lpData);

	// compilação feita
	return true;

error:
	// limpa a memória
	free (lpData);

	// erro de compilação
	CCompilerErrorDlg dlgError;
	CString sError;

	// atualiza a string do erro
	sError.LoadString (nErrorIdx);
	if (nErrorParams == 2)
	{
		char lpMsg[2048];
		sprintf (lpMsg, sError, lpErrorData1, lpErrorData2);
		sError = lpMsg;
	}
	else if (nErrorParams == 1)
	{
		char lpMsg[2048];
		sprintf (lpMsg, sError, lpErrorData1);
		sError = lpMsg;
	}

	// seleciona o erro
	if (bSelect)
		m_wndMonite.SelectLine (nLine);

	// exibe o diálogo de erro
	dlgError.sErrorFile = sErrorFile;
	dlgError.sErrorDescrip = sError;
	dlgError.DoModal ();
	return false;
}

void CMainFrame::LoadRegisters ()
{
	// LoadRegisters - exibe todos os registradores utilizados na lista de registradores
	CString sStr;
	char sChar[2] = {0, 0};
	int i, nCount = pNorma.GetCount (), nIdx;

	dlgRegisters.m_lstRegs.DeleteAllItems ();
	for (i = 0; i < nCount; i++)
	{
		// pega o nome do registrador
		if (i < 26)
		{
			sChar[0] = 'A' + i;
			sStr = sChar;
		}
		else
			sStr.Format ("%d", i);

		// insere o item
		nIdx = dlgRegisters.m_lstRegs.InsertItem (i, sStr);

		// insere o valor
		sStr.Format ("%d", pNorma[i]);
		dlgRegisters.m_lstRegs.SetItemText (nIdx, 1, sStr);
	}
}

void CMainFrame::UpdateRegisters ()
{
	// UpdateRegisters - atualiza o valor de todos os registradores
	CString sStr;
	int i, nCount = pNorma.GetCount ();

	for (i = 0; i < nCount; i++)
	{
		sStr.Format ("%d", pNorma[i]);
		dlgRegisters.m_lstRegs.SetItemText (i, 1, sStr);
	}
}

void CMainFrame::SetMode (EDITOR_MODE emMode)
{
	// SetMode - modifica o modo de edição

	// verifica se é necessária a mudança
	if (emCurrentMode == emMode)
		return;

	// verifica se é necessária uma compilação
	if ((emCurrentMode == emMonite) && bNeedCompile)
	{
		if (!CompileProject ())
			return;
		bNeedCompile = false;
	}

	// modifica o editor
	CMenu *pMenu;
	switch (emMode)
	{
	case emMonite:
		{
			// pára a execução
			SetRunMode (rmStop);

			// atualiza os menus
			GetMenu ()->EnableMenuItem (1, MF_ENABLED | MF_BYPOSITION);
			pMenu = GetMenu ()->GetSubMenu (2);
			pMenu->EnableMenuItem (ID_VIEW_MACROS, MF_ENABLED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_VIEW_REGISTERS, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_VIEW_OUTPUT, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu = GetMenu ()->GetSubMenu (3);
			pMenu->EnableMenuItem (ID_MODE_RUN, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_STEP, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_PAUSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_STOP, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu->CheckMenuItem (ID_MODE_MONITE, MF_CHECKED | MF_BYCOMMAND);
			pMenu->CheckMenuItem (ID_MODE_FLOWCHART, MF_UNCHECKED | MF_BYCOMMAND);
			pMenu->CheckMenuItem (ID_MODE_INSTRUCTS, MF_UNCHECKED | MF_BYCOMMAND);

			// atualiza a barra de ferramentas
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_RUN, FALSE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_STEP, FALSE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_PAUSE, FALSE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_STOP, FALSE);
			m_wndToolBar.GetToolBarCtrl ().CheckButton (ID_MODE_MONITE, TRUE);
			m_wndToolBar.GetToolBarCtrl ().CheckButton (ID_MODE_FLOWCHART, FALSE);
			m_wndToolBar.GetToolBarCtrl ().CheckButton (ID_MODE_INSTRUCTS, FALSE);

			// atualiza as janelas auxiliares
			dlgMacros.ShowWindow (bMacrosVisible ? SW_SHOW : SW_HIDE);
			dlgRegisters.ShowWindow (SW_HIDE);
			dlgOutput.ShowWindow (SW_HIDE);

			// reabre as macros
			m_wndMonite.ReloadMacros ();

			// atualiza o editor ativo
			m_wndFlowchart.ShowWindow (SW_HIDE);
			m_wndInstructs.ShowWindow (SW_HIDE);
			m_wndMonite.ShowWindow (SW_SHOW);

			// dá o foco para o editor
			m_wndMonite.SetFocus ();

			break;
		}
		
	case emFlowchart:
	case emInstructs:
		{
			// atualiza os menus
			GetMenu ()->EnableMenuItem (1, MF_ENABLED | MF_BYPOSITION);
			pMenu = GetMenu ()->GetSubMenu (2);
			pMenu->EnableMenuItem (ID_VIEW_MACROS, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_VIEW_REGISTERS, MF_ENABLED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_VIEW_OUTPUT, MF_ENABLED | MF_BYCOMMAND);
			pMenu = GetMenu ()->GetSubMenu (3);
			pMenu->CheckMenuItem (ID_MODE_MONITE, MF_UNCHECKED | MF_BYCOMMAND);
			pMenu->CheckMenuItem (ID_MODE_FLOWCHART, ((emMode == emFlowchart) ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
			pMenu->CheckMenuItem (ID_MODE_INSTRUCTS, ((emMode == emInstructs) ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
			GetMenu ()->EnableMenuItem (1, MF_DISABLED | MF_GRAYED | MF_BYPOSITION);

			// atualiza a barra de ferramentas
			m_wndToolBar.GetToolBarCtrl ().CheckButton (ID_MODE_MONITE, FALSE);
			m_wndToolBar.GetToolBarCtrl ().CheckButton (ID_MODE_FLOWCHART, ((emMode == emFlowchart) ? TRUE : FALSE));
			m_wndToolBar.GetToolBarCtrl ().CheckButton (ID_MODE_INSTRUCTS, ((emMode == emInstructs) ? TRUE : FALSE));

			// atualiza a execução
			if (bIsRunning)
				SetRunMode (rmRunMode);
			else
				SetRunMode (rmStop);

			// atualiza as janelas auxiliares
			dlgMacros.ShowWindow (SW_HIDE);
			dlgRegisters.ShowWindow (bRegsVisible ? SW_SHOW : SW_HIDE);
			dlgOutput.ShowWindow (bOutputVisible ? SW_SHOW : SW_HIDE);

			// atualiza o editor ativo
			m_wndMonite.ShowWindow (SW_HIDE);
			m_wndFlowchart.ShowWindow (((emMode == emFlowchart) ? SW_SHOW : SW_HIDE));
			m_wndInstructs.ShowWindow (((emMode == emInstructs) ? SW_SHOW : SW_HIDE));

			// dá o foco para o editor
			if (emMode == emFlowchart)
				m_wndFlowchart.SetFocus ();
			else if (emMode == emInstructs)
				m_wndInstructs.SetFocus ();

			break;
		}

	}

	// atualiza o modo atual
	emCurrentMode = emMode;
}

void CMainFrame::SetRunMode (RUN_MODE rmNewRunMode)
{
	// SetRunMode - muda o modo de execução atual
	CMenu *pMenu = GetMenu ()->GetSubMenu (3);

	// atualiza a flag de execução e o título
	bIsRunning = (rmNewRunMode != rmStop);
	UpdateTitle ();

	// atualiza a IDE
	switch (rmNewRunMode)
	{
	case rmPlay:
	case rmPlayStep:
		{
			// atualiza o menu
			pMenu->EnableMenuItem (ID_MODE_RUN, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_STEP, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_PAUSE, MF_ENABLED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_STOP, MF_ENABLED | MF_BYCOMMAND);

			// atualiza a barra de ferramentas
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_RUN, FALSE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_STEP, FALSE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_PAUSE, TRUE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_STOP, TRUE);

			break;
		}

	case rmPause:
		{
			// atualiza o menu
			pMenu->EnableMenuItem (ID_MODE_RUN, MF_ENABLED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_STEP, MF_ENABLED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_PAUSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_STOP, MF_ENABLED | MF_BYCOMMAND);

			// atualiza a barra de ferramentas
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_RUN, TRUE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_STEP, TRUE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_PAUSE, FALSE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_STOP, TRUE);

			break;
		}

	case rmStop:
		{
			// atualiza o menu
			pMenu->EnableMenuItem (ID_MODE_RUN, MF_ENABLED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_STEP, MF_ENABLED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_PAUSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
			pMenu->EnableMenuItem (ID_MODE_STOP, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);

			// atualiza a barra de ferramentas
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_RUN, TRUE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_STEP, TRUE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_PAUSE, FALSE);
			m_wndToolBar.GetToolBarCtrl ().EnableButton (ID_MODE_STOP, FALSE);

			// atualiza o flag de execução
			pMenu->EnableMenuItem (ID_VIEW_OUTPUT, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);

			break;
		}

	}

	// atualiza o modo atual
	rmRunMode = rmNewRunMode;
}

bool CMainFrame::SaveProject (CString sFileName)
{
	// SaveProject - salva o projeto atual
	CString sActualFileName = sProjectFileName;

	// atualiza o nome do arquivo
	if (sFileName.IsEmpty ())
	{
		CFileDialog dlgSave (FALSE, "smn", sProjectFileName.GetBuffer (sProjectFileName.GetLength ()), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "SimNorma (*.smn)|*.smn||", this);
		sProjectFileName.ReleaseBuffer ();
		if (dlgSave.DoModal () == IDOK)
			sFileName = dlgSave.GetPathName ();
		else
			return false;
	}

	// tenta salvar o arquivo
	sProjectFileName = sFileName;
	if (m_wndMonite.SaveToFile ())
	{
		sProjectFilePath = sProjectFileName;
		ExtractFilePath (sProjectFilePath);
		bModified = false;
		return true;
	}
	else
	{
		sProjectFileName = sActualFileName;
		return false;
	}
}

void CMainFrame::UpdateTitle ()
{
	// UpdateTitle - atualiza o título da janela
	CString sTitle;

	if (sProjectFileName.IsEmpty ())
		sTitle.LoadString (IDS_UNTITLED);
	else
		sTitle = sProjectFileName;

	if (bIsRunning)
		sTitle = "SimNorma - Em Execução - [" + sTitle;
	else
		sTitle = "SimNorma - [" + sTitle;

	if (bModified)
		sTitle += "*]";
	else
		sTitle += "]";
	SetWindowText (sTitle);
}

void CMainFrame::UpdateMacros ()
{
	// UpdateMacros - atualiza a lista das macros disponíveis
	long i, nCount = pMacros.MacrosCount ();
	dlgMacros.m_lstMacros.ResetContent ();

	for (i = 0; i < nCount; i++)
		dlgMacros.m_lstMacros.AddString (pMacros.GetMacro (i)->GetName ());
}

void CMainFrame::PrintOutput (LPCSTR lpData, bool bUpdateWindow)
{
	// PrintOutput - imprime alguma string na janela de saída

	// imprime na janela
	if (bUpdateWindow)
		dlgOutput.m_lstOutput.SetCurSel (dlgOutput.m_lstOutput.AddString (lpData));

	// imprime no arquivo
	if (hOutFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwLen = strlen (lpData), dwWritten;
		if (dwLen)
		{
			char sNewLine[2] = {'\r', '\n'};
			WriteFile (hOutFile, lpData, dwLen * sizeof(char), &dwWritten, NULL);
			WriteFile (hOutFile, sNewLine, 2 * sizeof(char), &dwWritten, NULL);
		}
	}
}

void CMainFrame::PrintComp (long nIdx)
{
	// PrintComp - imprime na tela ou no arquivo um item da computação
	CString sStr, sComp;
	long i, nRegsCount = pNorma.GetCount ();

	sComp.Format ("(%d, (", nIdx);
	if (nRegsCount)
	{
		for (i = 0; i < nRegsCount - 1; i++)
		{
			sStr.Format ("%d, ", pNorma[i]);
			sComp += sStr;
		}
		sStr.Format ("%d", pNorma[nRegsCount - 1]);
		sComp += sStr;
	}
	sComp += "))";
	PrintOutput (sComp, bPrintComp);
}

void CMainFrame::StartRunLoop ()
{
	// StartRunLoop - incia o loop de execução
	MSG msg;
	CUR_STEP pCurStep = pProgram[0];
	DWORD dwStart, dwSteps = 0;
	CString sStr;

	// cria o arquivo de saída
	if (bSaveComp)
		hOutFile = CreateFile (sOutFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// atualiza a janela de saída
	dlgOutput.m_lstOutput.ResetContent ();

	// atualiza o fluxograma
	m_wndFlowchart.SetMode (true);
	if (bUpdateControls)
		m_wndFlowchart.SelectItem (&pProgram.fiStart);

	while (rmRunMode != rmStop)
	{
		if (rmRunMode == rmPlayStep)
			SetRunMode (rmPause);

		// atualiza os registradores
		if (bUpdateRegs)
			UpdateRegisters	();

		// atualiza os controles
		if (bUpdateControls)
		{
			// atualiza o fluxograma
			if (!pCurStep)
				m_wndFlowchart.SelectItem (&pProgram.fiEnd);
			else
				m_wndFlowchart.SelectItem (&pCurStep->fiFlowData);

			// atualiza as instruções rotuladas
			m_wndInstructs.SelectItem (pCurStep);
		}

		// imprime a computação
		if (bPrintComp || bSaveComp)
			PrintComp (pCurStep->nIdx + 1);

		do
		{
			// processa todas as mensagem da pilha
			while (PeekMessage (&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage (&msg);
				DispatchMessage (&msg);
				if (rmRunMode == rmStop)
				{
					UpdateRegisters ();
					m_wndFlowchart.SetMode (false);
					m_wndInstructs.SelectItem (NULL);

					if (bPrintComp || bSaveComp)
						PrintComp (0);
					sStr.Format ("Número de passos: %d", dwSteps);
					PrintOutput (sStr);

					if (hOutFile != INVALID_HANDLE_VALUE)
					{
						CloseHandle (hOutFile);
						hOutFile = INVALID_HANDLE_VALUE;
					}
					return;
				}
			}
		}
		while (rmRunMode == rmPause);

		// executa a instrução atual
		pCurStep = pNorma.Step (m_hWnd, pCurStep);
		dwSteps++;
		
		if (!pCurStep)
		{
			// atualiza os registradores
			UpdateRegisters ();
			m_wndFlowchart.SelectItem (&pProgram.fiEnd);
			m_wndFlowchart.SetMode (false);
			m_wndInstructs.SelectItem (NULL);
			SetRunMode (rmStop);

			if (bPrintComp || bSaveComp)
				PrintComp (0);
			sStr.Format ("Número de passos: %d", dwSteps);
			PrintOutput (sStr);

			if (hOutFile != INVALID_HANDLE_VALUE)
			{
				CloseHandle (hOutFile);
				hOutFile = INVALID_HANDLE_VALUE;
			}
			return;
		}

		// espera um tempo de delay
		if (bUseDelay && (rmRunMode == rmPlay))
		{
			dwStart = GetTickCount ();
			while (GetTickCount () - dwStart < dwDelay)
			{
				do
				{
					// processa todas as mensagem da pilha
					while (PeekMessage (&msg, 0, 0, 0, PM_REMOVE))
					{
						TranslateMessage (&msg);
						DispatchMessage (&msg);
						if (rmRunMode == rmStop)
						{
							UpdateRegisters ();
							m_wndFlowchart.SetMode (false);
							m_wndInstructs.SelectItem (NULL);

							if (bPrintComp || bSaveComp)
								PrintComp (0);
							sStr.Format ("Número de passos: %d", dwSteps);
							PrintOutput (sStr);

							if (hOutFile != INVALID_HANDLE_VALUE)
							{
								CloseHandle (hOutFile);
								hOutFile = INVALID_HANDLE_VALUE;
							}
							return;
						}
					}
				}
				while (rmRunMode == rmPause);
			}
		}
	}
}

void CMainFrame::NewProject ()
{
	// NewProject - cria um novo projeto
	
	// verifica se o usuário modificou alguma coisa no editor que pode ser salvo
	if (m_wndMonite.GetModified ())
	{
		CString sMsg;
		sMsg.LoadString (IDS_MSG1);
		int nReturn = MessageBox (sMsg, NULL, MB_YESNOCANCEL | MB_ICONQUESTION);

		switch (nReturn)
		{
		case IDCANCEL:
			return;
		case IDYES:
			if (!SaveProject ())
				return;
		}
	}

	// pára a execução
	SetRunMode (rmStop);

	// limpa o conteúdo do editor
	m_wndMonite.ClearEditor ();

	// atualiza as variáveis internas
	sProjectFileName = "";
	sProjectFilePath = "";
	bModified = false;
	bNeedCompile = true;

	// atualiza o modo de edição
	SetMode (emMonite);

	// atualiza o título da janela
	UpdateTitle ();
	m_wndMonite.ReloadMacros ();
}

void CMainFrame::OpenProjectFile (CString sFileName)
{
	// OpenProjectFile - abre o projeto de um arquivo externo

	// pára a execução
	SetRunMode (rmStop);

	// abre o novo projeto
	CString sActualFileName = sProjectFileName;
	sProjectFileName = sFileName;
	if (!m_wndMonite.LoadFromFile ())
	{
		sProjectFileName = sActualFileName;
		return;
	}

	// atualiza as variáveis internas
	sProjectFilePath = sProjectFileName;
	ExtractFilePath (sProjectFilePath);
	bModified = false;
	bNeedCompile = true;

	// atualiza o modo de edição
	SetMode (emMonite);

	// atualiza o título da janela
	UpdateTitle ();

	// atualiza as macros
	m_wndMonite.ReloadMacros ();
}

void CMainFrame::OpenProject()
{
	// OpenProject - abre o projeto de um arquivo externo

	// verifica se o usuário modificou alguma coisa no editor que pode ser salvo
	if (m_wndMonite.GetModified ())
	{
		CString sMsg;
		sMsg.LoadString (IDS_MSG1);
		int nReturn = MessageBox (sMsg, NULL, MB_YESNOCANCEL | MB_ICONQUESTION);

		switch (nReturn)
		{
		case IDCANCEL:
			return;
		case IDYES:
			if (!SaveProject ())
				return;
		}
	}

	// exibe o diálogo de abertura de projeto
	CFileDialog dlgOpen (TRUE, "smn", sProjectFileName.GetBuffer (sProjectFileName.GetLength ()), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "SimNorma (*.smn)|*.smn||", this);
	sProjectFileName.ReleaseBuffer ();
	if (dlgOpen.DoModal () != IDOK)
		return;

	// abre o arquivo
	OpenProjectFile (dlgOpen.GetPathName ());
}

void CMainFrame::OnSaveProject ()
{
	// OnSaveProject - salva o projeto atual
	if (SaveProject (sProjectFileName))
		UpdateTitle ();
}

void CMainFrame::OnSaveProjectAs ()
{
	// OnSaveProjectAs - salva o projeto com um novo nome
	if (SaveProject ())
		UpdateTitle ();
}

void CMainFrame::OnUndo ()
{
	// OnUndo - desfaz a última ação
	m_wndMonite.Undo ();
}

void CMainFrame::OnRedo()
{
	// OnRedo - refaz a última ação desfeita
	m_wndMonite.Redo ();
}

void CMainFrame::OnCut()
{
	// OnCut - recorta o texto selecionado
	m_wndMonite.Cut ();
}

void CMainFrame::OnCopy()
{
	// OnCopy - copia o texto selecionado
	m_wndMonite.Copy ();
}

void CMainFrame::OnPaste()
{
	// OnPaste - cola o conteúdo da área de transferência
	m_wndMonite.Paste ();
}

void CMainFrame::OnDelete()
{
	// On Delete - limpa o texto selecionado
	m_wndMonite.DeleteSelection ();
}

void CMainFrame::OnSelectAll()
{
	// OnSelectAll - seleciona todo o texto do editor
	m_wndMonite.SelectAll ();
}

void CMainFrame::OnViewMacros()
{
	// OnViewMacros - mostra ou esconde a janela de macros
	bMacrosVisible = !bMacrosVisible;
	GetMenu ()->GetSubMenu (2)->CheckMenuItem (ID_VIEW_MACROS, (bMacrosVisible ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	if (bMacrosVisible)
		m_wndMonite.ReloadMacros ();
	if (emCurrentMode == emMonite)
		dlgMacros.ShowWindow (bMacrosVisible ? SW_SHOW : SW_HIDE);
}

void CMainFrame::OnRefresh()
{
	// OnRefresh - atualiza a lista das macros disponíveis
	if (emCurrentMode == emMonite)
		m_wndMonite.ReloadMacros ();
}

void CMainFrame::OnModeMonite()
{
	// OnModeMonite - muda para o modo de edição
	SetMode (emMonite);
}

void CMainFrame::OnModeFlowchart()
{
	// OnModeFlowchart - muda para o modo de fluxograma
	SetMode (emFlowchart);
}

void CMainFrame::OnModeInstructs()
{
	// OnModeInstructs - muda para o modo de instruções rotuladas
	SetMode (emInstructs);
}

void CMainFrame::OnRun()
{
	// OnRun - incia a execução
	bool bStartRun = !bIsRunning;
	SetRunMode (rmPlay);
	GetMenu ()->GetSubMenu (3)->EnableMenuItem (ID_VIEW_OUTPUT, MF_ENABLED | MF_BYCOMMAND);
	if (bStartRun)
		StartRunLoop ();
}

void CMainFrame::OnModeStep()
{
	// OnModeStep - incia a execução passo a passo
	bool bStartRun = !bIsRunning;
	SetRunMode (rmPlayStep);
	GetMenu ()->GetSubMenu (3)->EnableMenuItem (ID_VIEW_OUTPUT, MF_ENABLED | MF_BYCOMMAND);
	if (bStartRun)
		StartRunLoop ();
}

void CMainFrame::OnModePause()
{
	// OnModePause - pauseia a execução
	SetRunMode (rmPause);
}

void CMainFrame::OnModeStop()
{
	// OnModeStop - pára a execução
	SetRunMode (rmStop);
}

void CMainFrame::OnUpdateModeRun(CCmdUI *pCmdUI)
{
	pCmdUI->Enable ((emCurrentMode != emMonite) && ((rmRunMode == rmPause) || (rmRunMode == rmStop)));
}

void CMainFrame::OnUpdateModeStep(CCmdUI *pCmdUI)
{
	pCmdUI->Enable ((emCurrentMode != emMonite) && ((rmRunMode == rmPause) || (rmRunMode == rmStop)));
}

void CMainFrame::OnUpdateModePause(CCmdUI *pCmdUI)
{
	pCmdUI->Enable ((emCurrentMode != emMonite) && (rmRunMode == rmPlay));
}

void CMainFrame::OnUpdateModeStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable ((emCurrentMode != emMonite) && (rmRunMode != rmStop));
}

void CMainFrame::OnModeOptions()
{
	// OnModeOptions - exibe as opções da execução
	CRunOptionsDlg dlgRunOptions;
	dlgRunOptions.sOutFile = sOutFile;
	dlgRunOptions.dwDelay = dwDelay;
	dlgRunOptions.bUseDelay = bUseDelay;
	dlgRunOptions.bUpdateControls = bUpdateControls;
	dlgRunOptions.bUpdateRegs = bUpdateRegs;
	dlgRunOptions.bPrintComp = bPrintComp;
	dlgRunOptions.bSaveComp = bSaveComp;
	
	if (dlgRunOptions.DoModal () == IDOK)
	{
		sOutFile = dlgRunOptions.sOutFile;
		dwDelay = dlgRunOptions.dwDelay;
		bUseDelay = dlgRunOptions.bUseDelay;
		bUpdateControls = dlgRunOptions.bUpdateControls;
		bUpdateRegs = dlgRunOptions.bUpdateRegs;
		bPrintComp = dlgRunOptions.bPrintComp;
		bSaveComp = dlgRunOptions.bSaveComp;
	}
}

void CMainFrame::OnViewRegisters()
{
	// OnViewRegisters - mostra ou esconde a janela de registradores
	bRegsVisible = !bRegsVisible;
	GetMenu ()->GetSubMenu (2)->CheckMenuItem (ID_VIEW_REGISTERS, (bRegsVisible ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	if (emCurrentMode != emMonite)
		dlgRegisters.ShowWindow (bRegsVisible ? SW_SHOW : SW_HIDE);
}

void CMainFrame::OnViewOutput()
{
	// OnViewOutput - mostra ou esconde a janela de saída
	bOutputVisible = !bOutputVisible;
	GetMenu ()->GetSubMenu (2)->CheckMenuItem (ID_VIEW_OUTPUT, (bOutputVisible ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	if (emCurrentMode != emMonite)
		dlgOutput.ShowWindow (bOutputVisible ? SW_SHOW : SW_HIDE);
}

void CMainFrame::OnHelpTopics()
{
	// OnHelpTopics - exibe o arquivo de ajuda
	SHELLEXECUTEINFO execInfo;
	char lpFileName[MAX_PATH];
	char *lpFileNamePtr = lpFileName;
	int nLen = strlen (lpFileName);

	GetModuleFileName (AfxGetApp ()->m_hInstance, lpFileName, MAX_PATH);
	nLen = strlen (lpFileName);
	lpFileNamePtr += nLen;
	while ((*lpFileNamePtr != '\\') && (nLen >= 0))
	{
		lpFileNamePtr--;
		nLen--;
	}

	if (nLen < 0)
		return;
	lpFileName[nLen + 1] = 0;
	strcat (lpFileName, "SimNorma.chm");

	memset (&execInfo, 0, sizeof(SHELLEXECUTEINFO));
	execInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	execInfo.fMask = SEE_MASK_FLAG_NO_UI;
	execInfo.hwnd = 0;
	execInfo.lpVerb = "open";
	execInfo.lpFile = lpFileName;
	execInfo.lpParameters = NULL;
	execInfo.lpDirectory = NULL;
	execInfo.nShow = SW_SHOW;
	execInfo.hInstApp = 0;
	ShellExecuteEx (&execInfo);
}
