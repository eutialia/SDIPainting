
// SDIPaintingView.cpp : implementation of the CSDIPaintingView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SDIPainting.h"
#endif

#include "SDIPaintingDoc.h"
#include "SDIPaintingView.h"
#include "DDA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIPaintingView

IMPLEMENT_DYNCREATE(CSDIPaintingView, CView)

BEGIN_MESSAGE_MAP(CSDIPaintingView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAWING_DDA, &CSDIPaintingView::OnDrawingDda)
END_MESSAGE_MAP()

// CSDIPaintingView construction/destruction

CSDIPaintingView::CSDIPaintingView()
{
	// TODO: add construction code here

}

CSDIPaintingView::~CSDIPaintingView()
{
}

BOOL CSDIPaintingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSDIPaintingView drawing

void CSDIPaintingView::OnDraw(CDC* /*pDC*/)
{
	CSDIPaintingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CSDIPaintingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSDIPaintingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSDIPaintingView diagnostics

#ifdef _DEBUG
void CSDIPaintingView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIPaintingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIPaintingDoc* CSDIPaintingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIPaintingDoc)));
	return (CSDIPaintingDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIPaintingView message handlers


void CSDIPaintingView::OnDrawingDda()
{
	// TODO: Add your command handler code here

	CDDA drawDDA;
	if (drawDDA.DoModal() == IDOK) {
		CClientDC dc(this);
		DDA_dx = abs(drawDDA.DDA_x2 - drawDDA.DDA_x1);
		DDA_dy = abs(drawDDA.DDA_y2 - drawDDA.DDA_y1);

		if (DDA_dx >= DDA_dy) {
			step = DDA_dx;
		}
		else {
			step = DDA_dy;
		}

		DDA_dx = DDA_dx / step;
		DDA_dy = DDA_dy / step;

		DDA_initx = drawDDA.DDA_x1;
		DDA_inity = drawDDA.DDA_y1;

		for (int i = 1; i <= step; i++)
		{
			dc.SetPixel(DDA_initx, DDA_inity, RGB(0, 0, 0));
			DDA_initx = DDA_initx + DDA_dx;
			DDA_inity = DDA_inity + DDA_dy;
		}
	}
}
