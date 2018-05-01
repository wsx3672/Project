//ArrangeNumbers4.c
/*
���ϸ�Ī:ArrangeNumbers4.c
���:��Ģ���� ã�� ���� �Է��Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��25��
*/
//��ũ�μ���
#include <stdio.h>
#define ROWS 5
#define COLUMNS 5
#pragma warning (disable:4996)
//�ڷ�������
typedef signed long int Long;
//�Լ�����
int main(int argc, char *argv[]);
void ArrangeNumbers4(Long(*numbers)[COLUMNS]);
void Output(Long(*numbers)[COLUMNS]);
//�Լ�����
int main(int argc, char *argv[])
{
	Long numbers[ROWS][COLUMNS];
	ArrangeNumbers4(numbers);
	Output(numbers);
	return 0;
}
/*
�Լ��̸�:ArrangeNumbers4
���:��Ģ���� ã�� ���� �Է��Ѵ�
�Է�:X
���:�̹���
*/
void ArrangeNumbers4(Long(*numbers)[COLUMNS])
{
	Long i;
	Long j;
	Long remainber;
	Long number = 1;
	for (j = 1; j < ROWS + 1; j++)
	{
		remainber = j % 2;
		if (remainber == 0)
		{
			i = COLUMNS - 1;
			while (i >= 0)
			{
				numbers[j - 1][i] = number;
				number++;
				i--;
			}

		}
	
		else
		{
			i = 0;
			while (i < COLUMNS)
			{
				numbers[j - 1][i] = number;
				number++;
				i++;
			}

		}
	}

}
/*
�Լ��̸�:Output
���:���ĵȼ����� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:����
���:X
*/
void Output(Long(*numbers)[COLUMNS])
{
	Long i;
	for (i = 0; i < ROWS; i++)
	{
		printf("%2d %2d %2d %2d %2d\n", numbers[i][0], numbers[i][1], numbers[i][2], numbers[i][3], numbers[i][4]);
	}
}