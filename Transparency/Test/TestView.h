
// TestView.h : interface of the CTestView class
//

#pragma once
#include "Facet.h"
#include "Vector3.h"
#include "Lighting.h"
#include "Triangle.h"

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
	public:
	void DoubleBuffer(CDC *pDC);//双缓冲
	void ReadControlVertex(void);//读入顶点表
	void ReadFacet(void);//读入面表
	void LeftMultiMatrix(double M0[][4],CP3 P0[][4],int p,int f); //左乘矩阵
	void RightMultiMatrix(CP3 P0[][4],double M1[][4],int p,int f);//右乘矩阵
	void TransposeMatrix(double M0[][4]);//矩阵转置
	void InitialParameter(void);//变换参数
	void Perspect(); //透视
	CP3 PerspectiveProject(CP3 WorldPoint);//透视投影
	void DrawGround(CDC *pDC);//绘制物体底部灰色平面
	void Bezier();//绘制Bezier曲面
	void DrawGraph(CDC *pDC);//绘图
public:
	double R, Psi,Phi;//视点在用户坐标系中的球坐标
	double d;//视距
	double k[8];
	CP3 ViewPoint;//视点球坐标位置	
	CTriangle* pFill; //三角形填充
	int LightSourceNumer;//光源数量
	CLighting* pLight;//光照环境
	CMaterial* pMaterial;//物体材质
public:
	double MT[4][4];//M的转置矩阵
	CFacet F[100];
	CP3 ControlP[3][4][4][4];
	CP3 ObjectP[3][4][121];
	int part;//物体有几部分
	int face;//每部分有几个面
	BOOL bPlay;//动画开关
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

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGraphDraw();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateGraphDraw(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

