// P3.h: interface for the CP3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P3_H__5B85FC65_6516_4259_941E_FAB30D13824E__INCLUDED_)
#define AFX_P3_H__5B85FC65_6516_4259_941E_FAB30D13824E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P2.h"

class CP3:public CP2
{
public:
	CP3();
	virtual ~CP3();
	CP3(double x, double y, double z);
	friend CP3 operator +(const CP3 &p0, const CP3 &p1);//‘ÀÀ„∑˚÷ÿ‘ÿ
	friend CP3 operator -(const CP3 &p0, const CP3 &p1);
	friend CP3 operator *(const CP3 &p, double scalar);
	friend CP3 operator *(double scalar,const CP3 &p);
	friend CP3 operator /(const CP3 &p, double scalar);
	friend CP3 operator+=(CP3 &p0, CP2 &p1);
	friend CP3 operator-=(CP3 &p0, CP2 &p1);
	friend CP3 operator*=(CP3 &p, double scalar);
	friend CP3 operator/=(CP3 &p, double scalar);
public:
	double z;
	double xk;
		double yk;
			double zk;
};

#endif // !defined(AFX_P3_H__5B85FC65_6516_4259_941E_FAB30D13824E__INCLUDED_)
