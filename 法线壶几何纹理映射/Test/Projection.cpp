#include "StdAfx.h"
#include "Projection.h"
#include "math.h"
#define PI 3.1415926
#define Round(d) int(floor(d+0.5))//四舍五入宏定义


CProjection::CProjection()
{
		Near=800.0,Far=1200.0;//近剪切面与远剪切面
}

CProjection::~CProjection()
{

}


CP3 CProjection::InitalParameter()//透视变换参数初始化
{
	R = 1200, d = 800, Phi = 90.0, Theta = 0.0;
	k[1] = sin(PI * Theta /180);
	k[2] = sin(PI * Phi / 180);
	k[3] = cos(PI * Theta / 180);
	k[4] = cos(PI * Phi / 180);
	k[5] = k[2] * k[3];
	k[6] = k[2] * k[1];
	k[7] = k[4] * k[3];
	k[8] = k[4] * k[1];
	CP3 ViewPoint;
	ViewPoint.x=R*k[6];
	ViewPoint.y=R*k[4];
	ViewPoint.z=R*k[5];
	return ViewPoint;
}

CPi3 CProjection::PerspectiveProjection(CP3 WorldP)//透视投影
{
	InitalParameter();
	CP3 ViewP;//观察坐标系三维坐标
	ViewP.x =  WorldP.x * k[3] - WorldP.z * k[1];
	ViewP.y = -WorldP.x * k[8] + WorldP.y * k[2] - WorldP.z * k[7];
	ViewP.z = -WorldP.x * k[6] - WorldP.y * k[4] - WorldP.z * k[5] + R;
	CPi3 ScreenP;//屏幕二维坐标系
	ScreenP.x = d * ViewP.x / ViewP.z;
	ScreenP.y = Round(d * ViewP.y / ViewP.z);
	ScreenP.z = Far*(1-Near/ViewP.z)/(Far-Near);
	return ScreenP;
}

CP2 CProjection::OrthogonalProjection(CP3 WorldP)//正交投影
{
	CP2 ScreenP;
    ScreenP.x = WorldP.x;
	ScreenP.y = WorldP.y;
	return ScreenP;
}

CP2 CProjection::CavalierProjection(CP3 WorldP)//斜等测投影
{
	CP2 ScreenP;
	double Alpha = 45 * PI / 180;
    ScreenP.x = WorldP.x - WorldP.z * cos(Alpha);
	ScreenP.y = WorldP.y - WorldP.z * cos(Alpha);
	return ScreenP;
}

CP2 CProjection::CabinetProjection(CP3 WorldP)//斜二测投影
{
	CP2 ScreenP;
	double Alpha = 45 * PI / 180;
    ScreenP.x = WorldP.x - WorldP.z / 2 * cos(Alpha);
	ScreenP.y = WorldP.y - WorldP.z / 2 * cos(Alpha);
	return ScreenP;
}
