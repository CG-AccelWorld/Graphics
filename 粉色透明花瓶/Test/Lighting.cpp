#include "StdAfx.h"
#include "Lighting.h"
#include <math.h>
#define  PI  3.14159265
#define  MIN(a,b)  ((a<b)?(a):(b))
#define  MAX(a,b)  ((a>b)?(a):(b))

CLighting::CLighting()
{
	LightNum=1;
	Light=new CLight[LightNum];
	Ambient=CRGB(0.3,0.3,0.3);//环境光恒定不变
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

CRGB CLighting::Lighting(CP3 ViewPoint,CP3 Point,CVector Normal,CMaterial *pMaterial,BOOL M,CRGB InitC)
{
	

	if(M)
	{
		LastC=pMaterial->M_Emit;//材质自身发散色为初始值	
		 for(int i=0;i<LightNum;i++)//来自光源
		{	
		if(Light[i].L_OnOff)
		{	
			
			CVector VL(Point,Light[i].L_Position);//VL为指向光源的矢量
			double d=VL.Mag();//d为光传播的距离，等于光矢量VL的模
			VL=VL.Normalize();//单位化光矢量
			CVector VN=Normal;
			VN=VN.Normalize();//单位化法矢量			
			//第1步，加入漫反射光
			double CosTheta=MAX(Dot(VL,VN),0);			
			InitC+=Light[i].L_Diffuse*pMaterial->M_Diffuse*CosTheta;
			
			//第2步，加入镜面反射光
				//CVector VV(Point,ViewPoint);//VV为视矢量
				//VV=VV.Normalize();//单位化视矢量
				//CVector VH=(VL+VV)/(VL+VV).Mag();//VH为平分矢量	
				//double nHN=pow(max(Dot(VH,VN),0),pMaterial->M_n);
				//InitC+=Light[i].L_Specular*pMaterial->M_Specular*nHN;
			
			//第3步，光强衰减
			//double c0=Light[i].L_C0;//c0为常数衰减因子
			//double c1=Light[i].L_C1;//c1线性衰减因子
			//double c2=Light[i].L_C2;//c2二次衰减因子			
			//double f=(1.0/(c0+c1*d+c2*d*d));//光强衰减函数
			//f=MIN(1.0,f);		
			//LastC+=InitC*f;		
		}
		else
			LastC+=Point.c;//物体自身颜色		
	}
	//第4步，加入环境光
		LastC+=Ambient*pMaterial->M_Ambient;
		LastC.Normalize();		
	//第6步，返回所计算顶点的光强颜色
	return LastC;

	}
	else
	{
		  for(int i=0;i<LightNum;i++)//来自光源
		{	
			if(Light[i].L_OnOff)
			{
			CVector VL(Point,Light[i].L_Position);//VL为指向光源的矢量
			double d=VL.Mag();//d为光传播的距离，等于光矢量VL的模
			VL=VL.Normalize();//单位化光矢量
			CVector VN=Normal;
			VN=VN.Normalize();//单位化法矢量	
			CVector VV(Point,ViewPoint);//VV为视矢量
			VV=VV.Normalize();//单位化视矢量
			CVector VH=(VL+VV)/(VL+VV).Mag();//VH为平分矢量	
			double nHN=pow(max(Dot(VH,VN),0),pMaterial->M_n);
			InitC+=Light[i].L_Specular*pMaterial->M_Specular*nHN;
			double c0=Light[i].L_C0;//c0为常数衰减因子
			double c1=Light[i].L_C1;//c1线性衰减因子
			double c2=Light[i].L_C2;//c2二次衰减因子			
			double f=(1.0/(c0+c1*d+c2*d*d));//光强衰减函数
			f=MIN(1.0,f);		
			LastC+=InitC*f;
			
			}
		 }
			LastC.Normalize();
			return LastC; 
		 
	}
		
}