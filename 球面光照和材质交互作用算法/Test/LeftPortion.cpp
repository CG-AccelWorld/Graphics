// LeftPortion.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "LeftPortion.h"
#include "TestDoc.h"//
#include "math.h"//


// CLeftPortion

IMPLEMENT_DYNCREATE(CLeftPortion, CFormView)

CLeftPortion::CLeftPortion()
	: CFormView(CLeftPortion::IDD)
{
	EnableAutomation();
}

CLeftPortion::~CLeftPortion()
{
}

void CLeftPortion::OnFinalRelease()
{
	// TODO: 在此添加专用代码和/或调用基类
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。
	CFormView::OnFinalRelease();
}

void CLeftPortion::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_AMBIENT, m_Ambient);
	DDX_Check(pDX, IDC_DIFFUSE, m_Diffuse);  
	DDX_Check(pDX, IDC_SPECULAR, m_Specular);
}

BEGIN_MESSAGE_MAP(CLeftPortion, CFormView)
	ON_BN_CLICKED(IDC_AMBIENT, &CLeftPortion::OnBnClickedAmbient)
	ON_BN_CLICKED(IDC_DIFFUSE, &CLeftPortion::OnBnClickedDiffuse)
	ON_BN_CLICKED(IDC_SPECULAR, &CLeftPortion::OnBnClickedSpecular)
	ON_BN_CLICKED(IDC_GOLD, &CLeftPortion::OnBnClickedGold)
	ON_BN_CLICKED(IDC_RUBY, &CLeftPortion::OnBnClickedRuby)
	ON_BN_CLICKED(IDC_SILVER, &CLeftPortion::OnBnClickedSilver)
	ON_BN_CLICKED(IDC_BERYL, &CLeftPortion::OnBnClickedBeryl)
	ON_BN_CLICKED(IDC_LEFTTOP, &CLeftPortion::OnBnClickedLefttop)
	ON_BN_CLICKED(IDC_LEFTDOWN, &CLeftPortion::OnBnClickedLeftdown)
	ON_BN_CLICKED(IDC_RIGHTTOP, &CLeftPortion::OnBnClickedRighttop)
	ON_BN_CLICKED(IDC_RIGHTDOWN, &CLeftPortion::OnBnClickedRightdown)
END_MESSAGE_MAP()


// CLeftPortion 诊断

#ifdef _DEBUG
void CLeftPortion::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftPortion::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftPortion 消息处理程序

void CLeftPortion::OnBnClickedAmbient()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	//在具有多个视图类的程序中，系统不能分辨是否当前视图与文档类匹配，需进行强制转换。
 	pDoc->UpdateAllViews(NULL,1); 
}

void CLeftPortion::OnBnClickedDiffuse()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,2);
}

void CLeftPortion::OnBnClickedSpecular()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,3);
}

void CLeftPortion::OnBnClickedGold()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,4);
}

void CLeftPortion::OnBnClickedSilver()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,5);
}

void CLeftPortion::OnBnClickedRuby()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,6);
}

void CLeftPortion::OnBnClickedBeryl()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,7);
}

void CLeftPortion::OnBnClickedLefttop()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,8);
}

void CLeftPortion::OnBnClickedLeftdown()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,9);
}

void CLeftPortion::OnBnClickedRighttop()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,10);
}

void CLeftPortion::OnBnClickedRightdown()
{
	// TODO: 在此添加控件通知处理程序代码
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,11);
}

void CLeftPortion::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//设置左窗格控件的初始状态
	CheckRadioButton(IDC_GOLD,IDC_BERYL,IDC_RUBY);
	CheckRadioButton(IDC_LEFTTOP,IDC_RIGHTDOWN,IDC_RIGHTTOP);
	m_Ambient = TRUE;
	m_Diffuse = TRUE;
	m_Specular = TRUE;
	UpdateData(FALSE);
	//UpdateData(TRUE) == 将控件的值赋值给成员变量;UpdateData(FALSE) == 将成员变量的值赋值给控件。
}
