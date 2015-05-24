/*
Copyright 2015 TrelScript maintainers

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iostream>
#include <string>
#include "Line.h"
#include "main.h"

using namespace std;

Line::Line()
{
	setLine("Bad line ctor", false);
}

Line::Line(string a_lineText)
{
	setLine(a_lineText);
}

/************************
 *	Purpose / what it does
 *		Converts the given string and sets it to the object's 'line' character array
 *
 *	Parameters
 *		string	a_charArray		The line to be set
 *		bool	a_getWords		Default true. Whether or not to process the words in the line
 ************************/
void Line::setLine(std::string a_newLine, bool a_getWords)
{
	if (a_newLine[0] == 0 && a_newLine.size() == 1)
		numChars	= 0;
	else
		numChars	= a_newLine.size();
	a_newLine.copy(line, numChars);

	if (a_getWords)
		getWords();
}


/************************
 *	Purpose / what it does
 *		Splits the line object up into an array of words (delimitered by spaces)
 ************************/
void Line::getWords()
{
	// Used when testing characters from other arrays for a space-bar
	char space	= ' ';
	char tab	= '	';

	// Initialise the vairables we'll be using to locate words
	numWords = 0;
	char thisWord[1024];
	int charCounter	= 0;

	for (int i = 0; i < numChars; ++i)
	{
		// If this character in 'line' is a space or if we're at the end of the 'line' array, add word to the array of words
		if (line[i] == space || i == numChars - 1)
		{
			if (i == numChars - 1)
			{
				thisWord[charCounter]	= line[i];
				++charCounter;
			}

			words[numWords]	= charArrayToString(thisWord, charCounter);
			clearArray(thisWord, 1024);
			charCounter	= 0;
			++numWords;
		}
		// If it's not a 'flag' for a new word, record the letter and increment the character count
		else
		{
			if (line[i] != tab)
			{
				thisWord[charCounter] = line[i];
				++charCounter;
			}
		}

	}
}

/************************
 *	Purpose / what it does
 *		Clears the given array
 *
 *	Parameters
 *		char* a_array			Memory location of the array to nullify
 *		int a_arraySize			Number of elements in array
 ************************/
void Line::clearArray(char *a_array, int a_arraySize)
{
	// This should be obivous
	for (int i=0; i < a_arraySize; ++i)
		a_array[i] = NULL;
}

/************************
 *	Purpose / what it does
 *		Converts a character array to a string
 *
 *	Parameters
 *		char* a_charArray		The character array to convert to a string
 *		int a_usableSize		The number of chars to use (useful if there's padding at the end of the array)
 *
 *	Returns
 *		string					The char array as a string
 ************************/
string Line::charArrayToString(char* a_charArray, int a_usableSize)
{
	// Create new array of the size specified (plus one for the null character) so that we only use what is actual data (not the other padding)
	char *newArray	= new char[a_usableSize + 1];
	for (int i=0; i < a_usableSize; ++i)
		newArray[i]	= a_charArray[i];

	// Add the null character to prevent derps
	newArray[a_usableSize] = '\0';

	// Set to string so we can safely destroy the pointer array before returning
	string toReturn	= string(newArray);

	// Delete array and return string
	delete newArray;
	return toReturn;
}
