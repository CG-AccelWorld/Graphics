// Lighting.h: interface for the CLighting class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIGHTING_H__BC7ED84F_9575_48BB_BC74_555862870BA3__INCLUDED_)
#define AFX_LIGHTING_H__BC7ED84F_9575_48BB_BC74_555862870BA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector3.h"
#include "Light.h"
#include "Material.h"

class CLighting  
{
public:
	CLighting();
	CLighting(int);
	virtual ~CLighting();
	void SetLightNumber(int);//设置光源数量
	CRGB Lighting(CP3,CP3,CVector3,CMaterial *,BOOL Sign);//计算光照	
public:
	int LightNum;//光源数量
	CLight *Light;//光源数组
	CRGB Ambient;//环境光
};



#endif // !defined(AFX_LIGHTING_H__BC7ED84F_9575_48BB_BC74_555862870BA3__INCLUDED_)
