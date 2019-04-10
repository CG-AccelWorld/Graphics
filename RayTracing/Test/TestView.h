
// TestView.h : CTestView 类的接口
//

#pragma once
#include "Sphere.h"
#include "ZBuffer.h"
#include "Lighting.h"
#include "Material.h"
#include "Projection.h"
#include "Plane.h"

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
	void DoubleBuffer(CDC* pDC);//双缓冲
	void DrawObject(CDC* pDC);//绘制球面

    CRay CalculateReflection(CRay in, CInterPoint hit); //已知入射光线 和交点 求反射 光线
    CRGB Shade(CRay ray, CInterPoint  hit, int count);//此条光线矢量  交点 递归次数
    CRGB Trace(CRay ray, int count); // 从视点 发出的 第一条 矢量  、 递归次数
    CRay CalculateRefraction(CRay in, CInterPoint hit);

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
	int	 LightNum;//光源数量
	CLighting *pLight;//光照环境
	CMaterial pMaterial[4];//物体材质
    CProjection  projection;
	int Width;
	int Height;
	CP3 ViewPoint;
	CPrimitive *objects[5];
	int nObjectCount;
	CP3 Positionlight[2];
	int nLightCount;
	CP3 ppppp;
	bool is_pppp;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TestView.cpp 中的调试版本
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

