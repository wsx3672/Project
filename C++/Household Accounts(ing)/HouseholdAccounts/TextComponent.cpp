#include "TextComponent.h"

TextComponent::TextComponent() {
}
TextComponent::~TextComponent() {
}
TextComponent::TextComponent(const TextComponent& source) {
}
TextComponent& TextComponent::operator= (const TextComponent& source) {
	return *this;
}
TextComposite* TextComponent::GetComposite() {
	return 0;
}
Long TextComponent::Add(TextComponent *textComponent) {
	return -1;
}
Long TextComponent::Remove(TextComponent *textComponent) {
	return 0;
}
Long TextComponent::Insert(Long index, TextComponent *textComponent) {
	return -1;
}