#include "CSSBlock.h"

CSSBlock::CSSBlock() : attributeCounter(NULL), selectorCounter(NULL){
	firstSelector = new ListNode<Text>;
	firstAttribute = new ListNode<Text>;
	selectorCounter = 0;
	attributeCounter = 0;
}
ListNode<Text>* CSSBlock::getFirstSelector() {
	return firstSelector;
}
ListNode<Text>* CSSBlock::getFirstAttribute() {
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