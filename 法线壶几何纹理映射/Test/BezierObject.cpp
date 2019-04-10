#include "StdAfx.h"
#include "BezierObject.h"
#include "math.h"//数学头文件
#define Round(d) int(floor(d+0.5))//四舍五入宏定义
#define nNum  4//三次B 4个控制点
#define PI 3.1415926


CBezierObject::CBezierObject()
{
	Vertex = NULL;
	P = NULL;
	Patch = NULL;
	LightNum=2;//光源个数
	pLight=new CLighting(LightNum);//一维光源动态数组
	pLight->Light[0].SetPosition(500,500,800);//设置光源位置坐标	
	pLight->Light[1].SetPosition(-500,-500,800);//设置光源位置坐标	
	for(int i=0;i<LightNum;i++)
	{
		pLight->Light[i].L_Diffuse=CRGB(1.0,1.0,1.0);//光源的漫反射颜色	
		pLight->Light[i].L_Specular=CRGB(1.0,1.0,1.0);//光源镜面高光颜色
		pLight->Light[i].L_C0=1.0;//常数衰减系数
		pLight->Light[i].L_C1=0.0000001;//线性衰减系数
		pLight->Light[i].L_C2=0.00000001;//二次衰减系数
		pLight->Light[i].L_OnOff=TRUE;//光源开启
	}
	pMaterial1=new CMaterial;//一维材质动态数组
	pMaterial1->SetAmbient(CRGB(0.075,0.012,0.012));//材质对环境光光的反射率
	pMaterial1->SetDiffuse(CRGB(0.041,0.041,0.041));//材质对漫反射光的反射率
	pMaterial1->SetSpecular(CRGB(1.0,1.0,1.0));//材质对镜面反射光的反射率
	pMaterial1->SetEmit(CRGB(0.05,0.05,0.002));//材质自身发散的颜色
	pMaterial1->SetExp(30);//高光指数
}

CBezierObject::~CBezierObject(void)
{
    if (Vertex!=NULL)
    {
		for (int i=0; i < NumObject ; i++)
		{
			delete []Vertex[i]; 
		}
		delete []Vertex;
    }

	if (Patch!=NULL)
	{

		for (int i=0; i < NumObject ; i++)
		{
			delete []Patch[i]; 
		}
		delete []Patch;
	}
	for (int j=0;j<41;j++)
	{
	   delete 	[]FacePoint[j]; //列
	}
    delete []FacePoint;
		for (int j=0;j<41;j++)
	{
	   delete 	[]FaceTPoint[j]; //列
	}
    delete []FaceTPoint;
	delete pMaterial1;
	delete pLight;
}
void CBezierObject::ReadBeizerObject(int num,CP3 **P)
{
	NumObject = num;
	this->P = P;
	Patch = new CFace*[NumObject];
	for (int i=0; i < NumObject ; i++)
	{
		Patch[i] = new CFace[4];
	}

    Vertex = new CP3 *[NumObject];     // 几个部分
	for (int i=0; i < NumObject ; i++)
	{
		Vertex[i] = new CP3[64]; // 每部分 4个面 每面16个点  共64个点
	}
	FacePoint= new CP3*[41];  //   

	for (int j=0;j<41;j++)
	{
		FacePoint[j] = new CP3[41]; //列
	}
	FaceTPoint= new CT2*[41];  //   

	for (int j=0;j<41;j++)
	{
		FaceTPoint[j] = new CT2[41]; //列
	}
	//读入点表
     ReadVertex();
	 ReadPatch();
}
void CBezierObject::ReadVertex()
{
	const double m = 0.5523;
	CP3 P0, P1, P2, P3;

	for (int i = 0; i < NumObject ; i++)
	{
	P0 = P[i][0],	P1 = P[i][1];	P2 = P[i][2];	P3 = P[i][3];
	//1/4
	Vertex[i][0].x = P0.x, Vertex[i][0].y = P0.y, Vertex[i][0].z = P0.z;
	Vertex[i][1].x = P1.x, Vertex[i][1].y = P1.y, Vertex[i][1].z = P1.z;
	Vertex[i][2].x = P2.x, Vertex[i][2].y = P2.y, Vertex[i][2].z = P2.z;
	Vertex[i][3].x = P3.x, Vertex[i][3].y = P3.y, Vertex[i][3].z = P3.z;

	Vertex[i][4].x = Vertex[i][0].x, Vertex[i][4].y = Vertex[i][0].y, Vertex[i][4].z = Vertex[i][0].x * m;
	Vertex[i][5].x = Vertex[i][1].x, Vertex[i][5].y = Vertex[i][1].y, Vertex[i][5].z = Vertex[i][1].x * m;
	Vertex[i][6].x = Vertex[i][2].x, Vertex[i][6].y = Vertex[i][2].y, Vertex[i][6].z = Vertex[i][2].x * m;
	Vertex[i][7].x = Vertex[i][3].x, Vertex[i][7].y = Vertex[i][3].y, Vertex[i][7].z = Vertex[i][3].x * m;

	Vertex[i][8].x = Vertex[i][0].x * m,  Vertex[i][8].y = Vertex[i][0].y,  Vertex[i][8].z = Vertex[i][0].x;
	Vertex[i][9].x = Vertex[i][1].x * m,  Vertex[i][9].y = Vertex[i][1].y,  Vertex[i][9].z = Vertex[i][1].x;
	Vertex[i][10].x =Vertex[i][2].x * m,  Vertex[i][10].y = Vertex[i][2].y, Vertex[i][10].z = Vertex[i][2].x;
	Vertex[i][11].x =Vertex[i][3].x * m,  Vertex[i][11].y = Vertex[i][3].y, Vertex[i][11].z = Vertex[i][3].x;

	Vertex[i][12].x = Vertex[i][0].z,  Vertex[i][12].y = Vertex[i][0].y, Vertex[i][12].z = Vertex[i][0].x;
	Vertex[i][13].x = Vertex[i][1].z,  Vertex[i][13].y = Vertex[i][1].y, Vertex[i][13].z = Vertex[i][1].x;
	Vertex[i][14].x = Vertex[i][2].z,  Vertex[i][14].y = Vertex[i][2].y, Vertex[i][14].z = Vertex[i][2].x;
	Vertex[i][15].x = Vertex[i][3].z,  Vertex[i][15].y = Vertex[i][3].y, Vertex[i][15].z = Vertex[i][3].x;
	//2/4
	Vertex[i][16].x = Vertex[i][0].z,  Vertex[i][16].y = Vertex[i][0].y, Vertex[i][16].z = Vertex[i][0].x;
	Vertex[i][17].x = Vertex[i][1].z,  Vertex[i][17].y = Vertex[i][1].y, Vertex[i][17].z = Vertex[i][1].x;
	Vertex[i][18].x = Vertex[i][2].z,  Vertex[i][18].y = Vertex[i][2].y, Vertex[i][18].z = Vertex[i][2].x;
	Vertex[i][19].x = Vertex[i][3].z,  Vertex[i][19].y = Vertex[i][3].y, Vertex[i][19].z = Vertex[i][3].x;

	Vertex[i][20].x =-Vertex[i][0].x * m, Vertex[i][20].y = Vertex[i][0].y,  Vertex[i][20].z = Vertex[i][0].x;
	Vertex[i][21].x =-Vertex[i][1].x * m, Vertex[i][21].y = Vertex[i][1].y,  Vertex[i][21].z = Vertex[i][1].x;
	Vertex[i][22].x =-Vertex[i][2].x * m, Vertex[i][22].y = Vertex[i][2].y,  Vertex[i][22].z = Vertex[i][2].x;
	Vertex[i][23].x =-Vertex[i][3].x * m, Vertex[i][23].y = Vertex[i][3].y,  Vertex[i][23].z = Vertex[i][3].x;

	Vertex[i][24].x =-Vertex[i][0].x, Vertex[i][24].y = Vertex[i][0].y, Vertex[i][24].z = Vertex[i][0].x * m;
	Vertex[i][25].x =-Vertex[i][1].x, Vertex[i][25].y = Vertex[i][1].y, Vertex[i][25].z = Vertex[i][1].x * m;
	Vertex[i][26].x =-Vertex[i][2].x, Vertex[i][26].y = Vertex[i][2].y, Vertex[i][26].z = Vertex[i][2].x * m;
	Vertex[i][27].x =-Vertex[i][3].x, Vertex[i][27].y = Vertex[i][3].y, Vertex[i][27].z = Vertex[i][3].x * m;

	Vertex[i][28].x =-Vertex[i][0].x, Vertex[i][28].y = Vertex[i][0].y, Vertex[i][28].z = Vertex[i][0].z;
	Vertex[i][29].x =-Vertex[i][1].x, Vertex[i][29].y = Vertex[i][1].y, Vertex[i][29].z = Vertex[i][1].z;
	Vertex[i][30].x =-Vertex[i][2].x, Vertex[i][30].y = Vertex[i][2].y, Vertex[i][30].z = Vertex[i][2].z;
	Vertex[i][31].x =-Vertex[i][3].x, Vertex[i][31].y = Vertex[i][3].y, Vertex[i][31].z = Vertex[i][3].z;
	//3/4
	Vertex[i][32].x =-Vertex[i][0].x, Vertex[i][32].y = Vertex[i][0].y, Vertex[i][32].z = Vertex[i][0].z;
	Vertex[i][33].x =-Vertex[i][1].x, Vertex[i][33].y = Vertex[i][1].y, Vertex[i][33].z = Vertex[i][1].z;
	Vertex[i][34].x =-Vertex[i][2].x, Vertex[i][34].y = Vertex[i][2].y, Vertex[i][34].z = Vertex[i][2].z;
	Vertex[i][35].x =-Vertex[i][3].x, Vertex[i][35].y = Vertex[i][3].y, Vertex[i][35].z = Vertex[i][3].z;

	Vertex[i][36].x =-Vertex[i][0].x, Vertex[i][36].y = Vertex[i][0].y, Vertex[i][36].z =-Vertex[i][0].x * m;
	Vertex[i][37].x =-Vertex[i][1].x, Vertex[i][37].y = Vertex[i][1].y, Vertex[i][37].z =-Vertex[i][1].x * m;
	Vertex[i][38].x =-Vertex[i][2].x, Vertex[i][38].y = Vertex[i][2].y, Vertex[i][38].z =-Vertex[i][2].x * m;
	Vertex[i][39].x =-Vertex[i][3].x, Vertex[i][39].y = Vertex[i][3].y, Vertex[i][39].z =-Vertex[i][3].x * m;

	Vertex[i][40].x =-Vertex[i][0].x * m, Vertex[i][40].y = Vertex[i][0].y,  Vertex[i][40].z =-Vertex[i][0].x;
	Vertex[i][41].x =-Vertex[i][1].x * m, Vertex[i][41].y = Vertex[i][1].y,  Vertex[i][41].z =-Vertex[i][1].x;
	Vertex[i][42].x =-Vertex[i][2].x * m, Vertex[i][42].y = Vertex[i][2].y,  Vertex[i][42].z =-Vertex[i][2].x;
	Vertex[i][43].x =-Vertex[i][3].x * m, Vertex[i][43].y = Vertex[i][3].y,  Vertex[i][43].z =-Vertex[i][3].x;

	Vertex[i][44].x = Vertex[i][0].z,  Vertex[i][44].y = Vertex[i][0].y, Vertex[i][44].z =-Vertex[i][0].x;
	Vertex[i][45].x = Vertex[i][1].z,  Vertex[i][45].y = Vertex[i][1].y, Vertex[i][45].z =-Vertex[i][1].x;
	Vertex[i][46].x = Vertex[i][2].z,  Vertex[i][46].y = Vertex[i][2].y, Vertex[i][46].z =-Vertex[i][2].x;
	Vertex[i][47].x = Vertex[i][3].z,  Vertex[i][47].y = Vertex[i][3].y, Vertex[i][47].z =-Vertex[i][3].x;
	//4/4
	Vertex[i][48].x = Vertex[i][0].z,  Vertex[i][48].y = Vertex[i][0].y, Vertex[i][48].z =-Vertex[i][0].x;
	Vertex[i][49].x = Vertex[i][1].z,  Vertex[i][49].y = Vertex[i][1].y, Vertex[i][49].z =-Vertex[i][1].x;
	Vertex[i][50].x = Vertex[i][2].z,  Vertex[i][50].y = Vertex[i][2].y, Vertex[i][50].z =-Vertex[i][2].x;
	Vertex[i][51].x = Vertex[i][3].z,  Vertex[i][51].y = Vertex[i][3].y, Vertex[i][51].z =-Vertex[i][3].x;

	Vertex[i][52].x = Vertex[i][0].x * m, Vertex[i][52].y = Vertex[i][0].y,  Vertex[i][52].z =-Vertex[i][0].x;
	Vertex[i][53].x = Vertex[i][1].x * m, Vertex[i][53].y = Vertex[i][1].y,  Vertex[i][53].z =-Vertex[i][1].x;
	Vertex[i][54].x = Vertex[i][2].x * m, Vertex[i][54].y = Vertex[i][2].y,  Vertex[i][54].z =-Vertex[i][2].x;
	Vertex[i][55].x = Vertex[i][3].x * m, Vertex[i][55].y = Vertex[i][3].y,  Vertex[i][55].z =-Vertex[i][3].x;

	Vertex[i][56].x = Vertex[i][0].x, Vertex[i][56].y = Vertex[i][0].y, Vertex[i][56].z =-Vertex[i][0].x * m;
	Vertex[i][57].x = Vertex[i][1].x, Vertex[i][57].y = Vertex[i][1].y, Vertex[i][57].z =-Vertex[i][1].x * m;
	Vertex[i][58].x = Vertex[i][2].x, Vertex[i][58].y = Vertex[i][2].y, Vertex[i][58].z =-Vertex[i][2].x * m;
	Vertex[i][59].x = Vertex[i][3].x, Vertex[i][59].y = Vertex[i][3].y, Vertex[i][59].z =-Vertex[i][3].x * m;

	Vertex[i][60].x = Vertex[i][0].x, Vertex[i][60].y = Vertex[i][0].y, Vertex[i][60].z = Vertex[i][0].z;
	Vertex[i][61].x = Vertex[i][1].x, Vertex[i][61].y = Vertex[i][1].y, Vertex[i][61].z = Vertex[i][1].z;
	Vertex[i][62].x = Vertex[i][2].x, Vertex[i][62].y = Vertex[i][2].y, Vertex[i][62].z = Vertex[i][2].z;
	Vertex[i][63].x = Vertex[i][3].x, Vertex[i][63].y = Vertex[i][3].y, Vertex[i][63].z = Vertex[i][3].z;
	}
}


void CBezierObject::ReadPatch()//读入双三次曲面片
{
	for (int i = 0; i < NumObject; i++)
	{
		for (int m = 0 ; m < 4 ; m++)
		{
			Patch[i][m].SetNum(16);
			for (int j = 0; j < 16; j++)
				Patch[i][m].vI[j] = j + m * 16;
		}

	}
}

void CBezierObject::DrawObject(CDC* pDC,CVector **N,int nWidth,int nHeight)
{
	for (int i = 0; i < NumObject; i++)
	{
		for (int m = 0; m < 4 ;m++)
		{
			for (int j = 0; j < 16; j++)
			{
				P3[j] = Vertex[i][Patch[i][m].vI[j]];
			}
	    	BicubicCurvedSurface(pDC,i,m,nWidth,nHeight);//双三次Bezier曲面
		}
	}
	zbuf = new CZBuffer();
	zbuf->InitDeepBuffer(800,800,800);
	zbuf->ReadNormal(N);
	DrawFace(pDC,3,true);
	delete zbuf;
}

void CBezierObject::DrawControlGrid(CDC* pDC)//绘制控制网格
{
	for (int i = 0; i < NumObject; i++)
	{

		for (int m = 0; m < 4 ;m++)
		{
			for (int j = 0; j < 16; j++)
			{
				P3[j] = Vertex[i][Patch[i][m].vI[j]];
			}
		    ControlGrid(pDC);//控制网格
		}
	}
}

void CBezierObject::ControlGrid(CDC* pDC)//控制网格
{
	int i, j;
	for (i = 0; i < nNum * nNum; i++)
		P2[i] = projection.OrthogonalProjection(P3[i]);//控制点斜等测投影
	CPen NewPen, *pOldPen;
	NewPen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));//控制多边形颜色
	pOldPen = pDC->SelectObject(&NewPen);
	for (i = 0; i < nNum; i++)
	{
		pDC->MoveTo(Round(P2[i*4].x), Round(P2[i*4].y));
		for (j = 1; j < nNum; j++)
			pDC->LineTo(Round(P2[i*4+j].x), Round(P2[i*4+j].y));
	}
	for (j = 0; j < nNum; j++)
	{
		pDC->MoveTo(Round(P2[j].x), Round(P2[j].y));
		for (int i = 1; i < nNum; i++)
			pDC->LineTo(Round(P2[i*4+j].x), Round(P2[i*4+j].y));
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}

void CBezierObject::BicubicCurvedSurface(CDC* pDC,int NumObject,int m,int nWidth,int nHeight)//绘制双三次Bezier曲面片	
{
	CMatrix44 Mbe;//矩阵Mbe
	Mbe.matrix[0][0] = -1;Mbe.matrix[0][1] = 3;Mbe.matrix[0][2] =-3;Mbe.matrix[0][3] = 1;
	Mbe.matrix[1][0] =  3;Mbe.matrix[1][1] =-6;Mbe.matrix[1][2] = 3;Mbe.matrix[1][3] = 0;
	Mbe.matrix[2][0] = -3;Mbe.matrix[2][1] = 3;Mbe.matrix[2][2] = 0;Mbe.matrix[2][3] = 0;
	Mbe.matrix[3][0] =  1;Mbe.matrix[3][1] = 0;Mbe.matrix[3][2] = 0;Mbe.matrix[3][3] = 0;
	LeftMultiplyMatrix(Mbe, P3);//数字矩阵左乘三维控制点矩阵
	Mbe = Mbe.Transpose();//计算转置矩阵
	RightMultiMatrix(P3, Mbe);//数字矩阵右乘三维控制点矩阵
	double step = 0.1;
	double u, v, U[4], V[4];
	for (u = 0; u <= 1; u += step)
	{
		for (v = 0; v <= 1; v += step)
		{
			U[0] = u * u * u;
			U[1] = u * u;
			U[2] = u;
			U[3] = 1;
			V[0] = v * v * v;
			V[1] = v * v;
			V[2] = v;
			V[3] = 1;
			CP3 Point3 = (U[0] * P3[0] + U[1] * P3[4] + U[2] * P3[8] +  U[3] * P3[12]) * V[0]
			+ (U[0] * P3[1] + U[1] * P3[5] + U[2] * P3[9] +  U[3] * P3[13]) * V[1]
			+ (U[0] * P3[2] + U[1] * P3[6] + U[2] * P3[10] + U[3] * P3[14]) * V[2]
			+ (U[0] * P3[3] + U[1] * P3[7] + U[2] * P3[11] + U[3] * P3[15]) * V[3];
			FacePoint[Round(v*10)+10*NumObject][Round(u*10)+10*m] = Point3;
			FaceTPoint[Round(v*10)+10*NumObject][Round(u*10)+10*m].u=((u*10)+10*m)/41* (nWidth-1) ;
			FaceTPoint[Round(v*10)+10*NumObject][Round(u*10)+10*m].v=((v*10)+10*NumObject)/41*(nHeight-1);
		} 
	}

}

void CBezierObject::LeftMultiplyMatrix(CMatrix44 M, CP3* P)//左乘矩阵M*P
{
	int i, j;
	CP3 PNew[16];
	for (i = 0; i < nNum * nNum; i++)
		PNew[i] = P[i];
	for (i = 0; i < nNum; i++)
		for(j = 0; j < nNum; j++)
			P[i*nNum+j] = M.matrix[i][0] * PNew[0*nNum+j] + M.matrix[i][1] * PNew[1*nNum+j] + M.matrix[i][2] * PNew[2*nNum+j] + M.matrix[i][3] * PNew[3*nNum+j];	
}

void CBezierObject::RightMultiMatrix(CP3* P, CMatrix44 M)//右乘矩阵P*M
{
	int i, j;
	CP3 PNew[16];
	for (i = 0; i < nNum * nNum; i++)
		PNew[i] = P[i];
	for (i = 0; i < nNum; i++)
		for(j = 0; j < nNum; j++)
			P[i*nNum+j] = PNew[i*nNum+0] * M.matrix[0][j] + PNew[i*nNum+1] * M.matrix[1][j] + PNew[i*nNum+2] * M.matrix[2][j] + PNew[i*nNum+3] * M.matrix[3][j];
}
void CBezierObject::DrawFace(CDC *pDC, int NumObject,bool sign)
{
	//  0   1    数组中面中四个顶点索引顺序
	//  3   2
	


	CP3 FP4[4];//
	CT2 tFP4[4];
    
    int hang = 11 + NumObject*10;

	int lie = 41;	


	///////循环遍历每个点 为 每个点求法矢量//////////
	for (int u=0;u<hang;u++)   //u 行   横
	{ 
		for (int v=0;v<lie;v++) //v 列  竖
		{
			int beforeu = u-1,afteru = u+1;
			int beforev = v-1,afterv = v+1;
			if (0==v) beforev = lie-1;	

			if(lie==afterv)afterv=0;

			CVector vN0,vN1,vN2,vN3,AveN;

			if (0==u)   //第一行
			{

				//左下
				CVector v05(FacePoint[u][v],FacePoint[u+1][beforev]);
				CVector v06(FacePoint[u][v],FacePoint[u+1][v]);
				vN2 = Cross(v05,v06);
				//右下
				CVector v07(FacePoint[u][v],FacePoint[u+1][v]);
				CVector v08(FacePoint[u][v],FacePoint[u+1][afterv]);
				vN3 = Cross(v07,v08);
				AveN = (vN2+vN3);
				AveN /= AveN.Mag();
				FacePoint[u][v].xk = AveN.x;
				FacePoint[u][v].yk = AveN.y;
				FacePoint[u][v].zk = AveN.z;

			}
			else  if (hang == afteru)
			{

				//左上
				CVector v01(FacePoint[u][v],FacePoint[u-1][v]);
				CVector v02(FacePoint[u][v],FacePoint[u-1][beforev]);
				vN0 = Cross(v01,v02);
				//右上
				CVector v03(FacePoint[u][v],FacePoint[u-1][afterv]);
				CVector v04(FacePoint[u][v],FacePoint[u-1][v]);
				vN1 = Cross(v03,v04);
				AveN = (vN0+vN1);
				AveN /= AveN.Mag();
				FacePoint[u][v].xk = AveN.x;
				FacePoint[u][v].yk = AveN.y;
				FacePoint[u][v].zk = AveN.z;
			}
			else
			{

				//左上
				CVector v01(FacePoint[u][v],FacePoint[u-1][v]);
				CVector v02(FacePoint[u][v],FacePoint[u][beforev]);
				vN0 = Cross(v01,v02);
				//右上
				CVector v03(FacePoint[u][v],FacePoint[u][afterv]);
				CVector v04(FacePoint[u][v],FacePoint[u-1][v]);
				vN1 = Cross(v03,v04);
				//左下
				CVector v05(FacePoint[u][v],FacePoint[u][beforev]);
				CVector v06(FacePoint[u][v],FacePoint[u+1][v]);
				vN2 = Cross(v05,v06);
				//右下
				CVector v07(FacePoint[u][v],FacePoint[u+1][v]);
				CVector v08(FacePoint[u][v],FacePoint[u][afterv]);
				vN3 = Cross(v07,v08);
				AveN = (vN0+vN1+vN2+vN3);
				AveN /= AveN.Mag();
				FacePoint[u][v].xk = AveN.x;
				FacePoint[u][v].yk = AveN.y;
				FacePoint[u][v].zk = AveN.z;  
			}
		}
	}

	//////遍历每个小四边形面片///
	for (int u=0;u<hang-1;u++)   //u 行   横
	{ 
		for (int v=0;v<lie;v++) //v 列  竖 
		{
			int tempv = v+1;
			if (tempv == lie)
			{
				tempv = 0;
			}
			FP4[0] = FacePoint[(u)][(v)];
			FP4[1] = FacePoint[(u)][(tempv)];
			FP4[2] = FacePoint[(u+1)][(tempv)];
			FP4[3] = FacePoint[(u+1)][(v)];
			tFP4[0] =FaceTPoint[(u)][(v)];
			tFP4[1] =FaceTPoint[(u)][(tempv)];
			tFP4[2] =FaceTPoint[(u+1)][(tempv)];
			tFP4[3] =FaceTPoint[(u+1)][(v)];
			if (tempv == lie)
			{
				tFP4[1].v=0;
				tFP4[2].v=0;
			}
			DrawFaceP4(pDC,FP4,tFP4,sign);
		}
	}
}
void CBezierObject::DrawFaceP4(CDC *pDC,CP3 P4[4],CT2 tP4[4],bool sign)
{
	CP3 ViewPoint = projection.InitalParameter();
	CVector Normal[4];
	CVector Normal4[4];
	//1. 求面的视矢量
	CVector ViewVector(P4[0],ViewPoint);
	ViewVector = ViewVector.Normalize();
	//2.求面的法矢量
	CVector v01(P4[0],P4[3]);
	CVector v02(P4[0],P4[2]);

	CVector fNormal;
	fNormal =  Cross(v01,v02);
	
	fNormal = fNormal.Normalize();
	CPi3 point4[4];
	CT2  tpoint4[4];
    for (int i=0;i<4;i++)
	{
	   point4[i] = projection.PerspectiveProjection(P4[i]);
	   tpoint4[i]=tP4[i];
	   Normal4[i]=CVector(-P4[i].xk,-P4[i].yk,-P4[i].zk);
	}
	
	zbuf->SetPoint(point4, Normal4,tpoint4,4);//设置顶点			
	zbuf->CreateBucket();//建立桶表
	zbuf->CreateEdge();//建立边表
	zbuf->Phong(pDC,ViewPoint,pLight,pMaterial1);//纹理映射
	zbuf->ClearMemory();//内存清理	
}
