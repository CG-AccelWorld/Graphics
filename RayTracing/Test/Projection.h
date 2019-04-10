#pragma once
/*
	透视投影类
*/

#include "P3.h"
#include "Pi3.h"
class CProjection  
{
public:
	CProjection(void);
	~CProjection(void);
	void InitalParameter();
	CP2 PerspectiveProjection(CP3 WorldP);//二维透视投影
	CP2 OrthogonalProjection(CP3 WorldP);//正交投影
	CP2 CavalierProjection(CP3 WorldP);//斜等测投影
	CP2 CabinetProjection(CP3 WorldP);//斜二测投影
	CPi3 PerspectiveProjection3(CP3 WorldP);//三维透视投影
public:
	double k[9];//透视投影常数
	double R, Theta, Phi, d;//视点在用户坐标系中的球坐标
	double Near, Far;//远近剪切面
	CP3 ViewPoint;
};

