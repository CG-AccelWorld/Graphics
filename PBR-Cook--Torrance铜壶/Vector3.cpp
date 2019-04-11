// Vector3.cpp: implementation of the CVector33 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Vector3.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector3::CVector3()//z轴正向
{
	x=0.0;
	y=0.0;
	z=1.0;
}

CVector3::~CVector3()
{

}

CVector3::CVector3(const CP3 &p)
{
	x=p.x;
	y=p.y;
	z=p.z;
}

CVector3::CVector3(double x,double y,double z)
{
	this->x=x;
	this->y=y;
	this->z=z;	
}

CVector3::CVector3(const CP3 &p0,const CP3 &p1)
{
	x=p1.x-p0.x;
	y=p1.y-p0.y;
	z=p1.z-p0.z;
}

CVector3::CVector3(const CPi3 &p0,const CPi3 &p1)
{
	x=p1.x-p0.x;
	y=p1.y-p0.y;
	z=p1.z-p0.z;
}

double CVector3::Mag()//矢量的模
{
	return sqrt(x*x+y*y+z*z);
}

CVector3 CVector3::Normalize()//归一化到单位矢量
{
	CVector3 vector;
	double Mag=sqrt(x*x+y*y+z*z);
	if(fabs(Mag)<1e-6)
		Mag=1.0;
	vector.x=x/Mag;
	vector.y=y/Mag;
	vector.z=z/Mag;
	return vector;
}

CVector3 operator +(const CVector3 &v0,const CVector3 &v1)//矢量的和
{
	CVector3 vector;
	vector.x=v0.x+v1.x;
	vector.y=v0.y+v1.y;
	vector.z=v0.z+v1.z;
	return vector;
}

CVector3 operator -(const CVector3 &v0,const CVector3 &v1)//矢量的差
{
	CVector3 vector;
	vector.x=v0.x-v1.x;
	vector.y=v0.y-v1.y;
	vector.z=v0.z-v1.z;
	return vector;
}

CVector3 operator *(const CVector3 &v,double k)//矢量与常量的积
{
	CVector3 vector;
	vector.x=v.x*k;
	vector.y=v.y*k;
	vector.z=v.z*k;
	return vector;
}

CVector3 operator *(double k,const CVector3 &v)//常量与矢量的积
{
	CVector3 vector;
	vector.x=v.x*k;
	vector.y=v.y*k;
	vector.z=v.z*k;
	return vector;
}

CVector3 operator /(const CVector3 &v,double k)//矢量数除
{
	if(fabs(k)<1e-6)
		k=1.0;
	CVector3 vector;
	vector.x=v.x/k;
	vector.y=v.y/k;
	vector.z=v.z/k;
	return vector;
}

CVector3 operator +=(CVector3 &v0,CVector3 &v1)//+=运算符重载
{
	v1.x=v0.x+v1.x;
	v1.y=v0.y+v1.y;
	v1.z=v0.z+v1.z;
	return v1;
}

CVector3 operator -=(CVector3 &v0,CVector3 &v1)//-=运算符重载
{
	v0.x=v0.x-v1.x;
	v0.y=v0.y-v1.y;
	v0.z=v0.z-v1.z;
	return v0;
}

CVector3 operator *=(CVector3 &v0,CVector3 &v1)//*=运算符重载
{
	v0.x=v0.x*v1.x;
	v0.y=v0.y*v1.y;
	v0.z=v0.z*v1.z;
	return v0;
}

CVector3 operator /=(CVector3 &v,double k)///=运算符重载
{
	v.x=v.x/k;
	v.y=v.y/k;
	v.z=v.z/k;
	return v;
}

double Dot(const CVector3 &v0,const CVector3 &v1)//矢量的点积
{
	return(v0.x*v1.x+v0.y*v1.y+v0.z*v1.z);
}

CVector3 Cross(const CVector3 &v0,const CVector3 &v1)//矢量的叉积
{
	CVector3 vector;
	vector.x=v0.y*v1.z-v0.z*v1.y;
	vector.y=v0.z*v1.x-v0.x*v1.z;
	vector.z=v0.x*v1.y-v0.y*v1.x;
	return vector;
}