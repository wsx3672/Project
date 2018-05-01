//ArrangeNumbers6.c
/*
���ϸ�Ī:ArrangeNumbers6.c
���:��Ģ���� ã�� ��Ī�� �̿��Ͽ� ������ �Է��Ѵ�
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
void ArrangeNumbers6(ULong(*numbers)[COLUMNS]);
void Output(ULong(*numbers)[COLUMNS]);
//�Լ�����
int main(int argc, char *argv[])
{
	ULong numbers[ROWS][COLUMNS];
	ArrangeNumbers6(numbers);
	Output(numbers);
	return 0;
}
/*
�Լ��̸�:ArrangeNumbers6
���:��Ģ���� ã�� ��Ī�� �̿��Ͽ� ���鸦 �Է��Ѵ�
�Է�:X
���:�̹���
*/
void ArrangeNumbers6(ULong(*numbers)[COLUMNS])
{
	ULong i;
	ULong j;
	for (i = 0; i <(ROWS +1)/ 2; i++)
	{
		for (j = 0; j<(COLUMNS+1) / 2; j++)
		{
			if (i + j < 2)
			{
				numbers[i][j] = 0;
			}
			else
			{
				numbers[i][j] = i + j - 1;
			}
			if (i != 2 && j != 2)
			{
				numbers[ROWS-1 - i][j] = numbers[i][j];
				numbers[i][COLUMNS-1 - j] = numbers[i][j];
				numbers[ROWS-1 - i][COLUMNS-1 - j] = numbers[i][j];
			}
			if (i == 2 && j != 2)
			{
				numbers[i][COLUMNS-1 - j] = numbers[i][j];
			}
			if (i != 2 && j == 2)
			{
				numbers[ROWS-1 - i][j] = numbers[i][j];
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
void Output(ULong(*numbers)[COLUMNS])
{
	ULong i;
	for (i = 0; i < ROWS; i++)
	{
		printf("%2d %2d %2d %2d %2d\n", numbers[i][0], numbers[i][1], numbers[i][2], numbers[i][3], numbers[i][4]);
	}
}