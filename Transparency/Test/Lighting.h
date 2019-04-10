#pragma once
#include "LightSource.h"
#include "Material.h"
#include "Vector3.h"

class CLighting
{
public:
	CLighting(void);
	CLighting(int LightNumber);
	virtual ~CLighting(void);
	void SetLightNumber(int Number);//设置光源数量
	CRGBA illuminate(CP3 ViewPoint, CP3 Point, CVector3 Normal, CMaterial* pMaterial);//计算光照	
public:
	int Number;//光源数量
	CLightSource* LightSource;//光源数组
	CRGBA Ambient;//环境光
};