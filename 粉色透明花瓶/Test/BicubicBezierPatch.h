#pragma once
#include "P3.h"
#include "Vector.h"
#include "Lighting.h"
class CBicubicBezierPatch
{
public:
	CBicubicBezierPatch(void);
	~CBicubicBezierPatch(void);
	void ReadControlPoint(CP3 P[4][4]);//读入16个控制点
	void DrawCurvedPatch(CDC* pDC,CP3 ViewPoint,CLighting *pLight,CMaterial *pMaterial);//绘制双三次Bezier曲面片
	void DrawControlGrid(CDC* pDC);//绘制控制网格
private:
	void LeftMultiplyMatrix(double M[][4],CP3 P[][4]);//左乘顶点矩阵
	void RightMultiplyMatrix(CP3 P[][4],double M[][4]);//右乘顶点矩阵
	void TransposeMatrix(double M[][4]);//转置矩阵
	CP2 ObliqueProjection(CP3 Point3);//斜二测投影
public:
	CP3 P[4][4];//三维控制点
	CP3 PV[121];
	CVector NV[121];
};
