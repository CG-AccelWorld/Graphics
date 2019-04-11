// Vector3.h: interface for the CVector33 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR3_H__AF0E0B97_5194_4C82_A77D_28BD70CFE75F__INCLUDED_)
#define AFX_VECTOR3_H__AF0E0B97_5194_4C82_A77D_28BD70CFE75F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Pi3.h"
#include "P3.h" 
class CVector3  
{
public:
	CVector3();	
	virtual ~CVector3();
	CVector3(double,double,double);
	CVector3(const CP3 &);
	CVector3(const CP3 &,const CP3 &);
	CVector3(const CPi3 &,const CPi3 &);
	double Mag();//矢量的模
	CVector3 Normalize();//单位矢量
	friend CVector3 operator +(const CVector3 &,const CVector3 &);//运算符重载
	friend CVector3 operator -(const CVector3 &,const CVector3 &);
	friend CVector3 operator *(const CVector3 &,double);
	friend CVector3 operator *(double,const CVector3 &);
	friend CVector3 operator /(const CVector3 &,double);
	friend CVector3 operator+=(CVector3 &,CVector3 &);
	friend CVector3 operator-=(CVector3 &,CVector3 &);
	friend CVector3 operator*=(CVector3 &,CVector3 &);
	friend CVector3 operator/=(CVector3 &,double);
	friend double  Dot(const CVector3 &,const CVector3 &);  //矢量点积
	friend CVector3 Cross(const CVector3 &,const CVector3 &);//矢量叉积
public:
	double x,y,z;//公有数据成员，方便外部访问
};
#endif // !defined(AFX_VECTOR3_H__AF0E0B97_5194_4C82_A77D_28BD70CFE75F__INCLUDED_)
