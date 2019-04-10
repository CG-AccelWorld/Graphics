
// TestView.h : CTestView 类的接口
//

#pragma once

#include "Face.h"
#include "Vector.h"
#include "ZBuffer.h"
#include "Lighting.h"
#include "Transform.h"
#include "BezierObject.h"
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
	void ReadNormal();//读入法向量
	void BiLinear_BMP(COLORREF **,int,int,COLORREF **,int,int);//双线性插值
	void InitParameter();//参数初始化
	void PerProject(CP3);//透视投影
	void DoubleBuffer(CDC *pDC);//双缓冲绘图
	void DrawObject(CDC *);//绘制立方体表面
// 重写
public:
	void Diamond();//绘制金刚石图案函数
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
	CP3 V[8];//点表
	CFace F[6];//面表
	double R,Theta,Phi;//视点在用户坐标系中的球坐标
	double d;//视距
	double Near,Far;//远近剪切面
	double k[9];//运算常量
	CP3 ViewPoint;//视点球坐标
	CPi3 ScreenP;//屏幕坐标系的三维坐标点
	double Alpha,Beta;//x方向旋转α角,y方向旋转β角
	int LightNum;//光源数量
	CLighting *pLight;//光照环境
	CMaterial *pMaterial;//物体材质
	BOOL bPlay;//动画开关
	CTransform tran;//变换对象
	CP3 **P;
	int NumObject;
	CBezierObject DrawBezier;
	CVector **N;//法向量的二维数组
	COLORREF **Image,**LImage;//二维动态数组
	BITMAP bmp;//BITMAP结构体变量
	BYTE *im;
	int nWidth,nHeight;//图像的宽度和高度
	double h;//圆柱高度
	double r;//圆柱半径

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDrawpic();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnPlay();
	afx_msg void OnUpdatePlay(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // TestView.cpp 中的调试版本
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

