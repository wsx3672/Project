/*
���ϸ�Ī:Days.c
���:�����̰� �칰 ������ �����µ� �ɸ��� ���ڸ� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��15��
��������:2017��5��26��
��������:�Լ�������Լ����ǰ� �߸��Ǿ��ְ� Days�Լ����� ���Ϲ����� �߸��Ǿ��־���.
*/
//��ũ�μ���
#include <stdio.h>
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char* argv[]);
ULong Input();
ULong Days(ULong depth);
void Output(ULong depth, ULong days);
//�Լ�����
int main(int argc, char *argv[])
{
	ULong depth;
	ULong days;
	depth = Input();
	days = Days(depth);
	Output(depth,days);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� ���� �Է¹޴´�
�Է�:X
���:����
*/
ULong Input()
{
	ULong depth;
	scanf("%d", &depth);
	return depth;
}
/*
�Լ��̸�:days.c
���:�����̰� �칰������ �����µ� �ɸ��� ���ڸ� ���Ѵ�
�Է�:����
���:����
*/
ULong Days(ULong depth)
{
	ULong days = 1;
	ULong snail = 3;
	while (snail < depth) {
		snail -= 2;
		days++;
		snail += 3;
	}
	return days;
}
/*
�Լ��̸�:Output
���:�ɸ������ڸ� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:����,����
���:X
*/
void Output(ULong depth, ULong days) 
{
	printf("�����̰� �칰�� ������ %d�� ���������µ� �ɸ��� ���ڴ� %d�Դϴ�.\n ", depth, days);
}




