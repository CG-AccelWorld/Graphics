
// EetFillView.h : CEetFillView 类的接口
//

#pragma once
#include "P2.h"
#include "Pi2.h"


class CEetFillView : public CView
{
protected: // 仅从序列化创建
	CEetFillView();
	DECLARE_DYNCREATE(CEetFillView)

// 特性
public:
	CEetFillDoc* GetDocument() const;
// 操作
public:
	void Draw(CDC *);
	void ReadPoint();
	void FillPolygon(CDC *);//填充多边形
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
	virtual ~CEetFillView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPi2 P1[10];//y整数点表
	CPoint *Q,t;
	int Max,num;
	BOOL bFlag;
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawpolygon();
	afx_msg void OnFill();
};

#ifndef _DEBUG  // EetFillView.cpp 中的调试版本
inline CEetFillDoc* CEetFillView::GetDocument() const
   { return reinterpret_cast<CEetFillDoc*>(m_pDocument); }
#endif

