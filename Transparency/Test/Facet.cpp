#include "StdAfx.h"
#include "Facet.h"


CFacet::CFacet(void)
{
}

void CFacet::SetVertexNum(int vNumber)
{
	this->vNumber = vNumber;
}

CFacet::~CFacet(void)
{
}

void CFacet::SetFacetNormal(CP3 Vertex0, CP3 Vertex1, CP3 Vertex2)//计算小面法矢量
{
	CVector3 Vector01(Vertex0, Vertex1);       // Vertex0与Vertex1顶点构成边矢量
	CVector3 Vector02(Vertex0, Vertex2);       // Vertex0与Vertex2顶点构成边矢量
	fNormal = CrossProduct(Vector01,Vector02);
}
