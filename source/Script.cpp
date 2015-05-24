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

#include <fstream>
#include <string>
#include "Interpreter.h"
#include "Function.h"
#include "Script.h"
#include "Line.h"

Script::Script()
{
	interpreter		= new Interpreter();
	m_filepath		= "";
	m_numberOfLines	= 0;
	m_numberOfFunctions	= 0;
	m_recursionDepth	= 0;
	lines			= new Line[1];
	functions		= new Function[1];
	
	maxLibFuncs	= 10;
	libFunctions	= new Function[10];

	m_inLoop		= false;
	m_skipToRoasted	= false;
}

Script::Script(std::string a_filename)
{
	interpreter		= new Interpreter();
	m_filepath		= a_filename;
	m_numberOfLines	= 0;
	m_numberOfFunctions	= 0;
	m_recursionDepth	= 0;
	getLineCount();
	lines			= new Line[m_numberOfLines];
	functions		= new Function[m_numberOfFunctions];
	getLines();
	setFunctions();
	
	maxLibFuncs	= 10;
	libFunctions	= new Function[10];

	m_inLoop		= false;
	m_skipToRoasted	= false;
}

Script::~Script()
{
	delete[] lines;
	delete[] functions;
	delete interpreter;
}

void Script::setConfig(std::string a_settingName, std::string a_settingValue)
{
	std::string n	= a_settingName;
	if(n == "recursionLimit")
	{
		m_recursionDepth = atoi(a_settingValue.c_str());
	}
}

void Script::getLineCount()
{
	std::string	line;
	m_file.open(m_filepath.c_str());
	while (std::getline(m_file, line))
	{
		++m_numberOfLines;
		if(line.substr(0,4) == "spud")
			++m_numberOfFunctions;
	}
	m_file.close();
}

void Script::setFunctions()
{
	std::string	line;
	m_file.open(m_filepath.c_str());
	int funcCount	= 0;
	int lineCount	= 0;
	while (std::getline(m_file, line))
	{
		++lineCount;
		if(line.substr(0,4) == "spud")
		{
			functions[funcCount].setName(line.substr(5));
			functions[funcCount].lineStart	= lineCount;
		}
		else if(line == "burn spud")
		{
			functions[funcCount].lineEnd	= lineCount;
			++funcCount;
		}
	}
	m_file.close();
}

void Script::getLines()
{
	// Open the file
	m_file.open(m_filepath.c_str());
	std::string line;
	int lineCount	= 0;

	while(m_file.good())
	{
		line.clear();
		getline(m_file, line);
		lines[lineCount].setLine(line + '\0');

		++lineCount;
	}
	m_file.close();
}

bool Script::executeScript()
{
	if(m_filepath != "")
	{
		bool skipLine	= false;

		// Yo dawg, I heard you like loops, so we put a loop in your loop so you can loop while you loop
		for(int lineNum=0; lineNum<m_numberOfLines; ++lineNum)
		{
			if(lines[lineNum].line[0] != '\0' && !m_skipToRoasted)// && lines[lineNum].words[0] != "roasted")) // If it's an empty line, just ignore it
			{
				// Check if the script calls a function
				if(lines[lineNum].words[0] == "eat" && !skipLine)
				{
					// If there is a lib function with the name, run it. If not, run the script with the same name
					if(runLibFunction(lines[lineNum].words[1]) == 1) // Returns 1 if could not find a lib func with specified name
						executeFunction(lines[lineNum].words[1]);
				}
				else if(lines[lineNum].words[0] == "roast" && lines[lineNum].words[1] == "while")
				{
					if(interpreter->conditionResult(lines[lineNum].words[2], lines[lineNum].words[4], lines[lineNum].words[3]))
					{
						m_inLoop	= true;
						m_loopLine	= lineNum;
					}
					else
					{
						m_skipToRoasted	= true;
					}
				}
				else if(lines[lineNum].words[0] == "roasted" && m_inLoop)
				{
					m_inLoop	= false;
					lineNum		= m_loopLine - 1;
				}
				else 
				{
					if(lines[lineNum].words[0] == "spud")
						skipLine	= true;

					if(!skipLine)
					{
						// If the interpreter returns zero, exit the program (means a call to "divide by zero")
						if(interpreter->interpretLine(lines[lineNum]) == 0)
							break;
					}
					
					if(lines[lineNum].words[0] == "burn")
						skipLine	= false;
				}
			}
			else if(m_skipToRoasted && lines[lineNum].words[0] == "roasted")
			{
				m_skipToRoasted	= false;
			}
		}
	}
	else
	{
		std::cout << "No script file specified.\n";
	}

	return true;
}

int Script::executeFunction(std::string a_funcName)
{
	for(int i=0; i<m_numberOfFunctions; ++i) // Get the function it called
	{
		if(functions[i].getName() == a_funcName)
		{
			Line inlineCommand;
			inlineCommand.setLine("ham barf");

			// Create new scope for function
			interpreter->interpretLine(inlineCommand);
			// Execute each line of the function, then break
			for(int funcLineNum=functions[i].lineStart; funcLineNum<functions[i].lineEnd-1; ++funcLineNum)
			{
				if(lines[funcLineNum].words[0] == "eat")
				{
					// Protect against a stack overflow.. kinda
					if(m_recursionDepth < 5)
					{
						++m_recursionDepth;
						executeFunction(lines[funcLineNum].words[1]);
						--m_recursionDepth;
					}
					else
					{
						std::cout << "Recursion limit reached.\n";
					}
				}
				else
					interpreter->interpretLine(lines[funcLineNum]);
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

void Script::addLibFunction(std::string a_funcName, void (*a_func)())
{
	for(int i=0; i<maxLibFuncs; ++i)
	{
		if(libFunctions->m_pFunction == NULL)
		{
			libFunctions->setName(a_funcName);
			libFunctions->setFuncPtr(a_func);
		}
	}
}

int Script::runLibFunction(std::string a_funcName)
{
	for(int i=0; i<maxLibFuncs; ++i)
	{
		if(libFunctions[i].getName() == a_funcName)
		{
			libFunctions[i].runFunc();
			return 0;
		}
	}
	
	return 1;
}