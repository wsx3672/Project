//Form.cpp

#include "wordBook.h"
#include "Form.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

// 메인메뉴
// 메인메뉴
void Form::DisplayMenu() {
	system("cls");
	cout << "\n\n\n\n\n" << endl;
	cout << "\t\t\t  주소록 Version 1.00" << endl;
	cout << "\t\t\t  =============================" << endl;
	cout << "\t\t\t  [1] 기재하기" << endl;
	cout << "\t\t\t  [2] 찾    기" << endl;
	cout << "\t\t\t  [3] 고 치 기" << endl;
	cout << "\t\t\t  [4] 지 우 기" << endl;
	cout << "\t\t\t  [5] 정리하기" << endl;
	cout << "\t\t\t  [6] 전체보기" << endl;
	cout << "\t\t\t  [0] 끝 내 기" << endl;
	cout << "\t\t\t  -----------------------------" << endl;
	cout << "\t\t\t  메뉴를 선택하십시오. " << endl;
	cout << "\t\t\t  ";
}
// [1] 기재하기
void  Form::FormForRecording(WordBook& wordBook)
{
	string spelling;
	string meaning;
	string wordClass;
	string example;
	Word word;
	char recording;
	char going = 'Y';
	Long index;
	while (going == 'Y' || going == 'y') {
		system("cls");

		cout << "\n\n\n" << endl;
		cout << "\t\t       주소록 Version 1.00 -기재하기" << endl;
		cout << "\t\t       =============================" << endl;
		cout << "\t\t       단 어 명 : "; cin >> spelling;
		cout << "\t\t       의    미 : "; cin >> meaning;
		cout << "\t\t       품    사 : "; cin >> wordClass; cin.ignore();
		cout << "\t\t       예    문 : "; getline(cin, example, '\n');
		cout << "\t\t       -----------------------------" << endl;
		cout << "\t\t       기재하시겠습니까? (Yes/No) "; recording = getchar();
		if (recording == 'Y' || recording == 'y') {
			index = wordBook.Record(spelling, meaning, wordClass, example);
			word = wordBook.GetAt(index);
			cout << "\t    =======================================================" << endl;
			cout << "\t    번호\t단어\t의미\t품사\t예문" << endl;
			cout << "\t    -------------------------------------------------------" << endl;
			cout << "\t    " << index + 1 << "\t\t";
			cout << word.GetSpelling() << "\t";
			cout << word.GetMeaning() << "\t";
			cout << word.GetWordClass() << "\t";
			cout << word.GetExample() << "\t" << endl;
		}
		cout << "\t    =======================================================" << endl; cin.ignore();
		cout << "\t    계속하시겠습니까? (Yes/No) "; going = getchar();
	}
}

// [2] 찾    기
void Form::FormForFinding(WordBook& wordBook)
{
	string spelling;
	char going = 'Y';
	Word word;
	Long(*indexes);
	Long count;
	Long i = 0;
	Long index;
	while (going == 'Y' || going == 'y') {
		system("cls");
		cout << "\n\n\n" << endl;
		cout << "\t\t       단어장 Version 0.05 -찾    기" << endl;
		cout << "\t\t       =============================" << endl;
		cout << "\t\t       단 어 명 : "; cin >> spelling;
		cout << "\t    =======================================================" << endl;
		wordBook.Find(spelling, &indexes, &count);
		cout << "\t    번호\t단어\t의미\t품사\t예문" << endl;
		cout << "\t    -------------------------------------------------------" << endl;
		while (i < count) {
			index = indexes[i];
			word = wordBook.GetAt(index);
			cout << "\t    " << i + 1 << "\t\t";
			cout << word.GetSpelling() << "\t";
			cout << word.GetMeaning() << "\t";
			cout << word.GetWordClass() << "\t";
			cout << word.GetExample() << "\t" << endl;
			i++;
		}
		if (indexes != 0) { //할당해제
			delete[] indexes;
			indexes = 0;
		}
		cout << "\t    =======================================================" << endl; cin.ignore();
		cout << "\t    계속하시겠습니까? (Yes/No) ";  going = cin.get(); //진행여부를 입력받는다.
	}
}

// [3] 고 치 기
void Form::FormForCorrecting(WordBook& wordBook)
{
	string spelling;
	string meaning;
	string wordClass;
	string example;
	char correcting;
	char going = 'Y';
	Long number;
	Long(*indexes);
	Long count;
	Word word;
	Long index;
	Long i = 0;
	while (going == 'Y' || going == 'y') {
		system("cls");
		cout << "\n" << endl;
		cout << "\t\t       단어장 Version 1.00 -고 치 기" << endl;
		cout << "\t\t       =============================" << endl;
		cout << "\t\t       단 어 명 : "; cin >> spelling;
		wordBook.Find(spelling, &indexes, &count); //Find함수를 호출한다.
		if (count > 0) {
			cout << "\t    -------------------------------------------------------" << endl;
			cout << "\t    번호\t단어\t의미\t품사\t예문" << endl;
			cout << "\t    =======================================================" << endl;
			while (i < count) {
				index = indexes[i];
				word = wordBook.GetAt(index);
				cout << "\t    " << i + 1 << "\t\t";
				cout << word.GetSpelling() << "\t";
				cout << word.GetMeaning() << "\t";
				cout << word.GetWordClass() << "\t";
				cout << word.GetExample() << "\t" << endl;
				i++;
			}
			cout << "\t    -------------------------------------------------------" << endl;
			cout << "\t    번    호 : "; cin >> number; //고칠 줄번호를 번호로 입력받는다.
			index = indexes[number - 1];
			word = wordBook.GetAt(index);
			cout << "\t    의    미 (" << word.GetMeaning() << ") : "; cin >> meaning; //주소를 입력받는다.
			if (meaning == "") { //입력값이 없으면 기존값으로 복사한다.
				meaning = word.GetMeaning();
			}
			cout << "\t    품    사 (" << word.GetWordClass() << ") : "; cin >> wordClass; //주소를 입력받는다.
			if (wordClass == "") { //입력값이 없으면 기존값으로 복사한다.
				wordClass = word.GetWordClass();
			}
			cout << "\t    예    문 (" << word.GetExample() << ") : "; cin >> example; //주소를 입력받는다.
			if (example == "") { //입력값이 없으면 기존값으로 복사한다.
				example = word.GetExample();
			}

			cout << "\t    -------------------------------------------------------" << endl;
			cout << "\t    고치시겠습니까? (Yes/No) "; cin.ignore(); correcting = getchar(); //진행여부를 입력받는다.
			if (correcting == 'Y' || correcting == 'y') {
				wordBook.Correct(index, meaning, wordClass, example); //Correct함수를 호출한다.
				cout << "\t    -------------------------------------------------------" << endl;
				cout << "\t    번호\t단어\t의미\t품사\t예문" << endl;
				cout << "\t    -------------------------------------------------------" << endl;
				cout << "\t    " << index + 1;
				word = wordBook.GetAt(index);
				cout << "\t    " << word.GetSpelling() << "\t" << word.GetMeaning() << "\t" << word.GetWordClass() << "\t" << word.GetExample() << endl;
			}
		}
		if (indexes != 0) { //할당해제
			delete[] indexes;
			indexes = 0;
		}
		cout << "\t    =======================================================" << endl; cin.ignore();
		cout << "\t    계속하시겠습니까? (Yes/No) "; going = getchar(); //진행여부를 입력받는다.
	}
}

// [4] 지 우 기
void Form::FormForErasing(WordBook& wordBook)
{
	string spelling;
	Word word;
	char erasing;
	char going = 'Y';
	Long number;
	while (going == 'Y' || going == 'y') {
		system("cls");
		cout << "\n\n\n" << endl;
		cout << "\t\t  주소록 Version 0.05 -지 우 기" << endl;
		cout << "\t\t  =============================" << endl;
		cout << "\t\t  번    호 : "; cin >> number; //지울 줄번호를 번호로 입력받는다.
		cout << "\t\t  -----------------------------" << endl;
		word = wordBook.GetAt(number - 1);
		cout << "\t\t  단어\t의미\t품사\t예문" << endl;
		cout << "\t\t  -----------------------------" << endl;
		cout << "\t\t  " << word.GetSpelling() << "\t" << word.GetMeaning() << "\t" << word.GetWordClass() << "\t" << word.GetExample() << endl;
		cout << "\t\t  -----------------------------" << endl;
		cout << "\t\t  지우시겠습니까? (Yes/No) "; cin.ignore(); erasing = getchar();  //진행여부를 입력받는다.
		if (erasing == 'Y' || erasing == 'y') {
			wordBook.Erase(number - 1); //Erase함수를 호출한다.
			cout << "\t\t  =============================" << endl;
			cout << "\t\t  지워졌습니다." << endl;
		}


		cout << "\t\t  =============================" << endl; cin.ignore();
		cout << "\t\t  계속하시겠습니까? (Yes/No) "; going = getchar();
	}
}

// [5] 정리하기
void Form::FormForArranging(WordBook& wordBook)
{
	Word word;
	Long index = 0;
	Long i;
	wordBook.Arrange(); //Arrange함수를 호출한다.
	while (index < wordBook.GetLength()) { //줄번호가 주소록의 사용량보다 작을때까지
		system("cls");
		cout << "\n\n\n" << endl;
		cout << "\t    주소록 Version 0.05 -정리하기" << endl;
		cout << "\t    -------------------------------------------------------" << endl;
		cout << "\t    번호\t단어\t의미\t품사\t예문" << endl;
		cout << "\t    -------------------------------------------------------" << endl;
		i = 1;
		while (i <= 5 && index < wordBook.GetLength()) { // 5줄씩 출력하기위한 반복문
			word = wordBook.GetAt(index);
			cout << "\t    " << index + 1;
			cout << "\t\t" << word.GetSpelling() << "\t" << word.GetMeaning() << "\t" << word.GetWordClass() << "\t" << word.GetExample() << endl;
			i++;
			index++;
		}
		cout << "\t    =======================================================" << endl; cin.ignore();
		cout << "\t    아무키나 누르시오. " << endl; getchar(); //아무키나 입력받는다.
	}
}

// [6] 전체보기
void Form::FormForViewAll(WordBook& wordBook)
{
	Word word;
	Long index = 0;
	Long i;

	while (index < wordBook.GetLength()) {//줄번호가 주소록의 사용량보다 작을때까지
		system("cls");
		cout << "\n\n\n" << endl;
		cout << "\t    주소록 Version 0.05 - 전체보기" << endl;
		cout << "\t    -------------------------------------------------------" << endl;
		cout << "\t    번호\t단어\t의미\t품사\t예문" << endl;
		cout << "\t    -------------------------------------------------------" << endl;
		i = 1;
		while (i <= 5 && index < wordBook.GetLength()) { // 5줄씩 출력하기위한 반복문
			word = wordBook.GetAt(index);
			cout << "\t    " << index + 1 << "\t\t" << word.GetSpelling() << "\t" // spelling 출력
				<< word.GetMeaning() << "\t" <<
				word.GetWordClass() << "\t" <<
				word.GetExample() << endl; // 주소록의 레코드들을 출력한다.
			i++;
			index++;
		}
		cout << "\t    =======================================================" << endl; cin.ignore();
		cout << "\t    아무키나 누르시오. " << endl; cin.get(); //아무키나 입력받는다.
	}
}