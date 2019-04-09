#pragma once
class CP2
{
public:
	CP2(void);
	~CP2(void);
public:
	double x;//直线段端点x坐标
	double y;//直线段端点y坐标
	UINT  rc;//直线段端点编码int是有符号的
	//可以为负数，比如8位的int值就是从-128到127.
	//uint是无符号的，只能为0或者是正数，8位uint是从0-255 
	//uint在位操作(bit manipulation)中常用到，如~, <<, >>, &, |, ^ 
	//int  rc;//直线段端点编码
};

