#pragma once
#define T 8
#include "CSSBlock.h"
#include "Text.h"

template <typename type> class ListNode {
private:
	ListNode* previous;
	ListNode* next;
	type* data;
	int counter;
public:
	ListNode();
	ListNode(int n);
	ListNode(ListNode& previousNode);
	ListNode(const ListNode& node);
	type* getData();
	int getCounter();
	const ListNode& getLastNode(const ListNode& firstNode);
	virtual ListNode* getNextNode();
	void setPreviousNode(ListNode* previousNode);
	void setNextNode(ListNode* nextNode);
	~ListNode();
};