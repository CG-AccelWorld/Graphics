#pragma once
#include "P3.h"
#include "Vector.h"

class CFacet
{
public:
	CFacet(void);
	~CFacet(void);
	void SetFaceNormal(CP3,CP3,CP3);//设置小面法矢量
public:
	int pIndex[4];
	CVector fNormal; //小面的法矢量
};

