// CRGB.h: interface for the CRGB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRGB_H__F14E5B6C_E5FA_4DD9_8051_EB943E4929E7__INCLUDED_)
#define AFX_CRGB_H__F14E5B6C_E5FA_4DD9_8051_EB943E4929E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRGB  
{
public:
	CRGB();
	CRGB(double red, double green, double blue);
	virtual ~CRGB();
	friend CRGB operator+(const CRGB &c1, const CRGB &c2);//运算符重载
	friend CRGB operator-(const CRGB &c1, const CRGB &c2);
	friend CRGB operator*(const CRGB &c1, const CRGB &c2);
	friend CRGB operator*(const CRGB &c1, double scalar);
	friend CRGB operator*(double scalar,const CRGB &c);
	friend CRGB operator/(const CRGB &c1, double scalar);
	friend CRGB operator+=(CRGB &c1, CRGB &c2);
	friend CRGB operator-=(CRGB &c1, CRGB &c2);
	friend CRGB operator*=(CRGB &c1, CRGB &c2);
	friend CRGB operator/=(CRGB &c1, double scalar);
	void   Normalize();	//归一化到[0,1]区间
public:
	double red;//红色分量
	double green;//绿色分量
	double blue;//蓝色分量
};

#endif // !defined(AFX_CRGB_H__F14E5B6C_E5FA_4DD9_8051_EB943E4929E7__INCLUDED_)
