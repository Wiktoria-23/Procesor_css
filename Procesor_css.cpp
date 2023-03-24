#include <iostream>
#include "Text.h"
#include "CSSBlock.h"
#include "ListNode.h"
#define ATTRIBUTE_START '{'
#define ATTRIBUTE_END '}'
#define SPACE ' '
#define COMMA ','

enum programState {
	GET_SELECTORS = 0,
	GET_ATTRIBUTES = 1,
	GET_COMMANDS = 2,
	NOT_ACTIVE = 3,
};

using namespace std;

int main() {
	char character;
	programState currentState = GET_SELECTORS;
	Text input;
	ListNode<CSSBlock> currentNode;
	while (currentState != NOT_ACTIVE) {
		character = getchar();
		if (currentState == GET_SELECTORS) {
			if (character == COMMA) {
				ListNode<Text>* newSelector = new ListNode<Text>;
				*(currentNode.getData()->getFirstSelector()->getLastNode().getData()) = input;
				currentNode.getData()->getFirstSelector()->getLastNode().setNextNode(newSelector);
			}
			else if (character != ATTRIBUTE_START && character != SPACE) {
				input.newChar(character, input);
			}
			else if (character == ATTRIBUTE_START) {
				currentState = GET_ATTRIBUTES;
			}
		}
		else if (currentState == GET_ATTRIBUTES) {

		}
		if (character == ATTRIBUTE_START) {
			currentState = GET_ATTRIBUTES;
		}
		input.newChar(character, input);
	}
	return 0;
}