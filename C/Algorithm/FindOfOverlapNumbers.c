//FindOfOverlapNumbers.c
/*
���ϸ�Ī:FindOfOverlapNumbers.c
���:������ �Է¹޾� �ߺ��ȼ��� �����ϰ� �����ִ� ������ ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��22��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//�ڷ�������
typedef signed long int Long;
//�Լ�����
int main(int argc, char *argv[]);
void Input(Long(*numbers));
void FindOfOverlapNumbers(Long(*numbers), Long(*remainingNumbers), Long *length);
void Output(Long(*numbers), Long(*reamainingNumbers), Long length);
//�Լ�����
int main(int argc, char *argv[])
{
	Long numbers[MAX];
	Long remainingNumbers[MAX];
	Long length;
	Input(numbers);
	FindOfOverlapNumbers(numbers, remainingNumbers, &length);
	Output(numbers, remainingNumbers, length);
	return 0;
}
/*
�Լ��̸�:Input
���:������ �Է¹޴´�
�Է�:X
���:����
*/
void Input(Long(*numbers))
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers + i);
	}
}
/*
�Լ��̸�:FindOfOverlapNumbers
���:�ߺ��ȼ����������ϰ� ���������� ���Ѵ�
�Է�:����
���:��������,��뷮
*/
void FindOfOverlapNumbers(Long(*numbers), Long(*remainingNumbers), Long *length)
{
	Long i;
	Long j;
	Long k = 0;
	Long count = 0;
	*length = 0;
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			if (i != j)
				if (numbers[i] == numbers[j])
				{
					count++;
				}
		}

		if (count == 0)
		{
			remainingNumbers[k] = numbers[i];
			k++;
			(*length)++;
		}
		j = 1;
		count = 0;
	}
}
/*
�Լ��̸�:Output
���:�����ִ¼����� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:����,�����ִ¼���,��뷮
���:X
*/
void Output(Long(*numbers), Long(*remainingNumbers), Long length)
{
	Long i = 0;
	while (i<length)
	{
		printf("%d ", remainingNumbers[i]);
		i++;
		
	}
}