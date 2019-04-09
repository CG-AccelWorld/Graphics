
// CutView.h : CCutView 类的接口
//

#pragma once
#include "P2.h"

class CCutView : public CView
{
protected: // 仅从序列化创建
	CCutView();
	DECLARE_DYNCREATE(CCutView)

// 特性
public:
	CCutDoc* GetDocument() const;

// 操作
public:
	void DoubleBuffer(CDC *pDC);//双缓冲
	void DrawWindowRect(CDC *);//绘制裁剪窗口
	void Cohen();//裁剪函数
	void EnCode(CP2 &);//编码函数
	CP2  Convert(CPoint point);//坐标系转换
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
	virtual ~CCutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int wxl,wxr;//窗口矩形x坐标
	int wyb,wyt;//窗口矩形y坐标
	BOOL bDrawLine;//是否允许画线
	CP2 P[2];//直线的起点和终点
	int PtCount;//顶点个数
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOndrawpic();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClip();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // CutView.cpp 中的调试版本
inline CCutDoc* CCutView::GetDocument() const
   { return reinterpret_cast<CCutDoc*>(m_pDocument); }
#endif

