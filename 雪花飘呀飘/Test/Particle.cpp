#include "StdAfx.h"
#include "Particle.h"


CParticle::CParticle(void)
{
}

CParticle::CParticle(int number,int WIDTH,int HEIGHT)
{
	m_number=number;
	m_pSnow=new struct snow[m_number];
	this->WIDTH = WIDTH;
	this->HEIGHT = HEIGHT;
}

CParticle::~CParticle(void)
{
	delete[] m_pSnow;
}

//将png贴图透明
void CParticle::TransparentPNG(CImage *png)
{
	for(int i = 0; i <png->GetWidth(); i++)
	{
		for(int j = 0; j <png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(png->GetPixelAddress(i , j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}

void CParticle::Init()
{
	//加载雪花图像
	char buf[20];
	for(int i=0;i<7;i++)    //加载七种图像
	{
		sprintf_s(buf,"Snow//%d.png",i);//将Snow文件夹下的图片打印成字符串保存在buf里
		m_snowMap[i].Load(buf);
		TransparentPNG(&m_snowMap[i]);
	}
	//初始化雪花粒子
	for(int i=0;i<m_number;i++)
	{
		m_pSnow[i].x=rand()% WIDTH;   //最初雪花在水平方向上随机出现
		m_pSnow[i].y=rand()% HEIGHT; //垂直方向上也是随机出现
		m_pSnow[i].number=rand()%7;         //七种雪花中的一种
		m_pSnow[i].speedx=(rand()%5+1)/30.0;
		m_pSnow[i].speedy=(rand()%5+1)/20.0;
	}
}

void CParticle::Draw(CDC &pDC)
{
	//绘制雪花粒子
	for(int i=0;i<m_number;i++)
		m_snowMap[m_pSnow[i].number].Draw(pDC,m_pSnow[i].x,m_pSnow[i].y,32,32);
}

void CParticle::Update(double time)
{
	for(int i=0;i<m_number;i++)
	{
		m_pSnow[i].x+=time*m_pSnow[i].speedx;
		if(m_pSnow[i].x>WIDTH)
			m_pSnow[i].x=-32;  

		m_pSnow[i].y+=time*m_pSnow[i].speedy;
		if(m_pSnow[i].y>HEIGHT)
			m_pSnow[i].y=-32; 
	}
}