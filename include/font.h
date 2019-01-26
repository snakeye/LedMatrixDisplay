#pragma once

class Font {
public:
	int getCharWidth(char ch);
	int getStringWidth(const char* str);

	unsigned char getCharColumn(char ch, int col);
};
