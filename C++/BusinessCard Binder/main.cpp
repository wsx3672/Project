//main.cpp
#include "Indexes.h"
#include "BusinessCardBinder.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

	BusinessCardBinder businessCardBinder;
	Indexes indexes;

	BusinessCard businessCard("홍길동", "사장", "01011111111", "Hong@", "삼성", "서울시서초구", "021111111", "021111112", "Sang.com");
	BusinessCard *businessCardIndex = businessCardBinder.TakeIn(businessCard);
	Index *index = indexes.TakeIn(businessCardIndex);
	string companyName = index->GetName();
	cout << companyName << endl;
	Long position = index->Find(businessCardIndex);
	BusinessCard *businessCradCheckIndex = index->GetAt(position);



	string name = businessCradCheckIndex->GetName();
	string personalPosition = businessCradCheckIndex->GetPosition();
	string cellphoneNumber = businessCradCheckIndex->GetCellphoneNumber();
	string emailAddress = businessCradCheckIndex->GetEmailAddress();
	companyName = businessCradCheckIndex->GetCompanyName();
	string address = businessCradCheckIndex->GetAddress();
	string telephoneNumber = businessCradCheckIndex->GetTelephoneNumber();
	string faxNumber = businessCradCheckIndex->GetFaxNumber();
	string url = businessCradCheckIndex->GetUrl();


	cout << name << personalPosition << cellphoneNumber << emailAddress << companyName << address << telephoneNumber << faxNumber << url << endl;


	BusinessCard businessCard1("구길동", "과장", "01011111111", "Hong@", "박컴", "서울시서초구", "021111111", "021111112", "Sang.com");
	businessCardIndex = businessCardBinder.TakeIn(businessCard1);
	index = indexes.TakeIn(businessCardIndex);
	companyName = index->GetName();
	cout << companyName << endl;
	position = index->Find(businessCardIndex);
	businessCradCheckIndex = index->GetAt(position);



	name = businessCradCheckIndex->GetName();
	personalPosition = businessCradCheckIndex->GetPosition();
	cellphoneNumber = businessCradCheckIndex->GetCellphoneNumber();
	emailAddress = businessCradCheckIndex->GetEmailAddress();
	companyName = businessCradCheckIndex->GetCompanyName();
	 address = businessCradCheckIndex->GetAddress();
	 telephoneNumber = businessCradCheckIndex->GetTelephoneNumber();
	 faxNumber = businessCradCheckIndex->GetFaxNumber();
	 url = businessCradCheckIndex->GetUrl();
	 cout << name << personalPosition << cellphoneNumber << emailAddress << companyName << address << telephoneNumber << faxNumber << url << endl;

	 BusinessCard businessCard2("김길동", "부장", "01011111111", "Hong@", "기아", "서울시서초구", "021111111", "021111112", "Sang.com");
	 businessCardIndex = businessCardBinder.TakeIn(businessCard2);
	 index = indexes.TakeIn(businessCardIndex);
	 companyName = index->GetName();
	 cout << companyName << endl;
	 position = index->Find(businessCardIndex);
	 businessCradCheckIndex = index->GetAt(position);


	 name = businessCradCheckIndex->GetName();
	 personalPosition = businessCradCheckIndex->GetPosition();
	 cellphoneNumber = businessCradCheckIndex->GetCellphoneNumber();
	 emailAddress = businessCradCheckIndex->GetEmailAddress();
	 companyName = businessCradCheckIndex->GetCompanyName();
	 address = businessCradCheckIndex->GetAddress();
	 telephoneNumber = businessCradCheckIndex->GetTelephoneNumber();
	 faxNumber = businessCradCheckIndex->GetFaxNumber();
	 url = businessCradCheckIndex->GetUrl();

	 cout << name << personalPosition << cellphoneNumber << emailAddress << companyName << address << telephoneNumber << faxNumber << url << endl;

	 BusinessCard businessCard3("정길동", "사원", "01011111111", "Hong@", "박컴", "서울시서초구", "021111111", "021111112", "Sang.com");
	 businessCardIndex = businessCardBinder.TakeIn(businessCard3);
	 index = indexes.TakeIn(businessCardIndex);
	 companyName = index->GetName();
	 cout << companyName << endl;
	 position = index->Find(businessCardIndex);
	 businessCradCheckIndex = index->GetAt(position);

	 name = businessCradCheckIndex->GetName();
	 personalPosition = businessCradCheckIndex->GetPosition();
	 cellphoneNumber = businessCradCheckIndex->GetCellphoneNumber();
	 emailAddress = businessCradCheckIndex->GetEmailAddress();
	 companyName = businessCradCheckIndex->GetCompanyName();
	 address = businessCradCheckIndex->GetAddress();
	 telephoneNumber = businessCradCheckIndex->GetTelephoneNumber();
	 faxNumber = businessCradCheckIndex->GetFaxNumber();
	 url = businessCradCheckIndex->GetUrl();

	 cout << name << personalPosition << cellphoneNumber << emailAddress << companyName << address << telephoneNumber << faxNumber << url << endl;

	  index = indexes.Find(companyName);

	
	 companyName=index->GetName();
	 cout << companyName << endl;
	
	 Long i = 0;
	 Long length = index->GetLength();
	 while (i < length) {
		 name = index->GetAt(i)->GetName();
		 personalPosition = index->GetAt(i)->GetPosition();
		 cellphoneNumber = index->GetAt(i)->GetCellphoneNumber();
		 emailAddress = index->GetAt(i)->GetEmailAddress();
		 companyName = index->GetAt(i)->GetCompanyName();
		 address = index->GetAt(i)->GetAddress();
		 telephoneNumber = index->GetAt(i)->GetTelephoneNumber();
		 faxNumber = index->GetAt(i)->GetFaxNumber();
		 url = index->GetAt(i)->GetUrl();
		 cout << name << personalPosition << cellphoneNumber << emailAddress << companyName << address << telephoneNumber << faxNumber << url << endl;
		 i++;
	 }
	 indexes.Arrange();
	 businessCard = businessCardBinder.TakeOut(businessCardIndex);
	 companyName = businessCard.GetCompanyName();
	 index = indexes.TakeOut(&businessCard, companyName);
	 if (index != 0) {
		 companyName = index->GetName();
		 cout << companyName << endl;
	 }
	 else {
		 cout << "색인이 삭제되었습니다." << endl;
	 }
	 Index(*indexesIndexes);
	 Long count;
	 indexes.MakeList(&indexesIndexes, &count);
	 i = 0;
	 cout << endl;
	 while (i < count) {
		 companyName = indexesIndexes[i].GetName();				//반복확인이 뭐인지 까먹음.
		 cout << companyName << endl;
		 i++;
	 }
	 if (indexesIndexes != 0) {
		 delete []indexesIndexes;
		 indexesIndexes = 0;
	 }
	return 0;
}

