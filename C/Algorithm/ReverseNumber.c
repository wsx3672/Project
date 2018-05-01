//ReverseNumber.c
/*
���ϸ�Ī:ReverseNumber.c
���:�Է¹������� �����´�.
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
ULong ReverseNumber(ULong number);
void Output(ULong number, ULong reverseNumber);
//�Լ�����
int main (int argc, char*argv[])
{
	ULong number;
    ULong reverseNumber;
	number = Input();
	reverseNumber = ReverseNumber(number);
	Output(number, reverseNumber);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��ͼ����Է¹޴´�
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
�Լ��̸�:ReverseNumber
���:�Է¹������� �����´�
�Է�:��
���:��������
*/
ULong ReverseNumber(ULong number)
{
	ULong reverseNumber = 0;
	ULong remainNumber;
	ULong backNumber;
	remainNumber = number;
	while (remainNumber >= 10)
	{
		backNumber = remainNumber - remainNumber / 10 * 10;
		reverseNumber = (reverseNumber * 10) + (backNumber * 10);
		remainNumber = remainNumber / 10;
	}
	reverseNumber += remainNumber;
	return reverseNumber;
}
/*
�Լ��̸�:Output
���:���������� ����Ϳ� ����Ѵ�
�Է�:��,��������
���:X
*/
void Output(ULong number, ULong reverseNumber)
{
	printf("�Է¹�����:%d\n", number);
	printf("��������:%d", reverseNumber);
}
