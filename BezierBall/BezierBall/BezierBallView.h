
// BezierBallView.h : CBezierBallView 类的接口
//

#pragma once
#include "P3.h"
#include "Bezier.h"
#include "Transform.h"

class CBezierBallView : public CView
{
protected: // 仅从序列化创建
	CBezierBallView();
	DECLARE_DYNCREATE(CBezierBallView)

// 特性
public:
	CBezierBallDoc* GetDocument() const;

// 操作
public:
	void ReadPoint();
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
	virtual ~CBezierBallView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CP3 Q1[4][4],Q2[4][4],Q3[4][4],Q4[4][4],Q5[4][4],Q6[4][4],Q7[4][4],Q8[4][4];
	//CP3 V1[4][4],V2[4][4],V3[4][4],V4[4][4],V5[4][4],V6[4][4],V7[4][4],V8[4][4];
	CP3 P1[16],P2[16],P3[16],P4[16],P5[16],P6[16],P7[16],P8[16];//点表
	double Alpha,Beta;//绕x轴旋转角α，绕y轴旋转角β
	Transform tran;
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // BezierBallView.cpp 中的调试版本
inline CBezierBallDoc* CBezierBallView::GetDocument() const
   { return reinterpret_cast<CBezierBallDoc*>(m_pDocument); }
#endif

