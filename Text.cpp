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
void Text::setChar(char character, int index) {
	this->text[index] = character;
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
	delete current;
}
void Text::makeEmpty() {
	Text tmp;
	swap(this->text, tmp.text);
	this->counter = 0;
	this->length = 1;
}
void Text::changeText(Text& text) {
	Text tmp(text.getLength());
	for (int i = 0; i < text.getLength(); i++) {
		tmp.setChar(text[i], i);
	}
	this->length = text.getLength();
	this->counter = text.getCounter();
	this->text = tmp.text;
}
char* Text::getText() {
	return this->text;
}
int Text::getCounter() {
	return counter;
}
int Text::getLength() {
	return length;
}
Text::~Text() {
	/*if (text != nullptr) {
		delete[] text;
	}*/
}

std::ostream& operator<< (std::ostream& ostr, Text& text) {
	for (int i = 0; i < text.getLength(); i++) {
		ostr << text[i];
	}
	return ostr;
}
char Text::operator[] (int i) {
	return this->text[i];
}