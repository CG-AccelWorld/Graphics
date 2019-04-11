
// CubeView.cpp : CCubeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Cube.h"
#endif

#include "CubeDoc.h"
#include "CubeView.h"
#include "math.h"
#define PI 3.1415926

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCubeView

IMPLEMENT_DYNCREATE(CCubeView, CView)

BEGIN_MESSAGE_MAP(CCubeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCubeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
//	ON_COMMAND(ID_32772, &CCubeView::On32772)
END_MESSAGE_MAP()

// CCubeView 构造/析构

CCubeView::CCubeView()
{
	// TODO: 在此处添加构造代码
	R=1000.0;d=900.0;Alpha=0.0;Beta=0.0;
}

CCubeView::~CCubeView()
{
}

BOOL CCubeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCubeView 绘制

void CCubeView::OnDraw(CDC* pDC)
{
	CCubeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;//定义客户区矩形
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(),rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(),-rect.Height());//设置视区范围,x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//客户区中心为原点
	CDC memDC;//内存DC
	memDC.CreateCompatibleDC(pDC);//创建一个与显示pDC兼容的内存memDC
	CBitmap NewBitmap,*pOldBitmap;//内存中承载的临时位图 
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//创建兼容位图 
	pOldBitmap=memDC.SelectObject(&NewBitmap);//将兼容位图选入memDC 
	memDC.FillSolidRect(rect,pDC->GetBkColor());//按原来背景填充客户区，否则是黑色
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC自定义坐标系
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	DrawObject(&memDC);//向memDC绘制图形
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图 
}


// CCubeView 打印


void CCubeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCubeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCubeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCubeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CCubeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCubeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCubeView 诊断

#ifdef _DEBUG
void CCubeView::AssertValid() const
{
	CView::AssertValid();
}

void CCubeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCubeDoc* CCubeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCubeDoc)));
	return (CCubeDoc*)m_pDocument;
}
#endif //_DEBUG


// CCubeView 消息处理程序
void CCubeView::ReadPoint()
{
	double a = 150;
	P[0].x=-a;P[0].y=-a;P[0].z=-a;P[0].c=CRGB(0.0,0.0,0.0);//黑色
	P[1].x=+a;P[1].y=-a;P[1].z=-a;P[1].c=CRGB(1.0,0.0,0.0);//红色
	P[2].x=+a;P[2].y=+a;P[2].z=-a;P[2].c=CRGB(1.0,1.0,0.0);//黄色
	P[3].x=-a;P[3].y=+a;P[3].z=-a;P[3].c=CRGB(0.0,1.0,0.0);//绿色
	P[4].x=-a;P[4].y=-a;P[4].z=+a;P[4].c=CRGB(0.0,0.0,1.0);//蓝色
	P[5].x=+a;P[5].y=-a;P[5].z=+a;P[5].c=CRGB(1.0,0.0,1.0);//品红
	P[6].x=+a;P[6].y=+a;P[6].z=+a;P[6].c=CRGB(1.0,1.0,1.0);//白色
	P[7].x=-a;P[7].y=+a;P[7].z=+a;P[7].c=CRGB(0.0,1.0,1.0);//青色
}
void CCubeView::ReadFace()
{
	//面的顶点数索引号
	F[0].pIndex[0]=4;F[0].pIndex[1]=5;F[0].pIndex[2]=6;F[0].pIndex[3]=7;
	F[1].pIndex[0]=0;F[1].pIndex[1]=3;F[1].pIndex[2]=2;F[1].pIndex[3]=1;
	F[2].pIndex[0]=0;F[2].pIndex[1]=4;F[2].pIndex[2]=7;F[2].pIndex[3]=3;
	F[3].pIndex[0]=1;F[3].pIndex[1]=2;F[3].pIndex[2]=6;F[3].pIndex[3]=5;
	F[4].pIndex[0]=2;F[4].pIndex[1]=3;F[4].pIndex[2]=7;F[4].pIndex[3]=6;
	F[5].pIndex[0]=0;F[5].pIndex[1]=1;F[5].pIndex[2]=5;F[5].pIndex[3]=4;
}
void CCubeView::InitParameter()//透视变换参数初始化
{
	k[1]=sin(PI*Beta/180);
	k[2]=sin(PI*Alpha/180);
	k[3]=cos(PI*Beta/180);
	k[4]=cos(PI*Alpha/180);
	k[5]=k[2]*k[3];
	k[6]=k[2]*k[1];
	k[7]=k[4]*k[3];
	k[8]=k[4]*k[1];
	ViewPoint.x=R*k[6];
	ViewPoint.y=R*k[4];
	ViewPoint.z=R*k[5];
}
void CCubeView::PerProject(CP3 P)//透视变换
{
	CP3 ViewP;
	ViewP.x=P.x*k[3]-P.z*k[1];//观察坐标系三维坐标
	ViewP.y=-P.x*k[8]+P.y*k[2]-P.z*k[7];
	ViewP.z=-P.x*k[6]-P.y*k[4]-P.z*k[5]+R;
    ViewP.c=P.c;
    ScreenP.x=d*ViewP.x/ViewP.z;//屏幕坐标系二维坐标
	ScreenP.y=d*ViewP.y/ViewP.z;
	ScreenP.c=ViewP.c;
}
void CCubeView::DrawObject(CDC *pDC)
{
	CPoint Screen[4];
	CP2 l;
	for(int nFacet = 0; nFacet<6; nFacet++)
	{
		CVector ViewVector(P[F[nFacet].pIndex[0]],ViewPoint);//面的视矢量
		ViewVector=ViewVector.Normalize();//视矢量单位化
		F[nFacet].SetFaceNormal(P[F[nFacet].pIndex[0]],P[F[nFacet].pIndex[1]],P[F[nFacet].pIndex[2]]);
		F[nFacet].fNormal.Normalize();//面的单位化法矢量
		if(Dot(ViewVector,F[nFacet].fNormal)>=0)//背面剔除
		{
			for(int nPoint=0;nPoint<4;nPoint++)//顶点循环
		{
			PerProject(P[F[nFacet].pIndex[nPoint]]);//透视投影
			if(0==nPoint)
			{
				pDC->MoveTo(ScreenP.x,ScreenP.y);
				l=ScreenP;
			}
			else
				pDC->LineTo(ScreenP.x,ScreenP.y);
		}
			pDC->LineTo(l.x,l.y);;//闭合多边形
		}
	}
}
void CCubeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nChar)
	{
	case VK_UP:
		Alpha += 5;
		//tran.RotateX(Alpha);
		break;
	case VK_DOWN:
		Alpha -= 5;
		//tran.RotateX(Alpha);
		break;
	case VK_LEFT:
		Beta += 5;
		//tran.RotateY(Beta);
		break;
	case VK_RIGHT:
		Beta -= 5;
		//tran.RotateY(Beta);
		break;
	default:
		break;
	}
	InitParameter();
	Invalidate(FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CCubeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	ReadPoint();
	ReadFace();
	//tran.SetMatrix(P,8);
	InitParameter();
}
