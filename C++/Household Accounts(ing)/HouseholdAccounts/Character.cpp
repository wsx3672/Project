#include "Character.h"
#include "DoubleByteCharacter.h"
Character::Character() {
}
Character::Character(const Character& source) {
}
Character::~Character() {
}
Long Character::CheckingSingleAndDouble() {
	Long checking = 0;
	if (dynamic_cast<DoubleByteCharacter*>(this)) {
		checking = 1;
	}
	return checking;
	//Single 이면 0 Double 이면 1 
}
