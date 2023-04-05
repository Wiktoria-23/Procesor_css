#include "CSSBlock.h"

CSSBlock::CSSBlock() : selectorCounter(NULL), attributeCounter(NULL) {
	firstSelector = new ListNode<MyString>;
	firstAttribute = new ListNode<Attribute>;
	selectorCounter = 0;
	attributeCounter = 0;
}
ListNode<MyString>* CSSBlock::getFirstSelector() {
	return firstSelector;
}
ListNode<Attribute>* CSSBlock::getFirstAttribute() {
	return firstAttribute;
}
int CSSBlock::getSelectorCounter() const {
	return selectorCounter;
}
int CSSBlock::getAttributeCounter() const {
	return attributeCounter;
}
void CSSBlock::setFirstAttribute(ListNode<Attribute>* newFirstAttribute) {
	this->firstAttribute = newFirstAttribute;
}
void CSSBlock::deleteAllData() {
	firstSelector = firstSelector->deleteAllNextNodes();
	firstSelector->getData()->makeEmpty();
	selectorCounter = 0;
	if (attributeCounter > 0) {
		firstAttribute = firstAttribute->deleteAllNextNodes();
		firstAttribute->getData()->getKey().makeEmpty();
		firstAttribute->getData()->getValue().makeEmpty();
	}
	attributeCounter = 0;
}
void CSSBlock::incrementAttributeCounter() {
	this->attributeCounter += 1;
}
void CSSBlock::incrementSelectorCounter() {
	this->selectorCounter += 1;
}
void CSSBlock::decrementAttributeCounter() {
	this->attributeCounter -= 1;
}
CSSBlock::~CSSBlock() {
	firstSelector->deleteAllNextNodes();
	firstAttribute->deleteAllNextNodes();
	delete firstSelector;
	delete firstAttribute;
}