#pragma once
/*
	物体类
	属性:
		物体的位置
		物体的材质
*/
#include "P3.h"
#include"InterPoint.h"
#include"Material.h"
#include"Ray.h"
class CPrimitive
{
public:
	CPrimitive(void);
	CPrimitive(double r, CP3 positionP,CMaterial pMaterial);
	~CPrimitive(void);
	virtual bool GetInterPoint(CRay Ray,CInterPoint &InPoint); //获取 直线 与 物体的交点 
public:
	CP3 positionP;//在球方程中当做球心，在面方程中当做法向量
	double r;//在球方程中当做半径，在面方程中当做D
	CMaterial pMaterial;//每个物体的材质
};

