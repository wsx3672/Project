//Personal.h

//가드선언
#ifndef _PERSONAL_H
#define _PERSONAL_H
#include <string>
using namespace std;

//자료형설계
class Personal {
public:
	Personal(); //디폴트 생성자
	Personal(string name, string address, string telephoneNumber, string emailAddress); //매개변수4개 생성자
	Personal(const Personal& source); //복사생성자
	~Personal(); //소멸자

	bool IsEqual(const Personal& other); // 비교연산
	bool IsNotEqual(const Personal& other);

	Personal& operator = (const Personal& source); //치환연산자

	bool operator == (const Personal& source); // 비교연산자
	bool operator != (const Personal& source);

	string& GetName() const;
	string& GetAddress() const;
	string& GetTelephoneNumber() const;
	string& GetEmailAddress() const;
private:
	string name;
	string address;
	string telephoneNumber;
	string emailAddress;
};
inline string& Personal::GetName() const {
	return const_cast<string&>(this->name);
}
inline string& Personal::GetAddress() const {
	return const_cast<string&>(this->address);
}
inline string& Personal::GetTelephoneNumber() const {
	return const_cast<string&>(this->telephoneNumber);
}
inline string& Personal::GetEmailAddress() const {
	return const_cast<string&>(this->emailAddress);
}

#endif // _PERSONAL_H