
// CubeView.h : CCubeView 类的接口
//

#pragma once
#include "P3.h"
#include "P2.h"
#include "Facet.h"
#include "Transform.h"
#include "Pi2.h"
#include "Fill.h"
#include "Triangle.h"

class CCubeView : public CView
{
protected: // 仅从序列化创建
	CCubeView();
	DECLARE_DYNCREATE(CCubeView)

// 特性
public:
	CCubeDoc* GetDocument() const;

// 操作
public:
	void ReadPoint();
	void ReadFace();
	void DrawObject(CDC*);
	void InitParameter();//参数初始化
	void PerProject(CP3);//透视投影
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
	virtual ~CCubeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CP3 P[8];//点表
	CP3 ViewPoint;//视点球坐标
	CP2 ScreenP;//屏幕坐标系的二维坐标点
	CFacet F[6];//面表
	double k[9];//运算常量
	double Alpha,Beta;//绕x轴旋转角α，绕y轴旋转角β
	double R,Theta,Phi,d;//R,Theta,Phi视点在用户坐标系的球坐标,d视距
	BOOL bPlay;//动画开关
	Transform tran;//变换对象

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void On32772();
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // CubeView.cpp 中的调试版本
inline CCubeDoc* CCubeView::GetDocument() const
   { return reinterpret_cast<CCubeDoc*>(m_pDocument); }
#endif

