
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
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")//导入声音头文件库
#define SNOW_NUMBER 200  //雪花例子的数量
//定时器的名称用宏比较清楚
#define TIMER_PAINT 1
#define TIMER_HEROMOVE 2
//四个方向
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3
//窗口大小
#define WINDOW_WIDTH 1916
#define WINDOW_HEIGHT 964

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
	ON_COMMAND(ID_GRAPH_DRAW, &CTestView::OnGraphDraw)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DRAW, &CTestView::OnUpdateGraphDraw)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_APP_Play, &CTestView::OnAppPlay)
	ON_COMMAND(ID_MUSIC_PLAY, &CTestView::OnMusicPlay)
END_MESSAGE_MAP()

// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	bPlay = TRUE;
	bFlag = TRUE;
}

CTestView::~CTestView()
{
	mciSendString("stop bgMusic ",NULL,0,NULL);
	delete m_snow;
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTestView drawing

void CTestView::OnDraw(CDC* /*pDC*/)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
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


void CTestView::OnGraphDraw()
{
	// TODO: Add your command handler code here
}


void CTestView::OnUpdateGraphDraw(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

//计算地图左端x开始位置
void CTestView::GetMapStartX()
{
	//如果人物不在最左边和最右边半个屏幕内时，地图的起始坐标是需要根据人物位置计算的。
	if(MyHero.x<m_mapWidth-WINDOW_WIDTH/2 && MyHero.x>WINDOW_WIDTH/2)
		m_xMapStart=MyHero.x-WINDOW_WIDTH/2;
}
//获取人物在屏幕上的坐标
int GetScreenX(int xHero,int mapWidth)
{
	//如果人物在最左边和最右边半个屏幕内时，那么人物就处在屏幕中间
	if(xHero<mapWidth-WINDOW_WIDTH/2 && xHero>WINDOW_WIDTH/2)
		return WINDOW_WIDTH/2;
	else if(xHero<=WINDOW_WIDTH/2)     //在最左边半个屏幕时，人物在屏幕上的位置就是自己的x坐标了
		return xHero;
	else 
		return WINDOW_WIDTH-(mapWidth-xHero);  //在最右边半个屏幕
}

void CTestView::DrawObject()
{
	static double lastTime=timeGetTime();   //函数以毫秒计的系统时间。该时间为从系统开启算起所经过的时间。 
	static double currentTime=timeGetTime();
	//获取窗口DC指针
	CDC *cDC=this->GetDC();
	//获取窗口大小
	GetClientRect(&rect);
	//创建缓冲DC
	memDC.CreateCompatibleDC(NULL);
	memBitmap.CreateCompatibleBitmap(cDC,rect.Width(),rect.Height());
	memDC.SelectObject(&memBitmap);
	//计算背景地图起始位置
	GetMapStartX();
	//————————————————————开始绘制——————————————————————
	//贴背景,现在贴图就是贴在缓冲DC：m_cache中了
	m_bg.Draw(memDC,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,m_xMapStart,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	//贴英雄
	MyHero.hero.Draw(memDC,GetScreenX(MyHero.x,m_mapWidth),MyHero.y,120,120,MyHero.frame*80,MyHero.direct*80,80,80);
	//绘制雪花粒子
	m_snow->Draw(memDC);
	//更新雪花
	currentTime=timeGetTime();
	m_snow->Update(currentTime-lastTime);
	lastTime=currentTime;
	//最后将缓冲DC内容输出到窗口DC中
	cDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);

	//————————————————————绘制结束—————————————————————
	
	//在绘制完图后,使窗口区有效
	ValidateRect(&rect);
	//释放缓冲DC
	memDC.DeleteDC();
	//释放对象
	memBitmap.DeleteObject();
	//释放窗口DC
	ReleaseDC(cDC);
}

void CTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	//加载背景
	m_bg.Load("bigbg.png");
	//获取背景地图的宽度
	m_mapWidth=m_bg.GetWidth();
	//加载雪花图像
	m_snow=new CParticle(SNOW_NUMBER,WINDOW_WIDTH,WINDOW_HEIGHT);
	//初始化雪花粒子
	m_snow->Init();
	//加载英雄图片
	MyHero.hero.Load("heroMove.png");
	m_snow->TransparentPNG(&MyHero.hero);
	//初始化英雄状态
	MyHero.direct=UP;
	MyHero.frame=0;
	//设置英雄初始位置
	MyHero.x=80;    
	MyHero.y=700;
	//设置地图初始从最左端开始显示
	m_xMapStart=0;
	//打开音乐文件
	mciSendString("open BackMusic认真的雪.mp3 alias bgMusic ", NULL, 0, NULL);
	mciSendString("play bgMusic repeat", NULL, 0, NULL);
}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case TIMER_PAINT:DrawObject();//若是重绘定时器，就执行OnPaint函数
		break;  
	case TIMER_HEROMOVE:               //控制人物移动的定时器
		{
			MyHero.frame++;              //每次到了间隔时间就将图片换为下一帧
			if(MyHero.frame==4)          //到最后了再重头开始
				MyHero.frame=0;
		}
		break;
	}

	CView::OnTimer(nIDEvent);
}

int CTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//创建一个10毫秒产生一次消息的定时器
	SetTimer(TIMER_PAINT,10,NULL);
	//创建人物行走动画定时器
	SetTimer(TIMER_HEROMOVE,100,NULL);
	return 0;
}


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	//nChar表示按下的键值
	switch(nChar)
	{
	case 'd':         //游戏中按下的键当然应该不区分大小写了
	case 'D':
	case VK_RIGHT:
		MyHero.direct=RIGHT;
		MyHero.x+=5;
		break;
	case 'a':
	case 'A':
	case VK_LEFT:
		MyHero.direct=LEFT;
		MyHero.x-=5;
		break;
	case 'w':
	case 'W':
	case VK_UP:
		MyHero.direct=UP;
		MyHero.y-=5;
		break;
	case 's':
	case 'S':
	case VK_DOWN:
		MyHero.direct=DOWN;
		MyHero.y+=5;
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTestView::OnAppPlay()
{
	// TODO: Add your command handler code here
	bFlag = !bFlag;
	if(bFlag)//设置定时器
		SetTimer(TIMER_PAINT, 10, NULL);	
	else
		KillTimer(TIMER_PAINT);
}


void CTestView::OnMusicPlay()
{
	// TODO: Add your command handler code here
	bPlay = !bPlay;
	if(bPlay)//设置定时器
	{	
		//打开音乐文件
		mciSendString("open BackMusic认真的雪.mp3 alias bgMusic ", NULL, 0, NULL);
		mciSendString("play bgMusic repeat", NULL, 0, NULL);	
	}
	else
		mciSendString("stop bgMusic ",NULL,0,NULL);
}
