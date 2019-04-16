#pragma once
#include"P2.h"
#include"Point2.h"
#include "P3.h"
#include "Vector.h"

class CZBuffer
{
public:
	CZBuffer(void);
	~CZBuffer(void);
	void SetPoint(CP3 P0, CP3 P1, CP3 P2);
	void Gouraud(CDC* pDC);//填充三角形
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//为边做标记
	void InitDeepBuffer(int,int,double);//初始化深度缓冲器
	CRGB ClrInterpolation(double t, double mStart, double mEnd, CRGB cStart, CRGB cEnd);//颜色线性插值
	void SortVertex();//顶点排序
public:
	CPoint2 point0, point1, point2;//三角形的整数顶点坐标
	CPoint2* pLeft; //跨度的起点数组标志
	CPoint2* pRight;//跨度的终点数组标志
	int nIndex;//记录扫描线条数
	double **zBuffer;//缓深度冲区
	int Width,Height;//缓冲区参数
};

