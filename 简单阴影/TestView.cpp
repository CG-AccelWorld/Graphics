
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "math.h"//包含数学头文件
#define  PI 3.1415926//PI的宏定义
#define Round(d) int(floor(d+0.5))//四舍五入宏定义
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_GRAPH_DRAW, &CTestView::OnGraphDraw)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DRAW, &CTestView::OnUpdateGraphDraw)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	bPlay=FALSE;
	R = 1200.0, d = 800, Phi = 70.0, Theta = 0.0;//透视投影参数初始化
	Alpha = 0.0, Beta = 0.0;
	Near=1000,Far=1200;
	ReadPoint();
	ReadFacet();
	InitialParameter();
	transform.SetMatrix(P,8);
	LightNumber = 1;//光源个数
 	pLight = new CLighting(LightNumber);//一维光源动态数组
	pLight->LightSource[0].SetPosition(800, 800,800);//设置光源位置坐标	
 	for(int loop = 0; loop < LightNumber; loop++)
	{
		pLight->LightSource[loop].L_Diffuse = CRGB(1.0, 1.0, 1.0);//光源的漫反射颜色
		pLight->LightSource[loop].L_Specular = CRGB(1.0, 1.0, 1.0);//光源镜面高光颜色
		pLight->LightSource[loop].L_C0 = 1.0;//常数衰减系数
		pLight->LightSource[loop].L_C1 = 0.0000001;//线性衰减系数
		pLight->LightSource[loop].L_C2 = 0.00000001;//二次衰减系数
		pLight->LightSource[loop].L_OnOff = TRUE;//光源开启
	}
	pMaterial = new CMaterial;//一维材质动态数组
	pMaterial->SetAmbient(CRGB(0.247,0.200,0.075));//材质对环境光的反射率
	pMaterial->SetDiffuse(CRGB(0.752,0.606,0.226));//材质对漫反射光的反射率
	pMaterial->SetSpecular(CRGB(1.0, 1.0, 1.0));//材质对镜面反射光的反射率
	pMaterial->SetEmit(CRGB(0.05,0.05,0.002));//材质自身发散的颜色
	pMaterial->SetExp(30.0);//高光指数
}

CTestView::~CTestView()
{
	if(NULL != pLight)
	{
		delete pLight;
		pLight = NULL;
	}
	if(NULL != pMaterial)
	{
		delete pMaterial;
		pMaterial = NULL;
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
	DoubleBuffer(pDC);//绘制图形
}
void CTestView::ReadPoint()//点表
{
	double a=400;//立方体边长为a
	//顶点的三维坐标(x,y,z)
	P[0].x=-a/2;P[0].y=-a/2;P[0].z=-a/2;
	P[1].x=+a/2;P[1].y=-a/2;P[1].z=-a/2;
	P[2].x=+a/2;P[2].y=+a/2;P[2].z=-a/2;
	P[3].x=-a/2;P[3].y=+a/2;P[3].z=-a/2;
	P[4].x=-a/2;P[4].y=-a/2;P[4].z=+a/2;
	P[5].x=+a/2;P[5].y=-a/2;P[5].z=+a/2;
	P[6].x=+a/2;P[6].y=+a/2;P[6].z=+a/2;
	P[7].x=-a/2;P[7].y=+a/2;P[7].z=+a/2;
}

void CTestView::ReadFacet()//面表
{
	//面的边数、面的顶点编号
	F[0].PointNum(4);F[0].ptIndex[0]=4;F[0].ptIndex[1]=5;F[0].ptIndex[2]=6;F[0].ptIndex[3]=7;
	F[1].PointNum(4);F[1].ptIndex[0]=0;F[1].ptIndex[1]=3;F[1].ptIndex[2]=2;F[1].ptIndex[3]=1;//后面
	F[2].PointNum(4);F[2].ptIndex[0]=0;F[2].ptIndex[1]=4;F[2].ptIndex[2]=7;F[2].ptIndex[3]=3;//左面
	F[3].PointNum(4);F[3].ptIndex[0]=1;F[3].ptIndex[1]=2;F[3].ptIndex[2]=6;F[3].ptIndex[3]=5;//右面
	F[4].PointNum(4);F[4].ptIndex[0]=2;F[4].ptIndex[1]=3;F[4].ptIndex[2]=7;F[4].ptIndex[3]=6;//顶面
	F[5].PointNum(4);F[5].ptIndex[0]=0;F[5].ptIndex[1]=1;F[5].ptIndex[2]=5;F[5].ptIndex[3]=4;//底面
}

void CTestView::DoubleBuffer(CDC* pDC)//双缓冲绘图
{
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width()/2, rect.Height()/2);
	CDC memDC;//声明内存DC
	memDC.CreateCompatibleDC(pDC);//创建一个与显示DC兼容的内存DC
	CBitmap NewBitmap, *pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(), rect.Height());//创建兼容内存位图 
	pOldBitmap=memDC.SelectObject(&NewBitmap);//将兼容位图选入内存DC
	memDC.FillSolidRect(rect, pDC->GetBkColor());//设置客户区背景色
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	memDC.SetMapMode(MM_ANISOTROPIC);//内存DC自定义坐标系
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	DrawGround(&memDC);
	DrawGraph(&memDC);//绘制图形
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width()/2, -rect.Height()/2, SRCCOPY); //将内存DC中的位图拷贝到显示DC
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();
}

void CTestView::InitialParameter()//透视变换参数初始化
{	
	k[1] = sin(PI * Theta / 180);
	k[2] = sin(PI * Phi / 180);
	k[3] = cos(PI * Theta / 180);
	k[4] = cos(PI * Phi / 180);
	k[5] = k[2] * k[3];
	k[6] = k[2] * k[1];
	k[7] = k[4] * k[3];
	k[8] = k[4] * k[1];
	ViewPoint.x = R * k[6];
	ViewPoint.y = R * k[4];
	ViewPoint.z = R * k[5];
}

CP3 CTestView::PerspectiveProjection(CP3 WorldP)//透视变换
{
	CP3 ViewP;//观察坐标系三维坐标
	ViewP.x =  WorldP.x * k[3] - WorldP.z * k[1];
	ViewP.y = -WorldP.x * k[8] + WorldP.y * k[2] - WorldP.z * k[7];
	ViewP.z = -WorldP.x * k[6] - WorldP.y * k[4] - WorldP.z * k[5] + R;
	ViewP.c=WorldP.c;
	CP3 ScreenP;//屏幕二维坐标系
    ScreenP.x = d * ViewP.x / ViewP.z;
	ScreenP.y = d * ViewP.y / ViewP.z;
	ScreenP.z = Far * (1 - Near / ViewP.z) / (Far -Near);
	ScreenP.c=ViewP.c;
	return ScreenP;
}

void CTestView::DrawGraph(CDC* pDC)//表面二维投影
{
	CP3 ScreenPoint[4];
	pZBuffer = new CZBuffer;//申请内存
	pZBuffer->InitDeepBuffer(1000,1000,1000);//初始化深度缓存器
	for(int nFacet=0;nFacet<6;nFacet++)//面循环
	{	CVector ViewVector(P[F[nFacet].ptIndex[0]],ViewPoint);//面的视矢量
		ViewVector=ViewVector.Normalize();//单位化视矢量
		F[nFacet].SetFaceNormal(P[F[nFacet].ptIndex[0]],P[F[nFacet].ptIndex[1]],P[F[nFacet].ptIndex[2]]);	
		F[nFacet].fNormal.Normalize();//单位化法矢量
		for(int nPoint=0;nPoint<F[nFacet].ptNumber;nPoint++)//顶点循环
		{
			ScreenPoint[nPoint] = PerspectiveProjection(P[F[nFacet].ptIndex[nPoint]]);
			ScreenPoint[nPoint].c = pLight->Lighting(ViewPoint,P[F[nFacet].ptIndex[nPoint]],F[nFacet].fNormal,pMaterial);
		}
		pZBuffer->SetPoint(ScreenPoint[0],ScreenPoint[1], ScreenPoint[2]);
		pZBuffer->Gouraud(pDC);
		pZBuffer->SetPoint(ScreenPoint[0],ScreenPoint[2], ScreenPoint[3]);
		pZBuffer->Gouraud(pDC);


		CVector LightVector(P[F[nFacet].ptIndex[0]],pLight->LightSource[0].L_Position);//面的视矢量
		LightVector = LightVector.Normalize();//单位化视矢量
		F[nFacet].SetFaceNormal(P[F[nFacet].ptIndex[0]],P[F[nFacet].ptIndex[1]],P[F[nFacet].ptIndex[2]]);	
		F[nFacet].fNormal.Normalize();//单位化法矢量
		if(Dot(LightVector,F[nFacet].fNormal)<0)//背面剔除
		{
			for(int nPoint = 0; nPoint < F[nFacet].ptNumber; nPoint++)//顶点循环
			{
				ScreenPoint[nPoint] = PerspectiveProjection(CalculateCrossPoint(pLight->LightSource[0].L_Position,P[F[nFacet].ptIndex[nPoint]]));
				ScreenPoint[nPoint].c=CRGB(0.2,0.2,0.2);
			}
			pZBuffer->SetPoint(ScreenPoint[0],ScreenPoint[1], ScreenPoint[2]);
			pZBuffer->Gouraud(pDC);
			pZBuffer->SetPoint(ScreenPoint[0],ScreenPoint[2], ScreenPoint[3]);
			pZBuffer->Gouraud(pDC);
		}
	}
	delete pZBuffer;
}
void CTestView::DrawGround(CDC *pDC)
{
	CP3 p[4];
	Point1[0] = CP3(1000,-200,800);
	Point1[1] = CP3(-1000,-200,800);
	Point1[2] = CP3(-1000,-200,-800);
	Point1[3] = CP3(1000,-200,-800);
	p[0]=PerspectiveProjection(Point1[0]);
	p[1]=PerspectiveProjection(Point1[1]);
	p[2]=PerspectiveProjection(Point1[2]);
	p[3]=PerspectiveProjection(Point1[3]);
	CBrush NewBrush;
	NewBrush.CreateSolidBrush(RGB(150,150,150));
	CBrush *pOldBrush=pDC->SelectObject(&NewBrush);	
	pDC->BeginPath();
	pDC->MoveTo(Round(p[0].x),p[0].y);//绘制多边形
	for(int i=1;i<4;i++)
		pDC->LineTo(Round(p[i].x),p[i].y);
	pDC->LineTo(Round(p[0].x),p[0].y);
	pDC->EndPath();
	pDC->FillPath();//FillPath填充路径层
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();
}
CP3 CTestView::CalculateCrossPoint(CP3 p0,CP3 p1)
{
	CP3 p;
	double	A,B,C,D;//平面方程Ax+By+Cz＋D=0的系数
	CVector V01(Point1[0],Point1[1]),V02(Point1[0],Point1[2]);
	CVector VN=Cross(V01,V02);
	A=VN.x;B=VN.y;C=VN.z;
	D=-A*Point1[0].x-B*Point1[0].y-C*Point1[0].z;	
	double t;		//计算直线参数方程的公共系数t
	t=-(A*p0.x+B*p0.y+C*p0.z+D)/(A*(p1.x-p0.x)+B*(p1.y-p0.y)+C*(p1.z-p0.z));
	p.x=p0.x+t*(p1.x-p0.x);//代入参数方程计算交点坐标
	p.y=p0.y+t*(p1.y-p0.y);
	p.z=p0.z+t*(p1.z-p0.z);
	p.c=CRGB(p1.c.red,p1.c.green,p1.c.blue);
	return  p;
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
	Alpha=5;
	Beta=5;
	transform.RotateX(Alpha);
	transform.RotateY(Beta);
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if(!bPlay)
	{
		switch(nChar)
		{
		case VK_UP:
			Alpha=-5;
			transform.RotateX(Alpha);
			break;
		case VK_DOWN:
			Alpha=5;
			transform.RotateX(Alpha);
			break;
		case VK_LEFT:
			Beta=-5;
			transform.RotateY(Beta);
			break;
		case VK_RIGHT:
			Beta=5;
			transform.RotateY(Beta);
			break;
		default:
			break;
		}
		Invalidate(FALSE);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
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


