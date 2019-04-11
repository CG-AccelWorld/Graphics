#pragma once
#include"P2.h"
#include"Point2.h"
#include "P3.h"
#include "Vector3.h"
#include "Lighting.h"

class CZBuffer
{
public:
	CZBuffer(void);
	virtual ~CZBuffer(void);
	void SetPoint(CPi3 P0,CPi3 P1,CPi3 P2,CVector3 N0,CVector3 N1,CVector3 N2);//三角形初始化
	void PhongShading(CDC* pDC,CP3 ViewPoint,CLighting* pLight,CMaterial* pMaterial,BOOL Sign);//Phong明暗处理填充三角形
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//为边做标记
	void InitDeepBuffer(int,int,double);//初始化深度缓冲器
	CRGB LinearInterpolation (double t, double tStart, double tEnd, CRGB intensityStart, CRGB intensityEnd);//光强线性插值
	CVector3 LinearInterpolation (double t, double tStart, double tEnd, CVector3 vStart, CVector3 vEnd);//法矢量线性插值
	void SortVertex();//顶点排序
public:
	CPoint2 point0, point1, point2;//三角形的整数顶点坐标
	CPi3 V0, V1, V2;//三角形的浮点数顶点坐标
	CPoint2* pLeft; //跨度的起点数组标志
	CPoint2* pRight;//跨度的终点数组标志
	int nIndex;//记录扫描线条数
	double **zBuffer;//缓深度冲区
	int Width,Height;//缓冲区参数
};

