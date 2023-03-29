#include <iostream>
#include "Text.h"
#include "CSSBlock.h"
#include "ListNode.h"
#define BUFFER 30
#define SPECIAL_COMMAND_LENGTH 4
#define SECOND_ARGUMENT_POSITION 3
#define THIRD_ARGUMENT_POSITION 5
#define ONE_LETTER 1
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
#define SELECTOR 'S'
#define ATTRIBUTE 'A'
#define DELETE 'D'
#define ALL '*'

enum programState {
	GET_SELECTORS = 0,
	GET_ATTRIBUTES = 1,
	GET_COMMANDS = 2,
	NOT_ACTIVE = 3,
};

using namespace std;

void deleteSection() {

}

void deleteElement() {

}

void getElementName() {

}

void printSelectorFrom(int i, int j) {

}

int countAttributesForSection() {

}

int countSelectorsForSection() {

}

int getNumber(int index, char* arr, int startPoint) {
	int tmpNumber;
	int number = NULL;
	for (int i = startPoint; i < index; i++) {
		tmpNumber = arr[i] - '0'; //conversion to int
		for (int j = index - i - 1; j > 0; j--) {
			tmpNumber *= 10;
		}
		number += tmpNumber;
	}
}

int countSections(ListNode<CSSBlock>* currentNode) {
	ListNode<CSSBlock>* tmp = currentNode->getFirstNode();
	int counter = NULL;
	while (tmp != nullptr) {
		counter += tmp->getCounter();
		tmp = tmp->getNextNode();
	}
	return counter;

}

bool checkRepeatingChars(char* input, char toFind) {
	for (int i = 0; i < SPECIAL_COMMAND_LENGTH; i++) {
		if (input[i] != toFind) {
			return false;
		}
	}
	return true;
}

void checkIfSelectorIsSaved(ListNode<CSSBlock>& currentNode) {
	if (currentNode.getData()->getFirstSelector()->getData()->getCounter() == 0) {
		char toWrite[ONE_LETTER];
		toWrite[0] = '*'; //creating array without \0
		currentNode.getData()->getFirstSelector()->getData()->changeText(toWrite, ONE_LETTER);
	}
}

char* clearInput(char* input, int charactersCount) {
	for (int i = 0; i < charactersCount; i++) {
		input[i] = SPACE;
	}
	return input;
}

bool checkCommas(char* input, int charactersCount) {
	int commasCounter = NULL;
	for (int i = 0; i < charactersCount; i++) {
		if (input[i] == COMMA) {
			commasCounter += 1;
		}
	}
	if (commasCounter == 2) {
		return true;
	}
	return false;
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
				checkIfSelectorIsSaved(currentNode);
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
				cout << "? == " << countSections(&currentNode) << endl;
			}
			else if (character != NEW_LINE && character != SPACE){
				input[charactersCount] = character;
				charactersCount += 1;
			}
			else if (checkCommas(input, charactersCount)) {
				int index = NULL;
				int number = NULL;
				char* arr = new char[charactersCount];
				while (input[index] != COMMA) {
					if (input[index] > '0' && input[index] < '9') {
						arr[index] = input[index];
					}
					else {
						break;
					}
					index += 1;
				}
				if (index == NULL) {
					char character = input[index];
				}
				else {
					number = getNumber(index, arr, NULL);
				}
				if (number > 0) {
					if (input[SECOND_ARGUMENT_POSITION] == ATTRIBUTE) {
						if (input[THIRD_ARGUMENT_POSITION] == QUESTION_MARK) {
							cout << countAttributesForSection();//napisz funkcje
						}
						else {
							getElementName();//napisz funkcje
							
						}
					}
					else if (input[SECOND_ARGUMENT_POSITION] == SELECTOR) {
						if (input[THIRD_ARGUMENT_POSITION] == QUESTION_MARK) {
							cout << countSelectorsForSection();//napisz funkcje
						}
						else {
							int number2 = getNumber(index, input, THIRD_ARGUMENT_POSITION);
							printSelectorFrom(number, number2);//napisz funkcje
						}
					}
					else if (input[SECOND_ARGUMENT_POSITION] == DELETE) {
						if (input[THIRD_ARGUMENT_POSITION] == ALL) {
							deleteSection();//napisz funkcje
						}
						else {
							getElementName();//napisz funkcje
							deleteElement();//napisz funkcje
						}
					}
				}
				else {
					getElementName();//napisz funkcje
				}
				delete[] arr;
			}
		}
		if (character == QUESTION_MARK && checkRepeatingChars(input, QUESTION_MARK)) {
			clearInput(input, charactersCount);
			charactersCount = NULL;
			currentState = GET_COMMANDS;
		}
		if (character == ASTERISK && checkRepeatingChars(input, ASTERISK)) {
			clearInput(input, charactersCount);
			charactersCount = NULL;
			currentState = GET_SELECTORS;
		}
	}
	return 0;
}