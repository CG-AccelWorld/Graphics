#pragma once
class CRGB
{
public:
	CRGB(void);
	~CRGB(void);
	CRGB(double red,double green,double blue);
public:
	double red;
	double green;
	double blue;
public:
	void Normalize();
public:
	friend CRGB operator+(const CRGB &,const CRGB &);//‘ÀÀ„∑˚÷ÿ‘ÿ
	friend CRGB operator-(const CRGB &,const CRGB &);
	friend CRGB operator*(const CRGB &,const CRGB &);
	friend CRGB operator*(const CRGB &,double);
	friend CRGB operator*(double,const CRGB &);
	friend CRGB operator/(const CRGB &,double);
	friend CRGB operator+=(CRGB &,CRGB &);
	friend CRGB operator-=(CRGB &,CRGB &);
	friend CRGB operator*=(CRGB &,CRGB &);
	friend CRGB operator/=(CRGB &,double);
};

