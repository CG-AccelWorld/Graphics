#include "StdAfx.h"
#include "Material.h"

CMaterial::CMaterial(void)
{
	M_Ambient = CRGBA(0.2,0.2,0.2);//材质对环境光的反射率
	M_Diffuse = CRGBA(0.8,0.8,0.8);//材质对漫反射光的反射率
	M_Specular = CRGBA(0.0,0.0,0.0);//材质对镜面反射光的反射率
	M_k = 0.0;//材料粗糙度
	M_f = 1.0;//Fresnel反射系数
}

CMaterial::~CMaterial(void)
{

}

void CMaterial::SetAmbient(CRGBA c)
{
	M_Ambient = c;
}

void CMaterial::SetDiffuse(CRGBA c)
{
	M_Diffuse = c;
}

void CMaterial::SetSpecular(CRGBA c)
{
	M_Specular = c;
}

void CMaterial::SetEmit(CRGBA emi)
{
	M_Emit=emi;
}

void CMaterial::SetSlope(double k)
{
	M_k = k;
}

void CMaterial::SetFresnel(double f)
{
	M_f = f;
}