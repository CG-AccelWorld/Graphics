#include "StdAfx.h"
#include "P2.h"


CP2::CP2()
{
	x=0;
	y=0;
	w=0;
	c=CRGB(0.0,0.0,0.0);
}

CP2::~CP2()
{

}

CP2::CP2(double x,double y)
{
	this->x=x;
	this->y=y;
	this->w=1;
	this->c=CRGB(1.0,1.0,1.0);
}
