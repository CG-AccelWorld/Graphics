#pragma once
#include "p2.h"
class CP3 :
	public CP2
{
public:
	CP3();
	virtual ~CP3();
	CP3(double x, double y, double z);
public:
	double z;
	double A;//曲面透明因子
};

