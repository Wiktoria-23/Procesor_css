#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "MyString.h"
#include "CSSBlock.h"
#include "ListNode.h"
#define SPECIAL_COMMAND_LENGTH 4
#define SECOND_ARGUMENT_POSITION 1
#define THIRD_ARGUMENT_POSITION 3
#define ONE_LETTER 1
#define NOT_FOUND -1
#define ATTRIBUTES_START '{'
#define ATTRIBUTES_END '}'
#define NUMBERS_START '0'
#define NUMBERS_END '9'
#define SPACE ' '
#define COMMA ','
#define NEW_LINE '\n'
#define TAB '\t'
#define SEMICOLON ';'
#define COLON ':'
#define EMPTY ""
#define QUESTION_MARK '?'
#define ASTERISK '*'
#define SELECTOR 'S'
#define ATTRIBUTE 'A'
#define DELETE 'D'
#define VALUE 'E'
#define ALL '*'

using namespace std;

enum programState {
	GET_SELECTORS = 0,
	GET_ATTRIBUTES = 1,
	GET_COMMANDS = 2,
	NOT_ACTIVE = 3,
};

bool checkIfAttributeExist(MyString& attribute, ListNode<CSSBlock>& currentNode, int index) {
	ListNode<Attribute>* node = currentNode.getFirstNode()->findNodeByNumberT(index)->getDataFromIndex((index - 1) % T)->getFirstAttribute(); //counting in array starts from 0
	while (node != nullptr) {
		if (node->getData()->getKey() == attribute) {
			return true;
		}
		node = node->getNextNode();
	}
	return false;
}

void deleteSection(int number, ListNode<CSSBlock>& currentNode) {
	int index = (number - 1) % T;
	currentNode.findNodeByNumberT(number)->getDataFromIndex(index)->deleteAllData(); //nodes and elements in array are counted from 0, not from 1
	currentNode.decrementCounter();
}

void deleteElement(int number, MyString& attributeName, ListNode<CSSBlock>& currentNode) {
	int index = (number - 1) % T;
	if (!checkIfAttributeExist(attributeName, currentNode, number)) {
		return;
	}
	ListNode<Attribute>* tmp = currentNode.findNodeByNumberT(number)->getDataFromIndex(index)->getFirstAttribute();
	while (tmp->getData()->getKey() != attributeName) {
		tmp = tmp->getNextNode();
	}
	if (tmp->getNextNode() == nullptr && tmp->getPreviousNode() == nullptr) {
		tmp->getData()->getKey().changeText(DELETED);
		tmp->getData()->getValue().changeText(DELETED);
	}
	else {
		tmp->deleteNode();
	}
	CSSBlock* currentBlock = currentNode.findNodeByNumberT(number)->getDataFromIndex(index);
	currentBlock->decrementAttributeCounter();
	if (currentBlock->getAttributeCounter() == NULL) {
		currentBlock->deleteAllData();
		currentNode.decrementCounter();
	}
	if (currentNode.getCounter() == NULL) {
		if (currentNode.getNextNode() != nullptr) {
			currentNode = *currentNode.getNextNode();
			currentNode.getPreviousNode()->deleteNode();
		}
		else if (currentNode.getPreviousNode() != nullptr) {
			currentNode = *currentNode.getPreviousNode();
			currentNode.getNextNode()->deleteNode();
		}
	}
	cout << number << COMMA << DELETE << COMMA << attributeName << " == " << "deleted" << endl;
}

int getLength(MyString& input, int index, int startPoint) {
	while (input.getCharacter(index) != COMMA && input.getCharacter(index) != '\0') {
		index += 1;
	}
	return index - startPoint;
}

int countSelector(MyString& selectorName, ListNode<CSSBlock>& currentNode) {
	ListNode<CSSBlock>* tmp = currentNode.getFirstNode();
	int counter = NULL;
	while (tmp != nullptr) {
		for (int i = 0; i < tmp->getCounter(); i++) {
			CSSBlock* currentBlock = tmp->getDataFromIndex(i);
			if (currentBlock->getSelectorCounter() > NULL) {
				ListNode<MyString>* currentSelector = currentBlock->getFirstSelector();
				while (currentSelector != nullptr) {
					if (*currentSelector->getData() == selectorName) {
						counter += 1;
					}
					currentSelector = currentSelector->getNextNode();
				}
			}
		}
		tmp = tmp->getNextNode();
	}
	return counter;
}

int countAttribute(MyString& attributeName, ListNode<CSSBlock>& currentNode) {
	ListNode<CSSBlock>* tmp = currentNode.getFirstNode();
	int counter = NULL;
	while (tmp != nullptr) {
		for (int i = 0; i < tmp->getCounter(); i++) {
			CSSBlock* currentBlock = tmp->getDataFromIndex(i);
			ListNode<Attribute>* currentAttribute = tmp->getDataFromIndex(i)->getFirstAttribute();
			while (currentBlock->getSelectorCounter() != NULL && currentAttribute != nullptr) {
				if (currentAttribute->getData()->getKey() == attributeName) {
					counter += 1;
				}
				currentAttribute = currentAttribute->getNextNode();
			}
		}
		tmp = tmp->getNextNode();
	}
	return counter;
}

bool checkIfSectionExist(ListNode<CSSBlock>& currentNode, int number) {
	ListNode<CSSBlock>* tmp = currentNode.getFirstNode()->findNodeByNumberT(number - 1);
	if (tmp->getCounter() > (number - 1) % T) { //counting in array starts from 0
		return true;
	}
	return false;
}

MyString& findAttributeValue(MyString& attribute, ListNode<CSSBlock>& currentNode, int index) {
	ListNode<Attribute>* node = currentNode.getFirstNode()->findNodeByNumberT(index)->getDataFromIndex((index - 1) % T)->getFirstAttribute();
	while (node->getNextNode() != nullptr) {
		if (node->getData()->getKey() == attribute) { //counting in array starts from 0
			break;
		}
		node = node->getNextNode();
	}
	return node->getData()->getValue();
}

MyString& getElementName(MyString& input, int startIndex, int endIndex) {
	MyString* elementName = new MyString(endIndex - startIndex);
	for (int i = 0; i < elementName->getLength() - 1; i++) {
		elementName->setChar(input[i + startIndex], i);
	}
	elementName->setChar('\0', elementName->getLength() - 1);
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
	ListNode<CSSBlock>* tmp = currentNode.getFirstNode()->findNodeByNumberT(number);
	number = (number - 1) % T;
	return tmp->getDataFromIndex(number)->getAttributeCounter(); //indexing starts from 1, not 0
}

int getSelectorsAmountForSection(ListNode<CSSBlock>& currentNode, int number) {
	ListNode<CSSBlock>* tmp = currentNode.findNodeByNumberT(number - 1);
	number = (number - 1) % T;
	return tmp->getDataFromIndex(number)->getSelectorCounter(); //indexing starts from 1, not 0
}

int getNumber(int length, MyString& text, int startPoint) {
	int tmpNumber;
	int number = NULL;
	for (int i = startPoint; i < length + startPoint; i++) {
		tmpNumber = text[i] - '0'; //conversion to int
		for (int j = startPoint + length - i - 1; j > 0; j--) {
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

void checkInput(MyString& input) {
	if (input.getText()[input.getLength() - 2] == SPACE || input.getText()[input.getLength() - 2] == NEW_LINE || input.getText()[input.getLength() - 2] == TAB) { //last place in text is '\0'
		input.getText()[input.getLength() - 2] = '\0';
		input.setLength(input.getLength() - 1);
	}
}

void addSelector(MyString& input, ListNode<CSSBlock>& currentNode) {
	checkInput(input);
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
	checkInput(input);
	if (currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode()->getCurrentIndexData()->getKey().getLength() != 1) {
		ListNode<Attribute>* newAttribute = new ListNode<Attribute>;
		newAttribute->setPreviousNode(currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode());
		currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode()->setNextNode(newAttribute);
	}
	currentNode.getCurrentIndexData()->getFirstAttribute()->getLastNode()->getData()->getKey().changeText(input);
	currentNode.getCurrentIndexData()->incrementAttributeCounter();
	input.makeEmpty();
}

void addAttributeValue(MyString& input, ListNode<Attribute>& currentNode) {
	checkInput(input);
	currentNode.getData()->getValue().changeText(input);
	input.makeEmpty();
}

void findLastValue(MyString& attributeName, MyString& selectorName, ListNode<CSSBlock>& currentNode) {
	ListNode<CSSBlock>* tmp = currentNode.getLastNode();
	while (tmp != nullptr) {
		for (int i = tmp->getCounter() - 1; i >= 0; i--) {
			ListNode<MyString>* currentSelector = tmp->getDataFromIndex(i)->getFirstSelector();
			while (currentSelector != nullptr) {
				if (*currentSelector->getData() == selectorName) {
					ListNode<Attribute>* currentAttribute = tmp->getDataFromIndex(i)->getFirstAttribute();
					while (currentAttribute != nullptr) {
						if (currentAttribute->getData()->getKey() == attributeName) {
							cout << selectorName << COMMA << VALUE << COMMA << attributeName << " == " << currentAttribute->getData()->getValue() << endl;
							return;
						}
						currentAttribute = currentAttribute->getNextNode();
					}
				}
				currentSelector = currentSelector->getNextNode();
			}
		}
		tmp = tmp->getPreviousNode();
	}
}

void chooseCommandWithName(MyString& input, int counter, ListNode<CSSBlock>& currentNode) {
	MyString elementName = getElementName(input, NULL, counter + 1); //length has to be one char bigger
	if (input.getCharacter(SECOND_ARGUMENT_POSITION + counter) == ATTRIBUTE) {
		if (input.getCharacter(THIRD_ARGUMENT_POSITION + counter) == QUESTION_MARK) {
			cout << elementName << COMMA << ATTRIBUTE << COMMA << QUESTION_MARK << " == " << countAttribute(elementName, currentNode) << endl;
		}
	}
	else if (input.getCharacter(SECOND_ARGUMENT_POSITION + counter) == SELECTOR) {
		if (input.getCharacter(THIRD_ARGUMENT_POSITION + counter) == QUESTION_MARK) {
			cout << elementName << COMMA << SELECTOR << COMMA << QUESTION_MARK << " == " << countSelector(elementName, currentNode) << endl;
		}
	}
	else if (input.getCharacter(SECOND_ARGUMENT_POSITION + counter) == VALUE) {
		int nameLength = getLength(input, counter, THIRD_ARGUMENT_POSITION + counter);
		MyString attributeName = getElementName(input, THIRD_ARGUMENT_POSITION + counter, input.getLength());
		findLastValue(attributeName, elementName, currentNode);
	}
	input.makeEmpty();
}

void chooseCommandWithNumber(MyString& input, int counter, ListNode<CSSBlock>& currentNode, int number) {
	if (input.getCharacter(SECOND_ARGUMENT_POSITION + counter) == ATTRIBUTE) {
		if (input.getCharacter(THIRD_ARGUMENT_POSITION + counter) == QUESTION_MARK) {
			if (checkIfSectionExist(currentNode, number)) {
				cout << number << COMMA << ATTRIBUTE << COMMA << QUESTION_MARK << " == " << getAttributesAmountForSection(currentNode, number) << endl;
			}
		}
		else {
			MyString attributeName = getElementName(input, THIRD_ARGUMENT_POSITION + counter, input.getLength());
			if (checkIfAttributeExist(attributeName, currentNode, number)) {
				cout << number << COMMA << ATTRIBUTE << COMMA << attributeName << " == " << findAttributeValue(attributeName, currentNode, number) << endl;
			}
		}
	}
	else if (input.getCharacter(SECOND_ARGUMENT_POSITION + counter) == SELECTOR) {
		if (input.getCharacter(THIRD_ARGUMENT_POSITION + counter) == QUESTION_MARK) {
			if (checkIfSectionExist(currentNode, number)) {
				cout << number << COMMA << SELECTOR << COMMA << QUESTION_MARK << " == " << getSelectorsAmountForSection(currentNode, number) << endl;
			}
		}
		else {
			int length = getLength(input, THIRD_ARGUMENT_POSITION + counter, THIRD_ARGUMENT_POSITION + counter);
			int number2 = getNumber(length, input, THIRD_ARGUMENT_POSITION + counter);
			if (checkIfSectionExist(currentNode, number)) {
				printSelectorFrom(number, number2, currentNode);
			}
		}
	}
	else if (input.getCharacter(SECOND_ARGUMENT_POSITION + counter) == DELETE) {
		if (input.getCharacter(THIRD_ARGUMENT_POSITION + counter) == ALL) {
			deleteSection(number, currentNode);
			cout << number << COMMA << DELETE << COMMA << ALL << " == " << "deleted" << endl;
		}
		else {
			MyString& attributeName = getElementName(input, THIRD_ARGUMENT_POSITION + counter, input.getLength());
			deleteElement(number, attributeName, currentNode);
		}
	}
	input.makeEmpty();
}

bool checkIfAttributeIsSaved(MyString& input, ListNode<CSSBlock>& currentNode) {
	ListNode<Attribute>* tmp = currentNode.getCurrentIndexData()->getFirstAttribute();
	while (tmp != nullptr) {
		if (tmp->getData()->getKey() == input) {
			return true;
		}
		tmp = tmp->getNextNode();
	}
	return false;
}

programState getSelectors(char character, MyString& input, ListNode<CSSBlock>* currentNode, programState currentState) {
	if ((character == COMMA || character == ATTRIBUTES_START) && input.getLength() > 1) {
		checkInput(input);
		addSelector(input, *currentNode);
	}
	else if (character != ATTRIBUTES_START && character != NEW_LINE && character != TAB) {
		input.addCharacter(character);
	}
	if (character == ATTRIBUTES_START) {
		checkIfSelectorIsSaved(*currentNode);
		currentState = GET_ATTRIBUTES;
	}
	return currentState;
}

programState getAttributes(char character, MyString& input, ListNode<CSSBlock>* currentNode, programState currentState) {
	static bool attributeToOverwrite;
	static MyString attributeName;
	if (character == COLON && input.getLength() > 1) {
		checkInput(input);
		if (!checkIfAttributeIsSaved(input, *currentNode)) {
			addAttributeKey(input, *currentNode);
			attributeToOverwrite = false;
		}
		else {
			attributeToOverwrite = true;
			attributeName = input;
			input.makeEmpty();
		}
	}
	else if ((character == SEMICOLON || character == ATTRIBUTES_END) && input.getLength() > 1) {
		checkInput(input);
		ListNode<Attribute>* tmp = currentNode->getLastNode()->getCurrentIndexData()->getFirstAttribute()->getLastNode();
		if (attributeToOverwrite) {
			tmp = currentNode->getLastNode()->getCurrentIndexData()->getFirstAttribute();
			while (tmp->getData()->getKey() != attributeName) {
				tmp = tmp->getNextNode();
			}
		}
		addAttributeValue(input, *tmp);
	}
	else if (character != ATTRIBUTES_END && character != NEW_LINE && character != TAB) {
		input.addCharacter(character);
	}
	if (character == ATTRIBUTES_END) {
		currentNode->incrementCounter();
		currentState = GET_SELECTORS;
	}
	return currentState;
}

programState getCommands(char character, MyString& input, ListNode<CSSBlock>* currentNode, programState currentState) {
	if (character != NEW_LINE && character != SPACE) {
		input.addCharacter(character);
	}
	if (character == NEW_LINE) {
		if (checkCommas(input)) {
			int number = NULL;
			int counter = NULL;
			while (input.getCharacter(counter) != COMMA) {
				if (input.getCharacter(counter) >= NUMBERS_START && input.getCharacter(counter) <= NUMBERS_END) {//finds chars between 0-9
					counter += 1;
				}
				else {
					break;
				}
			}
			if (counter == NULL) {
				counter = getLength(input, counter, NULL);
				if (counter == 1) {
					char character = input.getCharacter(counter);
				}
				else {
					chooseCommandWithName(input, counter, *currentNode);
				}
			}
			else {
				number = getNumber(counter, input, NULL);
			}
			if (number > 0) {
				chooseCommandWithNumber(input, counter, *currentNode, number);
			}
		}
		else if (input.getCharacter(NULL) == QUESTION_MARK) {
			cout << "? == " << countSections(currentNode) << endl;
			input.makeEmpty();
		}
	}
	return currentState;
}

ListNode<CSSBlock>* checkIfAddNextNode(char character, MyString& input, ListNode<CSSBlock>* currentNode) {
	if ((character == COMMA || character == ATTRIBUTES_START) && input.getLength() > 1) {
		if (currentNode->getCounter() >= T) {
			ListNode<CSSBlock>* newNode = new ListNode<CSSBlock>(T);
			newNode->setPreviousNode(currentNode);
			currentNode->setNextNode(newNode);
			currentNode = currentNode->getNextNode();
		}
	}
	return currentNode;
}

int main() {
	char character;
	programState currentState = GET_SELECTORS;
	MyString* input = new MyString();
	ListNode<CSSBlock>* currentNode = new ListNode<CSSBlock>(T);
	while (currentState != NOT_ACTIVE) {
		character = getchar();
		if (character == EOF) {
			currentState = NOT_ACTIVE;
		}
		if (currentState == GET_SELECTORS) {
			currentNode = checkIfAddNextNode(character, *input, currentNode);
			currentState = getSelectors(character, *input, currentNode, currentState);
		}
		else if (currentState == GET_ATTRIBUTES) {
			currentState = getAttributes(character, *input, currentNode, currentState);
		}
		else if (currentState == GET_COMMANDS) {
			currentState = getCommands(character, *input, currentNode, currentState);
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