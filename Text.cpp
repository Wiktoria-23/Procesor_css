#include <iostream>
#include "Text.h"

using namespace std;

Text::Text() {
	text = new char[1];
	text[0] = '\0';
	counter = 0;
	length = 1;
}
Text::Text(int length) : length(length) {
	text = new char[length];
	text[length - 1] = '\0';
	counter = length - 1;
}
void Text::newChar(char input, Text& previous) {
	length += 1;
	Text* current = new Text(length);
	for (int i = 0; i < counter; i++) {
		current->text[i] = previous.text[i];
	}
	current->text[counter] = input;
	counter += 1;
	current[counter] = '\0';
	swap(previous, *current);
	delete current;
}
Text::~Text() {

}