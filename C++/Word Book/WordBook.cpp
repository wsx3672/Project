//WordBook.cpp
#include "Form.h"
#include "WordBook.h"

//디폴트생성자
WordBook::WordBook(Long capacity) : words(capacity)
{
	this->capacity = capacity;
	this->length = 0;
}

//복사생성자
WordBook::WordBook(const WordBook& source) :words(source.words)
{
	this->capacity = source.capacity;
	this->length = source.length;
}

//소멸자
WordBook::~WordBook() {
}

Long WordBook::Record(string spelling, string meaning, string wordClass, string example)
{
	Word word(spelling, meaning, wordClass, example);
	Long index;
	if (this->length < this->capacity) {
		index = this->words.Store(this->length, word);
	}
	else {
		index = this->words.AppendFromRear(word);
		this->capacity++;
	}
	this->length++;

	return index;
}

void WordBook::Find(string spelling, Long *(*indexes), Long *count)
{
	this->words.LinearSearchDuplicate(&spelling, indexes, count, CompareSpellings);
}

Long WordBook::Erase(Long index)
{
	index = this->words.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}
Long WordBook::Correct(Long index, string meaning, string wordClass, string example)
{
	Word word = this->words.GetAt(index);
	Word otherWord(word.GetSpelling(), meaning, wordClass, example);
	index = this->words.Modify(index, otherWord);
	return index;
}

void WordBook::Arrange() {
	this->words.InsertionSort(CompareWords);
}

Word& WordBook::GetAt(Long index) {
	return this->words.GetAt(index);
}

WordBook& WordBook::operator=(const WordBook& source)
{
	this->words = source.words;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Word& WordBook::operator[](Long index) {
	return this->words[index];
}

Word* WordBook::operator+(Long index) {
return (this->words) + index;
}

int CompareSpellings(void *one, void *other) {
	return (static_cast<Word*>(one))->GetSpelling().compare(*(static_cast<string*>(other)));
}

int CompareWords(void *one, void *other) {
	return (static_cast<Word*>(one))->GetSpelling().compare((static_cast<Word*>(other))->GetSpelling());
}


#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
	Form form;
	WordBook wordBook;
	Long menu; //메뉴번호

	form.DisplayMenu(); scanf("%d", &menu); //메뉴를 입력받는다.
	while (menu != 0) {
		switch (menu) {

		case 1:form.FormForRecording(wordBook); break;   // [1] 기재하기

		case 2:form.FormForFinding(wordBook); break;      // [2] 찾기

		case 3:form.FormForCorrecting(wordBook); break;   // [3] 고치기

		case 4:form.FormForErasing(wordBook); break;      // [4] 지우기

		case 5:form.FormForArranging(wordBook); break;   // [5] 정리하기

		case 6:form.FormForViewAll(wordBook); break;      // [6] 전체보기

		default: break; //0~6외의 값은 반복

		}
		form.DisplayMenu(); rewind(stdin); scanf("%d", &menu); //각 메뉴가 끝나면 메인메뉴 호출
	}

	return 0;
}





/*
#include<iostream>
using namespace std;
int main(int argc, char *argv[]) {
	WordBook wordBook(3);
	Word word;

	cout << "-기재하기-" << endl;
	Long index = wordBook.Record("dog", "dog", "dog", "dog");
	cout << wordBook[index].GetSpelling() << " " << wordBook[index].GetMeaning() << " " << wordBook[index].GetWordClass() << " " << wordBook[index].GetExample() << endl;
	index = wordBook.Record("zzz", "zzz", "zzz", "zzz");
	cout << wordBook[index].GetSpelling() << " " << wordBook[index].GetMeaning() << " " << wordBook[index].GetWordClass() << " " << wordBook[index].GetExample() << endl;
	index = wordBook.Record("xxx", "xxx", "xxx", "xxx");
	cout << wordBook[index].GetSpelling() << " " << wordBook[index].GetMeaning() << " " << wordBook[index].GetWordClass() << " " << wordBook[index].GetExample() << endl;
	index = wordBook.Record("xxx", "xxx", "xxx", "ccc");
	cout << wordBook[index].GetSpelling() << " " << wordBook[index].GetMeaning() << " " << wordBook[index].GetWordClass() << " " << wordBook[index].GetExample() << endl;
	cout << endl << endl;

	Long count;
	Long(*indexes);

	cout << "-찾    기-" << endl;
	wordBook.Find("xxx", &indexes, &count);
	Long i = 0;
	while (i < count) {
		cout << wordBook[indexes[i]].GetSpelling() << " " << wordBook[indexes[i]].GetMeaning() << " " << wordBook[indexes[i]].GetWordClass() << " " << wordBook[indexes[i]].GetExample() << endl;
		i++;
	}
	if (index != 0) {
		delete[] indexes;
		indexes = 0;
	}
	cout << endl << endl;

	cout << "-고 치 기-" << endl;
	index = wordBook.Correct(0, "yyy", "yyy", "yyy");
	cout << wordBook[index].GetSpelling() << " " << wordBook[index].GetMeaning() << " " << wordBook[index].GetWordClass() << " " << wordBook[index].GetExample() << endl;
	cout<< endl << endl;

	cout<< "-GetAt-" << endl;
	Word wordOne = wordBook.GetAt(0);
	cout << wordOne.GetSpelling() << " " << wordOne.GetMeaning() << " " << wordOne.GetWordClass() << " " << wordOne.GetExample() << endl << endl;

	cout << endl << "-지 우 기-" << endl;
	index = wordBook.Erase(0);
	if (index == -1) {
		cout << "삭제됨" << endl;
	}
	cout << endl << endl;

	cout << "-복사생성자-" << endl;
	WordBook otherWordBook(wordBook);
	i = 0;
	while (i < otherWordBook.GetLength()) {
		cout << otherWordBook[i].GetSpelling() << " " << otherWordBook[i].GetMeaning() << " " << otherWordBook[i].GetWordClass() << " " << otherWordBook[i].GetExample() << endl;
		i++;
	}
	cout << endl << endl;

	cout << "-정리하기-" << endl;
	wordBook.Arrange();
	i = 0;
	while (i < wordBook.GetLength()) {
		cout << wordBook[i].GetSpelling() << " " << wordBook[i].GetMeaning() << " " << wordBook[i].GetWordClass() << " " << wordBook[i].GetExample() << endl;
		i++;
	}
	cout << endl << endl;

	cout << "-등가함수-" << endl;
	if (wordBook[1] == wordBook[1]) {
		cout << "같습니다" << endl;
	}
	if (wordBook[1] != wordBook[2]) {
		cout << "다릅니다" << endl;
	}
	cout << endl;
	return 0;
}
*/