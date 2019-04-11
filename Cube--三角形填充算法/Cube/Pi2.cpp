#include "StdAfx.h"
#include "Pi2.h"


CPi2::CPi2(void)
{
	x=0.0;
	y=0;
	c=CRGB(0.0,0.0,0.0);
}


CPi2::~CPi2(void)
{
}
CPi2::CPi2(double x,int y)
{
	this->x=x;
	this->y=y;
}
