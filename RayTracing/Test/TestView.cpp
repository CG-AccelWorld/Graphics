
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
#include "math.h"
#define  PI 3.1415926
#define  MIN(a,b)  ((a<b)?(a):(b))
#define  MAX(a,b)  ((a>b)?(a):(b))
#define Round(d) int(floor(d+0.5))


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView()
{
	// TODO: 在此处添加构造代码
	Positionlight[0] = CP3(0,0,800);//设置光源位置坐标
	Positionlight[1] = CP3(-200,800,800);//设置光源位置坐标
	nLightCount =2;
	 
 	pLight=new CLighting(nLightCount);//一维光源动态数组
	pLight->Light[0].SetPosition(Positionlight[0].x,Positionlight[0].y,Positionlight[0].z);//设置光源位置坐标
	pLight->Light[1].SetPosition(Positionlight[1].x,Positionlight[1].y,Positionlight[1].z);//设置光源位置坐标	
	for(int i=0;i<nLightCount;i++)
	{
		pLight->Light[0].L_Diffuse = CRGB(255.0, 255.0, 255.0); //光源的漫反射颜色	
		pLight->Light[0].L_Specular = CRGB(255.0, 255.0, 255.0);//光源镜面高光颜色
		pLight->Light[0].L_C0 = 1.0;//常数衰减系数
		pLight->Light[0].L_C1 = 0.0000001;//线性衰减系数
		pLight->Light[0].L_C2 = 0.00000001;//二次衰减系数
		pLight->Light[0].L_OnOff = true;//光源开启	

	}

	pMaterial[0].SetAmbient(CRGB(0.1,0.1,0.1));//材质对环境光的反射率
	pMaterial[0].SetDiffuse(CRGB(0.2,0.2,0.2));//材质对环境光和漫反射光的反射率相等
	pMaterial[0].SetSpecular(CRGB(0.99,0.99,0.99));//材质对镜面反射光的反射率
	pMaterial[0].SetEmit(CRGB(0.0,0.0,0.0));//材质自身发散的颜色
	pMaterial[0].M_n=100.0;//高光指数
	pMaterial[0].sigma = 1.1;

	pMaterial[1].SetAmbient(CRGB(0.0,0.1,0.0));//材质对环境光的反射率
	pMaterial[1].SetDiffuse(CRGB(0.0,0.508,0.0));//材质对环境光和漫反射光的反射率相等
	pMaterial[1].SetSpecular(CRGB(0.0,0.508,0.0));//材质对镜面反射光的反射率
	pMaterial[1].SetEmit(CRGB(0,0,0));//材质自身发散的颜色
	pMaterial[1].M_n=50.0;//高光指数
	pMaterial[1].sigma = 0;

	pMaterial[2].SetAmbient(CRGB(0.1,0.0,0.0));//材质对环境光的反射率
	pMaterial[2].SetDiffuse(CRGB(1.0,0.0,0.0));//材质对环境光和漫反射光的反射率相等
	pMaterial[2].SetSpecular(CRGB(1.0,0.2,0.2));//材质对镜面反射光的反射率
	pMaterial[2].SetEmit(CRGB(1.0,0,0));//材质自身发散的颜色
	pMaterial[2].M_n=50.0;//高光指数
	pMaterial[2].sigma = 0;

	pMaterial[3].SetAmbient(CRGB(0.1,0.1,0.0));//材质对环境光的反射率
	pMaterial[3].SetDiffuse(CRGB(1.0,1.0,0.0));//材质对环境光和漫反射光的反射率相等
	pMaterial[3].SetSpecular(CRGB(1.0,0.1,0.1));//材质对镜面反射光的反射率
	pMaterial[3].SetEmit(CRGB(0.5,0.5,0));//材质自身发散的颜色
	pMaterial[3].M_n=20.0;//高光指数
	pMaterial[3].sigma = 0;

	is_pppp = true;
}

CTestView::~CTestView()
{
	delete pLight;
	for(int i=0; i<5; i++)
	{
		delete objects[i];
	}
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
}


// CTestView 打印

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
void CTestView::DoubleBuffer(CDC* pDC)//双缓冲
{
	CRect rect;//客户区矩形
	GetClientRect(&rect);//获得客户区的大小
	Width = rect.Width();
    Height = rect.Height();
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
	//pDC->FillSolidRect(rect,pDC->GetBkColor());//按原来背景填充客户区，否则是黑色
	pDC->FillSolidRect(rect,RGB(0,0,0));

	DrawObject(pDC);//绘制对象
	
//	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图
	memDC.DeleteDC();//删除memDC
}

void CTestView::DrawObject(CDC* pDC)
{
	objects[0] = new CPlane(200,CP3(0.0,1.0,0.0),pMaterial[0],-400,400,-200,-200,-1600,0);//下面的墙
	objects[1] = new CSphere(70,CP3(120,-110, -80),pMaterial[0]);//获取球的半径，位置，材质
	objects[2] = new CSphere(100,CP3(-20,-70, -200),pMaterial[1]);//获取球的半径，位置，材质
	objects[3] = new CSphere(50,CP3(-150,-150,-50),pMaterial[2]);//获取球的半径，位置，材质
	objects[4] = new CSphere(90,CP3(150,-120, -500),pMaterial[3]);//获取球的半径，位置，材质
	nObjectCount =5;

	for (int i = -Width/2; i< Width/2; i++)//遍历背景
	{
		for (int j = -Height/2; j< Height/2; j++)
		{
			is_pppp = true;
			CVector EyeToScreenP(projection.ViewPoint,CP3(i,j,-200)); //从屏幕到 某一视点  像素中心得 矢量	
			CRay ray(projection.ViewPoint,EyeToScreenP); //光线的 起点， 方向矢量
			ray.alpha = -1;
			ray.Normalized();  //单位化该矢量

			CRGB color = Trace(ray,5);   //发出这条矢量		

			CP2 p = projection.PerspectiveProjection(ppppp);//透视投影
			color.Normalize();
			pDC->SetPixelV(Round(p.x),Round(p.y),RGB(color.red,color.green,color.blue));
		}
	}
}
CRGB CTestView::Trace(CRay ray, int count) // 从视点 发出的 第一条 矢量  、 递归次数
{
	CRGB ret(0.0,0.0,0.0); //初始 颜色 、黑色
	if(!count)//递归次数为count
	{
		return ret;
	}
	CInterPoint min_hit; 
	for (int i = 0; i<nObjectCount; i++)// 循环所有物体，找到 最先与此条光线相交 的一点
	{
		CInterPoint hit;
		if (objects[i]->GetInterPoint(ray,hit) && hit.t > 0.00001 &&hit.t < min_hit.t)
		{
			min_hit = hit; //找到最近的交点保存
		}
	}

	if (min_hit.t == 100000)  //没有找到
	{
		return ret;
	}
	else
	{
		if (is_pppp)//保存每一次刚开始的交点坐标，让其透视投影
		{
			ppppp = min_hit.IntersectionPoint;
		}
		is_pppp = FALSE;
		return Shade(ray, min_hit, count);  //找到了光线与物体的第一个交点min_hit
	}
}
CRGB CTestView::Shade(CRay ray, CInterPoint  hit, int count)//此条光线矢量  交点 递归次数
{
	CRGB ret(0.0,0.0,0.0);
	CP3 point = hit.IntersectionPoint;  //光线与物体的交点
	for (int i = 0; i < nLightCount; i++)
	{
		CRay shadow_ray(point, CVector(point,pLight->Light[i].L_Position)); //交点到 光源的 光线
		shadow_ray.Normalized();//方向单位化
	                                             
		CInterPoint min_hit;
		for (int j = 0; j<nObjectCount; j++)//判断在 交点和 光源之间是否有物体阻挡
			{
				CInterPoint hit1;
				if (objects[j]->GetInterPoint(shadow_ray, hit1) && hit1.t > 0.00001 && hit1.t < min_hit.t)
				{
					min_hit = hit1;	

				}
			}
		//交点与光源的距离
		double dist = sqrt(pow(pLight->Light[i].L_Position.x-point.x,2)+ 
		pow(pLight->Light[i].L_Position.y-point.y,2)+ 
		pow(pLight->Light[i].L_Position.z-point.z,2) );


//		if (min_hit.t >= dist)
		{
			 ret += pLight->Lighting(ray.origin ,point, hit.Nformal,&hit.pMaterial, i);
		}
	}

///////////	
	////加入递归
	CRGB TotalRGB ;
	CRGB s = Trace(CalculateReflection(ray, hit), count - 1); //反射
	CRGB t(0.0,0.0,0.0);
	t = Trace(CalculateRefraction(ray, hit), count - 1);
	if(hit.pMaterial.sigma != 0)//物体透明
	{
		TotalRGB = 0.8 * t + (1 - 0.5 - 0.08) * ret + 0.08 * s;
	}
	else
	{
		TotalRGB = 0.02 * t + 0.280 * s + 0.7 * ret ;
	}
	return TotalRGB;
}     

CRay CTestView::CalculateReflection(CRay in, CInterPoint hit) //已知入射光线 和交点 求反射 光线
{
	CRay ret;
	CVector VL(-in.dir.x, -in.dir.y, -in.dir.z);//单位化之后的入射光线矢量
	CVector VN(hit.Nformal.x, hit.Nformal.y, hit.Nformal.z);//交点法向量矢量
	VN = VN.Normalize();//单位化
	CVector R = 2.0 * VN * fabs(DotProduct(VN, VL)) - VL;

	ret.dir.x = R.x;
	ret.dir.y = R.y;
	ret.dir.z = R.z;//新光线的方向矢量
	ret.origin = hit.IntersectionPoint;//新光线的起始点
	ret.Normalized();

	return ret;
}
CRay CTestView::CalculateRefraction(CRay in, CInterPoint hit) //折射
{
	CRay ret;
	hit.Nformal = hit.Nformal.Normalize();//交点法向量矢量单位化

	double angle1 = -(in.dir.x*hit.Nformal.x + in.dir.y*hit.Nformal.y + in.dir.z*hit.Nformal.z);
	double angle2 = sqrt(1-((1-angle1*angle1)/(hit.pMaterial.sigma*hit.pMaterial.sigma)));
	
	double tmp = angle1/hit.pMaterial.sigma - angle2;

	ret.dir.x = tmp*hit.Nformal.x + in.dir.x/hit.pMaterial.sigma;//新光线的方向矢量
	ret.dir.y = tmp*hit.Nformal.y + in.dir.y/hit.pMaterial.sigma;
	ret.dir.z = tmp*hit.Nformal.z + in.dir.z/hit.pMaterial.sigma;

	ret.origin = hit.IntersectionPoint;//新光线的起始点

	ret.Normalized();
	return ret;
} 