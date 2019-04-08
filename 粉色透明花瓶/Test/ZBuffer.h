#pragma once
#include "Bucket.h"
#include "Vector.h"
#include "Lighting.h"
#include "Material.h"
class CZBuffer
{
public:
	CZBuffer();
    virtual ~CZBuffer();
	void CreateBucket();//创建桶
	void CreateEdge();//边表
	void AddEt(CAET *);//合并ET表
	void ETOrder();
	void Phong(CDC *,CP3,CLighting *,CMaterial *,int);//Phong填充函数
	CRGB GetTransColor(CRGB,CRGB);//计算透明颜色
	void InitDeepBuffer(CDC *,int,int,double,CRGB);//初始化深度缓存
    CRGB Interpolation(double,double,double,CRGB,CRGB);//线性插值
	CVector Interpolation(double,double,double,CVector,CVector);//法矢线性插值
	double Interpolation(double,double,double,double,double);
	void SetPoint(CPi3 *,CVector *,int);
	void ClearMemory();//清理内存
	void DeleteAETChain(CAET* pAET);//删除边表
protected:
	int PNum;//顶点个数
	CPi3 *P;//顶点数组
	CVector *N;//顶点的法矢量动态数组
	CAET *pHeadE,*pCurrentE,*pEdge;//有效边表结点指针
	CBucket *pCurrentB,*pHeadB;
	double **zBuffer;//缓深度冲区
	CRGB   **cBuffer;//颜色缓冲区
	int Width,Height;//缓冲区参数
	double VAB;
	COLORREF BkaClr;
};

