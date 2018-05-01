//IsPrimeNumber.c
/*
���ϸ�Ī:IsPrimeNumber.c
���:���� �Է¹޾� �Ҽ����� �ռ������� �Ǵ��Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��05��15��
��������:2017��5��26�� 
��������:�Լ�������Լ����ǰ� �����̿��� IsPrimeNumber�Լ����� ������ isPrimeNumber�� �������� ����.
*/
//��ũ�μ���
#include <stdio.h>
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int  ULong;
typedef enum _boolean { FALSE = 0, TRUE = 1 } Boolean;
//�Լ�����
int main(int argc, char*argv[]);
ULong Input();
Boolean IsPrimeNumber(ULong number);
void Output(ULong number, Boolean isPrimeNumber);
//�Լ�����
int main(int argc, char*argv[])
{
	ULong number;
	Boolean isPrimeNumber;
	number = Input();
	isPrimeNumber = IsPrimeNumber(number);
	Output(number, isPrimeNumber);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����� ���� �Է¹޴´�
�Է�:X
���:��
*/
ULong Input()
{
	ULong number;
	scanf("%d", &number);
	return number;
}

/*�Լ��̸�:IsPrimeNumber
���:�Է¹������� �Ҽ����� �ռ������� �Ǵ��Ѵ�
�Է�:��
����:�Ҽ�����
*/

Boolean IsPrimeNumber(ULong number)

{
	Boolean isPrimeNumber;
	ULong factor = 0;
	ULong count = 0;
	ULong i = 1;
	ULong remainder;
	while (i <= number) {
		factor++;
		remainder = number - number / factor*factor;
		if (remainder == 0) {
			count++;
		}
		i++;
	}
	if (count == 2) {
		isPrimeNumber = TRUE;
	}
	else {
		isPrimeNumber = FALSE;
	}
	return isPrimeNumber;
}

/*�Լ��̸�:Output
���:�Ҽ��Ǵܿ��θ� ����ͷ� ����Ѵ�
�Է�:��,�Ҽ�����
���:X
*/
void Output(ULong number, Boolean isPrimeNumber) {
	if (isPrimeNumber == TRUE) {
		printf("%d�¼Ҽ��Դϴ�", number);
	}
	else {
		printf("%d�� �ռ����Դϴ�.", number);
	}
}