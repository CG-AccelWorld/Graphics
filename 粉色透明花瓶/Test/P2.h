#pragma once
#include "RGB.h"
class CP2
{
public:
	CP2(void);
	~CP2(void);
	CP2(double x,double y);
	CP2(double,double,CRGB);
public:
	double x;
	double y;
	double w;
	CRGB   c;
};

