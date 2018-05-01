//PrimeNumberSum.c
/*
���ϸ�Ī:PrimeNumberSum.c
���:�Է¹��� �μ������� �Ҽ����� ���� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��18��
*/
#include <stdio.h>
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char *argv[]);
void Input(ULong *frontNumber, ULong *backNumber);
ULong PrimeNumberSum(ULong frontNumber, ULong backNumber);
void Output(ULong frontNumber, ULong backNumber, ULong sum);
//�Լ�����
int main(int argc, char *argv[])
{
	ULong frontNumber;
	ULong backNumber;
	ULong sum;
	Input(&frontNumber, &backNumber);
	sum = PrimeNumberSum(frontNumber, backNumber);
	Output(frontNumber, backNumber, sum);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� �μ��� �Է¹޴´�
�Է�:X
���:���Ǽ�,���Ǽ�
*/


void Input(ULong *frontNumber, ULong *backNumber)
{
	scanf("%d %d", frontNumber, backNumber);
}
/*
�Լ��̸�:PrimeNumberSum
���:�Է¹��� �μ������� �Ҽ����� ���� ���Ѵ�
�Է�:���Ǽ�,���Ǽ�
���:�Ҽ�������
*/
ULong PrimeNumberSum(ULong frontNumber, ULong backNumber)
{
	ULong remainder;
	ULong count;
	ULong number;
	ULong i;
	ULong factor;
	ULong sum = 0;
	number = frontNumber;
	while (number <= backNumber)
	{
		i = 1;
		count = 0;
		factor = 0;
		while (i <= number)
		{
			factor++;
			remainder = number%factor;
			if (remainder == 0)
			{
				count++;
			}
			i++;
		}
		if (count == 2)
		{
			sum = sum + number;
		}
		number++;
	}
	return sum;
}
/*
�Լ��̸�:Output
���:�Ҽ��������� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:ù��°��,�ι�°��,�Ҽ�������
���:X
*/
void Output(ULong frontNumber, ULong backNumber, ULong sum)
{
	printf("�Է��Ͻż�:%d %d\n�μ������ǼҼ�������:%d", frontNumber, backNumber, sum);
}
