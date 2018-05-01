//TemperatureConversion.c
/*
파일명칭:TemperatureConversion.c
기능:입력받은 온도의종류를 판단하여 온도를 변환한다
작성자:박상민
작성일자:2017년05월17일
*/
//매크로선언
#include <stdio.h>
#pragma warning (disable:4996)
//자료형설계
typedef signed char Char;//생략가능(?)
						 //함수선언
int main(int argc, char *argv[]);
void Input(Char *temperatureType, float *temperature);
void TemperatureConversion(Char temperatureType, float temperature, Char *convertTemperatureType, float *convertTemperature);
void Output(Char temperatureType, float temperature, Char convertTemperatureType, float convertTemperature);
//함수정의
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
함수이름:Input
기능:키보드로부터 온도의종류와 온도를 입력받는다
입력:X
출력:온도의종류,온도
*/
void Input(Char *temperatureType, float *temperature)
{
	printf("온도의종류와온도를 입력해주세요 EX)C 12\n");
	scanf("%c %f", temperatureType, temperature);
}
/*
함수이름:TemperatureConversion
기능:입력받은 온도의종류와온도를 판단하여 온도를 변환한다
입력:온도의종류,온도
출력:변환된 온도의종류,변환된온도
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
함수이름:Output
기능:반환된온도의종류와반환된온도를 입력받아 모니터로 출력한다
입력:온도의종류,온도,변환된온도의종류,변환된온도
출력:X
*/
void  Output(Char temperatureType, float temperature, Char convertTemperatureType, float convertTemperature)
{
	if (convertTemperatureType == 'F' || convertTemperatureType == 'C')
	{
		printf("입력하신온도의종류:%c\n입력하신온도:%.2f\n\n", temperatureType, temperature);
		printf("변환된온도의종류:%c\n변환된온도:%.2f", convertTemperatureType, convertTemperature);
	}
	else
	{
		printf("ERROR DATA:0.00");
	}
}
