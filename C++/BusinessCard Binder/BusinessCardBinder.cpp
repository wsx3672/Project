//BusinessCardBinder.cpp

#include "BusinessCardBinder.h"

BusinessCardBinder::BusinessCardBinder() {
	this->length = 0;
	this->current = 0;
}

BusinessCardBinder::BusinessCardBinder(const BusinessCardBinder& source) :businessCards(source.businessCards) {
	this->length = source.length;
	LinkedList<BusinessCard>::Node *node = this->businessCards.GetCurrent();
	this->current = &node->GetObject();
}

BusinessCard* BusinessCardBinder::TakeIn(BusinessCard businessCard) {
	LinkedList<BusinessCard>::Node *node = this->businessCards.AppendFromTail(businessCard);
	this->length++;
	this->current = &node->GetObject();
	return this->current;
}

BusinessCard BusinessCardBinder::TakeOut(BusinessCard *index) {
	LinkedList<BusinessCard>::Node *node = this->businessCards.LinearSearchUnique(index, CompareBusinessCardLinkss);
	BusinessCard businessCard = node->GetObject();
	this->businessCards.Delete(node);
	this->length--;

	node = this->businessCards.GetCurrent();
	if (node != 0) {
		this->current = &node->GetObject();
	}
	else {
		this->current = 0;
	}

	return businessCard;
}

void BusinessCardBinder::Find(string name, BusinessCard**(*indexes), Long *count) {

	LinkedList<BusinessCard>::Node*(*nodes);

	this->businessCards.LinearSearchDuplicate(&name, &nodes, count, CompareNames);

	if (*count > 0) {
		*indexes = new BusinessCard*[*count];
	}
	Long i = 0;

	while (i < *count) {
		(*indexes)[i] = &nodes[i]->GetObject();
		i++;
	}
	if (nodes != 0) {
		delete[]nodes;
		nodes = 0;
	}
}

BusinessCard* BusinessCardBinder::First() {
	LinkedList<BusinessCard>::Node *node = this->businessCards.First();
	if (node != 0) {
		this->current = &node->GetObject();
	}
	else {
		this->current = 0;
	}
	return this->current;
}

BusinessCard* BusinessCardBinder::Previous() {
	LinkedList<BusinessCard>::Node *node = this->businessCards.Previous();

		this->current = &node->GetObject();

		return this->current;
}

BusinessCard* BusinessCardBinder::Next() {
	LinkedList<BusinessCard>::Node *node = this->businessCards.Next();
	this->current = &node->GetObject();

	return this->current;
}

BusinessCard* BusinessCardBinder::Last() {
	LinkedList<BusinessCard>::Node *node = this->businessCards.Last();
	this->current = &node->GetObject();

	return this->current;
}

BusinessCard* BusinessCardBinder::Move(BusinessCard* index) {
	LinkedList<BusinessCard>::Node *node = this->businessCards.LinearSearchUnique(index, CompareBusinessCardLinkss);
	node = this->businessCards.Move(node);

	this->current = &node->GetObject();

	return this->current;
}

BusinessCard* BusinessCardBinder::FindByCompanyName(string companyName) {
	LinkedList<BusinessCard>::Node *node = this->businessCards.LinearSearchUnique(&companyName, CompareCompanyNames);
	BusinessCard *index = 0;
	if (node != 0) {
		index = &node->GetObject();
	}
	return index;
}

BusinessCardBinder::~BusinessCardBinder() {
}

//치환연산자
BusinessCardBinder& BusinessCardBinder::operator = (const BusinessCardBinder& source) {
	LinkedList<BusinessCard>::Node *node;
	this->businessCards = source.businessCards;
	this->length = source.length;
	node = this->businessCards.GetCurrent();
	this->current = &node->GetObject();

	return *this;
}

int CompareNames(void *one, void *other) {
	return (static_cast<BusinessCard*>(one))->GetName().compare(*(static_cast<string*>(other)));
}

int CompareBusinessCardLinkss(void *one, void *other) {
	int ret;
	if (one == other) {
		ret = 0;
	}
	else {
		ret = -1;
	}
	return ret;
}

int CompareCompanyNames(void *one, void *other) {
	return (static_cast<BusinessCard*>(one)->GetCompanyName().compare(*(static_cast<string*>(other))));
}

BusinessCard& BusinessCardBinder::operator [] (Long index) {
	return this->businessCards[index];
}

//////////////////////////////////////////////////////////////////////////////////////////
/*
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	BusinessCardBinder businessCardBinder;
	BusinessCard businessCard("홍길동", "사장", "01020202020", "Hong@", "삼성", "서울시 서초구", "0211111111", "0222222222", "Hong.com");
	BusinessCard *index = businessCardBinder.TakeIn(businessCard);
	string name = index->GetName();
	string position = index->GetPosition();
	string cellPhoneNumber = index->GetCellphoneNumber();
	string emailAddress = index->GetEmailAddress();
	string companyName = index->GetCompanyName();
	string address = index->GetAddress();
	string telephoneNumber = index->GetTelephoneNumber();
	string faxNumber = index->GetFaxNumber();
	string url = index->GetUrl();
	cout << name << " " << position << cellPhoneNumber << " " << emailAddress
		<< " " << companyName << " " << address <<
		" " << telephoneNumber << " " << faxNumber << " " << url << endl;

	BusinessCard businessCard1("김길동", "전무", "01012402020", "Kimg@", "현대", "서울시 시흥구", "12124", "022214222", "kim.com");
	index = businessCardBinder.TakeIn(businessCard1);
	name = index->GetName();
	position = index->GetPosition();
	cellPhoneNumber = index->GetCellphoneNumber();
	emailAddress = index->GetEmailAddress();
	companyName = index->GetCompanyName();
	address = index->GetAddress();
	telephoneNumber = index->GetTelephoneNumber();
	faxNumber = index->GetFaxNumber();
	url = index->GetUrl();
	cout << name << " " << position << cellPhoneNumber << " " << emailAddress
		<< " " << companyName << " " << address <<
		" " << telephoneNumber << " " << faxNumber << " " << url << endl;

	BusinessCard businessCard2("김묵은지", "퇴장", "123123213", "Kimc@", "김치", "서울시 청담동", "123124455", "1232132", "kimchi.com");
	index = businessCardBinder.TakeIn(businessCard2);
	name = index->GetName();
	position = index->GetPosition();
	cellPhoneNumber = index->GetCellphoneNumber();
	emailAddress = index->GetEmailAddress();
	companyName = index->GetCompanyName();
	address = index->GetAddress();
	telephoneNumber = index->GetTelephoneNumber();
	faxNumber = index->GetFaxNumber();
	url = index->GetUrl();
	cout << name << " " << position << cellPhoneNumber << " " << emailAddress
		<< " " << companyName << " " << address <<
		" " << telephoneNumber << " " << faxNumber << " " << url << endl;

	BusinessCard businessCard3("김묵은지", "사장", "321321321", "suhwan@", "고기집", "서울시 강남구", "1111111", "33333", "chodJo.com");
	index = businessCardBinder.TakeIn(businessCard3);
	name = index->GetName();
	position = index->GetPosition();
	cellPhoneNumber = index->GetCellphoneNumber();
	emailAddress = index->GetEmailAddress();
	companyName = index->GetCompanyName();
	address = index->GetAddress();
	telephoneNumber = index->GetTelephoneNumber();
	faxNumber = index->GetFaxNumber();
	url = index->GetUrl();
	cout << name << " " << position << cellPhoneNumber << " " << emailAddress
		<< " " << companyName << " " << address <<
		" " << telephoneNumber << " " << faxNumber << " " << url << endl;

	BusinessCard businessCard4("김길동", "알바", "43212345", "alba@", "삼성", "서울시 서초구", "12321", "21312", "jessica.com");
	index = businessCardBinder.TakeIn(businessCard4);
	name = index->GetName();
	position = index->GetPosition();
	cellPhoneNumber = index->GetCellphoneNumber();
	emailAddress = index->GetEmailAddress();
	companyName = index->GetCompanyName();
	address = index->GetAddress();
	telephoneNumber = index->GetTelephoneNumber();
	faxNumber = index->GetFaxNumber();
	url = index->GetUrl();
	cout << name << " " << position << cellPhoneNumber << " " << emailAddress
		<< " " << companyName << " " << address <<
		" " << telephoneNumber << " " << faxNumber << " " << url << endl;

	cout << endl << "입력완료" << endl;

	index = businessCardBinder.First();
	BusinessCard *it = index;
	BusinessCard *previous = 0;

	while (previous != it) {
		name = it->GetName();
		position = it->GetPosition();
		cellPhoneNumber = it->GetCellphoneNumber();
		emailAddress = it->GetEmailAddress();
		companyName = it->GetCompanyName();
		address = it->GetAddress();
		telephoneNumber = it->GetTelephoneNumber();
		faxNumber = it->GetFaxNumber();
		url = it->GetUrl();
		cout << name << " " << position << cellPhoneNumber << " " << emailAddress
			<< " " << companyName << " " << address <<
			" " << telephoneNumber << " " << faxNumber << " " << url << endl;
		previous = it;
		it = businessCardBinder.Next();
	}

	cout << endl << endl;

	index = businessCardBinder.Last();
	it = index;
	previous = 0;

	while (previous != it) {
		name = it->GetName();
		position = it->GetPosition();
		cellPhoneNumber = it->GetCellphoneNumber();
		emailAddress = it->GetEmailAddress();
		companyName = it->GetCompanyName();
		address = it->GetAddress();
		telephoneNumber = it->GetTelephoneNumber();
		faxNumber = it->GetFaxNumber();
		url = it->GetUrl();
		cout << name << " " << position << cellPhoneNumber << " " << emailAddress
			<< " " << companyName << " " << address <<
			" " << telephoneNumber << " " << faxNumber << " " << url << endl;
		previous = it;
		it = businessCardBinder.Previous();
	}
	cout << endl << "TakeOut" << endl;

	businessCard = businessCardBinder.TakeOut(index);
	name = businessCard.GetName();
	position = businessCard.GetPosition();
	cellPhoneNumber = businessCard.GetCellphoneNumber();
	emailAddress = businessCard.GetEmailAddress();
	companyName = businessCard.GetCompanyName();
	address = businessCard.GetAddress();
	telephoneNumber = businessCard.GetTelephoneNumber();
	faxNumber = businessCard.GetFaxNumber();
	url = businessCard.GetUrl();
	cout << name << " " << position << cellPhoneNumber << " " << emailAddress
		<< " " << companyName << " " << address <<
		" " << telephoneNumber << " " << faxNumber << " " << url << endl;
	cout << endl;

	cout << endl << "Find" << endl;
	BusinessCard *(*indexes);
	Long count = 0;
	businessCardBinder.Find("김길동", &indexes, &count);
	Long i = 0;
	it = businessCardBinder.First();
	while (i < count) {
		name = indexes[i]->GetName();
		position = indexes[i]->GetPosition();
		cellPhoneNumber = indexes[i]->GetCellphoneNumber();
		emailAddress = indexes[i]->GetEmailAddress();
		companyName = indexes[i]->GetCompanyName();
		address = indexes[i]->GetAddress();
		telephoneNumber = indexes[i]->GetTelephoneNumber();
		faxNumber = indexes[i]->GetFaxNumber();
		url = indexes[i]->GetUrl();
		cout << name << " " << position << cellPhoneNumber << " " << emailAddress
			<< " " << companyName << " " << address <<
			" " << telephoneNumber << " " << faxNumber << " " << url << endl;
		i++;
	}

	cout << endl << "FindByCompanyName" << endl;
	index = businessCardBinder.FindByCompanyName("삼성");
	if (index != 0) {
		companyName = index->GetCompanyName();
		address = index->GetAddress();
		telephoneNumber = index->GetTelephoneNumber();
		faxNumber = index->GetFaxNumber();
		url = index->GetUrl();
		cout << name << " " << position << cellPhoneNumber << " " << emailAddress
			<< " " << companyName << " " << address <<
			" " << telephoneNumber << " " << faxNumber << " " << url << endl;
	}

	cout << endl << "전꺼로 Move" << endl;
	index = businessCardBinder.Move(index);
	name = index->GetName();
	position = index->GetPosition();
	cellPhoneNumber = index->GetCellphoneNumber();
	emailAddress = index->GetEmailAddress();
	companyName = index->GetCompanyName();
	address = index->GetAddress();
	telephoneNumber = index->GetTelephoneNumber();
	faxNumber = index->GetFaxNumber();
	url = index->GetUrl();
	cout << name << " " << position << cellPhoneNumber << " " << emailAddress << endl;

	return 0;
}
*/