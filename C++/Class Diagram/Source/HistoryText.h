//HistoryText.h

#ifndef _HISTORYTEXT_H
#define _HISTORYTEXT_H

#include "Array.h"

typedef signed long int Long;

class Text;
class Caret;
class HistoryText {
public:
	HistoryText();
	HistoryText(const HistoryText& source);
	~HistoryText();

	void PushUndo(Text *text, Caret *caret);
	Text* PopUndoText();
	Caret* PopUndoCaret();

	void PushRedo(Text *text, Caret *caret);
	Text* PopRedoText();
	Caret* PopRedoCaret();

	Text* GetUndoArray() const;
	Text* GetRedoArray() const;
public:
	Array<Text*>*undoTextArray;
	Array<Text*>*redoTextArray;

	Array<Caret*>*undoCaretArray;
	Array<Caret*>*redoCaretArray;
};

inline Text* HistoryText::GetUndoArray() const {
	// �ʿ��ϸ� �迭 ��ü ���߿�
}
inline Text* HistoryText::GetRedoArray() const {
	// �ʿ��ϸ� �迭 ��ü ���߿�
}

#endif //_HISTORYTEXT_H
