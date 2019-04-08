
// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif
#include<math.h>
#include "TestDoc.h"
#include "TestView.h"
#include"Revolution.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define  PI 3.1415926
#define Round(d) int(floor(d+0.5))

// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CTestView construction/destruction

CTestView::CTestView()
{
	R=1000,d=1000,Phi=90.0,Theta=0.0;//视点位于正前方
	Near=1000,Far=2000;//近剪切面与远剪切面
 	LightNum=2;//光源个数
 	pLight=new CLighting(LightNum);//一维光源动态数组
	pLight->Light[0].SetPosition(500,500,500);//设置光源位置坐标
	pLight->Light[1].SetPosition(-500,-500,500);//设置光源位置坐标
 	for(int i=0;i<LightNum;i++)
	{
		pLight->Light[i].L_Diffuse=CRGB(1.0,1.0,1.0);//光源的漫反射颜色
		pLight->Light[i].L_Specular=CRGB(1.0,1.0,1.0);//光源镜面高光颜色
		pLight->Light[i].L_C0=2.0;//常数衰减系数
		pLight->Light[i].L_C1=0.0000001;//线性衰减系数
		pLight->Light[i].L_C2=0.00000001;//二次衰减系数
		pLight->Light[i].L_OnOff=true;//光源开启
	}
	pMaterial=new CMaterial[3];//一维材质动态数组
	pMaterial[0].SetAmbient(CRGB(0.2,0.2,0.2));//材质对环境光光的反射率
	pMaterial[0].SetDiffuse(CRGB(0.2,0.2,0.2));//材质对漫反射光的反射率
	pMaterial[0].SetSpecular(CRGB(0.4,0.4,0.4));//材质对镜面反射光的反射率
	pMaterial[0].SetEmit(CRGB(0.5,0.356,0.378));//材质自身发散的颜色
	pMaterial[0].SetExp(50);//高光指数

	pMaterial[1].SetAmbient(CRGB(0.0,0.0,0.0));//材质对环境光光的反射率
	pMaterial[1].SetDiffuse(CRGB(0.0,0.0,0.0));//材质对环境光和漫反射光的反射率相等
	pMaterial[1].SetSpecular(CRGB(0.0,0.0,0.0));//材质对镜面反射光的反射率
	pMaterial[1].SetEmit(CRGB(1.0,1.0,1.0));//材质自身发散的颜色
	pMaterial[0].SetExp(50);//高光指数

	pMaterial[2].SetAmbient(CRGB(0.0,0.0,0.0));//材质对环境光光的反射率
	pMaterial[2].SetDiffuse(CRGB(0.0,0.0,0.0));//材质对环境光和漫反射光的反射率相等
	pMaterial[2].SetSpecular(CRGB(0.0,0.0,0.0));//材质对镜面反射光的反射率
	pMaterial[2].SetEmit(CRGB(0.0,0.0,0.0));//材质自身发散的颜色
	pMaterial[0].SetExp(50);//高光指数
	Alpha=0;
	Beta=0;
	ReadPoint();
	ReadFace();
	ReadCubeVertex();
	ReadCubeFace();
	tran4.SetMatrix(CN,144);
	tran4.RotateX(-90);
	tran4.Translate(0,150,0);
	tran4.RotateX(30);
	InitParameter();
	// TODO: add construction code here

}

CTestView::~CTestView()
{
	if(pLight!=NULL)
	{
		delete pLight;
		pLight=NULL;
	}
	if(pMaterial!=NULL)
	{
		delete []pMaterial;
		pMaterial=NULL;
	}
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DoubleBuffer(pDC);//双缓冲
}


// CTestView printing


void CTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG
void CTestView::DoubleBuffer(CDC* pDC)//双缓冲
{
	
	CRect rect;
	GetClientRect(&rect);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(),rect.Height());
	pDC->SetViewportExt(rect.Width(),-rect.Height());
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap NewBitmap,*pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	pOldBitmap=memDC.SelectObject(&NewBitmap);
	
	memDC.SetMapMode(MM_ANISOTROPIC);
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
//	memDC.FillSolidRect(rect, RGB(0,0,0));
	CZBuffer *zbuf=new CZBuffer;//申请内存
	zbuf->InitDeepBuffer(pDC,3000,3000,3000,CRGB(0.0,0.0,0.0));//初始化深度缓冲器
	DrawCube(&memDC,zbuf);
	DrawGraph(&memDC);
	DrawObject(&memDC,zbuf);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();
	delete zbuf;//释放内存
}
void CTestView::ReadCubeVertex()//读入立方体顶点坐标
{
	//顶点的三维坐标(x,y,z),立方体边长为2a,t为透明度

	for(int i=0;i<12;i++)
	{
		for(int j=0;j<12;j++)
		{
			BN[i][j].x=-275+j*50;
			BN[i][j].y=300-i*50;
			BN[i][j].z=-280;
		}
	}

	for(int i=0;i<12;i++)
	{
		for(int j=0;j<12;j++)
		{
			CN[i*12+j]=BN[i][j];
		}
	}
}
void CTestView::ReadCubeFace()//读入立方体面表
{
	//面的顶点数、面的顶点索引号与面的颜色
	for(int i = 0; i<121; i++)
	{
		FC[i].SetNum(4);
		FC[i].vI[0] = int(i/11) + i;
		FC[i].vI[1] = int(i/11) + i + 12;
		FC[i].vI[2] = int(i/11) + i + 13;
		FC[i].vI[3] = int(i/11) + i + 1;
	}
}
// CTestView message handlers
void CTestView::ReadPoint()//读入控制多边形顶点
{
	
	P[0]=CP3(150,300,0);
	P[1]=CP3(300,100,0);
	P[2]=CP3(200,0,0);
	P[3]=CP3(150,-50,0);
	pdd.ReadControlPoint(P);
	tran.SetMatrix(pdd.V,64);

	P1[0]=CP3(150,-50,0);
	P1[1]=CP3(150,-70,0);
	P1[2]=CP3(140,-70,0);
	P1[3]=CP3(140,-50,0);
	pdd1.ReadCubicBezierControlPoint(P1);
	tran1.SetMatrix(pdd1.V,64);

	P2[0]=CP3(140,-50,0);
	P2[1]=CP3(0,-50,0);
	P2[2]=CP3(0,-50,0);
	P2[3]=CP3(0,-50,0);
	pdd2.ReadCubicBezierControlPoint(P2);
	tran2.SetMatrix(pdd2.V,64);

	//P3[0]=CP3(-168,-212,0);
	//P3[1]=CP3(-168,-213,0);
	//P3[2]=CP3(-168,-238,0);
	//P3[3]=CP3(-159,-227,0);
	//pdd.ReadCubicBezierControlPoint(P3);
	//tran.SetMatrix(pdd3.V,64);

}
void CTestView::DrawCube(CDC* pDC,CZBuffer *zbuf)//绘制立方体表面
{
	CPi3 Point[4];//面的二维顶点数组
	CVector Normal4[4];//面的法矢量
	for(int nFace=0;nFace<121;nFace++)//面循环
	{
		if(nFace%2==0)
		{
		for(int nVertex=0;nVertex<FC[nFace].vN;nVertex++)//顶点循环
		{
			PerProject(CN[FC[nFace].vI[nVertex]]);//透视投影
			Point[nVertex]=ScreenP;
			Normal4[nVertex]=FC[nFace].fNormal;
		}
		zbuf->SetPoint(Point,Normal4,4);//设置顶点
		zbuf->CreateBucket();//创建桶表
		zbuf->CreateEdge();//创建边表
		zbuf->Phong(pDC,ViewPoint,pLight,&pMaterial[1],SPHERE);//颜色渐变填充四边形
		zbuf->ClearMemory();
		}
		else
		{
		for(int nVertex=0;nVertex<FC[nFace].vN;nVertex++)//顶点循环
		{
			PerProject(CN[FC[nFace].vI[nVertex]]);//透视投影
			Point[nVertex]=ScreenP;
			Normal4[nVertex]=FC[nFace].fNormal;
		}
		zbuf->SetPoint(Point,Normal4,4);//设置顶点
		zbuf->CreateBucket();//创建桶表
		zbuf->CreateEdge();//创建边表
		zbuf->Phong(pDC,ViewPoint,pLight,&pMaterial[2],SPHERE);//颜色渐变填充四边形
		zbuf->ClearMemory();
		}
		
	
	}
}
void CTestView::DrawGraph(CDC* pDC)//绘制图形
{
	pdd.DrawRevolutionSurface(pDC,ViewPoint,pLight,pMaterial);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<121;j++)
		{
			N0[i][j]=pdd.MV[i][j];
			Nv0[i][j]=pdd.Nv[i][j];
		}
	}
			
	pdd1.DrawRevolutionSurface(pDC,ViewPoint,pLight,pMaterial);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<121;j++)
		{
			N1[i][j]=pdd1.MV[i][j];
			Nv1[i][j]=pdd1.Nv[i][j];
		}
	}
	pdd2.DrawRevolutionSurface(pDC,ViewPoint,pLight,pMaterial); 
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<121;j++)
		{
			N2[i][j]=pdd2.MV[i][j];
			Nv2[i][j]=pdd2.Nv[i][j];

		}
	}
}
void CTestView::ReadFace()
{
	for(int i = 0; i<100; i++)
	{
		F[i].SetNum(4);
		F[i].vI[0] = int(i/10) + i;
		F[i].vI[1] = int(i/10) + i + 11;
		F[i].vI[2] = int(i/10) + i + 12;
		F[i].vI[3] = int(i/10) + i + 1;
	}
}
void CTestView::InitParameter()
{
	k[1]=sin(PI*Theta/180);
	k[2]=sin(PI*Phi/180);
	k[3]=cos(PI*Theta/180);
	k[4]=cos(PI*Phi/180);
	k[5]=k[2]*k[3];
	k[6]=k[2]*k[1];
	k[7]=k[4]*k[3];
	k[8]=k[4]*k[1];
	ViewPoint.x=R*k[6];
	ViewPoint.y=R*k[4];
	ViewPoint.z=R*k[5];
}

void CTestView::PerProject(CP3 P)
{
	
	CP3 ViewP;
	ViewP.x=P.x*k[3]-P.z*k[1];//观察坐标系三维坐标
	ViewP.y=-P.x*k[8]+P.y*k[2]-P.z*k[7];
	ViewP.z=-P.x*k[6]-P.y*k[4]-P.z*k[5]+R;
	ViewP.c=P.c;
    ScreenP.x=d*ViewP.x/ViewP.z;//屏幕坐标系三维坐标
	ScreenP.y=d*ViewP.y/ViewP.z;
	ScreenP.z=Far*(1-Near/ViewP.z)/(Far-Near);
	ScreenP.c=ViewP.c;

}
void CTestView::DrawObject(CDC *pDC,CZBuffer *zbuf)
{	
	CPi3 Point4[4];
	CVector VVn[4];
	for(int n=0;n<3;n++)
	{
		if(n==0)
		{
		for(int j=0;j<4;j++)
		{
			for(int i=0;i<100;i++)
			{
				CVector ViewVector(N0[j][F[i].vI[0]],ViewPoint);//面的视矢量
				ViewVector=ViewVector.Normalize();//单位化视矢量
				F[i].SetFaceNormal(N0[j][F[i].vI[0]],N0[j][F[i].vI[1]],N0[j][F[i].vI[2]]);
				F[i].fNormal.Normalize();//单位化法矢量
				//if(Dot(ViewVector,F[i].fNormal)>=0)//背面剔除
				//{			
					for(int m=0;m<F[i].vN;m++)
					{
						PerProject(N0[j][F[i].vI[m]]);
						Point4[m]=ScreenP;
						VVn[m]=Nv0[j][F[i].vI[m]];

					
					}
			zbuf->SetPoint(Point4,VVn,4);//设置顶点
			zbuf->CreateBucket();//建立桶表
			zbuf->CreateEdge();//建立边表
			zbuf->Phong(pDC,ViewPoint,pLight,pMaterial,CUBE);//填充四边形
			zbuf->ClearMemory();//内存清理
			/*
				}*/
			}
		}
		}
		if(n==1)
		{
			for(int j=0;j<4;j++)
		{
			for(int i=0;i<100;i++)
			{
				CVector ViewVector(N1[j][F[i].vI[0]],ViewPoint);//面的视矢量
				ViewVector=ViewVector.Normalize();//单位化视矢量
				F[i].SetFaceNormal(N1[j][F[i].vI[0]],N1[j][F[i].vI[1]],N1[j][F[i].vI[2]]);
				F[i].fNormal.Normalize();//单位化法矢量
				//if(Dot(ViewVector,F[i].fNormal)>=0)//背面剔除
				//{			
					for(int m=0;m<F[i].vN;m++)
					{
						PerProject(N1[j][F[i].vI[m]]);
						Point4[m]=ScreenP;
						VVn[m]=Nv1[j][F[i].vI[m]];
			
					}
			zbuf->SetPoint(Point4,VVn,4);//设置顶点
			zbuf->CreateBucket();//建立桶表
			zbuf->CreateEdge();//建立边表
			zbuf->Phong(pDC,ViewPoint,pLight,pMaterial,CUBE);//填充四边形
			zbuf->ClearMemory();//内存清理
			
				/*}*/
			}
		}
		
		}
		if(n==2)
		{
           for(int j=0;j<4;j++)
		{
			for(int i=0;i<100;i++)
			{
				CVector ViewVector(N2[j][F[i].vI[0]],ViewPoint);//面的视矢量
				ViewVector=ViewVector.Normalize();//单位化视矢量
				F[i].SetFaceNormal(N2[j][F[i].vI[0]],N2[j][F[i].vI[1]],N2[j][F[i].vI[2]]);
				F[i].fNormal.Normalize();//单位化法矢量
				//if(Dot(ViewVector,	F[i].fNormal)>=0)//背面剔除
				//{			
					for(int m=0;m<F[i].vN;m++)
					{
						PerProject(N2[j][F[i].vI[m]]);
						Point4[m]=ScreenP;
						VVn[m]=Nv2[j][F[i].vI[m]];

					}
			zbuf->SetPoint(Point4,VVn,4);//设置顶点
			zbuf->CreateBucket();//建立桶表
			zbuf->CreateEdge();//建立边表
			zbuf->Phong(pDC,ViewPoint,pLight,pMaterial,CUBE);//填充四边形
			zbuf->ClearMemory();//内存清理
			
				/*}*/
			}
		}
		
}
	}	
}
void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nChar)
	{
	case VK_UP:
		Alpha=-5;
		tran.RotateX(Alpha);
		tran1.RotateX(Alpha);
		tran2.RotateX(Alpha);
		/*tran3.RotateX(Alpha);
		tran4.RotateX(Alpha);
		tran5.RotateX(Alpha);
		tran6.RotateX(Alpha);
		tran7.RotateX(Alpha);*/
		break;
	case VK_DOWN:
		Alpha=+5;
		tran.RotateX(Alpha);
		tran1.RotateX(Alpha);
		tran2.RotateX(Alpha);
		/*tran3.RotateX(Alpha);
		tran4.RotateX(Alpha);
		tran5.RotateX(Alpha);
		tran6.RotateX(Alpha);
		tran7.RotateX(Alpha);*/

		break;
	case VK_LEFT:
		Beta=-5;
		tran.RotateY(Beta);
		tran1.RotateY(Beta);
		tran2.RotateY(Beta);
		/*tran3.RotateY(Beta);
		tran4.RotateY(Beta);
		tran5.RotateY(Beta);
		tran6.RotateY(Beta);
		tran7.RotateY(Beta);*/
		break;
	case VK_RIGHT:
		Beta=+5;
		tran.RotateY(Beta);
		tran1.RotateY(Beta);
		tran2.RotateY(Beta);
		/*tran3.RotateY(Beta);
		tran4.RotateY(Beta);
		tran5.RotateY(Beta);
		tran6.RotateY(Beta);
		tran7.RotateY(Beta);*/
		break;
	default:
		break;			
	}
	InitParameter();
	Invalidate(false);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
