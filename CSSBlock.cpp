#include "CSSBlock.h"

CSSBlock::CSSBlock() : attributeCounter(NULL), selectorCounter(NULL){
	firstSelector = new ListNode<Text>;
	firstAtrribute = new ListNode<Text>;
}
ListNode<Text>* CSSBlock::getFirstSelector() {
	return firstSelector;
}
ListNode<Text>* CSSBlock::getFirstAttribute() {
	return firstAtrribute;
}
int CSSBlock::getSelectorCounter() {
	return selectorCounter;
}
int CSSBlock::getAttributeCounter() {
	return attributeCounter;
}
CSSBlock::~CSSBlock() {

}