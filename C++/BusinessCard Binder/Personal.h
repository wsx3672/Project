#pragma once
//Personal.h
#ifndef _PERSONAL_H
#define _PERSONAL_H
#include <string>
using namespace std;

class Personal {
public:
	Personal();
	Personal(string name, string position, string telephoneNumber, string emailAddress);
	Personal(const Personal& source);
	~Personal();
	Personal& operator =(const Personal& source);
	bool operator == (const Personal& source);
	bool operator != (const Personal& source);
	bool IsEqual(const Personal& other);
	bool IsNotEqual(const Personal& other);

	string& GetName() const;
	string& GetPosition() const;
	string& GetTelephoneNumber() const;
	string& GetEmailAddress() const;
private:
	string name;
	string position;
	string telephoneNumber;
	string emailAddress;
};
inline string& Personal::GetName() const {
	return const_cast<string&>(this->name);
}
inline string& Personal::GetPosition() const {
	return const_cast<string&>(this->position);
}
inline string& Personal::GetTelephoneNumber() const {
	return const_cast<string&>(this->telephoneNumber);
}
inline string& Personal::GetEmailAddress() const {
	return const_cast<string&>(this->emailAddress);
}
#endif // !_PERSONAL_H

