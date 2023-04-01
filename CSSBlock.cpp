#include "CSSBlock.h"

CSSBlock::CSSBlock() : attributeCounter(NULL), selectorCounter(NULL){
	firstSelector = new ListNode<MyString>;
	firstAttribute = new ListNode<MyString>;
	selectorCounter = 0;
	attributeCounter = 0;
}
ListNode<MyString>* CSSBlock::getFirstSelector() {
	return firstSelector;
}
ListNode<MyString>* CSSBlock::getFirstAttribute() {
	return firstAttribute;
}
int CSSBlock::getSelectorCounter() {
	return selectorCounter;
}
int CSSBlock::getAttributeCounter() {
	return attributeCounter;
}
void CSSBlock::incrementAttributeCounter() {
	this->attributeCounter += 1;
}
void CSSBlock::incrementSelectorCounter() {
	this->selectorCounter += 1;
}
CSSBlock::~CSSBlock() {
	delete firstSelector;
	delete firstAttribute;
}