// Material.h: interface for the CMaterial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATERIAL_H__3EED0CA6_44EC_4729_8322_40321CE68965__INCLUDED_)
#define AFX_MATERIAL_H__3EED0CA6_44EC_4729_8322_40321CE68965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RGB.h"

class CMaterial
{
public:
	CMaterial(void);
	~CMaterial(void);
public:
	void SetAmbient(CRGB);//设置材质对环境光的反射率
	void SetDiffuse(CRGB);//设置材质对漫反射光的反射率
	void SetSpecular(CRGB);//设置材质对镜面反射光的反射率
	void SetEmit(CRGB);//设置材质自身辐射的颜色
	void SetExp(double);//设置材质的高光指数	
	void SetRough(double);//设置材质的粗糙度
	void SetFresnel(double);//设置材质的菲涅尔反射系数，表示反射方向上的光强占原始光强的比率
public:
	CRGB M_Ambient;//材质对环境光的反射率
	CRGB M_Diffuse;//材质对漫反射光的反射率
	CRGB M_Specular;//材质对镜面反射光的反射率
	CRGB M_Emit;//材质自身辐射的颜色
	double M_n;//材质的高光指数
	double M_m;//材质的粗糙度
	double M_f;//菲涅尔反射系数
};

#endif // !defined(AFX_MATERIAL_H__3EED0CA6_44EC_4729_8322_40321CE68965__INCLUDED_)
