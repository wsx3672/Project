//TilesCount.c
/*
���ϸ�Ī:TilesCount.c
���:���οͼ�����ũ�⸦ �Է¹޾� ������Ÿ���Ǽ��� �߶󼭻���� Ÿ���Ǽ��� ���Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��5��17��
*/
#include <stdio.h>
#pragma warning (disable:4996)
//�ڷ�������
typedef unsigned long int ULong;
//�Լ�����
int main(int argc, char *argv[]);
void Input(ULong *widthSize, ULong *lengthSize);
void TilesCount(ULong widthSize, ULong lengthSize, ULong *wholeTiles, ULong *partTiles);
void Output(ULong widthSize, ULong lengthSize, ULong wholeTiles, ULong partTiles);
//�Լ�����
int main(int argc, char *argv[])
{
	ULong widthSize;
	ULong lengthSize;
	ULong wholeTiles;
	ULong partTiles;
	Input(&widthSize, &lengthSize);
	TilesCount(widthSize, lengthSize, &wholeTiles, &partTiles);
	Output(widthSize, lengthSize, wholeTiles, partTiles);
	return 0;
}
/*
�Լ�����:Input
���:Ű����κ��� ������ũ��ͼ�����ũ�⸦ �Է¹޴´�
�Է�:X
���:������ũ��,������ũ��
*/
void Input(ULong *widthSize, ULong *lengthSize)
{
	printf("������ũ�� ������ũ��\n");
	scanf("%d %d", widthSize, lengthSize);
}
/*
�Լ��̸�:TilesCount
���:����ũ�⿡ �°� ���Ǿ���� ������Ÿ���Ǽ����߶󼭻����Ÿ���Ǽ��� ���Ѵ�
�Է�:������ũ��,������ũ��
���:������Ÿ�ϼ�,�߶󼭻����Ÿ�ϼ�
*/
void TilesCount(ULong widthSize, ULong lengthSize, ULong *wholeTiles, ULong *partTiles)
{
	ULong widthTiles;
	ULong lengthTiles;
	ULong i;
	ULong j;
	widthTiles =  widthSize / 8;
	i = widthSize - widthTiles * 8;
	if (i != 0)
	{
		i = 1;
	}
	lengthTiles = lengthSize / 8;
	j = lengthSize - lengthTiles * 8;
	if (j != 0)
	{
		j = 1;
	}
	if (i == j&&i == 1)
	{
		*wholeTiles = widthTiles*lengthTiles;
		*partTiles = i*lengthTiles + j*widthTiles + 1;
	}
	else
	{
		*wholeTiles = widthTiles*lengthTiles;
		*partTiles = i*lengthTiles + j*widthTiles;
	}
}
/*
�Լ��̸�:Output
���:������Ÿ�ϼ����߶󼭻����Ÿ�ϼ����Է¹޾Ƹ���ͷ�����Ѵ�
�Է�:������ũ��,������ũ��,������Ÿ�ϼ�,�߶󼭻����Ÿ�ϼ�
���:X
*/
void Output(ULong widthSize, ULong lengthSize, ULong wholeTiles, ULong partTiles)
{
	printf("������ũ��%d   ������ũ��%d\n������Ÿ�ϼ�:%d   �߶󼭻����Ÿ�ϼ�:%d", widthSize, lengthSize, wholeTiles, partTiles);
}