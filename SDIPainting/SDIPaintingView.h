
// SDIPaintingView.h : interface of the CSDIPaintingView class
//

#pragma once


class CSDIPaintingView : public CView
{
protected: // create from serialization only
	CSDIPaintingView();
	DECLARE_DYNCREATE(CSDIPaintingView)

// Attributes
public:
	CSDIPaintingDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CSDIPaintingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawingDda();
private:
	int DDA_dx, DDA_dy, steep, DDA_initx, DDA_inity;//DDA
private:
	int MPL_dx, MPL_dy, p, MPL_initx, MPL_inity;//Mid-Point Line
private:
	int MPC_initx, MPC_inity, err;//Mid-Point Circle
public:
	afx_msg void OnDrawingMpl();
	afx_msg void OnDrawingMpc();
	afx_msg void OnDrawingSlf();
	void ScanLineFill(CDC * pDC, int x, int y, COLORREF oldColor, COLORREF newColor);
	afx_msg void OnDrawingSf();
	void FloodFill(CDC * pDC, int x, int y, COLORREF colorOld, COLORREF colorNew);
};

#ifndef _DEBUG  // debug version in SDIPaintingView.cpp
inline CSDIPaintingDoc* CSDIPaintingView::GetDocument() const
   { return reinterpret_cast<CSDIPaintingDoc*>(m_pDocument); }
#endif

