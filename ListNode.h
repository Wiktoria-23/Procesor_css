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
		int deletedCounter = NULL;
		int currentIndex = NULL;
		while (currentIndex != (index + deletedCounter)) {
			if ((data + currentIndex)->getSelectorCounter() == NULL && (data + currentIndex)->getAttributeCounter() == NULL) {
				deletedCounter += 1;
			}
			currentIndex += 1;
		}
		if ((data + currentIndex)->getSelectorCounter() == NULL && (data + currentIndex)->getAttributeCounter() == NULL) {
			deletedCounter += 1;
		}
		if (currentIndex < T) {
			return data + index + deletedCounter;
		}
		else {
			return data;
		}
	}
	type* getCurrentIndexData() {
		return data + counter;
	}
	type* getData() {
		return data;
	}
	int getCounter() const {
		return counter;
	}
	ListNode* getNextNode() {
		return next;
	}
	ListNode* getPreviousNode() {
		return previous;
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
		while (number > T) {
			number -= tmp->getCounter();
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
	void setPreviousNode(ListNode* previousNode) {
		this->previous = previousNode;
	}
	void setNextNode(ListNode* nextNode) {
		this->next = nextNode;
	}
	void setCounter(int number) {
		counter = number;
	}
	void incrementCounter() {
		counter += 1;
	}
	void decrementCounter() {
		counter -= 1;
	}
	ListNode* deleteAllNextNodes() {
		ListNode<type>* tmp = this->getLastNode();
		while (tmp->getPreviousNode() != nullptr) {
			tmp = tmp->getPreviousNode();
			tmp->getNextNode()->~ListNode();
			tmp->setNextNode(nullptr);
		}
		return tmp;
	}
	void deleteNode() {
		if (this->getPreviousNode() != nullptr) {
			this->getPreviousNode()->setNextNode(this->getNextNode());
		}
		if (this->getNextNode() != nullptr) {
			this->getNextNode()->setPreviousNode(this->getPreviousNode());
		}
		this->~ListNode();
	}
	~ListNode() {
		next = nullptr;
		previous = nullptr;
		/*if (data != nullptr) {
			delete[] data;
		}*/ //naprawic to, zeby dzialal test trzeci !!!
	}
};