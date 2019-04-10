#pragma once
#include "pi2.h"
class CPi3 :
	public CPi2
{
public:
	CPi3();
	virtual ~CPi3();
	CPi3(double,double,double);
				friend CPi3 operator +(const CPi3 &,const CPi3 &);//运算符重载
	friend CPi3 operator -(const CPi3 &,const CPi3 &);
	friend CPi3 operator *(const CPi3 &,double);
	friend CPi3 operator *(double,const CPi3 &);
	friend CPi3 operator /(const CPi3 &,double);
	friend CPi3 operator+=(CPi3 &,CPi3 &);
	friend CPi3 operator-=(CPi3 &,CPi3 &);
	friend CPi3 operator*=(CPi3 &,double);
	friend CPi3 operator/=(CPi3 &,double);
	double Mag();//长度

public:
	double z;
};

