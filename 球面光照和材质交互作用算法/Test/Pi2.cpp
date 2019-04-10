#include "StdAfx.h"
#include "Pi2.h"


CPi2::CPi2()
{
	x=0.0;
	y=0;
	c=CRGB(1.0,1.0,1.0);
}

CPi2::~CPi2()
{

}

CPi2::CPi2(double x,int y)
{
	this->x=x;
	this->y=y;
}