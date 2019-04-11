#include "StdAfx.h"
#include "ZBuffer.h"
#include "math.h"
#define Round(d) int(floor(d + 0.5))

CZBuffer::CZBuffer(void)
{
	zBuffer=NULL;
}
CZBuffer::~CZBuffer(void)
{
	for(int i=0;i<Width;i++)
	{
		delete[] zBuffer[i];
		zBuffer[i]=NULL;
	}
	if(zBuffer!=NULL)
	{
		delete zBuffer;
		zBuffer=NULL;
	}	
}
void CZBuffer::SetPoint(CPi3 P0,CPi3 P1,CPi3 P2,CVector3 N0,CVector3 N1,CVector3 N2)//三角形初始化
{
	point0.x = Round(P0.x);
	point0.y = Round(P0.y);
	point0.z = Round(P0.z);
	point0.c = P0.c;
	point0.N = N0;
	point1.x = Round(P1.x);
	point1.y = Round(P1.y);
	point1.z = Round(P1.z);
	point1.c = P1.c;
	point1.N = N1;
	point2.x = Round(P2.x);
	point2.y = Round(P2.y);
	point2.z = Round(P2.z);
	point2.c = P2.c;
	point2.N = N2;
	V0 = P0, V1 = P1, V2 = P2;
}

void CZBuffer::PhongShading(CDC* pDC,CP3 ViewPoint,CLighting* pLight,CMaterial* pMaterial,BOOL Sign)
{
	double	CurrentDepth = 0.0;//当前扫描线的深度
	CVector3 Vector01(V0,V1),Vector02(V0, V2);
	CVector3 fNormal = Cross(Vector01,Vector02);
	double A = fNormal.x, B = fNormal.y, C = fNormal.z;//平面方程Ax+By+Cz＋D=0的系数
	double D = -A * V0.x - B * V0.y - C * V0.z;//当前扫描线随着x增长的深度步长
	if (fabs(C) < 1e-4)
		C = 1.0;
	double DepthStep = -A/C;//计算扫描线深度步长增量
	//三点能构成三角形
	if(point0 != point1 && point0 != point2 && point1 != point2)	//重载了 ！= 运算符
	{
		//point0点为y坐标最小的点,point1点为y坐标最大的点,point2点的y坐标位于二者之间。如果y值相同，取x最小的点
		SortVertex();
		//定义三角形覆盖的扫描线条数
		int nTotalLine = point1.y - point0.y + 1;
		//定义span的起点与终点数组
		pLeft  = new CPoint2[nTotalLine];
		pRight = new CPoint2[nTotalLine];		
		//判断三角形与P0P1边的位置关系，0-1-2为右手系
		int nDeltz = (point1.x - point0.x) * (point2.y - point1.y) - (point1.y - point0.y) * (point2.x - point1.x);//点矢量叉积的z坐标
		if(nDeltz > 0)//三角形位于P0P1边的左侧
		{
			nIndex = 0;
			EdgeFlag(point0, point2, TRUE);
			EdgeFlag(point2, point1, TRUE);
			nIndex = 0;
			EdgeFlag(point0, point1, FALSE);
		}
		else//三角形位于P0P1边的右侧
		{
			nIndex = 0;
			EdgeFlag(point0, point1, TRUE);
			nIndex = 0;	
			EdgeFlag(point0, point2, FALSE);
			EdgeFlag(point2, point1, FALSE);
		}
		for(int y = point0.y ; y < point1.y; y++)//下闭上开
		{	
			int n = y - point0.y;
			BOOL bInFlag = FALSE;//跨度内外测试标志，初始值为假表示三角形外部
			for(int x = pLeft[n].x; x < pRight[n].x; x++)//左闭右开
			{
				if(bInFlag == FALSE)
				{
					CurrentDepth = -(A*x + B*y +D)/C;//z=-(Ax+By+D)/C
					bInFlag = TRUE;
					x -= 1;
				}
				else
				{
					CVector3 ptNormal = LinearInterpolation (x, pLeft[n].x, pRight[n].x, pLeft[n].N, pRight[n].N);
					ptNormal = ptNormal.Normalize();
					CRGB clr = pLight->Lighting(ViewPoint,CP3(Round(x),y,CurrentDepth),ptNormal,pMaterial,Sign);
					if(CurrentDepth<=zBuffer[Round(x)+Width/2][Round(y)+Height/2])//如果当前采样点的深度小于帧缓冲器中原采样点的深度
					{
						zBuffer[Round(x)+Width/2][Round(y)+Height/2]=CurrentDepth;//使用当前采样点的深度更新深度缓冲器
						if(Sign)
							pDC->SetPixelV(Round(x)+200,Round(y),RGB(clr.red*255,clr.green*255,clr.blue*255));//绘制当前采样点
						else
							pDC->SetPixelV(Round(x)-200,Round(y),RGB(clr.red*255,clr.green*255,clr.blue*255));//绘制当前采样点
					}
					CurrentDepth+=DepthStep;
				}
			}
		}		
		if(pLeft)
		{
			delete []pLeft;
			pLeft = NULL;
		}
		if(pRight)
		{
			delete []pRight;
			pRight = NULL;
		}
	}
}

void CZBuffer::EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature)
{
	CVector3 ptNormal = PStart.N;
	int dx = abs(PEnd.x - PStart.x);
	int dy = abs(PEnd.y - PStart.y);
	BOOL bInterChange = FALSE;//bInterChange为假，主位移方向为x方向
	int e, s1, s2, temp;
	s1 = (PEnd.x > PStart.x) ? 1 :((PEnd.x < PStart.x) ? -1 : 0);
	s2 = (PEnd.y > PStart.y) ? 1 :((PEnd.y < PStart.y) ? -1 : 0);
	if(dy > dx)//bInterChange为真，主位移方向为y方向
	{
		temp = dx;
		dx = dy;
		dy = temp;
		bInterChange = TRUE;
	}
	e = -dx;
	int x = PStart.x , y  = PStart.y;
	for(int i = 0;i < dx; i++)
	{
		if(bFeature)
			pLeft[nIndex] = CPoint2(x, y, ptNormal);
		else
			pRight[nIndex] = CPoint2(x, y, ptNormal);
		if(bInterChange)
		{
			y += s2;
			ptNormal = LinearInterpolation(y, PStart.y, PEnd.y, PStart.N, PEnd.N);
			if(bFeature)
				pLeft[++nIndex] = CPoint2(x, y, ptNormal);
			else
				pRight[++nIndex] = CPoint2(x, y, ptNormal);
		}
		else 
		{
			x += s1;
			ptNormal = LinearInterpolation(x, PStart.x, PEnd.x, PStart.N, PEnd.N);			
		}
		e += 2 * dy;
		if(e >= 0)
		{
			if(bInterChange)
			{
				x += s1;
				ptNormal = LinearInterpolation(y, PStart.y, PEnd.y, PStart.N, PEnd.N);
			}
			else
			{
				y += s2;
				ptNormal = LinearInterpolation(x, PStart.x, PEnd.x, PStart.N, PEnd.N);
				if(bFeature)
					pLeft[++nIndex] = CPoint2(x, y, ptNormal);
				else
					pRight[++nIndex] = CPoint2(x, y, ptNormal);
			}
			e -= 2 * dx;
		}
	}
}

CRGB CZBuffer::LinearInterpolation (double t, double tStart, double tEnd, CRGB intensityStart, CRGB intensityEnd)//光强线性插值
{
	CRGB Intensity;
	Intensity = (tEnd - t) / (tEnd - tStart) * intensityStart + (t - tStart) / (tEnd - tStart) * intensityEnd;
	return Intensity;
}

CVector3 CZBuffer::LinearInterpolation (double t, double tStart, double tEnd, CVector3 vStart, CVector3 vEnd)//光强线性插值
{
	CVector3 vector;
	vector = (tEnd - t) / (tEnd - tStart) * vStart + (t - tStart) / (tEnd - tStart) * vEnd;
	return vector;
}

void CZBuffer::SortVertex()
{
	CPoint2 p[3];
	p[0] = point0;
	p[1] = point1;
	p[2]  = point2;
	for(int i = 0; i < 2; ++i)
	{
		int k = i;
		for(int j = i + 1;j < 3; ++j)
		{
			if(p[k].y > p[j].y)
				k = j;
			if(p[k].y == p[j].y)
				if(p[k].x > p[j].x)
					k = j;
		}
		if(k != i)
		{
			CPoint2 pTemp = p[i];
			p[i] = p[k];
			p[k] = pTemp;
		}
	}
	point0 = p[0];
	point1 = p[2];
	point2  = p[1];
}

void CZBuffer::InitDeepBuffer(int Width,int Height,double Depth)//初始化深度缓冲
{
	this->Width=Width,this->Height=Height;
	zBuffer=new double *[Width];
	for(int i=0;i<Width;i++)
		zBuffer[i]=new double[Height];
	for(int i=0;i<Width;i++)//初始化深度缓冲
		for(int j=0;j<Height;j++)
			zBuffer[i][j]=Depth;
}