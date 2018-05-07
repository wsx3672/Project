//BusinessCard.cpp
#include "BusinessCard.h"
BusinessCard::BusinessCard() {
}
BusinessCard::BusinessCard(string name, string position, string cellphoneNumber, string emailAddress, string companyName, string address, string telephoneNumber, string faxNumber, string url) :personal(name, position, cellphoneNumber, emailAddress), company(companyName, address, telephoneNumber, faxNumber, url) {
}
BusinessCard::BusinessCard(const BusinessCard& source) : personal(source.personal), company(source.company) {
}
BusinessCard::~BusinessCard() {
}
bool BusinessCard::IsEqual(const BusinessCard& source) {
	bool ret = false;
	if (this->personal == source.personal && this->company == source.company) {
		ret = true;
	}
	return ret;
}
bool BusinessCard::IsNotEqual(const BusinessCard& source) {
	bool ret = false;
	if (this->personal != source.personal || this->company != source.company) {
		ret = true;
	}
	return ret;
}
BusinessCard& BusinessCard::operator = (const BusinessCard& source) {
	this->personal = source.personal;
	this->company = source.company;
	return *this;
}
bool BusinessCard::operator==(const BusinessCard& source) {
	bool ret = false;
	if (this->personal == source.personal && this->company == source.company) {
		ret = true;
	}
	return ret;
}
bool BusinessCard::operator!=(const BusinessCard& source) {
	bool ret = false;
	if (this->personal != source.personal || this->company != source.company) {
		ret = true;
	}
	return ret;
}