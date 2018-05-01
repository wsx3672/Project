//FindOfThreeAndMultipleThree.c
/*
���ϸ�Ī:FindOfThreeAndMultipleThree.c
���:1���� �Է¹��� ������ 3�ǹ����3�ǿ��θ����� clap���� �����Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��22��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 1000
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char *argv[]);
ULong Input();
void FindOfThreeAndMultipleThree (ULong number, ULong (*numbers));
void Output(ULong number, ULong (*numbers));
//�Լ�����
int main(int argc, char *argv[])
{
	ULong number;
	ULong numbers[MAX];
	number = Input();
	FindOfThreeAndMultipleThree(number, numbers);
	Output(number, numbers);
	return 0;
}
/*
�Լ��̸�:Input 
���:Ű����κ��� ���� �Է¹޴´�
�Է�:X
���:��
*/
ULong Input()
{
	ULong number;
	scanf("%d", &number);
	return number;
}
/*
�Լ��̸�:FindOfThreeAndMultipleThree
���:1���� �Է¹��������� 3�ǹ����3�ǿ��θ� ���Ѵ�
�Է�:��
���:����
*/
void FindOfThreeAndMultipleThree(ULong number, ULong(*numbers))
{
	ULong count;
	ULong quotient;
	ULong remainder;
	ULong i = 0;
	while (i < number)
	{
		count = 0;
		numbers[i] = i + 1;
		remainder = numbers[i] % 3;
		if (remainder == 0)
		{
			count++;
		}
		else
		{
			quotient = numbers[i];
			while (quotient > 0 && count == 0)
			{
				remainder = quotient % 10;
				if (remainder == 3)
				{
					count++;
				}
				quotient = quotient / 10;
			}
		}
		if (count > 0)
		{
			numbers[i] = 0;
		}
		i++;
	}
}
/*
�Լ��̸�:Output
���:������ �Է¹޾� �迭�� ��Ұ� 0�ΰ�� clap ���� �ٲپ��ش�
�Է�:��,����
���:X
*/
void Output(ULong number, ULong(*numbers))
{
	ULong i = 0;
	while (i < number)
	{
		if (numbers[i] == 0)
		{
			printf("clap ");
		}
		else
		{
			printf("%d ", numbers[i]);
		}
		i++;
	}
}