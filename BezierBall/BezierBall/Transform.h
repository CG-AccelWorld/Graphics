#pragma once
#include "P3.h"

class Transform
{
public:
	Transform(void);
	~Transform(void);
public:
	void SetMatrix(CP3* p, int ptNumber);//获取球的顶点矩阵
	void Identity();//初始变换矩阵
	void Translate(double tx,double ty, double tz); //平移变换矩阵
	void RotateX(double beta); //绕x轴旋转变换矩阵轴旋转变换矩阵
	void RotateY(double beta); //绕y轴旋转变换矩阵轴旋转变换矩阵
	void MultiplyMatrix();     //完成变换后的矩阵
public:
	double T[4][4];
	CP3* P;
	int ptNumber;
};

