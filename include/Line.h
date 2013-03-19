#ifndef __LINE_H__
#define __LINE_H__

#include <iostream>

struct Line {
	std::string words[1024];
	char line[1024];
	int numChars;
	int numWords;

	void setLine(std::string a_newLine, bool a_getWords = true);
	void getWords();
	
	void clearArray(char*, int);
	std::string charArrayToString(char*, int);
};


#endif // __LINE_H__