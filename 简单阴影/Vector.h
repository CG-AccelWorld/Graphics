#pragma once
#include "P3.h"
#include "Point2.h"
class CVector  
{
public:
	CVector();	
	virtual ~CVector();
	CVector(double,double,double);
	CVector(const CP3 &);
	CVector(const CP3 &,const CP3 &);
	CVector(const CPoint2 &,const CPoint2 &);
	double Mag();//矢量的模
	CVector Normalize();//单位矢量
	friend CVector operator +(const CVector &,const CVector &);//运算符重载
	friend CVector operator -(const CVector &,const CVector &);
	friend CVector operator *(const CVector &,double);
	friend CVector operator *(double,const CVector &);
	friend CVector operator /(const CVector &,double);
	friend CVector operator+=(CVector &,CVector &);
	friend CVector operator-=(CVector &,CVector &);
	friend CVector operator*=(CVector &,CVector &);
	friend CVector operator/=(CVector &,double);
	friend double  Dot(const CVector &,const CVector &);  //矢量点积
	friend CVector Cross(const CVector &,const CVector &);//矢量叉积
public:
	double x,y,z;//公有数据成员，方便外部访问
};

