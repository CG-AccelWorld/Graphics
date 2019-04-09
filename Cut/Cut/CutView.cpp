
// CutView.cpp : CCutView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Cut.h"
//#include "math.h"
#endif

#include "CutDoc.h"
#include "CutView.h"
#include "math.h"
#define LEFT 1     //代表：0001
#define RIGHT 2    //代表：0010
#define BOTTOM 4   //代表：0100
#define TOP 8      //代表：1000
#define Round(a) int(floor(a+0.5))//四舍五入宏定义

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCutView

IMPLEMENT_DYNCREATE(CCutView, CView)

BEGIN_MESSAGE_MAP(CCutView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCutView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_OnDrawPic, &CCutView::OnOndrawpic)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_CLIP, &CCutView::OnClip)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CCutView 构造/析构

CCutView::CCutView()
{
	// TODO: 在此处添加构造代码
	wxl=-300;
	wyt=150;
	wxr=300;
	wyb=-150;
	PtCount=0;
	bDrawLine=FALSE;
}

CCutView::~CCutView()
{
}

BOOL CCutView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCutView 绘制

void CCutView::OnDraw(CDC* pDC)
{
	CCutDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;//定义客户区
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
	DrawWindowRect(&memDC);//绘制窗口
	if(PtCount>=1)
	{
		CPen NewPen,*pOldPen;
		NewPen.CreatePen(PS_DASH,3,RGB(255,0,0));
		pOldPen = memDC.SelectObject(&NewPen);
		memDC.MoveTo(Round(P[0].x),Round(P[0].y));
		memDC.LineTo(Round(P[1].x),Round(P[1].y));
		pDC->SelectObject(pOldPen);
		NewPen.DeleteObject();
	}
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图
}


// CCutView 打印


void CCutView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCutView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCutView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCutView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CCutView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCutView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCutView 诊断

#ifdef _DEBUG
void CCutView::AssertValid() const
{
	CView::AssertValid();
}

void CCutView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCutDoc* CCutView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCutDoc)));
	return (CCutDoc*)m_pDocument;
}
#endif //_DEBUG


 //CCutView 消息处理程序
void CCutView::OnOndrawpic()
{
	// TODO: 在此添加命令处理程序代码
	PtCount=0;
	bDrawLine=TRUE;
	MessageBox(CString("鼠标画线，剪刀裁剪"),CString("提示"),/*MB_YESNO*/MB_OKCANCEL);
}
void CCutView::EnCode(CP2 &pt)//端点编码函数
{
	pt.rc=0;
	if(pt.x<wxl)
		pt.rc=pt.rc|LEFT;// a|b是按位或
	else if(pt.x>wxr)
		pt.rc=pt.rc|RIGHT;
	if(pt.y<wyb)
		pt.rc=pt.rc|BOTTOM;
	else if(pt.y>wyt)
		pt.rc=pt.rc|TOP;
}
void CCutView::Cohen()//Cohen-Sutherland算法
{
	CP2 p;//交点坐标
	EnCode(P[0]);//起点编码
	EnCode(P[1]);//终点编码
	while(P[0].rc!=0 || P[1].rc!=0)//处理至少一个顶点在窗口之外的情况
	{
		if((P[0].rc & P[1].rc)!=0)//简弃之
		{
			PtCount=0;
			return;
		}
		if(0==P[0].rc)//确保P[0]位于窗口之外
		{
			CP2 Temp;
			Temp=P[0];
			P[0]=P[1];
			P[1]=Temp;
		}
		UINT RC=P[0].rc;
		double k=(P[1].y-P[0].y)/(P[1].x-P[0].x);//直线段的斜率
		//窗口边界按左、右、下、上的顺序裁剪直线段
		if(RC & LEFT)//P[0]点位于窗口的左侧1
		{
			p.x=wxl;//计算交点y坐标
			p.y=k*(p.x-P[0].x)+P[0].y;
		}
		else if(RC & RIGHT)//P[0]点位于窗口的右侧
		{
			p.x=wxr;//计算交点y坐标
			p.y=k*(p.x-P[0].x)+P[0].y;
		}
		else if(RC & BOTTOM)//P[0]点位于窗口的下侧
		{
			p.y=wyb;//计算交点x坐标
			p.x=(p.y-P[0].y)/k+P[0].x;
		}			
		else if(RC & TOP)//P[0]点位于窗口的上侧
		{
			p.y=wyt;//计算交点x坐标
			p.x=(p.y-P[0].y)/k+P[0].x;
		}
		EnCode(p);
		P[0]=p;
	}
}
void CCutView::DrawWindowRect(CDC *pDC)
{
	pDC->SetTextColor(RGB(255,0,0));
	pDC->TextOut(wxl+10,wyt+20,CString("窗口"));
	CPen NewPen,*pOldPen;//定义3个像素宽度的画笔
	NewPen.CreatePen(PS_SOLID,3,RGB(0,255,0));
	pOldPen = pDC->SelectObject(&NewPen);
	pDC->Rectangle(wxl,wyb,wxr,wyt);
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}
CP2 CCutView::Convert(CPoint point)//设备坐标系向自定义坐标系转换
{
	CRect rect;
	GetClientRect(&rect);
	CP2 ptemp;
	ptemp.x=point.x-rect.Width()/2;
	ptemp.y=rect.Height()/2-point.y;
	return ptemp;
}
void CCutView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(bDrawLine)
	{	if(PtCount<2)
		{
			P[PtCount]=Convert(point);
			PtCount++;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CCutView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	if(bDrawLine)
	{	if(PtCount<2)
		{
			P[PtCount]=Convert(point);
			Invalidate(FALSE);
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CCutView::OnClip() 
{
	// TODO: 在此添加命令处理程序代码
	Cohen();
	bDrawLine=FALSE;
	Invalidate(FALSE);
}


BOOL CCutView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;//如果应用程序响应处理WM_ERASEBKGND消息并擦除背景，应返回非零值 ；告诉Windows没有必要再擦除
	//当窗口背景必须被擦除时 （例如，窗口的移动，窗口的大小的改变）才发送。
    //当窗口的一部分无效需要重绘时发送此消息。
	//return CView::OnEraseBkgnd(pDC);
}
