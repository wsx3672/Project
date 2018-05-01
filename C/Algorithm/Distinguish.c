//Distinguish.c
/*
���ϸ�Ī:Distinguish.c
���:������ �Է¹޾� ���������ǰ���,���������ǰ���,¦���ǰ���,Ȧ���ǰ����� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��19��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//�ڷ�������
typedef signed long int Long;
//�Լ�����
int main(int argc, char *argv);
void Input(Long(*numbers));
void Distinguish(Long(*numbers), Long *negativeInteger, Long *positiveInteger, Long *evenNumber, Long *oddNumber);
void Output(Long(*numbers), Long negativeInteger, Long positiveInteger, Long evenNumber, Long oddNumber);
//�Լ�����
int main(int argc, char *argv)
{
	Long numbers[MAX];
	Long negativeInteger;
	Long positiveInteger;
	Long evenNumber;
	Long oddNumber;
	Input(numbers);
	Distinguish(numbers, &negativeInteger, &positiveInteger, &evenNumber, &oddNumber);
	Output(numbers, negativeInteger, positiveInteger, evenNumber, oddNumber);

}
/*�Լ��̸�:Input
���:Ű����κ��� ������ �Է¹޴´�
�Է�:X
���;����
*/
void Input(Long(*numbers))
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers + i);
	}
}
/*
�Լ��̸�:Distinguish
���:�Է¹��������� �Ǵ��Ͽ� ���������ǰ���,���������ǰ���,¦���ǰ���,Ȧ���ǰ����� ����
�Է�:����
���:���������ǰ���,���������ǰ���,¦���ǰ���,Ȧ���ǰ���
*/
void Distinguish(Long(*numbers), Long *negativeInteger, Long *positiveInteger, Long *evenNumber, Long *oddNumber)
{
	Long i;
	Long remainder;
	*negativeInteger = 0;
	*positiveInteger = 0;
	*evenNumber = 0;
	*oddNumber = 0;
	for (i = 0; i < MAX; i++)
	{
		if (numbers[i]>0)
		{
			*positiveInteger = *positiveInteger + 1;
			remainder = numbers[i] % 2;
			if (remainder == 0)
			{
				*evenNumber = *evenNumber + 1;
			}
			else
			{
				*oddNumber = *oddNumber + 1;
			}
		}
		else
		{
			if (numbers[i] < 0)
			{
				*negativeInteger = *negativeInteger + 1;
			}
		}

	}
}
/*
�Լ��̸�:Output
���:���������ǰ���,���������ǰ���,¦���ǰ���,Ȧ���ǰ������Է¹޾� ����ͷ� ����Ѵ�
�Է�:����,���������ǰ���,���������ǰ���,¦���ǰ���,Ȧ���ǰ���
���:x
*/
void Output(Long(*numbers), Long negativeInteger, Long positiveInteger, Long evenNumber, Long oddNumber)
{
	
	printf("���������ǰ���:%d\n���������ǰ���:%d\n¦���ǰ���:%d\nȦ���ǰ���:%d", negativeInteger, positiveInteger, evenNumber, oddNumber);
}
