#include "stdafx.h"
#include "Plane.h"
#include "math.h"
#define Round(d) int(floor(d+0.5))


CPlane::CPlane(void)
{
}

CPlane::CPlane(double r, CP3 positionP,CMaterial pMaterial,double X_min,double X_max,double Y_min,double Y_max,double Z_min,double Z_max)
{
	this->r = r;
	this->positionP = positionP;
	this->pMaterial = pMaterial;
	this->X_min = X_min;
	this->X_max = X_max;
	this->Y_min = Y_min;
	this->Y_max = Y_max;
	this->Z_min = Z_min;
	this->Z_max = Z_max;
} 
CPlane::~CPlane(void)
{
}
bool CPlane::GetInterPoint(CRay ray,CInterPoint &InPoint) //获取 直线 与 面的交点
{
	CInterPoint InPoint1;
	bool sign = false;
	//曲面法矢量与光线的交点
	double mid=DotProduct(positionP,ray.dir);
	if(mid != 0)//光线与曲面有交点
	{
		//t=-(N*O+d)/(N*V)
		double ans=-(DotProduct(positionP,ray.origin)+r)/mid;
		if(ans>0.00001)
		{
			InPoint1.t = ans;
			InPoint1.IntersectionPoint = ray.GetPoint(InPoint1.t);   //交点坐标
			InPoint1.Nformal = CVector(positionP);//交点的法矢量
			InPoint1.type = 1;
		}

		if(Round(InPoint1.IntersectionPoint.x)>=X_min&&Round(InPoint1.IntersectionPoint.x)<=X_max
			&&Round(InPoint1.IntersectionPoint.y)>=Y_min&&Round(InPoint1.IntersectionPoint.y)<=Y_max
			&&Round(InPoint1.IntersectionPoint.z)>=Z_min&&Round(InPoint1.IntersectionPoint.z)<=Z_max)
		{
			InPoint=InPoint1;
 			InPoint.pMaterial = this->pMaterial;
			{
				if(1==(Round((InPoint1.IntersectionPoint.x+400)/80)+Round((InPoint1.IntersectionPoint.z+1600)/80))%2)
				{
					InPoint.pMaterial.SetAmbient(CRGB(0.0,255.0,0.0));//材质对环境光的反射率
					InPoint.pMaterial.SetDiffuse(CRGB(0.0,255.0,0.0));//材质对环境光和漫反射光的反射率相等
					InPoint.pMaterial.SetSpecular(CRGB(0.0,255.0,0.0));//材质对镜面反射光的反射率
					InPoint.pMaterial.SetEmit(CRGB(0.0,255.0,0.0));//材质自身发散的颜色
				}
					
				if(0==(Round((InPoint1.IntersectionPoint.x+400)/80)+Round((InPoint1.IntersectionPoint.z+1600)/80))%2)
				{
					InPoint.pMaterial.SetAmbient(CRGB(0.0,0.0,0.0));//材质对环境光的反射率
					InPoint.pMaterial.SetDiffuse(CRGB(0.0,0.0,0.0));//材质对环境光和漫反射光的反射率相等
					InPoint.pMaterial.SetSpecular(CRGB(0.0,0.0,0.0));//材质对镜面反射光的反射率
					InPoint.pMaterial.SetEmit(CRGB(0.0,0.0,0.0));//材质自身发散的颜色

				}
				InPoint.pMaterial.M_n=50.0;//高光指数
				InPoint.pMaterial.sigma = 0;

			}
			return true;
		}
	}
		return false;
}
