#pragma once
/*
	光线类
	属性:
		光线的起点坐标
		光线的矢量
*/


#include"Vector.h"
#include"RGB.h"
class CRay  
{
public:
	CRay();
	virtual ~CRay();
    CRay::CRay(CP3 origin, CVector dir);//获取光线的起始点和单位化方向矢量
    CP3 GetPoint(double t);//获取光线与物体的交点
	void Normalized();//单位化光线
public:
	double alpha;//光线所处的折射率+
    CP3 origin; //光线的起点
	CVector dir;   //光线的方向
};

