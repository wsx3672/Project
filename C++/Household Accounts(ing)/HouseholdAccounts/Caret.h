//Caret.h
/*
파일명 : Caret.h
기능 : 텍스트입력시 현재 어느위치에서 작업하는지 보여주기위한 캐럿클래스
작성자 : 박상민
작성일자 : 2017년 12월 6일
*/
#ifndef _CARET_H
#define _CARET_H
typedef signed long int Long;
class TextEdit;
class CFont;
class TextComponent;
typedef signed long int Long;
class Caret {
public:
	Caret(TextEdit *textEdit);
	Caret(const Caret& source);
	~Caret();
	Caret& operator= (const Caret& source);
	void CreateCaret(Long width = 2 ,Long height = 17);
	void ChangeCaretWidth();
	void FontSetting(CFont *font);
	void IncludeDoubleByteCharacter();
	void RightMovingCaret();
	void BackSpaceKeyMovingCaret();
	void NextRowMovingCaret();
	void PreviousRowMovingCaret();
	void LeftArrowKeyMovingCaret();
	void RightArrowKeyMovingCaret();
	void UpArrowKeyMovingCaret();
	void DownArrowKeyMovingCaret();
	void HomeKeyMovingCaret();
	void EndKeyMovingCaret();
	void ShiftAndLeftArrowCaretMoving(TextComponent *textComponent);
	void ShiftAndRightArrowCaretMoving(TextComponent *textComponent);
	Long GetCurrentX() const;
	Long GetCurrentY() const;
	Long GetCurrentRowIndex() const;
	Long SetCurrentX(Long currentX);
	Long SetCurrentY(Long currentY);
	Long SetCurrentRowIndex(Long currentRowIndex);
	Long SetCharacterIndex(Long characterIndex);
	Long GetCharacterIndex() const;
private:
	TextEdit *textEdit;
	Long currentX;
	Long currentY;
	Long currentRowIndex;
	Long characterIndex;
};
inline Long Caret::GetCurrentX() const {
	return this->currentX;
}
inline Long Caret::GetCurrentY() const {
	return this->currentY;
}
inline Long Caret::GetCurrentRowIndex() const {
	return this->currentRowIndex;
}
inline Long Caret::GetCharacterIndex() const {
	return this->characterIndex;
}
#endif // !_CARET_H
