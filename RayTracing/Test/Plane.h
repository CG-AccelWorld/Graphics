#pragma once
/*
	面片类
	属性：
		面的法矢量
		面的D
		面的x，y，z，的取值范围
*/
#include "primitive.h"

class CPlane :
	public CPrimitive
{
public:
	CPlane(void);
	~CPlane(void);
	CPlane(double r, CP3 positionP,CMaterial pMaterial,double,double ,double ,double ,double ,double );
    bool GetInterPoint(CRay Ray,CInterPoint &InPoint); //获取 直线 与 面片的交点
public:
	double X_min,X_max;
	double Y_min,Y_max;
	double Z_min,Z_max;
};

