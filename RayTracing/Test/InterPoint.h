#pragma once
/*
	光线与物体的交点类
	属性：
		参数t
		交点坐标
		交点的法矢量
		交点处的材质
*/
#include"Vector.h"
#include"Material.h"
class CInterPoint   
{
public:
	CInterPoint();
	virtual ~CInterPoint();

	double t;//万能参数T
	CP3 IntersectionPoint; // 直线与物体的交点坐标
    CVector Nformal;//交点的法矢量
	int type;
	CMaterial pMaterial;//交点处的材质
};

