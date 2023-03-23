#pragma once
#include "ListNode.h"
#include "Text.h"
#define TEXT 1

class CSSBlock {
private:
	ListNode<Text> node;
public:
	CSSBlock();
	void addSelectors();
	void addAttributes();
	~CSSBlock();
};