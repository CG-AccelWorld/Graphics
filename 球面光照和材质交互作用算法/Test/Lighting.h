#pragma once
#include "Light.h"
#include "Material.h"
#include "Vector.h"

class CLighting
{
public:
	CLighting(void);
	CLighting(int);
	~CLighting(void);
	void SetLightNumber(int);  //设置光源数量
	CRGB Lighting(CP3,CP3,CVector,CMaterial *);  //计算光照
public:
	int LightNum;   //光源数量
	CLight *Light;  //光源数组
	CRGB Ambient;   //环境光
};

