
// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"
#include "math.h"
#define  PI 3.1415926
#define Round(d) int(floor(d+0.5))

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_GRAPH_DRAW, &CTestView::OnGraphDraw)
	ON_WM_KEYDOWN()
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DRAW, &CTestView::OnUpdateGraphDraw)
END_MESSAGE_MAP()

// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	bPlay = FALSE;
	part = 3;
    R = 1000.0 , d = 900.0, Phi = 90.0, Psi = 0.0;//视点位于正前方;
	InitialParameter();
	LightSourceNumer = 1;//光源个数
 	pLight = new CLighting(LightSourceNumer);//一维光源动态数组
	pLight->LightSource[0].SetPosition(400,0,800);//设置光源位置坐标	
 	for(int i=0;i<LightSourceNumer;i++)
	{
		pLight->LightSource[i].L_Diffuse=CRGBA(1.0,1.0,1.0);//光源的漫反射颜色	
		pLight->LightSource[i].L_Specular=CRGBA(1.0,1.0,1.0);//光源镜面高光颜色
		pLight->LightSource[i].L_C0=1.0;//常数衰减系数
		pLight->LightSource[i].L_C1=0.0000001;//线性衰减系数
		pLight->LightSource[i].L_C2=0.00000001;//二次衰减系数
		pLight->LightSource[i].L_OnOff=TRUE;//光源开启
	}
	pMaterial = new CMaterial;//一维材质动态数组
	pMaterial->SetAmbient(CRGBA(0.1,0.1,0.1));//材质对环境光光的反射率
	pMaterial->SetDiffuse(CRGBA(0.508,0.508,0.508));//材质对漫反射光的反射率
	pMaterial->SetSpecular(CRGBA(0.508,0.508,0.508));//材质对镜面反射光的反射率
	pMaterial->SetEmit(CRGBA(0.2,0.2,0.2));//材质自身发散的颜色
	pMaterial->SetSlope(0.1);//材料粗糙度
	pMaterial->SetFresnel(1);
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
		delete pMaterial;
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

	// TODO: add draw code for native data here
	pFill = new CTriangle();
	pFill->InitDeepBuffer(1800,1800,1000);
	DoubleBuffer(pDC);
	delete pFill;
}
void CTestView::DoubleBuffer(CDC *pDC)
{
	//获取客户区信息
	CRect rect;
	GetClientRect(&rect);

	//自定义坐标系
	pDC->SetMapMode(MM_ANISOTROPIC);                    //设置为自定义坐标模式
	pDC->SetWindowExt(rect.Width(),rect.Height());      //设置比例
	pDC->SetViewportExt(rect.Width(),-rect.Height());   //设置xy轴方向
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//设置原点
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);  //将客户区与窗口区重合

	//双缓冲定义
	CDC memDC;
	CBitmap NewCBitmap, *OldCBitmap;
	memDC.CreateCompatibleDC(pDC);                      //创建一个与显示DC兼容的内存DC
	NewCBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//创建兼容内存位图
	OldCBitmap = memDC.SelectObject(&NewCBitmap);       //将兼容位图选入内存DC

	//自定义位图坐标系
	memDC.SetMapMode(MM_ANISOTROPIC);
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	memDC.FillSolidRect(rect, RGB(255,0,0));         //填充原来的背景色
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(i%2==1&&j%2==1 || i%2==0&&j%2==0)
			{
				CPen newPen,*oldPen;
				newPen.CreatePen(0,1,RGB(255,255,255));
				oldPen = memDC.SelectObject(&newPen);
				memDC.Rectangle(-500+i*50,-500+j*50,-450+i*50,-450+j*50);
				newPen.DeleteObject();
				memDC.SelectObject(oldPen);
				oldPen->DeleteObject();
			}
		}
	}
	DrawGround(&memDC);
	ReadControlVertex();
	ReadFacet();
	Bezier();
	DrawGraph(&memDC);

	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);

	memDC.SelectObject(OldCBitmap);	
	NewCBitmap.DeleteObject();
	ReleaseDC(&memDC);
}

void CTestView::ReadControlVertex(void)//读入控制点坐标
{
	double x[3][4],y[3][4],z[3][4],r[3][4];
	x[0][0] = -40;  y[0][0] = 250; z[0][0] = 0; r[0][0] = 40;
	x[0][1] = -60;  y[0][1] = 150; z[0][1] = 0; r[0][1] = 60;
	x[0][2] = -100; y[0][2] = 200; z[0][2] = 0; r[0][2] = 100;
	x[0][3] = -140; y[0][3] = 80;  z[0][3] = 0; r[0][3] = 140;

	x[1][0] = -140; y[1][0] = 80;  z[1][0] = 0; r[1][0] = 140;
	x[1][1] = -180; y[1][1] = -40; z[1][1] = 0; r[1][1] = 180;
	x[1][2] = -120; y[1][2] = -100;z[1][2] = 0; r[1][2] = 120;
	x[1][3] = -120; y[1][3] = -100;z[1][3] = 0; r[1][3] = 120;

	x[2][0] = -120; y[2][0] = -100;z[2][0] = 0; r[2][0] = 120;
	x[2][1] = -120; y[2][1] = -100;z[2][1] = 0; r[2][1] = 120;
	x[2][2] = 0;    y[2][2] = -100;z[2][2] = 0; r[2][2] = 0;
	x[2][3] = 0;    y[2][3] = -100;z[2][3] = 0; r[2][3] = 0;
	for(int p=0; p<part; p++)
	{
		for(int i=0; i<4; i++)
		{
			/*******************************Part1 Face1******************************/
			ControlP[p][0][i][0].x=-r[p][i];        ControlP[p][0][i][0].y=y[p][i]; ControlP[p][0][i][0].z=r[p][i]*0;
			ControlP[p][0][i][1].x=-r[p][i];        ControlP[p][0][i][1].y=y[p][i]; ControlP[p][0][i][1].z=r[p][i]*0.5528;
			ControlP[p][0][i][2].x=-r[p][i]*0.5528; ControlP[p][0][i][2].y=y[p][i]; ControlP[p][0][i][2].z=r[p][i];
			ControlP[p][0][i][3].x=-r[p][i]*0;      ControlP[p][0][i][3].y=y[p][i]; ControlP[p][0][i][3].z=r[p][i];
			/*******************************Part1 Face2******************************/
			ControlP[p][1][i][0].x=r[p][i]*0;       ControlP[p][1][i][0].y=y[p][i]; ControlP[p][1][i][0].z=r[p][i];
			ControlP[p][1][i][1].x=r[p][i]*0.5528;  ControlP[p][1][i][1].y=y[p][i]; ControlP[p][1][i][1].z=r[p][i];
			ControlP[p][1][i][2].x=r[p][i];         ControlP[p][1][i][2].y=y[p][i]; ControlP[p][1][i][2].z=r[p][i]*0.5528;
			ControlP[p][1][i][3].x=r[p][i];         ControlP[p][1][i][3].y=y[p][i]; ControlP[p][1][i][3].z=r[p][i]*0;
			/*******************************Part1 Face3******************************/
			ControlP[p][2][i][0].x=r[p][i];         ControlP[p][2][i][0].y=y[p][i]; ControlP[p][2][i][0].z=-r[p][i]*0;
			ControlP[p][2][i][1].x=r[p][i];         ControlP[p][2][i][1].y=y[p][i]; ControlP[p][2][i][1].z=-r[p][i]*0.5528;
			ControlP[p][2][i][2].x=r[p][i]*0.5528;  ControlP[p][2][i][2].y=y[p][i]; ControlP[p][2][i][2].z=-r[p][i];
			ControlP[p][2][i][3].x=r[p][i]*0;       ControlP[p][2][i][3].y=y[p][i]; ControlP[p][2][i][3].z=-r[p][i];
			/*******************************Part1 Face4******************************/
			ControlP[p][3][i][0].x=-r[p][i]*0;      ControlP[p][3][i][0].y=y[p][i]; ControlP[p][3][i][0].z=-r[p][i];
			ControlP[p][3][i][1].x=-r[p][i]*0.5528; ControlP[p][3][i][1].y=y[p][i]; ControlP[p][3][i][1].z=-r[p][i];
			ControlP[p][3][i][2].x=-r[p][i];        ControlP[p][3][i][2].y=y[p][i]; ControlP[p][3][i][2].z=-r[p][i]*0.5528;
			ControlP[p][3][i][3].x=-r[p][i];        ControlP[p][3][i][3].y=y[p][i]; ControlP[p][3][i][3].z=-r[p][i]*0;
		}
	}
}

void CTestView::Perspect()
{
	CP3 ViewP;
	for(int p=0; p<part; p++)
	{
		for(int f=0; f<4; f++)
		{
			for(int i=0; i<121; i++)
			{
				ViewP.x= k[3]*ObjectP[p][f][i].x-k[2]*ObjectP[p][f][i].z;//观察坐标系三维坐标
				ViewP.y=-k[6]*ObjectP[p][f][i].x+k[0]*ObjectP[p][f][i].y-k[7]*ObjectP[p][f][i].z;
				ViewP.z=-k[4]*ObjectP[p][f][i].x-k[1]*ObjectP[p][f][i].y-k[5]*ObjectP[p][f][i].z+R;
				ObjectP[p][f][i].x=d*ViewP.x/ViewP.z;
				ObjectP[p][f][i].y=Round(d*ViewP.y/ViewP.z);
				ObjectP[p][f][i].z=ViewP.z;
			}
		}
	}
}

CP3 CTestView::PerspectiveProject(CP3 WorldPoint)
{
	CP3 ViewPoint;//观察坐标系三维点
	ViewPoint.x = k[3] * WorldPoint.x - k[2] * WorldPoint.z; 
	ViewPoint.y = -k[6] * WorldPoint.x +k[0] * WorldPoint.y - k[7]* WorldPoint.z;
    ViewPoint.z = -k[4] * WorldPoint.x - k[1] * WorldPoint.y - k[5] * WorldPoint.z + R;
	ViewPoint.c = WorldPoint.c;
    CP3 ScreenPoint;//屏幕坐标系三维点
	ScreenPoint.x = d * ViewPoint.x / ViewPoint.z; 
	ScreenPoint.y = d * ViewPoint.y / ViewPoint.z;
	ScreenPoint.z = (ViewPoint.z-d)/ViewPoint.z;
	ScreenPoint.c = ViewPoint.c;
	return ScreenPoint;
}

void CTestView::InitialParameter()//透视变换参数初始化
{	
	k[0] = sin(PI * Phi / 180);//Phi代表φ
	k[1] = cos(PI * Phi / 180);
	k[2] = sin(PI * Psi / 180);//Psi代表ψ
	k[3] = cos(PI * Psi / 180);
	k[4] = k[0] * k[2];
	k[5] = k[0] * k[3];
	k[6] = k[1] * k[2];
	k[7] = k[1] * k[3];
	ViewPoint.x = R * k[4];// ViewPoint代表视点
	ViewPoint.y = R * k[1];// R为视径
	ViewPoint.z = R * k[5];
}

void CTestView::ReadFacet()
{
	for(int i=0; i<100; i++)
	{
		F[i].SetVertexNum(4);
		F[i].vIndex[0]=i/10+i;
		F[i].vIndex[1]=i/10+i+1;
		F[i].vIndex[2]=i/10+i+12;
		F[i].vIndex[3]=i/10+i+11;
	}
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


// CTestView message handlers
void CTestView::DrawGround(CDC *pDC)
{
	CP3 Point[4];//面的二维顶点数组
	Point[0] = PerspectiveProject(CP3(800,-100,800));
	Point[1] = PerspectiveProject(CP3(-800,-100,800));
	Point[2] = PerspectiveProject(CP3(-800,-100,-800));
	Point[3] = PerspectiveProject(CP3(800,-100,-800));
	CBrush NewBrush;
	NewBrush.CreateSolidBrush(RGB(150,150,150));
	CBrush *pOldBrush=pDC->SelectObject(&NewBrush);	
	pDC->BeginPath();
	pDC->MoveTo(Round(Point[0].x),Round(Point[0].y));//绘制多边形
	for(int i=1;i<4;i++)
		pDC->LineTo(Round(Point[i].x),Round(Point[i].y));
	pDC->LineTo(Round(Point[0].x),Round(Point[0].y));
	pDC->EndPath();
	pDC->FillPath();//FillPath填充路径层
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();
}

void CTestView::Bezier()
{
	double x,y,z,u,v,u1,u2,u3,u4,v1,v2,v3,v4;
	double au1,au2,au3,au4,av1,av2,av3,av4;
	double ux,uy,uz,vx,vy,vz;
	double M[4][4];
	for(int p=0; p<part; p++)
	{
		for(int f=0; f<4; f++)
		{
			M[0][0]=-1;M[0][1]=3; M[0][2]=-3;M[0][3]=1;
			M[1][0]=3; M[1][1]=-6;M[1][2]=3; M[1][3]=0;
			M[2][0]=-3;M[2][1]=3; M[2][2]=0; M[2][3]=0;
			M[3][0]=1; M[3][1]=0; M[3][2]=0; M[3][3]=0;
			LeftMultiMatrix(M,ControlP[p][f],p,f);
			TransposeMatrix(M);
			RightMultiMatrix(ControlP[p][f],MT,p,f);
		}
	}
	int i,j;
	for(u=0,i=0;u<=1;u+=0.1,i++)
	{
		for(v=0,j=0;v<=1;v+=0.1,j++)
		{
			for(int p=0; p<part; p++)
			{
				for(int f=0; f<4; f++)
				{
					u1=u*u*u;u2=u*u;u3=u;u4=1;v1=v*v*v;v2=v*v;v3=v;v4=1;
					au1=3*u*u;au2=2*u;au3=1;au4=0;av1=3*v*v;av2=2*v;av3=1;av4=0;
					x=(u1*ControlP[p][f][0][0].x+u2*ControlP[p][f][1][0].x+u3*ControlP[p][f][2][0].x+u4*ControlP[p][f][3][0].x)*v1
					 +(u1*ControlP[p][f][0][1].x+u2*ControlP[p][f][1][1].x+u3*ControlP[p][f][2][1].x+u4*ControlP[p][f][3][1].x)*v2
					 +(u1*ControlP[p][f][0][2].x+u2*ControlP[p][f][1][2].x+u3*ControlP[p][f][2][2].x+u4*ControlP[p][f][3][2].x)*v3
					 +(u1*ControlP[p][f][0][3].x+u2*ControlP[p][f][1][3].x+u3*ControlP[p][f][2][3].x+u4*ControlP[p][f][3][3].x)*v4;
					y=(u1*ControlP[p][f][0][0].y+u2*ControlP[p][f][1][0].y+u3*ControlP[p][f][2][0].y+u4*ControlP[p][f][3][0].y)*v1
					 +(u1*ControlP[p][f][0][1].y+u2*ControlP[p][f][1][1].y+u3*ControlP[p][f][2][1].y+u4*ControlP[p][f][3][1].y)*v2
					 +(u1*ControlP[p][f][0][2].y+u2*ControlP[p][f][1][2].y+u3*ControlP[p][f][2][2].y+u4*ControlP[p][f][3][2].y)*v3
					 +(u1*ControlP[p][f][0][3].y+u2*ControlP[p][f][1][3].y+u3*ControlP[p][f][2][3].y+u4*ControlP[p][f][3][3].y)*v4;
					z=(u1*ControlP[p][f][0][0].z+u2*ControlP[p][f][1][0].z+u3*ControlP[p][f][2][0].z+u4*ControlP[p][f][3][0].z)*v1
					 +(u1*ControlP[p][f][0][1].z+u2*ControlP[p][f][1][1].z+u3*ControlP[p][f][2][1].z+u4*ControlP[p][f][3][1].z)*v2
					 +(u1*ControlP[p][f][0][2].z+u2*ControlP[p][f][1][2].z+u3*ControlP[p][f][2][2].z+u4*ControlP[p][f][3][2].z)*v3
					 +(u1*ControlP[p][f][0][3].z+u2*ControlP[p][f][1][3].z+u3*ControlP[p][f][2][3].z+u4*ControlP[p][f][3][3].z)*v4;

					ux=(au1*ControlP[p][f][0][0].x+au2*ControlP[p][f][1][0].x+au3*ControlP[p][f][2][0].x+au4*ControlP[p][f][3][0].x)*v1
					 +(au1*ControlP[p][f][0][1].x+au2*ControlP[p][f][1][1].x+au3*ControlP[p][f][2][1].x+au4*ControlP[p][f][3][1].x)*v2
					 +(au1*ControlP[p][f][0][2].x+au2*ControlP[p][f][1][2].x+au3*ControlP[p][f][2][2].x+au4*ControlP[p][f][3][2].x)*v3
					 +(au1*ControlP[p][f][0][3].x+au2*ControlP[p][f][1][3].x+au3*ControlP[p][f][2][3].x+au4*ControlP[p][f][3][3].x)*v4;
					uy=(au1*ControlP[p][f][0][0].y+au2*ControlP[p][f][1][0].y+au3*ControlP[p][f][2][0].y+au4*ControlP[p][f][3][0].y)*v1
					 +(au1*ControlP[p][f][0][1].y+au2*ControlP[p][f][1][1].y+au3*ControlP[p][f][2][1].y+au4*ControlP[p][f][3][1].y)*v2
					 +(au1*ControlP[p][f][0][2].y+au2*ControlP[p][f][1][2].y+au3*ControlP[p][f][2][2].y+au4*ControlP[p][f][3][2].y)*v3
					 +(au1*ControlP[p][f][0][3].y+au2*ControlP[p][f][1][3].y+au3*ControlP[p][f][2][3].y+au4*ControlP[p][f][3][3].y)*v4;
					uz=(au1*ControlP[p][f][0][0].z+au2*ControlP[p][f][1][0].z+au3*ControlP[p][f][2][0].z+au4*ControlP[p][f][3][0].z)*v1
					 +(au1*ControlP[p][f][0][1].z+au2*ControlP[p][f][1][1].z+au3*ControlP[p][f][2][1].z+au4*ControlP[p][f][3][1].z)*v2
					 +(au1*ControlP[p][f][0][2].z+au2*ControlP[p][f][1][2].z+au3*ControlP[p][f][2][2].z+au4*ControlP[p][f][3][2].z)*v3
					 +(au1*ControlP[p][f][0][3].z+au2*ControlP[p][f][1][3].z+au3*ControlP[p][f][2][3].z+au4*ControlP[p][f][3][3].z)*v4;

					vx=(u1*ControlP[p][f][0][0].x+u2*ControlP[p][f][1][0].x+u3*ControlP[p][f][2][0].x+u4*ControlP[p][f][3][0].x)*av1
					 +(u1*ControlP[p][f][0][1].x+u2*ControlP[p][f][1][1].x+u3*ControlP[p][f][2][1].x+u4*ControlP[p][f][3][1].x)*av2
					 +(u1*ControlP[p][f][0][2].x+u2*ControlP[p][f][1][2].x+u3*ControlP[p][f][2][2].x+u4*ControlP[p][f][3][2].x)*av3
					 +(u1*ControlP[p][f][0][3].x+u2*ControlP[p][f][1][3].x+u3*ControlP[p][f][2][3].x+u4*ControlP[p][f][3][3].x)*av4;
					vy=(u1*ControlP[p][f][0][0].y+u2*ControlP[p][f][1][0].y+u3*ControlP[p][f][2][0].y+u4*ControlP[p][f][3][0].y)*av1
					 +(u1*ControlP[p][f][0][1].y+u2*ControlP[p][f][1][1].y+u3*ControlP[p][f][2][1].y+u4*ControlP[p][f][3][1].y)*av2
					 +(u1*ControlP[p][f][0][2].y+u2*ControlP[p][f][1][2].y+u3*ControlP[p][f][2][2].y+u4*ControlP[p][f][3][2].y)*av3
					 +(u1*ControlP[p][f][0][3].y+u2*ControlP[p][f][1][3].y+u3*ControlP[p][f][2][3].y+u4*ControlP[p][f][3][3].y)*av4;
					vz=(u1*ControlP[p][f][0][0].z+u2*ControlP[p][f][1][0].z+u3*ControlP[p][f][2][0].z+u4*ControlP[p][f][3][0].z)*av1
					 +(u1*ControlP[p][f][0][1].z+u2*ControlP[p][f][1][1].z+u3*ControlP[p][f][2][1].z+u4*ControlP[p][f][3][1].z)*av2
					 +(u1*ControlP[p][f][0][2].z+u2*ControlP[p][f][1][2].z+u3*ControlP[p][f][2][2].z+u4*ControlP[p][f][3][2].z)*av3
					 +(u1*ControlP[p][f][0][3].z+u2*ControlP[p][f][1][3].z+u3*ControlP[p][f][2][3].z+u4*ControlP[p][f][3][3].z)*av4;

					CVector3 v1,v2;
					v1.x=ux;v1.y=uy;v1.z=uz;
					v2.x=vx;v2.y=vy;v2.z=vz;
					v1 = v1.Normalize();
					v2 = v2.Normalize();

					ObjectP[p][f][i*11+j].x = x;
					ObjectP[p][f][i*11+j].y = y;
					ObjectP[p][f][i*11+j].z = z;
					ObjectP[p][f][i*11+j].c = pLight->illuminate(ViewPoint,ObjectP[p][f][i*11+j],CrossProduct(v1,v2),pMaterial);
					ObjectP[p][f][i*11+j].T=0.1+0.7*(1-pow((1-fabs(CrossProduct(v1,v2).Normalize().z)),1.2));
				}
			}
		}
	}
	Perspect();
}

void CTestView::LeftMultiMatrix(double M0[][4],CP3 P0[][4],int p,int f)
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
	{
		for(j=0;j<4;j++)
		{
			ControlP[p][f][i][j]=T[i][j];
		}
	}
}

void CTestView::RightMultiMatrix(CP3 P0[][4],double M1[][4],int p,int f)
{
	CP3 T[4][4];//临时矩阵
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{	
			T[i][j].x=P0[i][0].x*M1[0][j]+P0[i][1].x*M1[1][j]+P0[i][2].x*M1[2][j]+P0[i][3].x*M1[3][j];
			T[i][j].y=P0[i][0].y*M1[0][j]+P0[i][1].y*M1[1][j]+P0[i][2].y*M1[2][j]+P0[i][3].y*M1[3][j];
			T[i][j].z=P0[i][0].z*M1[0][j]+P0[i][1].z*M1[1][j]+P0[i][2].z*M1[2][j]+P0[i][3].z*M1[3][j];
		}
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			ControlP[p][f][i][j]=T[i][j];
	}
}

void CTestView::TransposeMatrix(double M0[][4])
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			MT[j][i]=M0[i][j];
}

void CTestView::DrawGraph(CDC *pDC)
{
	CP3 point[4];
	for(int p=0; p<part; p++)
	{
		for(int f=0; f<4; f++)
		{
			for(int i=0; i<100; i++)
			{
				for(int m=0;m<4;m++)
					point[m] = ObjectP[p][f][F[i].vIndex[m]];
				pFill->SetPoint(point[0],point[1], point[2]);
				pFill->Gouraud(pDC);
				pFill->SetPoint(point[0],point[2], point[3]);
				pFill->Gouraud(pDC);
			}
		}
	}
}

void CTestView::OnUpdateGraphDraw(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(bPlay)
	{
		pCmdUI->SetCheck(TRUE);
		pCmdUI->SetText(CString("停止"));
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
		pCmdUI->SetText(CString("播放"));
	}
}

void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Psi+=5;
	InitialParameter();
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}


void CTestView::OnGraphDraw()
{
	// TODO: Add your command handler code here
	bPlay=!bPlay;
	if(bPlay)//设置定时器
		SetTimer(1,150,NULL);	
	else
		KillTimer(1);
}


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if(!bPlay)
	{
		switch(nChar)
		{
		case VK_UP:
			Phi+=5;
			break;
		case VK_DOWN:
			Phi-=5;
			break;
		case VK_LEFT:
			Psi+=5;
			break;
		case VK_RIGHT:
			Psi-=5;
			break;
		default:
			break;
		}
		InitialParameter();
		Invalidate(FALSE);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

