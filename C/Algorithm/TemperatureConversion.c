//TemperatureConversion.c
/*
���ϸ�Ī:TemperatureConversion.c
���:�Է¹��� �µ��������� �Ǵ��Ͽ� �µ��� ��ȯ�Ѵ�
�ۼ���:�ڻ��
�ۼ�����:2017��05��17��
*/
//��ũ�μ���
#include <stdio.h>
#pragma warning (disable:4996)
//�ڷ�������
typedef signed char Char;//��������(?)
						 //�Լ�����
int main(int argc, char *argv[]);
void Input(Char *temperatureType, float *temperature);
void TemperatureConversion(Char temperatureType, float temperature, Char *convertTemperatureType, float *convertTemperature);
void Output(Char temperatureType, float temperature, Char convertTemperatureType, float convertTemperature);
//�Լ�����
int main(int argc, char *argv[])
{
	Char temperatureType;
	float temperature;
	Char convertTemperatureType;
	float convertTemperature;
	Input(&temperatureType, &temperature);
	TemperatureConversion(temperatureType, temperature, &convertTemperatureType, &convertTemperature);
	Output(temperatureType, temperature, convertTemperatureType, convertTemperature);
	return 0;
}
/*
�Լ��̸�:Input
���:Ű����κ��� �µ��������� �µ��� �Է¹޴´�
�Է�:X
���:�µ�������,�µ�
*/
void Input(Char *temperatureType, float *temperature)
{
	printf("�µ��������Ϳµ��� �Է����ּ��� EX)C 12\n");
	scanf("%c %f", temperatureType, temperature);
}
/*
�Լ��̸�:TemperatureConversion
���:�Է¹��� �µ��������Ϳµ��� �Ǵ��Ͽ� �µ��� ��ȯ�Ѵ�
�Է�:�µ�������,�µ�
���:��ȯ�� �µ�������,��ȯ�ȿµ�
*/
void TemperatureConversion(Char temperatureType, float temperature, Char *convertTemperatureType, float *convertTemperature)
{
	if (temperatureType == 'c' || temperatureType == 'C')
	{
		*convertTemperature = temperature*1.8F + 32.00F;
		*convertTemperatureType = 'F';
	}
	else
	{
		if (temperatureType == 'f' || temperatureType == 'F')
		{
			*convertTemperature = (temperature - 32.00F) / 1.8F;
			*convertTemperatureType = 'C';
		}
		else
		{
			*convertTemperature = 0;
			*convertTemperatureType = temperatureType;
		}
	}

}
/*
�Լ��̸�:Output
���:��ȯ�ȿµ��������͹�ȯ�ȿµ��� �Է¹޾� ����ͷ� ����Ѵ�
�Է�:�µ�������,�µ�,��ȯ�ȿµ�������,��ȯ�ȿµ�
���:X
*/
void  Output(Char temperatureType, float temperature, Char convertTemperatureType, float convertTemperature)
{
	if (convertTemperatureType == 'F' || convertTemperatureType == 'C')
	{
		printf("�Է��Ͻſµ�������:%c\n�Է��Ͻſµ�:%.2f\n\n", temperatureType, temperature);
		printf("��ȯ�ȿµ�������:%c\n��ȯ�ȿµ�:%.2f", convertTemperatureType, convertTemperature);
	}
	else
	{
		printf("ERROR DATA:0.00");
	}
}
