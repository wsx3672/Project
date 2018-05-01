//Arrange.c
/*
���ϸ�Ī:Arrange.c
���:������ �Է¹޾� ū����� �����Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��19��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 3
#pragma warning (disable:4996)
//�ڷ�������
typedef signed long int Long;
//�Լ�����
int main(int argc, char *argv[]);
void Input(Long(*numbers));
void Arrange(Long(*numbers));
void Output(Long(*numbers));
//�Լ�����
int main(int argc, char *argv[])
{
	Long numbers[MAX];
	Input(numbers);
	Arrange(numbers);
	Output(numbers);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� ������ �Է¹޴´�
�Է�:X
���:����
*/
void Input(Long(*numbers))
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", numbers+i);

	}

}
/*
�Լ��̸�:Arrange
���:�Էµȼ����� ū����� �����Ѵ�
�Է�:����
���:����(���ĵ�)
*/
void Arrange(Long(*numbers))
{
	Long i;
	Long j;
	Long temp;
	for (i = 0; i < MAX - 1; i++)
	{
		for (j = i + 1; j < MAX; j++)
		{
			if (numbers[i] < numbers[j])
			{
				temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
			}
		}
	}
}
/*
�Լ��̸�:Output
���:���ĵ� ������ �Է¹޾� ����ͷ� ����Ѵ�
�Է�:����(���ĵ�)
���:X
*/
void Output(Long(*numbers))
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		printf("%d\n", numbers[i]);
	}
}