
// TCubeView.h : CTCubeView 类的接口
//

#pragma once
#include "P3.h"
#include "Face.h"
#include "Transform.h"


class CTCubeView : public CView
{
protected: // 仅从序列化创建
	CTCubeView();
	DECLARE_DYNCREATE(CTCubeView)

// 特性
public:
	CTCubeDoc* GetDocument() const;

// 操作
public:
	void ReadPoint();//读入顶点表
	void ReadFace();//读入表面表
	void ObliqueProject(CP3);//斜等侧变换
	void DrawObject(CDC *);//绘制图形
	void DrawPolygon(CDC *);//绘制多边形
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTCubeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRect rect;//定义客户区
	CP3 P[8];
	CP2 ScreenP;
	CFace F[6];
	CTransform trans;
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTleft();
	afx_msg void OnTright();
	afx_msg void OnTup();
	afx_msg void OnTdown();
	afx_msg void OnTfront();
	afx_msg void OnTback();
	afx_msg void OnTbig();
	afx_msg void OnTsmall();
	afx_msg void OnRxaxis();
	afx_msg void OnRyaxis();
	afx_msg void OnRzaxis();
	afx_msg void OnRxoy();
	afx_msg void OnRyoz();
	afx_msg void OnRxoz();
	afx_msg void OnSxdirectionplus();
	afx_msg void OnSydirectionplus();
	afx_msg void OnSzdirectionneg();
	afx_msg void OnDrawpic();
	afx_msg void OnReset();
	afx_msg void OnAaa();
	afx_msg void OnBbb();
	afx_msg void OnCcc();
	afx_msg void OnDdd();
};

#ifndef _DEBUG  // TCubeView.cpp 中的调试版本
inline CTCubeDoc* CTCubeView::GetDocument() const
   { return reinterpret_cast<CTCubeDoc*>(m_pDocument); }
#endif

