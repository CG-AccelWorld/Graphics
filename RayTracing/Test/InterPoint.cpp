#include "stdafx.h"
#include "InterPoint.h"


CInterPoint::CInterPoint()
{
   t = 100000;
   IntersectionPoint = CP3(0,0,0);
   Nformal = CVector(0,0,0);
}

CInterPoint::~CInterPoint()
{

}