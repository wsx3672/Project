//DogsAndChicks.c
/*
���ϸ�Ī:DogsAndChicks.c
���:�������ͺ��Ƹ����հ��ٸ��Ǽ����Է¹޾� �������� ���Ƹ��� ���� ������� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��17��
*/
//��ũ�μ���
#include <stdio.h>
#pragma warning (disable:4996)
//�ڷ�������
typedef signed long int ULong;
//�Լ�����
int main(int argc, char *argv[]);
void Input(ULong *sum, ULong *legs);
void DogsAndChicks(ULong sum, ULong legs, ULong *dogs, ULong *chicks);
void Output(ULong sum, ULong legs, ULong dogs, ULong chicks);
//�Լ�����
int main(int argc, char *argv[])
{
	ULong sum;
	ULong legs;
	ULong dogs;
	ULong chicks;
	Input(&sum, &legs);
	DogsAndChicks(sum, legs, &dogs, &chicks);
	Output(sum, legs, dogs, chicks);
	return 0;
}
/*
�Լ��̸�;Input
���:Ű����κ��� �������ͺ��Ƹ����հ� �ٸ����� �Է¹޴´�
�Է�:X
���:�������ͺ��Ƹ�����,�ٸ��Ǽ�
*/
void Input(ULong *sum, ULong *legs)
{
	scanf("%d%d", sum, legs);
}
/*
�Լ��̸�:DogsAndChicks
���:�������ͺ��Ƹ��� ������� ���Ѵ�
�Է�:�������ͺ��Ƹ�����,�ٸ��Ǽ�
���:�������Ǽ�,���Ƹ��Ǽ�
*/
void DogsAndChicks(ULong sum, ULong legs, ULong *dogs, ULong *chicks)
{

	ULong count;

	*dogs = 0;
	*chicks = sum;
	count = *chicks * 2;
	while (count != legs && chicks >= 0)
	{
		*dogs = *dogs + 1;
		*chicks = *chicks - 1;
		count = 2 * *chicks + 4 * *dogs;
	}
	if (chicks < 0)
	{
		*dogs = 0;
		*chicks = 0;
	}
}
/*
�Լ��̸�:Output
���:�������Ǽ��ͺ��Ƹ��Ǽ��� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:�������ͺ��Ƹ�����,�ٸ��Ǽ�,�������Ǽ�,���Ƹ��Ǽ�
���:X
*/
void Output(ULong sum, ULong legs, ULong dogs, ULong chicks)
{
	printf("�Է��Ͻ� �������� ���Ƹ�����:%d\n�Է��ϽŴٸ��Ǽ�:%d\n�������Ǽ�:%d\n���Ƹ��Ǽ�:%d", sum, legs, dogs, chicks);
}

