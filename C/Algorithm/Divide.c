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
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char*argv[]);
ULong Input();
ULong HighNumber(ULong number);
void Output(ULong number, ULong highNumber);
//�Լ�����
int main(int argc, char*argv[])
{
	ULong number;
	ULong highNumber;
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
ULong Input()
{
	ULong number;
	scanf("%d", &number);
	return number;
}
/*
�Լ��̸�:HighNumber
���:�Է¹������� ����ū����� ����Ѵ�
�Է�:��
���:����ū��
*/
ULong HighNumber(ULong number)

{
	ULong highNumber = 0;
	ULong i;
	ULong temp;
	ULong count = 0;
	ULong exponent;
	ULong j = 1;
	temp = number;
	while (temp > 0)
	{
		count++;
		temp = temp / 10;
	}
	for (i = 9; i > 0; i--)
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
void Output(ULong number, ULong highNumber)

{
	printf("�Է��Ѽ�:%d\n", number);
	printf("����ū��:%d", highNumber);
}
