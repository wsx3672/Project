//Change.c
/*
�����̸�:Change.c
���:�Ž��������� ����� �����ǰ����� ����
�ۼ���:�ڻ��
�ۼ�����:2017��5��17��
*/
#include <stdio.h>
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned short Short;
//�Լ�����
int main(int argc, char *argv[]);
Short Input();
void Charge(Short price, Short *fiveHundred, Short *hundred, Short *fifty, Short *ten);
void Output(Short price, Short fiveHundred, Short hundred, Short fifty, Short ten);
//�Լ�����
int main(int argc, char *argv[])
{
	Short price;
	Short fiveHunderd;
	Short hundred;
	Short fifty;
	Short ten;
	price = Input();
	Charge (price,&fiveHunderd, &hundred, &fifty, &ten);
	Output (price,fiveHunderd, hundred, fifty, ten);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� ���� �Է¹޴´�
�Է�:X
���:���ǰ�
*/
Short Input()
{
	Short price;
	scanf("%hd", &price);
	return price;
}
/*
�Լ��̸�:Change
���:�Ž��������� ����� ������ ������ ���Ѵ�
�Է�:���ǰ�
���:500��,100��,50��,10��
*/
void Charge(Short price, Short *fiveHundred, Short *hundred, Short *fifty, Short *ten)
{
	Short change;
	change = 1000 - price;
	*fiveHundred = change / 500;
	change = change - *fiveHundred * 500;
	*hundred = change / 100;
	change = change - *hundred * 100;
	*fifty = change / 100;
	change = change - *fifty * 50;
	*ten = change / 10;
	change = change - *ten * 10;
}
/*
�Լ��̸�:Output
���:500��,100��,50��,10���� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:���ǰ�,500��,100��,50��,10��
���:X
*/
void Output(Short price, Short fiveHundred, Short hundred, Short fifty, Short ten)
{
	printf("���ǰ�:%d\n500��:%d\n100��:%d\n50��:%d\n10��:%d", price, fiveHundred, hundred, fifty, ten);
}
