
// TestView.h : CTestView 类的接口
//

#pragma once
#include "Pi2.h"
#include "Face.h"
#include "Vector.h"
#include "Lighting.h"
#include "Material.h"
#include "Transform.h"
#include "ZBuffer.h"

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
	void ReadVertex();//读入顶点表
	void ReadFace();//读入面表
	void InitParameter();//变换参数
	void PerProject(CP3);//透视投影
	void DoubleBuffer(CDC *pDC);//双缓冲
	void DrawObject(CDC *);//绘制球面
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
	double R,Theta,Phi;//视点在用户坐标系中的球坐标
	double d;//视距
	double Near,Far;//远近剪切面
	double k[9];
	CP3 ViewPoint;//视点球坐标位置
	CPi3 ScreenP;//屏幕坐标系的三维坐标点
	CP3 *V;//球的顶点一维数组
	CFace **F;//面的二维数组
	double Alpha,Beta;//x方向旋转α角,y方向旋转β角
	int N1,N2;//N1为纬度区域,N2为经度区域
	int	 LightNum;//光源数量
	CLighting *pLight;//光照环境
	CMaterial *pMaterial;//物体材质
	CTransform tran;//变换对象	
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // TestView.cpp 中的调试版本
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

