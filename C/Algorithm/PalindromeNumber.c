//PalindromeNumber.c
/*
���ϸ�Ī:PalindromeNumber.c
���:���� �Է¹޾� ȸ������ �����
�ۼ���:�ڻ��
�ۼ�����:2017��5��15��
*/
//��ũ�μ���
#include <stdio.h>
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char*argv[]);
ULong Input();
ULong PalindromeNumber(ULong Number);
void Output(ULong number, ULong palindromeNumber);
//�Լ�����
int main(int argc, char*argv[])
{
	ULong number;
	ULong palindromeNumber;
	number = Input();
	palindromeNumber = PalindromeNumber(number);
	Output(number, palindromeNumber);
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
�Լ��̸�:PalindromeNumber
���:�Է¹������� ȸ������ �����
�Է�:��
���:ȸ����
*/
ULong PalindromeNumber(ULong number)
{
	ULong palindromeNumber;
	ULong reverseNumber = 0;
	ULong quotient;
	ULong remainder;
	palindromeNumber = number;
	while (palindromeNumber != reverseNumber)
	{
		palindromeNumber += reverseNumber;
		quotient = palindromeNumber;
		reverseNumber = 0;
		while (quotient > 0)
		{
			remainder = quotient % 10;
			reverseNumber = reverseNumber * 10 + remainder;
			quotient = quotient / 10;
		}
	}
	return palindromeNumber;
}
/*
�Լ��̸�:Output
���:ȸ������ ����ͷ� ����Ѵ�.
�Է�:��,ȸ����
���:X
*/
void Output(ULong number, ULong palindromeNumber)
{
	printf("�Է��Ѽ�:%d\n", number);
	printf("ȸ����:%d", palindromeNumber);
}

