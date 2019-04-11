// Matrix44.h: interface for the CMatrix44 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX44_H__83967082_7870_4488_B5E9_2183AE9CE2D4__INCLUDED_)
#define AFX_MATRIX44_H__83967082_7870_4488_B5E9_2183AE9CE2D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMatrix44 //4°¡4æÿ’Û 
{
public:
	CMatrix44();
	virtual ~CMatrix44();
	void LoadZero();//¡„æÿ’Û
	void LoadIdentity();//µ•Œª’Û
	CMatrix44 Transpose();
	friend CMatrix44 operator+ (const CMatrix44 &m1, const CMatrix44 &m2);//æÿ’Û°∞+°±
	friend CMatrix44 operator- (const CMatrix44 &m1, const CMatrix44 &m2);//æÿ’Û°∞-°±
	friend CMatrix44 operator* (const CMatrix44 &m1, const double scalar);//æÿ’Û ˝≥À
	friend CMatrix44 operator* (const CMatrix44 &m1, const CMatrix44 &m2);//æÿ’Û°∞*°±
public:
	double matrix[4][4];
};

#endif // !defined(AFX_MATRIX44_H__83967082_7870_4488_B5E9_2183AE9CE2D4__INCLUDED_)
