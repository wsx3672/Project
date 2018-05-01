#include "WritingKorean.h"
#include "TextEdit.h"
#include "WriteKoreanTextProcess.h"
#include "Caret.h"
WritingKorean::WritingKorean() {
}
WritingKorean::~WritingKorean() {
}
WritingKorean::WritingKorean(const WritingKorean& source) {
}
WritingKorean& WritingKorean::operator=(const WritingKorean& source) {
	return *this;
}
void WritingKorean::WritingHanguel(WPARAM wParam, LPARAM lParam, HIMC hIMC, TextEdit *textEdit) {
	Long bufferLength = 0;
	char buffer[8];
	WriteKoreanTextProcess writeKoreanTextProcess;
	
	if (lParam & GCS_RESULTSTR) { // 조합 끝 
		bufferLength = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);
		ImmGetCompositionString(hIMC, GCS_RESULTSTR, buffer, bufferLength);
		writeKoreanTextProcess.EndComposition(textEdit, bufferLength, buffer);
		textEdit->caret->RightMovingCaret(); 
	}
	else if (lParam & GCS_COMPSTR) { 
		bufferLength = ImmGetCompositionString(hIMC, GCS_COMPSTR, NULL, 0);
		ImmGetCompositionString(hIMC, GCS_COMPSTR, buffer, bufferLength);
		if (textEdit->writingKoreanState == false) { //조합 시작일때 
			writeKoreanTextProcess.StartComposition(textEdit, bufferLength, buffer); 
		}
		else {
			//조합중일때
			writeKoreanTextProcess.DuringComposition(textEdit, bufferLength, buffer);
		}
		if ( bufferLength != 0) {
			textEdit->caret->IncludeDoubleByteCharacter();
		}
	}
}