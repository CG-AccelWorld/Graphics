// Face.cpp: implementation of the CFace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Face.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFace::CFace()
{
	ptI = NULL;
}

CFace::~CFace()
{
	if(NULL != ptI)
	{
		delete []ptI;
		ptI = NULL;
	}
}

void CFace::SetNum(int ptNum)
{
	this->ptNum = ptNum;
	ptI = new int[ptNum];
}