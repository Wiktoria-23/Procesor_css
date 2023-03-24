#pragma once

class Text {
private:
	char* text;
	int counter, length;
public:
	Text();
	Text(int length);
	Text(Text& text);
	void newChar(char input, Text& previous);
	~Text();
};