
// TestView.h : interface of the CTestView class
//

#pragma once
#include"Facet.h"
#include "Transform3.h"
#include "ZBuffer.h"
#include "Material.h"
#include "LightSource.h"
#include "Lighting.h"

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
	void ReadPoint();//读入点表
	void ReadFacet();//读入面表
	void InitialParameter();//参数初始化
	CP3 PerspectiveProjection(CP3 WorldP);//透视投影
	void DoubleBuffer(CDC* pDC);//双缓冲绘图
	void DrawGraph(CDC* pDC);//绘制立方体线框
	void DrawGround(CDC *pDC);
	CP3 CalculateCrossPoint(CP3 p0,CP3 p1);
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
	CP2 Point[3];
	CP3 P[8];//点表
	CFacet F[6];//面表
	CP3 Point1[4];
	double R,Theta,Phi,d;//R,Theta,Phi视点在用户坐标系的球坐标,d视距
	double k[9];//运算常量
	double Near,Far;
	CZBuffer *pZBuffer;
	CP3 ViewPoint;//视点球坐标
	CTransform3 transform;//变换对象
	double Alpha,Beta;//x方向旋转α角,y方向旋转β角
	int	 LightNumber;//光源数量
	CLighting* pLight;//光照环境
	CMaterial* pMaterial;//物体材质
	BOOL bPlay;//动画开关
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGraphDraw();
	afx_msg void OnUpdateGraphDraw(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

