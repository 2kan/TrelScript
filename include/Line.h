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

#ifndef __LINE_H__
#define __LINE_H__

#include <string>
#include <vector>

class Line
{
public:
	Line();
	Line(std::string a_lineText);

	const std::string& line() const;
	const std::string& word(int a_index) const;
	std::string& word(int a_index);
	int wordCount() const;

	void setLine(std::string a_newLine, bool a_getWords = true);
	void getWords();

private:
	std::vector<std::string> m_words;
	std::string m_line;

};


#endif // __LINE_H__
