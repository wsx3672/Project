//BackWards.c
/*
���ϸ�Ī:BackWards.c
���:�Էµȼ����� �Ųٷ� �����Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��19��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 1000
#pragma warning (disable:4996)
//�ڷ�������
typedef signed long int Long;
//�Լ�����
int main(int argc, char *argv[]);
void Input(Long *count, Long(*numbers));
void BackWards(Long count, Long(*numbers));
void Output(Long count, Long(*numbers));
//�Լ�����
int main(int argc, char *argv[])
{
	Long count;
	Long numbers[MAX];
	Input(&count, numbers);
	BackWards(count, numbers);
	Output(count, numbers);
}
/*
�Լ��̸�:Input
���:Ű����κ��� ������ �Է¹޴´�
�Է�:X
���:���ǰ���,����
*/
void Input(Long *count, Long(*numbers))
{
	Long i = 0;
	printf("���ǰ����� �Է��Ͻÿ�");
	scanf("%d", count);
	while (i < *count)
	{
		scanf("%d", numbers + i);
		i = i + 1;
	}
}
/*
�Լ��̸�:BackWards
���:�Էµȼ����� �Ųٷ� �����Ѵ�
�Է�:���ǰ���,����
���:����(���ĵ�)
*/
void BackWards(Long count, Long(*numbers))
{
	Long i = 0;
	Long j;
	Long temp;
	j = count - 1;
	while (i <= count / 2)
	{
		temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
		j--;
		i++;
	}
}
/*
�Լ��̸�:Output
���:���ĵȼ����� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:���ǰ���,����
���:X
*/
void Output(Long count, Long(*numbers))
{
	Long i = 0;
	while (i < count)
	{
		printf("%d ", numbers[i]);
		i = i + 1;
	}
}