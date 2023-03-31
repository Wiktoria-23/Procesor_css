#pragma once

class Text {
private:
	char* text;
	int counter, length;
	friend std::ostream& operator<< (std::ostream& ostr, Text& text);
public:
	Text();
	Text(int length);
	Text(const Text& text);
	Text(char* text, int charactersCount);
	void changeText(Text& text);
	void makeEmpty();
	char* getText();
	int getCounter();
	int getLength();
	void setChar(char character, int index);
	void newChar(char input, Text& previous);
	char operator[](int i);
	~Text();
};