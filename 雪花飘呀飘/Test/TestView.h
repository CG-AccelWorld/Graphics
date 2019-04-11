
// TestView.h : interface of the CTestView class
//

#pragma once
#include "Particle.h"

class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument() const;

// Operations
public:
	void GetMapStartX();
	void DrawObject();
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//英雄结构体
	struct shero
	{
		CImage hero;     //保存英雄的图像
		int x;             //保存英雄的位置
		int y;
		int direct;        //英雄的方向
		int frame;         //运动到第几张图片
	}MyHero;

	CParticle *m_snow;
	int m_xMapStart;     //x方向上地图的起始点
	int m_mapWidth;      //背景地图的宽度

	CRect rect;    //保存客户区大小
	CDC memDC;   //缓冲DC
	CBitmap memBitmap;//缓冲位图
	CImage m_bg;      //背景图片

	BOOL bFlag;//动画开关
	BOOL bPlay;//音乐开关
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGraphDraw();
	afx_msg void OnUpdateGraphDraw(CCmdUI *pCmdUI);
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnAppPlay();
	afx_msg void OnMusicPlay();
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

