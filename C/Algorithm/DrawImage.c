//DrawImage.c
/*
���ϸ�Ī:DrawImage.c
���:��Ģ���� ã�� �̹����� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��25��
*/
//��ũ�μ���
#include <stdio.h>
#define ROWS 5
#define COLUMNS 5
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char *argv[]);
void DrawImage(char(*image)[COLUMNS]);
void Output(char(*image)[COLUMNS]);
//�Լ�����
int main(int argc, char *argv[])
{
	char image[ROWS][COLUMNS];
	DrawImage(image);
	Output(image);
	return 0;
}
/*
�Լ��̸�:DrawImage
���:��Ģ���� ã�� �̹����� �����
�Է�;X
���:�̹���
*/
void DrawImage(char(*image)[COLUMNS])
{
	ULong i;
	ULong j;
	for (j=0;j<ROWS;j++ )
	{
		for (i = 0; i < COLUMNS; i++)
		{
			if ( j+i== COLUMNS - 1 || j == i)
			{
				image[j][i] = '*';
			}
			else
			{
				image[j][i] = ' ';
			}
	  }
	}
}
/*
�Լ��̸�:Output
���:�̹����� �Է¹޾� ����Ϳ� ����Ѵ�
�Է�:�̹���
���:X
*/
void Output(char(*image)[COLUMNS])
{
	ULong i;
	for (i = 0; i < ROWS; i++)
	{
		printf("%2c%2c%2c%2c%2c\n", image[i][0], image[i][1],image[i][2],image[i][3], image[i][4]);
	}
}
