#pragma once
#include "AET.h"

class CBucket
{
public:
	CBucket(void);
	~CBucket(void);
public:
	int ScanLine;    //扫描线
	CAET *pET;       //桶上的边表指针
	CBucket *pNext;
};

