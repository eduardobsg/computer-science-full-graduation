/********************************************************************
	DECLARAÇÃO DO CONTROLE DE FLUXOGRAMA
	Criação:	09/07/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien e
						 Leonardo Golob
********************************************************************/


#pragma once
#include "Program.h"


/********************************************************************
	CLASSE FLOWCHART */

enum CONNECTOR_TYPE {ctS, ctL, ctUPlus, ctULess};

class CFlowgram : public CWnd
{
// Construction
public:
	CFlowgram();

// Propriedades
public:
	PROGRAM *pProgram;
	CString sStart, sEnd, sTrue, sFalse;
	HFONT hItemsFont;
	COLORREF cBackColor, cActiveBackColor, cItemBackColor;
	COLORREF cActiveColor, cStartEndColor, cOperationColor, cTestColor, cConnectorColor;

	void UpdatePos ();
	void Refresh ();
	void PaintControl (CDC *pDC);
	void PaintFlowchart (CDC *pDC, long nStartX, long nStartY, long nDeviceWidth, long nDeviceHeight);

	void SetMode (bool bRunning);
	void SelectItem (FLOWCHART_ITEM *pItem);

// Funções internas
private:
	HCURSOR curDefault, curActive, curMoving;
	bool bRunning, bMoving, bVScroll, bHScroll;
	SIZE szControl, szFlowArea, szMoveDif, szScrollDif;
	POINT ptoFlowPos;

	CDC *bmpDC;
	CBitmap *bmpBuffer;
	SIZE bmpSize;
	FLOWCHART_ITEM *pActiveItem;

	void DrawConnector (CDC *pDC, POINT ptoSource, POINT ptoDest, CONNECTOR_TYPE ctConnector, long nSideSize, bool bVertical, bool bTest, bool bTestTrue);
	bool DetectCollision (POINT ptoSource, POINT ptoDest, CONNECTOR_TYPE ctConnector, long &nSideSize, bool bVertical);
	void PaintConnector (CDC *pDC, FLOWCHART_ITEM *pSource, FLOWCHART_ITEM *pDest, bool bTest, bool bTestTrue);

	FLOWCHART_ITEM *GetFlowItemXY (CPoint &ptoPos);

	void UpdateScroll ();

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CFlowgram();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

