/********************************************************************
	DECLARAÇÃO DO CONTROLE DE INTRUÇÕES ROTULADAS
	Criação:	17/07/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien e
						 Leonardo Golob
********************************************************************/


#pragma once
#include "Program.h"


/********************************************************************
	CLASSE INSTRUCTIONS CONTROL */

class CInstructionsCtrl : public CWnd
{
// Construction
public:
	CInstructionsCtrl();

// Funções externas
public:
	PROGRAM *pProgram;

	HFONT hItemsFont;
	COLORREF cBackColor, cBarColor, cBarBorder;
	COLORREF cActiveColor, cActiveBorder, cCallerColor, cCallerBorder;
	unsigned int nLabelWidth;

	void UpdatePos ();
	void SetProgram (PROGRAM *pNewProgram);
	void SelectItem (LABEL *pLabel);

// Funções internas
private:
	POINT ptoStartPos;
	LABEL *pActiveLabel, *pCallerLabel;
	bool bCallerWay;

	SIZE szInstrSize;
	CDC *bmpDC;
	CBitmap *bmpBuffer;
	SIZE bmpSize;

	void PaintControl (CDC *pDC);
	void PaintInstructions (CDC *pDC, POINT ptoStartPos);

	void UpdateScroll ();

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CInstructionsCtrl();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

