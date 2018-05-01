//Personal.cpp

#include "Personal.h"

Personal::Personal() :name(""), address(""), telephoneNumber(""), emailAddress("") {
}

Personal::Personal(string name, string address, string telephoneNumber, string emailAddress) : name(name), address(address), telephoneNumber(telephoneNumber), emailAddress(emailAddress) {
}

Personal::Personal(const Personal& source) : name(source.name), address(source.address), telephoneNumber(source.telephoneNumber), emailAddress(source.emailAddress) {
}

Personal::~Personal() {
}

bool Personal::IsEqual(const Personal& other) {
	bool ret = false;

	if (this->name == other.name && this->address == other.address
		&& this->telephoneNumber == other.telephoneNumber && this->emailAddress == other.emailAddress) {
		ret = true;
	}
	return ret;
}

bool Personal::IsNotEqual(const Personal& other) {
	bool ret = false;

	if (this->name != other.name || this->address != other.address ||
		this->telephoneNumber != other.telephoneNumber || this->emailAddress != other.emailAddress) {
		ret = true;
	}
	return ret;
}

//치환연산자
Personal& Personal::operator = (const Personal& source) {
	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->emailAddress = source.emailAddress;
	return *this;
}

//비교연산자
bool Personal::operator == (const Personal& other) {
	bool ret = false;

	if (this->name == other.name && this->address == other.address
		&& this->telephoneNumber == other.telephoneNumber && this->emailAddress == other.emailAddress) {
		ret = true;
	}
	return ret;
}

bool Personal::operator != (const Personal& other) {
	bool ret = false;

	if (this->name != other.name || this->address != other.address ||
		this->telephoneNumber != other.telephoneNumber || this->emailAddress != other.emailAddress) {
		ret = true;
	}
	return ret;
}