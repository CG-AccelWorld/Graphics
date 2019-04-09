#pragma once
#include "P3.h"

class Bezier
{
public:
	Bezier(void);
	~Bezier(void);
	Bezier(CP3[][4]);
public:
	void ObliqueProjection();//斜等测投影
	void LeftMultiMatrix(double M0[][4],CP3 P0[][4]); //左乘矩阵
	void RightMultiMatrix(CP3 P0[][4],double M0[][4]);//右乘矩阵
	void TransposeMatrix(double M0[][4]);//矩阵转置
	void DrawObject(CDC *);//绘制Bezier曲面
	void DrawCtrlPolygon(CDC *);//绘制控制多边形
public:
	CP3 P3[4][4];//三维顶点
	CP2 P2[4][4];//二维顶点
	double MT[4][4];//M的转置矩阵
};

