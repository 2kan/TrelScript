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

#include "Line.h"
#include <array>

Line::Line()
{
	setLine("Bad line ctor", false);
}

Line::Line(std::string a_lineText)
{
	setLine(a_lineText);
}


const std::string& Line::line() const
{
	return m_line;
}

const std::string& Line::word(int a_index) const
{
	return m_words[a_index];
}

std::string& Line::word(int a_index)
{
	return m_words[a_index];
}

int Line::wordCount() const
{
	return m_words.size();
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
	m_line = a_newLine;

	if (a_getWords)
		getWords();
}


/************************
 *	Purpose / what it does
 *		Splits the line object up into an array of words (delimitered by spaces)
 ************************/
void Line::getWords()
{
	// First clear the words vector.
	m_words.clear();

	// Characters used for separation.
	std::array<char, 2> seperators = {' ', '\t'};

	size_t i, lastIndex = 0;
	for (i = 0; i < m_line.size(); ++i)
	{
		for (unsigned int j = 0; j < seperators.size(); ++j)
		{
			if (m_line[i] == seperators[j])
			{
				size_t len = i - lastIndex;
				if (len > 0)
				{
					std::string word = m_line.substr(lastIndex, len);
					m_words.push_back(word);
					lastIndex = i + 1;
					break;
				}
				lastIndex = i + 1;
			}
		}
	}
	
	size_t len = --i - lastIndex;
	if (len > 0)
	{
		std::string word = m_line.substr(lastIndex, len);
		m_words.push_back(word);
	}
}
