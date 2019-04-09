
// testView.cpp : CtestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "test.h"
#endif

#include "testDoc.h"
#include "testView.h"
#include "math.h"
#define Round(a) int(floor(a+0.5))

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestView

IMPLEMENT_DYNCREATE(CtestView, CView)

BEGIN_MESSAGE_MAP(CtestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CtestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CtestView 构造/析构

CtestView::CtestView()
{
	// TODO: 在此处添加构造代码
	//初始化9个控制点
	P[0].x=120;P[0].y=350;
	P[1].x=250;P[1].y=250;
	P[2].x=316;P[2].y=420;
	P[3].x=428;P[3].y=167;
	P[4].x=525;P[4].y=500;
	P[5].x=650;P[5].y=250;
	P[6].x=682;P[6].y=40;
	P[7].x=850;P[7].y=450;
	P[8].x=950;P[8].y=350;
	m = -1;
	b_AbleToMove = FALSE;
	b_AbleToLeftBtn = FALSE;
}

CtestView::~CtestView()
{
}

BOOL CtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CtestView 绘制

void CtestView::OnDraw(CDC* pDC)
{
	CtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;//定义 客户区矩形
	GetClientRect(&rect);//获得客户区的大小
	CDC memDC;//内存DC
	CBitmap NewBitmap,*pOldBitmap;//内存中承载的临时位图
	memDC.CreateCompatibleDC(pDC);//创建一个与显示pDC兼容的内存memDC 
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//创建兼容位图 
	pOldBitmap=memDC.SelectObject(&NewBitmap);//将兼容位图选入memDC 
	memDC.FillSolidRect(rect,pDC->GetBkColor());//按原来背景填充客户区，否则是黑色
	CPen NewPen,*pOldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));
	pOldPen=memDC.SelectObject(&NewPen);
	memDC.MoveTo(P[0]);
	memDC.Ellipse(P[0].x-2,P[0].y-2,P[0].x+2,P[0].y+2);//绘制控制多边形顶点
	for(int i=1;i<9;i++)
	{
		memDC.LineTo(P[i]);
		memDC.Ellipse(P[i].x-2,P[i].y-2,P[i].x+2,P[i].y+2);
	}
	if(m!=-1 && b_AbleToMove == TRUE)
	{
		CString	str;
		str.Format(CString("x=%d,y=%d"),P[m].x,P[m].y);
		memDC.TextOut(P[m].x+5,P[m].y+5,str);
	}
	B3Curves(P,&memDC);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图
	//B3Curves(P,pDC);
	
}


// CtestView 打印


void CtestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CtestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CtestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CtestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CtestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CtestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CtestView 诊断

#ifdef _DEBUG
void CtestView::AssertValid() const
{
	CView::AssertValid();
}

void CtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestDoc* CtestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestDoc)));
	return (CtestDoc*)m_pDocument;
}
#endif //_DEBUG


// CtestView 消息处理程序
void CtestView::B3Curves(CPoint q[],CDC *pDC)//绘制三次B样条曲线
{
	CPoint p;
	double F03,F13,F23,F33;
	p.x=Round((q[0].x+4.0*q[1].x+q[2].x)/6.0);//t＝0的起点x坐标
	p.y=Round((q[0].y+4.0*q[1].y+q[2].y)/6.0);//t＝0的起点y坐标
	pDC->MoveTo(p);
	CPen NewPen,*pOldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,255,255));
	pOldPen = pDC->SelectObject(&NewPen);
	for(int i = 1;i<7;i++)
	{
		for(double t = 0.0;t<1.0;t+=0.01)
		{
			F03=(-t*t*t+3*t*t-3*t+1)/6;//计算F0,3(t)
			F13=(3*t*t*t-6*t*t+4)/6;//计算F1,3(t)
			F23=(-3*t*t*t+3*t*t+3*t+1)/6;//计算F2,3(t)
			F33=t*t*t/6;//计算B3,3(t)
			p.x=Round(q[i-1].x*F03+q[i].x*F13+q[i+1].x*F23+q[i+2].x*F33);
			p.y=Round(q[i-1].y*F03+q[i].y*F13+q[i+1].y*F23+q[i+2].y*F33);
			pDC->LineTo(p);
		}
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
	CString str;	
	for(int i = 0;i<9;i++)
	{
		if(i==0)
			pDC->MoveTo(P[0]);
		else
		    pDC->LineTo(P[i]);
		if(b_AbleToMove == FALSE)
		{
			str.Format(CString("x=%d,y=%d"),P[i].x,P[i].y);
			pDC->TextOutW(P[i].x+10,P[i].y-10,str);
		}	
	}
}


void CtestView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnMouseMove(nFlags, point);
	if(b_AbleToMove == TRUE)
	P[m] = point;
	for(int i = 0;i<9;i++)
	{
		if((point.x-P[i].x)*(point.x-P[i].x)+(point.y-P[i].y)*(point.y-P[i].y)<50)//?
		{
			m = i;
			//b_AbleToLeftBtn==TRUE;
			SetCursor(LoadCursor(NULL,IDC_SIZEALL));//改变为十字箭头光标
			//通过LoadCursor获得鼠标形状，载入一个光标，然后用SetCursor改变鼠标形状
		}
	}
	Invalidate(FALSE);	
}


void CtestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDown(nFlags, point);
	//if(b_AbleToLeftBtn==TRUE)
	b_AbleToMove = TRUE;
}


void CtestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	b_AbleToMove = FALSE;
	//b_AbleToLeftBtn = FALSE;
	m = -1;
	CView::OnLButtonUp(nFlags, point);
}
