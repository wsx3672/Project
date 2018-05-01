//OddSumAndMinimumOdd.c
/*
�����̸�:OddSumAndMinimumOdd.c
���:������ �Է¹޾� Ȧ�������հ� ��������Ȧ���� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��22��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 7
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char *argv[]);
void Input(ULong(*numbers));
void OddSumAndMinimumOdd(ULong(*numbers), ULong *sum, ULong *minumumOdd);
void Output(ULong(*numbers), ULong sum, ULong minimumOdd);
//�Լ�����
int main(int argc, char *argv[])
{
	ULong numbers[MAX];
	ULong sum;
	ULong minimunOdd;
	Input(numbers);
	OddSumAndMinimumOdd(numbers, &sum, &minimunOdd);
	Output(numbers, sum, minimunOdd);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� ������ �Է¹޴´�
�Է�:X
���:����
*/
void Input(ULong(*numbers))
{
	ULong i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers + i);
	}
}
/*
�Լ��̸�:OddSumAndMinimumOdd
���:Ȧ�������հ� �������� Ȧ���� ���Ѵ�
�Է�:����
���:Ȧ��������,��������Ȧ��
*/
void OddSumAndMinimumOdd(ULong(*numbers), ULong *sum, ULong *minumumOdd)
{
	ULong i;
	ULong remainder;
	*sum = 0;
	* minumumOdd = 0;
	for (i =0; i < MAX; i++)
	{
		remainder = numbers[i] % 2;
		if (remainder > 0)
		{
			*sum += numbers[i];
			if (numbers[i] < *minumumOdd || *minumumOdd == 0)
			{
				*minumumOdd = numbers[i];
			}
		}

	}
}
/*
�Լ��̸�:Output
���:Ȧ�������հ���������Ȧ���� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:����,Ȧ��������,��������Ȧ��
���:X
*/
void Output(ULong(*numbers), ULong sum, ULong minimumOdd)
{
	if (sum != 0)
	{
		printf("Ȧ��������:%d\n��������Ȧ��:%d", sum, minimumOdd);
	}
	else
	{
		printf("-1");
	}
}