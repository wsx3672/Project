//Form.cpp

#include "wordBook.h"
#include "Form.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

// ���θ޴�
// ���θ޴�
void Form::DisplayMenu() {
	system("cls");
	cout << "\n\n\n\n\n" << endl;
	cout << "\t\t\t  �ּҷ� Version 1.00" << endl;
	cout << "\t\t\t  =============================" << endl;
	cout << "\t\t\t  [1] �����ϱ�" << endl;
	cout << "\t\t\t  [2] ã    ��" << endl;
	cout << "\t\t\t  [3] �� ġ ��" << endl;
	cout << "\t\t\t  [4] �� �� ��" << endl;
	cout << "\t\t\t  [5] �����ϱ�" << endl;
	cout << "\t\t\t  [6] ��ü����" << endl;
	cout << "\t\t\t  [0] �� �� ��" << endl;
	cout << "\t\t\t  -----------------------------" << endl;
	cout << "\t\t\t  �޴��� �����Ͻʽÿ�. " << endl;
	cout << "\t\t\t  ";
}
// [1] �����ϱ�
void  Form::FormForRecording(WordBook& wordBook)
{
	string spelling;
	string meaning;
	string wordClass;
	string example;
	Word word;
	char recording;
	char going = 'Y';
	Long index;
	while (going == 'Y' || going == 'y') {
		system("cls");

		cout << "\n\n\n" << endl;
		cout << "\t\t       �ּҷ� Version 1.00 -�����ϱ�" << endl;
		cout << "\t\t       =============================" << endl;
		cout << "\t\t       �� �� �� : "; cin >> spelling;
		cout << "\t\t       ��    �� : "; cin >> meaning;
		cout << "\t\t       ǰ    �� : "; cin >> wordClass; cin.ignore();
		cout << "\t\t       ��    �� : "; getline(cin, example, '\n');
		cout << "\t\t       -----------------------------" << endl;
		cout << "\t\t       �����Ͻðڽ��ϱ�? (Yes/No) "; recording = getchar();
		if (recording == 'Y' || recording == 'y') {
			index = wordBook.Record(spelling, meaning, wordClass, example);
			word = wordBook.GetAt(index);
			cout << "\t    =======================================================" << endl;
			cout << "\t    ��ȣ\t�ܾ�\t�ǹ�\tǰ��\t����" << endl;
			cout << "\t    -------------------------------------------------------" << endl;
			cout << "\t    " << index + 1 << "\t\t";
			cout << word.GetSpelling() << "\t";
			cout << word.GetMeaning() << "\t";
			cout << word.GetWordClass() << "\t";
			cout << word.GetExample() << "\t" << endl;
		}
		cout << "\t    =======================================================" << endl; cin.ignore();
		cout << "\t    ����Ͻðڽ��ϱ�? (Yes/No) "; going = getchar();
	}
}

// [2] ã    ��
void Form::FormForFinding(WordBook& wordBook)
{
	string spelling;
	char going = 'Y';
	Word word;
	Long(*indexes);
	Long count;
	Long i = 0;
	Long index;
	while (going == 'Y' || going == 'y') {
		system("cls");
		cout << "\n\n\n" << endl;
		cout << "\t\t       �ܾ��� Version 0.05 -ã    ��" << endl;
		cout << "\t\t       =============================" << endl;
		cout << "\t\t       �� �� �� : "; cin >> spelling;
		cout << "\t    =======================================================" << endl;
		wordBook.Find(spelling, &indexes, &count);
		cout << "\t    ��ȣ\t�ܾ�\t�ǹ�\tǰ��\t����" << endl;
		cout << "\t    -------------------------------------------------------" << endl;
		while (i < count) {
			index = indexes[i];
			word = wordBook.GetAt(index);
			cout << "\t    " << i + 1 << "\t\t";
			cout << word.GetSpelling() << "\t";
			cout << word.GetMeaning() << "\t";
			cout << word.GetWordClass() << "\t";
			cout << word.GetExample() << "\t" << endl;
			i++;
		}
		if (indexes != 0) { //�Ҵ�����
			delete[] indexes;
			indexes = 0;
		}
		cout << "\t    =======================================================" << endl; cin.ignore();
		cout << "\t    ����Ͻðڽ��ϱ�? (Yes/No) ";  going = cin.get(); //���࿩�θ� �Է¹޴´�.
	}
}

// [3] �� ġ ��
void Form::FormForCorrecting(WordBook& wordBook)
{
	string spelling;
	string meaning;
	string wordClass;
	string example;
	char correcting;
	char going = 'Y';
	Long number;
	Long(*indexes);
	Long count;
	Word word;
	Long index;
	Long i = 0;
	while (going == 'Y' || going == 'y') {
		system("cls");
		cout << "\n" << endl;
		cout << "\t\t       �ܾ��� Version 1.00 -�� ġ ��" << endl;
		cout << "\t\t       =============================" << endl;
		cout << "\t\t       �� �� �� : "; cin >> spelling;
		wordBook.Find(spelling, &indexes, &count); //Find�Լ��� ȣ���Ѵ�.
		if (count > 0) {
			cout << "\t    -------------------------------------------------------" << endl;
			cout << "\t    ��ȣ\t�ܾ�\t�ǹ�\tǰ��\t����" << endl;
			cout << "\t    =======================================================" << endl;
			while (i < count) {
				index = indexes[i];
				word = wordBook.GetAt(index);
				cout << "\t    " << i + 1 << "\t\t";
				cout << word.GetSpelling() << "\t";
				cout << word.GetMeaning() << "\t";
				cout << word.GetWordClass() << "\t";
				cout << word.GetExample() << "\t" << endl;
				i++;
			}
			cout << "\t    -------------------------------------------------------" << endl;
			cout << "\t    ��    ȣ : "; cin >> number; //��ĥ �ٹ�ȣ�� ��ȣ�� �Է¹޴´�.
			index = indexes[number - 1];
			word = wordBook.GetAt(index);
			cout << "\t    ��    �� (" << word.GetMeaning() << ") : "; cin >> meaning; //�ּҸ� �Է¹޴´�.
			if (meaning == "") { //�Է°��� ������ ���������� �����Ѵ�.
				meaning = word.GetMeaning();
			}
			cout << "\t    ǰ    �� (" << word.GetWordClass() << ") : "; cin >> wordClass; //�ּҸ� �Է¹޴´�.
			if (wordClass == "") { //�Է°��� ������ ���������� �����Ѵ�.
				wordClass = word.GetWordClass();
			}
			cout << "\t    ��    �� (" << word.GetExample() << ") : "; cin >> example; //�ּҸ� �Է¹޴´�.
			if (example == "") { //�Է°��� ������ ���������� �����Ѵ�.
				example = word.GetExample();
			}

			cout << "\t    -------------------------------------------------------" << endl;
			cout << "\t    ��ġ�ðڽ��ϱ�? (Yes/No) "; cin.ignore(); correcting = getchar(); //���࿩�θ� �Է¹޴´�.
			if (correcting == 'Y' || correcting == 'y') {
				wordBook.Correct(index, meaning, wordClass, example); //Correct�Լ��� ȣ���Ѵ�.
				cout << "\t    -------------------------------------------------------" << endl;
				cout << "\t    ��ȣ\t�ܾ�\t�ǹ�\tǰ��\t����" << endl;
				cout << "\t    -------------------------------------------------------" << endl;
				cout << "\t    " << index + 1;
				word = wordBook.GetAt(index);
				cout << "\t    " << word.GetSpelling() << "\t" << word.GetMeaning() << "\t" << word.GetWordClass() << "\t" << word.GetExample() << endl;
			}
		}
		if (indexes != 0) { //�Ҵ�����
			delete[] indexes;
			indexes = 0;
		}
		cout << "\t    =======================================================" << endl; cin.ignore();
		cout << "\t    ����Ͻðڽ��ϱ�? (Yes/No) "; going = getchar(); //���࿩�θ� �Է¹޴´�.
	}
}

// [4] �� �� ��
void Form::FormForErasing(WordBook& wordBook)
{
	string spelling;
	Word word;
	char erasing;
	char going = 'Y';
	Long number;
	while (going == 'Y' || going == 'y') {
		system("cls");
		cout << "\n\n\n" << endl;
		cout << "\t\t  �ּҷ� Version 0.05 -�� �� ��" << endl;
		cout << "\t\t  =============================" << endl;
		cout << "\t\t  ��    ȣ : "; cin >> number; //���� �ٹ�ȣ�� ��ȣ�� �Է¹޴´�.
		cout << "\t\t  -----------------------------" << endl;
		word = wordBook.GetAt(number - 1);
		cout << "\t\t  �ܾ�\t�ǹ�\tǰ��\t����" << endl;
		cout << "\t\t  -----------------------------" << endl;
		cout << "\t\t  " << word.GetSpelling() << "\t" << word.GetMeaning() << "\t" << word.GetWordClass() << "\t" << word.GetExample() << endl;
		cout << "\t\t  -----------------------------" << endl;
		cout << "\t\t  ����ðڽ��ϱ�? (Yes/No) "; cin.ignore(); erasing = getchar();  //���࿩�θ� �Է¹޴´�.
		if (erasing == 'Y' || erasing == 'y') {
			wordBook.Erase(number - 1); //Erase�Լ��� ȣ���Ѵ�.
			cout << "\t\t  =============================" << endl;
			cout << "\t\t  ���������ϴ�." << endl;
		}


		cout << "\t\t  =============================" << endl; cin.ignore();
		cout << "\t\t  ����Ͻðڽ��ϱ�? (Yes/No) "; going = getchar();
	}
}

// [5] �����ϱ�
void Form::FormForArranging(WordBook& wordBook)
{
	Word word;
	Long index = 0;
	Long i;
	wordBook.Arrange(); //Arrange�Լ��� ȣ���Ѵ�.
	while (index < wordBook.GetLength()) { //�ٹ�ȣ�� �ּҷ��� ��뷮���� ����������
		system("cls");
		cout << "\n\n\n" << endl;
		cout << "\t    �ּҷ� Version 0.05 -�����ϱ�" << endl;
		cout << "\t    -------------------------------------------------------" << endl;
		cout << "\t    ��ȣ\t�ܾ�\t�ǹ�\tǰ��\t����" << endl;
		cout << "\t    -------------------------------------------------------" << endl;
		i = 1;
		while (i <= 5 && index < wordBook.GetLength()) { // 5�پ� ����ϱ����� �ݺ���
			word = wordBook.GetAt(index);
			cout << "\t    " << index + 1;
			cout << "\t\t" << word.GetSpelling() << "\t" << word.GetMeaning() << "\t" << word.GetWordClass() << "\t" << word.GetExample() << endl;
			i++;
			index++;
		}
		cout << "\t    =======================================================" << endl; cin.ignore();
		cout << "\t    �ƹ�Ű�� �����ÿ�. " << endl; getchar(); //�ƹ�Ű�� �Է¹޴´�.
	}
}

// [6] ��ü����
void Form::FormForViewAll(WordBook& wordBook)
{
	Word word;
	Long index = 0;
	Long i;

	while (index < wordBook.GetLength()) {//�ٹ�ȣ�� �ּҷ��� ��뷮���� ����������
		system("cls");
		cout << "\n\n\n" << endl;
		cout << "\t    �ּҷ� Version 0.05 - ��ü����" << endl;
		cout << "\t    -------------------------------------------------------" << endl;
		cout << "\t    ��ȣ\t�ܾ�\t�ǹ�\tǰ��\t����" << endl;
		cout << "\t    -------------------------------------------------------" << endl;
		i = 1;
		while (i <= 5 && index < wordBook.GetLength()) { // 5�پ� ����ϱ����� �ݺ���
			word = wordBook.GetAt(index);
			cout << "\t    " << index + 1 << "\t\t" << word.GetSpelling() << "\t" // spelling ���
				<< word.GetMeaning() << "\t" <<
				word.GetWordClass() << "\t" <<
				word.GetExample() << endl; // �ּҷ��� ���ڵ���� ����Ѵ�.
			i++;
			index++;
		}
		cout << "\t    =======================================================" << endl; cin.ignore();
		cout << "\t    �ƹ�Ű�� �����ÿ�. " << endl; cin.get(); //�ƹ�Ű�� �Է¹޴´�.
	}
}