#include "StdAfx.h"
#include "Revolution.h"


CRevolution::CRevolution(void)
{
}


CRevolution::~CRevolution(void)
{
}
void CRevolution::ReadCubicBezierControlPoint(CP3 *ctrP)
{
	for(int i=0;i<4;i++)
		P[i]=ctrP[i];
	ReadVertex();
	ReadPatch();
}
void CRevolution::ReadControlPoint(CP3 *ctrP)
{
	for(int i=0;i<4;i++)
		P[i]=ctrP[i];
	ReadPoint();
	ReadPatch();
}
void CRevolution::ReadPoint()
{
	const double m=0.5523;
	//第一块曲面片
	V[0].x=P[0].x,   V[0].y=P[0].y, V[0].z=P[0].z;
	V[1].x=P[1].x,   V[1].y=P[1].y, V[1].z=P[1].z;
	V[2].x=P[2].x   ,V[2].y=P[2].y, V[2].z=P[2].z;
	V[3].x=P[3].x   ,V[3].y=P[3].y, V[3].z=P[3].z;
	V[4].x=V[0].x,   V[4].y=350, V[4].z=V[0].x*m;
	V[5].x=V[1].x,   V[5].y=V[1].y, V[5].z=V[1].x*m;
	V[6].x=V[2].x,   V[6].y=V[2].y, V[6].z=V[2].x*m;
	V[7].x=V[3].x,   V[7].y=V[3].y, V[7].z=V[3].x*m;
	V[8].x=V[0].x*m, V[8].y=350, V[8].z=V[0].x;
	V[9].x=V[1].x*m, V[9].y=V[1].y, V[9].z=V[1].x;
	V[10].x=V[2].x*m,V[10].y=V[2].y,V[10].z=V[2].x;
	V[11].x=V[3].x*m,V[11].y=V[3].y,V[11].z=V[3].x;
	V[12].x=V[0].z,  V[12].y=V[0].y,V[12].z=V[0].x;
	V[13].x=V[1].z,  V[13].y=V[1].y,V[13].z=V[1].x;
	V[14].x=V[2].z,  V[14].y=V[2].y,V[14].z=V[2].x;
	V[15].x=V[3].z,  V[15].y=V[3].y,V[15].z=V[3].x;
	//第二块曲面片
	V[16].x=V[0].z,   V[16].y=V[0].y, V[16].z=V[0].x;
	V[17].x=V[1].z,   V[17].y=V[1].y, V[17].z=V[1].x;
	V[18].x=V[2].z,   V[18].y=V[2].y, V[18].z=V[2].x;
	V[19].x=V[3].z,   V[19].y=V[3].y, V[19].z=V[3].x;
	V[20].x=-V[0].x*m,V[20].y=350, V[20].z=V[0].x;
	V[21].x=-V[1].x*m,V[21].y=V[1].y, V[21].z=V[1].x;
	V[22].x=-V[2].x*m,V[22].y=V[2].y, V[22].z=V[2].x;
	V[23].x=-V[3].x*m,V[23].y=V[3].y, V[23].z=V[3].x;
	V[24].x=-V[0].x,  V[24].y=350, V[24].z=V[0].x*m;
	V[25].x=-V[1].x,  V[25].y=V[1].y, V[25].z=V[1].x*m;
	V[26].x=-V[2].x,  V[26].y=V[2].y, V[26].z=V[2].x*m;
	V[27].x=-V[3].x,  V[27].y=V[3].y, V[27].z=V[3].x*m;
	V[28].x=-V[0].x,  V[28].y=V[0].y, V[28].z=V[0].z;
	V[29].x=-V[1].x,  V[29].y=V[1].y, V[29].z=V[1].z;
	V[30].x=-V[2].x,  V[30].y=V[2].y, V[30].z=V[2].z;
	V[31].x=-V[3].x,  V[31].y=V[3].y, V[31].z=V[3].z;
	//第三块曲面片
	V[32].x=-V[0].x,  V[32].y=V[0].y, V[32].z=V[0].z;
	V[33].x=-V[1].x,  V[33].y=V[1].y, V[33].z=V[1].z;
	V[34].x=-V[2].x,  V[34].y=V[2].y, V[34].z=V[2].z;
	V[35].x=-V[3].x,  V[35].y=V[3].y, V[35].z=V[3].z;
	V[36].x=-V[0].x,  V[36].y=350, V[36].z=-V[0].x*m;
	V[37].x=-V[1].x,  V[37].y=V[1].y, V[37].z=-V[1].x*m;
	V[38].x=-V[2].x,  V[38].y=V[2].y, V[38].z=-V[2].x*m;
	V[39].x=-V[3].x,  V[39].y=V[3].y, V[39].z=-V[3].x*m;
	V[40].x=-V[0].x*m,V[40].y=350, V[40].z=-V[0].x;
	V[41].x=-V[1].x*m,V[41].y=V[1].y, V[41].z=-V[1].x;
	V[42].x=-V[2].x*m,V[42].y=V[2].y, V[42].z=-V[2].x;
	V[43].x=-V[3].x*m,V[43].y=V[3].y, V[43].z=-V[3].x;
	V[44].x=V[0].z,   V[44].y=V[0].y, V[44].z=-V[0].x;
	V[45].x=V[1].z,   V[45].y=V[1].y, V[45].z=-V[1].x;
	V[46].x=V[2].z,   V[46].y=V[2].y, V[46].z=-V[2].x;
	V[47].x=V[3].z,   V[47].y=V[3].y, V[47].z=-V[3].x;
	//第四块曲面片
	V[48].x=V[0].z,   V[48].y=V[0].y, V[48].z=-V[0].x;
	V[49].x=V[1].z,   V[49].y=V[1].y, V[49].z=-V[1].x;
	V[50].x=V[2].z,   V[50].y=V[2].y, V[50].z=-V[2].x;
	V[51].x=V[3].z,   V[51].y=V[3].y, V[51].z=-V[3].x;
	V[52].x=V[0].x*m,V[52].y=350, V[52].z=-V[0].x;
	V[53].x=V[1].x*m,V[53].y=V[1].y, V[53].z=-V[1].x;
	V[54].x=V[2].x*m,V[54].y=V[2].y, V[54].z=-V[2].x;
	V[55].x=V[3].x*m,V[55].y=V[3].y, V[55].z=-V[3].x;
	V[56].x=V[0].x,  V[56].y=350, V[56].z=-V[0].x*m;
	V[57].x=V[1].x,  V[57].y=V[1].y, V[57].z=-V[1].x*m;
	V[58].x=V[2].x,  V[58].y=V[2].y, V[58].z=-V[2].x*m;
	V[59].x=V[3].x,  V[59].y=V[3].y, V[59].z=-V[3].x*m;
	V[60].x=V[0].x,  V[60].y=V[0].y, V[60].z=V[0].z;
	V[61].x=V[1].x,  V[61].y=V[1].y, V[61].z=V[1].z;
	V[62].x=V[2].x,  V[62].y=V[2].y, V[62].z=V[2].z;
	V[63].x=V[3].x,  V[63].y=V[3].y, V[63].z=V[3].z;

}
void CRevolution::ReadVertex()
{
	const double m=0.5523;
	//第一块曲面片
	V[0].x=P[0].x,   V[0].y=P[0].y, V[0].z=P[0].z;
	V[1].x=P[1].x,   V[1].y=P[1].y, V[1].z=P[1].z;
	V[2].x=P[2].x   ,V[2].y=P[2].y, V[2].z=P[2].z;
	V[3].x=P[3].x   ,V[3].y=P[3].y, V[3].z=P[3].z;
	V[4].x=V[0].x,   V[4].y=V[0].y, V[4].z=V[0].x*m;
	V[5].x=V[1].x,   V[5].y=V[1].y, V[5].z=V[1].x*m;
	V[6].x=V[2].x,   V[6].y=V[2].y, V[6].z=V[2].x*m;
	V[7].x=V[3].x,   V[7].y=V[3].y, V[7].z=V[3].x*m;
	V[8].x=V[0].x*m, V[8].y=V[0].y, V[8].z=V[0].x;
	V[9].x=V[1].x*m, V[9].y=V[1].y, V[9].z=V[1].x;
	V[10].x=V[2].x*m,V[10].y=V[2].y,V[10].z=V[2].x;
	V[11].x=V[3].x*m,V[11].y=V[3].y,V[11].z=V[3].x;
	V[12].x=V[0].z,  V[12].y=V[0].y,V[12].z=V[0].x;
	V[13].x=V[1].z,  V[13].y=V[1].y,V[13].z=V[1].x;
	V[14].x=V[2].z,  V[14].y=V[2].y,V[14].z=V[2].x;
	V[15].x=V[3].z,  V[15].y=V[3].y,V[15].z=V[3].x;
	//第二块曲面片
	V[16].x=V[0].z,   V[16].y=V[0].y, V[16].z=V[0].x;
	V[17].x=V[1].z,   V[17].y=V[1].y, V[17].z=V[1].x;
	V[18].x=V[2].z,   V[18].y=V[2].y, V[18].z=V[2].x;
	V[19].x=V[3].z,   V[19].y=V[3].y, V[19].z=V[3].x;
	V[20].x=-V[0].x*m,V[20].y=V[0].y, V[20].z=V[0].x;
	V[21].x=-V[1].x*m,V[21].y=V[1].y, V[21].z=V[1].x;
	V[22].x=-V[2].x*m,V[22].y=V[2].y, V[22].z=V[2].x;
	V[23].x=-V[3].x*m,V[23].y=V[3].y, V[23].z=V[3].x;
	V[24].x=-V[0].x,  V[24].y=V[0].y, V[24].z=V[0].x*m;
	V[25].x=-V[1].x,  V[25].y=V[1].y, V[25].z=V[1].x*m;
	V[26].x=-V[2].x,  V[26].y=V[2].y, V[26].z=V[2].x*m;
	V[27].x=-V[3].x,  V[27].y=V[3].y, V[27].z=V[3].x*m;
	V[28].x=-V[0].x,  V[28].y=V[0].y, V[28].z=V[0].z;
	V[29].x=-V[1].x,  V[29].y=V[1].y, V[29].z=V[1].z;
	V[30].x=-V[2].x,  V[30].y=V[2].y, V[30].z=V[2].z;
	V[31].x=-V[3].x,  V[31].y=V[3].y, V[31].z=V[3].z;
	//第三块曲面片
	V[32].x=-V[0].x,  V[32].y=V[0].y, V[32].z=V[0].z;
	V[33].x=-V[1].x,  V[33].y=V[1].y, V[33].z=V[1].z;
	V[34].x=-V[2].x,  V[34].y=V[2].y, V[34].z=V[2].z;
	V[35].x=-V[3].x,  V[35].y=V[3].y, V[35].z=V[3].z;
	V[36].x=-V[0].x,  V[36].y=V[0].y, V[36].z=-V[0].x*m;
	V[37].x=-V[1].x,  V[37].y=V[1].y, V[37].z=-V[1].x*m;
	V[38].x=-V[2].x,  V[38].y=V[2].y, V[38].z=-V[2].x*m;
	V[39].x=-V[3].x,  V[39].y=V[3].y, V[39].z=-V[3].x*m;
	V[40].x=-V[0].x*m,V[40].y=V[0].y, V[40].z=-V[0].x;
	V[41].x=-V[1].x*m,V[41].y=V[1].y, V[41].z=-V[1].x;
	V[42].x=-V[2].x*m,V[42].y=V[2].y, V[42].z=-V[2].x;
	V[43].x=-V[3].x*m,V[43].y=V[3].y, V[43].z=-V[3].x;
	V[44].x=V[0].z,   V[44].y=V[0].y, V[44].z=-V[0].x;
	V[45].x=V[1].z,   V[45].y=V[1].y, V[45].z=-V[1].x;
	V[46].x=V[2].z,   V[46].y=V[2].y, V[46].z=-V[2].x;
	V[47].x=V[3].z,   V[47].y=V[3].y, V[47].z=-V[3].x;
	//第四块曲面片
	V[48].x=V[0].z,   V[48].y=V[0].y, V[48].z=-V[0].x;
	V[49].x=V[1].z,   V[49].y=V[1].y, V[49].z=-V[1].x;
	V[50].x=V[2].z,   V[50].y=V[2].y, V[50].z=-V[2].x;
	V[51].x=V[3].z,   V[51].y=V[3].y, V[51].z=-V[3].x;
	V[52].x=V[0].x*m,V[52].y=V[0].y, V[52].z=-V[0].x;
	V[53].x=V[1].x*m,V[53].y=V[1].y, V[53].z=-V[1].x;
	V[54].x=V[2].x*m,V[54].y=V[2].y, V[54].z=-V[2].x;
	V[55].x=V[3].x*m,V[55].y=V[3].y, V[55].z=-V[3].x;
	V[56].x=V[0].x,  V[56].y=V[0].y, V[56].z=-V[0].x*m;
	V[57].x=V[1].x,  V[57].y=V[1].y, V[57].z=-V[1].x*m;
	V[58].x=V[2].x,  V[58].y=V[2].y, V[58].z=-V[2].x*m;
	V[59].x=V[3].x,  V[59].y=V[3].y, V[59].z=-V[3].x*m;
	V[60].x=V[0].x,  V[60].y=V[0].y, V[60].z=V[0].z;
	V[61].x=V[1].x,  V[61].y=V[1].y, V[61].z=V[1].z;
	V[62].x=V[2].x,  V[62].y=V[2].y, V[62].z=V[2].z;
	V[63].x=V[3].x,  V[63].y=V[3].y, V[63].z=V[3].z;

}
void CRevolution::ReadPatch()
{
	//第一卦限曲面片
	S[0].pNumber=16;
	S[0].pIndex[0][0]=0;S[0].pIndex[0][1]=4;S[0].pIndex[0][2]=8;S[0].pIndex[0][3]=12;    
	S[0].pIndex[1][0]=1;S[0].pIndex[1][1]=5;S[0].pIndex[1][2]=9;S[0].pIndex[1][3]=13;
	S[0].pIndex[2][0]=2;S[0].pIndex[2][1]=6;S[0].pIndex[2][2]=10;S[0].pIndex[2][3]=14;
	S[0].pIndex[3][0]=3;S[0].pIndex[3][1]=7;S[0].pIndex[3][2]=11;S[0].pIndex[3][3]=15;
	//第二卦限曲面片
	S[1].pNumber=16;
	S[1].pIndex[0][0]=16;S[1].pIndex[0][1]=20;S[1].pIndex[0][2]=24;S[1].pIndex[0][3]=28;    
	S[1].pIndex[1][0]=17;S[1].pIndex[1][1]=21;S[1].pIndex[1][2]=25;S[1].pIndex[1][3]=29;
	S[1].pIndex[2][0]=18;S[1].pIndex[2][1]=22;S[1].pIndex[2][2]=26;S[1].pIndex[2][3]=30;
	S[1].pIndex[3][0]=19;S[1].pIndex[3][1]=23;S[1].pIndex[3][2]=27;S[1].pIndex[3][3]=31;
	//第三卦限曲面片
	S[2].pNumber=16;
	S[2].pIndex[0][0]=32;S[2].pIndex[0][1]=36;S[2].pIndex[0][2]=40;S[2].pIndex[0][3]=44;    
	S[2].pIndex[1][0]=33;S[2].pIndex[1][1]=37;S[2].pIndex[1][2]=41;S[2].pIndex[1][3]=45;
	S[2].pIndex[2][0]=34;S[2].pIndex[2][1]=38;S[2].pIndex[2][2]=42;S[2].pIndex[2][3]=46;
	S[2].pIndex[3][0]=35;S[2].pIndex[3][1]=39;S[2].pIndex[3][2]=43;S[2].pIndex[3][3]=47;
	//第四卦限曲面片
	S[3].pNumber=16;
	S[3].pIndex[0][0]=48;S[3].pIndex[0][1]=52;S[3].pIndex[0][2]=56;S[3].pIndex[0][3]=60;    
	S[3].pIndex[1][0]=49;S[3].pIndex[1][1]=53;S[3].pIndex[1][2]=57;S[3].pIndex[1][3]=61;
	S[3].pIndex[2][0]=50;S[3].pIndex[2][1]=54;S[3].pIndex[2][2]=58;S[3].pIndex[2][3]=62;
	S[3].pIndex[3][0]=51;S[3].pIndex[3][1]=55;S[3].pIndex[3][2]=59;S[3].pIndex[3][3]=63;

}
void CRevolution::DrawRevolutionSurface(CDC*pDC,CP3 ViewPoint,CLighting *pLight,CMaterial *pMaterial)
{
	for(int nPatch=0;nPatch<4;nPatch++)
	{
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				P3[i][j]=V[S[nPatch].pIndex[i][j]];
		surf.ReadControlPoint(P3);
		surf.DrawCurvedPatch(pDC,ViewPoint,pLight,pMaterial);
		for(int i=0;i<121;i++)
		{
			MV[nPatch][i]=surf.PV[i];
			Nv[nPatch][i]=surf.NV[i];
		}


	}

}
