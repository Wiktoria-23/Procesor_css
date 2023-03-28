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
Text::Text(const Text& text) {
	this->length = text.length;
	this->counter = text.counter;
	for (int i = 0; i < length; i++) {
		this[i] = text.text[i];
	}
}
Text::Text(char* text, int charactersCount) {
	this->length = charactersCount + 1;
	this->counter = charactersCount;
	for (int i = 0; i < charactersCount; i++) {
		this->text[i] = text[i];
	}
}
void Text::newChar(char input, Text& previous) {
	length += 1;
	Text* current = new Text(length);
	for (int i = 0; i < counter; i++) {
		current->text[i] = previous.text[i];
	}
	current->text[counter] = input;
	counter += 1;
	previous = *current;
}
void Text::makeEmpty() {
	Text tmp;
	swap(this->text, tmp.text);
	this->counter = 0;
	this->length = 1;
}
void Text::changeText(char* text, int charactersCount) {
	char* tmp = new char[charactersCount];
	for (int i = 0; i < charactersCount; i++) {
		tmp[i] = text[i];
	}
	this->text = tmp;
	this->length = charactersCount - 1;
	this->counter = charactersCount;
}
char* Text::getText() {
	return this->text;
}
int Text::getCounter() {
	return counter;
}
Text::~Text() {
	delete[] text;
}