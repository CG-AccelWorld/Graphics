#include "stdafx.h"
#include "Face.h"

CFace::CFace()
{
	ptI = NULL;
	fNormal = CVector(CP3(0.0, 0.0, 1.0));
}

CFace::~CFace()
{
	if (NULL != ptI)
	{
		delete []ptI;
		ptI = NULL;
	}
}

void CFace::SetNum(int ptNum)
{
	this->ptNum = ptNum;
	ptI = new int[ptNum];
}

void CFace::SetFaceNormal(CP3 pt0, CP3 pt1, CP3 pt2)//计算小面法矢量
{
	CVector vector01(pt0, pt1);
	CVector vector02(pt0, pt2);
	fNormal = CrossProduct(vector01, vector02);
	fNormal = fNormal.Normalize();
}
