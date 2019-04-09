#pragma once
class CRGB
{
public:
	CRGB(void);
	CRGB(double,double,double);
	~CRGB(void);
	friend CRGB operator+(const CRGB &,const CRGB &);//���������
	friend CRGB operator-(const CRGB &,const CRGB &);
	friend CRGB operator*(const CRGB &,const CRGB &);
	friend CRGB operator*(const CRGB &,double);
	friend CRGB operator*(double,const CRGB &);
	friend CRGB operator/(const CRGB &,double);
	friend CRGB operator+=(CRGB &,CRGB &);
	friend CRGB operator-=(CRGB &,CRGB &);
	friend CRGB operator*=(CRGB &,CRGB &);
	friend CRGB operator/=(CRGB &,double);
	void   Normalize();	//��һ����[0,1]����
public:
	double red;//��ɫ����
	double green;//��ɫ����
	double blue;//��ɫ����
};
