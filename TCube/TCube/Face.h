#pragma once
class CFace
{
public:
	CFace(void);
	~CFace(void);
	void SetNum(int);//设置面的顶点数
public:
	int vN; //面的顶点数
	int *vI;//面的顶点索引
};

