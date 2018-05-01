//Sum.c
/*���ϸ�Ī:Sum.c
���:���� �Է¹޾� ���ڸ��������� ���Ѵ�
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
ULong Sum(ULong number);
void Output(ULong number, ULong sum);
//�Լ�����
int main(int argc, char *argv[])
{
	ULong number;
	ULong sum;
	number = Input();
	sum = Sum(number);
	Output(number, sum);
	return 0;
}
/*
�Լ��̸�: Input
���:Ű����κ��� ���� �Է¹޴´�
�Է�:X
���:��
*/
ULong Input() {
	ULong number;
		scanf("%d", &number);
		return number;
}
/*
�Լ��̸�:Sum
���:�Է¹������� ���ڸ������������Ѵ�
�Է�:��
���:���ڸ�������
*/
ULong Sum(number) 
{
	ULong sum = 0;
	ULong remainder;
	ULong quotient;
		ULong i;
		i = number;
		while (i>=10){
			quotient = 1 / 10;
			remainder = i - quotient * 10;
			sum += remainder;
			i = i / 10;
		}
		sum += i;
		return sum;
}
/*
�Լ��̸�:Output
���:���ڸ��������� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:��,���ڸ�������
���:X
*/
void Output(number, sum) {
	printf("�Է��Ͻ� %d�� ���ڸ��������� %d�Դϴ�.", number, sum);
}