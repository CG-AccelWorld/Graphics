#include "stdafx.h"
#include "Projection.h"
#include "math.h"
#define PI 3.1415926
#define Round(d) int(floor(d+0.5))

CProjection::CProjection()
{
	R = 600, d = 800, Phi =90.0, Theta = 0.0;//视点位于正前方
	Near = d, Far = 2000.0;//近剪切面与远剪切面
	InitalParameter();
}

CProjection::~CProjection()
{

}

void CProjection::InitalParameter()//透视变换参数初始化
{	
	k[1]=sin(PI*Theta/180);
	k[2]=sin(PI*Phi/180);
	k[3]=cos(PI*Theta/180);
	k[4]=cos(PI*Phi/180);
	k[5]=k[2]*k[3];
	k[6]=k[2]*k[1];
	k[7]=k[4]*k[3];
	k[8]=k[4]*k[1];	
	ViewPoint.x=R*k[6];
	ViewPoint.y=R*k[4];
	ViewPoint.z=R*k[5];
}

CP2 CProjection::PerspectiveProjection(CP3 WorldP)//透视投影
{
	CP3 ViewP;//观察坐标系三维坐标
	ViewP.x =  WorldP.x * k[3] - WorldP.z * k[1];
	ViewP.y = -WorldP.x * k[8] + WorldP.y * k[2] - WorldP.z * k[7];
	ViewP.z = -WorldP.x * k[6] - WorldP.y * k[4] - WorldP.z * k[5] + R;
	CP3 ScreenP;//屏幕二维坐标系
	ScreenP.x = d * ViewP.x / ViewP.z;
	ScreenP.y = Round(d * ViewP.y / ViewP.z);
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

CPi3 CProjection::PerspectiveProjection3(CP3 WorldP)//三维透视投影变换
{
	CP3 ViewP;//观察坐标系三维坐标
	ViewP.x =  WorldP.x * k[3] - WorldP.z * k[1];
	ViewP.y = -WorldP.x * k[8] + WorldP.y * k[2] - WorldP.z * k[7];
	ViewP.z = -WorldP.x * k[6] - WorldP.y * k[4] - WorldP.z * k[5] + R;
	ViewP.c =  WorldP.c;
	CPi3 ScreenP;
	ScreenP.x = d * ViewP.x / ViewP.z;//屏幕坐标系三维坐标
	ScreenP.y = Round(d * ViewP.y / ViewP.z);
	ScreenP.z = Far * (1 - Near / ViewP.z) / (Far - Near);
	ScreenP.c = ViewP.c;
	return ScreenP;
}