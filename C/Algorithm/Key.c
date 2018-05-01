//Key.c
/*
���ϸ�Ī:Key.c
���:10���������� �Է¹ް� ã�����ϴ� ���� �Է¹޾� ����ġ�� ���Ѵ�
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
int main(int argc, char *argv[]);
void Input(Long(*numbers), Long *key);
void Key(Long(*numbers), Long key, Long *count, Long(*positions));
void Output(Long(*numbers), Long key, Long count, Long(*positions));
//�Լ�����
int main(int argc, char *argv[])
{
	Long numbers[MAX];
	Long positions[MAX];
	Long key;
	Long count;
	Input(numbers, &key);
	Key(numbers, key, &count, positions);
	Output(numbers, key, count, positions);
}
/*
�Լ��̸�:Input
���:Ű����κ��� ������ �Է¹޴´�
�Է�:X
���:����,ã�����ϴ°�
*/
void Input(Long(*numbers), Long *key)
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers + i);
	}
	printf("ã�����ϴ°�:");
	scanf("%d", key);
}
/*
�Լ��̸�:Key
���:�Է¹������߿��� ã�����ϴ°��� ã�� �� ��ġ�� ���Ѵ�
�Է�:����,ã�����ϴ°�
���:��ġ��
*/
void Key(Long(*numbers), Long key, Long *count, Long(*positions))
{
	Long i;
	Long j = 0;
	*count = 0;
	for (i = 0; i < MAX; i++)
	{
		if (numbers[i] == key)
		{
			positions[j] = i ;
			j = j + 1;
			*count = *count + 1;
		}
	}
}
/*
�Լ��̸�:Output
���:��ġ�����Է¹޾� ����ͷ� ����Ѵ�
�Է�:����,ã�����ϴ°�,��ġ��
���:X
*/
void Output(Long(*numbers), Long key, Long count, Long(*positions))
{
	Long i = 0;
	if (count != 0)
	{
		printf("��ġ��:");
		while (i < count)
		{

			printf("%d ", positions[i]+1);
			i = i + 1;
		}
	}
	else
	{
		printf("ã�����ϴ°��̾����ϴ�.");
	}
}