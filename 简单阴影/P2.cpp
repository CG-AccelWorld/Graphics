#include "StdAfx.h"
#include "P2.h"
#include "math.h"


CP2::CP2(void)
{
	x = 0.0;
	y = 0.0;
	c = CRGB(0.0, 0.0, 0.0);
	w = 1.0;
}
CP2::CP2(double x,double y)
{
	this->x=x;
	this->y=y;
	c=CRGB(0.0,0.0,0.0);
	w=1.0;
}
CP2::CP2(double x,double y,CRGB c)
{
	this->x=x;
	this->y=y;
	this->c=c;
	w=1.0;
}
CP2::~CP2(void)
{
}
CP2 operator + (const CP2 &p1, const CP2 &p2)//和
{	
	CP2 p;
	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	return p;
}

CP2 operator - (const CP2 &p1, const CP2 &p2)//差
{
	CP2 p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

CP2 operator * (const CP2 &p, double m)//点和常量的积
{	
	return CP2(p.x * m, p.y * m);
}

CP2 operator * (double m, const CP2 &p)//点和常量的积
{	
	return CP2(p.x * m, p.y * m);
}

CP2 operator / (const CP2 &p1, double m)//数除
{
	if(fabs(m) < 1e-6)
		m = 1.0;
	CP2 p;
	p.x = p1.x / m;
	p.y = p1.y / m;
	return p;
}
