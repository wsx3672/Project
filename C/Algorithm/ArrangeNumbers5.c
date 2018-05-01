//ArrangeNumbers5.c
/*
���ϸ�Ī:ArrangeNumbers5.c
���:��Ģ���� ã�� ������ �Է��Ѵ�
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
void ArrangeNumbers5(Long(*numbers)[COLUMNS]);
void Output(Long(*numbers)[COLUMNS]);
//�Լ�����
int main(int argc, char *argv[])
{
	Long numbers[ROWS][COLUMNS];
	ArrangeNumbers5(numbers);
	Output(numbers);
	return 0;
}
/*
�Լ��̸�:ArrangeNumbers5
���:��Ģ���� ã�� ���� �Է��Ѵ�
�Է�:X
���:�̹���
*/
void ArrangeNumbers5(Long(*numbers)[COLUMNS])
{
	Long i = 0;
	Long j = 0;
	Long k;
	Long number = 1;
	Long remainder;
	for (k = 1; k <= ROWS; k++)
	{
		remainder = k % 2;
		if (remainder == 1)
		{
			while (i<k-1)
			{
				numbers[i][j] = number;
				number++;
				i++;
			}
			while (j>=0)
			{
				numbers[i][j] = number;
				number++;
				j--;
			}
		}
		else
		{
			while (j < k - 1)
			{
				numbers[i][j] = number;
				number++;
				j++;

			}
			while (i >= 0)
			{
				numbers[i][j] = number;
				number++;
				i--;
			}
		}
		j++;
		i++;
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