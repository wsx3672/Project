//Count.c
/*
���ϸ�Ī:Count.c
���:1����10000�����Ǽ��� 7�ǰ����� ����
�ۼ���:�ڻ��
�ۼ�����:2017��5��15��
*/
//��ũ�μ���
#include <stdio.h>
#pragma warning (disable:4996 )
//�Լ�����
int main(int argc, char*argv[]);
int Count();
void Output(int count);
//�Լ�����
int main(int argc, char*argv[])
{
	int count;
	count = Count();
	Output(count);
	return 0;
}
/*
�Լ��̸�:count
���:1���� 10000�����Ǽ��� 7�ǰ����� ����
�Է�:X
���:7�ǰ���
*/
int count()
{
	int startNumber;
	int count = 0;
	int quotient ;
	int remainder;
	int i;
	for (startNumber = 1; startNumber <= 10000; startNumber++)
	{
		i = startNumber;
		while (i >= 10)
		{
			remainder = i % 10;
			if (remainder == 7) {
				count++;
			}
			i = i / 10;
		}
		if (i == 7) {
			count++;
		}
	}
	return count;
}
/*
�Լ��̸�:Output
���:7�ǰ����� ����ͷ�����Ѵ�
�Է�:7�ǰ���
���:X
*/
void Output(count)
{
	printf("1���� 10000������ ���� 7�ǰ����� %d�Դϴ�.", count);
}