#pragma once
#include "AET.h"

class CBucket  
{
public:
	CBucket();
	~CBucket();
public:
	int     ScanLine;
	CAET    *pET;
	CBucket *pNext;
};

