// Lighting.cpp: implementation of the CLighting class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "test.h"
#include "Lighting.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "math.h"
#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))
#define  PI  3.14159265
CLighting::CLighting()
{
	LightNum=1;
	Light=new CLight[LightNum];
	Ambient=CRGB(1.0,1.0,1.0);//环境光恒定不变
}

CLighting::~CLighting()
{
	if(Light)
	{
		delete []Light;
		Light=NULL;
	}
}
void CLighting::SetLightNumber(int lnum)
{
	if(Light)
		delete []Light;
	LightNum=lnum;
	Light=new CLight[lnum];
}

CLighting::CLighting(int lnum)
{
	LightNum=lnum;
	Light=new CLight[lnum];
	Ambient=CRGB(0.3,0.3,0.3);	
}

CRGB CLighting::Lighting(CP3 ViewPoint,CP3 Point,CVector3 Normal,CMaterial *pMaterial,BOOL Sign)
{
	CRGB LastC=pMaterial->M_Emit;//材质自身发散色为初始值
	for(int i=0;i<LightNum;i++)//来自光源
	{
		if(Light[i].L_OnOff)
		{
			CRGB InitC;
			InitC.red=0.0,InitC.green=0.0,InitC.blue=0.0;
			CVector3 VL(Point,Light[i].L_Position);//指向光源的矢量
			double d=VL.Mag();//光传播的距离，等于矢量VL的模
			VL=VL.Normalize();//单位化光矢量
			CVector3 VN=Normal;
			VN=VN.Normalize();//单位化法矢量
			double NdotL = MAX(Dot(VL, VN), 0.0);
			//第1步，加入漫反射光
			if(Light[i].b_Diffuse)
			{
				//double CosTheta=MAX(Dot(VL,VN),0);
				InitC.red+=Light[i].L_Diffuse.red*pMaterial->M_Diffuse.red*NdotL;
				InitC.green+=Light[i].L_Diffuse.green*pMaterial->M_Diffuse.green*NdotL;
				InitC.blue+=Light[i].L_Diffuse.blue*pMaterial->M_Diffuse.blue*NdotL;
			}
			if(Sign)
			{
				//第2步，加入镜面反射光
				if(Light[i].b_Specular)
				{
					CVector3 VV(Point,ViewPoint);//VV为视矢量
					VV=VV.Normalize();//单位化视矢量
					CVector3 VH=(VL+VV)/(VL+VV).Mag();//平分矢量
					double nHN=pow(MAX(Dot(VH,VN),0),pMaterial->M_n);
					InitC.red+=Light[i].L_Specular.red*pMaterial->M_Specular.red*nHN;
					InitC.green+=Light[i].L_Specular.green*pMaterial->M_Specular.green*nHN;
					InitC.blue+=Light[i].L_Specular.blue*pMaterial->M_Specular.blue*nHN;		
				}
			}
			else
			{
				if(Light[i].b_Specular)
				{
					CVector3 VV(Point,ViewPoint);//VV为视矢量
					VV=VV.Normalize();//单位化视矢量
					CVector3 VH=(VL+VV)/(VL+VV).Mag();//平分矢量
					double NdotH = MAX(Dot(VN, VH), 0.0);
					double NdotV = MAX(Dot(VN, VV), 0.0);
					double VdotH = MAX(Dot(VV, VH), 0.0);
					if(NdotL > 0.0 && NdotV > 0.0)
					{
						//geometric attenuation 几何衰减
						double NH2 = 2.0 * NdotH;
						double g1 = (NH2 * NdotV) / VdotH;
						double g2 = (NH2 * NdotL) / VdotH;
						double geoAtt = MIN(1.0, MIN(g1, g2));
						// beckmann distribution function 贝克曼分布函数 
						double r1 = 1.0 / (pow(pMaterial->M_m, 2) * pow(NdotH, 4.0));
						double r2 = (NdotH * NdotH - 1.0) / (pow(pMaterial->M_m, 2) * pow(NdotH, 2));
						double roughness = r1 * exp(r2);
						// fresnel Schlick approximation  菲涅尔项我们使用Schlick逼近
						double fresnel = pMaterial->M_f + pow(1.0 - VdotH, 5.0) * (1.0 - pMaterial->M_f);
						double Rs = (fresnel * geoAtt * roughness) / (NdotV * NdotL * 4);

						InitC.red += Light[i].L_Specular.red * pMaterial->M_Specular.red * Rs;
						InitC.green += Light[i].L_Specular.green * pMaterial->M_Specular.green * Rs;
						InitC.blue += Light[i].L_Specular.blue * pMaterial->M_Specular.blue * Rs;
					}
				}
			}
			//LastC+=InitC;
			//第3步，光强衰减
			double c0=Light[i].L_C0;//c0为常数衰减因子
			double c1=Light[i].L_C1;//c1线性衰减因子
			double c2=Light[i].L_C2;//c2二次衰减因子
			double f=(1.0/(c0+c1*d+c2*d*d));//光强衰减函数
			f=MIN(1.0,f);
			LastC+=InitC*f;
		}
		else
			LastC+=Point.c;//物体自身颜色
	}
	//第4步，加入环境光
	if(Light[0].b_Ambient)
		LastC+=Ambient*pMaterial->M_Ambient;
	//第5步，颜色归一化到[0,1]区间
	LastC.Normalize();
	//第6步，返回所计算顶点的光强颜色
	return LastC;
}