#pragma once
#include "P3.h"
class Transform3
{
public:
	Transform3(void);
	~Transform3(void);
	void SetMatrix(CP3* P, int ptNumber);
	void Identity();//单位矩阵
	void Translate(double tx, double ty, double tz);//平移变换矩阵
	void RotateX(double beta);//绕X轴旋转变换矩阵
	void RotateY(double beta);//绕Y轴旋转变换矩阵
	void RotateZ(double beta);//旋转变换矩阵
	void MultiplyMatrix();//矩阵相乘
public:
	double T[4][4];
	CP3*   P;
	int    ptNumber;
};

