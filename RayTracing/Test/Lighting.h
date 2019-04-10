#pragma once
#include "Vector.h"
#include "Light.h"
#include "Material.h"
#include "Ray.h"
class CLighting
{
public:
	CLighting();
	CLighting(int);
	virtual ~CLighting();
	void SetLightNumber(int);//设置光源数量
	CRGB Lighting(CP3,CP3,CVector,CMaterial *,int i);//计算光照	
public:
	int LightNum;//光源数量
	CLight *Light;//光源数组
	CRGB Ambient;//环境光
};

