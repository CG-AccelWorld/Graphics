#include "stdafx.h"
#include "P3.h"


CP3::CP3()
{
	z = 0.0;
}

CP3::~CP3()
{

}
CP3::CP3(double x, double y, double z):CP2(x, y)
{
	this->z = z;
}