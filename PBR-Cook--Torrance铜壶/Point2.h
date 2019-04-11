// Point2.h: interface for the CPoint2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT2_H__23903D3D_62CF_41CA_A7F1_805ECB008B28__INCLUDED_)
#define AFX_POINT2_H__23903D3D_62CF_41CA_A7F1_805ECB008B28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"RGB.h"
#include "Vector3.h"

class CPoint2
{
public:
	CPoint2(void);
	CPoint2(int x, int y);
	CPoint2(int x, int y, CRGB c);
	CPoint2(int x, int y, CVector3 N);
	~CPoint2(void);
	friend CPoint2 operator + (const CPoint2 &pt0, const CPoint2 &pt1);//运算符重载
	friend CPoint2 operator - (const CPoint2 &pt0, const CPoint2 &pt1);
	friend CPoint2 operator * (const CPoint2 &pt, double m);
	friend CPoint2 operator * (int m, const CPoint2 &pt);
	friend CPoint2 operator / (const CPoint2 &pt, int m);
	friend BOOL operator != (const CPoint2 pt0, const CPoint2 pt1);
	friend CPoint2 operator < (const CPoint2 pt0, const CPoint2 pt1);		//在y轴上选择出最小y值的点
	friend CPoint2 operator > (const CPoint2 pt0, const CPoint2 pt1);		//在y轴上选择出最大y值的点
public:
	int x, y;
	double z;
	CRGB   c;
	CVector3 N;
};

#endif // !defined(AFX_POINT2_H__23903D3D_62CF_41CA_A7F1_805ECB008B28__INCLUDED_)
