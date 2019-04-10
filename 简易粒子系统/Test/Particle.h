#pragma once

struct snow
{
	double x;
	double y;
	double speedx; //x方向速度
	double speedy; //y方向速度
	int number;  //粒子图像编号
};

class CParticle
{
public:
	CParticle(void);
	~CParticle(void);
	CParticle(int number,int WIDTH,int HEIGHT);
	void TransparentPNG(CImage *);//将png贴图透明
	void Init();  //初始化粒子
	void Draw(CDC &pDC);  //绘制粒子
	void Update(double time);//更新粒子
private:
	int WIDTH,HEIGHT;
	int m_number; //数量
	struct snow *m_pSnow;  //雪花
	CImage m_snowMap[7]; //七种雪花图像
};

