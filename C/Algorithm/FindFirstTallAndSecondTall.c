//FindFirstTallAndSecondTall.c
/*
���ϸ�Ī:FindFirstTallAndSecondTall.c
���:Ű���� �Է¹޾� ����ūŰ�� �ι�°ūŰ�� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017�� 5�� 23��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char *argv[]);
void Input(ULong(*numbers));
void FindFirstTallAndSecondTall(ULong(*numbers), ULong *firstTall, ULong *secondTall);
void Output(ULong(*numbers), ULong firstTall, ULong secondTall);
//�Լ�����
int main(int argc, char *argv[])
{
	ULong numbers[MAX];
	ULong firstTall;
	ULong secondTall;
	Input(numbers);
	FindFirstTallAndSecondTall(numbers, &firstTall, &secondTall);
	Output(numbers, firstTall, secondTall);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� Ű���� �Է¹޴´�
�Է�:X
���:Ű��
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
�Լ��̸�:FindFirstTallAndSecondTall
���:����ūŰ�͵ι�°ūŰ�����Ѵ�
�Է�:Ű��
���:����ūŰ,�ι�°ūŰ
*/
void FindFirstTallAndSecondTall(ULong(*numbers), ULong *firstTall, ULong *secondTall)
{
	ULong temp;
	ULong i = 0;
	ULong j;
	ULong k;
	k = MAX;
	while (k>0)
	{
		j = i + 1;
			while (j < k)
			{
				if (numbers[i] > numbers[j])
				{
					temp = numbers[i];
					numbers[i] = numbers[j];
					numbers[j] = temp;
				}
				i++;
				j++;
			}
			i = 1;
			k--;
	}
	*firstTall = numbers[MAX - 1];
	*secondTall = numbers[MAX - 2];
}
/*
�Լ��̸�:Output
���:����ūŰ�͵ι�°ūŰ�� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:����,����ūŰ.�ι�°ūŰ
���:X
*/
void Output(ULong(*numbers), ULong firstTall, ULong secondTall)
{
	printf("����ūŰ:%d\n�ι�°ūŰ:%d", firstTall, secondTall);
}