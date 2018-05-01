//HighNumber.c
/*
���ϸ�Ī:HighNumber.c
���:���� �Է¹޾� ����ū����� ����Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��16��
*/
//��ũ�μ���
#include <stdio.h>
#pragma warning (disable:4996)
//�ڷ�������
typedef signed long int Long;
//�Լ�����
int main(int argc, char*argv[]);
Long Input();
Long HighNumber(Long number);
void Output(Long number, Long highNumber);
//�Լ�����
int main(int argc, char*argv[])
{
	Long number;
	Long highNumber;
	number = Input();
	highNumber = HighNumber(number);
	Output(number, highNumber);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� ���� �Է¹޴´�
�Է�:X
���:��
*/
Long Input()
{
	Long number;
	scanf("%d", &number);
	return number;
}
/*
�Լ��̸�:HighNumber
���:�Է¹������� ����ū����� ����Ѵ�
�Է�:��
���:����ū��
*/
Long HighNumber(Long number)

{
	Long highNumber = 0;
	Long i;
	Long temp;
	Long count = 0;
	Long exponent;
	Long j = 1;
	temp = number;
	while (temp > 0)
	{
		count++;
		temp = temp / 10;
	}
	for (i = 9; i >= 0; i--)
	{
		j = 1;
		temp = number;
		exponent = temp - temp / 10 * 10;
		while (j <= count)
		{
			if (exponent == i)
			{
				highNumber = highNumber * 10 + exponent;
			}
			temp = temp / 10;
			exponent = temp % 10;
			j++;
		}
	}
	return highNumber;
}
/*
�Լ��̸�:Output
���:����ū�����Է¹޾Ƹ���ͷ�����Ѵ�
�Է�:��,����ū��
���:X
*/
void Output(Long number, Long highNumber)

{
	printf("�Է��Ѽ�:%d\n", number);
	printf("����ū��:%d", highNumber);
}
