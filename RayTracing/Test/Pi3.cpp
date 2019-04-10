#include "stdafx.h"
#include "Pi3.h"
#include "math.h"


CPi3::CPi3(void)
{
		z=0.0;
}


CPi3::~CPi3(void)
{
}

CPi3::CPi3(double x,double y,double z):CPi2(x,y)
{
	this->z=z;
}


CPi3 operator +(const CPi3 &p0,const CPi3 &p1)//和
{	
	CPi3 p;
	p.x=p0.x+p1.x;
	p.y=p0.y+p1.y;
	p.z=p0.z+p1.z;
	return p;
}

CPi3 operator -(const CPi3 &p0,const CPi3 &p1)//差
{
	CPi3 p;
	p.x=p0.x-p1.x;
	p.y=p0.y-p1.y;
	p.z=p0.z-p1.z;
	return p;
}

CPi3 operator *(const CPi3 &p,double k)//点和常量的积
{	
	return CPi3(p.x*k,p.y*k,p.z*k);
}

CPi3 operator *(double k,const CPi3 &p)//点和常量的积
{	
	return CPi3(p.x*k,p.y*k,p.z*k);
}

CPi3 operator /(const CPi3 &p0,double k)//数除
{
	if(fabs(k)<1e-6)
		k=1.0;
	CPi3 p;
	p.x=p0.x/k;
	p.y=p0.y/k;
	p.z=p0.z/k;
	return p;
}

CPi3 operator+=(CPi3 &p0,CPi3 &p1)
{
	p0.x=p0.x+p1.x;
	p0.y=p0.y+p1.y;
	p0.z=p0.z+p1.z;
	return p0;
}

CPi3 operator-=(CPi3 &p0,CPi3 &p1)
{
	p0.x=p0.x-p1.x;
	p0.y=p0.y-p1.y;
	p0.z=p0.z-p1.z;
	return p0;
}

CPi3 operator*=(CPi3 &p0,double k)
{
	p0.x=p0.x*k;
	p0.y=p0.y*k;
	p0.z=p0.z*k;
	return p0;
}

CPi3 operator/=(CPi3 &p0,double k)
{
	if(fabs(k)<1e-6)
		k=1.0;
	p0.x=p0.x/k;
	p0.y=p0.y/k;
	p0.z=p0.z/k;
	return p0;
}

double CPi3::Mag()//长度
{
	return sqrt(x*x+y*y+z*z);
}