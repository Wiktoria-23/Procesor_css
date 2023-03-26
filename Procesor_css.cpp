#include <iostream>
#include "Text.h"
#include "CSSBlock.h"
#include "ListNode.h"
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

void addSelector(Text& input, ListNode<CSSBlock>& currentNode) {
	ListNode<Text>* newSelector = new ListNode<Text>;
	*(currentNode.getData()->getFirstSelector()->getLastNode()->getData()) = input;
	currentNode.getData()->getFirstSelector()->getLastNode()->setNextNode(newSelector);
	currentNode.getData()->incrementSelectorCounter();
	input.makeEmpty();
}

void addAttribute(Text& input, ListNode<CSSBlock>& currentNode) {
	ListNode<Text>* newAttribute = new ListNode<Text>;
	*(currentNode.getData()->getFirstAttribute()->getLastNode()->getData()) = input;
	currentNode.getData()->getFirstAttribute()->getLastNode()->setNextNode(newAttribute);
	currentNode.getData()->incrementAttributeCounter();
	input.makeEmpty();
}

int main() {
	char character;
	programState currentState = GET_SELECTORS;
	Text input;
	ListNode<CSSBlock> currentNode;
	while (currentState != NOT_ACTIVE) {
		character = getchar();
		if (currentState == GET_SELECTORS) {
			if (character == COMMA) {
				addSelector(input, currentNode);
			}
			else if (character != ATTRIBUTES_START && character != SPACE && character != NEW_LINE) {
				input.newChar(character, input);
			}
			else if (character == ATTRIBUTES_START) {
				addSelector(input, currentNode);
				currentState = GET_ATTRIBUTES;
			}
		}
		else if (currentState == GET_ATTRIBUTES) {
			if (character == SEMICOLON || character == ATTRIBUTES_END) {
				addAttribute(input, currentNode);
			}
			else if (character != ATTRIBUTES_END && character != SPACE && character != NEW_LINE) {
				input.newChar(character, input);
			}
			else if (character == ATTRIBUTES_END) {
				addAttribute(input, currentNode);
				currentNode.incrementCounter();
				currentState = GET_SELECTORS;
			}
		}
	}
	return 0;
}