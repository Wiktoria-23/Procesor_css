#pragma once
#include "ListNode.h"
#include "MyString.h"
#include "Attribute.h"
#define TEXT 1

class CSSBlock {
private:
	ListNode<MyString>* firstSelector;
	ListNode<Attribute>* firstAttribute;
	int selectorCounter;
	int attributeCounter;
public:
	CSSBlock();
	ListNode<MyString>* getFirstSelector();
	ListNode<Attribute>* getFirstAttribute();
	int getSelectorCounter();
	int getAttributeCounter();
	void incrementSelectorCounter();
	void incrementAttributeCounter();
	~CSSBlock();
};