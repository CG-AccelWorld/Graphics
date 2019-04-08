#include "StdAfx.h"
#include "BicubicBezierPatch.h"
#include <math.h>
#define ROUND(d) int(floor(d+0.5))

CBicubicBezierPatch::CBicubicBezierPatch(void)
{
}


CBicubicBezierPatch::~CBicubicBezierPatch(void)
{
}

void CBicubicBezierPatch::ReadControlPoint(CP3 P[4][4])
{
   for(int i=0;i<4;i++)
	   for(int j=0;j<4;j++)
   			this->P[i][j]=P[i][j];
}
void CBicubicBezierPatch::DrawCurvedPatch(CDC* pDC,CP3 ViewPoint,CLighting *pLight,CMaterial *pMaterial)
 {
	/* CPen pen(PS_SOLID,1,RGB(255,0,0)),*pOldPen;
	pOldPen=pDC->SelectObject(&pen);*/
	double M[4][4];//系数矩阵Mbe
	M[0][0]=-1;M[0][1]=3; M[0][2]=-3;M[0][3]=1;
	M[1][0]=3; M[1][1]=-6;M[1][2]=3; M[1][3]=0;
	M[2][0]=-3;M[2][1]=3; M[2][2]=0; M[2][3]=0;
	M[3][0]=1; M[3][1]=0; M[3][2]=0; M[3][3]=0;
	CP3 P3[4][4];//曲线计算用控制点数组
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P3[i][j]=P[i][j];
	LeftMultiplyMatrix(M,P3);//数字矩阵左乘三维点矩阵
	TransposeMatrix(M);//计算转置矩阵
	RightMultiplyMatrix(P3,M);//数字矩阵右乘三维点矩阵
	double Step =0.1;//步长
	double u0,u1,u2,u3,v0,v1,v2,v3;//u，v参数的幂
	for(double u=0;u<=1;u+=Step)
	{
		for(double v=0;v<=1;v+=Step)
		{
			u3=u*u*u,u2=u*u,u1=u,u0=1;
			v3=v*v*v,v2=v*v,v1=v,v0=1;
			CP3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;
			
			PV[ROUND(u*10)*11 + ROUND(v*10)]=pt;
			u3=3*u*u,u2=2*u,u1=1,u0=0;
			v3=v*v*v,v2=v*v,v1=v,v0=1;
			CP3 p1=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;
			CVector vecU(p1.x,p1.y,p1.z);
			u3=u*u*u,u2=u*u,u1=u,u0=1;
			v3=3*v*v,v2=2*v,v1=1,v0=0;
			CP3 p2=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
			          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
			          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
			          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;
			CVector vecV(p2.x,p2.y,p2.z);
		//	PV[ROUND(u*10)*11 + ROUND(v*10)].c=pLight->Lighting(ViewPoint,PV[ROUND(u*10)*11 + ROUND(v*10)],Cross(vecV,vecU),pMaterial);//调用光照函数
			PV[ROUND(u*10)*11 + ROUND(v*10)].c.alpha=0.3+0.6*(1-pow((1-fabs(Cross(vecV,vecU).Normalize().z)),3));
			NV[ROUND(u*10)*11 + ROUND(v*10)]=Cross(vecV,vecU);
		}
	//		CP2 Point2=ObliqueProjection(pt);//斜投影
	//		if(v==0)
	//			pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));
	//		else
	//			pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
	//	}		  
	//for(double v=0;v<=1;v+=Step)
	//	for(double u=0;u<=1;u+=Step)
	//	{
	//		u3=u*u*u;u2=u*u;u1=u;u0=1;v3=v*v*v;v2=v*v;v1=v;v0=1;
	//		CP3 pt=(u3*P3[0][0]+u2*P3[1][0]+u1*P3[2][0]+u0*P3[3][0])*v3
	//		          +(u3*P3[0][1]+u2*P3[1][1]+u1*P3[2][1]+u0*P3[3][1])*v2
	//		          +(u3*P3[0][2]+u2*P3[1][2]+u1*P3[2][2]+u0*P3[3][2])*v1
	//		          +(u3*P3[0][3]+u2*P3[1][3]+u1*P3[2][3]+u0*P3[3][3])*v0;			
	//		CP2 Point2=ObliqueProjection(pt);//斜投影    
	//		if(0==u)
	//			pDC->MoveTo(ROUND(Point2.x),ROUND(Point2.y));
	//		else
	//			pDC->LineTo(ROUND(Point2.x),ROUND(Point2.y));
	//	}
	//	pDC->SelectObject(pOldPen);
	}
}

void CBicubicBezierPatch::LeftMultiplyMatrix(double M[][4],CP3 P[][4])//左乘矩阵M*P
{
	CP3 T[4][4];//临时矩阵
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			T[i][j]=M[i][0]*P[0][j]+M[i][1]*P[1][j]+M[i][2]*P[2][j]+M[i][3]*P[3][j];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P[i][j]=T[i][j];
}

void CBicubicBezierPatch::RightMultiplyMatrix(CP3 P[][4],double M[][4])//右乘矩阵P*M
{
	CP3 T[4][4];//临时矩阵
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			T[i][j]=P[i][0]*M[0][j]+P[i][1]*M[1][j]+P[i][2]*M[2][j]+P[i][3]*M[3][j];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			P[i][j]=T[i][j];
}

void CBicubicBezierPatch::TransposeMatrix(double M[][4])//转置矩阵
{
	double T[4][4];//临时矩阵
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			T[j][i]=M[i][j];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			M[i][j]=T[i][j];
}

//CP2 CBicubicBezierPatch::ObliqueProjection(CP3 Point3)//斜二测投影
//{
//	CP2 Point2;
//	Point2.x=Point3.x;
//	Point2.y=Point3.y;
//	return Point2;
//}
//
//void CBicubicBezierPatch::DrawControlGrid(CDC* pDC)//绘制控制网格
//{
//	CP2 P2[4][4];//二维控制点
//	for(int i=0;i<4;i++)
//		for(int j=0;j<4;j++)
//			P2[i][j]=ObliqueProjection(P[i][j]);
//	CPen NewPen,*pOldPen;
//	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));
//	pOldPen=pDC->SelectObject(&NewPen);
//	for(int i=0;i<4;i++)
//	{
//		pDC->MoveTo(ROUND(P2[i][0].x),ROUND(P2[i][0].y));
//		for(int j=1;j<4;j++)
//			pDC->LineTo(ROUND(P2[i][j].x),ROUND(P2[i][j].y));
//	}
//	for(int j=0;j<4;j++)
//	{
//		pDC->MoveTo(ROUND(P2[0][j].x),ROUND(P2[0][j].y));
//		for(int i=1;i<4;i++)
//			pDC->LineTo(ROUND(P2[i][j].x),ROUND(P2[i][j].y));
//	}
//	pDC->SelectObject(pOldPen);
//	NewPen.DeleteObject();
//}