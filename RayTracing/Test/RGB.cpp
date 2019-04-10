#include "stdafx.h"
#include "RGB.h"

CRGB::CRGB(void)
{
	red = 0.0;
	green = 0.0;
	blue = 0.0;
}

CRGB::~CRGB(void)
{
}

CRGB::CRGB(double red,double green,double blue)
{
	if(red>255) red = 255;
	if(green>255) green = 255;
	if(blue>255) blue = 255;
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void CRGB::Normalize()
{
	red = (red   < 0.0) ? 0.0 : ((  red > 255.0) ? 255.0 : red);
	green=(green < 0.0) ? 0.0 : ((green > 255.0) ? 255.0 : green);
	blue =(blue  < 0.0) ? 0.0 : (( blue > 255.0) ? 255.0 : blue);
}

CRGB operator +(const CRGB &c1,const CRGB &c2)//+运算符重载
{
	CRGB c;
	c.red=c1.red+c2.red;
	c.green=c1.green+c2.green;
	c.blue=c1.blue+c2.blue;
	return c;
}

CRGB operator -(const CRGB &c1,const CRGB &c2)//-运算符重载
{
	CRGB c;
	c.red=c1.red-c2.red;
	c.green=c1.green-c2.green;
	c.blue=c1.blue-c2.blue;
	return c;
}

CRGB operator *(const CRGB &c1,const CRGB &c2)//*运算符重载
{
	CRGB c;
	c.red=c1.red*c2.red;
	c.green=c1.green*c2.green;
	c.blue=c1.blue*c2.blue;
	return c;
}

CRGB operator *(const CRGB &c1,double k)//*运算符重载
{
   CRGB c;
   c.red=k*c1.red;
   c.green=k*c1.green;
   c.blue=k*c1.blue;
   return c;
}

CRGB operator *(double k,const CRGB &c1)//*运算符重载
{
   CRGB c;
   c.red=k*c1.red;
   c.green=k*c1.green;
   c.blue=k*c1.blue;
   return c;
}

CRGB operator /(const CRGB &c1,double k)///运算符重载
{
   CRGB c;
   c.red=c1.red/k;
   c.green=c1.green/k;
   c.blue=c1.blue/k;
   return c;
}

CRGB operator +=(CRGB &c1,CRGB &c2)//+=运算符重载
{
	c1.red=c1.red+c2.red;
	c1.green=c1.green+c2.green;
	c1.blue=c1.blue+c2.blue;
	return c1;
}

CRGB operator -=(CRGB &c1,CRGB &c2)//-=运算符重载
{
	c1.red=c1.red-c2.red;
	c1.green=c1.green-c2.green;
	c1.blue=c1.blue-c2.blue;
	return c1;
}

CRGB operator *=(CRGB &c1,CRGB &c2)//*=运算符重载
{
	c1.red=c1.red*c2.red;
	c1.green=c1.green*c2.green;
	c1.blue=c1.blue*c2.blue;
	return c1;
}

CRGB operator /=(CRGB &c1,double k)///=运算符重载
{
	c1.red=c1.red/k;
	c1.green=c1.green/k;
	c1.blue=c1.blue/k;
	return c1;
}