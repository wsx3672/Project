//Form.h
#ifndef _FORM_H
#define _FORM_H
#include "WordBook.h"

class WordBook;
class Form {
public:
	void DisplayMenu();   // �޴�
	void FormForRecording(WordBook& wordBook);   // [1] �����ϱ�
	void FormForFinding(WordBook& wordBook);      // [2] ã��
	void FormForCorrecting(WordBook& wordBook);   // [3] ��ġ��
	void FormForErasing(WordBook& wordBook);      // [4] �����
	void FormForArranging(WordBook& wordBook);   // [5] �����ϱ�
	void FormForViewAll(WordBook& wordBook);      // [6] ��ü����
private:
	WordBook wordBook;
};
#endif //_FORM_H