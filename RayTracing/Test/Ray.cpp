#include "stdafx.h"
#include "Ray.h"
#include "math.h"

CRay::CRay()
{
}

CRay::~CRay()
{

}
CRay::CRay(CP3 origin, CVector dir)
{
	this->origin = origin;
	this->dir    = dir;
}
CP3 CRay::GetPoint(double t)
{
	CP3 ans;
	ans.x = origin.x + t*dir.x;
	ans.y = origin.y + t*dir.y;
	ans.z = origin.z + t*dir.z;

	return ans;
}
void CRay::Normalized()
{
	double factor = sqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
	dir.x/=factor;
	dir.y/=factor;
	dir.z/=factor;
}
