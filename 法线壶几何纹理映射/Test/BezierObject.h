#pragma once
#include "P3.h"
#include "Matrix44.h"
#include "Projection.h"
#include "Transform.h"
#include "Face.h"
#include"Vector.h"
#include "ZBuffer.h"
#include "Lighting.h"
#include "Material.h"
#include "T2.h" 
class CBezierObject  
{
public:
	CBezierObject();

	virtual ~CBezierObject();
public:
    void ReadBeizerObject(int num,CP3 **P);

	void ReadVertex();//读入控制多边形顶点
	void ReadPatch();//读入双三次曲面片
	void LeftMultiplyMatrix(CMatrix44 M, CP3* P); //左乘矩阵
	void RightMultiMatrix(CP3* P, CMatrix44 M);//右乘矩阵
	void DrawObject(CDC* pDC,CVector **N,int nWidth,int nHeight);//绘制Bezier曲面片
	void DrawControlGrid(CDC* pDC);//绘制控制网格
	void BicubicCurvedSurface(CDC* pDC,int NumObject,int m,int nWidth,int nHeight);//双三次曲面片
	void ControlGrid(CDC* pDC);//控制网格
    void DrawFace(CDC *pDC,int NumObject,bool sign);

    void DrawFaceP4(CDC *pDC,CP3 P4[4],CT2 tP4[4],bool sign);
	int NumObject;//物体有几部分
	CP3 **Vertex; 
	CP3 **P;
	CP3 P3[16];//三维控制点
	CP2 P2[16];//二维控制点
	CFace **Patch;  //控制顶点面表
	CP3 **FacePoint; //物体面上 点的 面表
	CT2 **FaceTPoint; //物体面上 点的 面表
	CProjection projection;//投影对象
	int	 LightNum;//光源数量
	CLighting *pLight;//光照环境

	CMaterial *pMaterial1;//物体材质
	CZBuffer *zbuf;
};

