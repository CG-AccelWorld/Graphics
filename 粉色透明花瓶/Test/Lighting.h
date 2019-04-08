#pragma once
#include "Light.h"
#include "Material.h"
#include "Vector.h"
class CLighting
{
public:
	CLighting();
	CLighting(int);
	virtual ~CLighting();
	void SetLightNumber(int);//设置光源数量
	CRGB Lighting(CP3 ViewPoint, CP3 Point, CVector Normal, CMaterial *pMaterial,BOOL,CRGB InitC);
public:
	int LightNum;//光源数量
	CLight *Light;//光源数组
	CRGB Ambient;//环境光
	CRGB LastC;
};

