#pragma once



// CLeftPortion 窗体视图

class CLeftPortion : public CFormView
{
	DECLARE_DYNCREATE(CLeftPortion)

protected:
	CLeftPortion();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftPortion();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedAmbient();
	afx_msg void OnBnClickedDiffuse();
	afx_msg void OnBnClickedSpecular();
	afx_msg void OnBnClickedGold();
	afx_msg void OnBnClickedRuby();
	afx_msg void OnBnClickedSilver();
	afx_msg void OnBnClickedBeryl();
	afx_msg void OnBnClickedLefttop();
	afx_msg void OnBnClickedLeftdown();
	afx_msg void OnBnClickedRighttop();
	afx_msg void OnBnClickedRightdown();
	BOOL m_Ambient;
	BOOL m_Diffuse;
	BOOL m_Specular;
	virtual void OnFinalRelease();
};


