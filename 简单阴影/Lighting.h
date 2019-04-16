#pragma once
#include "Vector.h"
#include "Material.h"
#include "LightSource.h"

class CLighting  //光照类
{
public:
	CLighting();
	CLighting(int );
	virtual ~CLighting();
	void SetLightNumber(int LightNumber);//设置光源数量		
	CRGB Lighting(CP3 ViewPoint, CP3 Point, CVector Normal, CMaterial* pMaterial);//光照	
public:
	int LightNumber;//光源数量
	CLightSource* LightSource;//光源数组
	CRGB Ambient;//环境光
};

