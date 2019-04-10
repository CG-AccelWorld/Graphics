#pragma once
#include "P3.h"
#include "Pi3.h"
class CProjection  
{
public:
	CProjection();
	virtual ~CProjection();
	CP3 InitalParameter();
	CPi3 PerspectiveProjection(CP3 WorldP);//透视投影
	CP2 OrthogonalProjection(CP3 WorldP);//正交投影
	CP2 CavalierProjection(CP3 WorldP);//斜等测投影
	CP2 CabinetProjection(CP3 WorldP);//斜二测投影
private:
	double k[9];//透视投影常数
	double R, Theta, Phi, d;//视点在用户坐标系中的球坐标
		double	Near,Far;//近剪切面与远剪切面

};
