
// NBzierView.h : CNBzierView 类的接口
//

#pragma once


class CNBzierView : public CView
{
protected: // 仅从序列化创建
	CNBzierView();
	DECLARE_DYNCREATE(CNBzierView)

// 特性
public:
	CNBzierDoc* GetDocument() const;

// 操作
public:
	void DrawCtrlPolygon();//绘制控制多边形函数
	long Fac(int);//阶乘函数
	double Cni(const int &,const int &);//Bernstein第一项
	void DrawBezier();//绘制Bezier函数
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
	virtual ~CNBzierView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL bFlag; //标志
	CPoint *P;//顶点
	int  CtrlPointNum;//控制多边形顶点个数
	int  n;//Bezier曲线的阶次
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawpic();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // NBzierView.cpp 中的调试版本
inline CNBzierDoc* CNBzierView::GetDocument() const
   { return reinterpret_cast<CNBzierDoc*>(m_pDocument); }
#endif

