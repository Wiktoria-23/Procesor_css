#include <iostream>
#include "Text.h"
#include "CSSBlock.h"
#include "ListNode.h"
#define BUFFER 30
#define SPECIAL_COMMAND_LENGTH 4
#define ATTRIBUTES_START '{'
#define ATTRIBUTES_END '}'
#define SPACE ' '
#define COMMA ','
#define NEW_LINE '\n'
#define SEMICOLON ';'
#define EMPTY ""
#define COMMANDS_START "????"
#define READ_CSS "****"
#define QUESTION_MARK '?'
#define ASTERISK '*'

enum programState {
	GET_SELECTORS = 0,
	GET_ATTRIBUTES = 1,
	GET_COMMANDS = 2,
	NOT_ACTIVE = 3,
};

using namespace std;

bool checkInput(char* input, char toFind) {
	for (int i = 0; i < SPECIAL_COMMAND_LENGTH; i++) {
		if (input[i] != toFind) {
			return false;
		}
	}
	return true;
}

char* clearInput(char* input, int charactersCount) {
	for (int i = 0; i < charactersCount; i++) {
		input[i] = SPACE;
	}
	return input;
}

int addSelector(char* input, ListNode<CSSBlock>& currentNode, int charactersCount) {
	if (currentNode.getData()->getFirstSelector()->getNextNode() == nullptr && currentNode.getData()->getFirstSelector()->getData()->getText() == EMPTY) {
		ListNode<Text>* newSelector = new ListNode<Text>;
		currentNode.getData()->getFirstSelector()->getLastNode()->setNextNode(newSelector);
	}
	currentNode.getData()->getFirstSelector()->getLastNode()->getData()->changeText(input, charactersCount);
	currentNode.getData()->incrementSelectorCounter();
	clearInput(input, charactersCount);
	charactersCount = NULL;
	return charactersCount;
}

int addAttribute(char* input, ListNode<CSSBlock>& currentNode, int charactersCount) {
	if (currentNode.getData()->getFirstAttribute()->getNextNode() == nullptr && currentNode.getData()->getFirstAttribute()->getData()->getText() == EMPTY) {
		ListNode<Text>* newAttribute = new ListNode<Text>;
		currentNode.getData()->getFirstAttribute()->getLastNode()->setNextNode(newAttribute);
	}
	currentNode.getData()->getFirstAttribute()->getLastNode()->getData()->changeText(input, charactersCount);
	currentNode.getData()->incrementAttributeCounter();
	clearInput(input, charactersCount);
	charactersCount = NULL;
	return charactersCount;
}

int main() {
	char character;
	programState currentState = GET_SELECTORS;
	char* input = new char[BUFFER];
	int charactersCount = NULL;
	ListNode<CSSBlock> currentNode(T);
	while (currentState != NOT_ACTIVE) {
		character = getchar();
		if (currentState == GET_SELECTORS) {
			if (character == COMMA || character == ATTRIBUTES_START) {
				if (currentNode.getCounter() >= T) {
					ListNode<CSSBlock> newNode(T);
					currentNode.setNextNode(&newNode);
					currentNode = *currentNode.getNextNode();
				}
				charactersCount = addSelector(input, currentNode, charactersCount);
			}
			else if (character != ATTRIBUTES_START && character != NEW_LINE) {
				input[charactersCount] = character;
				charactersCount += 1;
			}
			if (character == ATTRIBUTES_START) {
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
				currentNode.incrementCounter();
				currentState = GET_SELECTORS;
			}
		}
		else if (currentState == GET_COMMANDS) {
			if (character == QUESTION_MARK) {
				cout << "? == " <<
			}
		}
		if (character == QUESTION_MARK && checkInput(input, QUESTION_MARK)) {
			clearInput(input, charactersCount);
			charactersCount = NULL;
			currentState = GET_COMMANDS;
		}
		if (character == ASTERISK && checkInput(input, ASTERISK)) {
			clearInput(input, charactersCount);
			charactersCount = NULL;
			currentState = GET_SELECTORS;
		}
	}
	return 0;
}