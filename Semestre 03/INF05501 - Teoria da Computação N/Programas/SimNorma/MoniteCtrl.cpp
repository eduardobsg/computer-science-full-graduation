/********************************************************************
	DECLARAÇÃO DA CLASSE DE EDIÇÃO DE ARQUIVOS MONITÈ
	Criado em:		14/06/2003
	Copyright:		(c) 2003 Marcelo Bona Boff e Fernando Trebien
********************************************************************/


#include "stdafx.h"
#include "SimNorma.h"
#include "MoniteCtrl.h"
#include "Parser.h"
#include "Program.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IS_SEPARATOR(ch) \
	((ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\r') || (ch == '(') || (ch == ')'))


/********************************************************************
	CLASSE MONITÈ EDITOR */

CMoniteControl::CMoniteControl()
{
	braceCount = 0;
	statementLookback = 10;

	pProgram = NULL;
	sSimNormaPath = NULL;
	sFileName = NULL;
	sFilePath = NULL;
	supportCallTips = true;

	ClearFlags ();
}

CMoniteControl::~CMoniteControl()
{
}

BEGIN_MESSAGE_MAP(CMoniteControl, CWnd)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

void CMoniteControl::SetAStyle(int nStyle, COLORREF cForeColor, COLORREF cBackColor, int nSize, const char *sFontFace)
{
	// SetAStyle - modifica todos os atributos de um estilo
	SendMessage (SCI_STYLESETFORE, nStyle, cForeColor);
	SendMessage (SCI_STYLESETBACK, nStyle, cBackColor);
	if (nSize >= 1)
		SendMessage (SCI_STYLESETSIZE, nStyle, nSize);
	if (sFontFace) 
		SendMessage (SCI_STYLESETFONT, nStyle, (LPARAM)sFontFace);
}

BOOL CMoniteControl::PreCreateWindow (CREATESTRUCT& cs) 
{
	// PreCreateWindow - atualiza a classe do controle que está sendo criado
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.lpszClass = "Scintilla";
	cs.lpszName = "Editor";
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style = WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_CLIPCHILDREN | WS_VISIBLE;
	return TRUE;
}

int CMoniteControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// OnCreate - atualiza as propriedades padrão do controle
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	const COLORREF cMIKeywords = RGB (0, 0, 0x80);
	const COLORREF cMIMacroDef = RGB (0x80, 0, 0);
	const COLORREF cMIRegister = RGB (0x80, 0, 0x80);
	const COLORREF cMIComment = RGB (0, 0x80, 0);

	SendMessage (SCI_SETLEXER, SCLEX_MONITE);
	SendMessage (SCI_SETMARGINMASKN, 2, SC_MASK_FOLDERS);
	SendMessage (SCI_SETMARGINSENSITIVEN, 2, 1);
	SendMessage (SCI_SETINDENT, 8);
	SendMessage (SCI_SETTABWIDTH, 8);
	SendMessage (SCI_SETTABINDENTS, true);
	SendMessage (SCI_SETBACKSPACEUNINDENTS, true);
	SendMessage (SCI_SETCONTROLCHARSYMBOL, 32);

	SendMessage (SCI_CALLTIPSETBACK, GetSysColor (COLOR_INFOBK));
	SendMessage (SCI_CALLTIPSETFORE, GetSysColor (COLOR_INFOTEXT));
	SendMessage (SCI_CALLTIPSETFOREHLT, GetSysColor (26 /*COLOR_HOTLIGHT*/));

	SendMessage (SCI_SETKEYWORDS, 0, reinterpret_cast<LPARAM>(moniteKeywords));
	SendMessage (SCI_SETKEYWORDS, 1, reinterpret_cast<LPARAM>(moniteMacroDef));

	// atualiza o estilo padrão
	SetAStyle (STYLE_DEFAULT, RGB (0, 0, 0), cWhite, 10, "Tahoma");
	SendMessage (SCI_STYLECLEARALL);	// copia o estilo padrão para os outros

	SetAStyle (SCE_MI_KEYWORDS, cMIKeywords);
	SetAStyle (SCE_MI_MACRODEF, cMIMacroDef);
	SetAStyle (SCE_MI_REGISTER, cMIRegister);
	SetAStyle (SCE_MI_STRING, cMIComment);
	SetAStyle (SCE_MI_LABEL, cMIKeywords);
	SetAStyle (SCE_MI_COMMENT, cMIComment);

	SendMessage (SCI_STYLESETBOLD, SCE_MI_KEYWORDS, 1);
	SendMessage (SCI_STYLESETBOLD, SCE_MI_MACRODEF, 1);
	SendMessage (SCI_STYLESETBOLD, SCE_MI_PARENTHESIS, 1);

	// atualiza as variáveis
	statementIndent.words = moniteStartIndent;
	statementIndent.styleNumber = SCE_MI_MACRODEF;
	statementEnd.words = moniteEndIndent;
	statementEnd.styleNumber = SCE_MI_MACRODEF;
	blockStart.words = moniteStartBlock;
	blockStart.styleNumber = SCE_MI_DELIMITER;
	blockEnd.words = moniteEndBlock;
	blockEnd.styleNumber = SCE_MI_DELIMITER;

	return 0;
}

CharacterRange CMoniteControl::GetSelection()
{
	CharacterRange crange;
	crange.cpMin = SendMessage (SCI_GETSELECTIONSTART);
	crange.cpMax = SendMessage (SCI_GETSELECTIONEND);
	return crange;
}

void CMoniteControl::SetSelection (int anchor, int currentPos)
{
	SendMessage (SCI_SETSEL, anchor, currentPos);
}

void CMoniteControl::CharAdded (char ch)
{
	CharacterRange crange = GetSelection ();
	int selStart = crange.cpMin;
	int selEnd = crange.cpMax;

	if ((selEnd == selStart) && (selStart > 0))
	{
		int style = SendMessage (SCI_GETSTYLEAT, selStart - 1, 0);
		if (style != 1)
		{
			if (SendMessage (SCI_CALLTIPACTIVE))
			{
				if (ch == ')')
				{
					braceCount--;
					if (braceCount < 1)
						SendMessage (SCI_CALLTIPCANCEL);
					else
						StartCallTip ();
				}
				else if (ch == '(')
				{
					braceCount++;
					StartCallTip ();
				}
				else
				{
					ContinueCallTip ();
				}
			}
			else
			{
				if ((ch == '(') && supportCallTips)
				{
					braceCount = 1;
					StartCallTip ();
				}
				else
				{
					MaintainIndentation (ch);
					AutomaticIndentation (ch);
				}
			}
		}
	}
}

bool CMoniteControl::ReloadMacros ()
{
	char *textbuf = (char*) malloc ((SendMessage (SCI_GETLENGTH) + 1) * sizeof(char));
	if (!textbuf)
		return false;
	SendMessage (SCI_GETTEXT, SendMessage (SCI_GETLENGTH), (LPARAM) textbuf);

	PARSER pParser;
	pParser.pProgram = pProgram;
	pParser.sProgramPath = sSimNormaPath;
	pParser.sFilePath = sFilePath;
	firstLoadMacros = !pParser.Parse (sFileName->GetBuffer (sFileName->GetLength ()), textbuf, true, firstLoadMacros);
	sFileName->ReleaseBuffer ();

	if (firstLoadMacros)
		needReloadMacros = true;
	free (textbuf);

	GetParent ()->SendMessage (WM_MONITEMSG, WMM_RELOADMACROS);

	return true;
}

void CMoniteControl::UpdateCallTip (bool bGoLeft, bool bKeyUp)
{
	CharacterRange crange = GetSelection ();
	int selStart = crange.cpMin;

	if (SendMessage (SCI_CALLTIPACTIVE))
	{
		char ch_next = SendMessage (SCI_GETCHARAT, selStart + (bKeyUp ? -1 : 0));
		char ch_prev = SendMessage (SCI_GETCHARAT, selStart - (bKeyUp ? 0 : 1));

		if (((ch_next == ')') && !bGoLeft) || ((ch_prev == '(') && bGoLeft))
			SendMessage (SCI_CALLTIPCANCEL);
		else
			ContinueCallTip ();
	}
}


/********************************************************************
	FUNÇÕES RELACIONADAS COM A INDENTAÇÃO */

int CMoniteControl::GetLineLength (int line)
{
	return SendMessage (SCI_GETLINEENDPOSITION, line) - SendMessage (SCI_POSITIONFROMLINE, line);
}

int CMoniteControl::GetCurrentLineNumber ()
{
	return SendMessage (SCI_LINEFROMPOSITION, SendMessage (SCI_GETCURRENTPOS));
}

int CMoniteControl::GetLineIndentation (int line)
{
	return SendMessage (SCI_GETLINEINDENTATION, line);
}

int CMoniteControl::GetLineIndentPosition (int line)
{
	return SendMessage (SCI_GETLINEINDENTPOSITION, line);
}

void CMoniteControl::SetLineIndentation (int line, int indent)
{
	if (indent < 0)
		return;
	CharacterRange crange = GetSelection ();
	int posBefore = GetLineIndentPosition (line);

	SendMessage (SCI_SETLINEINDENTATION, line, indent);
	int posAfter = GetLineIndentPosition (line);
	int posDifference = posAfter - posBefore;

	if (posAfter > posBefore)
	{
		// Move selection on
		if (crange.cpMin >= posBefore)
			crange.cpMin += posDifference;
		if (crange.cpMax >= posBefore)
			crange.cpMax += posDifference;
	}
	else if (posAfter < posBefore)
	{
		// Move selection back
		if (crange.cpMin >= posAfter)
		{
			if (crange.cpMin >= posBefore)
				crange.cpMin += posDifference;
			else
				crange.cpMin = posAfter;
		}
		if (crange.cpMax >= posAfter)
		{
			if (crange.cpMax >= posBefore)
				crange.cpMax += posDifference;
			else
				crange.cpMax = posAfter;
		}
	}

	SetSelection (crange.cpMin, crange.cpMax);
}

bool CMoniteControl::RangeIsAllWhitespace (int start, int end)
{
	WindowAccessor acc (this->m_hWnd, props);
	for (int i = start; i < end; i++) {
		if ((acc[i] != ' ') && (acc[i] != '\t'))
			return false;
	}
	return true;
}

int CMoniteControl::IndentOfBlock (int line)
{
	if (line < 0)
		return 0;
	int indentSize = SendMessage (SCI_GETINDENT);
	int indentBlock = GetLineIndentation (line);
	int backLine = line;
	IndentationStatus indentState = isNone;
	if (statementIndent.IsEmpty() && blockStart.IsEmpty() && blockEnd.IsEmpty())
		indentState = isBlockStart;	// Don't bother searching backwards

	int lineLimit = line - statementLookback;
	if (lineLimit < 0)
		lineLimit = 0;
	while ((backLine >= lineLimit) && (indentState == 0)) {
		indentState = GetIndentState (backLine);
		if (indentState != 0) {
			indentBlock = GetLineIndentation(backLine);
			if (indentState == isBlockStart) {
				if (!indentOpening)
					indentBlock += indentSize;
			}
			if (indentState == isBlockEnd) {
				if (indentClosing)
					indentBlock -= indentSize;
				if (indentBlock < 0)
					indentBlock = 0;
			}
			if ((indentState == isKeyWordStart) && (backLine == line))
				indentBlock += indentSize;
		}
		backLine--;
	}
	return indentBlock;
}

unsigned int CMoniteControl::GetLinePartsInStyle (int line, int style1, int style2, SString sv[], int len)
{
	for (int i = 0; i < len; i++)
		sv[i] = "";
	WindowAccessor acc (this->m_hWnd, props);
	SString s;
	int part = 0;
	int thisLineStart = SendMessage (SCI_POSITIONFROMLINE, line);
	int nextLineStart = SendMessage (SCI_POSITIONFROMLINE, line + 1);

	for (int pos = thisLineStart; pos < nextLineStart; pos++)
	{
		if (((acc.StyleAt(pos) == style1) || (acc.StyleAt(pos) == style2)) &&
			!IS_SEPARATOR (acc[pos]))
		{
			char c[2];
			c[0] = acc[pos];
			c[1] = '\0';
			s += c;
		}
		else if (s.length() > 0)
		{
			if (part < len)
				sv[part++] = s;
			s = "";
		}
	}
	if ((s.length() > 0) && (part < len))
		sv[part++] = s;
	return part;
}

static bool includes (const StyleAndWords &symbols, const SString value)
{
	if (symbols.words.GetLength() == 0)
		return false;
	else if (IsAlphabetic (symbols.words[0]))
	{
		// Set of symbols separated by spaces
		size_t lenVal = value.length();
		const char* symbol = symbols.words;

		while (symbol)
		{
			const char *symbolEnd = strchr(symbol, ' ');
			size_t lenSymbol = strlen(symbol);
			if (symbolEnd)
				lenSymbol = symbolEnd - symbol;
			if (lenSymbol == lenVal)
			{
				if (strncmp(symbol, value.c_str(), lenSymbol) == 0)
					return true;
			}
			symbol = symbolEnd;
			if (symbol)
				symbol++;
		}
	}
	else
	{
		// Set of individual characters. Only one character allowed for now
		char ch = symbols.words[0];
		return strchr(value.c_str(), ch) != 0;
	}
	return false;
}

#define ELEMENTS(a)	(sizeof(a) / sizeof(a[0]))

IndentationStatus CMoniteControl::GetIndentState (int line)
{
	// C like language indentation defined by braces and keywords
	IndentationStatus indentState = isNone;
	SString controlWords[20];
	unsigned int parts = GetLinePartsInStyle (line, statementIndent.styleNumber, -1, controlWords, ELEMENTS(controlWords));
	for (unsigned int i = 0; i < parts; i++)
	{
		if (includes (statementIndent, controlWords[i]))
			indentState = isKeyWordStart;
	}
	// Braces override keywords
	SString controlStrings[20];
	parts = GetLinePartsInStyle (line, blockEnd.styleNumber, -1, controlStrings, ELEMENTS(controlStrings));
	for (unsigned int j = 0; j < parts; j++)
	{
		if (includes(blockEnd, controlStrings[j]))
			indentState = isBlockEnd;
		if (includes(blockStart, controlStrings[j]))
			indentState = isBlockStart;
	}
	return indentState;
}

void CMoniteControl::MaintainIndentation (char ch)
{
	int eolMode = SendMessage (SCI_GETEOLMODE);
	int curLine = GetCurrentLineNumber ();
	int lastLine = curLine - 1;
	int indentAmount = 0;

	if (((eolMode == SC_EOL_CRLF || eolMode == SC_EOL_LF) && ch == '\n') ||
	        (eolMode == SC_EOL_CR && ch == '\r'))
	{
		while (lastLine >= 0 && GetLineLength (lastLine) == 0)
			lastLine--;
		if (lastLine >= 0)
			indentAmount = GetLineIndentation (lastLine);
		if (indentAmount > 0)
			SetLineIndentation (curLine, indentAmount);
	}
}

void CMoniteControl::AutomaticIndentation (char ch)
{
	CharacterRange crange = GetSelection ();
	int selStart = crange.cpMin;
	int curLine = GetCurrentLineNumber ();
	int thisLineStart = SendMessage (SCI_POSITIONFROMLINE, curLine);
	int indentSize = SendMessage (SCI_GETINDENT);
	int indentBlock = IndentOfBlock (curLine - 1);

	if (blockEnd.IsSingleChar() && ch == blockEnd.words[0])
	{
		if (!indentClosing)
		{
			if (RangeIsAllWhitespace(thisLineStart, selStart - 1)) {
				SetLineIndentation(curLine, indentBlock - indentSize);
			}
		}
	}
	else if (!blockEnd.IsSingleChar() && (ch == ' '))
	{
		if (!indentClosing && (GetIndentState(curLine) == isBlockEnd)) {}
	}
	else if (ch == blockStart.words[0])
	{
		if (!indentOpening && (GetIndentState(curLine - 1) == isKeyWordStart))
		{
			if (RangeIsAllWhitespace (thisLineStart, selStart - 1))
				SetLineIndentation(curLine, indentBlock - indentSize);
		}
	}
	else if ((ch == '\r' || ch == '\n') && (selStart == thisLineStart))
	{
		if (!indentClosing && !blockEnd.IsSingleChar())
		{
			SString controlWords[1];
			if (GetLinePartsInStyle (curLine - 1, blockEnd.styleNumber, -1, controlWords, ELEMENTS(controlWords)))
			{
				if (includes(blockEnd, controlWords[0]))
				{
					// Check if first keyword on line is an ender
					SetLineIndentation (curLine - 1, IndentOfBlock (curLine - 2) - indentSize);
					// Recalculate as may have changed previous line
					indentBlock = IndentOfBlock (curLine - 1);
				}
			}
		}
		SetLineIndentation (curLine, indentBlock);
	}
}


/********************************************************************
	FUNÇÕES RELACIONADAS COM AS CALLTIPS */

int CMoniteControl::GetCaretInLine ()
{
	int caret = SendMessage (SCI_GETCURRENTPOS);
	int line = SendMessage (SCI_LINEFROMPOSITION, caret);
	int lineStart = SendMessage (SCI_POSITIONFROMLINE, line);
	return caret - lineStart;
}

void CMoniteControl::GetLine (char *text, int sizeText, int line)
{
	if (line < 0)
		line = GetCurrentLineNumber ();
	int lineStart = SendMessage (SCI_POSITIONFROMLINE, line);
	int lineEnd = SendMessage (SCI_GETLINEENDPOSITION, line);
	int lineMax = lineStart + sizeText - 1;
	if (lineEnd > lineMax)
		lineEnd = lineMax;
	GetRange (lineStart, lineEnd, text);
	text[lineEnd - lineStart] = '\0';
}

void CMoniteControl::GetRange (int start, int end, char *text)
{
	TextRange tr;
	tr.chrg.cpMin = start;
	tr.chrg.cpMax = end;
	tr.lpstrText = text;
	SendMessage (SCI_GETTEXTRANGE, 0, (LPARAM) &tr);
}

bool CMoniteControl::GetCallTip (char *lpFunc)
{
	if (!pProgram)
		return false;

	MACRO *pCurMacro = pProgram->GetMacro (lpFunc);
	if (!pCurMacro)
		return false;

	functionDefinition = pCurMacro->GetName ();
	functionDefinition += " (";

	long nParamsCount = pCurMacro->ParamsCount ();
	for (long i = 0; i < nParamsCount; i++)
	{
		functionDefinition += pCurMacro->GetParamName (i);
		if (i < (nParamsCount - 1))
			functionDefinition += ", ";
	}

	functionDefinition += ")";
	return true;
}

bool CMoniteControl::StartCallTip ()
{
	if (!pProgram || !sFileName)
		return true;

	char linebuf[1000];
	GetLine (linebuf, sizeof(linebuf));

	int current = GetCaretInLine ();
	int pos = SendMessage (SCI_GETCURRENTPOS);

	char *plinebuf = linebuf;
	while (isspace (*plinebuf))
		plinebuf++;
	if (_strnicmp (plinebuf, "macro", 5) == 0)
		return false;

	int braces = 0;
	while (current > 0 && (braces || linebuf[current - 1] != '('))
	{
		if (linebuf[current - 1] == '(')
			braces--;
		else if (linebuf[current - 1] == ')')
			braces++;
		current--;
		pos--;
	}
	if (current > 0)
	{
		current--;
		pos--;
		while (current > 0 && isspace(linebuf[current - 1]))
		{
			current--;
			pos--;
		}
	}
	if (current <= 0)
		return true;

	startCalltipWord = current - 1;
	while (startCalltipWord > 0 && !isspace(linebuf[startCalltipWord - 1]))
		startCalltipWord--;

	if (needReloadMacros)
	{
		needReloadMacros = false;
		if (!ReloadMacros ())
			return false;
	}

	linebuf[current] = '\0';
	int rootlen = current - startCalltipWord;
	if (GetCallTip (linebuf + startCalltipWord))
	{
		SendMessage (SCI_CALLTIPSHOW, pos - rootlen, (LPARAM) functionDefinition.c_str());
		ContinueCallTip();
	}

	return true;
}

static bool IsCallTipSeparator(char ch) {
	return (ch == ',');
}

void CMoniteControl::ContinueCallTip ()
{
	char linebuf[1000];
	GetLine (linebuf, sizeof(linebuf));
	int current = GetCaretInLine();

	int braces = 0;
	int commas = 0;
	for (int i = startCalltipWord; i < current; i++)
	{
		if (linebuf[i] == '(')
			braces++;
		else if (linebuf[i] == ')' && braces > 0)
			braces--;
		else if (braces == 1 && IsCallTipSeparator (linebuf[i]))
			commas++;
	}

	int startHighlight = 0;
	while (functionDefinition[startHighlight] && functionDefinition[startHighlight] != '(')
		startHighlight++;
	if (functionDefinition[startHighlight] == '(')
		startHighlight++;
	while (functionDefinition[startHighlight] && commas > 0)
	{
		if (IsCallTipSeparator (functionDefinition[startHighlight]) || functionDefinition[startHighlight] == ')')
			commas--;
		startHighlight++;
	}
	if (IsCallTipSeparator (functionDefinition[startHighlight]) || functionDefinition[startHighlight] == ')')
		startHighlight++;
	int endHighlight = startHighlight;
	if (functionDefinition[endHighlight])
		endHighlight++;
	while (functionDefinition[endHighlight] && !IsCallTipSeparator(functionDefinition[endHighlight]) && functionDefinition[endHighlight] != ')')
		endHighlight++;

	SendMessage (SCI_CALLTIPSETHLT, startHighlight, endHighlight);
}

bool CMoniteControl::IsMacroLine (int line)
{
	char linebuf[1000];
	GetLine (linebuf, sizeof(linebuf));

	char *plinebuf = linebuf;
	while (isspace (*plinebuf))
		plinebuf++;

	return (_strnicmp (plinebuf, "macro", 5) == 0);
}

bool CMoniteControl::IsImportLine (int line)
{
	char linebuf[1000];
	GetLine (linebuf, sizeof(linebuf));

	char *plinebuf = linebuf;
	while (isspace (*plinebuf))
		plinebuf++;

	return (_strnicmp (plinebuf, "importar", 8) == 0);
}

void CMoniteControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int line = GetCurrentLineNumber ();
	if (!needReloadMacros)
		needReloadMacros = IsMacroLine (line) || IsImportLine (line);
	if (!firstLoadMacros)
		firstLoadMacros = IsImportLine (line);

	if ((nChar == VK_LEFT) || (nChar == VK_RIGHT) || (nChar == VK_BACK) || (nChar == VK_DELETE))
		UpdateCallTip (nChar != VK_RIGHT, false);

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMoniteControl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int line = GetCurrentLineNumber ();
	if (!needReloadMacros)
		needReloadMacros = IsMacroLine (line) || IsImportLine (line);
	if (!firstLoadMacros)
		firstLoadMacros = IsImportLine (line);

	if ((nChar == VK_LEFT) || (nChar == VK_RIGHT) || (nChar == VK_BACK) || (nChar == VK_DELETE))
		UpdateCallTip (nChar != VK_RIGHT, true);

	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}


/********************************************************************
	FUNÇÕES DE ENTRADA E SAÍDA DO CONTROLE */

void CMoniteControl::ClearFlags ()
{
	// ClearFlags - limpa as flags do editor
	indentOpening = true;
	indentClosing = true;
	needReloadMacros = true;
	firstLoadMacros = true;
	sSearchStr = "";
	sReplaceStr = "";
}

void CMoniteControl::ClearEditor ()
{
	// ClearEditor - limpa o editor por completo
	SendMessage (SCI_SETTEXT, 0, (LPARAM) "");
	SendMessage (SCI_SETSAVEPOINT);
	SendMessage (SCI_EMPTYUNDOBUFFER);
	SendMessage (SCI_CALLTIPCANCEL);
	ClearFlags ();
}

bool CMoniteControl::SaveToFile ()
{
	// SaveToFile - salva o conteúdo atual do editor em um arquivo
	if (sFileName->IsEmpty ())
		return false;

	// aloca espaço para o texto do controle
	long nLength = SendMessage (SCI_GETLENGTH);
	char *lpText = (char*) malloc ((nLength + 1) * sizeof(char));
	if (!lpText)
		return false;
	SendMessage (SCI_GETTEXT, nLength + 1, (LPARAM) lpText);

	// cria um novo arquivo
	HANDLE hFile = CreateFile (*sFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		free (lpText);
		return false;
	}

	// tenta escrever sobre o arquivo
	DWORD dwWritten;
	WriteFile (hFile, lpText, nLength * sizeof(char), &dwWritten, NULL);
	CloseHandle (hFile);

	// atualiza o flag de modificado
	SendMessage (SCI_SETSAVEPOINT);
	SendMessage (SCI_EMPTYUNDOBUFFER);

	// arquivo salvo com sucesso
	free (lpText);
	return true;
}

bool CMoniteControl::LoadFromFile ()
{
	// LoadFromFile - abre o conteúdo do editor de um arquivo
	if (sFileName->IsEmpty ())
		return false;

	// tenta abrir o arquivo
	HANDLE hFile = CreateFile (*sFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// aloca espaço para abrir o arquivo
	DWORD dwRead;
	long nLength = GetFileSize (hFile, NULL);
	char *lpText = (char*) malloc (nLength + sizeof(char));
	if (!lpText)
	{
		CloseHandle (hFile);
		return false;
	}
	ReadFile (hFile, lpText, nLength, &dwRead, NULL);
	CloseHandle (hFile);

	// atualiza o editor
	lpText[nLength / sizeof(char)] = 0;
	SendMessage (SCI_SETTEXT, 0, (LPARAM) lpText);
	SendMessage (SCI_SETSAVEPOINT);
	SendMessage (SCI_EMPTYUNDOBUFFER);
	SendMessage (SCI_CALLTIPCANCEL);

	// atualiza flags internas
	ClearFlags ();

	// arquivo lido com sucesso
	free (lpText);
	return true;
}

bool CMoniteControl::GetModified ()
{
	// GetModified - retorna se o arquivo aberto foi ou não modificado
	return SendMessage (SCI_GETMODIFY);
}

bool CMoniteControl::CanUndo ()
{
	// CanUndo - verifica se pode desfazer alguma ação
	return SendMessage (SCI_CANUNDO);
}

void CMoniteControl::Undo ()
{
	// Undo - desfaz a útlima ação
	if (CanUndo ())
	{
		SendMessage (SCI_UNDO);
		SendMessage (SCI_CALLTIPCANCEL);
	}
}

bool CMoniteControl::CanRedo ()
{
	// CanRedo - verifica se pode refazer alguma ação
	return SendMessage (SCI_CANREDO);
}

void CMoniteControl::Redo ()
{
	// Redo - refaz a última ação
	if (CanRedo ())
	{
		SendMessage (SCI_REDO);
		SendMessage (SCI_CALLTIPCANCEL);
	}
}

void CMoniteControl::Cut ()
{
	// Cut - recorta o texto selecionado
	int nSelStart = SendMessage (SCI_GETSELECTIONSTART);
	int nSelEnd = SendMessage (SCI_GETSELECTIONEND);

	if (nSelEnd > nSelStart)
	{
		SendMessage (SCI_CUT);
		SendMessage (SCI_CALLTIPCANCEL);
	}
	else
	{
		Copy ();
		needReloadMacros = firstLoadMacros = true;
	}
}

void CMoniteControl::Copy ()
{
	// Copy - copia o texto selecionado
	int nSelStart = SendMessage (SCI_GETSELECTIONSTART);
	int nSelEnd = SendMessage (SCI_GETSELECTIONEND);

	if (nSelEnd > nSelStart)
		SendMessage (SCI_COPY);
	else
	{
		int nLine = SendMessage (SCI_LINEFROMPOSITION, nSelStart);
		SendMessage (SCI_COPYRANGE, SendMessage (SCI_POSITIONFROMLINE, nLine), SendMessage (SCI_GETLINEENDPOSITION, nLine));
	}
}

bool CMoniteControl::CanPaste ()
{
	// CanPaste - verifica se é possível colar o conteúdo da área de transferência
	return SendMessage (SCI_CANPASTE);
}

void CMoniteControl::Paste ()
{
	// Paste - cola o conteúdo da área de transferência no editor
	if (CanPaste ())
	{
		SendMessage (SCI_PASTE);
		SendMessage (SCI_CALLTIPCANCEL);
		needReloadMacros = firstLoadMacros = true;
	}
}

void CMoniteControl::DeleteSelection ()
{
	// DeleteSelection - remove o texto selecionado
	SendMessage (SCI_CLEAR);
	SendMessage (SCI_CALLTIPCANCEL);
}

void CMoniteControl::SelectAll ()
{
	// SelectAll - seleciona todo o texto do editor
	SendMessage (SCI_SELECTALL);
	SendMessage (SCI_CALLTIPCANCEL);
}

bool CMoniteControl::StartSearch (CString sSearch, bool bReplace)
{
	// StartSearch - incia a procura no editor
	TextToFind ttfInfo;

	sSearchStr = sSearch;
	ttfInfo.chrg.cpMin = 0;
	ttfInfo.chrg.cpMax = SendMessage (SCI_GETLENGTH);
	ttfInfo.lpstrText = sSearchStr.GetBuffer (sSearchStr.GetLength ());

	long nPos = SendMessage (SCI_FINDTEXT, 0, (LPARAM) &ttfInfo);
	sSearchStr.ReleaseBuffer ();

	if (nPos == -1)
		return false;
	else
	{
		if (bReplace)
		{
			SendMessage (SCI_SETTARGETSTART, ttfInfo.chrgText.cpMin);
			SendMessage (SCI_SETTARGETEND, ttfInfo.chrgText.cpMax);
		}
		else
		{
			SendMessage (SCI_SETSELECTIONSTART, ttfInfo.chrgText.cpMin);
			SendMessage (SCI_SETSELECTIONEND, ttfInfo.chrgText.cpMax);
		}
		SendMessage (SCI_CALLTIPCANCEL);
		return true;
	}
}

bool CMoniteControl::SearchNext (bool bReplace)
{
	// SearchNext - procura a próxima ocorrência
	long nStrLen = sSearchStr.GetLength ();
	long nPos = SendMessage (SCI_SEARCHNEXT, 0, (LPARAM) sSearchStr.GetBuffer (nStrLen));
	sSearchStr.ReleaseBuffer ();

	if (nPos == -1)
		return false;
	else
	{
		if (bReplace)
		{
			SendMessage (SCI_SETTARGETSTART, nPos);
			SendMessage (SCI_SETTARGETEND, nPos + nStrLen);
		}
		else
		{
			SendMessage (SCI_SETSELECTIONSTART, nPos);
			SendMessage (SCI_SETSELECTIONEND, nPos + nStrLen);
		}
		SendMessage (SCI_CALLTIPCANCEL);
		return true;
	}
}

bool CMoniteControl::SearchPrevious (bool bReplace)
{
	// SearchPrevious - procura a ocorrência anterior
	long nStrLen = sSearchStr.GetLength ();
	long nPos = SendMessage (SCI_SEARCHPREV, 0, (LPARAM) sSearchStr.GetBuffer (nStrLen));
	sSearchStr.ReleaseBuffer ();

	if (nPos == -1)
		return false;
	else
	{
		if (bReplace)
		{
			SendMessage (SCI_SETTARGETSTART, nPos);
			SendMessage (SCI_SETTARGETEND, nPos + nStrLen);
		}
		else
		{
			SendMessage (SCI_SETSELECTIONSTART, nPos);
			SendMessage (SCI_SETSELECTIONEND, nPos + nStrLen);
		}
		SendMessage (SCI_CALLTIPCANCEL);
		return true;
	}
}

bool CMoniteControl::StartReplace (CString sSearch, CString sReplaceWith)
{
	// StartReplace - incia a substituição no editor
	sReplaceStr = sReplaceWith;
	if (!StartSearch (sSearch, true))
		return false;

	SendMessage (SCI_REPLACETARGET, -1, (LPARAM) sReplaceStr.GetBuffer (sReplaceStr.GetLength ()));
	sReplaceStr.ReleaseBuffer ();
	return true;
}

bool CMoniteControl::ReplaceNext ()
{
	// ReplaceNext - substitui a próxima ocorrência
	if (!SearchNext (true))
		return false;

	SendMessage (SCI_REPLACETARGET, -1, (LPARAM) sReplaceStr.GetBuffer (sReplaceStr.GetLength ()));
	sReplaceStr.ReleaseBuffer ();
	return true;
}

bool CMoniteControl::ReplacePrevious ()
{
	// ReplacePrevious - substitui a ocorrência anterior
	if (!SearchPrevious (true))
		return false;

	SendMessage (SCI_REPLACETARGET, -1, (LPARAM) sReplaceStr.GetBuffer (sReplaceStr.GetLength ()));
	sReplaceStr.ReleaseBuffer ();
	return true;
}

void CMoniteControl::SetSelText (CString sText)
{
	// SelSelText - modifica o texto selecionado
	SendMessage (SCI_REPLACESEL, 0, (LPARAM) sText.GetBuffer (sText.GetLength ()));
	sText.ReleaseBuffer ();
}

char *CMoniteControl::GetData ()
{
	// GetData - retorna os dados do controle
	long nLength = SendMessage (SCI_GETLENGTH);
	char *lpText = (char*) malloc ((nLength + 1) * sizeof(char));
	if (!lpText)
		return NULL;
	SendMessage (SCI_GETTEXT, nLength + 1, (LPARAM) lpText);
	return lpText;
}

long CMoniteControl::GetLineFromPosition (long nPosition)
{
	return SendMessage (SCI_LINEFROMPOSITION, nPosition);
}

void CMoniteControl::SelectLine (long nLine)
{
	SetSelection (SendMessage (SCI_GETLINEENDPOSITION, nLine), SendMessage (SCI_POSITIONFROMLINE, nLine));
}