// Pi3.h: interface for the CPi3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PI3_H__AE2BB61B_7089_47FF_B344_2CBA0E04E064__INCLUDED_)
#define AFX_PI3_H__AE2BB61B_7089_47FF_B344_2CBA0E04E064__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Pi2.h"

class CPi3:public CPi2  
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

#endif // !defined(AFX_PI3_H__AE2BB61B_7089_47FF_B344_2CBA0E04E064__INCLUDED_)
