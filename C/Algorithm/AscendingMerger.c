//AscendingMerger.c
/*
���ϸ�Ī:AscendingMerger.c
���:ù��°���鰡�ι�°������ �Է¹޾� ������������ �����Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��24��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char *argv[]);
void Input(ULong(*firstNumbers), ULong(*secondNumbers));
void AscendingMerger(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergerNumbers));
void Output(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergerNumbers));
//�Լ�����
int main(int argc, char *argv[])
{
	ULong firstNumbers[MAX];
	ULong secondNumbers[MAX];
	ULong mergerNumbers[MAX * 2];
	Input(firstNumbers, secondNumbers);
	AscendingMerger(firstNumbers, secondNumbers, mergerNumbers);
	Output(firstNumbers, secondNumbers, mergerNumbers);
	return 0;
}
/*
�Լ��̸�:Input
���:ù��°������ι�°������ �Է¹޴´�
�Է�:X
���:ù��°����,�ι�°����
*/
void Input(ULong(*firstNumbers), ULong(*secondNumbers))
{
	ULong i;
	printf("ù��°������ �Է��ϼ���");
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", firstNumbers + i);
	}
	printf("�ι�°������ �Է��ϼ���");
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", secondNumbers + i);
	}
}
/*
�Լ��̸�:AscendingMerger
���:ù��°������ι�°������ ������������ �����Ѵ�
�Է�:ù��°����,�ι�°����
���:���յȼ���
*/
void AscendingMerger(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergerNumbers))
{
	ULong i = 0;
	ULong j = 0;
	ULong k = 0;
	while (i < MAX&&j < MAX)
	{
		if (firstNumbers[i] < secondNumbers[j])
		{
			mergerNumbers[k] = firstNumbers[i];
			k++;
			i++;
		}
		else
		{
			mergerNumbers[k] = secondNumbers[j];
			k++;
			j++;
		}
	}
	while (j < MAX)
	{
		mergerNumbers[k] = secondNumbers[j];
		k++;
		j++;
	}
	while (i < MAX)
	{
		mergerNumbers[k] = firstNumbers[i];
		k++;
		i++;
	}

}
/*
�Լ��̸�:Output 
���:���յȼ����� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:ù��°����,�ι�°����,���յȼ���
���:X
*/
void Output(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergerNumbers))
{
	ULong i;
	for (i = 0; i < MAX*2; i++)
	{
		printf("%d ", mergerNumbers[i]);
	}
}