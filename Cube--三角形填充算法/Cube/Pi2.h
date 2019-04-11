#pragma once
#include "RGB.h"

class CPi2
{
public:
	CPi2(void);
	~CPi2(void);
public:
	CPi2(double,int);
	double x;
	int y;
	CRGB   c;
};

