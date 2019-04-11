#include "StdAfx.h"
#include "Facet.h"


CFacet::CFacet(void)
{
}


CFacet::~CFacet(void)
{
}
void CFacet::SetFaceNormal(CP3 pt0,CP3 pt1,CP3 pt2)//计算小面法矢量
{
	CVector V01(pt0,pt1);
	CVector V02(pt0,pt2);
	fNormal=Cross(V01,V02);
}
