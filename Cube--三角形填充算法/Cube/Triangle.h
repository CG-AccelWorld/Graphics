#pragma once
#include "P2.h"
#include "Point2.h"

class CTriangle
{
public:
	CTriangle(void);
	CTriangle(CP2 P0, CP2 P1, CP2 P2);//浮点数构造三角形
	~CTriangle(void);
	void Gouraud(CDC* pDC);//填充三角形
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//为边做标记
	CRGB ClrInterpolation(double t, double mStart, double mEnd, CRGB cStart, CRGB cEnd);//颜色线性插值
	void SortVertex();//顶点排序
public:
	CPoint2 point0, point1, point2;//三角形的整数顶点坐标
	CPoint2* pLeft; //跨度的起点数组标志
	CPoint2* pRight;//跨度的终点数组标志
	int nIndex;//记录扫描线条数
};

