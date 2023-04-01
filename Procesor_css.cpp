#include <iostream>
#include <math.h>
#include "MyString.h"
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
#define COLON ':'
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

bool checkIfSectionExist(ListNode<CSSBlock>& currentNode, int number) {
	if (currentNode.getLastNode()->getCounter() > number - 1) { //counting in array starts from 0
		return true;
	}
	return false;
}

bool checkIfAttributeExist(MyString& attribute, ListNode<CSSBlock>& currentNode, int index) {
	ListNode<Attribute>* node = currentNode.getFirstNode()->getDataFromIndex(index - 1)->getFirstAttribute(); //counting in array starts from 0
	while (node != nullptr) {
		if (node->getData()->getKey() == attribute) {
			/*cout << "Atrybut istnieje" << endl;*/
			return true;
		}
		node = node->getNextNode();
	}
	/*cout << "Atrybut nie istnieje" << endl;*/
	return false;
}

MyString& findAttributeValue(MyString& attribute, ListNode<CSSBlock>& currentNode, int index) {
	ListNode<Attribute>* node = currentNode.getFirstNode()->getDataFromIndex(index - 1)->getFirstAttribute();
	while (true) {
		if (node->getData()->getKey() == attribute) { //counting in array starts from 0
			return node->getData()->getValue();
		}
		node = node->getNextNode();
	}
}

MyString& getElementName(MyString& input, int index) {
	MyString* elementName = new MyString(input.getLength() - index);
	for (int i = 0; i < elementName->getLength(); i++) {
		elementName->setChar(input[i + index], i);
	}
	return *elementName;
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

int getNumber(int index, MyString& text, int startPoint) {
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

bool checkRepeatingChars(MyString& input, char toFind) {
	for (int i = 0; i < SPECIAL_COMMAND_LENGTH; i++) {
		if (input[i] != toFind) {
			return false;
		}
	}
	return true;
}

void checkIfSelectorIsSaved(ListNode<CSSBlock>& currentNode) {
	if (currentNode.getCurrentIndexData()->getFirstSelector()->getCurrentIndexData()->getLength() == 1) {
		MyString toWrite(1);
		toWrite.addCharacter('\0');
		currentNode.getCurrentIndexData()->getFirstSelector()->getCurrentIndexData()->changeText(toWrite);
	}
}

void clearInput(char* input, int charactersCount) {
	for (int i = 0; i < charactersCount; i++) {
		input[i] = SPACE;
	}
}

bool checkCommas(MyString& input) {
	int commasCounter = NULL;
	for (int i = 0; i < input.getLength(); i++) {
		if (input[i] == COMMA) {
			commasCounter += 1;
		}
	}
	if (commasCounter == 2) {
		return true;
	}
	return false;
}

void addSelector(MyString& input, ListNode<CSSBlock>& currentNode) {
	if (currentNode.getCurrentIndexData()->getFirstSelector()->getLastNode()->getCurrentIndexData()->getLength() != 1) {
		ListNode<MyString>* newSelector = new ListNode<MyString>;
		newSelector->setPreviousNode(currentNode.getCurrentIndexData()->getFirstSelector()->getLastNode());
		currentNode.getCurrentIndexData()->getFirstSelector()->getLastNode()->setNextNode(newSelector);
	}
	currentNode.getCurrentIndexData()->getFirstSelector()->getLastNode()->getData()->changeText(input);
	currentNode.getCurrentIndexData()->incrementSelectorCounter();
	input.makeEmpty();
}

void addAttributeKey(MyString& input, ListNode<CSSBlock>& currentNode) {
	if (currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode()->getCurrentIndexData()->getKey().getLength() != 1) {
		ListNode<Attribute>* newAttribute = new ListNode<Attribute>;
		newAttribute->setPreviousNode(currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode());
		currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode()->setNextNode(newAttribute);
	}
	currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode()->getData()->getKey().changeText(input);
	currentNode.getCurrentIndexData()->incrementAttributeCounter();
	input.makeEmpty();
}

void addAttributeValue(MyString& input, ListNode<CSSBlock>& currentNode) {
	currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode()->getData()->getValue().changeText(input);
	input.makeEmpty();
}

int main() {
	char character;
	programState currentState = GET_SELECTORS;
	MyString* input = new MyString();
	ListNode<CSSBlock> currentNode(T);
	while (currentState != NOT_ACTIVE) {
		character = getchar();
		if (character == EOF) {
			currentState = NOT_ACTIVE;
		}
		if (currentState == GET_SELECTORS) {
			if ((character == COMMA || character == ATTRIBUTES_START) && input->getLength() > 1) {
				if (currentNode.getCounter() >= T) {
					ListNode<CSSBlock>* newNode = new ListNode<CSSBlock>(T);
					currentNode.setNextNode(newNode);
					currentNode = *currentNode.getNextNode();
				}
				addSelector(*input, currentNode);
			}
			else if (character != ATTRIBUTES_START && character != NEW_LINE) {
				input->addCharacter(character);
			}
			if (character == ATTRIBUTES_START) {
				checkIfSelectorIsSaved(currentNode);
				currentState = GET_ATTRIBUTES;
			}
		}
		else if (currentState == GET_ATTRIBUTES) {
			if (character == COLON && input->getLength() > 1) {
				addAttributeKey(*input, currentNode);
			}
			else if ((character == SEMICOLON || character == ATTRIBUTES_END) && input->getLength() > 1) {
				addAttributeValue(*input, currentNode);
			}
			else if (character != ATTRIBUTES_END && character != NEW_LINE) {
				input->addCharacter(character);
			}
			if (character == ATTRIBUTES_END) {
				currentNode.incrementCounter();
				currentState = GET_SELECTORS;
			}
		}
		else if (currentState == GET_COMMANDS) {
			if (character != NEW_LINE && character != SPACE){
				input->addCharacter(character);
			}
			if (character == NEW_LINE) {
				if (checkCommas(*input)) {
					int number = NULL;
					int counter = NULL;
					while (input->getCharacter(counter) != COMMA) {
						if (input->getCharacter(counter) >= NUMBERS_START && input->getCharacter(counter) <= NUMBERS_END) {//finds chars between 0-9
							counter += 1;
						}
						else {
							break;
						}
					}
					if (counter == NULL) {
						char character = input->getCharacter(counter);
					}
					else {
						number = getNumber(counter, *input, NULL);
					}
					if (number > 0) {
						if (input->getCharacter(SECOND_ARGUMENT_POSITION + counter) == ATTRIBUTE) {
							if (input->getCharacter(THIRD_ARGUMENT_POSITION + counter) == QUESTION_MARK) {
								if (checkIfSectionExist(currentNode, number)) {
									cout << number << COMMA << ATTRIBUTE << COMMA << QUESTION_MARK << " == " << getAttributesAmountForSection(currentNode, number) << endl;
								}
							}
							else {
								MyString attributeName = getElementName(*input, THIRD_ARGUMENT_POSITION + counter);
								/*cout << attributeName << endl;*/
								if (checkIfAttributeExist(attributeName, currentNode, number)) {
									cout << number << COMMA << ATTRIBUTE << COMMA << attributeName << " == " << findAttributeValue(attributeName, currentNode, number) << endl;
								}
							}
						}
						else if (input->getCharacter(SECOND_ARGUMENT_POSITION + counter) == SELECTOR) {
							if (input->getCharacter(THIRD_ARGUMENT_POSITION + counter) == QUESTION_MARK) {
								if (checkIfSectionExist(currentNode, number)) {
									cout << number << COMMA << SELECTOR << COMMA << QUESTION_MARK << " == " << getSelectorsAmountForSection(currentNode, number) << endl;
								}
							}
							else {
								int number2 = getNumber(counter, *input, THIRD_ARGUMENT_POSITION + counter);
								if (checkIfSectionExist(currentNode, number)) {
									printSelectorFrom(number, number2, currentNode);//napisz funkcje
								}
							}
						}
						else if (input->getCharacter(SECOND_ARGUMENT_POSITION + counter) == DELETE) {
							if (input->getCharacter(THIRD_ARGUMENT_POSITION + counter) == ALL) {
								deleteSection();//napisz funkcje
							}
							else {
								//getElementName();//napisz funkcje
								deleteElement();//napisz funkcje
							}
						}
						input->makeEmpty();
					}
					else {
						//getElementName();//napisz funkcje
					}
				}
				else if (input->getCharacter(NULL) == QUESTION_MARK) {
					cout << "? == " << countSections(&currentNode) << endl;
					input->makeEmpty();
				}
			}
		}
		if (character == QUESTION_MARK && checkRepeatingChars(*input, QUESTION_MARK)) {
			input->makeEmpty();
			currentState = GET_COMMANDS;
		}
		if (character == ASTERISK && checkRepeatingChars(*input, ASTERISK)) {
			input->makeEmpty();
			currentState = GET_SELECTORS;
		}
	}
	return 0;
}