#pragma once
#include "Pi2.h"

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
	CAET   *pNext;
};

