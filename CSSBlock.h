#pragma once
#include "ListNode.h"
#include "MyString.h"
#define TEXT 1

class CSSBlock {
private:
	ListNode<MyString>* firstSelector;
	ListNode<MyString>* firstAttribute;
	int selectorCounter;
	int attributeCounter;
public:
	CSSBlock();
	ListNode<MyString>* getFirstSelector();
	ListNode<MyString>* getFirstAttribute();
	int getSelectorCounter();
	int getAttributeCounter();
	void incrementSelectorCounter();
	void incrementAttributeCounter();
	~CSSBlock();
};