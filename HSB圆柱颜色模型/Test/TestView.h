
// TestView.h : CTestView 类的接口
//

#pragma once
#include "Face.h"
#include "Transform.h"
#include "Fill.h"

class CTestView : public CView
{
protected: // 仅从序列化创建
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// 特性
public:
	CTestDoc* GetDocument() const;

// 操作
public:
	void ReadVertex();//读入点表
	void ReadFace();//读入面表
	void InitParameter();//参数初始化
	void PerProject(CP3);//透视投影
	void DoubleBuffer(CDC *pDC);//双缓冲绘图
	void DrawObject(CDC *);//绘制物体
	void CalVertexColor();//计算各点的光照颜色
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
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CP3 *V;//点表
	CFace **F;//面表
	int N1,N2;//N1为周向网格,N2纵向网格
	double R,Theta,Phi,d;//R,Theta,Phi视点在用户坐标系的球坐标,d视距
	double k[9];//运算常量
	CP3 ViewPoint;//视点球坐标
	CPi2 ScreenP;//屏幕坐标系的二维坐标点
	//BOOL bPlay;//动画开关
	double Alpha,Beta;//x方向旋转α角,y方向旋转β角
	CTransform tran;//变换对象
	double h;//圆柱高度
	double r;//圆柱半径
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	virtual void OnInitialUpdate();
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // TestView.cpp 中的调试版本
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

