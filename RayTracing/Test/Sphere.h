#pragma once
/*
	球类
	属性:
		球的的球心
		球的半径
*/

#include "Primitive.h"
class CSphere:
	public CPrimitive
{
public:
	CSphere();
	virtual ~CSphere();
	CSphere(double r, CP3 positionP,CMaterial pMaterial);
    bool GetInterPoint(CRay Ray,CInterPoint &InPoint); //获取 直线 与 球的交点
};

