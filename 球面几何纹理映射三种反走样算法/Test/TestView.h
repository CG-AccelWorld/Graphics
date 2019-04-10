
// TestView.h : CTestView 类的接口
//

#pragma once

#include "Face.h"
#include "Vector.h"
#include "ZBuffer.h"
#include "Lighting.h"
#include "Transform.h"
#include "T2.h"
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
	void ReadVertex();//读入顶点坐标
	void ReadFace();//读入面坐标
	void ReadImage(int Sign);//读入颜色纹理
	void ReadBumpMap(int Sign);//读入凹凸纹理
	void BiLinear_BMP(COLORREF **,int,int,COLORREF **,int,int);//最邻近取样算法
	void BiLinear_BMP1(COLORREF **,int,int,COLORREF **,int,int);//双线性插值算法
	void BiInterpolation_BMP(COLORREF **,int,int,COLORREF **,int,int);//双三次插值算法
	double BiInterpolation(double);//双三次插值
	void InitParameter();//变换参数
	void PerProject(CP3);//透视投影
	void DoubleBuffer(CDC *pDC);//双缓冲
	void DrawObject(CDC *,int Sign);//绘制球面
	void Paint(CDC *);//绘制物体
	void ClearMemory();//清理内存
	void DrawPic(CDC *);//输出字符串
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
	UINT nScale;//放大镜比例
	CP2 nRCenter;//裁剪矩形的中心坐标
	double nRHHeight,nRHWidth;//裁剪矩形的半高度和半宽度
    double R,Theta,Phi;//视点在用户坐标系中的球坐标
	double d;//视距
	double Near,Far;//远近剪切面
	double k[9];//透视变换参数
	CP3 ViewPoint;//视点球坐标位置
	CPi3 ScreenP;//屏幕坐标系的三维坐标点
	CP3 *V;//圆柱顶点一维数组
	CT2 *T;//圆柱纹理一维数组
	CFace **F;//面的二维数组
	int N1,N2;//N1为经度区间,N2为纬度区间
	int gAlpha,gBeta;//纬度角与经度角
	int LightNum;//光源数量
	CLighting *pLight;//光照环境
	CMaterial *pMaterial;//物体材质
	BOOL bPlay;//动画开关
	CTransform tran;//变换对象
	double Alpha,Beta;//x方向旋转α角,y方向旋转β角
	COLORREF **Image1,**Image2,**LImage1,**LImage2;//二维动态数组
	BITMAP bmp1,bmp2;//BITMAP结构体变量
	BYTE *im;
	double **Imgx_Gradient,**Imgy_Gradient;
	int nWidth,nHeight;//图像的宽度和高度
	int r;//球体半径
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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // TestView.cpp 中的调试版本
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

