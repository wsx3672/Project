//Boxs.c
/*
���ϸ�Ī:Boxs.c
���:�����ǹ��Ը� �Է¹޾� 5kg�ڽ����� 3kg�ڽ����� ���Ҽ��ִ� �ּҹڽ����� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��17��
*/
#include <stdio.h>
#pragma warning (disable:4996)
//�ڷ�������
typedef signed long int Long;
//�Լ�����
int main(int argc, char *argv[]);
Long Input();
void Boxs(Long sugarWeight, Long *sum, Long *fiveBoxs, Long *threeBoxs);
void Output(Long sugarWeight, Long sum, Long fiveBoxs, Long threeBoxs);
//�Լ�����
int main(int argc, char *argv[])
{
	Long sugarWeight;
	Long sum;
	Long fiveBoxs;
	Long threeBoxs;
	sugarWeight = Input();
	Boxs(sugarWeight, &sum, &fiveBoxs, &threeBoxs);
	Output(sugarWeight, sum, fiveBoxs, threeBoxs);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� �����ǹ��Ը� �Է¹޴´�
�Է�:X
���:�����ǹ���
*/
Long Input()
{

	Long sugarWeight;
	scanf("%d", &sugarWeight);
	return sugarWeight;
}
/*
�Լ��̸�:Boxs
���:�ּҹڽ�����5kg�ڽ�����3kg�ڽ��������Ѵ�
�Է�;�����ǹ���
���:�ּҹڽ���,5kg�ڽ���,3kg�ڽ���
*/
void Boxs(Long sugarWeight, Long *sum, Long *fiveBoxs, Long *threeBoxs)
{
	*threeBoxs = 0;
	*fiveBoxs = sugarWeight / 5;
	sugarWeight = sugarWeight % 5;
	while (sugarWeight > 0)
	{
		if (sugarWeight<3)
		{
			*fiveBoxs = *fiveBoxs - 1;
			sugarWeight = sugarWeight + 5;
		}
		*threeBoxs = *threeBoxs + 1;
		sugarWeight -= 3;
	}
	if (*fiveBoxs < 0)
	{
		*threeBoxs = 0;
		*fiveBoxs = 0;
	}
	*sum = *fiveBoxs + *threeBoxs;
}
/*
�Լ��̸�:Output
���:�ּҹڽ���,5kg�ڽ�����3kg�ڽ����� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:�ּҹڽ�,5kg�ڽ���,3kg�ڽ���
���:X
*/
void Output(Long sugarWeight, Long sum, Long fiveBoxs, Long threeBoxs)
{
	if (sum != 0) {
		printf("�ּҹڽ���:%d\n5kg�ڽ���:%d\n3kg�ڽ���:%d", sum, fiveBoxs, threeBoxs);
	}
	else {
		printf("ERROR DATE");
	}
}		