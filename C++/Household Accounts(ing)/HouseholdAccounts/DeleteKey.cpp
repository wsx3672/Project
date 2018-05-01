#include "DeleteKey.h"
#include "TextEdit.h"
#include "DeleteKeyProcess.h"
DeleteKey::DeleteKey() {
}
DeleteKey::~DeleteKey() {
}
DeleteKey::DeleteKey(const DeleteKey& source) {
}
DeleteKey& DeleteKey::operator=(const DeleteKey& source) {
	return *this;
}
void DeleteKey::Action(TextEdit *textEdit) {
	DeleteKeyProcess deleteKeyProcess;
	if (textEdit->selectedArea == false) {
		deleteKeyProcess.Delete(textEdit);
	}
	else {
		deleteKeyProcess.SelectionDelete(textEdit);
	}
}