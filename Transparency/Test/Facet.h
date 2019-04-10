#pragma once
#include "Vector3.h"

class CFacet//定义表面类
{
public:
	CFacet(void);
	virtual ~CFacet(void);
	void SetVertexNum(int vNumber);//设置表面顶点个数
	void SetFacetNormal(CP3 Vertex0,CP3 Vertex1,CP3 Vertex2);//设置小面法矢量
public:
	int vNumber;//面的顶点数
	int vIndex[4];//面的顶点索引号
	CVector3 fNormal;//面的法矢量
};
