#include "StdAfx.h"
#include "Lighting.h"
#include "math.h"
#define  PI  3.14159265
#define  MIN(a,b)  ((a<b)?(a):(b))
#define  MAX(a,b)  ((a>b)?(a):(b))

CLighting::CLighting(void)
{
	Number = 1;
	LightSource = new CLightSource[Number];
	Ambient = CRGBA(0.3, 0.3, 0.3);//环境光是常数
}

CLighting::~CLighting(void)
{
	if (LightSource)
	{
		delete []LightSource;
		LightSource = NULL;
	}
}

void CLighting::SetLightNumber(int Number)
{
	if(LightSource)
		delete []LightSource;
	this->Number = Number;
	LightSource = new CLightSource[Number];
}

CLighting::CLighting(int Number)
{
	this->Number = Number;
	LightSource = new CLightSource[Number];
	Ambient = CRGBA(0.3, 0.3, 0.3);
}

CRGBA CLighting::illuminate(CP3 ViewPoint, CP3 Point, CVector3 Normal, CMaterial* pMaterial)
{	
	CRGBA ResultI = pMaterial->M_Emit;// 初始化“最终”光强	为自身颜色
	for (int loop = 0; loop < Number; loop++)//检查光源开关状态
	{	
		if (LightSource[loop].L_OnOff)//光源开
		{		
			CRGBA I = CRGBA(0.0, 0.0, 0.0);// I代表“反射”光强
			CVector3 L(Point, LightSource[loop].L_Position);// L为光矢量
			double d = L.Magnitude();// d为光传播的距离 
			L = L.Normalize();//规范化光矢量
			CVector3 N = Normal;
			N = N.Normalize();//规范化法矢量
			//第1步，加入漫反射光
			double NdotL = MAX(DotProduct(L, N), 0);			
			I += LightSource[loop].L_Diffuse * pMaterial->M_Diffuse * NdotL;
			//第2步，加入镜面反射光
			CVector3 V(Point, ViewPoint);//V为视矢量
			V = V.Normalize();//规范化视矢量
			CVector3 H = (L + V) / (L + V).Magnitude();// H为中值矢量
			double NdotH = MAX(DotProduct(N, H), 0);
			double NdotV = MAX(DotProduct(N, V), 0);
			double VdotH = MAX(DotProduct(V, H), 0);
			if(NdotL > 0.0 && NdotV > 0.0)
			{
				// fresnel项
				double F = pMaterial->M_f + (1.0 - pMaterial->M_f) * pow(1.0 - VdotH, 5.0);
				//beckmann分布函数 
				double r1 = 1.0 / (pMaterial->M_k * pMaterial->M_k * pow(NdotH, 4.0));
				double r2 = (NdotH * NdotH - 1.0) / (pMaterial->M_k * pMaterial->M_k * NdotH * NdotH);
				double D = r1 * exp(r2);
				//几何衰减
				double Gm = (2.0 * NdotH * NdotV) / VdotH;
				double Gs = (2.0 * NdotH * NdotL) / VdotH;
				double G = MIN(1.0, MIN(Gm, Gs));				  
				double Rs = (F * D * G) / (NdotV * NdotL * PI);
				I += LightSource[loop].L_Specular * pMaterial->M_Specular * Rs;
			}
			//第3步，光强衰减
			double c0 = LightSource[loop].L_C0;//c0为常数衰减因子
			double c1 = LightSource[loop].L_C1;//c1为线性衰减因子
			double c2 = LightSource[loop].L_C2;//c2为二次衰减因子			
			double f = (1.0/(c0 + c1 * d + c2 * d * d));//光强衰减函数
			f = MIN(1.0, f);
			ResultI += I * f;
		}
		else
			ResultI += Point.c;//物体自身颜色		
	}
	//第4步，加入环境光
	ResultI += Ambient * pMaterial->M_Ambient;
	//第5步，光强规范化到[0,1]区间
	ResultI.Normalize();
	//第6步，返回所计算顶点的最终的光强颜色
	return ResultI;
}
