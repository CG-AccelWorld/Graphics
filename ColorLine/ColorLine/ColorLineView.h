
// ColorLineView.h : CColorLineView 类的接口
//

#pragma once


class CColorLineView : public CView
{
protected: // 仅从序列化创建
	CColorLineView();
	DECLARE_DYNCREATE(CColorLineView)

// 特性
public:
	CColorLineDoc* GetDocument() const;

public:
   void DrawObject(CDC *);
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
	virtual ~CColorLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	double Theta,q;//旋转角
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // ColorLineView.cpp 中的调试版本
inline CColorLineDoc* CColorLineView::GetDocument() const
   { return reinterpret_cast<CColorLineDoc*>(m_pDocument); }
#endif

