//Combination.c
/*
�����̸�:Combination.c
���:�ֻ��������� �Է¹޾� ����Ǽ��� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��22��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 6
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned short int UShort;
//�Լ����� 
int main(int argc, char *argv[]);
UShort Input();
void Combination(UShort sum, UShort(*firstNumbers), UShort(*secondNumbers), UShort *numberOfCase);
void Output(UShort sum, UShort(*firstNumbers), UShort(*secondNumbers), UShort numberOfCase);
//�Լ�����
int main(int argc, char *argv[])
{
	UShort sum;
	UShort firstNumbers[MAX];
	UShort secondNumbers[MAX];
	UShort numberOfCase;
	sum = Input();
	Combination(sum, firstNumbers, secondNumbers, &numberOfCase);
	Output(sum, firstNumbers, secondNumbers, numberOfCase);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� �ֻ��������� �Է¹޴´�
�Է�:X
���:�ֻ�������
*/
UShort Input()
{
	UShort sum;
	scanf("%hu", &sum);
	return sum;
}
/*
�Լ��̸�:Combination
���:�ֻ����������� ���Ѵ�
�Է�:�ֻ�������
���:ù��°�ֻ�������,�ι�°�ֻ�������,����Ǽ�
*/
void Combination(UShort sum, UShort(*firstNumbers), UShort(*secondNumbers), UShort *numberOfCase)
{
	UShort temp;
	UShort dice1;
	UShort dice2;
	UShort i = 0;
	*numberOfCase = 0;
	for (dice2 = 1; dice2 <= MAX; dice2++)
	{
		for (dice1 = 1; dice1 <= MAX; dice1++)
		{
			temp = dice1 + dice2;
			if (sum == temp)
			{
				firstNumbers[i] = dice1;
				secondNumbers[i] = dice2;
				(*numberOfCase)++;
				i++;
			}
		}
		dice1 = 1;

	}
}
/*
�Լ��̸�:Output
���:ù��°�ֻ���������ι�°�ֻ��������� �Է¹޾� ����Ϳ� ����Ѵ�
�Է�:�ֻ�������,ù��°�ֻ�������,�ι�°�ֻ�������,����Ǽ�
���:X
*/
void Output(UShort sum, UShort(*firstNumbers), UShort(*secondNumbers), UShort numberOfCase)
{
	UShort i = 0;
	if (numberOfCase != 0)
	{
		while (i < numberOfCase)
		{
			printf("ù��°�ֻ�����:%d �ι�°�ֻ�����:%d\n", firstNumbers[i], secondNumbers[i]);
			i++;
		}
	}
	else
	{
		printf("2�̻� 12�����Ǽ��� �Է����ּ���");
	}
}
