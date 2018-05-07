//Personal.cpp
#include "Personal.h"
Personal::Personal() :name(""), position(""), telephoneNumber(""), emailAddress("") {
}
Personal::Personal(string name, string position, string telephoneNumber, string emailAddress) : name(name), position(position), telephoneNumber(telephoneNumber), emailAddress(emailAddress) {
}
Personal::Personal(const Personal& source) : name(source.name), position(source.position), telephoneNumber(source.telephoneNumber), emailAddress(source.emailAddress) {
}
Personal::~Personal() {
}
Personal& Personal::operator=(const Personal& source) {
	this->name = source.name;
	this->position = source.position;
	this->telephoneNumber = source.telephoneNumber;
	this->emailAddress = source.emailAddress;
	return *this;
}
bool Personal::operator==(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 && this->position.compare(other.position) == 0 && this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}
bool Personal::operator!=(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 || this->position.compare(other.position) != 0 || this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}
bool Personal::IsEqual(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 && this->position.compare(other.position) == 0 && this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}
bool Personal::IsNotEqual(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 || this->position.compare(other.position) != 0 || this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}