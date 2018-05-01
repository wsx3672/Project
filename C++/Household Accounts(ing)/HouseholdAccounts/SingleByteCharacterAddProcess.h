//SingleByteCharacterAddProcess.h
/*
���ϸ� : SingleByteCharacterAddProcess.h
��� : 1����Ʈ char�� �ڷᱸ���� Add���ִ� Ŭ����
�ۼ��� : �ڻ��
�ۼ����� : 2017�� 12�� 26��
*/
#ifndef _SINGLEBYTECHARACTERADDPROCESS_H
#define _SINGLEBYTECHARACTERADDPROCESS_H

typedef signed long int Long;
class TextEdit;
class SingleByteCharacterAddProcess {
public:
	SingleByteCharacterAddProcess();
	~SingleByteCharacterAddProcess();
	SingleByteCharacterAddProcess(const SingleByteCharacterAddProcess& source);

	Long SingleByteCharacterAdd(char addChar, TextEdit *textEdit);
};
#endif // !_SINGLEBYTECHARACTERADDPROCESS_H

