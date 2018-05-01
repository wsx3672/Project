//FindScore.c
/*
���ϸ�Ī:FindScore.c
���:�������� �Է¹޾� 100���� ����� ������ ���Ѵ�. �� �ΰ��� ���� ���ð�� �� ���� ������ �����Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017�� 5��23��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//�ڷ�������
typedef signed long int Long;
//�Լ�����
int main(int argc, char *argv[]);
void Input(Long(*mushrooms));
Long FindScore(Long(*mushrooms));
void Output(Long(*mushrooms), Long score);
//�Լ�����
int main(int argc, char *argv[])
{
	Long mushrooms[MAX];
	Long score;
	Input(mushrooms);
	score = FindScore(mushrooms);
	Output(mushrooms, score);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� ���������������� �Է¹޴´�
�Է�:X
���:������
*/
void Input(Long(*mushrooms))
{
	Long i;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d",mushrooms + i);
	}
}
/*
�Լ��̸�:FindScore
���:100���� ����� ������ ���Ѵ�.�� �ΰ��� ���� ���ð�� �� ���� ������ �����Ѵ�
�Է�:������
���:����
*/
Long FindScore(Long(*mushrooms))
{
	Long previous = 0;
	Long i = 0;
	Long score = 0;
	Long gap1;
	Long gap2;
	while (i<=MAX&&score<100)
	{
		score += mushrooms[i];
		if (score < 100)
		{
			previous = score;
		}
		i++;
	}
	gap1 = 100 - previous;
	gap2 = score - 100;
	if (gap1 < gap2)
	{
		score = previous;
	}
	return score;
}
/*
�Լ��̸�:Output
���:������ �Է¹޾� ����Ϳ� ����Ѵ�
�Է�:������,����
���:X
*/
void Output(Long(*mushrooms), Long score)
{
	printf("100�������尡��������� %d�Դϴ�", score);
}