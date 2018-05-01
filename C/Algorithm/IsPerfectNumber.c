//IsPerfectNumber.c
/*���ϸ�Ī:IsperfectNumber.c
���:���� �Է¹޾� ���������� Ȯ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��16��*/
//��ũ�μ���
#include <stdio.h>
//�ڷ�������
typedef unsigned long int ULong;
typedef enum _boolean { FALSE = 0, TRUE = 1 }Boolean;
//�Լ�����
int main(int argc, char*argv[]);
ULong Input();
Boolean IsPerfectNumber(ULong number);
void Output(ULong number, Boolean isPerfectNumber);
//�Լ�����
int main(int argc, char*argv[])
{
	ULong number;
	Boolean isPerfectNumber;
	number = Input();
	isPerfectNumber = IsPerfectNumber(number);
	Output(number, isPerfectNumber);
	return 0;
}
/*�Լ��̸�:Input
���:Ű����κ��ͼ��� �Է¹޴´�
�Է�:X
���:��
*/
ULong Input() {
	ULong number;
	scanf("%d", &number);
	return number;
}
/*�Լ��̸�:IsPerfectNumber
���:�Է¹������� ���������� Ȯ���Ѵ�
�Է�:��
���:����������
*/
Boolean IsPerfectNumber(ULong number) {
	Boolean isPerfectNumber;
	ULong sum = 0;
	ULong remainder;
	ULong factor=0;
	ULong i = 1;
	while (i <= number / 2) {
		factor++;
		remainder = number%factor;
		if (remainder == 0) {
			sum += factor;
		}
		i++;
	}
	if (sum == number) {
		isPerfectNumber = TRUE;
	}
	else {
		isPerfectNumber = FALSE;
	}
	return isPerfectNumber;
}
/*�Լ��̸�:Output
���:���������θ� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:��,����������
���:X
*/
void Output(ULong number, Boolean isPerfectNumber) {
	if (isPerfectNumber == TRUE) {
		printf("%d�¿������Դϴ�.", number);
	}
	else {
		printf("%d�� ���������ƴմϴ�.", number);
	}
}
