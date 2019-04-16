#pragma once
#include "RGB.h"
#include "Vector.h"
class CFacet
{
public:
	CFacet(void);
	virtual ~CFacet(void);
	void PointNum(int ptNumber);
	void SetFaceNormal(CP3,CP3,CP3);//设置小面法矢量
public:
	int ptNumber; //面的顶点数
	int ptIndex[4];//面的顶点索引号
	CRGB c;
	CVector fNormal; //小面的法矢量
};

