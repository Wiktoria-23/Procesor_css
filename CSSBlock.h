#pragma once
#include "ListNode.h"
#include "Text.h"
#define TEXT 1

class CSSBlock {
private:
	ListNode<Text>* firstSelector;
	ListNode<Text>* firstAttribute;
	int selectorCounter;
	int attributeCounter;
public:
	CSSBlock();
	ListNode<Text>* getFirstSelector();
	ListNode<Text>* getFirstAttribute();
	int getSelectorCounter();
	int getAttributeCounter();
	void incrementSelectorCounter();
	void incrementAttributeCounter();
	~CSSBlock();
};