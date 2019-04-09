#pragma once
#include "Vector.h"

class CFace
{
public:
	CFace(void);
	~CFace(void);
	void SetNum(int);
	void SetFaceNormal(CP3,CP3,CP3);//设置小面法矢量
public:
	int vN;          //小面的顶点数
	int *vI;         //小面的顶点索引
	CVector fNormal; //小面的法矢量
};

