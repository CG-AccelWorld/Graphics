#include "StdAfx.h"
#include "RGBA.h"

CRGBA::CRGBA(void)
{
	red = 1.0;
	green = 1.0;
	blue = 1.0; 
	alpha = 0.0;
}

CRGBA::CRGBA(double red, double green, double blue)       //重载构造函数
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}
CRGBA::~CRGBA(void)
{
}
CRGBA operator +(const CRGBA &c0, const CRGBA &c1)          //"+"运算符重载
{
	CRGBA color;
	color.red = c0.red + c1.red;
	color.green = c0.green + c1.green;
	color.blue = c0.blue + c1.blue;
	return color;
}
CRGBA operator -(const CRGBA &c0, const CRGBA &c1)         //"-"运算符重载
{
	CRGBA color;
	color.red = c0.red - c1.red;
	color.green = c0.green - c1.green;
	color.blue = c0.blue - c1.blue;
	return color;
}
CRGBA operator *(const CRGBA &c0, const CRGBA &c1)         //"*"运算符重载
{
	CRGBA color;
	color.red = c0.red * c1.red;
	color.green = c0.green * c1.green;
	color.blue = c0.blue * c1.blue;
	return color;
}
CRGBA operator *(const CRGBA &c, double scalar)             //"*"运算符重载
{
	CRGBA color;
	color.red = scalar * c.red;
	color.green = scalar * c.green;
	color.blue = scalar * c.blue;
	return color;
}
CRGBA operator *(double scalar, const CRGBA &c)           //"*"运算符重载
{
	CRGBA color;
	color.red = scalar * c.red;
	color.green = scalar * c.green;
	color.blue = scalar * c.blue;
	return color;
}
CRGBA operator /(const CRGBA &c, double scalar)           //"/"运算符重载
{
	CRGBA color;
	color.red = c.red / scalar;
	color.green = c.green / scalar;
	color.blue = c.blue / scalar;
	return color;
}

CRGBA operator +=(CRGBA &c1,CRGBA &c2)//"+="运算符重载
{
	c1.red += c2.red;
	c1.green += c2.green;
	c1.blue += c2.blue;
	return c1;
}

CRGBA operator -=(CRGBA &c1,CRGBA &c2)//"-="运算符重载
{
	c1.red -= c2.red;
	c1.green -= c2.green;
	c1.blue -= c2.blue;
	return c1;
}

CRGBA operator *=(CRGBA &c1,CRGBA &c2)//"*="运算符重载
{
	c1.red *= c2.red;
	c1.green *= c2.green;
	c1.blue *= c2.blue;
	return c1;
}

CRGBA operator /=(CRGBA &c1,double scalar)//"/="运算符重载
{
	c1.red /= scalar;
	c1.green /= scalar;
	c1.blue /= scalar;
	return c1;
}

void CRGBA::Normalize()                                //规范化处理
{
	red = (red < 0.0) ? 0.0 : ((red > 1.0) ? 1.0 : red);
	green = (green < 0.0) ? 0.0 : ((green > 1.0) ? 1.0 : green);
	blue = (blue < 0.0) ? 0.0 : ((blue > 1.0) ? 1.0 : blue);
}