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

void deleteSection(int number, ListNode<CSSBlock>& currentNode) {
	int index = number % T;
	currentNode.findNodeByNumberT(number - 1)->getDataFromIndex(index - 1)->deleteAllData(); //nodes and elements in array are counted from 0, not from 1
	currentNode.decrementCounter();
}

void deleteElement(int number, MyString& attributeName, ListNode<CSSBlock>& currentNode) {
	int index = number % T;
	ListNode<Attribute>* tmp = currentNode.findNodeByNumberT(number - 1)->getDataFromIndex(index - 1)->getFirstAttribute();
	while (tmp->getData()->getKey() != attributeName) {
		tmp = tmp->getNextNode();
	}
	tmp->deleteNode();
	CSSBlock* currentBlock = currentNode.findNodeByNumberT(number - 1)->getDataFromIndex(index - 1);
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
}

int findLastOccurenceOfAttributeForSelector(ListNode<CSSBlock>& currentNode, MyString& attribute, MyString& selector) {
	int lastOccurence = NOT_FOUND;
	int nodeCounter = NULL;
	ListNode<CSSBlock>* node = currentNode.getFirstNode();
	while (node != nullptr) {
		for (int i = 0; i < node->getCounter(); i++) {
			ListNode<MyString>* selectorNode = currentNode.getFirstNode()->getDataFromIndex(i)->getFirstSelector();
			while (selectorNode != nullptr && node->getData()->getSelectorCounter() != NULL) {
				if (*selectorNode->getData() == selector) {
					ListNode<Attribute>* attributeNode = currentNode.getFirstNode()->getDataFromIndex(i)->getFirstAttribute();
					while (attributeNode != nullptr) {
						if (attributeNode->getData()->getKey() == attribute) {
							lastOccurence = nodeCounter + i;
						}
						attributeNode = attributeNode->getNextNode();
					}
				}
				selectorNode = selectorNode->getNextNode();
			}
		}
		nodeCounter += 1;
		node = node->getNextNode();
	}
	return lastOccurence;
}

int getNameLength(MyString& input, int counter) {
	while (input.getCharacter(counter) != COMMA) {
		if ((input.getCharacter(counter) >= 'a' && input.getCharacter(counter) <= 'z') || (input.getCharacter(counter) >= 'A' && input.getCharacter(counter) <= 'Z')) {
			counter += 1;
		}
		else {
			counter += 1;
			break;
		}
	}
	return counter;
}

int countSelector(MyString& selectorName, ListNode<CSSBlock>& currentNode) {
	ListNode<CSSBlock>* tmp = currentNode.getFirstNode();
	int counter = NULL;
	for (int i = 0; i < currentNode.getCounter(); i++) {
		CSSBlock* currentBlock = tmp->getDataFromIndex(i);
		ListNode<MyString>* currentSelector = currentBlock->getFirstSelector();
		while (currentBlock->getSelectorCounter() != NULL && currentSelector != nullptr) {
			if (*currentSelector->getData() == selectorName) {
				counter += 1;
			}
			currentSelector = currentSelector->getNextNode();
		}
	}
	return counter;
}

int countAttribute(MyString& attributeName, ListNode<CSSBlock>& currentNode) {
	ListNode<CSSBlock>* tmp = currentNode.getFirstNode();
	int counter = NULL;
	for (int i = 0; i < currentNode.getCounter(); i++) {
		CSSBlock* currentBlock = tmp->getDataFromIndex(i);
		ListNode<Attribute>* currentAttribute = tmp->getDataFromIndex(i)->getFirstAttribute();
		while (currentBlock->getFirstSelector() != 0 && currentAttribute != nullptr) {
			if (currentAttribute->getData()->getKey() == attributeName) {
				counter += 1;
			}
			currentAttribute = currentAttribute->getNextNode();
		}
	}
	return counter;
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
			return true;
		}
		node = node->getNextNode();
	}
	return false;
}

MyString& findAttributeValue(MyString& attribute, ListNode<CSSBlock>& currentNode, int index) {
	ListNode<Attribute>* node = currentNode.getFirstNode()->getDataFromIndex(index - 1)->getFirstAttribute();
	while (node != nullptr) {
		if (node->getData()->getKey() == attribute) { //counting in array starts from 0
			break;
		}
		node = node->getNextNode();
	}
	return node->getData()->getValue();
}

MyString& findAttributeValueForSelector(ListNode<CSSBlock>& currentNode, MyString& attribute, int lastOccurence) {
	int index = lastOccurence % T;
	lastOccurence = floor(lastOccurence / T);
	ListNode<CSSBlock>* node = currentNode.findNodeByNumber(lastOccurence);
	MyString& value = findAttributeValue(attribute, *node, index);
	return value;
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
	if (input.getText()[input.getLength() - 1] == SPACE || input.getText()[input.getLength() - 1] == NEW_LINE || input.getText()[input.getLength() - 1] == TAB) {
		input.getText()[input.getLength() - 1] = '\0';
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

void addAttributeValue(MyString& input, ListNode<CSSBlock>& currentNode) {
	checkInput(input);
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
			else if (character != ATTRIBUTES_START && character != NEW_LINE && character != TAB) {
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
			else if (character != ATTRIBUTES_END && character != NEW_LINE && character != TAB) {
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
						counter = getNameLength(*input, counter);
						if (counter == 1) {
							char character = input->getCharacter(counter);
						}
						else {
							MyString elementName = getElementName(*input, NULL, counter + 1); //length has to be one char bigger
							if (input->getCharacter(SECOND_ARGUMENT_POSITION + counter) == ATTRIBUTE) {
								if (input->getCharacter(THIRD_ARGUMENT_POSITION + counter) == QUESTION_MARK) {
									cout << elementName << COMMA << ATTRIBUTE << COMMA << QUESTION_MARK << " == " << countAttribute(elementName, currentNode) << endl;
								}
							}
							else if (input->getCharacter(SECOND_ARGUMENT_POSITION + counter) == SELECTOR) {
								if (input->getCharacter(THIRD_ARGUMENT_POSITION + counter) == QUESTION_MARK) {
									cout << elementName << COMMA << SELECTOR << COMMA << QUESTION_MARK << " == " << countSelector(elementName, currentNode) << endl;
								}
							}
							else if (input->getCharacter(SECOND_ARGUMENT_POSITION + counter) == VALUE) {
								int nameLength = getNameLength(*input, counter);
								MyString attributeName = getElementName(*input, THIRD_ARGUMENT_POSITION + counter, input->getLength());
								int lastOccurence = findLastOccurenceOfAttributeForSelector(currentNode, attributeName, elementName);
								if (lastOccurence >= 0) {
									cout << elementName << COMMA << VALUE << COMMA << attributeName << " == " << findAttributeValueForSelector(currentNode, attributeName, lastOccurence + 1) << endl; //nodes are counted from 0
								}
							}
							input->makeEmpty();
						}
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
								MyString attributeName = getElementName(*input, THIRD_ARGUMENT_POSITION + counter, input->getLength());
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
									printSelectorFrom(number, number2, currentNode);
								}
							}
						}
						else if (input->getCharacter(SECOND_ARGUMENT_POSITION + counter) == DELETE) {
							if (input->getCharacter(THIRD_ARGUMENT_POSITION + counter) == ALL) {
								deleteSection(number, currentNode);
								cout << number << COMMA << DELETE << COMMA << ALL << " == " << "deleted" << endl;
							}
							else {
								MyString& attributeName = getElementName(*input, THIRD_ARGUMENT_POSITION + counter, input->getLength());
								deleteElement(number, attributeName, currentNode);
								cout << number << COMMA << DELETE << COMMA << attributeName << " == " << "deleted" << endl;
							}
						}
						input->makeEmpty();
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