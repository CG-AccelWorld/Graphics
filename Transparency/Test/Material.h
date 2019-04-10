#pragma once
#include "RGBA.h"

class CMaterial
{
public:
	CMaterial(void);
	virtual~CMaterial(void);
	void SetAmbient(CRGBA c);//设置材质对环境光的反射率	
	void SetDiffuse(CRGBA c);//设置材质对漫反射光的反射率ic:
	void SetSpecular(CRGBA c);//设置材质对镜面反射光的反射率CRGB M_Ambient;//材质对环境光的反射率
	void SetEmit(CRGBA);//设置材质自身辐射的颜色
	void SetSlope(double k);//设置材质的微平面斜率
	void SetFresnel(double f);//设置材质的Fresnel反射系数
public:
	CRGBA M_Ambient;//材质对环境光的反射率
	CRGBA M_Diffuse;//材质对漫反射光的反射率
	CRGBA M_Specular;//材质对镜面反射光的反射率
	CRGBA M_Emit;//材质自身辐射的颜色
	double M_k;//材质的微平面斜率
	double M_f;//Fresnel反射系数
	double M_n;//材质的高光指数
};