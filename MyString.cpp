#include "MyString.h"
#include <iostream>

MyString::MyString() {
	this->length = 1;
	this->text = new char[length];
	text[0] = '\0';
}
MyString::MyString(int length) : length(length){
	this->text = new char[length];
	text[length - 1] = '\0';
}
MyString::MyString(MyString& otherString) : length(otherString.length) {
	text = new char[length];
	text[length - 1] = '\0';
	for (int i = 0; i < length - 1; i++) {
		text[i] = otherString[i];
	}
}
MyString::MyString(char* textToAdd, int length) : length(length) {
	text = new char[length];
	for (int i = 0; i < length; i++) {
		text[i] = textToAdd[i];
	}
}
void MyString::addCharacter(char character) {
	MyString* tmp = new MyString(length + 1);
	for (int i = 0; i < length; i++) {
		tmp->text[i] = this->text[i];
	}
	tmp->text[length - 1] = character;
	tmp->text[length] = '\0';
	*this = *tmp;
	delete tmp;
}
void MyString::changeText(MyString& otherText) {
	length = otherText.length;
	delete[] text;
	text = new char[length];
	text[length - 1] = '\0';
	for (int i = 0; i < length; i++) {
		text[i] = otherText[i];
	}
}
int MyString::getLength() {
	return length;
}
char* MyString::getText() {
	return text;
}
void MyString::setLength(int newLength) {
	length = newLength;
}
void MyString::setChar(char character, int index) {
	text[index] = character;
}
char MyString::operator[](int index) {
	return text[index];
}
std::ostream& operator<< (std::ostream& ostr, MyString& text) {
	for (int i = 0; i < text.getLength(); i++) {
		ostr << (text.getText())[i];
	}
	return ostr;
}
MyString& MyString::operator=(MyString& otherString) {
	length = otherString.getLength();
	for (int i = 0; i < length - 1; i++) {
		text[i] = otherString[i];
	}
	text[length] = '\0';
	return *this;
}
MyString::~MyString() {
	std::cout << "Destruktor " << *this << std::endl;
	if (text != nullptr) {
		delete[] text;
	}
}