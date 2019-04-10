#pragma once
#include "Vector.h"
class CFace
{
public:
	CFace();
	virtual ~CFace();
	void SetNum(int ptNum);//设置面的顶点数
	void SetFaceNormal(CP3 pt0, CP3 pt1, CP3 pt2);//设置小面法矢量
public:
	int ptNum; //面的顶点数
	int* ptI;//面的顶点索引
	CVector fNormal; //小面的法矢量
};

