/********************************************************************
	IMPLEMENTAÇÃO DO CONTROLE DE FLUXOGRAMA
	Criação:	09/07/2003
	Copyright:	(c) 2003 Marcelo Bona Boff, Fernando Trebien e
						 Leonardo Golob
********************************************************************/


#include "stdafx.h"
#include "Flowgram.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CORRECT_RECT(r, tmp) { \
		if (r.left > r.right) \
		{ \
			tmp = r.left; r.left = r.right; r.right = tmp; \
		} \
		if (r.top > r.bottom) \
		{ \
			tmp = r.top; r.top = r.bottom; r.bottom = tmp; \
		}}
#define UPDATE_FLOWAREA(r) { \
		if ((r.right + 8 - ptoFlowPos.x) > szFlowArea.cx) \
			szFlowArea.cx = r.right + 8 - ptoFlowPos.x; \
		if ((r.bottom + 8 - ptoFlowPos.y) > szFlowArea.cy) \
			szFlowArea.cy = r.bottom + 8 - ptoFlowPos.y; \
		}


/********************************************************************
	CLASSE FLOWCHART */

CFlowgram::CFlowgram()
{
	// atribui o valor padrão as variáveis
	pProgram = NULL;
	sStart = "partida";
	sEnd = "parada";
	sTrue = "V";
	sFalse = "F";

	hItemsFont = (HFONT) GetStockObject (DEFAULT_GUI_FONT);
	cBackColor = GetSysColor (COLOR_BTNFACE);
	cActiveBackColor = RGB (255, 255, 0);
	cItemBackColor = RGB (255, 255, 255);
	cActiveColor = RGB (128, 128, 0);
	cStartEndColor = RGB (0, 0, 128);
	cOperationColor = RGB (0, 128, 0);
	cTestColor = RGB (128, 0, 0);
	cConnectorColor = RGB (0, 0, 0);

	curDefault = LoadCursor (NULL, IDC_ARROW);
	curActive = LoadCursor (AfxGetInstanceHandle (), MAKEINTRESOURCE (IDC_HANDOPENED));
	curMoving = LoadCursor (AfxGetInstanceHandle (), MAKEINTRESOURCE (IDC_HANDCLOSED));

	bRunning = bMoving = bVScroll = bHScroll = false;
	szFlowArea.cx = 0; szFlowArea.cy = 0;
	szScrollDif.cx = 0; szScrollDif.cy = 0;
	ptoFlowPos.x = 0; ptoFlowPos.y = 0;

	bmpDC = NULL;
	bmpBuffer = NULL;
	bmpSize.cx = 0; bmpSize.cy = 0;
	pActiveItem = NULL;
}

CFlowgram::~CFlowgram()
{
	// destrói os objetos internos
	if (bmpDC)
		delete bmpDC;
	if (bmpBuffer)
		delete bmpBuffer;
}


BEGIN_MESSAGE_MAP(CFlowgram, CWnd)
ON_WM_CREATE()
ON_WM_PAINT()
ON_WM_ERASEBKGND()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_SIZE()
ON_WM_VSCROLL()
ON_WM_HSCROLL()
END_MESSAGE_MAP()



// CFlowgram message handlers

BOOL CFlowgram::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.style |= WS_HSCROLL | WS_VSCROLL;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		NULL, reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

int CFlowgram::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// desabilita as barras de rolagem
	EnableScrollBar (SB_VERT, ESB_DISABLE_BOTH);
	EnableScrollBar (SB_HORZ, ESB_DISABLE_BOTH);

	return 0;
}

void CFlowgram::OnPaint ()
{
	CPaintDC pDC (this); // dispositivo de pintura

	// pinta o controle
	PaintControl (&pDC);

	// atualiza a barra de rolagem
	UpdateScroll ();	
}

BOOL CFlowgram::OnEraseBkgnd(CDC* pDC)
{
	// não limpa o fundo do controle
	return FALSE;
}

void CFlowgram::OnMouseMove(UINT nFlags, CPoint point)
{
	// atualiza o rótulo ativo
	if (!bRunning)
	{
		if (bMoving && pActiveItem)
		{
			// move o rótulo ativo
			POINT ptoNewPos = {point.x - szMoveDif.cx, point.y - szMoveDif.cy};
			if ((pActiveItem->nLeft != ptoNewPos.x) || (pActiveItem->nTop != ptoNewPos.y))
			{
				pActiveItem->nLeft = ptoNewPos.x;
				pActiveItem->nTop = ptoNewPos.y;

				CDC *pDC = GetDC ();
				PaintControl (pDC);
				ReleaseDC (pDC);
			}
		}
		else
		{
			// muda o rótulo ativo
			FLOWCHART_ITEM *pNewActive = GetFlowItemXY (point);
			if (pActiveItem != pNewActive)
			{
				pActiveItem = pNewActive;

				CDC *pDC = GetDC ();
				PaintControl (pDC);
				ReleaseDC (pDC);
			}
		}
	}

	// atualiza o cursor
	if (bRunning || !pActiveItem)
		SetCursor (curDefault);
	else
	{
		if (bMoving)
			SetCursor (curMoving);
		else
			SetCursor (curActive);
	}
		

	CWnd::OnMouseMove(nFlags, point);
}

void CFlowgram::OnLButtonDown(UINT nFlags, CPoint point)
{
	// seleciona e inicia o movimento de um rótulo
	if (!bRunning && pActiveItem)
	{
		bMoving = true;
		szMoveDif.cx = point.x - pActiveItem->nLeft;
		szMoveDif.cy = point.y - pActiveItem->nTop;
		SetCursor (curMoving);
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CFlowgram::OnLButtonUp(UINT nFlags, CPoint point)
{
	// atualiza o flag de movimento
	if (bMoving)
	{
		UpdateScroll ();
		SetCursor (curActive);
	}
	bMoving = false;

	CWnd::OnLButtonUp(nFlags, point);
}

void CFlowgram::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	szControl.cx = cx;
	szControl.cy = cy;

	// atualiza a barra de rolagem
	UpdateScroll ();
}

void CFlowgram::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// pega os valores máximos e mínimos da barra
	int nMinPos, nMaxPos;
	GetScrollRange (SB_VERT, &nMinPos, &nMaxPos);

	// atualiza a posição relativa do fluxograma
	switch (nSBCode)
	{
		case SB_BOTTOM:
			ptoFlowPos.y = -(GetScrollPos(SB_VERT) + 2);
			break;
			
		case SB_TOP:
			ptoFlowPos.y = -(GetScrollPos(SB_VERT) - 2);
			break;

		case SB_LINEDOWN:
			ptoFlowPos.y = -(GetScrollPos(SB_VERT) + 2);
			break;

		case SB_LINEUP:
			ptoFlowPos.y = -(GetScrollPos(SB_VERT) - 2);
			break;

		case SB_PAGEDOWN:
			ptoFlowPos.y = -(GetScrollPos(SB_VERT) + 8);
			break;

		case SB_PAGEUP:
			ptoFlowPos.y = -(GetScrollPos(SB_VERT) - 8);
			break;

		case SB_THUMBPOSITION:
			ptoFlowPos.y = -nPos;
			break;

		case SB_THUMBTRACK:
			ptoFlowPos.y = -nPos;
			break;
	}

	// verifica se não passou do limite
	if (-ptoFlowPos.y > nMaxPos)
		ptoFlowPos.y = -nMaxPos;

	// repinta o controle
	CDC *pDC = GetDC ();
	PaintControl (pDC);
	ReleaseDC (pDC);

	// atualiza a posição da barra
	SetScrollPos (SB_VERT, -ptoFlowPos.y, TRUE);

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CFlowgram::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// pega os valores máximos e mínimos da barra
	int nMinPos, nMaxPos;
	GetScrollRange (SB_HORZ, &nMinPos, &nMaxPos);

	// atualiza a posição relativa do fluxograma
	switch (nSBCode)
	{
		case SB_RIGHT:
			ptoFlowPos.x = -(GetScrollPos(SB_HORZ) + 2);
			break;
			
		case SB_LEFT:
			ptoFlowPos.x = -(GetScrollPos(SB_HORZ) - 2);
			break;

		case SB_LINERIGHT:
			ptoFlowPos.x = -(GetScrollPos(SB_HORZ) + 2);
			break;

		case SB_LINELEFT:
			ptoFlowPos.x = -(GetScrollPos(SB_HORZ) - 2);
			break;

		case SB_PAGERIGHT:
			ptoFlowPos.x = -(GetScrollPos(SB_HORZ) + 8);
			break;

		case SB_PAGELEFT:
			ptoFlowPos.x = -(GetScrollPos(SB_HORZ) - 8);
			break;

		case SB_THUMBPOSITION:
			ptoFlowPos.x = -nPos;
			break;

		case SB_THUMBTRACK:
			ptoFlowPos.x = -nPos;
			break;
	}

	// verifica se não passou do limite
	if (-ptoFlowPos.x > nMaxPos)
		ptoFlowPos.x = -nMaxPos;

	// repinta o controle
	CDC *pDC = GetDC ();
	PaintControl (pDC);
	ReleaseDC (pDC);

	// atualiza a posição da barra
	SetScrollPos (SB_HORZ, -ptoFlowPos.x, TRUE);

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CFlowgram::UpdatePos ()
{
	// UpdatePos - atualiza para a posição incial do fluxograma

	ptoFlowPos.x = 0; ptoFlowPos.y = 0;
	SetScrollPos (SB_VERT, 0);
	SetScrollPos (SB_HORZ, 0);
}

void CFlowgram::Refresh ()
{
	// Repaint - repinta o controle
	CDC *pDC = GetDC ();
	PaintControl (pDC);
	ReleaseDC (pDC);

	UpdateScroll ();
}

void CFlowgram::PaintControl (CDC *pDC)
{
	// PaintControl - repinta o controle

	// atualiza o buffer de pintura
	if (!bmpDC)
	{
		bmpDC = new CDC ();
		bmpDC->CreateCompatibleDC (pDC);
	}
	if (!bmpBuffer || ((bmpSize.cx != szControl.cx) || (bmpSize.cy != szControl.cy)))
	{
		if (bmpBuffer)
			delete bmpBuffer;
		bmpBuffer = new CBitmap ();
		bmpSize.cx = szControl.cx;
		bmpSize.cy = szControl.cy;
		bmpBuffer->CreateCompatibleBitmap (pDC, bmpSize.cx, bmpSize.cy);
		bmpDC->SelectObject (bmpBuffer);
	}
	
	// pinta o bitmap
	PaintFlowchart (bmpDC, ptoFlowPos.x, ptoFlowPos.y, szControl.cx, szControl.cy);
	pDC->BitBlt (0, 0, szControl.cx, szControl.cy, bmpDC, 0, 0, SRCCOPY);
}

void CFlowgram::PaintFlowchart (CDC *pDC, long nStartX, long nStartY, long nDeviceWidth, long nDeviceHeight)
{
	// PaintFlowchart - pinta o fluxograma
	CBrush pBackBrush (cBackColor);
	CBrush pActiveBackBrush (cActiveBackColor);
	CBrush pBackItemBrush (cItemBackColor);
	CBrush pPolyBrush (cConnectorColor);
	CPen pActivePen (PS_SOLID, 2, cActiveColor);
	CPen pStartEndPen (PS_SOLID, 2, cStartEndColor);
	CPen pOperationPen (PS_SOLID, 2, cOperationColor);
	CPen pTestPen (PS_SOLID, 2, cTestColor);
	CPen pPolyPen (PS_SOLID, 2, cConnectorColor);
	CSize szText;
	CRect rRect;
	LABEL *pLabel;
	unsigned int nLabelsCount = pProgram->Count (), i, nTestSize;
	bool bIsTest;

	// atualiza a variável do tamanho do fluxograma
	szFlowArea.cx = 0; szFlowArea.cy = 0;

	// atualiza a fonte dos itens
	pDC->SelectObject (hItemsFont);
	pDC->SelectObject (pBackItemBrush);
	pDC->SetBkMode (TRANSPARENT);

	// pinta a cor de fundo
	rRect.left = rRect.top = 0;
	rRect.right = szControl.cx;
	rRect.bottom = szControl.cy;
	pDC->FillRect (rRect, &pBackBrush);

	// imprime a partida
	if (pActiveItem == &pProgram->fiStart)
	{
		if (bRunning)
			pDC->SelectObject (pActiveBackBrush);
		pDC->SelectObject (&pActivePen);
	}
	else
		pDC->SelectObject (&pStartEndPen);
	szText = pDC->GetTextExtent (sStart);
	rRect.left = pProgram->fiStart.nLeft + nStartX;
	rRect.top = pProgram->fiStart.nTop + nStartY;
	rRect.right = rRect.left + szText.cx + 8;
	rRect.bottom = rRect.top + szText.cy + 8;
	pProgram->fiStart.rPos = rRect;
	UPDATE_FLOWAREA (rRect);
    pDC->RoundRect (rRect, CPoint (12, 12));
	pDC->DrawText (sStart, CRect (rRect.left + 4, rRect.top + 4, rRect.right - 4, rRect.bottom - 4), DT_CENTER | DT_SINGLELINE);
	if ((pActiveItem == &pProgram->fiStart) && bRunning)
		pDC->SelectObject (pBackItemBrush);

	// pinta cada um dos itens do fluxograma
	for (i = 0; i < nLabelsCount; i++)
	{
		// pega label atual
		pLabel = (*pProgram)[i];

		// calcula o tamanho do texto
		szText = pDC->GetTextExtent (pLabel->sData);

		if ((pLabel->lType == ltTest) || (pLabel->lType == ltMacroTest))
		{
			// pinta um teste, calculando o seu retângulo
			nTestSize = ((12 + szText.cy) * (4 + szText.cx)) / 24;
			rRect.left = pLabel->fiFlowData.nLeft + nStartX;
			rRect.top = pLabel->fiFlowData.nTop + nStartY;
			rRect.right = 2 * nTestSize;
			rRect.bottom = szText.cy + 12;

			// pinta o retângulo
			if (pActiveItem == &pLabel->fiFlowData)
			{
				if (bRunning)
					pDC->SelectObject (pActiveBackBrush);
				pDC->SelectObject (&pActivePen);
			}
			else
				pDC->SelectObject (&pTestPen);
			POINT pPoints[5] = {{rRect.left, rRect.top + (rRect.bottom / 2)},
								{rRect.left + nTestSize, rRect.top},
								{rRect.left + rRect.right, rRect.top + (rRect.bottom / 2)},
								{rRect.left + nTestSize, rRect.top + rRect.bottom},
								{rRect.left, rRect.top + (rRect.bottom / 2)}};
			pDC->Polygon (pPoints, 5);

			// pinta o texto do retângulo
			rRect.right = rRect.left + 2 * nTestSize;
			rRect.bottom = rRect.top + szText.cy + 12;
			pDC->DrawText (pLabel->sData, CRect (rRect.left + (nTestSize - (szText.cx / 2)), rRect.top + 6, rRect.right - (nTestSize - (szText.cx / 2)), rRect.bottom - 6), DT_CENTER | DT_SINGLELINE);
			if ((pActiveItem == &pLabel->fiFlowData) && bRunning)
				pDC->SelectObject (pBackItemBrush);
		}
		else
		{
			// pinta uma operação, calculando o seu retângulo
			rRect.left = pLabel->fiFlowData.nLeft + nStartX;
			rRect.top = pLabel->fiFlowData.nTop + nStartY;
			rRect.right = rRect.left + szText.cx + 8;
			rRect.bottom = rRect.top + szText.cy + 8;

			// pinta o retângulo
			if (pActiveItem == &pLabel->fiFlowData)
			{
				if (bRunning)
					pDC->SelectObject (pActiveBackBrush);
				pDC->SelectObject (&pActivePen);
			}
			else
				pDC->SelectObject (&pOperationPen);
			pDC->Rectangle (rRect);

			// pinta o texto do retângulo
			pDC->DrawText (pLabel->sData, CRect (rRect.left + 4, rRect.top + 4, rRect.right - 4, rRect.bottom - 4), DT_CENTER | DT_SINGLELINE);
			if ((pActiveItem == &pLabel->fiFlowData) && bRunning)
				pDC->SelectObject (pBackItemBrush);
		}
		pLabel->fiFlowData.rPos = rRect;
		UPDATE_FLOWAREA (rRect);
	}

	// imprime a parada
	if (pActiveItem == &pProgram->fiEnd)
	{
		if (bRunning)
			pDC->SelectObject (pActiveBackBrush);
		pDC->SelectObject (&pActivePen);
	}
	else
		pDC->SelectObject (&pStartEndPen);
	szText = pDC->GetTextExtent (sEnd);
	rRect.left = pProgram->fiEnd.nLeft + nStartX;
	rRect.top = pProgram->fiEnd.nTop + nStartY;
	rRect.right = rRect.left + szText.cx + 8;
	rRect.bottom = rRect.top + szText.cy + 8;
	pProgram->fiEnd.rPos = rRect;
	UPDATE_FLOWAREA (rRect);
    pDC->RoundRect (rRect, CPoint (12, 12));
	pDC->DrawText (sEnd, CRect (rRect.left + 4, rRect.top + 4, rRect.right - 4, rRect.bottom - 4), DT_CENTER | DT_SINGLELINE);

	// atualiza as propriedades dos conectores
	pDC->SelectObject (pPolyBrush);
	pDC->SelectObject (pPolyPen);

	// pinta o conector da partida
	if (nLabelsCount)
		PaintConnector (pDC, &pProgram->fiStart, &(*pProgram)[0]->fiFlowData, false, false);

	// pinta os outros conectores
	for (i = 0; i < nLabelsCount; i++)
	{
		// pega label atual
		pLabel = (*pProgram)[i];
		bIsTest = (pLabel->lType == ltTest) || (pLabel->lType == ltMacroTest);

		// pinta o lado verdadeiro
		if (pLabel->pTrue)
			PaintConnector (pDC, &pLabel->fiFlowData, &pLabel->pTrue->fiFlowData, bIsTest, true);
		else
			PaintConnector (pDC, &pLabel->fiFlowData, &pProgram->fiEnd, bIsTest, true);

		// pinta o lado falso
		if (bIsTest)
		{
			if (pLabel->pFalse)
				PaintConnector (pDC, &pLabel->fiFlowData, &pLabel->pFalse->fiFlowData, bIsTest, false);
			else
				PaintConnector (pDC, &pLabel->fiFlowData, &pProgram->fiEnd, bIsTest, false);
		}
	}
}

void CFlowgram::DrawConnector (CDC *pDC, POINT ptoSource, POINT ptoDest, CONNECTOR_TYPE ctConnector, long nSideSize, bool bVertical, bool bTest, bool bTestTrue)
{
	// DrawConnector - desenha um conector
	POINT pPoints[4];
	RECT rTest;
	SIZE szTest;
	bool bTestVertical;

	// atualiza os pontos nunca modificados
	pPoints[0] = ptoSource;
	pPoints[3] = ptoDest;

	// pinta a linha do connector
	switch (ctConnector)
	{
	case ctS:
		{
			// pinta um conector S
			if (bVertical)
			{
				pPoints[1].x = ptoSource.x;
				pPoints[1].y = (ptoSource.y < ptoDest.y) ? ptoSource.y + nSideSize : ptoSource.y - nSideSize;
				pPoints[2].x = ptoDest.x; pPoints[2].y = pPoints[1].y;
			}
			else
			{
				pPoints[1].x = (ptoSource.x < ptoDest.x) ? ptoSource.x + nSideSize : ptoSource.x - nSideSize;
				pPoints[1].y = ptoSource.y;
				pPoints[2].x = pPoints[1].x; pPoints[2].y = ptoDest.y;
			}
			bTestVertical = bVertical;
			pDC->Polyline (pPoints, 4);
			break;
		}
	case ctL:
		{
			// pinta um conector L
			pPoints[2] = ptoDest;
			if (bVertical)
			{
				pPoints[1].x = ptoDest.x; pPoints[1].y = ptoSource.y;
			}
			else
			{
				pPoints[1].x = ptoSource.x; pPoints[1].y = ptoDest.y;
			}
			bTestVertical = !bVertical;
			pDC->Polyline (pPoints, 3);
			break;
		}
	case ctUPlus:
		{
			// pinta um conector UPlus
			if (bVertical)
			{
				pPoints[1].x = ptoSource.x; pPoints[1].y = ptoSource.y + nSideSize;
				pPoints[2].x = ptoDest.x; pPoints[2].y = pPoints[1].y;
			}
			else
			{
				pPoints[1].x = ptoSource.x + nSideSize; pPoints[1].y = ptoSource.y;
				pPoints[2].x = pPoints[1].x; pPoints[2].y = ptoDest.y;
			}
			bTestVertical = bVertical;
			pDC->Polyline (pPoints, 4);
			break;
		}
	case ctULess:
		{
			// pinta um conector ULess
			if (bVertical)
			{
				pPoints[1].x = ptoSource.x; pPoints[1].y = ptoSource.y - nSideSize;
				pPoints[2].x = ptoDest.x; pPoints[2].y = pPoints[1].y;
			}
			else
			{
				pPoints[1].x = ptoSource.x - nSideSize; pPoints[1].y = ptoSource.y;
				pPoints[2].x = pPoints[1].x; pPoints[2].y = ptoDest.y;
			}
			bTestVertical = bVertical;
			pDC->Polyline (pPoints, 4);
			break;
		}
	}

	// pinta a seta do conector
	pPoints[0] = ptoDest;
	if (bVertical)
	{
		if (((ptoSource.y < ptoDest.y) || (ctConnector == ctULess)) && (ctConnector != ctUPlus))
		{
			// atualiza os pontos de uma seta vertical para baixo
			pPoints[1].x = ptoDest.x - 3; pPoints[1].y = ptoDest.y - 6;
			pPoints[2].x = ptoDest.x + 3; pPoints[2].y = pPoints[1].y;
		}
		else
		{
			// atualiza os pontos de uma seta vertical para cima
			pPoints[1].x = ptoDest.x - 3; pPoints[1].y = ptoDest.y + 6;
			pPoints[2].x = ptoDest.x + 3; pPoints[2].y = pPoints[1].y;
		}
	}
	else
	{
		if (((ptoSource.x < ptoDest.x) || (ctConnector == ctULess)) && (ctConnector != ctUPlus))
		{
			// atualiza os pontos de uma seta horizontal para direita
			pPoints[1].x = ptoDest.x - 6; pPoints[1].y = ptoDest.y - 3;
			pPoints[2].x = pPoints[1].x; pPoints[2].y = ptoDest.y + 3;
		}
		else
		{
			// atualiza os pontos de uma seta horizontal para esquerda
			pPoints[1].x = ptoDest.x + 6; pPoints[1].y = ptoDest.y - 3;
			pPoints[2].x = pPoints[1].x; pPoints[2].y = ptoDest.y + 3;
		}
	}
	pDC->Polygon (pPoints, 4);

	// pinta o texto do teste
	if (bTest)
	{
		// calcula o tamanho do teste se necessário
		if (bTestTrue)
			szTest = pDC->GetTextExtent (sTrue);
		else
			szTest = pDC->GetTextExtent (sFalse);
		// calcula o retângulo do texto do teste
		if (bTestVertical)
		{
			rTest.right = ptoSource.x - 2;
			rTest.left = rTest.right - szTest.cx;
			if (ptoSource.y < ptoDest.y)
			{
				rTest.top = ptoSource.y + 2;
				rTest.bottom = rTest.top + szTest.cy;
			}
			else
			{
				rTest.bottom = ptoSource.y - 2;
				rTest.top = rTest.bottom - szTest.cy;
			}
		}
		else
		{
			rTest.bottom = ptoSource.y - 2;
			rTest.top = rTest.bottom - szTest.cy;
			if (ptoSource.x < ptoDest.x)
			{
				rTest.left = ptoSource.x + 2;
				rTest.right = rTest.left + szTest.cx;
			}
			else
			{
				rTest.right = ptoSource.x - 2;
				rTest.left = rTest.right - szTest.cy;
			}
		}
		// imprime o texto do teste
		if (bTestTrue)
			pDC->DrawText (sTrue, &rTest, DT_CENTER | DT_SINGLELINE);
		else
			pDC->DrawText (sFalse, &rTest, DT_CENTER | DT_SINGLELINE);
	}
}

bool CFlowgram::DetectCollision (POINT ptoSource, POINT ptoDest, CONNECTOR_TYPE ctConnector, long &nSideSize, bool bVertical)
{
	// DetectCollision - detecta uma colisão e procura um possível conector que não colide
	LABEL *pLabel;
	RECT rLine1, rLine2, rLine3, rIntersect;
	long int i, nCount = pProgram->Count (), nTmp;

	// calcula as linhas do connector
	switch (ctConnector)
	{
	case ctS:
		{
			// calcula o tamanho do lado padrão
			if (bVertical)
				nSideSize = abs ((ptoDest.y - ptoSource.y) / 2);
			else
				nSideSize = abs ((ptoDest.x - ptoSource.x) / 2);
			// calcula um conector S
			do
			{
tentar_S:
				if (bVertical)
				{
					rLine1.left = ptoSource.x;
					rLine1.right = rLine1.left + 2;
					rLine1.top = ptoSource.y;
					rLine1.bottom = rLine1.top + (ptoSource.y < ptoDest.y) ? ptoSource.y + nSideSize : ptoSource.y - nSideSize;
					rLine2.left = ptoSource.x;
					rLine2.right = ptoDest.x;
					rLine2.top = rLine1.bottom;
					rLine2.bottom = rLine2.top + 2;
					rLine3.left = ptoDest.x;
					rLine3.right = rLine3.left + 2;
					rLine3.top = rLine2.bottom;
					rLine3.bottom = ptoDest.y;
				}
				else
				{
					rLine1.top = ptoSource.y;
					rLine1.bottom = rLine1.top + 2;
					rLine1.left = ptoSource.x;
					rLine1.right = rLine1.left + (ptoSource.x < ptoDest.x) ? ptoSource.x + nSideSize : ptoSource.x - nSideSize;
					rLine2.top = ptoSource.y;
					rLine2.bottom = ptoDest.y;
					rLine2.left = rLine1.right;
					rLine2.right = rLine2.left + 2;
					rLine3.top = ptoDest.y;
					rLine3.bottom = rLine3.top + 2;
					rLine3.left = rLine2.right;
					rLine3.right = ptoDest.x;
				}
				CORRECT_RECT (rLine1, nTmp);
				CORRECT_RECT (rLine2, nTmp);
				CORRECT_RECT (rLine3, nTmp);
				// verifica se ocorreu colisão
				for (i = 0; i < nCount; i++)
				{
					pLabel = (*pProgram)[i];
					if (IntersectRect (&rIntersect, &rLine1, &pLabel->fiFlowData.rPos) ||
						IntersectRect (&rIntersect, &rLine3, &pLabel->fiFlowData.rPos))
						return true;
					else if (IntersectRect (&rIntersect, &rLine2, &pLabel->fiFlowData.rPos))
					{
						if (bVertical)
						{
							nSideSize += (pLabel->fiFlowData.rPos.bottom - rIntersect.bottom) + 4;
							if (nSideSize >= abs (ptoDest.y - ptoSource.y))
								return true;
							else
								goto tentar_S;
						}
						else
						{
							nSideSize += (pLabel->fiFlowData.rPos.right - rIntersect.right) + 4;
							if (nSideSize >= abs (ptoDest.x - ptoSource.x))
								return true;
							else
								goto tentar_S;
						}
					}
				}
				// neste caso não há uma colisão
				return false;
			} while (true);
		}
	case ctL:
		{
			// calcula um conector L
			do
			{
				if (bVertical)
				{
					rLine1.left = ptoSource.x;
					rLine1.right = ptoDest.x;
					rLine1.top = ptoSource.y;
					rLine1.bottom = rLine1.top + 2;
					rLine2.left = rLine1.right;
					rLine2.right = rLine2.left + 2;
					rLine2.top = rLine1.bottom;
					rLine2.bottom = ptoDest.y;
				}
				else
				{
					rLine1.top = ptoSource.y;
					rLine1.bottom = ptoDest.y;
					rLine1.left = ptoSource.x;
					rLine1.right = rLine1.left + 2;
					rLine2.top = rLine1.bottom;
					rLine2.bottom = rLine2.top + 2;
					rLine2.left = rLine1.right;
					rLine2.right = ptoDest.x;
				}
				CORRECT_RECT (rLine1, nTmp);
				CORRECT_RECT (rLine2, nTmp);
				// verifica se ocorreu colisão
				for (i = 0; i < nCount; i++)
				{
					pLabel = (*pProgram)[i];
					if (IntersectRect (&rIntersect, &rLine1, &pLabel->fiFlowData.rPos) ||
						IntersectRect (&rIntersect, &rLine2, &pLabel->fiFlowData.rPos))
						return true;
				}
				// neste caso não há uma colisão
				return false;
			} while (true);
		}
	case ctUPlus:
		{
			// calcula o tamanho do lado padrão
			if (bVertical)
			{
				if (ptoDest.y > ptoSource.y)
                    nSideSize = (ptoDest.y - ptoSource.y) + 12;
				else
					nSideSize = 12;
			}
			else
			{
				if (ptoDest.x > ptoSource.x)
					nSideSize = (ptoDest.x - ptoSource.x) + 12;
				else
					nSideSize = 12;
			}
			// calcula um conector UPlus
			do
			{
tentar_UPlus:
				if (bVertical)
				{
					rLine1.left = ptoSource.x;
					rLine1.right = rLine1.left + 2;
					rLine1.top = ptoSource.y + nSideSize;
					rLine1.bottom = ptoSource.y;
					rLine2.left = ptoSource.x;
					rLine2.right = ptoDest.x;
					rLine2.top = rLine1.top;
					rLine2.bottom = rLine2.top + 2;
					rLine3.left = ptoDest.x;
					rLine3.right = rLine3.left + 2;
					rLine3.top = rLine1.top;
					rLine3.bottom = ptoDest.y;
				}
				else
				{
					rLine1.top = ptoSource.y;
					rLine1.bottom = rLine1.top + 2;
					rLine1.left = ptoSource.x + nSideSize;
					rLine1.right = ptoSource.x;
					rLine2.top = ptoSource.y;
					rLine2.bottom = ptoDest.y;
					rLine2.left = rLine1.left;
					rLine2.right = rLine2.left + 2;
					rLine3.top = ptoDest.y;
					rLine3.bottom = rLine3.top + 2;
					rLine3.left = rLine1.left;
					rLine3.right = ptoDest.x;
				}
				CORRECT_RECT (rLine1, nTmp);
				CORRECT_RECT (rLine2, nTmp);
				CORRECT_RECT (rLine3, nTmp);
				// verifica se ocorreu colisão
				for (i = 0; i < nCount; i++)
				{
					pLabel = (*pProgram)[i];
					if (IntersectRect (&rIntersect, &rLine1, &pLabel->fiFlowData.rPos) ||
						IntersectRect (&rIntersect, &rLine3, &pLabel->fiFlowData.rPos))
						return true;
					else if (IntersectRect (&rIntersect, &rLine2, &pLabel->fiFlowData.rPos))
					{
						if (bVertical)
						{
							nSideSize += (pLabel->fiFlowData.rPos.bottom - rIntersect.bottom) + 8;
							goto tentar_UPlus;
							/*if (nSideSize >= abs (ptoDest.y - ptoSource.y))
								return true;*/
						}
						else
						{
							nSideSize += (pLabel->fiFlowData.rPos.right - rIntersect.right) + 8;
							goto tentar_UPlus;
							/*if (nSideSize >= abs (ptoDest.x - ptoSource.x))
								return true;*/
						}
					}
				}
				// neste caso não há uma colisão
				return false;
			} while (true);
		}
	case ctULess:
		{
			// calcula o tamanho do lado padrão
			if (bVertical)
			{
				if (ptoDest.y < ptoSource.y)
                    nSideSize = (ptoSource.y - ptoDest.y) + 12;
				else
					nSideSize = 12;
			}
			else
			{
				if (ptoDest.x < ptoSource.x)
					nSideSize = (ptoSource.x - ptoDest.x) + 12;
				else
					nSideSize = 12;
			}
			// calcula um conector ULess
			do
			{
tentar_ULess:
				if (bVertical)
				{
					rLine1.left = ptoSource.x;
					rLine1.right = rLine1.left + 2;
					rLine1.top = ptoSource.y - nSideSize;
					rLine1.bottom = ptoSource.y;
					rLine2.left = ptoSource.x;
					rLine2.right = ptoDest.x;
					rLine2.top = rLine1.top;
					rLine2.bottom = rLine2.top + 2;
					rLine3.left = ptoDest.x;
					rLine3.right = rLine3.left + 2;
					rLine3.top = rLine1.top;
					rLine3.bottom = ptoDest.y;
				}
				else
				{
					rLine1.top = ptoSource.y;
					rLine1.bottom = rLine1.top + 2;
					rLine1.left = ptoSource.x - nSideSize;
					rLine1.right = ptoSource.x;
					rLine2.top = ptoSource.y;
					rLine2.bottom = ptoDest.y;
					rLine2.left = rLine1.left;
					rLine2.right = rLine2.left + 2;
					rLine3.top = ptoDest.y;
					rLine3.bottom = rLine3.top + 2;
					rLine3.left = rLine1.left;
					rLine3.right = ptoDest.x;
				}
				// verifica se ocorreu colisão
				for (i = 0; i < nCount; i++)
				{
					pLabel = (*pProgram)[i];
					if (IntersectRect (&rIntersect, &rLine1, &pLabel->fiFlowData.rPos) ||
						IntersectRect (&rIntersect, &rLine3, &pLabel->fiFlowData.rPos))
						return true;
					else if (IntersectRect (&rIntersect, &rLine2, &pLabel->fiFlowData.rPos))
					{
						if (bVertical)
						{
							nSideSize += (rIntersect.top - pLabel->fiFlowData.rPos.top) + 8;
							goto tentar_ULess;
							/*if (nSideSize >= abs (ptoDest.y - ptoSource.y))
								return true;*/
						}
						else
						{
							nSideSize += (rIntersect.left - pLabel->fiFlowData.rPos.left) + 8;
							goto tentar_ULess;
							/*if (nSideSize >= abs (ptoDest.x - ptoSource.x))
								return true;*/
						}
					}
				}
				// neste caso não há uma colisão
				return false;
			} while (true);
		}
	default:
		return false;
	}
}

void CFlowgram::PaintConnector (CDC *pDC, FLOWCHART_ITEM *pSource, FLOWCHART_ITEM *pDest, bool bTest, bool bTestTrue)
{
	// PaintConnector - pinta um conector entre dois rótulos
	POINT ptoSource[4], ptoDest[4], ptoStart, ptoEnd;
	CONNECTOR_TYPE tConnector;
	POINT ptoS[2], ptoL1[2], ptoL2[2], ptoUPlus[2], ptoULess[2];
	long int nSideSize, nSideSize_S, nSideSize_UPlus, nSideSize_ULess;
	bool bInVertical, bInHorizontal, bVertical, bUseL1, bUseUPlus;

	// calcula os pontos médios da origem
	ptoSource[0].x = pSource->rPos.left; ptoSource[0].y = (pSource->rPos.top + pSource->rPos.bottom) / 2;
	ptoSource[1].x = (pSource->rPos.left + pSource->rPos.right) / 2; ptoSource[1].y = pSource->rPos.top;
	ptoSource[2].x = pSource->rPos.right; ptoSource[2].y = ptoSource[0].y;
	ptoSource[3].x = ptoSource[1].x; ptoSource[3].y = pSource->rPos.bottom;

	// calcula os pontos médios do destino
	ptoDest[0].x = pDest->rPos.left; ptoDest[0].y = (pDest->rPos.top + pDest->rPos.bottom) / 2;
	ptoDest[1].x = (pDest->rPos.left + pDest->rPos.right) / 2; ptoDest[1].y = pDest->rPos.top;
	ptoDest[2].x = pDest->rPos.right; ptoDest[2].y = ptoDest[0].y;
	ptoDest[3].x = ptoDest[1].x; ptoDest[3].y = pDest->rPos.bottom;

	// calcula as variáveis booleanas
	bInVertical = (pDest->rPos.bottom >= pSource->rPos.top) && (pDest->rPos.top <= pSource->rPos.bottom);
	bInHorizontal = (pDest->rPos.right >= pSource->rPos.left) && (pDest->rPos.left <= pSource->rPos.right);

	// identifica o caso do item
	if (bInVertical || bInHorizontal)
	{
		// este é o caso 1: o melhor conector é do tipo S
		if (bInHorizontal)
		{
			// temos o caso 1 com conectores verticais
			bVertical = true;
			if (pDest->rPos.bottom < pSource->rPos.top)
			{
				// neste caso a seta é de baixo para cima
				ptoS[0] = ptoSource[1]; ptoS[1] = ptoDest[3];
			}
			else
			{
				// neste caso a seta é de cima para baixo
				ptoS[0] = ptoSource[3]; ptoS[1] = ptoDest[1];
			}
			ptoUPlus[0] = ptoSource[2]; ptoUPlus[1] = ptoDest[2];
			ptoULess[0] = ptoSource[0]; ptoULess[1] = ptoDest[0];
		}
		else
		{
			// temos o caso 1 com conectores horizontais
			bVertical = false;
			if (pDest->rPos.right < pSource->rPos.left)
			{
				// neste caso a seta é da direita para esquerda
				ptoS[0] = ptoSource[0]; ptoS[1] = ptoDest[2];
			}
			else
			{
				// neste caso a seta é da esquerda para direita
				ptoS[0] = ptoSource[2]; ptoS[1] = ptoDest[0];
			}
			ptoUPlus[0] = ptoSource[3]; ptoUPlus[1] = ptoDest[3];
			ptoULess[0] = ptoSource[1]; ptoULess[1] = ptoDest[1];
		}
		// verifica as colisões e calcula o melhor conector
		if (!DetectCollision (ptoS[0], ptoS[1], ctS, nSideSize_S, bVertical))
			tConnector = ctS;
		else
		{
			if (DetectCollision (ptoUPlus[0], ptoUPlus[1], ctUPlus, nSideSize_UPlus, !bVertical))
				nSideSize_UPlus = -1;
			if (DetectCollision (ptoULess[0], ptoULess[1], ctULess, nSideSize_ULess, !bVertical))
				nSideSize_ULess = -1;
			// escolhe o conector
			if (nSideSize_S < nSideSize_UPlus)
			{
				if (nSideSize_S < nSideSize_ULess)
					tConnector = ctS;
				else if (nSideSize_ULess != -1)
				{
					bVertical = !bVertical;
					tConnector = ctULess;
				}
				else if (nSideSize_UPlus != -1)
				{
					bVertical = !bVertical;
					tConnector = ctUPlus;
				}
				else
					tConnector = ctS;
			}
			else if ((nSideSize_UPlus < nSideSize_S) && (nSideSize_UPlus != -1))
			{
				if (nSideSize_UPlus < nSideSize_ULess)
				{
					bVertical = !bVertical;
					tConnector = ctUPlus;
				}
				else if (nSideSize_ULess != -1)
				{
					bVertical = !bVertical;
					tConnector = ctULess;
				}
				else
					tConnector = ctS;
			}
			else if ((nSideSize_ULess < nSideSize_S) && (nSideSize_ULess != -1))
			{
				if (nSideSize_ULess < nSideSize_UPlus)
				{
					bVertical = !bVertical;
					tConnector = ctULess;
				}
				else if (nSideSize_UPlus != -1)
				{
					bVertical = !bVertical;
					tConnector = ctUPlus;
				}
				else
					tConnector = ctS;
			}
			else
				tConnector = ctS;
		}
	}
	else
	{
		// este é o caso 2: o melhor conector é do tipo L
		if (pDest->rPos.right < pSource->rPos.left)
		{
			// temos o caso 2 com conectores em direção à esquerda
			if (pDest->rPos.bottom < pSource->rPos.top)
			{
				// neste caso a seta é para NO (noroeste)
				bUseUPlus = false;
				ptoL1[0] = ptoSource[0]; ptoL1[1] = ptoDest[3];
				ptoL2[0] = ptoSource[1]; ptoL2[1] = ptoDest[2];
			}
			else
			{
				// neste caso a seta é para SO (sudoeste)
				bUseUPlus = false;
				ptoL1[0] = ptoSource[0]; ptoL1[1] = ptoDest[1];
				ptoL2[0] = ptoSource[3]; ptoL2[1] = ptoDest[2];
			}
			ptoULess[0] = ptoSource[0]; ptoULess[1] = ptoDest[0];
		}
		else
		{
			// temos o caso 2 com conectores em direção à direita
			if (pDest->rPos.bottom < pSource->rPos.top)
			{
				// neste caso a seta é para NE (nordeste)
				bUseUPlus = true;
				ptoL1[0] = ptoSource[2]; ptoL1[1] = ptoDest[3];
				ptoL2[0] = ptoSource[1]; ptoL2[1] = ptoDest[0];
			}
			else
			{
				// neste caso a seta é para SE (sudeste)
				bUseUPlus = true;
				ptoL1[0] = ptoSource[2]; ptoL1[1] = ptoDest[1];
				ptoL2[0] = ptoSource[3]; ptoL2[1] = ptoDest[0];
			}
			ptoUPlus[0] = ptoSource[2]; ptoUPlus[1] = ptoDest[2];
		}
		// verifica as colisões e calcula o melhor conector
		if (!DetectCollision (ptoL1[0], ptoL1[1], ctL, nSideSize_S, true))
		{
			bUseL1 = true;
			bVertical = true;
			tConnector = ctL;
		}
		else if (!DetectCollision (ptoL2[0], ptoL2[1], ctL, nSideSize_S, false))
		{
			bUseL1 = false;
			bVertical = false;
			tConnector = ctL;
		}
		else
		{
			if (bUseUPlus)
			{
				if (!DetectCollision (ptoUPlus[0], ptoUPlus[1], ctUPlus, nSideSize_UPlus, false))
				{
					bVertical = false;
					tConnector = ctUPlus;
				}
				else
				{
					bUseL1 = true;
					bVertical = true;
					tConnector = ctL;
				}
			}
			else
			{
				if (!DetectCollision (ptoULess[0], ptoULess[1], ctULess, nSideSize_ULess, false))
				{
					bVertical = false;
					tConnector = ctULess;
				}
				else
				{
					bUseL1 = true;
					bVertical = true;
					tConnector = ctL;
				}
			}
		}
	}

	// pinta o conector
	switch (tConnector)
	{
	case ctS:
		nSideSize = nSideSize_S;
		ptoStart = ptoS[0];
		ptoEnd = ptoS[1];
		break;
	case ctL:
		nSideSize = 0;
		if (bUseL1)
		{
			ptoStart = ptoL1[0];
			ptoEnd = ptoL1[1];
		}
		else
		{
			ptoStart = ptoL2[0];
			ptoEnd = ptoL2[1];
		}
		break;
	case ctUPlus:
		nSideSize = nSideSize_UPlus;
		ptoStart = ptoUPlus[0];
		ptoEnd = ptoUPlus[1];
		break;
	case ctULess:
		nSideSize = nSideSize_ULess;
		ptoStart = ptoULess[0];
		ptoEnd = ptoULess[1];
		break;
	}
	DrawConnector (pDC, ptoStart, ptoEnd, tConnector, nSideSize, bVertical, bTest, bTestTrue);
}


FLOWCHART_ITEM *CFlowgram::GetFlowItemXY (CPoint &ptoPos)
{
	// GetLabelXY - retorna o rótulo que encontrá-se na posição (X, Y)
	LABEL *pLabel;
	long int i, nCount = pProgram->Count ();

	// procura entre a partida e a chegada
	if (PtInRect (&pProgram->fiStart.rPos, ptoPos))
		return &pProgram->fiStart;
	if (PtInRect (&pProgram->fiEnd.rPos, ptoPos))
		return &pProgram->fiEnd;

	// procura cada um dos rótulos, de trás para frente
	for (i = nCount - 1; i >= 0; i--)
	{
		pLabel = (*pProgram)[i];
		if (PtInRect (&pLabel->fiFlowData.rPos, ptoPos))
			return &pLabel->fiFlowData;
	}

	// não foi encontrado
	return NULL;
}


void CFlowgram::UpdateScroll ()
{
	// UpdateScroll - atualiza a barra de rolagem
	unsigned int nVScroll, nHScroll, nRange;
	bool bPaint = false;

	// verifica se é necessário alguma das barras
	bool bNeedVScroll = (szFlowArea.cy > szControl.cy);
	nVScroll = bNeedVScroll ? GetSystemMetrics (SM_CXVSCROLL) : 0;
	bool bNeedHScroll = (szFlowArea.cx > (szControl.cx - nVScroll));
	nHScroll = bNeedHScroll ? GetSystemMetrics (SM_CYHSCROLL) : 0;

	// verifica novamente se não é necessário a barra vertical
	bNeedVScroll = (szFlowArea.cy > (szControl.cy - nHScroll));
	nVScroll = bNeedVScroll ? GetSystemMetrics (SM_CXVSCROLL) : 0;

	// atualiza a visualização da barra vertical
	if (bNeedVScroll)
	{
		SetScrollRange (SB_VERT, 0, szFlowArea.cy - (szControl.cy - nHScroll), TRUE);
		if (!bVScroll)
		{
			SetScrollPos (SB_VERT, 0, TRUE);
			EnableScrollBar (SB_VERT);
		}
	}
	else
	{
		if (bVScroll)
		{
			if (ptoFlowPos.y)
				bPaint = true;
			SetScrollPos (SB_VERT, 0, TRUE);
			EnableScrollBar (SB_VERT, ESB_DISABLE_BOTH);
		}
		ptoFlowPos.y = 0;
	}

	// atualiza a visualização da barra horizontal
	if (bNeedHScroll)
	{
		SetScrollRange (SB_HORZ, 0, szFlowArea.cx - (szControl.cx - nVScroll), TRUE);
		if (!bHScroll)
		{
			SetScrollPos (SB_HORZ, 0, TRUE);
			EnableScrollBar (SB_HORZ);
		}
	}
	else
	{
		if (bHScroll)
		{
			if (ptoFlowPos.x)
				bPaint = true;
			SetScrollPos (SB_HORZ, 0, TRUE);
			EnableScrollBar (SB_HORZ, ESB_DISABLE_BOTH);
		}
		ptoFlowPos.x = 0;
	}

	// corrige as variáveis e repinta (se necessário)
	bVScroll = bNeedVScroll;
	bHScroll = bNeedHScroll;
	if (bPaint)
	{
		CDC *pDC = GetDC ();
		PaintControl (pDC);
		ReleaseDC (pDC);
	}
}


void CFlowgram::SetMode (bool bRunning)
{
	// SetMode - muda o modo atual
	this->bRunning = bRunning;
	ptoFlowPos.x = ptoFlowPos.y = 0;
	SetScrollPos (SB_VERT, 0);
	SetScrollPos (SB_HORZ, 0);
	pActiveItem = NULL;

	CDC *pDC = GetDC ();
	PaintControl (pDC);
	ReleaseDC (pDC);
}


void CFlowgram::SelectItem (FLOWCHART_ITEM *pItem)
{
	// SelectItem - seleciona um item
	POINT ptoCenterPto;
	RECT rRect;
	GetClientRect (&rRect);

	// verifica se está na tela
	if ((pItem->rPos.left >= 0) && (pItem->rPos.right <= (rRect.right - rRect.left)) &&
		(pItem->rPos.top >= 0) && (pItem->rPos.bottom <= (rRect.bottom - rRect.top)))
	{
		pActiveItem = pItem;
		CDC *pDC = GetDC ();
		PaintControl (pDC);
		ReleaseDC (pDC);
		return;
	}

	// calcula o ponto central
	ptoCenterPto.x = ((rRect.right - rRect.left) / 2) - ((pItem->rPos.right - pItem->rPos.left) / 2);
	ptoCenterPto.y = ((rRect.bottom - rRect.top) / 2) - ((pItem->rPos.bottom - pItem->rPos.top) / 2);

	// calcula o deslocamento horizontal
	if (pItem->rPos.left < 0)
		ptoFlowPos.x += ptoCenterPto.x - pItem->rPos.left;
	else if (pItem->rPos.right > (rRect.right - rRect.left))
	{
		ptoFlowPos.x -= (pItem->rPos.right - (rRect.right - rRect.left));
		ptoFlowPos.x -= (pItem->nLeft + ptoFlowPos.x) - ptoCenterPto.x;
	}

	// calcula o deslocamento horizontal
	if (pItem->rPos.top < 0)
		ptoFlowPos.y += ptoCenterPto.y - pItem->rPos.top;
	else if (pItem->rPos.bottom > (rRect.bottom - rRect.top))
	{
		ptoFlowPos.y -= pItem->rPos.bottom - (rRect.bottom - rRect.top);
		ptoFlowPos.y -= (pItem->nTop + ptoFlowPos.y) - ptoCenterPto.y;
	}

	// atualiza o item selecionado
	pActiveItem = pItem;

	// desloca a tela
	SetScrollPos (SB_HORZ, -ptoFlowPos.x);
	SetScrollPos (SB_VERT, -ptoFlowPos.y);

	// repinta o controle
	CDC *pDC = GetDC ();
	PaintControl (pDC);
	ReleaseDC (pDC);
}