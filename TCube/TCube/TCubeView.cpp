
// TCubeView.cpp : CTCubeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TCube.h"
#endif

#include "TCubeDoc.h"
#include "TCubeView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCubeView

IMPLEMENT_DYNCREATE(CTCubeView, CView)

BEGIN_MESSAGE_MAP(CTCubeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTCubeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_TFRONT, &CTCubeView::OnTfront)
	ON_COMMAND(ID_TBACK, &CTCubeView::OnTback)
	ON_COMMAND(ID_TBIG, &CTCubeView::OnTbig)
	ON_COMMAND(ID_TSMALL, &CTCubeView::OnTsmall)
	ON_COMMAND(ID_RXAXIS, &CTCubeView::OnRxaxis)
	ON_COMMAND(ID_RYAXIS, &CTCubeView::OnRyaxis)
	ON_COMMAND(ID_RZAXIS, &CTCubeView::OnRzaxis)
	ON_COMMAND(ID_RXOY, &CTCubeView::OnRxoy)
	ON_COMMAND(ID_RYOZ, &CTCubeView::OnRyoz)
	ON_COMMAND(ID_RXOZ, &CTCubeView::OnRxoz)
	ON_COMMAND(ID_SXDIRECTIONPLUS, &CTCubeView::OnSxdirectionplus)
	ON_COMMAND(ID_SYDIRECTIONPLUS, &CTCubeView::OnSydirectionplus)
	ON_COMMAND(ID_SZDIRECTIONNEG, &CTCubeView::OnSzdirectionneg)
	ON_COMMAND(IDM_DRAWPIC, &CTCubeView::OnDrawpic)
	ON_COMMAND(ID_RESET, &CTCubeView::OnReset)
	ON_COMMAND(ID_AAA, &CTCubeView::OnAaa)
	ON_COMMAND(ID_BBB, &CTCubeView::OnBbb)
	ON_COMMAND(ID_CCC, &CTCubeView::OnCcc)
	ON_COMMAND(ID_DDD, &CTCubeView::OnDdd)
END_MESSAGE_MAP()

// CTCubeView 构造/析构

CTCubeView::CTCubeView()
{
	// TODO: 在此处添加构造代码

}

CTCubeView::~CTCubeView()
{
}

BOOL CTCubeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTCubeView 绘制

void CTCubeView::OnDraw(CDC* pDC)
{
	CTCubeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//CRect rect;//定义客户区矩形
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(),rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(),-rect.Height());//设置视区范围,x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//客户区中心为原点
	CDC memDC;//内存DC
	CBitmap NewBitmap,*pOldBitmap;//内存中承载的临时位图
	memDC.CreateCompatibleDC(pDC);//创建一个与显示pDC兼容的内存memDC 
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


// CTCubeView 打印


void CTCubeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTCubeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTCubeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTCubeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CTCubeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

//void CTCubeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CTCubeView 诊断

#ifdef _DEBUG
void CTCubeView::AssertValid() const
{
	CView::AssertValid();
}

void CTCubeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTCubeDoc* CTCubeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTCubeDoc)));
	return (CTCubeDoc*)m_pDocument;
}
#endif //_DEBUG


// CTCubeView 消息处理程序
void CTCubeView::ReadPoint()//点表
{
	double a=150;//立方体边长为a
	//顶点的三维坐标(x,y,z)
	P[0].x=0;P[0].y=0;P[0].z=0;
	P[1].x=a;P[1].y=0;P[1].z=0;
	P[2].x=a;P[2].y=a;P[2].z=0;
	P[3].x=0;P[3].y=a;P[3].z=0;
	P[4].x=0;P[4].y=0;P[4].z=a;
	P[5].x=a;P[5].y=0;P[5].z=a;
	P[6].x=a;P[6].y=a;P[6].z=a;
	P[7].x=0;P[7].y=a;P[7].z=a;
}
void CTCubeView::ReadFace()//面表
{
	//面的边数、面的顶点编号
	F[0].SetNum(4);F[0].vI[0]=4;F[0].vI[1]=5;F[0].vI[2]=6;F[0].vI[3]=7;//前面
	F[1].SetNum(4);F[1].vI[0]=0;F[1].vI[1]=3;F[1].vI[2]=2;F[1].vI[3]=1;//后面
	F[2].SetNum(4);F[2].vI[0]=0;F[2].vI[1]=4;F[2].vI[2]=7;F[2].vI[3]=3;//左面
	F[3].SetNum(4);F[3].vI[0]=1;F[3].vI[1]=2;F[3].vI[2]=6;F[3].vI[3]=5;//右面
	F[4].SetNum(4);F[4].vI[0]=2;F[4].vI[1]=3;F[4].vI[2]=7;F[4].vI[3]=6;//顶面
	F[5].SetNum(4);F[5].vI[0]=0;F[5].vI[1]=1;F[5].vI[2]=5;F[5].vI[3]=4;//底面
}
void CTCubeView::ObliqueProject(CP3 p)//斜等测变换
{
	ScreenP.x=p.x-p.z/(2*sqrt(2.0));
	ScreenP.y=p.y-p.z/(2*sqrt(2.0));	
}
void CTCubeView::DrawObject(CDC *pDC)//绘制图形
{
	pDC->MoveTo(0,0);//绘制x轴
	pDC->LineTo(rect.Width()/2,0);
	pDC->TextOut(rect.Width()/2-20,-20,CString("x"));
	pDC->MoveTo(0,0);//绘制y轴
	pDC->LineTo(0,rect.Height()/2);
	pDC->TextOut(-20,rect.Height()/2-20,CString("y"));
	pDC->MoveTo(0,0);//绘制z轴
	pDC->LineTo(-rect.Width()/2,-rect.Width()/2);
	pDC->TextOut(-rect.Height()/2-20,-rect.Height()/2+20,CString("z"));
	pDC->TextOut(10,-10,CString("O"));
	DrawPolygon(pDC);
}
void CTCubeView::DrawPolygon(CDC *pDC)//绘制立方体线框模型
{
	for(int nFace=0;nFace<6;nFace++)
	{
		CP2 t;
		CPoint a[4];
		for(int nVertex=0;nVertex<F[nFace].vN;nVertex++)//顶点循环
		{
			ObliqueProject(P[F[nFace].vI[nVertex]]);//斜等测投影
			//a[nVertex].x = P[F[nFace].vI[nVertex]].x;
			//a[nVertex].y = P[F[nFace].vI[nVertex]].y;
			if(0==nVertex)
			{
				pDC->MoveTo(ScreenP.x,ScreenP.y);
				t=ScreenP;
				//pDC->MoveTo(a[nVertex].x,a[nVertex].y);
			}
			else
				pDC->LineTo(ScreenP.x,ScreenP.y);
				//pDC->LineTo(a[nVertex].x,a[nVertex].y);
		}
		pDC->LineTo(t.x,t.y);//闭合多边形
		//pDC->LineTo(a[0].x,a[0].y);//闭合多边形
	}
}

void CTCubeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	ReadPoint();
	ReadFace();
	trans.SetMat(P,8);
}
void CTCubeView::OnAaa()
{
	// TODO: 在此添加命令处理程序代码t
	trans.Translate(-10,0,0);
	Invalidate(FALSE);
}


void CTCubeView::OnBbb()
{
	// TODO: 在此添加命令处理程序代码
	trans.Translate(10,0,0);
	Invalidate(FALSE);
}


void CTCubeView::OnCcc()
{
	// TODO: 在此添加命令处理程序代码
	trans.Translate(0,10,0);
	Invalidate(FALSE);
}


void CTCubeView::OnDdd()
{
	// TODO: 在此添加命令处理程序代码
	trans.Translate(0,-10,0);
	Invalidate(FALSE);
}
void CTCubeView::OnTfront()
{
	// TODO: 在此添加命令处理程序代码
	trans.Translate(0,0,10);
	Invalidate(FALSE);
}


void CTCubeView::OnTback()
{
	// TODO: 在此添加命令处理程序代码
	trans.Translate(0,0,-10);
	Invalidate(FALSE);	
}


void CTCubeView::OnTbig()
{
	// TODO: 在此添加命令处理程序代码
	trans.Scale(2,2,2);
	Invalidate(FALSE);
}


void CTCubeView::OnTsmall()
{
	// TODO: 在此添加命令处理程序代码
	trans.Scale(0.5,0.5,0.5);
	Invalidate(FALSE);	
}


void CTCubeView::OnRxaxis()
{
	// TODO: 在此添加命令处理程序代码
	trans.RotateX(30,P[0]);
	Invalidate(FALSE);
}


void CTCubeView::OnRyaxis()
{
	// TODO: 在此添加命令处理程序代码
	trans.RotateY(30,P[0]);
	Invalidate(FALSE);
}


void CTCubeView::OnRzaxis()
{
	// TODO: 在此添加命令处理程序代码
	trans.RotateZ(30,P[0]);
	Invalidate(FALSE);
}


void CTCubeView::OnRxoy()
{
	// TODO: 在此添加命令处理程序代码
	trans.ReflectXOY();
	Invalidate(FALSE);
}


void CTCubeView::OnRyoz()
{
	// TODO: 在此添加命令处理程序代码
	trans.ReflectYOZ();
	Invalidate(FALSE);
}


void CTCubeView::OnRxoz()
{
	// TODO: 在此添加命令处理程序代码
	trans.ReflectZOX();
	Invalidate(FALSE);
}


void CTCubeView::OnSxdirectionplus()
{
	// TODO: 在此添加命令处理程序代码
	trans.ShearX(1,1);
	Invalidate(FALSE);
}


void CTCubeView::OnSydirectionplus()
{
	// TODO: 在此添加命令处理程序代码
	trans.ShearY(1,1);
	Invalidate(FALSE);	
}


void CTCubeView::OnSzdirectionneg()
{
	// TODO: 在此添加命令处理程序代码
	trans.ShearZ(1,1);
	Invalidate(FALSE);
}


void CTCubeView::OnDrawpic()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(CString("请使用图标按钮进行三维几何变换"),CString("提示"),MB_OK);
}


void CTCubeView::OnReset()
{
	// TODO: 在此添加命令处理程序代码
	ReadPoint();
	Invalidate(FALSE);
}

