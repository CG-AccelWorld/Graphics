#include "StdAfx.h"
#include "Transform.h"
#include "math.h"
#define PI 3.1415926

Transform::Transform(void)
{
}


Transform::~Transform(void)
{
}
void Transform::SetMatrix(CP3* P, int ptNumber)//传入立方体顶点
{
	this->P = P;
	this->ptNumber = ptNumber;
}
void Transform::Identity() //初始矩阵
{
	T[0][0] = 1.0; T[0][1] = 0.0; T[0][2] = 0.0; T[0][3] = 0.0; 
	T[1][0] = 0.0; T[1][1] = 1.0; T[1][2] = 0.0; T[1][3] = 0.0;
	T[2][0] = 0.0; T[2][1] = 0.0; T[2][2] = 1.0; T[2][3] = 0.0;
	T[3][0] = 0.0; T[3][1] = 0.0; T[3][2] = 0.0; T[3][3] = 1.0;
}
void Transform::Translate(double tx, double ty, double tz)//平移矩阵
{
	Identity();
	T[3][0] = tx;
	T[3][1] = ty;
	T[3][2] = tz;
	MultiplyMatrix();
}
void Transform::RotateX(double beta)//绕x轴旋转矩阵
{
	Identity();
	double rad = beta*PI/180;
	T[1][1]=cos(rad);T[1][2]=sin(rad);
	T[2][1]=-sin(rad);T[2][2]=cos(rad);
	MultiplyMatrix();
}
void Transform::RotateY(double beta)//绕y轴旋转矩阵
{
	Identity();
	double rad = beta*PI/180;
	T[0][0]=cos(rad);T[0][2]=-sin(rad);
	T[2][0]=sin(rad);T[2][2]=cos(rad);
	MultiplyMatrix();
}
void Transform::MultiplyMatrix()//计算变换后的矩阵
{
	CP3* PTemp=new CP3[ptNumber];
	for(int i=0;i<ptNumber;i++)
		PTemp[i]=P[i];
	for(int j=0;j<ptNumber;j++)
	{
		P[j].x=T[0][0]*PTemp[j].x+T[0][1]*PTemp[j].y+T[0][2]*PTemp[j].z+T[0][3]*PTemp[j].w;
		P[j].y=T[1][0]*PTemp[j].x+T[1][1]*PTemp[j].y+T[1][2]*PTemp[j].z+T[1][3]*PTemp[j].w;
		P[j].z=T[2][0]*PTemp[j].x+T[2][1]*PTemp[j].y+T[2][2]*PTemp[j].z+T[2][3]*PTemp[j].w;
		P[j].w=T[3][0]*PTemp[j].x+T[3][1]*PTemp[j].y+T[3][2]*PTemp[j].z+T[3][3]*PTemp[j].w;
	}
	delete []PTemp;
}
