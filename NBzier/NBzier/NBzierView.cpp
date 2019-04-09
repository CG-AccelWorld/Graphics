
// NBzierView.cpp : CNBzierView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "NBzier.h"
#endif

#include "NBzierDoc.h"
#include "NBzierView.h"
#include "math.h"
#define  PI 3.1415926//PI的宏定义
#define Round(a) int(floor(a+0.5)) //四舍五入宏定义
#define MAX 8//控制多边形的最大顶点数

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNBzierView

IMPLEMENT_DYNCREATE(CNBzierView, CView)

BEGIN_MESSAGE_MAP(CNBzierView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNBzierView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAWPIC, &CNBzierView::OnDrawpic)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CNBzierView 构造/析构

CNBzierView::CNBzierView()
{
	// TODO: 在此处添加构造代码
	P=new CPoint[MAX];
	bFlag = TRUE;
}

CNBzierView::~CNBzierView()
{
}

BOOL CNBzierView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CNBzierView 绘制

void CNBzierView::OnDraw(CDC* /*pDC*/)
{
	CNBzierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CNBzierView 打印


void CNBzierView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNBzierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CNBzierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CNBzierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CNBzierView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

//void CNBzierView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CNBzierView 诊断

#ifdef _DEBUG
void CNBzierView::AssertValid() const
{
	CView::AssertValid();
}

void CNBzierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNBzierDoc* CNBzierView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNBzierDoc)));
	return (CNBzierDoc*)m_pDocument;
}
#endif //_DEBUG


// CNBzierView 消息处理程序
void CNBzierView::OnDrawpic()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(CString("左键绘制控制多边形，右键绘制曲线"),CString("提示"),MB_OK);
	//RedrawWindow();
	Invalidate(TRUE);
	bFlag=TRUE;
	CtrlPointNum=0;
}

void CNBzierView::DrawCtrlPolygon()//绘制控制多边形
{
	CDC *pDC=GetDC();//获取设备上下文指针 
	CBrush NewBrush,*pOldBrush;
	NewBrush.CreateSolidBrush(RGB(0,255,0));
	pOldBrush=/*(CBrush*)*/pDC->SelectObject(&NewBrush);/*SelectStockObject(GRAY_BRUSH);*///灰色实心圆绘制控制点
	for(int i=0;i<=n;i++)
	{
		if(0==i)
		{
			pDC->MoveTo(P[i]);
			pDC->Ellipse(P[i].x-5,P[i].y-5,P[i].x+5,P[i].y+5);
		}
		else
		{
			pDC->LineTo(P[i]);
			pDC->Ellipse(P[i].x-5,P[i].y-5,P[i].x+5,P[i].y+5);
		}
	}
	pDC->SelectObject(pOldBrush);
	ReleaseDC(pDC);
}
long CNBzierView::Fac(int m)//阶乘函数
{
	long F;
	if(m==0 || m ==1)
		F = 1;
	else
		F = m*Fac(m-1);
	return F;
}
double CNBzierView::Cni(const int &n,const int &i)//Bernstein第一项组合
{
	return double (Fac(n)/(Fac(i)*Fac(n-i)));
}
void CNBzierView::DrawBezier()//绘制Bezier曲线
{
	CDC *pDC = GetDC();
	CPen NewPen,*pOldPen;
	NewPen.CreatePen(PS_SOLID,1,RGB(0,255,0));
	pOldPen = pDC->SelectObject(&NewPen);
	pDC->MoveTo(P[0]);
	for(double t=0.0; t<=1.0; t+=0.01)
	{
		double x = 0,y = 0;
		for(int i=0;i<=n;i++)
		{
			x+=P[i].x*Cni(n,i)*pow(t,i)*pow((1-t),n-i);
			y+=P[i].y*Cni(n,i)*pow(t,i)*pow((1-t),n-i);
		}
		pDC->LineTo(Round(x),Round(y));
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
	ReleaseDC(pDC);
}
void CNBzierView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	if(bFlag)
	{
		P[CtrlPointNum].x = point.x;
		P[CtrlPointNum].y = point.y;
		if(CtrlPointNum<MAX)
			CtrlPointNum++;
		else
			bFlag = FALSE;
		n = CtrlPointNum-1;
		DrawCtrlPolygon();
	}

	CView::OnLButtonDown(nFlags, point);
}


void CNBzierView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(CtrlPointNum!=0)
		DrawBezier();

	CView::OnRButtonDown(nFlags, point);
}
