#pragma once
#include "ListNode.h"

class CSSBlock {
private:
	/*ListNode<Text>* firstSelector;
	ListNode<Text>* firstAttribute;
	ListNode<Text>* currentSelector;
	ListNode<Text>* currentAttribute;*/
public:
	CSSBlock();
	/*const ListNode<Text>& addSelector();*/
	void addAttribute();
	/*const ListNode<Text>& getEmptyNode();*/
	~CSSBlock();
};