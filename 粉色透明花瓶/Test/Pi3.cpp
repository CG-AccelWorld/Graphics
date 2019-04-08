#include "StdAfx.h"
#include "Pi3.h"


CPi3::CPi3()
{
	z=0.0;
}

CPi3::~CPi3()
{

}

CPi3::CPi3(double x,int y,double z):CPi2(x,y)
{
	this->z=z;
}