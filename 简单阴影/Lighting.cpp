#include "StdAfx.h"
#include "Lighting.h"
#include "math.h"
#define  PI  3.14159265
#define  MIN(a,b)  ((a<b)?(a):(b))
#define  MAX(a,b)  ((a>b)?(a):(b))


CLighting::CLighting()
{
	LightNumber = 1;
	LightSource = new CLightSource[LightNumber];
	Ambient = CRGB(0.3, 0.3, 0.3);//环境光是常数
}

CLighting::~CLighting()
{
	if (LightSource)
	{
		delete []LightSource;
		LightSource = NULL;
	}
}
void CLighting::SetLightNumber(int LightNumber)
{
	if(LightSource)
	{
		delete []LightSource;
	}
	this->LightNumber = LightNumber;
	LightSource = new CLightSource[LightNumber];
}

CLighting::CLighting(int LightNumber)
{
	this->LightNumber = LightNumber;
	LightSource = new CLightSource[LightNumber];
	Ambient = CRGB(0.3, 0.3, 0.3);
}

CRGB CLighting::Lighting(CP3 ViewPoint, CP3 Point, CVector Normal, CMaterial* pMaterial)
{	
	CRGB LastIntensity = pMaterial->M_Emit;//材质自身发散色为初始值	
	for (int loop = 0; loop < LightNumber; loop++)//检查光源开关状态
	{	
		if (LightSource[loop].L_OnOff)
		{		
			CRGB Intensity = CRGB(0.0, 0.0, 0.0);
			CVector vectorL(Point, LightSource[loop].L_Position);//vL为指向光源的矢量
			double d = vectorL.Mag();//d为光传播的距离，等于光矢量vectorL的模
			vectorL = vectorL.Normalize();//单位化光矢量
			CVector vectorN = Normal;
			vectorN = vectorN.Normalize();//单位化法矢量			
			//第1步，加入漫反射光
			double CosBeta = MAX(Dot(vectorL, vectorN), 0);			
			Intensity.red += LightSource[loop].L_Diffuse.red * pMaterial->M_Diffuse.red * CosBeta;
			Intensity.green += LightSource[loop].L_Diffuse.green * pMaterial->M_Diffuse.green * CosBeta;
			Intensity.blue += LightSource[loop].L_Diffuse.blue * pMaterial->M_Diffuse.blue * CosBeta;
			//第2步，加入镜面反射光
			CVector vectorV(Point, ViewPoint);//VV为视矢量
			vectorV = vectorV.Normalize();//单位化视矢量
			CVector vectorH = (vectorL + vectorV) / (vectorL + vectorV).Mag();//VH为平分矢量	
			double nHN = pow(MAX(Dot(vectorH, vectorN), 0), pMaterial->M_n);
			Intensity.red += LightSource[loop].L_Specular.red * pMaterial->M_Specular.red * nHN;
			Intensity.green += LightSource[loop].L_Specular.green * pMaterial->M_Specular.green * nHN;
			Intensity.blue += LightSource[loop].L_Specular.blue * pMaterial->M_Specular.blue * nHN;	
			//第3步，光强衰减
			double c0 = LightSource[loop].L_C0;//c0为常数衰减因子
			double c1 = LightSource[loop].L_C1;//c1线性衰减因子
			double c2 = LightSource[loop].L_C2;//c2二次衰减因子			
			double f = (1.0 / (c0 + c1 * d + c2 * d * d));//光强衰减函数
			f = MIN(1.0,f);		
			LastIntensity += Intensity * f;		
		}
		else
			LastIntensity += Point.c;//物体自身颜色		
	}
	//第4步，加入环境光
	LastIntensity += Ambient * pMaterial->M_Ambient;
	//第5步，颜色归一化到[0,1]区间
	LastIntensity.Normalize();		
	//第6步，返回所计算顶点的光强颜色
	return LastIntensity;
}	
