//FindOfNumbers.c
/*
���ϸ�Ī:FindOfNumbers.c
���:������ ������ �Է¹޾� �ڸ����ͼ��ڵ��ϰ����ͼ��ڵ��ϰ����� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��20��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 4
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned char Char;
//�Լ�����
int main(int argc, char *argv[]);
void Input(Char(*answers), Char(*numbers));
void FindOfNumbers(Char(*answers), Char(*numbers), Char *hit, Char *blow);
void Output(Char(*answers), Char(*numbers), Char hit, Char blow);
//�Լ�����
int main(int argc, char *argv[])
{
	Char answers[MAX];
	Char numbers[MAX];
	Char hit;
	Char blow;
	Input(answers, numbers);
	FindOfNumbers(answers, numbers, &hit, &blow);
	Output(answers, numbers, hit, blow);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� ������ ������ �Է¹޴´�
�Է�:X
���:�����,����
*/
void Input(Char(*answers), Char(*numbers))
{
	Char i;
	printf("������� �Է��Ͻÿ�\n");
		for (i = 0; i < MAX; i++)
		{
			scanf("%d", answers + i);
		}
		for (i = 0; i < MAX; i++)
		{
			scanf("%d", numbers + i);

		}
}
/*
�Լ��̸�:FindOfNumbers
���:�ڸ����ͼ��ڵ��ϰ����� ���ڵ��ϰ����� ���Ѵ�
�Է�:�����,����
���:�ڸ����ͼ��ڵ��ϰ���,���ڵ��ϰ���
*/
void FindOfNumbers(Char(*answers), Char(*numbers), Char *hit, Char *blow)
{
	Char i;
	Char j;
	*hit = 0;
	*blow = 0;
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			if (answers[i] == numbers[j]) 
				if (j == i)
				{
					*hit = *hit + 1;
					
				}
				else
				{
					*blow = *blow + 1;
				}
			 
			
		}
		
	}
	
}
/*
�Լ��̸�:Output
���:�ڸ����ͼ��ڵ��ϰ����� ���ڵ��ϰ������Է¹޾� ����Ϳ� ����Ѵ�
�Է�:�����,����,�ڸ����ͼ��ڵ��ϰ���,���ڵ��ϰ���
���:X
*/
void Output(Char(*answers), Char(*numbers), Char hit, Char blow)
{
	if (hit != 0)
	{
		printf("hit:%d   blow:%d", hit, blow);
	}
	else
	{
		printf("blow:%d", blow);
	}
}
