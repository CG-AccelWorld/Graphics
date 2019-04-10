#pragma once
#include "P3.h"

class CLightSource
{
public:
	CLightSource(void);
	virtual ~CLightSource(void);
	void SetDiffuse(CRGBA diffuse);//设置光源的漫反射光
	void SetSpecular(CRGBA specular);//设置光源的镜面反射光
	void SetPosition(double x, double y, double z);//设置光源的直角坐标位置
	void SetAttenuationFactor(double c0, double c1, double c2);//设置光强的衰减因子
	void SetOnOff(BOOL);//设置光源开关状态	
public:
	CRGBA L_Diffuse;//漫反射光颜色	
	CRGBA L_Specular;//镜面反射光颜色
	CP3 L_Position;//光源位置
	double L_C0;//常数衰减因子
	double L_C1;//线性衰减因子
	double L_C2;//二次衰减因子
	BOOL L_OnOff;//光源开启或关闭
};