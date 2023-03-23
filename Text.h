#pragma once

class Text {
private:
	char* text;
	int counter, length;
public:
	Text();
	Text(int length);
	void newChar(char input, Text& previous);
	~Text();
};