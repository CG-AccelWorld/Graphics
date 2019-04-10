#pragma once

class CRGBA
{
public:
	CRGBA(void);
	CRGBA (double red, double green, double blue);
	virtual ~CRGBA (void);
	friend CRGBA operator + (const CRGBA &c0, const CRGBA &c1);    //运算符重载
	friend CRGBA operator - (const CRGBA &c0, const CRGBA &c1);
	friend CRGBA operator * (const CRGBA &c0, const CRGBA &c1);
	friend CRGBA operator * (const CRGBA &c, double scalar);
	friend CRGBA operator * (double scalar,const CRGBA &c);
	friend CRGBA operator / (const CRGBA &c, double scalar);
	friend CRGBA operator+=(CRGBA &c1, CRGBA &c2);
	friend CRGBA operator-=(CRGBA &c1, CRGBA &c2);
	friend CRGBA operator*=(CRGBA &c1, CRGBA &c2);
	friend CRGBA operator/=(CRGBA &c1, double scalar);
	void Normalize(void);	                                   //规范化到[0,1]区间
public:
	double red;             //红色分量
	double green;           //绿色分量
	double blue;            //蓝色分量
	double alpha;           //alpha分量
};

