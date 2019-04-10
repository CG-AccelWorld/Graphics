#pragma once
#include "AET.h"
class CBucket
{
public:
	CBucket(void);
	~CBucket(void);
public:
	int ScanLine;
	CAET  *pET;
	CBucket *pNext;
};

