#include <iostream>
#include "Text.h"
#include "CSSBlock.h"
#include "ListNode.h"
#define BUFFER 30
#define ATTRIBUTES_START '{'
#define ATTRIBUTES_END '}'
#define SPACE ' '
#define COMMA ','
#define NEW_LINE '\n'
#define SEMICOLON ';'

enum programState {
	GET_SELECTORS = 0,
	GET_ATTRIBUTES = 1,
	GET_COMMANDS = 2,
	NOT_ACTIVE = 3,
};

using namespace std;

int addSelector(char* input, ListNode<CSSBlock>& currentNode, int charactersCount) {
	ListNode<Text>* newSelector = new ListNode<Text>;
	currentNode.getData()->getFirstSelector()->getLastNode()->getData()->changeText(input, charactersCount);
	currentNode.getData()->getFirstSelector()->getLastNode()->setNextNode(newSelector);
	currentNode.getData()->incrementSelectorCounter();
	charactersCount = NULL;
	return charactersCount;
}

int addAttribute(char* input, ListNode<CSSBlock>& currentNode, int charactersCount) {
	ListNode<Text>* newAttribute = new ListNode<Text>;
	currentNode.getData()->getFirstAttribute()->getLastNode()->getData()->changeText(input, charactersCount);
	currentNode.getData()->getFirstAttribute()->getLastNode()->setNextNode(newAttribute);
	currentNode.getData()->incrementAttributeCounter();
	charactersCount = NULL;
	return charactersCount;
}

int main() {
	char character;
	programState currentState = GET_SELECTORS;
	char* input = new char[BUFFER];
	int charactersCount = NULL;
	ListNode<CSSBlock> currentNode;
	while (currentState != NOT_ACTIVE) {
		character = getchar();
		if (currentState == GET_SELECTORS) {
			if (character == COMMA) {
				charactersCount = addSelector(input, currentNode, charactersCount);
			}
			else if (character != ATTRIBUTES_START && character != NEW_LINE) {
				input[charactersCount] = character;
				charactersCount += 1;
			}
			if (character == ATTRIBUTES_START) {
				charactersCount = addSelector(input, currentNode, charactersCount);
				currentState = GET_ATTRIBUTES;
			}
		}
		else if (currentState == GET_ATTRIBUTES) {
			if (character == SEMICOLON || character == ATTRIBUTES_END) {
				charactersCount = addAttribute(input, currentNode, charactersCount);
			}
			else if (character != ATTRIBUTES_END && character != NEW_LINE) {
				input[charactersCount] = character;
				charactersCount += 1;
			}
			if (character == ATTRIBUTES_END) {
				charactersCount = addAttribute(input, currentNode, charactersCount);
				currentNode.incrementCounter();
				currentState = GET_SELECTORS;
			}
		}
	}
	return 0;
}