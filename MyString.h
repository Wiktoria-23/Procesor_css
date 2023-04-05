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
	void changeText(const char* otherText);
	void makeEmpty();
	int getLength() const;
	char* getText();
	char getCharacter(int index) const;
	void setChar(char character,int index);
	char operator[](int index) const;
	MyString& operator=(MyString& otherString);
	bool operator==(MyString& otherString);
	bool operator!=(MyString& otherString);
	~MyString();
};