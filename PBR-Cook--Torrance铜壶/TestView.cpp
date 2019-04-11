// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//数学头文件
#define Round(d) int(floor(d+0.5))//四舍五入宏定义
#define nNum  4//三次Bezier4个控制点
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
//{{AFX_MSG_MAP(CTestView)
ON_COMMAND(IDM_DRAWPIC, OnDrawpic)
ON_WM_TIMER()
ON_WM_KEYDOWN()
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	Alpha = 0.0, Beta = 0.0;
	bPlay = FALSE;
	P = NULL;
}

CTestView::~CTestView()
{
	if (P!=NULL)
	{
		for (int i = 0; i < NumObject; i++)
		{
			delete []P[i];
		}
		delete []P;
	}
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DoubleBuffer(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

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

/////////////////////////////////////////////////////////////////////////////
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

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::DoubleBuffer(CDC* pDC)//双缓冲
{
	CRect rect;//客户区矩形
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2,rect.Height() / 2);//客户区中心为原点
	CDC memDC;//内存DC	
	memDC.CreateCompatibleDC(pDC);//建立与显示pDC兼容的memDC
	CBitmap NewBitmap, *pOldBitmap;//内存中承载图像的临时位图 
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//创建兼容位图 
	pOldBitmap = memDC.SelectObject(&NewBitmap);//将兼容位图选入memDC
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC自定义坐标系
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2,rect.Height() / 2);
//	memDC.FillSolidRect(rect, pDC->GetBkColor());//设置背景色
	DrawObject(&memDC);//绘制双三次Bezier曲面片
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图
	memDC.DeleteDC();//删除memDC	
}

void CTestView::DrawObject(CDC* pDC)
{
	
	DrawBezier.DrawObject(pDC);
	//DrawBezier.DrawControlGrid(pDC);
}

void CTestView::OnDrawpic() 
{
	// TODO: Add your command handler code here
	bPlay = !bPlay;
	if (bPlay)//设置定时器
		SetTimer(1, 150, NULL);	
	else
		KillTimer(1);
}

void CTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Alpha = 5;
	Beta = 5;
	for (int i = 0; i < NumObject ;i ++)
	{
		transform.SetMatrix(DrawBezier.Vertex[i],64);
		transform.RotateX(Alpha);
		transform.RotateY(Beta);
	}
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
		int i;
	case VK_UP:
		Alpha = -5;
		for (i = 0; i < NumObject ;i ++)
		{
			transform.SetMatrix(DrawBezier.Vertex[i],64);
			transform.RotateX(Alpha);
		}
		
		break;
	case VK_DOWN:
		Alpha = 5;
		for (i = 0; i < NumObject ;i ++)
		{
			transform.SetMatrix(DrawBezier.Vertex[i],64);
			transform.RotateX(Alpha);
		}	
		break;
	case VK_LEFT:
		Beta = -5;
		for (i = 0; i < NumObject ;i ++)
		{
            transform.SetMatrix(DrawBezier.Vertex[i],64);
			transform.RotateY(Beta);
		}
		break;
	case VK_RIGHT:
		Beta = 5;
		for (i = 0; i < NumObject ;i ++)
		{
			transform.SetMatrix(DrawBezier.Vertex[i],64);
			transform.RotateY(Beta);
		}
		break;
	default:
		break;			
	}
	Invalidate(FALSE);	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	NumObject = 4;
	P = new CP3*[NumObject];
	for (int i = 0; i < NumObject; i++)
	{
		P[i] = new CP3 [4];
	}
	//double a = 1.3;
	P[0][0].x = -43,  P[0][0].y = 203, P[0][0].z = 0;
	P[0][1].x = -83,  P[0][1].y = 228, P[0][1].z = 0;
	P[0][2].x = -96,  P[0][2].y = 195, P[0][2].z = 0;
	P[0][3].x = -51,  P[0][3].y = 191, P[0][3].z = 0;
	P[1][0].x = -51,  P[1][0].y = 191, P[1][0].z = 0;
	P[1][1].x = -51,  P[1][1].y = 171, P[1][1].z = 0;
	P[1][2].x = -47,  P[1][2].y = 138, P[1][2].z = 0;
	P[1][3].x = -110,  P[1][3].y = 61, P[1][3].z = 0;
	P[2][0].x = -110,  P[2][0].y = 61, P[2][0].z = 0;
	P[2][1].x = -189,  P[2][1].y = -18, P[2][1].z = 0;
	P[2][2].x = -259,  P[2][2].y = -110, P[2][2].z = 0;
	P[2][3].x = -168,  P[2][3].y = -212, P[2][3].z = 0;
	P[3][0].x = -168,  P[3][0].y = -213, P[3][0].z = 0;
	P[3][1].x = -168,  P[3][1].y = -238 ,P[3][1].z = 0;
	P[3][2].x = -159,  P[3][2].y = -227, P[3][2].z = 0;
	P[3][3].x = 0,  P[3][3].y = -227, P[3][3].z = 0;
	
	
	DrawBezier.ReadBeizerObject(NumObject,P);
}
