/********************************************************************
	DECLARAÇÃO DA JANELA PRINCIPAL DO SIMNORMA
	Criação:	30/07/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien
						 Leonardo Golob
********************************************************************/


#pragma once
#include "Program.h"
#include "Flowgram.h"
#include "MoniteCtrl.h"
#include "InstructionsCtrl.h"
#include "Norma.h"
#include "MacrosDlg.h"
#include "RegistersDlg.h"
#include "OutputDlg.h"


/********************************************************************
	CLASSE DA JANELA PRINCIPAL */

enum EDITOR_MODE {emMonite, emFlowchart, emInstructs};
enum RUN_MODE {rmPlay, rmPlayStep, rmPause, rmStop};

class CMainFrame : public CFrameWnd
{
private:
	CString sSimNormaPath;
	CString sProjectFileName;
	CString sProjectFilePath;
	PROGRAM pMacros, pProgram;
	SIMNORMA pNorma;
	CString sStart, sEnd;

	bool bToolbarVisible;
	bool bStatusVisible;
	bool bMacrosVisible, bRegsVisible, bOutputVisible;

	CMacrosDlg dlgMacros;
	CRegistersDlg dlgRegisters;
	COutputDlg dlgOutput;

	EDITOR_MODE emCurrentMode;
	bool bIsRunning;
	RUN_MODE rmRunMode;
	bool bModified, bNeedCompile;

	HANDLE hOutFile;
	CString sOutFile;
	DWORD dwDelay;
	bool bUseDelay, bUpdateControls, bUpdateRegs, bPrintComp, bSaveComp;

	void LoadIDE ();
	void SaveIDE ();

	bool CompileProject ();
	void LoadRegisters ();
	void UpdateRegisters ();
	void SetMode (EDITOR_MODE emMode);
	void SetRunMode (RUN_MODE rmNewRunMode);

	bool SaveProject (CString sFileName = "");
	void UpdateTitle ();
	void UpdateMacros ();
	void PrintOutput (LPCSTR lpData, bool bUpdateWindow = true);
	void PrintComp (long nIdx);
	void StartRunLoop ();

public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	CMoniteControl		m_wndMonite;
	CFlowgram			m_wndFlowchart;
	CInstructionsCtrl	m_wndInstructs;

public:
	void OpenProjectFile (CString sFileName);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void NewProject();
	afx_msg void OpenProject();
	afx_msg void OnSaveProject();
	afx_msg void OnSaveProjectAs();
	afx_msg void OnUndo();
	afx_msg void OnRedo();
	afx_msg void OnCut();
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	afx_msg void OnDelete();
	afx_msg void OnSelectAll();
	afx_msg void OnViewMacros();
	afx_msg void OnRefresh();
	afx_msg void OnModeMonite();
	afx_msg void OnModeFlowchart();
	afx_msg void OnModeInstructs();
	afx_msg void OnRun();
	afx_msg void OnModeStep();
	afx_msg void OnModePause();
	afx_msg void OnModeStop();
	afx_msg void OnUpdateModeRun(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModeStep(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModePause(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModeStop(CCmdUI *pCmdUI);
	afx_msg void OnModeOptions();
	afx_msg void OnViewRegisters();
	afx_msg void OnViewOutput();
	afx_msg void OnHelpTopics();
};