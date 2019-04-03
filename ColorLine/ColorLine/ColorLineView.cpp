
// ColorLineView.cpp : CColorLineView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ColorLine.h"
#endif

#include "ColorLineDoc.h"
#include "ColorLineView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PI 3.1415926
#define Round(a) int(floor(a+0.5))//返回按指定位数进行四舍五入的数值。


// CColorLineView

IMPLEMENT_DYNCREATE(CColorLineView, CView)

BEGIN_MESSAGE_MAP(CColorLineView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CColorLineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CColorLineView 构造/析构

CColorLineView::CColorLineView()
{
	// TODO: 在此处添加构造代码
	Theta = 0;
	q = -1;
}

CColorLineView::~CColorLineView()
{
}

BOOL CColorLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CColorLineView 绘制

void CColorLineView::OnDraw(CDC* pDC)
{
	CColorLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;//定义矩形
	GetClientRect(&rect);//获得客户区矩形
	pDC->SetMapMode(MM_ANISOTROPIC);//设置映射模式
	pDC->SetWindowExt(rect.Width(),rect.Height());
	pDC->SetViewportExt(rect.Width(),-rect.Height());//设置视区：x轴水平向右为正，y轴垂直向上为正
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//设置客户区中心为坐标原点
	CDC memDC;//声明内存DC
	CBitmap NewBitmap,*pOldBitmap;
	memDC.CreateCompatibleDC(pDC);//创建一个与显示DC兼容的内存DC 
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//创建兼容内存位图 
	pOldBitmap=memDC.SelectObject(&NewBitmap);//将兼容位图选入内存DC
	memDC.FillSolidRect(rect,pDC->GetBkColor());//按原来背景色填充客户区，否则是黑色
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	memDC.SetMapMode(MM_ANISOTROPIC);//内存DC自定义坐标系
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	DrawObject(&memDC);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY); //将内存DC中的位图拷贝到设备DC
	memDC.SelectObject(pOldBitmap);

	SetTimer(1,5,NULL);


}


// CColorLineView 打印


void CColorLineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CColorLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CColorLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CColorLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CColorLineView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CColorLineView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CColorLineView 诊断

#ifdef _DEBUG
void CColorLineView::AssertValid() const
{
	CView::AssertValid();
}

void CColorLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorLineDoc* CColorLineView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorLineDoc)));
	return (CColorLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CColorLineView 消息处理程序
void CColorLineView::DrawObject(CDC *pDC)
{
	//扇形
	long R = 100;
	long r = 10;
	long r1 = 5*r;
	CPoint ld,rt,as,ae;

	CPen NewPen, *pOldPen;
	CBrush NewBrush, *pOldBrush;

	NewPen.CreatePen(PS_DOT,1,RGB(20,20,20));
	pOldPen=pDC->SelectObject(&NewPen);

	ld = CPoint(-R,-R+200); rt = CPoint(R,R+200); 
	as = CPoint(Round(R*cos(30*PI/180)),-Round(R*sin(30*PI/180))+200); 
	ae = CPoint(Round(R*cos(30*PI/180)),Round(R*sin(30*PI/180))+200);
	pDC->Pie(CRect(ld,rt),as,ae);//调用扇形函数绘制黑色半圆


	pDC->SelectObject(pOldPen);//选入老笔。
	NewPen.DeleteObject();//调用DeleteObject（）函数释放资源。

	//矩形
	long Width = 30, Height = 40;
	NewPen.CreatePen(PS_SOLID,1,RGB(255,0,0));
	pOldPen=pDC->SelectObject(&NewPen);

	if(0<=Theta && Theta<=180)
	{
		ld = CPoint(-Width/2,-Height/2+100-10/9*Theta-r);
		rt = CPoint(Width/2,Height/2+100-10/9*Theta+r);
	}
	if(180<=Theta && Theta<=360)
	{
        ld = CPoint(-Width/2,-Height/2+100-10/9*(Theta+q)-r);
	    rt = CPoint(Width/2,Height/2+100-10/9*(Theta+q)+r);
	}
	pDC->Rectangle(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	
		//下大圆
	NewPen.CreatePen(PS_DOT,1,RGB(0,0,0));
	pOldPen=pDC->SelectObject(&NewPen);

	ld = CPoint(0-r1,-200-r1);
	rt = CPoint(0+r1,-200+r1);
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

		//直线
	pDC->MoveTo(0,300);
	pDC->LineTo(0,-200);

	

		//上方绿线
	NewPen.CreatePen(PS_SOLID,3,RGB(0,255,0));
	pOldPen=pDC->SelectObject(&NewPen);
	if(0<=Theta && Theta<=180)
	{
		as = CPoint(0,200);
		ae = CPoint(Round(1.5*R*cos((30-Theta/3)*PI/180)),200+Round(1.5*R*sin((30-Theta/3)*PI/180)));
	}
	if(180<Theta && Theta<360)
	{
		as = CPoint(0,200);
		ae = CPoint(Round(1.5*R*cos((30-(Theta+q)/3)*PI/180)),200+Round(1.5*R*sin((30-(Theta+q)/3)*PI/180)));
		q-=2;
	}
		//p = 30-(Theta+q)/3;//ae = CPoint(Ro180und(2*R*cos(30*PI/180)),50);
	pDC->MoveTo(as);
	pDC->LineTo(ae);

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//中间红线
	NewPen.CreatePen(PS_SOLID,3,RGB(255,0,0));
	pOldPen=pDC->SelectObject(&NewPen);

	if(0<=Theta && Theta<=180)
	{
		as = CPoint(0,100-10/9*Theta);
		ae = CPoint(Round(R*cos((30-Theta/3)*PI/180)),200+Round(R*sin((30-Theta/3)*PI/180)));
	}
	if(180<=Theta && Theta<=360)
	{
        as = CPoint(0,100-10/9*(Theta+q));
	    ae = CPoint(Round(R*cos((30-(Theta+q)/3)*PI/180)),200+Round(R*sin((30-(Theta+q)/3)*PI/180)));
	}
	pDC->MoveTo(as);
	pDC->LineTo(ae);

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//下方黄线
	NewPen.CreatePen(PS_SOLID,3,RGB(255,255,0));
	pOldPen=pDC->SelectObject(&NewPen);

	//as = CPoint(0,-200+r1);
	//as = CPoint(0,100);
	if(0<=Theta && Theta<=180)
	{
        as = CPoint(Round(r1*cos((-Theta-90)*PI/180)),-200-Round(r1*sin((-Theta-90)*PI/180)));
		ae = CPoint(0,100-10/9*Theta);
		//ae = CPoint(0,100-10/9*Theta);
	}
	if(180<=Theta && Theta<=360)
	{
		as = CPoint(Round(r1*cos((-Theta-90)*PI/180)),-200-Round(r1*sin((-Theta-90)*PI/180)));
        ae = CPoint(0,100-10/9*(Theta+q));
	    //ae = CPoint(0,100-10/9*(Theta+q));
	}
	pDC->MoveTo(as);
	pDC->LineTo(ae);

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//下方蓝线
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,255));
	pOldPen=pDC->SelectObject(&NewPen);

	as = CPoint(0,-200);
	ae = CPoint(Round(r1*cos((-Theta-90)*PI/180)),-200-Round(r1*sin((-Theta-90)*PI/180)));
	pDC->MoveTo(as);
	pDC->LineTo(ae);

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//矩形中小红圆
	NewPen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	pOldPen=pDC->SelectObject(&NewPen);

	
	if(0<=Theta && Theta<=180)
	{
		ld = CPoint(-r,100-10/9*Theta-r);
		rt = CPoint(r,100-10/9*Theta+r);
	}
	if(180<=Theta && Theta<=360)
	{
        ld = CPoint(-r,100-10/9*(Theta+q)-r);
	    rt = CPoint(r,100-10/9*(Theta+q)+r);
	}
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//上方小圆
	NewPen.CreatePen(PS_SOLID,2,RGB(0,255,0));
	pOldPen=pDC->SelectObject(&NewPen);

	ld = CPoint(-r,-r+200);
	rt = CPoint(r,r+200);
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

    //右上方小圆
	NewPen.CreatePen(PS_SOLID,2,RGB(0,255,0));
	pOldPen=pDC->SelectObject(&NewPen);

	//ld = CPoint(Round(R*cos(30*PI/180)-r),-Round(R*sin(30*PI/180))+150-r);
	//rt = CPoint(Round(R*cos(30*PI/180)+r),-Round(R*sin(30*PI/180))+150+r);
	if(0<=Theta && Theta<=180)
	{
        ld = CPoint(Round(R*cos((30-Theta/3)*PI/180))-r,200+Round(R*sin((30-Theta/3)*PI/180))-r);
	    rt = CPoint(Round(R*cos((30-Theta/3)*PI/180))+r,200+Round(R*sin((30-Theta/3)*PI/180))+r);
	}
	if(180<=Theta && Theta<=360)
	{
        ld = CPoint(Round(R*cos((30-(Theta+q)/3)*PI/180))-r,200+Round(R*sin((30-(Theta+q)/3)*PI/180))-r);
	    rt = CPoint(Round(R*cos((30-(Theta+q)/3)*PI/180))+r,200+Round(R*sin((30-(Theta+q)/3)*PI/180))+r);
	}
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//下小蓝圆
	NewPen.CreatePen(PS_SOLID,2,RGB(0,0,255));
	pOldPen=pDC->SelectObject(&NewPen);

	ld = CPoint(0-r,-200-r);
	rt = CPoint(0+r,-200+r);
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//最下小黄圆
	NewPen.CreatePen(PS_SOLID,2,RGB(255,255,0));
	pOldPen=pDC->SelectObject(&NewPen);

	//ld = CPoint(-r,-150-r);
	//rt = CPoint(r,-150+r);
	ld = CPoint(-r+Round(r1*cos((-Theta-90)*PI/180)),-r-200-Round(r1*sin((-Theta-90)*PI/180)));
	rt = CPoint(r+Round(r1*cos((-Theta-90)*PI/180)),r-200-Round(r1*sin((-Theta-90)*PI/180)));
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	
	

}


void CColorLineView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	Theta += 1;
	if(Theta == 360)
			{
				Theta = 0;
				q = -1;
	        }
	Invalidate(FALSE);//直接重绘，不擦除背景。
	CView::OnTimer(nIDEvent);
}

