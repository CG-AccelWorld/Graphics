// Bucket.h: interface for the CBucket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUCKET_H__F7236D0D_38C7_468E_94AF_2850E40C3C2B__INCLUDED_)
#define AFX_BUCKET_H__F7236D0D_38C7_468E_94AF_2850E40C3C2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AET.h"
class CBucket
{
public:
	CBucket(void);
	~CBucket(void);

	int ScanLine;
	CAET  *pET;
	CBucket *pNext;
};

#endif // !defined(AFX_BUCKET_H__F7236D0D_38C7_468E_94AF_2850E40C3C2B__INCLUDED_)
