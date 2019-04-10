#pragma once
#include "P3.h"

class CLightSource
{
public:
	CLightSource(void);
	virtual ~CLightSource(void);
	void SetDiffuse(CRGBA diffuse);//���ù�Դ���������
	void SetSpecular(CRGBA specular);//���ù�Դ�ľ��淴���
	void SetPosition(double x, double y, double z);//���ù�Դ��ֱ������λ��
	void SetAttenuationFactor(double c0, double c1, double c2);//���ù�ǿ��˥������
	void SetOnOff(BOOL);//���ù�Դ����״̬	
public:
	CRGBA L_Diffuse;//���������ɫ	
	CRGBA L_Specular;//���淴�����ɫ
	CP3 L_Position;//��Դλ��
	double L_C0;//����˥������
	double L_C1;//����˥������
	double L_C2;//����˥������
	BOOL L_OnOff;//��Դ������ر�
};