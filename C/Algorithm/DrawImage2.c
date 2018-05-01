//DrawImage2.c
/*
���ϸ�Ī:DrawImage2.c
���:��Ģ���� ã�� �̹����� �׸���
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
void DrawImage2(char(*image)[COLUMNS]);
void Output(char(*image)[COLUMNS]);
//�Լ�����
int main(int argc, char *argv[])
{
	char image[ROWS][COLUMNS];
	DrawImage2(image);
	Output(image);
	return 0;
}
/*
�Լ��̸�:DrawImage2
���:��Ģ���� ã�� �̹����� �׸���
�Է�:X
���:�̹���
*/
void DrawImage2(char(*image)[COLUMNS])
{
	ULong i;
	ULong j;
	ULong remainder;
	for (j = 1; j < ROWS + 1; j++)
	{
		remainder = j % 2;
		i = 1;
		if (remainder == 0)
		{
			while (i < COLUMNS + 1)
			{
				remainder = i % 2;
				if (remainder == 0)
				{
					image[j - 1][i - 1] = '*';
					
				}
				else
				{
					image[j - 1][i - 1] = ' ';
				}
				i++;
			}
		}
		else 
		{
			while (i < COLUMNS + 1)
			{
				remainder = i % 2;
				if (remainder == 1)
				{
					image[j - 1][i - 1] = '*';
				}
				else
				{
					image[j - 1][i - 1] = ' ';
				}
				i++;
			}
		}
	}	

}
/*
�Լ��̸�:Output
���:�̹����� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:�̹���
���:X
*/
void Output(char(*image)[COLUMNS])
{
	{
		ULong i;
		for (i = 0; i < ROWS; i++)
		{
			printf("%2c%2c%2c%2c%2c\n", image[i][0], image[i][1], image[i][2], image[i][3], image[i][4]);
		}
	}

}