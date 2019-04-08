
// TestView.h : CTestView 类的接口
//
#include"Transform3.h"
#pragma once
#include"BicubicBezierPatch.h"
#include"Revolution.h"
#include "Facet.h"
#include "ZBuffer.h"
class CTestView : public CView
{
protected: // 仅从序列化创建
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// 特性
public:
	CTestDoc* GetDocument() const;
	void DoubleBuffer(CDC* pDC);//双缓冲
	void DrawGraph1(CDC* pDC);
	void InitParameter();//变换参数
	void PerProject(CP3);//透视投影
	void ReadFace();//读入面表
	void DrawObject(CDC *,CZBuffer *);//绘制物体
	void ReadCubeVertex();//读入立方体顶点
	void ReadCubeFace();//读入立方体表面
	void DrawCube(CDC *,CZBuffer *);//绘制立方体
// 操作
public:
 void	DrawGraph(CDC*pDC);
 void ReadPoint();
private:
	CP3 P[4];CP3 P1[4];CP3 P2[4],P3[3];
	double Alpha,Beta;
	Transform3 tran;
	Transform3 tran1;
	Transform3 tran2;
	Transform3 tran3;
	Transform3 tran4;
	CRevolution pdd; 
	CRevolution pdd1; 
	CRevolution pdd2; 
	CRevolution pdd3; 
	Facet F[100];
	double R,Theta,Phi;//视点在用户坐标系中的球坐标
	double d;//视距
	double Near,Far;//远近剪切面
	double k[9];
	CP3 N0[4][121],N1[4][121],N2[4][121];
	CVector Nv0[4][121],Nv1[4][121],Nv2[4][121];
	CP3 ViewPoint;//视点球坐标位置
	CPi3 ScreenP;//屏幕坐标系的三维坐标点
	int	 LightNum;//光源数量
	CLighting *pLight;//光照环境
	CMaterial *pMaterial;//物体材质
	CZBuffer *pFill;
	CP3 BN[12][12];
	CP3 CN[144];
	Facet FC[121];
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

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // TestView.cpp 中的调试版本
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

