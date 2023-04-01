#pragma once
#include <iostream>

class MyString {
private:
	int length;
	char* text;
	friend std::ostream& operator<<(std::ostream& ostr, MyString& text);
public:
	MyString();
	MyString(int length);
	MyString(MyString& otherString);
	MyString(char* textToAdd, int length);
	void addCharacter(char character);
	void changeText(MyString& otherText);
	int getLength();
	char* getText();
	void setLength(int newLength);
	void setChar(char character,int index);
	char operator[](int index);
	MyString& operator=(MyString& otherString);
	~MyString();
};