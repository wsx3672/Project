#include "KoreanEnglishChangeKey.h"
#include "TextEdit.h"
#include "Caret.h"
KoreanEnglishChangeKey::KoreanEnglishChangeKey() {
}
KoreanEnglishChangeKey::~KoreanEnglishChangeKey() {
}
KoreanEnglishChangeKey::KoreanEnglishChangeKey(const KoreanEnglishChangeKey& source) {
}
KoreanEnglishChangeKey& KoreanEnglishChangeKey::operator=(const KoreanEnglishChangeKey& source) {
	return *this;
}
void KoreanEnglishChangeKey::Action(TextEdit *textEdit) {
	textEdit->caret->CreateCaret();
}