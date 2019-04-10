#include "stdafx.h"
#include "Sphere.h"
#include "math.h"

CSphere::CSphere()
{
}
CSphere::~CSphere()
{
}
CSphere::CSphere(double r, CP3 positionP,CMaterial pMaterial)
{
	this->r = r;
	this->positionP = positionP;
	this->pMaterial = pMaterial;
} 
//除起始点外没交点就返回false，有交点就返回true
bool CSphere::GetInterPoint(CRay ray,CInterPoint &InPoint) //获取 直线 与 球的交点
{
	bool sign = false;
	CVector mid(ray.origin.x - positionP.x, ray.origin.y - positionP.y, ray.origin.z - positionP.z);

	double a = 1, 
		b = 2.0*(mid.x*ray.dir.x + mid.y*ray.dir.y + mid.z*ray.dir.z), 
		c = mid.x*mid.x + mid.y*mid.y + mid.z*mid.z - r*r;

	double flag = b*b-4*a*c;

	if (flag >= 0)
	{
		double ans1 = -(b+sqrt(flag))/2.0;
		double ans2 = -(b-sqrt(flag))/2.0;

	//	hit.surface = *this;
		
		if (ans1 > 0.00001)
		{
			InPoint.t = ans1;
			InPoint.IntersectionPoint = ray.GetPoint(InPoint.t);   //交点坐标
            InPoint.Nformal = CVector(positionP,InPoint.IntersectionPoint);//交点的法矢量
			InPoint.type = 1;
		}
		else if (fabs(ans1) < 0.00001 && ans2 > 0.00001)
		{
			InPoint.t = ans2;
			InPoint.IntersectionPoint = ray.GetPoint(InPoint.t);
            InPoint.Nformal = CVector(InPoint.IntersectionPoint,positionP);//交点的法矢量		
			InPoint.type = 0;
		}
		else
		{
			return false;
		}

	    InPoint.pMaterial = this->pMaterial;
		return true;
	}
	return false;

}
