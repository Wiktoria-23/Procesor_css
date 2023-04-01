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
	void makeEmpty();
	int getLength();
	char* getText();
	char getCharacter(int index);
	void setLength(int newLength);
	void setChar(char character,int index);
	char operator[](int index);
	MyString& operator=(MyString& otherString);
	bool operator==(MyString& otherString);
	~MyString();
};