#include "stdafx.h"
#include "Transform.h"
#include "math.h"
#define PI 3.14159


CTransform::CTransform()
{

}

CTransform::~CTransform()
{

}

void CTransform::SetMatrix(CP3* P, int ptNumber)
{
	ptOld = P;
	this->ptNumber = ptNumber;
}

void CTransform::Translate(double tx, double ty, double tz)//平移变换矩阵
{
	T.LoadIdentity();
	T.matrix[3][0] = tx; 
	T.matrix[3][1] = ty; 
	T.matrix[3][2] = tz; 
	MultiplyMatrix();
}

void CTransform::Scale(double sx, double sy, double sz)//比例变换矩阵
{
	T.LoadIdentity();
	T.matrix[0][0] = sx; 
	T.matrix[1][1] = sy; 
	T.matrix[2][2] = sz; 
	MultiplyMatrix();
}

void CTransform::Scale(double sx, double sy, double sz, CP3 p)//相对于任意点的比例变换矩阵
{
	Translate(-p.x, -p.y, -p.z);
	Scale(sx, sy, sz);
	Translate(p.x, p.y, p.z);
}

void CTransform::RotateX(double beta)//绕X轴旋转变换矩阵
{
	T.LoadIdentity();
	double rad = beta * PI / 180;
	T.matrix[1][1] =  cos(rad);T.matrix[1][2] = sin(rad);
	T.matrix[2][1] = -sin(rad);T.matrix[2][2] = cos(rad);
	MultiplyMatrix();
}

void CTransform::RotateX(double beta, CP3 p)//相对于任意点的绕X轴旋转变换矩阵
{
	Translate(-p.x, -p.y, -p.z);
	RotateX(beta);
	Translate(p.x, p.y, p.z);
}

void CTransform::RotateY(double beta)//绕Y轴旋转变换矩阵
{
	T.LoadIdentity();
	double rad = beta * PI / 180;
	T.matrix[0][0] = cos(rad);T.matrix[0][2] = -sin(rad);
	T.matrix[2][0] = sin(rad);T.matrix[2][2] =  cos(rad);
	MultiplyMatrix();
}

void CTransform::RotateY(double beta, CP3 p)//相对于任意点的绕Y轴旋转变换矩阵
{
	Translate(-p.x, -p.y, -p.z);
	RotateY(beta);
	Translate(p.x, p.y, p.z);
}

void CTransform::RotateZ(double beta)//绕Z轴旋转变换矩阵
{
	T.LoadIdentity();
	double rad = beta * PI / 180;
	T.matrix[0][0] =  cos(rad);T.matrix[0][1] = sin(rad);
	T.matrix[1][0] = -sin(rad);T.matrix[1][1] = cos(rad);
	MultiplyMatrix();
}

void CTransform::RotateZ(double beta, CP3 p)//相对于任意点的绕Z轴旋转变换矩阵
{
	Translate(-p.x, -p.y, -p.z);
	RotateZ(beta);
	Translate(p.x, p.y, p.z);
}

void CTransform::ReflectX()//X轴反射变换矩阵
{
	T.LoadIdentity();
	T.matrix[1][1] = -1;
	T.matrix[2][2] = -1;
	MultiplyMatrix();
}

void CTransform::ReflectY()//Y轴反射变换矩阵
{
	T.LoadIdentity();
	T.matrix[0][0] = -1;
	T.matrix[2][2] = -1;
	MultiplyMatrix();
}

void CTransform::ReflectZ()//Z轴反射变换矩阵
{
	T.LoadIdentity();
	T.matrix[0][0] = -1;
	T.matrix[1][1] = -1;
	MultiplyMatrix();
}

void CTransform::ReflectXOY()//XOY面反射变换矩阵
{
	T.LoadIdentity();
	T.matrix[2][2] = -1;
	MultiplyMatrix();
}

void CTransform::ReflectYOZ()//YOZ面反射变换矩阵
{
	T.LoadIdentity();
	T.matrix[0][0] = -1;
	MultiplyMatrix();
}

void CTransform::ReflectXOZ()//ZOX面反射变换矩阵
{
	T.LoadIdentity();
	T.matrix[1][1] = -1;
	MultiplyMatrix();
}

void CTransform::ShearX(double d, double g)//X方向错切变换矩阵
{
	T.LoadIdentity();
	T.matrix[1][0] = d;
	T.matrix[2][0] = g;
	MultiplyMatrix();
}

void CTransform::ShearY(double b, double h)//Y方向错切变换矩阵
{
	T.LoadIdentity();
	T.matrix[0][1] = b;
	T.matrix[2][1] = h;
	MultiplyMatrix();
}

void CTransform::ShearZ(double c, double f)//Z方向错切变换矩阵
{
	T.LoadIdentity();
	T.matrix[0][2] = c;
	T.matrix[1][2] = f;
	MultiplyMatrix();
}

void CTransform::MultiplyMatrix()//矩阵相乘
{
	CP3* ptNew = new CP3[ptNumber];	
	for	(int i = 0;	i < ptNumber; i++)
	{
		ptNew[i] = ptOld[i];
	}
	for	(int j = 0;	j< ptNumber;	j++)
	{
		ptOld[j].x = ptNew[j].x * T.matrix[0][0] + ptNew[j].y * T.matrix[1][0] + ptNew[j].z * T.matrix[2][0] + ptNew[j].w * T.matrix[3][0];
		ptOld[j].y = ptNew[j].x * T.matrix[0][1] + ptNew[j].y * T.matrix[1][1] + ptNew[j].z * T.matrix[2][1] + ptNew[j].w * T.matrix[3][1];
		ptOld[j].z = ptNew[j].x * T.matrix[0][2] + ptNew[j].y * T.matrix[1][2] + ptNew[j].z * T.matrix[2][2] + ptNew[j].w * T.matrix[3][2];
		ptOld[j].w = ptNew[j].x * T.matrix[0][3] + ptNew[j].y * T.matrix[1][3] + ptNew[j].z * T.matrix[2][3] + ptNew[j].w * T.matrix[3][3];
	}
	delete []ptNew;
}

