#pragma once

class Text {
private:
	char* text;
	int counter, length;
public:
	Text();
	Text(int length);
	Text(const Text& text);
	Text(char* text, int charactersCount);
	void changeText(char* text, int charactersCount);
	void makeEmpty();
	char* getText();
	int getCounter();
	void newChar(char input, Text& previous);
	~Text();
};