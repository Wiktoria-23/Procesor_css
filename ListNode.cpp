#include <iostream>
#include "ListNode.h"
#define TEXT 1

using namespace std;

template <typename type> ListNode <type>::ListNode() {
	next = nullptr;
	previous = nullptr;
	counter = 0;
	data = new type[TEXT];
}
template <typename type> ListNode <type>::ListNode(int n) {
	next = nullptr;
	previous = nullptr;
	counter = 0;
	data = new type[n];
}
template <typename type> ListNode <type>::ListNode(ListNode& previousNode) {
	ListNode lastNode = getLastNode(previousNode);
	this->setPreviousNode(&previousNode);
	lastNode.setNextNode(this);
}
template <typename type> ListNode <type>::ListNode(const ListNode& node) {
	this->next = node.next;
	this->previous = node.previous;
}
template <typename type> type* ListNode <type>::getData() {
	return data;
}
template <typename type> int ListNode <type>::getCounter() {
	return counter;
}
template <typename type> ListNode <type>* ListNode <type>::getNextNode() {
	return next;
}
template <typename type> const ListNode <type> & ListNode <type>::getLastNode(const ListNode& firstNode) {
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
template <typename type> void ListNode <type>::setPreviousNode(ListNode* previousNode) {
	this->previous = previousNode;
}
template <typename type> void ListNode <type>::setNextNode(ListNode* nextNode) {
	this->next = nextNode;
}
template <typename type> ListNode <type>::~ListNode() {

}