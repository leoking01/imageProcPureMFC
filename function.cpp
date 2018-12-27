
#include "stdafx.h"
#include "function.h"
#include "math.h"
#include "image_processing.h"

/*
* 24λ���ͼͼ�����ݴ�ţ�
* ÿ������ռ3�ֽڣ����˳��BGR
* ��ͼ�����һ�п�ʼ�棬�浽ͼ���һ��
* ÿһ���е�˳���Ǵ�����
* ÿһ��������ռ�ֽ���������4���������������������ز�����ɫ
*/

//�������ص����c
void BMP_To_Matrix(BITMAPINFO* pBmpInfo,BYTE* pBmpData,unsigned char **** c)
{	
	//���ٿռ�c
	*c = new unsigned char ** [pBmpInfo->bmiHeader.biHeight];	//����c���ָ������Ӧ������ռ䣨һ��biHeight�������飩
	for(int i=0;i<pBmpInfo->bmiHeader.biHeight;i++)
	{
		(*c)[i] = new unsigned char * [pBmpInfo->bmiHeader.biWidth];	//ÿһ�ж�Ӧһ��char *ָ������
		for(int j=0;j<pBmpInfo->bmiHeader.biWidth;j++)
		{
			(*c)[i][j] = new unsigned char [3];
		}
	}

	//����ÿһ��ͼ�����������ֽ���
	int offset = pBmpInfo->bmiHeader.biWidth * 3 % 4;	//�ж��ǲ���4�ı����������ǣ�Ӧ�����Ķ��������������
	if(offset == 0)offset = 4;

	//��ԭͼ���������ؾ�����
	for(int y=0; y<pBmpInfo->bmiHeader.biHeight ; y++)		//�����һ�п�ʼ��������������һ��Ϊֹ��BMP��ʽ�Ǵ����һ�п�ʼ�洢�ģ�
	{
		for(int x=0; x<pBmpInfo->bmiHeader.biWidth ; x++)
		{
			char R,G,B;

			//��Դ�����ȡ���ص����ݣ�д�뵽R G B����������
			B = pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset)+ 3*x ];
			G = pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset) + 3*x + 1 ];
			R = pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset) + 3*x + 2 ];
			
			//���뵽��������ؾ�����
			(*c)[y][x][0] = B;
			(*c)[y][x][1] = G;
			(*c)[y][x][2] = R;
		}
	}
}

//ɾ�����ص����c
void Matrix_To_BMP(BITMAPINFO* pBmpInfo,BYTE* pBmpData,unsigned char *** c)
{
	//����ÿһ��ͼ�����������ֽ���
	int offset = pBmpInfo->bmiHeader.biWidth * 3 % 4;	//�ж��ǲ���4�ı����������ǣ�Ӧ�����Ķ��������������
	if(offset == 0)offset = 4;

	//�����ؾ��󿽱���ԭͼ
	for(int y=0; y<pBmpInfo->bmiHeader.biHeight ; y++)		//�����һ�п�ʼ��������������һ��Ϊֹ��BMP��ʽ�Ǵ����һ�п�ʼ�洢�ģ�
	{
		for(int x=0; x<pBmpInfo->bmiHeader.biWidth ; x++)
		{
			char R,G,B;

			//�����ؾ���ȡ���ص����ݣ�д�뵽R G B����������
			B = c[y][x][0];
			G = c[y][x][1];
			R = c[y][x][2];
			
			//���뵽��������ؾ�����
			pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset) + 3*x ]     = B;
			pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset) + 3*x + 1 ] = G;
			pBmpData[ y*(pBmpInfo->bmiHeader.biWidth*3+4-offset) + 3*x + 2 ] = R;
		}
	}

	//ɾ���ռ�c
	for (int i=0;i<pBmpInfo->bmiHeader.biHeight;i++)
	{
		for (int j=0;j<pBmpInfo->bmiHeader.biWidth;j++)
			delete[] c[i][j];
		delete[] c[i];
	}
	delete[] c;//new��delete�ǳɶԳ��ֵģ�����ҲҪ����ѭ���ͷŵ��ռ�
	c = NULL;
}

//�������ص����c
void BMP_To_GrayMatrix(BITMAPINFO* pBmpInfo, BYTE* pBmpData, unsigned char ** c)
{
	//����һά����ռ�
	(*c) = new unsigned char [pBmpInfo->bmiHeader.biHeight * pBmpInfo->bmiHeader.biWidth];

	//����ÿһ��ͼ�����������ֽ���
	int offset = pBmpInfo->bmiHeader.biWidth * 3 % 4;	//�ж��ǲ���4�ı����������ǣ�Ӧ�����Ķ��������������
	if (offset == 0)offset = 4;

	//��ԭͼ���������ؾ�����
	for (int y = 0; y<pBmpInfo->bmiHeader.biHeight; y++)		//�����һ�п�ʼ��������������һ��Ϊֹ��BMP��ʽ�Ǵ����һ�п�ʼ�洢�ģ�
	{
		for (int x = 0; x<pBmpInfo->bmiHeader.biWidth; x++)
		{
			unsigned char R, G, B;
			unsigned char Gray;

			//��Դ�����ȡ���ص����ݣ�д�뵽R G B����������
			B = pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x];
			G = pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x + 1];
			R = pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x + 2];

			Gray = (R * 299 + G * 587 + B * 114 + 500) / 1000;

			//���뵽��������ؾ�����
			(*c)[y*pBmpInfo->bmiHeader.biWidth + x] = (unsigned char)Gray;
		}
	}
}

//ɾ�����ص����c
void GrayMatrix_To_BMP(BITMAPINFO* pBmpInfo, BYTE* pBmpData, unsigned char ** c)
{
	//����ÿһ��ͼ�����������ֽ���
	int offset = pBmpInfo->bmiHeader.biWidth * 3 % 4;	//�ж��ǲ���4�ı����������ǣ�Ӧ�����Ķ��������������
	if (offset == 0)offset = 4;

	//�����ؾ��󿽱���ԭͼ
	for (int y = 0; y<pBmpInfo->bmiHeader.biHeight; y++)		//�����һ�п�ʼ��������������һ��Ϊֹ��BMP��ʽ�Ǵ����һ�п�ʼ�洢�ģ�
	{
		for (int x = 0; x<pBmpInfo->bmiHeader.biWidth; x++)
		{
			char R, G, B;

			//�����ؾ���ȡ���ص����ݣ�д�뵽R G B����������
			B = (*c)[y*pBmpInfo->bmiHeader.biWidth + x];
			G = (*c)[y*pBmpInfo->bmiHeader.biWidth + x];
			R = (*c)[y*pBmpInfo->bmiHeader.biWidth + x];

			//���뵽��������ؾ�����
			pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x] = B;
			pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x + 1] = G;
			pBmpData[y*(pBmpInfo->bmiHeader.biWidth * 3 + 4 - offset) + 3 * x + 2] = R;
		}
	}

	//ɾ���ռ�c
	delete[] (*c);//new��delete�ǳɶԳ��ֵģ�����ҲҪ����ѭ���ͷŵ��ռ�
	c = NULL;
}

void Fix1(unsigned char * c, double * pd1, double * pd2)
{
	processing(c, pd1, pd2);
}
