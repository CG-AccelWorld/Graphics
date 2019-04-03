
// DBezierView.h : CDBezierView 类的接口
//

#pragma once


class CDBezierView : public CView
{
protected: // 仅从序列化创建
	CDBezierView();
	DECLARE_DYNCREATE(CDBezierView)

// 特性
public:
	CDBezierDoc* GetDocument() const;

// 操作
public:
	void DrawPolygon(CDC *);//绘制多边形
	void DrawBezier(CDC *);//绘制Bezier函数
	void DrawPic(CDC *);
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
	virtual ~CDBezierView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPoint P[4];
	CPoint p[6];
	CPoint q[100];
	double t;
	int j;
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // DBezierView.cpp 中的调试版本
inline CDBezierDoc* CDBezierView::GetDocument() const
   { return reinterpret_cast<CDBezierDoc*>(m_pDocument); }
#endif

