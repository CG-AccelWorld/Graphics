#pragma once
#include "P3.h"
#include "BicubicBezierPatch.h"
#include "Facet.h"
class CRevolution
{
public:
	CRevolution(void);
	~CRevolution(void);
	void ReadCubicBezierControlPoint(CP3*ctrP);
	void ReadControlPoint(CP3*ctrP);
	void ReadPoint();
	void ReadVertex();
	void ReadPatch();
	void DrawRevolutionSurface(CDC*pDC,CP3 ViewPoint,CLighting *pLight,CMaterial *pMaterial);
public:
	CP3 V[64];
	CP3 MV[4][121];
	CVector Nv[4][121];
private:
	CP3 P[4];
	Facet S[4];
	CP3 P3[4][4];
	CBicubicBezierPatch surf;
	
};

