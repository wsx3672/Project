//Word.cpp
#include "Word.h"

Word::Word() //콜론초기화  생성&치환을 동시에 
	:spelling(""), meaning(""), wordClass(""), example("") {
}

Word::Word(string spelling, 	string meaning, string 	wordClass, string example)
	: spelling(spelling), meaning(meaning), wordClass(wordClass), example(example) {
}

Word::Word(const Word& source) //복사생성자
	: spelling(source.spelling), meaning(source.meaning), wordClass(source.wordClass), example(source.example) {
}
Word::~Word(){ //소멸자
}

bool Word::IsEqual(const Word& source)
{
	bool ret;

	if (this->spelling.compare(source.spelling) == 0 &&
		this->meaning.compare(source.meaning) == 0 &&
		this->wordClass.compare(source.wordClass) == 0 &&
		this->example.compare(source.example) == 0)	{

		ret = true;
	}
	return ret;
}

bool Word::IsNotEqual(const Word& source)
{
	bool ret;

	if (this->spelling.compare(source.spelling) != 0 || 
		this->meaning.compare(source.meaning) != 0 || 
		this->wordClass.compare(source.wordClass) != 0 || 
		this->example.compare(source.example) != 0) {

		ret = true;
	}
	return ret;
}

bool Word::operator==(const Word& source)
{
	bool ret;

	if (this->spelling.compare(source.spelling) == 0 && 
		this->meaning.compare(source.meaning) == 0 && 
		this->wordClass.compare(source.wordClass) == 0 && 
		this->example.compare(source.example) == 0) {

		ret = true;
	}
	return ret;
}

bool Word::operator!=(const Word& source)
{
	bool ret;

	if (this->spelling.compare(source.spelling) != 0 || 
		this->meaning.compare(source.meaning) != 0 || 
		this->wordClass.compare(source.wordClass) != 0 || 
		this->example.compare(source.example) != 0) {

		ret = true;
	}
	return ret;
}

Word& Word::operator=(const Word& source)
{
	this->spelling = source.spelling;
	this->meaning = source.meaning;
	this->wordClass = source.wordClass;
	this->example = source.example;

	return *this;
}
