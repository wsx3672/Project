//AscendingNumbers.c
/*
���ϸ�Ī:AscendingNumbers.c
���:������ �Է¹޾� �������ķ� ���������� �����
�ۼ���:�ڻ��
�ۼ�����:2017��5��23��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//�ڷ�������
typedef signed long int ULong;
//�Լ�����
int main(int argc, char *argv[]);
void Input(ULong(*numbers));
void AscendingNumbers(ULong(*numbers), ULong(*ascendingNumbers));
void Output(ULong(*numbers), ULong(*ascendingNumbers));
//�Լ�����
int main(int argc, char *argv[])
{
	ULong numbers[MAX];
	ULong ascendingNumbers[MAX];
	Input(numbers);
	AscendingNumbers(numbers, ascendingNumbers);
	Output(numbers, ascendingNumbers);
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
�Լ��̸�:AscendingNumbers
���:�Էµȼ����� �����������̿��� ������������ �����
�Է�:����
���:���ĵȼ���
*/
void AscendingNumbers(ULong(*numbers), ULong(*ascendingNumbers))
{
	ULong i;
	ULong j;
	ULong temp;
	for (i = 0; i < MAX; i++)
	{
		ascendingNumbers[i] = numbers[i];
	}
	for (j = 1; j < MAX; j++)
	{
		i = j - 1;
		temp = ascendingNumbers[j];
		while (i>=0&&temp<ascendingNumbers[i])
		{
			ascendingNumbers[i + 1] = ascendingNumbers[i];
			i--;
		}
		ascendingNumbers[i + 1] = temp;
	}
}
/*
�Լ��̸�:Output
���:���ĵȼ����� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:����,���ĵȼ���
���:X
*/
void Output(ULong(*numbers), ULong(*ascendingNumbers))
{
	ULong i;
	printf("�Է��Ѽ�:");
	for (i = 0; i < MAX; i++)
	{
		printf("%d ",numbers[i]);
	}
	printf("���ĵȼ�:");
	for (i = 0; i < MAX; i++)
		
		printf("%d ", ascendingNumbers[i]);
}