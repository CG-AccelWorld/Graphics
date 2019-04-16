#include "StdAfx.h"
#include "Point2.h"
#include "math.h"

CPoint2::CPoint2(void)
{
	x = 0;
	y = 0;
	c = CRGB(0, 0, 0);
}
CPoint2::CPoint2(int x, int y)
{
	this->x = x;
	this->y = y;
	c = CRGB(0, 0, 0);
}
CPoint2::CPoint2(int x, int y, CRGB c)
{
	this->x = x;
	this->y = y;
	this->c = c;
}
CPoint2::~CPoint2(void)
{
}
CPoint2 operator + (const CPoint2 &pt0, const CPoint2 &pt1)//和
{	
	CPoint2 point;
	point.x = pt0.x + pt1.x;
	point.y = pt0.y + pt1.y;
	return point;
}

CPoint2 operator - (const CPoint2 &pt0, const CPoint2 &pt1)//差
{
	CPoint2 point;
	point.x = pt0.x - pt1.x;
	point.y = pt0.y - pt1.y;
	return point;
}

CPoint2 operator * (const CPoint2 &pt, int m)//点和常量的积
{	
	return CPoint2(pt.x * m, pt.y * m);
}

CPoint2 operator * (int m, const CPoint2 &pt)//点和常量的积
{	
	return CPoint2(pt.x * m, pt.y * m);
}

CPoint2 operator / (const CPoint2 &pt, double m)//数除
{
	if(fabs(m) < 1e-4)
		m = 1.0;
	CPoint2 point;
	point.x = int(pt.x / m);
	point.y = int(pt.y / m);
	return point;
}

BOOL operator != (const CPoint2 pt0, const CPoint2 pt1)
{
	if(pt0.x == pt1.x && pt0.y == pt1.y)
		return FALSE;
	else
		return TRUE;
}

CPoint2 operator < (const CPoint2 pt0, const CPoint2 pt1)
{
	CPoint2 point;
	if(pt0.y < pt1.y)
		point = pt0;		
	if(pt0.y == pt1.y)
	{
		if(pt0.x < pt1.x)
			point = pt0;
		else
			point = pt1;	
	}
	if(pt0.y > pt1.y)
		point = pt1;	
	return point;
}

CPoint2 operator > (const CPoint2 pt0, const CPoint2 pt1)
{
	CPoint2 point;
	if(pt0.y > pt1.y)
		point = pt0;
	if(pt0.y == pt1.y)
	{
		if(pt0.x < pt1.x)
			point = pt0;
		else
			point = pt1;	
	}
	if(pt0.y < pt1.y)
		point = pt1;
	return point;
}
