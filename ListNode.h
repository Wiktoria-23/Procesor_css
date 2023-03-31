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
	ListNode(const ListNode<type>& node) {
		this->next = node.next;
		this->previous = node.previous;
	}
	type* getDataFromIndex(int index) {
		return data + index;
	}
	type* getCurrentIndexData() {
		return data + counter;
	}
	type* getData() {
		return data;
	}
	int getCounter() {
		return counter;
	}
	ListNode* getLastNode() {
		if (next == nullptr) {
			return this;
		}
		else {
			ListNode* tmp = this;
			while (tmp->next != nullptr) {
				tmp = tmp->next;
			}
			return tmp;
		}
	}
	ListNode* getFirstNode() {
		if (previous == nullptr) {
			return this;
		}
		else {
			ListNode* tmp = this;
			while (tmp->previous != nullptr) {
				tmp = tmp->previous;
			}
			return tmp;
		}
	}
	ListNode* findNodeByNumberT(int number) {
		ListNode<type>* tmp = this->getFirstNode();
		int nodeNumber = floor(number / T);
		int nodeCounter = 1;
		while (nodeCounter < nodeNumber) {
			nodeCounter += 1;
			tmp = tmp->getNextNode();
		}
		return tmp;
	}
	ListNode* findNodeByNumber(int number) {
		ListNode<type>* tmp = this->getFirstNode();
		int nodeCounter = 1;
		while (nodeCounter < number) {
			nodeCounter += 1;
			tmp = tmp->getNextNode();
			if (tmp == nullptr) {
				break;
			}
		}
		return tmp;
	}
	ListNode* getNextNode() {
		return next;
	}
	void setPreviousNode(ListNode* previousNode) {
		this->previous = previousNode;
	}
	void setNextNode(ListNode* nextNode) {
		this->next = nextNode;
	}
	void incrementCounter() {
		counter += 1;
	}
	~ListNode() {
		delete[] data;
	}
};