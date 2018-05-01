//IsPerfectNumber.c
/*파일명칭:IsperfectNumber.c
기능:수를 입력받아 완전수임을 확인한다
작성자:박상민
작성일자:2017년5월16일*/
//매크로선언
#include <stdio.h>
//자료형설계
typedef unsigned long int ULong;
typedef enum _boolean { FALSE = 0, TRUE = 1 }Boolean;
//함수선언
int main(int argc, char*argv[]);
ULong Input();
Boolean IsPerfectNumber(ULong number);
void Output(ULong number, Boolean isPerfectNumber);
//함수정의
int main(int argc, char*argv[])
{
	ULong number;
	Boolean isPerfectNumber;
	number = Input();
	isPerfectNumber = IsPerfectNumber(number);
	Output(number, isPerfectNumber);
	return 0;
}
/*함수이름:Input
기능:키보드로부터수를 입력받는다
입력:X
출력:수
*/
ULong Input() {
	ULong number;
	scanf("%d", &number);
	return number;
}
/*함수이름:IsPerfectNumber
기능:입력받은수가 완전수임을 확인한다
입력:수
출력:완전수여부
*/
Boolean IsPerfectNumber(ULong number) {
	Boolean isPerfectNumber;
	ULong sum = 0;
	ULong remainder;
	ULong factor=0;
	ULong i = 1;
	while (i <= number / 2) {
		factor++;
		remainder = number%factor;
		if (remainder == 0) {
			sum += factor;
		}
		i++;
	}
	if (sum == number) {
		isPerfectNumber = TRUE;
	}
	else {
		isPerfectNumber = FALSE;
	}
	return isPerfectNumber;
}
/*함수이름:Output
기능:완전수여부릉 입력받아 모니터로 출력한다
입력:수,완전수여부
출력:X
*/
void Output(ULong number, Boolean isPerfectNumber) {
	if (isPerfectNumber == TRUE) {
		printf("%d는완전수입니다.", number);
	}
	else {
		printf("%d는 완전수가아닙니다.", number);
	}
}
