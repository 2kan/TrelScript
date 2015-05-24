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
#include <fstream>
#include <string>
#include "Interpreter.h"
#include "Function.h"
#include "Script.h"
#include "Line.h"

Script::Script()
{
	interpreter			= std::unique_ptr<Interpreter>(new Interpreter());
	m_filepath			= "";
	m_recursionDepth	= 0;

	m_open			= false;
	m_inLoop		= false;
	m_skipToRoasted	= false;
}

Script::Script(std::string a_filename) : Script()
{
	m_filepath = a_filename;
	m_open = getLines ();
}

Script::~Script()
{

}

void Script::setConfig(std::string a_settingName, std::string a_settingValue)
{
	std::string n = a_settingName;
	if (n == "recursionLimit")
	{
		m_recursionDepth = atoi(a_settingValue.c_str());
	}
}

void Script::setFunctions()
{
	std::string	line;
	std::ifstream file (m_filepath);
	int funcCount	= 0;
	int lineCount	= 0;
	while (std::getline(file, line))
	{
		++lineCount;
		if (line.substr(0, 4) == "spud")
		{
			m_functions[funcCount].setName(line.substr(5));
			m_functions[funcCount].lineStart	= lineCount;
		}
		else if (line == "burn spud")
		{
			m_functions[funcCount].lineEnd	= lineCount;
			++funcCount;
		}
	}
	file.close();
}

bool Script::getLines()
{
	// Open the file
	std::ifstream file(m_filepath);
	if (!file.is_open())
	{
		return false;
	}

	std::string line;
	int lineCount = 0;

	while (file.good())
	{
		line.clear();
		std::getline(file, line);
		m_lines.push_back(line);

		++lineCount;
	}

	file.close();

	return (m_lines.size() > 0);
}

bool Script::executeScript()
{
	if (!m_open)
	{
		std::cout << "No script file specified.\n";
		return false;
	}

	bool skipLine = false;

	// Yo dawg, I heard you like loops, so we put a loop in your loop so you can loop while you loop
	for (unsigned int lineNum = 0; lineNum < m_lines.size(); ++lineNum)
	{
		if (m_lines[lineNum].line()[0] != '\0' && !m_skipToRoasted)// && lines[lineNum].word(0) != "roasted")) // If it's an empty line, just ignore it
		{
			// Check if the script calls a function
			if (m_lines[lineNum].word(0) == "eat" && !skipLine)
			{
				// If there is a lib function with the name, run it. If not, run the script with the same name
				if (runLibFunction(m_lines[lineNum].word(1)) == 1) // Returns 1 if could not find a lib func with specified name
					executeFunction(m_lines[lineNum].word(1));
			}
			else if (m_lines[lineNum].word(0) == "roast" && m_lines[lineNum].word(1) == "while")
			{
				if (interpreter->conditionResult(m_lines[lineNum].word(2), m_lines[lineNum].word(4), m_lines[lineNum].word(3)))
				{
					m_inLoop	= true;
					m_loopLine	= lineNum;
				}
				else
				{
					m_skipToRoasted	= true;
				}
			}
			else if (m_lines[lineNum].word(0) == "roasted" && m_inLoop)
			{
				m_inLoop	= false;
				lineNum		= m_loopLine - 1;
			}
			else
			{
				if (m_lines[lineNum].word(0) == "spud")
					skipLine	= true;

				if (!skipLine)
				{
					// If the interpreter returns zero, exit the program (means a call to "divide by zero")
					if (interpreter->interpretLine(m_lines[lineNum]) == 0)
						break;
				}

				if (m_lines[lineNum].word(0) == "burn")
					skipLine	= false;
			}
		}
		else if (m_skipToRoasted && m_lines[lineNum].word(0) == "roasted")
		{
			m_skipToRoasted	= false;
		}
	}

	return true;
}

int Script::executeFunction(std::string a_funcName)
{
	for (unsigned int i = 0; i < m_functions.size(); ++i) // Get the function it called
	{
		if (m_functions[i].getName() == a_funcName)
		{
			Line inlineCommand;
			inlineCommand.setLine("ham barf");

			// Create new scope for function
			interpreter->interpretLine(inlineCommand);
			// Execute each line of the function, then break
			for (int funcLineNum = m_functions[i].lineStart; funcLineNum < m_functions[i].lineEnd - 1; ++funcLineNum)
			{
				if (m_lines[funcLineNum].word(0) == "eat")
				{
					// Protect against a stack overflow.. kinda
					if (m_recursionDepth < 5)
					{
						++m_recursionDepth;
						executeFunction(m_lines[funcLineNum].word(1));
						--m_recursionDepth;
					}
					else
					{
						std::cout << "Recursion limit reached.\n";
					}
				}
				else
				{
					interpreter->interpretLine(m_lines[funcLineNum]);
				}
			}
			// End the scope
			inlineCommand.setLine("ham eat");
			interpreter->interpretLine(inlineCommand);
			break;
		}
	}

	return 0;
}


// Trelscript as a lib implementation
void Script::addLibFunction(std::string a_funcName, void(*a_func)())
{
	for (unsigned int i = 0; i < m_libFuncs.size(); ++i)
	{
		if (m_libFuncs[i].m_pFunction == nullptr)
		{
			m_libFuncs[i].setName(a_funcName);
			m_libFuncs[i].setFuncPtr(a_func);
		}
	}
}

int Script::runLibFunction(std::string a_funcName)
{
	for (unsigned int i = 0; i < m_libFuncs.size(); ++i)
	{
		if (m_libFuncs[i].getName() == a_funcName)
		{
			m_libFuncs[i].runFunc();
			return 0;
		}
	}

	return 1;
}
