#pragma once
#include "RGB.h"

class CP2  
{
public:
	CP2();
	virtual ~CP2();
	CP2(double,double);
	CP2(double,double,CRGB);
public:
	double x;
	double y;
	double w;
	CRGB   c;
};
