#include <iostream>
#include <math.h>
#include "Text.h"
#include "CSSBlock.h"
#include "ListNode.h"
#define BUFFER 30
#define SPECIAL_COMMAND_LENGTH 4
#define SECOND_ARGUMENT_POSITION 1
#define THIRD_ARGUMENT_POSITION 3
#define ONE_LETTER 1
#define ATTRIBUTES_START '{'
#define ATTRIBUTES_END '}'
#define NUMBERS_START '0'
#define NUMBERS_END '9'
#define SPACE ' '
#define COMMA ','
#define NEW_LINE '\n'
#define SEMICOLON ';'
#define EMPTY ""
#define QUESTION_MARK '?'
#define ASTERISK '*'
#define SELECTOR 'S'
#define ATTRIBUTE 'A'
#define DELETE 'D'
#define ALL '*'

using namespace std;

enum programState {
	GET_SELECTORS = 0,
	GET_ATTRIBUTES = 1,
	GET_COMMANDS = 2,
	NOT_ACTIVE = 3,
};

void deleteSection() {

}

void deleteElement() {

}

Text& getElementName(Text& input, int index) {
	Text* elementName = new Text(input.getCounter());
	for (int i = index; i < elementName->getCounter(); i++) {
		elementName[i] = input[i];
	}
	return *elementName;///?????
}

void printSelectorFrom(int i, int j, ListNode<CSSBlock>& currentNode) {
	ListNode<CSSBlock>* tmp = currentNode.findNodeByNumberT(i);
	int number = i % T;
	if (tmp != nullptr && tmp->getDataFromIndex(number - 1)->getFirstSelector()->findNodeByNumber(j) != nullptr) {
		cout << i << COMMA << SELECTOR << COMMA << j << " == " << tmp->getDataFromIndex(number - 1)->getFirstSelector()->findNodeByNumber(j)->getData()->getText() << endl; //indexing starts from 1, not 0
	}
}

int getAttributesAmountForSection(ListNode<CSSBlock>& currentNode, int number) {
	ListNode<CSSBlock>* tmp = currentNode.findNodeByNumberT(number);
	number %= T;
	return currentNode.getDataFromIndex(number - 1)->getAttributeCounter(); //indexing starts from 1, not 0
}

int getSelectorsAmountForSection(ListNode<CSSBlock>& currentNode, int number) {
	ListNode<CSSBlock>* tmp = currentNode.findNodeByNumberT(number);
	number %= T;
	return tmp->getDataFromIndex(number - 1)->getSelectorCounter(); //indexing starts from 1, not 0
}

int getNumber(int index, Text& text, int startPoint) {
	int tmpNumber;
	int number = NULL;
	for (int i = startPoint; i < index + startPoint; i++) {
		tmpNumber = text[i] - '0'; //conversion to int
		for (int j = startPoint + index - i - 1; j > 0; j--) {
			tmpNumber *= 10;
		}
		number += tmpNumber;
	}
	return number;
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

bool checkRepeatingChars(Text& input, char toFind) {
	for (int i = 0; i < SPECIAL_COMMAND_LENGTH; i++) {
		if (input[i] != toFind) {
			return false;
		}
	}
	return true;
}

void checkIfSelectorIsSaved(ListNode<CSSBlock>& currentNode) {
	if (currentNode.getCurrentIndexData()->getFirstSelector()->getCurrentIndexData()->getCounter() == 0) {
		Text toWrite(1);
		toWrite.newChar('\0', toWrite);
		currentNode.getCurrentIndexData()->getFirstSelector()->getCurrentIndexData()->changeText(toWrite);
	}
}

void clearInput(char* input, int charactersCount) {
	for (int i = 0; i < charactersCount; i++) {
		input[i] = SPACE;
	}
}

bool checkCommas(Text& input) {
	int commasCounter = NULL;
	for (int i = 0; i < input.getCounter(); i++) {
		if (input[i] == COMMA) {
			commasCounter += 1;
		}
	}
	if (commasCounter == 2) {
		return true;
	}
	return false;
}

void addSelector(Text& input, ListNode<CSSBlock>& currentNode) {
	if (currentNode.getCurrentIndexData()->getFirstSelector()->getLastNode()->getCurrentIndexData()->getCounter() != NULL) {
		ListNode<Text>* newSelector = new ListNode<Text>;
		newSelector->setPreviousNode(currentNode.getCurrentIndexData()->getFirstSelector()->getLastNode());
		currentNode.getCurrentIndexData()->getFirstSelector()->getLastNode()->setNextNode(newSelector);
	}
	currentNode.getCurrentIndexData()->getFirstSelector()->getLastNode()->getData()->changeText(input);
	currentNode.getCurrentIndexData()->incrementSelectorCounter();
	input.makeEmpty();
}

void addAttribute(Text& input, ListNode<CSSBlock>& currentNode) {
	if (currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode()->getCurrentIndexData()->getCounter() != NULL) {
		ListNode<Text>* newAttribute = new ListNode<Text>;
		newAttribute->setPreviousNode(currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode());
		currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode()->setNextNode(newAttribute);
	}
	currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode()->getData()->changeText(input);
	currentNode.getCurrentIndexData()->incrementAttributeCounter();
	input.makeEmpty();
}

int main() {
	char character;
	programState currentState = GET_SELECTORS;
	Text input;
	ListNode<CSSBlock> currentNode(T);
	while (currentState != NOT_ACTIVE) {
		character = getchar();
		if (character == EOF) {
			currentState = NOT_ACTIVE;
		}
		if (currentState == GET_SELECTORS) {
			if ((character == COMMA || character == ATTRIBUTES_START) && input.getCounter() > 0) {
				if (currentNode.getCounter() >= T) {
					ListNode<CSSBlock>* newNode = new ListNode<CSSBlock>(T);
					currentNode.setNextNode(newNode);
					currentNode = *currentNode.getNextNode();
				}
				addSelector(input, currentNode);
			}
			else if (character != ATTRIBUTES_START && character != NEW_LINE) {
				input.newChar(character, input);
			}
			if (character == ATTRIBUTES_START) {
				checkIfSelectorIsSaved(currentNode);
				currentState = GET_ATTRIBUTES;
			}
		}
		else if (currentState == GET_ATTRIBUTES) {
			if ((character == SEMICOLON || character == ATTRIBUTES_END) && input.getCounter() > 0) {
				addAttribute(input, currentNode);
			}
			else if (character != ATTRIBUTES_END && character != NEW_LINE) {
				input.newChar(character, input);
			}
			if (character == ATTRIBUTES_END) {
				currentNode.incrementCounter();
				currentState = GET_SELECTORS;
			}
		}
		else if (currentState == GET_COMMANDS) {
			if (character != NEW_LINE && character != SPACE){
				input.newChar(character, input);
			}
			if (character == NEW_LINE) {
				if (checkCommas(input)) {
					int number = NULL;
					int counter = NULL;
					while (input[counter] != COMMA) {
						if (input[counter] >= NUMBERS_START && input[counter] <= NUMBERS_END) {//finds chars between 0-9
							counter += 1;
						}
						else {
							break;
						}
					}
					if (counter == NULL) {
						char character = input[counter];
					}
					else {
						number = getNumber(counter, input, NULL);
					}
					if (number > 0) {
						if (input[SECOND_ARGUMENT_POSITION + counter] == ATTRIBUTE) {
							if (input[THIRD_ARGUMENT_POSITION + counter] == QUESTION_MARK) {
								cout << number << COMMA << ATTRIBUTE << COMMA << QUESTION_MARK << " == " << getAttributesAmountForSection(currentNode, number) << endl;
							}
							else {
								Text attrubuteName = getElementName(input,THIRD_ARGUMENT_POSITION + counter);

							}
						}
						else if (input[SECOND_ARGUMENT_POSITION + counter] == SELECTOR) {
							if (input[THIRD_ARGUMENT_POSITION + counter] == QUESTION_MARK) {
								cout << number << COMMA << SELECTOR << COMMA << QUESTION_MARK << " == " << getSelectorsAmountForSection(currentNode, number) << endl;
							}
							else {
								int number2 = getNumber(counter, input, THIRD_ARGUMENT_POSITION + counter);
								printSelectorFrom(number, number2, currentNode);//napisz funkcje
							}
						}
						else if (input[SECOND_ARGUMENT_POSITION + counter] == DELETE) {
							if (input[THIRD_ARGUMENT_POSITION + counter] == ALL) {
								deleteSection();//napisz funkcje
							}
							else {
								//getElementName();//napisz funkcje
								deleteElement();//napisz funkcje
							}
						}
						input.makeEmpty();
					}
					else {
						//getElementName();//napisz funkcje
					}
				}
				else if (input[NULL] == QUESTION_MARK) {
					cout << "? == " << countSections(&currentNode) << endl;
					input.makeEmpty();
				}
			}
		}
		if (character == QUESTION_MARK && checkRepeatingChars(input, QUESTION_MARK)) {
			input.makeEmpty();
			currentState = GET_COMMANDS;
		}
		if (character == ASTERISK && checkRepeatingChars(input, ASTERISK)) {
			input.makeEmpty();
			currentState = GET_SELECTORS;
		}
	}
	return 0;
}