/********************************************************************
	DECLARAÇÃO DA CLASSE DE EDIÇÃO DE ARQUIVOS MONITÈ
	Criado em:		14/06/2003
	Copyright:		(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#pragma once


// inclui os itens necessários para editar um arquivo na linguagem Monitè
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <time.h>

#include "SciLexer.h"
#include "Scintilla.h"
#include "Platform.h"

#include "PropSet.h"
#include "Accessor.h"
#include "WindowAccessor.h"

#include "Program.h"
#include "stdafx.h"


#define WM_MONITEMSG		WM_USER + 4
#define WMM_RELOADMACROS	0


// declaração das constantes
const COLORREF cWhite = RGB (0xFF, 0xFF, 0xFF);
const char moniteKeywords[] = "se entao senao enquanto ate faca va_para";
const char moniteMacroDef[] = "importar programa iterativo monolitico macro teste fimmacro retornar";
const char moniteStartIndent[] = "macro";
const char moniteEndIndent[] = "fimmacro";
const char moniteStartBlock[] = "(";
const char moniteEndBlock[] = ")";


// tipo atual da identação
enum IndentationStatus
{
	isNone,		// no effect on indentation
	isBlockStart,	// indentation block begin such as "{" or VB "function"
	isBlockEnd,	// indentation end indicator such as "}" or VB "end"
	isKeyWordStart	// Keywords that cause indentation
};


struct StyleAndWords
{
	int styleNumber;
	CString words;
	bool IsEmpty() { return words.GetLength() == 0; }
	bool IsSingleChar() { return words.GetLength() == 1; }
};


/********************************************************************
	CLASSE MONITÈ EDITOR */

class CMoniteControl : public CWnd
{
// Funções e variáveis internas
private:
	StyleAndWords statementIndent;
	StyleAndWords statementEnd;
	StyleAndWords blockStart;
	StyleAndWords blockEnd;
	PropSet props;
	bool indentOpening, indentClosing;
	int statementLookback;
	int braceCount;

	SString functionDefinition;
	int startCalltipWord;

	void SetAStyle (int nStyle, COLORREF cForeColor, COLORREF cBackColor = cWhite, int nSize = -1, const char *sFontFace = NULL);

	CharacterRange GetSelection();
	void SetSelection (int anchor, int currentPos);

	int GetLineLength (int line);
	int GetCurrentLineNumber ();
	int GetLineIndentation (int line);
	int GetLineIndentPosition (int line);
	void SetLineIndentation (int line, int indent);
	bool RangeIsAllWhitespace (int start, int end);
	int IndentOfBlock (int line);
	unsigned int GetLinePartsInStyle (int line, int style1, int style2, SString sv[], int len);
	IndentationStatus GetIndentState (int line);

	void MaintainIndentation (char ch);
	void AutomaticIndentation (char ch);

	int GetCaretInLine ();
	void GetLine (char *text, int sizeText, int line = -1);
	void GetRange (int start, int end, char *text);

	bool GetCallTip (char *lpFunc);
	bool StartCallTip ();
	void ContinueCallTip ();

	bool IsMacroLine (int line);
	bool IsImportLine (int line);

public:
	CMoniteControl();

public:
	PROGRAM *pProgram;
	CString *sSimNormaPath;
	CString *sFileName;
	CString *sFilePath;
	bool needReloadMacros, firstLoadMacros;
	bool supportCallTips;

	CString sSearchStr;
	CString sReplaceStr;

	void CharAdded (char ch);
	bool ReloadMacros ();
	void UpdateCallTip (bool bGoLeft, bool bKeyUp);

	void ClearFlags ();
	void ClearEditor ();

	bool SaveToFile ();
	bool LoadFromFile ();
	bool GetModified ();

	bool CanUndo ();
	void Undo ();
	bool CanRedo ();
	void Redo ();

	void Cut ();
	void Copy ();
	bool CanPaste ();
	void Paste ();
	void DeleteSelection ();
	void SelectAll ();

	bool StartSearch (CString sSearch, bool bReplace = false);
	bool SearchNext (bool bReplace = false);
	bool SearchPrevious (bool bReplace = false);

	bool StartReplace (CString sSearch, CString sReplaceWith);
	bool ReplaceNext ();
	bool ReplacePrevious ();

	void SetSelText (CString sText);
	char *GetData ();

	long GetLineFromPosition (long nPosition);
	void SelectLine (long nLine);

public:
	virtual ~CMoniteControl();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:

public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};