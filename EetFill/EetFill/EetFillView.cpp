
// EetFillView.cpp : CEetFillView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "EetFill.h"
#endif

#include "EetFillDoc.h"
#include "EetFillView.h"
#include "Fill.h"
#include "math.h"
#define Round(a) int(floor(a+0.5))

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEetFillView

IMPLEMENT_DYNCREATE(CEetFillView, CView)

BEGIN_MESSAGE_MAP(CEetFillView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEetFillView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(ID_DRAW, &CEetFillView::OnDraw)
ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_DrawPolygon, &CEetFillView::OnDrawpolygon)
ON_COMMAND(ID_Fill, &CEetFillView::OnFill)
END_MESSAGE_MAP()

// CEetFillView 构造/析构

CEetFillView::CEetFillView()
{
	// TODO: 在此处添加构造代码
}

CEetFillView::~CEetFillView()
{
}

BOOL CEetFillView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CEetFillView 绘制

void CEetFillView::OnDraw(CDC* pDC)
{
	CEetFillDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//CRect rect;                                         //定义客户区
	//GetClientRect(&rect);                               //获得客户区的大小                                   //定义设备上下文指针              
	//pDC->SetMapMode(MM_ANISOTROPIC);                    //自定义坐标系
	//pDC->SetWindowExt(rect.Width(),rect.Height());      //设置窗口比例
	//pDC->SetViewportExt(rect.Width(),-rect.Height());   //设置视区比例，且x轴水平向右，y轴垂直向上
	//pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//设置客户区中心为坐标系原点
	//rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);  //矩形与客户区重合
	////Draw(pDC);
	//FillPolygon(pDC);
}


// CEetFillView 打印


void CEetFillView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEetFillView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CEetFillView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CEetFillView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}
// CEetFillView 诊断

#ifdef _DEBUG
void CEetFillView::AssertValid() const
{
	CView::AssertValid();
}

void CEetFillView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEetFillDoc* CEetFillView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEetFillDoc)));
	return (CEetFillDoc*)m_pDocument;
}
#endif //_DEBUG
void CEetFillView::Draw(CDC*pDC)
{
	for(int i = 0;i<num;i++)
	{
	    if(i == 0)
		{
	        pDC->MoveTo(Q[i]);
			t = Q[i];
		}
		else
		    pDC->LineTo(Q[i]);
	}
}
void CEetFillView::FillPolygon(CDC *pDC)
{
	//ReadPoint();
	for(int i=0;i<num;i++)//转储顶点坐标，y坐标取为整数
	{
		P1[i].x=Round(Q[i].x);
		P1[i].y=Round(Q[i].y);
		if(i == 0)
		    P1[i].c=CRGB(0.0,0.0,0.0);
		if(i == 1)	
		    P1[i].c=CRGB(1.0,0.0,0.0);
		if(i == 2)	
		    P1[i].c=CRGB(1.0,1.0,0.0);
		if(i == 3)	
		    P1[i].c=CRGB(0.0,1.0,0.0);
		if(i == 4)	
		    P1[i].c=CRGB(0.0,0.0,1.0);
		if(i == 5)
		    P1[i].c=CRGB(1.0,0.0,1.0);
	}
	CFill *fill=new CFill;      //动态分配内存 
	fill->SetPoint(P1,num);       //初始化Fill对象
	fill->CreateBucket();       //建立桶表
	fill->CreateEdge();         //建立边表
    fill->Gouraud(pDC);         //填充多边形
	delete fill;                //撤销内存
}
void CEetFillView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDC();
	if(bFlag)
	{
	    Q[num].x = point.x;
	    Q[num].y = point.y;
		if(num<Max)
		num++;
	}
	Draw(pDC);
	ReleaseDC(pDC);
	CView::OnLButtonDown(nFlags, point);
}


void CEetFillView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDC();
	bFlag = FALSE;
	Draw(pDC);
	pDC->LineTo(t);
	ReleaseDC(pDC);
	CView::OnRButtonDown(nFlags, point);
}


void CEetFillView::OnDrawpolygon()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(CString("左键绘制控制多边形，右键闭合多边形"),CString("提示"),MB_OK);
	//RedrawWindow();//擦除背景
	bFlag = TRUE;
	Max = 10;
	num = 0;
    Q=new CPoint[Max];
}


void CEetFillView::OnFill()
{
	// TODO: 在此添加命令处理程序代码
	CDC *pDC = GetDC();
	FillPolygon(pDC);
	ReleaseDC(pDC);
}

