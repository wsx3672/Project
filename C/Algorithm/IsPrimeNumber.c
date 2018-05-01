//IsPrimeNumber.c
/*
파일명칭:IsPrimeNumber.c
기능:수를 입력받아 소수인지 합성수인지 판단한다
작성자:박상민
작성일자:2017년05월15일
오류수정:2017년5월26일 
오류내용:함수선언과함수정의가 엉망이였고 IsPrimeNumber함수에서 리턴을 isPrimeNumber로 보내도록 수정.
*/
//매크로선언
#include <stdio.h>
#pragma warning (disable:4996)
//자료형설계
typedef unsigned long int  ULong;
typedef enum _boolean { FALSE = 0, TRUE = 1 } Boolean;
//함수선언
int main(int argc, char*argv[]);
ULong Input();
Boolean IsPrimeNumber(ULong number);
void Output(ULong number, Boolean isPrimeNumber);
//함수정의
int main(int argc, char*argv[])
{
	ULong number;
	Boolean isPrimeNumber;
	number = Input();
	isPrimeNumber = IsPrimeNumber(number);
	Output(number, isPrimeNumber);
	return 0;
}
/*
함수이름:Input
기능:키보드로 수를 입력받는다
입력:X
출력:수
*/
ULong Input()
{
	ULong number;
	scanf("%d", &number);
	return number;
}

/*함수이름:IsPrimeNumber
기능:입력받은수를 소수인지 합성수인지 판단한다
입력:수
츨력:소수여부
*/

Boolean IsPrimeNumber(ULong number)

{
	Boolean isPrimeNumber;
	ULong factor = 0;
	ULong count = 0;
	ULong i = 1;
	ULong remainder;
	while (i <= number) {
		factor++;
		remainder = number - number / factor*factor;
		if (remainder == 0) {
			count++;
		}
		i++;
	}
	if (count == 2) {
		isPrimeNumber = TRUE;
	}
	else {
		isPrimeNumber = FALSE;
	}
	return isPrimeNumber;
}

/*함수이름:Output
기능:소수판단여부를 모니터로 출력한다
입력:수,소수여부
출력:X
*/
void Output(ULong number, Boolean isPrimeNumber) {
	if (isPrimeNumber == TRUE) {
		printf("%d는소수입니다", number);
	}
	else {
		printf("%d는 합성수입니다.", number);
	}
}