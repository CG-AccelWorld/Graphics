
// TestView.cpp : CTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//包含数学头文件
#define  PI 3.1415926//PI的宏定义
#define Round(d) int(floor(d+0.5))//四舍五入宏定义

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView()
{
	// TODO: 在此处添加构造代码
	R=800.0;d=1000;Phi=90;Theta=0;
	Alpha=0.0;Beta=0.0;
	V=NULL;F=NULL;
}

CTestView::~CTestView()
{
	if(V!=NULL)
	{
		delete[] V;
		V=NULL;
	}
	for(int n=0;n<N2+2;n++)//注意撤销次序,先列后行,与设置相反
	{
		delete[] F[n];
		F[n]=NULL;
	}
	delete[] F;
	F=NULL;
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestView 绘制

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	DoubleBuffer(pDC);
	//调用时间函数
	SetTimer(1,1,NULL);//第一个参数：ID号。第二个：时间间隔（毫秒）。第三个：回调函数。
}


// CTestView 打印


void CTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

// CTestView 诊断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView 消息处理程序
void CTestView::ReadVertex()//点表
{
	r=100;//圆柱底面半径
	h=300;//圆柱的高
	int cTheta=10;//周向夹角
	int cNum=300;//纵向间距
	double red,green,blue;
	N1=360/cTheta;//N1周向网格数
	N2=Round(h/cNum);//N2为纵向网格数
	V=new CP3[N1*(N2+1)+2];
	double cTheta1,cNum1;
	V[0].x=0.0;V[0].y=-150.0;V[0].z=0.0;//底面中心
	V[0].c=CRGB(0.0,0.0,0.0);
	V[N1*(N2+1)+1].x=0;V[N1*(N2+1)+1].y=h-150;V[N1*(N2+1)+1].z=0;//顶面中心	
	V[N1*(N2+1)+1].c = CRGB(1.0,1.0,1.0);
	for(int i=0;i<N2+1;i++)//纵向
	{	
		cNum1=i*cNum;
		for(int j=0;j<N1;j++)//周向
		{
			cTheta1=j*cTheta*PI/180;
			V[i*N1+j+1].x=r*cos(cTheta1);
			V[i*N1+j+1].y=cNum1-150;	
			V[i*N1+j+1].z=r*sin(cTheta1);			
		}
	}
	for(int j=0;j<N1;j++)//第一圈
		{
			V[j+1].c = CRGB(0.0,0.0,0.0);
		}
	
		for(int j=0;j<N1;j++)//最后一圈
			{
				cTheta1=j*cTheta;
				if(0<=cTheta1 && cTheta1<60)
				{
					red = 1.0;
					green = 0.0 + cTheta1*(1.0/60);
					blue = 0.0;
				}
				if(60<=cTheta1 && cTheta1<120)
				{
					red = 1.0 - (cTheta1-60)*(1.0/60);
					green = 1.0;
					blue = 0.0;
				}
				if(120<=cTheta1 && cTheta1<180)
				{
					red = 0.0;
					green = 1.0;
					blue = 0.0 + (cTheta1-60*2)*(1.0/60);
				}
				if(180<=cTheta1 && cTheta1<240)
				{
					red = 0.0;
					green = 1.0 - (cTheta1-60*3)*(1.0/60);
					blue = 1.0;
				}
				if(240<=cTheta1 && cTheta1<300)
				{
					red = 0.0 + (cTheta1-60*4)*(1.0/60);
					green = 0.0;
					blue = 1.0;
				}
				if(300<=cTheta1 && cTheta1<360)
				{
					red = 1.0;
					green = 0.0;
					blue = 1.0 - (cTheta1-60*5)*(1.0/60);
				}
				V[N1*N2+j+1].c = CRGB(red,green,blue);
			}

	CFill * fill;
	for(int i=1;i<N2;i++)//纵向 中间圈
	{	
		for(int j=0;j<N1;j++)//周向
		{
			V[i*N1+j+1].c = fill->Interpolation(h,V[j+1].y,V[N1*N2+j+1].y,V[j+1].c,V[N1*N2+j+1].c);  
		}
	}
}

void CTestView::ReadFace()//面表
{
	//设置二维动态数组
	F=new CFace *[N2+2];//纵向
	for(int n=0;n<N2+2;n++)
		F[n]=new CFace[N1];//周向
	for(int j=0;j<N1;j++)//构造底部三角形面片
	{
		int tempj=j+1;
		if(tempj==N1) tempj=0;//面片的首尾连接
		int BottomIndex[3];//底部三角形面片索引号数组
		BottomIndex[0]=0;
		BottomIndex[1]=j+1;
		BottomIndex[2]=tempj+1;
		F[0][j].SetNum(3);
		for(int k=0;k<F[0][j].vN;k++)//面片中顶点的索引
			F[0][j].vI[k]=BottomIndex[k];
	}
	for(int i=1;i<=N2;i++)//构造圆柱体四边形面片
	{
		for(int j=0;j<N1;j++)
	    {
			int tempi=i+1;
			int tempj=j+1;
			if(N1==tempj) tempj=0;
			int BodyIndex[4];//圆柱体四边形面片索引号数组
			BodyIndex[0]=(i-1)*N1+j+1;
			BodyIndex[1]=(tempi-1)*N1+j+1;
			BodyIndex[2]=(tempi-1)*N1+tempj+1;
			BodyIndex[3]=(i-1)*N1+tempj+1;
			F[i][j].SetNum(4);
			for(int k=0;k<F[i][j].vN;k++)
				F[i][j].vI[k]=BodyIndex[k];
		}
	}
	for(int j=0;j<N1;j++)//构造顶部三角形面片
	{
		int tempj=j+1;
		if(tempj==N1) tempj=0;
		int TopIndex[3];//顶部三角形面片索引号数组
		TopIndex[0]=N1*(N2+1)+1;
		TopIndex[1]=N1*N2+tempj+1;
		TopIndex[2]=N1*N2+j+1;
		F[N2+1][j].SetNum(3);	
		for(int k=0;k<F[N2+1][j].vN;k++)
			F[N2+1][j].vI[k]=TopIndex[k];
	}
}

void CTestView::InitParameter()//透视变换参数初始化
{	
	k[1]=sin(PI*Theta/180);
	k[2]=sin(PI*Phi/180);
	k[3]=cos(PI*Theta/180);
	k[4]=cos(PI*Phi/180);
	k[5]=k[2]*k[3];
	k[6]=k[2]*k[1];
	k[7]=k[4]*k[3];
	k[8]=k[4]*k[1];
	ViewPoint.x=R*k[6];//用户坐标系的视点球坐标
	ViewPoint.y=R*k[4];
	ViewPoint.z=R*k[5];
}

void CTestView::PerProject(CP3 P)//透视变换
{
	CP3 ViewP;
	ViewP.x=k[3]*P.x-k[1]*P.z;//观察坐标系三维坐标
	ViewP.y=-k[8]*P.x+k[2]*P.y-k[7]*P.z;
	ViewP.z=-k[6]*P.x-k[4]*P.y-k[5]*P.z+R;
	ViewP.c=P.c;
    ScreenP.x=d*ViewP.x/ViewP.z;//屏幕坐标系二维坐标
	ScreenP.y=d*ViewP.y/ViewP.z;
	ScreenP.c=ViewP.c;
}

void CTestView::DoubleBuffer(CDC *pDC)//双缓冲
{
	CRect rect;//定义客户区矩形
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

void CTestView::DrawObject(CDC* pDC)//绘制圆柱体网格
{
    CPi2 Point3[3],t3;//顶面与底面顶点数组
	CPi2 Point4[4],t4;//侧面顶点数组
	for(int i=0;i<N2+2;i++)//N2+2
	{
		for(int j=0;j<N1;j++)
		{
			CVector ViewVector(V[F[i][j].vI[0]],ViewPoint);//面的视向量
			ViewVector=ViewVector.Normalize();//单位化视向量
			F[i][j].SetFaceNormal(V[F[i][j].vI[0]],V[F[i][j].vI[1]],V[F[i][j].vI[2]]);	
			F[i][j].fNormal.Normalize();//单位化法矢量
			if(Dot(ViewVector,F[i][j].fNormal)>=0)//背面剔除
			{
				if(3==F[i][j].vN)//三角形面片
				{
					for(int m=0;m<F[i][j].vN;m++)
					{
						PerProject(V[F[i][j].vI[m]]);
						Point3[m]=ScreenP;
					}			
					CFill *fill=new CFill;//动态分配内存 
					fill->SetPoint(Point3,3);//设置顶点
					fill->CreateBucket();//建立桶表
					fill->CreateEdge();//建立边表
					fill->Gouraud(pDC);//填充面片
					delete fill;//撤销内存
				}
				else//四边形面片
				{
					for(int m=0;m<F[i][j].vN;m++)
					{
						PerProject(V[F[i][j].vI[m]]);
						Point4[m]=ScreenP;						
					}
					CFill *fill=new CFill;//动态分配内存 
					fill->SetPoint(Point4,4);//设置顶点
					fill->CreateBucket();//建立桶表
					fill->CreateEdge();//建立边表
					fill->Gouraud(pDC);//填充面片
					delete fill;//撤销内存
				}
			} 	
		}	
	}
}

void CTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	ReadVertex();
	ReadFace();
	tran.SetMat(V,N1*(N2+1)+2);
	InitParameter();
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		switch(nChar)
		{
		case VK_UP:
			Alpha=-5;
			tran.RotateX(Alpha);
			break;
		case VK_DOWN:
			Alpha=5;
			tran.RotateX(Alpha);
			break;
		case VK_LEFT:
			Beta=-5;
			tran.RotateY(Beta);
			break;
		case VK_RIGHT:
			Beta=5;
			tran.RotateY(Beta);
			break;
		default:
			break;			
		}
		Invalidate(FALSE);		
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CTestView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	R=R+100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnLButtonDown(nFlags, point);
}


void CTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	R=R-100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnRButtonDown(nFlags, point);
}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Beta=5;
	Alpha=5;
	tran.RotateY(Beta);
	tran.RotateX(Alpha);
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}
