#pragma once
#include "Vector.h"
class CAET
{
public:
	CAET(void);
	~CAET(void);
public:
	double  x;//当前扫描线与有效边交点的x坐标
	int     yMax;//边的最大y值
	double  k;//斜率的倒数(x的增量)
	CPi2    ps;//边的起点
	CPi2    pe;//边的终点
	CVector ns;//起点法矢量
	CVector ne;//终点法矢量
	double A;
	double B;
	CAET   *pNext;

};

