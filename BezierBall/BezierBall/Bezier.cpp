#include "StdAfx.h"
#include "Bezier.h"
#include "math.h"
#define Round(a) int(floor(a+0.5))

Bezier::Bezier(void)
{
}


Bezier::~Bezier(void)
{
}
Bezier::Bezier(CP3 M[][4])
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			P3[i][j]=M[i][j];
		}
	}
}
void Bezier::ObliqueProjection()//什么是斜等测投影??? 
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			//P2[i][j].x=P3[i][j].x-P3[i][j].z/sqrt(2.0);
			//P2[i][j].y=P3[i][j].y-P3[i][j].z/sqrt(2.0);
			P2[i][j].x=P3[i][j].x;
			P2[i][j].y=P3[i][j].y;
		}
}
void Bezier::LeftMultiMatrix(double M0[][4],CP3 P0[][4])//左乘矩阵M*P
{
	CP3 T[4][4];//临时矩阵
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{	
			T[i][j].x=M0[i][0]*P0[0][j].x+M0[i][1]*P0[1][j].x+M0[i][2]*P0[2][j].x+M0[i][3]*P0[3][j].x;	
			T[i][j].y=M0[i][0]*P0[0][j].y+M0[i][1]*P0[1][j].y+M0[i][2]*P0[2][j].y+M0[i][3]*P0[3][j].y;
			T[i][j].z=M0[i][0]*P0[0][j].z+M0[i][1]*P0[1][j].z+M0[i][2]*P0[2][j].z+M0[i][3]*P0[3][j].z;
		}
	}
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			P3[i][j]=T[i][j];
}

void Bezier::RightMultiMatrix(CP3 P0[][4],double M1[][4])//右乘矩阵P*M
{
	CP3 T[4][4];//临时矩阵
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{	
			T[i][j].x=P0[i][0].x*M1[0][j]+P0[i][1].x*M1[1][j]+P0[i][2].x*M1[2][j]+P0[i][3].x*M1[3][j];
			T[i][j].y=P0[i][0].y*M1[0][j]+P0[i][1].y*M1[1][j]+P0[i][2].y*M1[2][j]+P0[i][3].y*M1[3][j];
			T[i][j].z=P0[i][0].z*M1[0][j]+P0[i][1].z*M1[1][j]+P0[i][2].z*M1[2][j]+P0[i][3].z*M1[3][j];
		}
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			P3[i][j]=T[i][j];
}
void Bezier::TransposeMatrix(double M0[][4])//转置矩阵
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			MT[j][i]=M0[i][j];
}
void Bezier::DrawCtrlPolygon(CDC *pDC)
{
	P3[4][4];
	ObliqueProjection();
	CPen NewPen,*pOldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,255,0));
	pOldPen=pDC->SelectObject(&NewPen); 
	for(int i=0;i<4;i++)//固定一个，画出另一个
	{
		pDC->MoveTo(Round(P2[i][0].x),Round(P2[i][0].y));
		for(int j=1;j<4;j++)
			pDC->LineTo(Round(P2[i][j].x),Round(P2[i][j].y));
	}
	for(int j=0;j<4;j++)
	{
		pDC->MoveTo(Round(P2[0][j].x),Round(P2[0][j].y));
		for(int i=1;i<4;i++)
			pDC->LineTo(Round(P2[i][j].x),Round(P2[i][j].y));
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}
void Bezier::DrawObject(CDC *pDC)//绘制双三次Bezier曲面	
{
	CPen NewPen,*pOldPen;
	NewPen.CreatePen(PS_SOLID,1,RGB(255,0,0));
	pOldPen = pDC->SelectObject(&NewPen);
	double x,y,u,v,u1,u2,u3,u4,v1,v2,v3,v4;
	double M[4][4];
	M[0][0]=-1;M[0][1]=3; M[0][2]=-3;M[0][3]=1;
	M[1][0]=3; M[1][1]=-6;M[1][2]=3; M[1][3]=0;
	M[2][0]=-3;M[2][1]=3; M[2][2]=0; M[2][3]=0;
	M[3][0]=1; M[3][1]=0; M[3][2]=0; M[3][3]=0;
	LeftMultiMatrix(M,P3);//数字矩阵左乘三维点矩阵
	TransposeMatrix(M);//计算转置矩阵
	RightMultiMatrix(P3,MT);//数字矩阵右乘三维点矩阵
	ObliqueProjection();//轴侧投影？？？
	for(u=0;u<=1;u+=0.1)
		for(v=0;v<=1;v+=0.1)
		{
			u1=u*u*u;u2=u*u;u3=u;u4=1;v1=v*v*v;v2=v*v;v3=v;v4=1;
			x=(u1*P2[0][0].x+u2*P2[1][0].x+u3*P2[2][0].x+u4*P2[3][0].x)*v1
			 +(u1*P2[0][1].x+u2*P2[1][1].x+u3*P2[2][1].x+u4*P2[3][1].x)*v2
			 +(u1*P2[0][2].x+u2*P2[1][2].x+u3*P2[2][2].x+u4*P2[3][2].x)*v3
			 +(u1*P2[0][3].x+u2*P2[1][3].x+u3*P2[2][3].x+u4*P2[3][3].x)*v4;
			y=(u1*P2[0][0].y+u2*P2[1][0].y+u3*P2[2][0].y+u4*P2[3][0].y)*v1
			 +(u1*P2[0][1].y+u2*P2[1][1].y+u3*P2[2][1].y+u4*P2[3][1].y)*v2
			 +(u1*P2[0][2].y+u2*P2[1][2].y+u3*P2[2][2].y+u4*P2[3][2].y)*v3
			 +(u1*P2[0][3].y+u2*P2[1][3].y+u3*P2[2][3].y+u4*P2[3][3].y)*v4;
			if(v==0)

				pDC->MoveTo(Round(x),Round(y));
			else
				
				pDC->LineTo(Round(x),Round(y));
		}		  
	for(v=0;v<=1;v+=0.1)
		for(u=0;u<=1;u+=0.1)
		{
			u1=u*u*u;u2=u*u;u3=u;u4=1;v1=v*v*v;v2=v*v;v3=v;v4=1;
			x=(u1*P2[0][0].x+u2*P2[1][0].x+u3*P2[2][0].x+u4*P2[3][0].x)*v1
			 +(u1*P2[0][1].x+u2*P2[1][1].x+u3*P2[2][1].x+u4*P2[3][1].x)*v2
			 +(u1*P2[0][2].x+u2*P2[1][2].x+u3*P2[2][2].x+u4*P2[3][2].x)*v3
			 +(u1*P2[0][3].x+u2*P2[1][3].x+u3*P2[2][3].x+u4*P2[3][3].x)*v4;
			y=(u1*P2[0][0].y+u2*P2[1][0].y+u3*P2[2][0].y+u4*P2[3][0].y)*v1
			 +(u1*P2[0][1].y+u2*P2[1][1].y+u3*P2[2][1].y+u4*P2[3][1].y)*v2
			 +(u1*P2[0][2].y+u2*P2[1][2].y+u3*P2[2][2].y+u4*P2[3][2].y)*v3
			 +(u1*P2[0][3].y+u2*P2[1][3].y+u3*P2[2][3].y+u4*P2[3][3].y)*v4;
			if(0==u)
				pDC->MoveTo(Round(x),Round(y));
			else
				pDC->LineTo(Round(x),Round(y));
		}
		pDC->SelectObject(pOldPen);
		NewPen.DeleteObject();
}

