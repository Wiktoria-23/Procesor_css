#pragma once
#define T 8
#define TEXT 1
#include <iostream>

template <typename type> class ListNode {
private:
	ListNode* previous;
	ListNode* next;
	type* data;
	int counter;
public:
	ListNode() : previous(nullptr), next(nullptr), counter(NULL) {
		data = new type[TEXT];
	}
	ListNode(int n) : previous(nullptr), next(nullptr), counter(NULL) {
		data = new type[n];
	}
	ListNode(ListNode<type>& previousNode) {
		ListNode lastNode = getLastNode(previousNode);
		this->setPreviousNode(&previousNode);
		lastNode.setNextNode(this);
	}
	ListNode(const ListNode<type>& node) {
		this->next = node.next;
		this->previous = node.previous;
	}
	type* getData() {
		return data;
	}
	int getCounter() {
		return counter;
	}
	const ListNode& getLastNode(const ListNode<type>& firstNode) {
		if (firstNode.next == nullptr) {
			return firstNode;
		}
		else {
			ListNode tmp = firstNode;
			while (tmp.next != nullptr) {
				tmp = *(tmp.next);
			}
		}
	}
	virtual ListNode* getNextNode() {
		return next;
	}
	void setPreviousNode(ListNode* previousNode) {
		this->previous = previousNode;
	}
	void setNextNode(ListNode* nextNode) {
		this->next = nextNode;
	}
	~ListNode() {

	}
};