#include "SingleByteCharacter.h"

SingleByteCharacter::SingleByteCharacter() {
	this->character = ' ';
}
SingleByteCharacter::SingleByteCharacter(char character) {
	this->character = character;
}
SingleByteCharacter::~SingleByteCharacter() {
}
SingleByteCharacter::SingleByteCharacter(const SingleByteCharacter& source) {
	this->character = source.character;
}
SingleByteCharacter& SingleByteCharacter::operator=(const SingleByteCharacter& source) {
	this->character = source.character;
	return *this;
}
TextComponent* SingleByteCharacter::Clone() const {
	return new SingleByteCharacter(*this);
}
 /*
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	SingleByteCharacter character('A');
	SingleByteCharacter character1;
	character1 = character;

	char test = character.GetCharacter();
	char test1 = character1.GetCharacter();
	cout << test << test1 << endl;
	return 0;
}
*/