#include "DoubleByteCharacter.h"

DoubleByteCharacter::DoubleByteCharacter() {
	this->characters[0] = ' ';
	this->characters[1] = ' ';
}
DoubleByteCharacter::DoubleByteCharacter(char *(characters)) {
	this->characters[0] = characters[0];
	this->characters[1] = characters[1];
}
DoubleByteCharacter::~DoubleByteCharacter() {
}
DoubleByteCharacter::DoubleByteCharacter(const DoubleByteCharacter& source) {
	this->characters[0] = source.characters[0];
	this->characters[1] = source.characters[1];
}
DoubleByteCharacter& DoubleByteCharacter::operator=(const DoubleByteCharacter& source) {
	this->characters[0] = source.characters[0];
	this->characters[1] = source.characters[1];
	return *this;
}
TextComponent* DoubleByteCharacter::Clone() const {
	return new DoubleByteCharacter(*this);
}
/*  DoubleByteCharacter 뒤에 '\0' 문자를 넣어줘서 짤라줘야함.
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	DoubleByteCharacter character("우");
	DoubleByteCharacter character1("장");

	char *test = character.GetCharacter();
	char *test1 = character1.GetCharacter();
	test[2] = '\0';
	test1[2] = '\0';
	cout << test << test1 << endl;

	character1 = character;

	cout << test << test1 << endl;
	return 0;
}
*/