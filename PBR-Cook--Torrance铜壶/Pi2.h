// Pi2.h: interface for the CPi2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PI2_H__BEBAE790_5711_4961_A3D5_8D0A86F49D9D__INCLUDED_)
#define AFX_PI2_H__BEBAE790_5711_4961_A3D5_8D0A86F49D9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"RGB.h"
class CPi2  
{
public:
	CPi2();
	virtual ~CPi2();
	CPi2(double,double);
	double x;
	double    y;
	CRGB   c;
};

#endif // !defined(AFX_PI2_H__BEBAE790_5711_4961_A3D5_8D0A86F49D9D__INCLUDED_)
