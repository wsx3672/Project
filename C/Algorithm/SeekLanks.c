//SeekLank.c
/*
���ϸ�Ī:SeekLank.c
���:��ȣ���������� �Է¹޾� �������� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��23��
*/
//��ũ�μ���
#include <stdio.h>
#define MAX 10
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char *argv[]);
void Input(ULong(*numbers), ULong(*totalScores));
void SeekLank(ULong(*totalScores), ULong(*ranks));
void Output(ULong(*totalScores), ULong(*numbers), ULong(*ranks));
//�Լ�����
int main(int argc, char *argv[])
{
	ULong numbers[MAX];
	ULong totalScores[MAX];
	ULong ranks[MAX];
	Input(numbers, totalScores);
	SeekLank(totalScores, ranks);
	Output(totalScores, numbers, ranks);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� ��ȣ���������� �Է¹޴´�
�Է�:x
���:������,��ȣ
*/
void Input(ULong(*numbers), ULong(*totalScores))
{

	ULong i;
	printf("�������� �Է��ϼ���\n");
	for (i = 0; i < MAX; i++)

	{
		numbers[i] = i + 1;
		scanf("%d",totalScores + i);
	}
}
/*
�Լ��̸�:SeekLanks
���:�������� ���Ѵ�
�Է�:������
���:������
*/
void SeekLank(ULong(*totalScores), ULong(*ranks))
{
	ULong i;
	ULong j = 0;
	ULong k;
	for (i = 0; i < MAX; i++)
	{
		ranks[i] = 1;
	}
	while (j <= MAX - 1)
	{
		k = j + 1;

		while (k < MAX)
		{
			if (totalScores[j] != totalScores[k])
			{
				if (totalScores[j] < totalScores[k])
				{
					ranks[j] = ranks[j] + 1;
				}
				else
				{
					ranks[k] = ranks[k] + 1;
				}
			}
			k++;
		}
		j++;
	}
}
/*
�Լ��̸�:Output
���:��ȣ,������,�������� �Է¹޾� ����ͷ�����Ѵ�
�Է�:��ȣ,������,������
���;X
*/
void Output(ULong(*totalScores), ULong(*numbers), ULong(*ranks))
{
	ULong i;
	printf("��ȣ ���� ����\n");
	for (i = 0; i < MAX; i++)
	{
		printf("%d %d %d\n", numbers[i], totalScores[i], ranks[i]);
	}
}