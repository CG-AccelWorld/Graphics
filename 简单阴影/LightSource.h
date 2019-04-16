#pragma once
#include "P3.h"

class CLightSource  //光源类
{
public:
	CLightSource();
	virtual ~CLightSource();
	void SetDiffuse(CRGB diffuse);//设置光源的漫反射光
	void SetSpecular(CRGB specular);//设置光源的镜面反射光
	void SetPosition(double x, double y, double z);//设置光源的直角坐标位置
	void SetGlobal(double r, double phi, double theta);//设置光源的球坐标位置
	void SetCoefficient(double c0, double c1, double c2);//设置光强的衰减系数
	void SetOnOff(BOOL);//设置光源开关状态	
	void GlobalToXYZ();//球坐标转换为直角坐标	
public:
	CRGB L_Diffuse;//光的漫反射颜色	
	CRGB L_Specular;//光的镜面高光颜色
	CP3  L_Position;//光源的位置
	double L_R,L_Phi,L_Theta;//光源球坐标
	double L_C0;//常数衰减系数
	double L_C1;//线性衰减系数
	double L_C2;//二次衰减系数
	BOOL L_OnOff;//光源开关
};

