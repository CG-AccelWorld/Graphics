// AET.h: interface for the CAET class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AET_H__D631187C_9F48_4313_B4D4_B4A9075354F0__INCLUDED_)
#define AFX_AET_H__D631187C_9F48_4313_B4D4_B4A9075354F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"Pi2.h"
class CAET  
{
public:
	CAET();
	virtual ~CAET();

	double x;
	int yMax;
	double k;
	CPi2 ps;
	CPi2 pe;
	CAET *pNext;
};

#endif // !defined(AFX_AET_H__D631187C_9F48_4313_B4D4_B4A9075354F0__INCLUDED_)
