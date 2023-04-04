#include "CSSBlock.h"
#define DELETED "DELETED"

CSSBlock::CSSBlock() : attributeCounter(NULL), selectorCounter(NULL){
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
int CSSBlock::getSelectorCounter() {
	return selectorCounter;
}
int CSSBlock::getAttributeCounter() {
	return attributeCounter;
}
void CSSBlock::setFirstAttribute(ListNode<Attribute>* newFirstAttribute) {
	this->firstAttribute = newFirstAttribute;
}
void CSSBlock::deleteAllData() {
	ListNode<MyString>* tmp = firstSelector->getLastNode();
	tmp = tmp->deleteAllNextNodes();
	tmp->getData()->makeEmpty();
	tmp->getData()->changeText(DELETED);//poprawiæ usuwanie
	selectorCounter = 0;
	ListNode<Attribute>* tmp2 = firstAttribute->getLastNode();//ostatni atrybut nie ma nullptr - problem z usuwaniem atrybutu
	if (attributeCounter > 0) {
		tmp2 = tmp2->deleteAllNextNodes();
		tmp2->getData()->getKey().changeText(DELETED);
		tmp2->getData()->getValue().changeText(DELETED);
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